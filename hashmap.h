//
// Created by lucky on 10/12/2019.
//

#ifndef HASHMAP_HASHMAP_H
#define HASHMAP_HASHMAP_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node Node;


struct Node {

    const char* key;
    void* data;
    Node* next;

};


typedef struct HashTable {

    size_t n_buckets;
    Node** list;

} HashMap;

typedef void* (*ResolveCollisionCallback)(void *old_data, void *new_data);

typedef void (*StandardCallback)(const char* bucket_key, void* data);

typedef void (*DestroyDataCallback)(void* data);

unsigned int my_strlen(const char *s);

unsigned int get_hash_index(unsigned int hash, HashMap* ht);

HashMap* create_hashmap(size_t n_buckets);


unsigned int hash(const char* bucket_key);


void insert_data(HashMap* ht, const char* bucket_key, void* value, ResolveCollisionCallback collision_resolve);


void* get_data(HashMap* ht, const char* bucket_key);


void iterate(HashMap* ht, StandardCallback std_callback);


void remove_data(HashMap* ht, const char* bucket_key, DestroyDataCallback data_destruction);


void delete_hashmap(HashMap* ht, DestroyDataCallback data_destruction);


#endif //HASHMAP_HASHMAP_H
