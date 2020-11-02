__author__ = 'Nickolas'

import constraints

debug = True

file = open("data.txt")

raw_data = file.readlines()

data = []

for line in raw_data:
    line = line.strip("\n")
    data.append(line.split(" "))

if debug:
    for operation in data:
        print("\nTime: {}\nOperation: {}\nAddress: {}".format(
            operation[0],
            constraints.operations[int(operation[1])],
            operation[2]))
