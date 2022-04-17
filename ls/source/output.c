#include <output.h>

void print_name(struct dirent *entry, struct stat *stats)
{
    if (stats->st_mode & S_IFDIR)
    {
        printf(ESC_FG_BLUE);
    }
    else if (stats->st_mode & (S_IEXEC))
    {
        printf(ESC_FG_GREEN);
    }

    printf("%s", entry->d_name);
    printf(ESC_FG_DEFAULT);
}

void print_normal_oneline(struct dirent **entries)
{
    while (*entries)
    {
        struct stat stats;
        stat((*entries)->d_name, &stats);

        print_name(*entries, &stats);
        printf("  ");

        entries++;
    }
    printf("\n");
}

void print_normal_matrix(struct dirent **entries, unsigned int cols)
{
    unsigned int max_dirname_length = get_max_dirname_length(entries);
    unsigned int max_printable_cols = (cols / (max_dirname_length + 2));
    unsigned int max_printable_rows = num_entries(entries) / max_printable_cols;
    unsigned int count = num_entries(entries);

    for (unsigned int i = 0; i < max_printable_rows; i++)
    {
        for (unsigned int j = 0; j < max_printable_cols; j++)
        {
            if((i + (j * max_printable_rows)) >= count)
            {
                break;
            }
            struct dirent *entry = entries[i + (j * max_printable_rows)];
            if (!entry)
            {
                continue;
            }

            struct stat stats;
            stat(entry->d_name, &stats);
            print_name(entry, &stats);

            unsigned int dirname_length = strlen(entry->d_name);
            unsigned int diff = (max_dirname_length - dirname_length) + 2;
            printf("%*s", diff, " ");
        }
        printf("\n");
    }
    printf("\n");
}

void print_normal(struct dirent **entries)
{
    unsigned int cols = get_term_width();

    unsigned int max_print_length = 0;
    for (unsigned int i = 0; entries[i]; i++)
    {
        max_print_length += strlen(entries[i]->d_name) + 2;
        if (max_print_length > cols)
        {
            print_normal_matrix(entries, cols);
            return;
        }
    }
    print_normal_oneline(entries);
}

void print_username(struct stat *stats)
{
    struct passwd *pw = getpwuid(stats->st_uid);
    if (!pw)
    {
        printf(ESC_FG_RED "??????????" ESC_FG_DEFAULT);
        return;
    }
    printf(ESC_FG_YELLOW "%*s" ESC_FG_DEFAULT, USERNAME_LEN, pw->pw_name);
}

void print_groupname(struct stat *stats)
{
    struct group *gr = getgrgid(stats->st_gid);
    if (!gr)
    {
        printf(ESC_FG_RED "??????????" ESC_FG_DEFAULT);
        return;
    }
    printf(ESC_FG_CYAN "%*s" ESC_FG_DEFAULT, GROUP_LEN, gr->gr_name);
}

void print_filetype(struct stat *stats)
{
    if (stats->st_mode & S_IFDIR)
    {
        printf(ESC_FG_BLUE "d" ESC_FG_DEFAULT);
        return;
    }
    if (!(stats->st_mode & S_IFREG))
    {
        if (stats->st_mode & S_IFLNK)
        {
            printf(ESC_FG_CYAN "l" ESC_FG_DEFAULT);
            return;
        }
        if (stats->st_mode & S_IFSOCK)
        {
            printf(ESC_FG_MAGENTA "s" ESC_FG_DEFAULT);
            return;
        }
        if (stats->st_mode & S_IFCHR)
        {
            printf(ESC_FG_RED "c" ESC_FG_DEFAULT);
            return;
        }
        if (stats->st_mode & S_IFBLK)
        {
            printf(ESC_FG_GREEN "b" ESC_FG_DEFAULT);
            return;
        }
        if (stats->st_mode & S_IFIFO)
        {
            printf(ESC_FG_YELLOW "p" ESC_FG_DEFAULT);
            return;
        }
    }
    printf(".");
}

char *human_readable_size(unsigned long size, char *__restrict buffer)
{
    int i = 0;
    const char *units[] = {"B", "K", "M", "G", "T", "P", "E", "Z", "Y"};

    while (size > 1024)
    {
        size /= 1024;
        i++;
    }

    snprintf(buffer, SIZE_LEN, "%ld%s", size, units[i]);
    return buffer;
}

