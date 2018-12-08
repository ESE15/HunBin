#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define prototypeFileName "../prototype.txt"
#define MakeFileName "Makefile"
#define SUCCESS 1
#define FAIL 0

char buffer[255];


int ScriptMakefile( void ){
    int returnValue = FAIL;
    int headerNameIndex = 0;
    int libNameMacroIndex = 0;
    
    FILE* pPrototype = NULL;
    FILE* pMakeFile = NULL;
    
    char* libName;
    char* headerName[255];
    char* tempPtr;
    char libNameMacroTmp[255];
    
    if ( ( pMakeFile = fopen(MakeFileName,"w") ) == NULL ){
        perror("cannot create Makefile");
    }
    
    fputs("CC=gcc\nCFLAGS=-Wall\n",pMakeFile);
    
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
            sprintf(libNameMacroTmp,"OUTPUT=%s\n",libName);
            fputs(libNameMacroTmp,pMakeFile);
            
            tempPtr = strtok(NULL,":");
            sprintf(libNameMacroTmp,"OBJS=%s\n",tempPtr);
            fputs(libNameMacroTmp,pMakeFile);
            
            fputs("INCLUDE=-I../include\nall : $(OBJS) $(OUTPUT)\n",pMakeFile);
            fputs("$(OUTPUT): $(OBJS)\n\tar rv $(OUTPUT) $(OBJS)\n",pMakeFile);
            fputs("%.o: %.c ../include/%.h\n\t$(CC) -c $(CFLAGS) $< $(INCLUDE) -o $@\n",pMakeFile);
            fputs("clean:\n\trm -f $(OBJS) $(OUTPUT)",pMakeFile);
            while( (tempPtr = strtok(NULL,",")) != NULL ){
                headerName[headerNameIndex] = tempPtr;
                headerNameIndex++;
            }
        }
        
        //printf("%s %s %s\n",libName,headerName[0],headerName[1]);
    }
    fclose(pPrototype);
    fclose(pMakeFile);
    return returnValue;
}

int main( void ){
    ScriptMakefile();
    return 0;
}
