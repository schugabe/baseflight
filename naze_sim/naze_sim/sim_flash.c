//
//  sim_flash.c
//  naze_sim
//
//  Created by Johannes Kasberger on 01.06.14.
//  Copyright (c) 2014 Johannes Kasberger. All rights reserved.
//
#include "board.h"

#define FLASH_SIZE                  2048

static FILE* configFile;

void loadEEPROM(void) {
    FILE* eeprom = fopen("flash.bin","rb+");
    
    if (eeprom == NULL)
        return;
    
    uint8_t tmpFlash[FLASH_SIZE];
    
    fread(tmpFlash, sizeof(uint8_t), FLASH_SIZE, eeprom);
    fclose(eeprom);
    
    int i;
    for (i=0; i < FLASH_SIZE; i++) {
        FLASH_WRITE_ADDR[i] = tmpFlash[i];
    }
}

void FLASH_Lock(void) {
    fclose(configFile);
}

void FLASH_Unlock(void) {
    configFile = fopen("flash.bin","wb+");
}

void FLASH_ClearFlag(uint32_t FLASH_FLAG) {
    
}

FLASH_Status FLASH_ErasePage(uint8_t* Page_Address) {
    FLASH_Status status = FLASH_COMPLETE;
    
    memset(Page_Address, FLASH_SIZE, 0);
    
    if (configFile != NULL) {
        fseek(configFile, 0, SEEK_SET);
        uint8_t zero = 0;
        fwrite(&zero, sizeof(zero), FLASH_SIZE, configFile);
    }
    return status;
}

FLASH_Status FLASH_ProgramWord(uint8_t* Address, uint32_t Data){
    FLASH_Status status = FLASH_COMPLETE;
    
    if (configFile != NULL) {
        int offset = Address - FLASH_WRITE_ADDR;
    
        if (fseek(configFile, offset, SEEK_SET) == 0) {
            fwrite(&Data, sizeof(Data), 1, configFile);
        }
        else
            printf("seek %i offset failed\n",offset);
    }
    
   *(uint32_t*)Address = Data;
    return status;
}
