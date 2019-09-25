/*
 * config.h
 *
 *  Created on: 27 ago. 2019
 *      Author: Larraitz
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

#define RCC_GPIO_CLK_ENABLE( __GPIO_PORT__ )              \
do {                                                    \
    switch( __GPIO_PORT__)                                \
    {                                                     \
      case GPIOA_BASE: __HAL_RCC_GPIOA_CLK_ENABLE(); break;    \
      case GPIOB_BASE: __HAL_RCC_GPIOB_CLK_ENABLE(); break;    \
      case GPIOC_BASE: __HAL_RCC_GPIOC_CLK_ENABLE(); break;    \
      case GPIOD_BASE: __HAL_RCC_GPIOD_CLK_ENABLE(); break;    \
      case GPIOH_BASE: default:  __HAL_RCC_GPIOH_CLK_ENABLE(); \
    }                                                    \
  } while(0)

#define RCC_GPIO_CLK_DISABLE( __GPIO_PORT__ )              \
do {                                                    \
    switch( __GPIO_PORT__)                                \
    {                                                     \
      case GPIOA_BASE: __HAL_RCC_GPIOA_CLK_DISABLE(); break;    \
      case GPIOB_BASE: __HAL_RCC_GPIOB_CLK_DISABLE(); break;    \
      case GPIOC_BASE: __HAL_RCC_GPIOC_CLK_DISABLE(); break;    \
      case GPIOD_BASE: __HAL_RCC_GPIOD_CLK_DISABLE(); break;    \
      case GPIOH_BASE: default:  __HAL_RCC_GPIOH_CLK_ENABLE(); \
    }                                                    \
  } while(0)

//#define RADIO_DIO_4
//#define RADIO_DIO_5

/* LORA I/O definition */

#define RADIO_RESET_PORT                          GPIOC
#define RADIO_RESET_PIN                           GPIO_PIN_0

#define RADIO_MOSI_PORT                           GPIOA
#define RADIO_MOSI_PIN                            GPIO_PIN_7

#define RADIO_MISO_PORT                           GPIOA
#define RADIO_MISO_PIN                            GPIO_PIN_6

#define RADIO_SCLK_PORT                           GPIOB
#define RADIO_SCLK_PIN                            GPIO_PIN_3

#define RADIO_NSS_PORT                            GPIOA
#define RADIO_NSS_PIN                             GPIO_PIN_15

#define RADIO_DIO_0_PORT                          GPIOB
#define RADIO_DIO_0_PIN                           GPIO_PIN_4

#define RADIO_DIO_1_PORT                          GPIOB
#define RADIO_DIO_1_PIN                           GPIO_PIN_1

#define RADIO_DIO_2_PORT                          GPIOB
#define RADIO_DIO_2_PIN                           GPIO_PIN_0

#define RADIO_DIO_3_PORT                          GPIOC
#define RADIO_DIO_3_PIN                           GPIO_PIN_13

#ifdef RADIO_DIO_4
#define RADIO_DIO_4_PORT                          GPIOA
#define RADIO_DIO_4_PIN                           GPIO_PIN_5
#endif

#ifdef RADIO_DIO_5
#define RADIO_DIO_5_PORT                          GPIOA
#define RADIO_DIO_5_PIN                           GPIO_PIN_4
#endif

#define RADIO_TCXO_VCC_PORT                       GPIOA
#define RADIO_TCXO_VCC_PIN                        GPIO_PIN_12

#define RADIO_ANT_SWITCH_PORT_RX                  GPIOA //CRF1
#define RADIO_ANT_SWITCH_PIN_RX                   GPIO_PIN_1

#define RADIO_ANT_SWITCH_PORT_TX_BOOST            GPIOC //CRF3
#define RADIO_ANT_SWITCH_PIN_TX_BOOST             GPIO_PIN_1

#define RADIO_ANT_SWITCH_PORT_TX_RFO              GPIOC //CRF2
#define RADIO_ANT_SWITCH_PIN_TX_RFO               GPIO_PIN_2

/*  SPI MACRO redefinition */

#define SPI_CLK_ENABLE()                __HAL_RCC_SPI1_CLK_ENABLE()

#define SPI1_AF                          GPIO_AF0_SPI1

/* ADC MACRO redefinition */

#define BAT_LEVEL_PORT  GPIOA //CRF2
#define BAT_LEVEL_PIN  GPIO_PIN_4
#define ADC_READ_CHANNEL                 ADC_CHANNEL_4
#define ADCCLK_ENABLE()                 __HAL_RCC_ADC1_CLK_ENABLE() ;
#define ADCCLK_DISABLE()                __HAL_RCC_ADC1_CLK_DISABLE() ;



/* --------------------------- RTC HW definition -------------------------------- */

#define RTC_OUTPUT       DBG_RTC_OUTPUT

#define RTC_Alarm_IRQn              RTC_IRQn
/* --------------------------- USART HW definition -------------------------------*/


#define USARTX                           USART2
#define USARTX_CLK_ENABLE()              __USART2_CLK_ENABLE();
#define USARTX_RX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()
#define USARTX_TX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()

#define USARTX_FORCE_RESET()             __USART2_FORCE_RESET()
#define USARTX_RELEASE_RESET()           __USART2_RELEASE_RESET()


#define USARTX_TX_PIN                  GPIO_PIN_2
#define USARTX_TX_GPIO_PORT            GPIOA
#define USARTX_TX_AF                   GPIO_AF7_USART2
#define USARTX_RX_PIN                  GPIO_PIN_3
#define USARTX_RX_GPIO_PORT            GPIOA
#define USARTX_RX_AF                   GPIO_AF7_USART2

/* Definition for USARTx's NVIC */
#define USARTX_IRQn                      USART2_IRQn
#define USARTX_IRQHandler                USART2_IRQHandler

#define LED_Toggle( x )                 BSP_LED_Toggle( x );
#define LED_On( x )                     BSP_LED_On( x );
#define LED_Off( x )                    BSP_LED_Off( x );

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_H_ */
