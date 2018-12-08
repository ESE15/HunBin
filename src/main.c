#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "JH_SEARCH.h"
//#include "YB_SCRIPT.h"

int main(int argc, char *argv[]){

	extern char *optarg;
	extern int optind;
	int num;
	// arg parsing
	while( (num = getopt(argc, argv, "o:d:")) != -1){
		// -1 means getopt() parsed all options
		switch (num){
			case 'o':
				// fopen name by after -o
				break;
			case 'd':
				// do search
				SearchDependencies(optarg, 0);
				printf("main : optarg = %s \n",optarg);
				break;
			case '?':
				printf("Unknown Parameter : %c\n", optopt);
				break;
		}
	}


	// do script
	// YB's code here

	return 0;
}
