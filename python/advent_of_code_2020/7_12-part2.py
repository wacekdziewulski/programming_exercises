#!/usr/bin/python3

import re
from sys import stdin

DEBUG=True
BASE_REGEX = re.compile('([a-z]+ [a-z]+) bags')
CHILD_REGEX = re.compile('([0-9]+) ([a-z]+ [a-z]+) bag[s]?')

class GraphNode:
    def __init__(self, number, name):
        self.number = number 
        self.name = name
        self.parent = None
        self.children = []
    def __str__(self):
        output = ""
        if self.number != 0:
            output += f"{self.number} of {self.name}"
        else:
            output += f"{self.name}"
            for child in self.children:
                output += f"\n\t{child}"
        return output

def parseBagLine(line):
    line = line.rstrip()
    (bag_type, bag_contents) = line.split(' contain ')
    bag = BASE_REGEX.match(bag_type).group(1)
    node = GraphNode(0, bag)
    if bag_contents != 'no other bags.':
        for matcher in CHILD_REGEX.findall(bag_contents):
            node.children.append(GraphNode(int(matcher[0]), matcher[1]))
    if DEBUG:
        print(node)
    return node

def findBagByName(name, bag_list):
    for bag in bag_list:
        if bag.name == name:
            return bag
    return None

def getNumberOfBags(bag_name, bag_list):
    result = 0
    bag = findBagByName(bag_name, bag_list)
    if len(bag.children) == 0:
        return 0
    else:
        for child in bag.children:
            bags_number = child.number * getNumberOfBags(child.name, bag_list) + child.number
            result += bags_number
            print(f"bags in {bag_name}: {result}")
        return result

bag_list = []
for line in stdin:
    bag_list.append(parseBagLine(line))

print(getNumberOfBags('shiny gold', bag_list))
