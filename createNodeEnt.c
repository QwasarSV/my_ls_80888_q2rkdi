#include "my_ls.h"

entryList* createNodeEnt(struct stat* sb, char* path){
    entryList* newNode = malloc(sizeof(entryList));
    newNode->sb = sb;
    newNode->path = path;
    newNode->next = NULL;
    return newNode;
}