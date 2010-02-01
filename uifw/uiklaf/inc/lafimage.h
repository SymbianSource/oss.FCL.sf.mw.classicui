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


#ifndef __LAFIMAGE_H__
#define __LAFIMAGE_H__

#include <e32std.h>
#include <gulalign.h>
#include <gulutil.h>

class MLafEnv;
class CCoeControl;
class CWindowGc;
class CFbsBitmap;

/**
 * @internal
 * Do not use
 */
class LafImage
	{
public:
	IMPORT_C static void Draw(const MLafEnv& aEnv,const CCoeControl& aControl,CWindowGc& aGc,const TRect& aRect,
								TMargins8 aMargins,TGulAlignment aAlignment,const CFbsBitmap& aBitmap,
								const CFbsBitmap* aMask,TBool aFullEmphasis);
private:
	static void DrawPicture(const MLafEnv& aEnv,const CCoeControl& aControl,CWindowGc& aGc,const TRect& aRect,
								const CFbsBitmap& aBitmap,const CFbsBitmap* aMask,TBool aToBeClipped);
	};

#endif
