#include "my_ls.h"

void writeCurrDir(entryList* sortedList_, int instruction){
    entryList* sortedList_Cpy = sortedList_;
    if(instruction){};
    while(sortedList_!= NULL){
        if(instruction == 0 && sortedList_->path[0] == '.'){
            sortedList_ = sortedList_->next;
        }else{
        printf("%s\n",sortedList_->path);
        sortedList_ = sortedList_->next;
        }
    }
    cleanUp(sortedList_Cpy);
}