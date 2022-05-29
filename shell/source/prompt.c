#include <prompt.h>

prompt_t prompt;

void print_prompt(void)
{
    for (int i = 0; i < prompt.lines; i++)
    {
        printf("%s", prompt.prompt[i]);
    }
}

void free_prompt(__attribute__((unused)) int status, void *prompt_struct)
{
    prompt_t *prompt = (prompt_t *)prompt_struct;
    for (int i = 0; i < prompt->lines; i++)
    {
        free(prompt->prompt[i]);
    }
    free(prompt->prompt);
}