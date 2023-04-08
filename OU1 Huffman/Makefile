CC = gcc
CFLAGS = -Wall -std=c99 -g
DEPS = frequency.h binarytree.h pqueue.h list.h bit_buffer.h
OBJ = huffman.o frequency.o binarytree.o pqueue.o list.o bit_buffer.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

huffman: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)
