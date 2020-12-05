#!/usr/bin/python3

from sys import stdin

plane = []
for i in range(0, 128):
    plane.append([])
    for j in range(0, 8):
        plane[i].append(False)

for line in stdin:
    row = 0
    column = 0
    line = line.rstrip()
    for letter in line:
        if letter in ['F', 'B']:
            row <<= 1
            if letter == 'B':
                row += 1
        if letter in ['L', 'R']:
            column <<= 1
            if letter == 'R':
                column += 1

    print(f"{line} => r:{row} c:{column}")
    plane[row][column] = True

for row in range(1, 127):
    for column in range(0, 8):
        if plane[row][column] == False and plane[row-1][column] == True and plane[row+1][column] == True:
            seat_id = 8 * row + column
            print(f"Free => r:{row} c:{column} s_id:{seat_id}")
