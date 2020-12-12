#!/usr/bin/python3

from sys import stdin

Debug = True

class Seat:
    def __init__(self, value):
        self._current = value
        self._next = ''
        self._hasChanged = False

    def get(self):
        return self._current

    def isEmpty(self):
        return self._current == 'L'
    
    def isFloor(self):
        return self._current == '.'
    
    def isOccupied(self):
        return self._current == '#'
    
    def setOccupied(self):
        self._next = '#'

    def setEmpty(self):
        self._next = 'L'

    def flip(self):
        # retain value
        if self._current == '.':
            return
        if self._next == '':
            self._next = self._current
        self._hasChanged = (self._current != self._next)
        self._current = self._next
        self._next = ''

    def isChanged(self):
        return self._hasChanged

    def __str__(self):
        return self._current

class GameOfLife:
    def __init__(self):
        self.board = []

    def initRow(self, row):
        gameRow = []
        for letter in row:
            gameRow.append(Seat(letter))
        self.board.append(gameRow)

    def _getFirstSeatOnVector(self, row, column, vector):
        current = [row + vector[0], column + vector[1]]
        while current[0] >= 0 and current[0] < len(self.board) and current[1] >= 0 and current[1] < len(self.board[row]):
            seat = self.board[current[0]][current[1]]
            if not seat.isFloor():
                return seat
            current[0] += vector[0]
            current[1] += vector[1]

        if current[0]-vector[0] == row and current[1]-vector[1] == column:
            return None
        else:
            return self.board[current[0]-vector[0]][current[1]-vector[1]]

    def _getNeighbours(self, row, column):
        neighbours = []
        for i in range(-1, 2, 1):
            for j in range(-1, 2, 1):
                if i == 0 and j == 0:
                    continue
                seat = self._getFirstSeatOnVector(row, column, [i, j])
                if seat:
                    neighbours.append(seat)
        return neighbours

    def inspect(self, row, column):
        print()
        print(f"seat[{row}][{column}]: {self.board[row][column]}", end=' | ')
        print(f"neighbours: ", end='')
        for neighbour in self._getNeighbours(row, column):
            print(neighbour, end='')
        print()

    def step(self):
        changedSeats = 0
        for row in range(0, len(self.board)):
            for column in range(0, len(self.board[0])):
                neighbours = self._getNeighbours(row, column)
                currentSeat = self.board[row][column]
                if self.board[row][column].isEmpty():
                    self._tryEmptyToOccupied(currentSeat, neighbours)
                elif self.board[row][column].isOccupied():
                    self._tryOccupiedToEmpty(currentSeat, neighbours)

        for row in self.board:
            for seat in row:
                seat.flip()
                if seat.isChanged():
                    changedSeats += 1
        return changedSeats

    def getOccupiedSeats(self):
        occupiedSeats = 0
        for row in self.board:
            for seat in row:
                if seat.isOccupied():
                    occupiedSeats += 1
        return occupiedSeats

    def _tryEmptyToOccupied(self, seat, neighbours):
        for neighbour in neighbours:
            if neighbour.isOccupied() == True:
                return
        seat.setOccupied()
    
    def _tryOccupiedToEmpty(self, seat, neighbours):
        occupiedNeighbours = 0
        for neighbour in neighbours:
            if neighbour.isOccupied() == True:
                occupiedNeighbours += 1
        if occupiedNeighbours >= 5:
            seat.setEmpty()

    def __str__(self):
        output = ""
        row_no = 0
        for row in self.board:
            output += str(row_no) + ": "
            for seat in row:
                output += seat.__str__()
            output += '\n'
            row_no += 1
        return output

game = GameOfLife()
for line in stdin:
    game.initRow(line.rstrip())

print("initial:")
print(game)
while game.step() > 0:
    print(game)

print("occupied seats: " + str(game.getOccupiedSeats()))
