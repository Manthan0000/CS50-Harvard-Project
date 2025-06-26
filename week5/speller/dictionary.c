// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdio.h>

#include "dictionary.h"

// Number of buckets in hash table
const unsigned int N = 26;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Hash table
node *table[N];

// Word count
unsigned int word_count = 0;

// Hash function: hashes word to a number
unsigned int hash(const char *word)
{
    // Use first letter of word as hash index, case-insensitive
    return toupper(word[0]) - 'A';
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word to get its index
    unsigned int index = hash(word);

    // Traverse linked list at table[index]
    for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        // Compare word case-insensitively
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true; // Word found
        }
    }
    return false; // Word not found
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    // Buffer to store each word
    char word[LENGTH + 1];

    // Read words from file
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fprintf(stderr, "Memory allocation failed.\n");
            fclose(file);
            return false;
        }

        // Copy word into node
        strcpy(n->word, word);
        n->next = NULL;

        // Hash word to determine which bucket to insert into
        unsigned int index = hash(word);

        // Insert node into hash table (at the beginning of the linked list)
        n->next = table[index];
        table[index] = n;

        // Increment word count
        word_count++;
    }

    // Close dictionary file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop through each bucket
    for (int i = 0; i < N; i++)
    {
        // Free all nodes in the linked list at table[i]
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
