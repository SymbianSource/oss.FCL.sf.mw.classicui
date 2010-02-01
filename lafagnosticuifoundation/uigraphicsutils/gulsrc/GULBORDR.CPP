// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#include <gdi.h>
#include <gulbordr.h>
#include <gulpanic.h>
#include "GULSTD.H"
#include "gullogicalborder.h"

const TInt KTypeMask=0xFFFFFF00; 
const TInt KAdjacentMask=0xF;

const TInt KBorderTypeConversionMask=0x00FFFFFF;

const TInt KBorderShift=0x8;
const TInt KDepthBitPosition=0x4;
const TInt KDepthShift=KBorderShift+KDepthBitPosition;

//
// Class MGulLogicalBorder
//

EXPORT_C void MGulLogicalBorder::MGulLogicalBorderReserved()
	{
	}

//
// Class GulTls
//

EXPORT_C void GulTls::SetLogicalBorder(MGulLogicalBorder* aLogicalBorder)
	{
	Dll::SetTls(REINTERPRET_CAST(TAny*,aLogicalBorder));
	};

EXPORT_C const MGulLogicalBorder* GulTls::LogicalBorder()
	{
	return REINTERPRET_CAST(const MGulLogicalBorder*,Dll::Tls());
	}

//
// Class TGulBorder::TColors
//

EXPORT_C TGulBorder::TColors::TColors()
	: iLine(KRgbBlack), iBack(KRgbWhite), iLight(KRgbWhite),
	iMidlight(KRgbWhite), iMid(KRgbDarkGray), iDark(KRgbDarkGray), iInternalBack(KRgbWhite)
/** Default constructor.

Initialises the border colours to blacks, whites and greys. For details, see 
the data members. */
	{
	}

//
// Class TGulBorder
//

EXPORT_C TGulBorder::TGulBorder()
	: iType(0)
/** Default constructor.

The border type is initialised to zero (i.e. no border). */
	{
	}


EXPORT_C TGulBorder::TGulBorder(TBorderType aType)
	: iType(STATIC_CAST(TInt,aType)<<KBorderShift)
/** Constructor with a border type.

@param aType The border type. */
    {
	TranslateLegacyTypes();
	}


EXPORT_C TGulBorder::TGulBorder(TBorderType aType,TGulAdjacent aAdjacent)
	: iType((STATIC_CAST(TInt,aType)<<KBorderShift)|aAdjacent)
/** Constructor with a border type and an adjacency.

@param aType The border type.
@param aAdjacent Border adjacency. No outline is drawn for border sides that 
are adjacent. */
    {
	TranslateLegacyTypes();
	}

EXPORT_C TGulBorder::TGulBorder(TInt aType)
	: iType(aType<<KBorderShift)
/** Constructor with a border type, specified as a TInt.

@param aType The border type. Possible values are defined in the TBorderType 
enumeration. */
    {
	TranslateLegacyTypes();
	}


EXPORT_C TGulBorder::TGulBorder(TInt aType,TGulAdjacent aAdjacent)
	: iType((aType<<KBorderShift)|aAdjacent)
/** Constructor with a border type, specified as a TInt, and a border adjacency.

@param aType The border type.
@param aAdjacent Border adjacency. No outline is drawn for border sides that 
are adjacent. */
    {
	TranslateLegacyTypes();
	}

EXPORT_C void TGulBorder::SetType(TInt aType)
/** Sets the border type.

Descriptive borders use one of the values from the TBorderType enum. Logical 
borders use one of the TLogicalType values. Custom border types can be created 
by selecting one value from each of the enums T3DStyle and TConstructionStyle, 
one or more values from each of the enums TOutlineStyle and TInlineStyle, 
one or more values from the enums TThickness and TRounding and ORing all these 
values together.

@param aType The border type. */
    {
    iType&=(~KTypeMask);
    iType|=(aType<<KBorderShift);

	TranslateLegacyTypes();
    }

//
// Translates legacy border types which now affect the adjacency as well as the border
// primitive type.
//
void TGulBorder::TranslateLegacyTypes()
	{
	TInt internalType=InternalType();

	if(internalType&EWithOverlap)
		{
		if(internalType&EHorizontal)
			SetAdjacent(EGulAdjTop|EGulAdjBottom);
		else
			SetAdjacent(EGulAdjLeft|EGulAdjRight);
	    iType|=(EWithOutline<<KBorderShift);
		}
	}


