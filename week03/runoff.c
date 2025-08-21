// 引入必要的头文件
#include <cs50.h>   // CS50库，提供简化输入输出函数
#include <stdio.h>  // 标准输入输出库
#include <string.h> // 字符串处理函数库

// 定义常量
#define MAX_VOTERS 100      // 最大选民数
#define MAX_CANDIDATES 9    // 最大候选人数

// 声明全局变量
int preferences[MAX_VOTERS][MAX_CANDIDATES]; // 存储每个选民的偏好顺序

// 定义候选人结构体
typedef struct
{
    string name;        // 候选人姓名
    int votes;          // 得票数
    bool eliminated;    // 是否已被淘汰
} candidate;

candidate candidates[MAX_CANDIDATES]; // 候选人数组
int voter_count;                      // 选民总数
int candidate_count;                  // 候选人总数

// 函数原型声明
bool vote(int voter, int rank, string name); // 记录投票
void tabulate(void);                         // 统计票数
bool print_winner(void);                     // 检查是否有获胜者
int find_min(void);                          // 找到最低得票数
bool is_tie(int min);                        // 检查是否平局
void eliminate(int min);                     // 淘汰候选人

// 主函数
int main(int argc, string argv[])
{
    // 检查命令行参数数量是否正确
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n"); // 打印使用说明
        return 1; // 返回错误代码1
    }

    // 设置候选人数
    candidate_count = argc - 1;
    // 检查是否超过最大候选人数限制
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES); // 打印错误信息
        return 2; // 返回错误代码2
    }
    
    // 初始化候选人数组
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1]; // 设置候选人姓名
        candidates[i].votes = 0;          // 初始票数为0
        candidates[i].eliminated = false; // 初始状态为未被淘汰
    }

    // 获取选民数量
    voter_count = get_int("Number of voters: ");
    // 检查是否超过最大选民数限制
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS); // 打印错误信息
        return 3; // 返回错误代码3
    }

    // 收集每个选民的投票偏好
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1); // 获取选民的第j偏好
            if (!vote(i, j, name)) // 尝试记录投票
            {
                printf("Invalid vote.\n"); // 如果投票无效，打印错误信息
                return 4; // 返回错误代码4
            }
        }
        printf("\n"); // 每个选民投票结束后换行
    }

    // 主循环：进行多轮投票直到有获胜者或平局
    while (true)
    {
        tabulate(); // 统计票数
        bool won = print_winner(); // 检查是否有获胜者
        if (won) // 如果有获胜者
        {
            break; // 跳出循环
        }

        int min = find_min(); // 找到未被淘汰的候选人中的最低得票数
        bool tie = is_tie(min); // 检查是否所有未被淘汰的候选人得票数相同

        if (tie) // 如果是平局
        {
            // 打印所有未被淘汰的候选人
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated) // 如果候选人未被淘汰
                {
                    printf("%s\n", candidates[i].name); // 打印候选人姓名
                }
            }
            break; // 跳出循环
        }

        eliminate(min); // 淘汰得票数等于最低票数的候选人
        // 重置所有候选人的票数为0，准备下一轮投票
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0; // 程序正常结束
}

// 记录有效投票的候选人索引，并检查是否重复投票
bool vote(int voter, int rank, string name)
{
    int candidate_index = -1; // 初始化候选人索引为-1（表示未找到）
    
    // 遍历所有候选人，查找匹配的姓名
    for (int i = 0; i < candidate_count; i++)
    {
        // 比较输入的姓名与候选人姓名
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidate_index = i; // 找到匹配的候选人，记录索引
            break; // 跳出循环
        }
    }
    
    // 如果候选人不存在，返回false
    if (candidate_index == -1)
    {
        return false; // 表示无效投票
    }
    
    // 检查该选民是否已经投票给这个候选人
    for (int i = 0; i < rank; i++) // 遍历该选民之前的投票记录
    {
        // 检查是否已经投过这个候选人
        if (preferences[voter][i] == candidate_index)
        {
            return false; // 如果已经投过，返回false表示无效投票
        }
    }
    
    // 记录投票
    preferences[voter][rank] = candidate_index; // 存储候选人索引到偏好数组中
    return true; // 返回true表示投票成功
}

// 统计票数
void tabulate(void)
{
    // 遍历所有选民
    for (int i = 0; i < voter_count; i++)
    {
        // 遍历每个选民的所有偏好
        for (int j = 0; j < candidate_count; j++)
        {
            int cand_index = preferences[i][j]; // 获取选民的第j偏好对应的候选人索引
            // 检查该候选人是否已被淘汰
            if (!candidates[cand_index].eliminated)
            {
                candidates[cand_index].votes++; // 如果未被淘汰，增加其票数
                break; // 跳出内层循环，处理下一个选民
            }
        }
    }
}

// 检查是否有候选人获得超过半数的选票
bool print_winner(void)
{
    // 遍历所有候选人
    for (int i = 0; i < candidate_count; i++)
    {
        // 检查候选人得票是否超过总票数的一半
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name); // 打印获胜者姓名
            return true; // 返回true表示有获胜者
        }
    }
    return false; // 返回false表示没有获胜者
}

// 找到未被淘汰的候选人中的最低得票数
int find_min(void)
{
    int min = voter_count; // 初始化最低票数为选民总数（最大值）
    // 遍历所有候选人
    for (int i = 0; i < candidate_count; i++)
    {
        // 检查候选人是否未被淘汰且得票数小于当前最低票数
        if (!candidates[i].eliminated && candidates[i].votes < min)
        {
            min = candidates[i].votes; // 更新最低票数
        }
    }
    return min; // 返回最低票数
}

// 检查所有未被淘汰的候选人是否得票数相同（平局）
bool is_tie(int min)
{
    // 遍历所有候选人
    for (int i = 0; i < candidate_count; i++)
    {
        // 检查候选人是否未被淘汰且得票数不等于最低票数
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false; // 返回false表示不是平局
        }
    }
    return true; // 返回true表示是平局
}

// 淘汰得票数等于最低票数的候选人
void eliminate(int min)
{
    // 遍历所有候选人
    for (int i = 0; i < candidate_count; i++)
    {
        // 检查候选人是否未被淘汰且得票数等于最低票数
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            candidates[i].eliminated = true; // 标记候选人为已淘汰
        }
    }
}
