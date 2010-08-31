/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:
*
*/


#include "EIKCONCL.H"
#include "EIKCONCL.PAN"
#include <eikconso.h>
#include <eikenv.h>
#include <eikappui.h>  
#include <basched.h>
#include <apgwgnam.h>
#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <eikdef.h>
#else
#include <eikdef.h>
#include <uikon/eikdefmacros.h>
#endif
#include <avkon.hrh>
#include <aknSctDialog.h>
#include <avkon.rsg>
#include <c32comm.h>
#include <aknappui.h>

GLDEF_C void Panic(TEikConClPanic aPanic)
	{
	_LIT(KPanicCat,"EIKON-CONCL");
	User::Panic(KPanicCat,aPanic);
	}

class CEikConsMessager;

class CCommsKeyReader : public CActive
	{
public:
	CCommsKeyReader(RComm& aComm, CEikConsMessager* aMessager);
	~CCommsKeyReader();

private:
	void RunL();
	void DoCancel();
	void Start();

private:
	RComm& iComm;
	CEikConsMessager* iMessager;
	TBuf8<1> iBuf;
	TBuf8<4> iMatch;
	};


class CCommsKeyWriter : public CActive
	{
public:
	CCommsKeyWriter(RComm& aComm);
	~CCommsKeyWriter();

	void Write(const TDesC& aDes);

private:
	void WriteIfReady();
	void RunL();
	void DoCancel();
	void AppendBlocking(TText8 aChar);

private:
	RComm& iComm;
	TBuf8<256> iBuf;
	TBuf8<256> iWrite;
	TBool iInFakeCancel;
	};


enum
	{
	EExit,
	ERead,
	EReadCancel,
	EWrite,
	ESetCursorPosAbs,
	ESetCursorPosRel,
	ESetCursorHeight,
	ESetTitle,
	EClearScreen,
	EClearToEndOfLine
	};


struct TFepKey
	{
	TText iLong;
	const TText* iLower;
	const TText* iUpper;
	};

const TFepKey KFepKeyTable[] = 
	{
		{ '0', _S(" 0\r"), _S(" 0\r") },
		{ '1', _S("\\.:1#*/-+=\"',()|`!$%^&_[]{};@~<>?"), _S("\\.:1#*/-+=\"',()|`!$%^&_[]{};@~<>?") },
		{ '2', _S("abc2"), _S("ABC2") },
		{ '3', _S("def3"), _S("DEF3") },
		{ '4', _S("ghi4"), _S("GHI4") },
		{ '5', _S("jkl5"), _S("JKL5") },
		{ '6', _S("mno6"), _S("MNO6") },
		{ '7', _S("pqrs7"), _S("PQRS7") },
		{ '8', _S("tuv8"), _S("TUV8") },
		{ '9', _S("wxyz9"), _S("WXYZ9") }
	};

const TText* const KModeNames[] = 
	{
	_S("Lower"),
	_S("Caps"),
	_S("Numeric")
	};

const TText* const KIOModeNames[] = 
	{
	_S("Screen"),
	_S("Serial"),
	_S("Ansi-Serial")
	};

_LIT(KCommModule, "IRCOMM");
_LIT(KCommPort, "IRCOMM::0");

//
// class CEikConsMessager
//

class CEikConsMessager : public CActive
	{
public:
	enum TMyFlags
		{
		EShift,
		EDigitPressed
		};
	enum TKeyMode
		{
		ELower,
		ECaps,
		ENumeric,
		ENumModes
		};
	enum TIOMode
		{
		EScreen,
		ESerial,
		EAnsi,
		ENumIOModes
		};
public:
	CEikConsMessager(CEikConsoleScreen* aScreen,RThread aParentThread);
	~CEikConsMessager();
	void ConstructL(CEikConsoleClient* aClient);
	void HandleKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	void AddKeyEvent(const TKeyEvent& aKeyEvent);
private: // overridden
	void RunL();
	void DoCancel();
private: // internal
	void CompleteReadRequest();
private: // fep like stuff
	void StartTimer();
	static TInt TimerCallBack(TAny* aThis);
	void DoTimer();
	void LaunchSCTL();
	void HandleDigit(const TKeyEvent& aKeyEvent, TEventCode aType);
	void StartCommsL();
	void StopComms();
	void WriteComms(const TDesC& aMsg);

private:
	CEikConsoleScreen* iScreen;
	RThread iParentThread;
	TRequestStatus* iReadStatus;
	TKeyEvent* iKeyEvent;
	TInt iMessage;
	const TAny* iParam;
	TRequestStatus* iReplyStatus;
	CCirBuf<TKeyEvent>* iKeyQ;

	// fep like stuff
	TKeyEvent iLastKey;
	CPeriodic* iTimer;
	TBitFlags iFlags;
	TInt iMultiStep;
	TKeyMode iKeyMode;
	TIOMode iIOMode;
	RCommServ iCommServ;
	RComm iComm;
	CCommsKeyReader* iReader;
	CCommsKeyWriter* iWriter;
	};

