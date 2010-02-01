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


#include "TestRedrawHandler.h"
#include "TestWindows.h"

#include <w32std.h>

CTestRedrawHandler::CTestRedrawHandler(RWsSession& aWs) : CActive(50),
iWs(aWs)
	{
	}
	
CTestRedrawHandler::~CTestRedrawHandler()
	{
	Cancel();
	}

void CTestRedrawHandler::Start()
	{
	CActiveScheduler::Add(this);
	iWs.RedrawReady(&iStatus);
	SetActive();
	}

void CTestRedrawHandler::RunL()
	{
	TWsRedrawEvent redraw;
	iWs.GetRedraw(redraw);
	
	iWs.RedrawReady(&iStatus);
	SetActive();

	if (redraw.Handle())
		{
		if(redraw.Rect().IsEmpty())
			User::Leave(KErrGeneral);
		CTestWindowTreeNode* node = reinterpret_cast<CTestWindowTreeNode *>(redraw.Handle());
		node->RedrawL(redraw);
//		reinterpret_cast<CTestWindowTreeNode *>(redraw.Handle())->RedrawL(redraw);
		}
	}

void CTestRedrawHandler::DoCancel()
	{
	iWs.RedrawReadyCancel();
	}

TInt CTestRedrawHandler::RunError(TInt aError)
	{
	return(aError);
	}

