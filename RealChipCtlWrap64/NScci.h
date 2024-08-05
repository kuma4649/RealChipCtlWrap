// NScci.h

#pragma once
#include "scci2.h"
#include <msclr\marshal.h>
using namespace msclr::interop;

using namespace System;

namespace NScci {

	public ref class NSCCI_INTERFACE_INFO
	{ 

	public:
		NSCCI_INTERFACE_INFO();
		~NSCCI_INTERFACE_INFO();
		!NSCCI_INTERFACE_INFO();

		SCCI2_INTERFACE_INFO* SCCI_INTERFACE_INFO_;

		// Interface Name
		property String^  cInterfaceName {
			String^ get() {
				msclr::interop::marshal_context context;
				return context.marshal_as<System::String^>(SCCI_INTERFACE_INFO_->cInterfaceName);
			}
		}
		// Sound Chip Count;
		property int iSoundChipCount {
			int get() {
				return SCCI_INTERFACE_INFO_->iSoundChipCount;
			}
		}
	};

	public ref class NSCCI_SOUND_CHIP_INFO
	{

	public:
		NSCCI_SOUND_CHIP_INFO();
		~NSCCI_SOUND_CHIP_INFO();
		!NSCCI_SOUND_CHIP_INFO();

		SCCI2_SOUND_CHIP_INFO* SCCI_SOUND_CHIP_INFO_;

		// Sound Chip Name
		property String^ cSoundChipName {
			String^ get() {
				msclr::interop::marshal_context context;
				return context.marshal_as<System::String^>(SCCI_SOUND_CHIP_INFO_->cSoundChipName);
			}
		}
		// Sound Chip ID
		property int iSoundChip {
			int get() {
				return SCCI_SOUND_CHIP_INFO_->iSoundChip;
			}
		}
		// Compatible Sound Chip ID
		property array<int>^ iCompatibleSoundChip {
			array<int>^ get() {
				array<int>^ a1 = gcnew array<int>(2);
				a1[0] = SCCI_SOUND_CHIP_INFO_->iCompatibleSoundChip[0];
				a1[1] = SCCI_SOUND_CHIP_INFO_->iCompatibleSoundChip[1];

				return a1;
			}
		}
		// Sound Chip clock
		property long dClock {
			long get() {
				return SCCI_SOUND_CHIP_INFO_->dClock;
			}
		}
		// Sound Chip clock
		property array<long>^ dCompatibleClock {
			array<long>^ get() {
				array<long>^ a1 = gcnew array<long>(2);
				a1[0] = SCCI_SOUND_CHIP_INFO_->dCompatibleClock[0];
				a1[1] = SCCI_SOUND_CHIP_INFO_->dCompatibleClock[1];

				return a1;
			}
		}
		// Sound Chip Used Check
		property Boolean bIsUsed {
			Boolean get() {
				return SCCI_SOUND_CHIP_INFO_->bIsUsed;
			}
		}
		// 接続バスID
		property long dBusID {
			long get() {
				return SCCI_SOUND_CHIP_INFO_->dBusID;
			}
		}
		// サウンドロケーション
		property long dSoundLocation {
			long get() {
				return SCCI_SOUND_CHIP_INFO_->dSoundLocation;
			}
		}
	};

	ref class NSoundInterfaceManager;
	ref class NSoundInterface;
	ref class NSoundChip;

	//----------------------------------------
	// Sound Interface Manager
	//----------------------------------------
	public ref class NSoundInterfaceManager
	{
	public:
		NSoundInterfaceManager();
		~NSoundInterfaceManager();
		!NSoundInterfaceManager();

		Scci2SoundInterfaceManager* SoundInterfaceManager_;

		// ---------- LOW LEVEL APIs ----------
		// get interface count
		int getInterfaceCount();
		// get interface information 
		NSCCI_INTERFACE_INFO^ getInterfaceInfo(int iInterfaceNo);
		// get interface instance
		NSoundInterface^ getInterface(int iInterfaceNo);
		// release interface instance
		bool releaseInterface(NSoundInterface pSoundInterface);
		// release all interface instance
		bool releaseAllInterface();
		// ---------- HI LEVEL APIs ----------
		// get sound chip instance
		NSoundChip^ getSoundChip(int iSoundChipType, long dClock);
		// release sound chip instance
		bool releaseSoundChip(NSoundChip pSoundChip);
		// release all sound chip instance
		bool releaseAllSoundChip();
		// set delay time
		bool setDelay(long dMSec);
		// get delay time
		long getDelay();
		// reset interfaces(A sound chips initialize after interface reset)
		bool reset();
		// initialize sound chips
		bool init();
		// Sound Interface instance initialize
		bool initializeInstance();
		// Sound Interface instance release
		bool releaseInstance();
		//// config scci
		//// !!!this function is scciconfig exclusive use!!!
		//bool config();
		// get version info
		long getVersion(long% pMVersion);
		// get Level mater disp valid
		bool isValidLevelDisp();
		// get Level mater disp visible
		bool isLevelDisp();
		// set Level mater disp visible
		void setLevelDisp(bool bDisp);
		// set mode
		void setMode(int iMode);
		// send datas
		void sendData();
		// clear buffer
		void clearBuff();
		// set Acquisition Mode(Sound Chip)
		void setAcquisitionMode(int iMode);
		// set Acquisition Mode clock renge
		void setAcquisitionModeClockRenge(long dClock);
		// set command buffer size
		bool setCommandBuffetSize(long dBuffSize);
		// buffer check
		bool isBufferEmpty();

	};

	//----------------------------------------
	// Sound Interface(LOW level APIs)
	//----------------------------------------
	public ref class NSoundInterface
	{
	public:
		NSoundInterface();
		~NSoundInterface();
		!NSoundInterface();

		Scci2SoundInterface* SoundInterface_;

		// support low level API check
		Boolean isSupportLowLevelApi();
		// send data to interface
		Boolean setData(array<Byte>^ pData, long dSendDataLen);
		// get data from interface
		long    getData(array<Byte>^ pData, long dGetDataLen);
		// set delay time
		Boolean setDelay(long dDelay);
		// get delay time
		long    getDelay();
		// reset interface
		Boolean reset();
		// initialize sound chips
		Boolean init();
		// サウンドチップ数取得
		long	getSoundChipCount();
		// サウンドチップ取得
		NSoundChip^ getSoundChip(long dNum);
	};

	//----------------------------------------
	// Sound Chip
	//----------------------------------------
	public ref class NSoundChip
	{

	public:
		NSoundChip();
		~NSoundChip();
		!NSoundChip();

		Scci2SoundChip* SoundChip_;

		// get sound chip information
		NSCCI_SOUND_CHIP_INFO^ getSoundChipInfo();
		// get sound chip type
		int getSoundChipType();
		// set Register data
		Boolean setRegister(long dAddr, long dData);
		// get Register data(It may not be supported)
		long getRegister(long dAddr);
		// initialize sound chip(clear registers)
		Boolean init();
		// get sound chip clock
		long getSoundChipClock();
		// get writed register data
		long getWrittenRegisterData(long addr);
		// buffer check
		Boolean isBufferEmpty();
	};

	public ref class NScci
	{
		Scci2SoundInterfaceManager* SoundInterfaceManager_;
		Scci2SoundInterface* SoundInterface_;
		Scci2SoundChip* SoundChip_;

	public:
		NScci();
		~NScci();
		!NScci();

		NSoundInterfaceManager^ NSoundInterfaceManager_;
		NSoundInterface^ NSoundInterface_;
		NSoundChip^ NSoundChip_;
	};

}
