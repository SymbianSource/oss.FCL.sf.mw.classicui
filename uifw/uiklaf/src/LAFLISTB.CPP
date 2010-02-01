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

#include "lafstd.h"
//#include "lafccten.h"  < This file doesn't exist any more.  In fact LafListB isn't used in uikon any more
#include "laflistb.h"

const TInt KLafListBoxBackgroundColor			=15;	// later, this will be a data member of the listbox  
const TInt KLafListBoxItemVGap					=6;		// to allow a box to be drawn around each item
const TInt KLafListBoxPointerRepeatInterval		=100;	// in micro seconds

/*The decision on whether or not to use the following 4 laf values is not 
made here.  Values >= 0 are appropriate (but obviously not too large, such as to
cause overlapping margins in the listbox).*/
/* SERIES 60 LAF */
const TInt KLafListBoxTopMargin					=0;
const TInt KLafListBoxBottomMargin				=0;
const TInt KLafListBoxLeftMargin				=0;
const TInt KLafListBoxRightMargin				=0;
/* END OF SERIES 60 LAF */
const TInt KInnerGutter							=0;		// gutter at the left of textual list items, >= 0 is sensible, 0 turns it off

/*Important display parameters (only) for popout listboxes*/
const TInt KLafListBoxMaxHeightInNumOfItems		=KLafListboxNoMaxCellWidth;				// >= 1 is sensible, KLafListboxNoMaxCellWidth value turns it off
const TInt KLafListBoxMaxCellWidthInNumOfPixels =KLafListboxNoMaxHeightInNumOfItems;	// >= 20 is sensible, KLafListboxNoMaxHeightInNumOfItems value turns it off

EXPORT_C TBool LafListbox::FadeBehind()
	{
	return EFalse;
	}

/**
 * Gets the default border for the matched control in aBorder. Called from the constructor of the matched control.
 */
EXPORT_C void LafListbox::GetDefaultBorder(TGulBorder& aBorder)
	{
	aBorder=TGulBorder(TGulBorder::ENone);
	}

/**
 * Gets the set of border colors for the matched control in aBorderColors. The RGB values of the colors obtained
 * may depend on the the display mode aMode, the environment color list aColorList and the instance of the
 * matched control aMatchedControl. Called by the matched control from its Draw() method and passed on to the
 * Draw() method of TGulBorder. 
 */
EXPORT_C void LafListbox::GetBorderColors(TGulBorder::TColors& aBorderColors, TDisplayMode aDisplayMode, const CColorList& aColorList, const CCoeControl& aMatchedControl)
	{
	ColorUtils::GetRgbDerivedBorderColors( aBorderColors,
			ControlColor(aColorList,aMatchedControl,EColorControlSurroundBackground), aDisplayMode );
	}

/**
 * Gets the default border for the matched control in aBorder. Called from the constructor of the matched control.
 */
EXPORT_C void LafListbox::GetDefaultPopoutBorder(TGulBorder& aBorder)
	{
	aBorder=TGulBorder(TGulBorder::EThickDeepRaisedWithOutline);
	}

/**
 * Gets the set of border colors for the matched control in aBorderColors. The RGB values of the colors obtained
 * may depend on the the display mode aMode, the environment color list aColorList and the instance of the
 * matched control aMatchedControl. Called by the matched control from its Draw() method and passed on to the
 * Draw() method of TGulBorder. 
 */
EXPORT_C void LafListbox::GetPopoutBorderColors(TGulBorder::TColors& aBorderColors, TDisplayMode aDisplayMode, const CColorList& aColorList, const CCoeControl& aMatchedControl)
	{
	ColorUtils::GetRgbDerivedBorderColors( aBorderColors,
			ControlColor(aColorList,aMatchedControl,EColorControlBackground), aDisplayMode );
	}

