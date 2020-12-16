#!/usr/bin/python3

from sys import stdin

stdin.readline()
buses = stdin.readline().rstrip().split(',')
base = int(buses[0])
buses_with_index = []
for i in range(1, len(buses)):
    if (buses[i] == 'x'):
        continue
    buses_with_index.append([i, int(buses[i])])
buses_with_index = sorted(buses_with_index, key = lambda x : x[1], reverse=True)
print(f"base: {base}, buses_with_index: {buses_with_index}")

sought = base
i = 0
while True:
    i += 1
    found = True
    sought += base
    for bus in buses_with_index:
        if bus[1] - (sought % bus[1]) != bus[0]:
            found = False
            break
    if i % 1000000 == 0:
        print(f"Searching: {sought}")
    if found:
        print(f"Found! : {sought}")
        break
