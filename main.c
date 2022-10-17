#include "my_ls.h"

int main(int argc, char** argv){
    int index = 1;
    if(argc == 1){  
        file_list* curr_dir = make_curr_direc();
        printDirectories(curr_dir,0,false);
    }
    else{
        int flags = getFlags(argc, argv,&index);
        file_list* list  = make_lists(argc, argv,index,&flags);
        if(list == NULL){//flags but no specified files/directories
            file_list* curr_dir = make_curr_direc();

            printFiles(curr_dir,flags);
        }else{
            if(flags & TIME_SORT){
                insertionSort(&list, time_cmp);
            }else{
                insertionSort(&list, lex_cmp);
            }
            printFiles(list, flags);
        }
    }
    return 0;
}
