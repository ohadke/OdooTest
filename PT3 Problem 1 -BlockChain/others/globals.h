#ifndef __GLOBALS__
#define __GLOBALS__

#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sched.h>
#include <zlib.h>
#include <time.h>
#include"BlockChain.h"
#define DIFFICULTY 25

Block L_Block; //global Block represent copy of the last block in the chain
Block Send_To_Check_Block; //global Block represent copy of the next Block to check by the server
pthread_mutex_t last_Block;
pthread_mutex_t stam_mutex;
pthread_mutex_t Speak_To_Server;
pthread_cond_t Check_Block_Event;
pthread_cond_t Finish_Check;


#endif