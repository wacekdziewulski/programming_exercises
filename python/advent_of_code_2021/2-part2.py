#!/usr/bin/python3

depth = 0
distance = 0
aim = 0

with open('2.txt', 'r') as data:
    for line in data:
        (direction, value) = line.rstrip().split(' ')
        if direction == 'forward':
            distance = distance+int(value)
            depth = depth+(int(value)*aim)
        elif direction == 'up':
            aim = aim-int(value)
        elif direction == 'down':
            aim = aim+int(value)
print(f'depth: {depth}, distance: {distance}, mult:{depth*distance}')
