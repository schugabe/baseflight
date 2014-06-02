//
//  sim.c
//  naze_sim
//
//  Created by Johannes Kasberger on 30.05.14.
//  Copyright (c) 2014 Johannes Kasberger. All rights reserved.
//

#include "board.h"
#include "mw.h"
#include "telemetry_common.h"

int SystemCoreClock = 1234;
uint32_t hse_value = 1234;
USART_TypeDef USART1_BASE;
USART_TypeDef *USART1 = &USART1_BASE;
USART_TypeDef USART2_BASE;
USART_TypeDef *USART2 = &USART2_BASE;
GPIO_TypeDef GPIOB_data;
GPIO_TypeDef *GPIOB = &GPIOB_data;


void systemInit(bool overclock) {
    
}

// failure
void failureMode(uint8_t mode) {
    printf("Failure Mode %i\n",mode);
    exit(1);
}

// bootloader/IAP
void systemReset(bool toBootloader) {
    
}

void delayMicroseconds(uint32_t us) {
    
}

void delay(uint32_t ms) {
    
}

uint32_t micros(void) {
    return 0;
}

uint32_t millis(void) {
    return 0;
}