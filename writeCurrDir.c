#include "my_ls.h"

void writeCurrDir(entryList* sortedList_, int instruction){
    entryList* sortedList_Cpy = sortedList_;
    while(sortedList_!= NULL){
        if((instruction == 0) || sortedList_->path[0] != '.') {
            printf("%s\n",sortedList_->path);
        }
        sortedList_ = sortedList_->next;
    }
    cleanUp(sortedList_Cpy);
}