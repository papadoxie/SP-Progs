#pragma once

#ifndef __LL_H__
#define __LL_H__

#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

struct stat **long_listing(struct dirent **entries, unsigned int num_entries);

#endif // __LL_H__