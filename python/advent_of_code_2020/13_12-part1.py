#!/usr/bin/python3

from sys import stdin

timestamp = int(stdin.readline())
buses = stdin.readline().rstrip().split(',')
buses = list(filter(lambda x : x != 'x', buses))
print(f"buses: {buses}")
waiting_times = list(map(lambda x : int(x) - (timestamp % int(x)), buses))
print(f"waiting_times: {waiting_times}")
min_waiting_time = min(waiting_times)
bus_id = buses[waiting_times.index(min_waiting_time)]
print(f"result: {int(bus_id)*min_waiting_time}")
