#include <ctype.h>
#include <string.h>
#include "wordcount.h"
#include "hashmap.h"

void print_occurence_count(const char *key, unsigned int* data){
	printf("%s: %ls\n", key, data);
}

void remove_count(unsigned int* data){
	//free(data);
	data = NULL;
}

void count_words(FILE* stream){

	if( stream  == NULL ){
		printf("%s\n", "File doesn't exist");
	};

	size_t n_buckets = 1024;
	HashMap* hm = create_hashmap(n_buckets);

	char curr_char;

	char word[255] = {0};
	unsigned int length = 0;
	

	while(1) {
    	if(feof(stream)){
    		break;
    	}
    	curr_char = getc(stream);
 		
		if(isalpha(curr_char) || isdigit(curr_char)){
			// Do Something
			word[length] = curr_char;
			length++;
			printf("%c  -  %s  -  %d\n", curr_char, word, (unsigned int)strlen(word));
			continue;
		}
		else{
			if(strlen(word) > 0){
				// Do Something
				unsigned int* count = get_data(hm, word);
				//*count = 0;
				if(count == NULL){
					unsigned int* new_count = malloc(sizeof(unsigned int));
					*new_count = 1;
					insert_data(hm, word, new_count, NULL);
					printf("Count: %p  - %p\n", (void*)&new_count, (void*)get_data(hm, word));
				}
				else{
					
				}
				
			}
			else{
				// Do Nothing
			}			
		} 



		length = 0;   
		memset(word, 0, sizeof(word));   	
    }

    //iterate(hm, print_occurence_count);
	delete_hashmap(hm, remove_count);
}