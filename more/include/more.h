#pragma once

#ifndef __MORE_H__
#define __MORE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sigwinch.h>
#include <unistd.h>
#include <format.h>

// Implementation of more
int more(const char *filename);

#endif // __MORE_H__