from xml.dom import minidom
from xml.dom.minidom import Node
import re


def getHeaderOpener(header_name):
	return str("#ifndef "+header_name+"\n"+"#define "+header_name+"\n\n")
def getHeaderCloser(header_name):
	return str("\n\n//End of file "+header_name+"\n"+"#endif\n")
def getLicenseString():
	return str("/***********************************************************************************\n" +
		 " *                                                                                 *\n" +
		 " *   kLib - C++ development tools for ARM Cortex-M devices                         *\n" +
		 " *                                                                                 *\n" +
		 " *     Copyright (c) 2016, project author Pawel Zalewski                           *\n" +
		 " *     All rights reserved.                                                        *\n" +
		 " *                                                                                 *\n" +
		 " ***********************************************************************************\n" +
		 " * Redistribution and use in source and binary forms, with or without modification,\n" +
		 " * are permitted provided that the following conditions are met:\n" +
		 " *\n" +
		 " *   1. Redistributions of source code must retain the above copyright notice,\n" +
		 " *      this list of conditions and the following disclaimer.\n" +
		 " *   2. Redistributions  in  binary  form  must  reproduce the above copyright\n" +
		 " *      notice,  this  list  of conditions and the following disclaimer in the\n" +
		 " *      documentation  and/or  other materials provided with the distribution.\n" +
		 " *   3. Neither  the  name  of  the  copyright  holder  nor  the  names of its\n" +
		 " *      contributors  may  be used to endorse or promote products derived from\n" +
		 " *      this software without specific prior written permission.\n" +
		 " *\n" +
		 " *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\"\n" +
		 " *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,  BUT NOT LIMITED  TO, THE\n" +
		 " *   IMPLIED WARRANTIES OF MERCHANTABILITY  AND FITNESS FOR A PARTICULAR PURPOSE\n" +
		 " *   ARE DISCLAIMED.  IN NO EVENT SHALL  THE COPYRIGHT HOLDER OR CONTRIBUTORS BE\n" +
		 " *   LIABLE  FOR  ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR\n" +
		 " *   CONSEQUENTIAL  DAMAGES  (INCLUDING,  BUT  NOT  LIMITED  TO,  PROCUREMENT OF\n" +
		 " *   SUBSTITUTE  GOODS  OR SERVICES;  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS\n" +
		 " *   INTERRUPTION) HOWEVER  CAUSED  AND  ON  ANY THEORY OF LIABILITY, WHETHER IN\n" +
		 " *   CONTRACT,  STRICT  LIABILITY,  OR  TORT (INCLUDING NEGLIGENCE OR OTHERWISE)\n" +
		 " *   ARISING  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE\n" +
		 " *   POSSIBILITY OF SUCH DAMAGE.\n" +
		 " *\n" +
		 " */\n\n"
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
def grabTags(parent,tag_name):
	return parent.getElementsByTagName(tag_name)
def getAttribute(tag,attribute_name):
	return tag.attributes[attribute_name].value
def getContent(tag):
	return tag.nodeValue
def isTimerAF(tag):
	if 'TIM_CH' in getContent(tag):
		return True
	return false
def isTimer(strg):
	if "Timer" in getAttribute('name'):
		return True
	return False
def getTimerOCchannel(strg):
	return str(re.match("CH(.+?)",strg))
def getTimer(strg):
	return str("Timer" + str(re.match("TIM(.+?)",strg)))
def grapPeriphTags(parent,periph_name):
	res = []
	for periph in grabTags(dev,'PERIPHERAL'):
		if periph_name in getAttribute(periph,'name'):
			res.append(periph)
			
def grabPeriphAFtags(peripheral_tag):

def grabTimerOCx_AFtags(parent, oc_number):
	res = []
	for af in grabPeriphAFtags(parent):
		if int(getTimerOCchannel(getContent(parent))) == oc_number:
			res.append(af)


	
# parse an xml file by name
defs = minidom.parse('devices.xml')
devices = defs.getElementsByTagName('device')

file = open("kPWMdefs.h","w") 
file.write(getLicenseString())
file.write(getHeaderOpener())



for dev in devices:
	file.write(getPlatformCondition(getAttribute(dev,'name'))
				
	for tim in grapPeriphTags(dev,'Timer'):
		for oc_x in range(1,4):
			oc_exist = False
			for pin in grabTimerOCx_AFtags(tim,oc_x):
				if not oc_exist:
					file.write(	"\ttypedef struct\n"+
							"\t{\n"+
							"\t\ttypedef enum\n"+
							"\t\t{\n")
					oc_exist = True

				code = int(getHardwareSetupCode(0,
								tim.attributes['rccEnableBit'].value,
								tim.attributes['address'].value,
								0,
								2,
								tim.attributes['alternateFunction'].value,
								gpio.firstChild.data),16)
				code |= int(getTimerSetupCode(oc.attributes['number'].value),16)
				file.write("\t\t\tPORT"+gpio.firstChild.data+" = "+hex(code)+"\n")
		
			file.write(	"\t\t}kPWM_"+tim.attributes['name'].value+"_OC"+oc.attributes['number'].value+"_Pin;\n")
			file.write(	"\t}kPWM_OC"+oc.attributes['number'].value+"_"+tim.attributes['name'].value+";\n\n")
				

  
	file.write("\n#endif\n")
	
file.write(getHeaderCloser())
file.close() 
