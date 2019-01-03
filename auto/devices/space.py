def replaceWhiteSpecesRegion(file_path):


	res = ""
	with open(file_path) as fp:  
		line = fp.readline()
		cnt = 1
		while line:
			
			line = line.rstrip("\n")
			line = line.rstrip("\r")
			
			splitted = line.split()

			print(line)
			print(splitted)

			res += splitted[0] + "\t"
			res += splitted[1] + "\t"
			res += splitted[2] + "\t"
			res += splitted[3] + "\t"

			for i in range(4,len(splitted)-2):
				res += splitted[i] + " "
				
			res += "\t" + splitted[-2] + splitted[-1] + "\n"

			line = fp.readline()

	
	
	f = open("test.txt","w")
	f.write(res)
	
replaceWhiteSpecesRegion("nvic.txt")