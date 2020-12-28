#!/usr/bin/python3

from sys import stdin
from sys import exit

DEBUG = False
PREAMBLE_LENGTH = 25

numbers = []

for line in stdin:
    numbers.append(int(line.rstrip()))

for i in range(len(numbers)-PREAMBLE_LENGTH-1):
    moving_window = sorted(numbers[i:i+PREAMBLE_LENGTH].copy())
    next_value = numbers[i+PREAMBLE_LENGTH]
    value_ok = False
    if DEBUG:
        print(f"mw={moving_window}, nv={next_value}")
    for j in range(PREAMBLE_LENGTH):
        if value_ok or j > next_value:
            break
        for k in range(j+1, PREAMBLE_LENGTH):
            sum_of_two = moving_window[j]+moving_window[k] 
            if sum_of_two == next_value:
                value_ok = True
                break
            elif sum_of_two > next_value:
                break
    if not value_ok:
        print(next_value)
        exit(1)
