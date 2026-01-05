#include <stdio.h>
#include "commands.h"

int cmd_version(char *input){
    printf("C-Shell v0.1.0\n");
    return 1;
}