/*
* Copyright (c) 2001 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:
*
*/


#ifndef __EIKLAY_H__
#define __EIKLAY_H__

#include <frmtlay.h>

class TAvkonEditorCustomWrap : public MFormCustomWrap
	{
public:
	enum
		{
		EAvkSpaceLineBreakClass=MTmCustom::ELineBreakClasses, // 29
		EAvkLineBreakClasses
		};

public:
	// overrides of line break functions from MFormCustomWrap
	TUint LineBreakClass(TUint aCode,TUint& aRangeStart,TUint& aRangeEnd) const;
	TBool LineBreakPossible(TUint aPrevClass,TUint aNextClass,TBool aHaveSpaces) const;
	};

#endif // __EIKLAY_H__
