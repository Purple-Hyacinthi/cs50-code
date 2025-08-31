def get_int_mario():
    while True:
        n = input("Height: ")
        try:
            get_int = int(n)
            if get_int < 1 or get_int > 8:
                print("Value error,the height must be greater than 0 and less than 9")
                continue
            else:
                return get_int
        except ValueError:
            print("Value error,please enter integer numbers like 1 or 2")

def out_mario():
    out_mario = get_int_mario()
    for i in range(out_mario):
        print(f' '*(out_mario-i-1) + '#'* (i+1))

out_mario()
