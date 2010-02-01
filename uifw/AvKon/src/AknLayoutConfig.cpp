/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  Layout configuration data retrieval and access
*
*/


#include "AknLayoutConfig.h"
#include <eikenv.h>
#include <AknPanic.h>
#include <aknpriv.rsg>
#include <barsread.h>
#include <barsc2.h>
#include "AknLib.h"
#include <AknLayoutConsts.h>
#include "AknLayoutConfigInternal.h"
#include <CdlTypes.h>
#include <AknCapServerClient.h>

NONSHARABLE_CLASS(CAknLayoutConfigWsiniParser) : public CBase
	{
public:
	static void GetConfigL(SAknLayoutConfig& aConfig, 
						   RArray<SAknScreenModeInfo>& aScreenInfoArray, 
						   RArray<SHardwareStateInfo>& aHardwareStateArray);

private:
	CAknLayoutConfigWsiniParser(SAknLayoutConfig& aConfig, 
								RArray<SAknScreenModeInfo>& aScreenInfoArray, 
								RArray<SHardwareStateInfo>& aHardwareStateArray);
	~CAknLayoutConfigWsiniParser();
	void GetConfigL();
	HBufC* GetWsiniLC();
	void ParseWsiniL(const TDesC& aWsini);
	void ParseLineL(const TText* aKwStart, const TText* aKwEnd, const TText* aLineEnd);

	SHardwareStateInfo& HardwareStateL(TInt aStateNumber);
	SAknScreenModeInfo& ScreenModeL(TInt aScreenMode);
	TInt ParseIntL(TPtrC& aLine);
	TInt ParseKeycodeL(TPtrC& aLine);
	TAknPrivSoftkeyLocation ParseSoftkeyLocationL(TPtrC& aLine);
	TInt ScreenStyleHash(TPtrC& aLine);

private:
#define WSINI_PARSE_FUNC(name) static void Call##name(CAknLayoutConfigWsiniParser* aSelf, TPtrC& aLine) { aSelf->name(aLine); } void name(TPtrC& aLine);
	WSINI_PARSE_FUNC(HardwareStateKeycodeL)
	WSINI_PARSE_FUNC(HardwareStateScreenModeL)
	WSINI_PARSE_FUNC(HardwareStateAltScreenModeL)
	WSINI_PARSE_FUNC(ScreenModeSoftkeyLocationL)
	WSINI_PARSE_FUNC(ScreenModeStyleNameL)

private:
	struct SParseEntry
		{
		const TText16* iKeyword;
		TInt iKeywordLen;
		void (*iFunc)(CAknLayoutConfigWsiniParser* aSelf, TPtrC& aLine);
		};
	static const SParseEntry iParseTable[];

private:
	SAknLayoutConfig& iConfig;
	RArray<SAknScreenModeInfo>& iScreenInfoArray;
	RArray<SHardwareStateInfo>& iHardwareStateArray;
	};

//
// CAknLayoutConfig::TScreenMode
//
EXPORT_C const TPixelsTwipsAndRotation& CAknLayoutConfig::TScreenMode::PixelsTwipsAndRotation() const
	{
	return iInfo.iPixelsTwipsAndRotation;
	}

CAknLayoutConfig::TScreenMode::TScreenMode(const SAknScreenModeInfo& aInfo)
: TAknScreenMode(aInfo)
	{
	}

EXPORT_C TAknPrivSoftkeyLocation CAknLayoutConfig::TScreenMode::SoftkeyLocation() const
	{
	return iInfo.iSoftkeyLocation;
	}

EXPORT_C TInt CAknLayoutConfig::TScreenMode::ScreenStyleHash() const
	{
	return iInfo.iScreenStyleHash;
	}


//
// CAknLayoutConfig::TScreenModeArray
//
EXPORT_C CAknLayoutConfig::TScreenMode CAknLayoutConfig::TScreenModeArray::At(TInt aIndex) const
	{
	__ASSERT_ALWAYS(0 <= aIndex && aIndex < iInfo.iNumScreenModes, Panic(EAknPanicLayoutConfigBadScreenModeIndex));
	return TScreenMode(iInfo.iScreenModes[aIndex]);
	}

