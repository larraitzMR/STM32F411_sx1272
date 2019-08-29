/*
 * stm32f4xx_hw.c
 *
 *  Created on: 29 ago. 2019
 *      Author: Propietario
 */


#include "radio.h"
#include "vcom.h"

/*!
 *  \brief Unique Devices IDs register set ( STM32L0xxx )
 */
#define         ID1                                 ( 0x1FF80050 )
#define         ID2                                 ( 0x1FF80054 )
#define         ID3                                 ( 0x1FF80064 )

/*!
 * \brief ADC Vbat measurement constants
 */

 /* Internal voltage reference, parameter VREFINT_CAL*/
#define VREFINT_CAL       ((uint16_t*) ((uint32_t) 0x1FF80078))
#define LORAWAN_MAX_BAT   254

//static ADC_HandleTypeDef hadc;
///*!
// * Flag to indicate if the ADC is Initialized
// */
//static bool AdcInitialized = false;
//
///*!
// * Flag to indicate if the MCU is Initialized
// */
//static bool McuInitialized = false;

/**
  * @brief This function initializes the hardware
  * @param None
  * @retval None
  */
void HW_Init( void )
{
//  if( McuInitialized == false )
//  {
//#if defined( USE_BOOTLOADER )
//    /* Set the Vector Table base location at 0x3000 */
//    NVIC_SetVectorTable( NVIC_VectTab_FLASH, 0x3000 );
//#endif
//
//    HW_AdcInit( );
//
//    Radio.IoInit( );
//
////    HW_SPI_Init( );
//
//    HW_RTC_Init( );
//
//    vcom_Init( );
//
//    McuInitialized = true;
//  }
}

/**
  * @brief This function Deinitializes the hardware
  * @param None
  * @retval None
  */
