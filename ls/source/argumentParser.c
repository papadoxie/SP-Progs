#include <argumentParser.h>

const char *argp_program_version = "ls 0.1.0";
const char *argp_program_bug_address = "nofilqasim@gmail.com";
const char doc[] = "ls -- list files in a directory";
char args_doc[] = "DIRECTORY";

struct argp_option options[] =
    {
        {0, 0, 0, 0, "Output options:", 1},
        {"directory", 777, "DIRECTORY", OPTION_ARG_OPTIONAL, "The path of the directory to list", 1},
        {"version", 'v', 0, 0, "output version information", 1},
        {0, 0, 0, 0, 0, 0}};

error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    switch (key)
    {
    case ARGP_KEY_ARG:
        if (state->arg_num > 1)
        {
            argp_usage(state);
        }
        // Start actual program
        ls(arg);
        break;

    case ARGP_KEY_END:
        if (state->arg_num < 1)
        {
            const char *pwd = getenv("PWD");
            if (pwd == NULL)
            {
                argp_usage(state);
            }
            ls(pwd);
        }
        break;
    }

    return EXIT_SUCCESS;
}