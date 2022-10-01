#include "my_ls.h"
entryList* timeSort(entryList* head){
    struct stat* statBuff = malloc(sizeof(struct stat));
    char* path = head->path;
    stat(path, statBuff);

    entryList* nextInLine = head;
    nextInLine->sb = statBuff;

    head = head->next;

    while(head != NULL){
        statBuff = malloc(sizeof(struct stat));
        path = head->path;
        stat(path, statBuff);

        if(statBuff->st_mtim.tv_sec > nextInLine->sb->st_mtim.tv_sec){
            nextInLine = head;
        }else if(statBuff->st_mtim.tv_sec == nextInLine->sb->st_mtim.tv_sec){
            if(statBuff->st_mtim.tv_nsec > nextInLine->sb->st_mtim.tv_nsec){
                nextInLine = head;
            }
        }
        head = head->next;
    }
    return nextInLine; 
}