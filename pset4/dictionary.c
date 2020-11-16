/*dictionary.c
aka misery.c
Guilherme Albertini
CS50 2019
*/

// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table. 
#define N 10000

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

unsigned int count = 0;
int LOADED = true;
node *head = NULL;

/*========HASH FUNCTION FROM GENIUS, SURPRISINGLY NOT ME AMIRIGHT==============
===============================================================================

/ Below is a case-insensitive implementation of the djb2 hash function.
  
  Adapted by Neel Mehta (@hathix)
  https://github.com/hathix/cs50-section/blob/master/code/7/
  sample-hash-functions/good-hash-function.c
*/
unsigned int hashIt(const char *word)
{
    unsigned long hash = 5381;

    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash % N;
}
 
/*===========================================================================
============================== ಠ_ಠ=========================================*/


/*=======================LOAD DICTIONARY TO MEMORY=============================
=============================================================================*/
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];
    
    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        //Create new "box ptr" or node
        node *new_node = malloc(sizeof(node));
        
        //Initialize new_node with 0s to avoid valgrind uninitialized value flag
        memset(new_node, 0, sizeof(node));
        
        //Copy word into node if it exists
        if (!new_node)
        {
            unload();
            return false;
        }
        else
        {
            strcpy(new_node->word, word);    
        }

        //Hash words using borrowed algorithm
        int index = hashIt(word);
        head = hashtable[index];

        //Add to start of bucket llist if not there else append
        if (head == NULL)
        {
            hashtable[index] = new_node;
            head = new_node;
        }
        else
        {
            new_node->next = head;
            hashtable[index] = new_node;
            head = new_node;
        }
        
        
        //Keep track of words
        count++;
    }
    
    // Close dictionary
    fclose(file);
    
    // Indicate success
    return true;
}

/*================================================(ง'̀-'́)ง=====================
============================================================================*/


/*==================DICTIONARY WORD COUNT=====================================
============================================================================*/

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return LOADED ? count : 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //Match hash indexes if found to chekc or return false
    node *cursor = hashtable[hashIt(word)];

    while (cursor)
    {
        int pass = strcasecmp(cursor->word, word);
        if (pass == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    return false;
}
    

/*===========================================================================
============================================================================*/

/*=============UNLOAD THAT MEMORY, DICTIONARY================================
============================================================================*/

// Unloads dictionary from memory, returning true if successful else false

bool unload(void)
{
    for (int i = 0; i < N; i ++)
    {
        node *del = hashtable[i];
        
        while (del)
        {
            node *bucket = del;
            del = del->next;
            free(bucket);
        }
        //hashtable[N] = NULL;
        hashtable[i] = NULL;
    }
    return true;
}

/*==================ʕノ•ᴥ•ʔノ ︵ ┻━┻===<me in this pset========================
============================================================================*/


/*Future work: Try a trie (though slower, no?) Further optimize and include some
gizmos along the way. This was miserable. I let Jesus take the wheel. And cried*/