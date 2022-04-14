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

int compare_entries(const void *ent1, const void *ent2)
{
    return strcmp(((struct dirent *)ent1)->d_name, ((struct dirent *)ent2)->d_name) > 0;
}

void sort_entries(struct dirent **entries, unsigned int count)
{
    qsort(entries, count, sizeof(struct dirent *), compare_entries);
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