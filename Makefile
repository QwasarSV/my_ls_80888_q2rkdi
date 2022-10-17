CC = gcc
CFLAGS += -Wall -Werror -Wextra
CFLAGS_DEBUG = $(CFLAGS)
MAIN = my_ls
SRCS = main.c flagHandler.c linkedListFunctions.c printingFunctions.c sortingFunctions.c
OBJS = $(SRCS:.c=.o) 

all: $(MAIN)

$(MAIN): $(OBJS)
				$(CC) $(CFLAGS) -o $@ $(LINKERFLAG) $^

clean:
				$(RM) -f $(OBJS)

fclean: clean
				$(RM) -f $(MAIN) $(DEBUG)

re: fclean all