#include <argumentParser.h>

error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;

    switch (key)
    {
    case ARGP_KEY_ARG:
        if (state->arg_num > 1)
        {
            argp_usage(state);
        }
        strncpy(arguments->filename, arg, 255);
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