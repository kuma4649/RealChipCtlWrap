#include "stdafx.h"
#include "Nc86ctl.h"
#include <msclr\marshal.h>
using namespace msclr::interop;

HMODULE	hC86ctl = NULL;
typedef HRESULT(WINAPI *TCreateInstance)(REFIID, interior_ptr<c86ctl::IRealChipBase>);

Nc86ctl::Nc86ctl::Nc86ctl()
{
	if (hC86ctl == NULL) {
		hC86ctl = LoadLibraryA("c86ctl.dll");
	}

	if (hC86ctl == NULL) {
		::FreeLibrary(hC86ctl);
		return;
	}

	TCreateInstance pCreateInstance = (TCreateInstance)(::GetProcAddress(hC86ctl, "CreateInstance"));
	if (pCreateInstance == NULL) {
		::FreeLibrary(hC86ctl);
		return;
	}

	pCreateInstance(c86ctl::IID_IRealChipBase, (interior_ptr<c86ctl::IRealChipBase>)&pChipBase);
	pChipBase->initialize();
}

Nc86ctl::Nc86ctl::~Nc86ctl()
{
	this->!Nc86ctl();
}

Nc86ctl::Nc86ctl::!Nc86ctl()
{
	hC86ctl = NULL;
	::FreeLibrary(hC86ctl);
}

int Nc86ctl::Nc86ctl::initialize()
{
	return pChipBase->initialize();
}

int Nc86ctl::Nc86ctl::deinitialize()
{
	return pChipBase->deinitialize();
}

Nc86ctl::NIRealChip^ Nc86ctl::Nc86ctl::getChipInterface(int id)
{
	if (pChipBase == nullptr) {
		throw gcnew Exception();
	}

	c86ctl::IRealChip3 * pRC;
	pChipBase->getChipInterface(id, c86ctl::IID_IRealChip, (void**)&pRC);
	if (pRC == nullptr) {
		return nullptr;
	}

	NIRealChip^ nirc = gcnew NIRealChip();
	nirc->pRC = pRC;

	return nirc;
}

int Nc86ctl::Nc86ctl::getNumberOfChip()
{
	return pChipBase->getNumberOfChip();
}




Nc86ctl::NIRealChip::NIRealChip()
{
}

Nc86ctl::NIRealChip::~NIRealChip()
{
	this->!NIRealChip();
}

Nc86ctl::NIRealChip::!NIRealChip()
{
}

void Nc86ctl::NIRealChip::reset()
{
	pRC->reset();
}

void Nc86ctl::NIRealChip::out(UInt16 adr,byte data)
{
	pRC->out(adr, data);
}

void Nc86ctl::NIRealChip::directOut(UInt16 adr, byte data)
{
	pRC->directOut(adr, data);
}

byte Nc86ctl::NIRealChip::in(UInt16 adr)
{
	return pRC->in(adr);
}

Nc86ctl::NIGimic2^ Nc86ctl::NIRealChip::QueryInterface()
{
	if (pRC == nullptr) {
		throw gcnew Exception();
	}

	c86ctl::IGimic2 * pIGimic;
	pRC->QueryInterface(c86ctl::IID_IGimic2, (void**)&pIGimic);

	if (pIGimic == nullptr) {
		return nullptr;
	}

	NIGimic2^ nig = gcnew NIGimic2();
	nig->pIGimic = pIGimic;

	return nig;
}



Nc86ctl::NIGimic2::NIGimic2()
{
}

Nc86ctl::NIGimic2::~NIGimic2()
{
	this->!NIGimic2();
}

Nc86ctl::NIGimic2::!NIGimic2()
{
}

int Nc86ctl::NIGimic2::getFWVer(UInt16% major, UInt16% minor, UInt16% revision, UInt16% build)
{
	UINT ma;
	UINT mi;
	UINT rev;
	UINT bui;
	pIGimic->getFWVer(&ma, &mi, &rev, &bui);
	major = (UInt16)ma;
	minor = (UInt16)mi;
	revision = (UInt16)rev;
	build = (UInt16)bui;
	return 0;
}

Nc86ctl::Devinfo ^ Nc86ctl::NIGimic2::getMBInfo()
{
	c86ctl::Devinfo di;
	pIGimic->getMBInfo(&di);

	Devinfo^ inf = gcnew Devinfo();
	msclr::interop::marshal_context context;
	inf->Devname = context.marshal_as<System::String^>(di.Devname);
	inf->Rev = di.Rev;
	inf->Serial = context.marshal_as<System::String^>(di.Serial);

	return inf;
}

Nc86ctl::ChipType Nc86ctl::NIGimic2::getModuleType()
{
	c86ctl::ChipType tp;
	pIGimic->getModuleType(&tp);

	return (ChipType)(int)tp;
}

Nc86ctl::Devinfo^ Nc86ctl::NIGimic2::getModuleInfo()
{
	c86ctl::Devinfo di;
	pIGimic->getModuleInfo(&di);

	Devinfo^ inf = gcnew Devinfo();
	msclr::interop::marshal_context context;
	inf->Devname = context.marshal_as<System::String^>(di.Devname);
	inf->Rev = di.Rev;
	inf->Serial = context.marshal_as<System::String^>(di.Serial);

	return inf;
}

void Nc86ctl::NIGimic2::setSSGVolume(byte vol)
{
	pIGimic->setSSGVolume(vol);
}

byte Nc86ctl::NIGimic2::getSSGVolume()
{
	UCHAR vol;
	pIGimic->getSSGVolume(&vol);
	return vol;
}

void Nc86ctl::NIGimic2::setPLLClock(UInt32 clock)
{
	pIGimic->setPLLClock(clock);
}

UInt32 Nc86ctl::NIGimic2::getPLLClock()
{
	UINT clock;
	pIGimic->getPLLClock(&clock);
	return clock;
}
