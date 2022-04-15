#include <longListing.h>

struct stat **long_listing(struct dirent **entries, unsigned int num_entries)
{
    struct stat **ent_stats = malloc(sizeof(struct stat *) * num_entries);
    if (ent_stats == NULL)
    {
        return NULL;
    }

    unsigned int allocd = 0;
    for (unsigned int i = 0; i < num_entries; i++)
    {
        ent_stats[i] = malloc(sizeof(struct stat));
        if (ent_stats[i] == NULL)
        {
            delent_stats(ent_stats, allocd);
            return NULL;
        }
        allocd++;
        if (stat(entries[i]->d_name, ent_stats[i]) == -1)
        {
            delent_stats(ent_stats, allocd);
            return NULL;
        }
    }
    return ent_stats;
}

void delent_stats(struct stat **ent_stats, unsigned int num_entries)
{
    if (ent_stats == NULL)
    {
        return;
    }
    for (unsigned int i = 0; i < num_entries; i++)
    {
        free(ent_stats[i]);
    }
    free(ent_stats);
}