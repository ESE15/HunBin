#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define prototypeFileName "prototype.txt"

char buffer[255];

int ScriptMakefile( void ){
    FILE* pPrototype = NULL;
    FILE* pMakeFile = NULL;
    
    char libName[30];
    char* headerName[255];
    
    if ( fopen(prototypeFileName,"r") == NULL ){
        perror("cannot find prototype file\n");
        exit(1);
    }
    
    memset(buffer,"\0",sizeof(buffer)*sizeof(char));
    
    while(fgets(buffer,pPrototype)){
        
    }
    
}
