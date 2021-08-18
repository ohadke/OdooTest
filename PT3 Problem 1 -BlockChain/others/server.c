#include"globals.h"
#include"server.h"
#include<string.h>

void createGenesisBlock(BlockChain *chain)
{
	Block genBlock;
	BlockDataForHash  data;
	memset(&genBlock, 0x00, sizeof(Block));
	genBlock.timestamp=((int)time(NULL));
	data = getDataForHash(genBlock);
	genBlock.hash = calcHash(data);
	addBlockToChain(chain,genBlock);
	L_Block = genBlock;
}

int isValidBlock()
{
	BlockDataForHash  data;
	int hash;
	if(L_Block.height + 1 ==  Send_To_Check_Block.height){
		if(L_Block.hash == Send_To_Check_Block.prev_hash){
			if(isValidHash(Send_To_Check_Block.hash, DIFFICULTY)){
				data = getDataForHash(Send_To_Check_Block);
				hash = calcHash(data);
				if(hash == Send_To_Check_Block.hash)
					return 1;
			}
		}
	}
	return 0;
}
void printNewBlock(){
	printf("Server: New block added by %d ,attributes : height (%d), timestamp(%d), hash(0x%04x), prev_hash(0x%04x), difficulty(%d), nonce(%d)\n",Send_To_Check_Block.relayed_by,Send_To_Check_Block.height,Send_To_Check_Block.timestamp, Send_To_Check_Block.hash,Send_To_Check_Block.prev_hash,Send_To_Check_Block.difficulty,Send_To_Check_Block.nonce);
}

void updateChain(BlockChain* chain)
{
	printNewBlock();
    addBlockToChain(chain,Send_To_Check_Block);
	L_Block=Send_To_Check_Block;
}
void* ServerRoutine(void* input){
	BlockChain chain = getEmptyBlockChain();
	createGenesisBlock(&chain);
	pthread_mutex_lock(&last_Block);
	while(1){
			pthread_cond_wait(&Check_Block_Event, &last_Block);
		 if(isValidBlock())
				 updateChain(&chain);
		else{
			printf("Server reject the block of %d\n", Send_To_Check_Block.relayed_by);
		}
		pthread_cond_signal(&Finish_Check);
	}
		pthread_mutex_unlock(&last_Block);
	return NULL;
}
