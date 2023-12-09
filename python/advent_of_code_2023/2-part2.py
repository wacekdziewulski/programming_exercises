#!/usr/bin/python3

from functools import reduce

FILENAME = '2.txt'

def parse_game(line):
    draw_results = [] 
    (game, results) = line.split(": ")
    game_no = int(game.split(' ')[1])
    draws = results.split('; ')
    draw_result = { 'blue': 1, 'red': 1, 'green': 1 }
    for draw in draws:
        for color_and_val in draw.split(', '):
            (number, color) = color_and_val.split(' ')
            draw_result[color] = max(draw_result[color], int(number))
    print(draw_result)
    return {'id': game_no, 'result': draw_result}

def analyze_game(game):
    return reduce(lambda x, y: x * y, game['result'].values())

solution = 0
with open(FILENAME, 'r') as file:
    for line in file:
        game = parse_game(line.rstrip())
        solution += analyze_game(game)
print(solution)