CEikConsMessager::CEikConsMessager(CEikConsoleScreen* aScreen,RThread aParentThread)
	: CActive(EActivePriorityIpcEventsHigh),
	iParentThread(aParentThread)
	{
	iScreen=aScreen;
	}

CEikConsMessager::~CEikConsMessager()
	{
	StopComms();
	delete iTimer;
	iParentThread.Close();
	delete iKeyQ;
	}

void CEikConsMessager::ConstructL(CEikConsoleClient* aClient)
	{
	iTimer = CPeriodic::NewL(EPriorityStandard);
	iKeyQ=new(ELeave) CCirBuf<TKeyEvent>;
	iKeyQ->SetLengthL(40);	// buffer length, too high? too low?
	iKeyEvent=(&aClient->iKeyEvent);
	aClient->iThreadStatus=(&iStatus);
	aClient->iMessage=(&iMessage);
	aClient->iParam=(&iParam);
	aClient->iReplyStatus=(&iReplyStatus);
	aClient->iScreen=iScreen;
	CActiveScheduler::Add(this);
	iStatus=KRequestPending;
	SetActive();
	}

void CEikConsMessager::DoCancel()
	{
	}

void CEikConsMessager::RunL()
	{
	switch (iMessage)
		{
	case EExit:
		CBaActiveScheduler::Exit();
		break;
	case ERead:
		if (iReadStatus)
			Panic(EEikConClPanicReadAlreadyOutstanding);
		iReadStatus=(TRequestStatus*)iParam;
		if (iKeyQ->Count()>0) // already a buffered event
			CompleteReadRequest();
		break;
	case EReadCancel:
		if (iReadStatus)
			iParentThread.RequestComplete(iReadStatus,KErrCancel);
		break;
	case EWrite:
		iScreen->Write(*(const TDesC*)iParam);
		if (iIOMode != EScreen)
			WriteComms(*(const TDesC*)iParam);
		break;
	case ESetCursorPosAbs:
		iScreen->SetCursorPosAbs(*(const TPoint*)iParam);
		if (iIOMode == EAnsi)
			{
			TPoint point = iScreen->CursorPos();
			TBuf<10> buf;
			buf.Format(_L("\033[%d;%dH"), point.iY, point.iX);
			WriteComms(buf);
			}
		break;
	case ESetCursorPosRel:
		iScreen->SetCursorPosRel(*(const TPoint*)iParam);
		if (iIOMode == EAnsi)
			{
			TPoint point = iScreen->CursorPos();
			TBuf<10> buf;
			buf.Format(_L("\033[%d;%dH"), point.iY, point.iX);
			WriteComms(buf);
			}
		break;
	case ESetCursorHeight:
		iScreen->SetCursorHeight((TInt)iParam);
		break;
	case EClearScreen:
		iScreen->ClearScreen();
		if (iIOMode == EAnsi)
			{
			WriteComms(_L("\033[2J"));
			}
		break;
	case EClearToEndOfLine:
		iScreen->ClearToEndOfLine();
		if (iIOMode == EAnsi)
			{
			WriteComms(_L("\033[K"));
			}
		break;
		}
	iStatus=KRequestPending;
	SetActive();
	iParentThread.RequestComplete(iReplyStatus,0);
	}

void CEikConsMessager::CompleteReadRequest()
	{
	if (iReadStatus)
		{ 
		iKeyQ->Remove(iKeyEvent);;
		iParentThread.RequestComplete(iReadStatus,0);
		}
	}