EXPORT_C TInt TGulBorder::Type() const
/** Gets the border type. 

@return The border type. This is one of the values from the TBorderType (for 
descriptive borders) or TLogicalType (for logical borders) enums. */
    {
    return (KBorderTypeConversionMask&((iType&KTypeMask)>>KBorderShift));
    }

EXPORT_C void TGulBorder::SetAdjacent(TInt aAdjacent)
/** Sets the border adjacency.

No outline is drawn for border sides that are adjacent.

@param aAdjacent The border adjacency. For possible values, see the TGulAdjacent 
enum. */
    {
    iType&=(~KAdjacentMask);
    iType|=(KAdjacentMask & aAdjacent);
    }

inline TInt TGulBorder::Depth() const
	{
	return (iType>>KDepthShift)&0x3;
	}

EXPORT_C TBool TGulBorder::HasBorder() const
/** Tests whether a border is present.

No border is present if its type is ENoBorder.

@return True if a border is present, otherwise false. */
	{
	return (!(((iType&KTypeMask)>>KBorderShift)==ENoBorder));
	}


EXPORT_C TInt TGulBorder::Adjacent() const
/** Gets the border adjacency.

No outline is drawn for border sides that are adjacent.

@return The border adjacency. For possible values, see the TGulAdjacent enum. */
	{
	return iType&KAdjacentMask;
	}


inline TBool TGulBorder::IsSunken() const
	{
	return (iType>>KBorderShift)&ESunken;
	}

//
// Returns the innner rectangular area of the outline
// Simply returns the outer rectangle if there is no outline 
//
TRect TGulBorder::OutlineInnerRect(const TRect& aOuterRect) const
    {
	if (!(InternalType()&EWithOutline))
		return aOuterRect;
	
	TRect inner=aOuterRect;
    TMargins margins=OutlineMargins();
    inner.iTl.iX+=margins.iLeft;
    inner.iTl.iY+=margins.iTop;
    inner.iBr.iX-=margins.iRight;
    inner.iBr.iY-=margins.iBottom;
    return inner;
    }

//
// Returns the number of rounding pixels for the start of the mid-tone colored part of the border.
//
TInt TGulBorder::BorderRounding() const
	{
	TInt rounding=Rounding();
	if (InternalType()&EWithOutline)
		rounding--;
	return (rounding<0 ? 0 : rounding);
	}

//
// Returns the number of rounding pixels at the inline.
//
TInt TGulBorder::InlineRounding() const
	{
	TInt rounding=BorderRounding();
	rounding-=Thickness();
	return (rounding<0 ? 0 : rounding);
	}

EXPORT_C TMargins TGulBorder::Margins() const
/** Returns the border margins.

The border margins are four integers that represent the widths in pixels of 
the top, bottom, left and right hand sides of the border.

If the border is a logical border, then calculating the margins is delegated 
to its implementation of MGulLogicalBorder::Margins().

Otherwise, the margins are calculated by adding together the single pixel 
border outline, if present (this is zero for adjacent sides), the border thickness 
(containing the mid-tone highlights and lowlights), and the single pixel interior 
outline, if present.

@return The border margins. */
    {
	// Delegates the margin size determination to TLS instance of MGulLogicalBorder if logical border
	if (InternalType()&ELogical)
		{
		const MGulLogicalBorder* logicalBorder=GulTls::LogicalBorder();
		__ASSERT_DEBUG(logicalBorder,Panic(EEgulPanicNullTls));
		return logicalBorder ? logicalBorder->Margins(*this) : TMargins();
		}

    TMargins margins=OutlineMargins();
	
	TMargins borderMargins=BorderMargins();

	margins.iTop+=borderMargins.iTop;
	margins.iLeft+=borderMargins.iLeft;
	margins.iRight+=borderMargins.iRight;
	margins.iBottom+=borderMargins.iBottom;

	TMargins inlineMargins=InlineMargins();

	margins.iTop+=inlineMargins.iTop;
	margins.iLeft+=inlineMargins.iLeft;
	margins.iRight+=inlineMargins.iRight;
	margins.iBottom+=inlineMargins.iBottom;

	return margins;
    }

