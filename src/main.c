#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct command{
    char name[16];
    int (*action)(char *);
} Commands;

int cmd_exit(char *input){
    return 0;
}

int cmd_help(char *input){
    printf("Command list:\n");
    printf("HELP        shows the command list\n");
    printf("EXIT        closes the shell\n");
    printf("VERSION     shows the C-SHELL's current version\n");
    printf("CLEAR       clears the terminal\n");
    return 1;
}

int cmd_version(char *input){
    printf("C-Shell v0.1.0\n\n");
    return 1;
}

int cmd_clear(char *input){
    system("clear");
    return 1;
}


int main(){
    
    Commands commands[] = {
        {"exit", cmd_exit},
        {"help", cmd_help},
        {"version", cmd_version},
        {"clear", cmd_clear}
    };

    int found = 0;
    int running = 1;

    while(running){
        char input[1024];
        printf("myshell> ");
        fgets(input, sizeof(input), stdin);
        
        input[strcspn(input, "\n")] = '\0';

        for(int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++){
            if(strcmp(input, commands[i].name) == 0){
                found++;
                running = commands[i].action(input);
            }
        }

        if(found == 0){
            printf("Command not found! Try 'help'!\n\n");
        }

        found = 0;
    }
}