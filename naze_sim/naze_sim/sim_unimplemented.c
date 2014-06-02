//
//  sim_unimplemented.c
//  naze_sim
//
//  Created by Johannes Kasberger on 01.06.14.
//  Copyright (c) 2014 Johannes Kasberger. All rights reserved.
//

#include "board.h"

void serialWrite(serialPort_t *instance, uint8_t ch){
    
}
uint8_t serialTotalBytesWaiting(serialPort_t *instance){
    return 0;
}
uint8_t serialRead(serialPort_t *instance) {
    return 0;
}
void serialSetBaudRate(serialPort_t *instance, uint32_t baudRate) {
    
}
void serialSetMode(serialPort_t *instance, portMode_t mode) {
    
}
bool isSerialTransmitBufferEmpty(serialPort_t *instance) {
    return true;
}


void adcInit(drv_adc_config_t *init) {
    
}

uint16_t adcGetChannel(uint8_t channel) {
    return 0;
}

void initTelemetry(void) {
    
}
void checkTelemetryState(void) {
    
}
void handleTelemetry(void){
    
}

bool adxl345Detect(drv_adxl345_config_t *init, sensor_t *acc) {
    return false;
}

bool bma280Detect(sensor_t *acc) {
    return false;
}

bool bmp085Detect(baro_t *baro) {
    return false;
}

void hcsr04_init(sonar_config_t config)
{
}

// distance calculation is done asynchronously, using interrupt
void hcsr04_get_distance(volatile int32_t *distance)
{
}

bool hmc5883lDetect(sensor_align_e align) {
    return false;
}
void hmc5883lInit(void) {
    
}
void hmc5883lRead(int16_t *magData) {
    
}

void i2cInit(I2C_TypeDef *I2Cx) {
    
}
bool i2cWriteBuffer(uint8_t addr_, uint8_t reg_, uint8_t len_, uint8_t *data) {
    return false;
}
bool i2cWrite(uint8_t addr_, uint8_t reg, uint8_t data) {
    return false;
}
bool i2cRead(uint8_t addr_, uint8_t reg, uint8_t len, uint8_t* buf) {
    return false;
}
uint16_t i2cGetErrorCounter(void) {
    return 0;
}

bool l3g4200dDetect(sensor_t *gyro, uint16_t lpf) {
    return false;
}

bool ledringDetect(void) {
    return false;
}
void ledringState(void) {
    
}
void ledringBlink(void) {
    
}

bool mma8452Detect(sensor_t *acc) {
    return false;
}

bool mpu3050Detect(sensor_t *gyro, uint16_t lpf) {
    return false;
}

bool ms5611Detect(baro_t *baro) {
    return false;
}

// spektrum
void spektrumInit(rcReadRawDataPtr *callback) {
    
}
bool spektrumFrameComplete(void) {
    return false;
}

// sbus
void sbusInit(rcReadRawDataPtr *callback) {
    
}
bool sbusFrameComplete(void) {
    return false;
}

// sumd
void sumdInit(rcReadRawDataPtr *callback) {
    
}
bool sumdFrameComplete(void) {
    return false;
}

void serialPrint(serialPort_t *instance, const char *str) {
    
}

void setupSoftSerialPrimary(uint32_t baud, uint8_t inverted) {
    
}

void setupSoftSerialSecondary(uint8_t inverted) {
    
}

void systemBeep(bool onoff) {
    
}

serialPort_t *uartOpen(USART_TypeDef *USARTx, serialReceiveCallbackPtr callback, uint32_t baudRate, portMode_t mode) {
    return NULL;
}