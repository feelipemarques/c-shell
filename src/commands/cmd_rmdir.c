#include <stdio.h>
#include <unistd.h>
#include "commands.h"

int cmd_rmdir(char *input){
    if(input == NULL){
        printf("rmdir: missing operand");
        return 1;
    }
    rmdir(input);
    return 1;
}