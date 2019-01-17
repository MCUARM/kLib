Class_str = [	"Calibration",
				"Settings",
				"Protections",
				"Permanent Fail",
				"Charge Algorithm",
				"Fuel Gauging",
				"Power",
				"PF Status",
				"Black Box",
				"System Data",
				"SBS Configuration",
				"LED Support",
				"Lifetimes",
				"GPIO"]


def matchClassName(word, i):
	
	index=-1
	for j in range(0,len(Class_str)):
		print(Class_str[j])
		temp = Class_str[j].split(" ")
		print(len(temp))
		matched = True
		for k in range(0,len(temp)):
			
		
			if temp[k] != word[i+k]:
				matched = False
				print(temp[k] + " != " + word[i+k] + " NOT MATCHED")
		if matched:
			index = j
			print("Matched")
			break
	return index

def getSubclassName(word,i):
	j = getIndexAddress(word,i)
	
	res = ""
	for k in range(i,j):
		if k != i:
			res += " "
		res += word[k]
	return res
	
def getNameName(word,i):
	j = getTypeIndex(word,i)
	
	res = ""
	for k in range(i,j):
		if k != i:
			res += " "
		res += word[k]
	return res

def getIndexOfHexNumber(word,i):
	j = i
	while "0x" not in word[j]:
		j+=1
	return j

def getTypeIndex(word,i):
	matched=False
	while not matched:
		if word[i][0] == "U":
			matched = True
		if word[i][0] == "I":
			matched = True		
		if word[i][0] == "F":
			matched = True		
		if word[i][0] == "H":
			matched = True		
		if word[i][0] == "S":
			matched = True
		if not matched:
			i+=1
			continue
		if word[i][1].isdigit():
			return i
		matched = False
		i+=1
		
def assertString(string):
	string = string.replace(" ", "_")
	string = string.replace(".", "")
	string = string.replace("/", "_")
	string = string.replace("%", "Percent")
	string = string.replace("-", "_")

	return string

def replaceWhiteSpecesRegion(file_path):



					
			

	res = ""
	word = [];
	with open(file_path) as fp:  
		line = fp.readline()
		cnt = 1
		
				
		while line:
			
			line = line.rstrip("\n")
			line = line.rstrip("\r")
			
			
			splitted = line.split()
		
			for i in range(0,len(splitted)):
				word.append(splitted[i])
			
			line = fp.readline()
	
	state=0;
	i=0
	while (i<len(word)):
	
	
		cmd_value = "VOID"
		cmd_name = "VOID"
		access = "VOID"
	
		if state==0:
			#cmd value match
			index = getIndexOfHexNumber(word,i)
			if index < 0:
				if i < (len(word)-2):
					i+=1
					continue
				else:
					break
			
			cmd_value = word[index]
			i = index+1
			state = 1
	
		if state==1:
			#access match
			access = word[i]
			i+=1
			state = 2
	
		if state==2:
			#cmd_name match
			cmd_name = word[i]
			i+=1
			state = 0
			if not (i+7) < len(word):
				i+=10

			
		cmd_value = assertString(cmd_value)
		cmd_name = assertString(cmd_name)
	
	
		line =  cmd_value + "\t"
		line += access + "\t"
		line += cmd_name + "\n"

	
		res += line
	
	f = open("test.txt","w")
	f.write(res)
	
replaceWhiteSpecesRegion("MA_commands.txt")