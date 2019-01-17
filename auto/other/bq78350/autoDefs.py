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
def getCellValue2(sheet,row,col):
	res = str(sheet.cell(row,col).value)
	res = res.replace("—", "-")
	return res


def xls2xml():

	filesDir = '';
	root = etree.Element("flash")
	

	wb = open_workbook('bq78350.xlsx')

	for sheet in wb.sheets():
		number_of_rows = sheet.nrows
		number_of_columns = sheet.ncols
		
		for row in range(2, number_of_rows):
	
			af = etree.SubElement(root, "REG")
			af.set('class',getCellValue(sheet,row,0))
			af.set('subclass',getCellValue(sheet,row,1))
			af.set('address',getCellValue(sheet,row,2));
			af.set('name',getCellValue(sheet,row,3));
			af.set('type',getCellValue(sheet,row,4));


	wb = open_workbook('SBS.xlsx')

	for sheet in wb.sheets():
		number_of_rows = sheet.nrows
		number_of_columns = sheet.ncols
		
		for row in range(2, number_of_rows):
	
			af = etree.SubElement(root, "SBS")
			af.set('value',getCellValue(sheet,row,0))
			af.set('access',getCellValue(sheet,row,1))
			af.set('name',getCellValue(sheet,row,2));
			af.set('dataDescription',getCellValue2(sheet,row,3));
			af.set('dataSize',getCellValue2(sheet,row,4));
			af.set('min',getCellValue2(sheet,row,5));
			af.set('max',getCellValue2(sheet,row,6));
			af.set('default',getCellValue2(sheet,row,7));
			af.set('units',getCellValue2(sheet,row,8));
	
	wb = open_workbook('MA.xlsx')

	for sheet in wb.sheets():
		number_of_rows = sheet.nrows
		number_of_columns = sheet.ncols
		
		for row in range(2, number_of_rows):
	
			af = etree.SubElement(root, "MA")
			af.set('value',getCellValue(sheet,row,0))
			af.set('name',getCellValue(sheet,row,1))
			af.set('access',getCellValue(sheet,row,2))
				
	tree = etree.ElementTree(root)
	tree.write('bq78350.xml',pretty_print=True)
				
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

def getName(tag):
	return getAttribute(tag,'name')
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


def getClassName(tag):
	return getAttribute(tag,'class')
def getSublcassName(tag):
	return getAttribute(tag,'subclass')
	
def getClassListNames(tags):
	res = []
	
	for tag in tags:
		class_name = getClassName(tag)
		if class_name not in res:
			res.append(class_name)
	return res
	
def getSubclassListNames(tags):
	res = []
	
	for tag in tags:
		subclass_name = getSublcassName(tag)
		if subclass_name not in res:
			res.append(subclass_name)
	return res

def grabAllClassTags(parent,class_name):
	res = []
	for tag in parent:
		if class_name == getClassName(tag):
			res.append(tag)
	return res
def grabAllSubclassTags(parent,subclass_name):
	res = []
	for tag in parent:
		if subclass_name == getSublcassName(tag):
			res.append(tag)
	return res

def assertString(str):
	str = str.replace(".","")
	str = str.replace("%","Percent")
	str = str.replace("/","_")
	str = str.replace("-","")
	
	return str
	
def removeDecimalPoints(str):
	str = str.replace(".0", "")
	return str

