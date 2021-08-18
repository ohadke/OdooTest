#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <assert.h>
#include <string.h>

#define HASH "hash"
#define HEIGHT "height"
#define TIME "time"
#define RECEIVED_TIME "received_time"
#define RELAYED_BY "relayed_by"
#define PREV_BLOCK "prev_block"
#define TOTAL "total"


typedef struct BlockChain {
	char* hash;
	char* height;
	char* total;
	char* time;
	char* received_time;
	char* relayed_by;
	char* prev_block;
}BlockChain;

BlockChain* read10Blocks();
void freeBlocks(BlockChain** blocks);
void printBlock(BlockChain* block);
void printBlocks(BlockChain* blocks);
char* getValueOfAttribute(BlockChain block, char* attribute) ;
BlockChain findBlock(BlockChain* blocks, char* attributeName, char* value);
