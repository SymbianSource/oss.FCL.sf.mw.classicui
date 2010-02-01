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


#ifndef __LAFLBD_H__
#define __LAFLBD_H__

#include <e32std.h>
#include <gdi.h>
#include "laflbi.h"

class TRect;
class CWindowGc;

/**
 * @internal
 * Do not use
 */
class LafListBoxData
	{
public:
	IMPORT_C static void DrawSearchText(const TRect& aItemTextRect,
			CWindowGc& aGc,const CFont& aItemFont,const CFont& aBoldFont,
			const TDesC& aItemText,TInt aStrPos,TInt aStrLen,
			TInt aBaseLineOffset,CGraphicsContext::TTextAlign aAlign);
	};

#endif //__LAFLBD_H__
