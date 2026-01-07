all: compile

compile:
	gcc -g src/main.c src/commands/*.c -Iinclude -Wall -o build/shell.exe