from xml.dom import minidom
from xml.dom.minidom import Node
import re

from xlrd import open_workbook
from lxml import etree
import os


def replaceCodeRegion(file_path,region_name,new_region_content):
	#pragma region
	regex = "// region " + region_name + ".*" + "// endregion " + region_name
	
	file_content = open(file_path, 'r').read();
	old_region_content = str(re.search(regex, file_content,re.DOTALL)[0])

	
	file_content_list = file_content.split(old_region_content,1)
	file_content = file_content_list[0]
	file_content += "// region " + region_name + "\n\n"
	file_content += new_region_content
	file_content += "\n\n// endregion " + region_name
	file_content += file_content_list[1]
	f = open(file_path,"w")
	f.write(file_content)	


def updateLicenseText():
	license = getLicenseString();
	
	dir = "../inc/"
	files = []
	for file in os.listdir(dir):
		if file.endswith(".h"):
			files.append(file)
		
	for file in files:
		file_content = open(dir + file, 'r').read();
		file_content = file_content.split("#ifndef",1)[1]
		file_content = license + "\n\n" + "#ifndef" + file_content
		f = open(dir + file,"w")
		f.write(file_content)
		
	dir = "../src/"
	files = []
	for file in os.listdir(dir):
		if file.endswith(".cpp"):
			files.append(file)
		
	for file in files:
		file_content = open(dir + file, 'r').read();
		file_content = file_content.split("#include",1)[1]
		file_content = license + "\n\n" + "#include" + file_content
		f = open(dir + file,"w")
		f.write(file_content)
		
		


def formatHex(hex_str):
	
	tmp = removeWhiteSigns(hex_str.upper())
	tmp = tmp.replace("X","x")
	n = len(tmp)
	
	res = ""
	for i in range(0,2):
		res += tmp[i]
	for i in range(0,10-n):
		res += "0"
	for i in range(2,n):
		res += tmp[i]
		
	return res
	
def removeWhiteSigns(str):
	res = ""
	
	for c in str:
		if ord(c) > 32 and ord(c) < 127:
			res += c
	return res
def getCellValuesList(sheet,row,col):
	return str(sheet.cell(row,col).value).split()	
def getCellValue(sheet,row,col):
	return removeWhiteSigns(str(sheet.cell(row,col).value))




def xls2xml():

	filesDir = 'devices/';
	root = etree.Element("devices")
	
	for file in os.listdir("devices/"):
		if file.endswith(".xlsx"):

			wb = open_workbook(filesDir + file)



			device = None
			for sheet in wb.sheets():
				number_of_rows = sheet.nrows
				number_of_columns = sheet.ncols
				
				
				
				if sheet.name == "AFM":
				
					if number_of_columns < 16:
						continue
					if number_of_rows < 2:
						continue
						
					
					if device == None:	
						device = etree.SubElement(root, "device", name=getCellValue(sheet,0,1))


					for row in range(2, number_of_rows):

						for col in range(1,number_of_columns):
							value = getCellValue(sheet,row,col)
							if not value or value.isspace():
								continue
								
							af = etree.SubElement(device, "AFM")
							af.set('pinName',getCellValue(sheet,row,0))
							af.set('number',str(col-1))
							af.set('value',getCellValue(sheet,row,col));

				if "DMA" in sheet.name:
				
					if number_of_columns < 9:
						continue
					if number_of_rows < 10:
						continue
						
					
					if device == None:	
						device = etree.SubElement(root, "device", name=getCellValue(sheet,0,1))


					for row in range(2, number_of_rows):

						for col in range(1,number_of_columns):
						
							for value in getCellValuesList(sheet,row,col):
								if not value or value.isspace():
									continue
								
								af = etree.SubElement(device, "DMA")
								af.set('name',sheet.name)
								af.set('channel',str(row-2))
								af.set('stream',str(col-1))
								af.set('value',value);

				

				if sheet.name == "Peripherals":
					
					if number_of_columns < 3:
						continue
					if number_of_rows < 2:
						continue
						
					if device == None:	
						device = etree.SubElement(root, "device", name=getCellValue(sheet,0,1))
						
					for row in range(2, number_of_rows):
						periph = etree.SubElement(device, 'PERIPHERAL',name=getCellValue(sheet,row,0))
						periph.set('address',getCellValue(sheet,row,1))
						periph.set('rccEnableBit',str(int(float(getCellValue(sheet,row,2)))))
						
				if sheet.name == "Vector table":
					
					if number_of_columns < 6:
						continue
					if number_of_rows < 2:
						continue
						
					if device == None:	
						device = etree.SubElement(root, "device", name=getCellValue(sheet,0,1))
						
					
					for row in range(2, number_of_rows):

						nvic = etree.SubElement(device, 'NVIC',name=getCellValue(sheet,row,3))
						nvic.set('description',(str(sheet.cell(row,4).value)))
						nvic.set('position',str(int(float(getCellValue(sheet,row,0)))))
						nvic.set('address',getCellValue(sheet,row,5))
				
				
	tree = etree.ElementTree(root)
	tree.write('devices.xml',pretty_print=True)
				

def getHeaderOpener(header_name):
	return str("#ifndef "+header_name+"\n"+"#define "+header_name+"\n\n")
def getHeaderCloser(header_name):
	return str("\n\n#endif  //End of "+header_name+"\n")
def getLicenseString():
	str = open('License.txt', 'r').read()
	return str
	

def getTimerSetupCode(OC_number):
	oc_num = int(OC_number)
	res =  ((oc_num-1) & 0x00000003) << 27
	if oc_num > 2:
		res |= 0x20000000
	if (oc_num == 2) or (oc_num == 4):
		res |= 0x40000000
	return hex(res)
def getUsartSetupCode(enable_rx,enable_tx):
	res = 0
	if enable_rx:
		res |= 4
	if enable_tx:
		res |=8
	res = res << 25
	return hex(res)
def getHardwareSetupCode(user_code,peripheral_clock_enable_bit_position,peripheral_address,gpio_output_type,gpio_mode,alternate_function,gpio_pin):

	RCC_APBx_ENR_byte_offset = int(int(peripheral_clock_enable_bit_position)/8)
	

	res =  ((int(user_code) & 0x0000001F) << 27 )
	res |= ((int(peripheral_clock_enable_bit_position) & 0x00000007) << 24 )
	res |= ((int(RCC_APBx_ENR_byte_offset) & 0x00000003) << 22 )
	res |= ((int(peripheral_address,16) & 0x0001FC00) << 5 )
	res |= ((int(gpio_output_type) & 0x00000001) << 14 )
	res |= ((int(gpio_mode) & 0x00000003) << 12 )
	res |= ((int(alternate_function) & 0x0000000F) << 8 )
	res |= (((ord(gpio_pin[0]) - 0x41) & 0x0000000F) << 4)
	res |= int(gpio_pin[1:]) 

	return hex(res)
