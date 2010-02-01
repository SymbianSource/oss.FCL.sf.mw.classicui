/*
* Copyright (c) 2000 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __LAFMNBUT_H__
#define __LAFMNBUT_H__


#include <e32std.h>

//
// class LafMenuButton
//

/**
 * @since App-Framework_6.1
 */
class LafMenuButton
	{
public:
	IMPORT_C static TBool IsReportingOnButtonDown();
	IMPORT_C static void GetMenuPosition(TPoint& aMenuPosition, const TRect& aButtonRect, const TSize& aMenuSize, const TSize& aScreenSize);
	};


#endif //__LAFMNBUT_H__
