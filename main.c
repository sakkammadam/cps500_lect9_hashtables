#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ChainedHashNode{
    int key;
    int value;
    struct ChainedHashNode* next;
} ChainedHashNode;

typedef struct ChainedHashTable{
    // Array of pointers to HashNode*
    ChainedHashNode** array; // array for lookup!
    int N; // size of array
} ChainedHashTable;

typedef struct ProbedHashNode{
    int key;
    int value;
} ProbedHashNode;

typedef struct ProbedHashTable{
    ProbedHashNode** array;
    int size;
} ProbedHashTable;

int insertChainedHashTable(ChainedHashTable* table, int key, int value){
    // function!
    int index = value%(table->N); // use mod/%
    // declare hashNode
    ChainedHashNode* front = table->array[index];
    ChainedHashNode* tail = NULL;
    // iterate over the list to see if there is a hit of the key!
    while(front!=NULL){
        if(front->key == key){
            // key found ! exit
            return 0;
        }
        // the front becomes tail
        tail=front;
        // the next element on list becomes front
        front=front->next;
    }
    // if not found!
    // declare a node in heap
    ChainedHashNode* node = malloc(sizeof(ChainedHashTable));
    // set the next pointer to null
    node->next = NULL;
    // associate data
    node->key = key;
    node->value = value;
    // if the table was empty to begin with
    if(tail==NULL){
        table->array[index] = node;
        return 1;
    }
    // if table was not empty!
    tail->next=node;
    return 1;
}

// Open Addressing - Linear Probing
int insertProbeHashTable(ProbedHashTable* table, int key, int value){
    for(int i=0; i < table->size; i++){
        int index = (value%(table->size)+i)%(table->size);
        if(table->array[index]==NULL){
            table->array[index] = malloc(sizeof(ProbedHashNode));
            table->array[index]->key=key;
            table->array[index]->value=value;
            return 1;
        } else if (table->array[key]->key == key){
            return 0;
        }
    }
    // there was hash-collision if not null!
    return 0;
}

// Open Addressing - Quadratic probing
int insertQuadHashTable(ProbedHashTable* table, int key, int value){
    double c1=0.5;
    double c2=0.5;
    for(int i=0; i < table->size; i++){
        int index = (int)(value%(table->size)+ (int)(c1*i)+ (int)c2*(pow(i,2)))%(table->size);
        if(table->array[index]==NULL){
            table->array[index] = malloc(sizeof(ProbedHashNode));
            table->array[index]->key=key;
            table->array[index]->value=value;
            return 1;
        } else if (table->array[key]->key == key){
            return 0;
        }
    }
    // there was hash-collision if not null!
    return 0;
}

// Open Addressing - Double hashing
int insertDoubleHashTable(ProbedHashTable* table, int key, int value){
    for(int i=0; i < table->size; i++){
        int index = (value%(table->size)+ i*(10-(value)%(table->size)))%(table->size);
        if(table->array[index]==NULL){
            table->array[index] = malloc(sizeof(ProbedHashNode));
            table->array[index]->key=key;
            table->array[index]->value=value;
            return 1;
        } else if (table->array[key]->key == key){
            return 0;
        }
    }
    // there was hash-collision if not null!
    return 0;
}

// Hashtable exists
int checkHashTableHelper(ChainedHashTable* table, int key){
    if(table->array[key]){
        return key;
    } else
        return -1;
}

int checkHashTable(ChainedHashTable* table, int valueToLookFor){
    for(int i=0; i < table->N, i++){
        int left = valueToLookFor-table->array[i]->value;
        if(checkHashTableHelper(table,left)!=-1){
            return 1;
        }
        insertChainedHashTable(&table,i,valueToLookFor);
    }
}

int main() {
    return 0;
}
