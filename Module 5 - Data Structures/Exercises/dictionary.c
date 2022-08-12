// Implements a dictionary's functionality (implementa a funcionalidade dicionário)

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table (respresanta um nó numa hash table)
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table (número de bickets na hash table)
enum {N = 100000};
// const unsigned int N = 26;

// Hash table
node *table[N];

int dictionary_size = 0;

// Returns true if word is in dictionary, else false (retorna verdadeiro se a palavra está no dicionário, caso contrário falso)
bool check(const char *word)
{
    // Hash word to get a hash number (Usa a função hash na palavra para conseguir um número de hash)
    int hash_number = hash(word);

    // Acess the linked list at that index in has table (Acessa o a linked list daquele número na hash table)
    node *n = table[hash_number];

    // Check on the linked list looking for the word (checa na linked list procurando pela palavra)
    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }

        n = n->next;
    }
    return false;
}

// Hashes word to a number (Retorna um número de hash)
unsigned int hash(const char *word)
{
    // Get the ASCII value of the fisrt letter in the word (pega o valor ASCII da primeira letra da palavra)
    /*int index = tolower(word[0]);

    return index - 'a';*/
    long sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false (carrega o dicionário na memória, retornando verdadeiro se conseguir, caso contrário falso)
bool load(const char *dictionary)
{
    // Open dictionary file (abre o arquivo dictionary)
    FILE *dictionary_pointer = fopen(dictionary, "r");

    // Check if NULL (checa se é NULL)
    if (dictionary == NULL)
    {
        printf("Error: Enable to open %s\n", dictionary);
        return false;
    }

    // Initialise word array (inicializa a array da palavra)
    char next_word[LENGTH + 1];

    // Read words from file one at a time (lê as palavras do arquivo um por vez)
    while (fscanf(dictionary_pointer, "%s", next_word) != EOF)
    {
        // Create a new node for each word (cria um novo nó para cada palavra)
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copy word into node using strcpy (Copia a palavra para o nó usando strcpy)
        strcpy(n->word, next_word);

        // Hash word to get a hash number (Usa a função hash na palavra para conseguir um número de hash)
        int hash_value = hash(next_word);

        // Insert node into hash table at that location (insere o nó na hash table na localização do número hash)
        n->next = table[hash_value];
        table[hash_value] = n;
        dictionary_size++;
    }

    // Close file (fecha o arquivo)
    fclose(dictionary_pointer);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded (retorna o número de palavras do dicionário se carregado, caso contrário retorna 0)
unsigned int size(void)
{
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false (Descarrega o dicionário da memória, retornado verdadeiro se conseguir e falso se não conseguir)
bool unload(void)
{
    // Iterate over hash table and free nodes in each linked list (percorre a hash table e libera os nós de cada linked list)
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];

        while (n != NULL)
        {
            node *tmp = n;
            n = n->next;
            free(tmp);
        }

        if (n == NULL && i == N -1)
        {
            return true;
        }
    }
    return false;
}
