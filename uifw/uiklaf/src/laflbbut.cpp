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


#include "laflbbut.h"
#include <coeinput.h>
#include "LAFSTD.H"

const TInt KLafLabeledButtonMinimumButtonHeight=23;
const TInt KLafLabeledButtonMaxLabelTextLengthInChars=20;//if any constructed label exceeds this the code will panic deliberatly
const TInt KLafLabeledButtonHorizontalLabelMargin=2;
const TInt KLafLabeledButtonVerticalLabelMargin=2;
const TGulAlignmentValue KLafLabeledButtonLabelAlignment=EHCenterVCenter;

/**
 * The EverShowHotKey() function returns ETrue if hotkeys should be displayed when set
 * and EFalse otherwise.
 */
EXPORT_C TBool LafLabeledButton::ShowHotKey()
	{// static
	return ETrue;
	}

/**
 * Returns the key types labeled buttons want to receive from a FEP
 */
EXPORT_C TInt LafLabeledButton::InputCapabilities()
	{ // static
	return TCoeInputCapabilities::ENavigation;
	}

/**
 * Returns the required alignment for the contents of the labeled button
 */
EXPORT_C TGulAlignmentValue LafLabeledButton::LabelAlignment()
	{// static
	return KLafLabeledButtonLabelAlignment;
	}

/**
 * Returns a constant value according to aConstantType.
 * @internal
 */
EXPORT_C TInt LafLabeledButton::Constant(TConstantType aConstant)
	{// static
	TInt retValue = 0;
	switch (aConstant)
		{
	case EMinimumButtonHeight:
		retValue = KLafLabeledButtonMinimumButtonHeight;
		break;
	case EHorizontalLabelMargin:
		retValue = KLafLabeledButtonHorizontalLabelMargin;
		break;
	case EVerticalLabelMargin:
		retValue = KLafLabeledButtonVerticalLabelMargin;
		break;
	case EMaxLabelTextLengthInChars:
		retValue = KLafLabeledButtonMaxLabelTextLengthInChars;
		break;
	default:
		__ASSERT_DEBUG(EFalse, Panic(ELafPanicConstantNotKnown));
		break;
		}
	return retValue;
	}
