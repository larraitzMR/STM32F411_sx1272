/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech
 ___ _____ _   ___ _  _____ ___  ___  ___ ___
/ __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
\__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
|___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
embedded.connectivity.solutions===============

Description: LoRa MAC region US915 implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis ( Semtech ), Gregory Cristian ( Semtech ) and Daniel Jaeckle ( STACKFORCE )
*/
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "radio.h"
#include "timer.h"
#include "LoRaMac.h"

#include "utilities.h"

#include "Region.h"
#include "RegionCommon.h"
#include "RegionUS915.h"
//#include "debug.h"


// Definitions
#define CHANNELS_MASK_SIZE              6



// Global attributes
/*!
 * LoRaMAC channels
 */
static ChannelParams_t Channels[US915_MAX_NB_CHANNELS];

/*!
 * LoRaMac bands
 */
static Band_t Bands[US915_MAX_NB_BANDS] =
{
    US915_BAND0
};

/*!
 * LoRaMac channels mask
 */
static uint16_t ChannelsMask[CHANNELS_MASK_SIZE];

/*!
 * LoRaMac channels remaining
 */
static uint16_t ChannelsMaskRemaining[CHANNELS_MASK_SIZE];

/*!
 * LoRaMac channels default mask
 */
static uint16_t ChannelsDefaultMask[CHANNELS_MASK_SIZE];



// Static functions
static uint8_t ApplyDrOffset( int8_t dr, int8_t drOffset )
{
    int8_t datarate = DatarateOffsetsUS915[dr][drOffset];

    if( datarate < 0 )
    {
        datarate = DR_0;
    }
    return datarate;
}

static uint16_t GetSymbTimeout( int8_t dr )
{
    uint16_t symbolTimeout = 5;

    switch( dr )
    {
        case DR_0:      // SF10 - BW125
        {
            symbolTimeout = 5;
            break;
        }
        case DR_1:      // SF9  - BW125
        case DR_2:      // SF8  - BW125
        case DR_8:      // SF12 - BW500
        case DR_9:      // SF11 - BW500
        case DR_10:     // SF10 - BW500
        {
            symbolTimeout = 8;
            break;
        }
        case DR_3:      // SF7  - BW125
        case DR_11:     // SF9  - BW500
        {
            symbolTimeout = 10;
            break;
        }
        case DR_4:      // SF8  - BW500
        case DR_12:     // SF8  - BW500
        {
            symbolTimeout = 14;
            break;
        }
        case DR_13:     // SF7  - BW500
        {
            symbolTimeout = 16;
            break;
        }
    }
    return symbolTimeout;
}

static uint32_t GetBandwidth( int8_t dr )
{
    uint32_t bandwidth = 0;

    if( dr > DR_4 )
    { // LoRa 500 kHz
        bandwidth = 2;
    }
    return bandwidth;
}

static int8_t LimitTxPower( int8_t txPower, int8_t datarate, uint16_t* channelsMask )
{
    int8_t txPowerResult = txPower;

    if( ( datarate == DR_4 ) || ( ( datarate >= DR_8 ) && ( datarate <= DR_13 ) ) )
    {// Limit tx power to max 26dBm
        txPowerResult = MAX( txPower, TX_POWER_2 );
    }
    else
    {
        if( RegionCommonCountChannels( channelsMask, 0, 4 ) < 50 )
        {// Limit tx power to max 21dBm
            txPowerResult = MAX( txPower, TX_POWER_5 );
        }
    }
    return txPowerResult;
}

