#!/usr/bin/python3

def bit_occurences(bit_index, bit_lines):
    occurences = [0,0]
    for bit_line in bit_lines:
        occurences[int(bit_line[bit_index])] += 1
    return occurences

def max_occurences(occurences):
    return '0' if occurences[0] > occurences[1] else '1'

def min_occurences(occurences):
    return '0' if occurences[0] <= occurences[1] else '1'

co2_scrubber_lines = []
oxygen_lines = []

with open('3.txt', 'r') as data:
    for line in data:
        oxygen_lines.append(line.rstrip())
        co2_scrubber_lines.append(line.rstrip())

for bit_index in range(0, 12):
    oxygen_bit = max_occurences(bit_occurences(bit_index, oxygen_lines))
    co2_scrubber_bit = min_occurences(bit_occurences(bit_index, co2_scrubber_lines))
    if len(oxygen_lines) != 1:
        oxygen_lines = list(filter(lambda line: line[bit_index] == oxygen_bit, oxygen_lines))
    if len(co2_scrubber_lines) != 1:
        co2_scrubber_lines = list(filter(lambda line: line[bit_index] == co2_scrubber_bit, co2_scrubber_lines))
    print("----------------------")
    print(f"index: {bit_index}")
    print(f'oxygen_bit: {oxygen_bit}, lines left: {oxygen_lines}')
    print(f'co2_bit: {co2_scrubber_bit}, lines left: {co2_scrubber_lines}')

oxygen = int(oxygen_lines[0],2)
co2 = int(co2_scrubber_lines[0], 2)
print(f"oxygen: {oxygen}, co2 scrubber {co2}, mult: {oxygen*co2}")
