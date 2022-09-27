#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <dirent.h>

#ifndef STRUCT_LISTS
#define STRUCT_LISTS
// enum{
//     A_T,
//     A,
//     T
// };
typedef struct s_dirList{//list of directories
    // struct dirent* entry;
    char* fileName;
    struct s_dirList* next;
    int* empty;
}dirList;

typedef struct s_fileList{//list of files
    char* fileName;
    struct s_fileList* next;
    int* empty;
}fileList;

typedef struct s_unknownFileList{//list of files that DNE
    char* fileName;
    struct s_unknownFileList* next;
    int* empty;
}unknownFileList;

// typedef struct s_listHub{
//     union{
//         fileList* headFL;
//         dirList* headDL;
//         unknownFileList* headUFL;
//     };
// }listHub;

#endif

// int getFlags(char* flags){
//     int instruction = 0;


//     return instruction; 
// }
unknownFileList* createNodeUF(char* fileName){
    unknownFileList* newNode = malloc(sizeof(unknownFileList*));
    newNode->fileName = fileName;
    newNode->next = NULL;
    // newNode = newNode->next;
    return newNode;
}
fileList* createNodeF(char* fileName){
    fileList* newNode = malloc(sizeof(fileList*));
    newNode->fileName = fileName;
    newNode->next = NULL;
    // newNode = newNode->next;
    return newNode;
}
dirList* createNodeD(char* dirName){//struct dirent* entry goes in??
    dirList* newNode = malloc(sizeof(dirList*));
    newNode->fileName = dirName;
    newNode->next = NULL;
    // newNode = newNode->next;
    return newNode;
}

// void removeNode(int dummy, ...){
//     int index = 0;
//     file_list* head_cpy = head;
//     while(head != NULL){
//         if(head->next == node && index == 0){
//             file_list* temp = head;
//             head = head->next;
//             head_cpy = head;
//             temp->next = NULL;
//             temp->entry = NULL;
//             free(temp);
//             break;
//         }else if(head->next == node){
//             head->next = node->next;
//             node->next = NULL;
//             node->entry = NULL;
//             free(node);
//             break;
//         }else{
//             head = head->next;
//             index++;
//         }
//     }
// }

void writeFilesUK(unknownFileList* uList){
    // unknownFileList* uListCPY = uList;
    // fileList* fListCPY = fList;
    // dirList* dListCPY = dList;
    while(uList != NULL){
        char* currFilName = uList->fileName;
        printf("ls: %s: No such file or directory\n",currFilName);
        unknownFileList* temp = uList;
        uList = uList->next;
        temp->next = NULL;
        temp->fileName = NULL;
        free(temp);
    }
}

void writeFilesFL(fileList* fList){
    while(fList != NULL){
        char* currFilName = fList->fileName;
        printf("%s\n",currFilName);
        fileList* temp = fList;
        fList = fList->next;
        temp->next = NULL;
        temp->fileName = NULL;
        free(temp);
    }     
}

void writeFilesDL(dirList* dList){
    while(dList != NULL){
        char* currFilName = dList->fileName;
        printf("\n%s:\n", currFilName);
        DIR* directory = opendir(currFilName);
        struct dirent* entry;

        while((entry = readdir(directory)) != NULL){
            printf("%s\n",entry->d_name);
        }

        dirList* temp = dList;
        dList = dList->next;
        temp->next = NULL;
        temp->fileName = NULL;
        free(temp);
        closedir(directory);
    }
}

int getFiles(char** files, int ac){

    unknownFileList* ukLis = malloc(sizeof(unknownFileList*));
    unknownFileList* ukLisCpy = NULL;
    int UKCount = 0;

    fileList* fileLis = malloc(sizeof(fileList*));
    fileList* fileLisCpy = NULL;
    int FLcount = 0;

    dirList* directLis = malloc(sizeof(dirList*));
    dirList* directLisCpy = NULL;
    int dlCount = 0;

    int index = 1;
    while(index < ac){//possible that i run into something else in memory that != NULL?
        
        char* path = files[index];
        struct stat path_stat;
        stat(path, &path_stat);
        if(S_ISDIR(path_stat.st_mode) == 1){//checks if current input is a directory
            if(dlCount == 0){//find a way not to do this everytime?
                dlCount++;
                directLis = createNodeD(path);
                directLisCpy = directLis;
            }else{
                directLis->next = createNodeD(path);
                directLis = directLis->next;
            }
        }else if(S_ISREG(path_stat.st_mode) == 1){//checks if current input is a file
            if(FLcount == 0){
                FLcount++;
                fileLis = createNodeF(path);
                fileLisCpy = fileLis;
            }else{
                fileLis->next = createNodeF(path);
                fileLis = fileLis->next;
            }
        }else{//current input is an unknown (non existing) entry
            if(UKCount == 0){
                UKCount++;
                ukLis = createNodeUF(path);
                ukLisCpy = ukLis;
            }else{
                ukLis->next = createNodeUF(path);
                ukLis = ukLis->next;
            }
        }
        index++;
    }

    if(ukLisCpy != NULL){
        writeFilesUK(ukLisCpy);
    }
    if(fileLisCpy != NULL){
        writeFilesFL(fileLisCpy);
    }
    if(directLisCpy != NULL){
        writeFilesDL(directLisCpy);
    }
    //write the list here. need to parse flags in input to see what order to print things out in
    //2 separate write funcitons (maybe 3 or more?)
    return 0;
}

int readInput(int ac, ...){
    va_list ap;
    va_start(ap,ac);
    
    char** argv = va_arg(ap,char**);
    bool flags = true;
    bool files = true;

    int index = 1;
    while(index < ac){
        if(argv[1][0] != '-'){//no flags, but files
            flags = false;
            getFiles(argv,ac);
            break;
        }else{//flags, and possibly files

        }
        index++;
    }
    va_end(ap);
    return 0;
}

// int my_ls(int instruction, char** argv){
//     return 0;
// }

int main(int argc, char** argv){
    if(argc == 1){//no arguments
        // my_ls(argc,".");
        printf("nothing\n");
    }else{//arguments present, unclear whether flags, files, or both are present in the arguments, need to parse
        readInput(argc,argv);
    }
    // DIR* dir = opendir("testdir");
    // if(dir == NULL){
    //     printf("hhhh\n");
    // }
    // struct dirent* entry;
    // while((entry = readdir(dir)) != NULL){
    //     printf("%s\n",entry->d_name);
    // }
    // closedir(dir);
    // char* path = "testdir";
    // struct stat path_stat;
    // stat(path, &path_stat);
    // int sts =  S_ISDIR(path_stat.st_mode);
    // printf("%d\n",sts);
    return 0;
}
//tests:
    //./ls stuff testdir bnuwcbeuri testfile testdir2 main.c -breaks: trys to display unknown file like a directory
    //./ls testdir testdir2 main.c stuff wweeffewrwg testfile -breaks: displays unknown files like regular files
    //./ls stuff niuner hwberffyibewrig testdir testdir2 main.c testfile: works