static uint8_t CountNbOfEnabledChannels( uint8_t datarate, uint16_t* channelsMask, ChannelParams_t* channels, Band_t* bands, uint8_t* enabledChannels, uint8_t* delayTx )
{
    uint8_t nbEnabledChannels = 0;
    uint8_t delayTransmission = 0;

    for( uint8_t i = 0, k = 0; i < US915_MAX_NB_CHANNELS; i += 16, k++ )
    {
        for( uint8_t j = 0; j < 16; j++ )
        {
            if( ( channelsMask[k] & ( 1 << j ) ) != 0 )
            {
                if( channels[i + j].Frequency == 0 )
                { // Check if the channel is enabled
                    continue;
                }
                if( RegionCommonValueInRange( datarate, channels[i + j].DrRange.Fields.Min,
                                              channels[i + j].DrRange.Fields.Max ) == false )
                { // Check if the current channel selection supports the given datarate
                    continue;
                }
                if( bands[channels[i + j].Band].TimeOff > 0 )
                { // Check if the band is available for transmission
                    delayTransmission++;
                    continue;
                }
                enabledChannels[nbEnabledChannels++] = i + j;
            }
        }
    }

    *delayTx = delayTransmission;
    return nbEnabledChannels;
}


void RegionUS915GetPhyParam( GetPhyParams_t* getPhy )
{
    switch( getPhy->Attribute )
    {
        case PHY_MIN_DR:
        {
            getPhy->Param.Value = US915_TX_MIN_DATARATE;
            break;
        }
        case PHY_DEF_TX_DR:
        {
            getPhy->Param.Value = US915_DEFAULT_DATARATE;
            break;
        }
        case PHY_DEF_TX_POWER:
        {
            getPhy->Param.Value = US915_DEFAULT_TX_POWER;
            break;
        }
        case PHY_MAX_PAYLOAD:
        {
            getPhy->Param.Value = MaxPayloadOfDatarateUS915[getPhy->Datarate];
            break;
        }
        case PHY_MAX_PAYLOAD_REPEATER:
        {
            getPhy->Param.Value = MaxPayloadOfDatarateRepeaterUS915[getPhy->Datarate];
            break;
        }
        case PHY_DUTY_CYCLE:
        {
            getPhy->Param.Value = US915_DUTY_CYCLE_ENABLED;
            break;
        }
        case PHY_MAX_RX_WINDOW:
        {
            getPhy->Param.Value = US915_MAX_RX_WINDOW;
            break;
        }
        case PHY_RECEIVE_DELAY1:
        {
            getPhy->Param.Value = US915_RECEIVE_DELAY1;
            break;
        }
        case PHY_RECEIVE_DELAY2:
        {
            getPhy->Param.Value = US915_RECEIVE_DELAY2;
            break;
        }
        case PHY_JOIN_ACCEPT_DELAY1:
        {
            getPhy->Param.Value = US915_JOIN_ACCEPT_DELAY1;
            break;
        }
        case PHY_JOIN_ACCEPT_DELAY2:
        {
            getPhy->Param.Value = US915_JOIN_ACCEPT_DELAY2;
            break;
        }
        case PHY_MAX_FCNT_GAP:
        {
            getPhy->Param.Value = US915_MAX_FCNT_GAP;
            break;
        }
        case PHY_ACK_TIMEOUT:
        {
            getPhy->Param.Value = ( US915_ACKTIMEOUT + randr( -US915_ACK_TIMEOUT_RND, US915_ACK_TIMEOUT_RND ) );
            break;
        }
        case PHY_DEF_DR1_OFFSET:
        {
            getPhy->Param.Value = US915_DEFAULT_RX1_DR_OFFSET;
            break;
        }
        case PHY_DEF_RX2_FREQUENCY:
        {
            getPhy->Param.Value = US915_RX_WND_2_FREQ;
            break;
        }
        case PHY_DEF_RX2_DR:
        {
            getPhy->Param.Value = US915_RX_WND_2_DR;
            break;
        }
        case PHY_CHANNELS_MASK:
        {
            getPhy->Param.ChannelsMask = ChannelsMask;
            break;
        }
        case PHY_CHANNELS_DEFAULT_MASK:
        {
            getPhy->Param.ChannelsMask = ChannelsDefaultMask;
            break;
        }
        case PHY_MAX_NB_CHANNELS:
        {
            getPhy->Param.Value = US915_MAX_NB_CHANNELS;
            break;
        }
        case PHY_CHANNELS:
        {
            getPhy->Param.Channels = Channels;
            break;
        }
        case PHY_DEF_UPLINK_DWELL_TIME:
        case PHY_DEF_DOWNLINK_DWELL_TIME:
        case PHY_DEF_MAX_EIRP:
        {
            getPhy->Param.Value = 0;
            break;
        }
        case PHY_NB_JOIN_TRIALS:
        case PHY_DEF_NB_JOIN_TRIALS:
        {
            getPhy->Param.Value = 2;
            break;
        }
        default:
        {
            return;
        }
    }
}

