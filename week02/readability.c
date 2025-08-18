#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // 处理除数为0的情况
    if (words == 0) {
        printf("Before Grade 1\n");
        return 0;
    }

    // 计算每100个单词的字母和句子数
    float L = (float)letters / words * 100;
    float S = (float)sentences / words * 100;
    float index_value = 0.0588 * L - 0.296 * S - 15.8;

    int index;
    if (index_value < 0)
        index = (int)(index_value - 0.5);
    else
        index = (int)(index_value + 0.5);

    // 根据指数输出对应等级
    if (index < 1)
        printf("Before Grade 1\n");
    else if (index >= 16)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n", index);
}

int count_letters(string text)
{
    int letter = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if(isalpha(text[i]))
            letter += 1;
    }
    return letter;
}

// 单词计数函数
int count_words(string text)
{
    int word = 0;
    bool in_word = false;
    int len = strlen(text);

    for (int j = 0; j < len; j++)
    {
        // 遇到非空格字符
        if (!isspace(text[j]))
        {
            if (!in_word)
            {
                word++;
                in_word = true;
            }
        }
        else  // 遇到空格
        {
            in_word = false;
        }
    }
    return word;
}

// 句子计数函数
int count_sentences(string text)
{
    int sentence = 0;
    int len = strlen(text);

    for (int k = 0; k < len; k++)
    {
        // 检查句子结束符
        if (text[k] == '.' || text[k] == '!' || text[k] == '?')
        {
            sentence++;
            // 跳过连续结束符
            while (k + 1 < len && (text[k+1] == '.' || text[k+1] == '!' || text[k+1] == '?'))
            {
                k++;
            }
        }
    }
    return sentence;
}
