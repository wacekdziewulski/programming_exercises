#!/usr/bin/python3

from sys import stdin

DEBUG = False
acc = 0
eip = 0
instructions = []

def reset():
    global instructions
    global eip
    global acc
    for instruction in instructions:
        instruction.executions = 0
    eip = 0
    acc = 0

class Instruction:
    def __init__(self, instruction, value):
        self.instruction = instruction
        self.value = value
        self.executions = 0

    def exchangeJmpNop(self):
        if self.instruction == 'nop':
            self.instruction = 'jmp'
            return True
        elif self.instruction == 'jmp':
            self.instruction = 'nop'
            return True
        else: # acc should not be modified
            return False

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

for instruction in instructions:
    if instruction.exchangeJmpNop() == True:
        while eip != -1 and eip != len(instructions):
            (eip, acc) = instructions[eip].execute(eip, acc)
        if eip == len(instructions):
            print(f"WIN: Fixed the solution by replacing instruction: {instruction.instruction} with value: {instruction.value}. Quitting.")
            print(f"Accumulator: {acc}")
            break
        instruction.exchangeJmpNop() # restore the previous instruction value
        reset()
