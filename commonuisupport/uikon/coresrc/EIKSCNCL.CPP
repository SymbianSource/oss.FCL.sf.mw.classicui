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

#include "EIKSCNCL.H"
#include <coemain.h>
#include <eiksvdef.h>
#include <eikdef.h>
#include <eikenv.h>
#include <eiksrvs.h>

CEikScreenClearerWin::CEikScreenClearerWin()
	{}

CEikScreenClearerWin::~CEikScreenClearerWin()
	{
	iEikonEnv->WsSession().Flush();
	if (iEikSrvStatus == KErrNone)
		{
		iEikSrv.UnblankScreen();
		iEikSrv.Close();
		}
	}

void CEikScreenClearerWin::ConstructL()
// Use eikserv to blank the screen if possible, otherwise create a blank window.
	{
	// try to open eiksrvs thread to see if it exists
	if (RThread().Name().Compare(EIKAPPUI_SERVER_THREAD_NAME)!=0)
		{
		// check if the server is present
		TFindServer find(EIKAPPUI_SERVER_NAME);
 		TFullName name;
 		iEikSrvStatus = (find.Next(name) == KErrNone ? iEikSrv.Connect() : KErrNotFound); 
		}
	else
		iEikSrvStatus = KErrInUse;		// this thread is eiksrv !

	if (iEikSrvStatus == KErrNone)
		iEikSrv.BlankScreen();
	else
		{
		CreateWindowL();
		SetBlank();
		SetExtentToWholeScreen();
		ActivateL();
		SetPointerCapture(ETrue);
		DrawableWindow()->ClaimPointerGrab();
		DrawNow();
		}

	iCoeEnv->WsSession().PurgePointerEvents();
	}

EXPORT_C CEikScreenClearerWin* CEikScreenClearerWin::NewLC()
	{
	CEikScreenClearerWin* self = new(ELeave) CEikScreenClearerWin;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}