EXPORT_C CAknLayoutConfig::TScreenMode CAknLayoutConfig::TScreenModeArray::Find(TInt aModeNumber) const
	{
	for (TInt ii=0; ii<iInfo.iNumScreenModes; ii++)
		{
		if (iInfo.iScreenModes[ii].iModeNumber == aModeNumber)
			return TScreenMode(iInfo.iScreenModes[ii]);
		}
	return TScreenMode(iInfo.iScreenModes[0]);
	}

CAknLayoutConfig::TScreenModeArray::TScreenModeArray(const SAknLayoutConfig& aInfo)
: TAknScreenModes(aInfo)
	{
	}


//
// CAknLayoutConfig::THardwareState
//
EXPORT_C TInt CAknLayoutConfig::THardwareState::StateNumber() const
	{
	return iInfo.iStateNum;
	}

EXPORT_C TInt CAknLayoutConfig::THardwareState::KeyCode() const
	{
	return iInfo.iKeyCode;
	}

EXPORT_C TInt CAknLayoutConfig::THardwareState::ScreenMode() const
	{
	return iInfo.iScreenMode;
	}

EXPORT_C TInt CAknLayoutConfig::THardwareState::AlternateScreenMode() const
	{
	return iInfo.iAltScreenMode;
	}

CAknLayoutConfig::THardwareState::THardwareState(const SHardwareStateInfo& aInfo)
: iInfo(aInfo)
	{
	}


//
// CAknLayoutConfig::THardwareStateArray
//
EXPORT_C TInt CAknLayoutConfig::THardwareStateArray::Count() const
	{
	return iInfo.iNumHardwareStates;
	}

EXPORT_C CAknLayoutConfig::THardwareState CAknLayoutConfig::THardwareStateArray::At(TInt aIndex) const
	{
	__ASSERT_ALWAYS(0 <= aIndex && aIndex < iInfo.iNumHardwareStates, Panic(EAknPanicLayoutConfigBadHardwareStateIndex));
	return THardwareState(iInfo.iHardwareStates[aIndex]);
	}

EXPORT_C CAknLayoutConfig::THardwareState CAknLayoutConfig::THardwareStateArray::Find(TInt aStateNumber) const
	{
	for (TInt ii=0; ii<iInfo.iNumHardwareStates; ii++)
		{
		if (iInfo.iHardwareStates[ii].iStateNum == aStateNumber)
			return THardwareState(iInfo.iHardwareStates[ii]);
		}
	return THardwareState(iInfo.iHardwareStates[0]);
	}

CAknLayoutConfig::THardwareStateArray::THardwareStateArray(const SAknLayoutConfig& aInfo)
: iInfo(aInfo)
	{
	}


//
// CAknLayoutConfig
//
EXPORT_C CAknLayoutConfig::TScreenModeArray CAknLayoutConfig::ScreenModes() const
	{
	return TScreenModeArray(*iData);
	}

EXPORT_C CAknLayoutConfig::THardwareStateArray CAknLayoutConfig::HardwareStates() const
	{
	return THardwareStateArray(*iData);
	}

CAknLayoutConfig::CAknLayoutConfig()
	{
	}

CAknLayoutConfig::~CAknLayoutConfig()
	{
	delete iBuf;
	}

EXPORT_C CAknLayoutConfig* CAknLayoutConfig::NewL()
	{
	CAknLayoutConfig* self = new(ELeave) CAknLayoutConfig;
	CleanupStack::PushL(self);

	RAknUiServer aknUiServer;
	CleanupClosePushL(aknUiServer);
	User::LeaveIfError(aknUiServer.Connect());
	HBufC8* configBuf = aknUiServer.GetPackedConfigL();
	CleanupStack::PopAndDestroy(&aknUiServer);

	// ownership of configBuf immediately transferred to self
	self->ConstructL(configBuf);
	CleanupStack::Pop(self);
	return self;
	}

#define UNPACK_CHECK(b) __ASSERT_ALWAYS(b, Panic(EAknPanicLayoutConfigUnpackFail))

