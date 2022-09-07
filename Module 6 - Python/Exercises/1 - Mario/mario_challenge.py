from cs50 import get_int

while True:
    height = get_int("Height (between 1 and 8): ")
    if height > 0 and height < 9:
        break

for i in range(height):
    print(" " * (height - i - 1), end="")
    print("#" * (i + 1), end="")
    print(" ", end="")
    print("#" * (i + 1))

    #for j in range(height - i - 1):
    #    print(" ", end="")
    #for k in range(i + 1):
    #    print("#", end="")
    #print(" ", end="")
    #for k in range(i + 1):
    #    print("#", end="")
    #print("")