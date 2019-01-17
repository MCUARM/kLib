/***********************************************************************************
 *                                                                                 *
 *   kLib - C++ development tools for ARM Cortex-M devices                         *
 *                                                                                 *
 *     Copyright (c) 2018, project author Pawel Zalewski                           *
 *     All rights reserved.                                                        *
 *                                                                                 *
 ***********************************************************************************
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions  in  binary  form  must  reproduce the above copyright
 *      notice,  this  list  of conditions and the following disclaimer in the
 *      documentation  and/or  other materials provided with the distribution.
 *   3. Neither  the  name  of  the  copyright  holder  nor  the  names of its
 *      contributors  may  be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,  BUT NOT LIMITED  TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY  AND FITNESS FOR A PARTICULAR PURPOSE
 *   ARE DISCLAIMED.  IN NO EVENT SHALL  THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *   LIABLE  FOR  ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR
 *   CONSEQUENTIAL  DAMAGES  (INCLUDING,  BUT  NOT  LIMITED  TO,  PROCUREMENT OF
 *   SUBSTITUTE  GOODS  OR SERVICES;  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *   INTERRUPTION) HOWEVER  CAUSED  AND  ON  ANY THEORY OF LIABILITY, WHETHER IN
 *   CONTRACT,  STRICT  LIABILITY,  OR  TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *   ARISING  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 *
 */



#ifndef __kBQ78350_H
#define __kBQ78350_H

