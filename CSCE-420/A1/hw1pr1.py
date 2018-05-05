# Raymond Zhu
# 923008555
# CSCE 420
# Due: February 12, 2018
# hw1pr1.py

import sys
import os.path

performanceCount = 0
actions = 0
vR = 0
vC = 0
Grid = [[]]
cleanTiles = set()

def UP():
    global vR
    global actions
    global cleanTiles
    global performanceCount
    vR -= 1
    actions+=1
    performanceCount += len(cleanTiles)
    isDirty()

def DOWN():
    global vR
    global actions
    global cleanTiles
    global performanceCount
    vR += 1
    actions+=1
    performanceCount += len(cleanTiles)
    isDirty()

def LEFT():
    global vC
    global actions
    global cleanTiles
    global performanceCount
    vC -= 1
    actions+=1
    performanceCount += len(cleanTiles)
    isDirty()

def RIGHT():
    global vC
    global actions
    global cleanTiles
    global performanceCount
    vC += 1
    actions+=1
    performanceCount += len(cleanTiles)
    isDirty()

def createMatrix(r, c, v):
    global Grid
    Grid = [[0 for x in range(c)] for x in range(r)]
    for i in range(0, r):
        list = v[i].split()
        for j in range(0, c):
            Grid[i][j] = int(list[j])

def isDirty():
    if Grid[vR][vC] == 1:
        suck()
    elif str(vR)+" "+str(vC) not in cleanTiles:
        cleanTiles.add(str(vR)+" "+str(vC))

def suck():
    global vR
    global vC
    global actions
    global cleanTiles
    global performanceCount
    Grid[vR][vC] = 0
    cleanTiles.add(str(vR)+" "+str(vC))
    actions+=1
    performanceCount += len(cleanTiles)

def run(r, c):
    isDirty()
    while actions <= 1000:
        for i in range(0, r):
            if i%2 == 0:
                while vC != c-1 and actions <= 1000:
                    RIGHT()
            else:
                while vC != 0 and actions <= 1000:
                    LEFT()
            if vR != r-1:
                DOWN()
        for i in range(0, r):
            if i%2 == 0:
                while vC != 0 and actions <= 1000:
                    LEFT()
            else:
                while vC != c-1 and actions <= 1000:
                    RIGHT()
            if vR != 0:
                UP()

if os.path.exists(sys.argv[1]):
    with open(sys.argv[1], 'r') as _f:
        numOfRows = int(_f.readline())
        numOfColumns = int(_f.readline())
        rowContents = _f.readlines()
        rowContents = [x.strip() for x in rowContents]
    createMatrix(numOfRows, numOfColumns, rowContents)
    run(numOfRows, numOfColumns)

    print("Vacuum performance measure: " + str(performanceCount))
else:
    print('No input file!')