//
// Returns the margins for the single pixel outline only
// Margins are zero if the border has no outline.
// There is no margin on sides which are adjacent.
//
TMargins TGulBorder::OutlineMargins() const
    {
	TMargins margins;

	margins.iTop=margins.iLeft=0;
	margins.iBottom=margins.iRight=0;

	if (!(InternalType()&EWithOutline))
		return margins;

	if (!(iType&EGulAdjLeft))
		margins.iLeft+=1;

	if (!(iType&EGulAdjTop))
		margins.iTop+=1;

	if (!(iType&EGulAdjRight))
		margins.iRight+=1;

	if (!(iType&EGulAdjBottom))
		margins.iBottom+=1;

    return margins;
	}


TMargins TGulBorder::BorderMargins() const
    {
    TMargins margins;

	TInt topLeftMargin=0;
	TInt bottomRightMargin=0;

	if (InternalType()&EOneStep)
		topLeftMargin=bottomRightMargin=Thickness();
	else if (InternalType()&ETwoStep || InternalType()&EInvertedTwoStep)
		{
		if((InternalType()&ERaised && !(InternalType()&EInvertedTwoStep)) || (InternalType()&ESunken && (InternalType()&EInvertedTwoStep)))
			{
			topLeftMargin=1;
			bottomRightMargin=Thickness()+1;
			}
		else
			{
			topLeftMargin=Thickness()+1;
			bottomRightMargin=1;
			}
		}
	else if (InternalType()&EThreeStep)
		topLeftMargin=bottomRightMargin=Thickness()+1;

	margins.iTop=topLeftMargin;
	margins.iLeft=topLeftMargin;
	margins.iBottom=bottomRightMargin;
	margins.iRight=bottomRightMargin;

	return margins;
    }

TMargins TGulBorder::InlineMargins() const
    {
    TMargins margins;

	TInt marginWidth = 0;

	if (InternalType()&EWithInline)
		marginWidth++;

	margins.iTop=marginWidth;
	margins.iLeft=marginWidth;
	margins.iBottom=marginWidth;
	margins.iRight=marginWidth;
	
	return margins;
    }

EXPORT_C TSize TGulBorder::SizeDelta() const
/** Returns the size difference between the inner and outer rectangles of the border.

@return The size difference between the inner and outer rectangles. */
    {
    TMargins margins=Margins();
    return TSize(margins.iLeft+margins.iRight,margins.iTop+margins.iBottom);
    }

EXPORT_C TRect TGulBorder::OuterRect(const TRect& aInnerRect) const
/** Returns the rectangular area required to accommodate the inner rectangle aInnerRect
and the border.

@param aInnerRect The inner rectangular area.
@return The enclosing rectangular area. */
    {
    TRect outer=aInnerRect;
    TMargins margins=Margins();
    outer.iTl.iX-=margins.iLeft;
    outer.iTl.iY-=margins.iTop;
    outer.iBr.iX+=margins.iRight;
    outer.iBr.iY+=margins.iBottom;
    return outer;
    }

EXPORT_C TRect TGulBorder::InnerRect(const TRect& aOuterRect) const
/** Returns the rectangular area enclosed by the border.

@param aOuterRect The border's containing rectangle.
@return The inner rectangle. */
    {
    TRect inner=aOuterRect;
    TMargins margins=Margins();
    inner.iTl.iX+=margins.iLeft;
    inner.iTl.iY+=margins.iTop;
    inner.iBr.iX-=margins.iRight;
    inner.iBr.iY-=margins.iBottom;
    return inner;
    }


TRect TGulBorder::BorderInnerRect(const TRect& aOuterRect) const
    {
    TRect inner=aOuterRect;
    TMargins margins=BorderMargins();
    inner.iTl.iX+=margins.iLeft;
    inner.iTl.iY+=margins.iTop;
    inner.iBr.iX-=margins.iRight;
    inner.iBr.iY-=margins.iBottom;
    return inner;
    }

