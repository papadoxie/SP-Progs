#include <argumentParser.h>

const char *argp_program_version = "more 0.1.0";
const char *argp_program_bug_address = "nofilqasim@gmail.com";
const char doc[] = "more -- a program to display a file one screenful at a time";
char args_doc[] = "FILE";

struct argp_option options[] =
    {
        {0, 0, 0, 0, "Output options:", 1},
        {"filename", 777, "FILENAME", 0, "The name of the file to display", 1},
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
        more(arg);
        break;

    case ARGP_KEY_END:
        if (state->arg_num < 1)
        {
            argp_usage(state);
        }
        break;
    }

    return EXIT_SUCCESS;
}