#!/usr/bin/python3

from sys import stdin

DEBUG = True

class Position:
    def __init__(self):
        self.x = 0
        self.y = 0

    def get(self):
        return (self.x, self.y)
    
    def modify(self, direction, distance):
        if direction == 'N':
            self.y -= distance
        elif direction == 'S':
            self.y += distance
        elif direction == 'W':
            self.x -= distance
        elif direction == 'E':
            self.x += distance

    def __str__(self):
        return f"x: {self.x}, y: {self.y}"

class Orientation:
    def __init__(self, initial):
        self.DIRECTION_ORDER = ['N', 'E', 'S', 'W']
        self.facing = initial

    def rotate(self, degrees):
        self.facing = self.DIRECTION_ORDER[(self.DIRECTION_ORDER.index(self.facing) + int(degrees / 90)) % len(self.DIRECTION_ORDER)]

    def set(self, facing):
        self.facing = facing

    def get(self):
        return self.facing

class Ship:
    def __init__(self):
        self.orientation = Orientation('E')
        self.position = Position()

    def move(self, direction, value):
        if DEBUG:
            print(f"Moving '{direction}' by '{value}'")
        if direction == 'R':
            self.orientation.rotate(value)
        elif direction == 'L':
            self.orientation.rotate(-value)
        elif direction == 'F':
            self.position.modify(self.orientation.get(), value)
        else:
            self.position.modify(direction, value)

    def totalDistance(self):
        position = self.position.get()
        return abs(position[0]) + abs(position[1])

    def __str__(self):
        return f"Ship: orientation: {self.orientation.get()}, position: {self.position}"

ship = Ship()
for line in stdin:
    line = line.rstrip()
    ship.move(line[0], int(line[1:]))
    print(ship)

print("manhattan distance: " + str(ship.totalDistance()))
