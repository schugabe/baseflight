//
//  sim_interface.c
//  naze_sim
//
//  Created by Johannes Kasberger on 22.06.14.
//  Copyright (c) 2014 Johannes Kasberger. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>
#include <arpa/inet.h>

#include "board.h"
#include "mw.h"
#include "telemetry_common.h"

#define CHANNEL_COUNT 8

static pthread_t threadid;
static int sockfd_interface;
static int running = 1;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct in_msg_t {
    uint16_t version;
    int16_t gyroData[3];
    int16_t accelData[3];
    uint16_t rcData[CHANNEL_COUNT];
} in_msg_t;

static in_msg_t lastMsg;

typedef struct out_msg_t {
    int version;
    int16_t rcData[CHANNEL_COUNT];
} out_msg_t;

static out_msg_t outMsg;

bool openPort(int portno) {
    sockfd_interface = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
	if (sockfd_interface < 0)
		return false;
    
	struct sockaddr_in serv_addr;
	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
    
	if (bind(sockfd_interface, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		return false;
    
    outMsg.version = 1;
    return true;
}

void setData(in_msg_t *msg) {
    if (pthread_mutex_lock(&lock)) {
        puts("Mutex locking not possible!");
    }
    
    memcpy(&lastMsg, msg, sizeof(in_msg_t));
    
    if (pthread_mutex_unlock(&lock)) {
        puts("Mutex unlocking not possible!");
    }
}

void* communicationThread(void* unused) {
    in_msg_t msg;
    struct sockaddr_in si_other;
    
	puts("Listening for packets...");
	
    while (running) {
        memset(&msg,0,sizeof(msg));
        memset((char *) &si_other, 0, sizeof(si_other));
        unsigned int slen = sizeof(si_other);
        ssize_t len_rec = recvfrom(sockfd_interface, &msg, sizeof(msg), 0, (struct sockaddr *) &si_other, &slen);
        if (len_rec == -1)
            continue;
        
        if (len_rec == sizeof(msg)) {
            setData(&msg);
            sendto(sockfd_interface, &outMsg, sizeof(outMsg), 0, (struct sockaddr*) &si_other, slen);
        }
	}
	return NULL;
}

bool createListenThread() {
    if (!openPort(3000))
        return false;
    
	if (pthread_create(&threadid, NULL, communicationThread, NULL) != 0)
        return false;
    //void *bla;
    //communicationThread(bla);
    return true;
}

void getDataAcc(int16_t *data) {
    if (pthread_mutex_lock(&lock)) {
        puts("Mutex locking not possible!");
    }
    
    int axis;
    for( axis = 0; axis < 3; axis++)
        data[axis] = lastMsg.accelData[axis];
    
    if (pthread_mutex_unlock(&lock)) {
        puts("Mutex unlocking not possible!");
    }
}

void getDataGyro(int16_t* data) {
    if (pthread_mutex_lock(&lock)) {
        puts("Mutex locking not possible!");
    }
    
    int axis;
    for( axis = 0; axis < 3; axis++)
        data[axis] = lastMsg.accelData[axis];
    
    
    if (pthread_mutex_unlock(&lock)) {
        puts("Mutex unlocking not possible!");
    }
}

uint16_t getDataRC(int channel) {
    if (pthread_mutex_lock(&lock)) {
        puts("Mutex locking not possible!");
    }
    
    uint16_t data = lastMsg.rcData[channel];
    
    if (pthread_mutex_unlock(&lock)) {
        puts("Mutex unlocking not possible!");
    }
    
    return data;
}

void sendUpdateRC(unsigned int channel, uint16_t data) {
    if (channel < CHANNEL_COUNT)
        outMsg.rcData[channel] = data;
}

