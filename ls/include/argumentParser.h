#pragma once

#ifndef __ARGUMENT_PARSER_H__
#define __ARGUMENT_PARSER_H__

#include <stdlib.h>
#include <string.h>
#include <argp.h>
#include <ls.h>

// Unused fields in argp struct
#define ARGP_CHILDREN NULL
#define HELP_FILTER NULL
#define ARGP_DOMAIN NULL

#define FILENAME_LEN 255

// Functions needed for argp
error_t parse_opt(int key, char *arg, struct argp_state *state);

// Variables used for argp
extern const char doc[32];
extern char args_doc[10];
extern struct argp_option options[10];

struct arguments
{
    char directory[FILENAME_MAX + 1];
    int all;
    int long_format;
    int reverse;
    int sort;
    int time;
};

#endif // __ARGUMENT_PARSER_H__