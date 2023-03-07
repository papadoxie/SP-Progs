#include <argumentParser.h>
#include <signal.h>
#include <sigwinch.h>

int main(int argc, char **argv)
{
    init_sigwinch_handler();
    // Register SIGWINCH handler to handle window resizing on runtime
    signal(SIGWINCH, handle_sigwinch);
    // Raise SIGWINCH ourselves to initialize rows and cols
    raise(SIGWINCH);

    struct argp argp =
        {
            options,
            parse_opt,
            args_doc,
            doc,
            ARGP_CHILDREN,
            HELP_FILTER,
            ARGP_DOMAIN};

    argp_parse(&argp, argc, argv, 0, NULL, NULL);
    return EXIT_SUCCESS;
}