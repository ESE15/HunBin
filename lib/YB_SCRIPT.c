#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "YB_SCRIPT.h"

#define aFileName "libmyfunc.a"
#define prototypeFileName "../prototype.txt"
#define MakeFileName "Makefile"
#define MainMakeFileName "../src/Makefile"
#define SUCCESS 1
#define FAIL 0

char buffer[255];



int ScriptMakefile( void ){
    int returnValue = FAIL;
    int headerNameIndex = 0;
    int cFileNameIndex = 0;
    
    FILE* pPrototype = NULL;
    FILE* pMakeFile = NULL;
    FILE* pMainMakeFile = NULL;
    
    char* path;
    char* libName;
    char* headerName[255];
    char* cFileName[255];
    char* tempPtr;
    char libNameMacroTmp[255];
    
    if ( ( pMainMakeFile = fopen(MainMakeFileName,"w") ) == NULL ){
        perror("cannot create Main Makefile");
    }
    
    if ( ( pMakeFile = fopen(MakeFileName,"w") ) == NULL ){
        perror("cannot create Makefile");
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
    /* script lib Makefile*/
    fputs("CC=gcc\nCFLAGS=-Wall\nOUTPUT=libmyfunc.a\nINCLUDE=-I../include\n",pMakeFile);
    fputs("OBJS ~~~~\n",pMakeFile);
    fputs("$(OUTPUT): $(OBJS)\n\tar rv $(OUTPUT) $(OBJS)\n\n",pMakeFile);
    fputs("%.o: %.c ../include/%.h\n\t$(CC) -c $(CFLAGS) $< $(INCLUDE) -o $@\n\n",pMakeFile);
    fputs("clean:\n\trm -f $(OBJS) $(OUTPUT)\n",pMakeFile);
    
    fputs("CC=gcc\nINCLUDE=-I../include\nLIB=-L../lib\nLIBNAME=-lhunbin\nOBJS=main.o\nOUTPUT=main\nCFLAGS=-Wall\n\nall : $(OUTPUT)\n\n$(OUTPUT): $(OBJS)\n\t$(CC) -o $(OUTPUT) $(OBJS) $(LIB) $(LIBNAME)",pMainMakeFile);
    
    fclose(pPrototype);
    fclose(pMakeFile);
    fclose(pMainMakeFile);
    return returnValue;
}

int main( void ){
    ScriptMakefile();
    return 0;
}
