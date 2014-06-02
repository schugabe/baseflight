//
//  sim_flash.c
//  naze_sim
//
//  Created by Johannes Kasberger on 01.06.14.
//  Copyright (c) 2014 Johannes Kasberger. All rights reserved.
//
#include "board.h"

#define FLASH_PAGE_SIZE                 ((uint16_t)0x400)

void FLASH_Unlock(void) {
    
}

void FLASH_ClearFlag(uint32_t FLASH_FLAG) {
    
}

void FLASH_Lock(void) {
    
}

FLASH_Status FLASH_ErasePage(uint8_t* Page_Address) {
    FLASH_Status status = FLASH_COMPLETE;
    memset(Page_Address, FLASH_PAGE_SIZE, 0);
    return status;
}

FLASH_Status FLASH_ProgramWord(uint8_t* Address, uint32_t Data){
    FLASH_Status status = FLASH_COMPLETE;
    *((uint32_t*)Address) = Data;
    return status;
}
