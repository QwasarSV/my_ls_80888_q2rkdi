#include "my_ls.h"
#include <string.h>

entryList* lexSort(entryList* head){
    entryList* nextInLine = head;
    while(head != NULL){
        if(strcmp(head->path, nextInLine->path) < 0){
            nextInLine = head;
        }
        head = head->next;
    }
    return nextInLine; 
}