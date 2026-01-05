#include <stdio.h>
#include "commands.h"

int cmd_clear(char *input){
    system("clear");
    return 1;
}