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
// GFXTRANSEFFECT.CPP
// 
//

#include "GfxTransUtils.h"

void Panic(const TInt aCode)
	{
	_LIT(KPanicText,"GFXTRANS");
	__BREAKPOINT();
	User::Panic(KPanicText,aCode);
	}

