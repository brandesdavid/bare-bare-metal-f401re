/**
 *@file startup_STM32F401RE.c
 *@brief Startup Code for Vector Table Initialization and Reset Handling
 *@include startup_STM32F401RE.c
 **/
#include <stdint.h>

/** global variables **/
extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

/* diese funktionen sind prototypen fuer verschiedenste handler funktionen, bei interrupts.
der "weak" keyword ist eine ueberschreibbare funktion. sollte diese funktion nicht anderswo
veraendert werden, dann wird diese funktion aufgerufen, und der alias zeigt auf einen
default handler, sollte alles schief gehen, denke ich. */
/** Prototypes **/
extern int main(void);
void Reset_handler          (void);
void NMI_handler            (void)__attribute__((weak, alias("Default_handler")));
void HardFault_handler      (void)__attribute__((weak, alias("Default_handler")));
void MemManage_handler      (void)__attribute__((weak, alias("Default_handler")));
void BusFault_handler       (void)__attribute__((weak, alias("Default_handler")));
void UsageFault_handler    (void)__attribute__((weak, alias("Default_handler")));
void SVCall_handler         (void)__attribute__((weak, alias("Default_handler")));
void DebugMonitor_handler   (void)__attribute__((weak, alias("Default_handler")));
void PendSV_handler         (void)__attribute__((weak, alias("Default_handler")));
void Systick_handler        (void)__attribute__((weak, alias("Default_handler")));
void WWDG_handler                 (void)__attribute__((weak, alias("Default_handler")));
void EXITI16_PVD__handler         (void)__attribute__((weak, alias("Default_handler")));
void EXITI21_TAMP_STAMP_handler   (void)__attribute__((weak, alias("Default_handler")));
void EXITI22_RTC_WKUP_handler     (void)__attribute__((weak, alias("Default_handler")));
void FLASH_handler                (void)__attribute__((weak, alias("Default_handler")));
void RCC_handler                  (void)__attribute__((weak, alias("Default_handler")));
void EXTI0_handler                (void)__attribute__((weak, alias("Default_handler")));
void EXTI1_handler                (void)__attribute__((weak, alias("Default_handler")));
void EXTI2_handler                (void)__attribute__((weak, alias("Default_handler")));
void EXTI3_handler                (void)__attribute__((weak, alias("Default_handler")));
void EXTI4_handler                (void)__attribute__((weak, alias("Default_handler")));
void DMA1_Stream0_handler         (void)__attribute__((weak, alias("Default_handler")));
void DMA1_Stream1_handler         (void)__attribute__((weak, alias("Default_handler")));
void DMA1_Stream2_handler         (void)__attribute__((weak, alias("Default_handler")));
void DMA1_Stream3_handler         (void)__attribute__((weak, alias("Default_handler")));
void DMA1_Stream4_handler         (void)__attribute__((weak, alias("Default_handler")));
void DMA1_Stream5_handler         (void)__attribute__((weak, alias("Default_handler")));
void DMA1_Stream6_handler         (void)__attribute__((weak, alias("Default_handler")));
void ADC_handler                  (void)__attribute__((weak, alias("Default_handler")));
void EXTI9_5__handler             (void)__attribute__((weak, alias("Default_handler")));
void TIM1_BRK_TIM9_handler        (void)__attribute__((weak, alias("Default_handler")));
void TIM1_UP_TIM10_handler        (void)__attribute__((weak, alias("Default_handler")));
void TIM1_TRG_COM_TIM11_handler   (void)__attribute__((weak, alias("Default_handler")));
void TIM1_CC_handler              (void)__attribute__((weak, alias("Default_handler")));
void TIM2_handler                 (void)__attribute__((weak, alias("Default_handler")));
void TIM3_handler                 (void)__attribute__((weak, alias("Default_handler")));
void TIM4_handler                 (void)__attribute__((weak, alias("Default_handler")));
void I2C1_EV_handler              (void)__attribute__((weak, alias("Default_handler")));
void I2C1_ER_handler              (void)__attribute__((weak, alias("Default_handler")));
void I2C2_EV_handler              (void)__attribute__((weak, alias("Default_handler")));
void I2C2_ER_handler              (void)__attribute__((weak, alias("Default_handler")));
void SPI1_handler                 (void)__attribute__((weak, alias("Default_handler")));
void SPI2_handler                 (void)__attribute__((weak, alias("Default_handler")));
void UART1_handler                (void)__attribute__((weak, alias("Default_handler")));
void UART2_handler                (void)__attribute__((weak, alias("Default_handler")));
void EXTI15_10_handler            (void)__attribute__((weak, alias("Default_handler")));
void EXTI17_RTC_Alarm_handler     (void)__attribute__((weak, alias("Default_handler")));
void EXTI18_OTG_FS_WKUP_handler   (void)__attribute__((weak, alias("Default_handler")));
void DMA1_Stream7_handler         (void)__attribute__((weak, alias("Default_handler")));
void SDIO_handler                 (void)__attribute__((weak, alias("Default_handler")));
void TIM5_handler                 (void)__attribute__((weak, alias("Default_handler")));
void SPI3_handler                 (void)__attribute__((weak, alias("Default_handler")));
void DMA2_Stream0_handler                 (void)__attribute__((weak, alias("Default_handler")));
void DMA2_Stream1_handler                 (void)__attribute__((weak, alias("Default_handler")));
void DMA2_Stream2_handler                 (void)__attribute__((weak, alias("Default_handler")));
void DMA2_Stream3_handler                 (void)__attribute__((weak, alias("Default_handler")));
void DMA2_Stream4_handler                 (void)__attribute__((weak, alias("Default_handler")));
void OTG_FS_handler                       (void)__attribute__((weak, alias("Default_handler")));
void DMA2_Stream5_handler                 (void)__attribute__((weak, alias("Default_handler")));
void DMA2_Stream6_handler                 (void)__attribute__((weak, alias("Default_handler")));
void DMA2_Stream7_handler                 (void)__attribute__((weak, alias("Default_handler")));
void UART6_handler                        (void)__attribute__((weak, alias("Default_handler")));
void I2C3_EV_handler                      (void)__attribute__((weak, alias("Default_handler")));
void I2C3_ER_handler                      (void)__attribute__((weak, alias("Default_handler")));
void FPU_handler                          (void)__attribute__((weak, alias("Default_handler")));
void SPI4_handler                         (void)__attribute__((weak, alias("Default_handler")));


