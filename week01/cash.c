#include <cs50.h>
#include <stdio.h>
/*
知识点：*变量名==>变量指针存储了变量地址
可利用&取对应变量地址
例如：
int num = 100;
int *ptr = &num
num = 100
&num =0xf...(内存地址)
ptr = &num
*ptr = 100
*/
void cash(int change, int *c25, int *c10, int *c5, int *c1);

int main(void)
{
    int change;
    do
    {
        change = get_int("Change owed: ¢");
    }
    while (change < 0);

    int c25, c10, c5, c1;
    cash(change, &c25, &c10, &c5, &c1);

    int total = c25 + c10 + c5 + c1;
    printf("total_coins:%i,\nrespectively:¢25:%i ¢10:%i ¢5:%i ¢1:%i\n", total, c25, c10, c5, c1);
}

void cash(int change, int *c25, int *c10, int *c5, int *c1)
{
    *c25 = change / 25;
    change %= 25;

    *c10 = change / 10;
    change %= 10;

    *c5 = change / 5;
    change %= 5;

    *c1 = change;
}
