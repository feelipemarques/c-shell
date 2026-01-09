CC = gcc
CFLAGS = -g -Wall -Iinclude
LDFLAGS = -lreadline

SRC = src/main.c \
      src/core/*.c \
      src/commands/*.c

all:
	$(CC) $(CFLAGS) $(SRC) -o build/shell.exe $(LDFLAGS)
