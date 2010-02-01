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
#include <bautils.h>
#include "tnotify2v2.h"
#include "tnotdial.h"

#include <uikon.hrh>
#include <tnotdial.rsg>


const TUid KScreenOutputChannel ={0x00000666};
const TUid KLEDOutputChannel ={0x00000111};

_LIT(KResFileNamePath,"\\system\\test\\tnotdial\\");
_LIT(KResFileName1,"tnotdial.rsc");

_LIT8(KStartSmsDialogResponse,"Response: started SMS dialog");
_LIT8(KStartSmsLEDResponse,"Response: started SMS LED");
_LIT8(KStartEmailDialogResponse,"Response: started email dialog");
_LIT8(KStartEmailLEDResponse,"Response: started email LED");
_LIT8(KUpdateSmsDialogResponse, "Response: updated SMS dialog");
_LIT8(KUpdateSmsLEDResponse, "Response: updated SMS LED");
_LIT8(KUpdateEmailDialogResponse, "Response: updated email dialog");
_LIT8(KUpdateEmailLEDResponse, "Response: updated email LED");
_LIT8(KUpdateSmsDialogResponseAsync, "Response: updated SMS dialog");
_LIT8(KUpdateSmsLEDResponseAsync, "Response: updated SMS LED");
_LIT8(KUpdateEmailDialogResponseAsync, "Response: updated email dialog");
_LIT8(KUpdateEmailLEDResponseAsync, "Response: updated email LED");

EXPORT_C   CArrayPtr<MEikSrvNotifierBase2>* NotifierArray()
//
// Lib main entry point
//
	{
//	RDebug::Print(_L("\nExported entry point\n"));
	CArrayPtrFlat<MEikSrvNotifierBase2>* subjects=new (ELeave)CArrayPtrFlat<MEikSrvNotifierBase2>(4);
	CleanupStack::PushL(subjects);
	subjects->AppendL(CMySmsNotifierSubject::NewLC()); 
	subjects->AppendL(CMyLEDSmsNotifierSubject::NewLC());
	subjects->AppendL(CMyEmailNotifierSubject::NewLC()); 
	subjects->AppendL(CMyLEDEmailNotifierSubject::NewLC());
	CleanupStack::Pop(5, subjects);
	return subjects;
	}

EXPORT_C   CArrayPtr<MEikSrvNotifierBase2>* NotifierArray1()
//
// Lib main entry point
//
	{
//	RDebug::Print(_L("\nExported entry point\n"));
	CArrayPtrFlat<MEikSrvNotifierBase2>* subjects=new (ELeave)CArrayPtrFlat<MEikSrvNotifierBase2>(2);
	CleanupStack::PushL(subjects);
	subjects->AppendL(CMySmsNotifierSubject::NewLC()); 
	subjects->AppendL(CMyLEDSmsNotifierSubject::NewLC());
	CleanupStack::Pop(3, subjects);
	return subjects;
	}
EXPORT_C   CArrayPtr<MEikSrvNotifierBase2>* NotifierArray2()
//
// Lib main entry point
//
	{
//	RDebug::Print(_L("\nExported entry point\n"));
	CArrayPtrFlat<MEikSrvNotifierBase2>* subjects=new (ELeave)CArrayPtrFlat<MEikSrvNotifierBase2>(2);
	CleanupStack::PushL(subjects);
	subjects->AppendL(CMyEmailNotifierSubject::NewLC()); 
	subjects->AppendL(CMyLEDEmailNotifierSubject::NewLC());
	CleanupStack::Pop(3, subjects);
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


void CMySmsNotifierSubject::Release()
	{
	delete this;
	}

CMySmsNotifierSubject::TNotifierInfo CMySmsNotifierSubject::RegisterL()
	{
	iInfo.iUid=KMyNewSmsNotifierUid;
	iInfo.iChannel=KScreenOutputChannel;
	iInfo.iPriority=ENotifierPriorityHigh;
	return iInfo;
	}

CMySmsNotifierSubject::TNotifierInfo CMySmsNotifierSubject::Info() const
	{
	return iInfo;
	}

TPtrC8 CMySmsNotifierSubject::StartL(const TDesC8& /*aBuffer*/)
	{
	RDebug::Print(_L("Plugin: SMS notifier started\n"));
	if (!IsVisible())
		{
		RouseSleepingDialog();
		}
	return KNullDesC8();
	}

void CMySmsNotifierSubject::StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: SMS notifier started (asynch.)\n"));
	TRAPD(err,aMessage.WriteL(aReplySlot,KStartSmsDialogResponse));
	__ASSERT_ALWAYS(!err,User::Panic(_L("WriteL(aReplySlot,KStartSmsDialogResponse)"),err));
	StartL(aBuffer);
	//aMessage.Complete(EEikNotExtRequestCompleted);
	}