void CEikConsMessager::HandleKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	iFlags.Assign(EShift, aKeyEvent.iModifiers & EModifierShift);

	if ('0' <= aKeyEvent.iScanCode && aKeyEvent.iScanCode <= '9')
		{
		HandleDigit(aKeyEvent, aType);
		}
	else if (aKeyEvent.iScanCode == EStdKeyHash)
		{
		if (aType == EEventKeyDown)
			{
			if (iFlags[EShift])
				{
				iIOMode = TIOMode((iIOMode+1)%ENumIOModes);
				User::InfoPrint(TPtrC(KIOModeNames[iIOMode]));
				if (iIOMode == ESerial)
					{
					StartCommsL();
					}
				else if (iIOMode == EScreen)
					StopComms();
				}
			else
				{
				iKeyMode = TKeyMode((iKeyMode+1)%ENumModes);
				User::InfoPrint(TPtrC(KModeNames[iKeyMode]));
				}
			iTimer->Cancel();
			}
		}
	else if (aType == EEventKey)
		{
		if (aKeyEvent.iCode == '*')
			{
			LaunchSCTL();
			iTimer->Cancel();
			}
		else if (aKeyEvent.iCode != EKeyF21)
			{
			AddKeyEvent(aKeyEvent);
			iTimer->Cancel();
			}
		}
	}

void CEikConsMessager::AddKeyEvent(const TKeyEvent& aKeyEvent)
	{
	TInt ret=iKeyQ->Add(&aKeyEvent);
	if (ret==0)
		CEikonEnv::Beep();
	if (iKeyQ->Count()==1) // client may be waiting on this key event
		CompleteReadRequest();
	}

void CEikConsMessager::LaunchSCTL()
	{
    TBuf<8> specialChars;
    TBool shift = !COMPARE_BOOLS(iFlags[EShift], (iKeyMode==ECaps));
    TInt sctCase = (shift ? EAknSCTUpperCase : EAknSCTLowerCase);
    CAknCharMapDialog* dialog=new(ELeave) CAknCharMapDialog(sctCase, specialChars);
    if (dialog->ExecuteLD(R_AVKON_SPECIAL_CHARACTER_TABLE_DIALOG))
        {
        TKeyEvent event =  { 0, 0, 0, 0 };
        for ( TInt ii = 0; ii < specialChars.Length(); ii++)
            {
            if ( specialChars[ii] == 0x000A ) // 0x000A is line feed
                {
                event.iCode = EKeyEnter;
                event.iScanCode = EKeyEnter;
                }
            else
                {
                event.iCode = specialChars[ii];
                event.iScanCode = specialChars[ii];
                }
            AddKeyEvent(event);
            }
        }
    }

void CEikConsMessager::HandleDigit(const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	TText digit = TText(aKeyEvent.iScanCode);
	__ASSERT_DEBUG('0' <= digit && digit <= '9', Panic(EEikConClPanicIllegalFepChar));
	TBool shift = !COMPARE_BOOLS(iFlags[EShift], (iKeyMode==ECaps));
	const TFepKey& fepKey = KFepKeyTable[digit - '0'];
	TPtrC keys(shift ? fepKey.iUpper : fepKey.iLower);

	if (iKeyMode == ENumeric)
		{
		if (aType == EEventKey)
			{
			AddKeyEvent(aKeyEvent);
			iTimer->Cancel();
			}
		}
	else
		{
		if (aType == EEventKeyDown)
			{
			iFlags.Set(EDigitPressed);
			if (digit == iLastKey.iScanCode)
				{
				iMultiStep = (iMultiStep + 1) % keys.Length();
				TKeyEvent del = {EKeyBackspace, EStdKeyBackspace, 0, 0};
				AddKeyEvent(del);
				TKeyEvent event = {keys[iMultiStep], keys[iMultiStep], 0, 0};
				AddKeyEvent(event);
				}
			else
				{
				iMultiStep = 0;
				TKeyEvent event = {keys[iMultiStep], keys[iMultiStep], 0, 0};
				AddKeyEvent(event);
				}

			StartTimer();
			iLastKey = aKeyEvent;
			}
		else if (aType == EEventKeyUp)
			{
			iFlags.Clear(EDigitPressed);
			}
		}
	}

