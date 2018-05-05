# Raymond Zhu
# 923008555
# CSCE 420
# Due: May 1, 2018
# hw4pr2.py

import sys

# a list of all the inputs made by the user [[a, b], [b, c], ... ]
listOfModulePairs = []
# a dictionary containing the degree of each module in the topological graph {'main':0}
degOfModules = {}
# a dictionary containing each module's dependencies as a list {'main': [a, b, c]}
moduleRelations = {}
isCycle = False

def detectCycles(x, iteration, _moduleRelations):
    # checks to see if a link loops back to itself
    # x initial node that is checked against
    # iteration is to indicate the depth of the loop (used for recursion later)
    for i in _moduleRelations[iteration]:
        try:
            if x == i:
                return True
            else:
                if detectCycles(x, i, _moduleRelations):
                    return True
                else:
                    return False
        except RecursionError:
            # sometimes checking against a node goes into an infinite loop
            # this just takes care of it, since its not a cycle
            return False
    return False
            
# take in user input and convert input into a nested list of pairs
modules = sys.stdin.read()
moduleList = modules.split('\n')
for x in moduleList:
    listOfModulePairs.append(x.split())

for x in listOfModulePairs:
    if not x:
        # not x means the list is empty; skips empty lists
        # after pressing enter on last input, before ctrl-D, it creates an empty list in listOfModulePairs
        continue
    if x[0] not in moduleRelations:
        # initializes key
        moduleRelations[x[0]] = []
    if x[1] not in moduleRelations:
        # initializes key
        moduleRelations[x[1]] = []
    if x[0] not in degOfModules:
        # initializes key
        degOfModules[x[0]] = 0
    if x[1] not in degOfModules:
        # initializes key
        degOfModules[x[1]] = 0

    # updates degree and dependencies based on pairs in listOfModulePairs
    degOfModules[x[1]] += 1
    moduleRelations[x[0]].append(x[1])   

for x in moduleRelations:
    # checks for a cycle before even attempting to complete a topological sort
    if detectCycles(x, x, moduleRelations):
        isCycle = True

if isCycle:
    print("Cycle exists, no total order")

while isCycle is False:
    for x in degOfModules:
        # chooses the next key where its degree is 0
        if degOfModules[x] == 0:
            print(x)
            # for each dependency of x, subtract its degree by 1
            for i in moduleRelations[x]:
                degOfModules[i] -= 1
            # x has been used to remove it from the dictionary, no longer needed
            del degOfModules[x]
            # restart for loop
            break 
    if not degOfModules:
        # breaks when degOfModules is empty, when all modules have been printed
        break