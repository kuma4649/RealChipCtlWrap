// これは メイン DLL ファイルです。

#include "stdafx.h"
#include "NScci.h"
#include <stdio.h>
#include <msclr\marshal.h>
using namespace msclr::interop;

using namespace System;

HMODULE	hScci = NULL;


NScci::NScci::NScci()
{

	if (hScci == NULL) {
		hScci = LoadLibraryA("scci.dll");
	}

	if (hScci == NULL) {
		::FreeLibrary(hScci);
		return;
	}

	SCCIFUNC getSoundInterfaceManager = (SCCIFUNC)(::GetProcAddress(hScci, "getSoundInterfaceManager"));
	if (getSoundInterfaceManager == NULL) {
		::FreeLibrary(hScci);
		return;
	}

	try {
		// サウンドインターフェースマネージャー取得
		SoundInterfaceManager_ = getSoundInterfaceManager();
		SoundInterfaceManager_->initializeInstance();
		NSoundInterfaceManager_ = gcnew NSoundInterfaceManager();
		NSoundInterfaceManager_->SoundInterfaceManager_ = SoundInterfaceManager_;
	}
	catch(...) {
	}
}

NScci::NScci::~NScci()
{
	this->!NScci();
}

NScci::NScci::!NScci()
{
	hScci = NULL;
	if (SoundInterfaceManager_ == NULL) {
		return;
	}
	else {
		try {
			// 一括開放する場合（チップ一括開放の場合）
			SoundInterfaceManager_->releaseAllSoundChip();
			// サウンドインターフェースマネージャーインスタンス開放
			// FreeLibraryを行う前に必ず呼び出ししてください
			SoundInterfaceManager_->releaseInstance();
			SoundInterfaceManager_ = NULL;
			::FreeLibrary(hScci);
		}
		catch (...) {
		}
	}
}


NScci::NSCCI_INTERFACE_INFO::NSCCI_INTERFACE_INFO()
{
}

NScci::NSCCI_INTERFACE_INFO::~NSCCI_INTERFACE_INFO()
{
	this->!NSCCI_INTERFACE_INFO();
}

NScci::NSCCI_INTERFACE_INFO::!NSCCI_INTERFACE_INFO()
{
}


NScci::NSCCI_SOUND_CHIP_INFO::NSCCI_SOUND_CHIP_INFO()
{
}

NScci::NSCCI_SOUND_CHIP_INFO::~NSCCI_SOUND_CHIP_INFO()
{
	this->!NSCCI_SOUND_CHIP_INFO();
}

NScci::NSCCI_SOUND_CHIP_INFO::!NSCCI_SOUND_CHIP_INFO()
{

}


NScci::NSoundInterfaceManager::NSoundInterfaceManager()
{
}

NScci::NSoundInterfaceManager::~NSoundInterfaceManager()
{
	this->!NSoundInterfaceManager();
}

NScci::NSoundInterfaceManager::!NSoundInterfaceManager()
{
}

int NScci::NSoundInterfaceManager::getInterfaceCount()
{
	if (SoundInterfaceManager_ == nullptr) return 0;
	return SoundInterfaceManager_->getInterfaceCount();
}

NScci::NSCCI_INTERFACE_INFO^ NScci::NSoundInterfaceManager::getInterfaceInfo(int iInterfaceNo)
{
	if (SoundInterfaceManager_ == nullptr) return nullptr;
	SCCI_INTERFACE_INFO* a = SoundInterfaceManager_->getInterfaceInfo(iInterfaceNo);

	NSCCI_INTERFACE_INFO^ info = gcnew NSCCI_INTERFACE_INFO();
	info->SCCI_INTERFACE_INFO_ = a;

	return info;
}

NScci::NSoundInterface^ NScci::NSoundInterfaceManager::getInterface(int iInterfaceNo)
{
	if (SoundInterfaceManager_ == nullptr) return nullptr;
	SoundInterface* si = SoundInterfaceManager_->getInterface(iInterfaceNo);

	NSoundInterface^ nsi = gcnew NSoundInterface();
	nsi->SoundInterface_ = si;

	return nsi;
}

bool NScci::NSoundInterfaceManager::releaseInterface(NSoundInterface pSoundInterface)
{
	if (SoundInterfaceManager_ == nullptr) return false;

	return SoundInterfaceManager_->releaseInterface(pSoundInterface.SoundInterface_);
}

