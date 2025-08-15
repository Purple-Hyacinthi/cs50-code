#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string argv);
char rotate(char c, int k);
int main(int argc, string argv[])
{
    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int k = atoi(argv[1]);//atoi - 转换字符串为整形
    string plainttext = get_string("plaintext: ");
    char ciphertext[strlen(plainttext) + 1];
    for (int n = 0; n < strlen(plainttext); n++)
    {
        ciphertext[n] = rotate(plainttext[n], k);
    }
    ciphertext[strlen(plainttext)] = '\0'; // 补结束符
    printf("ciphertext:%s\n", ciphertext);
    return 0;
}

bool only_digits(string argv)
{
    for (int i = 0; i < strlen(argv); i++)
    {
        if (!isdigit((unsigned char) argv[i]))
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int k)
{
    if (c >= 'a' && c <= 'z')
    {
        return 'a' + (c - 'a' + k) % 26;
    }
    else if (c >= 'A' && c <= 'Z')
    {
        return 'A' + (c - 'A' + k) % 26;
    }
    else
    {
        return c;
    }
}
