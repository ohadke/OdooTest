CC=gcc
CFLAGS=-c -Wall
all: running PrintBlockChain.out PrintCertianBlock.out PrintToCSV.out RunScript.out
 
running:   
				gcc -shared -fPIC BlockChain.c -o libBlockChain.so
					            
PrintBlockChain.out: PrintBlockChain.c libBlockChain.so
				$(CC)  PrintBlockChain.c -L  pwd libBlockChain.so -o PrintBlockChain.out
				export LD_LIBRARY_PATH=`pwd`
PrintCertianBlock.out: PrintCertianBlock.c libBlockChain.so
				$(CC) PrintCertianBlock.c -L  pwd libBlockChain.so -o PrintCertianBlock.out
				 export LD_LIBRARY_PATH=`pwd`
PrintToCSV.out: PrintToCSV.c libBlockChain.so
				$(CC) PrintToCSV.c -L  pwd libBlockChain.so -o PrintToCSV.out
				 export LD_LIBRARY_PATH=`pwd`
RunScript.out: RunScript.c 
				$(CC) RunScript.c -L  pwd libBlockChain.so -o RunScript.out
				 export LD_LIBRARY_PATH=`pwd`
				 	
clean:
	find . -name "*.out" -exec rm -rf {} \;

		  
          				 