void print_size(struct stat *stats, int human_readable)
{
    printf(ESC_FG_GREEN);
    if (human_readable)
    {
        char hr_buffer[SIZE_LEN];
        printf("%*s", SIZE_LEN, human_readable_size(stats->st_size, hr_buffer));
        printf(ESC_FG_DEFAULT);
        return;
    }
    printf("%*ld", SIZE_LEN, stats->st_size);
    printf(ESC_FG_DEFAULT);
}

void print_permissions(struct stat *stats)
{
    char r[] = ESC_FG_YELLOW "r" ESC_FG_DEFAULT;
    char w[] = ESC_FG_RED "w" ESC_FG_DEFAULT;
    char x[] = ESC_FG_GREEN "x" ESC_FG_DEFAULT;
    char s[] = ESC_FG_GREEN "s" ESC_FG_DEFAULT;
    char S[] = ESC_FG_GREEN "S" ESC_FG_DEFAULT;
    char t[] = ESC_FG_GREEN "t" ESC_FG_DEFAULT;
    char T[] = ESC_FG_GREEN "T" ESC_FG_DEFAULT;
    char blank[] = ESC_DIM "-" ESC_RESET;

    printf("%s", (stats->st_mode & S_IRUSR) ? r : blank);
    printf("%s", (stats->st_mode & S_IWUSR) ? w : blank);
    if (stats->st_mode & S_ISUID)
    {
        if (stats->st_mode & S_IXUSR)
        {
            printf("%s", s);
        }
        else
        {
            printf("%s", S);
        }
    }
    else
    {
        printf("%s", (stats->st_mode & S_IXUSR) ? x : blank);
    }

    printf("%s", (stats->st_mode & S_IRGRP) ? r : blank);
    printf("%s", (stats->st_mode & S_IWGRP) ? w : blank);
    if (stats->st_mode & S_ISGID)
    {
        if (stats->st_mode & S_IXGRP)
        {
            printf("%s", s);
        }
        else
        {
            printf("%s", S);
        }
    }
    else
    {
        printf("%s", (stats->st_mode & S_IXGRP) ? x : blank);
    }

    printf("%s", (stats->st_mode & S_IROTH) ? r : blank);
    printf("%s", (stats->st_mode & S_IWOTH) ? w : blank);
    if (stats->st_mode & S_ISVTX)
    {
        if (stats->st_mode & S_IXOTH)
        {
            printf("%s", t);
        }
        else
        {
            printf("%s", T);
        }
    }
    else
    {
        printf("%s", (stats->st_mode & S_IXOTH) ? x : blank);
    }
}

void print_modification_time(struct stat *stats)
{
    char buffer[TIME_LEN];
    strftime(buffer, TIME_LEN, "%b %d %H:%M", localtime(&stats->st_mtime));
    printf(ESC_FG_BLUE "%*s" ESC_FG_DEFAULT, TIME_LEN, buffer);
}

void print_header(void)
{
    printf(ESC_UNDERLINE "Permissions" ESC_RESET "    ");
    printf(ESC_UNDERLINE "Size" ESC_RESET "       ");
    printf(ESC_UNDERLINE "User" ESC_RESET "       ");
    printf(ESC_UNDERLINE "Group" ESC_RESET "  ");
    printf(ESC_UNDERLINE "Last Modified" ESC_RESET "  ");
    printf(ESC_UNDERLINE "Name" ESC_RESET "\n");
}

void print_longlisting(struct dirent **entries, const void *args)
{
    struct arguments *arguments = (struct arguments *)args;

    print_header();
    while (*entries)
    {
        struct stat stats;
        stat((*entries)->d_name, &stats);

        print_filetype(&stats);
        print_permissions(&stats);
        printf("  ");
        print_size(&stats, arguments->human_readable);
        printf(" ");
        print_username(&stats);
        printf("  ");
        print_groupname(&stats);
        printf("  ");
        print_modification_time(&stats);
        printf("  ");
        print_name(*entries, &stats);
        printf("\n");
        entries++;
    }
}