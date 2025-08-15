#include <cs50.h>
#include <stdio.h>
#include <string.h>

char *type(char *card, int *sum_ptr);

int main(void)
{
    char card[17];
    long number;

    number = get_long("Number: ");
    sprintf(card, "%ld", number);
    while (strlen(card) != 13 && strlen(card) != 15 && strlen(card) != 16)
    {
        printf("INVALID\n");
        return 0;
    }

    int total_sum;
    char *name = type(card, &total_sum);

    if (total_sum % 10 == 0 && name != NULL)
    {
        printf("%s\n", name);
    }
    else
    {
        printf("INVALID\n");
    }
}

char *type(char *card, int *sum_ptr)
{
    int len = strlen(card);
    int sum = 0;
    char *name = NULL;
    int double_digit = 0;//利用0表示false
    for (int i = len - 1; i >= 0; i--)
    {
        int digit = card[i] - '0';//将ASCII字符转换为数字（0-9）

        if (double_digit)//判断真假
        {
            digit *= 2;
            sum += (digit > 9) ? (digit - 9) : digit;
        }
        else
        {
            sum += digit;
        }
        double_digit = !double_digit;//真假反转（保证双倍乘法只在偶数位进行）
    }
    *sum_ptr = sum;

    // 判断卡类型
    if (len == 15 && card[0] == '3' && (card[1] == '4' || card[1] == '7'))
    {
        name = "AMEX";
    }
    else if (len == 16 && card[0] == '5' && card[1] >= '1' && card[1] <= '5')
    {
        name = "MASTERCARD";
    }
    else if ((len == 13 || len == 16) && card[0] == '4')
    {
        name = "VISA";
    }

    return name;
}
