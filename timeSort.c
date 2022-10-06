#include "my_ls.h"
entryList* timeSort(entryList* list){
    entryList* nextInLine = list;

    list = list->next;

    while(list != NULL){
        if(list->sb->st_mtim.tv_sec > nextInLine->sb->st_mtim.tv_sec){
            nextInLine = list;
        }
        else if (list->sb->st_mtim.tv_sec == nextInLine->sb->st_mtim.tv_sec) {
            if (list->sb->st_mtim.tv_nsec > nextInLine->sb->st_mtim.tv_nsec) {
                nextInLine = list;
            }
            else if (list->sb->st_mtim.tv_nsec == nextInLine->sb->st_mtim.tv_nsec) {
                if(my_strcmp(list->path, nextInLine->path) < 0) {
                    nextInLine = list;
                }
            }
        }
        list = list->next;
    }
    return nextInLine; 
}