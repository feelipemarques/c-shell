#include <stdio.h>
#include "commands.h"

int cmd_help(int argc, char **argv){
    printf("Command list:\n");
    printf("HELP        shows the command list\n");
    printf("EXIT        closes the shell\n");
    printf("VERSION     shows the C-SHELL's current version\n");
    printf("CLEAR       clears the terminal\n");
    printf("CD          changes the directory\n");
    printf("PWD         shows current directory\n");
    printf("LS          lists the current directory's content\n");
    printf("MKDIR       creates a new directory\n");
    return 1;
}
