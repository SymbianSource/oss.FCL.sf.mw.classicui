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
#include <gulfont.h>

#include "LAFSTD.H"
#include "LAFSCBUT.H"
#include "LAFSCRLB.H"
#include "lafmain.h"
#include <uiklaf/private/lafenv.h>
#include "lafcommn.h"


#include "eiksfont.h"

const TInt KArrowHeadScrollBarHeight=15;


//
// local functions specific to our type of scrollbar button
//
LOCAL_C TRgb IconColor(const MLafEnv& aLafEnv, const CCoeControl& aScrollButton,TBool aPressed)
	{
	TLogicalColor color=EColorScrollButtonIcon;
	if (aScrollButton.IsDimmed())
		color=EColorScrollButtonIconDimmed;
	else if (aPressed)
		color=EColorScrollButtonIconPressed;
	return aLafEnv.ControlColor(color,aScrollButton);
	}

LOCAL_C void DrawIcon(const MLafEnv& aLafEnv,CWindowGc& aGc,TRect& aRect,const CCoeControl& aScrollButton,TInt aButtonType,TBool aPressed)
	{
	TInt charCode=0;
	switch (aButtonType)
		{
    default:
        break;
	case SLafScrollButton::ENudgeUp:
		charCode=ESymFontScrollUp;
		break;
	case SLafScrollButton::ENudgeDown:
		charCode=ESymFontScrollDown;
		break;
	case SLafScrollButton::ENudgeLeft:
		charCode=ESymFontScrollLeft;
		break;
	case SLafScrollButton::ENudgeRight:
		charCode=ESymFontScrollRight;
		break;
	case SLafScrollButton::EPageUp:
		charCode=ESymFontScrollPageUp;
		break;
	case SLafScrollButton::EPageDown:
		charCode=ESymFontScrollPageDown;
		break;
	case SLafScrollButton::EPageLeft:
		charCode=ESymFontScrollPageLeft;
		break;
	case SLafScrollButton::EPageRight:
		charCode=ESymFontScrollPageRight;
		break;
	case SLafScrollButton::ETop:
		charCode=ESymFontScrollToTop;
		break;
	case SLafScrollButton::EBottom:
		charCode=ESymFontScrollToBottom;
		break;
	case SLafScrollButton::EHome:
		charCode=ESymFontScrollToLeftEnd;
		break;
	case SLafScrollButton::EEnd:
		charCode=ESymFontScrollToRightEnd;
		break;
		}
	TBuf<1> symbol;
	symbol.Append(TChar(charCode));
	TLogicalFont logicalFont;
	logicalFont.iFontId=TUid::Uid(KLafUidSymbolFontVal);
	const CFont* symFont=aLafEnv.Font(logicalFont);
	aGc.UseFont(symFont);
	aGc.SetPenStyle(CGraphicsContext::ESolidPen);
	aGc.SetPenColor(IconColor(aLafEnv,aScrollButton,aPressed));
	const TInt extraVerticalSpace=(aRect.Height() - symFont->HeightInPixels());
	const TInt baselineOffset=Max(symFont->AscentInPixels(),extraVerticalSpace/2 + symFont->AscentInPixels());
	aGc.DrawText(symbol,aRect,baselineOffset,CGraphicsContext::ECenter);
	aGc.DiscardFont();
	}

//
// Class LafScrollButton
//
EXPORT_C void LafScrollButton::GetBorder(TGulBorder& aBorder, TBool aIsPressed)
	{
	TInt adj = aBorder.Adjacent();
	aBorder=TGulBorder(aIsPressed ? TGulBorder::EShallowSunken : TGulBorder::EDeepRaised);
	aBorder.SetAdjacent(adj);
	}

/**
 * Gets the set of border colors for the matched control in aBorderColors. The RGB values of the colors obtained
 * may depend on the the display mode, the environment color list and the instance of the
 * matched control aMatchedControl. Called by the matched control from its Draw() method and passed on to the
 * Draw() method of TGulBorder. 
 */
EXPORT_C void LafScrollButton::GetBorderColors(TGulBorder::TColors& aBorderColors, const MLafEnv& aLafEnv, const CCoeControl& aMatchedControl)
	{
	LafCommonUtils::GetRgbDerivedBorderColors( aBorderColors,
			EColorScrollButtonThumbBackground, aLafEnv,aMatchedControl );
	}

EXPORT_C TInt LafScrollButton::ButtonBreadth()
	{ // should this be allowed...
	return LafScrollBar::DefaultBreadth();
	}

EXPORT_C void LafScrollButton::DrawButton(const MLafEnv& aLafEnv,CWindowGc& aGc,const CCoeControl& aScrollButton,const TRect& aRect,TInt aButtonType,TBool aPressed)
	{
	TRect rect(aRect);
	const TRgb brushColor=aLafEnv.ControlColor((aPressed? EColorScrollButtonThumbBackgroundPressed : EColorScrollButtonThumbBackground),aScrollButton);
	aGc.SetBrushColor(brushColor);
	aGc.Clear(rect);
//
	if (aPressed)
		rect.iTl+=TPoint(2,2);

	DrawIcon(aLafEnv,aGc,rect,aScrollButton,aButtonType,aPressed);
	}

EXPORT_C void LafScrollButton::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList)
	{ // static
	TInt commonAttributes = TCoeColorUse::ESurrounds|TCoeColorUse::ENormal|TCoeColorUse::ENeutral;
	TCoeColorUse colorUse;

	colorUse.SetLogicalColor(EColorScrollButtonThumbBackgroundPressed);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EPressed|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorScrollButtonThumbBackground);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EActive|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorScrollButtonIcon);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EActive|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorScrollButtonIconDimmed);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EDimmed|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorScrollButtonIconPressed);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EPressed|commonAttributes);
	aColorUseList.AppendL(colorUse);
	}

//
// class LafArrowHeadScrollButton
//

EXPORT_C void LafArrowHeadScrollButton::GetBorder(TGulBorder& aBorder, TBool /*aIsPressed*/)
	{
	aBorder=TGulBorder(TGulBorder::ENone);
	}

/**
 * Gets the set of border colors for the matched control in aBorderColors. The RGB values of the colors obtained
 * may depend on the the display mode, the environment color list and the instance of the
 * matched control aMatchedControl. Called by the matched control from its Draw() method and passed on to the
 * Draw() method of TGulBorder. 
 */
EXPORT_C void LafArrowHeadScrollButton::GetBorderColors(TGulBorder::TColors& aBorderColors, const MLafEnv& aLafEnv, const CCoeControl& aMatchedControl)
	{
	LafCommonUtils::GetRgbDerivedBorderColors( aBorderColors,
			EColorScrollButtonThumbBackground, aLafEnv,aMatchedControl );
	}

EXPORT_C TInt LafArrowHeadScrollButton::ButtonBreadth()
	{
	return KArrowHeadScrollBarHeight;
	}

EXPORT_C void LafArrowHeadScrollButton::DrawButton(const MLafEnv& aLafEnv,CWindowGc& aGc,const CCoeControl& aScrollButton,const TRect& aRect,TInt aButtonType,TBool aPressed)
	{
	TRect rect(aRect);
	const TRgb brushColor=aLafEnv.ControlColor(EColorMenuPaneBackground,aScrollButton);
	aGc.SetBrushColor(brushColor);
	aGc.Clear(rect);
//
	if (aPressed)
		rect.iTl+=TPoint(2,2);

	DrawIcon(aLafEnv,aGc,rect,aScrollButton,aButtonType,aPressed);
	}
