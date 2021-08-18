#ifndef __MINER__
#define __MINER__

#include"globals.h"
#include"BlockChain.h"
void* MinerRoutine(void* input);
void* DummyMinerRoutine(void* input);
Block createBlock(BlockDataForHash blockData,unsigned int hash);
BlockDataForHash getBlockForDataData( int id);

#endif