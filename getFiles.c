#include "my_ls.h"

entryList* getFiles(char** files, int ac, int startingIndex){
    entryList* enLis = malloc(sizeof(entryList));
    entryList* enLisCpy;
    entryList* newNode;

    struct stat* statBuff = malloc(sizeof(struct stat));

    int ENCount = 0;
    while(startingIndex < ac){
        char* path = files[startingIndex];
        int statVal = stat(path, statBuff);
        if(statVal == 0){//checks if current input is a directory or file         
            if(ENCount == 0){//find a way not to do this everytime?
                ENCount++;
                newNode = createNodeEnt(statBuff,path);
                enLis = newNode;
                enLisCpy = newNode;
            }else{
                newNode = createNodeEnt(statBuff,path);
                enLis->next = newNode;
                enLis = enLis->next;   
            }
        }else{//current input is an unknown (non existing) entry
            printf("ls: %s: No such file or directory\n",path);
        }
        startingIndex++;
    }
    free(statBuff);
    
    // free(enLis);
    return enLisCpy;
}