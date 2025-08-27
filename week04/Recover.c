#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// 检查缓冲区前4字节内容是否符合JPEG文件头特征
int is_jpeg_header(const uint8_t *buffer) {
    return (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0);
}

int main(const int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[512];
    FILE *out = nullptr;        // 当前输出的JPEG文件
    int jpeg_count = 0;      // 已发现的JPEG文件计数器

    while (fread(buffer, 1, 512, card) == 512)
    {
        // 检查是否为新的JPEG文件头
        if (is_jpeg_header(buffer))
        {
            // 如果已有打开的JPEG文件，先关闭
            if (out != NULL) {
                fclose(out);
            }

            // 创建新的JPEG文件
            char filename[8];
            sprintf(filename, "%03i.jpg", jpeg_count++);
            out = fopen(filename, "w");
            if (out == NULL) {
                fclose(card);
                printf("Could not create JPEG file.\n");
                return 1;
            }
        }

        // 如果当前有打开的JPEG文件，写入数据块
        if (out != NULL) {
            fwrite(buffer, 1, 512, out);
        }
    }

    // 清理资源
    fclose(card);
    if (out != NULL) {
        fclose(out);
    }

    return 0;
}
