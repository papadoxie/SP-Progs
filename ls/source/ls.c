#include <ls.h>

void print_entry(struct dirent *entry)
{
    printf("%s\n", entry->d_name);
}

void print_entries(struct dirent **entries)
{
    while (*entries != NULL)
    {
        print_entry(*entries);
        entries++;
    }
}

int ls(const char *directory)
{
    DIR *dirptr = opendir(directory);
    if (dirptr == NULL)
    {
        perror("Error opening directory");
        return EXIT_FAILURE;
    }

    struct dirent **entries = getent(dirptr);
    if (entries == NULL)
    {
        perror("Error getting directory entries");
        return EXIT_FAILURE;
    }

    print_entries(entries);
    delent(entries);

    closedir(dirptr);
    
    return EXIT_SUCCESS;
}