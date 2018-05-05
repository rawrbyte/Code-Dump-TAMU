# Raymond Zhu
# 923008555
# CSCE 420
# Due: March 5, 2018
# hw2pr3.py

import sys
import os

def query(eval):
    # evaluates the satisfiability of the queried symbol
    return not eval

def applyDeMorganLaw(clause):
    # this method takes the ~ into the parenthesis
    # applies demorgan rule to a conjunction of symbols
    result = ""
    for x in range(0, len(clause)):
        if clause[x].isalpha():
            result = result + "~" + clause[x]
        elif clause[x] == ',':
            result = result + " | "
    return result

def removeImplication(clauseList):
    # converts A->B to cnf form
    # takes in a list of size 2 as input
    # clauseList[0] = rhs, clauseList[0] = lhs
    lhs = ""
    if ',' in clauseList[1]:
        lhs = applyDeMorganLaw(clauseList[1])
    else:
        lhs = "~" + clauseList[1][0]
    rhs = clauseList[0]
    return lhs + " | " + rhs
    
def convertToCnfForm(clause):
    # converts prolog notation into cnf form
    if clause == ":-.":
        return ""
    elif clause[0].isalpha():
        if len(clause) == 2:
            return clause[0]
        elif ":-." in clause:
            return clause[0]
        elif ":-" in clause:
            implyList = clause.split(":-")
            return removeImplication(implyList)
    elif clause.startswith(":-"):
        if ',' in clause:
            return applyDeMorganLaw(clause)
        return "~" + clause[2]
    elif clause.startswith('?'):
        return "~" + clause[1]
        
def interpretClause(clause, model):
    # interprets the truth value of the given clause
    # this method is recursive by passing a substring
    boolVal = None
    nextCall = ""
    if len(clause) == 0:
        return False
    for x in range(0, len(clause)):
        if clause[x] == "~":
            if clause[x+1] in model:
                boolVal = not model[clause[x+1]]
            else:
                return None
        elif clause[x] == "|":
            nextCall = clause[x+1:]   
            break
        elif clause[x].isalpha():
            if clause[x-1] == "~":
                continue
            elif clause[x] in model:
                boolVal = model[clause[x]]
            else:
                return None
    return boolVal or interpretClause(nextCall, model)

def addToDict(model, P, value):
    # adds element into dictionary
    # using this method because can't
    # add elements dynamically
    m = model.copy()
    m[P] = value
    return m
    
def removeSymbols(P, symbols):
    # removes the symbol from list of symbols
    s = symbols.copy()
    s.remove(P)
    return s

def DPLL_SATISFIABLE(s):
    clauses = []
    symbols = set()
    for x in s:
        # added a space here for a "simple" trick to evaluate clauses
        # where symbols do not have ~
        cnf = " " + convertToCnfForm(x)
        if cnf == " ":
            continue
        clauses.append(cnf)
        for y in range(0, len(cnf)):
            if cnf[y].isalpha():
                symbols.add(cnf[y]) 
    return DPLL(clauses, symbols, {})

def DPLL(clauses, symbols, model):
    # DPLL method from the textbook, pretty much like how
    # the textbook described the algorithm
    boolVals = []
    boolDict = {}
    for var in clauses:
        val = interpretClause(var, model)
        boolVals.append(val)
        boolDict[var] = val
    if None not in boolVals:
        if False in boolVals:
            return query(False)
        else:
            return query(True)
    P, value = FIND_PURE_SYMBOL(symbols, clauses, model)
    if P is not None:
        return DPLL(clauses, removeSymbols(P, symbols), addToDict(model, P, value))
    P, value = FIND_UNIT_CLAUSE(clauses, model)
    if P is not None:
        return DPLL(clauses, removeSymbols(P, symbols), addToDict(model, P, value))
    P = symbols.pop(0)
    return DPLL(clauses, symbols, addToDict(model, P, False)) or DPLL(clauses, symbols, addToDict(model, P, True))

def FIND_UNIT_CLAUSE(clauses, model):
    # all but one symbol needs to be unknown in 
    # a clause to give it a truth value
    # and so, an offset value is used to see
    # whether there are one or more unknown variables
    result = set()
    for var in clauses:
        result.clear()
        offset = 0
        unitChar = ''
        for x in range(0, len(var)):
            if var[x].isalpha() and var[x] not in model:
                offset += 1
                unitChar = var[x]
        if offset == 1:
            if '~'+unitChar in var:
                return unitChar, False
            else:
                return unitChar, True
    return None, None

def FIND_PURE_SYMBOL(symbols, clauses, model):
    # using a set because a specific symbol can
    # either appear as only false or true, so
    # a set allows for an easy check
    result = set()
    for i in symbols:
        result.clear()
        for var in clauses:
            if len(var) <= 3:
                # this condition here makes sure unit clause
                # doesn't override the facts stated in the
                # horn clauses
                if i in var:
                    if '~'+i in var:
                        return i, False
                    else:
                        return i, True
            elif i in var:
                if '~'+i in var:
                    result.add("False")
                else:
                    result.add("True")
        if len(result) != 1:
            continue
        if "False" in result:
            return i, False
        elif "True" in result:
            return i, True
    return None, None

with open(sys.argv[1], 'r') as _f:
    contents = _f.readlines()
    contents = [x.strip() for x in contents]
print(DPLL_SATISFIABLE(contents))
