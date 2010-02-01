// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

/**
 @file
 @internalComponent - Internal Symbian test code 
*/


#include <techview/eikdialg.h>
#include <tnotdial.rsg>
#include <bautils.h>
#include "tpluginV2.h"
#include "tnotdial.h"

#include <uikon.hrh>
#include <tnotdial.rsg>
#include <uikon/eikscchange.h>

const TUid KScreenOutputChannel ={0x00000666};
const TUid KLEDOutputChannel ={0x00000111};

_LIT(KResFileNamePath,"\\system\\test\\tnotdial\\");
_LIT(KResFileName1,"tnotdial.rsc");

_LIT8(KStartAgendaDialogResponse,"Response: started Agenda dialog (asynch.)");
_LIT8(KStartAgendaLEDResponse,"Response: started LED Agenda notifier (asynch.)");
_LIT8(KUpdateAgendaDialogResponseAsync,"Response: Updated Agenda dialog (asynch.)");
_LIT8(KUpdateAgendaLEDResponseAsync,"Response: Updated LED Agenda notifier (asynch.)");
_LIT8(KUpdateAgendaResponse, "Response: Updated Agenda Dialog");
_LIT8(KUpdateAgendaLEDResponse,"Response: Updated Agenda LED");
_LIT8(KUpdatePhoneResponse, "Response: Updated Phone Dialog");
_LIT8(KUpdatePhoneLEDResponse, "Response: Updated Phone LED");
_LIT8(KUpdatePhoneResponseAsync, "Response: Updated Phone Dialog (asynch.)");
_LIT8(KUpdatePhoneLEDResponseAsync, "Response: Updated Phone LED (asynch.)");
_LIT8(KUpdateBatteryResponse, "Response: Updated Battery Dialog");
_LIT8(KUpdateBatteryLEDResponse, "Response: Updated Battery LED");
_LIT8(KUpdateBatteryResponseAsync, "Response: Updated Battery Dialog (asynch.)");
_LIT8(KUpdateBatteryLEDResponseAsync, "Response: Updated Battery LED (asynch.)");

EXPORT_C   CArrayPtr<MEikSrvNotifierBase2>* NotifierArray()
//
// Lib main entry point
//
	{
	//RDebug::Print(_L("\nExported entry point\n"));
	CArrayPtrFlat<MEikSrvNotifierBase2>* subjects=new (ELeave)CArrayPtrFlat<MEikSrvNotifierBase2>(6);
	CleanupStack::PushL(subjects);
	subjects->AppendL(CMyPhoneNotifierSubject::NewLC()); 
	subjects->AppendL(CMyLEDPhoneNotifierSubject::NewLC());
	subjects->AppendL(CMyLEDLowBatteryNotifierSubject::NewLC());
	subjects->AppendL(CMyLowBatteryNotifierSubject::NewLC()); 
	subjects->AppendL(CMyAgendaNotifierSubject::NewLC()); 
	subjects->AppendL(CMyLEDAgendaNotifierSubject::NewLC());
	CleanupStack::Pop(7, subjects);
	return subjects;
	}

GLDEF_C TInt E32Dll(
					)
//
// DLL entry point
//
	{
//	INFO_PRINTF1(_L("\nPlugin E32 Dll entry point\n"));
    return(KErrNone);
   	}


void CMyPhoneNotifierSubject::Release()
	{
	delete this;
	}

CMyPhoneNotifierSubject::TNotifierInfo CMyPhoneNotifierSubject::RegisterL()
	{
	iInfo.iUid=KMyNewPhoneNotifierUid;
	iInfo.iChannel=KScreenOutputChannel;
	iInfo.iPriority=ENotifierPriorityVHigh;
	return iInfo;
	}

CMyPhoneNotifierSubject::TNotifierInfo CMyPhoneNotifierSubject::Info() const
	{
	return iInfo;
	}

TPtrC8 CMyPhoneNotifierSubject::StartL(const TDesC8& /*aBuffer*/)
	{
	RDebug::Print(_L("Plugin: Phone notifier started\n"));
	RouseSleepingDialog();
	return KNullDesC8();
	}