def getPlatformCondition(device_tag):
	return str("#if (kLib_config_PLATFORM == kLib_"+getName(device_tag)+")\n\n")
def getEndIfStr():
	return str("#endif\n")
def grabTags(parent,tag_name):
	return parent.getElementsByTagName(tag_name)
def getAttribute(tag,attribute_name):
	return str(tag.attributes[attribute_name].value)
def getValue(tag):
	return getAttribute(tag,'value')
def getAllDMAchannelTags(dev,DMA,stream):
	res = []
	for channel in grabTags(dev,"DMA"):
		if getName(DMA) == getName(channel):
			if int(getAttribute(channel,'stream')) == stream:
				res.append(channel)
	return res
def getDMAchannelTags(dev,DMA,stream,channel_num):
	res = []
	for channel in grabTags(dev,"DMA"):
		if getName(DMA) == getName(channel):
			if int(getAttribute(channel,'stream')) == stream:
				if int(getAttribute(channel,'channel')) == channel_num:
					res.append(channel)
	return res

def isTimerAF(tag):
	if 'TIM' in getValue(tag):
		return True
	return False
def getName(tag):
	return getAttribute(tag,'name')
def isTimer(tag):
	if "Timer" in getName(tag):
		return True
	return False
def getTimerOCchannelFromAFtag(afm_tag):
	return int(str(re.findall("CH(.+?)",getValue(afm_tag))[0]))
def getTimerNumberFromAFtag(afm_tag):
	return int(str(re.findall("TIM(.+?)",getValue(afm_tag))[0]))
def grabPeriphTags(dev,periph_name):
	res = []
	for periph in grabTags(dev,'PERIPHERAL'):
		if periph_name in getName(periph):
			res.append(periph)
	return res
def grabPeriphByName(dev,periph_name):
	return grabPeriphTags(dev,periph_name)[0]
def getPeripheralNumber(periph_tag):
		return int(str(re.findall("\d+",getName(periph_tag))[0]))
def grabPinAFtags(device_tag,pin):
	res = []
	for afm in grabTags(device_tag,'AFM'):
		if pin == getAttribute(afm,'pinName'):
			res.append(afm)
	return res
def grabPeriphAFtags(device_tag,peripheral_tag):
	
	pattern = getName(peripheral_tag)
	if isTimer(peripheral_tag):
		periph_num = getPeripheralNumber(peripheral_tag)
		pattern = str("TIM")
		pattern += str(periph_num)
	
	res = []
	for afm in grabTags(device_tag,'AFM'):
		if pattern in getValue(afm):
			res.append(afm)
	return res

def grabTimerOCx_AFtags(device_tag,timer_tag, oc_number):
	res = []
	for af in grabPeriphAFtags(device_tag,timer_tag):
		if getTimerOCchannelFromAFtag(af) == oc_number:
			res.append(af)
	return res
def isUartRx_AFtag(afm_tag):
	if "RX" in getValue(afm_tag):
		return True
	return False
def grabUartRx_AFtags(device_tag,uart_tag):
	res = []
	for af in grabPeriphAFtags(device_tag,uart_tag):
		if isUartRx_AFtag(af):
			res.append(af)
	return res
def isUartTx_AFtag(afm_tag):
	if "TX" in getValue(afm_tag):
		return True
	return False
def grabUartTx_AFtags(device_tag,uart_tag):
	res = []
	for af in grabPeriphAFtags(device_tag,uart_tag):
		if isUartTx_AFtag(af):
			res.append(af)
	return res
def isI2CxSCL_AFtag(afm_tag):
	if "SCL" in getValue(afm_tag):
		return True
	return False
def isI2CxSDA_AFtag(afm_tag):
	if "SDA" in getValue(afm_tag):
		return True
	return False
def grabI2CxSCL_AFtags(device_tag,i2c_tag):
	res = []
	for af in grabPeriphAFtags(device_tag,i2c_tag):
		if isI2CxSCL_AFtag(af):
			res.append(af)
	return res
def isI2CxSCL_AFtag(afm_tag):
	if "SCL" in getValue(afm_tag):
		return True
	return False
def isSPIxMISO_AFtag(afm_tag):
	if "MISO" in getValue(afm_tag):
		return True
	return False
def isSPIxMOSI_AFtag(afm_tag):
	if "MOSI" in getValue(afm_tag):
		return True
	return False
def isSPIxSCK_AFtag(afm_tag):
	if "SCK" in getValue(afm_tag):
		return True
	return False
def isSPIxNSS_AFtag(afm_tag):
	if "NSS" in getValue(afm_tag):
		return True
	return False
def grabI2CxSDA_AFtags(device_tag,i2c_tag):
	res = []
	for af in grabPeriphAFtags(device_tag,i2c_tag):
		if isI2CxSDA_AFtag(af):
			res.append(af)
	return res
def grabSPIxMISO_AFtags(device_tag,spi_tag):
	res = []
	for af in grabPeriphAFtags(device_tag,spi_tag):
		if isSPIxMISO_AFtag(af):
			res.append(af)
	return res
def grabSPIxMOSI_AFtags(device_tag,spi_tag):
	res = []
	for af in grabPeriphAFtags(device_tag,spi_tag):
		if isSPIxMOSI_AFtag(af):
			res.append(af)
	return res
def grabSPIxSCK_AFtags(device_tag,spi_tag):
	res = []
	for af in grabPeriphAFtags(device_tag,spi_tag):
		if isSPIxSCK_AFtag(af):
			res.append(af)
	return res
def grabSPIxNSS_AFtags(device_tag,spi_tag):
	res = []
	for af in grabPeriphAFtags(device_tag,spi_tag):
		if isSPIxNSS_AFtag(af):
			res.append(af)
	return res
def existHardNSS(device_tag,spi_tag):
	res = grabSPIxNSS_AFtags(device_tag,spi_tag)
	if not res: return False
	return True

def grabAllTimers(device_tag):
	return grabPeriphTags(device_tag,'Timer')
def grabAllI2Cs(device_tag):
	return grabPeriphTags(device_tag,'I2C')
def grabAllDMA(device_tag):
	return grabPeriphTags(device_tag,'DMA')
