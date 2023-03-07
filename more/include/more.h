#pragma once

#ifndef __MORE_H__
#define __MORE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <format.h>
#include <buffering.h>

#define REFRESH 1

// Implementation of more
int more(const char *filename);

#endif // __MORE_H__