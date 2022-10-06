#include "my_ls.h"
#include <string.h>

bool ends_with(char *str, char c) {
    int endex = strlen(str) - 1;

    if (endex >= 0) {
        return str[endex] == c;
    }
    return false;
}

entryList* build_list(char* dir_path){
    entryList* enLis = malloc(sizeof(entryList));
    entryList* head = NULL;
    entryList* newNode;
    struct dirent* entry;

    DIR* dir = opendir(dir_path);

    while((entry = readdir(dir)) != NULL) {
        char fullpath[255] = { '\0' };

        if (strcmp(".", dir_path) != 0) {
            strcpy(fullpath, dir_path);
        }
        if (ends_with(dir_path, '/') == false) {
            strcat(fullpath, "/");
        }
        strcat(fullpath, entry->d_name);

        struct stat* statBuff = malloc(sizeof(struct stat));
        int statVal = stat(fullpath, statBuff);

        if (statVal == 0){//checks if current input is a directory or file         
            if (head == NULL) {
                newNode = createNodeEnt(statBuff, entry->d_name);
                enLis = newNode;
                head = newNode;
            } else {
                newNode = createNodeEnt(statBuff, entry->d_name);
                enLis->next = newNode;
                enLis = enLis->next;   
            }
        }
    }    
    closedir(dir);
    return head;
}

void writeFiles2(entryList* list) {
    while(list != NULL){
        // printf("%s...%lu\n",orderedList->path,orderedList->sb->st_mtimespec.tv_sec);
        struct stat* statBuff = malloc(sizeof(struct stat));
        char* path = list->path;
        stat(path, statBuff);
        if(S_ISREG(statBuff->st_mode)){
            printf("%s\n", path);
        }
        list = list->next;
    }
}

            //     if(instruction == 2 || instruction == 3){
            //         if(entry->d_name[0] == '.'){
            //             continue;    
            //         }
            //     }
            //     printf("%s\n",entry->d_name);


void writeDir2(entryList* head, int instruction) {
    entryList* list = head;

    while(list != NULL){
        struct stat* statBuff = malloc(sizeof(struct stat));
        char* path = list->path;
        stat(path, statBuff);
        if(S_ISDIR(statBuff->st_mode)){
            if (head->next != NULL) {
                printf("%s:\n",list->path);
            }

            entryList* current_files = build_list(list->path);
            if (instruction == 0 || instruction == 2) {
                current_files = timeSortedList(current_files);
            }
            else {
                current_files = lexSortedList(current_files);
            }

            writeCurrDir(current_files, instruction);
        }
        list = list->next;
        if (list != NULL) {
            printf("\n");
        }        
    }
}

void writeFiles(entryList* orderedList, int instruction){
    writeFiles2(orderedList);

    writeDir2(orderedList, instruction);

    cleanUp(orderedList);
}