void CMySmsNotifierSubject::Cancel()
	{
	RDebug::Print(_L("Plugin: SMS notifier canceled\n"));
	ExitSleepingDialog();
	}

TPtrC8 CMySmsNotifierSubject::UpdateL(const TDesC8& aBuffer)
	{
	RDebug::Print(_L("Plugin: SMS notifier updated\n"));
	TBuf<100> buffer;
	buffer.Copy(aBuffer);
	CEikonEnv::Static()->InfoMsgWithAlignment(EHLeftVBottom,buffer);
	return KUpdateSmsDialogResponse();
	}

void CMySmsNotifierSubject::UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: SMS notifier updated (asynch. call) \n"));
	UpdateL(aBuffer);
	TRAPD(err,aMessage.WriteL(aReplySlot,KUpdateSmsDialogResponseAsync));
	__ASSERT_ALWAYS(!err,User::Panic(_L("WriteL(aReplySlot,KUpdateSmsDialogResponseAsync)"),err));
	aMessage.Complete(EEikNotExtRequestCompleted);
	}

CMySmsNotifierSubject* CMySmsNotifierSubject::NewLC()
	{
	CMySmsNotifierSubject* self=new (ELeave) CMySmsNotifierSubject();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMySmsNotifierSubject::CMySmsNotifierSubject()
	{
	}

CMySmsNotifierSubject::~CMySmsNotifierSubject()
	{
	}

void CMySmsNotifierSubject::ConstructL()
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

	TRAPD(err,ConstructSleepingAlertDialogL(R_SMS_ALERT));
	iEikonEnv->DeleteResourceFile(offset);
	User::LeaveIfError(err);
	}

void CMySmsNotifierSubject::PreLayoutDynInitL()
	{ // must not fail
	}

TBool CMySmsNotifierSubject::OkToExitL(TInt /*aButtonId*/)
	{
	iManager->CancelNotifier(iInfo.iUid);
	return ETrue;
	}

void CMyEmailNotifierSubject::Release()
	{
	delete this;
	}

CMyEmailNotifierSubject::TNotifierInfo CMyEmailNotifierSubject::RegisterL()
	{
	iInfo.iUid=KMyNewEmailNotifierUid;
	iInfo.iChannel=KScreenOutputChannel;
	iInfo.iPriority=ENotifierPriorityVLow;
	return iInfo;
	}

CMyEmailNotifierSubject::TNotifierInfo CMyEmailNotifierSubject::Info() const
	{
	return iInfo;
	}

TPtrC8 CMyEmailNotifierSubject::StartL(const TDesC8& /*aBuffer*/)
	{
	RDebug::Print(_L("Plugin: email notifier started\n"));
	if (!IsVisible())
		{
		RouseSleepingDialog();
		}
	return KNullDesC8();
	}

void CMyEmailNotifierSubject::StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
	{
//	__DEBUGGER();
	RDebug::Print(_L("Plugin: email notifier started (asynch.)\n"));
	TRAPD(err,aMessage.WriteL(aReplySlot,KStartEmailDialogResponse));
	__ASSERT_ALWAYS(!err,User::Panic(_L("WriteL(aReplySlot,KStartEmailDialogResponse)"),err));
	StartL(aBuffer);
	}

void CMyEmailNotifierSubject::Cancel()
	{
	RDebug::Print(_L("Plugin: email notifier canceled\n"));
	ExitSleepingDialog();
	}

TPtrC8 CMyEmailNotifierSubject::UpdateL(const TDesC8& aBuffer)
	{
	RDebug::Print(_L("Plugin: email notifier updated\n"));
	TBuf<100> buffer;
	buffer.Copy(aBuffer);
	CEikonEnv::Static()->InfoMsgWithAlignment(EHLeftVBottom,buffer);
	return KUpdateEmailDialogResponse();
	}

