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

#include "LAFSCRLB.H"
#include "LAFSTD.H"
#include "lafmain.h"
#include "lafcommn.h"

//
// Class LafScrollBar
//

const TInt KLafScrollBarMinThumbLength=16;
const TInt KLafScrollBarBorderWidth=1;
const TInt KLafScrollBarDefaultBreadth = 23;
	
EXPORT_C TInt LafScrollBar::Constant(TConstantType aConstant)
	{
	TInt retVal=0;
	switch(aConstant)
		{
	case EMinimumThumbLen:
		retVal=KLafScrollBarMinThumbLength;
		break;
	case EDefaultFlags:
		retVal=0;
		break;
	case EDefaultBreadth:
		retVal=KLafScrollBarDefaultBreadth;
		break;
	case EBorderWidth:
		retVal=KLafScrollBarBorderWidth;
		break;
	case EDefaultButtonPositionFlags:
		retVal=SLafScrollBar::EButtonsAtEndOfShaft;
		break;
	default:
		__ASSERT_DEBUG(EFalse,Panic(ELafPanicConstantNotKnown));
		break;
		}
	return retVal;
	}

/**
 * Gets the default border for the matched control in aBorder. Called from the constructor of the matched control.
 */
EXPORT_C void LafScrollBar::GetDefaultBorder(TGulBorder& aBorder)
	{
	aBorder=TGulBorder(TGulBorder::ESingleBlack);
	}

/**
 * Gets the set of border colors for the matched control in aBorderColors. The RGB values of the colors obtained
 * may depend on the the display mode, the environment color list and the instance of the
 * matched control aMatchedControl. Called by the matched control from its Draw() method and passed on to the
 * Draw() method of TGulBorder. 
 */
EXPORT_C void LafScrollBar::GetBorderColors(TGulBorder::TColors& aBorderColors, const MLafEnv& aLafEnv, const CCoeControl& aMatchedControl)
	{
	LafCommonUtils::GetRgbDerivedBorderColors( aBorderColors,
			EColorScrollBarShaft, aLafEnv,aMatchedControl );
	}

EXPORT_C void LafScrollBar::DrawHighlightedShaftArea(const MLafEnv& aLafEnv, const CCoeControl& aScrollBar, CWindowGc& aGc, TRect& aArea, TBool aIsHighlighted,
													 TInt /*aThumbPos*/, TInt /*aThumbLength*/, TBool /*aHorizontal*/)
	{//static
	TRgb color= aLafEnv.ControlColor((aIsHighlighted? EColorScrollBarShaftPressed : EColorScrollBarShaft), aScrollBar);
	aGc.SetBrushColor(color);
	aGc.Clear(aArea);
	}

/**
* Draws the shaft only for scrollbars with 'no thumb' or 'no thumb and no shaft'.
*/
EXPORT_C void LafScrollBar::DrawShaft(const MLafEnv& aLafEnv,const CCoeControl& aScrollBar,CWindowGc& aGc,const TRect& aRect,TInt aScrollBarDisplayFlags,TBool /*aHorizontal*/)
	{
	if (aScrollBarDisplayFlags&SLafScrollBar::EEikScrollBarNoShaftOrThumb)
		{
		aGc.SetBrushColor(aLafEnv.ControlColor(EColorScrollBarNoShaftOrThumb, aScrollBar)); //KEikScrollBarNoShaftOrThumbColor);
		aGc.Clear(aRect);
		}
	else if (aScrollBarDisplayFlags&SLafScrollBar::EEikScrollBarShaftButNoThumb)
		{
		const TRgb shaftColor= aLafEnv.ControlColor((aScrollBar.IsDimmed()? EColorScrollBarShaftDimmed : EColorScrollBarShaft),aScrollBar);
		aGc.SetBrushColor(shaftColor);
		aGc.Clear(aRect);
		}
	}


