#pragma once

#ifndef __DIR_M_H__
#define __DIR_M_H__

#include <dirent.h>
#include <stdbool.h>
#include <stdlib.h>

#define MEMSIZE 32
#define MEM_MULTIPLE ((n_entries / 32) + 1)

struct dirent **getent(DIR *dirptr);
void delent(struct dirent **entries);

#endif // __DIR_M_H__