#include <argumentParser.h>

const char *argp_program_version = "ls 0.1.0";
const char *argp_program_bug_address = "nofilqasim@gmail.com";
const char doc[] = "ls -- list files in a directory";
char args_doc[] = "DIRECTORY";

struct argp_option options[] =
    {
        {0, 0, 0, 0, "Output options:", 1},
        {"directory", 777, "DIRECTORY", OPTION_ARG_OPTIONAL, "The path of the directory to list", 1},
        {"all", 'a', 0, 0, "List all files, including hidden files", 1},
        {"long", 'l', 0, 0, "List in long format", 1},
        {"reverse", 'r', 0, 0, "Reverse the order of the output", 1},
        {"sort", 's', 0, 0, "Sort the output", 1},
        {"time", 't', 0, 0, "Sort by time", 1},
        {"help", 'h', 0, 0, "Show this help", 1},
        {"version", 'v', 0, 0, "output version information", 1},
        {0, 0, 0, 0, 0, 0}};

error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;
    switch (key)
    {
    case 'a':
        arguments->all = 1;
        break;
    
    case 'l':
        arguments->long_format = 1;
        break;
    
    case 'r':
        arguments->reverse = 1;
        break;
    
    case 's':
        arguments->sort = 1;
        break;
    
    case 't':
        arguments->time = 1;
        break;
    
    case 'h':
        argp_state_help(state, stdout, ARGP_HELP_LONG);
        exit(0);
    
    case 'v':
        printf("%s\n", argp_program_version);
        exit(0);

    case ARGP_KEY_ARG:
        if (state->arg_num > 1)
        {
            argp_usage(state);
        }
        strncpy(arguments->directory, arg, 255);
        break;

    case ARGP_KEY_END:
        if (state->arg_num < 1)
        {
            const char *pwd = getenv("PWD");
            if (pwd == NULL)
            {
                argp_usage(state);
            }
            strncpy(arguments->directory, pwd, 255);
        }
        break;
    }

    return EXIT_SUCCESS;
}