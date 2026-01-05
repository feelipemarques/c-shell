#include <stdio.h>
#include "commands.h"

int cmd_pwd(char *input){
    char buffer[1024];
    printf("%s\n", getcwd(buffer, 1024));
    return 1;
}