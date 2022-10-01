#include "my_ls.h"

void writeCurrDir(entryList* lexSortedList_){
    entryList* lexSortedList_Cpy = lexSortedList_;
    while(lexSortedList_!= NULL){
        printf("%s\n",lexSortedList_->path);
        lexSortedList_ = lexSortedList_->next;
    }
    cleanUp(lexSortedList_Cpy);
}