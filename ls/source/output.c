#include <output.h>

void print_dirname(struct dirent *entry)
{
    // Check if the entry is a directory
    // Color blue if true
    DIR *temp = opendir(entry->d_name);
    if (temp)
    {
        printf(ESC_FG_BLUE);
        closedir(temp);
    }

    printf("%s", entry->d_name);
    printf(ESC_FG_DEFAULT);
}

unsigned int get_term_width()
{
    struct winsize ws;
    ioctl(STDOUT, TIOCGWINSZ, &ws);
    return ws.ws_col;
}

unsigned int get_max_dirname_length(struct dirent **entries)
{
    unsigned int max_length = 0;
    for (unsigned int i = 0; entries[i]; i++)
    {
        unsigned int length = strlen(entries[i]->d_name);
        if (length > max_length)
        {
            max_length = length;
        }
    }
    return max_length;
}

void print_direntries_oneline(struct dirent **entries)
{
    while (*entries)
    {
        print_dirname(*entries);
        printf("  ");
        entries++;
    }
    printf("\n");
}

void print_direntries_matrix(struct dirent **entries, unsigned int cols)
{
    unsigned int max_dirname_length = get_max_dirname_length(entries);
    unsigned int printed = 0;
    while (*entries)
    {
        unsigned int dirname_length = strlen((*entries)->d_name);
        printed += dirname_length + 2;
        if (printed > cols)
        {
            printf("\n");
            printed = 0;
            continue;
        }
        print_dirname(*entries);

        unsigned int diff = max_dirname_length - dirname_length + 2;
        printf("%*s", diff, " ");

        entries++;
    }
    printf("\n");
}

void print_direntries(struct dirent **entries)
{
    unsigned int cols = get_term_width();

    unsigned int max_print_length = 0;
    for (unsigned int i = 0; entries[i]; i++)
    {
        max_print_length += strlen(entries[i]->d_name) + 2;
        if (max_print_length > cols)
        {
            print_direntries_matrix(entries, cols);
            return;
        }
    }
    print_direntries_oneline(entries);
}

void print_uid(struct stat *entry)
{
    printf("%d", entry->st_uid);
}

void print_stats(struct stat **entries)
{

    while (entries && *entries)
    {
        print_uid(*entries);
        entries++;
    }
}