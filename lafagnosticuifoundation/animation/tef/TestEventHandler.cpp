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


#include "TestEventHandler.h"
#include "TestWindows.h"

#include <w32std.h>

CTestEventHandler::CTestEventHandler(RWsSession& aWs) : CActive(100),
iWs(aWs)
	{
	}
	
CTestEventHandler::~CTestEventHandler()
	{
	Cancel();
	}

void CTestEventHandler::Start()
	{
	CActiveScheduler::Add(this);
	iWs.EventReady(&iStatus);
	SetActive();
	}

void CTestEventHandler::RunL()
	{
	TWsEvent event;
	iWs.GetEvent(event);
	
	if (event.Handle())
		{
		reinterpret_cast<CTestWindowTreeNode *>(event.Handle())->EventL(event);
		}

	iWs.EventReady(&iStatus);
	SetActive();
	}

void CTestEventHandler::DoCancel()
	{
	iWs.EventReadyCancel();
	}

TInt CTestEventHandler::RunError(TInt aError)
	{
	return(aError);
	}

