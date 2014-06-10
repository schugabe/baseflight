//
//  sim_pwm.c
//  naze_sim
//
//  Created by Johannes Kasberger on 01.06.14.
//  Copyright (c) 2014 Johannes Kasberger. All rights reserved.
//

#include "board.h"
#include "mw.h"

uint16_t last_value[8];

bool pwmInit(drv_pwm_config_t *init) {
    int i;
    for (i=0; i < 8; i++) {
        last_value[i] = 0;
    }
    return false;
}
void pwmWriteMotor(uint8_t index, uint16_t value) {
    if (last_value[index] != value) {
        //printf("%d motor: %i\n",index,value);
        last_value[index] = value;
    }
}
void pwmWriteServo(uint8_t index, uint16_t value) {
    
}
uint16_t pwmRead(uint8_t channel) {
/*    static long ticks = 0;
    ticks++;
    
    if (ticks < 1000)
        return mcfg.midrc;
        
    if (!f.ARMED) {
        if (ticks < 2500) {
            if (channel == 2) {
                return mcfg.mincheck-1;
            }
            if (channel == 3) {
                return mcfg.maxcheck+1;
            }
            return mcfg.midrc;
        }
        else {
            if (ticks > 2700)
                ticks = 1001;
            return mcfg.midrc;
        }
    }*/
    return mcfg.midrc;
}