while True:
    try:
        height = int(input("Height: "))
        if 1 <= height <= 8:
            break
    except ValueError:
        pass
for i in range(1, height + 1):
    left = " " * (height - i) + "#" * i
    right = "#" * i
    print(left + "  " + right)
