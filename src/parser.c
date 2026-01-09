#include <stdio.h>

void parse_input(char *input, int *argc, char **argv){
    input[strcspn(input, "\n")] = '\0'; // Transforma o '\n' (quebra de linha) em um '\0'

    char *start = input;
    char *p = input;

    while(*p != '\0' && *argc < 10){
        if(*p == ' '){
            *p = '\0';
            argv[(*argc)++] = start;
            start = p + 1;
        }
        p++; 
    }

    if (*start != '\0' && *argc < 9) { argv[(*argc)++] = start; }

    *argv[*argc] = NULL;
}