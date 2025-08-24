#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    //从输入文件复制头文件到输出文件
    //unit无符号，int有符号，加上8_t/16_t是为了保证跨平台稳定性
    uint8_t header[HEADER_SIZE];
    //fread等本身就是批量读取对象文本
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    //从输入文件中读取样本并将更新后的数据写入输出文件
    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    fclose(input);
    fclose(output);
}
