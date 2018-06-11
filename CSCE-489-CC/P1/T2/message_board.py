import redis
dir(redis)

r = redis.Redis()

listening = False;
topic = "";

while True:
	try:
		if listening:
			print("sub")
			for item in p.listen():	
				print(item)

		cmd = raw_input('Enter your command: \n')
		print(cmd)
		cmd_parts = cmd.split(" ")
		print(cmd_parts)
		if cmd_parts[0] == "select":
			topic = cmd_parts[1]
		elif cmd_parts[0] == "read":
			if topic == "":
				print("No board was selected")
			else:
				res = r.get(topic)
				print res
		elif cmd_parts[0] == "write":
			if topic == "":
				print("No board was selected")
			else:
				to_pub = ' '.join(cmd_parts[1:])
				r.append(topic, to_pub+'\n')
				res = r.publish(topic, to_pub) 
				print res
		elif cmd_parts[0] == "listen":
			if topic == "":
				print("No board was selected")
			else:
				listening = True;
				p = r.pubsub()
				res = p.subscribe(topic) 
				print res
		elif cmd_parts[0] == "quit":
			break;
		else:
			print("Input format wrong");

	except KeyboardInterrupt:
		listening = False

