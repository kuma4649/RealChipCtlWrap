//----------------------------------------------------------------------
//	Sound Chip common Interface
//----------------------------------------------------------------------
#pragma once
#include	<Windows.h>

// Sound Interface Infomation
typedef struct {
	char	cInterfaceName[64];			// Interface Name
	int		iSoundChipCount;			// Sound Chip Count;
} SCCI2_INTERFACE_INFO;

// Sound Chip Infomation
typedef struct {
	char	cSoundChipName[64];			// Sound Chip Name
	int		iSoundChip;					// Sound Chip ID
	int		iCompatibleSoundChip[2];	// Compatible Sound Chip ID
	DWORD	dClock;						// Sound Chip clock
	DWORD	dCompatibleClock[2];		// Sound Chip clock
	BOOL	bIsUsed;					// Sound Chip Used Check
	DWORD	dBusID;						// �ڑ��o�XID
	DWORD	dSoundLocation;				// �T�E���h���P�[�V����
} SCCI2_SOUND_CHIP_INFO;

class	Scci2SoundInterfaceManager;
class	Scci2SoundInterface;
class	Scci2SoundChip;

//----------------------------------------
// Sound Interface Manager
//----------------------------------------
class	Scci2SoundInterfaceManager{
public:
	// ---------- LOW LEVEL APIs ----------
	// get interface count
	virtual int __stdcall getInterfaceCount() = 0;
	// get interface information 
	virtual SCCI2_INTERFACE_INFO* __stdcall getInterfaceInfo(int iInterfaceNo) = 0;
	// get interface instance
	virtual Scci2SoundInterface* __stdcall getInterface(int iInterfaceNo) = 0;
	// release interface instance
	virtual BOOL __stdcall releaseInterface(Scci2SoundInterface* pSoundInterface) = 0;
	// release all interface instance
	virtual BOOL __stdcall releaseAllInterface() = 0;
	// ---------- HI LEVEL APIs ----------
	// get version info
	virtual DWORD __stdcall getVersion(DWORD* pMVersion = NULL) = 0;
	// get sound chip instance
	virtual Scci2SoundChip* __stdcall getSoundChip(int iSoundChipType,DWORD dClock) = 0;
	// release sound chip instance
	virtual BOOL __stdcall releaseSoundChip(Scci2SoundChip* pSoundChip) = 0;
	// release all sound chip instance
	virtual BOOL __stdcall releaseAllSoundChip() = 0;
	// set delay time
	virtual BOOL __stdcall setDelay(DWORD dMSec) = 0;
	// get delay time
	virtual DWORD __stdcall getDelay() = 0;
	// reset interfaces(A sound chips initialize after interface reset)
	virtual BOOL __stdcall reset() = 0;
	// initialize sound chips
	virtual BOOL __stdcall init() = 0;
	// Sound Interface instance initialize
	virtual	BOOL __stdcall initializeInstance() = 0;
	// Sound Interface instance release
	virtual BOOL __stdcall releaseInstance() = 0;
	// config scci
	// !!!this function is scciconfig exclusive use!!!
	virtual BOOL __stdcall config() = 0;
	// get Level mater disp valid
	virtual BOOL __stdcall isValidLevelDisp() = 0;
	// get Level mater disp visible
	virtual BOOL __stdcall isLevelDisp() = 0;
	// set Level mater disp visible
	virtual void __stdcall setLevelDisp(BOOL bDisp) = 0;
	// set mode
	virtual void __stdcall setMode(int iMode) = 0;
	// set start tick
	virtual void __stdcall setBaseTick() = 0;
	// send datas
	virtual void __stdcall sendData() = 0;
	// clear buffer
	virtual void __stdcall clearBuff() = 0;
	// set ClockRange Mode(Sound Chip)
	virtual void __stdcall setClockRangeMode(int iMode) = 0;
	// set ClockRange Mode clock renge
	virtual void __stdcall setClockRangeModeRenge(DWORD dClock) = 0;
	// set command buffer size
	virtual BOOL __stdcall setCommandBuffetSize(DWORD dBuffSize) = 0;
	// buffer check
	virtual BOOL __stdcall isBufferEmpty() = 0;
};

//----------------------------------------
// Sound Interface(LOW level APIs)
//----------------------------------------
class	Scci2SoundInterface{
public:
	// support low level API check
	virtual BOOL __stdcall isSupportLowLevelApi() = 0;
	// send data to interface
	virtual BOOL __stdcall setData(BYTE *pData,DWORD dSendDataLen) = 0;
	// get data from interface
	virtual DWORD __stdcall getData(BYTE *pData,DWORD dGetDataLen) = 0;
	// set delay time
	virtual	BOOL __stdcall setDelay(DWORD dDelay) = 0;
	// get delay time
	virtual DWORD __stdcall getDelay() = 0;
	// reset interface
	virtual BOOL __stdcall reset() = 0;
	// initialize sound chips
	virtual BOOL __stdcall init() = 0;
	// �T�E���h�`�b�v���擾
	virtual DWORD	__stdcall getSoundChipCount() = 0;
	// �T�E���h�`�b�v�擾
	virtual	Scci2SoundChip* __stdcall getSoundChip(DWORD dNum) = 0;
};

