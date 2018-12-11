#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "YB_SCRIPT.h"

#define aFileName "libmyfuncs.a"
#define prototypeFileName "../dependencies.txt"
#define MakeFileName "Makefile"
#define MainMakeFileName "../src/Makefile"
#define WholeMakeFileName "../Makefile"
#define INCLUDE_PATH "../include/"
#define SUCCESS 1
#define FAIL 0

char buffer[255];

char* parseObjectName(char ** pHeaderName,int headerCnt,int flag){
    char temp[255];
    char *temp2;
    static char tempHeaderName[255];
    //printf("%d\n",headerCnt);
    if (flag == 1){
        for (int i = 0; i < headerCnt; i++){
            strtok(pHeaderName[i],".");
            strcat(pHeaderName[i],".o");
            //printf("%s\n",pHeaderName[i]);
        }
    
        for (int i = 0;i < headerCnt-1; i++){
            memset(temp,0,255);
            sprintf(temp," %s",pHeaderName[i+1]);
            strcat(pHeaderName[0],temp);
        }
        //printf("OBJS = %s\n",pHeaderName[0]);
    }
    else if (flag == 0){
        strcpy(tempHeaderName,pHeaderName[0]);
        for (int i = 0;i < headerCnt-1; i++){
            memset(temp,0,255);
            sprintf(temp," %s",pHeaderName[i+1]);
            strcat(tempHeaderName,temp);
        }
        //printf("header list = %s\n",tempHeaderName);
    }
    return tempHeaderName;
}


int ScriptMakefile(char* path){
    int returnValue = FAIL;
    int headerNameIndex = 0;
    int cFileNameIndex = 0;
    int srcHeaderNameIndex = 0;
    
    FILE* pPrototype = NULL;
    FILE* pMakeFile = NULL;
    FILE* pMainMakeFile = NULL;
    FILE* pWholeMakeFile = NULL;
    
    char* path;
    char* Headerlist;
    char* srcHeaderlist;
    char* headerName[255];
    char* tempHeaderName[255];
    char ObjectName[255];
    char* cFileName[255];
    char* tempPtr;
    char libNameMacroTmp[255];
    char* srcHeaderName[255];
    
    char srcPath[255];
    char includePath[255];
    char libPath[255];
    
    srtcat(srcPath,"/src/Makefile");
    srtcat(includePath,"/include/Makefile");
    strcat(libPath,"/lib/Makefile");
    tempPtr = path;
    strcat(path,"Makefile");
    if ( ( pMainMakeFile = fopen(srcPath,"w") ) == NULL ){
        perror("cannot create Main Makefile\n");
        exit(1);
    }
    
    if ( ( pMakeFile = fopen(libPath,"w") ) == NULL ){
        perror("cannot create Makefile\n");
        exit(1);
    }
    
    if( (pWholeMakeFile = fopen(path,"w")) == NULL ){
        perror("cannot create Makefile\n");
        exit(1);
    }
    
    if ( ( pPrototype = fopen(tempPtr,"r") ) == NULL ){
        tempPtr = NULL;
        perror("cannot find prototype file");
    }
    else{
        //initialize buffer
        memset(buffer,0,sizeof(buffer)*sizeof(char));
        
        //read string from file
        while(fgets(buffer,(int)sizeof(buffer),pPrototype)){
            if(buffer[strlen(buffer)-1] == '\n'){
                buffer[strlen(buffer)-1] = '\0';
            }
            tempPtr = buffer;
            strtok(tempPtr,",");
            path = tempPtr;
            //printf("path : %s\n",path);
            if (strcmp(path,"src")==0){
                tempPtr = strtok(NULL,",");
                cFileName[cFileNameIndex++] = tempPtr;
                while( (tempPtr = strtok(NULL,",")) != NULL ){
                    srcHeaderName[srcHeaderNameIndex] = malloc(strlen(tempPtr));
                    strcpy(srcHeaderName[srcHeaderNameIndex],tempPtr);
                    srcHeaderNameIndex++;
                    //printf("src dir headerfile : %s\n",tempPtr);
                }
            }
            else{
                tempPtr = strtok(NULL,",");
                cFileName[cFileNameIndex] = tempPtr;
                cFileNameIndex++;
                while( (tempPtr = strtok(NULL,",")) != NULL ){
                    headerName[headerNameIndex] = malloc(strlen(tempPtr));
                    strcpy(headerName[headerNameIndex],tempPtr);
                    headerNameIndex++;
                    //printf("lib headername : %s\n",headerName[headerNameIndex-1]);
                }
            }
        }
    }

    memcpy(tempHeaderName,headerName,sizeof(char*)*255);
    Headerlist = parseObjectName(tempHeaderName,headerNameIndex,0);
    /* script main Makefile*/
    fputs("CC=gcc\nINCLUDE=-I../include\nLIB=-L../lib\nLIBNAME=-lmyfuncs\nOBJS=main.o\nOUTPUT=main\nCFLAGS=-Wall\nHEADERS=",pMainMakeFile);
    
    fputs(Headerlist,pMainMakeFile);
    fputs("\n\n",pMainMakeFile);
          
    fputs("all : $(OUTPUT)\n\n$(OUTPUT):$(OBJS)\n\t$(CC) -o $(OUTPUT) $(OBJS) $(LIB) -lmyfuncs\n\n%.o: %.c ",pMainMakeFile);
    
    for (int i = 0;i<headerNameIndex; i++){
        fprintf(pMainMakeFile,"../include/%s ",headerName[i]);
    }
    for (int i = 0; i < srcHeaderNameIndex; i++){
        fprintf(pMainMakeFile,"../include/%s ",srcHeaderName[i]);
    }
    fprintf(pMainMakeFile,"\n");
    fputs("\t$(CC) -c $(CFLAGS) $< $(INCLUDE) -o $@\n\nclean:\n",pMainMakeFile);
    fputs("\t rm -f $(OUTPUT) $(OBJS)",pMainMakeFile);
    
    
    /* script whole Makefile*/
    fputs("DIRS=lib src\n.PHONY: all clean\nMAKE=make\nall:\n\t@for d in $(DIRS);\\\n\tdo\\\n\t\t$(MAKE) -C $$d;\\\n\tdone\n\nclean:\n\t@for d in $(DIRS);\\\n\tdo\\\n\t\t$(MAKE) -C $$d clean;\\\n\tdone",pWholeMakeFile);
    
    
    memcpy(tempHeaderName,headerName,sizeof(char*)*255);
    parseObjectName(tempHeaderName,headerNameIndex,1);
    /* script lib Makefile*/
    fputs("CC=gcc\nCFLAGS=-Wall\nOUTPUT=libmyfuncs.a\nINCLUDE=-I../include\n",pMakeFile);
    fprintf(pMakeFile,"OBJS=%s\n",tempHeaderName[0]);
    fputs("all : $(OBJS) $(OUTPUT)\n\n$(OUTPUT): $(OBJS)\n\tar rv $(OUTPUT) $(OBJS)\n\n",pMakeFile);
    fputs("%.o: %.c ../include/%.h\n\t$(CC) -c $(CFLAGS) $< $(INCLUDE) -o $@\n\n",pMakeFile);
    fputs("clean:\n\trm -f $(OBJS) $(OUTPUT)\n",pMakeFile);
    
    fclose(pPrototype);
    fclose(pMakeFile);
    fclose(pMainMakeFile);
    returnValue = SUCCESS;
    return returnValue;
}
