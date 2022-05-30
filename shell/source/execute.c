#include <execute.h>

int execute(commands_t *commands)
{
    process_t *processes = malloc(sizeof(process_t) * commands->num_commands);

    for (uint32_t i = 0; i < commands->num_commands; i++)
    {
        process_t cur_proc;
        cur_proc.command = commands->commands[i];
        cur_proc.pid = fork();

        if (!cur_proc.pid)
        {
            cur_proc.status = execvp(cur_proc.command->command,
                                     cur_proc.command->arguments);
            if (cur_proc.status == -1)
            {
                printf("cronShell: Unknown command: %s\n", cur_proc.command->command);
                exit(EXIT_FAILURE);
            }
        }
        waitpid(cur_proc.pid, &cur_proc.status, 0);
    }

    free(processes);
    return 0;
}