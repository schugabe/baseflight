//
//  sim.c
//  naze_sim
//
//  Created by Johannes Kasberger on 30.05.14.
//  Copyright (c) 2014 Johannes Kasberger. All rights reserved.
//
#include <unistd.h>
#include <sys/time.h>

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
uint32_t U_ID_0 = 0x1FFFF7E8;
uint32_t U_ID_1 = 0x1FFFF7EC;
uint32_t U_ID_2 = 0x1FFFF7F0;
struct timeval startTime;

void systemInit(bool overclock) {
    gettimeofday(&startTime,NULL);
    
    if(createListenThread()) {
        exit(1);
    }
    
    
    return;
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
    usleep(us);
}

void delay(uint32_t ms) {
    delayMicroseconds(ms*1000);
}

uint32_t micros(void) {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return 1000000 * (tv.tv_sec-startTime.tv_sec) + (tv.tv_usec-startTime.tv_usec);
}

uint32_t millis(void) {
    return micros()/1000;
}