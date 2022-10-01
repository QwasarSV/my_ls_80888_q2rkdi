#include "my_ls.h"

void writeFiles(entryList* orderedList, int instruction){
    struct dirent* entry;
    entryList* orderedListCpy = orderedList;
    entryList* orderedListCpy2 = orderedList;

    while(orderedList != NULL){
        // printf("%s...%lu\n",orderedList->path,orderedList->sb->st_mtimespec.tv_sec);
        struct stat* statBuff = malloc(sizeof(struct stat));
        char* path = orderedList->path;
        stat(path, statBuff);
        if(S_ISREG(statBuff->st_mode)){
            printf("%s\n", path);
        }
        orderedList = orderedList->next;
    }
    while(orderedListCpy != NULL){
        struct stat* statBuff = malloc(sizeof(struct stat));
        char* path = orderedListCpy->path;
        stat(path, statBuff);
        if(S_ISDIR(statBuff->st_mode)){
            DIR* dir = opendir(orderedListCpy->path);
            printf("\n%s:\n",orderedListCpy->path);
            while((entry = readdir(dir)) != NULL){
                if(instruction == 2 || instruction == 3){
                    if(entry->d_name[0] == '.'){
                        continue;    
                    }
                }
                printf("%s\n",entry->d_name);
            }
            closedir(dir);
        }
        orderedListCpy = orderedListCpy->next;
    }
    cleanUp(orderedListCpy2);
}