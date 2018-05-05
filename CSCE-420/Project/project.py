# Raymond Zhu
# 923008555
# CSCE 420
# Due: April 23, 2018
# project.py

import math
import random
import time
import operator
import copy
import sys
import numpy as np

#   ASCII FONT
A = ["0x7E", "0x11", "0x11", "0x11", "0x7E"]
B = ["0x7F", "0x49", "0x49", "0x49", "0x36"]
C = ["0x3E", "0x41", "0x41", "0x41", "0x22"]
D = ["0x7F", "0x41", "0x41", "0x22", "0x1C"]
E = ["0x7F", "0x49", "0x49", "0x49", "0x41"]
F = ["0x7F", "0x09", "0x09", "0x01", "0x01"]
G = ["0x3E", "0x41", "0x41", "0x51", "0x32"]
H = ["0x7F", "0x08", "0x08", "0x08", "0x7F"]
I = ["0x00", "0x41", "0x7F", "0x41", "0x00"]
J = ["0x20", "0x40", "0x41", "0x3F", "0x01"]
K = ["0x7F", "0x08", "0x14", "0x22", "0x41"]
L = ["0x7F", "0x40", "0x40", "0x40", "0x40"]
M = ["0x7F", "0x02", "0x04", "0x02", "0x7F"]
N = ["0x7F", "0x04", "0x08", "0x10", "0x7F"]
O = ["0x3E", "0x41", "0x41", "0x41", "0x3E"]
P = ["0x7F", "0x09", "0x09", "0x09", "0x06"]
Q = ["0x3E", "0x41", "0x51", "0x21", "0x5E"]
R = ["0x7F", "0x09", "0x19", "0x29", "0x46"]
S = ["0x46", "0x49", "0x49", "0x49", "0x31"]
T = ["0x01", "0x01", "0x7F", "0x01", "0x01"]
U = ["0x3F", "0x40", "0x40", "0x40", "0x3F"]
V = ["0x1F", "0x20", "0x40", "0x20", "0x1F"]
W = ["0x7F", "0x20", "0x18", "0x20", "0x7F"]
X = ["0x63", "0x14", "0x08", "0x14", "0x63"]
Y = ["0x03", "0x04", "0x78", "0x04", "0x03"]
Z = ["0x61", "0x51", "0x49", "0x45", "0x43"]

# List of all the letters containing their hex codes
Alphabet = [A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z]
# List of characters to help assign index values to letters. A-Z <=> 0-25
Characters = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']
# The batch that will be used when training the neural network
listOfExamples = []

class Example:
    def __init__(self, x, y):
        self.input_vector = x
        self.output_vector = y
        
    input_vector = []
    output_vector  = []

class Network:
    def __init__(self, l, i, h, o):
        self.layers = l
        self.inputSize = i
        self.hiddenSize = h
        self.outputSize = o
		
    inputSize = 0
    hiddenSize = 0
    outputSize = 0
    layers = 0
    wout = []
    whidden = []

def HEX_TO_BINARY(list):
    # https://stackoverflow.com/questions/1425493/convert-hex-to-binary
    binary_list = []
    scale = 16 ## equals to hexadecimal
    num_of_bits = 7
    for x in list:
        binary_list.append(bin(int(x, scale))[2:].zfill(num_of_bits))

    return binary_list

def SIGMOID_ACTIVATION_FUNCTION(x):
    return 1 / (1 + math.exp(-x))

def TANH_ACTIVATION_FUNCTION(x):
    return math.tanh(x)

def LOGISTIC_SIGMOID(x):
    # the derivative for sigmoid activation function
    return SIGMOID_ACTIVATION_FUNCTION(x) * (1-SIGMOID_ACTIVATION_FUNCTION(x))

def HYPERBOLIC_TANGENT_SIGMOID(x):
    # the derivative for tanh activation function
    return 1 - TANH_ACTIVATION_FUNCTION(x)**2

