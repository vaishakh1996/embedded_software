/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Bare-metal STM32F1 main, sets system clock, timers, GPIO,
 *                   EXTI and PWM with interrupt.
 * @attention      :
 *   - NVIC vector table maps IRQ handlers by position, linking EXTI3 IRQ to EXTI3_IRQHandler().
 *   - NVIC interrupt priority registers are 8-bit; only upper 4 bits used.
 *   - Timer update event (UG) reloads ARR/PSC immediately, syncs registers.
 *   - EXTI configured for edge interrupts triggers NVIC IRQ.
 ******************************************************************************
 */

#include <stdint.h>
#include <peripherals.h>

volatile uint8_t pwm_duty = 0;  // Shared PWM duty cycle variable

// Function prototypes
void SYSCLK_init(void);
void Timer2_Init(void);
void GPIOB_Init(void);
void TIM4_PWM_Init(void);
void delay_ms(uint32_t ms);

int main(void) {
    SYSCLK_init();         // Set system clock to 32 MHz via PLL
    Timer2_Init();         // Initialize TIM2 for delay_ms timing
    GPIOB_Init();          // Setup GPIO pins PB3, PB6, PB7, PB8
    TIM4_PWM_Init();       // Setup TIM4 channel 1 as PWM output (PB6)



    while (1) {
        // Blink PB7 and PB8 alternately using bit set/reset registers
        GPIOB_BSRR = (1 << 7);
        delay_ms(1000);
        GPIOB_BSRR = (1 << (7 + 16));

        GPIOB_BSRR = (1 << 8);
        delay_ms(1000);
        GPIOB_BSRR = (1 << (8 + 16));

        delay_ms(1000);
    }
}

void SYSCLK_init(void) {
    RCC_CR |= (1 << 16);              // Enable HSE (8 MHz external clock)
    while (!(RCC_CR & (1 << 17))) {} // Wait for HSE ready
    FLASH_ACR |= (1 << 4);            // Enable prefetch buffer
    FLASH_ACR |= 1;                  // Set flash latency to 1WS for 32 MHz
    RCC_CFGR |= (1 << 16);           // Choose HSE as PLL source
    RCC_CFGR |= (0x2 << 18);         // PLL multiply by 4 => 32 MHz
    RCC_CR |= (1 << 24);             // Enable PLL
    while (!(RCC_CR & (1 << 25))) {} // Wait PLL ready
    RCC_CFGR |= 0x2;                 // Select PLL as system clock
    while ((RCC_CFGR & (0x3 << 2)) != (0x2 << 2)) {}  // Wait PLL used
}

void Timer2_Init(void) {
    RCC_APB1ENR |= (1 << 0);         // Enable TIM2 clock
    TIM2_PSC = 31999;                // Set prescaler; timer clk = 1 kHz
    TIM2_ARR = 0xFFFF;               // Max ARR value
    TIM2_CR1 |= 1;                  // Enable TIM2 counter
}

void GPIOB_Init(void) {
    RCC_APB2ENR |= (1 << 3);         // Enable GPIOB clock

    // PB7: output push-pull, 2 MHz
    GPIOB_CRL &= ~(0xF << (7 * 4));
    GPIOB_CRL |= (0x2 << (7 * 4));

    // PB8: output push-pull, 2 MHz
    GPIOB_CRH &= ~(0xF << (0 * 4));
    GPIOB_CRH |= (0x2 << (0 * 4));

    // Configure PB6 as Alternate function push-pull, 2 MHz
    GPIOB_CRL &= ~(0xF << (6 * 4));          // Clear bits for pin 6
    GPIOB_CRL |= (0xA << (6 * 4));           // MODE6=0b10 (2 MHz output), CNF6=0b10 (AF push-pull)

}

void TIM4_PWM_Init(void) {
    RCC_APB1ENR |= (1 << 2);         // Enable TIM4 clock
    TIM4_PSC = 31;                   // 1 MHz timer clock
    TIM4_ARR = 99;                   // PWM period 100 µs @ 1 MHz
    TIM4_CCR1 = 80;                  // Initial duty cycle 80%
    TIM4_CCMR1 &= ~(0x7 << 4);
    TIM4_CCMR1 |= (0x6 << 4);        // PWM mode 1
    TIM4_CCMR1 |= (1 << 3);          // Enable preload register for CCR1
    TIM4_CCER |= 1;                  // Enable channel 1 output (PB6)
    TIM4_CR1 |= (1 << 7) | 1;        // ARPE enabled, counter enabled
    TIM4_EGR |= 1;                   // Generate update event to load registers
}

void delay_ms(uint32_t ms) {
    TIM2_CR1 &= ~1;                  // Disable counter
    TIM2_CNT = 0;                   // Reset counter
    TIM2_EGR = 1;                   // Generate update event to load PSC and ARR
    TIM2_CR1 |= 1;                  // Enable counter
    while (TIM2_CNT < ms) {}        // Wait until count reached
    TIM2_CR1 &= ~1;                 // Disable counter (optional)
}