// interrupt vector tabelle bzw. ein array von funktionen, die aufgerufen werden, wenn ein interrupt auftritt.
// wenn ein interrupt auftritt, wird die entsprechende funktion aufgerufen.
/** Initialize Interrupt Vector **/
__attribute__ ((section(".isr_vector")))
void (* const fpn_vector[])(void) = {
    // das ist der initiale stackpointer. wenn der microcontroller startet, wird der stackpointer auf diesen wert gesetzt.
    // der stackpointer zeigt auf den letzten wert im ram.
    // das ist ein funktion pointer, der auf eine funktion zeigt, die keinen rückgabewert hat und keine parameter hat.
    (void (*)(void))(&_estack),
    // das ist der entry point fuer das programm. wenn der microcontroller startet, wird diese funktion aufgerufen.
    Reset_handler,
    // nmihandler heißt non maskable interrupt handler. d.h. egal was passiert, dieser interrupt wird immer ausgeführt.
    NMI_handler,
    // hardfault handler wird aufgerufen, wenn ein fehler auftritt, der nicht behandelt werden kann.
    HardFault_handler,
    // memmanage handler wird aufgerufen, wenn ein fehler auftritt, der mit dem speicher zu tun hat.
    MemManage_handler,
    // busfault handler wird aufgerufen, wenn ein fehler auftritt, der mit dem bus zu tun hat.
    BusFault_handler,
    // usagefault handler wird aufgerufen, wenn ein fehler auftritt, der mit der benutzung des microcontrollers zu tun hat.
    UsageFault_handler,
    0,
    0,
    0,
    0,
    SVCall_handler,
    DebugMonitor_handler,
    0,
    PendSV_handler,
    Systick_handler,
    WWDG_handler,
    EXITI16_PVD__handler,
    EXITI21_TAMP_STAMP_handler,
    EXITI22_RTC_WKUP_handler,
    FLASH_handler,
    RCC_handler,
    EXTI0_handler,
    EXTI1_handler,
    EXTI2_handler,
    EXTI3_handler,
    EXTI4_handler,
    DMA1_Stream0_handler,
    DMA1_Stream1_handler,
    DMA1_Stream2_handler,
    DMA1_Stream3_handler,
    DMA1_Stream4_handler,
    DMA1_Stream5_handler,
    DMA1_Stream6_handler,
    ADC_handler,
    0,
    0,
    0,
    0,
    EXTI9_5__handler,
    TIM1_BRK_TIM9_handler,
    TIM1_UP_TIM10_handler,
    TIM1_TRG_COM_TIM11_handler,
    TIM1_CC_handler,
    TIM2_handler,
    TIM3_handler,
    TIM4_handler,
    I2C1_EV_handler,
    I2C1_ER_handler,
    I2C2_EV_handler,
    I2C2_ER_handler,
    SPI1_handler,
    SPI2_handler,
    UART1_handler,
    UART2_handler,
    0,
    EXTI15_10_handler,
    EXTI17_RTC_Alarm_handler,
    EXTI18_OTG_FS_WKUP_handler,
    0,
    0,
    0,
    0,
    DMA1_Stream7_handler,
    0,
    SDIO_handler,
    TIM5_handler,
    SPI3_handler,
    0,
    0,
    0,
    0,
    DMA2_Stream0_handler,
    DMA2_Stream1_handler,
    DMA2_Stream2_handler,
    DMA2_Stream3_handler,
    DMA2_Stream4_handler,
    0,
    0,
    0,
    0,
    0,
    0,
    OTG_FS_handler,
    DMA2_Stream5_handler,
    DMA2_Stream6_handler,
    DMA2_Stream7_handler,
    UART6_handler,
    I2C3_EV_handler,
    I2C3_ER_handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    FPU_handler,
    0,
    0,
    SPI4_handler
};

/* dieser reset_handler wird vom linker file declared. das ist die aller erste funktion die aufgerufen wird, 
wenn das board resettet wird oder angeschaltet wird.*/

void Reset_handler(void){
    /** Copy Data from FLASH to SRAM **/
    uint32_t * pSRC = (uint32_t *)&_sidata;
    uint32_t * pDST = (uint32_t *)&_sdata;

    for(uint32_t *dataptr = (uint32_t *)pDST; dataptr < &_edata;){

        *dataptr++ = *pSRC++;
    }
    /** Initialize BSS with ZEROES **/
    for(uint32_t *bss_ptr = (uint32_t *)&_sbss; bss_ptr < &_ebss;){
        *bss_ptr++ = 0;
    }

    /** CALL main() **/
    main();
}

// default handler funktion ist eine endlosschleife, die aufgerufen wird, wenn ein interrupt auftritt, der nicht behandelt wird.
void Default_handler(void){
    for(;;);
}