void CMyPhoneNotifierSubject::StartL(const TDesC8& aBuffer, TInt /*aReplySlot*/, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: Phone notifier started\n"));
	StartL(aBuffer);
	aMessage.Complete(EEikNotExtRequestCompleted);
	}

void CMyPhoneNotifierSubject::Cancel()
	{
	RDebug::Print(_L("Plugin: Phone notifier canceled\n"));
	ExitSleepingDialog();
	}

TPtrC8 CMyPhoneNotifierSubject::UpdateL(const TDesC8& aBuffer)
	{
	RDebug::Print(_L("Plugin: Phone notifier updated\n"));
	TBuf<100> buffer;
	buffer.Copy(aBuffer);
	CEikonEnv::Static()->InfoMsgWithAlignment(EHLeftVBottom,buffer);
	return KUpdatePhoneResponse();
	}

void CMyPhoneNotifierSubject::UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: Phone notifier updated (asynch. call) \n"));
	UpdateL(aBuffer);
	TRAPD(err,aMessage.WriteL(aReplySlot,KUpdatePhoneResponseAsync));
	__ASSERT_ALWAYS(!err,User::Panic(_L("WriteL(aReplySlot,KUpdatePhoneResponseAsync))"),err));
	aMessage.Complete(EEikNotExtRequestCompleted);
	}

CMyPhoneNotifierSubject* CMyPhoneNotifierSubject::NewLC()
	{
	CMyPhoneNotifierSubject* self=new (ELeave) CMyPhoneNotifierSubject();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMyPhoneNotifierSubject::CMyPhoneNotifierSubject()
	{
	}

CMyPhoneNotifierSubject::~CMyPhoneNotifierSubject()
	{
	}

void CMyPhoneNotifierSubject::ConstructL()
	{
	//Get the system filesession	
	RFs& fs = CEikonEnv::Static()->FsSession(); 
	//Get the file finder 
	TFindFile* findFile=new(ELeave) TFindFile(fs);
    CleanupStack::PushL(findFile);
	//File name parser
	TParse* fileNameParser=new(ELeave) TParse;
    CleanupStack::PushL(fileNameParser);

	//search for all rsc files in *\system\libs\plugins\*.rsc
	CDir* directory=NULL;
	User::LeaveIfError(findFile->FindWildByDir(KResFileName1, KResFileNamePath, directory));
	CleanupStack::PushL(directory);

	const TEntry& entry=(*directory)[directory->Count()-1];
	fileNameParser->Set(entry.iName,&findFile->File(),NULL);
	TFileName resourceFileName(fileNameParser->FullName());
	
	BaflUtils::NearestLanguageFile(iCoeEnv->FsSession(),resourceFileName);
	RDebug::Print(_L("Resource file name [%S]"),&resourceFileName);
	TInt offset=iEikonEnv->AddResourceFileL(resourceFileName);
	CleanupStack::PopAndDestroy(3);

	TRAPD(err,ConstructSleepingAlertDialogL(R_PHONE_RINGS));
	iEikonEnv->DeleteResourceFile(offset);
	User::LeaveIfError(err);
	}

void CMyPhoneNotifierSubject::PreLayoutDynInitL()
	{ // must not fail
	}

TBool CMyPhoneNotifierSubject::OkToExitL(TInt /*aButtonId*/)
	{
	iManager->CancelNotifier(iInfo.iUid);
	return ETrue;
	}

void CMyLowBatteryNotifierSubject::Release()
	{
	delete this;
	}

CMyLowBatteryNotifierSubject::TNotifierInfo CMyLowBatteryNotifierSubject::RegisterL()
	{
	iInfo.iUid=KMyNewLowBatteryNotifierUid;
	iInfo.iChannel=KScreenOutputChannel;
	iInfo.iPriority=ENotifierPriorityAbsolute;
	return iInfo;
	}

CMyLowBatteryNotifierSubject::TNotifierInfo CMyLowBatteryNotifierSubject::Info() const
	{
	return iInfo;
	}

TPtrC8 CMyLowBatteryNotifierSubject::StartL(const TDesC8& /*aBuffer*/)
	{
	RDebug::Print(_L("Plugin: Low battery notifier started\n"));
	RouseSleepingDialog();
	return KNullDesC8();
	}

void CMyLowBatteryNotifierSubject::StartL(const TDesC8& aBuffer, TInt /*aReplySlot*/, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: Low battery notifier started \n"));
	StartL(aBuffer);
	aMessage.Complete(EEikNotExtRequestCompleted);
	}

void CMyLowBatteryNotifierSubject::Cancel()
	{
	RDebug::Print(_L("Plugin: Low battery notifier canceled\n"));
	ExitSleepingDialog();
	}

TPtrC8 CMyLowBatteryNotifierSubject::UpdateL(const TDesC8& aBuffer)
	{
	RDebug::Print(_L("Plugin: Low battery notifier updated\n"));
	TBuf<100> buffer;
	buffer.Copy(aBuffer);
	CEikonEnv::Static()->InfoMsgWithAlignment(EHLeftVBottom,buffer);
	return KUpdateBatteryResponse();
	}

void CMyLowBatteryNotifierSubject::UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: Low Battery notifier updated (asynch. call) \n"));
	UpdateL(aBuffer);
	TRAPD(err,aMessage.WriteL(aReplySlot,KUpdateBatteryResponseAsync));
	__ASSERT_ALWAYS(!err,User::Panic(_L("WriteL(aReplySlot,KUpdateBatteryResponseAsync)"),err));
	aMessage.Complete(EEikNotExtRequestCompleted);
	}

