# Raymond Zhu
# 923008555
# CSCE 420
# Due: February 12, 2018
# hw1pr2.py

import sys
import os.path
import time
import random

actions = 0
vR = 0
vC = 0
r = 0
c = 0
Grid = [[]]
cleanTiles = set()
obstacles = set()
whoopsWall = set()
performanceMeasure = []
performanceCount = 0

def resetValues():
    # this function resets the values needed for each run
    global vR
    global vC
    global Grid
    global actions
    global cleanTiles
    global obstacles
    global whoopsWall
    global performanceCount
    
    vR = 0
    vC = 0
    Grid.clear()
    actions = 0
    cleanTiles.clear()
    obstacles.clear()
    whoopsWall.clear()
    performanceCount = 0

def UP():
    # this function moves the agent up a row
    global vR
    global actions
    global performanceCount
    vR -= 1
    actions += 1
    performanceCount += len(cleanTiles)
    
    if isWall():
        vR += 1
    elif isObstacle():
        vR += 1
    else:
        isDirty()

def DOWN():
    # this function moves the agent down a row
    global vR
    global actions
    global performanceCount
    vR += 1
    actions += 1
    performanceCount += len(cleanTiles)

    if isWall():
        vR-= 1
    elif isObstacle():
        vR -= 1
    else:
        isDirty()

def LEFT():
    # this function shifts the agent to the left column
    global vC
    global actions
    global performanceCount
    vC -= 1
    actions += 1
    performanceCount += len(cleanTiles)

    if isWall():
        vC += 1
    elif isObstacle():
        vC += 1
    else:
        isDirty()

def RIGHT():
    # this function shifts the agent to the right column
    global vC
    global actions
    global performanceCount
    vC += 1
    actions += 1
    performanceCount += len(cleanTiles)

    if isWall():
        vC -= 1
    elif isObstacle():
        vC -= 1
    else:
        isDirty()

def createMatrix(_numOfRows, _numOfColumns, v):
    # this function takes the values parsed from load() and creates the 2D matrix
    global Grid
    global r
    global c
    r = _numOfRows
    c = _numOfColumns
    obstacleList = set()
    randomValue = random.randint(0,r*c)
    Grid = [[0 for x in range(c)] for x in range(r)]
    for i in range(0, r):
        list = v[i].split()
        for j in range(0, c):
            Grid[i][j] = int(list[j])
    while randomValue > 0:
        _row = random.randint(0,r-1)
        _column = random.randint(0,c-1)
        if str(_row)+" "+str(_column) not in obstacleList:
            obstacleList.add(str(_row)+" "+str(_column))
            Grid[_row][_column] = -1
            randomValue -= 1

def printMatrix():
    # https://stackoverflow.com/questions/13214809/pretty-print-2d-python-list
    global Grid
    s = [[str(e) for e in row] for row in Grid]
    lens = [max(map(len, col)) for col in zip(*s)]
    fmt = ' '.join('{{:{}}}'.format(x) for x in lens)
    table = [fmt.format(*row) for row in s]
    print('\n'.join(table) + '\n')
    print("pos(" + str(vR) + ", " + str(vC) + ")")

def isDirty():
    # this function checks whether the current tile the agent is on is dirty
    global vR
    global vC
    global Grid
    global cleanTiles
    global performanceCount
    if Grid[vR][vC] == 0:
        if str(vR)+" "+str(vC) not in cleanTiles:
            cleanTiles.add(str(vR)+" "+str(vC))
    elif Grid[vR][vC] == 1:
        suck()
        performanceCount += len(cleanTiles)
    #printMatrix()
            
def suck():
    # this function "sucks" the tile if dirty
    global vR
    global vC
    global Grid
    global actions
    global cleanTiles
    Grid[vR][vC] = 0
    actions+=1
    cleanTiles.add(str(vR)+" "+str(vC))

def isObstacle():
    # this function checks to see whether the tile the agent attempts to move to is an obstacle
    global vR
    global vC
    global actions
    global Grid
    global obstacles
    if Grid[vR][vC] == -1:
        if str(vR)+" "+str(vC) not in obstacles:
            obstacles.add(str(vR)+" "+str(vC))
        return True
    return False

def isWall():
    # this function checks to see whether the tile the agent attempts to move to is a wall
    global r
    global c
    global vR
    global vC
    if vR >= r or vR < 0 or vC >= c or vC < 0:
        if str(vR)+" "+str(vC) not in whoopsWall:
            whoopsWall.add(str(vR)+" "+str(vC))
        return True
    return False