EXPORT_C void TGulBorder::Draw(CGraphicsContext& aGc,const TRect& aRect) const
/** Draws the border using a graphics context, inside a containing rectangle, and 
using default values for the border colours. 

For details of the default border colours, see class TColors.

This function does nothing if the border type is ENone. If the border is a 
logical border, drawing is delegated to its implementation of MGulLogicalBorder::Draw().

@param aGc The graphics context to draw through.
@param aRect The containing rectangle. This defines the border's outline, i.e. 
the border is drawn inside this rectangle.
@see MGulLogicalBorder::Draw() */
    {
	TColors borderColors;
	Draw(aGc,aRect,borderColors);
    }

EXPORT_C void TGulBorder::Draw(CGraphicsContext& aGc,const TRect& aRect, const TColors& aBorderColors) const
/** Draws the border using a graphics context, inside a containing rectangle, and 
using the border colours specified.

This function does nothing if the border type is ENone. If the border is a 
logical border, drawing is delegated to its implementation of MGulLogicalBorder::Draw().

@param aGc The graphics context to draw through.
@param aRect The containing rectangle. This defines the border's outline, i.e. 
the border is drawn inside this rectangle.
@param aBorderColors The border colours.
@see MGulLogicalBorder::Draw() */
    {
    if (!HasBorder())
        return;
	
	// Delegate drawing of logical border to TLS instance of MGulLogicalBorder if logical border
	if (InternalType()&ELogical)
		{
		const MGulLogicalBorder* logicalBorder=GulTls::LogicalBorder();
		__ASSERT_DEBUG(logicalBorder,Panic(EEgulPanicNullTls));
		if(logicalBorder)
			{
			logicalBorder->Draw(*this,aGc,aRect,aBorderColors);
			}
		return;
		}

	TRect workingRect=aRect;
	DrawOutline(aGc,workingRect,aBorderColors.iLine);

	if (Thickness())
		{
		workingRect=OutlineInnerRect(workingRect);

		if (InternalType()&EOneStep)
			DrawOneStep(aGc,workingRect,aBorderColors.iMidlight,aBorderColors.iMid);
		else if (InternalType()&ETwoStep)
			DrawTwoStep(aGc,workingRect,aBorderColors.iLight,aBorderColors.iMidlight,aBorderColors.iMid,aBorderColors.iDark);
		else if (InternalType()&EInvertedTwoStep)
			DrawInvertedTwoStep(aGc,workingRect,aBorderColors.iLight,aBorderColors.iMidlight,aBorderColors.iMid,aBorderColors.iDark);
		else if (InternalType()&EThreeStep)
			DrawThreeStep(aGc,workingRect,aBorderColors.iBack,aBorderColors.iLight,aBorderColors.iMidlight,aBorderColors.iMid,aBorderColors.iDark);
		}

	workingRect=BorderInnerRect(workingRect);
	DrawInline(aGc,workingRect,aBorderColors.iLine);
    }


void TGulBorder::DrawInline(CGraphicsContext& aGc,const TRect& aRect,TRgb aColor) const
    {
	if (!(InternalType()&EWithInline))
		return;

	TInt rounding=InlineRounding();

	DrawTopLeft(aGc,aRect,aColor,rounding);
	DrawBottomRight(aGc,aRect,aColor,rounding);
	}

//
// Draws the optional single pixel outline
// If there is no outline no drawing is done.
//
void TGulBorder::DrawOutline(CGraphicsContext& aGc,const TRect& aRect,TRgb aColor) const
    {
	if (!(InternalType()&EWithOutline))
		return;

	// legacy border types color support
	TRgb color;
	const TInt internalType=InternalType();
	if(internalType&EBlack)
		color=KRgbBlack;
	else if(internalType&EGray)
		color=KRgbGray;
	else
		color=aColor;
	//

	aGc.SetPenColor(color);
	if (internalType&EDottedOutline)
		aGc.SetPenStyle(CGraphicsContext::EDottedPen);

	TInt rounding=Rounding();

	if (rounding)
		{
		DrawTopLeft(aGc,aRect,color,rounding);
		DrawBottomRight(aGc,aRect,color,rounding);
		}
	else
		DrawRectOutline(aGc,aRect);

	if (internalType&EDottedOutline)
		aGc.SetPenStyle(CGraphicsContext::ESolidPen);
	}


