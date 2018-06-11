from mongo_connect import connectMongo
from glob import iglob
import constants
import pymongo
import json
import os.path
import pprint

collection = connectMongo()

print('----------WQ1----------')
for fname in iglob(os.path.expanduser('dummy-fitness.json')):
    with open(fname) as fin:
        value = json.load(fin)
        WQ1 = collection.insert(value)
for data in WQ1:
    pprint.pprint(data)

print('----------WQ2----------')
for fname in iglob(os.path.expanduser('user1001-new.json')):
    with open(fname) as fin:
        value = json.load(fin)
        WQ2 = collection.update({'uid': 1001}, {'$set': value})
for data in WQ2:
    pprint.pprint(data)

print('----------RQ1----------')
RQ1 = collection.count()
pprint.pprint(RQ1)

print('----------RQ2----------')
RQ2 = collection.find({'tags': 'active'})
for data in RQ2:
    pprint.pprint(data)

print('----------RQ3----------')
RQ3 = collection.find({'goal.activityGoal': {'$gt': '60min', '$ne': 'NA'}})
for data in RQ3:
    pprint.pprint(data)

print('----------RQ4----------')
RQ4 = collection.aggregate([{'$unwind': '$activityDuration'}, {'$group':{'_id': '$uid', 'total': {'$exists':{'$sum': '$activityDuration'}}}}])
for data in RQ4:
    pprint.pprint(data)

print('----------Clear----------')
DELETE = collection.delete_many({})
pprint.pprint(DELETE)
