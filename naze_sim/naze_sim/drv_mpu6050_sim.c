//
//  drv_mpu6050_sim.c
//  naze_sim
//
//  Created by Johannes Kasberger on 01.06.14.
//  Copyright (c) 2014 Johannes Kasberger. All rights reserved.
//

#include "board.h"

static sensor_align_e gyroAlign = CW0_DEG;
static sensor_align_e accAlign = CW0_DEG;
extern uint16_t acc_1G;
static uint8_t mpuAccelHalf = 0;

static void mpu6050AccInit(sensor_align_e align)
{
    if (mpuAccelHalf)
        acc_1G = 255 * 8;
    else
        acc_1G = 512 * 8;
    
    if (align > 0)
        accAlign = align;
}

static void mpu6050AccRead(int16_t *accData)
{
    uint8_t buf[6];
    int16_t data[3];
    
    data[0] = (int16_t)((buf[0] << 8) | buf[1]);
    data[1] = (int16_t)((buf[2] << 8) | buf[3]);
    data[2] = (int16_t)((buf[4] << 8) | buf[5]);
    
    alignSensors(data, accData, accAlign);
}

static void mpu6050GyroInit(sensor_align_e align)
{
    if (align > 0)
        gyroAlign = align;
}

static void mpu6050GyroRead(int16_t *gyroData)
{
    uint8_t buf[6];
    int16_t data[3];
    
    data[0] = (int16_t)((buf[0] << 8) | buf[1]) / 4;
    data[1] = (int16_t)((buf[2] << 8) | buf[3]) / 4;
    data[2] = (int16_t)((buf[4] << 8) | buf[5]) / 4;
    
    alignSensors(data, gyroData, gyroAlign);
}


bool mpu6050Detect(sensor_t * acc, sensor_t * gyro, uint16_t lpf, uint8_t *scale) {
    acc->init = mpu6050AccInit;
    acc->read = mpu6050AccRead;
    gyro->init = mpu6050GyroInit;
    gyro->read = mpu6050GyroRead;
    
    // 16.4 dps/lsb scalefactor
    gyro->scale = (4.0f / 16.4f) * (M_PI / 180.0f) * 0.000001f;
    return true;
}

void mpu6050DmpLoop(void) {
    
}
void mpu6050DmpResetFifo(void) {
    
}