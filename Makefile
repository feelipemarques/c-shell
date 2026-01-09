CC = gcc
CFLAGS = -g -Wall -Iinclude

SRC = src/main.c \
      src/core/*.c \
      src/commands/*.c

all:
	$(CC) $(CFLAGS) $(SRC) -o build/shell.exe
