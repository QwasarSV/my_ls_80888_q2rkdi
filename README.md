# Welcome to My Ls
***
Welcome! Have you ever wondered how the ls function works? Me neither! Let's find out!!!

## Task
Our goal is to recreate the UNIX command ls, including the functionality of 2 flags: -t which prints files by the time they were last modified, with the most recent files being displayed first, and the -a flag, which includes the hidden, dot directories (it does not by default). We will also be printing the files to the console with ls's -1 format, which displays all files in a single, vertical column. 


## Overview
The architecture of this project is divided into 4 main stages: firstly, we must read the user input (if any) and determine flags (options) that they specified, and any specific file-paths that were specified in the command line arguments. If no command line arguments are provided by the user, then the current directory is written to the screen, lexicographically sorted by default. The second step is to create the lists, doubly linked lists in this case, that will store the names/file-paths of regular files and directories, the size of the list, a structure created by the stat(2) system call see man page ([Man Page](https://man7.org/linux/man-pages/man2/lstat.2.html#:~:text=The%20fields%20in%20the%20stat,the%20file%20type%20and%20mode) ) which will be utilized later to access information about the UNIX time that the files were last modified. The third stage of the program is sorting. For this implementation, an in-place insertion sort algorithm was used to minimize space complexity, but at the cost of a higher time complexity O(n²) in the worst case. This is fine when dealing with the relatively small files tree sizes on a personal computer, but will become more costly when scaling. In the next implementation of this project, I would consider sorting the files as they were pushed into the linked list, or perhaps using merge sort, as it is more efficient as the data size increases. For the purposes of this project however, insertion sort will, in most cases, outperform merge sort with an O(n) time complexity in the best case, while merge sort will constantly perform at O(nlogn) and O(n) time and space complexity respectively. The final portion of this project is to print the files/directories to the screen, mimicking the format of ls, and freeing the memory  stored in the nodes of the linked lists.

## Description
This initial work is done by the getFlags function. To keep track of the options that the user specifies, we used binary numbers/bit operators to store the information in a single, 3 bit binary number (by default 0). The flag variable (int) is able to hold information about 3 flags: -a (INC_DOT_FILES) presented by the binary number 1 (001), -t (TIME_SORT) represented by the binary number 2 (010), and a third flag (UNKNOWN_FILES_EXIST) that is not specified by the user, but is activated in the make_lists function when if it reads a file inputted by the user that does not exist. This third flag is represented with the binary number 4 (100) to prevent interactions with the two other flags, since the binary number 3 (011) may interfere with how the flag variable is interpreted.
Once the options have been determined, the next stage is to move onto the make_lists function to create an unsorted linked list of the specified files and directories. If no files are specified, then the helper function make_curr_direc is employed to create a linked list of the files/directories in the current (“.”) directory. If unknown files are encountered here, as mentioned before, the message “ls: [unknown file]: No such file or directory” is printed to the console. 
After the unsorted list of files/directories is created, the list is passed to the insertionSort function which takes the unsorted list, and a function pointer to the time_cmp or lex_cmp functions depending on if the -t flag was specified by the user. Function pointers were employed here to adhere to DRY principles. Finally, the sorted list is passed to the printfFiles function where, as per ls formatting, prints the files first. As the files are printed, the node containing their information is freed. After all the files in the list have been printed, the remaining directories (if any) in the list are passed to the printfDirectories function which prints out the directories and the files they contain in the ls format standard. The files within the directory are first made into a new linked list, sorted, and freed. 

## Future Improvements
The first improvements to this project I plan to make is to reduce the code size of the printFiles and printDirectories functions, or at least to split them into more helper functions, to increase the readability of the code. The size of make_lists could also be reduced. Besides getting rid of repetitive and unnecessary code, to make the program more efficient, I could use insertion sort to sort the linked lists as they are created. 

## Installation
The libraries that were used in this project are :stdio.h, stdlib.h, string.h, unistd.h, sys/stat.h, dirent.h, stdbool.h.

## Usage
This project is optimal for usage in personal projects where file systems are relatively small.

<span><i>Made at <a href='https://qwasar.io'>Qwasar Silicon Valley</a></i></span>
<span><img alt='Qwasar Silicon Valley Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>