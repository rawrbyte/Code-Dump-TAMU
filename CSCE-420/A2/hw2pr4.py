# Raymond Zhu
# 923008555
# CSCE 420
# Due: March 5, 2018
# hw2pr4.py

import sys
import itertools

def createTruthTable(size):
    #https://stackoverflow.com/questions/6336424/python-build-a-dynamic-growing-truth-table     
    return list(itertools.product([False, True], repeat=size))
    
def interpret(_clause, _symbols, _truthVal):
    boolVal = False
    # matches each row with the symbols to a dictionary
    letterValues = dict(zip(_symbols, _truthVal))
    _clause = [x.strip() for x in _clause]
    # treating list as a stack
    while(len(_clause) > 0):
        c = _clause.pop(0)
        if c == '-':
            s = _clause.pop(0)
            boolVal = boolVal or (not letterValues[s])
        elif c.isalpha():
            boolVal = boolVal or letterValues[c]     
    return boolVal
    
def evaluate(_symbols, _clauses, _table):
    # evaluates every row in the truth table for the clause formula
    resultList = []
    for x in _table:
       boolVal = True
       for c in _clauses:
            val = interpret(c, _symbols, x)
            boolVal = boolVal and val
       resultList.append(boolVal)
    return resultList
    
conjunctions = sys.stdin.read()
clauses = conjunctions.split()
symbols = []

for c in clauses:
    for s in c:
        if s.isalpha() and s not in symbols:
            symbols.append(s)
            
symbols.sort()
table = createTruthTable(len(symbols))
list = evaluate(symbols, clauses, table)

# prints truth table
header = ""
line = ""
for s in symbols:
   header = header + s + "\t"   
header = header + "Formula"
for _ in range(0, len(symbols)):
    line = line + "--------"
line = line + "-------"
print(line)
print(header)
print(line)
for i in range(0, len(table)):
    row = ""
    for var in table[i]:
        if var == True:
            row = row + "T \t"
        else:
            row = row + "F \t"
    if list[i] == False:
        row = row + "   F"
    else:
        row = row + "   T"
    print(row)
