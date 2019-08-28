/*
 * uart.h
 *
 *  Created on: 28 ago. 2019
 *      Author: Larraitz
 */

#ifndef __UART_H__
#define __UART_H__


#define GPIOA_CLK_ENABLE()				__HAL_RCC_GPIOA_CLK_ENABLE()
#define GPIOA_CLK_DISABLE()				__HAL_RCC_GPIOA_CLK_DISABLE()

#define GPIOC_CLK_ENABLE()				__HAL_RCC_GPIOC_CLK_ENABLE()
#define GPIOC_CLK_DISABLE()				__HAL_RCC_GPIOC_CLK_DISABLE()

#define USART6_CLK_ENABLE()				__USART6_CLK_ENABLE();
#define USART2_CLK_ENABLE()				__USART6_CLK_ENABLE();


void UART_Config(void);
void UART_DeInit(UART_HandleTypeDef* huart);
void USART2_UART_Init(void);

#endif // __UART_H__
