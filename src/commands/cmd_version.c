#include <stdio.h>
#include "commands.h"

int cmd_version(int argc, char **input){
    printf("C-Shell v1.0.0\n");
    return 1;
}