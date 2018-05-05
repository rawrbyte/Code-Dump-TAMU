# Raymond Zhu
# 923008555
# CSCE 420
# Due: February 12, 2018
# hw1pr4.py

import sys
import copy
import operator

# global variables
startMatrix = [[]]
endMatrix = [[]]
blankPosition = [[[]]]
steps = [[[]]]
matrices = [[[]]]
distances = [[[]]]
numOfStates = 0

def createMatrix(list):
    _matrix = [[0 for x in range(3)] for x in range(3)]
    for i in range(0, 3):
        for j in range(0, 3):
            _matrix[i][j] = int(list[3*i + j])
    return _matrix

def printMatrix(matrix):
    #https://stackoverflow.com/questions/13214809/pretty-print-2d-python-list
    s = [[str(e) for e in row] for row in matrix]
    lens = [max(map(len, col)) for col in zip(*s)]
    fmt = ' '.join('{{:{}}}'.format(x) for x in lens)
    table = [fmt.format(*row) for row in s]
    print('\n'.join(table))

def output(_list, matrix):
    print("START")
    printMatrix(matrix)
    print("- - -")
    for i in range(1, len(_list)):
        if (list(map(operator.sub, _list[i], _list[i-1]))) == [1,0]:
            temp = matrix[_list[i][0]][_list[i][1]]
            matrix[_list[i][0]][_list[i][1]] = matrix[_list[i-1][0]][_list[i-1][1]]
            matrix[_list[i-1][0]][_list[i-1][1]] = temp
            print("DOWN")
            printMatrix(matrix)
            print("- - -")
        elif (list(map(operator.sub, _list[i], _list[i-1]))) == [-1,0]:
            temp = matrix[_list[i][0]][_list[i][1]]
            matrix[_list[i][0]][_list[i][1]] = matrix[_list[i-1][0]][_list[i-1][1]]
            matrix[_list[i-1][0]][_list[i-1][1]] = temp
            print("UP")
            printMatrix(matrix)
            print("- - -")
        elif (list(map(operator.sub, _list[i], _list[i-1]))) == [0,1]:
            temp = matrix[_list[i][0]][_list[i][1]]
            matrix[_list[i][0]][_list[i][1]] = matrix[_list[i-1][0]][_list[i-1][1]]
            matrix[_list[i-1][0]][_list[i-1][1]] = temp
            print("RIGHT")
            printMatrix(matrix)
            print("- - -")
        elif (list(map(operator.sub, _list[i], _list[i-1]))) == [0,-1]:
            temp = matrix[_list[i][0]][_list[i][1]]
            matrix[_list[i][0]][_list[i][1]] = matrix[_list[i-1][0]][_list[i-1][1]]
            matrix[_list[i-1][0]][_list[i-1][1]] = temp
            print("LEFT")
            printMatrix(matrix)
            print("- - -")
    print("Done! Generated " + str(numOfStates) + " state(s)")

def isSolution(index):
    if matrices[index][len(matrices[index])-1] == endMatrix:
        output(steps[index][len(steps[index])-1], startMatrix)
        quit()

def calculateMHAT(matrix, _matrix):
    distance = 0
    for i in range(0,3):
        for j in range(0,3):
            for k in range(0,3):
                for l in range(0,3):
                    if matrix[i][j] == _matrix[k][l]:
                        if matrix[i][j] != 0:
                            distance += (abs(i-k) + abs(j-l))       
    return distance

def UP(position):
    return isValid(position[0]-1, position[1])

def DOWN(position):
    return isValid(position[0]+1, position[1])

def LEFT(position):
    return isValid(position[0], position[1]-1)

def RIGHT(position):
    return isValid(position[0], position[1]+1)

def isValid(r, c):
    # verifies if a move is valid
    if r > 2 or c > 2 or r < 0 or c < 0:
        return False
    else:
        return True

def update(position, matrix, sequence, index, rowChange, columnChange):
    global matrices
    global blankPosition
    global steps
    global distances
    
    _matrix = copy.deepcopy(matrix)
    temp = _matrix[position[0]][position[1]]
    _matrix[position[0]][position[1]] = _matrix[position[0]+rowChange][position[1]+columnChange]
    _matrix[position[0]+rowChange][position[1]+columnChange] = temp
    manhattanDistance = calculateMHAT(endMatrix, _matrix)

    # saving new state
    if not matrices[index][0]:
        matrices[index][0].extend(_matrix)
        blankPosition[index][0].extend([position[0]+rowChange,position[1]+columnChange])
        steps[index][0].extend(sequence + [[position[0]+rowChange,position[1]+columnChange]])
        distances[index][0].extend([manhattanDistance])
    else:
        matrices[index].append(_matrix)
        blankPosition[index].append([position[0]+rowChange,position[1]+columnChange])
        steps[index].append(sequence + [[position[0]+rowChange,position[1]+columnChange]])
        distances[index].append([manhattanDistance])

def run(position, matrix, sequence, index):
    global numOfStates

    if UP(position):
        update(position, matrix, sequence, index, -1, 0)
        numOfStates += 1
        isSolution(index)
    if RIGHT(position):
        update(position, matrix, sequence, index, 0, 1)
        numOfStates += 1
        isSolution(index)
    if DOWN(position):
        update(position, matrix, sequence, index, 1, 0)
        numOfStates += 1
        isSolution(index)
    if LEFT(position):
        update(position, matrix, sequence, index, 0, -1)
        numOfStates += 1
        isSolution(index)

puzzleStart = input("Enter 8-puzzle starting state by rows (0 for blank): ")
puzzleEnd = input("Enter ending state by rows (0 for blank): ")

# prime initial state for bfs to run
startMatrix = createMatrix(puzzleStart.split(','))
endMatrix = createMatrix(puzzleEnd.split(','))
matrices[0] = [startMatrix]
distances[0] = [calculateMHAT(startMatrix,endMatrix)]

for i in range (0, 3):
    for j in range (0 ,3):
        if startMatrix[i][j] == 0:
            blankPosition[0] = [[i,j]]
            steps[0] = [[[i,j]]]

for i in range(0,100): # represents each depth
    blankPosition.append([[]])
    distances.append([[]])
    matrices.append([[]])
    steps.append([[]])
    minMHAT = distances[i][0]
    minList = []
    for j in range(0, len(blankPosition[i])): # represents the children of each depth
        if distances[i][j] <= minMHAT: # chooses the smallest manhattan values of all the matrices produced
            minMHAT = distances[i][j]
    for k in range(0, len(blankPosition[i])): # runs through all the matrices that have the same lowest value
        if distances[i][k] == minMHAT:
            minList.append(k)
    for l in range(0, len(minList)):
        run(blankPosition[i][minList[l]], matrices[i][minList[l]], steps[i][minList[l]], i+1)
