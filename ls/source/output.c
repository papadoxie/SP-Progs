#include <output.h>

void print_dirent(struct dirent *entry)
{
    printf("%s\n", entry->d_name);
}

void print_direntries(struct dirent **entries)
{
    while (*entries != NULL)
    {
        print_dirent(*entries);
        entries++;
    }
}

void print_stat(struct stat *entry)
{
    printf("%ld\n", entry->st_ino);
}

void print_stats(struct stat **entries)
{
    while (*entries != NULL)
    {
        print_stat(*entries);
        entries++;
    }
}