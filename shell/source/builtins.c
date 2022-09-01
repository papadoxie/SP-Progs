#include <builtins.h>

// Function prototypes
// These won't be declared in the header file
// They must be used via the builtin_funcs array
// which is declared in the header file
int cd(int argc, char **argv);
int pwd(int argc, char **argv);
int exit_shell(int argc, char **argv);
int echo(int argc, char **argv);
int set(int argc, char **argv);
int unset(int argc, char **argv);
int jobs(int argc, __attribute__((unused)) char **argv);

// Builtin functions accessible by the user
builtin_func_t builtin_funcs[] = {
    {"cd", cd},
    {"pwd", pwd},
    {"exit", exit_shell},
    {"echo", echo},
    {"set", set},
    {"unset", unset},
    {"jobs", jobs},
    {NULL, NULL}};

// Array of backround processes
job_t cur_jobs[MAX_BG_PROC];
int num_jobs = 0;

// Change directory
int cd(int argc, char **argv)
{
    if (argc > 2)
    {
        fprintf(stderr, "cd: Too many arguments\n");
        return 1;
    }

    char *dirpath = NULL;
    if (argc == 1)
    {
        dirpath = getenv("HOME");
    }
    else if (argc == 2)
    {
        dirpath = argv[1];
    }

    if (chdir(dirpath) == -1)
    {
        fprintf(stderr, "cd: %s: No such file or directory\n", argv[1]);
        return 1;
    }

    char *cwd = getcwd(NULL, 0);
    setenv("PWD", cwd, 1);
    free(cwd);
    return 0;
}

// Print current working directory
int pwd(int argc,
        __attribute__((unused)) char **argv)
{
    if (argc > 1)
    {
        fprintf(stderr, "pwd: Too many arguments\n");
        return 1;
    }

    char *cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        fprintf(stderr, "pwd: Failed to get current working directory\n");
        return 1;
    }

    printf("%s\n", cwd);
    free(cwd);
    return 0;
}

// Print command line arguments
int echo(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\n");
    return 0;
}

// Set environment variable
int set(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "set: Invalid number of arguments\n");
        return 1;
    }

    if (setenv(argv[1], argv[2], 1) == -1)
    {
        fprintf(stderr, "set: Failed to set environment variable\n");
        return 1;
    }

    return 0;
}

// Unset environment variable
int unset(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "unset: Invalid number of arguments\n");
        return 1;
    }

    if (unsetenv(argv[1]) == -1)
    {
        fprintf(stderr, "unset: Failed to unset environment variable\n");
        return 1;
    }

    return 0;
}

// Create a new backround task
void create_job(command_t *command, pid_t pid)
{
    cur_jobs[num_jobs].pid = pid;
    char *command_name = strdup(command->command);
    cur_jobs[num_jobs].command = command_name;
    cur_jobs[num_jobs].status = 0;
    num_jobs++;
}

int jobs(int argc, __attribute__((unused))char **argv)
{
    if (argc > 1)
    {
        fprintf(stderr, "jobs: Too many arguments\n");
        return 1;
    }

    printf("ID      PID     COMMAND\n");
    for (int i = 0; i < num_jobs; i++)
    {
        printf("%d     %d      %s\n", i + 1, cur_jobs[i].pid, cur_jobs[i].command);
    }
    return 0;
}
// Exit the shell
int exit_shell(__attribute__((unused)) int argc,
               __attribute__((unused)) char **argv)
{
    // exec_buf is defined in shell.c
    // Doesn't exist in headers so declare it here
    extern jmp_buf exec_buf;
    longjmp(exec_buf, 1);
}