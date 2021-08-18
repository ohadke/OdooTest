#include "BlockChain.h"
void createCSV(char* filename, BlockChain* Block, int numOfBlocks) {
        int i;
        printf("\n Creating %s.csv file", filename);
        FILE *fp;


        fp = fopen(filename, "w+");
        fprintf(fp,"%s,", HASH);
        fprintf(fp, "%s,", HEIGHT);
        fprintf(fp, "%s,", TIME);
        fprintf(fp, "%s,", RECEIVED_TIME);
        fprintf(fp, "%s,", RELAYED_BY);
        fprintf(fp, "%s,", PREV_BLOCK);
        fprintf(fp, "%s,\n", TOTAL);

        for (i = 0; i<numOfBlocks; i++)
        {
                fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", Block[i].hash, Block[i].height, Block[i].time, Block[i].received_time, Block[i].relayed_by, Block[i].prev_block, Block[i].total);
        }
        fclose(fp);

        
}

int main()
{
        BlockChain* b = read10Blocks();
        int numOfBlocks = 10;
        char* nameOfFile = "Main3.csv";
        createCSV(nameOfFile, b, numOfBlocks);
        freeBlocks(&b);
        return 0;
} 
