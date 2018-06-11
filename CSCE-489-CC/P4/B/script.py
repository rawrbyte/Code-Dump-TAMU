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
        with open(filename) as _f:
            content = _f.readlines()
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
    for _index in range(1, len(_list)):
        _dictionary[_list[_index].split()[0]] = _list[_index]
    _file = open(filename, "wb")
    pickle.dump(_dictionary, _file)
    _file.close()
    return None

def availableHdwr(filename):
    "This will show the hardware properties of each available physical server"
    if os.path.exists(filename):
        with open(filename, "rb") as _f:
            _data = pickle.load(_f)
            for _key in _data:
                hdwrList = _data[_key].split()
                print(_key + " " + hdwrList[3] + " " + hdwrList[4] + " " + hdwrList[5])
        return True
    return False

def showInstances(filename):
    "This will show the instances running"
    if os.path.exists(filename):
        with open(filename, "rb") as _f:
            _data = pickle.load(_f)
            for _key in _data:
                _instanceList = _data[_key].split()
                print(_key + " " + _instanceList[1] + " " + _instanceList[2])
        return True
    return False

def showData(filename):
    "This will load and display the data in the console"
    # https://stackoverflow.com/questions/1047318/easiest-way-to-persist-a-data-structure-to-a-file-in-python
    if os.path.exists(filename):
        with open(filename, "rb") as _f:
            _data = pickle.load(_f)
            print(len(_data))
            for _key in _data:
                print(_data[_key])
        return True
    return False

def saveData(filename, data):
    "This method saves the reconfigured dictionary"
    _file = open(filename, "wb")
    pickle.dump(data, _file)
    _file.close()

def fileExist(filename):
    "This method will check if file exists"
    if os.path.exists(filename):
        return True
    else:
        logger(False)
        print(filename + " does not exist")
        return False

def fileCheck(_list, numProperties):
    "This will check if config file follows the correct requirements"
    if len(_list[0].split()) != 1:
        return False
    for _index in range(1, len(_list)):
        parsedLine = _list[_index].split()
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

def removeMachine():
    "This will remove the physical server from the datacenter"
    if os.path.exists("hdwr-data.pkl"):
        with open("hdwr-data.pkl", "rb") as _h:
            if os.path.exists("available-hdwr-data.pkl"):
                with open("available-hdwr-data.pkl", "rb") as _ah:
                    _hdata = pickle.load(_h)
                    _ahdata = pickle.load(_ah)
                    if sys.argv[4] in _hdata:
                        del _hdata[sys.argv[4]]
                        if sys.argv[4] in _ahdata:
                            del _ahdata[sys.argv[4]]
                            saveData("hdwr-data.pkl", _hdata)
                            saveData("available-hdwr-data.pkl", _ahdata)
                            logger(True)
                        else:
                            logger(False)
                            print("Selected physical server does not exist")
                    else:
                        logger(False)
                        print("Selected physical server does not exist")
            else:
                logger(False)
                print("available-hdwr-data.pkl does not exist")
    else:
        logger(False)
        print("hdwr-data.pkl does not exist")

