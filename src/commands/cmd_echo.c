#include <stdio.h>
#include "commands.h"

int cmd_echo(char *input){
    printf("%s\n", input);
    return 1;
}