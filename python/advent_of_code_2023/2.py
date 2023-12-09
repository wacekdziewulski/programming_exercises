#!/usr/bin/python3

import re

LIMITS = {
    "red": 12,
    "green": 13,
    "blue": 14,
}
FILENAME = '2.txt'

def parse_game(line):
    draw_results = [] 
    (game, results) = line.split(": ")
    game_no = int(game.split(' ')[1])
    draws = results.split('; ')
    for draw in draws:
        draw_result = {}
        for color_and_val in draw.split(', '):
            (number, color) = color_and_val.split(' ')
            draw_result[color] = int(number)
        draw_results.append(draw_result)
    return {'id': game_no, 'results': draw_results}

def analyze_game(game):
    for draw_result in game['results']:
        for (color, value) in draw_result.items():
            if LIMITS[color] < value:
                print(f"{game['id']}: {color}:{value} is > limit: {LIMITS[color]}")
                return 0
    return game['id']

solution = 0
with open(FILENAME, 'r') as file:
    for line in file:
        game = parse_game(line.rstrip())
        solution += analyze_game(game)
print(solution)
