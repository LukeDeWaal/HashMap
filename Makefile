# Usage:
# Run 'make test' to execute the test program.
# Run 'make valgrind' to run the test program in Valgrind.
# Run 'make submit' to generate the ZIP file to upload to CPM.
# Run 'make clean' to remove compiled files.

CC					:= gcc
CFLAGS				:= -Wall -Wextra -pedantic -std=c99 -g
WORDCOUNT_HEADER	:= wordcount.h
WORDCOUNT_SRC		:= wordcount.c
SRC					:= hashmap.c
DEPS				:= $(SRC) $(SRC:.c=.h)
TEST				:= test_sample.c
TARGET				:= test

# Checks if wordcount.h exists, if so defines COUNTING_WORDS, includes wordcount.c in compilation
# and updates the dependencies.
ifneq ($(wildcard $(WORDCOUNT_HEADER)),)
CFLAGS	+= -DCOUNTING_WORDS
SRC		+= $(WORDCOUNT_SRC)
DEPS	:= $(SRC) $(SRC:.c=.h)
endif

.PHONY: test valgrind submit clean

default: test

compile:
	$(CC) $(CFLAGS) $(SRC) $(TEST) -o $(TARGET)

test: compile
	./test

valgrind:
	valgrind --tool=memcheck ./test

submit: $(DEPS)
	zip $(SRC:.c=.zip) $(DEPS)

clean:
	-rm -f *.o
	-rm -f $(TARGET) $(SRC:.c=.zip)
