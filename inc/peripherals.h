/**
 *@file peripherals.h
 *@brief Peripheral initialization using structs
 **/
#ifndef PERIPHERLAS_H
#define PERIPHERLAS_H
#include <stdint.h>
/* volatile wird oft benutzt vom fuer memory mapped io registers.
    damit sagen wir, dass der wert von der variable im laufe des runtimes veraendert wird,
    welches nicht von unserem code veraendert wird. (sondern von der hardware).
    somit sagen wir dem compiler, dass er diese werte nicht optimieren muss, 
    und immer nur wirklich den wert liest, der da ist.

    (bspw. eine variable die gelesen wird aber nie veraendert wird, 
    kann der compiler optimieren und einfach den wert speichern, 
    anstatt immer wieder zu lesen. mit volatile sagen wir, 
    dass der compiler das nicht machen soll, da der wert sich aendern kann.)
    */
#define __IO volatile 

/* siehe unten bei RCC fuer erklaerung der structs*/

typedef struct GPIOx_t{
	__IO uint32_t GPIOx_MODER; 		
	__IO uint32_t GPIOx_OTYPER;	
	__IO uint32_t GPIOx_OSPEEDER;	
	__IO uint32_t GPIOx_PUPDR;	
	__IO uint32_t GPIOx_IDR;
	__IO uint32_t GPIOx_ODR;	
	__IO uint32_t GPIOx_BSRR;	
	__IO uint32_t GPIOx_LCKR;
	__IO uint32_t GPIOx_AFRL;
	__IO uint32_t GPIOx_AFRH;
}GPIOx_t;

/*  da unser board nach reihenfolge io memory mapped ist und der RCC auf addr. 0x40023800 liegt, 
    erstellen wir eine Struktur, die vom Compiler dann in dieser Reihenfolge im Speicher automatisch mappt.
    jeder teil hier ist ein uint32_t register, d.h. alle 4 bytes lang.
    siehe dafuer in main.c, wie der rcc address definiert wurde. ab da wird die Struktur im Speicher gemappt.
*/

typedef struct RCC_t{
    __IO uint32_t RCC_CR;           // Address: 0x40023800
    __IO uint32_t RCC_PLLCFGT;      // Address: 0x40023804
    __IO uint32_t RCC_CFGR;         // Address: 0x40023808
    __IO uint32_t RCC_CIR;          // Address: 0x4002380C
    __IO uint32_t RCC_AHB1RSTR;     // Address: 0x40023810
    __IO uint32_t RCC_AHB2RSTR;     // Address: 0x40023814
    __IO uint32_t res1[2];          // Addresses: 0x40023818, 0x4002381C (diese sind reserviert und mit res[2] skippen wir bestimmte parts)
	__IO uint32_t RCC_APB1RSTR;
	__IO uint32_t RCC_APB2RSTR;
	__IO uint32_t res2[2];
	__IO uint32_t RCC_AHB1ENR;
	__IO uint32_t RCC_AHB2ENR;
	__IO uint32_t res3[2];
	__IO uint32_t RCC_APB1ENR;
	__IO uint32_t RCC_APB2ENR;
	__IO uint32_t res4[2];
	__IO uint32_t RCC_AHB1LPENR;
	__IO uint32_t RCC_AHB2LPENR;
	__IO uint32_t res5[2];
	__IO uint32_t RCC_APB1LPENR;
	__IO uint32_t RCC_APB2LPENR;
	__IO uint32_t res6[2];
	__IO uint32_t RCC_BDCR;
	__IO uint32_t RCC_CSR;
	__IO uint32_t res7[2];
	__IO uint32_t RCC_SSCGR;
	__IO uint32_t RCC_PLLI2SCFGR;
	__IO uint32_t res8;
	__IO uint32_t RCC_DCKCFGR;
}RCC_t;


typedef struct TIMx_t{
    __IO uint32_t TIMx_CR1;
    __IO uint32_t TIMx_CR2;
    __IO uint32_t TIMx_SMCR;
    __IO uint32_t TIMx_DIER;
    __IO uint32_t TIMx_SR;
    __IO uint32_t TIMx_EGR;
    __IO uint32_t TIMx_CCMR1;
    __IO uint32_t TIMx_CCMR2;
    __IO uint32_t TIMx_CCER;
    __IO uint32_t TIMx_CNT;
    __IO uint32_t TIMx_PSC;
    __IO uint32_t TIMx_ARR;
    __IO uint32_t res1;
    __IO uint32_t TIMx_CCR1;
    __IO uint32_t TIMx_CCR2;
    __IO uint32_t TIMx_CCR3;
    __IO uint32_t TIMx_CCR4;
    __IO uint32_t res2;
    __IO uint32_t TIMx_DCR;
    __IO uint32_t TIMx_DMAR;
    __IO uint32_t TIMx_OR;
}TIMx_t;

typedef struct USART_t{
    __IO uint32_t USART_SR;
    __IO uint32_t USART_DR;
    __IO uint32_t USART_BRR;
    __IO uint32_t USART_CR1;
    __IO uint32_t USART_CR2;
    __IO uint32_t USART_CR3;
    __IO uint32_t USART_GTPR;
}USART_t;

typedef struct NVIC_t{
    volatile uint32_t ISER[8];
    volatile uint32_t ICER[8];
    volatile uint32_t ISPR[8];
    volatile uint32_t ICPR[8];
    volatile uint32_t IABR[8];
    volatile uint32_t IPR[8];
    volatile uint32_t STIR[8];
}NVIC_t;


typedef struct SYSCFG_t{
    __IO uint32_t SYSCFG_MEMRMP;
    __IO uint32_t SYSCFG_PMC;
    __IO uint32_t SYSCFG_EXTICR1;
    __IO uint32_t SYSCFG_EXTICR2;
    __IO uint32_t SYSCFG_EXTICR3;
    __IO uint32_t SYSCFG_EXTICR4;
    __IO uint32_t res[2];
    __IO uint32_t SYSCFG_CMPCR;
}SYSCFG_t;

typedef struct EXTI_t{
    __IO uint32_t EXTI_IMR;
    __IO uint32_t EXTI_EMR;
    __IO uint32_t EXTI_RTSR;
    __IO uint32_t EXTI_FTSR;
    __IO uint32_t EXTI_SWIER;
    __IO uint32_t EXTI_PR;
}EXTI_t;

// diese deklarationen erlauben uns diese pointer in anderen dateien zu benutzen.
extern RCC_t * const RCC;
extern GPIOx_t * const GPIOA;
extern USART_t * const USART2;
extern NVIC_t * const NVIC;

#endif
