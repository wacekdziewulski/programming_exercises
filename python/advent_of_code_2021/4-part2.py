#!/usr/bin/python3

DEBUG = True

class Board:
    def __init__(self, lines):
        self.is_bingo = False
        self.board = []
        self.size = 5
        for row in lines:
            numbers = row.rstrip().split()
            self.board.append(list(map(lambda x: [int(x),0], numbers)))

    def bingo(self):
        self.is_bingo = True

    def mark(self, search_val):
        for i in range(self.size):
            for j in range(self.size):
                if self.board[i][j][0] == search_val:
                    self.board[i][j][1] = 1
                    return True
        return False

    def dump(self):
        print("--------------------")
        for line in self.board:
            print(line)

    def has_bingo(self):
        if self.is_bingo:
            return True
        if self._bingo_on_diagonals():
            return True
        for i in range(self.size):
            if self._bingo_on_line(i, 0, 0, 1):
                return True
            if self._bingo_on_line(0, i, 1, 0):
                return True

    def _bingo_on_diagonals(self):
        return self._bingo_on_line(0, 0, 1, 1) or self._bingo_on_line(0, 4, 1,-1)

    def _bingo_on_line(self, initial_x, initial_y, vect_x, vect_y):
        total = 0
        for i in range(self.size):
            total += self.board[initial_x+i*vect_x][initial_y+i*vect_y][1]
        return total == self.size

    def sum_of_unmarked_numbers(self):
        total = 0
        for i in range(self.size):
            for j in range(self.size):
                if self.board[i][j][1] == 0:
                    total += self.board[i][j][0]
        return total

numbers = []
boards = []

with open('4.txt', 'r') as data:
    lines = data.readlines()
    numbers = lines[0].rstrip().split(',')
    for i in range(0, int((len(lines)-2)/6)):
        boards.append(Board(lines[i*6+2:i*6+7]))

last_board = 0
for number in numbers:
    for board in boards:
        if board.has_bingo():
            continue
        board.mark(int(number))
        if board.has_bingo():
            print(f'Bingo! Board: {number}')
            board.bingo()
            last_board = board
    all_boards_have_bingo = True
    for board in boards:
        if not board.has_bingo():
            all_boards_have_bingo = False
            break
    if all_boards_have_bingo:
        print(f'Final score: {last_board.sum_of_unmarked_numbers()*int(number)}')
        exit(0)
