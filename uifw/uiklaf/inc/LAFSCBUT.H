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



#ifndef __LAFSCBUT_H__
#define __LAFSCBUT_H__

#include <e32std.h>
#include <gulbordr.h>
#include <coecntrl.h>
#include <lafpublc.h>

class MLafEnv;

/**
 * @internal
 * Do not use
 */
class LafScrollButton
	{
public:
	IMPORT_C static void GetBorder(TGulBorder& aBorder, TBool aIsPressed);
	IMPORT_C static void GetBorderColors(TGulBorder::TColors& aBorderColors,const MLafEnv& aEnv,const CCoeControl& aMatchedControl);
	IMPORT_C static void DrawButton(const MLafEnv& aLafEnv,CWindowGc& aGc,const CCoeControl& aScrollButton,const TRect& aRect,TInt aButtonType,TBool aPressed);
	IMPORT_C static TInt ButtonBreadth();
	IMPORT_C static void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList);
	};

/**
 * @internal
 * Do not use
 */
class LafArrowHeadScrollButton
	{
public:
	IMPORT_C static void GetBorder(TGulBorder& aBorder, TBool aIsPressed);
	IMPORT_C static void GetBorderColors(TGulBorder::TColors& aBorderColors,const MLafEnv& aEnv,const CCoeControl& aMatchedControl);
	IMPORT_C static void DrawButton(const MLafEnv& aLafEnv,CWindowGc& aGc,const CCoeControl& aScrollButton,const TRect& aRect,TInt aButtonType,TBool aPressed);
	IMPORT_C static TInt ButtonBreadth();
	};

#endif
