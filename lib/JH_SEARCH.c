#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
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
		change_dir = chdir(dir);
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
				searchSubDir((char *)get_current_dir_name(), 'i');
			} 
			else if (strcmp(dp->d_name, "lib") == 0) { // found lib directory
				// do some
				searchSubDir((char *)get_current_dir_name(), 'l');
			} 
			else if (strcmp(dp->d_name, "src") == 0){ // found src directory
				// do some
				searchSubDir((char *)get_current_dir_name(), 's');
			}
		}
	}
	
	// return status  0: error , 1 : done
	return 1;
}

int searchSubDir(char *dir, char subPath){
	int status;
	int fileStat;
	int change_dir;
	int prjFd;
	int sourceFSize;
	char *prjDir= dir;
	char *fileBuffer;
	char curDir[255]={0, };
	FILE *sourceFp;
	DIR *dirPointer;
    struct dirent *dp;
    struct stat statBuffer;


	prjFd = open(prjDir, O_WRONLY|O_APPEND|O_CREAT, 0666);
	strcat(curDir, dir);
	
	switch(subPath){
		case 'i':
			printf("Searching include directory! \n");
			strcat(curDir, "/include");
			status =1;
			break;
		case 'l':
			printf("Searching library directory! \n");
			strcat(curDir, "/lib");
			status =2;
			break;
		case 's':
			printf("Searching source  directory! \n");
			strcat(curDir, "/src");
			status =3;
			break;
	}

	//hint : cat JH_SEARCH.c | grep ".h\""

	if(status==2){ //  lib directory
		dirPointer = opendir(curDir);
		if(dirPointer == NULL){
			perror("opendir");
			exit(0);
		}
		change_dir = chdir(curDir);
		
		while( dp = readdir(dirPointer)){
			if(dp == NULL){
				break;
			}
			fileStat = stat(dp->d_name, &statBuffer);
			if( (statBuffer.st_mode & S_IFMT) == S_IFREG){
				if( strstr(dp->d_name, ".c") != NULL ){ // found source file
					sourceFp = fopen(dp->d_name, "r");
					fseek(sourceFp, 0, SEEK_END);
					sourceFSize = ftell(sourceFp);
					fileBuffer = (char *)malloc(sourceFSize+1);
					memset(fileBuffer, 0, sourceFSize+1);
					fseek(sourceFp, 0, SEEK_SET);
					fread(fileBuffer, sourceFSize, 1,sourceFp);
					printf("%s\n", fileBuffer);
				}
			}

		}

	} 
	else if(status==3){ // src directory
	}

	return 0;
}

int strFromStr(char *destStr, char *originStr, char * startStr, char *endStr, int startIdx){

	int temp=0, temp2=0;
	int len = strlen(originStr), len2 = strlen(startStr);
	int i, j;

	for(i = startIdx, j=0; i<len; i++){
		if(originStr[i] == startStr[j]){
			j++;
			if(j==len2){
				temp= i+1;
				break;
			}
		}
		else{
			j=0;
		}
	}

	if(temp==0){
		return 0;
	}
	len = strlen(originStr);
	len2 = strlen(endStr);

	for(i=startIdx, j=0; i<len; i++){
		if(originStr[i] == endStr[j]){
			j++;
			if(j==len2){
				temp2 = i-len2;
				break;
			}
		}
		else{
			j=0;
		}
	}
	if(temp2==0){
		return 0;
	}

	for(i=temp;i<=temp2;i++){
		destStr[i-temp] = originStr[i];
	}
	destStr[i-temp] = '\0';

	return 1;
}