def BACK_PROP_LEARNING(examples, network):
    # initalize error arrays 
    errors_output = [0 for x in range(network.outputSize)]
    errors_hidden = [0 for x in range(network.hiddenSize)]
    epoch = 0
    
    while True:
        # initializing heuristics
        sTime = time.time()
        totalError = 0.0
        letterAccuracy = []
        for x in range(0, len(examples)):
            weighted_sum = []
            output_actual = []
            input_activations = []
            hidden_activations = []
            hidden_weighted_sum = []
            # forward propagation
            for i in examples[x].input_vector:
                input_activations.append(i)
            for j in range(0, network.hiddenSize):
                # weights array is arranged in the from [w11, w12, w13, ... , wij]
                # the list is divided into j sections each containing i weights 
                ws = 0
                for i in range(0, network.inputSize):
                    # for each neuron in the hidden layer, get the sum of all its inputs
                    # i*network.hiddenSize+j = w1j, w2j, w3j ... for each j neuron in the hidden layer
                    ws += (network.whidden[i*network.hiddenSize+j] * input_activations[i])
                hidden_weighted_sum.append(round(ws,3))
                hidden_activations.append(round(TANH_ACTIVATION_FUNCTION(ws),3))
            for j in range(0, network.outputSize):
                # weights array is arranged in the from [w11, w12, w13, ... , wij]
                # the list is divided into j sections each containing i weights 
                ws = 0
                for i in range(0, network.hiddenSize):
                    # for each neuron in the output layer, get the sum of all its connections
                    # i*network.outputSize+j = w1j, w2j, w3j ... for each j neuron in the output layer
                    ws += (network.wout[i*network.outputSize+j] * hidden_activations[i])
                weighted_sum.append(round(ws,3))
                output_actual.append(round(SIGMOID_ACTIVATION_FUNCTION(ws),3))
            # backward propagation    
            for j in range(0, network.outputSize):
                # error calculation of output layer
                errors_output[j] = LOGISTIC_SIGMOID(weighted_sum[j]) * (examples[x].output_vector[j]-output_actual[j])
            for i in range(0, network.hiddenSize):
                error = 0
                for j in range(0, network.outputSize):
                    # for each neuron in the hidden layer, get the sum of all its connections
                    # i*network.outputSize+j = wi1, wi2, wi3, ... for each i neuron in the hidden layer
                    error += network.wout[i*network.outputSize+j] * errors_output[j]
                errors_hidden[i] = HYPERBOLIC_TANGENT_SIGMOID(hidden_weighted_sum[i])*error
            # update weights    
            counter = 0
            for w in range(0, len(network.wout)):
                # need a counter to get the position of each i neuron's jth index for j layer's error array value
                # math.floor() is used to get the correct index for each ith node relative to the size of weights array 
                network.wout[w] = network.wout[w] + 1/(math.sqrt(network.hiddenSize)) * hidden_activations[math.floor(w/network.outputSize)] * errors_output[counter]
                counter += 1
                if counter == network.outputSize:
                    counter = 0
            counter = 0
            for w in range(0, len(network.whidden)):
                # need a counter to get the position of each i neuron's jth index for j layer's error array value
                # math.floor() is used to get the correct index for each ith node relative to the size of weights array 
                network.whidden[w] = network.whidden[w] + 1/(math.sqrt(network.inputSize)) * input_activations[math.floor(w/network.hiddenSize)] * errors_hidden[counter]
                counter += 1    
                if counter == network.hiddenSize:
                    counter = 0
            # Subtracting a list with a list and taking the sum of the absolute value of that list    
            totalError = totalError + sum(list(map(abs, list(map(operator.sub, examples[x].output_vector, output_actual)))))
            letterAccuracy.append(output_actual[x])

        # totalError is a sum of all 26 letters' errors, need to calculate the average totalError
        totalError = round(totalError/len(examples), 4)
        averageAccuracy = round(sum(letterAccuracy)/26.0, 3)
        print("epoch: " + str(epoch) + "\terror: " + str(totalError) + "\t avg: " + str(averageAccuracy) + "\ttime: " + str(round(time.time()-sTime,3)))
        log = open("training_data.txt", "a")
        log.write(str(totalError)+"\n")

        epoch += 1
        if averageAccuracy >= 0.9:
            break
    return network

def test(example, network):
    # same code used in back propagation
    weighted_sum = []
    output_actual = []
    input_activations = []
    hidden_activations = []
    hidden_weighted_sum = []
    for i in example.input_vector:
        input_activations.append(i)
    # forward propagation
    for j in range(0, network.hiddenSize):
        ws = 0
        for k in range(0, network.inputSize):
            ws += (network.whidden[k*network.hiddenSize+j] * input_activations[k])
        hidden_weighted_sum.append(round(ws,3))
        hidden_activations.append(round(TANH_ACTIVATION_FUNCTION(ws),3))
    for k in range(0, network.outputSize):
        ws = 0
        for l in range(0, network.hiddenSize):
            ws += (network.wout[l*network.outputSize+k] * hidden_activations[l])
        weighted_sum.append(round(ws,3))
        output_actual.append(round(SIGMOID_ACTIVATION_FUNCTION(ws),3))
    
    return output_actual

def flip(example, flippedSet):
    # take in a letter and flip 0 to 1 or 1 to 0 in it's input_vector
    # add the index of the flipped bit into a set flippedSet to ensure every flip is a different index
    randomNum = random.randint(0, 34)
    if randomNum in flippedSet:
        while randomNum in flippedSet:
            randomNum = random.randint(0, 34)
    flippedSet.add(randomNum)

    if example.input_vector[randomNum] == 0:
        example.input_vector[randomNum] = 1
    else:
        example.input_vector[randomNum] = 0
    
    return example, flippedSet

