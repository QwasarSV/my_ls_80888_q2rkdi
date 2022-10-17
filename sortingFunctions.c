#include "my_ls.h"

bool lex_cmp(file_list* curr_node, file_list* next_node){
    int res = strcmp(curr_node->pathname,next_node->pathname);
    if(res > 0){
        return true;
    }
    return false;
}

bool time_cmp(file_list* curr_node, file_list* next_node){
    if(curr_node->sb->st_ctimespec.tv_sec == next_node->sb->st_ctimespec.tv_sec){
        if(curr_node->sb->st_ctimespec.tv_nsec == next_node->sb->st_ctimespec.tv_nsec){
            return lex_cmp(curr_node, next_node);
        }
        return curr_node->sb->st_ctimespec.tv_nsec < next_node->sb->st_ctimespec.tv_nsec;
    }
    return curr_node->sb->st_ctimespec.tv_sec < next_node->sb->st_ctimespec.tv_sec;
}

void sorter(file_list** sorted_head, file_list* new_node,bool (*cmp)(file_list*,file_list*)){
    if(*sorted_head == NULL){
        *sorted_head = new_node;
    }
    else if( cmp((*sorted_head),new_node)){
        new_node->next = *sorted_head;
        new_node->next->prev = new_node;
        *sorted_head = new_node;
    }
    else{
        file_list* current = *sorted_head;
        while(current->next != NULL && !cmp((current->next),new_node)){
            current = current->next;
        }
        new_node->next = current->next;
        if(current->next != NULL){
            new_node->next->prev = new_node;
        }
        current->next = new_node;
        new_node->prev = current;
    }
}

void insertionSort(file_list** head_ptr, bool (*cmp)(file_list*, file_list*)){
    file_list* sorted = NULL;
    file_list* current = * head_ptr;
    while(current != NULL){
        file_list* next = current->next;
        current->prev = current->next = NULL;
        sorter(&sorted,current,cmp);
        current = next;
    }
    *head_ptr = sorted;
}