void HW_DeInit( void )
{
//  HW_SPI_DeInit( );
//
//  Radio.IoDeInit( );
//
//  vcom_DeInit( );
//
//  McuInitialized = false;
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 32000000
  *            HCLK(Hz)                       = 32000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  *            PLLMUL                         = 6
  *            PLLDIV                         = 3
  *            Flash Latency(WS)              = 1
  * @retval None
  */

//void SystemClock_Config( void )
//{
//  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
//  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//
//  /* Enable HSE Oscillator and Activate PLL with HSE as source */
//  RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
//  RCC_OscInitStruct.HSEState            = RCC_HSE_OFF;
//  RCC_OscInitStruct.HSIState            = RCC_HSI_ON;
//  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
//  RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
//  RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSI;
//  RCC_OscInitStruct.PLL.PLLMUL          = RCC_PLLMUL_6;
//  RCC_OscInitStruct.PLL.PLLDIV          = RCC_PLLDIV_3;
//
//  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /* Set Voltage scale1 as MCU will run at 32MHz */
//  __HAL_RCC_PWR_CLK_ENABLE();
//  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
//
//  /* Poll VOSF bit of in PWR_CSR. Wait until it is reset to 0 */
//  while (__HAL_PWR_GET_FLAG(PWR_FLAG_VOS) != RESET) {};
//
//  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
//  clocks dividers */
//  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
//  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
//  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
//  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
//  {
//    Error_Handler();
//  }
//}
/**
  * @brief This function return a random seed
  * @note based on the device unique ID
  * @param None
  * @retval see
  */
uint32_t HW_GetRandomSeed( void )
{
  return ( ( *( uint32_t* )ID1 ) ^ ( *( uint32_t* )ID2 ) ^ ( *( uint32_t* )ID3 ) );
}

/**
  * @brief This function return a unique ID
  * @param unique ID
  * @retval none
  */
void HW_GetUniqueId( uint8_t *id )
{
    id[7] = ( ( *( uint32_t* )ID1 )+ ( *( uint32_t* )ID3 ) ) >> 24;
    id[6] = ( ( *( uint32_t* )ID1 )+ ( *( uint32_t* )ID3 ) ) >> 16;
    id[5] = ( ( *( uint32_t* )ID1 )+ ( *( uint32_t* )ID3 ) ) >> 8;
    id[4] = ( ( *( uint32_t* )ID1 )+ ( *( uint32_t* )ID3 ) );
    id[3] = ( ( *( uint32_t* )ID2 ) ) >> 24;
    id[2] = ( ( *( uint32_t* )ID2 ) ) >> 16;
    id[1] = ( ( *( uint32_t* )ID2 ) ) >> 8;
    id[0] = ( ( *( uint32_t* )ID2 ) );
}

/**
  * @brief This function return the battery level
  * @param none
  * @retval the battery level  1 (very low) to 254 (fully charged)
  */
uint8_t HW_GetBatteryLevel( void )
{
//  uint8_t batteryLevel = 0;
//  uint16_t measuredLevel = 0;
//  uint32_t batteryLevelmV;
//
//  measuredLevel = HW_AdcReadChannel( ADC_CHANNEL_VREFINT );
//
//  if (measuredLevel == 0)
//  {
//    batteryLevelmV = 0;
//  }
//  else
//  {
//    batteryLevelmV= (( (uint32_t) VDDA_TEMP_CAL * (*VREFINT_CAL ) )/ measuredLevel);
//  }
//
//  if (batteryLevelmV > VDD_BAT)
//  {
//    batteryLevel = LORAWAN_MAX_BAT;
//  }
//  else if (batteryLevelmV < VDD_MIN)
//  {
//    batteryLevel = 0;
//  }
//  else
//  {
//    batteryLevel = (( (uint32_t) (batteryLevelmV - VDD_MIN)*LORAWAN_MAX_BAT) /(VDD_BAT-VDD_MIN) );
//  }
//  return batteryLevel;
}

/**
  * @brief This function initializes the ADC
  * @param none
  * @retval none
  */
void HW_AdcInit( void )
{
//  if( AdcInitialized == false )
//  {
//    AdcInitialized = true;
//    GPIO_InitTypeDef initStruct;
//
//    hadc.Instance  = ADC1;
//
//    hadc.Init.OversamplingMode      = DISABLE;
//
//    hadc.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV1;
//    hadc.Init.LowPowerAutoPowerOff  = DISABLE;
//    hadc.Init.LowPowerFrequencyMode = ENABLE;
//    hadc.Init.LowPowerAutoWait      = DISABLE;
//
//    hadc.Init.Resolution            = ADC_RESOLUTION_12B;
//    hadc.Init.SamplingTime          = ADC_SAMPLETIME_7CYCLES_5;
//    hadc.Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD;
//    hadc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
//    hadc.Init.ContinuousConvMode    = DISABLE;
//    hadc.Init.DiscontinuousConvMode = DISABLE;
//    hadc.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
//    hadc.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
//    hadc.Init.DMAContinuousRequests = DISABLE;
//
//    ADCCLK_ENABLE();
//
//
//    HAL_ADC_Init( &hadc );
//
//    initStruct.Mode =GPIO_MODE_ANALOG;
//    initStruct.Pull = GPIO_NOPULL;
//    initStruct.Speed = GPIO_SPEED_HIGH;
//
//    HW_GPIO_Init( BAT_LEVEL_PORT, BAT_LEVEL_PIN, &initStruct );
//  }
}
/**
  * @brief This function De-initializes the ADC
  * @param none
  * @retval none
  */
void HW_AdcDeInit( void )
{
//  AdcInitialized = false;
}

/**
  * @brief This function De-initializes the ADC
  * @param Channel
  * @retval Value
  */
uint16_t HW_AdcReadChannel( uint32_t Channel )
{

//  ADC_ChannelConfTypeDef adcConf;
//  uint16_t adcData = 0;
//
//  if( AdcInitialized == true )
//  {
//    /* wait the the Vrefint used by adc is set */
//    while (__HAL_PWR_GET_FLAG(PWR_FLAG_VREFINTRDY) == RESET) {};
//
//    ADCCLK_ENABLE();
//
//    /*calibrate ADC if any calibraiton hardware*/
//    HAL_ADCEx_Calibration_Start(&hadc, ADC_SINGLE_ENDED );
//
//    /* Deselects all channels*/
//    adcConf.Channel = ADC_CHANNEL_MASK;
//    adcConf.Rank = ADC_RANK_NONE;
//    HAL_ADC_ConfigChannel( &hadc, &adcConf);
//
//    /* configure adc channel */
//    adcConf.Channel = Channel;
//    adcConf.Rank = ADC_RANK_CHANNEL_NUMBER;
//    HAL_ADC_ConfigChannel( &hadc, &adcConf);
//
//    /* Start the conversion process */
//    HAL_ADC_Start( &hadc);
//
//    /* Wait for the end of conversion */
//    HAL_ADC_PollForConversion( &hadc, HAL_MAX_DELAY );
//
//    /* Get the converted value of regular channel */
//    adcData = HAL_ADC_GetValue ( &hadc);
//
//    __HAL_ADC_DISABLE( &hadc) ;
//
//    ADCCLK_DISABLE();
//  }
//  return adcData;
}

/**
  * @brief Enters Low Power Stop Mode
  * @note ARM exists the function when waking up
  * @param none
  * @retval none
  */
void HW_EnterStopMode( void)
{
//  BACKUP_PRIMASK();
//
//  DISABLE_IRQ( );
//
//  HW_DeInit( );
//
//  /*clear wake up flag*/
//  SET_BIT(PWR->CR, PWR_CR_CWUF);
//
//  RESTORE_PRIMASK( );
//
//  /* Enter Stop Mode */
//  HAL_PWR_EnterSTOPMode ( PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI );
}
/**
  * @brief Exists Low Power Stop Mode
  * @note Enable the pll at 32MHz
  * @param none
  * @retval none
  */
void HW_ExitStopMode( void)
{
//  /* Disable IRQ while the MCU is not running on HSI */
//
//  BACKUP_PRIMASK();
//
//  DISABLE_IRQ( );
//
//  /* After wake-up from STOP reconfigure the system clock */
//  /* Enable HSI */
//  __HAL_RCC_HSI_ENABLE();
//
//  /* Wait till HSI is ready */
//  while( __HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) == RESET ) {}
//
//  /* Enable PLL */
//  __HAL_RCC_PLL_ENABLE();
//  /* Wait till PLL is ready */
//  while( __HAL_RCC_GET_FLAG( RCC_FLAG_PLLRDY ) == RESET ) {}
//
//  /* Select PLL as system clock source */
//  __HAL_RCC_SYSCLK_CONFIG ( RCC_SYSCLKSOURCE_PLLCLK );
//
//  /* Wait till PLL is used as system clock source */
//  while( __HAL_RCC_GET_SYSCLK_SOURCE( ) != RCC_SYSCLKSOURCE_STATUS_PLLCLK ) {}
//
//  /*initilizes the peripherals*/
//  HW_Init( );
//
//  RESTORE_PRIMASK( );
}

/**
  * @brief Enters Low Power Sleep Mode
  * @note ARM exits the function when waking up
  * @param none
  * @retval none
  */
void HW_EnterSleepMode( void)
{
//    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

