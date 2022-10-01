#include "my_ls.h"

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