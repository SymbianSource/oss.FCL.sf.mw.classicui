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


#include "LAFMENUP.H"
#include <eiksfont.h>
#include <gulfont.h>
#include <gulicon.h>
#include <gulutil.h>
#include <coecntrl.h>
#include <coeinput.h>

#include <avkon.hrh>
#include "uikon.hrh"

#include "LAFSCRLB.H"
#include "LAFSTD.H"
#include "lafcommn.h"


const TInt KLafMenuItemRadio = (EEikMenuItemRadioStart|EEikMenuItemRadioMiddle|EEikMenuItemRadioEnd);

// Margin Values for the menu pane
const TInt KLafLeftMargin	= 2; // it is used to be KLafLeftHighlightGap
const TInt KLafRightMargin	= 2; // it is used to be KLafRightHighlightGap
const TInt KLafTopMargin	= 2; // it is used to be KLafTopHighlightGap
const TInt KLafBottomMargin	= 2; // it is used to be KLafBottomHighlightGap

// Margin Values for the cascade menu
const TInt KLafCascadeLeftMargin	= KLafLeftMargin;
const TInt KLafCascadeRightMargin	= KLafRightMargin;
const TInt KLafCascadeTopMargin		= KLafTopMargin;
const TInt KLafCascadeBottomMargin	= KLafBottomMargin;

// Margin Values for the scroll bar
const TInt KLafTopScrollBarMargin = 0;		//TopGapForArrowHead	=10;
const TInt KLafBottomScrollBarMargin = 0;	//KLafBottomGapForArrowHead=10;
const TInt KLafLeftScrollBarMargin = 0;
const TInt KLafRightScrollBarMargin = 0;

// These values are added to font height. They do not have any effect if the icon height is bigger.
const TInt KLafMenuPaneTextTopSpace	= 3;
const TInt KLafMenuPaneTextBottomSpace = 3;

// Separator
const TInt KLafMenuPaneSeparatorMargin = 4; // offset from the margin for the seperator
const TInt KLafMenuSeparatorYOffset = 2;

//	Left Adornment width
const TInt KLafLeftAdornmentSpace = 8;
// Pre and Post adornment widths
const TInt KLafPreLeftAdornmentSpace = 3;
const TInt KLafPostLeftAdornmentSpace = 3;


//	Right Adornment width
const TInt KLafRightAdornmentSpace = 10;
// Pre and Post adornment widths
const TInt KLafPreRightAdornmentSpace = 3; // it can be used as gap between hotkey and cascade symbol.
const TInt KLafPostRightAdornmentSpace = 3;

const TInt KLafSpaceBetweenTextAndHotkey	= 6;

const TInt KLafMenuPaneDefaultShadowHeight			= 3;
const TInt KLafOffsetBetweenMenuPaneAndMenuPaneTitle= 0;

// Pre and Post widths around the Icon
const TInt KLafPreIconSpace = 0;
const TInt KLafPostIconSpace = 0;

const TInt KLafExtraBaselineOffset	=1;
const TInt KLafMenuPaneSeparatorAfterSpace=6;
const TInt KLafMenuCascadeOverlap=8; // + value reduces the gap between the cascade menu and its owner



//
// Class LafMenuPane::TMenuPaneAttributes
//

EXPORT_C LafMenuPane::TItemAttributes::TItemAttributes()
	: iBaseLine(0), iFlags(0), iInternalFlags(0), iHeight(0), iHighlightType(SLafMenuPane::ENoHighlight),
	iHPosition(0)
	{
	}

//
// Class LafMenuPane
//


/*
 * Returns the left or right adornment width determined by aItemAttributes internal flags.
 * The internal flags are set so that it is possible to know which adornments the menu pane has and
 * which one, between left and right adornment, has to be taken in consideration in order to evaluate
 * the returning value.
 */
