#include <shell.h>

int init_shell(void)
{
    const char *config_file_paths[] = {
        "./.cronconfig",
        "~/.config/.cronconfig",
        "tools/.cronconfig",    // For testing
        "../tools/.cronconfig", // For testing
        NULL};

    FILE *config_file = NULL;
    const char **path = config_file_paths;
    while (*path)
    {
        config_file = fopen(*path, "r");
        if (config_file)
        {
            break;
        }
        path++;
    }

    if (!config_file)
    {
        set_default_config();
        return 0;
    }

    fclose(config_file);
    return 0;
}

int interactive_shell(void)
{
    while(true)
    {
        print_prompt();
    }
    return 0;
}
