#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates (número máximo de candidatos)
#define MAX 9

// Candidates have name and vote count (candidatos tem nome e número de votos)
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates (array de candidatos)
candidate candidates[MAX];

// Number of candidates (número de candidatos)
int candidate_count;

int voter_count;

// Function prototypes (protótipos das funções)
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage (testa a validade da entrada)
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates (preenche a array de candidatos)
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    voter_count = get_int("Number of voters: ");

    // Loop over all voters (loop para entrada de todos os votos)
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote (checa a validade do voto)
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election (mostra o vencedor da eleição)
    print_winner();
}

// Update vote totals given a new vote (atualiza totais de votos dado um novo voto)
bool vote(string name)
{
    // Loop checking if vote is valid and if it so update the number of votes of the candidate (loop para checar se o voto é válido e sendo atualiza o número de votos do candidato)
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election (imprime o vencedor ou vencedores da eleição)
void print_winner(void)
{
    // Loop to sort the candidates by the number of votes (loop para ordenar os candidatos pelo número de votos)
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count - 1; j++)
        {
            if (candidates[j].votes > candidates[j + 1].votes)
            {
                int x = candidates[j].votes;
                candidates[j].votes = candidates[j + 1].votes;
                candidates[j + 1].votes = x;
                string s = candidates[j].name;
                candidates[j].name = candidates[j + 1].name;
                candidates[j + 1].name = s;
            }
        }
    }
    
    // Display the candidate with the most votes (mostra o candidato com o maior número de votos)
    printf("%s\n", candidates[candidate_count - 1].name);

    // Loop to check if there is more than one candidate winner (loop para checar se tem mais de um candidato vencedor)
    for (int i = 0; i < candidate_count - 1; i++)
    {
        if (candidates[i].votes == candidates[candidate_count - 1].votes)
        {;
            printf ("%s\n", candidates[i].name);
        }
    }
    //return;
}

