/*
 * peripherals.h
 *
 *  Created on: Nov 16, 2025
 *      Author: vaishakh
 */

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include <stdint.h>

#define RCC_BASE       0x40021000UL     // RCC registers base address
#define FLASH_BASE     0x40022000UL     // Flash memory interface base
#define GPIOB_BASE     0x40010C00UL     // GPIO port B base

#define RCC_CR         (*(volatile uint32_t *)(RCC_BASE + 0x00))  // RCC clock control
#define RCC_CFGR       (*(volatile uint32_t *)(RCC_BASE + 0x04))  // RCC clock configuration
#define RCC_APB2ENR    (*(volatile uint32_t *)(RCC_BASE + 0x18))  // APB2 peripheral clock enable
#define RCC_APB1ENR    (*(volatile uint32_t *)(RCC_BASE + 0x1C))  // APB1 peripheral clock enable

#define FLASH_ACR      (*(volatile uint32_t *)(FLASH_BASE + 0x00)) // Flash access control

#define GPIOB_CRL      (*(volatile uint32_t *)(GPIOB_BASE + 0x00)) // GPIOB low control (pins 0-7)
#define GPIOB_CRH      (*(volatile uint32_t *)(GPIOB_BASE + 0x04)) // GPIOB high control (pins 8-15)
#define GPIOB_BSRR     (*(volatile uint32_t *)(GPIOB_BASE + 0x10)) // GPIOB bit set/reset register

#define TIM2_BASE      0x40000000UL     // Timer 2 base address
#define TIM2_PSC       (*(volatile uint32_t *)(TIM2_BASE + 0x28)) // TIM2 prescaler
#define TIM2_ARR       (*(volatile uint32_t *)(TIM2_BASE + 0x2C)) // TIM2 auto reload
#define TIM2_CR1       (*(volatile uint32_t *)(TIM2_BASE + 0x00)) // TIM2 control reg 1
#define TIM2_CNT       (*(volatile uint32_t *)(TIM2_BASE + 0x24)) // TIM2 counter
#define TIM2_EGR       (*(volatile uint32_t *)(TIM2_BASE + 0x14)) // TIM2 event generation

#define TIM4_BASE      0x40000800UL     // Timer 4 base address
#define TIM4_CR1       (*(volatile uint32_t *)(TIM4_BASE + 0x00)) // TIM4 control reg 1
#define TIM4_CNT       (*(volatile uint32_t *)(TIM4_BASE + 0x24)) // TIM4 counter
#define TIM4_PSC       (*(volatile uint32_t *)(TIM4_BASE + 0x28)) // TIM4 prescaler
#define TIM4_ARR       (*(volatile uint32_t *)(TIM4_BASE + 0x2C)) // TIM4 auto reload
#define TIM4_EGR       (*(volatile uint32_t *)(TIM4_BASE + 0x14)) // TIM4 event generation
#define TIM4_CCR1      (*(volatile uint32_t *)(TIM4_BASE + 0x34)) // TIM4 capture/compare reg 1
#define TIM4_CCMR1     (*(volatile uint32_t *)(TIM4_BASE + 0x18)) // TIM4 capture/compare mode reg 1
#define TIM4_CCER      (*(volatile uint32_t *)(TIM4_BASE + 0x20)) // TIM4 capture/compare enable reg

#define AFIO_BASE      0x40000100UL     // Alternate function I/O base
#define AFIO_EXTICR1   (*(volatile uint32_t *)(AFIO_BASE + 0x08))


#define EXTI_BASE      0x40010400UL     // EXTI controller base
#define EXTI_IMR       (*(volatile uint32_t *)(EXTI_BASE + 0x00)) // Interrupt mask register
#define EXTI_RTSR      (*(volatile uint32_t *)(EXTI_BASE + 0x08)) // Rising trigger selection register
#define EXTI_FTSR      (*(volatile uint32_t *)(EXTI_BASE + 0x0C)) // Falling trigger selection register
#define EXTI_PR        (*(volatile uint32_t *)(EXTI_BASE + 0x14)) // Pending register

#define NVIC_ISER      ((volatile uint32_t *)0xE000E100)          // NVIC interrupt set-enable registers (32 IRQs/unit)
#define NVIC_IPR       ((volatile uint8_t  *)0xE000E400)          // NVIC interrupt priority registers (8-bit each)

#define EXTI3_IRQn     9                                          // IRQ number for EXTI line 3


#endif /* PERIPHERALS_H_ */
