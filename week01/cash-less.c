#include <cs50.h>
#include <stdio.h>

// Corrected: Change return type to int instead of void
int cash(int change);

int main(void)
{
    int change;
    do
    {
        change = get_int("Change owed: ¢");
    }
    while (change < 0);

    int total_coins = cash(change);

    printf("total_coins: %i\n", total_coins);
}

int cash(int change)
{
    int c25 = change / 25;
    change %= 25;

    int c10 = change / 10;
    change %= 10;

    int c5 = change / 5;
    change %= 5;

    int c1 = change;

    int total = c25 + c10 + c5 + c1;
    return total;  
}