/**
* Draws the piece of shaft before and after the thumb the first time that the scrollbar is drawn. 
* The function RedrawShaft() draws the shaft subsequently.
*
*/
EXPORT_C void LafScrollBar::DrawShaftAroundThumb(const MLafEnv& aLafEnv,const CCoeControl& aScrollBar,CWindowGc& aGc,const TRect& aShaftRect,TBool aHorizontal,TInt aThumbPos,TInt aThumbLength)
	{
	const TRgb shaftColor= aLafEnv.ControlColor((aScrollBar.IsDimmed()? EColorScrollBarShaftDimmed : EColorScrollBarShaft),aScrollBar);
	// draw shaft before thumb
	TRect rect=aShaftRect;
	TInt& endOfShaftBeforeThumb=(aHorizontal)? rect.iBr.iX : rect.iBr.iY;
	endOfShaftBeforeThumb=aThumbPos;
	aGc.SetBrushColor(shaftColor);
	aGc.Clear(rect);
	// draw shaft after thumb
	rect=aShaftRect;
	TInt& startOfShaftAfterThumb=(aHorizontal)? rect.iTl.iX : rect.iTl.iY;
	startOfShaftAfterThumb=aThumbPos+aThumbLength;
	aGc.SetBrushColor(shaftColor);
	aGc.Clear(rect);
	}

/**
 * This function redraws the piece of the shaft which was previously 
 * covered by the thumb before a thumb drag event has taken place. The
 * rectangle aRect contains the region to be redrawn. The integer
 * aShaftStart is where the first part of the shaft meets the thumb, 
 * and aShaftEnd, the points where the second part of the shaft meets the thumb.
 */
EXPORT_C void LafScrollBar::RedrawShaft(const MLafEnv& aLafEnv,const CCoeControl& aScrollBar,CWindowGc& aGc, const TRect& aRect,TInt aShaftStart,TInt aShaftEnd,TBool aHorizontal)
	{
	TRect rect=aRect;
	TRgb shaftColor=aLafEnv.ControlColor((aScrollBar.IsDimmed()? EColorScrollBarShaftDimmed : EColorScrollBarShaft),aScrollBar);
	aGc.SetPenColor(aLafEnv.ControlColor(EColorScrollBarBorder,aScrollBar));
	// first check endpoints
	if(!IsBorderOutsideButtons())
		{
		if (aHorizontal)
			{
			if (rect.iTl.iX==aShaftStart)
				{
				aGc.DrawLine(rect.iTl, TPoint(rect.iTl.iX, rect.iBr.iY));
				rect.iTl.iX++;
				}
			if (rect.iBr.iX==aShaftEnd)
				{
				aGc.DrawLine(TPoint(rect.iBr.iX-1, rect.iTl.iY), TPoint(rect.iBr.iX-1, rect.iBr.iY));
				rect.iBr.iX--;
				}
			}
		else
			{
			if (rect.iTl.iY==aShaftStart)
				{
				aGc.DrawLine(rect.iTl, TPoint(rect.iBr.iX, rect.iTl.iY));
				rect.iTl.iY++;
				}
			if (rect.iBr.iY==aShaftEnd)
				{
				aGc.DrawLine(TPoint(rect.iTl.iX, rect.iBr.iY-1), TPoint(rect.iBr.iX, rect.iBr.iY-1));
				rect.iBr.iY--;
				}
			}
		}
	aGc.SetBrushColor(shaftColor);
	aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	aGc.Clear(rect);
	}

EXPORT_C TInt LafScrollBar::CalcThumbPosInScrollBar(TInt aShaftStart, TInt aShaftEnd,
		TInt aThumbLength,TInt aModelThumbPos,TInt aModelScrollSpan,TInt aModelThumbSpan )
	{
	TInt ret=aShaftStart;
	const TInt scrollRange=aModelScrollSpan-aModelThumbSpan;
	if (scrollRange<=0)
		return ret;
	const TInt maxRet=aShaftEnd-aThumbLength;
	if (scrollRange>0)
		ret+=aModelThumbPos*(maxRet-aShaftStart)/scrollRange;
	if (ret>maxRet)
		ret=maxRet;
	return ret;
	}

EXPORT_C TInt LafScrollBar::CalcThumbPosInScrollBarModel(TInt aShaftStart, TInt aShaftEnd,
		TInt aThumbLength,TInt aThumbPos,TInt aModelScrollSpan,TInt aModelThumbSpan )
	{
	TInt ret=0;
	const TInt scrollRange=aShaftEnd-aShaftStart-aThumbLength;
	if (scrollRange<=0)
		return ret;
	TInt maxRet=aModelScrollSpan-aModelThumbSpan;
	ret=(((aThumbPos-aShaftStart)<<1)*maxRet+scrollRange)/(scrollRange<<1);
	if (ret>maxRet)
		ret=maxRet;
	return ret;
	}