def display(example):
    # prints out what the input_vector looks like
    _matrix = []
    for k in range(0, 5):
        row = []
        for j in range(0, 7):
            row.append(example.input_vector[k*7+j])
        _matrix.append(row)
    matrix = np.rot90(np.matrix(_matrix))

    print("---------------")

    for r in range(0 , 7):
        row = ""
        for c in range(0, 5):
            if matrix[r, c] == 0:
                row = row + "   "
            else:
                row = row + " 1 "
        print(row)

    print("---------------\n")

    return None

for x in range(0, len(Alphabet)):
    training_output = []
    training_input = []
    training_input_bin = HEX_TO_BINARY(Alphabet[x])

    for i in training_input_bin:
        # append each bit into a list for a letter's input_vector
        for j in list(i):
            training_input.append(int(j))
    for y in range(0, 26):
        # creates the output_vector
        if y == x:
            # since the for loop runs through A-Z, each x represents A-Z
            training_output.append(1)
            continue
        training_output.append(0)
        
    listOfExamples.append(Example(training_input, training_output))

random.seed(time)
ASCII_NN = Network(2, 35, 35, 26)
for w in range(0, ASCII_NN.inputSize*ASCII_NN.hiddenSize):
    # generate random weights for input/hidden layer
    rw = random.uniform(-0.1, 0.1)
    while rw == 0.0:
        rw = random.uniform(-0.1, 0.1)
    ASCII_NN.whidden.append(round(rw,3))
for w in range(0, ASCII_NN.hiddenSize*ASCII_NN.outputSize):
    # generate random weights for hidden/output layer
    rw = random.uniform(-0.1, 0.1)
    while rw == 0.0:
        rw = random.uniform(-0.1, 0.1)
    ASCII_NN.wout.append(round(rw,3))

# Training the neural network
ASCII_NN = BACK_PROP_LEARNING(listOfExamples, ASCII_NN)

# Basic Letter Verification Test
for x in range(0, len(listOfExamples)):
    letter_num = 0
    maxvalue = 0.0
    result = test(listOfExamples[x], ASCII_NN)
    # iterating through the output vector and getting the index of the highest value
    for i in range(0, len(result)):
        if result[i] > maxvalue:
            maxvalue = result[i]
            letter_num = i
    print("testing:" + str(Characters[x]) + "\tresult: " + str(Characters[letter_num]) + "\tvalue: " + str(round(result[letter_num],3)))

# Bit Flip Test
for _ in range(0, 3):
    # each x index corresponds to the english alphabet from A - Z
    for x in range(0, len(listOfExamples)):
        tolerance = 0
        letter_num = x
        flippedSet = set()
        # making a deep copy of a letter's example class that will be modified per bit flip
        modifiedExample = copy.deepcopy(listOfExamples[x])
        while x == letter_num:
            maxvalue = 0.0
            modifiedExample, flippedSet = flip(modifiedExample, flippedSet)
            result = test(modifiedExample, ASCII_NN)
            # iterating through the output vector and getting the index of the highest value
            for i in range(0, len(result)):
                if result[i] > maxvalue:
                    maxvalue = result[i]
                    letter_num = i
            # checks to see whether the highest index matches the current index being tested        
            if x == letter_num:
                tolerance += 1
            # prevents an infinite loop, the test can only flip a letter's bits 35 times
            if len(flippedSet) == 35:
                break

        log = open("test_data.txt", "a")
        log.write("The letter " + Characters[x] + " tolerated " + str(tolerance) + " flips\n")
        log.write("The neural network thinks it is the letter " + Characters[letter_num] + "\n")
        log.close()
        log = open("bitflip.txt", "a")
        log.write(str(tolerance) + "\n")
        log.close()
        print("The letter " + Characters[x] + " tolerated " + str(tolerance) + " flips")

# Input Test
while True:
    try:
        # Input error checking
        inputString = input("Input: ")
        while len(inputString) != 35:
            print("Not a valid length")
            inputString = input("Input: ")
        int(inputString)
        # Turns a string into a list of characters, then maps each character into an integer value
        input_vector = list(map(int, list(inputString)))
        output_vector = []
        letter_num = 0
        maxvalue = 0.0
        example = Example(input_vector, output_vector)
        result = test(example, ASCII_NN)
        # Testing input
        for i in range(0, len(result)):
            if result[i] > maxvalue:
                maxvalue = result[i]
                letter_num = i
        print("The neural network thinks your input is the letter " + Characters[letter_num] + ", " + str(round(result[letter_num],3)))
        display(example)
    except ValueError:
        print("Not a valid input")
        continue
