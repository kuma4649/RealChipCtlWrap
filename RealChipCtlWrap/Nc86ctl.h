#pragma once
#include "c86ctl.h"
using namespace System;

namespace Nc86ctl {

	public enum class ChipType {
		CHIP_UNKNOWN = 0x0000,

		CHIP_OPNA = 0x00001,
		CHIP_YM2608 = 0x00001,
		CHIP_YM2608NOADPCM = 0x10001,
		CHIP_OPM = 0x00002,
		CHIP_YM2151 = 0x00002,
		CHIP_OPN3L = 0x00003,
		CHIP_YMF288 = 0x00003,
		CHIP_OPL3 = 0x00004,
		CHIP_YMF262 = 0x00004,
		CHIP_OPLL = 0x00005,
		CHIP_YM2413 = 0x00005,

		CHIP_SN76489 = 0x00006,
		CHIP_SN76496 = 0x10006,
		CHIP_AY38910 = 0x00007,
		CHIP_YM2149 = 0x10007,
		CHIP_YM2203 = 0x00008,
		CHIP_YM2612 = 0x00009,
		CHIP_YM3526 = 0x0000a,
		CHIP_YM3812 = 0x0000b,
		CHIP_YMF271 = 0x0000c,
		CHIP_YMF278B = 0x0000d,
		CHIP_YMZ280B = 0x0000e,
		CHIP_YMF297 = 0x0000f,
		CHIP_YM2610B = 0x00010,
		CHIP_Y8950 = 0x00020,
		CHIP_Y8950ADPCM = 0x10020,
		CHIP_YM3438 = 0x00021
	};

	public ref class Devinfo
	{
	public:
		String^ Devname;
		int Rev;
		String^ Serial;
	};


	public ref class NIGimic2
	{
	public:
		NIGimic2();
		~NIGimic2();
		!NIGimic2();

		c86ctl::IGimic2* pIGimic;
		int getFWVer(UInt16%, UInt16%, UInt16%, UInt16%);
		Devinfo^ getMBInfo();
		ChipType getModuleType();
		Devinfo^ getModuleInfo();
		void setSSGVolume(byte);
		byte getSSGVolume();
		void setPLLClock(UInt32);
		UInt32 getPLLClock();
	};

	public ref class NIRealChip 
	{
	public:
		NIRealChip();
		~NIRealChip();
		!NIRealChip();

		c86ctl::IRealChip* pRC;
		void reset();
		void out(UInt16, byte);
		byte in(UInt16);
		NIGimic2^ QueryInterface();

	private:
	};

	public ref class Nc86ctl
	{
	public:
		Nc86ctl();
		~Nc86ctl();
		!Nc86ctl();

		int getNumberOfChip();
		int initialize();
		int deinitialize();
		NIRealChip^ getChipInterface(int);



	private:
		c86ctl::IRealChipBase* pChipBase;

	};

}