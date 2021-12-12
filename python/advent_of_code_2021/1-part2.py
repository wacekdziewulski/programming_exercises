#!/usr/bin/python3

FILENAME = '1.txt'

def getStrippedFileLinesList(filename):
    numbers = []
    with open(filename, 'r') as numbers_file:
        for line in numbers_file:
            numbers.append(int(line.rstrip()))
    return numbers

numbers = getStrippedFileLinesList(FILENAME)

increments = 0

for i in range(3,len(numbers)):
    if numbers[i-3]+numbers[i-2]+numbers[i-1] < numbers[i-2]+numbers[i-1]+numbers[i]:
        increments += 1

print(increments)
