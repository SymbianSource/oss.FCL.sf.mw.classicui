/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
// lafmsg.cpp
//
//
//

#include <uiklaf/private/lafmsg.h>
#include <gulfont.h>
#include <uiklaf/private/lafenv.h>
#include "LAFSTD.H"
#include <gulcolor.h>


enum
	{
	EGapAboveText=3,
	EGapBelowText=2,
	EGapLeftOfText=2,
	EGapRightOfText=2
	};


enum
	{
	EWindowOffsetVertical=6,
	EWindowOffsetHorizontal=0
	};


enum
	{
	EInfoMsgWinDuration=25*100000,
	EBusyMsgWinInitialDelay=10*100000
	};

EXPORT_C LafMsgWin::TDisplayParameters::TDisplayParameters(TDes& aTextToDisplay)
	:iTextToDisplay(aTextToDisplay)
	{
	/** Message window position. */
	iMsgWinPosition.iX = 0;
	iMsgWinPosition.iY = 0;

    /** Message window size. */
	iMsgWinSize.iWidth = 176;
	iMsgWinSize.iHeight = 50;

    /** Message window margins. */
    iMsgWinBorders.iTop = 5;
    iMsgWinBorders.iBottom = 5;
    iMsgWinBorders.iLeft = 5;
    iMsgWinBorders.iRight = 5;

    /** Message window alignment. */
	TGulAlignment iDisplayCorner = EHRightVTop;
     
    }

/**
 * This method sets the shadow on the blank window which the Info Message or Busy 
 * message is contained in.
 */
EXPORT_C void LafMsgWin::SetUpBlankWindow(RBlankWindow& aBlankWindow)
	{//static
	aBlankWindow.SetShadowHeight(0);
	aBlankWindow.SetShadowDisabled(ETrue);
	}

/**
 * This method completes the intitialisation of the LafMsgWin. This method should
 * set a font and call constructL on aMessageWin.
 */
EXPORT_C void LafMsgWin::CompleteMessageWinConstructionL(RMessageWindow& aMessageWin,const MLafEnv& aEnv)
	{//static
	TLogicalFont logicalFont(TLogicalFont::EView, TLogicalFont::ENormal, TZoomFactor());
	const CFbsFont& font=*(CFbsFont*)aEnv.Font(logicalFont);
	aMessageWin.ConstructL(EGapAboveText+font.AscentInPixels(), font.Handle(), aEnv.Color(EColorMsgWinBackground), aEnv.Color(EColorMsgWinForeground));
	}

EXPORT_C void LafMsgWin::HandleResourceChange(RMessageWindow& aMessageWin,const MLafEnv& aEnv)
	{//static
	aMessageWin.SetBackgroundColor(aEnv.Color(EColorMsgWinBackground));
	aMessageWin.SetTextColor(aEnv.Color(EColorMsgWinForeground));
	}

/**
 * This method should truncate the text in aParams.iTextToDisplay if this is needed on the 
 * device. It should also set aParms.iMsgWinSize and aParams.iMsgWinPosition of the message,
 * depending on the corner aParams.iDisplayCorner, and the font for the device.
 * aParams.iClientRect is provided for devices that wish to set the position relative to the
 * client rect of the application rather than the screen rect.
 */
EXPORT_C void LafMsgWin::ConfigureText(TDisplayParameters& aParams,const MLafEnv& aEnv)
	{//static
	TLogicalFont logicalFont(TLogicalFont::EView, TLogicalFont::ENormal, TZoomFactor());
	const CFont& font=*aEnv.Font(logicalFont);
	
	aParams.iMsgWinSize=TSize(aParams.iMsgWinBorders.iLeft+aParams.iMsgWinBorders.iRight+EGapLeftOfText+EGapRightOfText+font.TextWidthInPixels(aParams.iTextToDisplay),
				aParams.iMsgWinBorders.iTop+aParams.iMsgWinBorders.iBottom+EGapAboveText+EGapBelowText+font.HeightInPixels());
	aParams.iMsgWinPosition=aParams.iDisplayCorner.InnerTopLeft(aParams.iEnv->ScreenDevice()->SizeInPixels(), aParams.iMsgWinSize);
	switch (aParams.iDisplayCorner.HAlignment())
		{
	case EHLeft:
		aParams.iMsgWinPosition.iX+=EWindowOffsetHorizontal;
		break;
	case EHCenter:
		break;
	case EHRight:
		aParams.iMsgWinPosition.iX-=EWindowOffsetHorizontal;
		break;
#if defined(_DEBUG)
	default:
		Panic(ELafPanicMsgWinBadHorizontalAlignment);
		break;
#endif
		}
	switch (aParams.iDisplayCorner.VAlignment())
		{
	case EVTop:
		aParams.iMsgWinPosition.iY+=EWindowOffsetVertical;
		break;
	case EVCenter:
		break;
	case EVBottom:
		aParams.iMsgWinPosition.iY-=EWindowOffsetVertical;
		break;
#if defined(_DEBUG)
	default:
		Panic(ELafPanicMsgWinBadVerticalAlignment);
		break;
#endif
		}
	}

/**
 * Returns the duration (in microseconds), which the info message should be displayed for.
 *
 * @since App-Framework_6.1
 */
EXPORT_C TTimeIntervalMicroSeconds32 LafInfoMsgWin::DefaultDuration()
	{
	return EInfoMsgWinDuration;
	}

/**
 * Returns the duration (in microseconds), after which the busy message should initially appear.
 *
 * @since App-Framework_6.1
 */
EXPORT_C TTimeIntervalMicroSeconds32 LafBusyMsgWin::DefaultInitialDelay()
	{
	return EBusyMsgWinInitialDelay;
	}
