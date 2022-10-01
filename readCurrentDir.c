#include "my_ls.h"

entryList* readCurrDir(){
    DIR* directory = opendir(".");
    entryList* currDir;
    entryList* currDirCpy;
    struct dirent* entry = malloc(sizeof(struct dirent));
    int index = 0;
    while((entry = readdir(directory)) != NULL){
        char* path = entry->d_name;
        struct stat* statBuff = malloc(sizeof(struct stat));;
        stat(path, statBuff);
        if(index == 0){
            currDir = createNodeEnt(statBuff,path);
            currDirCpy = currDir;
        }else{
            currDir->next = createNodeEnt(statBuff,path);
            currDir = currDir->next;
        }
        index++;
    }
    // printf("hello\n");
    return currDirCpy;
}