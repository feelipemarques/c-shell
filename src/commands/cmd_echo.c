#include <stdio.h>
#include "commands.h"

int cmd_echo(int argc, char **argv){
    for(int i = 1; i < argc; i++){
        printf("%s ", argv[i]);
    }
    printf("\n");
    return 1;
}