#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_list{
    int val;
    struct s_list* next;
    struct s_list* prev;
}list;

list* createNode(int val, list* prev){
    list* newNode = malloc(sizeof(list));
    newNode->val = val;
    newNode->next = NULL;
    newNode->prev = prev;
    return newNode;
}

list* makeList(int array[], int length){
    int i = 0;
    list* prev = NULL;
    list* head = NULL;
    list* list = NULL;
    while(i < length){
        if(head == NULL){
            list = createNode(array[i], prev);
            // prev=list;
            head = list;
        }else{
            prev=list;
            list->next = createNode(array[i],prev);
            list = list->next;
        }
        i++;
    }
    return head;
}

bool lex_cmp(char* curr_node, char* next_node){
    int res = strcmp(curr_node,next_node);
    if(res > 0){
        return true;
    }
    return false;
}

bool time_cmp(list* curr_node, list* next_node){
    return curr_node->val < next_node->val;
}

void sorter(list** sorted_head, list* new_node,bool (*cmp)(list*,list*)){
    if(*sorted_head == NULL){
        *sorted_head = new_node;
    }
    else if( cmp((*sorted_head), new_node) ){
        new_node->next = *sorted_head;
        new_node->next->prev = new_node;
        *sorted_head = new_node;
    }
    else{
        list* curr = *sorted_head;
        while(curr->next != NULL && !cmp(curr->next, new_node) ){
            curr = curr->next;
        }
        new_node->next = curr->next;
        if(curr->next != NULL){
            new_node->next->prev = new_node;
        }
        curr->next = new_node;
        new_node->prev = curr;
    }
}

void insertionSort(list** head_ptr, bool (*cmp)(list*, list*)){
    list* sorted_list = NULL;
    list* curr = *head_ptr;
    while(curr != NULL){
        list* next = curr->next;
        curr->prev = curr->next = NULL;

        sorter(&sorted_list, curr, cmp);

        curr = next;
    }
    *head_ptr = sorted_list;
}

void printList(list* head){
    printf("[");
    while(head != NULL){
        printf("%d", head->val);
        if(head->next != NULL){
            printf(",");
        }
        head = head->next;
    }
    printf("]\n\n");
}

int main(int ac, char** av){
    int array[] = {3,7,1,5,2,8};
    char* array[8] = {"list.c", "main.c", ".","great","zesty","Zsh","ash","main"};

    list* list = makeList(array,6);
    printf("Before Sorting:");
    printList(list);

    if(*av[1] == 't'){
    insertionSort(&list,&time_cmp);
    printf("After Sorting (descending):");
    printList(list);
    }
    else{
    insertionSort(&list, &lex_cmp);
    printf("After Sorting (ascending):");
    printList(list);
    }
    return 0;
}