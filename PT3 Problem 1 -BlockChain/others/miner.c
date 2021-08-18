#include"miner.h"

BlockDataForHash getBlockDataFromL_Block( int id);
Block createBlock(BlockDataForHash blockData,unsigned int hash);

void* MinerRoutine(void* input){
	int id = *((int*)input);
	int hash, blocksCounter = 0;
	Block myBlock;
	BlockDataForHash blockData;
	blockData.prev_hash = 0;
	while(1){
		while(1){
			pthread_mutex_lock(&last_Block);
			if( L_Block.hash != blockData.prev_hash){
				blockData=getBlockDataFromL_Block(id);
			}
			else{
				blockData.nonce++;
			}
			pthread_mutex_unlock(&last_Block);
			hash = calcHash(blockData);
			if(isValidHash(hash,DIFFICULTY)){ 
				myBlock = createBlock(blockData, hash);
				printf("Miner #%d: Mined a new block #%d, with the hash 0x%04x\n", id, ++blocksCounter, hash);
				break;
			}
		}
		pthread_mutex_lock(&Speak_To_Server);
			Send_To_Check_Block = myBlock;
			pthread_cond_signal(&Check_Block_Event);//wake up server
			pthread_mutex_lock(&stam_mutex);//dummy mutex because i want to hold the Speak_to_server and then let only one miner speak to server at the time
				pthread_cond_wait(&Finish_Check, &stam_mutex);
			pthread_mutex_unlock(&stam_mutex);
		pthread_mutex_unlock(&Speak_To_Server);
	}
	return NULL;
}

void* DummyMinerRoutine(void* input){

	Block myBlock;
	BlockDataForHash blockData;
	blockData.prev_hash = 0;
	while(1){
		pthread_mutex_lock(&last_Block);
		blockData=getBlockDataFromL_Block(-1);
		pthread_mutex_unlock(&last_Block);
		myBlock = createBlock(blockData, 1);
		printf("DummyMiner: trying to mislead the server\n");
		pthread_mutex_lock(&Speak_To_Server);
			Send_To_Check_Block = myBlock;
			pthread_cond_signal(&Check_Block_Event);//wake up server
			pthread_mutex_lock(&stam_mutex);//dummy mutex because i want to hold the Speak_to_server and then let only one miner speak to server at the time
				pthread_cond_wait(&Finish_Check, &stam_mutex);
			pthread_mutex_unlock(&stam_mutex);
		pthread_mutex_unlock(&Speak_To_Server);
		sleep(1);
	}
	return NULL;
}
Block createBlock(BlockDataForHash blockData,unsigned int hash)
{
	Block newBlock;
	newBlock.hash=hash;
	newBlock.difficulty=DIFFICULTY;
	newBlock.timestamp=blockData.timestamp;
	newBlock.prev_hash=blockData.prev_hash;
	newBlock.relayed_by=blockData.relayed_by;
	newBlock.height=blockData.height;
	newBlock.nonce=blockData.nonce;
	return newBlock;
}


	BlockDataForHash getBlockDataFromL_Block( int id)
	{
			BlockDataForHash block;
			block.nonce=1000*id;
			block.prev_hash=L_Block.hash;
			block.height=(L_Block.height+1);
			block.timestamp=((int)time(NULL));
			block.relayed_by=id;
			return block;
			
	}
	