//INCLUDE THE FOLLOWING SECTION IF YOU WANT TO USE AN ELLIPSIS (IE.QUARTZ) 
//BUT DON'T INCLUDE IT IF YOU AREN'T USING ELLIPSIS TRUNCATION ^ELLIPSIS^
/*
LOCAL_C TBool DrawFullItemSegment(const TDesC& aDes,TRect& aRect,TInt aLeftXOfRect,
									TInt aRightXOfRect,TInt& aWidthLeftToFitInto,
									CWindowGc& aGc,const CFont& aFont,const TInt aBaseLineOffset,
									TFontUnderline aUnderlineStyle)
	{
	if(aDes.Length() == aFont.TextCount(aDes,aWidthLeftToFitInto))
		{
		aWidthLeftToFitInto -= aFont.TextWidthInPixels(aDes);
		aGc.UseFont(&aFont);
		aGc.SetUnderlineStyle(aUnderlineStyle);
		aRect.iTl.iX = aLeftXOfRect;
		aRect.iBr.iX = aRightXOfRect;
		aGc.DrawText(aDes,aRect,aBaseLineOffset);
		return true;
		}
	else
		{
		return false;
		}
	}

LOCAL_C void DrawPartialItemSegment(const TDesC& aDes,TRect& aRect,
										TInt aLeftXOfRect,TInt& aWidthLeftToFitInto,
										CWindowGc& aGc,const CFont& aFont,const TInt aBaseLineOffset,
										TFontUnderline aUnderlineStyle,TInt aRightXOfRect,
										const TDesC& aEllipsisDes,const CFont& aSecondFont,
										TBool aUseSecondFont)
	{
	aGc.UseFont(&aFont);
	aGc.SetUnderlineStyle(aUnderlineStyle);
	aRect.iTl.iX = aLeftXOfRect;
	aRect.iBr.iX = aRect.iTl.iX + aFont.TextWidthInPixels(aDes.Left(aFont.TextCount(aDes,aWidthLeftToFitInto)));
	aGc.DrawText(aDes.Left(aFont.TextCount(aDes,aWidthLeftToFitInto)),aRect,aBaseLineOffset);

	// the following lines add an ellipsis onto the end of the text segment
	if(aUseSecondFont) // for the case when you must switch fonts
		{
		aGc.UseFont(&aSecondFont);
		}
	aGc.SetUnderlineStyle(EUnderlineOff);
	aRect.iTl.iX = aRect.iBr.iX;
	aRect.iBr.iX = aRightXOfRect;
	aGc.DrawText(aEllipsisDes,aRect,aBaseLineOffset);
	}
*/

EXPORT_C void LafListbox::DrawNormalText(const TDesC& aDes,const CFont& /*aFont*/,CWindowGc& aGc,
										 const TRect& aItemTextRect,const TInt aBaseLineOffset,
										 const CGraphicsContext::TTextAlign aAlign)
	{//static
	TBuf<256> temp = aDes;
	//INCLUDE THE FOLLOWING 2 LINES IF YOU WANT TO USE AN ELLIPSIS (IE.QUARTZ) 
	//BUT DON'T INCLUDE IT IF YOU AREN'T USING ELLIPSIS TRUNCATION ^ELLIPSIS^
	//ALSO NEED TO 'UNCOMMENT-OUT' THE AFONT PARAMETER IN THE SIGNATURE
	//TInt visibleTextWidth = aItemTextRect.Width() - InnerGutter();
	//TextUtils::ClipToFit(temp,aFont,visibleTextWidth);
	aGc.DrawText(temp,aItemTextRect,aBaseLineOffset,aAlign,InnerGutter());
	}

