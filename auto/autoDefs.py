from xml.dom import minidom
from xml.dom.minidom import Node
import re

from xlrd import open_workbook
from lxml import etree
import os


def updateLicenseText():
	license = getLicenseString();
	
	dir = "../inc"
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
		
	dir = "../src"
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
def isTimerAF(tag):
	if 'TIM' in getValue(tag):
		return True
	return false
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
def getPeripheralNumber(periph_tag):
		return int(str(re.findall("\d+",getName(periph_tag))[0]))
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
def grabAllTimers(device_tag):
	return grabPeriphTags(device_tag,'Timer')
def grabAllI2Cs(device_tag):
	return grabPeriphTags(device_tag,'I2C')
def grabAllGPIOs(device_tag):
	return grabPeriphTags(device_tag,'GPIO')
def getGPIOnumber(gpio_tag):
	return str(re.findall("GPIO(.+?)",getName(gpio_tag))[0])
def grabAllSPIs(device_tag):
	return grabPeriphTags(device_tag,'SPI')
def grabAllUARTS(device_tag):
	return (grabPeriphTags(device_tag,'UART') + grabPeriphTags(device_tag,'USART'))
def getPortFromAFtag(afm_tag):
	return getAttribute(afm_tag,'pinName').split("P",1)[1] 
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
	return str("\n\t\t\tPORT"+getPortFromAFtag(af_tag)+" = "+formatHex(hex(hardware_code)))
def grabDevices():
	defs = minidom.parse('devices.xml')
	return defs.getElementsByTagName('device')
def createPWMdefs():
	file = open("kPWMdefs.h","w")
	header_name = '__kPWMDEFS_H'
	file.write(getLicenseString())
	file.write(getHeaderOpener(header_name))

	for dev in grabDevices():
		file.write(getPlatformCondition(dev))
		for tim in grabAllTimers(dev):
			for oc_x in range(1,5):
				oc_exist = False
				for af in grabTimerOCx_AFtags(dev,tim,oc_x):
					if not oc_exist:
						file.write(getStructEnumOpener())
					if oc_exist:
						file.write(',')
					oc_exist = True
					code = int(getHardwareSetupCode(0,
									getAttribute(tim,'rccEnableBit'),
									getAttribute(tim,'address'),
									0,
									2,
									getAttribute(af,'number'),
									getPortFromAFtag(af)),16)
									

					code |= int(getTimerSetupCode(oc_x),16)
					file.write("\n\t\t\tPORT"+getPortFromAFtag(af)+" = "+formatHex(hex(code)))
					
				if oc_exist:
					file.write(getStructEnumCloser("kPWM_"+getName(tim)+"_OC"+str(oc_x)+"_Pin","kPWM_OC"+str(oc_x)+"_"+getName(tim)))	
			oc_exist = False	
			for oc_x in range(1,5):
				for af in grabTimerOCx_AFtags(dev,tim,oc_x):
					if not oc_exist:
						file.write(getStructOpener())
					oc_exist = True
					file.write("\n\t\tkPWM_OC"+str(oc_x)+"_"+getName(tim) + " OC" + str(oc_x)+";")
					break	
			if oc_exist:
				file.write(getStructCloser("kPWM_"+getName(tim)))
		
		pwm_out_exist = False
		for tim in grabAllTimers(dev):		
			oc_exist = False	
			for oc_x in range(1,5):
				for af in grabTimerOCx_AFtags(dev,tim,oc_x):
					if not pwm_out_exist:
						file.write(getStructOpener())
					pwm_out_exist = True
					oc_exist = True
			if oc_exist:
				file.write("\n\t\tkPWM_"+getName(tim) + " " + getName(tim) +";")	
		if pwm_out_exist:
			file.write(getStructCloser("kPWM_out"))

		file.write("\n#endif\n")
		
	file.write(getHeaderCloser(header_name))
	file.close()
