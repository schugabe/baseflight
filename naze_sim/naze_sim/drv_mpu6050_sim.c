//
//  drv_mpu6050_sim.c
//  naze_sim
//
//  Created by Johannes Kasberger on 01.06.14.
//  Copyright (c) 2014 Johannes Kasberger. All rights reserved.
//

#include "board.h"
#include "mw.h"

static sensor_align_e gyroAlign = CW0_DEG;
static sensor_align_e accAlign = CW0_DEG;
extern uint16_t acc_1G;

static void mpu6050AccInit(sensor_align_e align)
{
    acc_1G = 512 * 8;
    
    if (align > 0)
        accAlign = align;
}

static void mpu6050AccRead(int16_t *accData)
{
    int16_t data[3];
    
    /*data[X] = -310;
    data[Y] = -400;
    data[Z] = 4112;*/
    
    getDataAcc(data);
    alignSensors(data, accData, accAlign);
}

static void mpu6050GyroInit(sensor_align_e align)
{
    if (align > 0)
        gyroAlign = align;
}

static void mpu6050GyroRead(int16_t *gyroData)
{
    int16_t data[3] = {0,0,0};
    
    /*if (!f.ARMED) {
        data[X] = 0;
        data[Y] = 0;
        data[Z] = 0;
    }
    else {*/
    /*    static int bla = 0;
        bla++;
    if (bla>1200)
        data[X] = (int16_t)(8000.0f*cosf(bla));*/
        //data[Y] = (int16_t)(100.0f*sinf(bla));
        //data[Z] = (int16_t)(100.0f*cosf(bla));
    //}
    
    getDataGyro(data);
    
    alignSensors(data, gyroData, gyroAlign);
}


bool mpu6050Detect(sensor_t * acc, sensor_t * gyro, uint16_t lpf, uint8_t *scale) {
    acc->init = mpu6050AccInit;
    acc->read = mpu6050AccRead;
    gyro->init = mpu6050GyroInit;
    gyro->read = mpu6050GyroRead;
    
    if (scale)
        *scale = 0;
    
    // 16.4 dps/lsb scalefactor
    gyro->scale = (4.0f / 16.4f) * (M_PI / 180.0f) * 0.000001f;
    return true;
}

void mpu6050DmpLoop(void) {
    
}
void mpu6050DmpResetFifo(void) {
    
}