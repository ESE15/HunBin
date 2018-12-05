#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define prototypeFileName "../prototype.txt"
#define Success 1
#define Fail 0

char buffer[255];

int ScriptMakefile( void ){
    int returnValue = Fail;
    FILE* pPrototype = NULL;
    FILE* pMakeFile = NULL;
    
    char* libname;
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
            printf("%s",buffer);
        }
        
    }
    return returnValue;
}

int main( void ){
    ScriptMakefile();
    return 0;
}
