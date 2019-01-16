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

def getIndexAddress(word,i):
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
	
	
		class_name = "VOID"
		subclass_name = "VOID"
		address_name = "VOID"
		name_name = "VOID"
		type_name = "VOID"
	
		if state==0:
			#Class match
			index = matchClassName(word,i)
			if index < 0:
				if i < (len(word)-2):
					i+=1
					continue
				else:
					break
			class_name = Class_str[index]
			splitted = class_name.split(" ")
			i += len(splitted)
			state = 1
		
		if state==1:
			#Subclass match
			subclass_name = getSubclassName(word,i)
			state = 2
		
		if state==2:
			#address_name
			index = getIndexAddress(word,i)
			address_name = word[index]
			i = index+1
			state = 3
			
		if state==3:
			#name_name
			name_name = getNameName(word,i)
			state = 4
			
		if state==4:
			#type_name
			index = getTypeIndex(word,i)
			type_name = word[index]
			i = index+1
			state = 0		
	
		class_name = class_name.replace(" ", "_")
		subclass_name = subclass_name.replace(" ", "_")
		address_name = address_name.replace(" ", "_")
		name_name = name_name.replace(" ", "_")
		type_name = type_name.replace(" ", "_")
		
		class_name = class_name.replace("%", "Percent")
		subclass_name = subclass_name.replace("%", "Percent")
		address_name = address_name.replace("%", "Percent")
		name_name = name_name.replace("%", "Percent")
		type_name = type_name.replace("%", "Percent")
		
		class_name = class_name.replace("/", "_")
		subclass_name = subclass_name.replace("/", "_")
		address_name = address_name.replace("/", "_")
		name_name = name_name.replace("/", "_")
		type_name = type_name.replace("/", "_")
		
		line = class_name + "\t" + subclass_name + "\t" + address_name + "\t" + name_name + "\t" + type_name + "\n"
	
		res += line
	
	f = open("test.txt","w")
	f.write(res)
	
replaceWhiteSpecesRegion("bq78350.txt")