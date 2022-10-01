#include "my_ls.h"

int countEntries(entryList* head){
    int fileCount = 0;
    while(head != NULL){
        fileCount++;
        head = head->next;
    }
    return fileCount;
}