def createUSARTdefs():

	file = open("kSerialDefs.h","w")
	header_name = '__kSERIALDEFS_H'
	file.write(getLicenseString())
	file.write(getHeaderOpener(header_name))

	for dev in grabDevices():
		file.write(getPlatformCondition(dev))
		for uart in grabAllUARTS(dev):
			rx_exist = False
			for af in grabUartRx_AFtags(dev,uart):
				if not rx_exist:
					file.write(getStructEnumOpener())
				if rx_exist:
					file.write(",")
				rx_exist = True	

				code = int(getHardwareSetupCode(0,
								getAttribute(uart,'rccEnableBit'),
								getAttribute(uart,'address'),
								0,
								2,
								getAttribute(af,'number'),
								getPortFromAFtag(af)),16)
				
				code |= int(getUsartSetupCode(True,False),16)
				file.write("\n\t\t\tPORT"+getPortFromAFtag(af)+" = "+formatHex(hex(code)))
				
			if rx_exist:
				file.write(getStructEnumCloser("kSerial_"+getName(uart)+"_RX_Pin","kSerial_"+getName(uart)+"_RX"))	
				
			tx_exist = False
			for af in grabUartTx_AFtags(dev,uart):
				if not tx_exist:
					file.write(getStructEnumOpener())
				if tx_exist:
					file.write(",")
				tx_exist = True	

				code = int(getHardwareSetupCode(0,
								getAttribute(uart,'rccEnableBit'),
								getAttribute(uart,'address'),
								0,
								2,
								getAttribute(af,'number'),
								getPortFromAFtag(af)),16)
				
				code |= int(getUsartSetupCode(True,False),16)
				file.write("\n\t\t\tPORT"+getPortFromAFtag(af)+" = "+formatHex(hex(code)))
				
			if tx_exist:
				file.write(getStructEnumCloser("kSerial_"+getName(uart)+"_TX_Pin","kSerial_"+getName(uart)+"_TX"))				
	  
		file.write("\n#endif\n")
		
	file.write(getHeaderCloser(header_name))
	file.close()	
def createPORTdefs():

	file = open("kPORTdefs.h","w")
	header_name = '__kPORTDEFS_H'
	file.write(getLicenseString())
	file.write(getHeaderOpener(header_name))

	for dev in grabDevices():
		file.write(getPlatformCondition(dev))
		for gpio in grabAllGPIOs(dev):
			file.write("\t#define kPort_config_USE_"+getName(gpio).replace("GPIO","PORT")+"_OBJECT\n")
		file.write("\n#endif\n")	
	file.write(getHeaderCloser(header_name))
	file.close()
def createI2Cdefs():

	file = open("kI2CDefs.h","w")
	header_name = '__kSI2CDEFS_H'
	file.write(getLicenseString())
	file.write(getHeaderOpener(header_name))

	for dev in grabDevices():
		file.write(getPlatformCondition(dev))
		for i2c in grabAllI2Cs(dev):
			sda_exist = False
			for af in grabI2CxSDA_AFtags(dev,i2c):
				if not sda_exist:
					file.write(getStructEnumOpener())
				if sda_exist:
					file.write(",")
				sda_exist = True	

				code = int(getHardwareSetupCode(0,
								getAttribute(i2c,'rccEnableBit'),
								getAttribute(i2c,'address'),
								1,
								2,
								getAttribute(af,'number'),
								getPortFromAFtag(af)),16)
				
				file.write(getStructEnumItemString(af,code))
				
			if sda_exist:
				file.write(getStructEnumCloser("kI2C_"+getName(i2c)+"_SDA_Pin","kSPI_"+getName(i2c)+"_SDA"))
		
			scl_exist = False
			for af in grabI2CxSCL_AFtags(dev,i2c):
				if not scl_exist:
					file.write(getStructEnumOpener())
				if scl_exist:
					file.write(",")
				scl_exist = True	

				code = int(getHardwareSetupCode(0,
								getAttribute(i2c,'rccEnableBit'),
								getAttribute(i2c,'address'),
								1,
								2,
								getAttribute(af,'number'),
								getPortFromAFtag(af)),16)
				
				file.write(getStructEnumItemString(af,code))
				
			if scl_exist:
				file.write(getStructEnumCloser("kI2C_"+getName(i2c)+"_SCL_Pin","kSPI_"+getName(i2c)+"_SCL"))
		file.write("\n#endif\n")
	file.write(getHeaderCloser(header_name))
	file.close()


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
						getAttribute(spi,'rccEnableBit'),
						getAttribute(spi,'address'),
						0,
						2,
						getAttribute(af,'number'),
						getPortFromAFtag(af)),16)
		
		res += getStructEnumItemString(af,code)
		
	if nss_exist:
		res += getStructEnumCloser("kSPI_"+getName(spi)+"_NSS_HARD_Pin","kSPI_"+getName(spi)+"_NSS_HARD")

		
	
	
	
	return res



