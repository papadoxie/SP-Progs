#include <prompt.h>

prompt_t prompt;

char *get_username(char *buf, size_t buf_size);
char *get_hostname(char *buf, size_t buf_size);
char *get_pwd(char *buf, size_t buf_size);

static prompt_modifier prompt_modifiers[] = {
    {"username", get_username},
    {"hostname", get_hostname},
    {"pwd", get_pwd},
    {NULL, NULL}};

int apply_modifier(char *buf, const char *modifier, size_t buf_size)
{
    prompt_modifier *modifier_ptr = prompt_modifiers;
    while (modifier_ptr->modifier_index)
    {
        if (strcmp(modifier_ptr->modifier_index, modifier) == 0)
        {
            modifier_ptr->modifier(buf, buf_size);
            return 1;
        }
        modifier_ptr++;
    }
    return 0;
}

void print_prompt(void)
{
    printf("\n");
    for (int i = 0; i < prompt.lines; i++)
    {
        if (i > 0)
        {
            printf("\n");
        }
        char *prompt_line = strdup(prompt.prompt[i]);
        // Make a copy so we can free after strtok ruins the original
        char *prompt_line_orig = prompt_line;
        prompt_line = strtok(prompt_line, MODIFIER_DELIMITERS);
        while (prompt_line)
        {
            char mod_buf[MODIFIER_LENGTH];

            printf("%s",
                   apply_modifier(mod_buf, prompt_line, MODIFIER_LENGTH) ? mod_buf : prompt_line);

            prompt_line = strtok(NULL, MODIFIER_DELIMITERS);
        }
        free(prompt_line_orig);
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

//! Write backups for these
char *get_username(char *buf, size_t buf_size)
{
    char *username = getenv("USER");
    strncpy(buf, username ? username : "user", buf_size);
    return buf;
}

char *get_hostname(char *buf, size_t buf_size)
{
    if (gethostname(buf, buf_size) == -1)
    {
        strncpy(buf, "host", buf_size);
    }
    return buf;
}

char *get_pwd(char *buf, size_t buf_size)
{
    char *pwd = getenv("PWD");
    strncpy(buf, pwd ? pwd : "pwd", buf_size);
    return buf;
}
