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
#include <gulutil.h>
#include <gdi.h>
#include <gulcolor.h>
#include <coecntrl.h>

#include "LAFSTD.H"
#include "LAFCMBUT.H"
#include <uiklaf/private/lafenv.h>
#include "lafcommn.h"
#include "uikon.hrh"
#include <eikon.hrh>
#include "lafpublc.h"


const TInt KPressedDepth=2;
const TInt KSetDepth=1;
const TInt KImageMargin=0;
const TInt KLabelMargin=0;
const TInt KIntraComponentMargin=2;

const TInt KCommandButtonBaseHorizontalMargins=KPressedDepth;	//deals with command,twopicturecommand & invertercommand buttons
const TInt KCommandButtonBaseVerticalMargins=KPressedDepth;		//deals with command,twopicturecommand & invertercommand buttons
const TInt KBitmapButtonHorizontalMargins=2;
const TInt KBitmapButtonVerticalMargins=2;
const TInt KTextButtonHorizontalMargins=2;
const TInt KTextButtonVerticalMargins=2;

// The border types for the above set and pressed depths
const TInt KBorderClear			=TGulBorder::EDeepRaised;
const TInt KBorderClearPressed	=TGulBorder::EDeepSunken;
const TInt KBorderSet			=TGulBorder::EDeepSunken;
const TInt KBorderSetPressed	=TGulBorder::EDeepSunken;


//
// Class LafCommandButtonBase
//

/**
 * Gets the default border for the matched control in aBorder. Called from the constructor of the matched control.
 */
EXPORT_C void LafCommandButtonBase::GetDefaultBorder(TGulBorder& aBorder)
	{
	aBorder=KBorderClear;
	}

/**
 * Gets the set of border colors for the matched control in aBorderColors. The RGB values of the colors obtained
 * may depend on the the display mode, the environment color list and the instance of the
 * matched control aMatchedControl. Called by the matched control from its Draw() method and passed on to the
 * Draw() method of TGulBorder. 
 */
EXPORT_C void LafCommandButtonBase::GetBorderColors(TGulBorder::TColors& aBorderColors,const MLafEnv& aLafEnv,const CCoeControl& aMatchedControl)
	{
	LafCommonUtils::GetRgbDerivedBorderColors( aBorderColors,
			EColorButtonFaceClear, aLafEnv,aMatchedControl );
	}

/**
 * Gets the border appropriate for the behavior (including default buttons) and state of the control.
 */
EXPORT_C void LafCommandButtonBase::GetBorder(TGulBorder& aBorder, TInt aDrawState, 
											  TInt aFlags,const CCoeControl& /*aButtonBase*/,
											  const TBool /*aIsDefaultButton*/)
	{
	TInt borderType = TGulBorder::ENone;

	if (aFlags&EEikButLatches)
		{
		switch (aDrawState)
			{
		case SLafButtonBase::EDrawClear:
			borderType = KBorderClear;
			break;
		case SLafButtonBase::EDrawClearPressed:
			borderType = KBorderClearPressed;
			break;
		case SLafButtonBase::EDrawSet:
			borderType = KBorderSet;
			break;
		case SLafButtonBase::EDrawSetPressed:
			borderType = KBorderSetPressed;
			break;
		default:
			__ASSERT_DEBUG(EFalse,Panic(ELafPanicConstantNotKnown));
			break;
			}
		}
	else
		{
		switch (aDrawState)
			{
		case SLafButtonBase::EDrawSetPressed:
			borderType = KBorderSetPressed;
			break;
		case SLafButtonBase::EDrawClear:
			borderType = KBorderClear;
			break;
		case SLafButtonBase::EDrawClearPressed:
		case SLafButtonBase::EDrawSet:
			borderType = KBorderSet;
			break;
		default:
			__ASSERT_DEBUG(EFalse,Panic(ELafPanicConstantNotKnown));
			break;
			}
		}

	aBorder.SetType(borderType);
	}

EXPORT_C TInt LafCommandButtonBase::ComponentOffset(TInt aDrawState, TInt aFlags)
	{
	TInt pos = 0;
	if (aFlags&EEikButLatches)
		{
		switch (aDrawState)
			{
		default:
		case SLafButtonBase::EDrawClear:
			break;
		case SLafButtonBase::EDrawClearPressed:
			pos = KPressedDepth;
			break;
		case SLafButtonBase::EDrawSet:
			pos = KSetDepth;
			break;
		case SLafButtonBase::EDrawSetPressed:
 			pos = KPressedDepth;
			break;
			}
		}
	else
		{
		switch (aDrawState)
			{
		case SLafButtonBase::EDrawSetPressed:
 			pos = KPressedDepth;
			break;
		default:
		case SLafButtonBase::EDrawClear:
			break;
		case SLafButtonBase::EDrawClearPressed:
		case SLafButtonBase::EDrawSet:
			pos = KSetDepth;
			break;
			}
		}
	return pos;
	}


