#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define prototypeFileName "../prototype.txt"
#define MakeFileName "../Makefile"
#define SUCCESS 1
#define FAIL 0

char buffer[255];


int ScriptMakefile( void ){
    int returnValue = FAIL;
    int headerNameIndex = 0;
    
    FILE* pPrototype = NULL;
    FILE* pMakeFile = NULL;
    
    char* libName;
    char* headerName[255];
    char* tempPtr;
    
    if ( ( pPrototype = fopen(prototypeFileName,"r") ) == NULL ){
        perror("cannot find prototype file");
    }
    else{
        //initialize buffer
        memset(buffer,0,sizeof(buffer)*sizeof(char));
        
        //read string from file
        while(fgets(buffer,(int)sizeof(buffer),pPrototype)){
            tempPtr = buffer;
            strtok(tempPtr,":");
            libName = tempPtr;
            while( (tempPtr = strtok(NULL,",")) != NULL ){
                headerName[headerNameIndex++] = tempPtr;
            }
        }
        
        if ( ( pMakeFile = fopen(MakeFileName,"w") ) == NULL ){
            perror("cannot create make file");
        }
        //fputs func here
        
        //printf("%s %s %s\n",libName,headerName[0],headerName[1]);
    }
    return returnValue;
}

int main( void ){
    ScriptMakefile();
    return 0;
}