void CEikConsMessager::StartTimer()
	{
	iTimer->Cancel();
	iTimer->Start(800000, 1000000, TCallBack(TimerCallBack, this));
	}

TInt CEikConsMessager::TimerCallBack(TAny* aThis)
	{
	((CEikConsMessager*)aThis)->DoTimer();
	return 0;
	}

void CEikConsMessager::DoTimer()
	{
	if (iFlags[EDigitPressed])
		{
		TText digit = TText(iLastKey.iScanCode);
		__ASSERT_DEBUG('0' <= digit && digit <= '9', Panic(EEikConClPanicIllegalFepChar));
		TText key = KFepKeyTable[digit - '0'].iLong;
		TKeyEvent del = {EKeyBackspace, EStdKeyBackspace, 0, 0};
		AddKeyEvent(del);
		TKeyEvent event = {key, key, 0, 0};
		AddKeyEvent(event);
		iFlags.Clear(EDigitPressed);
		}

	iLastKey.iScanCode = 0;
	iMultiStep = 0;
	}

void CEikConsMessager::StartCommsL()
	{
	User::LeaveIfError(iCommServ.Connect());
	User::LeaveIfError(iCommServ.LoadCommModule(KCommModule));
	User::LeaveIfError(iComm.Open(iCommServ, KCommPort, ECommExclusive));
	TCommConfig cBuf;
	iComm.Config(cBuf);
	TCommConfigV01& c=cBuf();
	c.iRate=EBps115200;
	c.iDataBits=EData8;
	c.iStopBits=EStop1;
	c.iParity=EParityNone;
	User::LeaveIfError(iComm.SetConfig(cBuf));
	delete iReader;
	iReader=0;
	iReader = new(ELeave) CCommsKeyReader(iComm, this);
	delete iWriter;
	iWriter=0;
	iWriter = new(ELeave) CCommsKeyWriter(iComm);
	}

void CEikConsMessager::StopComms()
	{
	delete iWriter;
	iWriter=0;
	delete iReader;
	iReader=0;
	iComm.Close();
	iCommServ.Close();
	}

void CEikConsMessager::WriteComms(const TDesC& aMsg)
	{
	if (iWriter)
		{
		iWriter->Write(aMsg);
		}
	}


struct TEscSeq
	{
	TText8 iText[4];
	TKeyCode iCode;
	TStdScanCode iScanCode;
	};

const TEscSeq KEscSeqs[] =
	{
		{"[?D", EKeyLeftArrow, EStdKeyLeftArrow},
		{"[?C", EKeyRightArrow, EStdKeyRightArrow},
		{"[?A", EKeyUpArrow, EStdKeyUpArrow},
		{"[?B", EKeyDownArrow, EStdKeyDownArrow}
	};


CCommsKeyReader::CCommsKeyReader(RComm& aComm, CEikConsMessager* aMessager)
: CActive(EPriorityHigh), iComm(aComm), iMessager(aMessager)
	{
	CActiveScheduler::Add(this);
	Start();
	}

CCommsKeyReader::~CCommsKeyReader()
	{
	Cancel();
	}

void CCommsKeyReader::RunL()
	{
	if (iStatus == KErrNone)
		{
		Start();
		if (iMatch.Length() || iBuf[0]=='[')
			{
			iMatch.Append(iBuf[0]);
			for (TInt i=0; i<4; i++)
				{
				if (iMatch.Match(TPtrC8(KEscSeqs[i].iText)) == 0)
					{
					TKeyEvent event = {KEscSeqs[i].iCode, KEscSeqs[i].iScanCode, 0, 0};
					iMessager->AddKeyEvent(event);
					iMatch.Zero();
					return;
					}
				}
			if (iMatch.Length() >= 3)
				iMatch.Zero();
			else
				return;
			}
		TKeyEvent event = {iBuf[0], iBuf[0], 0, 0};
		iMessager->AddKeyEvent(event);
		}
	}

void CCommsKeyReader::DoCancel()
	{
	iComm.ReadCancel();
	}

void CCommsKeyReader::Start()
	{
	iComm.ReadOneOrMore(iStatus, iBuf);
	SetActive();
	}


