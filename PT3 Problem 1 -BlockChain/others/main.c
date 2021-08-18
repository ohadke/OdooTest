#include"BlockChain.h"
#include"globals.h"
#include"server.h"
#include"miner.h"
#define NUM_OF_MINERS 4
void initializeMutexesAndCond(){
	pthread_cond_init(&Check_Block_Event, NULL);
	pthread_mutex_init(&stam_mutex, NULL);
	pthread_mutex_init(&Speak_To_Server, NULL);
	pthread_mutex_init(&last_Block, NULL);
}
void createServerAndMinersThreads(pthread_t* server, pthread_t* miners){
	int i,x[4] = {1,2,3,4};
	struct sched_param max_prio, min_prio ;
	pthread_attr_t server_attr,miner_attr;
	
	max_prio.sched_priority = sched_get_priority_max(SCHED_RR);
	min_prio.sched_priority = sched_get_priority_min(SCHED_RR);
	
	pthread_attr_init(&server_attr);
	pthread_attr_init(&miner_attr);
	pthread_attr_setschedparam(&server_attr,&max_prio);
	pthread_attr_setschedparam(&miner_attr, &min_prio);
	pthread_attr_setschedpolicy(&server_attr, SCHED_RR);
	pthread_attr_setschedpolicy(&miner_attr, SCHED_RR);
	pthread_attr_setinheritsched(&server_attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setinheritsched(&miner_attr, PTHREAD_EXPLICIT_SCHED);
	pthread_setschedparam(pthread_self(), SCHED_RR, &min_prio);
	
	pthread_create(server, &server_attr,ServerRoutine, NULL);
	for(i=0;i<NUM_OF_MINERS;i++){
			pthread_create(miners + i, &miner_attr, MinerRoutine, x+i);
	}
	pthread_create(miners + i, &miner_attr, DummyMinerRoutine, NULL);
}
void waitForServerAndMinersThreads(pthread_t* server, pthread_t* miners){
	int i;
	for(i=0;i<NUM_OF_MINERS +1;i++){
		pthread_join(miners[i], NULL);
	}
	pthread_join(*server, NULL);
}

void main() {
	pthread_t server,miners[NUM_OF_MINERS + 1];//last for dummy miner
	initializeMutexesAndCond();
	createServerAndMinersThreads(&server,miners);
	waitForServerAndMinersThreads(&server,miners);
	printf("program done!\n");
}