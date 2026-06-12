CC       = gcc
CFLAGS   = -Wall -Wextra -std=c99 -g
TARGET   = test_BST
SRCS     = test_BST.c BST.c
OBJS     = $(SRCS:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c BST.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)