def createDataFlashRegisterStructs():

	res = ""
	defs = minidom.parse('bq78350.xml')
	registers = defs.getElementsByTagName('REG')

	classes = getClassListNames(registers)
	
	
	for class_name in classes:
		
		class_tags = grabAllClassTags(registers,class_name)
		subclasses_names = getSubclassListNames(class_tags)
		
		
		class_name = assertString(class_name)
		
		for subclass_name in subclasses_names:
			subclass_tags = grabAllSubclassTags(class_tags,subclass_name)
		
			subclass_name = assertString(subclass_name)
		
			enum_exist = False
			for tag in subclass_tags:
				if not enum_exist:
					res += getStructEnumOpener()
				if enum_exist:
					res += ","
				enum_exist = True

				

				temp_name = getAttribute(tag,'name')
				temp_name = assertString(temp_name)

				res += "\n\t\t\t_" + temp_name + " = " + getAttribute(tag,'address')
			
			if enum_exist:
				temp_str = "kBQ78350_DATA_FLASH_REGISTER_"+class_name+"_"+ subclass_name + "_SELECT_"
				res += getStructEnumCloser(temp_str + "ENUM",temp_str + "STRUCT")

	for class_name in classes:
		
		class_tags = grabAllClassTags(registers,class_name)
		subclasses_names = getSubclassListNames(class_tags)
		
		class_name = assertString(class_name)
		
		res += getStructOpener()
		for subclass_name in subclasses_names:

			subclass_name = assertString(subclass_name)

			temp_str = "kBQ78350_DATA_FLASH_REGISTER_"+class_name+"_"+ subclass_name + "_SELECT_STRUCT"
			res += "\n\t\t" + temp_str + " _" + subclass_name + ";"
			
		temp_str = "kBQ78350_DATA_FLASH_REGISTER_"+class_name+"_SELECT_SELECT_STRUCT"
		res += getStructCloser(temp_str)
		
	res += getStructOpener()
	for class_name in classes:
		
		class_name = assertString(class_name)
		
		temp_str = "kBQ78350_DATA_FLASH_REGISTER_"+class_name+"_SELECT_SELECT_STRUCT"
		res += "\n\t\t" + temp_str + " _" + class_name + ";"
		
	temp_str = "kBQ78350_DATA_FLASH_REGISTER_SELECT_SELECT_SELECT_STRUCT"
	res += getStructCloser(temp_str)
		
	
	sbs = defs.getElementsByTagName('SBS')
	res += getStructEnumOpener()
	isLastTag = True
	n = len(sbs)
	i=0
	
	max_str = "RemainingCapacityAlarm = 0x01,"
	
	for tag in sbs:
		i+= 1

		temp = "\n\t\t\t" + getAttribute(tag,'name') + " = " + getAttribute(tag,'value')
		if i != n:
			temp += ","
		m = len(max_str) - len(temp) + 2
		for j in range(0,m):
			temp += " "
		temp += "\t// ACCESS: " + getAttribute(tag,'access')
		temp += ",\tDATA TYPE: " + getAttribute(tag,'dataDescription')
		temp += ",\tDATA SIZE: " + removeDecimalPoints(getAttribute(tag,'dataSize'))
		temp += ",\tMIN: " + removeDecimalPoints(getAttribute(tag,'min'))
		temp += ",\tMAX: " + removeDecimalPoints(getAttribute(tag,'max'))
		temp += ",\tDEFAULT: " + removeDecimalPoints(getAttribute(tag,'default'))
		temp += ",\tUNIT: " + getAttribute(tag,'units')
		
		
		res += temp
		
	temp_str = "kBQ78350_SBS_COMMANDS_"
	res += getStructEnumCloser(temp_str + "ENUM",temp_str + "STRUCT")		
	

	ma = defs.getElementsByTagName('MA')
	res += getStructEnumOpener()
	isLastTag = True
	n = len(ma)
	i=0
	
	max_str = "OutputCellVoltageCCandTempforCalibration = 0xF082 "
	
	for tag in ma:
		i+= 1

		temp = "\n\t\t\t" + getAttribute(tag,'name') + " = " + getAttribute(tag,'value')
		if i != n:
			temp += ","
		m = len(max_str) - len(temp) + 2
		for j in range(0,m):
			temp += " "
		temp += "\t// ACCESS: " + getAttribute(tag,'access')
		
		res += temp
		
	temp_str = "kBQ78350_MANUFACTURER_ACCESS_COMMANDS_"
	res += getStructEnumCloser(temp_str + "ENUM",temp_str + "STRUCT")		

	return res


	
xls2xml()
replaceCodeRegion("../../../inc/kIC/kBQ78350.h",'PLATFORM_DEPENDED_STRUCTS',createDataFlashRegisterStructs())