//----------------------------------------
// Sound Chip
//----------------------------------------
class	Scci2SoundChip{
public:
	// get sound chip information
	virtual SCCI2_SOUND_CHIP_INFO* __stdcall getSoundChipInfo() = 0;
	// get sound chip type
	virtual int __stdcall getSoundChipType() = 0;
	// set Register data
	virtual BOOL __stdcall setRegister(DWORD dAddr,LONG_PTR dData,DWORD dDelay = 0) = 0;
	// get Register data(It may not be supported)
	virtual LONG_PTR __stdcall getRegister(DWORD dAddr) = 0;
	// initialize sound chip(clear registers)
	virtual BOOL __stdcall init() = 0;
	// get sound chip clock
	virtual DWORD __stdcall getSoundChipClock() = 0;
	// get Written register data
	virtual DWORD __stdcall getWrittenRegisterData(DWORD addr) = 0;
	// buffer check
	virtual BOOL __stdcall isBufferEmpty() = 0;
};

//----------------------------------------
// get sound interface manager function
//----------------------------------------
typedef Scci2SoundInterfaceManager* (__stdcall *SCCIFUNC)(void);

//----------------------------------------
// pcm callback function
// void callback(SCCIPCMDATA *pPcm,DWORD dSize)
//----------------------------------------

typedef struct {
	int	iL;
	int	iR;
} SCCI2PCMDATA;

// Sound chip list
enum SC2_CHIP_TYPE {
	SC2_TYPE_NONE = 0,
	SC2_TYPE_YM2608,
	SC2_TYPE_YM2151,
	SC2_TYPE_YM2610,
	SC2_TYPE_YM2203,
	SC2_TYPE_YM2612,
	SC2_TYPE_AY8910,
	SC2_TYPE_SN76489,
	SC2_TYPE_YM3812,
	SC2_TYPE_YMF262,
	SC2_TYPE_YM2413,
	SC2_TYPE_YM3526,
	SC2_TYPE_YMF288,
	SC2_TYPE_SCC,
	SC2_TYPE_SCCS,
	SC2_TYPE_Y8950,
	SC2_TYPE_YM2164,		// OPP:OPM�Ƃ̓n�[�h�E�F�ALFO�̐��䂪�Ⴄ
	SC2_TYPE_YM2414,		// OPZ:OPM�ƃs���R���p�`
	SC2_TYPE_AY8930,		// APSG:�g��PSG
	SC2_TYPE_YM2149,		// SSG:PSG�Ƃ�DAC���Ⴄ(YM3439�Ƃ͓���Ƃ݂Ă����Ǝv��)
	SC2_TYPE_YMZ294,		// SSGL:SSG�Ƃ�DAC���Ⴄ(YMZ284�Ƃ͓���Ƃ݂Ă����Ǝv��)
	SC2_TYPE_SN76496,	// DCSG:76489�Ƃ̓m�C�Y�W�F�l���[�^�̐��������Ⴄ
	SC2_TYPE_YM2420,		// OPLL2:OPLL�Ƃ�Fnum�̐ݒ���@���Ⴄ�B���͓����B
	SC2_TYPE_YMF281,		// OPLLP:OPLL�Ƃ͓���ROM���F���Ⴄ�B����͓����B
	SC2_TYPE_YMF276,		// OPN2L:OPN2/OPN2C�Ƃ�DAC���Ⴄ
	SC2_TYPE_YM2610B,	// OPNB-B:OPNB�Ƃ�FM����ch�����Ⴄ�B
	SC2_TYPE_YMF286,		// OPNB-C:OPNB�Ƃ�DAC���Ⴄ�B
	SC2_TYPE_YM2602,		// 315-5124: 76489/76496�Ƃ̓m�C�Y�W�F�l���[�^�̐��������Ⴄ�BPOWON���ɔ��U���Ȃ��B
	SC2_TYPE_UM3567,		// OPLL�̃R�s�[�i�i������DIP24�Ȃ̂ł��̂܂܃��v���[�X�ł��Ȃ��j
	SC2_TYPE_YMF274,		// OPL4:���얢��
	SC2_TYPE_YM3806,		// OPQ:����\��
	SC2_TYPE_YM2163,		// DSG:���쒆
	SC2_TYPE_YM7129,		// OPK2:���쒆
	SC2_TYPE_YMZ280,		// PCM8:ADPCM8ch:����\��
	SC2_TYPE_YMZ705,		// SSGS:SSG*2set+ADPCM8ch:���쒆
	SC2_TYPE_YMZ735,		// FMS:FM8ch+ADPCM8ch:���쒆
	SC2_TYPE_YM2423,		// YM2413�̉��F�Ⴂ
	SC2_TYPE_SPC700,		// SPC700
	SC2_TYPE_NBV4,		// NBV4�p
	SC2_TYPE_AYB02,		// AYB02�p
	SC2_TYPE_8253,		// i8253�i�y�ь݊��`�b�v�p�j
	SC2_TYPE_315_5124,	// DCSG�݊��`�b�v
	SC2_TYPE_SPPCM,		// SPPCM
	SC2_TYPE_C140,		// NAMCO C140(SPPCM�f�o�C�X�j
	SC2_TYPE_SEGAPCM,	// SEGAPCM(SPPCM�f�o�C�X�j
	SC2_TYPE_SPW,		// SPW
	SC2_TYPE_SAM2695,	// SAM2695
	SC2_TYPE_MIDI,		// MIDI�C���^�[�t�F�[�X
	SC2_TYPE_MSCCX_SCC,			// MSCCX Level Upper SCC(SLOT0)
	SC2_TYPE_MSCCX_SCCP,			// MSCCX Level Upper SCC(SLOT0)
	SC2_TYPE_MSCCX_SCC_SCC,		// MSCCX Level Upper SCC(SLOT0) SCC(SLOT1)
	SC2_TYPE_MSCCX_SCC_SCCP,		// MSCCX Level Upper SCC(SLOT0) SCCP(SLOT1)
	SC2_TYPE_MSCCX_SCCP_SCC,		// MSCCX Level Upper SCCP(SLOT0) SCC(SLOT1)
	SC2_TYPE_MSCCX_SCCP_SCCP,	// MSCCX Level Upper SCCP(SLOT0) SCCP(SLOT1)
	SC2_TYPE_MAX,		// �g�p�\�f�o�C�XMAX�l
	// �ȍ~�́A��p�n�[�h�p

