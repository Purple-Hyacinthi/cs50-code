//模拟血型基因遗传
#define _DEFAULT_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//每个人有一对父母和两个等位基因
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;//规定缩进长度

//声明函数
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    //种子随机数生成器
    srandom(time(0));// 用当前时间初始化随机数生成器

    //创建一个三代同堂的新家庭
    person *p = create_family(GENERATIONS);

    //打印血型家谱
    print_family(p, 0);

   //释放内存
    free_family(p);
}

//用' generations '创建一个新的个人
person *create_family(int generations)
{
    //为新人分配内存
    person *new_person = malloc(sizeof(person));
    if (new_person == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for new person\n");
        exit(1);
    }

    //如果还有代要创建（旨在先完成家族生成）
    if (generations > 1)
    {
        //通过递归调用Create为当前成员创建两个新的父级_家庭
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // 设置当前人的父母指针
        new_person->parents[0] = parent0;
        new_person->parents[1] = parent1;

        // 随机分配当前人的等位基因，基于父母的等位基因
        new_person->alleles[0] = parent0->alleles[random() % 2];
        new_person->alleles[1] = parent1->alleles[random() % 2];
    }

    // 如果没有代要创建（溯源到最初祖先时，随机生成其遗传信息）
    else
    {
        // 设置父母指针为NULL
        new_person->parents[0] = NULL;
        new_person->parents[1] = NULL;

        // 随机分配等位基因
        new_person->alleles[0] = random_allele();
        new_person->alleles[1] = random_allele();
    }

   //返回新创建的人（本质上相当于课堂中的list列表头）
    return new_person;
}

//释放‘ p ’和‘ p ’的所有祖先。
void free_family(person *p)
{
    // 基本情况
    if (p == NULL)
    {
        return;
    }

    // 递归释放父母
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // 释放孩子
    free(p);
}

//打印每个家庭成员及其等位基因。
void print_family(person *p, int generation)
{
    // 基本情况
    if (p == NULL)
    {
        return;
    }

    //打印缩进
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    //打印人
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    //打印当前代的父节点
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// 随机选择一个血型等位基因。
char random_allele()
{
    int r = random() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