EXPORT_C void LafScrollBar::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList)
	{ // static
	TInt commonAttributes = TCoeColorUse::ESurrounds|TCoeColorUse::ENormal|TCoeColorUse::ENeutral;
	TCoeColorUse colorUse;

	colorUse.SetLogicalColor(EColorScrollBarBorder);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EActive|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorScrollBarShaft);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EActive|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorScrollBarShaftDimmed);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EDimmed|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorScrollBarShaftPressed);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EPressed|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorScrollBarNoShaftOrThumb);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EActive|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorScrollButtonIcon);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EActive|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorScrollButtonIconPressed);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EPressed|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorScrollButtonIconDimmed);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EActive|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorScrollThumbDimmed);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EDimmed|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorScrollButtonThumbBackground);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EActive|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorScrollButtonThumbBackgroundPressed);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EPressed|commonAttributes);
	aColorUseList.AppendL(colorUse);
	}

/**
 * Returns ETrue if the current position is not within the drag range from the scrollbar
 *
 * @since App-Framework_6.1
 */
EXPORT_C TBool LafScrollBar::IsPointerOutOfDragRange(const TPoint& /*aPointerPosition*/,const TRect& /*aScrollBarRect*/,TBool /*aHorizontal*/)
	{
	return EFalse;
	}

/**
 * Returns ETrue if the border of the scroll bar goes around the outside of the scroll
 * buttons.  Returns EFalse if the border is inside the scroll buttons
 * (ie. only surrounding the scroll bar shaft)
 *
 * @since App-Framework_6.1
 */
EXPORT_C TBool LafScrollBar::IsBorderOutsideButtons()
	{
	return EFalse;
	}

EXPORT_C TInt LafScrollBar::CalculateThumbLength(TInt aShaftLength,TInt aModelScrollSpan,
		TInt aModelThumbSpan)
	{
	TInt thumbLength=aShaftLength;
	const TInt scrollRange=aModelScrollSpan-aModelThumbSpan;
	if (scrollRange>0 && aModelScrollSpan)
		{
		thumbLength*=aModelThumbSpan;
		thumbLength/=aModelScrollSpan;
		}
	if (thumbLength<KLafScrollBarMinThumbLength)
		thumbLength=KLafScrollBarMinThumbLength;
	return thumbLength;
	}

/**
 * Method which modifies the size (aSize) and position (aPosition) of a scroll button
 * (of aButtonType) in the case where the border of the scroll bar draws into area which
 * used to belong to the buttons.  Other required parameters are aScrollBarFlags, aHorizontal
 * and aMargins which are all obvious properties of the matched class.
 *
 * @since App-Framework_6.1
 */
EXPORT_C void LafScrollBar::AdjustButtonExtentForScrollBarBorder(TPoint& /*aPosition*/,TSize& /*aSize*/,TInt /*aButtonType*/,TInt /*aScrollBarFlags*/, TBool /*aHorizontal*/, const TMargins& /*aMargins*/)
	{
	}

/**
 * Method which modifies the shaft start (aShaftStart) and shaft end (aShaftEnd) parameters
 * of a scroll button (of aButtonType) in the case were the border of the scroll bar draws
 * into area which used to belong to the buttons. Other required parameters are aScrollBarFlags, aHorizontal
 * and aMargins which are all obvious properties of the matched class.
 *
 * @since App-Framework_6.1
 */
EXPORT_C void LafScrollBar::AdjustShaftRangeForScrollBarBorder(TInt& /*aShaftStart*/,TInt& /*aShaftEnd*/,TBool /*aHorizontal*/,TInt /*aScrollBarFlags*/,const TMargins& /*aMargins*/)
	{
	}

//
// Class LafArrowHeadScrollBar
//

/**
 * Gets the default border for the matched control in aBorder. Called from the constructor of the matched control.
 */
EXPORT_C void LafArrowHeadScrollBar::GetDefaultBorder(TGulBorder& aBorder)
	{
	aBorder=TGulBorder(TGulBorder::ENone);
	}

/**
 * Gets the set of border colors for the matched control in aBorderColors. The RGB values of the colors obtained
 * may depend on the the display mode, the environment color list and the instance of the
 * matched control aMatchedControl. Called by the matched control from its Draw() method and passed on to the
 * Draw() method of TGulBorder. 
 */
EXPORT_C void LafArrowHeadScrollBar::GetBorderColors(TGulBorder::TColors& aBorderColors, const MLafEnv& aLafEnv, const CCoeControl& aMatchedControl)
	{
	LafCommonUtils::GetRgbDerivedBorderColors( aBorderColors,
			EColorScrollBarShaft, aLafEnv,aMatchedControl );
	}