def grabAllGPIOs(device_tag):
	return grabPeriphTags(device_tag,'GPIO')
def grabAllNVICtags(device_tag):
	return grabTags(device_tag,'NVIC')
def getGPIOnumber(gpio_tag):
	return str(re.findall("GPIO(.+?)",getName(gpio_tag))[0])
def grabAllSPIs(device_tag):
	return grabPeriphTags(device_tag,'SPI')
def grabAllUARTS(device_tag):
	return (grabPeriphTags(device_tag,'UART') + grabPeriphTags(device_tag,'USART'))
def getPortFromAFtag(afm_tag):
	return getAttribute(afm_tag,'pinName').split("P",1)[1]
def getPinNumberFromAFtag(afm_tag):	
	return int(str(re.findall("\d+",getPortFromAFtag(afm_tag))[0]))
def getStructEnumOpener():
	res = str(	"\ttypedef struct\n"+
				"\t{\n"+
				"\t\ttypedef enum\n"+
				"\t\t{")
	return res
def getStructEnumCloser(enum_name,struct_name):
	res = "\n\t\t}"+enum_name+";\n"
	res += "\t}"+struct_name+";\n\n"
	return res
def getStructOpener():
	res = str(	"\ttypedef struct\n"+
				"\t{")
	return res
def getStructCloser(struct_name):
	res = "\n\t}"+struct_name+";\n\n"
	return res

def getStructEnumItemString(af_tag,hardware_code):
	space = ""
	if getPinNumberFromAFtag(af_tag) < 10:
		space = " "
	return str("\n\t\t\tPORT"+getPortFromAFtag(af_tag)+space+" = "+formatHex(hex(hardware_code)))
def grabDevices():
	defs = minidom.parse('devices.xml')
	return defs.getElementsByTagName('device')
def createPWMdefs():

	res = ""


	for dev in grabDevices():
		res += getPlatformCondition(dev)
		for tim in grabAllTimers(dev):
			for oc_x in range(1,5):
				oc_exist = False
				for af in grabTimerOCx_AFtags(dev,tim,oc_x):
					if not oc_exist:
						res += getStructEnumOpener()
					if oc_exist:
						res += ','
					oc_exist = True
					code = int(getHardwareSetupCode(0,
									getAttribute(tim,'rccEnableBit'),
									getAttribute(tim,'address'),
									0,
									2,
									getAttribute(af,'number'),
									getPortFromAFtag(af)),16)
									
					code |= int(getTimerSetupCode(oc_x),16)
					
					res += getStructEnumItemString(af,code)
					
				if oc_exist:
					res += getStructEnumCloser("kPWM_"+getName(tim)+"_OC"+str(oc_x)+"_Pin","kPWM_OC"+str(oc_x)+"_"+getName(tim))	
			oc_exist = False	
			for oc_x in range(1,5):
				for af in grabTimerOCx_AFtags(dev,tim,oc_x):
					if not oc_exist:
						res += getStructOpener()
					oc_exist = True
					res += "\n\t\tkPWM_OC"+str(oc_x)+"_"+getName(tim) + " OC" + str(oc_x)+";"
					break	
			if oc_exist:
				res += getStructCloser("kPWM_"+getName(tim))
		
		for gpio in grabAllGPIOs(dev):
			for i in range(0,16):
				
				pin = "P" + getGPIOnumber(gpio) + str(i)
			
		
				pwm_out_exist = False
				for af in grabPinAFtags(dev,pin):
					if not isTimerAF(af): continue
			
					if not pwm_out_exist:
						res += getStructEnumOpener()
					if pwm_out_exist:
						res += ","
					pwm_out_exist = True
					
					tim = grabPeriphByName(dev,str("Timer" + str(getTimerNumberFromAFtag(af))))
					
					code = int(getHardwareSetupCode(0,
								getAttribute(tim,'rccEnableBit'),
								getAttribute(tim,'address'),
								0,
								2,
								getAttribute(af,'number'),
								getPortFromAFtag(af)),16)
								
					code |= int(getTimerSetupCode(getTimerOCchannelFromAFtag(af)),16)
					
					if getTimerNumberFromAFtag(af) < 10: space = " "
					res += "\n\t\t\tTimer"+str(getTimerNumberFromAFtag(af))+"_OC"+str(getTimerOCchannelFromAFtag(af))+space+" = "+formatHex(hex(code))	
				if pwm_out_exist:
					res += getStructEnumCloser(	"kPWM_OUT_PORT"+getGPIOnumber(gpio) + str(i)+"_PIN",
													"kPWM_out_PORT"+getGPIOnumber(gpio) + str(i))

		
		
		pwm_out_exist = False
		for tim in grabAllTimers(dev):		
			oc_exist = False	
			for oc_x in range(1,5):
				for af in grabTimerOCx_AFtags(dev,tim,oc_x):
					if not pwm_out_exist:
						res += getStructOpener()
					pwm_out_exist = True
					oc_exist = True
			if oc_exist:
				space = " "
				if getPeripheralNumber(tim) < 10: space += " "
				res += "\n\t\tkPWM_"+getName(tim) + space + getName(tim) +";"
				
		
		for gpio in grabAllGPIOs(dev):
			gpio_pwm_out_exist = False
			for i in range(0,16):
				pin = "P" + getGPIOnumber(gpio) + str(i)
				pin_exist = False
				for af in grabPinAFtags(dev,pin):
					if not isTimerAF(af): continue
					
					if not pwm_out_exist:
						res += getStructEnumOpener()
					pwm_out_exist = True
					if not gpio_pwm_out_exist:
						res += "\n"
						gpio_pwm_out_exist = True
					
					space = " " 
					if i < 10: space += " ";
					
					if not pin_exist:
						res += "\n\t\tkPWM_out_PORT"+getGPIOnumber(gpio) + str(i) + space + "PORT" + getGPIOnumber(gpio) + str(i) + ";"+space+"//  "+getValue(af)
					else:
						res += space + getValue(af)
					pin_exist = True	
					
						
		if pwm_out_exist:
			res += getStructCloser("kPWM_out")


		for exti_num in range(0,16):

			res += getStructEnumOpener()
			is_first = True
			for gpio in grabAllGPIOs(dev):
				if not is_first:
					res += ","
				is_first = False

				syscfg = grabPeriphByName(dev,"SYSCFG")

				port_name = getGPIOnumber(gpio) + str(exti_num)

				code = int(	getHardwareSetupCode(2,
							getAttribute(syscfg,'rccEnableBit'),
							getAttribute(syscfg,'address'),
							0,
							0,
							0,
							port_name),16)
				code |= 0x80000000
				
				res += "\n\t\t\tPORT"+port_name + " = " + formatHex(hex(code))
				
			res += getStructEnumCloser("kPWM_EXTI"+str(exti_num)+ "_Pin","kPWM_EXTI"+str(exti_num))
			
		res += getStructOpener()
		for exti_num in range(0,16):
			res += "\n\t\t" + "kPWM_EXTI"+str(exti_num) + " _EXTI" + str(exti_num) + ";"
		res += getStructCloser("kPWM_in")


		res += "\n#endif\n"
		

	return res
	
