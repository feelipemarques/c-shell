#include <stdio.h>
#include "commands.h"

int cmd_help(int argc, char **argv){
    printf("Command list:\n");
    printf("HELP        show the command list\n");
    printf("EXIT        close the shell\n");
    printf("VERSION     show the C-SHELL's current version\n");
    printf("CLEAR       clear the terminal\n");
    printf("CD          change the directory\n");
    printf("PWD         show current directory\n");
    printf("LS          list the current directory's content\n");
    printf("MKDIR       create a new directory\n");
    printf("RMDIR       remove the specified directory\n");
    printf("RM          remove the specified file\n");
    printf("CAT         read the specified file\n");
    printf("CP          create a copy from the specified file\n");
    printf("ECHO        write arguments to the standard output\n");
    printf("TOUCH       create a new file\n");
    return 1;
}
