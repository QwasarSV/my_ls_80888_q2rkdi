#include "my_ls.h"

int readInput(int ac, ...){
    va_list ap;
    va_start(ap,ac);
    char** argv = va_arg(ap,char**);
    int startingIndex;
    entryList* sortedList;
    int instruction;
    if(argv[1][0] != '-'){//no flags, but files
        instruction = 3;
        startingIndex = 1;
        entryList* unorderedList = getFiles(argv,ac,startingIndex);
        sortedList = lexSortedList(unorderedList);
        // writeFiles(sortedList, instruction, countEntries(sortedList));
        writeFiles(sortedList,instruction);
    }else{//flags, and possibly files
        getFlags(argv, &instruction, &startingIndex);
        if(instruction != 4){
            entryList* unorderedList = getFiles(argv,ac,startingIndex);
            if(instruction == 0 || instruction == 2){
                sortedList = timeSortedList(unorderedList);
                writeFiles(sortedList, instruction);
                // writeFiles(sortedList,instruction, countEntries(sortedList));
            }else{
                sortedList = lexSortedList(unorderedList);
                writeFiles(sortedList,instruction);
                // writeFiles(sortedList, instruction, countEntries(sortedList));
            }
        }
    }
    va_end(ap);
    return 0;
}