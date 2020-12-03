#!/usr/bin/python3

# https://devolution.ovh
input = [104, 116, 116, 112, 115, 58, 47, 47, 100, 101, 118, 111, 108, 117, 116, 105, 111, 110, 46, 111, 118, 104]
output = ''.join(map(lambda x : chr(x), input))
print(output)