CMyLowBatteryNotifierSubject* CMyLowBatteryNotifierSubject::NewLC()
	{
	CMyLowBatteryNotifierSubject* self=new (ELeave) CMyLowBatteryNotifierSubject();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMyLowBatteryNotifierSubject::CMyLowBatteryNotifierSubject()
	{
	}

CMyLowBatteryNotifierSubject::~CMyLowBatteryNotifierSubject()
	{
	}

void CMyLowBatteryNotifierSubject::ConstructL()
	{
	//Get the system filesession	
	RFs& fs = CEikonEnv::Static()->FsSession(); 
	//Get the file finder 
	TFindFile* findFile=new(ELeave) TFindFile(fs);
    CleanupStack::PushL(findFile);
	//File name parser
	TParse* fileNameParser=new(ELeave) TParse;
    CleanupStack::PushL(fileNameParser);

	//search for all rsc files in *\system\libs\plugins\*.rsc
	CDir* directory=NULL;
	User::LeaveIfError(findFile->FindWildByDir(KResFileName1, KResFileNamePath, directory));
	CleanupStack::PushL(directory);

	const TEntry& entry=(*directory)[directory->Count()-1];
	fileNameParser->Set(entry.iName,&findFile->File(),NULL);
	TFileName resourceFileName(fileNameParser->FullName());

	BaflUtils::NearestLanguageFile(iCoeEnv->FsSession(),resourceFileName);
	RDebug::Print(_L("Resource file name [%S]"),&resourceFileName);
	TInt offset=iEikonEnv->AddResourceFileL(resourceFileName);
	CleanupStack::PopAndDestroy(3);

	TRAPD(err,ConstructSleepingAlertDialogL(R_LOW_BATTERY));
	iEikonEnv->DeleteResourceFile(offset);
	User::LeaveIfError(err);
	}

void CMyLowBatteryNotifierSubject::HandleSystemEventL(TUid aEvent)
	//Added for flip support GPO 18.05.2001
	{
	if(aEvent == KUidEventScreenModeChanged)
		{
		RDebug::Print(_L("MyLowBatteryNotifier had been notified of a EFlipChanged Event.\n"));
		}
	else
		{
		ASSERT(EFalse);
		}
	}

TInt CMyLowBatteryNotifierSubject::NotifierCapabilites()
	//Added for flip support GPO 18.05.2001
	{
	TInt capabilities=0;
	capabilities |=EScreenDeviceChangeSupported;
	return capabilities;
	}

void CMyLowBatteryNotifierSubject::PreLayoutDynInitL()
	{ // must not fail
	}

TBool CMyLowBatteryNotifierSubject::OkToExitL(TInt /*aButtonId*/)
	{
	iManager->CancelNotifier(iInfo.iUid);
	return ETrue;
	}

void CMyAgendaNotifierSubject::Release()
	{
	delete this;
	}

CMyAgendaNotifierSubject::TNotifierInfo CMyAgendaNotifierSubject::RegisterL()
	{
	iInfo.iUid=KMyNewAgendaAlarmUid;
	iInfo.iChannel=KScreenOutputChannel;
	iInfo.iPriority=ENotifierPriorityHigh;
	return iInfo;
	}
CMyAgendaNotifierSubject::TNotifierInfo CMyAgendaNotifierSubject::Info() const
	{
	return iInfo;
	}

TPtrC8 CMyAgendaNotifierSubject::StartL(const TDesC8& /*aBuffer*/)
	{
	RDebug::Print(_L("Plugin: Agenda notifier started\n"));
	if (!IsVisible())
		{
		RouseSleepingDialog();
		}
	return KNullDesC8();
	}

void CMyAgendaNotifierSubject::StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: Agenda notifier started (asynch.)\n"));
	TRAPD(err,aMessage.WriteL(aReplySlot,KStartAgendaDialogResponse));
	__ASSERT_ALWAYS(!err,User::Panic(_L("WriteL(aReplySlot,KStartAgendaDialogResponse)"),err));
	StartL(aBuffer);
	aMessage.Complete(EEikNotExtRequestCompleted);
	}

