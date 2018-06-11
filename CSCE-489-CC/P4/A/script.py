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
                print(key + " " + hdwrList[3] + " " + hdwrList[4] + " " + hdwrList[5])
        return True
    return False

def showInstances(filename):
    "This will show the instances running"
    if os.path.exists(filename):
        with open(filename, "rb") as f:
            _data = pickle.load(f)
            for key in _data:
                _instanceList = _data[key].split()
                print(key + " " + _instanceList[1] + " " + _instanceList[2])
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

def canHost(hdwr, flavor):
    "This will check if hdwr can host flavor"
    if os.path.exists("available-hdwr-data.pkl"):
        with open("available-hdwr-data.pkl", "rb") as _h:
            _hdata = pickle.load(_h)
            if hdwr in _hdata:
                hList = _hdata[hdwr].split()
                if os.path.exists("flavor-data.pkl"):
                    with open("flavor-data.pkl", "rb") as _f:
                        _fdata = pickle.load(_f)
                        if flavor in _fdata:
                            fList = _fdata[flavor].split()
                            if int(hList[3]) >= int(fList[1]) and int(hList[4]) >= int(fList[2]) and int(hList[5]) >= int(fList[3]):
                                return True
                            else:
                                return False
                        else:
                            print("No such flavor configuration")
                            return False
                else:
                    print("flavor-data.pkl does not exist")
                    return False
            else:
                print("No such physical server")
                return False
    else:
        print("hdwr-data.pkl does not exist")
        return False