void CMyEmailNotifierSubject::UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: Email notifier updated (asynch. call) \n"));
	UpdateL(aBuffer);
	TRAPD(err,aMessage.WriteL(aReplySlot,KUpdateEmailDialogResponseAsync));
	__ASSERT_ALWAYS(!err,User::Panic(_L("WriteL(aReplySlot,KUpdateEmailDialogResponseAsync)"),err));
	aMessage.Complete(EEikNotExtRequestCompleted);
	}

CMyEmailNotifierSubject* CMyEmailNotifierSubject::NewLC()
	{
	CMyEmailNotifierSubject* self=new (ELeave) CMyEmailNotifierSubject();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMyEmailNotifierSubject::CMyEmailNotifierSubject()
	{
	}

void CMyEmailNotifierSubject::ConstructL()
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

	TRAPD(err,ConstructSleepingAlertDialogL(R_EMAIL_ALERT));
	iEikonEnv->DeleteResourceFile(offset);
	User::LeaveIfError(err);
	}

CMyEmailNotifierSubject::~CMyEmailNotifierSubject()
	{
	}

void CMyEmailNotifierSubject::PreLayoutDynInitL()
	{ // must not fail
	}

TBool CMyEmailNotifierSubject::OkToExitL(TInt /*aButtonId*/)
	{
	iManager->CancelNotifier(iInfo.iUid);
	return ETrue;
	}

void CMyLEDEmailNotifierSubject::Release()
	{
	delete this;
	}

CMyLEDEmailNotifierSubject::TNotifierInfo CMyLEDEmailNotifierSubject::RegisterL()
	{
	iInfo.iUid=KMyNewEmailNotifierUid;
	iInfo.iChannel=KLEDOutputChannel;
	iInfo.iPriority=ENotifierPriorityVLow;
	return iInfo;
	}

CMyLEDEmailNotifierSubject::TNotifierInfo CMyLEDEmailNotifierSubject::Info() const
	{
	return iInfo;
	}

TPtrC8 CMyLEDEmailNotifierSubject::StartL(const TDesC8& aBuffer)
	{
	RDebug::Print(_L("Plugin: LED email notifier started\n"));
	TBuf<100> buffer;
	buffer.Copy(aBuffer);
	iBusyMsgWin->StartDisplay(buffer,EHLeftVCenter);
	return KNullDesC8();
	}

void CMyLEDEmailNotifierSubject::StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: LED email notifier started (asynch.)\n"));
	TRAPD(err,aMessage.WriteL(aReplySlot,KStartEmailLEDResponse));
	__ASSERT_ALWAYS(!err,User::Panic(_L("WriteL(aReplySlot,KStartEmailLEDResponse)"),err));
	StartL(aBuffer);
	
//	aMessage.Complete(EEikNotExtRequestCompleted);
	}

void CMyLEDEmailNotifierSubject::Cancel()
	{
	RDebug::Print(_L("Plugin: LED email notifier canceled\n"));
	iBusyMsgWin->CancelDisplay();
	}

TPtrC8 CMyLEDEmailNotifierSubject::UpdateL(const TDesC8& aBuffer)
	{
	RDebug::Print(_L("Plugin: LED email notifier updated\n"));
	TBuf<100> buffer;
	buffer.Copy(aBuffer);
	CEikonEnv::Static()->InfoMsgWithAlignment(EHLeftVBottom,buffer);
	return KUpdateEmailLEDResponse();
	}

void CMyLEDEmailNotifierSubject::UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: LED Email notifier updated (asynch. call) \n"));
	UpdateL(aBuffer);
	TRAPD(err,aMessage.WriteL(aReplySlot,KUpdateEmailLEDResponseAsync));
	__ASSERT_ALWAYS(err,User::Panic(_L("WriteL(aReplySlot,KUpdateEmailLEDResponseAsync)"),err));
	}

