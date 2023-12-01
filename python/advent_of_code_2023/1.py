#!/usr/bin/python3

import re

FILENAME = '1.txt'

result = 0
number = []
with open(FILENAME, 'r') as file:
    for line in file:
        line = line.rstrip()
        number = "".join(re.findall('\d+', line))
        calibration_value = int(number[0] + number[-1])
        result += calibration_value
print(result)
