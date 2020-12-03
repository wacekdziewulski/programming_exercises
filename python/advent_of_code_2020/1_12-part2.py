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

for i in range(len(numbers)-2):
    for j in range(i+1, len(numbers)-1):
        for k in range(j+1, len(numbers)-2):
            first = numbers[i]
            second = numbers[j]
            third = numbers[k]
            if i != j != k and first+second+third == EXPECTED_SUM_OF_TWO_NUMBERS:
                multiplied = first * second * third
                print(f"{first},{second},{third} => {multiplied}")
