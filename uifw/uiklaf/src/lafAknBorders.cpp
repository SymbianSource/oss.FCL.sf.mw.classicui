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


#include <aknborders.h>
#include "lafAknBorders.h"
#include <gulutil.h>
#include <AknUtils.h>

const TInt KMaxBorderBits = 3;


struct SBorderBit
	{
	enum TSide 
		{ 
		ELeft = 1,
		ERight = 2,
		ETop = 4,
		EBottom = 8,
		EBottomRight = 10,
		EAll = 15
		};

//	TInt iColorIndex;
	TInt iColor;
	TInt iSides;
	TInt iLeftIndent;		// relative to overall rectangle iTl.iX
	TInt iTopIndent;		// relative to overall rectangle iTl.iY
	TInt iWidthDiff;		// relative to overall rectangle width
	TInt iHeightDiff;		// relative to overall rectangle height

	void Draw(CGraphicsContext& aGc, const TRect& aRect) const;
	TRect Rect(const TRect& aParent) const;
	void DrawSide(CGraphicsContext& aGc, const TRect& aRect, TInt aSide) const;
	};


struct SBorderSpec
	{
	TMargins iMargins;					// margins between overall rect and inside area
	TInt iNumBits;						// number of sub parts
	SBorderBit iBits[KMaxBorderBits];	// array of sub parts

	void Draw(CGraphicsContext& aGc,const TRect& aRect) const;
	void ClearMargins(CGraphicsContext& aGc,const TRect& aRect) const;
	};

// Table derived from Series 60 LAF v0.8, with changes for apparent bugs (marked **)
const SBorderSpec gBorderSpecs[] =	// indexed from bordertype - EAknBorderNotePopup
	{
		// EAknBorderNotePopup	- Table 151 Eur. LAF 3.2
		{
			{3, 5, 3, 7},	// margins (l,r,t,b)
			3,				// number of sub parts
			{
				{0x999999, SBorderBit::EBottomRight, 6, 6, 8, 10},		// 2nd shadow
				{0x777777, SBorderBit::EBottomRight, 4, 4, 7, 9},		// 1st shadow
				{0x000000, SBorderBit::EAll,         2, 2, 6, 8}		// outline
			}
		},

		// EAknBorderMenuPopup
		{
			{3, 5, 3, 3},	// margins	** table 164.5 H = p-6
			3,				// number of sub parts
			{
				{0x999999, SBorderBit::EBottomRight, 6, 6, 8, 6},		// 2nd shadow
				{0x777777, SBorderBit::EBottomRight, 4, 4, 7, 5},		// 1st shadow
				{0x000000, SBorderBit::EAll,         2, 2, 6, 4}		// outline
			}
		},

		// EAknBorderMenuSubmenuPopup
		{
			{2, 3, 2, 3},	// margins  ** table 170.5 W,H = p-5
			2,				// number of sub parts
			{
				{0x777777, SBorderBit::EBottomRight, 3, 3, 4, 4},		// 1st shadow
				{0x000000, SBorderBit::EAll,         1, 1, 3, 3}		// outline
			}
		},

		// EAknBorderNotificationPopup  ** table 190.1 H = 61?
		{
			{3, 5, 9, 3},	// margins
			3,				// number of sub parts
			{
				{0x999999, SBorderBit::EBottomRight, 6, 12, 8, 12},		// 2nd shadow
				{0x777777, SBorderBit::EBottomRight, 4, 10, 7, 11},		// 1st shadow
				{0x000000, SBorderBit::EAll,         2, 8, 6, 10}		// outline
			}
		},

		// EAknBorderGroupedNotificationsPopup
		{
			{3, 5, 9, 7},	// margins
			3,				// number of sub parts
			{
				{0x999999, SBorderBit::EBottomRight, 6, 12, 8, 16},		// 2nd shadow  ** table 194.2 l = 6
				{0x777777, SBorderBit::EBottomRight, 4, 10, 7, 15},		// 1st shadow
				{0x000000, SBorderBit::EAll,         2, 8, 6, 14}		// outline
			}
		},

		// EAknBorderCharacterSelectionPopup
		{
			{3, 4, 3, 7},	// margins
			3,				// number of sub parts
			{
				{0x999999, SBorderBit::EBottomRight, 6, 6, 7, 10},		// 2nd shadow
				{0x777777, SBorderBit::EBottomRight, 4, 4, 6, 9},		// 1st shadow
				{0x000000, SBorderBit::EAll,         2, 2, 5, 8}		// outline
			}
		},

	};


