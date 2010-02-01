// Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "SpriteAnimationDll.h"
#include "SpriteAnimationServer.h"

// the only exported function in the DLL
EXPORT_C CAnimDll* CreateCAnimDllL()
	{
	return new(ELeave) CSpriteAnimationDll;
	}

// global functions
const TInt KPanicClientFromServer=1;

GLDEF_C void Panic(TInt aReason)
	{
	_LIT(KPanicAnimationServer,"SpriteAnimation-server");
	User::Panic(KPanicAnimationServer, aReason);
	}

GLDEF_C void PanicClientFromServer()
	{
	User::Leave(KPanicClientFromServer);
	}

// CSpriteAnimationDll
CAnim* CSpriteAnimationDll::CreateInstanceL(TInt /*aType*/)
	{
	return CSpriteAnimationServer::NewL();
	}

