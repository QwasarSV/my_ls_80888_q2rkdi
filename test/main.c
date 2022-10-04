#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <dirent.h>

int main(){
    struct stat* statBuff = malloc(sizeof(struct stat));
    char* path = "hello.c";
    DIR* dir = opendir(path);
    int suc = stat(path, statBuff);
    printf("%d\n",suc);
    // DIR* dir = opendir(path);
    if(S_ISREG(statBuff->st_mode)){
        printf("SUCCESS\n");
    }
    return 0;
}