# 导入csv模块用于处理CSV文件
import csv
# 导入sys模块用于访问命令行参数
import sys

# 定义主函数
def main():
    # TODO：检查命令行使用情况(格式规定: python dna.py 数据库.csv 序列.txt)
    # 如果参数数量不等于3（脚本名+数据库文件+序列文件）
    if len(sys.argv) != 3:
        # 打印正确用法提示
        print("用法: python dna.py 数据库.csv 序列.txt")
        # 退出程序并返回错误代码1
        sys.exit(1)

    # TODO：将数据库文件读入变量
    # 以只读模式打开命令行指定的数据库CSV文件
    '''
    open() 打开文件并返回文件对象

    as file 将该文件对象赋值给变量 file

    在代码块内使用 file 操作文件

    退出代码块时自动调用 file.close() 关闭文件
    '''
    with open(sys.argv[1], "r") as db_file:
        # 创建CSV字典读取器，第一行作为字段名
        reader = csv.DictReader(db_file)
        # 将读取的所有行存入列表database
        database = [row for row in reader]

    # TODO：将DNA序列文件读取到变量中
    # 以只读模式打开命令行指定的DNA序列文件
    with open(sys.argv[2], "r") as dna_file:
        # 读取整个文件内容到dna_sequence变量
        dna_sequence = dna_file.read()

    # TODO：找出DNA序列中每个STR的最长匹配
    # 创建空字典用于存储STR计数
    str_counts = {}
    # 遍历数据库中的每一行（每个人）
    for row in database:
        # 遍历当前行的每个键（字段名）
        for str_name in row.keys():
            # 排除"name"字段（只处理STR字段）
            if str_name != "name":
                # 计算当前STR在DNA序列中的最长连续重复次数
                str_counts[str_name] = longest_match(dna_sequence, str_name)

    # TODO: 检查数据库是否匹配DNA序列
    # 遍历数据库中的每一行（每个人）
    for row in database:
        # 检查当前人的所有STR计数是否匹配DNA序列的计数
        # all()确保所有STR都匹配，int()将字符串计数值转为整数
        if all(str_counts[str_name] == int(row[str_name]) for str_name in str_counts):
            # 如果匹配，打印对应人名
            print(f"{row['name']}")
            # 结束程序
            return

    # 没有匹配时打印No match
    print("No match")
    # 结束程序
    return

# 定义函数：计算子序列在序列中的最长连续重复次数
def longest_match(sequence, subsequence):
    """返回序列中子序列的最长运行长度。"""
    # 初始化最长连续计数为0
    longest_run = 0
    # 获取子序列长度
    subsequence_length = len(subsequence)
    # 获取主序列长度
    sequence_length = len(sequence)

    # 遍历主序列中的每个字符位置
    for i in range(sequence_length):
        # 初始化当前位置的连续计数为0
        count = 0

        # 使用无限循环检测连续重复
        while True:
            # 计算当前检测段的起始位置
            start = i + count * subsequence_length
            # 计算当前检测段的结束位置
            end = start + subsequence_length

            # 如果当前段超出序列长度，跳出循环
            if end > sequence_length:
                break

            # 检查当前段是否匹配子序列
            if sequence[start:end] == subsequence:
                # 匹配成功，计数增加
                count += 1
            else:
                # 匹配失败，跳出循环
                break

        # 更新全局最长连续计数
        longest_run = max(longest_run, count)

    # 返回找到的最长连续重复次数
    return longest_run

# 调用主函数
main()
