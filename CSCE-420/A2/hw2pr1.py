# Raymond Zhu
# 923008555
# CSCE 420
# Due: March 5, 2018
# hw2pr1.py

import sys
import itertools

allDiff = set()
letterList = {}
solutions = []

def AllDiff(x, y, z):
    global allDiff
	# since a set contains only unique elements, 
	# a set of concatenated strings will only have unique characters
    allDiff = set(x + y + z)

def check(x, y, z):
    global letterList
    _first = ""
    _second = ""
    _solution = ""
	# these for loops are used to append the values and then a simple int() call 
	# can convert them into integers for comparison
    for index in range(0, len(x)):
        _first = _first + str(letterList[x[index]])
    for index in range(0, len(y)):
        _second = _second + str(letterList[y[index]])
    for index in range(0, len(z)):
        _solution = _solution + str(letterList[z[index]])

    if _first[0] == '0' or _second[0] == '0' or _solution[0] == '0':
        return False
    elif int(_first)+int(_second) == int(_solution):
        solutions.append(_first + " + " + _second + " = " + _solution)
        return True
    return False
    
first = input("Argument 1: ")
second = input("Argument 2: ")
solution = input("Sum: ")

AllDiff(first, second, solution)

# a permutation of all possible combinations.
# for loop won't go through all permutations since some
# heuristics have been applied to skip unecessary permutations
for x in itertools.permutations(range(10), len(allDiff)):
    letterList = dict(zip(allDiff, x))
    if len(solution) > len(first) and len(solution) > len(second):
        if letterList[solution[0]] != 1:
			# if the solution is longer than both words, then obviously the first
			# character of solution[0] should be 1
            continue
        elif first[0] == second[0]:
            if letterList[solution[1]] not in range(5,10):
				# if both are equal, they need to be >= 5 to get a remainder 1
                continue
        elif len(first) > len(second):
			# needs to be 9 to ensure it can pass a remainder 1 after getting a remainder
            if letterList[first[0]] != 9:
                continue
        elif len(first) < len(second):
			# needs to be 9 to ensure it can pass a remainder 1 after getting a remainder
            if letterList[second[0]] != 9:
                continue
    elif len(solution) == len(first) or len(solution) == len(second):
        if first[0] == second[0]:
            if letterList[solution[0]] not in range(0,5):
				# if the solution is the same length as both words
				# then both words at [0] should be <5
                continue
    if check(first, second, solution):
        break

if not solutions:
    print("No solutions")
else:
    for var in solutions:
        print(var)