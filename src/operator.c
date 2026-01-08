#include <stdio.h>
#include "../include/commands.h"
#include "../include/operators.h"

int is_operator(const char *token){
    for(int i = 0; OPERATORS[i] != NULL; i++){
        if(strcmp(token, OPERATORS[i]) == 0){
            return 1;
        }
    }
    return 0;
}

int validate_operators(int *argc, char **argv, RedirectInfo *redirect){
    int operator_index = -1;

    for(int i = 0; i < *argc; i++){
        if(is_operator(argv[i]) == 1){
            if(i == 0 || i == (*argc - 1) || operator_index != -1){
                printf("Syntax error!\n");
                return 0;
            }
            operator_index = i;

            if(strcmp(argv[i], ">") == 0){
                redirect->type = REDIRECT_OUT;
                redirect->filename = argv[i + 1];
            } else if(strcmp(argv[i], "<") == 0){
                redirect->type = REDIRECT_IN;
                redirect->filename = argv[i + 1];
            } else if(strcmp(argv[i], ">>") == 0){
                redirect->type = REDIRECT_APPEND;
                redirect->filename = argv[i + 1];
            } else if(strcmp(argv[i], "<<") == 0){
                redirect->type = REDIRECT_HEREDOC;
                redirect->heredoc_find = argv[i + 1];
            } 
            
            break;
        }
    }

    if(operator_index == -1){
        redirect->type = REDIRECT_NONE;
        redirect->filename = NULL;
        return 1;
    }

    for(int j = operator_index; j < *argc -2; j++){
        argv[j] = argv[j + 2];
    }

    *argc -= 2;
    argv[*argc] = NULL;

    return 1;
}