#!/usr/bin/python3

from sys import stdin

card_public_key = int(stdin.readline().rstrip())
door_public_key = int(stdin.readline().rstrip())
REMAINDER = 20201227

def transform(value, subject):
    value *= subject
    value %= REMAINDER
    return value

def find_loop_size(subject, expected):
    loop_size = 0
    value = 1
    while value != expected:
        value = transform(value, subject)
        loop_size += 1
    return loop_size

def calculate_private_key(subject, loop_size):
    private_key = 1
    loops = 0
    while loops < loop_size:
        private_key = transform(private_key, subject)
        loops += 1
    return private_key

SUBJECT = 7

card_loop_size = find_loop_size(SUBJECT, card_public_key)
print(f"card loop size: {card_loop_size}")
door_loop_size = find_loop_size(SUBJECT, door_public_key)
print(f"door loop size: {door_loop_size}")

card_private_key = calculate_private_key(door_public_key, card_loop_size)
print(f"card private key: {card_private_key}")
door_private_key = calculate_private_key(card_public_key, door_loop_size)
print(f"door private key: {door_private_key}")
