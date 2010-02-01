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


#ifndef __LAFBTPAN_H__
#define __LAFBTPAN_H__

#include <e32std.h>
#include <lafpublc.h>
#include <gulutil.h>

const TInt KLafButPanMaxLinesOfDlgButtons=5; // Change requires Uikon recompile. Must be same across all Uikon devices per Epoc release
const TInt KLafButPanNoMinButWidth=0;


/**
 * @internal
 * Do not use
 */
class LafButtonPanel
	{
public:
	class TDimensions;
public:
	IMPORT_C static TBool ButtonsAllSameSize();
	IMPORT_C static void TranslateForExcessSpace(TInt aExcess, TInt& aShiftLeft, TInt& aShiftRight);
	IMPORT_C static void ReduceMarginsToFit(
		const TFixedArray<TDimensions,KLafButPanMaxLinesOfDlgButtons>& aArray,
		TInt8& aLeftBorder, TInt8& aRightBorder, TInt& aGapBetweenButtons);
	IMPORT_C static TMargins8 Margins();
	inline static TInt DefaultStartCorner();
	inline static TInt DefaultOrientation();
	inline static TInt InterRowMargin();
	inline static TInt VerGapBetweenButtons();
	inline static TInt HorGapBetweenButtons();
	inline static TInt MinButtonWidth();
private:
	enum TConstantType
		{
		EStartCorner,
		EOrientation,
		EInterRowMargin,
		EVerticalGap,
		EHorizontalGap,
		EMinWidth
		};
private:
	IMPORT_C static TInt Constant(TConstantType aConstant);
	};

/**
 * The LafButtonPanel::TDimensions is used to pass information about a row of
 * buttons from CEikButtonPanel to LafButtonPanel.
 */
class LafButtonPanel::TDimensions
	{
public:
	TInt iNumButtons;
	TInt iExcess;
	};

/**
 * The DefaultStartCorner() function should return ELafBtPanFromTopLeft if the first button is
 * to be leftmost, or ELafBtPanFromTopRight if the first button is to be rightmost.
 */
inline TInt LafButtonPanel::DefaultStartCorner()
	{//static	
	return Constant(EStartCorner);	
	};
 
/**
 * The DefaultOrientation() function should return ELafBtPanLayVertically for a device allowing
 * vertical buttons, or ELafBtPanLayHorizontally for a device with only horizontal buttons.
 */
inline TInt LafButtonPanel::DefaultOrientation()
	{//static
	return Constant(EOrientation);
	};

/**
 * The InterRowMargin() function returns the size of the gap between two
 * rows of buttons.
 */
inline TInt LafButtonPanel::InterRowMargin()
	{//static
	return Constant(EInterRowMargin);
	};

/**
 * The VerGapBetweenButtons() function returns the size of the vertical gap between two
 * buttons in a vertical layout.
 */
inline TInt LafButtonPanel::VerGapBetweenButtons()
	{//static
	return Constant(EVerticalGap);
	};

/**
 * The HorGapBetweenButtons() function returns the size of the desired horizontal gap between two
 * buttons in a horizontal layout.
 */
inline TInt LafButtonPanel::HorGapBetweenButtons()
	{//static
	return Constant(EHorizontalGap);	
	};

/**
 * The MinButtonWidth() function returns the minimum size of a dialog button. If set to 
 * KLafButPanNoMinButWidth then the minimum width of the button will be used.
 */
inline TInt LafButtonPanel::MinButtonWidth()	
	{//static
	return Constant(EMinWidth);	
	};


#endif // __LAFBTPAN_H__
