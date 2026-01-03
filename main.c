#include <stdio.h>
#include <string.h>

typedef struct comando{
    char nome[5];
    int (*acao)(char *);
} Comandos;

int cmd_exit(char *input){
    return 0;
}

int main(){
    
    Comandos comandos[] = {
        {"exit", cmd_exit},
    };

    while(1){
        char input[1024];
        printf("myshell> ");
        fgets(input, sizeof(input), stdin);
        
        input[strcspn(input, "\n")] = '\0';

        for(int i = 0; i <= 10; i++){
            if(strcmp(input, comandos[i].nome) == 0){
                
            }
        }
    }
}