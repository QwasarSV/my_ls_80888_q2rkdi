#include "my_ls.h"
entryList* removeNode(entryList* head, entryList* node){
    entryList* curr = head;
    entryList* prev = NULL;

    while(head != NULL){
        if(curr == node){
            if(prev == NULL){
                entryList* temp = head;
                head = head->next;
                temp->next = NULL;
                free(temp);
                break;
            }else{
                prev->next = curr->next;
                curr->next = NULL;
                free(curr);
                break;
            }
        }
        prev = curr;
        curr = curr->next;
    }
    return head;
}