void RegionUS915SetBandTxDone( SetBandTxDoneParams_t* txDone )
{
    RegionCommonSetBandTxDone( &Bands[Channels[txDone->Channel].Band], txDone->LastTxDoneTime );
}

void RegionUS915InitDefaults( InitType_t type )
{
    switch( type )
    {
        case INIT_TYPE_INIT:
        {
            // Channels
            // 125 kHz channels
            for( uint8_t i = 0; i < US915_MAX_NB_CHANNELS - 8; i++ )
            {
                Channels[i].Frequency = 902300000 + i * 200000;
                Channels[i].DrRange.Value = ( DR_3 << 4 ) | DR_0;
                Channels[i].Band = 0;
            }
            // 500 kHz channels
            for( uint8_t i = US915_MAX_NB_CHANNELS - 8; i < US915_MAX_NB_CHANNELS; i++ )
            {
                Channels[i].Frequency = 903000000 + ( i - ( US915_MAX_NB_CHANNELS - 8 ) ) * 1600000;
                Channels[i].DrRange.Value = ( DR_4 << 4 ) | DR_4;
                Channels[i].Band = 0;
            }

            // ChannelsMask
            ChannelsDefaultMask[0] = 0xFFFF;
            ChannelsDefaultMask[1] = 0xFFFF;
            ChannelsDefaultMask[2] = 0xFFFF;
            ChannelsDefaultMask[3] = 0xFFFF;
            ChannelsDefaultMask[4] = 0x00FF;
            ChannelsDefaultMask[5] = 0x0000;

            // Copy channels default mask
            RegionCommonChanMaskCopy( ChannelsMask, ChannelsDefaultMask, 6 );

            // Copy into channels mask remaining
            RegionCommonChanMaskCopy( ChannelsMaskRemaining, ChannelsMask, 6 );
            break;
        }
        case INIT_TYPE_RESTORE:
        {
            // Copy channels default mask
            RegionCommonChanMaskCopy( ChannelsMask, ChannelsDefaultMask, 6 );

            for( uint8_t i = 0; i < 6; i++ )
            { // Copy-And the channels mask
                ChannelsMaskRemaining[i] &= ChannelsMask[i];
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

bool RegionUS915Verify( VerifyParams_t* verify, PhyAttribute_t phyAttribute )
{
    switch( phyAttribute )
    {
        case PHY_TX_DR:
        {
            return RegionCommonValueInRange( verify->Datarate, US915_TX_MIN_DATARATE, US915_TX_MAX_DATARATE );
        }
        case PHY_DEF_TX_DR:
        {
            return RegionCommonValueInRange( verify->Datarate, DR_0, DR_5 );
        }
        case PHY_DEF_TX_POWER:
        case PHY_TX_POWER:
        {
            // Remark: switched min and max!
            return RegionCommonValueInRange( verify->TxPower, US915_MAX_TX_POWER, US915_MIN_TX_POWER );
        }
        case PHY_DUTY_CYCLE:
        {
            return US915_DUTY_CYCLE_ENABLED;
        }
        case PHY_NB_JOIN_TRIALS:
        {
            if( verify->NbJoinTrials < 2 )
            {
                return false;
            }
            break;
        }
        default:
            return false;
    }
    return true;
}

void RegionUS915ApplyCFList( ApplyCFListParams_t* applyCFList )
{
    return;
}

bool RegionUS915ChanMaskSet( ChanMaskSetParams_t* chanMaskSet )
{
    uint8_t nbChannels = RegionCommonCountChannels( chanMaskSet->ChannelsMaskIn, 0, 4 );

    // Check the number of active channels
    if( ( nbChannels < 2 ) &&
        ( nbChannels > 0 ) )
    {
        return false;
    }

    switch( chanMaskSet->ChannelsMaskType )
    {
        case CHANNELS_MASK:
        {
            RegionCommonChanMaskCopy( ChannelsMask, chanMaskSet->ChannelsMaskIn, 6 );

            for( uint8_t i = 0; i < 6; i++ )
            { // Copy-And the channels mask
                ChannelsMaskRemaining[i] &= ChannelsMask[i];
            }
            break;
        }
        case CHANNELS_DEFAULT_MASK:
        {
            RegionCommonChanMaskCopy( ChannelsDefaultMask, chanMaskSet->ChannelsMaskIn, 6 );
            break;
        }
        default:
            return false;
    }
    return true;
}

bool RegionUS915AdrNext( AdrNextParams_t* adrNext, int8_t* drOut, int8_t* txPowOut, uint32_t* adrAckCounter )
{
    bool adrAckReq = false;
    int8_t datarate = adrNext->Datarate;
    int8_t txPower = adrNext->TxPower;

    // Report back the adr ack counter
    *adrAckCounter = adrNext->AdrAckCounter;

    if( adrNext->AdrEnabled == true )
    {
        if( datarate == US915_TX_MIN_DATARATE )
        {
            *adrAckCounter = 0;
            adrAckReq = false;
        }
        else
        {
            if( adrNext->AdrAckCounter >= US915_ADR_ACK_LIMIT )
            {
                adrAckReq = true;
            }
            else
            {
                adrAckReq = false;
            }
            if( adrNext->AdrAckCounter >= ( US915_ADR_ACK_LIMIT + US915_ADR_ACK_DELAY ) )
            {
                if( ( adrNext->AdrAckCounter % US915_ADR_ACK_DELAY ) == 0 )
                {
                    if( txPower == US915_MAX_TX_POWER )
                    {
                        if( ( datarate > US915_TX_MIN_DATARATE ) && ( datarate == DR_8 ) )
                        {
                            datarate = DR_4;
                        }
                        else if( datarate > US915_TX_MIN_DATARATE )
                        {
                            datarate--;
                        }

                        if( datarate == US915_TX_MIN_DATARATE )
                        {
                            if( adrNext->UpdateChanMask == true )
                            {
                                // Re-enable default channels
                                ChannelsMask[0] = 0xFFFF;
                                ChannelsMask[1] = 0xFFFF;
                                ChannelsMask[2] = 0xFFFF;
                                ChannelsMask[3] = 0xFFFF;
                                ChannelsMask[4] = 0x00FF;
                                ChannelsMask[5] = 0x0000;
                            }
                        }
                    }
                    else
                    {
                        txPower = US915_MAX_TX_POWER;
                    }
                }
            }
        }
    }

    *drOut = datarate;
    *txPowOut = txPower;
    return adrAckReq;
}

bool RegionUS915RxConfig( RxConfigParams_t* rxConfig, int8_t* datarate )
{
    int8_t dr = rxConfig->Datarate;
    uint8_t maxPayload = 0;
    uint16_t symbTimeout = 0;
    uint32_t bandwidth = 0;
    int8_t phyDr = 0;
    uint32_t frequency = rxConfig->Frequency;

    if( Radio.GetStatus( ) != RF_IDLE )
    {
        return false;
    }

    if( rxConfig->Window == 0 )
    {
        // Apply the datarate offset for RX window 1
        dr = ApplyDrOffset( dr, rxConfig->DrOffset );
        // Apply window 1 frequency
        frequency = US915_FIRST_RX1_CHANNEL + ( rxConfig->Channel % 8 ) * US915_STEPWIDTH_RX1_CHANNEL;
    }
    symbTimeout = GetSymbTimeout( dr );
    bandwidth = GetBandwidth( dr );
    // Read the physical datarate from the datarates table
    phyDr = DataratesUS915[dr];

    Radio.SetChannel( frequency );

    Radio.SetRxConfig( MODEM_LORA, bandwidth, phyDr, 1, 0, 8, symbTimeout, false, 0, false, 0, 0, true, rxConfig->RxContinuous );

    if( rxConfig->RepeaterSupport == true )
    {
        maxPayload = MaxPayloadOfDatarateRepeaterUS915[dr];
    }
    else
    {
        maxPayload = MaxPayloadOfDatarateUS915[dr];
    }
    Radio.SetMaxPayloadLength( MODEM_LORA, maxPayload + LORA_MAC_FRMPAYLOAD_OVERHEAD );
    
    DBG_PRINTF("RX on freq %d Hz at DR %d\n\r", frequency, dr);

    *datarate = (uint8_t) dr;
    return true;
}

bool RegionUS915TxConfig( TxConfigParams_t* txConfig, int8_t* txPower, TimerTime_t* txTimeOnAir )
{
    int8_t phyDr = DataratesUS915[txConfig->Datarate];
    int8_t txPowerLimited = LimitTxPower( txConfig->TxPower, txConfig->Datarate, ChannelsMask );
    uint32_t bandwidth = GetBandwidth( txConfig->Datarate );
    int8_t phyTxPower = 0;

    phyTxPower = TxPowersUS915[txPowerLimited];

    Radio.SetChannel( Channels[txConfig->Channel].Frequency );

    Radio.SetMaxPayloadLength( MODEM_LORA, txConfig->PktLen );
    Radio.SetTxConfig( MODEM_LORA, phyTxPower, 0, bandwidth, phyDr, 1, 8, false, true, 0, 0, false, 3e3 );
  
    DBG_PRINTF("TX on freq %d Hz at DR %d\n\r", Channels[txConfig->Channel].Frequency, txConfig->Datarate);

    *txTimeOnAir = Radio.TimeOnAir( MODEM_LORA,  txConfig->PktLen );
    *txPower = txPowerLimited;

    return true;
}

uint8_t RegionUS915LinkAdrReq( LinkAdrReqParams_t* linkAdrReq, int8_t* drOut, int8_t* txPowOut, uint8_t* nbRepOut, uint8_t* nbBytesParsed )
{
    uint8_t status = 0x07;
    LinkAdrParams_t linkAdrParams;
    uint8_t nextIndex = 0;
    uint8_t bytesProcessed = 0;
    uint16_t channelsMask[6] = { 0, 0, 0, 0, 0, 0 };

    // Initialize local copy of channels mask
    RegionCommonChanMaskCopy( channelsMask, ChannelsMask, 6 );

    while( bytesProcessed < linkAdrReq->PayloadSize )
    {
        nextIndex = RegionCommonParseLinkAdrReq( &( linkAdrReq->Payload[bytesProcessed] ), &linkAdrParams );

        if( nextIndex == 0 )
            break; // break loop, since no more request has been found

        // Update bytes processed
        bytesProcessed += nextIndex;

        // Revert status, as we only check the last ADR request for the channel mask KO
        status = 0x07;

        if( linkAdrParams.ChMaskCtrl == 6 )
        {
            // Enable all 125 kHz channels
            channelsMask[0] = 0xFFFF;
            channelsMask[1] = 0xFFFF;
            channelsMask[2] = 0xFFFF;
            channelsMask[3] = 0xFFFF;
            // Apply chMask to channels 64 to 71
            channelsMask[4] = linkAdrParams.ChMask;
        }
        else if( linkAdrParams.ChMaskCtrl == 7 )
        {
            // Disable all 125 kHz channels
            channelsMask[0] = 0x0000;
            channelsMask[1] = 0x0000;
            channelsMask[2] = 0x0000;
            channelsMask[3] = 0x0000;
            // Apply chMask to channels 64 to 71
            channelsMask[4] = linkAdrParams.ChMask;
        }
        else if( linkAdrParams.ChMaskCtrl == 5 )
        {
            // RFU
            status &= 0xFE; // Channel mask KO
        }
        else
        {
            channelsMask[linkAdrParams.ChMaskCtrl] = linkAdrParams.ChMask;
        }
    }

    // FCC 15.247 paragraph F mandates to hop on at least 2 125 kHz channels
    if( ( linkAdrParams.Datarate < DR_4 ) && ( RegionCommonCountChannels( channelsMask, 0, 4 ) < 2 ) )
    {
        status &= 0xFE; // Channel mask KO
    }

    // Verify datarate
    if( RegionCommonChanVerifyDr( US915_MAX_NB_CHANNELS, channelsMask, linkAdrParams.Datarate, US915_TX_MIN_DATARATE, US915_TX_MAX_DATARATE, Channels  ) == false )
    {
        status &= 0xFD; // Datarate KO
    }

    // Verify tx power
    if( RegionCommonValueInRange( linkAdrParams.TxPower, US915_MAX_TX_POWER, US915_MIN_TX_POWER ) == 0 )
    {
        // Verify if the maximum TX power is exceeded
        if( US915_MAX_TX_POWER > linkAdrParams.TxPower )
        { // Apply maximum TX power. Accept TX power.
            linkAdrParams.TxPower = US915_MAX_TX_POWER;
        }
        else
        {
            status &= 0xFB; // TxPower KO
        }
    }

    // Update channelsMask if everything is correct
    if( status == 0x07 )
    {
        if( linkAdrParams.NbRep == 0 )
        { // Value of 0 is not allowed, revert to default.
            linkAdrParams.NbRep = 1;
        }

        // Copy Mask
        RegionCommonChanMaskCopy( ChannelsMask, channelsMask, 6 );

        ChannelsMaskRemaining[0] &= ChannelsMask[0];
        ChannelsMaskRemaining[1] &= ChannelsMask[1];
        ChannelsMaskRemaining[2] &= ChannelsMask[2];
        ChannelsMaskRemaining[3] &= ChannelsMask[3];
        ChannelsMaskRemaining[4] = ChannelsMask[4];
        ChannelsMaskRemaining[5] = ChannelsMask[5];
    }

    // Update status variables
    *drOut = linkAdrParams.Datarate;
    *txPowOut = linkAdrParams.TxPower;
    *nbRepOut = linkAdrParams.NbRep;
    *nbBytesParsed = bytesProcessed;

    return status;
}

uint8_t RegionUS915RxParamSetupReq( RxParamSetupReqParams_t* rxParamSetupReq )
{
    uint8_t status = 0x07;
    uint32_t freq = rxParamSetupReq->Frequency;

    // Verify radio frequency
    if( ( Radio.CheckRfFrequency( freq ) == false ) ||
        ( freq < US915_FIRST_RX1_CHANNEL ) ||
        ( freq > US915_LAST_RX1_CHANNEL ) ||
        ( ( ( freq - ( uint32_t ) US915_FIRST_RX1_CHANNEL ) % ( uint32_t ) US915_STEPWIDTH_RX1_CHANNEL ) != 0 ) )
    {
        status &= 0xFE; // Channel frequency KO
    }

    // Verify datarate
    if( RegionCommonValueInRange( rxParamSetupReq->Datarate, US915_RX_MIN_DATARATE, US915_RX_MAX_DATARATE ) == false )
    {
        status &= 0xFD; // Datarate KO
    }
    if( ( RegionCommonValueInRange( rxParamSetupReq->Datarate, DR_5, DR_7 ) == true ) ||
        ( rxParamSetupReq->Datarate > DR_13 ) )
    {
        status &= 0xFD; // Datarate KO
    }

    // Verify datarate offset
    if( RegionCommonValueInRange( rxParamSetupReq->DrOffset, US915_MIN_RX1_DR_OFFSET, US915_MAX_RX1_DR_OFFSET ) == false )
    {
        status &= 0xFB; // Rx1DrOffset range KO
    }

    return status;
}

uint8_t RegionUS915NewChannelReq( NewChannelReqParams_t* newChannelReq )
{
    // Datarate and frequency KO
    return 0;
}

int8_t RegionUS915TxParamSetupReq( TxParamSetupReqParams_t* txParamSetupReq )
{
    return -1;
}

uint8_t RegionUS915DlChannelReq( DlChannelReqParams_t* dlChannelReq )
{
    return 0;
}

int8_t RegionUS915AlternateDr( AlternateDrParams_t* alternateDr )
{
    int8_t datarate = 0;

    // Re-enable 500 kHz default channels
    ChannelsMask[4] = 0x00FF;

    if( ( alternateDr->NbTrials & 0x01 ) == 0x01 )
    {
        datarate = DR_4;
    }
    else
    {
        datarate = DR_0;
    }
    return datarate;
}

void RegionUS915CalcBackOff( CalcBackOffParams_t* calcBackOff )
{
    uint8_t channel = calcBackOff->Channel;

    Bands[Channels[channel].Band].TimeOff = 0;
}

bool RegionUS915NextChannel( NextChanParams_t* nextChanParams, uint8_t* channel, TimerTime_t* time )
{
    uint8_t nbEnabledChannels = 0;
    uint8_t delayTx = 0;
    uint8_t enabledChannels[US915_MAX_NB_CHANNELS] = { 0 };
    TimerTime_t nextTxDelay = ( TimerTime_t )( -1 );

    // Count 125kHz channels
    if( RegionCommonCountChannels( ChannelsMaskRemaining, 0, 4 ) == 0 )
    { // Reactivate default channels
        RegionCommonChanMaskCopy( ChannelsMaskRemaining, ChannelsMask, 4  );
    }
    // Check other channels
    if( nextChanParams->Datarate >= DR_4 )
    {
        if( ( ChannelsMaskRemaining[4] & 0x00FF ) == 0 )
        {
            ChannelsMaskRemaining[4] = ChannelsMask[4];
        }
    }

    if( nextChanParams->AggrTimeOff <= TimerGetElapsedTime( nextChanParams->LastAggrTx ) )
    {
        // Search how many channels are enabled
        nbEnabledChannels = CountNbOfEnabledChannels( nextChanParams->Datarate,
                                                      ChannelsMask, Channels,
                                                      Bands, enabledChannels, &delayTx );
    }
    else
    {
        delayTx++;
        nextTxDelay = nextChanParams->AggrTimeOff - TimerGetElapsedTime( nextChanParams->LastAggrTx );
    }

    if( nbEnabledChannels > 0 )
    {
        // We found a valid channel
        *channel = enabledChannels[randr( 0, nbEnabledChannels - 1 )];
        // Disable the channel in the mask
        RegionCommonChanDisable( ChannelsMaskRemaining, *channel, US915_MAX_NB_CHANNELS - 8 );

        *time = 0;
        return true;
    }
    else
    {
        if( delayTx > 0 )
        {
            // Delay transmission due to AggregatedTimeOff or to a band time off
            *time = nextTxDelay;
            return true;
        }
        // Datarate not supported by any channel
        *time = 0;
        return false;
    }
}

LoRaMacStatus_t RegionUS915ChannelAdd( ChannelAddParams_t* channelAdd )
{
    return LORAMAC_STATUS_PARAMETER_INVALID;
}

bool RegionUS915ChannelsRemove( ChannelRemoveParams_t* channelRemove  )
{
    return LORAMAC_STATUS_PARAMETER_INVALID;
}

void RegionUS915SetContinuousWave( ContinuousWaveParams_t* continuousWave )
{
    int8_t phyTxPower = LimitTxPower( continuousWave->TxPower, continuousWave->Datarate, ChannelsMask );
    uint32_t frequency = Channels[continuousWave->Channel].Frequency;

    Radio.SetTxContinuousWave( frequency, phyTxPower, continuousWave->Timeout );
}
