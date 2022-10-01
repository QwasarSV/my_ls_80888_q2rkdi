#include "my_ls.h"
entryList* lexSortedList(entryList* enLis){
    entryList* sortedList = malloc(sizeof(entryList));
    entryList* sortedListCpy = NULL;
    entryList* nextInLine = NULL;
    entryList* newNode = NULL;

    int index = 0;
    int length = countEntries(enLis);
    while(index < length){
        nextInLine = lexSort(enLis);
        newNode = createNodeEnt(nextInLine->sb,nextInLine->path);
        if(index == 0){
            sortedList = newNode;
            sortedListCpy = sortedList;
        }else{
            sortedList->next = newNode;
            sortedList = sortedList->next;
        }
        enLis = removeNode(enLis, nextInLine);
        index++;
    }
    sortedList = sortedList->next;
    free(sortedList);
    return sortedListCpy;
}