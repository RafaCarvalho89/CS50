#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates (máximo de votantes e de candidatos)
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i (preferences[i][j] é j-ésima preferência para o votante i)
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status (cadidatos tem nome, votos, status eliminado)
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates (array de candidatos)
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates (números de votantes e candidatos)
int voter_count;
int candidate_count;

int tab;

// Function prototypes (protótipos das funções)
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage (checa a validade da entrada)
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates (preenche a array de candidatos)
    candidate_count = argc - 1;

    // Check for invalid number of candidates (checa a validade do número de candidatos)
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    // Populate candidates with argv[] (preenche candidates com argv[])
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");

    // Check for invalid number of voters (checa a validade do número de votantes)
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes (loop para pegar os votos)
    for (int i = 0; i < voter_count; i++)
    {
        // Query for each rank (loop para pegar o rank dos votos)
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid (registra o voto, a menos que seja inválido)
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists (mantém a eleição até que exista um vencedor )
    while (true)
    {
        // Calculate votes given remaining candidates (calcula os votos dados aos candidatos remanescentes)
        tabulate();

        // Check if election has been won (checa se a eleição possui um vencedor)
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates (elimina o(s) candidato(s) que está(ão) na última colocação)
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins (se verdadeiro, todos vencem)
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes (eliminar qualquer candidato que tenha o número mínimo de votos)
        eliminate(min);

        // Reset vote counts back to zero (reseta a contagem de votos para zero)
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid (registra a preferência se o voto for válido)
bool vote(int voter, int rank, string name)
{
    // Check if vot is valid (checa se o voto é válido)
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates (tabula os votos para os candidatos não eliminados)
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
        {
            for (int j = 0; j < candidate_count; j++)
                {
                    if (candidates[preferences[i][j]].eliminated == false)
                    {
                        candidates[preferences[i][j]].votes++;
                        break;
                    }
                }
        }
    return;
}

// Print the winner of the election, if there is one (imprime o vencedor da eleição)
bool print_winner(void)
{
    int x = 0;

    // Check who is the most voted candidate (checa quem é o candidato mais votado)
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes > x)
            {
                x = candidates[i].votes;
            }
        }
    }

    // Check if the most voted has the majority of total votes (checa se o mais votado tem a maioria do total dos votos)
    if (x > (voter_count / 2))
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes == x)
            {
                printf("%s\n", candidates[i].name);
            }
        }
        return true;
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has (retorna o número mínimo de votos entre os candidatos restantes)
int find_min(void)
{
    // Check who is the least voted candidate (checa quem é o candidato menos votado)
    int x = MAX_VOTERS;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes < x)
            {
                x = candidates[i].votes;
            }

        }
    }
    return x;
}

// Return true if the election is tied between all candidates, false otherwise (retorna verdadeiro se a eleição está empatada entre todos os candidatos e falso caso contrário)
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes > min)
            {
                return false;
            }
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place (elimina o(s) candidato(s) na última colocação)
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes == min)
            {
                candidates[i].eliminated = true;
            }
        }
    }
    return;
}
