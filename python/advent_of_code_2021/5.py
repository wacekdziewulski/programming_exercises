#!/usr/bin/python3

DEBUG = True

class Board:
    def __init__(self, size_x, size_y):
        self.size = [size_x, size_y]
        self.board = [[0]*(self.size[0])]*(self.size[1])

    def mark(self, v1, v2):
        for i in range(v1[0], v2[0]):
            for j in range(v1[1], v2[1]):
                self.board[i][j] += 1

    def dump(self):
        print("--------------------")
        for line in self.board:
            print(line)

coordinates = []
with open('5-basic.txt', 'r') as data:
    for line in data:
        (beg, end) = map(lambda v: [int(v[0]), int(v[1])], map(lambda x: x.split(','), line.rstrip().split(' -> ')))
        coordinates.append([beg, end])
    max_size_x = max(coordinates, key=lambda coord: max([coord[0][0], coord[1][0]]))
    max_size_y = max(coordinates, key=lambda coord: max([coord[0][1], coord[1][1]]))
    board = Board(max(max_size_x[0][0], max_size_x[1][0]), max(max_size_y[0][1], max_size_x[1][1]))

for coordinate in coordinates:
    board.mark(coordinate[0], coordinate[1])
    board.dump()
