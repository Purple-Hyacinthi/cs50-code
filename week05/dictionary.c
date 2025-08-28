//实现字典的功能
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include "dictionary.h"

//表示哈希表中的一个节点
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO：选择哈希表中的桶数
const unsigned int N = 26;

//哈希表
node *table[N];

//如果单词在字典中返回true，否则返回false
bool check(const char *word)
{
    unsigned int index = hash(word);
    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}



//将单词散列到一个数字
unsigned int hash(const char *word)
{
    if (word[0] == '\0')
    {
        return 0;
    }
    return toupper(word[0]) - 'A';

}

//将字典加载到内存中，成功则返回true，否则返回false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    char buffer[LENGTH + 1];
    while (fscanf(source, "%s", buffer) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(source);
            return false;
        }

        // 复制单词到节点
        strcpy(new_node->word, buffer);
        new_node->next = NULL;

        // 计算哈希值并插入
        unsigned int index = hash(buffer);
        if (table[index] != NULL) {
            new_node->next = table[index];
        }
        table[index] = new_node;
    }

    fclose(source);
    return true;
}

//如果已加载则返回字典中的单词数，如果尚未加载则返回0
unsigned int size(void)
{
    unsigned int count = 0;
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            count++;
            cursor = cursor->next;
        }
    }
    return count;
}

//从内存中卸载字典，如果成功则返回true，否则返回false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        table[i] = NULL;  // 清空指针
    }
    return true;
}
