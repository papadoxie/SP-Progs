#pragma once

#ifndef __FORMAT_H__
#define __FORMAT_H__

// Maximum size of escape sequence
#define SEQ_SIZE 11

// Size of color escape sequence
#define COLOR_SEQ_SIZE 6

#define ESC_FG_RED "\033[31m"
#define ESC_FG_GREEN "\033[32m"
#define ESC_FG_YELLOW "\033[33m"
#define ESC_FG_BLUE "\033[34m"
#define ESC_FG_MAGENTA "\033[35m"
#define ESC_FG_CYAN "\033[36m"
#define ESC_FG_WHITE "\033[37m"
#define ESC_FG_DEFAULT "\033[39m"

#define ESC_BG_RED "\033[41m"
#define ESC_BG_GREEN "\033[42m"
#define ESC_BG_YELLOW "\033[43m"
#define ESC_BG_BLUE "\033[44m"
#define ESC_BG_MAGENTA "\033[45m"
#define ESC_BG_CYAN "\033[46m"
#define ESC_BG_WHITE "\033[47m"
#define ESC_BG_DEFAULT "\033[49m"

// Size of normal escape sequence
#define NORM_SEQ_SIZE 5

#define ESC_ERASE_LINE "\033[K\r"
#define ESC_UNDERLINE "\033[4m"
#define ESC_BOLD "\033[1m"
#define ESC_DIM "\033[2m"
#define ESC_REVERSE "\033[7m"
#define ESC_RESET "\033[0m"

#endif // __FORMAT_H__