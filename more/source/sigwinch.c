#include <sigwinch.h>

struct window window;

static pthread_mutex_t mut_free;

void init_sigwinch_handler(void)
{
    pthread_mutex_init(&mut_free, NULL);
}

void delete_sigwinch_handler(void)
{
    pthread_mutex_destroy(&mut_free);
}

void handle_sigwinch(int sig)
{
    if (sig == SIGWINCH)
    {
        // Delete old buffer first because it depends on old terminal size
        at_sigwinch();

#if defined(TIOCGSIZE)
        struct ttysize ts;
        ioctl(STDOUT, TIOCGSIZE, &ts);
        rows = ts.ts_rows;
        cols = ts.ts_cols;

#elif defined(TIOCGWINSZ)
        struct winsize ws;
        ioctl(STDOUT, TIOCGWINSZ, &ws);
        window.rows = ws.ws_row;
        window.cols = ws.ws_col + TERM_MAGIC_SIZE;
#endif

        post_sigwinch();
    }
}