//
//  sim_serial.c
//  naze_sim
//
//  Created by Johannes Kasberger on 06.06.14.
//  Copyright (c) 2014 Johannes Kasberger. All rights reserved.
//
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "board.h"

static uartPort_t uartPort1;
//static uartPort_t uartPort2;
static DMA_Channel_TypeDef dma_channel;

#define BUFFER_SIZE 1024
char buffer[BUFFER_SIZE];
int read_buffer_index = 0;
int bytes_in_buffer = 0;
int sockfd;

void serialWrite(serialPort_t *instance, uint8_t ch){
    write(sockfd,&ch,1);
}

int cliPrintf(char *format, ...)
{
    char printf_buffer[1024];
    va_list aptr;
    
    
    va_start(aptr, format);
    int n = vsprintf(printf_buffer, format, aptr);
    va_end(aptr);
    
    int i;
    for (i=0; i < n; i++) {
       serialWrite((serialPort_t *)&uartPort1,printf_buffer[i]);
    }
    return n;
}

uint8_t serialTotalBytesWaiting(serialPort_t *instance){
    if (bytes_in_buffer == 0) {
        memset(buffer,0,BUFFER_SIZE);
        int bytes = recv(sockfd,buffer,BUFFER_SIZE, MSG_DONTWAIT);
    
        if (bytes > 0)
        {
            bytes_in_buffer = bytes;
            read_buffer_index = 0;
        }
    }
    return bytes_in_buffer;
}

uint8_t serialRead(serialPort_t *instance) {
    uint8_t c = 0;
    if (bytes_in_buffer > 0) {
        c = buffer[read_buffer_index];
        read_buffer_index++;
        bytes_in_buffer--;
    }
    return c;
}

void serialSetBaudRate(serialPort_t *instance, uint32_t baudRate) {
    
}

void serialSetMode(serialPort_t *instance, portMode_t mode) {
    
}

bool isSerialTransmitBufferEmpty(serialPort_t *instance) {
    return true;
}

// socat -d -d TCP4-LISTEN:54323,reuseaddr,fork  PTY,ispeed=115200,ospeed=115200,raw,iexten=0
void openSocket()
{
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    portno = 54323;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("ERROR opening socket");
        exit(0);
    }
    
    server = gethostbyname("localhost");
    if (server == NULL) {
        printf("ERROR, no such host\n");
        exit(0);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        printf("ERROR connecting");
        exit(0);
    }
}

serialPort_t *uartOpen(USART_TypeDef *USARTx, serialReceiveCallbackPtr callback, uint32_t baudRate, portMode_t mode) {
    uartPort_t *s;
    static volatile uint8_t rx1Buffer[UART1_RX_BUFFER_SIZE];
    static volatile uint8_t tx1Buffer[UART1_TX_BUFFER_SIZE];
    
    s = &uartPort1;
    //s->port.vTable = uartVTable;
    
    s->port.baudRate = baudRate;
    
    s->port.rxBuffer = rx1Buffer;
    s->port.txBuffer = tx1Buffer;
    s->port.rxBufferSize = UART1_RX_BUFFER_SIZE;
    s->port.txBufferSize = UART1_TX_BUFFER_SIZE;
    
    s->rxDMAChannel = &dma_channel;
    s->txDMAChannel = &dma_channel;
    
    openSocket();
    
    
    return (serialPort_t *)s;
}