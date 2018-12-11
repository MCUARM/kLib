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
							af.text = str(sheet.cell(row,col).value)
				

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
				

xls2xml()