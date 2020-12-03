#!/usr/bin/python3

import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

t = input()

def isLetter(character):
    return (ord(character) >= 65 and ord(character) <= 90)

def rot13(character):
    if (isLetter(character)):
        return chr(((ord(character)-65)+13)%26+65)
    else:
        return character;
        
for character in t:
    print(rot13(character))