void CMyAgendaNotifierSubject::Cancel()
	{
	RDebug::Print(_L("Plugin: Agenda notifier canceled"));
	ExitSleepingDialog();
	}

TPtrC8 CMyAgendaNotifierSubject::UpdateL(const TDesC8& aBuffer)
	{
	RDebug::Print(_L("Plugin: Agenda notifier updated\n"));
	TBuf<100> buffer;
	buffer.Copy(aBuffer);
	CEikonEnv::Static()->InfoMsgWithAlignment(EHLeftVBottom,buffer);
	return KUpdateAgendaResponse();
	}

void CMyAgendaNotifierSubject::UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: Agenda notifier updated (asynch. call) \n"));
	UpdateL(aBuffer);
	TRAPD(err,aMessage.WriteL(aReplySlot,KUpdateAgendaDialogResponseAsync));
	__ASSERT_ALWAYS(!err,User::Panic(_L("WriteL(aReplySlot,KUpdateAgendaDialogResponseAsync)"),err));
	aMessage.Complete(EEikNotExtRequestCompleted);
	}

CMyAgendaNotifierSubject* CMyAgendaNotifierSubject::NewLC()
	{
	CMyAgendaNotifierSubject* self=new (ELeave) CMyAgendaNotifierSubject();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMyAgendaNotifierSubject::CMyAgendaNotifierSubject()
	{
	}

void CMyAgendaNotifierSubject::ConstructL()
	{
	//Get the system filesession	
	RFs& fs = CEikonEnv::Static()->FsSession(); 
	//Get the file finder 
	TFindFile* findFile=new(ELeave) TFindFile(fs);
    CleanupStack::PushL(findFile);
	//File name parser
	TParse* fileNameParser=new(ELeave) TParse;
    CleanupStack::PushL(fileNameParser);

	//search for all rsc files in *\system\libs\plugins\*.rsc
	CDir* directory=NULL;
	User::LeaveIfError(findFile->FindWildByDir(KResFileName1, KResFileNamePath, directory));
	CleanupStack::PushL(directory);

	const TEntry& entry=(*directory)[directory->Count()-1];
	fileNameParser->Set(entry.iName,&findFile->File(),NULL);
	TFileName resourceFileName(fileNameParser->FullName());

	BaflUtils::NearestLanguageFile(iCoeEnv->FsSession(),resourceFileName);
	RDebug::Print(_L("Resource file name [%S]"),&resourceFileName);
	TInt offset=iEikonEnv->AddResourceFileL(resourceFileName);
	CleanupStack::PopAndDestroy(3);

	TRAPD(err,ConstructSleepingAlertDialogL(R_AGENDA_ALARM));
	iEikonEnv->DeleteResourceFile(offset);
	User::LeaveIfError(err);
	}

CMyAgendaNotifierSubject::~CMyAgendaNotifierSubject()
	{
	}

void CMyAgendaNotifierSubject::PreLayoutDynInitL()
	{ // must not fail
	}

TBool CMyAgendaNotifierSubject::OkToExitL(TInt /*aButtonId*/)
	{
	iManager->CancelNotifier(iInfo.iUid);
	return ETrue;
	}

void CMyLEDAgendaNotifierSubject::Release()
	{
	delete this;
	}

CMyLEDAgendaNotifierSubject::TNotifierInfo CMyLEDAgendaNotifierSubject::RegisterL()
	{
	iInfo.iUid=KMyNewAgendaAlarmUid;
	iInfo.iChannel=KLEDOutputChannel;
	iInfo.iPriority=ENotifierPriorityHigh;
	return iInfo;
	}

CMyLEDAgendaNotifierSubject::TNotifierInfo CMyLEDAgendaNotifierSubject::Info() const
	{
	return iInfo;
	}

TPtrC8 CMyLEDAgendaNotifierSubject::StartL(const TDesC8& aBuffer)
	{
	RDebug::Print(_L("Plugin: LED Agenda notifier started\n"));
	TBuf<100> buffer;
	buffer.Copy(aBuffer);
	iBusyMsgWin->StartDisplay(buffer,EHLeftVCenter);
	return KNullDesC8();
	}

void CMyLEDAgendaNotifierSubject::StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: LED Agenda notifier started (asynch. call) \n"));
	StartL(aBuffer);
	TRAPD(err,aMessage.WriteL(aReplySlot,KStartAgendaLEDResponse));
	__ASSERT_ALWAYS(!err,User::Panic(_L("WriteL(aReplySlot,KStartAgendaLEDResponse)"),err));
//	aMessage.Complete(EEikNotExtRequestCompleted);
	}

