#!/usr/bin/python3

from sys import stdin

max_id = 0

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
    seat_id = 8 * row + column
    if seat_id > max_id:
        max_id = seat_id

    print(f"{line} => r:{row} c:{column} s_id: {seat_id}")
print(f"max id = {max_id}")
