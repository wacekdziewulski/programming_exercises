#!/usr/bin/python3

from sys import stdin

DEBUG = True

class Position:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def get(self):
        return (self.x, self.y)

    def move(self, x, y):
        self.x += x
        self.y += y
    
    def follow(self, destination, times):
        for i in range(times):
            self.x += destination.x
            self.y += destination.y

    def __str__(self):
        return f"x: {self.x}, y: {self.y}"

class Waypoint:
    def __init__(self, x, y):
        self.position = Position(x, y)

    def move(self, direction, value):
        if direction == 'N':
            self.position.move(0, -value)
        elif direction == 'S':
            self.position.move(0, value)
        elif direction == 'E':
            self.position.move(value, 0)
        elif direction == 'W':
            self.position.move(-value, 0)

    def rotate(self, degrees):
        if degrees < 0:
            degrees += 360
        while degrees > 0:
            # (1, -10) -> (10, 1) -> 
            tmp = self.position.x
            self.position.x = -self.position.y
            self.position.y = tmp
            degrees -= 90

    def __str__(self):
        return f"waypoint: {self.position}"

class Ship:
    def __init__(self):
        self.position = Position(0, 0)
        self.waypoint = Waypoint(10, -1)

    def move(self, direction, value):
        if DEBUG:
            print(f"Moving '{direction}' by '{value}'")
        if direction == 'R':
            self.waypoint.rotate(value)
        elif direction == 'L':
            self.waypoint.rotate(-value)
        elif direction == 'F':
            self.position.follow(self.waypoint.position, value)
        else:
            self.waypoint.move(direction, value)

    def totalDistance(self):
        position = self.position.get()
        return abs(position[0]) + abs(position[1])

    def __str__(self):
        return f"Ship: waypoint: {self.waypoint.position}, position: {self.position}"

ship = Ship()
for line in stdin:
    line = line.rstrip()
    ship.move(line[0], int(line[1:]))
    print(ship)

print("manhattan distance: " + str(ship.totalDistance()))
