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
// source code for the top level of the server-side DLL
// $Workfile:   DLL.CPP  $
// $Revision:   1.5  $
// $Author:   chrisd  $
// $Date:   14 Dec 1998 11:42:18  $
// 
//

#include "CL_STD.H"

// put the uids in the WINS builds

// the only exported function in the DLL

IMPORT_C CAnimDll* CreateCAnimDllL();
EXPORT_C CAnimDll* CreateCAnimDllL()
	{
	return new(ELeave) DClockDll;
	}

// global functions


GLDEF_C void Panic(TClockServerPanic aReason)
	{
	_LIT(KPanicClockServer,"Clock-server");
	User::Panic(KPanicClockServer, aReason);
	}

GLDEF_C void PanicClientFromServer()
	{
	User::Leave(KPanicClientFromServer);
	}

// DClockDll

DClockDll::DClockDll()
	{
	__DECLARE_NAME(_S("DClockDll"));
	}

CAnim* DClockDll::CreateInstanceL(TInt aType)
	{
	switch(aType)
		{
	case EAnimClock:
		return new(ELeave) DClock;
	case EAnimMessageWindow:
		return new(ELeave) DMessageWindow;
	default:
		User::Leave(KErrArgument);
		return NULL; // dummy return to prevent compiler error
		}
	}

