    /*!
 * \file      lora_init.c
 *
 * \brief     Target board SX1272 driver implementation
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \code
 *                ______                              _
 *               / _____)             _              | |
 *              ( (____  _____ ____ _| |_ _____  ____| |__
 *               \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *               _____) ) ____| | | || |_| ____( (___| | | |
 *              (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *              (C)2013-2017 Semtech
 *
 * \endcode
 *
 * \author    Miguel Luis ( Semtech )
 *
 * \author    Gregory Cristian ( Semtech )
 */
  
/* Includes ------------------------------------------------------------------*/

//#include "hw.h"
#include "radio.h"
#include "sx1272.h"
#include "lora_init.h"
#include "delay.h"
#include "timeServer.h"
#include "includes.h"
#include "gpio.h"

//#define IRQ_HIGH_PRIORITY  0
//
///* Delay in ms between radio set in sleep mode and TCXO off*/
//#define TCXO_OFF_DELAY 2
///*!
// * callback to stop TCXO on timer timeout
// */
//static TimerEvent_t TcxoStopTimer;
//
//static void OnTcxoStopTimerEvent( void );

/*!
 * Flag used to set the RF switch control pins in low power mode when the radio is not active.
 */
static bool RadioIsActive = false;

//static void SX1272AntSwInit( void );
//
//static void SX1272AntSwDeInit( void );

/*!
 * Radio driver structure initialization
 */
const struct Radio_s Radio =
{
	SX1272Init,
	SX1272GetStatus,
	SX1272SetModem,
	SX1272SetChannel,
	SX1272IsChannelFree,
	SX1272Random,
	SX1272SetRxConfig,
	SX1272SetTxConfig,
	SX1272CheckRfFrequency,
	SX1272GetTimeOnAir,
	SX1272Send,
	SX1272SetSleep,
	SX1272SetStby,
	SX1272SetRx,
	SX1272StartCad,
	SX1272SetTxContinuousWave,
	SX1272ReadRssi,
	SX1272Write,
	SX1272Read,
	SX1272WriteBuffer,
	SX1272ReadBuffer,
	SX1272SetMaxPayloadLength,
	SX1272SetPublicNetwork,
	SX1272GetWakeupTime
};


void SX1272IoInit( void )
{
  GPIO_InitTypeDef initStruct={0};
  
  initStruct.Mode =GPIO_MODE_IT_RISING;
  initStruct.Pull = GPIO_PULLUP;
  initStruct.Speed = GPIO_SPEED_HIGH;

  GPIO_Init( RADIO_DIO_0_PORT, RADIO_DIO_0_PIN, &initStruct );
  GPIO_Init( RADIO_DIO_1_PORT, RADIO_DIO_1_PIN, &initStruct );
  GPIO_Init( RADIO_DIO_2_PORT, RADIO_DIO_2_PIN, &initStruct );
  GPIO_Init( RADIO_DIO_3_PORT, RADIO_DIO_3_PIN, &initStruct );
//  HW_GPIO_Init( RADIO_DIO_4_PORT, RADIO_DIO_4_PIN, &initStruct );
//  HW_GPIO_Init( RADIO_DIO_5_PORT, RADIO_DIO_5_PIN, &initStruct );
  
  initStruct.Mode = GPIO_MODE_OUTPUT_PP;
  initStruct.Pull = GPIO_NOPULL;  
  GPIO_Init( RADIO_TCXO_VCC_PORT, RADIO_TCXO_VCC_PIN, &initStruct );
}

void SX1272IoIrqInit( DioIrqHandler **irqHandlers )
{
  GPIO_SetIrq( RADIO_DIO_0_PORT, RADIO_DIO_0_PIN, IRQ_HIGH_PRIORITY, irqHandlers[0] );
  GPIO_SetIrq( RADIO_DIO_1_PORT, RADIO_DIO_1_PIN, IRQ_HIGH_PRIORITY, irqHandlers[1] );
  GPIO_SetIrq( RADIO_DIO_2_PORT, RADIO_DIO_2_PIN, IRQ_HIGH_PRIORITY, irqHandlers[2] );
  GPIO_SetIrq( RADIO_DIO_3_PORT, RADIO_DIO_3_PIN, IRQ_HIGH_PRIORITY, irqHandlers[3] );
//  HW_GPIO_SetIrq( RADIO_DIO_4_PORT, RADIO_DIO_4_PIN, IRQ_HIGH_PRIORITY, irqHandlers[4] );
//  HW_GPIO_SetIrq( RADIO_DIO_5_PORT, RADIO_DIO_5_PIN, IRQ_HIGH_PRIORITY, irqHandlers[5] );
}


