#include <stdio.h>
#include "commands.h"

int cmd_cd(char *input){
    if(input == NULL){
        printf("cd: missing argument\n");
        return 1;
    }
    if(chdir(input) != 0){
        printf("cd: an error ocurred! try again!\n");
    }
    return 1;
}