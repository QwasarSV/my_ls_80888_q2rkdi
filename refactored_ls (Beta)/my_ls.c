#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdbool.h>
#define INC_DOT_FILES 0b1
#define TIME_SORT 0b10
#define UNKNOWN_FILES_EXIST 0b100

typedef struct s_file_list{
    struct s_file_list* prev;
    struct s_file_list* next;
    char* pathname;
    size_t size;
    struct stat* sb;
}file_list;



//read input
    //if no arguments, print current directory
    //arguments, but no flags, push files and direcotories separatley
    //parse flags
//sort lists
//write files
//write directories
    //sort files within directories

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

file_list* create_node(char* pathname, struct stat* sb, size_t size, file_list* prev){
    file_list* new_node = malloc(sizeof(file_list));
    new_node->pathname = pathname;
    new_node->sb = sb;
    new_node->size = size;
    new_node->next = NULL;
    new_node->prev = prev;
    return new_node;
}
// file_list* push_node(file_list* head, file_list* node){

// }   
// file_list* remove_node(file_list* head, file_list* node){

// }

bool time_sort(int a, int b){
    return a > b;//larger times are more recent
}

bool lex_sort(int a, int b){
    return a < b;//smaller ascii character values are last in lexico-sort
}

file_list* traverse_list_forwards(file_list* head, int index){
    int j = 0;
    while(j < index){
        head = head->next;
    }
    return head;
}

file_list* traverse_list_backwards(file_list* head, int index){
    int j = 0;
    while(j < index){
        head = head->next;
    }
    return head;
}

void swap_nodes(file_list* prev_node, file_list* curr_node){
    
    file_list* behind_previous = prev_node->prev;//node before previous
    file_list* in_front_of_curr = curr_node->next;//node after current
    
    behind_previous->next = curr_node;
    in_front_of_curr->prev = prev_node

    prev_node->next = in_front_of_curr;
    prev_node->prev = curr_node;
    
    curr_node->next = prev_node;
    curr_node->prev = behind_previous;
}

file_list* insertion_sort(file_list* unsorted_list, int size, bool (*sort)(int, int)){
    for(int i = 1; i < size; i++){
        int curr_val = traverse_list_forwards(unsorted_list, i);
        int prev_val  = traverse_list_backwards(unsorted_list, i - 1);

        while(prev_val != starting_index && sort()){

        }
    }
}

file_list* make_lists(int argc, char** argv, int index, int* flags){
    file_list* head = NULL;
    file_list* files = NULL;
    file_list* prev = NULL;
    file_list* newNode;
    size_t size = 0;
    while(index < argc){
        struct stat* sb = malloc(sizeof(struct stat));
        char* pathname = argv[index];
        if((lstat(pathname,sb)) == -1){
            *flags |= UNKNOWN_FILES_EXIST;
            printf("ls: %s: No such file or directory\n", pathname);
        }
        else if(S_ISREG(sb->st_mode) || S_ISDIR(sb->st_mode)){
            size++;
            if(head == NULL){
                files = create_node(pathname, sb, size, prev);
                prev = files;
                head = files;
            }
            else{
                files->next = create_node(pathname, sb, size, prev);
                prev = files;
                files = files->next;
                head->size++;
            }
        }
        index++;
    }
    return head;
}


void printDirectories(file_list* directories, int flags, bool are_files){
    DIR* dir;
    struct dirent* entry;
    int length = directories->size;
    int index = 0;
    while(index < length){
        dir = opendir(directories->pathname);
        printf("\n%s:\n",directories->pathname);
        while((entry = readdir(dir))){
            if(!(flags & INC_DOT_FILES) && entry->d_name[0] == '.'){
                continue;
            }
            else{
                printf("%s\n",entry->d_name);
            }
        }
        directories = directories->next;
        index++;
    }
}

void printFiles(file_list* files, int flags){
    file_list* directories = NULL;
    file_list* prev = NULL;
    bool are_files = false; //to know if a space should be placed before printing
    size_t size = 0;
    file_list* head = NULL;
    int index = 0;
    int length = files->size;
    while(index < length ){
        if(S_ISDIR(files->sb->st_mode)){
            size++;
            if(head == NULL){
                directories = create_node(files->pathname, files->sb, size, prev);
                prev = directories;
                head = directories;
            }else{
                directories->next = create_node(files->pathname, files->sb, size, prev);
                prev = directories;
                directories = directories->next;
                head->size++;
            }
        }
        else if(!(flags & INC_DOT_FILES) && files->pathname[0] == '.'){
            are_files = true;
        }
        else{
            are_files = true;
            printf("%s\n",files->pathname);
        }
        files = files->next;
        index++;
    }
    if(directories != NULL){
        printDirectories(head, flags, are_files);
    }
}

int main(int argc, char** argv){
    int index = 1;
    if(argc == 1){  
        //if returned index ==  argc, then there are no files to parse, print cd
        struct stat* sb = malloc(sizeof(struct stat));
        file_list* prev = NULL;
        lstat(".",sb);
        file_list* curr_dir = create_node(".",sb,1, prev);
        // printDirectories(curr_dir,0,false);
    }
    else{
        int flags = getFlags(argc, argv,&index);
        file_list* unsorted_list  = make_lists(argc, argv,index,&flags);
        printf("%d\n",flags);
        if(unsorted_list == NULL){
            struct stat* sb;
            file_list* prev = NULL;
            lstat(".",sb);
            file_list* curr_dir = create_node(".",sb,1, prev);
            // printDirectories(curr_dir,flags,false);
        }else{
            // printFiles(unsorted_list, flags);//may not be able to make this assumption (all directories)
        }
    }
    return 0;
}