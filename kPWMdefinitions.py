from xml.dom import minidom
from xml.dom.minidom import Node


def getTimerSetupCode(OC_number):
	oc_num = int(OC_number)
	res =  ((oc_num-1) & 0x00000003) << 27
	if oc_num > 2:
		res |= 0x20000000
	if (oc_num == 2) or (oc_num == 4):
		res |= 0x40000000
	return hex(res)

def getHardwareSetupCode(user_code,peripheral_clock_enable_bit_position,RCC_APBx_ENR_byte_offset,peripheral_address,gpio_output_type,gpio_mode,alternate_function,gpio_pin):

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
	


# parse an xml file by name
pwm_defs = minidom.parse('kPWMdefs.xml')


file = open("kPWMdefs.h","w") 
file.write("/***********************************************************************************\n" +
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
		 " */\n\n")
file.write("#ifndef __kPWM_H\n"+
		"#define __kPWM_H\n\n")
 

devices = pwm_defs.getElementsByTagName('device')
for dev in devices:
	file.write("#if (kLib_config_PLATFORM == kLib_"+dev.attributes['name'].value+")\n\n")
	for tim in dev.getElementsByTagName('timer'):
		for oc in tim.getElementsByTagName('OC'):
			file.write(	"\ttypedef struct\n"+
					"\t{\n"+
					"\t\ttypedef enum\n"+
					"\t\t{\n")

			for gpio in oc.getElementsByTagName('GPIO'):
				code = int(getHardwareSetupCode(0,
								tim.attributes['rccEnableBit'].value,
								tim.attributes['rccEnableByte'].value,
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
	


file.write("\n#endif\n")

file.close() 