try:
    if sys.argv[1] == "aggiestack":
        if sys.argv[2] == "admin":
            if sys.argv[3] == "add":
                if sys.argv[4] == "-mem":
                    if sys.argv[6] == "-disk":
                        if sys.argv[8] == "-vcpus":
                            if sys.argv[10] == "-ip":
                                if sys.argv[12] == "-rack":
                                    mem = sys.argv[5]
                                    disk = sys.argv[7]
                                    vcpus = sys.argv[9]
                                    ip = sys.argv[11]
                                    rack = sys.argv[13]
                                    machine = sys.argv[14]
                                    newMachine = machine + " " + rack + " " + ip + " " + str(mem) + " " + str(disk) + " " + str(vcpus)
                                    if fileExist("hdwr-data.pkl"):
                                        with open("hdwr-data.pkl", "rb") as h:
                                            if fileExist("available-hdwr-data.pkl"):
                                                with open("available-hdwr-data.pkl", "rb") as ah:
                                                    _hdata = pickle.load(h)
                                                    _ahdata = pickle.load(ah)
                                                    if machine in _hdata or machine in _ahdata:
                                                        logger(False)
                                                        print("Physical server with the same name already exists")
                                                    else:
                                                        _ahdata[machine] = newMachine
                                                        _hdata[machine] = newMachine
                                                        saveData("available-hdwr-data.pkl", _ahdata)
                                                        saveData("hdwr-data.pkl", _hdata)
                                                        logger(True)
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
                else:
                    logger(False)
                    print("Invalid input. Please double-check your arguments.")
            elif sys.argv[3] == "remove":
                if os.path.exists("instance-data.pkl"):
                    with open("instance-data.pkl", "rb") as ii:
                        _iidata = pickle.load(ii)
                        hosting = False
                        for key in _iidata:
                            if sys.argv[4] == _iidata[key].split()[3]:
                                hosting = True
                        if not hosting:
                            removeMachine()
                        else:
                            logger(False)
                            print("Cannot remove physical server. Server hosting virtual machines")
                else:
                    removeMachine()
            elif sys.argv[3] == "evacuate":
                if fileExist("instance-data.pkl"):
                    with open("instance-data.pkl", "rb") as ii:
                        _iidata = pickle.load(ii)
                        if fileExist("flavor-data.pkl"):
                            with open("flavor-data.pkl", "rb") as f:
                                newInstanceDictionary = {}
                                _fdata = pickle.load(f)
                                for ikey in _iidata:
                                    success = True
                                    if fileExist("available-hdwr-data.pkl"):
                                        with open("available-hdwr-data.pkl", "rb") as ah:
                                            _ahdata = pickle.load(ah)
                                            instanceSplit = _iidata[ikey].split()
                                            instanceFlavor = instanceSplit[2]
                                            instanceHdwr = instanceSplit[3]
                                            if instanceHdwr in _ahdata:
                                                newHdwrName = ""
                                                hdwrSplit = _ahdata[instanceHdwr].split()
                                                currRack = hdwrSplit[1]
                                                for ahkey in _ahdata:
                                                    newHdwrSplit = _ahdata[ahkey].split()
                                                    if newHdwrSplit[1] != sys.argv[4] and canHost(newHdwrSplit[0], instanceFlavor):
                                                        newHdwrName = newHdwrSplit[0]
                                                        break
                                                if newHdwrName == "":
                                                    success = False
                                                else:
                                                    newHdwrSplit = _ahdata[newHdwrName].split()
                                                    oldHdwrSplit = _ahdata[instanceHdwr].split()
                                                    flavorSplit = _fdata[instanceFlavor].split()

                                                    oldHdwrRack = oldHdwrSplit[1]
                                                    oldHdwrIP = oldHdwrSplit[2]
                                                    oldHdwrMem = int(oldHdwrSplit[3])
                                                    oldHdwrDisk = int(oldHdwrSplit[4])
                                                    oldHdwrCore = int(oldHdwrSplit[5])

                                                    newHdwrRack = newHdwrSplit[1]
                                                    newHdwrIP = newHdwrSplit[2]
                                                    newHdwrMem = int(newHdwrSplit[3])
                                                    newHdwrDisk = int(newHdwrSplit[4])
                                                    newHdwrCore = int(newHdwrSplit[5])

                                                    flavorMem = int(flavorSplit[1])
                                                    flavorDisk = int(flavorSplit[2])
                                                    flavorCore = int(flavorSplit[3])

                                                    newHdwrMem = newHdwrMem - flavorMem
                                                    newHdwrDisk = newHdwrDisk - flavorDisk
                                                    newHdwrCore = newHdwrCore - flavorCore

                                                    oldHdwrMem = oldHdwrMem + flavorMem
                                                    oldHdwrDisk = oldHdwrDisk + flavorDisk
                                                    oldHdwrCore = oldHdwrCore + flavorCore

                                                    newHdwr = newHdwrName + " " + newHdwrRack + " " + newHdwrIP + " " + str(newHdwrMem) + " " + str(newHdwrDisk) + " " + str(newHdwrCore)
                                                    oldHdwr = instanceHdwr + " " + oldHdwrRack + " " + oldHdwrIP + " " + str(oldHdwrMem) + " " + str(oldHdwrDisk) + " " + str(oldHdwrCore)

                                                    _ahdata[newHdwrName] = newHdwr
                                                    _ahdata[instanceHdwr] = oldHdwr

                                                    newInstanceDictionary[instanceSplit[0]] = instanceSplit[0] + " " + instanceSplit[1] + " " + instanceSplit[2] + " " + newHdwrName

                                                    saveData("available-hdwr-data.pkl", _ahdata)
                                            else:
                                                success = False
                                if success:
                                    saveData("instance-data.pkl", newInstanceDictionary)
                                    logger(True)
                                else:
                                    logger(False)
                                    print("Rack evacuation failed")
            elif sys.argv[3] == "show":
                if sys.argv[4] == "instances":
                    if fileExist("instance-data.pkl"):
                        with open("instance-data.pkl", "rb") as f:
                            _data = pickle.load(f)
                            for key in _data:
                                instanceList = _data[key].split()
                                print(key + " " + instanceList[3])
                        logger(True)
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
                if fileExist("instance-data.pkl"):
                    with open("instance-data.pkl", "rb") as ii:
                        _iidata = pickle.load(ii)
                        if sys.argv[4] in _iidata:
                            instanceSplit = _iidata[sys.argv[4]].split()
                            instanceFlavor = instanceSplit[2]
                            instanceHdwr = instanceSplit[3]
                            if fileExist("flavor-data.pkl"):
                                with open("flavor-data.pkl", "rb") as f:
                                    _fdata = pickle.load(f)
                                    if fileExist("available-hdwr-data.pkl"):
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
                                                saveData("available-hdwr-data.pkl", _ahdata)

                                                del _iidata[sys.argv[4]]
                                                saveData("instance-data.pkl", _iidata)
                                                logger(True)
                                            else:
                                                logger(False)
                                                print("Physical server does not exist")
                        else:
                            logger(False)
                            print("Instance does not exist")
            elif sys.argv[3] == "list":
                if showInstances("instance-data.pkl"):
                    logger(True)
                else:
                    logger(False)
                    print("instance-data.pkl does not exist")
            elif sys.argv[3] == "create":
                if sys.argv[4] == "--image":
                    if fileExist("image-data.pkl"):
                        with open("image-data.pkl", "rb") as i:
                            _idata = pickle.load(i)
                            if sys.argv[5] in _idata:
                                if sys.argv[6] == "--flavor":
                                    if fileExist("flavor-data.pkl"):
                                        with open("flavor-data.pkl", "rb") as f:
                                            _fdata = pickle.load(f)
                                            if sys.argv[7] in _fdata:
                                                if fileExist("available-hdwr-data.pkl"):
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
                                                                            saveData("available-hdwr-data.pkl", _ahdata)

                                                                            _iidata[sys.argv[8]] = instanceList[1]
                                                                            saveData("instance-data.pkl", _iidata)

                                                                            logger(True)
                                                                        else:
                                                                            logger(False)
                                                                            print("Physical server does not exist")
                                                            else:
                                                                if hdwrName in _ahdata:
                                                                    _ahdata[hdwrName] = newHdwr
                                                                    saveData("available-hdwr-data.pkl", _ahdata)
                                                                    saveConfig(instanceList, "instance-data.pkl")
                                                                    logger(True)
                                                                else:
                                                                    logger(False)
                                                                    print("Physical server does not exist")
                                            else:
                                                logger(False)
                                                print("Flavor does not exist")
                                else:
                                    logger(False)
                                    print("Invalid input. Please double-check your arguments.")
                            else:
                                logger(False)
                                print("Image does not exist")
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