EXPORT_C TInt LafMenuPane::AdornmentSpace(const TItemAttributes& aItemAttributes)
	{
	const TInt& internalFlags = aItemAttributes.iInternalFlags;
	TInt adornment = 0;
	if (internalFlags&EMenuIsLeftAdornment)
		{
		adornment = KLafPreLeftAdornmentSpace + KLafPostLeftAdornmentSpace;
		if (internalFlags&EMenuHasLeftAdornment)
			adornment += KLafLeftAdornmentSpace;
		}
	else
		{
		adornment = KLafPreRightAdornmentSpace + KLafPostRightAdornmentSpace;
		if (internalFlags&EMenuHasRightAdornment)
			adornment += KLafRightAdornmentSpace;
		}
	return adornment;
	}

/**
 * Returns the keypresses menu pane is interested in from a FEP
 */
EXPORT_C TInt LafMenuPane::InputCapabilities()
	{ // static
	return TCoeInputCapabilities::ENavigation;
	}
	
/**
 * Returns ETrue if the first item on a menu pane should be selected by default.
 * Returning EFalse signifies that nothing should be selected initially.
 */
EXPORT_C TBool LafMenuPane::SelectFirstItemOnConstruction()
	{
	return ETrue;
	}
	
EXPORT_C TInt LafMenuPane::DefaultCbaResId()
	{ // static
	return 0;
	}
	
EXPORT_C void LafMenuPane::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList)
	{ // static
	TInt commonAttributes = TCoeColorUse::ENormal|TCoeColorUse::ENeutral;
	TCoeColorUse colorUse;

	colorUse.SetLogicalColor(EColorMenuPaneText);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EActive|TCoeColorUse::ESurrounds|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorMenuPaneBackground);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EActive|TCoeColorUse::ESurrounds|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorMenuPaneTextHighlight);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EActive|TCoeColorUse::EHighlights|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorMenuPaneHighlight);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EActive|TCoeColorUse::EHighlights|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorMenuPaneDimmedTextHighlight);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EDimmed|TCoeColorUse::EHighlights|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorMenuPaneDimmedHighlight);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EDimmed|TCoeColorUse::EHighlights|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorMenuPaneDimmedText);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EDimmed|TCoeColorUse::ESurrounds|commonAttributes);
	aColorUseList.AppendL(colorUse);
	}

/**
 * Returns the keycode to use with menus for the given event.  Intended primarily to allow custom
 * device hardware keys to map to standard Epoc functions.
 *
 * @since App-Framework_6.1
 */ 
