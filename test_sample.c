#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashmap.h"

#ifdef COUNTING_WORDS
#include "wordcount.h"
#endif

size_t mystrlen(const char *str) {
    return strlen(str) + 1;
}

void print_element(const char *key, void *data) {
	printf("(\"%s\", %s)\n", key, (char*)data);
}

void* resolve_collision(void *old_value, void *new_value) {
	return new_value;
}

void destroy_data(void* data){
	free((void*) data);
	//data = NULL;
}

unsigned your_own_hash(const char *key) {
	return (unsigned) strlen(key) + (unsigned) *key;
}

int main() {
	unsigned int key_space = 1024;
	HashMap * hm = create_hashmap(key_space);

	char * string_1 = "CSE2425";
	char * string_2 = "Embedded";
	char * string_3 = "Software";
	const char * key_1    = "ab";
	const char * key_2    = "cd";
	const char * key_3    = "ad";
	const char * key_4    = "xy";
	const char * key_5    = "ba";
	const char * key_6	  = "x";	

	// Insert ("ab" -> "CSE2425").
	insert_data(hm, key_1, string_1, resolve_collision);
	assert(memcmp(get_data(hm, key_1), string_1, mystrlen(string_1)) == 0);

	// Insert ("cd" -> "Embedded").
	insert_data(hm, key_2, string_2, resolve_collision);
	assert(memcmp(get_data(hm, key_2), string_2, mystrlen(string_2)) == 0);

	// Insert ("ad" -> "Software").
	insert_data(hm, key_3, string_3, resolve_collision);
	assert(memcmp(get_data(hm, key_3), string_3, mystrlen(string_3)) == 0);

	// Insert ("ab" -> "Embedded").
	insert_data(hm, key_1, string_2, resolve_collision);
	assert(memcmp(get_data(hm, key_1), string_2, mystrlen(string_2)) == 0);

	insert_data(hm, key_5, string_1, resolve_collision);
	assert(memcmp(get_data(hm, key_5), string_1, mystrlen(string_2)) == 0);

	// Get data for a not inserted key.
	assert(get_data(hm, key_4) == NULL);
	//printf("%p  -  %p\n", hm->list[hash(key_1)%key_space]->next->key, key_1);
	
	//Node* curr = hm->list[hash(key_1)%key_space];
	for(unsigned int j = 0; j < key_space; j++){
		Node* curr = hm->list[j];
		while(curr){
			if(strcmp(key_1, curr->key) == 0){
				assert(!(key_1 == curr->key));
			}
			curr = curr->next;
		}
	}
	

	// Iterate the hash map
	iterate(hm, print_element);

#ifdef NEW_HASH
	set_hash_function(hm, your_own_hash);

	printf("\nHERE WE GO AGAIN!\n\n");

	// Iterate the hash map 
	iterate(hm, print_element);
#endif

	// Delete key "cd".
	remove_data(hm, key_2, NULL);
	assert(get_data(hm, key_2) == NULL);

	remove_data(hm, key_2, NULL);
	assert(get_data(hm, key_2) == NULL);

	remove_data(hm, key_4, NULL);
	assert(get_data(hm, key_4) == NULL);

	// Delete key "ab".
	remove_data(hm, key_1, NULL);
	assert(get_data(hm, key_1) == NULL);

	// Delete key "ad".
	remove_data(hm, key_3, NULL);
	assert(get_data(hm, key_3) == NULL);

	// Delete the hash map.
	delete_hashmap(hm, NULL);
	//delete_hashmap(NULL, NULL);

	//hm = create_hashmap(key_space);

	//delete_hashmap(hm, )

#ifdef COUNTING_WORDS
	// Create a temporary file
	FILE *stream = tmpfile();

	// Write to the stream
	fprintf(stream, "foo bar_, baz!\n");
	fprintf(stream, "foo\t\"bar\".\n");
	fprintf(stream, "foo?\n");

	// Set the position to the start of the stream
	fseek(stream, 0, SEEK_SET);

	// Count the words
	count_words(stream);

	// Close the file
	fclose(stream);
#endif

	return 0;
}