CMyLEDEmailNotifierSubject* CMyLEDEmailNotifierSubject::NewLC()
	{
	CMyLEDEmailNotifierSubject* self=new (ELeave) CMyLEDEmailNotifierSubject();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMyLEDEmailNotifierSubject::CMyLEDEmailNotifierSubject()
	{
	}

void CMyLEDEmailNotifierSubject::ConstructL()
	{
	iBusyMsgWin=new(ELeave) CEikBusyMsgWin(*iEikonEnv);
	iBusyMsgWin->ConstructL(iEikonEnv->RootWin());
	}

CMyLEDEmailNotifierSubject::~CMyLEDEmailNotifierSubject()
	{
	delete iBusyMsgWin;
	}

void CMyLEDSmsNotifierSubject::Release()
	{
	delete this;
	}

CMyLEDSmsNotifierSubject::TNotifierInfo CMyLEDSmsNotifierSubject::RegisterL()
	{
	iInfo.iUid=KMyNewSmsNotifierUid;
	iInfo.iChannel=KLEDOutputChannel;
	iInfo.iPriority=ENotifierPriorityHigh;
	return iInfo;
	}

CMyLEDSmsNotifierSubject::TNotifierInfo CMyLEDSmsNotifierSubject::Info() const
	{
	return iInfo;
	}

TPtrC8 CMyLEDSmsNotifierSubject::StartL(const TDesC8& aBuffer)
	{
	RDebug::Print(_L("Plugin: LED SMS notifier started\n"));
	TBuf<100> buffer;
	buffer.Copy(aBuffer);
	iBusyMsgWin->StartDisplay(buffer,EHLeftVCenter);
	return KNullDesC8();
	}

void CMyLEDSmsNotifierSubject::StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: LED SMS notifier started (asynch.)\n"));
	TRAPD(err,aMessage.WriteL(aReplySlot,KStartSmsLEDResponse));
	__ASSERT_ALWAYS(!err,User::Panic(_L("WriteL(aReplySlot,KUpdateEmailDialogResponseAsync)"),err));
	StartL(aBuffer);
//	aMessage.Complete(EEikNotExtRequestCompleted);
	}

void CMyLEDSmsNotifierSubject::Cancel()
	{
	RDebug::Print(_L("Plugin: LED SMS notifier canceled\n"));
	iBusyMsgWin->CancelDisplay();
	}

TPtrC8 CMyLEDSmsNotifierSubject::UpdateL(const TDesC8& aBuffer)
	{
	RDebug::Print(_L("Plugin: LED SMS notifier updated\n"));
	TBuf<100> buffer;
	buffer.Copy(aBuffer);
	CEikonEnv::Static()->InfoMsgWithAlignment(EHLeftVBottom,buffer);
	return KUpdateSmsLEDResponse();
	}

void CMyLEDSmsNotifierSubject::UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
	{
	RDebug::Print(_L("Plugin: LED SMS notifier updated (asynch. call) \n"));
	UpdateL(aBuffer);
	TRAPD(err,aMessage.WriteL(aReplySlot,KUpdateSmsLEDResponseAsync));
	__ASSERT_ALWAYS(!err,User::Panic(_L("WriteL(aReplySlot,KUpdateSmsLEDResponseAsync"),err));
	}

CMyLEDSmsNotifierSubject* CMyLEDSmsNotifierSubject::NewLC()
	{
	CMyLEDSmsNotifierSubject* self=new (ELeave) CMyLEDSmsNotifierSubject();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMyLEDSmsNotifierSubject::CMyLEDSmsNotifierSubject()
	{
	}

void CMyLEDSmsNotifierSubject::ConstructL()
	{
	iBusyMsgWin=new(ELeave) CEikBusyMsgWin(*iEikonEnv);
	iBusyMsgWin->ConstructL(iEikonEnv->RootWin());
	}

CMyLEDSmsNotifierSubject::~CMyLEDSmsNotifierSubject()
	{
	delete iBusyMsgWin;
	}

//Adding ECOM SUPPORT
#include <ecom/implementationproxy.h>
const TImplementationProxy ImplementationTable[] =
	{
	IMPLEMENTATION_PROXY_ENTRY(0x10022238,NotifierArray1),
	IMPLEMENTATION_PROXY_ENTRY(0x10022237,NotifierArray2)
	};

EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
	{
	aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy) ;
	return ImplementationTable;
	}
