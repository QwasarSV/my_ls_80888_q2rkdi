#include "my_ls.h"

int getFlags(int argc, char** argv, int *index){
    int flags = 0b0;
    if(argv[1][0] != '-'){
            return flags;
    }
    while(*index < argc){
        if(argv[*index][0] != '-'){
            return flags;
        }
        if(argv[*index][1] == 'a'){
            flags |= INC_DOT_FILES;
            if(argv[*index][2] == 't'){
                flags |= TIME_SORT;
            }
        }
        if(argv[*index][1] == 't'){
            flags |= TIME_SORT;
            if(argv[*index][2] == 'a'){
                flags |= INC_DOT_FILES;
            }
        }
        *index+=1;
    }
    return flags;
}
