#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "JH_SEARCH.h"



// Recursive Function
int SearchDependencies(char *dir){
	DIR *dirPointer;
	struct dirent *dp;
	struct stat statBuffer;
	int fileStat;
	int change_dir;

	// open Directory ( Project directory )
	dirPointer = opendir(dir);
	if(dirPointer == NULL){
		perror("opendir");
		exit(0);
	}
	// Change current directory to working directory
	// It's NECESSARY
	change_dir = chdir(dir);

	// read Directory ( Porject directory)
	while((dp = readdir(dirPointer))!= NULL){
		if(dp==NULL){
			break;
		}

		fileStat = stat(dp->d_name, &statBuffer);
		if(fileStat==-1){
			perror("stat");
			exit(0);
		}
		if( (statBuffer.st_mode & S_IFMT) == S_IFDIR){
			// check if there are reserved directories
			// and search(cat) files for extracting header
			if(strcmp(dp->d_name, "include") == 0){ // found include directory
				// do some
				searchSubDir(get_current_dir_name(), 'i');
			} 
			else if (strcmp(dp->d_name, "lib") == 0) { // found lib directory
				// do some
				searchSubDir(get_current_dir_name(), 'l');
			} 
			else if (strcmp(dp->d_name, "src") == 0){ // found src directory
				// do some
				searchSubDir(get_current_dir_name(), 's');
			}
		}
	}
	
	// return status  0: error , 1 : done
	return 1;
}

int searchSubDir(char *dir, char subPath){
	int status;
	char curDir[255]={0, };
	strcat(curDir, dir);

	switch(subPath){
		case 'i':
			printf("Searching include directory! \n");
			printf("%s\n", strcat(curDir, "/include"));
			status =1;
			break;
		case 'l':
			printf("Searching library directory! \n");
			printf("%s\n", strcat(curDir, "/lib"));
			status =2;
			break;
		case 's':
			printf("Searching source  directory! \n");
			printf("%s\n", strcat(curDir, "/src"));
			status =3;
			break;
	}

	return 0;
}
