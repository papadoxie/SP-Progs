#pragma once

#ifndef __PROMPT_H__
#define __PROMPT_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MODIFIER_LENGTH 256
#define MODIFIER_DELIMITERS "{}"

void print_prompt(void);
void free_prompt(int status, void *prompt_struct);

typedef struct __prompt_modifiers
{
    char *modifier_index;
    char *(*modifier)(char *, size_t);
} prompt_modifier;

typedef struct __prompt_t
{
    uint8_t lines;
    char **prompt;
} prompt_t;

extern prompt_t prompt;

#endif // __PROMPT_H__