//
// Draws the rectangular version of the outline
// The outline is not drawn on sides which are adjacent
//
void TGulBorder::DrawRectOutline(CGraphicsContext& aGc,const TRect& aRect) const
    {
	// left
	if (!(iType&EGulAdjLeft))
		aGc.DrawLine(TPoint(aRect.iTl.iX,aRect.iBr.iY-1),TPoint(aRect.iTl.iX,aRect.iTl.iY-1));

	// top
	if (!(iType&EGulAdjTop))
		aGc.DrawLine(TPoint(aRect.iTl.iX,aRect.iTl.iY),TPoint(aRect.iBr.iX,aRect.iTl.iY));

	// right
	if (!(iType&EGulAdjRight))
		aGc.DrawLine(TPoint(aRect.iBr.iX-1,aRect.iTl.iY),TPoint(aRect.iBr.iX-1,aRect.iBr.iY));
	
	// bottom
	if (!(iType&EGulAdjBottom))
		aGc.DrawLine(TPoint(aRect.iBr.iX-1,aRect.iBr.iY-1),TPoint(aRect.iTl.iX-1,aRect.iBr.iY-1));
	}

//
// Draws the one step border type.
// This consists of repeated one pixel frames drawn in the mid-tone highlight and lowlight colors
//	
void TGulBorder::DrawOneStep(CGraphicsContext& aGc,const TRect& aRect,TRgb aMidlight,TRgb aMid) const
    {	
	TRect workingRect = aRect;

	TRgb topOneColor=aMidlight;
	TRgb bottomOneColor=aMid;

	if (InternalType()&ESunken)
		{
		topOneColor=aMid;
		bottomOneColor=aMidlight;
		}

	if (InternalType()&EFlat)
		topOneColor=aMid;

	TInt rounding=BorderRounding();

	for(int i=0;i<Thickness();i++)
		{
		DrawBottomRight(aGc,workingRect,bottomOneColor,rounding);
		DrawTopLeft(aGc,workingRect,topOneColor,rounding);
		rounding--;
		workingRect.Shrink(1,1);
		}
	}

//
// Draws the two step border type.
// The outer closed frame is drawn in highlihgt and lowlight colors
// A repeating one pixel half-frame is then drawn in either the mid-tone highlight or lowlight color.
//
void TGulBorder::DrawTwoStep(CGraphicsContext& aGc,const TRect& aRect,TRgb aLight,TRgb aMidlight,TRgb aMid,TRgb aDark) const
    {	
	TRect workingRect = aRect;
	TBool drawTopLeftOnly=EFalse;

	TRgb topOneColor=aMid;
	TRgb bottomOneColor=aMid;
	TRgb topTwoColor=aLight;
	TRgb bottomTwoColor=aDark;

	if (InternalType()&ESunken)
		{
		topTwoColor=aDark;
		bottomTwoColor=aLight;
		drawTopLeftOnly=ETrue;
		}

	if (InternalType()&EFlat)
		{
		topTwoColor=aMidlight;
		bottomTwoColor=aMidlight;
		drawTopLeftOnly=ETrue;
		}
	
	TInt rounding=BorderRounding();

	DrawBottomRight(aGc,workingRect,bottomTwoColor,rounding);
	DrawTopLeft(aGc,workingRect,topTwoColor,rounding);
	rounding--;
	if (drawTopLeftOnly)
		{
		workingRect.iTl.iX+=1;
		workingRect.iTl.iY+=1;
		workingRect.iBr.iY-=1;
		}
	else
		{
		workingRect.iTl.iX+=1;
		workingRect.iBr.iX-=1;
		workingRect.iBr.iY-=1;
		}

	for(int i=0;i<Thickness();i++)
		{
		if (drawTopLeftOnly)
			{
			DrawTopLeft(aGc,workingRect,topOneColor,rounding);
			rounding--;
			workingRect.iTl.iX+=1;
			workingRect.iTl.iY+=1;
			}
		else
			{	
			DrawBottomRight(aGc,workingRect,bottomOneColor,rounding);
			rounding--;
			workingRect.iBr.iX-=1;
			workingRect.iBr.iY-=1;
			}
		}
	}

