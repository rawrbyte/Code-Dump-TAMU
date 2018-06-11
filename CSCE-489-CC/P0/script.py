import os.path
import pickle
import sys
import socket

def ipv4_check(address):
    "This validates an ipv4 address"
    # https://stackoverflow.com/questions/319279/how-to-validate-ip-address-in-python
    try:
        socket.inet_pton(socket.AF_INET, address)
    except AttributeError:  # no inet_pton here, sorry
        try:
            socket.inet_aton(address)
        except socket.error:
            return False
        return address.count('.') == 3
    except socket.error:  # not a valid address
        return False

    return True

def ipv6_check(address):
    "This validates an ipv6 address"
    # https://stackoverflow.com/questions/319279/how-to-validate-ip-address-in-python
    try:
        socket.inet_pton(socket.AF_INET6, address)
    except socket.error:  # not a valid address
        return False
    return True

def returnFileAsList(filename):
    "This reads a file and returns the contents as a list"
    # https://stackoverflow.com/questions/3277503/how-do-i-read-a-file-line-by-line-into-a-list
    if os.path.exists(filename):
        with open(filename) as f:
            content = f.readlines()
            content = [x.strip() for x in content]
            return content
    return None


def logger(bool):
    "This will log the success/failure result of a command"
    cmd = ' '.join(sys.argv)
    log = open("aggiestack-log.txt", "a")
    if bool:
        log.write(cmd + " --SUCCESS\n")
    else:
        log.write(cmd + " --FAILURE\n")
    log.close()
    return None


def saveConfig(_list, filename):
    "This will save the config files via pickle"
    # https://stackoverflow.com/questions/1047318/easiest-way-to-persist-a-data-structure-to-a-file-in-python
    _dictionary = {}
    for index in range(1, len(_list)):
        _dictionary[_list[index].split()[0]] = _list[index]
    _file = open(filename, "wb")
    pickle.dump(_dictionary, _file)
    _file.close()
    return None


def availableHdwr(filename):
    "This will show the hardware properties of each available physical server"
    if os.path.exists(filename):
        with open(filename, "rb") as f:
            _data = pickle.load(f)
            for key in _data:
                hdwrList = _data[key].split()
                print(key + " " + hdwrList[2] + " " + hdwrList[3] + " " + hdwrList[4])
        return True
    return False


def showData(filename):
    "This will load and display the data in the console"
    # https://stackoverflow.com/questions/1047318/easiest-way-to-persist-a-data-structure-to-a-file-in-python
    if os.path.exists(filename):
        with open(filename, "rb") as f:
            _data = pickle.load(f)
            print(len(_data))
            for key in _data:
                print(_data[key])
        return True
    return False


def fileCheck(_list, numProperties):
    "This will check if config file follows the correct requirements"
    if len(_list[0].split()) != 1:
        return False
    for index in range(1, len(_list)):
        parsedLine = _list[index].split()
        if len(parsedLine) != numProperties:
            return False
    return True

try:
    if sys.argv[1] == "aggiestack":
        if sys.argv[2] == "admin":
            if sys.argv[3] == "show":
                if sys.argv[4] == "hardware":
                    if availableHdwr("hdwr-data.pkl"):
                        logger(True)
                    else:
                        logger(False)
                        print("hdwr-data.pkl does not exist")
                else:
                    logger(False)
                    print("Invalid input. Please double-check your arguments.")
            elif sys.argv[3] == "can_host":
                if os.path.exists("hdwr-data.pkl"):
                    with open("hdwr-data.pkl", "rb") as h:
                        _hdata = pickle.load(h)
                        if sys.argv[4] in _hdata:
                            hList = _hdata[sys.argv[4]].split()
                            if os.path.exists("flavor-data.pkl"):
                                with open("flavor-data.pkl", "rb") as v:
                                    _fdata = pickle.load(v)
                                    if sys.argv[5] in _fdata:
                                        logger(True)
                                        fList = _fdata[sys.argv[5]].split()
                                        if int(hList[2]) >= int(fList[1]) and int(hList[3]) >= int(fList[2]) and int(hList[4]) >= int(fList[3]):
                                            print("yes")
                                        else:
                                            print("no")
                                    else:
                                        logger(False)
                                        print("No such flavor configuration")
                            else:
                                logger(False)
                                print("flavor-data.pkl does not exist")
                        else:
                            logger(False)
                            print("No such physical server")
                else:
                    logger(False)
                    print("hdwr-data.pkl does not exist")
            else:
                logger(False)
                print("Invalid input. Please double-check your arguments.")
        elif sys.argv[2] == "config":
            lineList = returnFileAsList(sys.argv[4])
            createFile = True
            if sys.argv[3] == "--hardware":
                if lineList is not None:
                    if fileCheck(lineList, 5):
                        for index in range(1, len(lineList)):
                            lineSplit = lineList[index].split()
                            if not ipv4_check(lineSplit[1]) or not ipv6_check(lineSplit[1]):
                                createFile = False
                        if createFile:
                            logger(True)
                            saveConfig(lineList, "hdwr-data.pkl")
                        else:
                            logger(False)
                            print("Configuration file contains invalid ip addresses")
                    else:
                        logger(False)
                        print("Configuration file is missing or contains too many properites")
                else:
                    logger(False)
                    print(sys.argv[4] + " does not exist")
            elif sys.argv[3] == "--images":
                if lineList is not None:
                    if fileCheck(lineList, 1):
                        logger(True)
                        saveConfig(lineList, "image-data.pkl")
                    else:
                        logger(False)
                        print("Configuration file is missing or contains too many properites")
                else:
                    logger(False)
                    print(sys.argv[4] + " does not exist")
            elif sys.argv[3] == "--flavors":
                if lineList is not None:
                    if fileCheck(lineList, 4):
                        logger(True)
                        saveConfig(lineList, "flavor-data.pkl")
                    else:
                        logger(False)
                        print("Configuration file is missing or contains too many properties")
                else:
                    logger(False)
                    print(sys.argv[4] + " does not exist")
            else:
                logger(False)
                print("Invalid input. Please double-check your arguments.")
        elif sys.argv[2] == "show":
            if sys.argv[3] == "hardware":
                if showData("hdwr-data.pkl"):
                    logger(True)
                else:
                    logger(False)
                    print("hdwr-data.pkl does not exist")
            elif sys.argv[3] == "images":
                if showData("image-data.pkl"):
                    logger(True)
                else:
                    logger(False)
                    print("image-data.pkl does not exist")
            elif sys.argv[3] == "flavors":
                if showData("flavor-data.pkl"):
                    logger(True)
                else:
                    logger(False)
                    print("flavor-data.pkl does not exist")
            elif sys.argv[3] == "all":
                if showData("hdwr-data.pkl") and showData("flavor-data.pkl") and showData("image-data.pkl"):
                    logger(True)
                else:
                    logger(False)
                    print("Not all data files exist. Please double-check.")
            else:
                logger(False)
                print("Invalid input. Please double-check your arguments.")
        else:
            logger(False)
            print("Invalid input. Please double-check your arguments.")
    else:
        logger(False)
        print("Invalid input. Please double-check your arguments.")
except:
    logger(False)
    print("Please double-check code. An error has occurred")
