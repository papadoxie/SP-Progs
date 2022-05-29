#include <config.h>

int set_default_config(void)
{
    const char *default_prompt = "[username]@[hostname] [pwd]> ";
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
