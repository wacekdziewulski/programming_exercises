#!/usr/bin/python3

from sys import stdin

max_id = 0

answers = {}
total_answers = 0
no_of_people = 0

for line in stdin:
    if line != '\n':
        line = line.rstrip()
        for letter in line:
            if letter in answers:
                answers[letter] += 1
            else:
                answers[letter] = 1
        no_of_people += 1
    else:
        print(f"people: {no_of_people} | answers: {answers}")
        for answer in answers.keys():
            if answers[answer] == no_of_people:
                total_answers += 1
        print(f"answers so far: {total_answers}")
        no_of_people = 0
        answers = {}

print(total_answers)
