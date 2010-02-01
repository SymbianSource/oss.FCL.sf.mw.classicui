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



#include <gulbordr.h>
#include <gulcolor.h>
#include <gulutil.h>
#include <coecntrl.h>

#include <uikon.hrh>
#include <eikon.hrh>

#include "LAFSCRLB.H"
#include "LAFSCBUT.H"
#include "LAFSTD.H"
#include "lafpublc.h"

#include "LAFSBFRM.H"


//
// Class LafScrollBarFrame::TScrollBarAttributes()
//

EXPORT_C LafScrollBarFrame::TScrollBarAttributes::TScrollBarAttributes()
: iControlType(EEikCtScrollBar), iBreadth(LafScrollBar::DefaultBreadth()),
	iSide(SLafScrollBarFrame::EBottomOrRight), iManagement(SLafScrollBarFrame::EComponent)
	{
	}

//
// Class LafScrollBarFrame
//

const TInt KLafFloatingScrollBarOffset=5;

/**
 * Returns the default flags for the matched control. Called from the constructor of the matched control.
 */
EXPORT_C TInt LafScrollBarFrame::DefaultFlags()
	{
	return 0;
	}

/**
 * Returns the default flags for the scroll bar for orientation aOrientation.
 * Called from the constructor of the scroll bar frame..
 */
EXPORT_C TInt LafScrollBarFrame::DefaultScrollBarFlags(TInt /*aOrientation*/)
	{
	return 0;
	}

/**
 * Gets the default attributes for the scroll bar for orientation aOrientation in aAttributes.
 * Called from the constructor of the scroll bar frame..
 */
EXPORT_C void LafScrollBarFrame::GetDefaultScrollBarAttributes(TInt /*aOrientation*/, TScrollBarAttributes& aAttributes)
	{
	aAttributes = LafScrollBarFrame::TScrollBarAttributes();
	}

/**
 * Gets the position for a floating scroll bar for orientation aOrientation in aPosition.
 * The scroll bar attributes aAttributes, the client rectangle of the scrolled area aClientRect and
 * the scroll bar size aScrollBarSize may all influence the positioning.  Called for floating scroll bars
 * from the TileL() method of the scroll bar frame when tiling the scroll bar geomtery with the client area.
 */
EXPORT_C void LafScrollBarFrame::GetFloatingScrollBarPosition(TInt aOrientation, const TScrollBarAttributes& aAttributes, const TRect& aClientRect, const TSize& /*aScrollBarSize*/, TPoint &aPosition)
	{
	aPosition = aClientRect.iTl;
	
	if (aOrientation == SLafScrollBar::EVertical)
		{
		if (aAttributes.iSide == SLafScrollBarFrame::EBottomOrRight)
			{
			aPosition.iX = aClientRect.iBr.iX - aAttributes.iBreadth - KLafFloatingScrollBarOffset;
			aPosition.iY += KLafFloatingScrollBarOffset;
			}
		}
	else
		{
		if (aAttributes.iControlType == EEikCtArrowHeadScrollBar)
			aPosition.iY = aClientRect.iBr.iY - LafArrowHeadScrollButton::ButtonBreadth();
		else
			{
			if (aAttributes.iSide == SLafScrollBarFrame::EBottomOrRight)
				aPosition.iY = aClientRect.iBr.iY - aAttributes.iBreadth - KLafFloatingScrollBarOffset;
			else
				aPosition.iY += KLafFloatingScrollBarOffset;
			
			aPosition.iX += KLafFloatingScrollBarOffset;
			}
		}
	}

/**
 * Returns the length of the floating scroll bar for orientation aOrientation.
 * The scroll bar attributes aAttributes, the client rectangle of the scrolled area aClientRect
 * and the scroll bar size aScrollBarSize may all influence the scroll bar length  Called for floating
 * scroll bars from the TileL() method of the scroll bar frame when tiling the scroll bar geomtery with
 * the client area.
 */
EXPORT_C TInt LafScrollBarFrame::FloatingScrollBarLength(TInt aOrientation, const TScrollBarAttributes& aAttributes, const TRect& aClientRect, const TSize& aScrollBarSize)
	{
	if (aOrientation == SLafScrollBar::EVertical)
		{
		if (aAttributes.iSide == SLafScrollBarFrame::EBottomOrRight)
			return 2*aScrollBarSize.iWidth;
		else
			return aClientRect.Height();
		}
	else
		{
		if (aAttributes.iControlType == EEikCtArrowHeadScrollBar)
			return aClientRect.Width();
		else
			return 2*aScrollBarSize.iHeight;
		}
	}

EXPORT_C void LafScrollBarFrameCornerWindow::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList)
	{ // static
	TCoeColorUse colorUse;
	colorUse.SetLogicalColor(EColorScrollButtonThumbBackground);
	colorUse.SetUse(TCoeColorUse::ESurrounds|TCoeColorUse::ENormal|TCoeColorUse::ENeutral|TCoeColorUse::EBack|TCoeColorUse::EActive);
	aColorUseList.AppendL(colorUse);
	}
