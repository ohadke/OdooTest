#include"BlockChain.h"

char* getAttribute(FILE* file) {
	char currentline[100];
	fgets(currentline, sizeof(currentline), file);
	char* str = strtok(currentline, " ");
	str = strtok(NULL, " ");
	return strdup(str);
}

BlockChain createBlockChain(FILE* file){
	BlockChain block;
	block.hash = getAttribute(file);
	block.height = getAttribute(file);
	block.total = getAttribute(file);
	block.time = getAttribute(file);
	block.received_time = getAttribute(file);
	block.relayed_by = getAttribute(file);
	block.prev_block = getAttribute(file);
	return block;
}

BlockChain* read10Blocks() {
	FILE *file = fopen("printdb1", "r");
	BlockChain *blocks = (BlockChain*)malloc(10 * sizeof(BlockChain));
	char currentline[100];
	int index = 0;
	while (fgets(currentline, sizeof(currentline), file) != NULL) {
		if (!strcmp(currentline, "**\n")) {
			blocks[index++] = createBlockChain(file);
		}
	}
	fclose(file);
	return blocks;
}

void freeBlocks(BlockChain** blocks) {
	BlockChain* blocksPtr = *blocks;
	for (int i = 0; i < 10; i++) {
		free(blocksPtr[i].hash);
		free(blocksPtr[i].height);
		free(blocksPtr[i].prev_block);
		free(blocksPtr[i].received_time);
		free(blocksPtr[i].relayed_by);
		free(blocksPtr[i].time);
		free(blocksPtr[i].total);
	}
	free(blocksPtr);
	*blocks = NULL;
}

void printBlock(BlockChain* block) {
	printf("%s: %s\n", HASH, block->hash);
	printf("%s: %s\n", HEIGHT, block->height);
	printf("%s: %s\n", TOTAL, block->total);
	printf("%s: %s\n", TIME, block->time);
	printf("%s: %s\n", RECEIVED_TIME, block->received_time);
	printf("%s: %s\n", RELAYED_BY, block->relayed_by);
	printf("%s: %s\n", PREV_BLOCK, block->prev_block);
}
void printArrow() {
	printf("\t\t\t|\n");
	printf("\t\t\t|\n");
	printf("\t\t\t|\n");
	printf("\t\t\tv\n");
}
void printBlocks(BlockChain* blocks) {
	printBlock(blocks);
	for (int i = 1; i < 10; i++) {
		printArrow();
		printBlock(blocks + i);
	}
}
char* getValueOfAttribute(BlockChain block, char* attribute) {
	char* value = NULL;
	if (!strcmp(attribute, HASH))
		value = block.hash;
	if (!strcmp(attribute, HEIGHT))
		value = block.height;
	if (!strcmp(attribute, TIME))
		value = block.time;
	if (!strcmp(attribute, PREV_BLOCK))
		value = block.prev_block;
	if (!strcmp(attribute, TOTAL))
		value = block.total;
	if (!strcmp(attribute, RECEIVED_TIME))
		value = block.received_time;
	if (!strcmp(attribute, RELAYED_BY))
		value = block.relayed_by;
	return value;
}
BlockChain findBlock(BlockChain* blocks, char* attributeName, char* value) {
	char* attribute;
	int i;
	for (i = 0; i < 10; i++) {
		attribute = getValueOfAttribute(blocks[i], attributeName);
		if (!strcmp(value, attribute))
			break;
	}
	return blocks[i];
}
