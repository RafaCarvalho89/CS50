#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates (número máximo de candidatos)
#define MAX 9

// preferences[i][j] is number of voters who prefer 'i' over 'j' (preferences[i][j] é o número de votantes que preferem o 'i' em vez do 'j')
int preferences[MAX][MAX];

// locked[i][j] means 'i' is locked in over 'j' (locked[i][j] significa que 'i' está travado em 'j', ou que 'i' aponta para 'j')
bool locked[MAX][MAX];

// Each pair has a winner, loser (cada par tem um vencedor, perdedor)
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates (array de candidatos)
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes (protótipo das funções)
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage (checa a validade da entrada)
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs (limpa a array dos pares travados)
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes (pega os votos de cada votante)
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference (rank[i] é i-ésima preferência dos vontantes)
        int ranks[candidate_count];

        // Query for each rank (pega a opção para cada rank)
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote (atualiza os novos votos ao ranks)
bool vote(int rank, string name, int ranks[])
{
    // Compare the name voted to the candidate's names and rank the vote (compara o nome votado com os nomes dos candidatos e ranqueia o voto)
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks (atualiza as preferências dadas)
void record_preferences(int ranks[])
{
    // Analyse voter's ranks to add preference of candidate ranks[i] over candidate ranks[j] (analisa os ranques dos votantes para adicionar a prefenrência o candidato ranks[i] sobre o candidato ranks[j])
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other (registra os pares de candidatos onde um tem preferência sobre o outro)
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory (organiza os pares em ordem decrescente pela força da vitória (diferença de votos))
void sort_pairs(void)
{
    pair temp;

    for (int i = pair_count - 1; i >= 0; i--)
    {
        for (int j = 0; j <= i - 1; j++)
        {
            if ((preferences[pairs[j].winner][pairs[j].loser]) < (preferences[pairs[j + 1].winner][pairs[j + 1].loser]))
            {
                temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
    return;
}

// Test for cycle by checking arrow coming into each candidate (testa para o ciclo checando a fleccha em cada candidato)
bool cycle(int end, int cycle_start)
{
    // Return true if there is a cycle created - Recursion base case (Retorna verdadeiro se há um ciclo criado - Caso base da recursão)
    if (end == cycle_start)
    {
        return true;
    }
    // Loop through candidates - Recursive case (checa através dos candidatos - Caso recursivo)
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i])
        {
            if (cycle(i, cycle_start))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles (trava os pares de candidatos sem criar ciclos)
void lock_pairs(void)
{
    // Loop through pairs in cycle function (checa todos os pares na função cycle)
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election (imprime o vencedor da eleição)
void print_winner(void)
{
    // Winner is the candidate with no arrows pointing to him (vencedor é o candidato que não tem flechas apontando para ele)
    for (int i = 0; i < candidate_count; i++)
    {
        int false_count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                false_count++;
                if (false_count == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}