//
// Draw the inverted two step border type.
// As above the outer closed frame is drawn in highlihgt and lowlight colors
// A repeating one pixel half-frame is then drawn in either the mid-tone highlight or lowlight color.
// The difference is that the raised border show using top-left midlight etc.
// Another small difference is that sunken has light, midlight colors swapped
//
void TGulBorder::DrawInvertedTwoStep(CGraphicsContext& aGc,const TRect& aRect,TRgb aLight,TRgb aMidlight,TRgb aMid,TRgb aDark) const
    {	
	TRect workingRect = aRect;
	TBool drawTopLeftOnly=ETrue;

	TRgb topOneColor=aMidlight;
	TRgb bottomOneColor=aMidlight;
	TRgb topTwoColor=aLight;
	TRgb bottomTwoColor=aDark;

	if (InternalType()&ESunken)
		{
		topTwoColor=aDark;
		bottomTwoColor=aMidlight;
		bottomOneColor=aLight;
		drawTopLeftOnly=EFalse;
		}

	if (InternalType()&EFlat)
		{
		topTwoColor=aMid;
		bottomTwoColor=aMid;
		drawTopLeftOnly=EFalse;
		}
	
	TInt rounding=BorderRounding();

	DrawBottomRight(aGc,workingRect,bottomTwoColor,rounding);
	DrawTopLeft(aGc,workingRect,topTwoColor,rounding);
	rounding--;
	if (drawTopLeftOnly)
		{
		workingRect.iTl.iX+=1;
		workingRect.iTl.iY+=1;
		workingRect.iBr.iY-=1;
		}
	else
		{
		workingRect.iTl.iX+=1;
		workingRect.iBr.iX-=1;
		workingRect.iBr.iY-=1;
		}

	for(int i=0;i<Thickness();i++)
		{
		if (drawTopLeftOnly)
			{
			DrawTopLeft(aGc,workingRect,topOneColor,rounding);
			rounding--;
			workingRect.iTl.iX+=1;
			workingRect.iTl.iY+=1;
			}
		else
			{	
			DrawBottomRight(aGc,workingRect,bottomOneColor,rounding);
			rounding--;
			workingRect.iBr.iX-=1;
			workingRect.iBr.iY-=1;
			}
		}
	}

//
// Draws the three step border type.
// The outer frame is drawn in combined colors
// A repeating one pixel frame is then drawn in the mid-tone highlight and lowlight colors.
// The inner frame is drawn in combined colors
//
void TGulBorder::DrawThreeStep(CGraphicsContext& aGc,const TRect& aRect,TRgb aBack,TRgb aLight,TRgb aMidlight,TRgb aMid,TRgb aDark) const
    {
	TRect workingRect = aRect;

	TRgb topOneColor=aBack;
	TRgb bottomOneColor=aMid;
	TRgb topTwoColor=aLight;
	TRgb bottomTwoColor=aDark;

	if (InternalType()&ESunken)
		{
		topOneColor=aMid;
		bottomOneColor=aBack;
		topTwoColor=aDark;
		bottomTwoColor=aLight;
		}

	if (InternalType()&EFlat)
		{
		topOneColor=aMid;
		bottomOneColor=aMid;
		topTwoColor=aMidlight;
		bottomTwoColor=aMidlight;
		}
	
	TInt rounding=BorderRounding();

	DrawBottomRight(aGc,workingRect,bottomTwoColor,rounding);
	DrawTopLeft(aGc,workingRect,topOneColor,rounding);
	rounding--;
	workingRect.Shrink(1,1);

	for(int i=1;i<Thickness();i++)
		{
		DrawBottomRight(aGc,workingRect,bottomOneColor,rounding);
		DrawTopLeft(aGc,workingRect,topOneColor,rounding);
		rounding--;
		workingRect.Shrink(1,1);
		}

	DrawBottomRight(aGc,workingRect,bottomOneColor,rounding);
	DrawTopLeft(aGc,workingRect,topTwoColor,rounding);
	}

