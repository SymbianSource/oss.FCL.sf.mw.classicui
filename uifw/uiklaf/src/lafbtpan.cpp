/*
* Copyright (c) 1998-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#include "lafbtpan.h"
#include <lafpanic.h>
#include "LAFSTD.H"

const TInt8 KLafButtonPanelTopMargin		=2;
const TInt8 KLafButtonPanelBottomMargin		=2;
const TInt8 KLafButtonPanelLeftMargin		=4;
const TInt8 KLafButtonPanelRightMargin		=4;

/**
 * The ButtonsAllSameSize() function should return ETrue if all dialog buttons are to be
 * the same size, or EFalse if they should only be their MinimumSize().
 */
EXPORT_C TBool LafButtonPanel::ButtonsAllSameSize()
	{//static 
	return ETrue; 
	}


/**
 * Shares out the length aExcess
 * between aShiftLeft and aShiftRight in order to align the button panel within the dialog.
 * This function is only used for horizontal buttons.
 */
EXPORT_C void LafButtonPanel::TranslateForExcessSpace(TInt aExcess, TInt& aShiftLeft, TInt& aShiftRight)
	{//static 
	aShiftLeft=aExcess/2;
	aShiftRight=(aShiftLeft-aExcess);
	}

/**
 * The ReduceMarginsToFit() function should reduce aHorizontalBorder and aGapBetweenButtons
 * until all of the lines of buttons in aArray fit into the available space. This function
 * should only be implemented by devices supporting dynamic margin adjustments when not 
 * enough space is provided.
 */
EXPORT_C void LafButtonPanel::ReduceMarginsToFit(
	const TFixedArray<TDimensions,KLafButPanMaxLinesOfDlgButtons>& /*aArray*/,
	TInt8& /*aLeftBorder*/, TInt8& /*aRightBorder*/, TInt& /*aGapBetweenButtons*/)
	{//static 
	}

/**
 * Return the margins for the button panel, packaged in a TMargins8 object
 *
 * @since App-Framework_6.1
 */
EXPORT_C TMargins8 LafButtonPanel::Margins()
 	{
 	TMargins8 margins;
 	margins.iLeft = KLafButtonPanelLeftMargin;
 	margins.iRight = KLafButtonPanelRightMargin;
 	margins.iTop = KLafButtonPanelTopMargin;
 	margins.iBottom = KLafButtonPanelBottomMargin;
 	return margins;
 	}

EXPORT_C TInt LafButtonPanel::Constant(TConstantType aConstant)
	{//static
	TInt retVal=0;
	switch (aConstant)
		{
	case EStartCorner:
		retVal=SLafControlGroup::EFromTopLeft;
		break;
	case EOrientation:
		retVal=SLafControlGroup::ELayVertically;
		break;
	case EInterRowMargin:
		retVal=2;
		break;
	case EVerticalGap:
		retVal=5;
		break;
	case EHorizontalGap:
		retVal=12;
		break;
	case EMinWidth:
		retVal=50;
		break;
	default:
		__ASSERT_DEBUG(EFalse,Panic(ELafPanicConstantNotKnown)); // should never be reached
		break;
		}
	return retVal;
	};
