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


#include "ActiveWait.h"

CActiveWait* CActiveWait::NewL()
	{
	CActiveWait* self = new (ELeave) CActiveWait;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}
	
void CActiveWait::ConstructL()
	{
	User::LeaveIfError(iTimer.CreateLocal());
	CActiveScheduler::Add(this);
	}
	
CActiveWait::CActiveWait() : CActive(EPriorityNormal)
	{
	iFromTime.HomeTime();
	}

CActiveWait::~CActiveWait()
	{
	Cancel();
	iTimer.Close();
	}

void CActiveWait::DoCancel()
	{
	iTimer.Cancel();
	CActiveScheduler::Stop();
	}

void CActiveWait::RunL()
	{
	CActiveScheduler::Stop();
	}
	
TInt CActiveWait::RunError(TInt aError)
	{
	return aError; // exists so a break point can be placed on it.
	}

void CActiveWait::Wait(TInt aDelay)

//    Note when using this : because other active objects can perform part of their
//    processing whilst we wait, wrapping calls to this in __UHEAP_MARK / __UHEAP_MARKEND
//    is likely to fail.  The data providers and animators are a major cause of this. 

	{
	iTimer.After(iStatus, aDelay);
	SetActive();
	CActiveScheduler::Start();
	}
