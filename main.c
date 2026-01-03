#include <stdio.h>
#include <string.h>

typedef struct comando{
    char nome[5];
    int (*acao)(char *);
} Comandos;

int cmd_exit(char *input){
    return 0;
}

int cmd_help(char *input){
    printf("Command list:\n");
    printf("HELP    shows the command list\n");
    printf("EXIT    closes the shell\n");

    return 2;
}

int main(){
    
    Comandos comandos[] = {
        {"exit", cmd_exit},
        {"help", cmd_help}
    };

    int found = 0;
    int nextLine = 1;

    while(nextLine){
        char input[1024];
        printf("myshell> ");
        fgets(input, sizeof(input), stdin);
        
        input[strcspn(input, "\n")] = '\0';

        for(int i = 0; i < sizeof(comandos)/sizeof(comandos[0]); i++){
            if(strcmp(input, comandos[i].nome) == 0){
                found++;
                nextLine = comandos[i].acao(input);
            }
        }

        if(found == 0){
            printf("Command not found! Try 'help'!\n\n");
        }

        found = 0;
    }
}