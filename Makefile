
S := src/
SS := $(S)qsort.c
H := -I include/
NAME := libsort.a
CC := gcc
OCF := -O3 -Wall -Wextra -Werror
GCF := -g -Wall -Wextra -Werror
ifeq ($(shell echo $$DOCKER), 1)
debug = 1
endif
ifdef debug
CF := $(GCF)
else
CF := $(OCF)
endif
ifeq ($(shell echo $$DOCKER), 1)
TEST = $(CC) $(CF) $(H) -o test.run test/main.c libsort.a
else
TEST = $(CC) $(CF) $(H) -L ./ -lsort -o test.run test/main.c
endif

all: $(NAME)

%.o: %.c
	$(CC) $(CF) $(H) -c -o $@ $<

$(NAME): $(SS:.c=.o)
	ar rc $(NAME) $(SS:.c=.o) 
	
test: $(NAME) 
	$(TEST)
	./test.run

clean:
	/bin/rm -f $(SS:.c=.o)

fclean: clean
	/bin/rm -f $(NAME)

tclean: fclean
	/bin/rm -f test.run test.run.dSYM

re: fclean all

.PHONY: test
