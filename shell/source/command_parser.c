#include <command_parser.h>

char *read_commandline(FILE *stream)
{
    char *commandline = NULL;
    size_t commandline_size = 0;

    getline(&commandline, &commandline_size, stream);

    if (ferror(stream))
    {
        fprintf(stderr, "Error reading commandline\n");
        if (commandline)
        {
            free(commandline);
        }
        return NULL;
    }

    return commandline;
}

command_t *__internal_parse_command(const char *command_string, uint pipe_val)
{
    command_t *command = malloc(sizeof(command_t));
    if (!command)
    {
        perror("Could not process command");
        return NULL;
    }

    command->instream = NULL;
    command->outstream = NULL;
    command->errstream = NULL;

    switch (pipe_val)
    {
    case PIPE_OUT:
        command->piped_out = true;
        command->piped_in = false;
        break;
    case PIPE_IN:
        command->piped_out = false;
        command->piped_in = true;
        break;
    case PIPE_BOTH:
        command->piped_out = true;
        command->piped_in = true;
        break;
    default:
        break;
    }

    char *command_copy = strdup(command_string);
    // Make a copy so we can free after strtok ruins the original
    char *command_copy_orig = command_copy;

    command_copy = strtok(command_copy, ARG_DELIMITERS);  
    command->command = strdup(command_copy);

    command->argc = 0;
    command->argv = NULL;

    while (command_copy)
    {
        command->argc++;
        command->argv = realloc(command->argv, sizeof(char *) * (command->argc));
        if (!command->argv)
        {
            perror("Could not process command");
            free(command->command);
            free(command_copy_orig);
            free(command);
            return NULL;
        }

        command->argv[ARG_INDEX] = strdup(command_copy);
        command_copy = strtok(NULL, ARG_DELIMITERS);
    }

    // Place NULL at end of argv
    command->argv = realloc(command->argv, sizeof(char *) * (command->argc + 1));
    command->argv[command->argc] = NULL;

    // Free the copy
    free(command_copy_orig);
    return command;
}

uint __internal_set_pipe(char *command_string)
{
    if (!strchr(command_string, PIPE))
    {
        return NO_PIPE;
    }
    if (strchr(command_string, PIPE) == strrchr(command_string, PIPE))
    {
        return PIPE_OUT;
    }
    if (strchr(command_string, PIPE) == command_string)
    {
        if(strrchr(command_string, PIPE) != command_string)
        {
            return PIPE_IN;
        }
        return PIPE_BOTH;
    }
    return NO_PIPE;
}

uint __internal_set_pipe_prev(uint pipe_val, uint prev_pipe_val)
{
    if (prev_pipe_val == PIPE_OUT || prev_pipe_val == PIPE_BOTH)
    {
        if(pipe_val == PIPE_OUT)
        {
            return PIPE_BOTH;
        }
        return PIPE_IN;
    }
    return pipe_val;
}

commands_t *parse_commandline(const char *command_line)
{
    commands_t *commands = malloc(sizeof(commands_t));
    commands->num_commands = 0;
    commands->commands = NULL;

    char *command_string = strdup(command_line);
    // Make a copy so we can free after strtok ruins the original
    char *command_string_orig = command_string;
    if (!command_string)
    {
        perror("Could not process command string");
        return NULL;
    }

    command_string = strtok(command_string, COMMAND_DELIMITERS);

    uint prev_pipe_val = NO_PIPE;
    while (command_string)
    {
        uint pipe_val = __internal_set_pipe(command_string);
        if(pipe_val)
        {
            command_string = strtok(NULL, PIPE_DELIMITERS);
        }
        pipe_val = __internal_set_pipe_prev(pipe_val, prev_pipe_val);
        prev_pipe_val = pipe_val;

        commands->commands = realloc(commands->commands,
                                     sizeof(command_t *) * (commands->num_commands + 1));
        if (!commands->commands)
        {
            perror("Could not process command string");
            free(command_string_orig);
            free(commands);
            return NULL;
        }

        commands->commands[commands->num_commands] = __internal_parse_command(command_string, pipe_val);
        if (!commands->commands[commands->num_commands])
        {
            perror("Could not process command string");
            free(command_string_orig);
            free(commands);
            return NULL;
        }
        commands->num_commands++;
        command_string = strtok(NULL, COMMAND_DELIMITERS);
    }

    free(command_string_orig);
    return commands;
}

void free_commands(commands_t *commands)
{
    for (uint32_t i = 0; i < commands->num_commands; i++)
    {
        free(commands->commands[i]->command);

        for (int j = 0; j < commands->commands[i]->argc; j++)
        {
            free(commands->commands[i]->argv[j]);
        }
        free(commands->commands[i]->argv);
        free(commands->commands[i]);
    }
    free(commands->commands);
    free(commands);
}
