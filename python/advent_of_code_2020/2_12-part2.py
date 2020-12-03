#!/usr/bin/python3

import sys
import re

PASSWORD_ENTRY_PATTERN = re.compile('([0-9]+)\-([0-9]+) ([a-z])\: ([a-z]+)')

correct_passwords_count = 0

for line in sys.stdin:
    valid = False
    matcher = PASSWORD_ENTRY_PATTERN.match(line.rstrip())
    first_occurence, second_occurence, letter, password = matcher.group(1, 2, 3, 4)
    if (password[int(first_occurence)-1] == letter) ^ (password[int(second_occurence)-1] == letter):
        correct_passwords_count += 1
        valid = True
    print(f"({first_occurence}-{second_occurence}) of {letter} in {password}: {valid}")

print(correct_passwords_count)
