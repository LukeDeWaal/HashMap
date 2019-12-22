#include "hashmap.h"

unsigned int my_strlen(const char *s)
{
    unsigned int count = 0;
 
    while(*s!='\0')
    {
        count++;
        s++;
    }
 
    return count;
}


HashMap* create_hashmap(size_t key_space) {

    if (key_space <= 0) {
        return NULL;
    }

    HashMap* hm = (HashMap*) malloc(sizeof(HashMap));
    hm->n_buckets = key_space;
    hm->list = (Node**) malloc(sizeof(Node*) * key_space);
    unsigned int i;

    for (i = 0; i < key_space; ++i) {
        hm->list[i] = NULL;
    }

    return hm;

}

unsigned int hash(const char* key) {

    if (key == NULL) {
        return (unsigned int)0;
    }

    unsigned int res = 0;
    unsigned int i;
    unsigned int keylen = my_strlen(key);

    for (i = 0; i < keylen; ++i) {
        res += (unsigned int)key[i];
    }

    return res;
}

void insert_data(HashMap* hm, const char* key, void* data, ResolveCollisionCallback resolve_collision) {
    
    if ((hm == NULL) || (key == NULL)) {
        return;
    }

    unsigned int h = hash(key) % hm->n_buckets;
    Node* list = hm->list[h];
    Node* newNode = (Node *) malloc(sizeof(Node));
    Node* curr = list;

    while(curr) {

        if(strcmp(curr->key, key) == 0 && curr->data != NULL) {

            void* new_data = resolve_collision(curr->data, data);
            curr->data = new_data;
            free((Node *) newNode);
            return;

        }
        else if(strcmp(curr->key, key) == 0 && curr->data == NULL){
            curr->data = data;
            free((Node *) newNode);
            return;
        }
    
        curr = curr->next;

    }

    char* p = malloc(sizeof(key));
    strcpy(p, key);
    newNode->key = p;

    newNode->data = data;
    newNode->next = list;
    hm->list[h] = newNode;

}

void* get_data(HashMap* hm, const char* key) {

    if ((hm == NULL) || (key == NULL)) {
        return NULL;
    };

    unsigned int position = hash(key) % hm->n_buckets;
    Node* list = hm->list[position];
    Node* curr = list;

    while (curr != NULL) {
        //printf("%p\n", curr->data);
        if (strcmp(curr->key, key)==0) {
            return curr->data;
        }

        curr = curr->next;

    };

    return (void*) NULL;
}

void remove_data(HashMap* hm, const char* key, DestroyDataCallback destroy_data) {

    if ((hm == NULL) || (key == NULL)) {
        return;
    };

    unsigned int i = hash(key) % hm->n_buckets;

    Node* header = hm->list[i];

    if(header == NULL){
        return;
    }

    Node* temp = NULL;
    Node* prev = NULL;

    temp = header;

    while(temp != NULL) {
        //printf("  %s - %s\n", temp->key, temp->data);

        if (strcmp(temp->key, key) == 0) {

            if(prev == NULL){
                hm->list[i] = temp->next;
            }
            else{
                prev->next = temp->next;
            }

            if (destroy_data != NULL) {

                destroy_data(temp->data);
                
            }
            
            free((char*) temp->key);
            free((Node*) temp);
            temp = NULL; 
            return;
        }

        prev = temp;
        temp = temp->next;

    }
}

void iterate(HashMap* hm, StandardCallback stb) {

    if (hm == NULL) {
        return;
    }

    unsigned int i;

    for(i = 0; i < hm->n_buckets; ++i) {

        Node* header = hm->list[i];

        while(header) {

            Node* temp = header;
            header = header->next;

            if (stb != NULL) {

                stb(temp->key, temp->data);

            }
        }
    }
}

void delete_hashmap(HashMap* hm, DestroyDataCallback destroy_data) {

    if (hm == NULL) {
        return;
    }

    unsigned int i;

    for (i = 0; i < hm->n_buckets; i++) {
        //printf("Bucket: %d\n", i);
        Node* header = hm->list[i];
        Node* temp = header;
        Node* next = NULL;

        while(temp != NULL) {
            //printf("  %s - %s\n", temp->key, temp->data);
            next = temp->next;
            if (destroy_data != NULL) {

                destroy_data(temp->data);
                
            }
            
            free((char*) temp->key);
            free((Node*) temp);
            temp = next;

        }
    }

    free((Node**) hm->list);
    free((HashMap*) hm);

}
