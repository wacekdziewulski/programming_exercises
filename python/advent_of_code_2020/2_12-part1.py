#!/usr/bin/python3

import sys
import re

PASSWORD_ENTRY_PATTERN = re.compile('([0-9]+)\-([0-9]+) ([a-z])\: ([a-z]+)')

def get_letter_occurences_dict(password):
    password_chars = {}
    for letter in password:
        password_chars[letter] = password_chars.get(letter, 0) + 1
    return password_chars

correct_passwords_count = 0

for line in sys.stdin:
    matcher = PASSWORD_ENTRY_PATTERN.match(line.rstrip())
    min_occurences, max_occurences, letter, password = matcher.group(1, 2, 3, 4)
    password_char_occurences = get_letter_occurences_dict(password)
    print(f"({min_occurences}-{max_occurences}) of {letter} in {password}, hash: {password_char_occurences}")
    if letter in password_char_occurences.keys() and password_char_occurences[letter] in range(int(min_occurences), int(max_occurences)+1):
        correct_passwords_count += 1

print(correct_passwords_count)