def createUSARTstructDefs():

	res = ""

	for dev in grabDevices():
		res += getPlatformCondition(dev)
		for uart in grabAllUARTS(dev):
			rx_exist = False
			for af in grabUartRx_AFtags(dev,uart):
				if not rx_exist:
					res += getStructEnumOpener()
				if rx_exist:
					res += ","
				rx_exist = True	

				code = int(getHardwareSetupCode(0,
								getAttribute(uart,'rccEnableBit'),
								getAttribute(uart,'address'),
								0,
								2,
								getAttribute(af,'number'),
								getPortFromAFtag(af)),16)
				
				code |= int(getUsartSetupCode(True,False),16)
				res += getStructEnumItemString(af,code)
				
			if rx_exist:
				res += getStructEnumCloser("kSerial_"+getName(uart)+"_RX_Pin","kSerial_"+getName(uart)+"_RX")
				
			tx_exist = False
			for af in grabUartTx_AFtags(dev,uart):
				if not tx_exist:
					res += getStructEnumOpener()
				if tx_exist:
					res += ","
				tx_exist = True	

				code = int(getHardwareSetupCode(0,
								getAttribute(uart,'rccEnableBit'),
								getAttribute(uart,'address'),
								0,
								2,
								getAttribute(af,'number'),
								getPortFromAFtag(af)),16)
				
				code |= int(getUsartSetupCode(False,True),16)
				res += getStructEnumItemString(af,code)
				
			if tx_exist:
				res += getStructEnumCloser("kSerial_"+getName(uart)+"_TX_Pin","kSerial_"+getName(uart)+"_TX")			
	  
		for uart in grabAllUARTS(dev):
			res += getStructOpener()
			res += "\n\t\tkSerial_" + getName(uart) + "_RX RX;"
			res += "\n\t\tkSerial_" + getName(uart) + "_TX TX;"
			res += getStructCloser("kSerial_" + getName(uart))

		res += "\n#endif\n"

	return res
	
def createUSARTdefs():
	
	res = ""
	
	for dev in grabDevices():
		res += "\t\t" + getPlatformCondition(dev)
		for uart in grabAllUARTS(dev):
			
			space = " "
			if getPeripheralNumber(uart) < 10:
				space += " "
			res += "\t\t\tstatic const kSerial_"+getName(uart)+space + "* _"+getName(uart)+";\n"
				
		res += "\n\t\t#endif\n\n"


	return res

def createSPIdefs():
	
	res = ""
	
	for dev in grabDevices():
		res += "\t\t" + getPlatformCondition(dev)
		for spi in grabAllSPIs(dev):
			
			space = " "
			if getPeripheralNumber(spi) < 10:
				space += " "
			res += "\t\t\tstatic const kSPI_"+getName(spi)+space + "* _"+getName(spi)+";\n"
				
		res += "\n\t\t#endif\n\n"


	return res

def createDMAdefs():
	
	res = ""
	
	for dev in grabDevices():
		res += "\t\t" + getPlatformCondition(dev)
		for dma in grabAllDMA(dev):
			
			space = " "
			if getPeripheralNumber(dma) < 10:
				space += " "
			res += "\t\t\tstatic const kDMA_" + getName(dma) + space + "* _"+getName(dma)+";\n"
				
		res += "\n\t\t#endif\n\n"


	return res

def createPORTdefs():

	res = ""
	
	for dev in grabDevices():
		res += getPlatformCondition(dev)
		for gpio in grabAllGPIOs(dev):
			res += "\t#define kPort_config_USE_"+getName(gpio).replace("GPIO","PORT")+"_OBJECT\n"
		res += "\n#endif\n"	
	
	return res
	
	
def createNVICstructDefs():

	res = ""
	
	for dev in grabDevices():
		res += getPlatformCondition(dev)
		res += getStructEnumOpener()
		is_last = False
		nvic_tags = grabAllNVICtags(dev)
		last = len(nvic_tags)-1
		for idx,irq in enumerate(grabAllNVICtags(dev)):
			if idx == last:
				is_last = True
		
			res += "\n\t\t\t_"+getName(irq) + " = " + getAttribute(irq,'position') 
			if not is_last:
				res += ","
			res += " // " + getAttribute(irq,'description')
			
		res += getStructEnumCloser("kSystem_IRQ_channel_enum","kSystem_IRQ_channel")
		res += "\n#endif\n"	
	
	return res


def createEXTIstructDefs():
	
	res = ""
	
	for dev in grabDevices():
		res += getPlatformCondition(dev)
		for exti_num in range(0,16):
		
			edge_str = ["Null","FallingEdge"," RisingEdge","   BothEdges"]
			edge_name = ["NULL","FALLING","RISING","BOTH"]
		
			for edge in range(1,4):
		
				res += getStructEnumOpener()
				is_first = True
				for gpio in grabAllGPIOs(dev):
					if not is_first:
						res += ","
					is_first = False

					syscfg = grabPeriphByName(dev,"SYSCFG")


					port_name = getGPIOnumber(gpio) + str(exti_num)

					code = int(	getHardwareSetupCode(edge,
								getAttribute(syscfg,'rccEnableBit'),
								getAttribute(syscfg,'address'),
								0,
								0,
								0,
								port_name),16)
					
					res += "\n\t\t\tPORT"+port_name + " = " + formatHex(hex(code))
					
				res += getStructEnumCloser("kEXTI_EXTI"+str(exti_num)+ "_" + edge_name[edge] + "_Pin","kEXTI_EXTI"+str(exti_num)+ "_" + edge_name[edge])
			
			res += getStructOpener()
			for edge in range(1,4):
				res += "\n\t\t" + "kEXTI_EXTI"+str(exti_num)+ "_" + edge_name[edge] + " " + edge_str[edge] + ";"
			res += getStructCloser("kEXTI_EXTI"+str(exti_num))

			
		res += "\n#endif\n"
	return res
