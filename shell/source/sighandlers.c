#include <sighandlers.h>

void SIGCHLD_hander(__attribute__((unused)) int sig)
{
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

void register_handlers(void)
{
    struct sigaction act;
    act.sa_handler = SIGCHLD_hander;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &act, NULL);
}