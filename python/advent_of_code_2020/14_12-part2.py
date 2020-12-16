#!/usr/bin/python3

from sys import stdin
import re

DEBUG = True
MASK_LENGTH = 36
MEM_PATTERN = re.compile('mem\[(\d+)\] = (\d+)')

mem = {}
mask = ['X' for i in range(MASK_LENGTH)]

def allFloatingAddresses(address, output):
    isAbsolute = True
    for i in range(MASK_LENGTH):
        if address[i] == 'X':
            isAbsolute = False
            for bit in ['0', '1']:
                new_address = address.copy()
                new_address[i] = bit
                allFloatingAddresses(new_address, output)
            return
    if isAbsolute:
        if DEBUG:
            print(f"Absolute address: {address}")
        output.append(int("".join(address), 2))

for line in stdin:
    line = line.rstrip()
    if line.startswith("mask"):
        mask = list(line[7:])
        if DEBUG:
            print(f"New mask: {mask}")
    elif line.startswith("mem"):
        matcher = MEM_PATTERN.match(line)
        address = list(('{:0>'+str(MASK_LENGTH)+'}').format(bin(int(matcher.group(1)))[2:]))
        value = int(matcher.group(2))
        if DEBUG:
            print(f"Mem[{address}] = {value} (before)")
        for i in range(MASK_LENGTH):
            if mask[i] != '0':
                address[i] = mask[i]
        if DEBUG:
            print(f"Mem[{address}] = {value} (after)")
        
        floating_addresses = []
        allFloatingAddresses(address, floating_addresses)
        for floating_address in floating_addresses:
            mem[floating_address] = value
            if DEBUG:
                print(f"Mem[{floating_address}] = {mem[floating_address]} (int)")

total = 0
for addr in mem.keys():
    total += mem[addr]

print(total)
