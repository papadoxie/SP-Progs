#include <execute.h>

int exec_external(process_t *cur_proc)
{
    cur_proc->pid = fork();

    if (!cur_proc->pid)
    {
        cur_proc->status = execvp(cur_proc->command->command,
                                  cur_proc->command->argv);
        if (cur_proc->status == -1)
        {
            printf("cronshell: Unknown command: %s\n", cur_proc->command->command);
            _Exit(EXIT_FAILURE);
        }
    }
    waitpid(cur_proc->pid, &cur_proc->status, 0);
    return WEXITSTATUS(cur_proc->status);
}

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

    int final_status = 0;
    for (uint32_t i = 0; i < commands->num_commands; i++)
    {
        process_t cur_proc;
        cur_proc.command = commands->commands[i];

        final_status = exec_builtin(&cur_proc);
        if (final_status == BUILTIN_NO_EXEC)
        {
            final_status = exec_external(&cur_proc);
        }
    }
    free(processes);
    return final_status;
}