void CAknLayoutConfig::ConstructL(HBufC8* aBuf)
	{
	iBuf = aBuf;
	
	// unpack & validate data
	TInt size = iBuf->Size();
	// basic structure
	UNPACK_CHECK(size >= sizeof(SAknLayoutConfig));
	iData = (SAknLayoutConfig*)iBuf->Ptr();

	// check total size
	UNPACK_CHECK(
		size == 
		(
			sizeof(SAknLayoutConfig) + 
			(iData->iNumScreenModes * sizeof(SAknScreenModeInfo)) +
			(iData->iNumHardwareStates * sizeof(SHardwareStateInfo))
		));

	// check and unpack screen modes, iScreenModes is an offset before unpacking
	UNPACK_CHECK((TUint32)iData->iScreenModes == sizeof(SAknLayoutConfig));
	iData->iScreenModes = (SAknScreenModeInfo*)((TUint8*)iData + (TUint32)iData->iScreenModes);
	
	// check iNumScreenModes (we've already checked it fits in size)
	UNPACK_CHECK(iData->iNumScreenModes >= 0);

	// check and unpack hardware states, iHardwareStates is an offset before unpacking
	UNPACK_CHECK((TUint32)iData->iHardwareStates == (sizeof(SAknLayoutConfig) + sizeof(SAknScreenModeInfo)*iData->iNumScreenModes));
	iData->iHardwareStates = (SHardwareStateInfo*)((TUint8*)iData + (TUint32)iData->iHardwareStates);

	// check iNumHardwareStates (we've already checked it fits in size)
	UNPACK_CHECK(iData->iNumHardwareStates >= 0);
	}

HBufC8* CAknLayoutConfig::CreatePackedBufL()
	{
	// set up structures to collect the config info
	SAknLayoutConfig config = { 0, NULL, 0, NULL };
	
	RArray<SAknScreenModeInfo> screenInfoArray;
	CleanupClosePushL(screenInfoArray);
	
	RArray<SHardwareStateInfo> hardwareStateArray;
	CleanupClosePushL(hardwareStateArray);

	// get the config info
	TRAP_IGNORE(GetConfigL(config, screenInfoArray, hardwareStateArray));
	
	// calculate how much space is needed for the config info
	TInt screenModesSize = sizeof(SAknScreenModeInfo) * screenInfoArray.Count();
	TInt hardwareStatesSize = sizeof(SHardwareStateInfo) * hardwareStateArray.Count();
	TInt bufSize = sizeof(SAknLayoutConfig) + screenModesSize + hardwareStatesSize;
	
	// create the buffer space
	HBufC8* buf = HBufC8::NewLC(bufSize);
	TPtr8 des(buf->Des());
	
	// pack the info for transport
	config.iScreenModes = (SAknScreenModeInfo*)sizeof(SAknLayoutConfig);
	config.iHardwareStates = (SHardwareStateInfo*)(sizeof(SAknLayoutConfig) + screenModesSize);
	
	// put the info into the buffer
	des.Append(TPckgC<SAknLayoutConfig>(config));
	if (screenModesSize)
		des.Append(TPtrC8((TText8*)&screenInfoArray[0], screenModesSize));
	if (hardwareStatesSize)
		des.Append(TPtrC8((TText8*)&hardwareStateArray[0], hardwareStatesSize));
	
	// tidy up and return
	CleanupStack::Pop(buf);
	CleanupStack::PopAndDestroy(2); // hardwareStateArray and screenInfoArray
	
	return buf;
	}

#ifdef _DEBUG
void DebugLayoutConfigLeaves(TAny*)
	{
	User::Panic(_L("LayoutConfigLeave"), 0);
	}
#endif

