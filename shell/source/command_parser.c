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

// Tokenize the command line
// This function returns a malloc'd array of strings. Must be freed by caller
char **__internal_tokenize(char *command_string)
{
    char **tokens = NULL;
    uint num_tokens = 0;

    char *command_string_copy = strdup(command_string);
    char *command_string_copy_orig = command_string_copy;

    char *token = strtok(command_string_copy, ARG_DELIMITERS);
    while (token)
    {
        num_tokens++;
        tokens = realloc(tokens, sizeof(char *) * num_tokens);
        if (!tokens)
        {
            perror("Could not process command");
            return NULL;
        }

        tokens[num_tokens - 1] = strdup(token);
        token = strtok(NULL, ARG_DELIMITERS);
    }

    tokens = realloc(tokens, sizeof(char *) * (num_tokens + 1));
    tokens[num_tokens] = NULL;
    free(command_string_copy_orig);

    return tokens;
}

// Set streams for the command
// redirect_type is just a token from the command line, like <, >, or >>
int __internal_set_stream(command_t *command, char **redirect_type)
{
    char **filename = redirect_type;
    filename++;

    bool file_exists = *filename ? true : false;

    if (!strcoll(*redirect_type, REDIRECT_IN))
    {
        if (file_exists)
        {
            command->instream = strdup(*filename);
            return command->instream ? 0 : -1;
        }
        fprintf(stderr, "Error: No input file specified\n");
        return -1;
    }
    if (!strcoll(*redirect_type, REDIRECT_OUT))
    {
        if (file_exists)
        {
            command->outstream = strdup(*filename);
            return command->outstream ? 0 : -1;
        }
        fprintf(stderr, "Error: No output file specified\n");
        return -1;
    }
    if (!strcoll(*redirect_type, REDIRECT_APPEND))
    {
        if (file_exists)
        {
            command->outstream = strdup(*filename);
            command->append = true;
            return command->outstream ? 0 : -1;
        }
        fprintf(stderr, "Error: No output file specified\n");

        return -1;
    }
    if (!strcoll(*redirect_type, REDIRECT_ERR))
    {
        if (file_exists)
        {
            command->errstream = strdup(*filename);
            return command->errstream ? 0 : -1;
        }
        fprintf(stderr, "Error: No output file specified\n");

        return -1;
    }
    return 1;
}

// Initialize a new command struct and return it
// This function returns a malloc'd pointer. Must be freed by caller
command_t *create_command(void)
{
    command_t *command = malloc(sizeof(command_t));
    command->command = NULL;
    command->argc = 0;
    command->argv = NULL;
    command->instream = NULL;
    command->outstream = NULL;
    command->errstream = NULL;
    command->append = false;
    command->piped_out = false;
    command->piped_in = false;
    command->is_bg = false;
    return command;
}

int __internal_parse_tokens(char **tokens, commands_t *commands)
{
    // Is the previous command piped out?
    bool prev_pipe = false;
    // Read till all tokens are used

    while (*tokens)
    {
        // Create a new command to add to commands
        command_t *command = create_command();
        // Allocate space for a new command
        commands->commands = realloc(commands->commands,
                                     sizeof(command_t *) * (commands->num_commands + 1));
        if (!command || !commands->commands)
        {
            perror("Could not process command");
            return -1;
        }

        // Set piped_in if previous command piped out
        if (prev_pipe)
        {
            command->piped_in = true;
            prev_pipe = false;
        }

        // Set command name
        command->command = strdup(*tokens);

        // Read till we hit a pipe or all tokens are used
        while (*tokens)
        {
            // Set piped_out
            if (!strcoll(*tokens, PIPE))
            {
                command->piped_out = true;
                prev_pipe = true;
                tokens++;
                break;
            }

            if(!strcoll(*tokens, BG))
            {
                command->is_bg = true;
                tokens++;
                break;
            }

            // Check if we need to set a stream
            int stream_set = __internal_set_stream(command, tokens);
            if (!stream_set)
            {
                tokens += 2;
                continue;
            }
            // No filename after redirect token
            if (stream_set == -1)
            {
                return -1;
            }

            // Add arguments to command
            command->argc++;
            command->argv = realloc(command->argv, sizeof(char *) * (command->argc));
            if (!command->argv)
            {
                perror("Could not process command");
                return -1;
            }
            command->argv[ARG_INDEX] = strdup(*tokens);
            tokens++;
        }
        // Place NULL at end of argv
        command->argv = realloc(command->argv, sizeof(char *) * (command->argc + 1));
        command->argv[command->argc] = NULL;

        // Add command to commands
        commands->commands[commands->num_commands] = command;
        commands->num_commands++;
    }
    return 0;
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

    while (command_string)
    {
        char **tokens = __internal_tokenize(command_string);
        if (__internal_parse_tokens(tokens, commands))
        {
            free(command_string_orig);
            free_commands(commands);
            return NULL;
        }
        // Free tokens
        // Make a copy so we can free the original pointer after incrementing
        char **tokens_orig = tokens;
        while (*tokens)
        {
            free(*tokens);
            tokens++;
        }
        free(tokens_orig);

        command_string = strtok(NULL, COMMAND_DELIMITERS);
    }

    free(command_string_orig);
    return commands;
}

void free_commands(commands_t *commands)
{
    for (uint32_t i = 0; i < commands->num_commands; i++)
    {
        command_t *command = commands->commands[i];
        free(command->command);
        free(command->instream);
        free(command->outstream);
        free(command->errstream);

        for (int j = 0; j < commands->commands[i]->argc; j++)
        {
            free(command->argv[j]);
        }
        free(command->argv);
        free(command);
    }
    free(commands->commands);
    free(commands);
}
