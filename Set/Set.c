#include <stddef.h>
#include <string.h>
#include <stdio.h>

// Constants for the hash map size and list size
#define HASH_MAP_SIZE 64
#define HASH_MAP_LIST_SIZE 1

// Structure representing an item in the set
struct aiv_set_item {
    const char *key; // The key (string)
    size_t key_len;  // The length of the key
};

// Structure representing the set itself
struct aiv_set {
    struct aiv_set_item hashmap[HASH_MAP_SIZE][HASH_MAP_LIST_SIZE]; // Hash map for the set
};

// Hash function (djb33x)
size_t djb33x_hash(const char *key, const size_t keylen) {
    size_t hash = 5381;

    // Iterate over each character in the key
    for (size_t i = 0; i < keylen; i++) {
        // Update the hash value
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

// Function to check if a key is unique in the set
int is_key_unique(struct aiv_set *set, const char *key) {
    // Iterate through the hash map
    for (size_t size = 0; size < HASH_MAP_SIZE; size++) {
        for (size_t i = 0; i < HASH_MAP_LIST_SIZE; i++) {
            // Check if the key exists and is equal to the given key
            if (set->hashmap[size][i].key && strcmp(set->hashmap[size][i].key, key) == 0) {
                // Key is not unique
                printf("\n%s already added\n\n", key);
                return 0; // Non-unique key
            }
        }
    }
    // Key is unique
    return 1;
}

// Function to insert a key into the set
void aiv_set_insert(struct aiv_set *set, const char *key) {
    // Check if the key is unique before insertion
    if (!is_key_unique(set, key)) {
        return;
    }

    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % HASH_MAP_SIZE;

    // Iterate through the list at the calculated index
    for (size_t i = 0; i < HASH_MAP_LIST_SIZE; i++) {
        // Check if the slot is empty
        if (set->hashmap[index][i].key_len == 0) {
            // Insert the key into the slot
            set->hashmap[index][i].key = key;
            set->hashmap[index][i].key_len = key_len;
            printf("- Added %s at index %zu slot %zu\n", key, index, i);
            return;
        }
    }

    // Collision handling: all slots are occupied
    printf("COLLISION! for %s (index %zu)\n", key, index);
}

// Function to remove a key from the set
void aiv_set_remove(struct aiv_set *set, const char *key) {
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % HASH_MAP_SIZE;

    printf("%s [ %zu ] (index: %zu)\n", key, hash, index);

    // Iterate through the list at the calculated index
    for (size_t i = 0; i < HASH_MAP_LIST_SIZE; i++) {
        // Check if the slot is occupied and the key matches
        if (set->hashmap[index][i].key_len > 0 &&
            set->hashmap[index][i].key_len == key_len &&
            !memcmp(set->hashmap[index][i].key, key, key_len)) {
            // Remove the key from the slot
            set->hashmap[index][i].key = NULL;
            set->hashmap[index][i].key_len = 0;
            return;
        }
    }
}

// Function to find and print a key in the set
void aiv_set_find(struct aiv_set *set, const char *key) {
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % HASH_MAP_SIZE;

    printf(" %s [ %zu ] (index: %zu)\n", key, hash, index);

    // Iterate through the list at the calculated index
    for (size_t i = 0; i < HASH_MAP_LIST_SIZE; i++) {
        // Check if the slot is occupied and the key matches
        if (set->hashmap[index][i].key_len > 0 &&
            set->hashmap[index][i].key_len == key_len &&
            !memcmp(set->hashmap[index][i].key, key, key_len)) {
            // Print the found key information
            printf("%s at index %zu slot %zu\n", key, index, i);
            return;
        }
    }
}

// Function to print the list of keys in the set
void print_key_list(struct aiv_set *set) {
    // Iterate through the entire hash map
    for (size_t size = 0; size < HASH_MAP_SIZE; size++) {
        for (size_t i = 0; i < HASH_MAP_LIST_SIZE; i++) {
            // Check if the slot is occupied
            if (set->hashmap[size][i].key) {
                // Print the key
                printf("Key : %s\n", set->hashmap[size][i].key);
            }
        }
    }
}

// Main function
int main(void) {
    // Initialize the set
    struct aiv_set myset;
    memset(&myset, 0, sizeof(struct aiv_set));

    // Adding keys to the set
    printf("Adding keys\n");
    aiv_set_insert(&myset, "Hello");
    aiv_set_insert(&myset, "Hello2");
    aiv_set_insert(&myset, "Test");
    aiv_set_insert(&myset, "Foobar");
    aiv_set_insert(&myset, "Foobar");
    aiv_set_insert(&myset, "XYZ");
    aiv_set_insert(&myset, "AAAAAA");
    aiv_set_insert(&myset, "AAAAAa");
    aiv_set_insert(&myset, "AAAAAa");

    // Finding a key in the set
    printf("\nFind key : ");
    aiv_set_find(&myset, "XYZ");

    // Removing a key from the set
    printf("\nRemove key : ");
    aiv_set_remove(&myset, "Hello2");

    // Print the list of keys in the set
    printf("\nPrint Key List\n");
    print_key_list(&myset);

    return 0;
}