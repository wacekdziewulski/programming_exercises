#!/usr/bin/python3

import re

FILENAME = '1.txt'

number_map = {
    "one": 1,
    "two": 2,
    "three": 3,
    "four": 4,
    "five": 5,
    "six": 6,
    "seven": 7,
    "eight": 8,
    "nine": 9
}

def value_from_number_map(number):
    global number_map
    for key in number_map.keys():
        if number.startswith(key):
            return number_map[key]
    return None

def parse(number):
    number_list = []
    for i in range(0, len(number)):
        if number[i].isdigit():
            number_list.append(int(number[i]))
            continue
        digit = value_from_number_map(number[i:])
        if digit:
            number_list.append(digit)
    return number_list

result = 0
number = []
with open(FILENAME, 'r') as file:
    for line in file:
        line = line.rstrip()
        number_list = parse(line)
        calibration_value = int(str(number_list[0]) + str(number_list[-1]))
        print(f"{line} -> {number_list} -> {calibration_value}")
        result += calibration_value
print(result)
