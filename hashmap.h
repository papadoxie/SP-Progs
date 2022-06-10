#pragma once

#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>


typedef struct __key_value_pair
{
    char key[256];
    void *value;
} pair;

typedef struct __hashmap
{
    pair **pairs;
    uint64_t capacity;
    uint64_t size;
    int (*insert_pair)(struct __hashmap *, char *, void *);
    void (*remove_pair)(struct __hashmap *, char *);
    void *(*get)(struct __hashmap *, char *);
    void (*destroy_map)(struct __hashmap *);
} hashmap;

hashmap *new_map(int size);

#endif // __HASHMAP_H__
