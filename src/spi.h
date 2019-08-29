/*
 * spi.h
 *
 *  Created on: 28 ago. 2019
 *      Author: Larraitz
 */

/*!
 * SPI peripheral ID
 */

#include "gpio.h"
#include "includes.h"

typedef enum
{
    SPI_1,
    SPI_2,
}SpiId_t;


/*!
 * SPI object type definition
 */
typedef struct Spi_s
{
    SpiId_t SpiId;
    Gpio_t Mosi;
    Gpio_t Miso;
    Gpio_t Sclk;
    Gpio_t Nss;
}Spi_t;


#define DMAx_CLK_ENABLE()                __HAL_RCC_DMA2_CLK_ENABLE()

/* Definition for SPIx's DMA */
#define SPIx_TX_DMA_STREAM               DMA2_Stream3
#define SPIx_RX_DMA_STREAM               DMA2_Stream2
#define SPIx_TX_DMA_CHANNEL              DMA_CHANNEL_3
#define SPIx_RX_DMA_CHANNEL              DMA_CHANNEL_3


/* Definition for SPIx's NVIC */
#define SPIx_DMA_TX_IRQn                 DMA2_Stream3_IRQn
#define SPIx_DMA_RX_IRQn                 DMA2_Stream2_IRQn

void SPI_Init(SPI_HandleTypeDef* hspi);
void SPI_DeInit(SPI_HandleTypeDef* hspi);
void SPI1_Init(void);
void SPI2_Init(void);
void SPI4_Init(void);
