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


#ifndef __LAFSCRLB_H__
#define __LAFSCRLB_H__

#include <e32std.h>
#include <gulbordr.h>
#include <coecntrl.h>
#include <lafpublc.h>

class MLafEnv;
class CWindowGc;

/**
 * @internal
 * Do not use
 */
class LafScrollBar
	{
public:
	inline static TInt MinimumThumbLength();
	inline static TInt DefaultFlags();
	inline static TInt DefaultBreadth();
	inline static TInt BorderWidth();
	inline static TInt DefaultButtonPositionFlags();
	IMPORT_C static void GetDefaultBorder(TGulBorder& aBorder);
	IMPORT_C static void GetBorderColors(TGulBorder::TColors& aBorderColors,const MLafEnv& aEnv,const CCoeControl& aMatchedControl);
// added to allow differing style of scrollbars
	IMPORT_C static void DrawShaft(const MLafEnv& aLafEnv,const CCoeControl& aScrollBar,CWindowGc& aGc,const TRect& aRect,TInt aScrollBarDisplayFlags,TBool aHorizontal);
	IMPORT_C static void DrawShaftAroundThumb(const MLafEnv& aLafEnv,const CCoeControl& aScrollBar,CWindowGc& aGc,const TRect& aShaftRect,TBool aHorizontal,TInt aThumbPos,TInt aThumbLength);
	IMPORT_C static void RedrawShaft(const MLafEnv& aLafEnv,const CCoeControl& aScrollBar,CWindowGc& aGc, const TRect& aRect,TInt aShaftStart,TInt aShaftEnd,TBool aHorizontal);
	IMPORT_C static void DrawHighlightedShaftArea(const MLafEnv& aLafEnv, const CCoeControl& aScrollBar, CWindowGc& aGc, TRect& aArea, TBool aIsHighlighted,
		TInt aThumbPos, TInt aThumbLength, TBool aHorizontal);
	IMPORT_C static TInt CalculateThumbLength(TInt aShaftLength,TInt aModelScrollSpan,
		TInt aModelThumbSpan);
	IMPORT_C static TInt CalcThumbPosInScrollBar(TInt aShaftStart, TInt aShaftEnd,
		TInt aThumbLength,TInt aModelThumbPos,TInt aModelScrollSpan,TInt aModelThumbSpan );
	IMPORT_C static TInt CalcThumbPosInScrollBarModel(TInt aShaftStart, TInt aShaftEnd,
		TInt aThumbLength,TInt aThumbPos,TInt aModelScrollSpan,TInt aModelThumbSpan );
	IMPORT_C static void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList);
	IMPORT_C static TBool IsPointerOutOfDragRange(const TPoint& aPointerPosition,const TRect& aScrollBarRect,TBool aHorizontal);
	IMPORT_C static TBool IsBorderOutsideButtons();
	IMPORT_C static void AdjustButtonExtentForScrollBarBorder(TPoint& aPosition,TSize& aSize,TInt aButtonType,TInt aScrollBarFlags, TBool aHorizontal, const TMargins& aMargins);
	IMPORT_C static void AdjustShaftRangeForScrollBarBorder(TInt& aShaftStart,TInt& aShaftEnd,TBool aHorizontal,TInt aScrollBarFlags,const TMargins& aMargins);
private:
	enum TConstantType
		{
		EMinimumThumbLen,
		EDefaultFlags,
		EDefaultBreadth,
		EBorderWidth,
		EDefaultButtonPositionFlags
		};
private:
	IMPORT_C static TInt Constant(TConstantType aConstant);
	};

class LafArrowHeadScrollBar
	{
public:
	IMPORT_C static void GetDefaultBorder(TGulBorder& aBorder);
	IMPORT_C static void GetBorderColors(TGulBorder::TColors& aBorderColors,const MLafEnv& aEnv,const CCoeControl& aMatchedControl);
	};

inline TInt LafScrollBar::MinimumThumbLength()
	{return Constant(EMinimumThumbLen);}
inline TInt LafScrollBar::DefaultFlags()
	{return Constant(EDefaultFlags);}
inline TInt LafScrollBar::DefaultBreadth()
	{return Constant(EDefaultBreadth);}
inline TInt LafScrollBar::BorderWidth()
	{return Constant(EBorderWidth);}

/**
 * Returns the button position flags which will be used if they have
 * not already been setup during scroll bar creation. 
 *
 * @since App-Framework_6.1
 */
inline TInt LafScrollBar::DefaultButtonPositionFlags()
	{return Constant(EDefaultButtonPositionFlags);}

#endif
