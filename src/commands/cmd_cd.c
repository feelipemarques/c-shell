#include <stdio.h>
#include <unistd.h>
#include "commands.h"


int cmd_cd(int argc, char **argv){
    if(argv[1] == NULL){
        printf("cd: missing argument\n");
        return 1;
    }
    if(chdir(argv[1]) != 0){
        printf("cd: an error ocurred! try again!\n");
    }
    return 1;
}