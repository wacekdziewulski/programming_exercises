#!/usr/bin/python3

FILENAME = '1_12.txt'
EXPECTED_SUM_OF_TWO_NUMBERS = 2020

def getStrippedFileLinesList(filename):
    numbers = []
    with open(filename, 'r') as numbers_file:
        for line in numbers_file:
            numbers.append(int(line.rstrip()))
    return numbers

def removeNonConformantValues(array):
    return list(filter(lambda x: x < EXPECTED_SUM_OF_TWO_NUMBERS, array))

numbers = removeNonConformantValues(getStrippedFileLinesList(FILENAME))

for i in range(len(numbers)-1):
    for j in range(i+1, len(numbers)):
        first = numbers[i]
        second = numbers[j]
        if i != j and first+second == EXPECTED_SUM_OF_TWO_NUMBERS:
            multiplied = first * second
            print(f"{first},{second} => {multiplied}")
