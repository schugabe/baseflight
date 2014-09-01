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


#include "board.h"
#include "mw.h"
#include "telemetry_common.h"

pthread_t threadid;
int sockfd;
int running = 1;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct in_msg_t {
    int version;
    int16_t gyroData[3];
    int16_t accelData[3];
    uint16_t rcData[8];
} in_msg_t;

in_msg_t lastMsg;

typedef struct out_msg_t {
    int version;
    int channel;
    int16_t rcData;
} out_msg_t;

bool openPort(int portno) {
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
	if (sockfd < 0)
		return false;
    
	const int on = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
		return false;
    
	struct sockaddr_in serv_addr;
	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
    
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		return false;
    
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
	int n;
    in_msg_t msg;
	puts("Listening...");
	while (running) {
        memset(&msg,0,sizeof(msg));
		size_t len_rec = 0;
		do {
			n = read(sockfd, (void*)&msg+len_rec, sizeof(msg)-len_rec);
			if (n <= 0) {
				break;
			}
			len_rec += n;
		} while (len_rec != sizeof(msg));
        
		if (n < 0) {
			if (running)
				fputs("Read error\n", stderr);
			break;
		}
		if (!n)
			continue;
        
        setData(&msg);
        
        
	}
	return NULL;
}

bool createListenThread() {
    if (!openPort(3000))
        return false;
    
	if (pthread_create(&threadid, NULL, communicationThread, NULL) != 0)
        return false;
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

void sendUpdateRC(int channel, uint16_t data) {
    out_msg_t msg;
    msg.version = 1;
    msg.channel = channel;
    msg.rcData = data;
    write(sockfd, &msg, sizeof(msg));
}

