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



#include "kMP3.h"

/*
 *
V1,L1	V1,L2	V1,L3	V2,L1	V2, L2 & L3
0		0		0		0		0
4		4		4		4		1
8		6		5		6		2
12		7		6		7		3
16		8		7		8		4
20		10		8		10		5
24		12		10		12		6
28		14		12		14		7
32		16		14		16		8
36		20		16		18		10
40		24		20		20		12
44		28		24		22		14
48		32		28		24		16
52		40		32		28		18
56		48		40		32		20
0		0		0		0		0
 *
 *
 */
static const uint8_t bitrate_mul_value[5][16] =
{
	{0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,0},
	{0,4,6,7,8,10,12,14,16,20,24,28,32,40,48,0},
	{0,4,5,6,7,8,10,12,14,16,20,24,28,32,40,0},
	{0,4,6,7,8,10,12,14,16,18,20,22,24,28,32,0},
	{0,1,2,3,4,5,6,7,8,10,12,14,16,18,20,0}
};

/*
 *
	MPEG1	MPEG2	MPEG2.5
	1764	882		441
	1920	960		480
	1280	640		320
	0		0		0
 */
static const uint16_t sampling_rate_mul_value[3][4] =
{
	{441,480,320,0},
	{882,960,640,0},
	{1764,1920,1280,0}
};

void kMP3::prvTrySynchronizeFrame(uint8_t byte)
{
	// Synchronisation sequence is 11 bits set to 1

	switch(SynchronizationState)
	{
		case NotSynchronized:
			// Try to match first synchronisation byte
			// it should be 0xFF
			if(byte == 0xFF) SynchronizationState = FirstByteMatched;

			break;
		case FirstByteMatched:
			// Try to match second synchronisation byte
			// it should have 3 most significant bits set
			if(byte & 0xE0)
			{
				// yes byte contains synchronisation bits

				// get MPEG version saved also in this byte
				frameHeader.version = (MPEG_Audio_version_ID_T)((byte & 0x18) >> 3);
				// extract Layer description
				frameHeader.layer = (MPEG_LAYER_T)(4 - ((byte & 0x06) >> 1));
				// get CRC protection bit
				frameHeader.protection = (MPEG_PROTECTION_T)(byte & 0x01);

				SynchronizationState = SecondByteMatched;
			}

			break;
		case SecondByteMatched:

			// Get bitrate
			frameHeader.bitrate = (byte & 0xF0) >> 4;

			uint8_t index;

			if(frameHeader.version < 3)
			{
				//MPEG version 2 or 2.5
				if(frameHeader.layer == Layer_I) index = 3;
				else frameHeader.bitrate = index =4;

			}else
			{
				//MPEG version 1
				index = frameHeader.layer-1;

			}
			frameHeader.bitrate = 8*bitrate_mul_value[index][frameHeader.bitrate];


			// Get sampling frequency [Hz]
			index = frameHeader.version;
			if(index > 1) --index;
			frameHeader.sampling_frequency = 25*sampling_rate_mul_value[index][(byte & 0x0C) >> 2];

			// Get padding
			frameHeader.padding = (MPEG_FRAME_PADDING_T)((byte & 0x02) >> 1);

			// get frame size
			if(frameHeader.layer == Layer_I)
			{
				// For layer I
				frameHeader.frame_size_bytes = (12000*((uint32_t)frameHeader.bitrate)/((uint32_t)frameHeader.sampling_frequency) + ((uint32_t)frameHeader.padding))*4;
			}else
			{
				// For layer II and III
				frameHeader.frame_size_bytes = 144000*((uint32_t)frameHeader.bitrate)/((uint32_t)frameHeader.sampling_frequency) + ((uint32_t)frameHeader.padding);
			}

			SynchronizationState = ThirdByteMatched;

			break;
		case ThirdByteMatched:

			// Get channel mode
			frameHeader.channel_mode = (MPEG_CHANNEL_MODE_T)((byte & 0xC0) >> 6);
			// discard other bits: mode extension, copyright, original and emphasis



			if(frameHeader.protection == CRC_Protected)
			{
				// next 2 bytes will be CRC16 of the header
				SynchronizationState = ReceivingFirstByteCRC;

			}else
			{
				// there is no CRC protection of the header
				// Header is received
				SynchronizationState = FrameSynchronized;
				ReadingSideInfoState = ReadingDataBeginFirstByte;
			}

			break;
		case ReceivingFirstByteCRC:

			// TODO CRC16 calculation check

			// skip byte
			SynchronizationState = ReceivingSecondByteCRC;
			break;
		case ReceivingSecondByteCRC:

			// TODO CRC16 calculation check

			// skip byte
			// Header is received
			SynchronizationState = FrameSynchronized;
			ReadingSideInfoState = ReadingDataBeginFirstByte;
			break;
		case FrameSynchronized:

			break;
		default:

			break;
	}

}

void kMP3::prvGetSideInformation(uint8_t byte)
{
	switch(ReadingSideInfoState)
	{
		case ReadingDataBeginFirstByte:
			// bits [7:0] are [8:1] bits of main_data_begin

			// reading main data begin
			// this is 9 bits long
			// read first 8 bits
			mainDataBegin = ((uint16_t)byte << 1);
			ReadingSideInfoState = ReadingDataBeginSecondByte;
			break;
		case ReadingDataBeginSecondByte:
			// bit [7] is the bit [0] of main_data_begin

			// read last one bit of the mainDataBegin
			mainDataBegin |= (((uint16_t)(byte & 0x80)) >> 7);

			// read scfsi  -> this field varies between channel modes
			if(frameHeader.channel_mode == SingleChannel)
			{
				// 5 private bits and
				// scfsi field has 4 bits
				// in this byte bits [6:2] are private
				// bits [1:0] are bits [3:2] of scfsi field
				// channel 1 will be sawed as least significant bits
				scfsi = ((byte & 0x03) << 2);
			}else
			{
				// this is not mono channel frame
				// 3 private bits
				// scfsi field has 8 bits
				// in this byte bits [6:4] are private
				// bits [3:0] are bits [7:4] of scfsi field
				// channel 2 will be sawed as most significant bits
				scfsi = ((byte & 0x0F) << 4);
			}

			ReadingSideInfoState = ReadingSCFSI;
			break;
		case ReadingSCFSI:
			// continue to read scfsi bits

			// read scfsi  -> this field varies between channel modes
			if(frameHeader.channel_mode == SingleChannel)
			{
				// scfsi field has 4 bits
				// in this byte bits [7:6] are bits [1:0] of scfsi field
				// channel 1 will be sawed as least significant bits
				scfsi |= ((byte & 0xC0) >> (4+2));
			}else
			{
				// this is not mono channel frame
				// scfsi field has 8 bits
				// in this byte bits [7:4] are bits [3:0] of scfsi field
				// channel 1 will be sawed as least significant bits
				scfsi = ((byte & 0xF0) >> 4);
			}

			break;

	}
}

uint32_t kMP3::feed(uint8_t byte)
{
	if(SynchronizationState != FrameSynchronized)
	{
		prvTrySynchronizeFrame(byte);
	}else
	{
		// Frame is synchronized

		// Read side information


	}




	return 0;
}