// region PLATFORM_DEPENDED_STRUCTS

	typedef struct
	{
		typedef enum
		{
			_Capacity_Gain = 0x4004
		}kBQ78350_DATA_FLASH_REGISTER_Calibration_Current_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Calibration_Current_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Cell1_Offset = 0x4008,
			_Cell2_Offset = 0x4009,
			_Cell3_Offset = 0x400A,
			_Cell4_Offset = 0x400B,
			_Cell5_Offset = 0x400C,
			_Cell6_Offset = 0x400D,
			_Cell7_Offset = 0x400E,
			_Cell8_Offset = 0x400F,
			_Cell9_Offset = 0x4010,
			_Cell10_Offset = 0x4011,
			_Cell11_Offset = 0x4012,
			_Cell12_Offset = 0x4013,
			_Cell13_Offset = 0x4014,
			_Cell14_Offset = 0x4015,
			_Cell15_Offset = 0x4016
		}kBQ78350_DATA_FLASH_REGISTER_Calibration_Voltage_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Calibration_Voltage_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_CC_Offset = 0x4018,
			_Coulomb_Counter_Offset_Samples = 0x401A
		}kBQ78350_DATA_FLASH_REGISTER_Calibration_Current_Offset_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Calibration_Current_Offset_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_T1_Temp_Offset = 0x401E,
			_T2_Temp_Offset = 0x401F,
			_T3_Temp_Offset = 0x4020,
			_Gauge_Internal_Temp_Offset = 0x4021
		}kBQ78350_DATA_FLASH_REGISTER_Calibration_Temperature_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Calibration_Temperature_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Ext_Cell_Divider_Gain = 0x4022
		}kBQ78350_DATA_FLASH_REGISTER_Calibration_Ext_Cell_Voltage_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Calibration_Ext_Cell_Voltage_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_VAux_Gain = 0x4024
		}kBQ78350_DATA_FLASH_REGISTER_Calibration_VAux_Voltage_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Calibration_VAux_Voltage_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Coeff_a1 = 0x454F,
			_Coeff_a2 = 0x4551,
			_Coeff_a3 = 0x4553,
			_Coeff_a4 = 0x4555,
			_Coeff_a5 = 0x4557,
			_Coeff_b1 = 0x4559,
			_Coeff_b2 = 0x455B,
			_Coeff_b3 = 0x455D,
			_Coeff_b4 = 0x455F,
			_Rc0 = 0x4561,
			_Adc0 = 0x4563
		}kBQ78350_DATA_FLASH_REGISTER_Calibration_Cell_Temperature_Model_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Calibration_Cell_Temperature_Model_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Coeff_a1 = 0x4569,
			_Coeff_a2 = 0x456B,
			_Coeff_a3 = 0x456D,
			_Coeff_a4 = 0x456F,
			_Coeff_a5 = 0x4571,
			_Coeff_b1 = 0x4573,
			_Coeff_b2 = 0x4575,
			_Coeff_b3 = 0x4577,
			_Coeff_b4 = 0x4579,
			_Rc0 = 0x457B,
			_Adc0 = 0x457D,
			_Rpad = 0x457F,
			_Rint = 0x4581
		}kBQ78350_DATA_FLASH_REGISTER_Calibration_Fet_Temperature_Model_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Calibration_Fet_Temperature_Model_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Deadband = 0x4318,
			_Coulomb_Counter_Deadband = 0x4319
		}kBQ78350_DATA_FLASH_REGISTER_Calibration_Current_Deadband_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Calibration_Current_Deadband_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Protection_Configuration = 0x44C5,
			_Enabled_Protections_A = 0x44C6,
			_Enabled_Protections_B = 0x44C7,
			_Enabled_Protections_C = 0x44C8,
			_Enabled_Removal_Recovery_A = 0x44CA,
			_Enabled_Removal_Recovery_B = 0x44CB
		}kBQ78350_DATA_FLASH_REGISTER_Settings_Protection_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Settings_Protection_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Enabled_PF_A = 0x451D,
			_Enabled_PF_B = 0x451E
		}kBQ78350_DATA_FLASH_REGISTER_Settings_Permanent_Failure_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Settings_Permanent_Failure_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_FET_Options = 0x445F,
			_Sbs_Gauging_Configuration = 0x4461,
			_Smb_Configuration = 0x4462,
			_Power_Config = 0x4472,
			_LED_Configuration = 0x448C,
			_Temperature_Enable = 0x44A9,
			_Temperature_Mode = 0x44AA,
			_DA_Configuration = 0x44AB,
			_AFE_Cell_Map = 0x44AC,
			_CEDV_Gauging_Configuration = 0x458B,
			_SOC_Flag_Config = 0x45D4,
			_Balancing_Configuration = 0x460C
		}kBQ78350_DATA_FLASH_REGISTER_Settings_Configuration_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Settings_Configuration_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_PF_SAFE_A = 0x4458,
			_PF_SAFE_B = 0x4459,
			_PF_SAFE_C = 0x445A,
			_Fuse_Blow_Timeout = 0x445E
		}kBQ78350_DATA_FLASH_REGISTER_Settings_Fuse_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Settings_Fuse_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Addr_Reads = 0x4463,
			_SMBTAR_ADDR0 = 0x4464,
			_SMBTAR_ADDR1 = 0x4465,
			_SMBTAR_ADDR2 = 0x4466,
			_SMBTAR_ADDR3 = 0x4467,
			_SMBTAR_ADDR4 = 0x4468,
			_SMBTAR_ADDR5 = 0x4469,
			_SMBTAR_ADDR6 = 0x446A,
			_SMBTAR_ADDR7 = 0x446B
		}kBQ78350_DATA_FLASH_REGISTER_Settings_Aux_SMB_Address_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Settings_Aux_SMB_Address_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Host_Address = 0x446E,
			_Charger_Address = 0x446F,
			_Alarm_Timer = 0x4470,
			_Charger_Request_Timer = 0x4471
		}kBQ78350_DATA_FLASH_REGISTER_Settings_SMB_Master_Mode_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Settings_SMB_Master_Mode_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Mfg_Status_init = 0x42C8
		}kBQ78350_DATA_FLASH_REGISTER_Settings_Manufacturing_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Settings_Manufacturing_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x44CC,
			_Delay = 0x44CE,
			_Recovery = 0x44CF
		}kBQ78350_DATA_FLASH_REGISTER_Protections_CUV_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Protections_CUV_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x44D1,
			_Delay = 0x44D3,
			_Recovery = 0x44D4
		}kBQ78350_DATA_FLASH_REGISTER_Protections_COV_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Protections_COV_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x44D6,
			_Delay = 0x44D8,
			_Recovery_Threshold = 0x44D9,
			_Recovery_Delay = 0x44DB
		}kBQ78350_DATA_FLASH_REGISTER_Protections_OCC_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Protections_OCC_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x44DC,
			_Delay = 0x44DE,
			_Recovery_Threshold = 0x44DF,
			_Recovery_Delay = 0x44E1
		}kBQ78350_DATA_FLASH_REGISTER_Protections_OCD_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Protections_OCD_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Latch_Limit = 0x44E2,
			_Counter_Dec_Delay = 0x44E3,
			_Reset = 0x44E4
		}kBQ78350_DATA_FLASH_REGISTER_Protections_OCDL_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Protections_OCDL_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold_and_Delay = 0x44B1,
			_Latch_Limit = 0x44E5,
			_Counter_Dec_Delay = 0x44E6,
			_Recovery = 0x44E7,
			_Reset = 0x44E8
		}kBQ78350_DATA_FLASH_REGISTER_Protections_AOLD_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Protections_AOLD_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold_and_Delay = 0x44B0,
			_Latch_Limit = 0x44E9,
			_Counter_Dec_Delay = 0x44EA,
			_Recovery = 0x44EB,
			_Reset = 0x44EC
		}kBQ78350_DATA_FLASH_REGISTER_Protections_ASCD_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Protections_ASCD_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x44ED,
			_Delay = 0x44EF,
			_Recovery = 0x44F0
		}kBQ78350_DATA_FLASH_REGISTER_Protections_OTC_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Protections_OTC_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x44F2,
			_Delay = 0x44F4,
			_Recovery = 0x44F5
		}kBQ78350_DATA_FLASH_REGISTER_Protections_OTD_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Protections_OTD_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x44F7,
			_Delay = 0x44F9,
			_Recovery = 0x44FA
		}kBQ78350_DATA_FLASH_REGISTER_Protections_OTF_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Protections_OTF_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x44FC,
			_Delay = 0x44FE,
			_Recovery = 0x44FF
		}kBQ78350_DATA_FLASH_REGISTER_Protections_UTC_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Protections_UTC_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x4501,
			_Delay = 0x4503,
			_Recovery = 0x4504
		}kBQ78350_DATA_FLASH_REGISTER_Protections_UTD_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Protections_UTD_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Delay = 0x4506,
			_Recovery = 0x4507
		}kBQ78350_DATA_FLASH_REGISTER_Protections_AFE_External_Override_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Protections_AFE_External_Override_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Charge_Threshold = 0x4508,
			_Suspend_Threshold = 0x450A,
			_Delay = 0x450C,
			_Reset = 0x450E
		}kBQ78350_DATA_FLASH_REGISTER_Protections_PTO_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Protections_PTO_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Charge_Threshold = 0x4510,
			_Suspend_Threshold = 0x4512,
			_Delay = 0x4514,
			_Reset = 0x4516
		}kBQ78350_DATA_FLASH_REGISTER_Protections_CTO_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Protections_CTO_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x4518,
			_Recovery = 0x451A,
			_RSOC_Recovery = 0x451C
		}kBQ78350_DATA_FLASH_REGISTER_Protections_OC_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Protections_OC_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x4521,
			_Delay = 0x4523
		}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_SOCC_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_SOCC_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x4524,
			_Delay = 0x4526
		}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_SOCD_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_SOCD_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x4527,
			_Delay = 0x4529
		}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_SOT_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_SOT_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x452A,
			_Delay = 0x452C
		}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_SOTF_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_SOTF_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x452D,
			_Delay = 0x452F
		}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_Open_Thermistor_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_Open_Thermistor_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Check_Voltage = 0x4530,
			_Check_Current = 0x4532,
			_Delta_Threshold = 0x4534,
			_Delta_Delay = 0x4536,
			_Duration = 0x4537
		}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_VIMR_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_VIMR_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_OFF_Threshold = 0x4539,
			_OFF_Delay = 0x453B
		}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_CFET_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_CFET_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_OFF_Threshold = 0x453C,
			_OFF_Delay = 0x453E
		}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_DFET_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_DFET_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x453F,
			_Delay_Period = 0x4540,
			_Compare_Period = 0x4541
		}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFER_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFER_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x4542,
			_Delay_Period = 0x4543
		}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFEC_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFEC_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x4544,
			_Delay_Period = 0x4545
		}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFE_XREADY_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFE_XREADY_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Delay = 0x4546
		}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFE_External_Override_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFE_External_Override_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_SOV_and_SUV_Delay = 0x44B2
		}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFE_SOV_AFE_SUV_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFE_SOV_AFE_SUV_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x44B7
		}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFE_SOV_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFE_SOV_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Threshold = 0x44B9
		}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFE_SUV_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFE_SUV_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Charge_Inhibit_Suspend_Low_Temp = 0x45DF,
			_Precharge_Temp = 0x45E0,
			_Charge_Inhibit_High_Temp = 0x45E1,
			_Charge_Suspend_High_Temp = 0x45E2,
			_Hysteresis_Temp = 0x45E3
		}kBQ78350_DATA_FLASH_REGISTER_Charge_Algorithm_Temperature_Ranges_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Charge_Algorithm_Temperature_Ranges_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Voltage = 0x45E4,
			_Current = 0x45E6
		}kBQ78350_DATA_FLASH_REGISTER_Charge_Algorithm_Fast_Charging_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Charge_Algorithm_Fast_Charging_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Current = 0x45E8,
			_Start_Voltage = 0x45EA,
			_Recovery_Voltage = 0x45EC
		}kBQ78350_DATA_FLASH_REGISTER_Charge_Algorithm_PreCharging_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Charge_Algorithm_PreCharging_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Charge_Term_Taper_Current = 0x45EE,
			_Charge_Term_Voltage = 0x45F2
		}kBQ78350_DATA_FLASH_REGISTER_Charge_Algorithm_Termination_Config_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Charge_Algorithm_Termination_Config_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Cell_Balance_Threshold = 0x460D,
			_Cell_Balance_Window = 0x460F,
			_Cell_Balance_Min = 0x4611,
			_Cell_Balance_Interval = 0x4612
		}kBQ78350_DATA_FLASH_REGISTER_Charge_Algorithm_Cell_Balancing_Config_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Charge_Algorithm_Cell_Balancing_Config_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Dsg_Current_Threshold = 0x44BD,
			_Chg_Current_Threshold = 0x44BF,
			_Quit_Current = 0x44C1,
			_Dsg_Relax_Time = 0x44C3,
			_Chg_Relax_Time = 0x44C4
		}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_Current_Thresholds_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_Current_Thresholds_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Design_Capacity_mAh = 0x45CC,
			_Design_Capacity_cWh = 0x45CE,
			_Design_Voltage = 0x45D0
		}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_Design_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_Design_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Cycle_Count_Percentage = 0x45D2
		}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_Cycle_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_Cycle_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Set_Percent_RSOC_Threshold = 0x45D6,
			_Clear_Percent_RSOC_Threshold = 0x45D7
		}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_FD_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_FD_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Set_Percent_RSOC_Threshold = 0x45D8,
			_Clear_Percent_RSOC_Threshold = 0x45D9
		}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_FC_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_FC_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Set_Percent_RSOC_Threshold = 0x45DA,
			_Clear_Percent_RSOC_Threshold = 0x45DB
		}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_TD_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_TD_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Set_Percent_RSOC_Threshold = 0x45DC,
			_Clear_Percent_RSOC_Threshold = 0x45DD
		}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_TC_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_TC_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Learned_Full_Charge_Capacity = 0x42C2,
			_Dod_at_EDV2 = 0x42C4,
			_Cycle_Count = 0x42C6
		}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_State_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_State_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_EMF = 0x458D,
			_C0 = 0x458F,
			_R0 = 0x4591,
			_T0 = 0x4593,
			_R1 = 0x4595,
			_TC = 0x4597,
			_C1 = 0x4598,
			_Age_Factor = 0x4599,
			_Fixed_EDV_0 = 0x459A,
			_EDV_0_Hold_Time = 0x459C,
			_Fixed_EDV_1 = 0x459D,
			_EDV_1_Hold_Time = 0x459F,
			_Fixed_EDV_2 = 0x45A0,
			_EDV_2_Hold_Time = 0x45A2,
			_Battery_Low_Percent = 0x45A7,
			_Min_Delta_V_Filter = 0x45AB,
			_FCC_Learn_Up = 0x45AD,
			_FCC_Learn_Down = 0x45AF,
			_Learning_Low_Temp = 0x45B4,
			_Requested_Learning_cycle_count = 0x45BD,
			_OverLoad_Current = 0x45BE,
			_Self_Discharge_Rate = 0x45C2,
			_Electronics_Load = 0x45C3,
			_Near_Full = 0x45C5,
			_Reserve_Capacity = 0x45C7,
			_RemCap_Init_Percent = 0x45CB
		}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_CEDV_cfg_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_CEDV_cfg_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Valid_Update_Voltage = 0x4473
		}kBQ78350_DATA_FLASH_REGISTER_Power_Power_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Power_Power_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Shutdown_Voltage = 0x4475,
			_Shutdown_Time = 0x4477,
			_PF_Shutdown_Voltage = 0x4478,
			_PF_Shutdown_Time = 0x447A,
			_Charger_Present_Threshold = 0x447B
		}kBQ78350_DATA_FLASH_REGISTER_Power_Shutdown_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Power_Shutdown_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Sleep_Current = 0x447D,
			_Bus_Timeout = 0x447F,
			_Voltage_Time = 0x4484,
			_Current_Time = 0x4485
		}kBQ78350_DATA_FLASH_REGISTER_Power_Sleep_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Power_Sleep_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_FET_Off_Time = 0x4487,
			_Delay = 0x4488,
			_Auto_Ship_Time = 0x4489
		}kBQ78350_DATA_FLASH_REGISTER_Power_Ship_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Power_Ship_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Time = 0x448B
		}kBQ78350_DATA_FLASH_REGISTER_Power_KEYIN_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Power_KEYIN_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Safety_Alert_A = 0x41C0,
			_Safety_Status_A = 0x41C1,
			_Safety_Alert_B = 0x41C2,
			_Safety_Status_B = 0x41C3,
			_Safety_Alert_C = 0x41C4,
			_Safety_Status_C = 0x41C5,
			_PF_Alert_A = 0x41C8,
			_PF_Status_A = 0x41C9,
			_PF_Alert_B = 0x41CA,
			_PF_Status_B = 0x41CB,
			_PF_Alert_C = 0x41CC,
			_PF_Status_C = 0x41CD,
			_Fuse_Flag = 0x41D0,
			_Operation_Status_A = 0x41D2,
			_Operation_Status_B = 0x41D4,
			_Temp_Range = 0x41D6,
			_Charging_Status = 0x41D7,
			_Gauging_Status = 0x41D8,
			_CEDV_Status = 0x41D9
		}kBQ78350_DATA_FLASH_REGISTER_PF_Status_Device_Status_Data_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_PF_Status_Device_Status_Data_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Cell_1_Voltage = 0x41DA,
			_Cell_2_Voltage = 0x41DC,
			_Cell_3_Voltage = 0x41DE,
			_Cell_4_Voltage = 0x41E0,
			_Cell_5_Voltage = 0x41E2,
			_Cell_6_Voltage = 0x41E4,
			_Cell_7_Voltage = 0x41E6,
			_Cell_8_Voltage = 0x41E8,
			_Cell_9_Voltage = 0x41EA,
			_Cell_10_Voltage = 0x41EC,
			_Cell_11_Voltage = 0x41EE,
			_Cell_12_Voltage = 0x41F0,
			_Cell_13_Voltage = 0x41F2,
			_Cell_14_Voltage = 0x41F4,
			_Cell_15_Voltage = 0x41F6,
			_Battery_Direct_Voltage = 0x41FA
		}kBQ78350_DATA_FLASH_REGISTER_PF_Status_Device_Voltage_Data_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_PF_Status_Device_Voltage_Data_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Current = 0x41FE
		}kBQ78350_DATA_FLASH_REGISTER_PF_Status_Device_Current_Data_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_PF_Status_Device_Current_Data_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_TS1_Temperature = 0x4200,
			_TS2_Temperature = 0x4202,
			_TS3_Temperature = 0x4204,
			_Gauge_Internal_Temperature = 0x4206
		}kBQ78350_DATA_FLASH_REGISTER_PF_Status_Device_Temperature_Data_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_PF_Status_Device_Temperature_Data_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_AFE_SYS_Stat = 0x4208,
			_AFE_Cell_Balance1 = 0x4209,
			_AFE_Cell_Balance2 = 0x420A,
			_AFE_Cell_Balance3 = 0x420B,
			_AFE_Sys_Control1 = 0x420C,
			_AFE_Sys_Control2 = 0x420D,
			_AFE_Protection1 = 0x420E,
			_AFE_Protection2 = 0x420F,
			_AFE_Protection3 = 0x4210,
			_AFE_OV_Trip = 0x4211,
			_AFE_UV_Trip = 0x4212
		}kBQ78350_DATA_FLASH_REGISTER_PF_Status_AFE_Regs_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_PF_Status_AFE_Regs_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_1st_Status_Status_A = 0x4180,
			_1st_Status_Status_B = 0x4181,
			_1st_Safety_Status_C = 0x4182,
			_1st_Time_to_Next_Event = 0x4184,
			_2nd_Status_Status_A = 0x4185,
			_2nd_Status_Status_B = 0x4186,
			_2nd_Safety_Status_C = 0x4187,
			_2nd_Time_to_Next_Event = 0x4189,
			_3rd_Status_Status_A = 0x418A,
			_3rd_Status_Status_B = 0x418B,
			_3rd_Safety_Status_C = 0x418C,
			_3rd_Time_to_Next_Event = 0x418E
		}kBQ78350_DATA_FLASH_REGISTER_Black_Box_Safety_Status_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Black_Box_Safety_Status_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_1st_PF_Status_A = 0x418F,
			_1st_PF_Status_B = 0x4190,
			_1st_PF_Status_C = 0x4191,
			_1st_Time_to_Next_Event = 0x4193,
			_2nd_PF_Status_A = 0x4194,
			_2nd_PF_Status_B = 0x4195,
			_2nd_PF_Status_C = 0x4196,
			_2nd_Time_to_Next_Event = 0x4198,
			_3rd_PF_Status_A = 0x4199,
			_3rd_PF_Status_B = 0x419A,
			_3rd_PF_Status_C = 0x419B,
			_3rd_Time_to_Next_Event = 0x419D
		}kBQ78350_DATA_FLASH_REGISTER_Black_Box_PF_Status_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Black_Box_PF_Status_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Manufacturer_Info_A_Length = 0x4040,
			_Manufacturer_Info_Block_A01 = 0x4041,
			_Manufacturer_Info_Block_A02 = 0x4042,
			_Manufacturer_Info_Block_A03 = 0x4043,
			_Manufacturer_Info_Block_A04 = 0x4044,
			_Manufacturer_Info_Block_A05 = 0x4045,
			_Manufacturer_Info_Block_A06 = 0x4046,
			_Manufacturer_Info_Block_A07 = 0x4047,
			_Manufacturer_Info_Block_A08 = 0x4048,
			_Manufacturer_Info_Block_A09 = 0x4049,
			_Manufacturer_Info_Block_A10 = 0x404A,
			_Manufacturer_Info_Block_A11 = 0x404B,
			_Manufacturer_Info_Block_A12 = 0x404C,
			_Manufacturer_Info_Block_A13 = 0x404D,
			_Manufacturer_Info_Block_A14 = 0x404E,
			_Manufacturer_Info_Block_A15 = 0x404F,
			_Manufacturer_Info_Block_A16 = 0x4050,
			_Manufacturer_Info_Block_A17 = 0x4051,
			_Manufacturer_Info_Block_A18 = 0x4052,
			_Manufacturer_Info_Block_A19 = 0x4053,
			_Manufacturer_Info_Block_A20 = 0x4054,
			_Manufacturer_Info_Block_A21 = 0x4055,
			_Manufacturer_Info_Block_A22 = 0x4056,
			_Manufacturer_Info_Block_A23 = 0x4057,
			_Manufacturer_Info_Block_A24 = 0x4058,
			_Manufacturer_Info_Block_A25 = 0x4059,
			_Manufacturer_Info_Block_A26 = 0x405A,
			_Manufacturer_Info_Block_A27 = 0x405B,
			_Manufacturer_Info_Block_A28 = 0x405C,
			_Manufacturer_Info_Block_A29 = 0x405D,
			_Manufacturer_Info_Block_A30 = 0x405E,
			_Manufacturer_Info_Block_A31 = 0x405F,
			_Manufacturer_Info_Block_A32 = 0x4060
		}kBQ78350_DATA_FLASH_REGISTER_System_Data_Manufacturer_Data_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_System_Data_Manufacturer_Data_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Manufacture_Date = 0x406B,
			_Serial_Number = 0x406D,
			_Manufacturer_Name = 0x406F,
			_Device_Name = 0x4084,
			_Device_Chemistry = 0x4099,
			_Remaining_AH_Cap_Alarm = 0x449F,
			_Remaining_WH_Cap_Alarm = 0x44A1,
			_Remaining_Time_Alarm = 0x44A3,
			_Initial_Battery_Mode = 0x44A5,
			_Specification_Information = 0x44A7
		}kBQ78350_DATA_FLASH_REGISTER_SBS_Configuration_Data_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_SBS_Configuration_Data_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_LED_Flash_Period = 0x448D,
			_LED_Blink_Period = 0x448F,
			_LED_Delay = 0x4491,
			_LED_Hold_Time = 0x4493,
			_LED_Flash_Alarm = 0x4494,
			_LED_Thresh_1 = 0x4495,
			_LED_Thresh_2 = 0x4496,
			_LED_Thresh_3 = 0x4497,
			_LED_Thresh_4 = 0x4498,
			_LED_Thresh_5 = 0x4499,
			_LCD_Refresh_Rate = 0x449A
		}kBQ78350_DATA_FLASH_REGISTER_LED_Support_LED_Config_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_LED_Support_LED_Config_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Cell_1_Max_Voltage = 0x40C0,
			_Cell_2_Max_Voltage = 0x40C2,
			_Cell_3_Max_Voltage = 0x40C4,
			_Cell_4_Max_Voltage = 0x40C6,
			_Cell_5_Max_Voltage = 0x40C8,
			_Cell_6_Max_Voltage = 0x40CA,
			_Cell_7_Max_Voltage = 0x40CC,
			_Cell_8_Max_Voltage = 0x40CE,
			_Cell_9_Max_Voltage = 0x40D0,
			_Cell_10_Max_Voltage = 0x40D2,
			_Cell_11_Max_Voltage = 0x40D4,
			_Cell_12_Max_Voltage = 0x40D6,
			_Cell_13_Max_Voltage = 0x40D8,
			_Cell_14_Max_Voltage = 0x40DA,
			_Cell_15_Max_Voltage = 0x40DC,
			_Cell_1_Min_Voltage = 0x40E0,
			_Cell_2_Min_Voltage = 0x40E2,
			_Cell_3_Min_Voltage = 0x40E4,
			_Cell_4_Min_Voltage = 0x40E6,
			_Cell_5_Min_Voltage = 0x40E8,
			_Cell_6_Min_Voltage = 0x40EA,
			_Cell_7_Min_Voltage = 0x40EC,
			_Cell_8_Min_Voltage = 0x40EE,
			_Cell_9_Min_Voltage = 0x40F0,
			_Cell_10_Min_Voltage = 0x40F2,
			_Cell_11_Min_Voltage = 0x40F4,
			_Cell_12_Min_Voltage = 0x40F6,
			_Cell_13_Min_Voltage = 0x40F8,
			_Cell_14_Min_Voltage = 0x40FA,
			_Cell_15_Min_Voltage = 0x40FC,
			_Max_Delta_Cell_Voltage = 0x4100
		}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Voltage_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Voltage_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Max_Charge_Current = 0x4102,
			_Max_Discharge_Current = 0x4104,
			_Max_Avg_Dsg_Current = 0x4106,
			_Max_Avg_Dsg_Power = 0x4108
		}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Current_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Current_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Max_Temp_Cell = 0x410A,
			_Min_Temp_Cell = 0x410B,
			_Max_Delta_Cell_Temp = 0x410C,
			_Max_Temp_Fet = 0x410D
		}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Temperature_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Temperature_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Max_Temp_Int_Sensor = 0x410E,
			_Min_Temp_Int_Sensor = 0x410F
		}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Gauge_Temperature_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Gauge_Temperature_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_No_Of_COV_Events = 0x4110,
			_Last_COV_Event = 0x4112,
			_No_Of_CUV_Events = 0x4114,
			_Last_CUV_Event = 0x4116,
			_No_Of_OCD_Events = 0x4118,
			_Last_OCD_Event = 0x411A,
			_No_Of_OCC_Events = 0x411C,
			_Last_OCC_Event = 0x411E,
			_No_Of_AOLD_Events = 0x4120,
			_Last_AOLD_Event = 0x4122,
			_No_Of_ASCD_Events = 0x4124,
			_Last_ASCD_Event = 0x4126,
			_No_Of_OTC_Events = 0x4128,
			_Last_OTC_Event = 0x412A,
			_No_Of_OTD_Events = 0x412C,
			_Last_OTD_Event = 0x412E,
			_No_Of_OTF_Events = 0x4130,
			_Last_OTF_Event = 0x4132
		}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Safety_Events_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Safety_Events_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_No_Valid_Charge_Term = 0x4134,
			_Last_Valid_Charge_Term = 0x4136
		}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Charging_Events_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Charging_Events_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_No_of_FCC_Updates = 0x4138,
			_Last_FCC_Update = 0x413A
		}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Gauging_Events_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Gauging_Events_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_No_Of_Shutdowns = 0x413C
		}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Power_Events_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Power_Events_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Cb_Time_Cell_1 = 0x4140,
			_Cb_Time_Cell_2 = 0x4141,
			_Cb_Time_Cell_3 = 0x4142,
			_Cb_Time_Cell_4 = 0x4143,
			_Cb_Time_Cell_5 = 0x4144,
			_Cb_Time_Cell_6 = 0x4145,
			_Cb_Time_Cell_7 = 0x4146,
			_Cb_Time_Cell_8 = 0x4147,
			_Cb_Time_Cell_9 = 0x4148,
			_Cb_Time_Cell_10 = 0x4149,
			_Cb_Time_Cell_11 = 0x414A,
			_Cb_Time_Cell_12 = 0x414B,
			_Cb_Time_Cell_13 = 0x414C,
			_Cb_Time_Cell_14 = 0x414D,
			_Cb_Time_Cell_15 = 0x414E
		}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Cell_Balancing_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Cell_Balancing_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_Total_Fw_Runtime = 0x4150,
			_Time_Spent_In_UT = 0x4152,
			_Time_Spent_In_LT = 0x4154,
			_Time_Spent_In_ST = 0x4156,
			_Time_Spent_In_HT = 0x4158,
			_Time_Spent_In_OT = 0x415A,
			_Time_Since_Last_Charge = 0x415C
		}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Time_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Time_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			_GPIO_Configuration = 0x449B,
			_GPIO_Output_Enable = 0x449C,
			_GPIO_Default_Output_Enable = 0x449D,
			_GPIO_Type = 0x449E
		}kBQ78350_DATA_FLASH_REGISTER_GPIO_GPIO_Config_SELECT_ENUM;
	}kBQ78350_DATA_FLASH_REGISTER_GPIO_GPIO_Config_SELECT_STRUCT;

	typedef struct
	{
		kBQ78350_DATA_FLASH_REGISTER_Calibration_Current_SELECT_STRUCT _Current;
		kBQ78350_DATA_FLASH_REGISTER_Calibration_Voltage_SELECT_STRUCT _Voltage;
		kBQ78350_DATA_FLASH_REGISTER_Calibration_Current_Offset_SELECT_STRUCT _Current_Offset;
		kBQ78350_DATA_FLASH_REGISTER_Calibration_Temperature_SELECT_STRUCT _Temperature;
		kBQ78350_DATA_FLASH_REGISTER_Calibration_Ext_Cell_Voltage_SELECT_STRUCT _Ext_Cell_Voltage;
		kBQ78350_DATA_FLASH_REGISTER_Calibration_VAux_Voltage_SELECT_STRUCT _VAux_Voltage;
		kBQ78350_DATA_FLASH_REGISTER_Calibration_Cell_Temperature_Model_SELECT_STRUCT _Cell_Temperature_Model;
		kBQ78350_DATA_FLASH_REGISTER_Calibration_Fet_Temperature_Model_SELECT_STRUCT _Fet_Temperature_Model;
		kBQ78350_DATA_FLASH_REGISTER_Calibration_Current_Deadband_SELECT_STRUCT _Current_Deadband;
	}kBQ78350_DATA_FLASH_REGISTER_Calibration_SELECT_SELECT_STRUCT;

	typedef struct
	{
		kBQ78350_DATA_FLASH_REGISTER_Settings_Protection_SELECT_STRUCT _Protection;
		kBQ78350_DATA_FLASH_REGISTER_Settings_Permanent_Failure_SELECT_STRUCT _Permanent_Failure;
		kBQ78350_DATA_FLASH_REGISTER_Settings_Configuration_SELECT_STRUCT _Configuration;
		kBQ78350_DATA_FLASH_REGISTER_Settings_Fuse_SELECT_STRUCT _Fuse;
		kBQ78350_DATA_FLASH_REGISTER_Settings_Aux_SMB_Address_SELECT_STRUCT _Aux_SMB_Address;
		kBQ78350_DATA_FLASH_REGISTER_Settings_SMB_Master_Mode_SELECT_STRUCT _SMB_Master_Mode;
		kBQ78350_DATA_FLASH_REGISTER_Settings_Manufacturing_SELECT_STRUCT _Manufacturing;
	}kBQ78350_DATA_FLASH_REGISTER_Settings_SELECT_SELECT_STRUCT;

	typedef struct
	{
		kBQ78350_DATA_FLASH_REGISTER_Protections_CUV_SELECT_STRUCT _CUV;
		kBQ78350_DATA_FLASH_REGISTER_Protections_COV_SELECT_STRUCT _COV;
		kBQ78350_DATA_FLASH_REGISTER_Protections_OCC_SELECT_STRUCT _OCC;
		kBQ78350_DATA_FLASH_REGISTER_Protections_OCD_SELECT_STRUCT _OCD;
		kBQ78350_DATA_FLASH_REGISTER_Protections_OCDL_SELECT_STRUCT _OCDL;
		kBQ78350_DATA_FLASH_REGISTER_Protections_AOLD_SELECT_STRUCT _AOLD;
		kBQ78350_DATA_FLASH_REGISTER_Protections_ASCD_SELECT_STRUCT _ASCD;
		kBQ78350_DATA_FLASH_REGISTER_Protections_OTC_SELECT_STRUCT _OTC;
		kBQ78350_DATA_FLASH_REGISTER_Protections_OTD_SELECT_STRUCT _OTD;
		kBQ78350_DATA_FLASH_REGISTER_Protections_OTF_SELECT_STRUCT _OTF;
		kBQ78350_DATA_FLASH_REGISTER_Protections_UTC_SELECT_STRUCT _UTC;
		kBQ78350_DATA_FLASH_REGISTER_Protections_UTD_SELECT_STRUCT _UTD;
		kBQ78350_DATA_FLASH_REGISTER_Protections_AFE_External_Override_SELECT_STRUCT _AFE_External_Override;
		kBQ78350_DATA_FLASH_REGISTER_Protections_PTO_SELECT_STRUCT _PTO;
		kBQ78350_DATA_FLASH_REGISTER_Protections_CTO_SELECT_STRUCT _CTO;
		kBQ78350_DATA_FLASH_REGISTER_Protections_OC_SELECT_STRUCT _OC;
	}kBQ78350_DATA_FLASH_REGISTER_Protections_SELECT_SELECT_STRUCT;

	typedef struct
	{
		kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_SOCC_SELECT_STRUCT _SOCC;
		kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_SOCD_SELECT_STRUCT _SOCD;
		kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_SOT_SELECT_STRUCT _SOT;
		kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_SOTF_SELECT_STRUCT _SOTF;
		kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_Open_Thermistor_SELECT_STRUCT _Open_Thermistor;
		kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_VIMR_SELECT_STRUCT _VIMR;
		kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_CFET_SELECT_STRUCT _CFET;
		kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_DFET_SELECT_STRUCT _DFET;
		kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFER_SELECT_STRUCT _AFER;
		kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFEC_SELECT_STRUCT _AFEC;
		kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFE_XREADY_SELECT_STRUCT _AFE_XREADY;
		kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFE_External_Override_SELECT_STRUCT _AFE_External_Override;
		kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFE_SOV_AFE_SUV_SELECT_STRUCT _AFE_SOV_AFE_SUV;
		kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFE_SOV_SELECT_STRUCT _AFE_SOV;
		kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_AFE_SUV_SELECT_STRUCT _AFE_SUV;
	}kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_SELECT_SELECT_STRUCT;

	typedef struct
	{
		kBQ78350_DATA_FLASH_REGISTER_Charge_Algorithm_Temperature_Ranges_SELECT_STRUCT _Temperature_Ranges;
		kBQ78350_DATA_FLASH_REGISTER_Charge_Algorithm_Fast_Charging_SELECT_STRUCT _Fast_Charging;
		kBQ78350_DATA_FLASH_REGISTER_Charge_Algorithm_PreCharging_SELECT_STRUCT _PreCharging;
		kBQ78350_DATA_FLASH_REGISTER_Charge_Algorithm_Termination_Config_SELECT_STRUCT _Termination_Config;
		kBQ78350_DATA_FLASH_REGISTER_Charge_Algorithm_Cell_Balancing_Config_SELECT_STRUCT _Cell_Balancing_Config;
	}kBQ78350_DATA_FLASH_REGISTER_Charge_Algorithm_SELECT_SELECT_STRUCT;

	typedef struct
	{
		kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_Current_Thresholds_SELECT_STRUCT _Current_Thresholds;
		kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_Design_SELECT_STRUCT _Design;
		kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_Cycle_SELECT_STRUCT _Cycle;
		kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_FD_SELECT_STRUCT _FD;
		kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_FC_SELECT_STRUCT _FC;
		kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_TD_SELECT_STRUCT _TD;
		kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_TC_SELECT_STRUCT _TC;
		kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_State_SELECT_STRUCT _State;
		kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_CEDV_cfg_SELECT_STRUCT _CEDV_cfg;
	}kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_SELECT_SELECT_STRUCT;

	typedef struct
	{
		kBQ78350_DATA_FLASH_REGISTER_Power_Power_SELECT_STRUCT _Power;
		kBQ78350_DATA_FLASH_REGISTER_Power_Shutdown_SELECT_STRUCT _Shutdown;
		kBQ78350_DATA_FLASH_REGISTER_Power_Sleep_SELECT_STRUCT _Sleep;
		kBQ78350_DATA_FLASH_REGISTER_Power_Ship_SELECT_STRUCT _Ship;
		kBQ78350_DATA_FLASH_REGISTER_Power_KEYIN_SELECT_STRUCT _KEYIN;
	}kBQ78350_DATA_FLASH_REGISTER_Power_SELECT_SELECT_STRUCT;

	typedef struct
	{
		kBQ78350_DATA_FLASH_REGISTER_PF_Status_Device_Status_Data_SELECT_STRUCT _Device_Status_Data;
		kBQ78350_DATA_FLASH_REGISTER_PF_Status_Device_Voltage_Data_SELECT_STRUCT _Device_Voltage_Data;
		kBQ78350_DATA_FLASH_REGISTER_PF_Status_Device_Current_Data_SELECT_STRUCT _Device_Current_Data;
		kBQ78350_DATA_FLASH_REGISTER_PF_Status_Device_Temperature_Data_SELECT_STRUCT _Device_Temperature_Data;
		kBQ78350_DATA_FLASH_REGISTER_PF_Status_AFE_Regs_SELECT_STRUCT _AFE_Regs;
	}kBQ78350_DATA_FLASH_REGISTER_PF_Status_SELECT_SELECT_STRUCT;

	typedef struct
	{
		kBQ78350_DATA_FLASH_REGISTER_Black_Box_Safety_Status_SELECT_STRUCT _Safety_Status;
		kBQ78350_DATA_FLASH_REGISTER_Black_Box_PF_Status_SELECT_STRUCT _PF_Status;
	}kBQ78350_DATA_FLASH_REGISTER_Black_Box_SELECT_SELECT_STRUCT;

	typedef struct
	{
		kBQ78350_DATA_FLASH_REGISTER_System_Data_Manufacturer_Data_SELECT_STRUCT _Manufacturer_Data;
	}kBQ78350_DATA_FLASH_REGISTER_System_Data_SELECT_SELECT_STRUCT;

	typedef struct
	{
		kBQ78350_DATA_FLASH_REGISTER_SBS_Configuration_Data_SELECT_STRUCT _Data;
	}kBQ78350_DATA_FLASH_REGISTER_SBS_Configuration_SELECT_SELECT_STRUCT;

	typedef struct
	{
		kBQ78350_DATA_FLASH_REGISTER_LED_Support_LED_Config_SELECT_STRUCT _LED_Config;
	}kBQ78350_DATA_FLASH_REGISTER_LED_Support_SELECT_SELECT_STRUCT;

	typedef struct
	{
		kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Voltage_SELECT_STRUCT _Voltage;
		kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Current_SELECT_STRUCT _Current;
		kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Temperature_SELECT_STRUCT _Temperature;
		kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Gauge_Temperature_SELECT_STRUCT _Gauge_Temperature;
		kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Safety_Events_SELECT_STRUCT _Safety_Events;
		kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Charging_Events_SELECT_STRUCT _Charging_Events;
		kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Gauging_Events_SELECT_STRUCT _Gauging_Events;
		kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Power_Events_SELECT_STRUCT _Power_Events;
		kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Cell_Balancing_SELECT_STRUCT _Cell_Balancing;
		kBQ78350_DATA_FLASH_REGISTER_Lifetimes_Time_SELECT_STRUCT _Time;
	}kBQ78350_DATA_FLASH_REGISTER_Lifetimes_SELECT_SELECT_STRUCT;

	typedef struct
	{
		kBQ78350_DATA_FLASH_REGISTER_GPIO_GPIO_Config_SELECT_STRUCT _GPIO_Config;
	}kBQ78350_DATA_FLASH_REGISTER_GPIO_SELECT_SELECT_STRUCT;

	typedef struct
	{
		kBQ78350_DATA_FLASH_REGISTER_Calibration_SELECT_SELECT_STRUCT _Calibration;
		kBQ78350_DATA_FLASH_REGISTER_Settings_SELECT_SELECT_STRUCT _Settings;
		kBQ78350_DATA_FLASH_REGISTER_Protections_SELECT_SELECT_STRUCT _Protections;
		kBQ78350_DATA_FLASH_REGISTER_Permanent_Fail_SELECT_SELECT_STRUCT _Permanent_Fail;
		kBQ78350_DATA_FLASH_REGISTER_Charge_Algorithm_SELECT_SELECT_STRUCT _Charge_Algorithm;
		kBQ78350_DATA_FLASH_REGISTER_Fuel_Gauging_SELECT_SELECT_STRUCT _Fuel_Gauging;
		kBQ78350_DATA_FLASH_REGISTER_Power_SELECT_SELECT_STRUCT _Power;
		kBQ78350_DATA_FLASH_REGISTER_PF_Status_SELECT_SELECT_STRUCT _PF_Status;
		kBQ78350_DATA_FLASH_REGISTER_Black_Box_SELECT_SELECT_STRUCT _Black_Box;
		kBQ78350_DATA_FLASH_REGISTER_System_Data_SELECT_SELECT_STRUCT _System_Data;
		kBQ78350_DATA_FLASH_REGISTER_SBS_Configuration_SELECT_SELECT_STRUCT _SBS_Configuration;
		kBQ78350_DATA_FLASH_REGISTER_LED_Support_SELECT_SELECT_STRUCT _LED_Support;
		kBQ78350_DATA_FLASH_REGISTER_Lifetimes_SELECT_SELECT_STRUCT _Lifetimes;
		kBQ78350_DATA_FLASH_REGISTER_GPIO_SELECT_SELECT_STRUCT _GPIO;
	}kBQ78350_DATA_FLASH_REGISTER_SELECT_SELECT_SELECT_STRUCT;

	typedef struct
	{
		typedef enum
		{
			RemainingCapacityAlarm = 0x01,	// ACCESS: R/W,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: ,	UNIT: 300 mAh or 10 mWh
			RemainingTimeAlarm = 0x02,  	// ACCESS: R/W,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: ,	UNIT: 10 min
			BatteryMode = 0x03,         	// ACCESS: R/W,	DATA TYPE: hex,	DATA SIZE: 2,	MIN: 0x0000,	MAX: 0xFFFF,	DEFAULT: -,	UNIT: 
			AtRate = 0x04,              	// ACCESS: R/W,	DATA TYPE: integer,	DATA SIZE: 2,	MIN: –32768,	MAX: 32767,	DEFAULT: -,	UNIT: mAh or 10 mWh
			AtRateTimeToFull = 0x05,    	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65534,	DEFAULT: -,	UNIT: min
			AtRateTimeToEmpty = 0x06,   	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65534,	DEFAULT: -,	UNIT: min
			AtRateOK = 0x07,            	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: 
			Temperature = 0x08,         	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: 0.1°K
			Voltage = 0x09,             	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			Current = 0x0A,             	// ACCESS: R,	DATA TYPE: integer,	DATA SIZE: 2,	MIN: –32768,	MAX: 32767,	DEFAULT: -,	UNIT: mA
			AverageCurrent = 0x0B,      	// ACCESS: R,	DATA TYPE: integer,	DATA SIZE: 2,	MIN: –32768,	MAX: 32767,	DEFAULT: -,	UNIT: mA
			MaxError = 0x0C,            	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 1,	MIN: 0,	MAX: 1,	DEFAULT: -,	UNIT: 
			RelativeStateOfCharge = 0x0D,	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 1,	MIN: 0,	MAX: 1,	DEFAULT: -,	UNIT: 
			AbsoluteStateOfCharge = 0x0E,	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 1,	MIN: 0,	MAX: 1,	DEFAULT: -,	UNIT: 
			RemainingCapacity = 0x0F,   	// ACCESS: R/W,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mAh or 10 mWh
			FullChargeCapacity = 0x10,  	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mAh or 10 mWh
			RunTimeToEmpty = 0x11,      	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65534,	DEFAULT: -,	UNIT: min
			AverageTimeToEmpty = 0x12,  	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65534,	DEFAULT: -,	UNIT: min
			AverageTimeToFull = 0x13,   	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65534,	DEFAULT: -,	UNIT: min
			ChargingCurrent = 0x14,     	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65534,	DEFAULT: -,	UNIT: mA
			ChargingVoltage = 0x15,     	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65534,	DEFAULT: -,	UNIT: mV
			BatteryStatus = 0x16,       	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0x0000,	MAX: 0xdbff,	DEFAULT: -,	UNIT: 
			CycleCount = 0x17,          	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: 
			DesignCapacity = 0x18,      	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mAh or 10 mWh
			DesignVoltage = 0x19,       	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			SpecificationInfo = 0x1A,   	// ACCESS: R,	DATA TYPE: hex,	DATA SIZE: 2,	MIN: 0x0000,	MAX: 0xFFFF,	DEFAULT: 0x0031,	UNIT: 
			ManufacturerDate = 0x1B,    	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: 
			SerialNumber = 0x1C,        	// ACCESS: R,	DATA TYPE: hex,	DATA SIZE: 2,	MIN: 0x0000,	MAX: 0xFFFF,	DEFAULT: 0x0001,	UNIT: 
			ManufacturerName = 0x20,    	// ACCESS: R,	DATA TYPE: string,	DATA SIZE: 11+1,	MIN: -,	MAX: -,	DEFAULT: Texas Instruments,	UNIT: ASCII
			DeviceName = 0x21,          	// ACCESS: R,	DATA TYPE: string,	DATA SIZE: 7+1,	MIN: -,	MAX: -,	DEFAULT: bq78350,	UNIT: ASCII
			DeviceChemistry = 0x22,     	// ACCESS: R,	DATA TYPE: string,	DATA SIZE: 4+1,	MIN: -,	MAX: -,	DEFAULT: LION,	UNIT: ASCII
			ManufacturerData = 0x23,    	// ACCESS: R,	DATA TYPE: String 14+1,	DATA SIZE: -,	MIN: -,	MAX: -,	DEFAULT: ASCII,	UNIT: 
			HostFETControl = 0x2B,      	// ACCESS: R/W,	DATA TYPE: hex,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: -
			GPIOStatus = 0x2C,          	// ACCESS: R,	DATA TYPE: hex,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: 
			GPIOControl = 0x2D,         	// ACCESS: R/W,	DATA TYPE: hex,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: 
			VAUXVoltage = 0x2E,         	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: 1,	UNIT: 
			Authenticate = 0x2F,        	// ACCESS: R/W,	DATA TYPE: hex,	DATA SIZE: 20+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: 
			Reserved = 0x30,            	// ACCESS: R,	DATA TYPE: -,	DATA SIZE: -,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: -
			CellVoltage15 = 0x31,       	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			CellVoltage14 = 0x32,       	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			CellVoltage13 = 0x33,       	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			CellVoltage12 = 0x34,       	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			CellVoltage11 = 0x35,       	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			CellVoltage10 = 0x36,       	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			CellVoltage9 = 0x37,        	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			CellVoltage8 = 0x38,        	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			CellVoltage7 = 0x39,        	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			CellVoltage6 = 0x3A,        	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			CellVoltage5 = 0x3B,        	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			CellVoltage4 = 0x3C,        	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			CellVoltage3 = 0x3D,        	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			CellVoltage2 = 0x3E,        	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			CellVoltage1 = 0x3F,        	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			DynamicPower = 0x4C,        	// ACCESS: R,	DATA TYPE: signed int,	DATA SIZE: 2,	MIN: –32768,	MAX: 32767,	DEFAULT: -,	UNIT: 10 mW
			ExtAveCellVoltage = 0x4D,   	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			PendingEDV = 0x4E,          	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 2,	MIN: 0,	MAX: 65535,	DEFAULT: -,	UNIT: mV
			StateOfHealth = 0x4F,       	// ACCESS: R,	DATA TYPE: unsigned int,	DATA SIZE: 1,	MIN: 0,	MAX: 1,	DEFAULT: -,	UNIT: 
			SafetyAlert = 0x50,         	// ACCESS: R,	DATA TYPE: hex,	DATA SIZE: 4+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: -
			SafetyStatus = 0x51,        	// ACCESS: R,	DATA TYPE: hex,	DATA SIZE: 4+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: -
			PFAlert = 0x52,             	// ACCESS: R,	DATA TYPE: hex,	DATA SIZE: 2+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: -
			PFStatus = 0x53,            	// ACCESS: R,	DATA TYPE: hex,	DATA SIZE: 4+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: -
			OperationStatus = 0x54,     	// ACCESS: R,	DATA TYPE: hex,	DATA SIZE: 4+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: -
			ChargingStatus = 0x55,      	// ACCESS: R,	DATA TYPE: hex,	DATA SIZE: 2+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: -
			GaugingStatus = 0x56,       	// ACCESS: R,	DATA TYPE: hex,	DATA SIZE: 2+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: -
			ManufacturingStatus = 0x57, 	// ACCESS: R,	DATA TYPE: hex,	DATA SIZE: 2+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: -
			AFEStatus = 0x58,           	// ACCESS: R,	DATA TYPE: hex,	DATA SIZE: 2+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: -
			AFEConfig = 0x59,           	// ACCESS: R,	DATA TYPE: String 10+1,	DATA SIZE: -,	MIN: -,	MAX: -,	DEFAULT: ,	UNIT: ASCII
			AFEVCx = 0x5A,              	// ACCESS: R,	DATA TYPE: String,	DATA SIZE: 32+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: ASCII
			AFEData = 0x5B,             	// ACCESS: R,	DATA TYPE: String,	DATA SIZE: 13+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: ASCII
			LifetimeDataBlock1 = 0x60,  	// ACCESS: R,	DATA TYPE: String,	DATA SIZE: 32+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: 
			LifetimeDataBlock2 = 0x61,  	// ACCESS: R,	DATA TYPE: String,	DATA SIZE: 32+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: 
			LifetimeDataBlock3 = 0x62,  	// ACCESS: R,	DATA TYPE: String,	DATA SIZE: 14+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: 
			LifetimeDataBlock4 = 0x63,  	// ACCESS: R,	DATA TYPE: String,	DATA SIZE: 20+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: 
			LifetimeDataBlock5 = 0x64,  	// ACCESS: R,	DATA TYPE: String,	DATA SIZE: 14+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: 
			LifetimeDataBlock6 = 0x65,  	// ACCESS: R,	DATA TYPE: String,	DATA SIZE: 32+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: 
			LifetimeDataBlock7 = 0x66,  	// ACCESS: R,	DATA TYPE: String,	DATA SIZE: 32+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: 
			ManufacturerInfo = 0x70,    	// ACCESS: R,	DATA TYPE: String,	DATA SIZE: 32+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: 
			DAStatus1 = 0x71,           	// ACCESS: R,	DATA TYPE: String,	DATA SIZE: 32+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: 
			DAStatus2 = 0x72,           	// ACCESS: R,	DATA TYPE: String,	DATA SIZE: 32+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: 
			CUV_Snapshot = 0x80,        	// ACCESS: R,	DATA TYPE: String,	DATA SIZE: 32+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: 
			COV_Snapshot = 0x81         	// ACCESS: R,	DATA TYPE: String,	DATA SIZE: 32+1,	MIN: -,	MAX: -,	DEFAULT: -,	UNIT: 
		}kBQ78350_SBS_COMMANDS_ENUM;
	}kBQ78350_SBS_COMMANDS_STRUCT;

	typedef struct
	{
		typedef enum
		{
			LifetimeDataCollection = 0x0023,                	// ACCESS: W
			PermanentFailure = 0x0024,                      	// ACCESS: W
			BlackBoxRecorder = 0x0025,                      	// ACCESS: W
			SAFE = 0x0026,                                  	// ACCESS: W
			LEDDisplayEnable = 0x0027,                      	// ACCESS: W
			LifetimeDataReset = 0x0028,                     	// ACCESS: W
			PermanentFailureDataReset = 0x0029,             	// ACCESS: W
			BlackBoxRecorderReset = 0x002A,                 	// ACCESS: W
			LED_Toggle = 0x002B,                            	// ACCESS: W
			LEDDisplayPress = 0x002C,                       	// ACCESS: W
			CalibrationMode = 0x002D,                       	// ACCESS: W
			SealDevice = 0x0030,                            	// ACCESS: W
			SecurityKeys = 0x0035,                          	// ACCESS: R_W
			AuthenticationKey = 0x0037,                     	// ACCESS: R_W
			DeviceReset = 0x0041,                           	// ACCESS: W
			StateOfHealth = 0x004F,                         	// ACCESS: R
			SafetyAlert = 0x0050,                           	// ACCESS: R
			SafetyStatus = 0x0051,                          	// ACCESS: R
			PFAlert = 0x0052,                               	// ACCESS: R
			PFStatus = 0x0053,                              	// ACCESS: R
			OperationStatus = 0x0054,                       	// ACCESS: R
			ChargingStatus = 0x0055,                        	// ACCESS: R
			GaugingStatus = 0x0056,                         	// ACCESS: R
			ManufacturingStatus = 0x0057,                   	// ACCESS: R
			AFEStatus = 0x0058,                             	// ACCESS: R
			AFEConfig = 0x0059,                             	// ACCESS: R
			AFEVCx = 0x005A,                                	// ACCESS: R
			AFEData = 0x005B,                               	// ACCESS: R_W
			LifetimeDataBlock1 = 0x0060,                    	// ACCESS: R
			LifetimeDataBlock2 = 0x0061,                    	// ACCESS: R
			LifetimeDataBlock3 = 0x0062,                    	// ACCESS: R
			LifetimeDataBlock4 = 0x0063,                    	// ACCESS: R
			LifetimeDataBlock5 = 0x0064,                    	// ACCESS: R
			LifetimeDataBlock6 = 0x0065,                    	// ACCESS: R
			LifetimeDataBlock7 = 0x0066,                    	// ACCESS: R
			ManufacturerInfo = 0x0070,                      	// ACCESS: R
			DAStatus1 = 0x0071,                             	// ACCESS: R
			DAStatus2 = 0x0072,                             	// ACCESS: R
			CUVSnapshot = 0x0080,                           	// ACCESS: R
			COVSnapshot = 0x0081,                           	// ACCESS: R
			DFAccessRowAddress = 0x0100,                    	// ACCESS: R_W
			ROMMode = 0x0F00,                               	// ACCESS: W
			ExitCalibrationOutput = 0xF080,                 	// ACCESS: R_W
			OutputCellVoltageforCalibration = 0xF081,       	// ACCESS: R_W
			OutputCellVoltageCCandTempforCalibration = 0xF082	// ACCESS: R_w
		}kBQ78350_MANUFACTURER_ACCESS_COMMANDS_ENUM;
	}kBQ78350_MANUFACTURER_ACCESS_COMMANDS_STRUCT;



// endregion PLATFORM_DEPENDED_STRUCTS

	class kBQ78350
	{
		public:

			static const kBQ78350_DATA_FLASH_REGISTER_SELECT_SELECT_SELECT_STRUCT * Register;
			static const kBQ78350_SBS_COMMANDS_STRUCT * SBS_Command;
			static const kBQ78350_MANUFACTURER_ACCESS_COMMANDS_STRUCT * MA_Command;

	};



#endif