//
// Draws the top left portion of the one pixel border frame
//
void TGulBorder::DrawTopLeft(CGraphicsContext& aGc,const TRect& aRect,TRgb aColor,const TInt aRounding) const
    {
	TInt xOffset=0;
	TInt yOffset=0;

	if ((InternalType()&EFlat) || (InternalType()&ERaised))
		xOffset=1;

	if(InternalType()&ESunken)
		yOffset=1;

	if((InternalType()&EFlat) && (InternalType()&EThreeStep))
		{
		xOffset=1;
		yOffset=1;
		}

	aGc.SetPenColor(aColor);

	if (aRounding>0)
		DrawRoundedTopLeft(aGc,aRect,aRounding);
	else
		{
		// left
		aGc.DrawLine(TPoint(aRect.iTl.iX,aRect.iTl.iY),TPoint(aRect.iTl.iX,aRect.iBr.iY-yOffset));
		// top
		aGc.DrawLine(TPoint(aRect.iTl.iX,aRect.iTl.iY),TPoint(aRect.iBr.iX-xOffset,aRect.iTl.iY));
		}
	}

//
// Draws a rounded off version top left portion of the one pixel border frame
//
void TGulBorder::DrawRoundedTopLeft(CGraphicsContext& aGc,const TRect& aRect,const TInt aRounding) const
    {
	// left
	aGc.DrawLine(TPoint(aRect.iTl.iX,aRect.iTl.iY+aRounding),TPoint(aRect.iTl.iX,aRect.iBr.iY-aRounding));
	// top left corner
	DrawRoundedCorner(aGc,TPoint(aRect.iTl.iX,aRect.iTl.iY+aRounding),aRounding,ETrue,ETrue);
	// top
	aGc.DrawLine(TPoint(aRect.iTl.iX+aRounding,aRect.iTl.iY),TPoint(aRect.iBr.iX-aRounding,aRect.iTl.iY));
	}

//
// Draws the bottom right portion of the one pixel border frame
//
void TGulBorder::DrawBottomRight(CGraphicsContext& aGc,const TRect& aRect,TRgb aColor,const TInt aRounding) const
    {
	TInt xOffset=0;
	TInt yOffset=0;

	if ((InternalType()&EFlat) || (InternalType()&ERaised))
		xOffset=1;

	if(InternalType()&ESunken)
		yOffset=1;

	if((InternalType()&EFlat) && (InternalType()&EThreeStep))
		{
		xOffset=1;
		yOffset=1;
		}

	aGc.SetPenColor(aColor);

	if (aRounding>0)
		DrawRoundedBottomRight(aGc,aRect,aRounding);
	else
		{
		// right
		aGc.DrawLine(TPoint(aRect.iBr.iX-1,aRect.iBr.iY-1),TPoint(aRect.iBr.iX-1,aRect.iTl.iY-1+yOffset));
		// bottom
		aGc.DrawLine(TPoint(aRect.iBr.iX-1,aRect.iBr.iY-1),TPoint(aRect.iTl.iX-1+xOffset,aRect.iBr.iY-1));
		}
	}

//
// Draws a rounded off version of the bottom right portion of the one pixel border frame
//
void TGulBorder::DrawRoundedBottomRight(CGraphicsContext& aGc,const TRect& aRect,const TInt aRounding) const
    {
	// top right corner
	DrawRoundedCorner(aGc,TPoint(aRect.iBr.iX-1,aRect.iTl.iY+aRounding),aRounding,ETrue,EFalse);	
	// right
	aGc.DrawLine(TPoint(aRect.iBr.iX-1,aRect.iBr.iY-1-aRounding),TPoint(aRect.iBr.iX-1,aRect.iTl.iY-1+aRounding));
	// bottom right corner
	DrawRoundedCorner(aGc,TPoint(aRect.iBr.iX-1,aRect.iBr.iY-1-aRounding),aRounding,EFalse,EFalse);
	// bottom
	aGc.DrawLine(TPoint(aRect.iBr.iX-1-aRounding,aRect.iBr.iY-1),TPoint(aRect.iTl.iX-1+aRounding,aRect.iBr.iY-1));
	// bottom left corner
	DrawRoundedCorner(aGc,TPoint(aRect.iTl.iX,aRect.iBr.iY-1-aRounding),aRounding,EFalse,ETrue);
	}

