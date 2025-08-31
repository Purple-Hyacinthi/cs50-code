def get_int_card():
    while True:
        n = input("Number: ")
        try:
            try_card = int(n)
            card = str(try_card)
            sum_card0 = 0
            sum_card1 = 0
            sum_card0 = sum(int(x) * 2 if int(x) * 2 < 10 else int(x) * 2 - 9 for x in card[-2::-2])#将字符串切片转为整形
            sum_card1 = sum(int(x) for x in card[-1::-2])
            sum_card =sum_card1 + sum_card0
            return card, sum_card
        except ValueError:
            print("Value error,please enter ture card numbers ")

def first_judge_card(card, sum_card):
    if sum_card % 10 != 0:
        return False
    if len(card) not in [13, 14, 15, 16]:
        return False
    return True

def type_card(card):
    length = len(card)
    start = card[0:2]

    # 按最严格条件优先匹配
    if length == 15 and start in ['34', '37']:
        return 'AMEX'
    elif length == 16:
        if 51 <= int(start) <= 55:
            return 'MASTERCARD'
    if (length == 13 or length == 16) and card[0] == '4':
        return 'VISA'
    return 'INVALID'


card_number, sum_number = get_int_card()
if first_judge_card(card_number, sum_number):
    name = type_card(card_number)
    print("card_name:",name)
else:
    print("INVALID")
