#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

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
    printf("CD          changes the directory\n");
    printf("PWD         shows current directory\n");
    return 1;
}

int cmd_version(char *input){
    printf("C-Shell v0.1.0\n");
    return 1;
}

int cmd_clear(char *input){
    system("clear");
    return 1;
}

int cmd_echo(char *input){
    printf("%s\n", input);
    return 1;
}

int cmd_cd(char *input){
    if(input == NULL){
        printf("cd: missing argument\n");
        return 1;
    }
    if(chdir(input) != 0){
        printf("cd: an error ocurred! try again!\n");
    }
    return 1;
}

int cmd_pwd(char *input){
    char buffer[1024];
    printf("%s\n", getcwd(buffer, 1024));
    return 1;
}

int cmd_ls(char *input){
    DIR *dir;
    struct dirent *entry;

    if(input == NULL){
        dir = opendir(".");
    }else{
        dir = opendir(input);
    }

    if(dir == NULL){
        printf("ls: cannot open directory\n");
    }

    while((entry = readdir(dir)) != NULL){
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 1;
}

int main(){
    
    Commands commands[] = {
        {"exit", cmd_exit},
        {"help", cmd_help},
        {"version", cmd_version},
        {"clear", cmd_clear},
        {"echo", cmd_echo},
        {"pwd", cmd_pwd},
        {"cd", cmd_cd},
        {"ls", cmd_ls}
    };

    int found = 0;
    int running = 1;

    while(running){
        char input[1024];
        printf("myshell> ");
        fgets(input, sizeof(input), stdin);
        
        input[strcspn(input, "\n")] = '\0';

        char *ptr = strchr(input, ' ');
        char *command_name;
        char *args;

        if(ptr == NULL){
            command_name = input;
            args = NULL;
        }else{
            *ptr = '\0';
            command_name = input;
            args = ptr + 1;
        }  

        for(int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++){
            if(strcmp(command_name, commands[i].name) == 0){
                found++;
                running = commands[i].action(args);
            }
        }

        if(found == 0){
            printf("Command not found! Try 'help'!\n");
        }

        found = 0;
    }
}