void LafAknBorders::DrawLogicalBorder(const TGulBorder& aBorder,CGraphicsContext& aGc,const TRect& aRect,const TGulBorder::TColors& /*aBorderColors*/)
	{
	TInt type = aBorder.Type();
	ASSERT(AknBorderId::EAknBorderNotePopup <= type && type < AknBorderId::EAknBorderMax);
	switch (type)
	    {
	    case AknBorderId::EAknBorderPopups:
			{
			// from popup_menu_window/LAF specification
			TInt height = aRect.Size().iHeight;
			TAknLayoutRect cover, second, first, outline, inside;
			cover.LayoutRect(  aRect,   0, 0, 0, ELayoutEmpty, ELayoutEmpty, 176, height);
			second.LayoutRect( aRect,  86, 6, 6, ELayoutEmpty, ELayoutEmpty, 168, height-6);
			first.LayoutRect(  aRect, 221, 4, 4, ELayoutEmpty, ELayoutEmpty, 169, height-4);
			outline.LayoutRect(aRect, 215, 2, 2, ELayoutEmpty, ELayoutEmpty, 170, height-3);
			inside.LayoutRect( aRect,   0, 3, 3, ELayoutEmpty, ELayoutEmpty, 168, height-4);
			AknDraw::DrawWindowShadow(STATIC_CAST(CWindowGc&,aGc), cover, second, first, outline, inside);		
			}
			break;
	    case AknBorderId::EAknBorderPopupsWithHeading:
			{
			// popup menu with heading window graphics
			TInt height = aRect.Size().iHeight;
			TAknLayoutRect cover, second, first, outline, inside;
			cover.LayoutRect(  aRect,   0, 0, 0, ELayoutEmpty, ELayoutEmpty, 176, height+23);
			second.LayoutRect( aRect,  86, 6, 6, ELayoutEmpty, ELayoutEmpty, 168, height+13);
			first.LayoutRect(  aRect, 221, 4, 4, ELayoutEmpty, ELayoutEmpty, 169, height+14);
			outline.LayoutRect(aRect, 215, 2, 2, ELayoutEmpty, ELayoutEmpty, 170, height+15);
			inside.LayoutRect( aRect,   0, 3, 3, ELayoutEmpty, ELayoutEmpty, 168, height+13);
			AknDraw::DrawWindowShadow(STATIC_CAST(CWindowGc&,aGc), cover, second, first, outline, inside);		
			}
	    default:
			TInt index = type - AknBorderId::EAknBorderNotePopup;
			if (index >= 0 && index < sizeof(gBorderSpecs)/sizeof(SBorderSpec))
			    {
                gBorderSpecs[index].Draw(aGc, aRect);
			    }
	    }
	}

TMargins LafAknBorders::LogicalBorderMargins(const TGulBorder& aBorder)
	{
    TMargins m;
    m.iTop = 0;
    m.iLeft = 0;
    m.iRight = 0;
    m.iBottom = 0;
    
	TInt type = aBorder.Type();
	ASSERT(AknBorderId::EAknBorderNotePopup <= type && type < AknBorderId::EAknBorderMax);
	
	if (type >= AknBorderId::EAknBorderNotePopup && type < AknBorderId::EAknBorderPopups)
	    {
        TInt index = type - AknBorderId::EAknBorderNotePopup;
        return gBorderSpecs[index].iMargins;
	    }
	
	// EAknBorderPopupsWithHeading and EAknBorderPopups return zeros.
	return m;	
	}


void SBorderBit::Draw(CGraphicsContext& aGc, const TRect& aRect) const
	{
	aGc.SetPenStyle(CGraphicsContext::ESolidPen);
	aGc.SetPenColor(TRgb(iColor));

	TRect rect = Rect(aRect);
	rect.iBr -= TPoint(1,1);	// convert to inclusive rect
	DrawSide(aGc, rect, iSides & ELeft);
	DrawSide(aGc, rect, iSides & EBottom);
	DrawSide(aGc, rect, iSides & ERight);
	DrawSide(aGc, rect, iSides & ETop);
	}

void SBorderBit::DrawSide(CGraphicsContext& aGc, const TRect& aRect, TInt aSide) const
	{
	TPoint start;
	TPoint end;

	switch (aSide)
		{
		case ELeft:
			start = aRect.iTl;
			end = TPoint(aRect.iTl.iX, aRect.iBr.iY);
			end.iY++;
			break;
		
		case ERight:
			start = aRect.iBr;
			end = TPoint(aRect.iBr.iX, aRect.iTl.iY);
			end.iY--;
			break;
		
		case ETop:
			start = TPoint(aRect.iBr.iX, aRect.iTl.iY);
			end = aRect.iTl;
			end.iX--;
			break;
		
		case EBottom:
			start = TPoint(aRect.iTl.iX, aRect.iBr.iY);
			end = aRect.iBr;
			end.iX++;
			break;

		default:
			return;
		}

	aGc.DrawLine(start, end);
	}

TRect SBorderBit::Rect(const TRect& aParent) const
	{
	TRect rect = aParent;
	rect.Move(iLeftIndent, iTopIndent);
	rect.iBr -= TPoint(iWidthDiff, iHeightDiff);
	return rect;
	}


void SBorderSpec::Draw(CGraphicsContext& aGc,const TRect& aRect) const
	{
	ClearMargins(aGc, aRect);
	for (TInt ii=0; ii<iNumBits; ii++)
		iBits[ii].Draw(aGc, aRect);
	}

void SBorderSpec::ClearMargins(CGraphicsContext& aGc,const TRect& aRect) const
	{
	// This blanks the entire margin space, so may cause flicker
	// more cunning margin clearers may be considered if this is a problem

	TRect inside = aRect;
	inside.iTl.iX += iMargins.iLeft;
	inside.iTl.iY += iMargins.iTop;
	inside.iBr.iX -= iMargins.iRight;
	inside.iBr.iY -= iMargins.iBottom;

	aGc.SetBrushColor(KRgbWhite);
	DrawUtils::ClearBetweenRects(aGc, aRect, inside);
	}