def run():
    # this function is the core of the vacuum agent. this includes how the agent starts, ends, and the conditions that makeup its AI
    global r
    global c
    trap1 = str(0)+" "+str(1)
    trap2 = str(1)+" "+str(0)
    isDirty()
    while actions <= 2000000: # the agent should know it's done cleaning when its memory contains the entire dimension of the room
        if actions >= 2000000:
            break
        elif Grid[0][0] == -1:
            break
        elif (trap1 in obstacles and trap2 in obstacles):
            RIGHT()   
        else: 
            movement = random.randint(0,3)
            exploredLeft = str(vR)+" "+str(vC-1)
            exploredRight = str(vR)+" "+str(vC+1)
            exploredUp = str(vR-1)+" "+str(vC)
            exploredDown = str(vR+1)+" "+str(vC)
            if exploredLeft in cleanTiles and (exploredRight in whoopsWall or exploredRight in obstacles) and (exploredUp in whoopsWall or exploredUp in obstacles) and (exploredDown in whoopsWall or exploredDown in obstacles):
                LEFT() 
            elif exploredRight in cleanTiles and (exploredLeft in whoopsWall or exploredLeft in obstacles) and (exploredUp in whoopsWall or exploredUp in obstacles) and (exploredDown in whoopsWall or exploredDown in obstacles):
                RIGHT()   
            elif exploredDown in cleanTiles and (exploredLeft in whoopsWall or exploredLeft in obstacles) and (exploredUp in whoopsWall or exploredUp in obstacles) and (exploredRight in whoopsWall or exploredRight in obstacles):
                DOWN()   
            elif exploredUp in cleanTiles and (exploredLeft in whoopsWall or exploredLeft in obstacles) and (exploredRight in whoopsWall or exploredRight in obstacles) and (exploredDown in whoopsWall or exploredDown in obstacles):
                UP()  
            elif exploredLeft in cleanTiles and exploredRight in cleanTiles and exploredDown in cleanTiles and (exploredUp in whoopsWall or exploredUp in obstacles):
                if movement == 0:
                    LEFT()
                elif movement == 1:
                    RIGHT()   
                elif movement == 2:
                    DOWN()
                else:
                    DOWN()  
            elif exploredLeft in cleanTiles and exploredRight in cleanTiles and exploredUp in cleanTiles and (exploredDown in whoopsWall or exploredDown in obstacles):
                if movement == 0:
                    LEFT()
                elif movement == 1:
                    RIGHT()   
                elif movement == 3:
                    UP()
                else:
                    UP()
            elif exploredLeft in cleanTiles and exploredUp in cleanTiles and exploredDown in cleanTiles and (exploredRight in whoopsWall or exploredRight in obstacles):
                if movement == 0:
                    LEFT()
                elif movement == 2:
                    DOWN()  
                elif movement == 3:
                    UP()
                else:
                    LEFT()
            elif exploredRight in cleanTiles and exploredUp in cleanTiles and exploredDown in cleanTiles and (exploredLeft in whoopsWall or exploredLeft in obstacles):
                if movement == 1:
                    RIGHT()   
                elif movement == 2:
                    DOWN()  
                elif movement == 3:
                    UP()
                else:
                    RIGHT()
            elif (exploredUp in whoopsWall or exploredUp in obstacles) and (exploredDown in whoopsWall or exploredDown in obstacles) and exploredLeft in cleanTiles and exploredRight in cleanTiles:
                if movement == 0 or movement == 2:
                    LEFT()
                elif movement == 1 or movement == 3:
                    RIGHT()   
            elif (exploredRight in whoopsWall or exploredRight in obstacles) and (exploredDown in whoopsWall or exploredDown in obstacles) and exploredUp in cleanTiles and exploredLeft in cleanTiles:
                if movement == 0 or movement == 1:
                    LEFT()
                elif movement == 3 or movement == 2:
                    UP()
            elif (exploredRight in whoopsWall or exploredRight in obstacles) and (exploredUp in whoopsWall or exploredUp in obstacles) and exploredDown in cleanTiles and exploredLeft in cleanTiles:
                if movement == 2 or movement == 0:
                    DOWN()  
                elif movement == 3 or movement == 1:
                    LEFT()
            elif (exploredLeft in whoopsWall or exploredLeft in obstacles) and (exploredDown in whoopsWall or exploredDown in obstacles) and exploredUp in cleanTiles and exploredRight in cleanTiles:
                if movement == 1 or movement == 0:
                    RIGHT()   
                elif movement == 3 or movement == 2:
                    UP()
            elif (exploredLeft in whoopsWall or exploredLeft in obstacles) and (exploredUp in whoopsWall or exploredUp in obstacles) and exploredDown in cleanTiles and exploredRight in cleanTiles:
                if movement == 1 or movement == 0:
                    RIGHT()   
                elif movement == 2 or movement == 3:
                    DOWN()  
            elif (exploredLeft in whoopsWall or exploredLeft in obstacles) and (exploredRight in whoopsWall or exploredRight in obstacles) and exploredDown in cleanTiles and exploredUp in cleanTiles:
                if movement == 2 or movement == 0:
                    DOWN()  
                elif movement == 3 or movement == 1:
                    UP()
            else:
                if movement == 0:
                    if exploredLeft in obstacles or exploredLeft in whoopsWall:
                        continue
                    LEFT()
                elif movement == 1:
                    if exploredRight in obstacles or exploredRight in whoopsWall:
                        continue
                    RIGHT()   
                elif movement == 2:
                    if exploredDown in obstacles or exploredDown in whoopsWall:
                        continue
                    DOWN()  
                elif movement == 3:
                    if exploredUp in obstacles or exploredUp in whoopsWall:
                        continue
                    UP()
            
def generateData():
    # this function creates a new data file each time it is called
    row = ""
    with open("data.txt", "w") as _f:
        _f.write("1000\n")
        _f.write("1000\n")
        for _ in range(0, 1000):
            for _ in range(0,1000):
                row = row + "1 "
            _f.write(row+"\n")
            row = ""
 
def load():
    # this function parses a data file and loads the file into a 2D matrix
    with open(sys.argv[1], 'r') as _f:
        numOfRows = int(_f.readline())
        numOfColumns = int(_f.readline())
        rowContents = _f.readlines()
        rowContents = [x.strip() for x in rowContents]
    createMatrix(numOfRows, numOfColumns, rowContents)

if __name__ == '__main__':
    if os.path.exists(sys.argv[1]):
        random.seed(time)
        generateData()
        for j in range (0, 10): # loop for how many tests to be done
            resetValues()
            load()
            start = time.time()
            run()
            end = time.time()
            performanceMeasure.append(performanceCount)
            print(str(j+1)+": " + str(len(cleanTiles)) + ", " + str(performanceMeasure[j]) + ", " + str(end-start) + " sec")

        print("Average agent performance: " + str(sum(performanceMeasure)/len(performanceMeasure)))
    else:
        print('No input file!')
