#include "BlockChain.h"

int main(int argc, const char * argv[])
{
        BlockChain* b = read10Blocks();
        printBlocks(b);
        freeBlocks(&b);
}
