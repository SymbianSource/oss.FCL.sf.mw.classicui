// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "Notifier1.h"
#include <eikenv.h>
#include <bautils.h>
#include <Notifier1Dialog.rsg>
#include <ImplementationProxy.h>	// For the ECom entry point definitions

const TUid KNotifier1Uid = { 0x102826DC };
const TUid KScreenOutput = { 0x10009D48 };

CNotifier1* CNotifier1::NewLC()
	{
	CNotifier1* self = new(ELeave) CNotifier1();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}
	
CNotifier1::~CNotifier1()
	{
	}
	
CNotifier1::CNotifier1()
	{
	}
	
void CNotifier1::ConstructL()
	{
	_LIT(KResourceFile, "z:\\resource\\apps\\Notifier1Dialog.rsc");
	TFileName resourceFileName(KResourceFile);
	BaflUtils::NearestLanguageFile(iEikonEnv->FsSession(), resourceFileName);
	TInt offset = iEikonEnv->AddResourceFileL(resourceFileName);
	TRAPD(err,ConstructSleepingAlertDialogL(R_NOTIFIER1));
	iEikonEnv->DeleteResourceFile(offset);
	User::LeaveIfError(err);
	}

void CNotifier1::Release()
	{
	delete this;
	}
	
CNotifier1::TNotifierInfo CNotifier1::RegisterL()
	{
	iInfo.iUid=KNotifier1Uid;
	iInfo.iChannel=KScreenOutput;
	iInfo.iPriority=ENotifierPriorityHigh;
	return iInfo;
	}
	
CNotifier1::TNotifierInfo CNotifier1::Info() const
	{
	return iInfo;
	}
	
void CNotifier1::StartL(const TDesC8& /*aBuffer*/, TInt /*aReplySlot*/, const RMessagePtr2& aMessage)
	{
	aMessage.Complete(KErrNotSupported);
	}
	
TPtrC8 CNotifier1::StartL(const TDesC8& /*aBuffer*/)
	{
	if (!IsVisible())
		{
		RouseSleepingDialog();
		}
	return KNullDesC8();
	}
	
void CNotifier1::Cancel()
	{
	ExitSleepingDialog();
	}
	
TPtrC8 CNotifier1::UpdateL(const TDesC8& /*aBuffer*/)
	{
	_LIT(KNewTitle, "Still Notifier1");
	SetTitleL(KNewTitle);
	DrawNow();
	return KNullDesC8();
	}
		
void CNotifier1::UpdateL(const TDesC8& /*aBuffer*/, TInt /*aReplySlot*/, const RMessagePtr2& aMessage)
	{
	aMessage.Complete(KErrNotSupported);
	}

CArrayPtr<MEikSrvNotifierBase2>* NotifierArrayL()
	{
	CArrayPtrFlat<MEikSrvNotifierBase2>* notifiers = new(ELeave) CArrayPtrFlat<MEikSrvNotifierBase2>(1);
	CleanupStack::PushL(notifiers);
	CNotifier1* notifier1 = CNotifier1::NewLC();
	notifiers->AppendL(notifier1);
	CleanupStack::Pop(notifier1);
	CleanupStack::Pop(notifiers);
	return notifiers;
	}


// ECom plugin entry point

const TImplementationProxy ImplementationTable[] =
	{
    IMPLEMENTATION_PROXY_ENTRY(0x102826DB, NotifierArrayL)
	};

EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
	{
	aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy);
	return ImplementationTable;
	}