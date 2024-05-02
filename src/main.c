/**
 *@file main.c
 *@brief Register Level Programming Simple Blink Project
 *@include main.c
 **/

#include <stdint.h>
#include "peripherals.h"

#define MODER_BITS 2
#define PIN_PA5 5
#define PIN_PC13 13

/**
 * @brief Struct Pointer for RCC Peripherals assigned with fixed address specified in reference manual
 **/
RCC_t   * const RCC     = (RCC_t    *)  0x40023800; 
/**
 * @brief Struct Pointer for GPIOA Peripherals assigned with fixed address specified in reference manual
 **/
GPIOx_t * const GPIOA   = (GPIOx_t  *)  0x40020000;

/**
 * @brief Struct Pointer for GPIOC Peripherals assigned with fixed address specified in reference manual
 **/
GPIOx_t * const GPIOC   = (GPIOx_t  *)  0x40020800;


/**
 *@brief This is a simple delay function implementation, that waits for <time>ms.
 *
 *In this implementation the inner for loop, cycles for 1600 CLK Cycles which results in around 1ms delay, depending on the parameter <time>, the amount of ms delay can be adjusted.
 *
 *@param[in] time | number of ms the processor should wait
 **/
void wait_ms(int time){
    for(int i = 0; i < time; i++){
        for(int j = 0; j < 1600; j++);
    }
}

/**
 *@brief Main entry point for blinking project.
 *
 *GPIOA Peripherals are configured to OUTPUT, with LED connected to PA5 being toggled every 100ms
 **/
int main(void){

    //Enable Clock to GPIOA Peripheral
    RCC->RCC_AHB1ENR |= 0b001;

    // enable clock to GPIOC
    RCC->RCC_AHB1ENR |= 0b100;
    
    // Reset MODER Bitfield of PA5
    GPIOA->GPIOx_MODER &= ~(3 << (PIN_PA5 * MODER_BITS));
    // Write Value 1 to MODER Bitfield PA5 to configure PA5 as "General purpose output mode"
    GPIOA->GPIOx_MODER |=  (1 << (PIN_PA5 * MODER_BITS));
    
    // Reset MODER Bitfield of PC13, which is also setting it as input mode (see reference manual 8.4.1)
    GPIOC->GPIOx_MODER &= ~(3 << (PIN_PC13 * MODER_BITS));

    for(;;){
        /* der IDR13 ist fuer den input in PIN_PC13, wichtig: der button ist ein pull up resistor.
            wenn der button down ist, dann ist IDR13 auf 0, wenn der button released ist, dann ist es auf 1*/
        if (GPIOC->GPIOx_IDR & (1 << 13)) {
            // Button is released (because the button is active low)
           GPIOA->GPIOx_ODR &= ~(1 << PIN_PA5);
        } else {
            // Button is pressed
            // Toggle PA5
            GPIOA->GPIOx_ODR |= (1 << PIN_PA5);
        }
        
        
    }
}
