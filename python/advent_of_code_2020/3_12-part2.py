#!/usr/bin/python3

from sys import stdin

toboggan_map = []
movement_vectors = [[1,1], [3,1], [5,1], [7,1], [1,2]]

global map_length

def count_trees_on_movement(vector_right, vector_down):
    x = 0
    y = 0
    trees = 0
    while y < len(toboggan_map):
        if (toboggan_map[y][x] == '#'):
            trees += 1
        #print(f"{x},{y} => {toboggan_map[y][x]}")
        x = (x + vector_right) % map_length
        y += vector_down 
    print(f"{trees} trees on {vector_right}-> and {vector_down}V")
    return trees

for line in stdin:
    toboggan_map.append(line.rstrip())
map_length = len(toboggan_map[0])

result = 1
for movement_vector in movement_vectors:
    result *= count_trees_on_movement(movement_vector[0], movement_vector[1])
print(result)
