#include <sigwinch.h>

struct window window;

// These functions will be called to refresh the buffer and display
extern int initBuffer(void);
extern void printBuffer(void);

void handle_sigwinch(int sig)
{
    if (sig == SIGWINCH)
    {
#if defined(TIOCGSIZE)
        struct ttysize ts;
        ioctl(STDOUT, TIOCGSIZE, &ts);
        rows = ts.ts_rows;
        cols = ts.ts_cols;

#elif defined(TIOCGWINSZ)
        struct winsize ws;
        ioctl(STDOUT, TIOCGWINSZ, &ws);
        window.rows = ws.ws_row;
        window.cols = ws.ws_col;
        initBuffer();
        printBuffer();
#endif
    }
}