EXPORT_C void LafListbox::DrawSearchText(const TRect& aItemTextRect,
							CWindowGc& aGc,const CFont& aItemFont,const CFont& aBoldFont,
							const TDesC& aItemText,const TInt aStrPos,const TInt aStrLen,
							const TInt aBaseLineOffset,const CGraphicsContext::TTextAlign aAlign)
	{//static
	//INCLUDE THE FOLLOWING SECTION IF YOU WANT TO USE AN ELLIPSIS (IE.QUARTZ) 
	//BUT DON'T INCLUDE IT IF YOU AREN'T USING ELLIPSIS TRUNCATION ^ELLIPSIS^
	//ALSO AALIGN PARAMETER SHOULD BE COMMENTED OUT WHEN USING ELLIPSIS
	/*
	TRect rectWithoutInnerGutter = aItemTextRect;	// copied for modification
	if(LafListbox::InnerGutter() != 0)
		{
		rectWithoutInnerGutter.iTl.iX += LafListbox::InnerGutter();
		TRect innerGutterRect(aItemTextRect.iTl.iX,aItemTextRect.iTl.iY,
			aItemTextRect.iTl.iX + LafListbox::InnerGutter(),aItemTextRect.iBr.iY);
		aGc.DrawRect(innerGutterRect);
		}
	TInt maxWidthInPixels = (rectWithoutInnerGutter.Width());

	const TPtrC headBuf = TPtrC(aItemText.Left(aStrPos));
	const TPtrC strBuf = TPtrC(aItemText.Mid(aStrPos,aStrLen));
	const TPtrC tailBuf = TPtrC(aItemText.Right(aItemText.Length()-aStrPos-aStrLen));

	const TInt headLen = aItemFont.TextWidthInPixels(headBuf);
	const TInt stringLen  = aBoldFont.TextWidthInPixels(strBuf);
	const TInt tailLen = aItemFont.TextWidthInPixels(tailBuf);
	const TInt theWidthOfTextSegment = headLen + stringLen + tailLen;

	TRect rect = rectWithoutInnerGutter;

	if (theWidthOfTextSegment < maxWidthInPixels)	// ... or the text segment falls within the rect bounds anyway
		{

		// draw item head up to search string
		rect.iBr.iX = rect.iTl.iX + headLen;
		aGc.DrawText(headBuf, rect, aBaseLineOffset);

		// draw item tail after the search string
		rect.iTl.iX = rect.iBr.iX + stringLen;
		rect.iBr.iX = rectWithoutInnerGutter.iBr.iX;
		aGc.DrawText(tailBuf, rect, aBaseLineOffset);

	    // change font and set underlining on
		aGc.UseFont(&aBoldFont);
		aGc.SetUnderlineStyle(EUnderlineOn);

		// draw the search string part of the item with different font
		rect.iBr.iX = rect.iTl.iX;
		rect.iTl.iX = rect.iBr.iX - stringLen;
		aGc.DrawText(strBuf, rect, aBaseLineOffset);

		}
	else	// must add in ellipsis truncation along with string font
		{
		TBuf<1> ellipsis;  // need it to calculate the width of ellipsis
		ellipsis.Append(0x2026);
		TInt ellipsisWidth = aItemFont.TextWidthInPixels(ellipsis); // width of ellipsis of next segment
		TInt widthLeftToFitInto = maxWidthInPixels - ellipsisWidth;

		if(DrawFullItemSegment(headBuf,rect,rect.iTl.iX,rect.iTl.iX + headLen,
			widthLeftToFitInto,aGc,aItemFont,aBaseLineOffset,EUnderlineOff))
			{
			if(DrawFullItemSegment(strBuf,rect,rect.iBr.iX,rect.iBr.iX + stringLen,
				widthLeftToFitInto,aGc,aBoldFont,aBaseLineOffset,EUnderlineOn))
				{
				if(DrawFullItemSegment(tailBuf,rect,rect.iBr.iX,rectWithoutInnerGutter.iBr.iX,
					widthLeftToFitInto,aGc,aItemFont,aBaseLineOffset,EUnderlineOff))
					{
					}
				else
					{
					DrawPartialItemSegment(tailBuf,rect,rect.iBr.iX,widthLeftToFitInto,
											aGc,aItemFont,aBaseLineOffset,EUnderlineOff,
											rectWithoutInnerGutter.iBr.iX,ellipsis,
											aBoldFont,EFalse);
					}
				}
				else
				{
				DrawPartialItemSegment(strBuf,rect,rect.iBr.iX,widthLeftToFitInto,
										aGc,aBoldFont,aBaseLineOffset,EUnderlineOn,
										rectWithoutInnerGutter.iBr.iX,ellipsis,
										aItemFont,ETrue);							
				}
			}
		else
			{
			DrawPartialItemSegment(headBuf,rect,rect.iTl.iX,widthLeftToFitInto,
									aGc,aItemFont,aBaseLineOffset,EUnderlineOff,
									rectWithoutInnerGutter.iBr.iX,ellipsis,
									aBoldFont,ETrue);
			}
		}
	*/

	//INCLUDE THE FOLLOWING SECTION IF YOU DON'T WANT TO USE AN ELLIPSIS
	//BUT DO INCLUDE IT IF YOU ARE USING ELLIPSIS TRUNCATION ^ELLIPSIS^

	const TPtrC textHead = TPtrC(aItemText.Left(aStrPos));
	const TPtrC searchStr= TPtrC(aItemText.Mid(aStrPos,aStrLen));
	const TPtrC textTail = TPtrC(aItemText.Right(aItemText.Length()-aStrPos-aStrLen));

	const TInt headLen = aItemFont.TextWidthInPixels(textHead);
	const TInt strLen  = aBoldFont.TextWidthInPixels(searchStr);
	const TInt tailLen = aItemFont.TextWidthInPixels(textTail);

	// adjust text alignment by drawing empty rect before text if necessary
	TRect rect = aItemTextRect;
	const TInt textLen = headLen + strLen + tailLen;
	TInt emptyLen = rect.Width() - textLen;
	if ((aAlign==CGraphicsContext::ELeft) || (emptyLen<=0))
		emptyLen = 0;
	else
		{
		if (aAlign==CGraphicsContext::ECenter) emptyLen = (emptyLen>>1);
		//else if (aAlign=ERight) emptyLen = emptyLen;
		}

	// draw item head up to search string
	rect.iBr.iX = rect.iTl.iX + emptyLen + headLen;
	aGc.DrawText( textHead, rect, aBaseLineOffset, CGraphicsContext::ERight );

	// draw item tail after the search string
	rect.iTl.iX = rect.iBr.iX + strLen;
	rect.iBr.iX = aItemTextRect.iBr.iX;
	aGc.DrawText( textTail, rect, aBaseLineOffset );

    // change font and set undelining on
	aGc.UseFont(&aBoldFont);
    aGc.SetUnderlineStyle(EUnderlineOn);

	// draw the search string part of the item with different font
	rect.iBr.iX = rect.iTl.iX;
	rect.iTl.iX = rect.iBr.iX - strLen;
	aGc.DrawText( searchStr, rect, aBaseLineOffset );
	}

