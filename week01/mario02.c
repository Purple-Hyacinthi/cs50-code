#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int bricks);

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);

    for (int i = 0; i < n; i++)
    {
        print_row(n-i-1, i+1);
    }
}

void print_row(int spaces, int bricks)
{
    for (int a = 0; a < spaces; a++)
    {
        printf(" ");
    }
    for (int b = 0; b < bricks; b++)
    {
        printf("#");
    }
    printf("  ");
    for (int c = 0; c < bricks; c++)
    {
        printf("#");
    }
    printf("\n");
}

