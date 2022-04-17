#include <ls.h>

void cleanup(DIR *dirptr, struct dirent **entries, char *old_directory)
{
    if (dirptr)
    {
        closedir(dirptr);
    }

    if (old_directory)
    {
        chdir(old_directory);
    }

    delent(entries);
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
        cleanup(dirptr, NULL, NULL);
        return EXIT_FAILURE;
    }

    // Change working directory
    char old_directory[PATH_MAX];
    getcwd(old_directory, PATH_MAX);
    chdir(arguments->directory);

    // Get all the entries in the directory
    struct dirent **entries = getent(dirptr);
    if (!entries)
    {
        perror("Error getting directory entries");
        cleanup(dirptr, entries, old_directory);
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

    if (arguments->long_format || arguments->human_readable)
    {
        print_longlisting(entries, arguments);
    }else
    {
        print_normal(entries);
    }


    cleanup(dirptr, entries, old_directory);
    return EXIT_SUCCESS;
}