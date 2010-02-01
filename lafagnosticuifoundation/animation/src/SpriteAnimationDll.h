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

#ifndef __SPRITEANIMATIONDLL_H__
#define __SPRITEANIMATIONDLL_H__

#include <w32adll.h>

NONSHARABLE_CLASS(CSpriteAnimationDll) : public CAnimDll
	{
public:
	virtual CAnim* CreateInstanceL(TInt aType);
	};

//
// global functions
//

GLREF_C void Panic(TInt aReason);

#endif // __SPRITEANIMATIONDLL_H__
