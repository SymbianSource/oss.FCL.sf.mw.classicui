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

	  
#include <gulcolor.h>

#include "lafthumb.h"
#include "lafmain.h"
#include "lafcommn.h"
#include "lafgrip.h"
#include "lafpublc.h"

//
// Class LafScrollThumb
//

const TInt KLafScrollThumbGripProportion=3;
const TInt KLafScrollThumbGripMargin=3;

/**
 * Draws the thumb of the scrollbar. The thumb can be drawn in pressed colors if aIsDragged is true, or in normal
 * colors otherwise. The scrollbar is horizontal if aHorizontal is true and vertical otherwise.
 */
EXPORT_C void LafScrollThumb::DrawDragState(const MLafEnv& aLafEnv,CWindowGc& aGc,const CCoeControl& aScrollThumb,TBool aIsDragged, const TRect& aRect, TBool aHorizontal)
    {
    TRgb bgColor;
    if (aScrollThumb.IsDimmed())
        {
        bgColor=aLafEnv.ControlColor((aIsDragged? EColorScrollButtonThumbBackgroundPressed : EColorScrollThumbDimmed),aScrollThumb);
        }
    else
        {
        bgColor=aLafEnv.ControlColor((aIsDragged? EColorScrollButtonThumbBackgroundPressed : EColorScrollButtonThumbBackground),aScrollThumb);
        }
    
    aGc.SetBrushColor(bgColor);
    aGc.Clear(aRect);
    
    TRect gripRect=aRect;
    TInt length=(aHorizontal)? gripRect.Size().iWidth : gripRect.Size().iHeight;
    TInt gripStart=((length*(KLafScrollThumbGripProportion-1))/KLafScrollThumbGripProportion)/2;
    TInt horizBorder=(aHorizontal)? gripStart : KLafScrollThumbGripMargin;
    TInt vertBorder=(aHorizontal)? KLafScrollThumbGripMargin : gripStart;
    
    gripRect.Shrink(horizBorder,vertBorder);
    // TLafGrip::TOrientation gripOrientation=(aHorizontal)? TLafGrip::EVertical : TLafGrip::EHorizontal;
    }

EXPORT_C void LafScrollThumb::GetDefaultBorder(TGulBorder& aBorder, TInt aOrientation)
	{
	if (aOrientation == SLafScrollThumb::EHorizontal)
		{
		aBorder=TGulBorder(TGulBorder::EHorizontalBar);
		}
	else
		{
		aBorder=TGulBorder(TGulBorder::EVerticalBar);
		}
	}

/**
 * Gets the set of border colors for the matched control in aBorderColors. The RGB values of the colors obtained
 * may depend on the the display mode, the environment color list and the instance of the
 * matched control aMatchedControl. Called by the matched control from its Draw() method and passed on to the
 * Draw() method of TGulBorder. 
 */
EXPORT_C void LafScrollThumb::GetBorderColors(TGulBorder::TColors& aBorderColors, const MLafEnv& aLafEnv, const CCoeControl& aMatchedControl)
	{
	LafCommonUtils::GetRgbDerivedBorderColors( aBorderColors,
			EColorScrollButtonThumbBackground, aLafEnv,aMatchedControl );
	}

EXPORT_C void LafScrollThumb::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList)
	{ // static
	TInt commonAttributes = TCoeColorUse::ESurrounds|TCoeColorUse::ENormal|TCoeColorUse::ENeutral;
	TCoeColorUse colorUse;

	colorUse.SetLogicalColor(EColorScrollThumbDimmed);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EDimmed|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorScrollButtonThumbBackgroundPressed);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EPressed|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorScrollButtonThumbBackground);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EActive|commonAttributes);
	aColorUseList.AppendL(colorUse);
	}