void SX1272IoDeInit( void )
{
  GPIO_InitTypeDef initStruct={0};

  initStruct.Mode = GPIO_MODE_IT_RISING ; //GPIO_MODE_ANALOG;
  initStruct.Pull = GPIO_PULLDOWN;
  
  GPIO_Init( RADIO_DIO_0_PORT, RADIO_DIO_0_PIN, &initStruct );
  GPIO_Init( RADIO_DIO_1_PORT, RADIO_DIO_1_PIN, &initStruct );
  GPIO_Init( RADIO_DIO_2_PORT, RADIO_DIO_2_PIN, &initStruct );
  GPIO_Init( RADIO_DIO_3_PORT, RADIO_DIO_3_PIN, &initStruct );
//  HW_GPIO_Init( RADIO_DIO_4_PORT, RADIO_DIO_4_PIN, &initStruct );
//  HW_GPIO_Init( RADIO_DIO_5_PORT, RADIO_DIO_5_PIN, &initStruct );
}

void SX1272SetRfTxPower( int8_t power )
{
    uint8_t paConfig = 0;
    uint8_t paDac = 0;

    paConfig = SX1272Read( REG_PACONFIG );
      paDac = SX1272Read( REG_PADAC );

      paConfig = ( paConfig & RF_PACONFIG_PASELECT_MASK ) | SX1272GetPaSelect( SX1272.Settings.Channel );

      if( ( paConfig & RF_PACONFIG_PASELECT_PABOOST ) == RF_PACONFIG_PASELECT_PABOOST )
      {
          if( power > 17 )
          {
              paDac = ( paDac & RF_PADAC_20DBM_MASK ) | RF_PADAC_20DBM_ON;
          }
          else
          {
              paDac = ( paDac & RF_PADAC_20DBM_MASK ) | RF_PADAC_20DBM_OFF;
          }
          if( ( paDac & RF_PADAC_20DBM_ON ) == RF_PADAC_20DBM_ON )
          {
              if( power < 5 )
              {
                  power = 5;
              }
              if( power > 20 )
              {
                  power = 20;
              }
              paConfig = ( paConfig & RFLR_PACONFIG_OUTPUTPOWER_MASK ) | ( uint8_t )( ( uint16_t )( power - 5 ) & 0x0F );
          }
          else
          {
              if( power < 2 )
              {
                  power = 2;
              }
              if( power > 17 )
              {
                  power = 17;
              }
              paConfig = ( paConfig & RFLR_PACONFIG_OUTPUTPOWER_MASK ) | ( uint8_t )( ( uint16_t )( power - 2 ) & 0x0F );
          }
      }
      else
      {
          if( power < -1 )
          {
              power = -1;
          }
          if( power > 14 )
          {
              power = 14;
          }
          paConfig = ( paConfig & RFLR_PACONFIG_OUTPUTPOWER_MASK ) | ( uint8_t )( ( uint16_t )( power + 1 ) & 0x0F );
      }
      SX1272Write( REG_PACONFIG, paConfig );
      SX1272Write( REG_PADAC, paDac );
}

uint8_t SX1272GetPaSelect( uint32_t channel )
{
    return RF_PACONFIG_PASELECT_PABOOST;
}



//void SX1272SetAntSwLowPower( bool status )
//{
//  if( RadioIsActive != status )
//  {
//    RadioIsActive = status;
//
//    if( status == false )
//    {
//      TimerStop( &TcxoStopTimer );
//
//      MLM_TCXO_ON();  //TCXO ON
//
//      DelayMs( BOARD_WAKEUP_TIME ); //start up time of TCXO
//
//      SX1272AntSwInit( );
//    }
//    else
//    {
//      SX1272AntSwDeInit( );
//
//      TimerInit( &TcxoStopTimer, OnTcxoStopTimerEvent );
//
//      TimerSetValue( &TcxoStopTimer, TCXO_OFF_DELAY);
//
//      TimerStart( &TcxoStopTimer );
//    }
//  }
//}