void CMyLEDAgendaNotifierSubject::Cancel()
	{
	RDebug::Print(_L("Plugin: LED Agenda notifier canceled\n"));
	iBusyMsgWin->CancelDisplay();
	}

TPtrC8 CMyLEDAgendaNotifierSubject::UpdateL(const TDesC8& aBuffer)
	{
	RDebug::Print(_L("Plugin: LED Agenda notifier updated\n"));
	TBuf<100> buffer;
	buffer.Copy(aBuffer);
	CEikonEnv::Static()->InfoMsgWithAlignment(EHLeftVBottom,buffer);
	return KUpdateAgendaLEDResponse();
	}

void CMyLEDAgendaNotifierSubject::UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: LED Agenda notifier updated (asynch. call) \n"));
	UpdateL(aBuffer);
	TRAPD(err,aMessage.WriteL(aReplySlot,KUpdateAgendaLEDResponseAsync));
	__ASSERT_ALWAYS(!err,User::Panic(_L("WriteL(aReplySlot,KUpdateAgendaLEDResponseAsync)"),err));
	}

CMyLEDAgendaNotifierSubject* CMyLEDAgendaNotifierSubject::NewLC()
	{
	CMyLEDAgendaNotifierSubject* self=new (ELeave) CMyLEDAgendaNotifierSubject();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMyLEDAgendaNotifierSubject::CMyLEDAgendaNotifierSubject()
	{
	}

void CMyLEDAgendaNotifierSubject::ConstructL()
	{
	iBusyMsgWin=new(ELeave) CEikBusyMsgWin(*iEikonEnv);
	iBusyMsgWin->ConstructL(iEikonEnv->RootWin());
	}

CMyLEDAgendaNotifierSubject::~CMyLEDAgendaNotifierSubject()
	{
	delete iBusyMsgWin;
	}

void CMyLEDLowBatteryNotifierSubject::Release()
	{
	delete this;
	}

CMyLEDLowBatteryNotifierSubject::TNotifierInfo CMyLEDLowBatteryNotifierSubject::RegisterL()
	{
	iInfo.iUid=KMyNewLowBatteryNotifierUid;
	iInfo.iChannel=KLEDOutputChannel;
	iInfo.iPriority=ENotifierPriorityAbsolute;
	return iInfo;
	}

CMyLEDLowBatteryNotifierSubject::TNotifierInfo CMyLEDLowBatteryNotifierSubject::Info() const
	{
	return iInfo;
	}

TPtrC8 CMyLEDLowBatteryNotifierSubject::StartL(const TDesC8& aBuffer)
	{
	RDebug::Print(_L("Plugin: LED Battery notifier started\n"));
	TBuf<100> buffer;
	buffer.Copy(aBuffer);
	iBusyMsgWin->StartDisplay(buffer,EHLeftVCenter);
	return KNullDesC8();
	}

void CMyLEDLowBatteryNotifierSubject::StartL(const TDesC8& aBuffer, TInt /*aReplySlot*/,const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: LEDLowBat notifier started\n"));
	StartL(aBuffer);
	aMessage.Complete(EEikNotExtRequestCompleted); //don't have to complete straight away
	}

void CMyLEDLowBatteryNotifierSubject::Cancel()
	{
	RDebug::Print(_L("Plugin: LEDLow battery notifier canceled\n"));
	iBusyMsgWin->CancelDisplay();
	}

TPtrC8 CMyLEDLowBatteryNotifierSubject::UpdateL(const TDesC8& aBuffer)
	{
	RDebug::Print(_L("Plugin: LEDLow battery notifier updated"));
	TBuf<100> buffer;
	buffer.Copy(aBuffer);
	CEikonEnv::Static()->InfoMsgWithAlignment(EHLeftVBottom,buffer);
	return KUpdateBatteryLEDResponse();
	}

void CMyLEDLowBatteryNotifierSubject::UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: LED Low Battery notifier updated (asynch. call) \n"));
	UpdateL(aBuffer);
	TRAPD(err,aMessage.WriteL(aReplySlot,KUpdateBatteryLEDResponseAsync));
	__ASSERT_ALWAYS(!err,User::Panic(_L("WriteL(aReplySlot,KUpdateBatteryLEDResponseAsync)"),err));
	aMessage.Complete(EEikNotExtRequestCompleted);
	}

