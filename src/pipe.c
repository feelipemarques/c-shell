#include <stdio.h>
#include "./include/commands.h"

int validate_pipe(int *argc, char **argv, CommandRange *ranges, int *num_cmds){
    *num_cmds = 0;
    int start = 0;
    for(int i = 0; i < *argc; i++){
        if(strcmp(argv[i], "||") == 0){
            printf("Syntax error!\n");
            return 0;
        }
        if(strcmp(argv[i], "|") == 0){
            if(i == 0 || i == (*argc - 1) || (i - 1) == "|"){
                printf("Syntax error!\n");
                return 0;
            }else{
                ranges[*num_cmds].start = start;
                ranges[*num_cmds].end = i - 1;
                start = i + 1;
                *num_cmds++;
                continue;
            }
        }
    }
    ranges[*num_cmds].start = start;
    ranges[*num_cmds].end = *argc - 1;
    *num_cmds += 1;
    return 1;
}