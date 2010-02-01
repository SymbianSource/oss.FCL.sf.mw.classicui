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


#ifndef __LAFLBBUT_H__
#define __LAFLBBUT_H__

#include <e32std.h>
#include <lafpublc.h>
#include <gulalign.h>

/**
 * @internal
 * Do not use
 */
class LafLabeledButton
	{
public:
	IMPORT_C static TBool ShowHotKey();
	IMPORT_C static TInt InputCapabilities();
	IMPORT_C static TGulAlignmentValue LabelAlignment();
	inline static TInt MinimumButtonHeight();
	inline static TInt HorizontalLabelMargin();
	inline static TInt VerticalLabelMargin();
	inline static TInt MaxLabelTextLengthInChars();
private:
	enum TConstantType
		{
		EMinimumButtonHeight,
		EHorizontalLabelMargin,
		EVerticalLabelMargin,
		EMaxLabelTextLengthInChars
		};
private:
	IMPORT_C static TInt Constant(TConstantType aConstant);
	};

/**
 * Returns the minimum height which a labeled button can have.
 *
 * @since App-Framework_6.1
 */
inline TInt LafLabeledButton::MinimumButtonHeight()
	{
	return Constant(EMinimumButtonHeight);
	}

/**
 * Returns the value of the horizontal label margin.
 * This is divided appropriately between the left and right sides of
 * the label in the labeled button, depending on its alignment setting.
 *
 * @since App-Framework_6.1
 */
inline TInt LafLabeledButton::HorizontalLabelMargin()
	{
	return Constant(EHorizontalLabelMargin);
	}

/**
 * Returns the value of the horizontal label margin.
 * This is divided appropriately between the top and bottom sides of
 * the label in the labeled button, depending on its alignment setting.
 *
 * @since App-Framework_6.1
 */
inline TInt LafLabeledButton::VerticalLabelMargin()
	{
	return Constant(EVerticalLabelMargin);
	}

/**
 * Returns the value of the maximum number of text characters for the
 * label in the button.  If any constructed label exceeds this length,
 * then the code will panic deliberatly.
 *
 * @since App-Framework_6.1
 */
inline TInt LafLabeledButton::MaxLabelTextLengthInChars()
	{
	return Constant(EMaxLabelTextLengthInChars);
	}

#endif // __LAFLBBUT_H__
