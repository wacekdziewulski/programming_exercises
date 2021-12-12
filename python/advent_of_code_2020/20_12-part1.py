#!/usr/bin/python3

from sys import stdin

class Tile:
    SIZE = 10
    DATA = [[0 for i in range(SIZE)] for j in range(SIZE)]

    def __init__(self, number, data_lines):
        self._number = number
        self._data = self._init_data(data_lines)

    def _init_data(self, data_lines):
        for line in data_lines:
          
    def __str__(self):
        print(f"Tile {self._number}:")
        for row in self.data():
            for char in row:
                print("".join(list(map(lambda x : '#' if x == 1 else '.'))))

tiles = {}

for line in stdin:
    line = line.rstrip()
    tile_number = 0
    if line.startswith('Tile'):
        tile_number = line.split()[1].rstrip(':')
