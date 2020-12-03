#!/usr/bin/python3

from sys import stdin

toboggan_map = []
x = 0
y = 0
trees = 0

for line in stdin:
    toboggan_map.append(line.rstrip())
map_length = len(toboggan_map[0])
print(map_length)

while y < len(toboggan_map):
    if (toboggan_map[y][x] == '#'):
        trees += 1
    print(f"{x},{y} => {toboggan_map[y][x]}")
    x = (x + 3) % map_length
    y += 1
print(trees)