EXPORT_C TInt LafListbox::ItemWidth(TInt aViewRectWidth, TInt aDataWidth)
	{
	//INCLUDE THE FOLLOWING LINE IF YOU WANT TO USE AN ELLIPSIS (IE.QUARTZ), OTHERWISE DON'T ^ELLIPSIS^
	//return aViewRectWidth;
	//INCLUDE THE FOLLOWING LINE IF YOU DON'T WANT TO USE AN ELLIPSIS, OTHERWISE DON'T ^ELLIPSIS^
	return Max(aViewRectWidth, aDataWidth);
	}

EXPORT_C TInt LafListbox::Constant(TConstantType aType)
	{ // static
	switch (aType)
		{
	case EBackgroundColor:
		return KLafListBoxBackgroundColor;
	case EItemVGap:
		return KLafListBoxItemVGap;
	case EPointerRepeatInterval:
		return KLafListBoxPointerRepeatInterval;
	case ETopMargin:
		return KLafListBoxTopMargin;
	case EBottomMargin:
		return KLafListBoxBottomMargin;
	case ELeftMargin:
		return KLafListBoxLeftMargin;
	case ERightMargin:
		return KLafListBoxRightMargin;
	case EMaxHeightInNumOfItems:
		return KLafListBoxMaxHeightInNumOfItems;
	case EMaxCellWidthInNumOfPixels:
		return KLafListBoxMaxCellWidthInNumOfPixels;
	case EInnerGutter:
		return KInnerGutter;
	default:
		break;
		// Panic - unknown type requested
		}
	return 0; // will never reach here	
	}

EXPORT_C void LafListbox::DrawFrame(CWindowGc& /*aGc*/,const TRect& /*aRect*/,const TInt /*aFlags*/)
	{ // static
	}

/**
 * Returns the default flags for the scroll bar for orientation aOrientation.
 * Called when the matched control creates its scroll bar frame..
 */
EXPORT_C TInt LafListbox::DefaultScrollBarFlags(TInt /*aOrientation*/)
	{
	return 0;
	}

/**
 * Gets the default attributes for the scroll bar for orientation aOrientation in aAttributes.
 * Called when the matched control creates its scroll bar frame..
 */
EXPORT_C void LafListbox::GetDefaultScrollBarAttributes(TInt /*aOrientation*/, LafScrollBarFrame::TScrollBarAttributes& aAttributes)
	{
	aAttributes = LafScrollBarFrame::TScrollBarAttributes();
	}
