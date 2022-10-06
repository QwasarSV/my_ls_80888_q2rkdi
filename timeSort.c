#include "my_ls.h"
#include <string.h>


#ifdef __APPLE__
# define MTIME st_mtimespec
#else
# define MTIME st_mtim
#endif

entryList* timeSort(entryList* list){
    entryList* nextInLine = list;

    list = list->next;

    while(list != NULL){
        if(list->sb->MTIME.tv_sec > nextInLine->sb->MTIME.tv_sec){
            nextInLine = list;
        }
        else if (list->sb->MTIME.tv_sec == nextInLine->sb->MTIME.tv_sec) {
            if (list->sb->MTIME.tv_nsec > nextInLine->sb->MTIME.tv_nsec) {
                nextInLine = list;
            }
            else if (list->sb->MTIME.tv_nsec == nextInLine->sb->MTIME.tv_nsec) {
                if(strcmp(list->path, nextInLine->path) < 0) {
                    nextInLine = list;
                }
            }
        }
        list = list->next;
    }
    return nextInLine; 
}