def createEXTIdefs():
	res = ""
	
	for exti_num in range(0,16):
			
		space = " "
		if exti_num < 10:
			space += " "
		res += "\t\t\tstatic const kEXTI_EXTI"+str(exti_num) + space + "_EXTI"+str(exti_num)+";\n"
			

	return res


def createI2CstructDefs():

	
	res = ""
	
	for dev in grabDevices():
		res += getPlatformCondition(dev)
		for i2c in grabAllI2Cs(dev):
			sda_exist = False
			for af in grabI2CxSDA_AFtags(dev,i2c):
				if not sda_exist:
					res += getStructEnumOpener()
				if sda_exist:
					res += ","
				sda_exist = True	

				code = int(getHardwareSetupCode(0,
								getAttribute(i2c,'rccEnableBit'),
								getAttribute(i2c,'address'),
								1,
								2,
								getAttribute(af,'number'),
								getPortFromAFtag(af)),16)
				
				res += getStructEnumItemString(af,code)
				
			if sda_exist:
				res += getStructEnumCloser("kI2C_"+getName(i2c)+"_SDA_Pin","kI2C_"+getName(i2c)+"_SDA")
		
			scl_exist = False
			for af in grabI2CxSCL_AFtags(dev,i2c):
				if not scl_exist:
					res += getStructEnumOpener()
				if scl_exist:
					res += ","
				scl_exist = True	

				code = int(getHardwareSetupCode(0,
								getAttribute(i2c,'rccEnableBit'),
								getAttribute(i2c,'address'),
								1,
								2,
								getAttribute(af,'number'),
								getPortFromAFtag(af)),16)
				
				res += getStructEnumItemString(af,code)
				
			if scl_exist:
				res += getStructEnumCloser("kI2C_"+getName(i2c)+"_SCL_Pin","kI2C_"+getName(i2c)+"_SCL")
				
		for i2c in grabAllI2Cs(dev):
			res += getStructOpener()
			res += "\n\t\tkI2C_" + getName(i2c) + "_SDA SDA;"
			res += "\n\t\tkI2C_" + getName(i2c) + "_SCL SCL;"
			res += getStructCloser("kI2C_" + getName(i2c))
				
		res += "\n#endif\n"
	return res
def createI2Cdefs():
	
	res = ""
	
	for dev in grabDevices():
		res += "\t\t" + getPlatformCondition(dev)
		for i2c in grabAllI2Cs(dev):
			
			space = " "
			if getPeripheralNumber(i2c) < 10:
				space += " "
			res += "\t\t\tstatic const kI2C_"+getName(i2c)+space + "* _"+getName(i2c)+";\n"
				
		res += "\n\t\t#endif\n\n"


	return res




def getSPIconfigStructs(device,spi_tag):

	res = ""

	MSTR_str = ["SLAVE","MASTER"]
	SSM_str = ["HARD","SOFT"]
	LSBFIRST_str = ["MSB","LSB"]
	CPOL_str = ["LOW","HIGH"]
	for MSTR in range(0,2):
		for LSBFIRST in range(0,2):
			for CPOL in range(0,2):
				
				code = int(getHardwareSetupCode(0,
						getAttribute(spi_tag,'rccEnableBit'),
						getAttribute(spi_tag,'address'),
						0,
						0,
						0,
						"A0"),16)
			
				code |= (MSTR << 2)
				code |= (LSBFIRST << 3)
				code |= (CPOL << 1)
				code |= 0x08000000
			
				res += getStructEnumOpener() + "\n"
				res += str("\n\t\t\tDataCapture_1Edge = " + formatHex(hex(code))+",")
				
				code |= 1
				res += str("\n\t\t\tDataCapture_2Edge = " + formatHex(hex(code)))
				
				name = "kSPI_" + getName(spi_tag) + "_" + MSTR_str[MSTR] + "_" + LSBFIRST_str[LSBFIRST] + "_" + CPOL_str[CPOL]
				res += getStructEnumCloser(	name + "_SELECT", name + "_EDGE")


	MSTR_name = ["Master","Slave"]
	LSBFIRST_name = ["MSB_First","LSB_First"]
	CPOL_name = ["SCK_IdleLow","SCK_IdleHigh"]
	
	for MSTR in range(0,2):
			for LSBFIRST in range(0,2):
				
				res += getStructOpener()
			
				for CPOL in range(0,2):
						item_name = "kSPI_" + getName(spi_tag) + "_" + MSTR_str[MSTR] + "_" + LSBFIRST_str[LSBFIRST] + "_" + CPOL_str[CPOL] + "_EDGE "
						res += str("\n\t\t" + item_name + CPOL_name[CPOL] + ";")

				name = "kSPI_" + getName(spi_tag) + "_" + MSTR_str[MSTR] + "_" + LSBFIRST_str[LSBFIRST] + "_SELECT_SELECT"
				res += getStructCloser(name)

	for MSTR in range(0,2):
				
			res += getStructOpener()
		
			for LSBFIRST in range(0,2):
					item_name = "kSPI_" + getName(spi_tag) + "_" + MSTR_str[MSTR] + "_" + LSBFIRST_str[LSBFIRST] + "_SELECT_SELECT "
					res += str("\n\t\t" + item_name + LSBFIRST_name[LSBFIRST] + ";")

			name = "kSPI_" + getName(spi_tag) + "_" + MSTR_str[MSTR] + "_SELECT_SELECT_SELECT"
			res += getStructCloser(name)


	nss_exist = False
	for af in grabSPIxNSS_AFtags(device,spi_tag):
		if not nss_exist:
			res += getStructEnumOpener()
		if nss_exist:
			res += ","
		nss_exist = True	

		code = int(getHardwareSetupCode(0,
						getAttribute(spi_tag,'rccEnableBit'),
						getAttribute(spi_tag,'address'),
						0,
						2,
						getAttribute(af,'number'),
						getPortFromAFtag(af)),16)
		
		res += getStructEnumItemString(af,code)
		
	if nss_exist:
		res += getStructEnumCloser("kSPI_"+getName(spi_tag)+"_NSS_HARD_Pin","kSPI_"+getName(spi_tag)+"_NSS_HARD")

		
	
	
	
	return res



