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
#include <coeinput.h>

#include "LAFSTD.H"
#include "lafpublc.h"
#include "LAFEDWIN.H"
#include "lafmain.h"
#include "lafcommn.h"

#define KDefaultMargin 1

/**
 * Gets the default border for the matched control in aBorder. Called from the constructor of the matched control.
 */
EXPORT_C void LafEdwin::GetDefaultBorder(TGulBorder& aBorder)
	{
	aBorder=TGulBorder(TGulBorder::ESingleGray);
	}

/**
 * Gets the set of border colors for the matched control in aBorderColors. The RGB values of the colors obtained
 * may depend on the the display mode, the environment color list and the instance of the
 * matched control aMatchedControl. Called by the matched control from its Draw() method and passed on to the
 * Draw() method of TGulBorder. 
 */
EXPORT_C void LafEdwin::GetBorderColors(TGulBorder::TColors& aBorderColors, const MLafEnv& aLafEnv, const CCoeControl& aMatchedControl)
	{
	LafCommonUtils::GetRgbDerivedBorderColors( aBorderColors,
			EColorControlSurroundBackground, aLafEnv,aMatchedControl );
	}

/**
 * Returns the default flags for the scroll bar for orientation aOrientation.
 * Called when the matched control creates its scroll bar frame..
 */
EXPORT_C TInt LafEdwin::DefaultScrollBarFlags(TInt /*aOrientation*/)
	{
	return 0;
	}

EXPORT_C CLafEdwinCustomDrawBase* LafEdwin::CreateEdwinCustomDrawL(const MLafEnv& aEnv,const CCoeControl& aControl,
																		CTextLayout& /*aTextLayout*/)
	{
	return CLafEdwinCustomDrawBase::NewL(aEnv,aControl);
	}

/**
 * Gets the default attributes for the scroll bar for orientation aOrientation in aAttributes.
 * Called when the matched control creates its scroll bar frame..
 */
EXPORT_C void LafEdwin::GetDefaultScrollBarAttributes(TInt /*aOrientation*/, LafScrollBarFrame::TScrollBarAttributes& aAttributes)
	{
	aAttributes = LafScrollBarFrame::TScrollBarAttributes();
	}

/**
 * Returns the keypresses an edwin is interested in receiving from a FEP
 */
EXPORT_C TInt LafEdwin::InputCapabilities()
	{ // static
	return TCoeInputCapabilities::EAllText|TCoeInputCapabilities::ENavigation;
	}

/**
 * Returns the default margins, for the edwin. Called during construction of the edwin.
 * The values may be overidden by the app programmer later.
 */
EXPORT_C TMargins8 LafEdwin::Margins()
	{//static
	TMargins8 margins;
	margins.SetAllValuesTo(KDefaultMargin);
	return margins;
	}

EXPORT_C void LafEdwin::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList)
	{ // static
	TInt commonAttributes=TCoeColorUse::ENormal|TCoeColorUse::ENeutral;
	TCoeColorUse colorUse;
	
	colorUse.SetLogicalColor(EColorControlDimmedText);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EContents|TCoeColorUse::EDimmed|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorControlDimmedBackground);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EContents|TCoeColorUse::EDimmed|commonAttributes);
	aColorUseList.AppendL(colorUse);
	
	colorUse.SetLogicalColor(EColorControlText);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EContents|TCoeColorUse::EActive|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorControlBackground);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EContents|TCoeColorUse::EActive|commonAttributes);
	aColorUseList.AppendL(colorUse);
	}

/**
 * Maps aKeyEvent from a specific device harware to standard EPOC key event.
 *
 * @since App-Framework_6.1
 */ 
EXPORT_C void LafEdwin::MapKeyEvent(TKeyEvent& /*aKeyEvent*/, TEventCode /*aType*/)
	{
	}

