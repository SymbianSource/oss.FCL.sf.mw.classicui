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


#ifndef __LAFEDWIN_H__
#define __LAFEDWIN_H__

#include <e32std.h>
#include <gulbordr.h>
#include <coecntrl.h>
#include "LAFSBFRM.H"

class CTextLayout;
class CLafEdwinCustomDrawBase;
class MLafEnv;

/**
 * @internal
 * Do not use
 */
class LafEdwin
	{
public:
	IMPORT_C static void GetDefaultBorder(TGulBorder& aBorder);
	IMPORT_C static CLafEdwinCustomDrawBase* CreateEdwinCustomDrawL(const MLafEnv& aEnv,const CCoeControl& aControl,
																		CTextLayout& aTextLayout);
	IMPORT_C static void GetBorderColors(TGulBorder::TColors& aBorderColors,const MLafEnv& aEnv,const CCoeControl& aMatchedControl);
	IMPORT_C static void GetDefaultScrollBarAttributes(TInt aOrientation, LafScrollBarFrame::TScrollBarAttributes& aAttributes);
	IMPORT_C static TInt DefaultScrollBarFlags(TInt aOrientation);
	IMPORT_C static TInt InputCapabilities();
	IMPORT_C static TMargins8 Margins();
	IMPORT_C static void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList);
	IMPORT_C static void MapKeyEvent(TKeyEvent& aKeyEvent, TEventCode aType);
	};

#endif