def createSPIstructDefs():

	res = ""
	
	for dev in grabDevices():
		res += getPlatformCondition(dev)
		for spi in grabAllSPIs(dev):
			miso_exist = False
			for af in grabSPIxMISO_AFtags(dev,spi):
				if not miso_exist:
					res += getStructEnumOpener()
				if miso_exist:
					res += ","
				miso_exist = True	

				code = int(getHardwareSetupCode(0,
								getAttribute(spi,'rccEnableBit'),
								getAttribute(spi,'address'),
								0,
								2,
								getAttribute(af,'number'),
								getPortFromAFtag(af)),16)
				
				res += getStructEnumItemString(af,code)
				
			if miso_exist:
				res += getStructEnumCloser("kSPI_"+getName(spi)+"_MISO_Pin","kSPI_"+getName(spi)+"_MISO")
			
			mosi_exist = False
			for af in grabSPIxMOSI_AFtags(dev,spi):
				if not mosi_exist:
					res += getStructEnumOpener()
				if mosi_exist:
					res += ","
				mosi_exist = True	

				code = int(getHardwareSetupCode(0,
								getAttribute(spi,'rccEnableBit'),
								getAttribute(spi,'address'),
								0,
								2,
								getAttribute(af,'number'),
								getPortFromAFtag(af)),16)
				
				res += getStructEnumItemString(af,code)
				
			if mosi_exist:
				res += getStructEnumCloser("kSPI_"+getName(spi)+"_MOSI_Pin","kSPI_"+getName(spi)+"_MOSI")
				
				
			sck_exist = False
			for af in grabSPIxSCK_AFtags(dev,spi):
				if not sck_exist:
					res += getStructEnumOpener()
				if sck_exist:
					res += ","
				sck_exist = True	

				code = int(getHardwareSetupCode(0,
								getAttribute(spi,'rccEnableBit'),
								getAttribute(spi,'address'),
								0,
								2,
								getAttribute(af,'number'),
								getPortFromAFtag(af)),16)
				
				res += getStructEnumItemString(af,code)
				
			if sck_exist:
				res += getStructEnumCloser("kSPI_"+getName(spi)+"_SCK_Pin","kSPI_"+getName(spi)+"_SCK")


			nss_exist = False
			for af in grabSPIxNSS_AFtags(dev,spi):
				if not nss_exist:
					res += getStructEnumOpener()
				if nss_exist:
					res += ","
				nss_exist = True	

				code = int(getHardwareSetupCode(0,
								getAttribute(spi,'rccEnableBit'),
								getAttribute(spi,'address'),
								0,
								2,
								getAttribute(af,'number'),
								getPortFromAFtag(af)),16)
				
				res += getStructEnumItemString(af,code)
				
			if nss_exist:
				res += getStructEnumCloser("kSPI_"+getName(spi)+"_NSS_Pin","kSPI_"+getName(spi)+"_NSS")


			res += getSPIconfigStructs(dev,spi)	
	

		res += getStructEnumOpener()
		
		soft_nss_exist = False
		for gpio in grabAllGPIOs(dev):
			for pin in range(0,16):
					
					if soft_nss_exist:
						res += ","
					soft_nss_exist = True
			
					pin_number = getGPIOnumber(gpio)+str(pin)
				
					code = int(getHardwareSetupCode(0,
					getAttribute(spi,'rccEnableBit'),
					getAttribute(spi,'address'),
					0,
					2,
					'0',
					pin_number),16)
					
					if pin < 10: pin_number += " "
					res += str("\n\t\t\tPORT"+pin_number+" = "+formatHex(hex(code)))
					
		if soft_nss_exist:
			res += getStructEnumCloser("kSPI_NSS_SOFT_Pin","kSPI_NSS_SOFT")	

		for spi in grabAllSPIs(dev):
			res += getStructOpener()
			
			if existHardNSS(dev,spi):
				res += "\n\t\tkSPI_" + getName(spi) + "_NSS Hard;"
			
			res += "\n\t\tkSPI_NSS_SOFT Soft;"
			res += getStructCloser("kSPI_" + getName(spi) + "_NSS_SELECT")
			

		
		MSTR_name = ["Master","Slave"]
		MSTR_str = ["SLAVE","MASTER"]
		
		for spi in grabAllSPIs(dev):
			res += getStructOpener()
			
			for MSTR in range(0,2):
				item_name = "kSPI_" + getName(spi) + "_" + MSTR_str[MSTR] + "_SELECT_SELECT_SELECT "
				res += str("\n\t\t" + item_name + MSTR_name[MSTR] +";")
		
		
			res += str("\n\t\tkSPI_" + getName(spi) + "_MISO MISO;")
			res += str("\n\t\tkSPI_" + getName(spi) + "_MOSI MOSI;")
			res += str("\n\t\tkSPI_" + getName(spi) + "_SCK  SCK;")
			res += str("\n\t\tkSPI_" + getName(spi) + "_NSS_SELECT NSS;")
			name = "kSPI_" + getName(spi)
			res += getStructCloser(name)
		
			
		res += "\n#endif\n"

	return res