CMyLEDLowBatteryNotifierSubject* CMyLEDLowBatteryNotifierSubject::NewLC()
	{
	CMyLEDLowBatteryNotifierSubject* self=new (ELeave) CMyLEDLowBatteryNotifierSubject();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMyLEDLowBatteryNotifierSubject::CMyLEDLowBatteryNotifierSubject()
	{
	}

CMyLEDLowBatteryNotifierSubject::~CMyLEDLowBatteryNotifierSubject()
	{
	delete iBusyMsgWin;
	}

void CMyLEDLowBatteryNotifierSubject::ConstructL()
	{
	iBusyMsgWin=new(ELeave) CEikBusyMsgWin(*iEikonEnv);
	iBusyMsgWin->ConstructL(iEikonEnv->RootWin());
	}

void CMyLEDLowBatteryNotifierSubject::HandleSystemEventL(TUid aEvent)
	//Added for flip support GPO 18.05.2001
	{
	if(aEvent == KUidEventScreenModeChanged)
		{
		RDebug::Print(_L("MyLEDLowBatteryNotifier had been notified of a EFlipChanged Event.\n"));
		}
	else
		{
		ASSERT(EFalse);
		}
	}

TInt CMyLEDLowBatteryNotifierSubject::NotifierCapabilites()
	//Added for flip support GPO 18.05.2001
	{
	TInt capabilities=0;
	capabilities |=EScreenDeviceChangeSupported;
	return capabilities;
	}

void CMyLEDPhoneNotifierSubject::Release()
	{
	delete this;
	}

CMyLEDPhoneNotifierSubject::TNotifierInfo CMyLEDPhoneNotifierSubject::RegisterL()
	{
	iInfo.iUid=KMyNewPhoneNotifierUid;
	iInfo.iChannel=KLEDOutputChannel;
	iInfo.iPriority=ENotifierPriorityVHigh;
	return iInfo;
	}

CMyLEDPhoneNotifierSubject::TNotifierInfo CMyLEDPhoneNotifierSubject::Info() const
	{
	return iInfo;
	}

TPtrC8 CMyLEDPhoneNotifierSubject::StartL(const TDesC8& aBuffer)
	{
	RDebug::Print(_L("Plugin: LED Phone notifier started\n"));
	TBuf<100> buffer;
	buffer.Copy(aBuffer);
	iBusyMsgWin->StartDisplay(buffer,EHLeftVCenter);
	return KNullDesC8();
	}

void CMyLEDPhoneNotifierSubject::StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: Phone notifier started \n"));
	TPtrC8 boolDes(_L8("LED Channel: PhoneAsynch"));
	TRAPD(err,aMessage.WriteL(aReplySlot,boolDes));
	__ASSERT_ALWAYS(!err,User::Panic(_L("WriteL(aReplySlot,boolDes)"),err));
	StartL(aBuffer);
	aMessage.Complete(EEikNotExtRequestCompleted); //don't have to complete straight away
	}

