#include <stdio.h>
#include <unistd.h>
#include "commands.h"

int cmd_pwd(int argc, char **argv){
    char buffer[1024];
    printf("%s\n", getcwd(buffer, 1024));
    return 1;
}