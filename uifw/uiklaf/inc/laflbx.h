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


#ifndef __LAFLBX_H__
#define __LAFLBX_H__


#include <e32std.h>
#include <w32std.h>
#include <gulutil.h>
#include <gulbordr.h>

#include "LAFSBFRM.H"

//
// Forward declarations
//

class CCoeControl;
class CWindowGc;
class MLafEnv;

/* value for LafListBox::MaxCellWidthInNumOfPixels
to test against which will define whether the laf
value for the maximum cell width is zero or not */
const TInt KLafListBoxNoMaxCellWidth = 0;

/* value for LafListBox::MaxHeightInNumOfItems
to test against which will define whether the laf
value for the maximum cell width is zero or not */
const TInt KLafListBoxNoMaxHeightInNumOfItems = 0;

/* value which decides whether the list box should use
the single value of 'iHorizontalMargin' provided by uikon
or the two values of left and right margins as defined by
this list box laf.  Should be kept at -1 for safety */
const TInt KLafListboxUseLafHorizMargins = -1;

/* value which decides whether the list box should use
the single value of 'iHorizontalMargin' provided by uikon
or the two values of left and right margins as defined by
this list box laf.  Should be kept at -1 for safety*/
const TInt KLafListboxUseLafVertMargins = -1;


/**
 * @internal
 * Do not use
 */
class LafListBox
	{
public:
    inline static TInt BackgroundColor();
    inline static TInt ItemVGap();
    inline static TInt PointerRepeatInterval();
	IMPORT_C static TBool FadeBehind();
	IMPORT_C static void GetDefaultBorder(TGulBorder& aBorder);
	IMPORT_C static void GetBorderColors(TGulBorder::TColors& aBorderColors, const MLafEnv& aLafEnv, const CCoeControl& aMatchedControl);
	IMPORT_C static void GetDefaultPopoutBorder(TGulBorder& aBorder);
	IMPORT_C static void GetPopoutBorderColors(TGulBorder::TColors& aBorderColors, const MLafEnv& aLafEnv, const CCoeControl& aMatchedControl);
	IMPORT_C static TMargins8 Margins();
	inline static TInt MaxHeightInNumOfItems();
	inline static TInt MaxCellWidthInNumOfPixels();
	inline static TInt InnerGutter();
	inline static TInt InterItemVGap();
	IMPORT_C static void GetDefaultScrollBarAttributes(TInt aOrientation, LafScrollBarFrame::TScrollBarAttributes& aAttributes);
	IMPORT_C static TInt DefaultScrollBarFlags(TInt aOrientation);
	IMPORT_C static TInt InputCapabilities(TInt aFlags);
	IMPORT_C static void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList);
	IMPORT_C static TUint MapKeyCode(const TKeyEvent& aKeyEvent,TEventCode aType);
private:
    enum TConstantType
        {
        EBackgroundColor,
        EItemVGap,
        EPointerRepeatInterval,
		EMaxHeightInNumOfItems,
		EMaxCellWidthInNumOfPixels,
		EInnerGutter,
		EInterItemVGap
        };
private:
    IMPORT_C static TInt Constant(TConstantType aType);
	};


//
// Inlines
//

inline TInt LafListBox::BackgroundColor()
    {return Constant(EBackgroundColor);}
inline TInt LafListBox::ItemVGap()
    {return Constant(EItemVGap);}
inline TInt LafListBox::PointerRepeatInterval()
    {return Constant(EPointerRepeatInterval);}
inline TInt LafListBox::MaxHeightInNumOfItems()
	{return Constant(EMaxHeightInNumOfItems);}
inline TInt LafListBox::MaxCellWidthInNumOfPixels()
	{return Constant(EMaxCellWidthInNumOfPixels);}
inline TInt LafListBox::InnerGutter()
	{return Constant(EInnerGutter);}
inline TInt LafListBox::InterItemVGap()
	{return Constant(EInterItemVGap);}

#endif //__LAFLBX_H__
