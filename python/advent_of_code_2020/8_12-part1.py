#!/usr/bin/python3

from sys import stdin

DEBUG = True
acc = 0
eip = 0
instructions = []

class Instruction:
    def __init__(self, instruction, value):
        self.instruction = instruction
        self.value = value
        self.executions = 0

    def execute(self, instruction_pointer, accumulator):
        if DEBUG:
            print(f"Executing: {self.instruction} with value: {self.value} under instruction_pointer: {instruction_pointer}")
        if self.executions > 0:
            print(f"Found bootloop with accumulator value: {accumulator} on instruction: {self.instruction} with instruction pointer: {instruction_pointer}")
            return (-1, accumulator)

        if self.instruction == 'nop':
            instruction_pointer += 1
        elif self.instruction == 'acc':
            accumulator += self.value
            instruction_pointer += 1
        elif self.instruction == 'jmp':
            instruction_pointer += self.value
        self.executions += 1
        
        return (instruction_pointer, accumulator)

    def __str__(self):
        return f"{self.instruction}:{self.value}"

for line in stdin:
    (instruction, value) = line.rstrip().split(" ")
    if value[0] == '+':
        value = value[1:]
    instructions.append(Instruction(instruction, int(value)))

while eip >= 0:
    (eip, acc) = instructions[eip].execute(eip, acc)
