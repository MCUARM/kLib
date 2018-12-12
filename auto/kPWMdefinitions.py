from xml.dom import minidom
from xml.dom.minidom import Node
import re

from xlrd import open_workbook
from lxml import etree
import os

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
						device = etree.SubElement(root, "device", name=str(sheet.cell(0,1).value))


					for row in range(2, number_of_rows):

						for col in range(1,number_of_columns):
							value = str((sheet.cell(row,col).value))
							if not value or value.isspace():
								continue
								
							af = etree.SubElement(device, "AFM")
							af.set('pinName',str(sheet.cell(row,0).value))
							af.set('number',str(col-1))
							af.set('value',str(sheet.cell(row,col).value))
				

				if sheet.name == "Peripherals":
					
					if number_of_columns < 3:
						continue
					if number_of_rows < 2:
						continue
						
					if device == None:	
						device = etree.SubElement(root, "device", name=str(sheet.cell(0,1).value))
						
					for row in range(2, number_of_rows):

						periph = etree.SubElement(device, 'PERIPHERAL',name=str(sheet.cell(row,0).value))
						periph.set('address',str(sheet.cell(row,1).value))
						periph.set('rccEnableBit',str(int(float(str(sheet.cell(row,2).value)))))
				
				
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
def getPlatformCondition(platform):
	return str("#if (kLib_config_PLATFORM == kLib_"+platform+")\n\n")
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
	periph_num = getPeripheralNumber(peripheral_tag)
	pattern = ""
	if isTimer(peripheral_tag):
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
def grabAllTimers(device_tag):
	return grabPeriphTags(device_tag,'Timer')
def grabAllGPIOs(device_tag):
	return grabPeriphTags(device_tag,'GPIO')
def getPortFromAFtag(afm_tag):
	return getAttribute(afm_tag,'pinName').split("P",1)[1] 

def createPWMdefs():
	# parse an xml file by name
	defs = minidom.parse('devices.xml')
	devices = defs.getElementsByTagName('device')

	file = open("kPWMdefs.h","w")
	header_name = '__kPWMDEFS_H'
	file.write(getLicenseString())
	file.write(getHeaderOpener(header_name))

	for dev in devices:
		file.write(getPlatformCondition(getName(dev)))
		for tim in grabAllTimers(dev):
			for oc_x in range(1,5):
				oc_exist = False
				for af in grabTimerOCx_AFtags(dev,tim,oc_x):
					if not oc_exist:
						file.write("\ttypedef struct\n"+
								"\t{\n"+
								"\t\ttypedef enum\n"+
								"\t\t{\n")
						oc_exist = True

					code = int(getHardwareSetupCode(0,
									getAttribute(tim,'rccEnableBit'),
									getAttribute(tim,'address'),
									0,
									2,
									getAttribute(af,'number'),
									getPortFromAFtag(af)),16)
									
					code |= int(getTimerSetupCode(oc_x),16)
					file.write("\t\t\tPORT"+getPortFromAFtag(af)+" = "+hex(code)+"\n")
					
				if oc_exist:
					file.write(	"\t\t}kPWM_"+getName(tim)+"_OC"+str(oc_x)+"_Pin;\n")
					file.write(	"\t}kPWM_OC"+str(oc_x)+"_"+getName(tim)+";\n\n")
					
	  
		file.write("\n#endif\n")
		
	file.write(getHeaderCloser(header_name))
	file.close()
def createPORTdefs():
	# parse an xml file by name
	defs = minidom.parse('devices.xml')
	devices = defs.getElementsByTagName('device')

	file = open("kPORTdefs.h","w")
	header_name = '__kPORTDEFS_H'
	file.write(getLicenseString())
	file.write(getHeaderOpener(header_name))

	for dev in devices:
		file.write(getPlatformCondition(getName(dev)))
		for gpio in grabAllGPIOs(dev):
			file.write("\t#define kPort_config_USE_"+getName(gpio).replace("GPIO","PORT")+"_OBJECT\n")
		file.write("\n#endif\n")	
	file.write(getHeaderCloser(header_name))
	file.close()


xls2xml()
createPWMdefs()
createPORTdefs()
