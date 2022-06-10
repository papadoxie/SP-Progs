#include <shell.h>

int init_shell(void)
{
    // Configs will be read from these files in order
    const char *config_file_paths[] = {
        "./.cronconfig",
        "~/.config/.cronconfig",
        "/etc/cronconfig",
        "tools/.cronconfig",    //? For testing
        "../tools/.cronconfig", //? For testing
        NULL};

    FILE *config_file = NULL;
    const char **path = config_file_paths;

    // Using pointer so won't have to keep track of length in case 
    // new config paths are added
    while (*path)
    {
        config_file = fopen(*path, "r");
        if (config_file)
        {
            break;
        }
        path++;
    }

    // If no config file found, set default config
    if (!config_file)
    {
        set_default_config();
        return 0;
    }
    
    //TODO change this to parse config file when available
    set_default_config();

    fclose(config_file);
    return 0;
}

// Jump buffer for exit routines
// Won't be provided in headers
// Must be declared using extern in source file
jmp_buf exit_buf;

// Start of interactive shell
int interactive_shell(void)
{
    char *command_string = NULL;
    commands_t *commands = NULL;

    // Cleanup on exit
    if(setjmp(exit_buf))
    {
        free_commands(commands ? commands : NULL);
        free(command_string ? command_string : NULL);
        return 0;
    }

    while (true)
    {
        // Display prompt
        print_prompt();
        
        // Read command line from stdin
        command_string = read_commandline(stdin);
        if (!command_string)
        {
            continue;
        }
        
        // Parse command line into command structs
        commands = parse_commandline(command_string);
        if (!commands)
        {
            continue;
        }
        
        // Execute commands in commands struct
        execute(commands);

        // Cleanup on each iteration
        free_commands(commands ? commands : NULL);
        commands = NULL;
        free(command_string ? command_string : NULL);
        command_string = NULL;
    }
    return 0;
}
