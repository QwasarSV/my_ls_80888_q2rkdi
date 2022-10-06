#ifndef MY_LS
#define MY_LS

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <dirent.h>

typedef struct s_entryList{
    struct stat* sb;
    char* path;
    struct s_entryList* next;
}entryList;


int my_strcmp(char* str1, char* str2);
int countEntries(entryList* head);
entryList* createNodeEnt(struct stat* sb, char* path);
entryList* removeNode(entryList* head, entryList* node);
entryList* lexSort(entryList* head);
entryList* getFiles(char** files, int ac, int startingIndex);
entryList* lexSortedList(entryList* enLis);
void writeFiles(entryList* orderedList, int instruction);
int readInput(int ac, ...);
void getFlags(char** argv, int* instruction, int* startingIndex);
entryList* timeSort(entryList* head);
entryList* timeSortedList(entryList* enLis);
entryList* readCurrDir();
void writeCurrDir(entryList* sortedList_, int instruction);
void cleanUp(entryList* finalList);
#endif