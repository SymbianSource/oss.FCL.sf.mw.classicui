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


#ifndef __LAFTHUMB_H__
#define __LAFTHUMB_H__

#include <e32std.h>
#include <gulbordr.h>
#include <coecntrl.h>

class MLafEnv;
class CWindowGc;

/**
 * @internal
 * Do not use
 */
class LafScrollThumb
	{
public:
	IMPORT_C static void DrawDragState(const MLafEnv& aLafEnv, CWindowGc& aGc, const CCoeControl& aScrollThumb,TBool aIsDragged, const TRect& aRect, TBool aHorizontal);
	IMPORT_C static void GetDefaultBorder(TGulBorder& aBorder, TInt aOrientation);
	IMPORT_C static void GetBorderColors(TGulBorder::TColors& aBorderColors,const MLafEnv& aEnv,const CCoeControl& aMatchedControl);
	IMPORT_C static void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList);
	};

#endif //__LAFTHUMB_H__
