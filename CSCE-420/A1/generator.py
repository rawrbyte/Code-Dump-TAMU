import random
import time

obstacles = random.randint(0,1000000)
print(obstacles)
row = ""

with open("data.txt", "w") as _f:
    _f.write("100\n")
    _f.write("100\n")
    random.seed(time)

    for i in range(0, 100):
        for i in range(0,100):
            if random.randint(0,100) > 90 and obstacles > 0:
                row = row + "-1 "
                obstacles -= 1
            else:
                row = row + "1 "
        _f.write(row+"\n")
        row = ""


