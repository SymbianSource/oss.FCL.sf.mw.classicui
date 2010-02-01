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

#include <gulfont.h>
#include "laftxlbx.h"
#include <lafmain.h>
#include <uiklaf/private/lafenv.h>

//
//class LafTextListBox
//

EXPORT_C const CFont* LafTextListBox::Font(const MLafEnv& aLafEnv)
	{//static
	TLogicalFont logicalFont;
	logicalFont.iFontId=TUid::Uid(KLafUidNormalFontVal);
	return (aLafEnv.Font(TLogicalFont(logicalFont)));
	}


//
// class LafSnakingTextListBox
//

EXPORT_C const CFont* LafSnakingTextListBox::Font(const MLafEnv& aLafEnv)
	{//static
	TLogicalFont logicalFont;
	logicalFont.iFontId=TUid::Uid(KLafUidNormalFontVal);
	return (aLafEnv.Font(TLogicalFont(logicalFont)));
	}

