#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "JH_SEARCH.h"



// Recursive Function
int SearchDependencies(char *dir, char D){
	DIR *dirPointer;
	struct dirent *dp;
	struct stat statBuffer;
	int fileStat;
	int change_dir;
	char dirString[255];

	if(D == 0){
	    printf("first \n");
	}
	else if(D=='i'){
	    printf("i\n");
	}
	else if(D=='l'){
	    printf("l\n");
	}
	else if(D=='s'){
	    printf("s\n");
    }

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
		if(D == 0){
			if( (statBuffer.st_mode & S_IFMT) == S_IFDIR){
				// check if there are reserved directories
				// and search(cat) files for extracting header
				if(strcmp(dp->d_name, "include") == 0){ // found include directory
					// do some
					//searchSubDir(get_current_dir_name(), 'i');
					strcat(dirString, get_current_dir_name());
					SearchDependencies(strcat( dirString,dp->d_name), 'i');
				} 
				else if (strcmp(dp->d_name, "lib") == 0) { // found lib directory
					// do some
					//searchSubDir(get_current_dir_name(), 'l');
					strcat(dirString, get_current_dir_name());
					SearchDependencies(strcat( dirString,dp->d_name), 'l');
				} 
				else if (strcmp(dp->d_name, "src") == 0){ // found src directory
					// do some
					//searchSubDir(get_current_dir_name(), 's');
					strcat(dirString, get_current_dir_name());
					SearchDependencies(strcat( dirString,dp->d_name), 's');
				}
			}
		}
		else if(D == 'i'){
			printf(" Searcing include dir! \n");
		}
		else if(D == 'l'){
			printf(" Searcing lib dir! \n");
		}
		else if(D == 's'){
			printf(" Searcing src dir! \n");
		}
	}

	// return status  0: error , 1 : done
	return 1;
}

int searchSubDir(char *dir, char subPath){
	int status;
	switch(subPath){
		case 'i':
			printf("Searching include directory! \n");
			status =1;
			break;
		case 'l':
			printf("Searching library directory! \n");
			status =2;
			break;
		case 's':
			printf("Searching source  directory! \n");
			status =3;
			break;
	}
}
