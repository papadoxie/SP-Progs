#include <helpers.h>

unsigned int num_entries(struct dirent **entries)
{
    unsigned int count = 0;
    while (entries[count] != NULL)
    {
        count++;
    }
    return count;
}

void filter_hidden(struct dirent **entries, unsigned int count)
{
    unsigned int removed = 0;
    for (unsigned int i = 0; i < count; i++)
    {
        if (!entries[i])
        {
            continue;
        }
        if (entries[i]->d_name[0] == '.')
        {
            removed++;
            entries[i] = NULL;
            for (unsigned int j = i; j < count - 1; j++)
            {
                entries[j] = entries[j + 1];
            }

            entries[count - removed] = NULL;
            i--;
        }
    }
}

void toLower(char *str)
{
    for (unsigned int i = 0; i < strlen(str); i++)
    {
        str[i] = tolower(str[i]);
    }
}

int compare_entries(const void *ent1, const void *ent2)
{
    char *name1 = (*(struct dirent **)ent1)->d_name;
    char *name2 = (*(struct dirent **)ent2)->d_name;

    char tempName1[strlen(name1) + 1];
    char tempName2[strlen(name2) + 1];

    strcpy(tempName1, name1);
    strcpy(tempName2, name2);

    toLower(tempName1);
    toLower(tempName2);

    // Compare names
    return strcmp(tempName1, tempName2);
}

void sort_entries(struct dirent **entries, unsigned int count)
{
    qsort(entries, count, sizeof(struct dirent **), compare_entries);
}

void reverse_entries(struct dirent **entries, unsigned int count)
{
    struct dirent *temp;
    for (unsigned int i = 0; i < count / 2; i++)
    {
        temp = entries[i];
        entries[i] = entries[count - i - 1];
        entries[count - i - 1] = temp;
    }
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
