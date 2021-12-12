#!/usr/bin/python3

depth = 0
distance = 0

with open('2.txt', 'r') as data:
    for line in data:
        (direction, value) = line.rstrip().split(' ')
        if direction == 'forward':
            distance = distance+int(value)
        elif direction == 'up':
            depth = depth-int(value)
        elif direction == 'down':
            depth = depth+int(value)
print(f'depth: {depth}, distance: {distance}, mult:{depth*distance}')
