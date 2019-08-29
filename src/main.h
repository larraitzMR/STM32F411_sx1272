/*
 * main.h
 *
 *  Created on: 28 ago. 2019
 *      Author: Propietario
 */

#ifndef MAIN_H_
#define MAIN_H_

/* LORA I/O definition */


#define RADIO_MOSI_PORT                           GPIOA
#define RADIO_MOSI_PIN                            GPIO_PIN_7

#define RADIO_MISO_PORT                           GPIOA
#define RADIO_MISO_PIN                            GPIO_PIN_6

#define RADIO_SCLK_PORT                           GPIOA
#define RADIO_SCLK_PIN                            GPIO_PIN_5

#define RADIO_NSS_PORT                            GPIOA
#define RADIO_NSS_PIN                             GPIO_PIN_4

#define RADIO_DIO_0_PORT                          GPIOA
#define RADIO_DIO_0_PIN                           GPIO_PIN_1

#define RADIO_DIO_1_PORT                          GPIOA
#define RADIO_DIO_1_PIN                           GPIO_PIN_0


#endif /* MAIN_H_ */
