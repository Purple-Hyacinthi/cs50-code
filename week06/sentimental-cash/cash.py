def get_float_cash():
    while True:
        n = input("change need: $")
        try:
            get_float = float(n)
            if get_float <= 0 :
                print("Value error,the height must be greater than 0 ")
                continue
            else:
                return get_float
        except ValueError:
            print("Value error,please enter Non-zero real number")

def calculate(get_float):
    get_float *= 100

    c25 = int(get_float//25)
    get_float %= 25

    c10 = int(get_float//10)
    get_float %= 10

    c5 = int(get_float//5)
    get_float %= 5

    c1 = int(get_float//1)

    return c1,c5,c10,c25

def cash_output(c1,c5,c10,c25):
    total = c1+c5+c10+c25
    print("respectively:¢25:{} ¢10:{} ¢5:{} ¢1:{}\ntotal:{}".format(c25,c10,c5,c1,total))

get_float = get_float_cash()
c1,c5,c10,c25 = calculate(get_float)
cash_output(c1,c5,c10,c25)
