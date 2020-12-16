#!/usr/bin/python3

from sys import stdin
import re

DEBUG = True
MEM_SIZE = 65536
MASK_LENGTH = 36
MEM_PATTERN = re.compile('mem\[(\d+)\] = (\d+)')

mem = [0 for i in range(MEM_SIZE)]
mask = ['X' for i in range(MASK_LENGTH)]

for line in stdin:
    line = line.rstrip()
    if line.startswith("mask"):
        mask = list(line[7:])
        if DEBUG:
            print(f"New mask: {mask}")
    elif line.startswith("mem"):
        matcher = MEM_PATTERN.match(line)
        address = int(matcher.group(1))
        value = list(('{:0>'+str(MASK_LENGTH)+'}').format(bin(int(matcher.group(2)))[2:]))
        if DEBUG:
            print(f"Mem[{address}] = {value} (before)")
        for i in range(MASK_LENGTH):
            if mask[i] != 'X':
                value[i] = mask[i]
        if DEBUG:
            print(f"Mem[{address}] = {value} (after)")
        mem[address] = int("".join(value), 2)
        if DEBUG:
            print(f"Mem[{address}] = {mem[address]} (int)")

print(sum(mem))
