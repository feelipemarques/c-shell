all: compile

compile:
	gcc src/main.c src/commands/*.c -Iinclude -Wall -o build/shell.exe