// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "dictionary.h"

uint32_t count = 0u;

void lower(char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower(str[i]);
    }
}

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char copy[100];
    strcpy(copy, word);
    lower(copy);
    uint32_t hash_val = hash(copy);
    node *head = table[hash_val];
    while (head != NULL)
    {
        if (strcmp(head->word, copy) == 0)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash_val = 0;
    for (size_t i = 0; word[i] != '\0'; i++)
    {
        hash_val += word[i];
    }
    return hash_val;
}

void insert(node **head, node *new_node)
{
    if (*head == NULL)
    {
        *head = new_node;
        return;
    }
    node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_node;
}

void print_rec(node *n)
{
    if (n == NULL)
    {
        return;
    }
    printf("%s -> ", n->word);
    print_rec(n->next);
}

void print_table()
{
    for (size_t i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            print_rec(table[i]);
            printf("\n");
        }
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *in = fopen(dictionary, "r");  
    char line[100];
    size_t line_max = 0;  
    while (fgets(line, sizeof(line), in) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';
        lower(line);
        uint32_t hash_val = hash(line);
        node *new_node = malloc(sizeof(node));
        strcpy(new_node->word, line);
        new_node->next = NULL;
        insert(&table[hash_val], new_node);
        count++;
    }

    fclose(in);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (size_t i = 0; i < N; i++)
    {
        node *head = table[i];
        node *temp;
        while (head != NULL)
        {
            temp = head->next;
            free(head);
            head = temp;
        }
        table[i] = NULL;
    }
    return true;
}
