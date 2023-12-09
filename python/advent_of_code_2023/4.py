#!/usr/bin/python3

FILENAME = '4.txt'

parse_numbers = lambda number_string: list(map(lambda x: int(x), filter(lambda y: y != '', number_string.split(' '))))

def parse_game(line):
    points = 0
    (card, results) = line.split(": ")
    (winning_numbers, all_numbers) = map(parse_numbers, results.split(' | '))
    winning_numbers.sort()
    all_numbers.sort()
    for winning_number in winning_numbers:
        if winning_number in all_numbers:
            if points == 0:
                points = 1
            else:
                points *= 2
    return points

answer = 0
with open(FILENAME, 'r') as file:
    for line in file:
        line = line.rstrip(' ')
        answer += parse_game(line.rstrip())
print(answer)
