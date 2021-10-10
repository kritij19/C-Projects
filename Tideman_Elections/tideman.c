/* Tideman is ranked-choice voting system. 
In a ranked-choice system, voters can vote for more than one candidate. 
Instead of just voting for their top choice, they can rank the candidates in order of preference.
This system is guaranteed to produce the Condorcet winner of the election if one exists.*/ 

#include <stdio.h>
#include <math.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cyclic(int w, int l);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
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

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
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

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
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

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
        preferences[ranks[i]][ranks[i]] = 0;
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                //printf("%i,%i\n",i,j);
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j +1].loser])
            {
                int tempw = pairs[j].winner;
                pairs[j].winner = pairs[j + 1].winner;
                pairs[j + 1].winner = tempw;
                int templ = pairs[j].loser;
                pairs[j].loser = pairs[j + 1].loser;
                pairs[j + 1].loser = templ;
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int count = 0;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[pairs[i].loser][j] == false)
            {
                count++;
            }
        }
        if (count == candidate_count)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        else
        {
            if (!cyclic(pairs[i].winner, pairs[i].loser))
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
            }
        }
    }
    /*for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                printf("locked: %s -> %s\n",candidates[i],candidates[j]);
            }
            
        }
    }
    for (int k = 0; k < candidate_count; k++)
    {
        for (int m = 0; m < candidate_count; m++)
        {
            if (locked[k][m] == true )
            {
                printf("T ");
            }
            else
                printf("F ");
        }
        printf("\n");
    }*/
    return;
}

// Print the winner of the election
void print_winner(void)
{
    
    for (int i = 0; i < candidate_count; i++)
    {
        int count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                count++;
            }
        }
        //printf("%s: %i\n",candidates[i],count);
        if (count == candidate_count)
        {
            printf("%s\n", candidates[i]);
            
        }
    }
    return;
}

bool cyclic(int w, int l)
{
    if (l == w)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[l][i] == true)
        {
            if (cyclic(w, i))
            {
                return true;
            }
        }
    }
    return false;
}
