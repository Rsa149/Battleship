# Makefile for building to run on your laptop/desktop

CC = gcc
CCFLAGS = -Wall -O1

# We don't touch the io_hw.c or io_hw.h files
SRCS := battleship.c io.c

bs : $(SRCS)
	$(CC) $(CCFLAGS) -o $@ $^

clean :
	rm -f bs   # delete (native) executable
	rm -f *~   # delete emacs backup files
