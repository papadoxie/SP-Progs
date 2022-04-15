#include <output.h>

void print_dirname(struct dirent *entry)
{
    puts(entry->d_name);
}

void print_direntries(struct dirent **entries)
{
    while (*entries != NULL)
    {
        print_dirname(*entries);
        entries++;
    }
}

void print_uid(struct stat *entry)
{
    printf("%i\n", entry->st_uid);

}

void print_stats(struct stat **entries)
{
    while (*entries != NULL)
    {
        print_uid(*entries);
        entries++;
    }
}