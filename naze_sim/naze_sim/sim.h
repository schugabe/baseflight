//
//  sim.h
//  naze_sim
//
//  Created by Johannes Kasberger on 30.05.14.
//  Copyright (c) 2014 Johannes Kasberger. All rights reserved.
//

#pragma once

typedef struct
{
    uint32_t CRL;
    uint32_t CRH;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t BRR;
    uint32_t LCKR;
} GPIO_TypeDef;





typedef struct
{
    uint16_t CR1;
    uint16_t  RESERVED0;
    uint16_t CR2;
    uint16_t  RESERVED1;
    uint16_t OAR1;
    uint16_t  RESERVED2;
    uint16_t OAR2;
    uint16_t  RESERVED3;
    uint16_t DR;
    uint16_t  RESERVED4;
    uint16_t SR1;
    uint16_t  RESERVED5;
    uint16_t SR2;
    uint16_t  RESERVED6;
    uint16_t CCR;
    uint16_t  RESERVED7;
    uint16_t TRISE;
    uint16_t  RESERVED8;
} I2C_TypeDef;

typedef struct
{
    uint16_t CR1;
    uint16_t  RESERVED0;
    uint16_t CR2;
    uint16_t  RESERVED1;
    uint16_t SMCR;
    uint16_t  RESERVED2;
    uint16_t DIER;
    uint16_t  RESERVED3;
    uint16_t SR;
    uint16_t  RESERVED4;
    uint16_t EGR;
    uint16_t  RESERVED5;
    uint16_t CCMR1;
    uint16_t  RESERVED6;
    uint16_t CCMR2;
    uint16_t  RESERVED7;
    uint16_t CCER;
    uint16_t  RESERVED8;
    uint16_t CNT;
    uint16_t  RESERVED9;
    uint16_t PSC;
    uint16_t  RESERVED10;
    uint16_t ARR;
    uint16_t  RESERVED11;
    uint16_t RCR;
    uint16_t  RESERVED12;
    uint16_t CCR1;
    uint16_t  RESERVED13;
    uint16_t CCR2;
    uint16_t  RESERVED14;
    uint16_t CCR3;
    uint16_t  RESERVED15;
    uint16_t CCR4;
    uint16_t  RESERVED16;
    uint16_t BDTR;
    uint16_t  RESERVED17;
    uint16_t DCR;
    uint16_t  RESERVED18;
    uint16_t DMAR;
    uint16_t  RESERVED19;
} TIM_TypeDef;

typedef struct
{
    uint32_t CCR;
    uint32_t CNDTR;
    uint32_t CPAR;
    uint32_t CMAR;
} DMA_Channel_TypeDef;

typedef struct
{
    uint16_t SR;
    uint16_t  RESERVED0;
    uint16_t DR;
    uint16_t  RESERVED1;
    uint16_t BRR;
    uint16_t  RESERVED2;
    uint16_t CR1;
    uint16_t  RESERVED3;
    uint16_t CR2;
    uint16_t  RESERVED4;
    uint16_t CR3;
    uint16_t  RESERVED5;
    uint16_t GTPR;
    uint16_t  RESERVED6;
} USART_TypeDef;




typedef enum
{
    FLASH_BUSY = 1,
    FLASH_ERROR_PG,
    FLASH_ERROR_WRP,
    FLASH_COMPLETE,
    FLASH_TIMEOUT
}FLASH_Status;

#define FLASH_FLAG_BSY                 ((uint32_t)0x00000001)  /*!< FLASH Busy flag */
#define FLASH_FLAG_EOP                 ((uint32_t)0x00000020)  /*!< FLASH End of Operation flag */
#define FLASH_FLAG_PGERR               ((uint32_t)0x00000004)  /*!< FLASH Program error flag */
#define FLASH_FLAG_WRPRTERR            ((uint32_t)0x00000010)  /*!< FLASH Write protected error flag */
#define FLASH_FLAG_OPTERR              ((uint32_t)0x00000001)  /*!< FLASH Option Byte error flag */


void FLASH_Unlock(void);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(uint8_t* Page_Address);
FLASH_Status FLASH_ProgramWord(uint8_t* Address, uint32_t Data);
void loadEEPROM(void);
extern uint8_t* FLASH_WRITE_ADDR;

extern int SystemCoreClock;
extern uint32_t hse_value;
extern USART_TypeDef *USART1;
extern USART_TypeDef *USART2;
extern GPIO_TypeDef *GPIOB;

void digitalHi(GPIO_TypeDef* p,uint32_t i);
void digitalLo(GPIO_TypeDef* p,uint32_t i);
void digitalToggle(GPIO_TypeDef* p,uint32_t i);
void digitalIn(GPIO_TypeDef* p,uint32_t i);


int cliPrintf(char *format, ...);