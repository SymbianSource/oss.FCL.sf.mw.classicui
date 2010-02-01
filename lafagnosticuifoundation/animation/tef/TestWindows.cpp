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

#include "TestWindows.h"
#include <w32std.h>

CTestWindow::CTestWindow(RWsSession & aWs, CTestWindowGroup & aGroup, CWindowGc& aGc) :
iGc(aGc)
	{
	iWin = new (ELeave) RWindow(aWs);
	Window()->Construct(*aGroup.WindowGroup(), TUint32(this));
	}
	
CTestWindow::~CTestWindow()
	{
	iWin->Close();
	delete iWin;
	}

void CTestWindow::EventL(TWsEvent & /*aEvent*/)
	{
	}

void CTestWindow::RedrawL(TWsRedrawEvent & /*aEvent*/)
	{
	Window()->BeginRedraw();
	iGc.Activate(*Window());
	DrawL();
	iGc.Deactivate();
	Window()->EndRedraw();
	}

void CTestWindow::DrawL()
	{
	}

CTestWindowGroup::CTestWindowGroup(RWsSession & aWs)
	{
	iWin = new (ELeave) RWindowGroup(aWs);
	WindowGroup()->Construct(TUint32(this));
	}

CTestWindowGroup::~CTestWindowGroup()
	{
	iWin->Close();
	delete iWin;
	}

void CTestWindowGroup::EventL(TWsEvent & /*aEvent*/)
	{
	}

void CTestWindowGroup::RedrawL(TWsRedrawEvent & /*aEvent*/)
	{
	}