void CMyLEDPhoneNotifierSubject::Cancel()
	{
	RDebug::Print(_L("Plugin: LED Phone notifier canceled\n"));
	iBusyMsgWin->CancelDisplay();
	}

TPtrC8 CMyLEDPhoneNotifierSubject::UpdateL(const TDesC8& aBuffer)
	{
	RDebug::Print(_L("Plugin: LED Phone notifier updated\n"));
	TBuf<100> buffer;
	buffer.Copy(aBuffer);
	CEikonEnv::Static()->InfoMsgWithAlignment(EHLeftVBottom,buffer);
	return KUpdatePhoneLEDResponse();
	}

void CMyLEDPhoneNotifierSubject::UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: LED Phone notifier updated (asynch. call) \n"));
	UpdateL(aBuffer);
	TRAPD(err,aMessage.WriteL(aReplySlot,KUpdatePhoneLEDResponseAsync));
	__ASSERT_ALWAYS(!err,User::Panic(_L("WriteL(aReplySlot,KUpdatePhoneLEDResponseAsync)"),err));
	aMessage.Complete(EEikNotExtRequestCompleted);
	}

CMyLEDPhoneNotifierSubject* CMyLEDPhoneNotifierSubject::NewLC()
	{
	CMyLEDPhoneNotifierSubject* self=new (ELeave) CMyLEDPhoneNotifierSubject();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMyLEDPhoneNotifierSubject::CMyLEDPhoneNotifierSubject()
	{
	}

void CMyLEDPhoneNotifierSubject::ConstructL()
	{
	iBusyMsgWin=new(ELeave) CEikBusyMsgWin(*iEikonEnv);
	iBusyMsgWin->ConstructL(iEikonEnv->RootWin());
	}

CMyLEDPhoneNotifierSubject::~CMyLEDPhoneNotifierSubject()
	{
	delete iBusyMsgWin;
	}


//Adding ECOM SUPPORT
#include <ecom/implementationproxy.h>
const TImplementationProxy ImplementationTable[] =
	{
	IMPLEMENTATION_PROXY_ENTRY(0x10022239,NotifierArray)
	};

EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
	{
	aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy) ;
	return ImplementationTable;
	}
