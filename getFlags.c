#include "my_ls.h"

void getFlags(char** argv, int* instruction, int* startingIndex){
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