#!/usr/bin/python3

from sys import stdin

max_id = 0

answers = {}
total_answers = 0

for line in stdin:
    if line != '\n':
        line = line.rstrip()
        for letter in line:
            answers[letter] = True
    else:
        print(answers.keys())
        total_answers += len(answers.keys())
        print(f"answers so far: {total_answers}")
        answers = {}

print(total_answers)
