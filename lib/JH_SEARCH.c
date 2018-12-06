#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "JH_SEARCH.h"

DIR *dirPointer;
struct dirent *dp;
struct dirent *include;
struct dirent *library;
struct dirent *src;
struct stat statBuffer;
int fileStat;

int SearchDependencies(char *dir){
	

	// open Directory ( Project directory )
	dirPointer = opendir(dir);
	if(dirPointer == NULL){
		perror("opendir");
		exit(0);
	}

	// read Directory ( Porject directory)
	while((dp = readdir(dirPointer))!= NULL){
		if(dp==NULL){
			break;
		}
		printf(" JH_SEARCH.c 's 32 Line \n");
		printf(" now directory is %s \n",dir);
		fileStat = stat(dp->d_name, &statBuffer);
		//if(fileStat==-1){
		//	perror("stat");
		//	exit(0);
		//}
		//if( (statBuffer.st_mode & S_IFMT) == S_IFREG){
		//}
		if( (statBuffer.st_mode & S_IFMT) == S_IFDIR){
			// check if there are reserved directories
			// and search(cat) files for extracting header
			if(strcmp(dp->d_name, "include") == 0){ // found include directory
				// do some
				//SearchInclude(dp->d_name);
				printf("%s \n",dp->d_name);
			} 
			else if (strcmp(dp->d_name, "lib") == 0) { // found lib directory
				printf("%s \n",dp->d_name);
				// do some
			} 
			else if (strcmp(dp->d_name, "src") == 0){ // found src directory
				// do some
				printf("%s\n",dp->d_name);
			}
		}
		//else if( (statBuffer.st_mode & S_IFMT) == S_IFLNK){
		//}
	}

	// return status  0: error , 1 : done
	return 1;
}


