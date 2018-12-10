#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "YB_SCRIPT.h"

#define aFileName "libmyfuncs.a"
#define prototypeFileName "../prototype.txt"
#define MakeFileName "Makefile"
#define MainMakeFileName "../src/Makefile"
#define WholeMakeFileName "../Makefile"
#define INCLUDE_PATH "../include/"
#define SUCCESS 1
#define FAIL 0

char buffer[255];

void parseObjectName(char ** pHeaderName,int headerCnt,int flag){
    char temp[255];
    char *temp2;
    char * tempHeaderName[255];
    memcpy(tempHeaderName,pHeaderName,sizeof(char*)*255);
    printf("%d\n",headerCnt);
    if (flag == 1){
        for (int i = 0; i < headerCnt; i++){
            strtok(pHeaderName[i],".");
            strcat(pHeaderName[i],".o");
            printf("%s\n",pHeaderName[i]);
        }
    
        for (int i = 0;i < headerCnt-1; i++){
            memset(temp,0,255);
            sprintf(temp," %s",pHeaderName[i+1]);
            strcat(pHeaderName[0],temp);
        }
    }
    else if (flag == 0){
        for (int i = 0;i < headerCnt-1; i++){
            memset(temp,0,255);
            sprintf(temp," %s",pHeaderName[i+1]);
            strcat(pHeaderName[0],temp);
        }
    }
    else if (flag == 2){
        for (int i = 0; i < headerCnt; i++){
            temp2 = pHeaderName[i];
            sprintf(tempHeaderName[i],"%s%s",INCLUDE_PATH,temp2);
            printf("%s\n",tempHeaderName[i]);
        }
        
        for (int i = 0;i < headerCnt-1; i++){
            memset(temp,0,255);
            sprintf(temp," %s",tempHeaderName[i+1]);
            strcat(tempHeaderName[0],temp);
        }
        memcpy(pHeaderName,tempHeaderName,sizeof(char*)*255);
        //printf("%s\n",pHeaderName[0]);
    }
}


int ScriptMakefile( void ){
    int returnValue = FAIL;
    int headerNameIndex = 0;
    int cFileNameIndex = 0;
    
    FILE* pPrototype = NULL;
    FILE* pMakeFile = NULL;
    FILE* pMainMakeFile = NULL;
    FILE* pWholeMakeFile = NULL;
    
    char* path;
    char* libName;
    char* headerName[255];
    char* tempHeaderName[255];
    char ObjectName[255];
    char* cFileName[255];
    char* tempPtr;
    char libNameMacroTmp[255];
    
    if ( ( pMainMakeFile = fopen(MainMakeFileName,"w") ) == NULL ){
        perror("cannot create Main Makefile\n");
        exit(1);
    }
    
    if ( ( pMakeFile = fopen(MakeFileName,"w") ) == NULL ){
        perror("cannot create Makefile\n");
        exit(1);
    }
    
    if( (pWholeMakeFile = fopen(WholeMakeFileName,"w")) == NULL ){
        perror("cannot create Makefile\n");
        exit(1);
    }
    
    if ( ( pPrototype = fopen(prototypeFileName,"r") ) == NULL ){
        perror("cannot find prototype file");
    }
    else{
        //initialize buffer
        memset(buffer,0,sizeof(buffer)*sizeof(char));
        
        //read string from file
        while(fgets(buffer,(int)sizeof(buffer),pPrototype)){
            tempPtr = buffer;
            strtok(tempPtr,",");
            path = tempPtr;
            
            tempPtr = strtok(NULL,",");
            cFileName[cFileNameIndex] = tempPtr;
            while( (tempPtr = strtok(NULL,",")) != NULL ){
                headerName[headerNameIndex] = tempPtr;
                headerNameIndex++;
            }
        }
    }
    //memcpy(tempHeaderName,headerName,sizeof(char*)*255);
    //parseObjectName(tempHeaderName,headerNameIndex,0);
    
    /* script main Makefile*/
    fputs("CC=gcc\nINCLUDE=-I../include\nLIB=-L../lib\nLIBNAME=-lmyfunc\nOBJS=main.o\nOUTPUT=main\nCFLAGS=-Wall\nHEADERS=",pMainMakeFile);
    
    fputs(tempHeaderName[0],pMainMakeFile);
    fputs("\n\n",pMainMakeFile);
          
    fputs("all : $(OUTPUT)\n\n$(OUTPUT):$(OBJS)\n\t$(CC) -o $(OUTPUT) $(OBJS) $(LIB) -lmyfuncs\n\n",pMainMakeFile);
    
    memcpy(tempHeaderName,headerName,sizeof(char*)*255);
    parseObjectName(tempHeaderName,headerNameIndex,2);
    
    /* script whole Makefile*/
    fputs("DIRS=lib src\n.PHONY: all clean\nMAKE=make\nall:\n\t@for d in $(DIRS);\\\n\tdo\\\n\t\t$(MAKE) -C $$d;\\\n\tdone\n\nclean:\n\t@for d in $(DIRS);\\\n\tdo\\\n\t\t$(MAKE) -C $$d clean;\\\n\tdone",pWholeMakeFile);
    
    //memcpy(tempHeaderName,headerName,sizeof(char*)*255);
    //parseObjectName(tempHeaderName,headerNameIndex,1);
    /* script lib Makefile*/
    fputs("CC=gcc\nCFLAGS=-Wall\nOUTPUT=libmyfunc.a\nINCLUDE=-I../include\n",pMakeFile);
    fputs("OBJS ~~~~\n\n",pMakeFile);
    fputs("all : $(OBJS) $(OUTPUT)\n\n$(OUTPUT): $(OBJS)\n\tar rv $(OUTPUT) $(OBJS)\n\n",pMakeFile);
    fputs("%.o: %.c ../include/%.h\n\t$(CC) -c $(CFLAGS) $< $(INCLUDE) -o $@\n\n",pMakeFile);
    fputs("clean:\n\trm -f $(OBJS) $(OUTPUT)\n",pMakeFile);
    
    fclose(pPrototype);
    fclose(pMakeFile);
    fclose(pMainMakeFile);
    returnValue = SUCCESS;
    return returnValue;
}

int main( void ){
    ScriptMakefile();
    return 0;
}