//
// Implements the rounded corner drawing algorithm
// Rounded corners are convex, nestable, symmetric, favour drawing in two pixel steps and favour filling outer pixels 
// Corners are drawn from aStart, breaching a gap of size (aRoundedLength,aRoundedLength)
// and use aUp and aRight to determine direction
// Drawing is done vertically from the start and horizontaly from the end till they meet in the middle.
//
void TGulBorder::DrawRoundedCorner(CGraphicsContext& aGc,const TPoint& aStart,const TInt aRoundedLength, const TBool aUp, const TBool aRight) const
	{
	if(aRoundedLength<2)
		return;

	TPoint end=aStart;
	end.iX += aRight ? aRoundedLength : -aRoundedLength;
	end.iY += aUp ? -aRoundedLength : aRoundedLength;

	// draw from start
	aGc.MoveTo(aStart);
	TInt steps=aRoundedLength/3;
	TInt count=0;
	while(count<steps)
		{
		aRight ? aGc.MoveBy(TPoint(1,0)) : aGc.MoveBy(TPoint(-1,0));
		aUp ? aGc.MoveBy(TPoint(0,-1)) : aGc.MoveBy(TPoint(0,1));		
		aUp ? aGc.DrawLineBy(TPoint(0,-2)) : aGc.DrawLineBy(TPoint(0,2));
		aUp ? aGc.MoveBy(TPoint(0,1)) : aGc.MoveBy(TPoint(0,-1));
		count++;
		}

	// draw from end
	aGc.MoveTo(end);
	count=0;
	while(count<steps)
		{
		aUp ? aGc.MoveBy(TPoint(0,1)) : aGc.MoveBy(TPoint(0,-1));
		aRight ? aGc.MoveBy(TPoint(-1,0)) : aGc.MoveBy(TPoint(1,0));
		aRight ? aGc.DrawLineBy(TPoint(-2,0)) : aGc.DrawLineBy(TPoint(2,0));
		aRight ? aGc.MoveBy(TPoint(1,0)) : aGc.MoveBy(TPoint(-1,0));
		count++;
		}
	
	// draw mid point if necessary
	if(aRoundedLength%3==2)
		{
		aUp ? aGc.MoveBy(TPoint(0,1)) : aGc.MoveBy(TPoint(0,-1));
		aRight ? aGc.MoveBy(TPoint(-1,0)) : aGc.MoveBy(TPoint(1,0));
		aRight ? aGc.DrawLineBy(TPoint(-1,0)) : aGc.DrawLineBy(TPoint(1,0));
		}
	}

//
// Returns the thickness of the part of the border which is colored in the mid-tone
// highlights and lowlights. In general, this is not the same as the size of the border
// margins.
EXPORT_C TInt TGulBorder::Thickness() const
/**
@publishedPartner
@deprecated
*/
	{
	TInt thickness=0;

	if (InternalType()&EAddOnePixel)
		thickness++;

	if (InternalType()&EAddTwoPixels)
		thickness+=2;

	if (InternalType()&EAddFourPixels)
		thickness+=4;

	return thickness;
	}

//
// Returns the number of pixels which will be chipped of the corners of a border rectangle
// to be joined by an rounding arc. The rounding is determined by the border type.
//
EXPORT_C TInt TGulBorder::Rounding() const
/**
@internalComponent
@released
*/
	{
	TInt rounding=0;
	
	if (InternalType()&EAddOneRoundingPixel)
		rounding++;

	if (InternalType()&EAddTwoRoundingPixels)
		rounding+=2;

	if (InternalType()&EAddFourRoundingPixels)
		rounding+=4;

	return rounding;
	}


//
// Returns the width of the smallest margin possible, given the rounding of the border rectangle.
// This is a simple mapping for the rounding range 0-7 and the current drawing algorithm,
//
TInt TGulBorder::RoundingMargin(const TInt aRoundedLength) const
	{
	TInt roundingMargin=0;

	if (aRoundedLength>4)
		roundingMargin=2;
	else if (aRoundedLength>1)
		roundingMargin=1;

	return roundingMargin;
	}


inline TInt TGulBorder::InternalType() const
	{
	return (iType>>KBorderShift);
	}


