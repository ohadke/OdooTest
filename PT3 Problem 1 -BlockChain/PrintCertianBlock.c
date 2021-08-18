#include"BlockChain.h"

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
int startWith(char* bigger, char* smaller) {
	int i;
	char* copy = (char*)malloc((strlen(smaller) + 1) * sizeof(char));
	for (i = 0; i < strlen(smaller); i++) {
		copy[i] = bigger[i];
	}
	copy[i] = 0;
	return strcmp(smaller, copy);
}
int main(int argc, char* argv[]) {
	int i;
	if(argv[1] && argv[2]){
	char* attributeName = argv[1];
	if (startWith(attributeName, "--") == 0)
		attributeName += strlen("--");
	char* value = argv[2];
	BlockChain* blocks = read10Blocks();
	BlockChain block = findBlock(blocks, attributeName, value);
	printBlock(&block);
	freeBlocks(&blocks);
	}
	else{
	printf("Eror: the program didn't get inputs");
	}
	return 0;
}
