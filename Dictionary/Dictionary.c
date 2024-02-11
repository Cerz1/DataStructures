#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum size of the hash table
#define HASH_TABLE_SIZE 100

// Define the structure for each item in the hash table
// Each item has a key, a value, and a pointer to the next item
// This allows us to handle collisions by chaining
typedef struct Item {
    char* key;
    char* value;
    struct Item* next;
} Item;

// Define the structure for the hash table
// The hash table is an array of pointers to items
typedef struct HashTable {
    Item* items[HASH_TABLE_SIZE];
} HashTable;

// Function to create a new item
// This function allocates memory for a new item and initializes its key and value
Item* createItem(char* key, char* value) {
    Item* item = (Item*) malloc(sizeof(Item));
    item->key = _strdup(key);
    item->value = _strdup(value);
    item->next = NULL;
    return item;
}

// Function to create a new hash table
// This function allocates memory for a new hash table and initializes all its items to NULL
HashTable* createHashTable() {
    HashTable* hashTable = (HashTable*) malloc(sizeof(HashTable));
    for(int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable->items[i] = NULL;
    }
    return hashTable;
}

// Hash function to map keys to array indices
// This function uses a simple hash function that sums the ASCII values of the characters in the key
// The result is then taken modulo the size of the hash table to ensure it fits within the array
int hashFunction(char* key) {
    int sum = 0;
    for(int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % HASH_TABLE_SIZE;
}

// Function to insert a key-value pair into the hash table
// This function first computes the hash of the key to find the index for the item
// It then creates a new item and inserts it into the hash table at the computed index
// If there is already an item at that index, it adds the new item to the end of the list
void insert(HashTable* hashTable, char* key, char* value) {
    int index = hashFunction(key);
    Item* item = createItem(key, value);

    if(hashTable->items[index] == NULL) {
        hashTable->items[index] = item;
    } else {
        Item* currentItem = hashTable->items[index];
        while(currentItem->next) {
            currentItem = currentItem->next;
        }
        currentItem->next = item;
    }
}

// Function to search for a key in the hash table and return the corresponding value
// This function computes the hash of the key to find the index for the item
// It then traverses the list at that index until it finds an item with a matching key
// If it finds a matching key, it returns the corresponding value; otherwise, it returns NULL
char* search(HashTable* hashTable, char* key) {
    int index = hashFunction(key);
    Item* item = hashTable->items[index];
    while(item) {
        if(strcmp(item->key, key) == 0) {
            return item->value;
        }
        item = item->next;
    }
    return NULL;
}

int main() {
    // Create a new hash table
    HashTable* hashTable = createHashTable();

    // Insert some key-value pairs into the hash table
    insert(hashTable, "name", "Alessio");
    insert(hashTable, "age", "23, ma giuro che ieri ne avevo 19");

    // Search for some keys in the hash table and print their values
    printf("Name: %s\n", search(hashTable, "name"));
    printf("Age: %s\n", search(hashTable, "age"));

    return 0;
}