#include <ls.h>

void cleanup(DIR *dirptr,
             struct dirent **entries,
             struct stat **ent_stats,
             unsigned int count)
{
    if (dirptr != NULL)
    {
        closedir(dirptr);
    }
    delent(entries);
    delent_stats(ent_stats, count);
}

int ls(const void *args)
{
    struct arguments *arguments = (struct arguments *)args;

    DIR *dirptr = opendir(arguments->directory);
    if (!dirptr)
    {
        char error_msg[ERROR_MSG_LEN];
        snprintf(error_msg, ERROR_MSG_LEN, "Error opening %s", arguments->directory);
        perror(error_msg);
        cleanup(dirptr, NULL, NULL, 0);
        return EXIT_FAILURE;
    }

    // Get all the entries in the directory
    struct dirent **entries = getent(dirptr);
    if (!entries)
    {
        perror("Error getting directory entries");
        cleanup(dirptr, entries, NULL, 0);
        return EXIT_FAILURE;
    }
    // Count the number of entries
    unsigned int count = num_entries(entries);

    // Sort entries
    sort_entries(entries, count);

    // Remove hidden files
    if (!arguments->all)
    {
        filter_hidden(entries, count);
        // Recount remaining entries
        count = num_entries(entries);
    }
    
    // Reverse entries
    if (arguments->reverse)
    {
        reverse_entries(entries, count);
    }

    // Not initializing until flags are set
    struct stat **ent_stats = NULL;
    if (arguments->long_format || arguments->time)
    {
        ent_stats = long_listing(entries, count);
        if (!ent_stats)
        {
            perror("Error getting directory entries stats");
            cleanup(dirptr, entries, ent_stats, count);
            return EXIT_FAILURE;
        }
        PRINT_ENTS(ent_stats);
    }

    PRINT_ENTS(entries);

    cleanup(dirptr, entries, ent_stats, count);
    return EXIT_SUCCESS;
}