try:
    if sys.argv[1] == "aggiestack":
        if sys.argv[2] == "admin":
            if sys.argv[3] == "show":
                if sys.argv[4] == "instances":
                    if os.path.exists("instance-data.pkl"):
                        with open("instance-data.pkl", "rb") as f:
                            _data = pickle.load(f)
                            for key in _data:
                                instanceList = _data[key].split()
                                print(key + " " + instanceList[3])
                        logger(True)
                    else:
                        logger(False)
                        print("instance-data.pkl does not exist")
                elif sys.argv[4] == "hardware":
                    if availableHdwr("available-hdwr-data.pkl"):
                        logger(True)
                    else:
                        logger(False)
                        print("hdwr-data.pkl does not exist")
                else:
                    logger(False)
                    print("Invalid input. Please double-check your arguments.")
            elif sys.argv[3] == "can_host":
                if canHost(sys.argv[4], sys.argv[5]):
                    print("yes")
                    logger(True)
                else:
                    print("no")
                    logger(False)
            else:
                logger(False)
                print("Invalid input. Please double-check your arguments.")
        elif sys.argv[2] == "config":
            lineList = returnFileAsList(sys.argv[4])
            createFile = True
            if sys.argv[3] == "--hardware":
                if len(lineList[0].split()) == 1:
                    rackList = []
                    rackSize = int(lineList[0]) + 1
                    for index in range(0, rackSize):
                        rackList.append(lineList[index])
                    if len(lineList[rackSize].split()) == 1:
                        hdwrList = []
                        hdwrSize = rackSize + int(lineList[rackSize]) + 1
                        for index in range(rackSize, hdwrSize):
                            hdwrList.append(lineList[index])
                        if hdwrList is not None and rackList is not None:
                            if fileCheck(hdwrList, 6) and fileCheck(rackList, 2):
                                for index in range(1, len(hdwrList)):
                                    lineSplit = hdwrList[index].split()
                                    if not ipv4_check(lineSplit[2]) and not ipv6_check(lineSplit[2]):
                                        createFile = False
                                if createFile:
                                    logger(True)
                                    saveConfig(hdwrList, "hdwr-data.pkl")
                                    saveConfig(hdwrList, "available-hdwr-data.pkl")
                                    saveConfig(rackList, "rack-data.pkl")
                                else:
                                    logger(False)
                                    print("Configuration file contains invalid ip addresses")
                            else:
                                logger(False)
                                print("Configuration file is missing or contains too many properites")
                        else:
                            logger(False)
                            print(sys.argv[4] + " does not exist")
                    else:
                        logger(False)
                        print("Configuration file does not contain hdwr count")
                else:
                    logger(False)
                    print("Configuration file does not contain rack count")
            elif sys.argv[3] == "--images":
                if lineList is not None:
                    if fileCheck(lineList, 3):
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
                if showData("rack-data.pkl") and showData("hdwr-data.pkl"):
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
                if showData("rack-data.pkl") and showData("hdwr-data.pkl") and showData("flavor-data.pkl") and showData("image-data.pkl"):
                    logger(True)
                else:
                    logger(False)
                    print("Not all data files exist. Please double-check.")
            else:
                logger(False)
                print("Invalid input. Please double-check your arguments.")
        elif sys.argv[2] == "server":
            if sys.argv[3] == "delete":
                if os.path.exists("instance-data.pkl"):
                    with open("instance-data.pkl", "rb") as ii:
                        _iidata = pickle.load(ii)
                        if sys.argv[4] in _iidata:
                            instanceSplit = _iidata[sys.argv[4]].split()
                            instanceFlavor = instanceSplit[2]
                            instanceHdwr = instanceSplit[3]
                            if os.path.exists("flavor-data.pkl"):
                                with open("flavor-data.pkl", "rb") as f:
                                    _fdata = pickle.load(f)
                                    if os.path.exists("available-hdwr-data.pkl"):
                                        with open("available-hdwr-data.pkl", "rb") as ah:
                                            _ahdata = pickle.load(ah)

                                            hdwrSplit = _ahdata[instanceHdwr].split()
                                            hdwrRack = hdwrSplit[1]
                                            hdwrIP = hdwrSplit[2]
                                            hdwrMem = int(hdwrSplit[3])
                                            hdwrDisk = int(hdwrSplit[4])
                                            hdwrCore = int(hdwrSplit[5])
                                            flavorSplit = _fdata[instanceFlavor].split()
                                            flavorName = flavorSplit[0]
                                            flavorMem = int(flavorSplit[1])
                                            flavorDisk = int(flavorSplit[2])
                                            flavorCore = int(flavorSplit[3])

                                            hdwrMem = hdwrMem + flavorMem
                                            hdwrDisk = hdwrDisk + flavorDisk
                                            hdwrCore = hdwrCore + flavorCore

                                            newHdwr = instanceHdwr + " " + hdwrRack + " " + hdwrIP + " " + str(hdwrMem) + " " + str(hdwrDisk) + " " + str(hdwrCore)

                                            if instanceHdwr in _ahdata:
                                                _ahdata[instanceHdwr] = newHdwr
                                                _file = open("available-hdwr-data.pkl", "wb")
                                                pickle.dump(_ahdata, _file)
                                                _file.close()

                                                del _iidata[sys.argv[4]]
                                                _file = open("instance-data.pkl", "wb")
                                                pickle.dump(_iidata, _file)
                                                _file.close()
                                                logger(True)
                                            else:
                                                logger(False)
                                                print("Physical server does not exist")
                                    else:
                                        logger(False)
                                        print("available-hdwr-data.pkl does not exist")
                            else:
                                logger(False)
                                print("flavor-data.pkl does not exist")
                        else:
                            logger(False)
                            print("Instance does not exist")
                else:
                    logger(False)
                    print("instance-data.pkl does not exist")
            elif sys.argv[3] == "list":
                if showInstances("instance-data.pkl"):
                    logger(True)
                else:
                    logger(False)
                    print("instance-data.pkl does not exist")
            elif sys.argv[3] == "create":
                if sys.argv[4] == "--image":
                    if os.path.exists("image-data.pkl"):
                        with open("image-data.pkl", "rb") as i:
                            _idata = pickle.load(i)
                            if sys.argv[5] in _idata:
                                if sys.argv[6] == "--flavor":
                                    if os.path.exists("flavor-data.pkl"):
                                        with open("flavor-data.pkl", "rb") as f:
                                            _fdata = pickle.load(f)
                                            if sys.argv[7] in _fdata:
                                                if os.path.exists("available-hdwr-data.pkl"):
                                                    with open("available-hdwr-data.pkl", "rb") as ah:
                                                        _ahdata = pickle.load(ah)
                                                        hdwrName = ""
                                                        for key in _ahdata:
                                                            if canHost(key, sys.argv[7]):
                                                                hdwrName = key
                                                                break

                                                        if hdwrName == "":
                                                            logger(False)
                                                            print("No physical server available. Resources have been exhausted")
                                                        else:
                                                            hdwrSplit = _ahdata[hdwrName].split()
                                                            hdwrRack = hdwrSplit[1]
                                                            hdwrIP = hdwrSplit[2]
                                                            hdwrMem = int(hdwrSplit[3])
                                                            hdwrDisk = int(hdwrSplit[4])
                                                            hdwrCore = int(hdwrSplit[5])
                                                            flavorSplit = _fdata[sys.argv[7]].split()
                                                            flavorName = flavorSplit[0]
                                                            flavorMem = int(flavorSplit[1])
                                                            flavorDisk = int(flavorSplit[2])
                                                            flavorCore = int(flavorSplit[3])

                                                            hdwrMem = hdwrMem - flavorMem
                                                            hdwrDisk = hdwrDisk - flavorDisk
                                                            hdwrCore = hdwrCore - flavorCore

                                                            newHdwr = hdwrName + " " + hdwrRack + " " + hdwrIP + " " + str(hdwrMem) + " " + str(hdwrDisk) + " " + str(hdwrCore)

                                                            instanceList = ['1', sys.argv[8] + " " + sys.argv[5] + " " + sys.argv[7] + " " + hdwrName]
                                                            if os.path.exists("instance-data.pkl"):
                                                                with open("instance-data.pkl", "rb") as ii:
                                                                    _iidata = pickle.load(ii)
                                                                    if sys.argv[8] in _iidata:
                                                                        logger(False)
                                                                        print("Instance already running")
                                                                    else:
                                                                        if hdwrName in _ahdata:
                                                                            _ahdata[hdwrName] = newHdwr
                                                                            _file = open("available-hdwr-data.pkl", "wb")
                                                                            pickle.dump(_ahdata, _file)
                                                                            _file.close()

                                                                            _iidata[sys.argv[8]] = instanceList[1]
                                                                            _file = open("instance-data.pkl", "wb")
                                                                            pickle.dump(_iidata, _file)
                                                                            _file.close()

                                                                            logger(True)
                                                                        else:
                                                                            logger(False)
                                                                            print("Physical server does not exist")
                                                            else:
                                                                if hdwrName in _ahdata:
                                                                    _ahdata[hdwrName] = newHdwr
                                                                    _file = open("available-hdwr-data.pkl", "wb")
                                                                    pickle.dump(_ahdata, _file)
                                                                    _file.close()
                                                                    saveConfig(instanceList, "instance-data.pkl")
                                                                    logger(True)
                                                                else:
                                                                    logger(False)
                                                                    print("Physical server does not exist")
                                                else:
                                                    logger(False)
                                                    print("available-hdwr-data.pkl does not exist")
                                            else:
                                                logger(False)
                                                print("Flavor does not exist")
                                    else:
                                        logger(False)
                                        print("flavor-data.pkl does not exist")
                                else:
                                    logger(False)
                                    print("Invalid input. Please double-check your arguments.")
                            else:
                                logger(False)
                                print("Image does not exist")
                    else:
                        logger(False)
                        print("image-data.pkl does not exist")
                else:
                    logger(False)
                    print("Invalid input. Please double-check your arguments.")
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
