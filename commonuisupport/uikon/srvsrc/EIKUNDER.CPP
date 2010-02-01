// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <eikunder.h>
#include <eiksrv.h>

EXPORT_C CEikUndertaker* CEikUndertaker::NewL(MEikUndertakerObserver& aObserver)
	{ // static
	CEikUndertaker* self = new(ELeave) CEikUndertaker(aObserver);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(); // self
	return self;
	}

EXPORT_C CEikUndertaker::~CEikUndertaker()
	{
	Cancel();
	if (iThreadHandle)
		{
		RThread r;
		r.SetHandle(iThreadHandle);
		r.Close();
		}
	}

CEikUndertaker::CEikUndertaker(MEikUndertakerObserver& aObserver)
	: CActive(CActive::EPriorityStandard), iObserver(aObserver)
	{}

void CEikUndertaker::ConstructL()
	{
	User::LeaveIfError(iUndertaker.Create());
	CActiveScheduler::Add(this);
	Request();
	}

void CEikUndertaker::Request()
	{
	iThreadHandle = KNullHandle;
	iUndertaker.Logon(iStatus,iThreadHandle);
	SetActive();
	}

void CEikUndertaker::DoCancel()
	{
	iUndertaker.LogonCancel();
	}

void CEikUndertaker::RunL()
	{
	RThread r;
	r.SetHandle(iThreadHandle);
	TRAPD(err, iObserver.HandleThreadExitL(r));
	r.Close();
	Request();
	User::LeaveIfError(err);
	}
