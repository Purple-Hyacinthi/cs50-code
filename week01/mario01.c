#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int lines = 0;
    do
    {
        lines = get_int("需生成几行：");
    }
    while ( lines < 1 || lines == 0);
    for(int i = 0; i < lines; i++)
    {
        for(int a = lines; a > i+1; a--)
        {
            printf(" ");
        }
        for(int b = 0 ; b < i+1; b++)
        {
            printf("#");
        }
        printf("\n");
    }

}