void CAknLayoutConfig::GetConfigL(SAknLayoutConfig& aConfig, 
								  RArray<SAknScreenModeInfo>& aScreenInfoArray, 
								  RArray<SHardwareStateInfo>& aHardwareStateArray)
	{
#ifdef _DEBUG
	CleanupStack::PushL(TCleanupItem(DebugLayoutConfigLeaves, 0));
#endif

	CEikonEnv* eikonEnv = CEikonEnv::Static();
	CResourceFile* resFile = CResourceFile::NewLC(eikonEnv->FsSession(), CAknLibrary::PrivateResourceFile(), 0, 0);
	resFile->ConfirmSignatureL();
	
	TAknPrivSoftkeyLocation landscapeSofkey = GetLandscapeSoftkeyLocationFromAknPrivL(resFile);
	GetScreenModesFromWservL(aConfig, aScreenInfoArray, landscapeSofkey);

	CAknLayoutConfigWsiniParser::GetConfigL(aConfig, aScreenInfoArray, aHardwareStateArray);
	if (aHardwareStateArray.Count() == 0)
		{
		// got no info from wsini, so look up AknPriv
		GetScreenMapFromAknPrivL(resFile, aScreenInfoArray, aHardwareStateArray);
		GetKeyMapFromAknPrivL(resFile, aHardwareStateArray);
		}
	aConfig.iNumHardwareStates = aHardwareStateArray.Count();

	CleanupStack::PopAndDestroy(resFile);
	
#ifdef _DEBUG
	CleanupStack::Pop(); 	// TCleanupItem(DebugLayoutConfigLeaves, 0)
#endif
	}

void CAknLayoutConfig::GetScreenMapFromAknPrivL(CResourceFile* aResFile,
												RArray<SAknScreenModeInfo>& aScreenInfoArray, 
											    RArray<SHardwareStateInfo>& aHardwareStateArray)
	{
	// get state screen map
#if defined(__WINS__)
    TInt screenMapResource = R_AKNPRIV_HARDWARE_STATE_SCREEN_MAP_EMUL;
#else
    TInt screenMapResource = R_AKNPRIV_HARDWARE_STATE_SCREEN_MAP;
#endif

	// open the resource table for the hardware state <-> screen map
	TResourceReader reader;
	reader.SetBuffer(aResFile->AllocReadLC(screenMapResource));

	// Read the entires
	TInt numScreenModes = aScreenInfoArray.Count();
	TInt count = reader.ReadInt16();
	aHardwareStateArray.ReserveL(count);
	for (TInt ii=0; ii<count; ii++)
		{
		SHardwareStateInfo hwInfo;
		Mem::FillZ(&hwInfo, sizeof(hwInfo));
		
		hwInfo.iStateNum = reader.ReadInt16();
		
		TInt width = reader.ReadInt16();
		TInt height = reader.ReadInt16();
		TSize size(width, height);
		CFbsBitGc::TGraphicsOrientation rotation = static_cast<CFbsBitGc::TGraphicsOrientation>(reader.ReadInt16());
		CFbsBitGc::TGraphicsOrientation altRotation = static_cast<CFbsBitGc::TGraphicsOrientation>(reader.ReadInt16());
		TSize altSize(height, width);
		if ((rotation % CFbsBitGc::EGraphicsOrientationRotated180) == 
			(altRotation % CFbsBitGc::EGraphicsOrientationRotated180))
			altSize = size;
		
		// find a matching screen number
		for (TInt jj=0; jj<numScreenModes; jj++)
			{
			SAknScreenModeInfo& screenMode = aScreenInfoArray[jj];
			if (screenMode.iPixelsTwipsAndRotation.iPixelSize == size && screenMode.iPixelsTwipsAndRotation.iRotation == rotation)
				hwInfo.iScreenMode = screenMode.iModeNumber;
			if (screenMode.iPixelsTwipsAndRotation.iPixelSize == altSize && screenMode.iPixelsTwipsAndRotation.iRotation == altRotation)
				hwInfo.iAltScreenMode = screenMode.iModeNumber;
			}
			
		aHardwareStateArray.AppendL(hwInfo);
		}

	CleanupStack::PopAndDestroy(); // reader's HBufC
	}
	
void CAknLayoutConfig::GetKeyMapFromAknPrivL(CResourceFile* aResFile,
											 RArray<SHardwareStateInfo>& aHardwareStateArray)
	{
	// get the state key map
#if defined(__WINS__)
    TInt hwMapResource = R_AKNPRIV_HARDWARE_STATE_KEY_MAP_EMUL;
#else
    TInt hwMapResource = R_AKNPRIV_HARDWARE_STATE_KEY_MAP;
#endif

	TResourceReader reader;
	reader.SetBuffer(aResFile->AllocReadLC(hwMapResource));

    TInt count = reader.ReadInt16();
    for (TInt ii=0; ii<count; ii++)
        {
        TInt key = (TUint32)reader.ReadUint16();
        TInt state = reader.ReadInt16();
		for (TInt jj=0; jj<aHardwareStateArray.Count(); jj++)
			{
			SHardwareStateInfo& hwInfo = aHardwareStateArray[jj];
			if (hwInfo.iStateNum == state)
				hwInfo.iKeyCode = key;
			}
        }

    CleanupStack::PopAndDestroy(); // reader's HBufC
	}

