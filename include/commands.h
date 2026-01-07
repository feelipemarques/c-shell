#ifndef COMMANDS_H
#define COMMANDS_H

typedef struct command {
    char name[16];
    int (*action)(int argc, char **argv);
} Commands;

typedef enum {
    REDIRECT_NONE,
    REDIRECT_IN,
    REDIRECT_OUT
} RedirectType;

typedef struct operator {
    RedirectType type;
    char *filename;
} RedirectInfo;

int cmd_exit(int argc, char **argv);
int cmd_help(int argc, char **argv);
int cmd_version(int argc, char **argv);
int cmd_clear(int argc, char **argv);
int cmd_echo(int argc, char **argv);
int cmd_cd(int argc, char **argv);
int cmd_pwd(int argc, char **argv);
int cmd_ls(int argc, char **argv);
int cmd_mkdir(int argc, char **argv);
int cmd_rmdir(int argc, char **argv);
int cmd_cp(int argc, char **argv);
int cmd_cat(int argc, char **argv);
int cmd_touch(int argc, char **argv);
int cmd_rm(int argc, char **argv);

#endif