#include <more.h>

int main(int argc, char **argv)
{
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