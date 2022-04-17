#include <argumentParser.h>
#include <locale.h>
#include <ls.h>

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");

    // Initialize argument parser
    struct arguments arguments;
    memset(arguments.directory, 0, FILENAME_LEN + 1);

    for (unsigned int i = 0; i < MAX_DIRS; i++)
    {
        memset(arguments.directories[i], 0, FILENAME_LEN + 1);
    }

    arguments.all = 0;
    arguments.long_format = 0;
    arguments.reverse = 0;
    arguments.sort = 0;
    arguments.human_readable = 0;

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

    // Go through all the directories
    for (unsigned int i = 0; i < MAX_DIRS; i++)
    {
        if (strlen(arguments.directories[i]) > 0)
        {
            // Print newline if more than one directory
            if (i)
            {
                printf("\n");
            }

            // Copy dirname to variable
            strncpy(arguments.directory, arguments.directories[i], FILENAME_LEN);
            ls(&arguments);
        }
    }
    return EXIT_SUCCESS;
}