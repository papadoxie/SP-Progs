#pragma once

#ifndef __DIR_M_H__
#define __DIR_M_H__

#include <dirent.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct dirent **getent(DIR *dirptr);
void delent(struct dirent **entries);

#endif // __DIR_M_H__