//
//  sim_led_beeper.c
//  naze_sim
//
//  Created by Johannes Kasberger on 06.06.14.
//  Copyright (c) 2014 Johannes Kasberger. All rights reserved.
//

#include "board.h"

#define LED_COUNT 2

bool leds[LED_COUNT] = {true,true};

int getLed(GPIO_TypeDef* p,uint32_t i)
{
    int8_t led = -1;
    if (p== GPIOB) {
        if (i == LED0_PIN) {
            led = 0;
        }
        else if (i == LED1_PIN) {
            led = 1;
        }
    }
    return led;
}

void logLed(int led)
{
    /*if (led >=0 && led < LED_COUNT) {
        if (leds[led]) {
            printf("led %i eingeschaltet\n",led);
        }
        else {
            printf("led %i ausgeschaltet\n",led);
        }
    }*/
}
void setLed(GPIO_TypeDef* p,uint32_t i, bool on)
{
    int led = getLed(p,i);
    
    if (led >= 0 && led < LED_COUNT) {
        leds[led] = on;
        logLed(led);
    }
}

void digitalHi(GPIO_TypeDef* p,uint32_t i)
{
    p->BSRR = i;
    setLed(p,i,false);
}

void digitalLo(GPIO_TypeDef* p,uint32_t i)
{
    p->BRR = i;
    setLed(p,i,true);
}

void digitalToggle(GPIO_TypeDef* p,uint32_t i)
{
    p->ODR ^= i;
    int led = getLed(p, i);
    if (led >=0 && led < LED_COUNT) {
        leds[led] = !leds[led];
        logLed(led);
    }
}

void digitalIn(GPIO_TypeDef* p,uint32_t i)
{
    p->IDR = p->IDR & i;
}

void systemBeep(bool onoff) {
    /*if (onoff) {
        printf("beep\n");
    }
    else {
        printf("beep off\n");
    }*/
}