EXPORT_C TUint LafMenuPane::MapKeyCode(const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
	{ // static
	return aKeyEvent.iCode;
	}

/**
 * Returns a constant value according to aConstantType.
 *
 * @internal
 */
EXPORT_C TInt LafMenuPane::Constant(TConstantType aConstantType)
	{//static
	TInt retValue = 0;
	switch (aConstantType)
		{
	case EPostRightAdornmentSpace:
		retValue = KLafPostRightAdornmentSpace;
		break;
	case EMenuPaneTextTopSpace:
		retValue = KLafMenuPaneTextTopSpace;
		break;
	case EMenuPaneTextBottomSpace:
		retValue = KLafMenuPaneTextBottomSpace;
		break;
	case ESpaceBetweenTextAndHotkey:
		retValue = KLafSpaceBetweenTextAndHotkey;
		break;
	case EOffsetBetweenMenuPaneAndMenuPaneTitle:
		retValue = KLafOffsetBetweenMenuPaneAndMenuPaneTitle;
		break;
	case EMenuPaneSeparatorMargin:
		retValue = KLafMenuPaneSeparatorMargin;
		break;
	case EShadowHeight:
		retValue = KLafMenuPaneDefaultShadowHeight;
		break;
	case EPreIconSpace:
		retValue = KLafPreIconSpace;
		break;
	case EPostIconSpace:
		retValue = KLafPostIconSpace;
		break;
	case EExtraBaselineOffset:
		retValue = KLafExtraBaselineOffset;
		break;
	case EMenuPaneSeparatorAfterSpace:
		retValue = KLafMenuPaneSeparatorAfterSpace;
		break;
	case EMenuCascadeOverlap:
		retValue = KLafMenuCascadeOverlap;
		break;
	case EMenuSeparatorYOffset:
		retValue = KLafMenuSeparatorYOffset;
		break;
	case ENumberOfItemsInView:
		retValue=-1;
		break;
	default:
		__ASSERT_DEBUG(EFalse, Panic(ELafPanicConstantNotKnown)); // should never be reached
		break;
		}
	return retValue;
	}

/**
 * Returns the font corresponding to aFontType.
 *
 * @internal
 */
EXPORT_C const CFont* LafMenuPane::Font(const MLafEnv& aLafEnv, TFontType aFontType)
	{ // static
	TLogicalFont logicalFont;

	switch (aFontType)
		{
	case EAnnotation:
		logicalFont.iFontId=TUid::Uid(EAknLogicalFontSecondaryFont);
		break;
	case ENormal:
		logicalFont.iFontId=TUid::Uid(EAknLogicalFontPrimaryFont);
		break;
	case ESymbol:
		logicalFont.iFontId=TUid::Uid(EAknLogicalFontSecondaryFont);
		break;
	default:
		__ASSERT_DEBUG(EFalse, Panic(ELafPanicFontIndexOutOfRange)); // should never be reached
		break;
		}

	return aLafEnv.Font(logicalFont);
	}

/**
 * Gets the default border for the matched control in aBorder. Called from the constructor of the matched control.
 */
EXPORT_C void LafMenuPane::GetDefaultBorder(TGulBorder& aBorder)
	{
	aBorder=TGulBorder(TGulBorder::EThickDeepRaisedWithOutline);
	}

/**
 * Gets the set of border colors for the matched control in aBorderColors. The RGB values of the colors obtained
 * may depend on the the display mode, the environment color list and the instance of the
 * matched control aMatchedControl. Called by the matched control from its Draw() method and passed on to the
 * Draw() method of TGulBorder. 
 */
EXPORT_C void LafMenuPane::GetBorderColors(TGulBorder::TColors& aBorderColors, const MLafEnv& aLafEnv, const CCoeControl& aMatchedControl)
	{
	LafCommonUtils::GetRgbDerivedBorderColors( aBorderColors,
			EColorMenuPaneBackground, aLafEnv,aMatchedControl );
	}

/**
 * Returns the default flags for the scroll bar for orientation aOrientation.
 * Called when the matched control creates its scroll bar frame..
 */
EXPORT_C TInt LafMenuPane::DefaultScrollBarFlags(TInt /*aOrientation*/)
	{
	return 0;
	}

/**
 * Draws the joints between menu pane and menu pane title into the graphics
 * context aGc, in the rectangle aRect.
 */
EXPORT_C void LafMenuPane::DrawTitlePaneJoint(const MLafEnv& aLafEnv, const CCoeControl& aMenuPane, CWindowGc& aGc, const CCoeControl* aMenuPaneTitle, const TRect& aInnerRect)
	{
	PrepareGcForDrawingItems(aLafEnv, aMenuPane, aGc);
    aGc.SetPenStyle(CGraphicsContext::ENullPen);
    aGc.DrawRect(aInnerRect);
	if (aMenuPaneTitle)
		{// pane has title, so make sure they are joined up correctly
		const TPoint titlePos = aMenuPaneTitle->Position();
		const TInt width = aMenuPaneTitle->Size().iWidth;
		const TPoint position = aMenuPane.Position();

		// left straight join
		aGc.SetPenStyle(CGraphicsContext::ESolidPen);
		aGc.SetPenColor(aLafEnv.ControlColor(EColorMenuPaneBackground, aMenuPane));
		// get rid of the gray bit of border
		aGc.DrawLine(TPoint(titlePos.iX-position.iX+5,4),TPoint(titlePos.iX-position.iX+width-5,4));
		// get rid of the black bit of border
		aGc.DrawLine(TPoint(titlePos.iX-position.iX+4,0),TPoint(titlePos.iX-position.iX+width-4,0));
		aGc.DrawLine(TPoint(titlePos.iX-position.iX+4,1),TPoint(titlePos.iX-position.iX+width-4,1));

		aGc.DrawLine(TPoint(titlePos.iX-position.iX+5,4),TPoint(titlePos.iX-position.iX+width-5,4));
		aGc.DrawLine(TPoint(titlePos.iX-position.iX+MenuPaneSeparatorMargin() ,0),TPoint(titlePos.iX-position.iX+width-MenuPaneSeparatorMargin(),0));
		aGc.DrawLine(TPoint(titlePos.iX-position.iX+MenuPaneSeparatorMargin() ,1),TPoint(titlePos.iX-position.iX+width-MenuPaneSeparatorMargin(),1));
		aGc.DrawLine(TPoint(titlePos.iX-position.iX+MenuPaneSeparatorMargin() ,2),TPoint(titlePos.iX-position.iX+width-MenuPaneSeparatorMargin(),2));
		aGc.DrawLine(TPoint(titlePos.iX-position.iX+MenuPaneSeparatorMargin() ,3),TPoint(titlePos.iX-position.iX+width-MenuPaneSeparatorMargin(),3));

		// draw in black line seperator
		aGc.SetPenColor(KRgbBlack);
		aGc.DrawLine(TPoint(titlePos.iX-position.iX +MenuPaneSeparatorMargin(),0),TPoint(titlePos.iX-position.iX+width-3-MenuPaneSeparatorMargin(),0));

		TGulBorder::TColors borderColors;
		GetBorderColors(borderColors, aLafEnv, *aMenuPaneTitle);

		aGc.SetPenColor(borderColors.iMidlight);
		aGc.DrawLine(TPoint(titlePos.iX-position.iX+1,0),TPoint(titlePos.iX-position.iX+4,0));
		aGc.DrawLine(TPoint(titlePos.iX-position.iX+1,1),TPoint(titlePos.iX-position.iX+4,1));

		if (aMenuPaneTitle->Rect().iBr.iX==aMenuPane.Rect().iBr.iX)
			{// right straight join
			aGc.SetPenColor(borderColors.iMid);
			aGc.DrawLine(TPoint(aInnerRect.iBr.iX,0),TPoint(aInnerRect.iBr.iX,5));
			aGc.DrawLine(TPoint(aInnerRect.iBr.iX+1,0),TPoint(aInnerRect.iBr.iX+1,4));
			aGc.DrawLine(TPoint(aInnerRect.iBr.iX+2,0),TPoint(aInnerRect.iBr.iX+2,3));
			}
		else
			{// right corner join
			TInt xPos=titlePos.iX-position.iX+width-4;
			aGc.SetPenColor(borderColors.iMid);
			aGc.DrawLine(TPoint(xPos,0),TPoint(xPos,4));
			aGc.DrawLine(TPoint(xPos+1,0),TPoint(xPos+1,3));
			aGc.DrawLine(TPoint(xPos+2,0),TPoint(xPos+2,2));
			}
		}
	}


/**
 * Draws the aHotKeys text into the graphics context aGc, in the rectangle aRect. By defalut the
 * text is right aligned.
 */
EXPORT_C void LafMenuPane::DrawHotKeyText(const MLafEnv& aLafEnv, const CCoeControl& /*aMenuPane*/, CWindowGc& aGc, const TRect& aRect, const TDesC& aHotKeysText, const TItemAttributes& aItemAttributes)
	{
	aGc.UseFont(AnnotationFont(aLafEnv));
// Left alignment
	aGc.DrawText(aHotKeysText, aRect, aItemAttributes.iBaseLine, CGraphicsContext::ELeft,KLafSpaceBetweenTextAndHotkey);
	aGc.UseFont(NormalFont(aLafEnv));
	}

/**
 * Draws the left adornment to the graphics context aGc, in the rectangle aRect. The menu pane
 * flags determines the type of adornment to be drawn.
 */
EXPORT_C void LafMenuPane::DrawLeftAdornment(const MLafEnv& aLafEnv, const CCoeControl& /*aMenuPane*/, CWindowGc& aGc, const TRect& aRect, const TItemAttributes& aItemAttributes)
	{
// Brush the background of the rect.
	aGc.SetPenStyle(CGraphicsContext::ENullPen);
	aGc.DrawRect(aRect);
	aGc.SetPenStyle(CGraphicsContext::ESolidPen);
	const TInt itemFlags = aItemAttributes.iFlags;
	if (itemFlags&EEikMenuItemSymbolOn)
		{
		if (itemFlags&EEikMenuItemCheckBox)
			{
			TRect rect = aRect;
			rect.iTl.iY += aItemAttributes.iBaseLine;
			TBuf<1> buf;
			buf.Append(TChar(ESymFontTick));
			aGc.UseFont(SymbolFont(aLafEnv));
			aGc.SetPenStyle(CGraphicsContext::ESolidPen);
			// as the tick is big, ignore KPreLeftAdornment and steal 1 pixels from left.
			aGc.DrawText(buf,TPoint(rect.iTl.iX-1, rect.iTl.iY));
			aGc.UseFont(NormalFont(aLafEnv));
			}
		else if (itemFlags&KLafMenuItemRadio)
			{
			TUid bmpUid(TUid::Uid(KLafUidEikonOptiVal));
			const CFbsBitmap* bitmap = aLafEnv.Bitmap(bmpUid);
			TSize bitsize = bitmap->SizeInPixels();
			TRect butRect(TPoint(0,0), TPoint(bitsize.iWidth,bitsize.iHeight));
			TInt yoffset = (aRect.Size().iHeight - bitsize.iHeight) / 2;
			TInt xoffset = KLafPreLeftAdornmentSpace;
			TPoint offset(xoffset,yoffset);
			if (aItemAttributes.iHighlightType == SLafMenuPane::EDrawHighlight)
				{
				bmpUid=TUid::Uid(KLafUidEikonOptihVal);
				bitmap = aLafEnv.Bitmap(bmpUid);
				}
			bmpUid=TUid::Uid(KLafUidEikonOptimVal);
			const CFbsBitmap* mask = aLafEnv.Bitmap(bmpUid);
			aGc.BitBltMasked((aRect.iTl+offset), bitmap, butRect, mask,ETrue);
			}
		}
	}

/**
 * Draws the cascade symbol into the graphics context aGc, in the rectangle aRect and sets
 * the pen color depending on whether the menu item is dimmed or focused.
 */
EXPORT_C void LafMenuPane::DrawRightAdornment(const MLafEnv& aLafEnv, const CCoeControl& /*aMenuPane*/, CWindowGc& aGc, const TRect& aRect, const TItemAttributes& aItemAttributes)
	{
	const TInt cascadeSize=Min(KLafRightAdornmentSpace,aItemAttributes.iHeight);

// Brush the background of the rect.
	aGc.SetPenStyle(CGraphicsContext::ENullPen);
	aGc.DrawRect(aRect);
	aGc.SetPenStyle(CGraphicsContext::ESolidPen);
	if (aItemAttributes.iInternalFlags&EMenuIsRightAdornment)
		{
		//Sort out rect for cascade symbol
		TRect cascadeRect=TRect(TPoint(aRect.iBr.iX-cascadeSize-PostRightAdornmentSpace(),aItemAttributes.iHPosition),
					TSize(cascadeSize,aItemAttributes.iHeight));
		cascadeRect.iTl.iY+=((aItemAttributes.iHeight-cascadeSize)/2);
		cascadeRect.iBr.iY-=((aItemAttributes.iHeight-cascadeSize)/2);
		TBuf<1> cascade;
		cascade.Append(TChar(ESymFontMenuCascade));
		aGc.UseFont(SymbolFont(aLafEnv));
		aGc.DrawText(cascade,cascadeRect,cascadeRect.Height(),CGraphicsContext::ERight);
		aGc.UseFont(NormalFont(aLafEnv));
		}
	}

/**
 * Draws a line seperator between two items into the graphics context aGc, in the rectangle aRect.
 */
EXPORT_C void LafMenuPane::DrawSeperator(const MLafEnv& aLafEnv, const CCoeControl& aMenuPane, CWindowGc& aGc, const TRect& aRect, const TItemAttributes& /*aItemAttributes*/)
	{
	aGc.SetPenColor(aLafEnv.ControlColor(EColorMenuPaneText, aMenuPane));
	aGc.DrawLine(aRect.iTl, aRect.iBr);
	}

/**
 * Draws aText into the graphics context aGc, in the rectangle aRect. By default aText is
 * left aligned
 */
EXPORT_C void LafMenuPane::DrawText(const MLafEnv& /*aLafEnv*/, const CCoeControl& /*aMenuPane*/, CWindowGc& aGc, const TRect& aRect, const TDesC& aText, const TItemAttributes& aItemAttributes)
	{
	aGc.DrawText(aText, aRect, aItemAttributes.iBaseLine, CGraphicsContext::ELeft);
	}

/**
 * Returns ETrue when the window behind the menu bar should be faded.
 */
EXPORT_C TBool LafMenuPane::FadeBehind()
	{ // static
	return EFalse;
	}

/**
 * Returns the margins for the cascade menu.
 */
EXPORT_C const TMargins8 LafMenuPane::CascadeMargins()
	{ // static
	TMargins8 cascadeMargins;
	cascadeMargins.iLeft = KLafCascadeLeftMargin;
	cascadeMargins.iRight =KLafCascadeRightMargin;
	cascadeMargins.iTop = KLafCascadeTopMargin;
	cascadeMargins.iBottom = KLafCascadeBottomMargin;
	return cascadeMargins;
	}

/**
 * Returns the menu pane margins.
 */
EXPORT_C const TMargins8 LafMenuPane::Margins()
	{ // static
	TMargins8 margins;
	margins.iLeft = KLafLeftMargin;
	margins.iRight =KLafRightMargin;
	margins.iTop = KLafTopMargin;
	margins.iBottom = KLafBottomMargin;
	return margins;
	}

/**
 * Returns the menu pane margins.
 */
EXPORT_C const TMargins8 LafMenuPane::ScrollBarMargins()
	{ // static
	TMargins8 margins;
	margins.iLeft = KLafLeftScrollBarMargin;
	margins.iRight = KLafRightScrollBarMargin;
	margins.iTop = KLafTopScrollBarMargin;
	margins.iBottom = KLafBottomScrollBarMargin;
	return margins;
	}

/**
 * Prepares the graphics context aGc for drawing the items by setting the pen and brush.
 */
EXPORT_C void LafMenuPane::PrepareGcForDrawingItems(const MLafEnv& aLafEnv, const CCoeControl& aMenuPane, CWindowGc& aGc)
	{
	const CFont* font = NormalFont(aLafEnv);
	aGc.UseFont(font);
	aGc.SetPenColor(aLafEnv.ControlColor(EColorMenuPaneText, aMenuPane));
	aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	aGc.SetBrushColor(aLafEnv.ControlColor(EColorMenuPaneBackground, aMenuPane));
	}

/**
 * Prepares the graphics context aGc according of aHighlightType before drawing an item. At the
 * same time it determines and returns the text color to be used during the drawing of all components
 * of an item.
 */
EXPORT_C void LafMenuPane::PrepareGcForHighlight(const MLafEnv& aLafEnv, const CCoeControl& aMenuPane, CWindowGc& aGc, const TItemAttributes& aItemAttributes)
	{
	TRgb textColor = aLafEnv.ControlColor(EColorMenuPaneText, aMenuPane); //KEikMenuPaneTextColor;
	switch (aItemAttributes.iHighlightType)
		{
	case SLafMenuPane::EDrawHighlight:
		aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
		textColor = aLafEnv.ControlColor(EColorMenuPaneTextHighlight, aMenuPane);
		if (aMenuPane.IsFocused())
			{
			aGc.SetBrushColor(aLafEnv.ControlColor(EColorMenuPaneHighlight, aMenuPane));
			if (aItemAttributes.iFlags&EEikMenuItemDimmed)
				textColor = aLafEnv.ControlColor(EColorMenuPaneDimmedTextHighlight, aMenuPane);
			}
		else
			{
			aGc.SetBrushColor(aLafEnv.ControlColor(EColorMenuPaneDimmedHighlight, aMenuPane));
			textColor = aLafEnv.ControlColor(EColorMenuPaneDimmedTextHighlight, aMenuPane);
			}
		break;
	case SLafMenuPane::ERemoveHighlight:
	aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
		if (aItemAttributes.iFlags&EEikMenuItemDimmed)
			textColor = aLafEnv.ControlColor(EColorMenuPaneDimmedText, aMenuPane);
		break;
	case SLafMenuPane::ENoHighlight:
		aGc.SetBrushStyle(CGraphicsContext::ENullBrush);
		if (aItemAttributes.iFlags&EEikMenuItemDimmed)
			textColor = aLafEnv.ControlColor(EColorMenuPaneDimmedText, aMenuPane);
		break;
	default:
		break;
		}
	aGc.SetPenColor(textColor);
	}

/**
 * Returns ETrue if the menu pane can show the hotkeys, otherwise it returns EFalse.
 */
EXPORT_C TBool LafMenuPane::ShowHotKeys()
	{ // static
	return ETrue;
	}





//
// class LafMenuPaneItem
//

/**
 * Draws the icon for the item to the graphics context aGc, in the middle of the rectangle aRect
 */
EXPORT_C void LafMenuPaneItem::DrawIcon(const MLafEnv& /*aLafEnv*/, const CCoeControl& /*aMenuPane*/, CWindowGc& aGc, const TRect& aRect, const CGulIcon* aIcon, SLafMenuPane::THighlightType aHighlightType)
	{
	if (aIcon)
		{
		if (aHighlightType == SLafMenuPane::EDrawHighlight)
			aGc.SetBrushStyle(CGraphicsContext::ENullBrush);

		// Determine the rect available for the bitmap
		TRect rect = aRect;
		// put the image in the middle of available rect
		const CFbsBitmap* bitmap = aIcon->Bitmap();
		const TSize bmpSize(bitmap->SizeInPixels());
		const TSize rectSize(aRect.Size());
		const TPoint offset(((rectSize.iWidth - bmpSize.iWidth) / 2), ((rectSize.iHeight - bmpSize.iHeight) / 2));
		const CFbsBitmap* mask = aIcon->Mask();
		if (mask)
			{
			const TRect bmpRect(0, 0, bmpSize.iWidth, bmpSize.iHeight);
			aGc.BitBltMasked(rect.iTl+offset, bitmap, bmpRect, mask, ETrue);
			}
		else
			aGc.BitBlt(rect.iTl+offset, bitmap);
		if (aHighlightType == SLafMenuPane::EDrawHighlight)
			aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
		}
	}


/**
 * Gets the default attributes for the scroll bar for orientation aOrientation in aAttributes.
 * Called when the matched control creates its scroll bar frame..
 */
EXPORT_C void LafMenuPane::GetDefaultScrollBarAttributes(TInt aOrientation, LafScrollBarFrame::TScrollBarAttributes& aAttributes)
	{
	aAttributes = LafScrollBarFrame::TScrollBarAttributes();
	if (aOrientation == SLafScrollBar::EVertical)
		{
		aAttributes.iControlType = EEikCtScrollBar;
		aAttributes.iSide = SLafScrollBarFrame::EBottomOrRight;
		aAttributes.iManagement = SLafScrollBarFrame::EComponent;
		aAttributes.iBreadth = LafScrollBar::DefaultBreadth();
		}
	}

/**
 * Draws visual feedback for a menu item to indicate that it has been selected. This is shown for
 * the brief interval between the item being selected and the menu being dismissed. Uses the
 * environment aLafEnv for setting up the context aGc for the menu pane aMenuPane and draws inside
 * the item rectangle aRect.
 *
 * @since App-Framework_6.1
 */
EXPORT_C void LafMenuPane::DrawVisualFeedback(const MLafEnv& /*aLafEnv*/, const CCoeControl& /*aMenuPane*/,
												CWindowGc& aGc, const TRect& aRect)
	{
	aGc.SetPenColor(KRgbBlack);
	aGc.SetBrushStyle(CGraphicsContext::ENullBrush);
	aGc.DrawRect(aRect);
	}