//static void SX1272AntSwInit( void )
//{
//  GPIO_InitTypeDef initStruct={0};
//
//  initStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  initStruct.Pull = GPIO_PULLUP; //GPIO_NOPULL;
//  initStruct.Speed = GPIO_SPEED_HIGH;
//
//  HW_GPIO_Init( RADIO_ANT_SWITCH_PORT_RX, RADIO_ANT_SWITCH_PIN_RX, &initStruct  );
//  HW_GPIO_Write( RADIO_ANT_SWITCH_PORT_RX, RADIO_ANT_SWITCH_PIN_RX, 0);
//
//  HW_GPIO_Init( RADIO_ANT_SWITCH_PORT_TX_BOOST, RADIO_ANT_SWITCH_PIN_TX_BOOST, &initStruct  );
//  HW_GPIO_Write( RADIO_ANT_SWITCH_PORT_TX_BOOST, RADIO_ANT_SWITCH_PIN_TX_BOOST, 0);
//
//  HW_GPIO_Init( RADIO_ANT_SWITCH_PORT_TX_RFO, RADIO_ANT_SWITCH_PIN_TX_RFO, &initStruct  );
//  HW_GPIO_Write( RADIO_ANT_SWITCH_PORT_TX_RFO, RADIO_ANT_SWITCH_PIN_TX_RFO, 0);
//}
//
//static void SX1272AntSwDeInit( void )
//{
//  GPIO_InitTypeDef initStruct={0};
//
//  initStruct.Mode = GPIO_MODE_ANALOG ;
//
//  initStruct.Pull = GPIO_NOPULL;
//  initStruct.Speed = GPIO_SPEED_HIGH;
//
//  HW_GPIO_Init( RADIO_ANT_SWITCH_PORT_RX, RADIO_ANT_SWITCH_PIN_RX, &initStruct  );
//  HW_GPIO_Write( RADIO_ANT_SWITCH_PORT_RX, RADIO_ANT_SWITCH_PIN_RX, 0);
//
//  HW_GPIO_Init( RADIO_ANT_SWITCH_PORT_TX_BOOST, RADIO_ANT_SWITCH_PIN_TX_BOOST, &initStruct  );
//  HW_GPIO_Write( RADIO_ANT_SWITCH_PORT_TX_BOOST, RADIO_ANT_SWITCH_PIN_TX_BOOST, 0);
//
//  HW_GPIO_Init( RADIO_ANT_SWITCH_PORT_TX_RFO, RADIO_ANT_SWITCH_PIN_TX_RFO, &initStruct  );
//  HW_GPIO_Write( RADIO_ANT_SWITCH_PORT_TX_RFO, RADIO_ANT_SWITCH_PIN_TX_RFO, 0);
//}

void SX1272SetAntSw( uint8_t opMode )
{
 uint8_t paConfig =  SX1272Read( REG_PACONFIG );
      switch( opMode )
    {
    case RFLR_OPMODE_TRANSMITTER:
      if( ( paConfig & RF_PACONFIG_PASELECT_PABOOST ) == RF_PACONFIG_PASELECT_PABOOST )
      {
        GPIO_Write( RADIO_ANT_SWITCH_PORT_TX_BOOST, RADIO_ANT_SWITCH_PIN_TX_BOOST, 1 );
      }
      else
      {
        GPIO_Write( RADIO_ANT_SWITCH_PORT_TX_RFO, RADIO_ANT_SWITCH_PIN_TX_RFO, 1 );
      }
      //SX1272.RxTx = 1;
	  break;
    case RFLR_OPMODE_RECEIVER:
    case RFLR_OPMODE_RECEIVER_SINGLE:
    case RFLR_OPMODE_CAD:
    default:
    	SX1272.RxTx = 0;
        GPIO_Write( RADIO_ANT_SWITCH_PORT_RX, RADIO_ANT_SWITCH_PIN_RX, 1 );
        break;
    }
  
}

bool SX1272CheckRfFrequency( uint32_t frequency )
{
    // Implement check. Currently all frequencies are supported
    return true;
}