	// �����n�[�h�p
	SC2_TYPE_OTHER = 1000,	// ���̑��f�o�C�X�p�A�A�h���X��A0-A3�œ��삷��
	SC2_TYPE_UNKNOWN,		// �J���f�o�C�X����
	SC2_TYPE_YMF825,			// YMF825�i�b��j
};

// Sound chip clock list
enum SC2_CHIP_CLOCK {
	SC2_CLOCK_NONE = 0,
	SC2_CLOCK_1789773 = 1789773,	// SSG,OPN,OPM,SN76489 etc
	SC2_CLOCK_1996800 = 1996800,	// SSG,OPN,OPM,SN76489 etc
	SC2_CLOCK_2000000 = 2000000,	// SSG,OPN,OPM,SN76489 etc
	SC2_CLOCK_2048000 = 2048000,	// SSGLP(4096/2|6144/3)
	SC2_CLOCK_3579545 = 3579545,	// SSG,OPN,OPM,SN76489 etc
	SC2_CLOCK_3993600 = 3993600,	// OPN(88)
	SC2_CLOCK_4000000 = 4000000,	// SSF,OPN,OPM etc
	SC2_CLOCK_7159090 = 7159090,	// OPN,OPNA,OPNB,OPN2,OPN3L etc
	SC2_CLOCK_7670454 = 7670454,	// YM-2612 etc
	SC2_CLOCK_7987200 = 7987200,	// OPNA(88)
	SC2_CLOCK_8000000 = 8000000,	// OPNB etc
	SC2_CLOCK_10738635 = 10738635, // 315-5124
	SC2_CLOCK_12500000 = 12500000, // RF5C164
	SC2_CLOCK_14318180 = 14318180, // OPL2
	SC2_CLOCK_16934400 = 16934400, // YMF271
	SC2_CLOCK_23011361 = 23011361, // PWM
};

// Sound chip location
enum SC2_CHIP_LOCATION {
	SC2_LOCATION_MONO = 0,
	SC2_LOCATION_LEFT = 1,
	SC2_LOCATION_RIGHT = 2,
	SC2_LOCATION_STEREO = 3
};

// mode defines
#define	SC2_MODE_ASYNC	(0x00000000)
#define SC2_MODE_SYNC	(0x00000001)
#define SC2_MODE_OFFSET	(0x00000002)

// sound chip clock range mode defines
#define	SC2_CLOCK_RANGE_MODE_NEAR	(0x00000000)
#define	SC2_CLOCK_RANGE_MODE_MATCH	(0x00000001)	

#define	SC2_WAIT_REG		(0xffffffff)	// �E�F�C�ƃR�}���h���M�i�f�[�^�͑��M����R�}���h���j
#define SC2_FLUSH_REG		(0xfffffffe)	// �������݃f�[�^�t���b�V���҂�
#define SC2_DIRECT_BUS		(0x80000000)	// �A�h���X�o�X�_�C���N�g���[�h

