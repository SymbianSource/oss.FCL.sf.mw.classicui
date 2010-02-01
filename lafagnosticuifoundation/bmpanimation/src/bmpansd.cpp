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

#include "bmpansrv.h"

// put the uids in the WINS builds

// the only exported function in the DLL


IMPORT_C CAnimDll* CreateCAnimDllL();
EXPORT_C CAnimDll* CreateCAnimDllL()
	{
	return new(ELeave) CBitmapAnimDll;
	}

// global functions

const TInt KPanicClientFromServer=1;



GLDEF_C void Panic(TBitmapAnimServerPanic aReason)
	{
	_LIT(KPanicAnimationServer,"Animation-server");
	User::Panic(KPanicAnimationServer, aReason);
	}

GLDEF_C void PanicClientFromServer()
	{
	User::Leave(KPanicClientFromServer);
	}


// CBitmapAnimDll

CBitmapAnimDll::CBitmapAnimDll()
	{
	}

CAnim* CBitmapAnimDll::CreateInstanceL(TInt /*aType*/)
	{
	return CBitmapAnim::NewL();
	}

