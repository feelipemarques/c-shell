#include <stdio.h>
#include <unistd.h>
#include "commands.h"

int cmd_rmdir(int argc, char **argv){
    if(argv[1] == NULL){
        printf("rmdir: missing operand");
        return 1;
    }
    rmdir(argv[1]);
    return 1;
}