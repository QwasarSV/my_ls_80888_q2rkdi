# Welcome to My Ls
***
Welcome! Have you ever wondered how the ls function works? Me neither! Let's find out!!!
## Task
Our goal is to recreate the funcitonality of the UNIX command ls, including the funcitonality of 2 flags: -t which prints files by the time they were created, with the
most recent files being displayed first, and the -a flag, which includes the hidden, dot directories (it does not by default). We will also be printing the files to the console
assuming the -1 flag, which displays all files in a single, vertical column. 


## Description
The bulk of the work is done by 4 functions: readInnput.c, getFiles.c, getFlags.c, and writeFiles.c... All the other funcitonality of the program is done by the various helper functions. 

    -readInput.c:
        -takes in command line arguments (if there is any), and determines whether or not there are flags (either a or t) included
            ...if flags exist, the getFlags.c function is called to determine what flags are present (read more about getFlags.c below)
            ...if flags DON'T exist, then the getFiles.c function is called (read more about getFiles.c below)
        -once flags (or lack therof) hav been determined, then either the timeSortingList funciton is called (in case of a -t flag) or, in all other cases,
            the lexSortingList funciton is called to sort the inputted files/directories, or the current directory if no files/directories are provided
        -the sorted list is then passed to the writeFiles funciton where the correclty sorted lists are printed to the console, and then all remaining memory is freed using the cleanUp.c funciton
    -getFlags.c:
        -reads command line argument and returns, by way of calling by address/reference (modifying pointers to enable the ability of a single funciton call to "return" multiple values), an instruciton variable,
            which denotes whether the -a and/or -t flags are present, and a startingIndex variable which will later inform the writeFiles funciton at what index of the command line arguments 
            to start at, as to not reiterate over the flags
        -if no files are given, the current directory is printed in whatever format was specified, by calling a separte reading/writing funcitons (readCurrDir.c/writeCurrDir.c)
            ...these separate funcitons are called directly in the main funciton in the case where there are no arguments provided, hence the current directory is  
                printed in lexicographical order
    -getFiles.c:
        -this funciton is called to retrieve all files/directories that were specified by the user in the command line, while also printing out to the screen non-existing files
            the user may have inputted
        -this funciton returns an unsorted list which will be sorted in the readInpu
        


<span><i>Made at <a href='https://qwasar.io'>Qwasar Silicon Valley</a></i></span>
<span><img alt='Qwasar Silicon Valley Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>
