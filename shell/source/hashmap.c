#include <hashmap.h>

// Find closest free slot in the hashmap
uint64_t free_index(pair **pairs, uint64_t capacity, uint64_t hash)
{
    uint64_t index = hash;
    while (pairs[index] != NULL)
    {
        index = (index + 1) % capacity;
    }

    return index;
}

// Calculate the hash of a key
uint64_t calc_hash(char *key, uint64_t capacity)
{
    int symbol = 0;
    uint64_t hash = 5831;

    while ((symbol = *key++))
    {
        hash = ((hash << 5) + hash) + symbol;
    }

    hash = hash % capacity;
    return hash;
}

int __internal_insert_pair(hashmap *map, char *key, void *value)
{
    pair **resized = NULL;

    // If the map is full, resize it
    if (map->size == map->capacity)
    {
        map->capacity *= 2;
        // Allocate placeholder for new pairs
        resized = malloc(sizeof(pair *) * map->capacity);
        if (!resized)
        {
            return -1;
        }
        memset(resized, 0, sizeof(pair *) * map->capacity);

        // Rehash all old pairs
        for (uint64_t i = 0; i < map->capacity / 2; i++)
        {
            uint64_t hash = calc_hash(map->pairs[i]->key, map->capacity);
            uint64_t index = free_index(resized, map->capacity, hash);
            resized[index] = map->pairs[i];
            free(map->pairs[i]);
        }
        // Free old pairs
        free(map->pairs);
        // Set new pairs
        map->pairs = resized;
    }

    // Allocate new pair
    pair *pair = malloc(sizeof(pair));
    if (!pair)
    {
        return -1;
    }
    strncpy(pair->key, key, strlen(key));
    pair->value = value;

    // Insert new pair
    uint64_t hash = calc_hash(key, map->capacity);
    uint64_t index = free_index(map->pairs, map->capacity, hash);
    map->pairs[index] = pair;
    map->size++;

    return 0;
}

void *__internal_get(hashmap *map, char *key)
{
    uint64_t hash = calc_hash(key, map->capacity);
    uint64_t index = hash;
    while (map->pairs[index])
    {
        if (strcmp(map->pairs[index]->key, key) == 0)
        {
            return map->pairs[index]->value;
        }
        index = (index + 1) % map->capacity;
    }

    return NULL;
}

void __internal_remove_pair(hashmap *map, char *key)
{
    uint64_t hash = calc_hash(key, map->capacity);
    uint64_t index = hash;
    while (map->pairs[index])
    {
        if (strcmp(map->pairs[index]->key, key) == 0)
        {
            free(map->pairs[index]);
            map->pairs[index] = NULL;
            map->size--;
            return;
        }
        index = (index + 1) % map->capacity;
    }
}

void free_map(__attribute__((unused)) int status, void *map_ptr)
{
    hashmap *map = (hashmap *)map_ptr;
    for (uint64_t i = 0; i < map->capacity; i++)
    {
        if (map->pairs[i])
        {
            free(map->pairs[i]);
            map->pairs[i] = NULL;
        }
    }
    free(map->pairs);
    map->pairs = NULL;
    free(map);
    map = NULL;
}

void __internal_destroy_map(hashmap *map)
{
    free_map(0, map);
}

hashmap *new_map(int size)
{
    // Allocate new hashmap
    hashmap *map = malloc(sizeof(hashmap));
    map->capacity = size;
    map->size = 0;

    // Allocate pairs
    map->pairs = malloc(sizeof(pair *) * size);
    if (!map->pairs)
    {
        free(map);
        return NULL;
    }
    
    // Cleanup
    on_exit(free_map, map);
    memset(map->pairs, 0, sizeof(pair *) * size);

    // Set functions
    map->insert_pair = __internal_insert_pair;
    map->remove_pair = __internal_remove_pair;
    map->get = __internal_get;
    map->destroy_map = __internal_destroy_map;

    return map;
}
