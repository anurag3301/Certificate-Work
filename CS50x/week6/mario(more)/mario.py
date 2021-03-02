while True:
    n = input("Height: ")
    try:
        n = int(n)
        if n > 0 and n < 9:
            break
    except:
        pass

for i in range(n):
    x = " " * (n - i - 1)
    y = "#" * (i + 1) + "  " + "#" * (i + 1)
    print(x + y)