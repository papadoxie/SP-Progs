#include <argumentParser.h>
#include <ls.h>

int main(int argc, char **argv)
{
    struct arguments arguments;
    memset(arguments.directory, 0, FILENAME_LEN + 1);
    arguments.all = 0;
    arguments.long_format = 0;
    arguments.reverse = 0;
    arguments.sort = 0;
    arguments.time = 0;

    struct argp argp =
        {
            options,
            parse_opt,
            args_doc,
            doc,
            ARGP_CHILDREN,
            HELP_FILTER,
            ARGP_DOMAIN};

    argp_parse(&argp, argc, argv, 0, NULL, &arguments);
    ls(&arguments);
    return EXIT_SUCCESS;
}