TAknPrivSoftkeyLocation CAknLayoutConfig::GetLandscapeSoftkeyLocationFromAknPrivL(CResourceFile* aResFile)
	{
#if defined(__WINS__)
    TInt skResource = R_AKNPRIV_SOFTKEY_LOCATION_LANDSCAPE_ROTATED90_EMUL;
#else
    TInt skResource = R_AKNPRIV_SOFTKEY_LOCATION_LANDSCAPE_ROTATED90;
#endif

	TResourceReader reader;
	reader.SetBuffer(aResFile->AllocReadLC(skResource));
	TAknPrivSoftkeyLocation softKeyLocation = (TAknPrivSoftkeyLocation)reader.ReadInt16();

    CleanupStack::PopAndDestroy(); // reader's HBufC
    
    return softKeyLocation;
	}

TBool IsLandscape(const TSize& aSize)
	{
	return aSize.iWidth > aSize.iHeight;
	}

void CAknLayoutConfig::GetScreenModesFromWservL(SAknLayoutConfig& aConfig,
												RArray<SAknScreenModeInfo>& aScreenInfoArray, 
												TAknPrivSoftkeyLocation aLandscapeSoftkeyLocation)
	{
	CEikonEnv* eikonEnv = CEikonEnv::Static();
	CWsScreenDevice* dev = eikonEnv->ScreenDevice();

	TInt numScreenModes = dev->NumScreenModes();
	aConfig.iNumScreenModes = numScreenModes;
	aScreenInfoArray.ReserveL(numScreenModes);
	for (TInt ii=0; ii<numScreenModes; ii++)
		{
		SAknScreenModeInfo screenMode;
		screenMode.iModeNumber = ii;
		screenMode.iScreenStyleHash = 0;
		dev->GetScreenModeSizeAndRotation(ii, screenMode.iPixelsTwipsAndRotation);
		if (IsLandscape(screenMode.iPixelsTwipsAndRotation.iPixelSize))
			{
			screenMode.iSoftkeyLocation = aLandscapeSoftkeyLocation;
	        // side-swapping logic moved from CAknEnv::StatusPaneResIdForCurrentLayout
	        if (screenMode.iPixelsTwipsAndRotation.iRotation == CFbsBitGc::EGraphicsOrientationRotated270)
	            {
	            if (aLandscapeSoftkeyLocation == EAknPrivSoftkeyLocationRight)
	                screenMode.iSoftkeyLocation = EAknPrivSoftkeyLocationLeft;
	            else if (aLandscapeSoftkeyLocation == EAknPrivSoftkeyLocationLeft)
	                screenMode.iSoftkeyLocation = EAknPrivSoftkeyLocationRight;
	            }
			}
		else
			{
			screenMode.iSoftkeyLocation = EAknPrivSoftkeyLocationBottom;
			}
    	screenMode.iDisplayMode = dev->GetScreenModeDisplayMode(ii);
		aScreenInfoArray.AppendL(screenMode);
		}
	}

