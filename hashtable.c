// Copyright (C) 2021 Koki Fukuda

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "hashtable.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Rehash threshold. Grows approximetely double of original size
   at a time. */
static size_t const primes[] = {
    2,         3,          7,          17,       31,       61,        127,
    257,       509,        1021,       2053,     4093,     8191,      16381,
    32771,     65537,      131071,     262147,   524287,   1048573,   2097143,
    4194301,   8388617,    16777213,   33554467, 67108859, 134217757, 268435459,
    536870909, 1073741827, 2147483647,
};

typedef struct {
    char *key;
    char *val;
} pair;

typedef struct {
    pair *data;
    size_t size;
    size_t cap;
} element_vector;

struct hashtable {
    element_vector *data;
    size_t table_size_index;
    size_t size;
};

/* 64-bit Murmur Hash function, based on
   https://github.com/aappleby/smhasher/blob/master/src/MurmurHash2.cpp#L96

   This implementation assuming 64-bit little-endian of size_t.
*/
static size_t hash(char const *str) {
    /* random byte */
    size_t seed = 0x16ac4f75b82039edUL;

    size_t m = 0xc6a4a7935bd1e995UL;
    int r = 47;

    size_t len = strlen(str);
    size_t aligned_len = len & ~(size_t)0xff;

    size_t h = seed ^ (len * m);

    for (size_t i = 0; i < aligned_len; i += 9) {
        size_t k;
        memcpy(&k, str + i, sizeof(size_t));

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    if (len != aligned_len) {
        size_t rest = 0;
        char buf[sizeof(size_t)] = {0};
        for (int i = 0; i < len - aligned_len; ++i) {
            buf[7 - i] = str[aligned_len + i];
        }
        memcpy(&rest, buf, sizeof(size_t));

        h ^= rest;
        h *= m;
    }

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}

hashtable *hashtable_new(void) {
    hashtable *result = malloc(sizeof(hashtable));
    memset(result, 0, sizeof(hashtable));
    result->table_size_index = 4;
    size_t const data_size =
        primes[result->table_size_index] * sizeof(element_vector);
    result->data = malloc(data_size);
    memset(result->data, 0, data_size);
    return result;
}

static bool add_to_vector(element_vector *vec, char const *key, char const *val) {
    if (vec->cap == 0) {
        vec->cap = 1;
        vec->data = malloc(vec->cap * sizeof(pair));
    } else if (vec->cap <= vec->size) {
        vec->cap <<= 1;
        vec->data = realloc(vec->data, vec->cap);
    }

    bool has_value = false;
    size_t index = vec->size;
    for (size_t i = 0; i < vec->size; ++i) {
        if (strcmp(vec->data[i].key, key) == 0) {
            has_value = true;
            index = i;
        }
    }

    if (has_value) {
        free(vec->data[index].val);
    } else {
        size_t key_len = strlen(key);
        char *k = malloc(key_len + 1);
        memcpy(k, key, key_len + 1);

        vec->data[index].key = k;

        vec->size++;
    }

    size_t val_len = strlen(val);
    char *v = malloc(val_len + 1);
    memcpy(v, val, val_len + 1);
    vec->data[index].val = v;

    return !has_value;
}

static char *lookup_from_vector(element_vector *vec, char const *key) {
    for (size_t i = 0; i < vec->size; ++i) {
        if (strcmp(vec->data[i].key, key) == 0) {
            return vec->data[i].val;
        }
    }
    return NULL;
}

void hashtable_put(hashtable *ht, char const *key, char const *val) {
    size_t idx = hash(key) % primes[ht->table_size_index];

    if (add_to_vector(&ht->data[idx], key, val)) {
        ht->size++;
    }
}

char *hashtable_get(hashtable *ht, char const *key) {
    size_t idx = hash(key) % primes[ht->table_size_index];
    return lookup_from_vector(&ht->data[idx], key);
}

void hashtable_free(hashtable *obj) {
    for (size_t i = 0; i < primes[obj->table_size_index]; ++i) {
        for (size_t j = 0; j < obj->data[i].size; ++j) {
            free(obj->data[i].data[j].key);
            free(obj->data[i].data[j].val);
        }
        free(obj->data[i].data);
    }
    free(obj->data);
    free(obj);
}