CCommsKeyWriter::CCommsKeyWriter(RComm& aComm)
: CActive(EPriorityStandard), iComm(aComm), iInFakeCancel(EFalse)
	{
	CActiveScheduler::Add(this);
	}

CCommsKeyWriter::~CCommsKeyWriter()
	{
	Cancel();
	}

void CCommsKeyWriter::Write(const TDesC& aDes)
	{
	for (TInt i=0; i<aDes.Length(); i++)
		{
		if (aDes[i] == '\n')
			{
			AppendBlocking('\r');
			}
		AppendBlocking(TText8(aDes[i]));
		}
	WriteIfReady();
	}

void CCommsKeyWriter::WriteIfReady()
	{
	if (!IsActive() && iBuf.Length()>0)
		{
		iWrite=iBuf;
		iBuf.Zero();
		iComm.Write(iStatus, iWrite);
		SetActive();
		}
	}

void CCommsKeyWriter::AppendBlocking(TText8 aChar)
	{
	if (iBuf.Length() >= iBuf.MaxLength())
		{
		RTimer t;
		t.CreateLocal();
		TRequestStatus tR;
		t.After(tR, 2000000);	// 2 second timeout
		User::WaitForRequest(iStatus, tR);
		if (iStatus != KRequestPending)
			{
			// write completed
			t.Cancel();
			User::WaitForRequest(tR);
			
			if (IsActive())
			    {
                iInFakeCancel = ETrue;
                Cancel();
			    }
			
            iWrite.Zero();
            WriteIfReady();
            
			}
		else
			{
			// timeout, throw away the buffered data - sorry!
			iBuf.Zero();
			}
		t.Close();
		}

	iBuf.Append(aChar);
	}

void CCommsKeyWriter::RunL()
	{
	iWrite.Zero();
	WriteIfReady();
	}

void CCommsKeyWriter::DoCancel()
	{
    if (iInFakeCancel == EFalse)    
        iComm.WriteCancel();
    
    iInFakeCancel = EFalse;
	}



//
// class CEikConsAppUi
//

struct SCommandLine
	{
	RThread iParentThread;
	TRequestStatus* iStatus;
	CEikConsoleClient* iClient;
	TSize iSize;
	const TDesC* iTitle;
	};

class CEikConsAppUi : public CAknAppUi //CEikAppUi
	{
public:
    DECLARE_TYPE_ID(0x2001b26a)
public:
	void ConstructL(const SCommandLine* aComLine);
	~CEikConsAppUi();
private: // overridden
	TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void HandleForegroundEventL(TBool aForeground);
	void SetAndDrawFocus(TBool aFocus);
protected:	// from MObjectProvider
	virtual TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
	virtual MObjectProvider* MopNext();
private:
	CEikConsoleScreen* iScreen;
	CEikConsoleControl* iControl;
	CEikConsMessager* iMessager;
	};

CEikConsAppUi::~CEikConsAppUi()
	{
	delete(iScreen);
	delete(iMessager);
	}
	
void CEikConsAppUi::ConstructL(const SCommandLine* aComLine)
	{
   // CEikAppUi::BaseConstructL(ENoAppResourceFile);
    CAknAppUi::BaseConstructL(ENoAppResourceFile | ENoScreenFurniture | EAknEnableMSK);
    iScreen=new(ELeave) CEikConsoleScreen;
	iScreen->ConstructL(*(aComLine->iTitle),0);
	iControl=iScreen->ConsoleControl();
	iControl->SetFocus(ETrue,EDrawNow);
	iMessager=new(ELeave) CEikConsMessager(iScreen,aComLine->iParentThread);
	iMessager->ConstructL(aComLine->iClient);
	RThread().SetPriority(EPriorityMore);
	}

void CEikConsAppUi::HandleForegroundEventL(TBool aForeground)
	{
	if (aForeground)
		RThread().SetPriority(EPriorityMore);
	CEikAppUi::HandleForegroundEventL(aForeground);
	}

void CEikConsAppUi::SetAndDrawFocus(TBool aFocus)
	{
	if (iControl)
		iControl->SetFocus(aFocus,EDrawNow);
	}

TKeyResponse CEikConsAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	iMessager->HandleKeyEventL(aKeyEvent, aType);
	return EKeyWasConsumed;
	}

