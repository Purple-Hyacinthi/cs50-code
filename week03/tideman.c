// 引入必要的头文件
#include <cs50.h>  // CS50库，提供get_int, get_string等函数
#include <stdio.h> // 标准输入输出库
#include <string.h> // 字符串处理库

// 定义最大候选人数为9
#define MAX 9

// 定义全局变量

// preferences[i][j] 表示偏好候选人i胜过候选人j的选民数量
int preferences[MAX][MAX];

// locked[i][j] 表示在图中有一条从i指向j的边（即i被锁定胜过j）
bool locked[MAX][MAX];

// 定义pair结构体，表示一对候选人的胜负关系
typedef struct
{
    int winner; // 胜者索引
    int loser;  // 败者索引
} pair;

// 候选人名字数组
string candidates[MAX];
// 存储所有可能的候选人对的数组，最大数量为MAX*(MAX-1)/2
pair pairs[MAX * (MAX - 1) / 2];

// 当前实际的pair数量
int pair_count;
// 当前实际的候选人数
int candidate_count;

// 函数声明
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool has_path(int start, int target, bool visited[]);
bool creates_cycle(int winner, int loser);
void lock_pairs(void);
void print_winner(void);

// 主函数
int main(int argc, string argv[])
{
    // 检查命令行参数是否正确
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // 初始化候选人数组
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

    // 初始化locked图，所有边设为false
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0; // 初始化pair计数为0
    int voter_count = get_int("Number of voters: "); // 获取选民数量

    // 处理每个选民的投票
    for (int i = 0; i < voter_count; i++)
    {
        // ranks数组存储该选民对候选人的排名，ranks[0]是最偏好的候选人
        int ranks[candidate_count];

        // 获取选民对每个排名的选择
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks)) // 如果投票无效
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks); // 记录该选民的偏好到preferences数组

        printf("\n");
    }

    add_pairs();    // 根据preferences数组生成候选人对
    sort_pairs();   // 按优势强度对pairs进行排序
    lock_pairs();   // 锁定不会形成环的边
    print_winner(); // 打印胜者
    return 0;
}

// 处理投票，将候选人名字转换为索引并存入ranks数组
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0) // 比较名字是否匹配
        {
            ranks[rank] = i; // 将候选人索引存入ranks数组的指定排名位置
            return true;
        }
    }
    return false; // 没有找到匹配的候选人名字
}

// 根据单个选民的排名更新preferences数组
void record_preferences(int ranks[])
{
    // 遍历所有排名组合
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // 对于每一对(i,j)，其中i的排名高于j，增加preferences[ranks[i]][ranks[j]]的计数
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// 生成所有候选人对，并存入pairs数组
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // 比较候选人i和j之间的偏好强度
            if (preferences[i][j] > preferences[j][i])
            {
                // i胜过j，添加这对
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                // j胜过i，添加这对
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            // 如果平局，不添加
        }
    }
    return;
}

// 使用选择排序按优势强度对pairs进行降序排序
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int max_index = i; // 假设当前最大元素位于i
        for (int j = i + 1; j < pair_count; j++)
        {
            // 计算当前pair j的优势强度
            int strength_j = preferences[pairs[j].winner][pairs[j].loser];
            // 计算当前最大pair的优势强度
            int strength_max = preferences[pairs[max_index].winner][pairs[max_index].loser];
            if (strength_j > strength_max)
            {
                max_index = j; // 更新最大元素索引
            }
        }
        // 交换当前元素与找到的最大元素
        pair temp = pairs[i];
        pairs[i] = pairs[max_index];
        pairs[max_index] = temp;
    }
    return;
}

// 深度优先搜索（DFS）检查从start到target是否存在路径
bool has_path(int start, int target, bool visited[])
{
    if (start == target) // 如果起点就是目标，找到路径
    {
        return true;
    }
    visited[start] = true; // 标记当前节点为已访问
    // 遍历所有候选人
    for (int i = 0; i < candidate_count; i++)
    {
        // 如果存在从start到i的边且i未被访问
        if (locked[start][i] && !visited[i])
        {
            // 递归检查从i到target是否存在路径
            if (has_path(i, target, visited))
            {
                return true;
            }
        }
    }
    return false; // 没有找到路径
}

// 检查添加从winner到loser的边是否会创建环
bool creates_cycle(int winner, int loser)
{
    if (winner == loser) // 如果winner和loser是同一人，直接形成环
    {
        return true;
    }
    bool visited[MAX] = {false}; // 初始化访问数组
    // 检查是否存在从loser到winner的路径（如果存在则会形成环）
    return has_path(loser, winner, visited);
}

// 锁定不会形成环的边
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // 如果添加当前pair不会形成环
        if (!creates_cycle(pairs[i].winner, pairs[i].loser))
        {
            // 锁定该边
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// 打印胜者：即没有入边的候选人（图的源）
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool has_incoming = false; // 假设没有入边
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i]) // 如果存在从j到i的边
            {
                has_incoming = true; // 标记有入边
                break;
            }
        }
        if (!has_incoming) // 如果没有入边，即为胜者
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
