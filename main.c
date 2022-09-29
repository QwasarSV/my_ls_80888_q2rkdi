#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <dirent.h>

#ifndef STRUCT_LISTS
#define STRUCT_LISTS

typedef struct s_entryList{
    struct stat* sb;
    char* path;
    struct s_entryList* next;
}entryList;
#endif

void getFlags(char** argv, int* instruction, int* startingIndex, int ac){
    bool aFlag = false;
    bool tFlag = false;
    bool done = false;
    int index = 1;
    while(done == false){
        char currentArg = argv[index][1];
        switch(currentArg){
            case 'a':
            {
                aFlag = true;
                if(argv[index][2] == 't'){
                    tFlag = true;
                    done = true;
                }
                break;
            }
            case 't':{
                tFlag = true;
                if(argv[index][2] == 'a'){
                    aFlag = true;
                    done = true;
                }
                break;
            }
            default:
            {
                printf("ls: %c: No such file or directory\n",currentArg);
                break;
            }
        }
        if(argv[index + 1]== NULL || argv[index + 1][0] != '-' ){
            break;
        }
        index++;
    }
    *startingIndex = index + 1;// plus one to leave out fd (argv[0])

    if(aFlag == true && tFlag  == true){
        *instruction = 0;
    }else if(aFlag == true && tFlag  == false){
        *instruction = 1;
    }else if(aFlag == false && tFlag  == true){
        *instruction = 2;
    }else{//invalid flag input, flag should always exist if this function is called
        *instruction = 3;
    }
}


int my_strcmp(char* str1, char* str2){
int index = 0;
while(str1[index]){
    if(str1[index] != str2[index]){
        if(str1[index] - str2[index] < 0){
            return -1;//str1 comes before str2 lexicographically
        }
        else{
            return 1;//str1 comes after str2 lexicographically
        }
    }
    index++;
}
//returns zero if above condition is not met, meaning that the two strings are equivalent 
return 0;
}

int countEntries(entryList* head){
    int fileCount = 0;
    while(head != NULL){
        fileCount++;
        head = head->next;
    }
    return fileCount;
}

entryList* createNodeEnt(struct stat* sb, char* path){
    entryList* newNode = malloc(sizeof(entryList));
    newNode->sb = sb;
    newNode->path = path;
    newNode->next = NULL;
    return newNode;
}
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

entryList* lexSort(entryList* head){
    entryList* nextInLine = head;
    while(head != NULL){
        if(my_strcmp(head->path, nextInLine->path) < 0){
            nextInLine = head;
        }
        head = head->next;
    }
    return nextInLine; 
}

entryList* getFiles(char** files, int ac, int startingIndex){
    entryList* enLis;
    entryList* enLisCpy;
    entryList* newNode;

    struct stat* statBuff = malloc(sizeof(struct stat));

    int ENCount = 0;
    while(startingIndex < ac){
        char* path = files[startingIndex];
        stat(path, statBuff);
        DIR* dir = opendir(path);
        if(S_ISDIR(statBuff->st_mode) && dir != NULL){//checks if current input is a directory or file
            closedir(dir);          
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
        }else if(S_ISREG(statBuff->st_mode)){
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
    free(enLis);
    return enLisCpy;
}

entryList* newSortedList(entryList* enLis){
    entryList* sortedList = malloc(sizeof(entryList));
    entryList* sortedListCpy = NULL;
    entryList* nextInLine = NULL;
    entryList* newNode = NULL;

    int index = 0;
    int length = countEntries(enLis);
    while(index < length){
        // printf("%d\n",countEntries(enLis));
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

void writeFiles(entryList* orderedList){
    while(orderedList != NULL){
        printf("%s\n",orderedList->path);
        orderedList = orderedList->next;
    }
}

int readInput(int ac, ...){
    va_list ap;
    va_start(ap,ac);
    
    char** argv = va_arg(ap,char**);
    int startingIndex;
    if(argv[1][0] != '-'){//no flags, but files
        startingIndex = 1;
        entryList* unorderedList = getFiles(argv,ac,startingIndex);
        // writeFiles(unorderedList);
        // entryList* sortedList = newSortedList(unorderedList);
        // printf("%d\n",countEntries(sortedList));
        // writeFiles(sortedList);
    }else{//flags, and possibly files
        int instruction;
        getFlags(argv, &instruction, &startingIndex, ac);
        entryList* unorderedList = getFiles(argv,ac,startingIndex);
        entryList* sortedList = newSortedList(unorderedList);
        writeFiles(sortedList);
        // writeFiles(unorderedList);
    }
    va_end(ap);
    return 0;
}

int main(int argc, char** argv){
    if(argc == 1){//no arguments
        // my_ls(argc,".");
        printf("nothing\n");
    }else{//arguments present, unclear whether flags, files, or both are present in the arguments, need to parse
        readInput(argc,argv);
    }
    return 0;
}
//tests:
    //./ls stuff testdir bnuwcbeuri testfile testdir2 main.c -breaks: trys to display unknown file like a directory
    //./ls testdir testdir2 main.c stuff wweeffewrwg testfile -breaks: displays unknown files like regular files
    //./ls stuff niuner hwberffyibewrig testdir testdir2 main.c testfile: works

    //      char* fileName;
    //      struct stat* sb = malloc(sizeof(struct stat));
    //      stat(fileName,sb);