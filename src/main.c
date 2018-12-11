#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "JH_SEARCH.h"
#include "YB_SCRIPT.h"

int main(int argc, char *argv[]){

	extern char *optarg;
	extern int optind;
	int num;
	char path[255];
	// arg parsing
	memset(path,0,255);
	while( (num = getopt(argc, argv, "o:d:")) != -1){
		// -1 means getopt() parsed all options
		switch (num){
			case 'o':
				// fopen name by after -o
				break;
			case 'd':
				// do search
				strcat(path, optarg);
				SearchDependencies(optarg);
				printf("main : optarg = %s \n",optarg);
				break;
			case '?':
				printf("Unknown Parameter : %c\n", optopt);
				break;
		}
	}

    ScriptMakefile();

	return 0;
}
