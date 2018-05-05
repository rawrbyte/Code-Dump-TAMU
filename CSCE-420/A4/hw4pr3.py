# Raymond Zhu
# 923008555
# CSCE 420
# Due: May 1, 2018
# hw4pr3.py

import sys
import os.path

# words should be distinct
setOfWords = set()

# load file from shared directory 
with open("/usr/share/dict/words", "rb") as _input:
    for word in _input:
        # converts the bytes into a string
        s = word.decode('ascii').rstrip('\r\n')
        # conditions for letters that are added to the set
        if len(s) >= 3 and s.isalpha():
            setOfWords.add(s)

while True:
    try: 
        user_input = input('Enter first two letters of a word: ')
        # checks if user input is of length 2 and only contains characters
        while len(user_input) != 2 or not user_input.isalpha():
            print("Input does not match requirements")
            user_input = input('Enter first two letters of a word: ')
        letterFrequency = {}
        frequentKey = ""
        numOfOccurences = 0
        for x in setOfWords:
            # using lower() to compare both strings as lower case strings
            if x.lower().startswith(user_input.lower()):
                # add to dictionary if not in dictionary
                if x[len(user_input)].lower() not in letterFrequency:
                    letterFrequency[x[len(user_input)].lower()] = 1
                else:
                    # increment frequency if already in dictionary
                    letterFrequency[x[len(user_input)].lower()] += 1
        if not letterFrequency:
            frequentKey = "none"
        else:
            for x in letterFrequency:
                # find the letter with the highest frequency, which will be the most likely next letter
                if letterFrequency[x] > numOfOccurences:
                    numOfOccurences = letterFrequency[x]
                    frequentKey = x
        print("The most likely next letter is " + frequentKey)
    except EOFError:
        break