/**
 * Prepares the basic graphic contents according to the the type of command
 * button, e.g. pen and brush colors.
 *
 * @since ER5U 
 */
EXPORT_C void LafCommandButtonBase::PrepareContext(CWindowGc& aGc,TInt aDrawState,
												   const MLafEnv& aLafEnv,
												   const CCoeControl& aButtonBase)
	{
	aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	TRgb penColor;
	TRgb brushColor;
	switch (aDrawState)
		{
	case SLafButtonBase::EDrawSet:
		penColor=aLafEnv.ControlColor(EColorButtonTextPressed,aButtonBase);
		brushColor=aLafEnv.ControlColor(EColorButtonFaceSet,aButtonBase);
		break;
	case SLafButtonBase::EDrawClearPressed:
		penColor=aLafEnv.ControlColor(EColorButtonTextPressed,aButtonBase);
		brushColor=aLafEnv.ControlColor(EColorButtonFaceClearPressed,aButtonBase);
		break;
	case SLafButtonBase::EDrawClear:
		penColor=aLafEnv.ControlColor(EColorButtonText,aButtonBase);
		brushColor=aLafEnv.ControlColor(EColorButtonFaceClear,aButtonBase);
		break;
	case SLafButtonBase::EDrawSetPressed:
		penColor=aLafEnv.ControlColor(EColorButtonText,aButtonBase);
		brushColor=aLafEnv.ControlColor(EColorButtonFaceSetPressed,aButtonBase);
		break;
	default:
		__ASSERT_DEBUG(EFalse,Panic(ELafPanicConstantNotKnown));
		break;
		}
	aGc.SetPenColor(penColor);
	aGc.SetBrushColor(brushColor);
	}

/**
 * Prepares the graphics context, picks the appropriate border colors, sets up internal rectangles
 * and draws border and internal controls.  Also facilitates different drawing of selected buttons
 * and buttons with default focus. 
 */
EXPORT_C void LafCommandButtonBase::Draw(const MLafEnv& aLafEnv, const CCoeControl& aMatchedControl,
							 CWindowGc& aGc,
							 const TGulBorder& aBorder,
							 TInt aDrawOffset,TInt aDrawState,
							 TMargins8 aMargins,
							 TBool /*aIsDefaultButton*/)
	{
	PrepareContext(aGc,aDrawState,aLafEnv,aMatchedControl);
	TGulBorder::TColors borderColors;
	GetBorderColors(borderColors,aLafEnv, aMatchedControl);	
	const TRect rect(aMatchedControl.Rect());
	aBorder.Draw(aGc, rect, borderColors);

    const TRect outerRect(aBorder.InnerRect(rect));
	TRect innerRect(outerRect);

	innerRect.SetRect(innerRect.iTl.iX+aMargins.iLeft+1,innerRect.iTl.iY+aMargins.iTop+1,
					innerRect.iBr.iX-aMargins.iRight-1,innerRect.iBr.iY-aMargins.iBottom-1);
	innerRect.Move(aDrawOffset,aDrawOffset);
	innerRect.iBr.iX-=1;
	innerRect.iBr.iY-=1;

	DrawUtils::ClearBetweenRects(aGc,outerRect,innerRect);

	if(aMatchedControl.IsFocused())
		DrawSelection(aBorder,rect,aGc);
    }

EXPORT_C void LafCommandButtonBase::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList)
	{ // static
	TInt commonAttributes = TCoeColorUse::ESurrounds|TCoeColorUse::ENeutral;
	TCoeColorUse colorUse;

	colorUse.SetLogicalColor(EColorButtonText);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EActive|TCoeColorUse::ENormal|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorButtonFaceClear);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EActive|TCoeColorUse::ENormal|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorButtonTextPressed);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EPressed|TCoeColorUse::ENormal|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorButtonFaceClearPressed);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EPressed|TCoeColorUse::ENormal|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorButtonFaceSet);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EActive|TCoeColorUse::ESet|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorButtonFaceSetPressed);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EPressed|TCoeColorUse::ESet|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorLabelDimmedText);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EPressed|TCoeColorUse::ESet|commonAttributes);
	aColorUseList.AppendL(colorUse);
	}

/**
 * Draws a dashed rectangle inside the button.
 *
 * @since ER5U 
 */
