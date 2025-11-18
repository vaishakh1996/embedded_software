/*
 * peripherals.h
 *
 *  Created on: Nov 16, 2025
 *      Author: vaishakh
 */

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include <stdint.h>

#define RCC_BASE       0x40021000UL
#define FLASH_BASE     0x40022000UL
#define GPIOA_BASE     0x40010800UL

#define RCC_CR         (*(volatile uint32_t *)(RCC_BASE + 0x00))
#define RCC_CFGR       (*(volatile uint32_t *)(RCC_BASE + 0x04))
#define RCC_APB2ENR    (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define RCC_APB1ENR (*((volatile uint32_t *)(RCC_BASE + 0x1C)))

#define FLASH_ACR      (*(volatile uint32_t *)(FLASH_BASE + 0x00))

#define GPIOA_CRL      (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_BSRR     (*(volatile uint32_t *)(GPIOA_BASE + 0x10))


#define TIM2_BASE 0x40000000U
#define TIM2_PSC (*((volatile uint32_t *)(TIM2_BASE + 0x28)))
#define TIM2_ARR (*((volatile uint32_t *)(TIM2_BASE + 0x2C)))
#define TIM2_CR1 (*((volatile uint32_t *)(TIM2_BASE + 0x00)))


#endif /* PERIPHERALS_H_ */
