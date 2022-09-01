#include <execute.h>

void flush_streams(void)
{
    fflush(stdout);
    fflush(stderr);
}

void buffer_streams(void)
{
    setvbuf(stdin, NULL, _IOLBF, 0);
    setvbuf(stdout, NULL, _IOLBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

// Redirect streams
void set_streams(command_t *command)
{
    freopen(command->instream, "r", stdin);
    if (command->append)
    {
        freopen(command->outstream, "ab+", stdout);
    }
    else
    {
        freopen(command->outstream, "w", stdout);
    }
    freopen(command->errstream, "w", stderr);
    buffer_streams();
    flush_streams();
}

// Reset Streams to default
void reset_streams(char *tty)
{
    freopen(tty, "r", stdin);
    freopen(tty, "w", stdout);
    freopen(tty, "w", stderr);
    buffer_streams();
    flush_streams();
}

void set_pipe(int *pipe_fd, command_t *command)
{
    if (command->piped_in)
    {
        close(pipe_fd[PIPE_WRITE]);
        dup2(pipe_fd[PIPE_READ], STDIN_FILENO);
        return;
    }
    if (command->piped_out)
    {
        close(pipe_fd[PIPE_READ]);
        dup2(pipe_fd[PIPE_WRITE], STDOUT_FILENO);
        return;
    }
}

void unset_pipe(int *pipe_fd, command_t *command)
{
    if (command->piped_in)
    {
        close(pipe_fd[PIPE_READ]);
        return;
    }
    if (command->piped_out)
    {
        close(pipe_fd[PIPE_WRITE]);
        return;
    }
}

// Execute command from PATH
int exec_external(process_t *cur_proc)
{
    cur_proc->pid = fork();
    if (!cur_proc->pid)
    {
        set_pipe(cur_proc->pipe_fd, cur_proc->command);
        cur_proc->status = execvp(cur_proc->command->command,
                                  cur_proc->command->argv);
        if (cur_proc->status == -1)
        {
            printf("cronshell: Unknown command: %s\n", cur_proc->command->command);
            _Exit(EXIT_FAILURE);
        }
        _Exit(EXIT_SUCCESS);
    }

    // Close pipes
    unset_pipe(cur_proc->pipe_fd, cur_proc->command);
    // Dont wait if background process
    if(cur_proc->command->is_bg)
    {
        extern void create_job(command_t *process, pid_t pid);
        create_job(cur_proc->command, cur_proc->pid);
        return 0;
    }
    waitpid(cur_proc->pid, &cur_proc->status, 0);
    return WEXITSTATUS(cur_proc->status);
}

// Execute command from builtin functions
int exec_builtin(process_t *cur_proc)
{
    builtin_func_t *builtin_func_ptr = builtin_funcs;

    while (builtin_func_ptr->function_index)
    {
        if (strcmp(builtin_func_ptr->function_index, cur_proc->command->command) == 0)
        {
            cur_proc->status = builtin_func_ptr->function(cur_proc->command->argc,
                                                          cur_proc->command->argv);
            return cur_proc->status;
        }
        builtin_func_ptr++;
    }
    return BUILTIN_NO_EXEC;
}

jmp_buf exec_buf;
// Execute all the commands in queue
int execute(commands_t *commands)
{
    process_t *processes = malloc(sizeof(process_t) * commands->num_commands);

    if (setjmp(exec_buf))
    {
        free(processes ? processes : NULL);
        extern jmp_buf exit_buf;
        longjmp(exit_buf, 1);
    }

    if (!processes)
    {
        perror("Could not run processes");
        return -1;
    }

    // Save default streams to restore later
    char *tty = ttyname(STDIN_FILENO);

    // Create pipe for redirection
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
    {
        perror("Could not create pipe");
        return -1;
    }

    // Status of last command
    int final_status = 0;
    for (uint32_t i = 0; i < commands->num_commands; i++)
    {
        process_t cur_proc = {
            .command = commands->commands[i],
            .pipe_fd = pipe_fd,
            .pid = 0,
            .status = 0,
        };

        set_streams(cur_proc.command);

        final_status = exec_builtin(&cur_proc);
        if (final_status == BUILTIN_NO_EXEC)
        {
            final_status = exec_external(&cur_proc);
        }
    }

    reset_streams(tty);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(processes);
    processes = NULL;
    return final_status;
}