void LafCommandButtonBase::DrawSelection(const TGulBorder& aBorder,const TRect& aRect,
										 CWindowGc& aGc)
	{
	aGc.SetPenStyle(CGraphicsContext::EDashedPen);
    TRect innerRect=aBorder.InnerRect(aRect);
//	innerRect.Shrink(1,1);
	TInt offset=2;
	innerRect.iTl.iX += 1;
	innerRect.iTl.iY += 1;
	innerRect.iBr.iX -= offset;
	innerRect.iBr.iY -= offset;
	TPoint posTl=innerRect.iTl;
	TPoint posBr=innerRect.iBr;
	aGc.DrawLine(posTl,TPoint(posBr.iX+1,posTl.iY));
	aGc.DrawLine(posBr,TPoint(posBr.iX,posTl.iY));
	aGc.DrawLine(posTl,TPoint(posTl.iX,posBr.iY));
	aGc.DrawLine(posBr,TPoint(posTl.iX-1,posBr.iY));
	aGc.SetPenStyle(CGraphicsContext::ESolidPen);
    }

/**
 * @internal
 */
EXPORT_C TInt LafCommandButtonBase::Constant(TConstantType aConstant)
	{// static
	TInt retValue = 0;
	switch (aConstant)
		{
	case EImageMargin:
		retValue = KImageMargin;
		break;
	case ELabelMargin:
		retValue = KLabelMargin;
		break;
	case EIntraComponentMargin:
		retValue = KIntraComponentMargin;
		break;
	default:
		__ASSERT_DEBUG(EFalse, Panic(ELafPanicConstantNotKnown));
		break;
		}
	return retValue;
	}

//
// Class LafCommandButton
//
EXPORT_C TMargins8 LafCommandButton::Margins()
	{
	TMargins8 margins;
	margins.iTop =KCommandButtonBaseVerticalMargins;
	margins.iBottom =KCommandButtonBaseVerticalMargins;
	margins.iLeft =KCommandButtonBaseHorizontalMargins;
	margins.iRight =KCommandButtonBaseHorizontalMargins;
	return margins;
	}


//
// Class LafTwoPictureCommandButton
//
EXPORT_C TMargins8 LafTwoPictureCommandButton::Margins()
	{
	TMargins8 margins;
	margins.iTop =KCommandButtonBaseVerticalMargins;
	margins.iBottom =KCommandButtonBaseVerticalMargins;
	margins.iLeft =KCommandButtonBaseHorizontalMargins;
	margins.iRight =KCommandButtonBaseHorizontalMargins;
	return margins;
	}


//
// Class LafInverterCommandButton
//
EXPORT_C TMargins8 LafInverterCommandButton::Margins()
	{
	TMargins8 margins;
	margins.iTop =KCommandButtonBaseVerticalMargins;
	margins.iBottom =KCommandButtonBaseVerticalMargins;
	margins.iLeft =KCommandButtonBaseHorizontalMargins;
	margins.iRight =KCommandButtonBaseHorizontalMargins;
	return margins;
	}


//
// Class LafBitmapButton
//
EXPORT_C TMargins8 LafBitmapButton::Margins()
	{
	TMargins8 margins;
	margins.iTop =KBitmapButtonVerticalMargins;
	margins.iBottom =KBitmapButtonVerticalMargins;
	margins.iLeft =KBitmapButtonHorizontalMargins;
	margins.iRight =KBitmapButtonHorizontalMargins;
	return margins;
	}

//
// Class LafTextButton
//
EXPORT_C TMargins8 LafTextButton::Margins()
	{
	TMargins8 margins;
	margins.iTop =KTextButtonVerticalMargins;
	margins.iBottom =KTextButtonVerticalMargins;
	margins.iLeft =KTextButtonHorizontalMargins;
	margins.iRight =KTextButtonHorizontalMargins;
	return margins;
	}

//
// Class LafTwoPictureCommandButton
//

/**
 * Gets the default border for the matched control in aBorder. Called from the constructor of the matched control.
 */
EXPORT_C void LafTwoPictureCommandButton::GetDefaultBorder(TGulBorder& aBorder)
	{
	aBorder=TGulBorder(TGulBorder::ENone);
	}

/**
 * Gets the set of border colors for the matched control in aBorderColors. The RGB values of the colors obtained
 * may depend on the the display mode, the environment color list and the instance of the
 * matched control aMatchedControl. Called by the matched control from its Draw() method and passed on to the
 * Draw() method of TGulBorder. 
 */
EXPORT_C void LafTwoPictureCommandButton::GetBorderColors(TGulBorder::TColors& aBorderColors, const MLafEnv& aLafEnv, const CCoeControl& aMatchedControl)
	{
	LafCommonUtils::GetRgbDerivedBorderColors( aBorderColors,
			EColorButtonFaceClear, aLafEnv,aMatchedControl );
	}

		
