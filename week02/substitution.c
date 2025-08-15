#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string key);
char rotate(char plaintext, string key);

int main(int argc, string argv[])
{
    if (argc != 2 || strlen(argv[1]) != 26 || !only_digits(argv[1]))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string plainttext = get_string("plaintext: ");
    char ciphertext[strlen(plainttext) + 1];
    for (int x = 0; x < strlen(plainttext); x++)
    {
        ciphertext[x] = rotate(plainttext[x], argv[1]);
    }
    ciphertext[strlen(plainttext)] = '\0';
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

bool only_digits(string key)
{
    bool seen[26] = {false};
    for (int i = 0; i < 26; i++)
    {
        char c = key[i];
        if (!isalpha(c))
        {
            return false;
        }
        int index = tolower(c) - 'a';
        if (seen[index])
        {
            return false;
        }
        seen[index] = true;
    }
    return true;
}

char rotate(char plaintext, string key)
{
    if (isupper(plaintext))
    {
        return toupper(key[plaintext - 'A']);
    }
    else if (islower(plaintext))
    {
        return tolower(key[plaintext - 'a']);
    }
    else
    {
        return plaintext;
    }
}