def createDMAstructDefs():

	res = ""
	
	
	DMA_str = []
	stream_str = []
	DataTransferDirection_str = ["P2M","M2P","M2M"]
	DataSize_str = ["Data8bit",
					"Data16bit",
					"Data32bit"]
	MemoryIncrementMode_str =  ["MemAddrFixed",
								"MemAddrIncr"]
	CircularMode_str = ["CircOff",
						"CircOn"]
	priority_str = ["PriorityLow     ",
					"PriorityMedium  ",
					"PriorityHigh    ",
					"PriorityVeryHigh"]
	
	
	DMA_name = []
	stream_name = []	
	DataTransferDirection_name = ["P2M","M2P","M2M"]
	DataSize_name = ["DATA8","DATA16","DATA32"]
	MemoryIncrementMode_name = ["FIXED","INCR"]
	CircularMode_name = ["CIRCOFF","CIRCON"]
	priority_name = ["LOW","MEDIUM","HIGH","VERYHIGH"]	
	
	for dev in grabDevices():
		res += getPlatformCondition(dev)
		for dma_idx,DMA in enumerate(grabAllDMA(dev)):
			
		
			
			DMA_str.append(getName(DMA).lower())
			DMA_name.append(getName(DMA))
		
			for stream in range(0,8):
			
				stream_str.append("Stream" + str(stream))
				stream_name.append("STREAM" + str(stream))
			
				for DataTransferDirection in range(0,2):
				
					for channel_num in range(0,8):
					
						for channel in getDMAchannelTags(dev,DMA,stream,channel_num):
					
					
							channel_str = getValue(channel)
							channel_name = "CHANNEL" + str(channel_num) + "_" + getValue(channel)					
					
						
							for DataSize in range (0,3):
								for MemoryIncrementMode in range (0,2):
									for CircularMode in range (0,2):

										res += getStructEnumOpener()
									
										for priority in range(0,4):
											if priority > 0:
												res += ","
											
										
											PeripheralFlowControler = 0

											if DataTransferDirection > 1:
												channel_num = 0
										
											code = getDMAsetupCode(	getPeripheralNumber(DMA),
																	stream,
																	channel_num,
																	priority,
																	DataSize,
																	MemoryIncrementMode,
																	CircularMode,
																	DataTransferDirection,
																	PeripheralFlowControler)
																	
											res += "\n\t\t\t" + priority_str[priority] + " = " + formatHex(hex(code))
																	
										name = 	"kDMA_"	+ DMA_name[dma_idx]
										name += "_" + stream_name[stream] 
										name += "_" + DataTransferDirection_name[DataTransferDirection]
										if DataTransferDirection < 2:
											name += "_" + channel_name
										name += "_" + DataSize_name[DataSize]
										name += "_" + MemoryIncrementMode_name[MemoryIncrementMode]
										name += "_" + CircularMode_name[CircularMode]
										name += "_" + "SELECT"
										
										res += getStructEnumCloser(name + "_ENUM",name + "_STRUCT")

				# only DMA2 can make M2M transfers				
				if not "DMA2" in getName(DMA):
					continue

				for DataTransferDirection in range(2,3):
				
					for DataSize in range (0,3):

						res += getStructEnumOpener()
					
						for priority in range(0,4):
							if priority > 0:
								res += ","
							
						
							PeripheralFlowControler = 0
							if DataTransferDirection < 2:
								PeripheralFlowControler = 1
							if DataTransferDirection > 1:
								channel_num = 0
								CircularMode = 0
								MemoryIncrementMode = 1
						
							code = getDMAsetupCode(	getPeripheralNumber(DMA),
													stream,
													channel_num,
													priority,
													DataSize,
													MemoryIncrementMode,
													CircularMode,
													DataTransferDirection,
													PeripheralFlowControler)
													
							# force memory increment mode and peripheral increment mode for M2M transactions
							code |= (3 << 9)
													
							res += "\n\t\t\t" + priority_str[priority] + " = " + formatHex(hex(code))
													
						name = 	"kDMA_"	+ DMA_name[dma_idx]
						name += "_" + stream_name[stream] 
						name += "_" + DataTransferDirection_name[DataTransferDirection]
						name += "_" + DataSize_name[DataSize]
						name += "_" + "SELECT"
						
						res += getStructEnumCloser(name + "_ENUM",name + "_STRUCT")

										
			for stream in range(0,8):
			
				for DataTransferDirection in range(0,2):
			
					for channel_num in range(0,8):
					
						for channel in getDMAchannelTags(dev,DMA,stream,channel_num):
					
					
							channel_str = getValue(channel)
							channel_name = "CHANNEL" + str(channel_num) + "_" + getValue(channel)					
						
						
							for DataSize in range (0,3):
								for MemoryIncrementMode in range (0,2):
									res += getStructOpener()
									name_new = ""
									for CircularMode in range (0,2):
						
										
																	
										name = 	"kDMA_"	+ DMA_name[dma_idx]
										name += "_" + stream_name[stream]
										name += "_" + DataTransferDirection_name[DataTransferDirection]
										if DataTransferDirection < 2:
											name += "_" + channel_name
										name += "_" + DataSize_name[DataSize]
										name += "_" + MemoryIncrementMode_name[MemoryIncrementMode]
										
										name_new = name
										name_new += "_SELECT_SELECT"
										
										name += "_" + CircularMode_name[CircularMode]										
										name += "_" + "SELECT_STRUCT"
										
										res += "\n\t\t" + name + " " + CircularMode_str[CircularMode] + ";"
										
									res += getStructCloser(name_new)

				# only DMA2 can make M2M transfers				
				if not "DMA2" in getName(DMA):
					continue

				for DataTransferDirection in range(2,3):
			
					res += getStructOpener()
					name_new = ""

					for DataSize in range (0,3):
					
						name = 	"kDMA_"	+ DMA_name[dma_idx]
						name += "_" + stream_name[stream] 
						name += "_" + DataTransferDirection_name[DataTransferDirection]
						
						name_new = name
						
						name += "_" + DataSize_name[DataSize]
						name += "_" + "SELECT_STRUCT"
						
						name_new += "_SELECT_SELECT"
				
						res += "\n\t\t" + name + " " + DataSize_str[DataSize] + ";"
							
					res += getStructCloser(name_new)

			
			for stream in range(0,8):
			
				for DataTransferDirection in range(0,2):
				
					for channel_num in range(0,8):
					
						for channel in getDMAchannelTags(dev,DMA,stream,channel_num):
					
							channel_str = getValue(channel)
							channel_name = "CHANNEL" + str(channel_num) + "_" + getValue(channel)					
						
						
							for DataSize in range (0,3):
								res += getStructOpener()
								
								name_new = ""
								for MemoryIncrementMode in range (0,2):
																	
									name = 	"kDMA_"	+ DMA_name[dma_idx]
									name += "_" + stream_name[stream]
									name += "_" + DataTransferDirection_name[DataTransferDirection]
									if DataTransferDirection < 2:
										name += "_" + channel_name
									name += "_" + DataSize_name[DataSize]
									
									name_new = name
									
									name += "_" + MemoryIncrementMode_name[MemoryIncrementMode]
									name += "_SELECT_SELECT"
									name_new += "_SELECT_SELECT_SELECT"
									
									res += "\n\t\t" + name + " " + MemoryIncrementMode_str[MemoryIncrementMode] + ";"
										
								res += getStructCloser(name_new)
								
				# only DMA2 can make M2M transfers				
				if not "DMA2" in getName(DMA):
					continue

				for DataTransferDirection in range(2,3):
						
					res += getStructOpener()
					name_new = ""
					
					for DataSize in range (0,3):
						
						
					
														
						name = 	"kDMA_"	+ DMA_name[dma_idx]
						name += "_" + stream_name[stream]
						name += "_" + DataTransferDirection_name[DataTransferDirection]

						name_new = name

						name += "_" + DataSize_name[DataSize]
						
						
						
				
						name += "_SELECT_STRUCT"
						name_new += "_SELECT_SELECT_SELECT"
						
						res += "\n\t\t" + name + " " + DataSize_str[DataSize] + ";"
							
					res += getStructCloser(name_new)

			for stream in range(0,8):
			
				for DataTransferDirection in range(0,2):
			
					for channel_num in range(0,8):
					
						for channel in getDMAchannelTags(dev,DMA,stream,channel_num):
					
					
							channel_str = getValue(channel)
							channel_name = "CHANNEL" + str(channel_num) + "_" + getValue(channel)					
						
						
						
							res += getStructOpener()
							name_new = ""
							for DataSize in range (0,3):
								
																	
									name = 	"kDMA_"	+ DMA_name[dma_idx]
									name += "_" + stream_name[stream]
									name += "_" + DataTransferDirection_name[DataTransferDirection]
									if DataTransferDirection < 2:
										name += "_" + channel_name
									
									name_new = name
									
									name += "_" + DataSize_name[DataSize]
									
									name += "_SELECT_SELECT_SELECT"
									name_new += "_SELECT_SELECT_SELECT_SELECT"
									
									res += "\n\t\t" + name + " " + DataSize_str[DataSize] + ";"
										
							res += getStructCloser(name_new)


			for stream in range(0,8):
			
				for DataTransferDirection in range(0,2):
			
						name_new = ""
					
						channel_exist = False
						for channel in getAllDMAchannelTags(dev,DMA,stream):
							if not channel_exist:
								res += getStructOpener()
							channel_exist = True
					
							channel_str = "_"+getValue(channel)
							channel_name = "CHANNEL" + getAttribute(channel,'channel') + "_" + getValue(channel)					
						

							
	
							name = 	"kDMA_"	+ DMA_name[dma_idx]
							name += "_" + stream_name[stream]
							name += "_" + DataTransferDirection_name[DataTransferDirection]
							
							
							name_new = name
							
							if DataTransferDirection < 2:
								name += "_" + channel_name
							
							name += "_SELECT_SELECT_SELECT_SELECT"
							name_new += "_SELECT_SELECT_SELECT_SELECT_SELECT"
							
							res += "\n\t\t" + name + " " + channel_str + ";"
						
						if channel_exist:
							res += getStructCloser(name_new)
							

			for stream in range(0,8):
		
				res += getStructOpener()
				name_new = ""
				for DataTransferDirection in range(0,2):
	

					name = 	"kDMA_"	+ DMA_name[dma_idx]
					name += "_" + stream_name[stream] 
					
					name_new = name
					
					name += "_" + DataTransferDirection_name[DataTransferDirection]

					
					name += "_SELECT_SELECT_SELECT_SELECT"
					if DataTransferDirection < 2:
						name += "_SELECT"
					name_new += "_SELECT_SELECT_SELECT_SELECT_SELECT_SELECT"
					
					res += "\n\t\t" + name + " " + DataTransferDirection_str[DataTransferDirection] + ";"
				
				
				# only DMA2 can make M2M transfers				
				if not "DMA2" in getName(DMA):
					res += getStructCloser(name_new)
					continue
				
				for DataTransferDirection in range(2,3):
	

					name = 	"kDMA_"	+ DMA_name[dma_idx]
					name += "_" + stream_name[stream]

					name_new = name
					
					name += "_" + DataTransferDirection_name[DataTransferDirection]
					
					name += "_SELECT_SELECT"
				
					name_new += "_SELECT_SELECT_SELECT_SELECT_SELECT_SELECT"
					
					
					res += "\n\t\t" + name + " " + DataTransferDirection_str[DataTransferDirection] + ";"
					
									
				res += getStructCloser(name_new)

			res += getStructOpener()
			name_new = ""
			for stream in range(0,8):
			
	
				name = 	"kDMA_"	+ DMA_name[dma_idx]
				
				name_new = name
				
				name += "_" + stream_name[stream] 
				name += "_SELECT_SELECT_SELECT_SELECT_SELECT_SELECT"
				
				res += "\n\t\t" + name + " " + stream_str[stream] + ";"
										
			res += getStructCloser(name_new)





		res += "\n#endif\n"							
									
	return res								