//
// CAknLayoutConfigWsiniParser
//
#define WSINI_PARSE_ENTRY(keyword, func) { _S(keyword), sizeof(keyword)-1, &CAknLayoutConfigWsiniParser::Call##func }
const CAknLayoutConfigWsiniParser::SParseEntry CAknLayoutConfigWsiniParser::iParseTable[] = 
	{
	WSINI_PARSE_ENTRY("S60_HWSTATE_KEYCODE", HardwareStateKeycodeL),		//S60_HWSTATE_KEYCODEn <KeyCode>
	WSINI_PARSE_ENTRY("S60_HWSTATE_SCREENMODE", HardwareStateScreenModeL),		//S60_HWSTATE_SCREENMODEn <ScreenModeNumber>
	WSINI_PARSE_ENTRY("S60_HWSTATE_ALT_SCREENMODE", HardwareStateAltScreenModeL),		//S60_HWSTATE_ALT_SCREENMODEn <ScreenModeNumber>
	WSINI_PARSE_ENTRY("S60_SCR_SOFTKEY_LOCATION", ScreenModeSoftkeyLocationL),		//S60_SCR_SOFTKEY_LOCATIONn <Location>
	WSINI_PARSE_ENTRY("S60_SCR_STYLE_NAME", ScreenModeStyleNameL),		//S60_SCR_STYLE_NAMEn <ScreenStyleName>
	};

void CAknLayoutConfigWsiniParser::GetConfigL(SAknLayoutConfig& aConfig, 
											 RArray<SAknScreenModeInfo>& aScreenInfoArray, 
											 RArray<SHardwareStateInfo>& aHardwareStateArray)
	{
	CAknLayoutConfigWsiniParser* self = new(ELeave) CAknLayoutConfigWsiniParser(aConfig, aScreenInfoArray, aHardwareStateArray);
	CleanupStack::PushL(self);
	self->GetConfigL();
	CleanupStack::PopAndDestroy();
	}

CAknLayoutConfigWsiniParser::CAknLayoutConfigWsiniParser(SAknLayoutConfig& aConfig, 
														 RArray<SAknScreenModeInfo>& aScreenInfoArray, 
														 RArray<SHardwareStateInfo>& aHardwareStateArray)
: iConfig(aConfig), iScreenInfoArray(aScreenInfoArray), iHardwareStateArray(aHardwareStateArray)	
	{
	}
	
CAknLayoutConfigWsiniParser::~CAknLayoutConfigWsiniParser()
	{
	}
	
void CAknLayoutConfigWsiniParser::GetConfigL()
	{
	HBufC* wsini = GetWsiniLC();
	ParseWsiniL(*wsini);
	CleanupStack::PopAndDestroy(wsini);
	}

void CAknLayoutConfigWsiniParser::HardwareStateKeycodeL(TPtrC& aLine)
	{
	//S60_HWSTATE_KEYCODEn <KeyCode>
	TInt stateNumber = ParseIntL(aLine);
	TInt keyCode = ParseKeycodeL(aLine);
	HardwareStateL(stateNumber).iKeyCode = keyCode;
	}

void CAknLayoutConfigWsiniParser::HardwareStateScreenModeL(TPtrC& aLine)
	{
	//S60_HWSTATE_SCREENMODEn <ScreenModeNumber>
	TInt stateNumber = ParseIntL(aLine);
	TInt modeNumber = ParseIntL(aLine) - 1;		// -1 to translate between wsini & CWsScreenDevice mode numbers
	HardwareStateL(stateNumber).iScreenMode = modeNumber;
	}

void CAknLayoutConfigWsiniParser::HardwareStateAltScreenModeL(TPtrC& aLine)
	{
	//S60_HWSTATE_ALT_SCREENMODEn <ScreenModeNumber>
	TInt stateNumber = ParseIntL(aLine);
	TInt modeNumber = ParseIntL(aLine) - 1;		// -1 to translate between wsini & CWsScreenDevice mode numbers
	HardwareStateL(stateNumber).iAltScreenMode = modeNumber;
	}

void CAknLayoutConfigWsiniParser::ScreenModeSoftkeyLocationL(TPtrC& aLine)
	{
	//S60_SCR_SOFTKEY_LOCATIONn <Location>
	TInt modeNumber = ParseIntL(aLine) - 1;		// -1 to translate between wsini & CWsScreenDevice mode numbers
	TAknPrivSoftkeyLocation location = ParseSoftkeyLocationL(aLine);
	ScreenModeL(modeNumber).iSoftkeyLocation = location;
	}

void CAknLayoutConfigWsiniParser::ScreenModeStyleNameL(TPtrC& aLine)
	{
	//S60_SCR_STYLE_NAMEn <ScreenStyleName>
	TInt modeNumber = ParseIntL(aLine) - 1;		// -1 to translate between wsini & CWsScreenDevice mode numbers
	TInt hash = ScreenStyleHash(aLine);
	ScreenModeL(modeNumber).iScreenStyleHash = hash;
	}

