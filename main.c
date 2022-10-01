#include "my_ls.h"
int main(int argc, char** argv){
    if(argc == 1){//no arguments
        entryList* currDir = readCurrDir();
        entryList* lexSortedList_ = lexSortedList(currDir);
        writeCurrDir(lexSortedList_);
    }else{//arguments present, unclear whether flags, files, or both are present in the arguments, need to parse
        readInput(argc,argv);
    }
    return 0;
}