bool NScci::NSoundInterfaceManager::releaseAllInterface()
{
	if (SoundInterfaceManager_ == nullptr) return false;

	return SoundInterfaceManager_->releaseAllInterface();
}

NScci::NSoundChip^ NScci::NSoundInterfaceManager::getSoundChip(int iSoundChipType, long dClock)
{
	if (SoundInterfaceManager_ == nullptr) return nullptr;

	SoundChip* a = SoundInterfaceManager_->getSoundChip(iSoundChipType, dClock);

	NSoundChip^ chip = gcnew NSoundChip();
	chip->SoundChip_ = a;

	return chip;
}

bool NScci::NSoundInterfaceManager::releaseSoundChip(NSoundChip pSoundChip)
{
	if (SoundInterfaceManager_ == nullptr) return false;

	return SoundInterfaceManager_->releaseSoundChip(pSoundChip.SoundChip_);
}

bool NScci::NSoundInterfaceManager::releaseAllSoundChip()
{
	if (SoundInterfaceManager_ == nullptr) return false;

	return SoundInterfaceManager_->releaseAllSoundChip();
}

bool NScci::NSoundInterfaceManager::setDelay(long dMSec)
{
	if (SoundInterfaceManager_ == nullptr) return false;

	return SoundInterfaceManager_->setDelay(dMSec);
}

long NScci::NSoundInterfaceManager::getDelay()
{
	if (SoundInterfaceManager_ == nullptr) return 0;

	return SoundInterfaceManager_->getDelay();
}

bool NScci::NSoundInterfaceManager::reset()
{
	if (SoundInterfaceManager_ == nullptr) return false;
	return SoundInterfaceManager_->reset();
	//for (int i = 0; i < getInterfaceCount(); i++) {
		//NSoundInterface^ nsif = getInterface(i);
		//nsif->reset();
	//}
}

bool NScci::NSoundInterfaceManager::init()
{
	if (SoundInterfaceManager_ == nullptr) return false;
	return SoundInterfaceManager_->init();
}

bool NScci::NSoundInterfaceManager::initializeInstance()
{
	if (SoundInterfaceManager_ == nullptr) return false;
	return SoundInterfaceManager_->initializeInstance();
}

bool NScci::NSoundInterfaceManager::releaseInstance()
{
	if (SoundInterfaceManager_ == nullptr) return false;
	return SoundInterfaceManager_->releaseInstance();
}

long NScci::NSoundInterfaceManager::getVersion(long% pMVersion)
{
	if (SoundInterfaceManager_ == nullptr) return 0;
	DWORD version;
	long ret= SoundInterfaceManager_->getVersion(&version);
	pMVersion = version;

	return ret;
}

bool NScci::NSoundInterfaceManager::isValidLevelDisp()
{
	if (SoundInterfaceManager_ == nullptr) return false;
	return SoundInterfaceManager_->isValidLevelDisp();
}

bool NScci::NSoundInterfaceManager::isLevelDisp()
{
	if (SoundInterfaceManager_ == nullptr) return false;
	return SoundInterfaceManager_->isLevelDisp();
}

void NScci::NSoundInterfaceManager::setLevelDisp(bool bDisp)
{
	if (SoundInterfaceManager_ == nullptr) return;
	SoundInterfaceManager_->setLevelDisp(bDisp);
}

void NScci::NSoundInterfaceManager::setMode(int iMode)
{
	if (SoundInterfaceManager_ == nullptr) return;
	SoundInterfaceManager_->setMode(iMode);
}

void NScci::NSoundInterfaceManager::sendData()
{
	if (SoundInterfaceManager_ == nullptr) return;
	SoundInterfaceManager_->sendData();
}

void NScci::NSoundInterfaceManager::clearBuff()
{
	if (SoundInterfaceManager_ == nullptr) return;
	SoundInterfaceManager_->clearBuff();
}

void NScci::NSoundInterfaceManager::setAcquisitionMode(int iMode)
{
	if (SoundInterfaceManager_ == nullptr) return;
	SoundInterfaceManager_->setAcquisitionMode(iMode);
}

