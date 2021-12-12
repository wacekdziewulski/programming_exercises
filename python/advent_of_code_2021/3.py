#!/usr/bin/python3

sums = []
mask = 0b111111111111
for i in range(0, 12):
    sums.append(0)

with open('3.txt', 'r') as data:
    for bits in data:
        bits=bits.rstrip()
        i = 0
        for bit in bits:
            if bit == '0':
                sums[i] -= 1
            else:
                sums[i] += 1
            i += 1

gamma_string = ''.join(list(map(lambda x: '1' if x > 0 else '0', sums)))
gamma = int(gamma_string, 2)
epsilon = (~gamma) & mask
epsilon_string = bin(epsilon)
print(f"gamma string: {gamma_string}, epsilon string {epsilon_string}")
print(f"gamma: {gamma}, epsilon: {epsilon}, mult: {gamma*epsilon}")