HBufC* CAknLayoutConfigWsiniParser::GetWsiniLC()
	{
	RFs& fs = CEikonEnv::Static()->FsSession();
	_LIT(KWsini, "z:\\system\\data\\wsini.ini");
	TEntry wsiniEntry;
	User::LeaveIfError(fs.Entry(KWsini, wsiniEntry));
	
	HBufC* wsiniText = HBufC::NewLC((wsiniEntry.iSize+1)/2);	// +1 /2 to round up and convert file size to UTF-16 character size
	TPtr wsiniPtr = wsiniText->Des();
	TPtr8 wsiniPtr8((TText8*)wsiniPtr.Ptr(), 0, wsiniPtr.MaxLength()*2);

	RFile wsiniFile;
	User::LeaveIfError(wsiniFile.Open(fs, KWsini, EFileRead | EFileShareReadersOnly));
	CleanupClosePushL(wsiniFile);
	
	User::LeaveIfError(wsiniFile.Read(wsiniPtr8, wsiniEntry.iSize));
	wsiniPtr.SetLength(wsiniPtr8.Length()/2);
	
	CleanupStack::PopAndDestroy(&wsiniFile);
	
	return wsiniText;
	}

inline TBool IsDigit(TText aChar)
	{
	return ('0' <= aChar && aChar <= '9');
	}
	
inline TBool IsKeywordChar(TText aChar)
	{
	return ('A' <= aChar && aChar <= 'Z') ||
		   IsDigit(aChar) ||
		   aChar == '_';
	}

inline TBool IsEndOfLine(TText aChar)
	{
	return aChar == '\r' || aChar == '\n';
	}
	
void CAknLayoutConfigWsiniParser::ParseWsiniL(const TDesC& aWsini)
	{
	if (!aWsini.Length())
		return;
	
	const TText* pChar = aWsini.Ptr();
	const TText* end = pChar + aWsini.Length();
	if (*pChar == 0xFEFF || *pChar == 0xFFFE)
		pChar++; 	// Skip, but otherwise ignore, the UTF-16 byte ordering marker (this is how it works in wserv)

	while (pChar != end)
		{
		// mark start of line
		const TText* kwStart = pChar;
		
		// find end of keyword (including digits)
		while (pChar != end && IsKeywordChar(*pChar))
			++pChar;

		// mark end of keyword (including digits)
		const TText* kwEnd = pChar;
		
		// count back to remove digits
		while (kwEnd != kwStart && IsDigit(*(kwEnd-1)))
			--kwEnd;
		
		// find end of line
		while (pChar != end && !IsEndOfLine(*pChar))
			++pChar;
		
		// parse the line
		ParseLineL(kwStart, kwEnd, pChar);

		// find start of next line
		while (pChar != end && IsEndOfLine(*pChar))
			++pChar;
		}
	}

void CAknLayoutConfigWsiniParser::ParseLineL(const TText* aKwStart, const TText* aKwEnd, const TText* aLineEnd)
	{
	if (aKwEnd == aKwStart)
		return;
	
	TPtrC kw(aKwStart, aKwEnd-aKwStart);
	TPtrC rest(aKwEnd, aLineEnd-aKwEnd);
	
	TInt targetCount = sizeof(iParseTable)/sizeof(SParseEntry);
	for (TInt ii=0; ii<targetCount; ii++)
		{
		const SParseEntry& parseEntry = iParseTable[ii];
		TPtrC header(parseEntry.iKeyword, parseEntry.iKeywordLen);
		if (kw == header)
			{
			(*parseEntry.iFunc)(this, rest);
			break;
			}
		}
	}

SHardwareStateInfo& CAknLayoutConfigWsiniParser::HardwareStateL(TInt aStateNumber)
	{
	TInt count = iHardwareStateArray.Count();
	for (TInt ii=0; ii<count; ii++)
		{
		if (iHardwareStateArray[ii].iStateNum == aStateNumber)
			return iHardwareStateArray[ii];
		}
		
	// not found, create a new one
	SHardwareStateInfo newInfo = { aStateNumber, 0, 0, 0 };
	iHardwareStateArray.AppendL(newInfo);
	return iHardwareStateArray[count];
	}