void NScci::NSoundInterfaceManager::setAcquisitionModeClockRenge(long dClock)
{
	if (SoundInterfaceManager_ == nullptr) return;
	SoundInterfaceManager_->setAcquisitionModeClockRenge(dClock);
}

bool NScci::NSoundInterfaceManager::setCommandBuffetSize(long dBuffSize)
{
	if (SoundInterfaceManager_ == nullptr) return false;
	return SoundInterfaceManager_->setCommandBuffetSize(dBuffSize);
}

bool NScci::NSoundInterfaceManager::isBufferEmpty()
{
	if (SoundInterfaceManager_ == nullptr) return false;
	return SoundInterfaceManager_->isBufferEmpty();
}


NScci::NSoundInterface::NSoundInterface()
{
}

NScci::NSoundInterface::~NSoundInterface()
{
	this->!NSoundInterface();
}

NScci::NSoundInterface::!NSoundInterface()
{

}

Boolean NScci::NSoundInterface::isSupportLowLevelApi()
{
	BOOL ret = SoundInterface_->isSupportLowLevelApi();
	return ret ? true : false;
}

Boolean NScci::NSoundInterface::setData(array<Byte>^ pData, long dSendDataLen)
{
	pin_ptr<Byte> p = &pData[0];

	BOOL ret = SoundInterface_->setData(p, dSendDataLen);

	delete p;

	return ret ? true : false;
}

long NScci::NSoundInterface::getData(array<Byte>^ pData, long dGetDataLen)
{
	pin_ptr<Byte> p = &pData[0];
	long ret = SoundInterface_->getData(p, dGetDataLen);
	delete p;
	return ret;
}

Boolean NScci::NSoundInterface::setDelay(long dDelay)
{

	BOOL ret = SoundInterface_->setDelay(dDelay);

	return ret ? true : false;
}

long NScci::NSoundInterface::getDelay()
{

	return SoundInterface_->getDelay();

}

Boolean NScci::NSoundInterface::reset()
{

	BOOL ret = SoundInterface_->reset();

	return ret ? true : false;
}

Boolean NScci::NSoundInterface::init()
{

	BOOL ret = SoundInterface_->init();

	return ret ? true : false;
}

long NScci::NSoundInterface::getSoundChipCount() 
{
	return SoundInterface_->getSoundChipCount();
}

NScci::NSoundChip^ NScci::NSoundInterface::getSoundChip(long iInterfaceNo)
{
	SoundChip* sc = SoundInterface_->getSoundChip(iInterfaceNo);
	NSoundChip^ nsc = gcnew NSoundChip();
	nsc->SoundChip_ = sc;

	return nsc;
}


NScci::NSoundChip::NSoundChip()
{
}

NScci::NSoundChip::~NSoundChip()
{
	this->!NSoundChip();
}

NScci::NSoundChip::!NSoundChip()
{

}

NScci::NSCCI_SOUND_CHIP_INFO^ NScci::NSoundChip::getSoundChipInfo()
{
	SCCI_SOUND_CHIP_INFO* ssci = SoundChip_->getSoundChipInfo();

	NSCCI_SOUND_CHIP_INFO^ nssci= gcnew NSCCI_SOUND_CHIP_INFO();
	nssci->SCCI_SOUND_CHIP_INFO_ = ssci;

	return nssci;
}

int NScci::NSoundChip::getSoundChipType()
{
	return SoundChip_->getSoundChipType();
}

Boolean NScci::NSoundChip::setRegister(long dAddr, long dData)
{
	BOOL ret = SoundChip_->setRegister(dAddr, dData);
	return ret ? true : false;
}

long NScci::NSoundChip::getRegister(long dAddr)
{
	return SoundChip_->getRegister(dAddr);
}

Boolean NScci::NSoundChip::init()
{
	BOOL ret = SoundChip_->init();
	return ret ? true : false;
}

long  NScci::NSoundChip::getSoundChipClock()
{
	return SoundChip_->getSoundChipClock();
}

long NScci::NSoundChip::getWrittenRegisterData(long addr)
{
	return SoundChip_->getWrittenRegisterData(addr);
}

Boolean NScci::NSoundChip::isBufferEmpty()
{
	BOOL ret = SoundChip_->isBufferEmpty();
	return ret ? true : false;
}

