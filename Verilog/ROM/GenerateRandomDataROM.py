import random

DEPTH = 1024
WIDTH = 8

with open("rom.mem", "w") as f:
    for i in range(DEPTH):
        f.write(f"{random.randint(0, 2**WIDTH-1):02X}\n")

print("rom.mem created")