TTypeUid::Ptr CEikConsAppUi::MopSupplyObject(TTypeUid aId)
/** Retrieves an object of the same type as that encapsulated in aId.

This function is used to allow to ask owners for access to 
other objects that they own.

Other than in the case where NULL is returned, the object returned must be 
of the same object type - that is, the ETypeId member of the object pointed 
to by the pointer returned by this function must be equal to the iUid member 
of aId.

@param aId An encapsulated object type ID.
@return Encapsulates the pointer to the object provided. Note that the encapsulated 
pointer may be NULL. */
	{
    if (aId.iUid == ETypeId)
        {
        // Touch compatibility mode uses this to detect console application
        return aId.MakePtr(this);
        }
	return TTypeUid::Null();
	}

MObjectProvider* CEikConsAppUi::MopNext()
/** Retrieves the parent.

@return A pointer to an object provider, or NULL if none is defined. 
@publishedAll 
@released */
	{
	CEikonEnv* env=(CEikonEnv*)iCoeEnv;
	return env->AppUiFactory();
	}

//
// class CConsEikonEnv
//

class CConsEikonEnv : public CEikonEnv
	{
public:
	void ConstructConsoleEnvironmentL(const SCommandLine* aComLine);

#if defined(SYMBIAN_UI_FRAMEWORKS_CONTROL_API_V2)
private:
	IMPORT_C virtual void CEikonEnv_Reserved_1();
	IMPORT_C virtual void CEikonEnv_Reserved_2();
	IMPORT_C virtual void CEikonEnv_Reserved_3();
	IMPORT_C virtual void CEikonEnv_Reserved_4();
	IMPORT_C virtual void CEikonEnv_Reserved_5();
	IMPORT_C virtual void CEikonEnv_Reserved_6();
	IMPORT_C virtual void CEikonEnv_Reserved_7();
	IMPORT_C virtual void CEikonEnv_Reserved_8();
	IMPORT_C virtual void CEikonEnv_Reserved_9();
	IMPORT_C virtual void CEikonEnv_Reserved_10();	
#endif	
	};

void CConsEikonEnv::ConstructConsoleEnvironmentL(const SCommandLine* aComLine)
	{
	ConstructL();
	CEikConsAppUi* appUi=new(ELeave) CEikConsAppUi;
	appUi->ConstructL(aComLine);
	CApaWindowGroupName* wgName=CApaWindowGroupName::NewLC(iWsSession);
	TPtrC caption=*(aComLine->iTitle);
	wgName->SetCaptionL(caption);
	wgName->SetRespondsToShutdownEvent(EFalse);
	wgName->SetRespondsToSwitchFilesEvent(EFalse);
	wgName->SetWindowGroupName(iRootWin);
	CleanupStack::PopAndDestroy(); // wgName

	User::RenameProcess(caption);
	User::RenameThread(caption);
	}
	
#if defined(SYMBIAN_UI_FRAMEWORKS_CONTROL_API_V2)
EXPORT_C void CConsEikonEnv::CEikonEnv_Reserved_1()
	{
	}
	
EXPORT_C void CConsEikonEnv::CEikonEnv_Reserved_2()
	{
	}
	
EXPORT_C void CConsEikonEnv::CEikonEnv_Reserved_3()
	{
	}
	
EXPORT_C void CConsEikonEnv::CEikonEnv_Reserved_4()
	{
	}
	
EXPORT_C void CConsEikonEnv::CEikonEnv_Reserved_5()
	{
	}
	
EXPORT_C void CConsEikonEnv::CEikonEnv_Reserved_6()
	{
	}
	
EXPORT_C void CConsEikonEnv::CEikonEnv_Reserved_7()
	{
	}
	
EXPORT_C void CConsEikonEnv::CEikonEnv_Reserved_8()
	{
	}
	
EXPORT_C void CConsEikonEnv::CEikonEnv_Reserved_9()
	{
	}
	
EXPORT_C void CConsEikonEnv::CEikonEnv_Reserved_10()
	{
	}
#endif

