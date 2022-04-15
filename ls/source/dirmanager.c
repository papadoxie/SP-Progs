#include <dirmanager.h>

unsigned int dir_size(DIR *dirptr)
{
    struct dirent *entry;
    unsigned int count = 0;
    while ((entry = readdir(dirptr)) != NULL)
    {
        count++;
    }
    rewinddir(dirptr);
    return count;
}

struct dirent **getent(DIR *dirptr)
{
    unsigned int num_entries = dir_size(dirptr);

    struct dirent **entries = malloc(sizeof(struct dirent *) * (dir_size(dirptr) + 1));
    if (entries == NULL)
    {
        return NULL;
    }
    memset(entries, 0, sizeof(struct dirent *) * (dir_size(dirptr) + 1));

    for (unsigned int i = 0; i < num_entries; i++)
    {
        entries[i] = readdir(dirptr);
    }
    
    entries[num_entries] = NULL;

    return entries;
}

void delent(struct dirent **entries)
{
    if (entries == NULL)
    {
        return;
    }
    free(entries);
}