def createSPIdefs():

	file = open("kSPIDefs.h","w")
	header_name = '__kSPIDEFS_H'
	file.write(getLicenseString())
	file.write(getHeaderOpener(header_name))

	for dev in grabDevices():
		file.write(getPlatformCondition(dev))
		for spi in grabAllSPIs(dev):
			miso_exist = False
			for af in grabSPIxMISO_AFtags(dev,spi):
				if not miso_exist:
					file.write(getStructEnumOpener())
				if miso_exist:
					file.write(",")
				miso_exist = True	

				code = int(getHardwareSetupCode(0,
								getAttribute(spi,'rccEnableBit'),
								getAttribute(spi,'address'),
								0,
								2,
								getAttribute(af,'number'),
								getPortFromAFtag(af)),16)
				
				file.write(getStructEnumItemString(af,code))
				
			if miso_exist:
				file.write(getStructEnumCloser("kSPI_"+getName(spi)+"_MISO_Pin","kSPI_"+getName(spi)+"_MISO"))
			
			mosi_exist = False
			for af in grabSPIxMOSI_AFtags(dev,spi):
				if not mosi_exist:
					file.write(getStructEnumOpener())
				if mosi_exist:
					file.write(",")
				mosi_exist = True	

				code = int(getHardwareSetupCode(0,
								getAttribute(spi,'rccEnableBit'),
								getAttribute(spi,'address'),
								0,
								2,
								getAttribute(af,'number'),
								getPortFromAFtag(af)),16)
				
				file.write(getStructEnumItemString(af,code))
				
			if mosi_exist:
				file.write(getStructEnumCloser("kSPI_"+getName(spi)+"_MOSI_Pin","kSPI_"+getName(spi)+"_MOSI"))
				
				
			sck_exist = False
			for af in grabSPIxSCK_AFtags(dev,spi):
				if not sck_exist:
					file.write(getStructEnumOpener())
				if sck_exist:
					file.write(",")
				sck_exist = True	

				code = int(getHardwareSetupCode(0,
								getAttribute(spi,'rccEnableBit'),
								getAttribute(spi,'address'),
								0,
								2,
								getAttribute(af,'number'),
								getPortFromAFtag(af)),16)
				
				file.write(getStructEnumItemString(af,code))
				
			if sck_exist:
				file.write(getStructEnumCloser("kSPI_"+getName(spi)+"_SCK_Pin","kSPI_"+getName(spi)+"_SCK"))


			file.write(getSPIconfigStructs(dev,spi))	
	

		file.write(getStructEnumOpener())
		
		soft_nss_exist = False
		for gpio in grabAllGPIOs(dev):
			for pin in range(0,16):
					
					if soft_nss_exist:
						file.write(",")
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
					file.write(str("\n\t\t\tPORT"+pin_number+" = "+formatHex(hex(code))))
					
		if soft_nss_exist:
			file.write(getStructEnumCloser("kSPI_NSS_SOFT_Pin","kSPI_NSS_SOFT"))	

		for spi in grabAllSPIs(dev):
			file.write(getStructOpener())
			file.write("\n\t\tkSPI_" + getName(spi) + "_NSS Hard;\n")
			file.write("\t\tkSPI_NSS_SOFT Soft;")
			file.write(getStructCloser("kSPI_" + getName(spi) + "_NSS_SELECT"))
			

		file.write(getStructOpener())
		MSTR_name = ["Master","Slave"]
		MSTR_str = ["SLAVE","MASTER"]
		for MSTR in range(0,2):
			item_name = "kSPI_" + getName(spi) + "_" + MSTR_str[MSTR] + "_SELECT_SELECT_SELECT "
			file.write(str("\n\t\t" + item_name + MSTR_name[MSTR] +";"))
		
		
		file.write(str("\n\t\tkSPI_" + getName(spi) + "_MISO MISO;"))
		file.write(str("\n\t\tkSPI_" + getName(spi) + "_MOSI MOSI;"))
		file.write(str("\n\t\tkSPI_" + getName(spi) + "_SCK  SCK;"))
		file.write(str("\n\t\tkSPI_" + getName(spi) + "_NSS_SELECT NSS;"))
		name = "kSPI_" + getName(spi)
		file.write(getStructCloser(name))


		file.write("\tclass\n")
		file.write("\t{\n")
		file.write("\t\tpublic:\n")
		file.write("\n")
		for spi in grabAllSPIs(dev):
			file.write("\t\t\tstatic const kSPI_"+getName(spi) + " * " + getName(spi).lower() + ";\n")
		file.write("\n\t}\n\n")	
		
		
			
		file.write("\n#endif\n")
	file.write(getHeaderCloser(header_name))
	file.close()

	
xls2xml()
createPWMdefs()
createPORTdefs()
createUSARTdefs()
createI2Cdefs()
createSPIdefs()