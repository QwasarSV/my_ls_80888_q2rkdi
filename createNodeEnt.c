#include "my_ls.h"
#include <string.h>

entryList* createNodeEnt(struct stat* sb, char* path){
    entryList* newNode = malloc(sizeof(entryList));
    newNode->sb = sb;
    newNode->path = strdup(path);
    newNode->next = NULL;
    return newNode;
}