TInt ConsoleClientStartFunction(TAny* aParam)
	{
	const SCommandLine* comLine=(const SCommandLine*)aParam;
	TInt err=KErrNoMemory;
    CConsEikonEnv* coe=new CConsEikonEnv;
	if (coe)
		{
		TRAP(err,coe->ConstructConsoleEnvironmentL(comLine));
		}
	TRequestStatus* pS=(comLine->iStatus);
	comLine->iParentThread.RequestComplete(pS,err);
    if (!err)
        coe->ExecuteD();
	return(0);
	}

//
// class CEikConsoleClient
//

CEikConsoleClient::~CEikConsoleClient()
	{
	if (iLogonStatus.Int()==KRequestPending && iReplyStatus)
		SendReceive(EExit,NULL);
	iThread.Close();
	}

CEikConsoleClient::CEikConsoleClient()
	{
	}
	
const TInt KMaxHeapSize=0x1000*254; // chunks are a megabyte anyway

TInt CEikConsoleClient::Create(const TDesC& aTitle,TSize aSize)
	{ 
	TInt err;
	TRequestStatus status=KRequestPending;
	SCommandLine comLine;
	comLine.iStatus=(&status);
	comLine.iClient=this;
	comLine.iSize=aSize;
	comLine.iTitle=&aTitle;
	TBuf<20> threadName;
	TInt num=0;
	do
		{
		_LIT(KTemp,"UI%02d");
		threadName.Format(KTemp,num++); // !! review the title
		err=iThread.Create(threadName,ConsoleClientStartFunction,KDefaultStackSize,KMinHeapSize,KMaxHeapSize,&comLine,EOwnerThread);
		} while(err==KErrAlreadyExists);
	if (!err)
		{
		iThread.Logon(iLogonStatus);
		comLine.iParentThread.Duplicate(iThread);
		iThread.Resume();
		User::WaitForRequest(status,iLogonStatus);
		err=status.Int();
		}
	return(err);
	}

void CEikConsoleClient::SendReceive(TInt aMessage,const TAny* aParam)
	{
	if (iLogonStatus.Int()!=KRequestPending)
		User::Exit(KErrCancel);
	*iMessage=aMessage;
	*iParam=aParam;
	TRequestStatus replyStatus=KRequestPending;
	*iReplyStatus=(&replyStatus);
	TRequestStatus* pS=iThreadStatus;
	iThread.RequestComplete(pS,0);
	User::WaitForRequest(replyStatus,iLogonStatus);
	}

void CEikConsoleClient::Read(TRequestStatus& aStatus)
	{
	aStatus=KRequestPending;
	SendReceive(ERead,&aStatus);
	}

void CEikConsoleClient::ReadCancel()
	{
	SendReceive(EReadCancel,NULL);
	}

void CEikConsoleClient::Write(const TDesC& aDes)
	{
	SendReceive(EWrite,&aDes);
	}

TPoint CEikConsoleClient::CursorPos() const
	{
	return(iScreen->CursorPos());
	}

void CEikConsoleClient::SetCursorPosAbs(const TPoint& aPosition)
	{
	SendReceive(ESetCursorPosAbs,&aPosition);
	}

void CEikConsoleClient::SetCursorPosRel(const TPoint &aVector)
	{
	SendReceive(ESetCursorPosRel,&aVector);
	}

void CEikConsoleClient::SetCursorHeight(TInt aPercentage)
	{
	SendReceive(ESetCursorHeight,aPercentage);
	}
		
void CEikConsoleClient::SetTitle(const TDesC& aTitle)
	{
	SendReceive(ESetTitle,&aTitle);
	}

void CEikConsoleClient::ClearScreen()
	{
	SendReceive(EClearScreen,NULL);
	}

void CEikConsoleClient::ClearToEndOfLine()
	{
	SendReceive(EClearToEndOfLine,NULL);
	}

TSize CEikConsoleClient::ScreenSize() const
	{
	return(iScreen->ScreenSize()+TSize(2,2));		// e32 console adds 2,2 for border, so we should too!
	}

TKeyCode CEikConsoleClient::KeyCode() const
	{
	return((TKeyCode)iKeyEvent.iCode);
	}

TUint CEikConsoleClient::KeyModifiers() const
	{
	return(iKeyEvent.iModifiers);
	}

extern "C" {
EXPORT_C TAny* NewConsole()
	{
	return(new CEikConsoleClient);
	}
}
