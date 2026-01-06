#include <stdio.h>
#include "commands.h"

int cmd_echo(int argc, char **argv){
    printf("%s\n", argv[1]);
    return 1;
}