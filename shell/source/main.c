#include <locale.h>
#include <shell.h>

// Entry point
int main(void) 
{
    // Enable support for wchar_t
    setlocale(LC_ALL, "");
    
    // Initialize the shell environment and configuration
    init_shell();

    // Start an interactive shell
    // Will add support for scripting later
    interactive_shell();
    return 0;
}