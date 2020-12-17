#!/usr/bin/python3

from sys import stdin

adapters = [0]
jolt_differences = {}

for line in stdin:
    adapters.append(int(line.rstrip()))
    adapters = sorted(adapters)

adapters.append(max(adapters)+3)
print(adapters)
print(len(adapters))

prev = adapters[0]
for i in range(1, len(adapters)):
    difference = adapters[i] - prev
    if difference not in jolt_differences:
        jolt_differences[difference] = 0
    jolt_differences[difference] += 1
    prev = adapters[i]

print(jolt_differences)
print(f"result={jolt_differences[1]*jolt_differences[3]}")
