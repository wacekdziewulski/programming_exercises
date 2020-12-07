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
            node.children.append(GraphNode(matcher[0], matcher[1]))
    if DEBUG:
        print(node)
    return node

def findBagByName(name, bag_list):
    for bag in bag_list:
        if bag.name == name:
            return bag
    return None

def findParentsOf(name, bag_list):
    parents = []
    for bag in bag_list:
        for child_bag in bag.children:
            if child_bag.name == name and not bag.name in parents:
                parents.append(bag.name)
    return parents

def findAllParentsOf(name, bag_list):
    all_parents_of_bag = []
    bags_to_find = findParentsOf(name, bag_list)
    new_bags_to_find = []
    while len(bags_to_find) > 0:
        print("------------------------------------")
        print(f"\tall: {len(all_parents_of_bag)} -> {all_parents_of_bag}")
        for bag_name in bags_to_find:
            parents = findParentsOf(bag_name, bag_list)
            for parent in parents:
                if parent not in new_bags_to_find:
                    new_bags_to_find.append(parent)
            if bag_name not in all_parents_of_bag:
                all_parents_of_bag.append(bag_name)
        bags_to_find = new_bags_to_find
        new_bags_to_find = []
        print(f"\tnew bags: {bags_to_find}")
    return all_parents_of_bag

bag_list = []
for line in stdin:
    bag_list.append(parseBagLine(line))

result = findAllParentsOf('shiny gold', bag_list)
print(len(result))
