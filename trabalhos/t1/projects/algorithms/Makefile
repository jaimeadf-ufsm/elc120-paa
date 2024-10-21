.SECONDARY:

CC=gcc
CFLAGS=-Wall -Wextra -O3 -g -MP -MD

BINARY=bin
SRC_DIR=src

CFILES=$(wildcard $(SRC_DIR)/*.c)
OBJECTS=$(patsubst %.c,%.o,$(CFILES))
DEPS=$(patsubst %.c,%.d,$(CFILES))

all: $(BINARY)

$(BINARY):$(OBJECTS)
	$(CC) -o $@ $^ -lm

%.o:%.c
	$(CC) $(CFLAGS) -c -o -pthread$@ $<

clean:
	rm -f $(BINARY) $(OBJECTS) $(DEPS) 

-include $(DEPS)

.PHONY: all clean