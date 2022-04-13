#include <dirmanager.h>

// Number of directory entries successfully read
static unsigned int n_entries = 0;

struct dirent **getent(DIR *dirptr)
{
    // Just get a pointer to realloc later
    struct dirent **entries = malloc(sizeof(struct dirent *) * 0);
    if (entries == NULL)
    {
        return NULL;
    }

    do
    {
        if (n_entries % 32 == 0)
        {
            entries = realloc(entries, sizeof(struct dirent *) * (MEMSIZE * MEM_MULTIPLE));
            if (entries == NULL)
            {
                return NULL;
            }
        }

        struct dirent *entry = readdir(dirptr);
        if (entry == NULL)
        {
            entries[n_entries] = NULL;
            break;
        }

        entries[n_entries++] = entry;
    } while (true);

    return entries;
}

void delent(struct dirent **entries)
{
    free(entries);
    n_entries = 0;
}