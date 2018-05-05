# Raymond Zhu
# 923008555
# CSCE 420
# Due: May 1, 2018
# hw4pr1.py

import sys
import itertools

def createTruthTable(size):
    #https://stackoverflow.com/questions/6336424/python-build-a-dynamic-growing-truth-table     
    return list(itertools.product([0, 0.25, 0.5, 0.75, 1], repeat=size))

def calcResult(_list):
    # calculates fuzzyImplies
    X = _list[0]
    Y = _list[1]
    notY = 1 - Y
    
    return 1 - min(X, notY)

def evaluate(_table):
    # evaluates every row in the truth table for calcResults
    resultList = []
    for x in _table:
        resultList.append(calcResult(x))
    return resultList

table = createTruthTable(2)
result = evaluate(table)

# prints truth table
header = "X\tY\tX => Y"
line = ""
for _ in range(0, 3):
    line = line + "--------"
print(line)
print(header)
print(line)
for i in range(0, len(table)):
    row = str(table[i][0]) + "\t" + str(table[i][1]) + "\t" + str(result[i])
    print(row)