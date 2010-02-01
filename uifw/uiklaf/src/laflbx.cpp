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


#include <w32std.h>
#include <gulutil.h>
#include <gulcolor.h>
#include <coeinput.h>

#include "LAFSTD.H"
#include "lafpublc.h"
#include "laflbx.h"
#include "lafcommn.h"

const TInt KLafListBoxBackgroundColor			=15;	// later, this will be a data member of the listbox  
const TInt KLafListBoxItemVGap					=6;		// to allow a box to be drawn around each item
const TInt KLafListBoxPointerRepeatInterval		=100;	// in micro seconds

/*The decision on whether or not to use the following 6 laf values is not 
made here.  Values >= 0 are appropriate (but obviously not too large, such as to
cause overlapping margins in the listbox).*/
const TInt KLafListBoxTopMargin					=0;
const TInt KLafListBoxBottomMargin				=0;
const TInt KLafListBoxLeftMargin				=0;
const TInt KLafListBoxRightMargin				=0;
const TInt KInnerGutter							=0;		// gutter at the left of textual list items, >= 0 is sensible, 0 turns it off
const TInt KInterItemVGap						=6;

/*Important display parameters (only) for popout listboxes*/
const TInt KLafListBoxMaxHeightInNumOfItems		=KLafListBoxNoMaxCellWidth;				// >= 1 is sensible, KLafListBoxNoMaxCellWidth value turns it off
const TInt KLafListBoxMaxCellWidthInNumOfPixels =KLafListBoxNoMaxHeightInNumOfItems;	// >= 20 is sensible, KLafListBoxNoMaxHeightInNumOfItems value turns it off

EXPORT_C TBool LafListBox::FadeBehind()
	{
	return EFalse;
	}

/**
 * Gets the default border for the matched control in aBorder. Called from the constructor of the matched control.
 */
EXPORT_C void LafListBox::GetDefaultBorder(TGulBorder& aBorder)
	{
	aBorder=TGulBorder(TGulBorder::ENone);
	}

/**
 * Gets the set of border colors for the matched control in aBorderColors. The RGB values of the colors obtained
 * may depend on the the display mode, the environment color list and the instance of the
 * matched control aMatchedControl. Called by the matched control from its Draw() method and passed on to the
 * Draw() method of TGulBorder. 
 */
EXPORT_C void LafListBox::GetBorderColors(TGulBorder::TColors& aBorderColors, const MLafEnv& aLafEnv, const CCoeControl& aMatchedControl)
	{
	LafCommonUtils::GetRgbDerivedBorderColors( aBorderColors,
			EColorControlSurroundBackground, aLafEnv,aMatchedControl );
	}

/**
 * Gets the default border for the matched control in aBorder. Called from the constructor of the matched control.
 */
EXPORT_C void LafListBox::GetDefaultPopoutBorder(TGulBorder& aBorder)
	{
	aBorder=TGulBorder(TGulBorder::EThickDeepRaisedWithOutline);
	}

/**
 * Gets the set of border colors for the matched control in aBorderColors. The RGB values of the colors obtained
 * may depend on the the display mode, the environment color list and the instance of the
 * matched control aMatchedControl. Called by the matched control from its Draw() method and passed on to the
 * Draw() method of TGulBorder. 
 */
EXPORT_C void LafListBox::GetPopoutBorderColors(TGulBorder::TColors& aBorderColors, const MLafEnv& aLafEnv, const CCoeControl& aMatchedControl)
	{
	LafCommonUtils::GetRgbDerivedBorderColors( aBorderColors,
			EColorControlBackground, aLafEnv,aMatchedControl );
	}


EXPORT_C TMargins8 LafListBox::Margins()
 	{
 	TMargins8 margins;
 	margins.iLeft = KLafListBoxLeftMargin;
 	margins.iRight = KLafListBoxRightMargin;
 	margins.iTop = KLafListBoxTopMargin;
 	margins.iBottom = KLafListBoxBottomMargin;
 	return margins;
 	}


EXPORT_C TInt LafListBox::Constant(TConstantType aType)
	{ // static
	switch (aType)
		{
	case EBackgroundColor:
		return KLafListBoxBackgroundColor;
	case EItemVGap:
		return KLafListBoxItemVGap;
	case EPointerRepeatInterval:
		return KLafListBoxPointerRepeatInterval;
	case EMaxHeightInNumOfItems:
		return KLafListBoxMaxHeightInNumOfItems;
	case EMaxCellWidthInNumOfPixels:
		return KLafListBoxMaxCellWidthInNumOfPixels;
	case EInnerGutter:
		return KInnerGutter;
	case EInterItemVGap:
		return KInterItemVGap;
	default:
		__ASSERT_DEBUG(EFalse,Panic(ELafPanicConstantNotKnown));
		}
	return 0; // will never reach here	
	}

/**
 * Returns the default flags for the scroll bar for orientation aOrientation.
 * Called when the matched control creates its scroll bar frame..
 */
EXPORT_C TInt LafListBox::DefaultScrollBarFlags(TInt /*aOrientation*/)
	{
	return 0;
	}

/**
 * Gets the default attributes for the scroll bar for orientation aOrientation in aAttributes.
 * Called when the matched control creates its scroll bar frame..
 */
EXPORT_C void LafListBox::GetDefaultScrollBarAttributes(TInt /*aOrientation*/, LafScrollBarFrame::TScrollBarAttributes& aAttributes)
	{
	aAttributes = LafScrollBarFrame::TScrollBarAttributes();
	}

/**
 * Returns the key types a listbox expects to receive from a FEP
 */
EXPORT_C TInt LafListBox::InputCapabilities(TInt aFlags)
	{ // static
	if (aFlags&SLafListBox::EIncrementalMatching)
		return TCoeInputCapabilities::ENavigation|TCoeInputCapabilities::EAllText;
	if (aFlags&SLafListBox::ENoFirstLetterMatching)
		return TCoeInputCapabilities::ENavigation;
	return TCoeInputCapabilities::ENavigation|TCoeInputCapabilities::EAllText;
	}

EXPORT_C void LafListBox::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList)
	{ // static
	TInt commonAttributes = TCoeColorUse::ENormal|TCoeColorUse::ENeutral;
	TCoeColorUse colorUse;

	colorUse.SetLogicalColor(EColorControlText);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EContents|TCoeColorUse::EActive|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorControlDimmedText);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EContents|TCoeColorUse::EDimmed|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorControlBackground);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EContents|TCoeColorUse::EActive|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorControlHighlightText);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EHighlights|TCoeColorUse::EActive|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorControlHighlightBackground);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EHighlights|TCoeColorUse::EActive|commonAttributes);
	aColorUseList.AppendL(colorUse);
	}

/**
 * Returns the keycode to use with listboxes for the given event.  Intended primarily to allow custom
 * device hardware keys to map to standard Epoc functions.
 *
 * @since App-Framework_6.1
 */ 
EXPORT_C TUint LafListBox::MapKeyCode(const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
	{ // static
	return aKeyEvent.iCode;
	}
