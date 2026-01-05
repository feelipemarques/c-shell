#include <stdio.h>
#include "commands.h"

int cmd_mkdir(char *input){
    if(input == NULL){
        printf("mkdir: dir name cannot be null\n");
        return 1;
    }
    mkdir(input);
    return 1;
}