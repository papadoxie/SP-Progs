#pragma once

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <prompt.h>
#include <format.h>

#define DEFAULT_PROMPT "" ESC_FG_RED "{username}" ESC_FG_DEFAULT                    \
                       "@" ESC_FG_RED ESC_DIM "{hostname}" ESC_RESET ESC_FG_DEFAULT \
                           ESC_FG_MAGENTA " {pwd}" ESC_FG_DEFAULT                   \
                       " $ "

int set_config(FILE *config_file);
int set_default_config(void);

#endif // __CONFIG_H__