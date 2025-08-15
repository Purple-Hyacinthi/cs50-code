#include <cs50.h>
#include <stdio.h>
#include <string.h>

// 最大候选人人数
#define MAX 9

// Candidates have name and vote count 候选人有名字和选票计数
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates 候选人名单
candidate candidates[MAX];

// Number of candidates候选人人数
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage 检查无效的用法
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates 候选者名单
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

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters 遍历所有选民
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote 检查无效投票
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election 显示选举获胜者
    print_winner();
}

// Update vote totals given a new vote 给新投票更新投票总数
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election 打印选举的获胜者（或获胜者）
void print_winner(void)
{
    int max_votes = 0;

    // Find the maximum vote count 查找最大投票数
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }

    // Print the names of all candidates with the maximum vote count 打印所有得票最多的候选人的名字
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