def getDMAsetupCode(dma_number,stream,channel,priority,DataSize,MemoryIncrementMode,CircularMode,DataTransferDirection,PeripheralFlowControler):
	code = 0;
	if PeripheralFlowControler != 0:
		code |= (1 << 5)
	code |= (DataTransferDirection << 6)
	if CircularMode != 0:
		code |= (1 << 8)
	if MemoryIncrementMode != 0:
		code |= (1 << 10)
	code |= (DataSize << 11)
	code |= (DataSize << 13)
	code |= (priority << 16)
	code |= (channel << 25)
	code |= (stream << 28)
	
	dma_number -= 1
	code  |= (dma_number << 31)

	return code


	
xls2xml()
replaceCodeRegion("../inc/kStandard/kPWM.h",'PLATFORM_DEPENDED_STRUCTS',createPWMdefs())

replaceCodeRegion("../inc/kStandard/kEXTI.h",'PLATFORM_DEPENDED_STRUCTS',createEXTIstructDefs())
replaceCodeRegion("../inc/kStandard/kEXTI.h",'EXTI_DECLARATIONS',createEXTIdefs())

replaceCodeRegion("../inc/kStandard/kSerial.h",'PLATFORM_DEPENDED_STRUCTS',createUSARTstructDefs())
replaceCodeRegion("../inc/kStandard/kSerial.h",'USARTS_DECLARATIONS',createUSARTdefs())

replaceCodeRegion("../inc/kStandard/kI2C.h",'PLATFORM_DEPENDED_STRUCTS',createI2CstructDefs())
replaceCodeRegion("../inc/kStandard/kI2C.h",'I2C_DECLARATIONS',createI2Cdefs())


replaceCodeRegion("../inc/kStandard/kSPI.h",'PLATFORM_DEPENDED_STRUCTS',createSPIstructDefs())
replaceCodeRegion("../inc/kStandard/kSPI.h",'SPI_DECLARATIONS',createSPIdefs())

replaceCodeRegion("../inc/kStandard/kDMA.h",'PLATFORM_DEPENDED_STRUCTS',createDMAstructDefs())
replaceCodeRegion("../inc/kStandard/kDMA.h",'DMA_DECLARATIONS',createDMAdefs())

replaceCodeRegion("../inc/kStandard/kPORT.h",'PLATFORM_DEPENDED_STRUCTS',createPORTdefs())

replaceCodeRegion("../inc/kStandard/kSystem.h",'PLATFORM_DEPENDED_STRUCTS',createNVICstructDefs())

updateLicenseText()
