# Raymond Zhu
# 923008555
# CSCE 420
# Due: March 5, 2018
# hw2pr2.py

import sys
import ast

def RESULT(state, action):
	if type(action) is int:
		# states can only be lists, 
		# so if the elem in a list is just an int, 
		# need to convert it to a list
		return [action]
	return action
	
def ACTIONS(state):
	return state

def TERMINAL_STATE(state):
	# this is a required, if not, the frontier will reach the maximum recursive depth. lol
	if len(state) == 1 and type(state[0]) is int:
		# two conditions to ensure that it's just an integer
		return True
	return False

def UTILITY(state):
		# returns the int value to be compared with min/max for value v
		return state[0]
	
def MAX_VALUE(state):
	if TERMINAL_STATE(state):
		return UTILITY(state)
	v = -99999
	for a in ACTIONS(state):
		v = max(v, MIN_VALUE(RESULT(state, a)))
	return v
	
def MIN_VALUE(state):
	if TERMINAL_STATE(state):
		return UTILITY(state)
	v = 99999
	for a in ACTIONS(state):
		v = min(v, MAX_VALUE(RESULT(state, a)))
	return v

tree = 	input("tree: ")
# Example tree: ((3,8,(7,(3,0,7),(8,8,2))),(4,(7,9,8),8),(((3,6,4),2,6),((9,2,9),4,7,(6,4,5) ),4,(6,4,5)))
# simple way of converting a string into a nested list
minimax = ast.literal_eval(tree)

solution = MIN_VALUE([MAX_VALUE(minimax)])
print("Minimax Decision: " + str(solution))
