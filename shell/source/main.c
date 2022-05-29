#include <locale.h>
#include <shell.h>

int main(void) 
{
    setlocale(LC_ALL, "");
    init_shell();
    interactive_shell();
    return 0;
}