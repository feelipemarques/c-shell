#include <stdio.h>
#include <stdlib.h>
#include "commands.h"

int cmd_clear(int argc, char **argv){
    system("clear");
    return 1;
}