SAknScreenModeInfo& CAknLayoutConfigWsiniParser::ScreenModeL(TInt aModeNumber)
	{
	TInt count = iScreenInfoArray.Count();
	for (TInt ii=0; ii<count; ii++)
		{
		if (iScreenInfoArray[ii].iModeNumber == aModeNumber)
			return iScreenInfoArray[ii];
		}
	
	// we failed to find the screen mode.
	User::Leave(KErrNotFound);
	return iScreenInfoArray[0];	// dummy return, will never get here.
	}

TInt CAknLayoutConfigWsiniParser::ParseIntL(TPtrC& aLine)
	{
	TLex lex(aLine);
	lex.SkipSpace();
	TInt num;
	User::LeaveIfError(lex.Val(num));
	aLine.Set(lex.Remainder());
	return num;
	}

struct SKeyTranslation
    {
    const TDesC* iName;
    TInt iBase;
    TInt iRangeStart;
    TInt iRangeEnd;
    };

_LIT(KKeyNameApp, "EKeyApplication");
_LIT(KKeyNameDev, "EKeyDevice");

const SKeyTranslation KKeyTranslationTable[] =
    {
        {
        LIT_AS_DESC_PTR(KKeyNameApp),
        EKeyApplication0,
        0x0,
        0xf
        },
        {
        LIT_AS_DESC_PTR(KKeyNameDev),
        EKeyDevice0,
        0x0,
        0xf
        },
        {
        LIT_AS_DESC_PTR(KKeyNameApp),
        EKeyApplication10,
        0x10,
        0x1f
        },
        {
        LIT_AS_DESC_PTR(KKeyNameDev),
        EKeyDevice10,
        0x10,
        0x1f
        }
    };

TInt CAknLayoutConfigWsiniParser::ParseKeycodeL(TPtrC& aLine)
	{
	TLex lex(aLine);
	lex.SkipSpace();
	aLine.Set(lex.Remainder());
	
	TUint key;
    // look in the translation table for a KeyNameXX match
	TInt count = sizeof(KKeyTranslationTable)/sizeof(SKeyTranslation);
	for (TInt ii = 0; ii < count; ii++)
	    {
	    const SKeyTranslation& trans = KKeyTranslationTable[ii];
	    const TDesC& name = *trans.iName;
	    TInt len = name.Length();
	    if (aLine.Length() > len && aLine.Left(len) == name)
	        {
	        lex.Assign(aLine.Mid(len));
    	    if (lex.Val(key, EHex) == KErrNone && trans.iRangeStart <= key && key <= trans.iRangeEnd)
    	        {
            	aLine.Set(lex.Remainder());
    	        return trans.iBase + key - trans.iRangeStart;
    	        }
	        }
	    }
	
	if (aLine.Length())
		{
		// use the character
		key = aLine[0];
		aLine.Set(aLine.Mid(1));
		return key;
		}

	User::Leave(KErrCorrupt);
	return 0;
	}

TAknPrivSoftkeyLocation CAknLayoutConfigWsiniParser::ParseSoftkeyLocationL(TPtrC& aLine)
	{
	TAknPrivSoftkeyLocation location = EAknPrivSoftkeyLocationBottom;
	TLex lex(aLine);
	lex.SkipSpace();
	TPtrC token = lex.NextToken();
	if (token == _L("right"))
		location = EAknPrivSoftkeyLocationRight;
	else if (token == _L("left"))
		location = EAknPrivSoftkeyLocationLeft;
	aLine.Set(lex.Remainder());
	return location;
	}

TInt CAknLayoutConfigWsiniParser::ScreenStyleHash(TPtrC& aLine)
	{
	TInt hash = 0;
	TLex lex(aLine);
	TPtrC name = lex.NextToken();
	const TText* pChar = name.Ptr();
	const TText* end = pChar + name.Length();
	
	// calculate the hash
	for (; pChar != end; ++pChar)
		{
		hash *= KAknLayoutScreenStyleNameHashMult;
		hash += *pChar;
		}

	return hash;
	}
