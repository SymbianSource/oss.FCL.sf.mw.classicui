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


#include "lafimage.h"

#include <w32std.h>
#include <coecntrl.h>
#include <uiklaf/private/lafenv.h>
#include <lafmain.h>

#include <AknsDrawUtils.h>
#include <coeccntx.h>

EXPORT_C void LafImage::Draw(const MLafEnv& aEnv,const CCoeControl& aControl,CWindowGc& aGc,const TRect& /*aRect*/,
								TMargins8 aMargins,TGulAlignment aAlignment,const CFbsBitmap& aBitmap,
								const CFbsBitmap* aMask,TBool aFullEmphasis)
	{ // static
	if (aFullEmphasis)
		{
		aGc.SetBrushColor(KRgbBlack);
		aGc.SetDrawMode(CGraphicsContext::EDrawModeNOTPEN);
		}
	const TRect rect(aControl.Rect());
	TRect inner=aMargins.InnerRect(rect);
	TSize bmpSize=aBitmap.SizeInPixels();
	const TSize innerSize=inner.Size();
	inner=aAlignment.InnerRect(inner,bmpSize);
	if (innerSize.iWidth<bmpSize.iWidth || innerSize.iHeight<bmpSize.iHeight)
		DrawPicture(aEnv,aControl,aGc,inner,aBitmap,aMask,ETrue);
	else
		DrawPicture(aEnv,aControl,aGc,inner,aBitmap,aMask,EFalse);
	aGc.SetDrawMode(CGraphicsContext::EDrawModePEN);

    AknsDrawUtils::BackgroundBetweenRects( AknsUtils::SkinInstance(),
        AknsDrawUtils::ControlContext( &aControl ), &aControl,
        aGc, rect, inner );
	}

void LafImage::DrawPicture(const MLafEnv& aEnv,const CCoeControl& aControl,CWindowGc& aGc,const TRect& aRect,
								const CFbsBitmap& aBitmap,const CFbsBitmap* aMask,TBool aToBeClipped)
	{ // static
	const TSize size=(aToBeClipped? aRect.Size() : aBitmap.SizeInPixels());
	const TRect rect(size);
	if (aControl.IsDimmed())
		{
		if (aMask)
			aGc.BitBltMasked(aRect.iTl,aEnv.Bitmap(TUid::Uid(KLafUidEikonGrayVal)),rect,aMask,ETrue);
		else
			aGc.BitBlt(aRect.iTl,&aBitmap,rect);
		return;
		}
	if (aMask)
		{
        // Reset the gc to make sure that the brush & pen are not used in blitting
        MCoeControlContext* ctrlCtx = aControl.ControlContext();
        if ( ctrlCtx )
            {
            ctrlCtx->ResetContext( aGc ); 
            }
        else
            {
            aGc.Reset();
            }
		aGc.BitBltMasked(aRect.iTl,&aBitmap,rect,aMask,ETrue);
		return;
		}
	aGc.BitBlt(aRect.iTl,&aBitmap,rect);
	}
