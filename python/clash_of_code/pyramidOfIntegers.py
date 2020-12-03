import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

n = int(input())

elements = list(range(1, (n*(n+1))//2+1))

for i in range(1,n+1):
    print(' '.join(map(str, (elements[0:i]))))
    elements = elements[i:]
