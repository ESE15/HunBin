#ifndef JH_SEARCH_H
#define JH_SEARCH_H
int SearchDependencies(char *dir);
int searchSubDir(char *dir, char subPath);
int strFromStr(char *destStr, char *originStr, char * startStr, char *endStr, int startIdx);
#endif
