#include <config.h>

int remove_comment(const char *buf)
{
    char *p = strchr(buf, '#');
    if (p)
    {
        *p = '\0';
        return 1;
    }
    return 0;
}

int set_config(FILE *config_file)
{

    char *line = NULL;
    size_t line_size = 0;

    while(getline(&line, &line_size, config_file))
    {
        char *line_orig = line;
        if (remove_comment(line) && strlen(line) == 0)
        {
            continue;
        }

        free(line_orig);
    }

    return 0;
}

int set_default_config(void)
{
    const char *default_prompt = DEFAULT_PROMPT;
    const int default_prompt_size = strlen(default_prompt) + 1;
    prompt.lines = 1;

    prompt.prompt = malloc(sizeof(char *) * prompt.lines);
    if (!prompt.prompt)
    {
        return 1;
    }

    prompt.prompt[0] = malloc(sizeof(char) * default_prompt_size);
    if (!prompt.prompt[0])
    {
        free(prompt.prompt);
        return 1;
    }

    on_exit(free_prompt, &prompt);
    strncpy(prompt.prompt[0], default_prompt, default_prompt_size);
    return 0;
}
