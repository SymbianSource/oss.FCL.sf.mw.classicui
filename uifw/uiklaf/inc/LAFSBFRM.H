/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __LAFSBFRM_H__
#define __LAFSBFRM_H__

#include <e32std.h>
#include <coecntrl.h>

/**
 * @internal
 * Do not use
 */
class LafScrollBarFrame
	{
public:
	class TScrollBarAttributes
		{
	public:
		IMPORT_C TScrollBarAttributes();
	public:
		TInt iControlType;
		TInt iBreadth;
		TInt iSide;
		TInt iManagement;
		};
public:
	IMPORT_C static TInt DefaultFlags();
	IMPORT_C static TInt DefaultScrollBarFlags(TInt aOrientation);
	IMPORT_C static void GetDefaultScrollBarAttributes(TInt aOrientation, TScrollBarAttributes& aAttributes);
	IMPORT_C static void GetFloatingScrollBarPosition(TInt aOrientation,const TScrollBarAttributes& aAttributes, const TRect& aClientRect, const TSize& aScrollBarSize, TPoint &aPosition);
	IMPORT_C static TInt FloatingScrollBarLength(TInt aOrientation, const TScrollBarAttributes& aAttributes, const TRect& aClientRect, const TSize& aScrollBarSize);
	};

/**
 * @internal
 * Do not use
 */
class LafScrollBarFrameCornerWindow
	{
public:
	IMPORT_C static void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList);
	};

#endif
