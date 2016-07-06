#ifndef __kConfig_H
#define __kConfig_H

	// kLib configuration file

	// PLATFORM SELECT
	#define kLib_config_PLATFORM STM32F411xE

	#ifndef kLib_config_PLATFORM
		#error "please select platform"
	#endif

	// GENERAL SETTINGS
	#define kLib_config_USE_RTOS 1
	#define kLib_config_USE_MODULE 1

#endif
