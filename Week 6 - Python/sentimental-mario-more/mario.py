from cs50 import get_int

height = get_int("Height: ")

while height <= 0 or height > 8:
    height = get_int("Height: ")

for i in range(1, height + 1):
    for j in range(height - i):
        print(" ", end="")
    for j in range(i):
        print("#", end="")
    print("  ", end="")
    for j in range(i):
        print("#", end="")
    print()
