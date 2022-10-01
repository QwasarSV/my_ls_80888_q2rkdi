#include "my_ls.h"

void cleanUp(entryList* finalList){
    while(finalList != NULL){
        entryList* temp = finalList;
        finalList = finalList->next;
        temp->next = NULL;
        temp->path = NULL;
        temp->sb = NULL;
        free(temp);
    }
}