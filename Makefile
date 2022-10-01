CC = gcc
CFLAGS += -Wall -Werror -Wextra
CFLAGS_DEBUG = $(CFLAGS)
MAIN = my_ls
SRCS = main.c \
		my_strcmp.c countEntries.c createNodeEnt.c removeNode.c lexSort.c getFiles.c lexSortedList.c writeFiles.c readInput.c getFlags.c timeSort.c timeSortedList.c readCurrentDir.c writeCurrDir.c cleanUp.c 
OBJS = $(SRCS: .c = .o) 

all: $(MAIN)

$(MAIN): $(OBJS)
		$(CC) $(CFLAGS) -o $@ $(LINKERFLAG) $^

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(MAIN) $(DEBUG)

re: fclean all