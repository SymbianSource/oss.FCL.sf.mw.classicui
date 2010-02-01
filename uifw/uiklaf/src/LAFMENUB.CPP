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


#include <gulfont.h>
#include <gulcolor.h>
#include <gulicon.h>
#include <gulutil.h>
#include <coeinput.h>
#include <coecntrl.h>

#include <avkon.hrh>

#include "LAFSTD.H"
#include "LAFMENUB.H"
#include "lafcommn.h"
#include "uikon.hrh"

const TInt KLafDefaultPaneIndex	= 0;
const TInt KLafShadowHeight = 3;
const TInt KLafTopLeftCornerPositionX = 0;
const TInt KLafTopLeftCornerPositionY = 0;

// From menu bar source code
const TInt KLafExtraBaselineOffsetForFirstPaneItem = 4;
const TInt KLafHorizontalBorder=8;
const TInt KLafVerticalBorder=2;
const TInt KLafMnemonicPad=3;

const TInt KLafNumOfSideButtons=5;
const TInt KLafSidebarPopupXPos=5;
const TInt KLafMenuPaneOverlap=1;

const TInt KLafMenuTitleLeftSpace		= 12;
const TInt KLafMenuTitleRightSpace		= 12;
const TInt KLafMenuTitleLeftSmallSpace	= 4;
const TInt KLafMenuTitleRightSmallSpace	= 4;

const TInt KLafSpaceBetweenMenuPaneTitleAndMenuBar = 0;

// Menu pane title
const TInt KLafMenuPaneTitleLeftSpace		= 12;
const TInt KLafMenuPaneTitleRightSpace		= 12;
const TInt KLafMenuPaneTitleSmallLeftSpace	= 0;
const TInt KLafMenuPaneTitleSmallRightSpace	= 0;



//
// Class LafMenuPane::TTitleAttributes
//

EXPORT_C LafMenuBar::TTitleAttributes::TTitleAttributes()
	: iBaseLine(0), iFlags(0)
	{
	}

//
// Class LafMenuBar
//


/**
 * Returns ETrue if the menu bar should be always visible oterwise it resturns EFalse.
 */
EXPORT_C TBool LafMenuBar::IsAlwaysVisible()
	{ // static
	return EFalse;
	}

/**
 * Returns ETrue when the window behind the menu bar should be faded.
 */
EXPORT_C TBool LafMenuBar::FadeBehind()
	{ // static
	return EFalse;
	}

/**
 * Gets the default border for the matched control in aBorder. Called from the constructor of the matched control.
 */
EXPORT_C void LafMenuBar::GetDefaultBorder(TGulBorder& aBorder)
	{
	aBorder=TGulBorder(TGulBorder::EThickDeepRaisedWithOutline);
	}

/**
 * Gets the set of border colors for the matched control in aBorderColors. The RGB values of the colors obtained
 * may depend on the the display mode, the environment color list and the instance of the
 * matched control aMatchedControl. Called by the matched control from its Draw() method and passed on to the
 * Draw() method of TGulBorder. 
 */
EXPORT_C void LafMenuBar::GetBorderColors(TGulBorder::TColors& aBorderColors, const MLafEnv& aLafEnv, const CCoeControl& aMatchedControl)
	{
	LafCommonUtils::GetRgbDerivedBorderColors( aBorderColors,
			EColorMenubarBackground, aLafEnv,aMatchedControl);
	}

EXPORT_C  LafMenuBar::TWidth LafMenuBar::DefaultSpan()
	{ // static
	return EMinPossible;
	}

/**
 * Returns the font corresponding to aFontType.
 */
EXPORT_C const CFont* LafMenuBar::Font(const MLafEnv& aLafEnv, TFontType aFontType)
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
 * Returns a constant value according to aConstatType.
 * @internal
 */
EXPORT_C TInt LafMenuBar::Constant(TConstantType aConstantType)
	{//static
	TInt retValue = 0;
	switch (aConstantType)
		{
	case EDefaultMenuPaneIndex:
		retValue = KLafDefaultPaneIndex;
		break;
	case EExtraBaselineOffsetForFirstPaneItem:
		retValue = KLafExtraBaselineOffsetForFirstPaneItem;
		break;
	case EHorizontalBorder:
		retValue = KLafHorizontalBorder;
		break;
	case EVerticalBorder:
		retValue = KLafVerticalBorder;
		break;
	case EMnemonicPad:
		retValue = KLafMnemonicPad;
		break;
	case EMenuPaneOverlap:
		retValue = KLafMenuPaneOverlap;
		break;
	case EMenuTitleLeftSpace:
		retValue = KLafMenuTitleLeftSpace;
		break;
	case EMenuTitleRightSpace:
		retValue = KLafMenuTitleRightSpace;
		break;
	case EMenuTitleLeftSmallSpace:
		retValue = KLafMenuTitleLeftSmallSpace;
		break;
	case EMenuTitleRightSmallSpace:
		retValue = KLafMenuTitleRightSmallSpace;
		break;
	case ENumOfSideButtons:
		retValue = KLafNumOfSideButtons;
		break;
	case ESidebarPopupXPos:
		retValue = KLafSidebarPopupXPos;
		break;
	case EShadowHeight:
		retValue = KLafShadowHeight;
		break;
	case ESpaceBetweenMenuPaneTitleAndMenuBar:
		retValue = KLafSpaceBetweenMenuPaneTitleAndMenuBar;
		break;
	default:
		__ASSERT_DEBUG(EFalse, Panic(ELafPanicConstantNotKnown));
		break;
		}
	return retValue;
	}

/**
 * Returns ETrue if the menu bar can show the hotkeys, otherwise it returns EFalse.
 */
EXPORT_C TBool LafMenuBar::ShowHotKeys()
	{ // static
	return ETrue;
	}

/**
 * Returns the left top corner position of the menu bar and if this position is relative to the screen
 * or to the client area.
 */
EXPORT_C void LafMenuBar::TopLeftCornerPosition(TPoint & aPosition, TAnchor& aMenuAnchor)
	{
	aMenuAnchor=ERelativeToScreen;
	aPosition = TPoint(KLafTopLeftCornerPositionX, KLafTopLeftCornerPositionY);
	}

/**
 *
 */
EXPORT_C void LafMenuBar::DrawBetweenRects(const MLafEnv& aLafEnv, const CCoeControl& aMenuBar, CWindowGc& aGc, const TRect& aInnerRect, const TRect& aClientRect)
	{
	aGc.SetBrushColor(aLafEnv.ControlColor(EColorMenubarBackground, aMenuBar));
	const TRect rect(aMenuBar.Rect());
	const TInt bottomMargin = rect.iBr.iY - aInnerRect.iBr.iY;
	const TInt rightMargin = rect.iBr.iX - aInnerRect.iBr.iX;
	if ((rect.iBr.iY-aClientRect.iTl.iY <= bottomMargin + MenuPaneOverlap()) ||
		(rect.iBr.iX-aClientRect.iTl.iX <= rightMargin+1))
		{// handle special case of pane being moved
		TRect innerRect = aInnerRect;
		innerRect.Intersection(aClientRect);
		aGc.Clear(innerRect);
		return;
		}
	aGc.Clear(aInnerRect);
	}

/**
 * Returns the keypresses a menu bar is interested in receiving from a FEP
 */
EXPORT_C TInt LafMenuBar::InputCapabilities()
	{ // static
	return TCoeInputCapabilities::ENavigation|TCoeInputCapabilities::EWesternNumericIntegerPositive;
	}

/**
 * Draws aText into the graphics context aGc, in the rectangle aRect. Called by the menu bar
 * control from its Draw() method after the aGc has been set up.
 */
EXPORT_C void LafMenuBar::DrawText(const MLafEnv& aLafEnv, const CCoeControl& /*aMenuBar*/, CWindowGc& aGc, const TRect& aRect, const TDesC& aText, const TTitleAttributes& aTitleAttributes)
	{
	CGraphicsContext::TTextAlign align=(aTitleAttributes.iFlags&EEikMenuTitleRightAlign? 
												CGraphicsContext::ERight : CGraphicsContext::ELeft);
	TBuf<SLafMenuBar::ENominalTextLength> text = aText;
	TextUtils::ClipToFit(text, *NormalFont(aLafEnv),aRect.Width());
	aGc.DrawText(text, aRect, aTitleAttributes.iBaseLine, align);
	}

/**
 * Prepares the graphics context aGc for drawing the title by setting the pen and brush. Called
 * by the menu bar control from its Draw() and DrawItem() methods. 
 */
EXPORT_C void LafMenuBar::PrepareGcForDrawingTitle(const MLafEnv& aLafEnv, const CCoeControl& aMenuBar, CWindowGc& aGc)
	{ // static
	aGc.SetPenColor(aLafEnv.ControlColor(EColorMenubarText, aMenuBar));
	aGc.UseFont(NormalFont(aLafEnv));
	aGc.SetBrushColor(aLafEnv.ControlColor(EColorMenubarBackground, aMenuBar));
	aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	}

EXPORT_C void LafMenuBar::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList)
	{ // static
	TInt commonAttributes = TCoeColorUse::EActive|TCoeColorUse::ESurrounds|TCoeColorUse::ENormal|TCoeColorUse::ENeutral;
	TCoeColorUse colorUse;

	colorUse.SetLogicalColor(EColorMenubarText);
	colorUse.SetUse(TCoeColorUse::EFore|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorMenubarBackground);
	colorUse.SetUse(TCoeColorUse::EBack|commonAttributes);
	aColorUseList.AppendL(colorUse);
	}

/**
 * Returns the keycode to use with menus for the given event.  Intended primarily to allow custom
 * device hardware keys to map to standard Epoc functions.
 *
 * @since App-Framework_6.1
 */ 
EXPORT_C TUint LafMenuBar::MapKeyCode(const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
	{ // static
	return aKeyEvent.iCode;
	}

//
// Class LafMenuPaneTitle
//

/**
 * Gets the default border for the matched control in aBorder. Called from the constructor of the matched control.
 */
EXPORT_C void LafMenuPaneTitle::GetDefaultBorder(TGulBorder& aBorder)
	{
	aBorder=TGulBorder(TGulBorder::EThickDeepRaisedWithOutline);
	}

/**
 * Gets the set of border colors for the matched control in aBorderColors. The RGB values of the colors obtained
 * may depend on the the display mode, the environment color list and the instance of the
 * matched control aMatchedControl. Called by the matched control from its Draw() method and passed on to the
 * Draw() method of TGulBorder. 
 */
EXPORT_C void LafMenuPaneTitle::GetBorderColors(TGulBorder::TColors& aBorderColors, const MLafEnv& aLafEnv, const CCoeControl& aMatchedControl)
	{
	LafCommonUtils::GetRgbDerivedBorderColors( aBorderColors,
		EColorMenubarTitleBackground, aLafEnv,aMatchedControl );
	}

/**
 * Returns a constant value according to aConstatType.
 */
EXPORT_C TInt LafMenuPaneTitle::Constant(TConstantType aConstantType)
	{//static
	TInt retValue = 0;
	switch (aConstantType)
		{
	case EShadowHeight:
		retValue = KLafShadowHeight;
		break;
	case ETitleLeftSpace:
		retValue = KLafMenuPaneTitleLeftSpace;
		break;
	case ETitleRightSpace:
		retValue = KLafMenuPaneTitleRightSpace;
		break;
	case ETitleSmallLeftSpace:
		retValue = KLafMenuPaneTitleSmallLeftSpace;
		break;
	case ETitleSmallRightSpace:
		retValue = KLafMenuPaneTitleSmallRightSpace;
		break;
	default:
		__ASSERT_DEBUG(EFalse, Panic(ELafPanicConstantNotKnown));
		break;
		}
	return retValue;
	}

/**
 *
 */
EXPORT_C void LafMenuPaneTitle::DrawTitlePaneJoint(const MLafEnv& aLafEnv, const CCoeControl& aMenuPaneTitle, CWindowGc& aGc, const TRect& aInnerRect)
	{
	const TRect rect(aMenuPaneTitle.Rect());

	aGc.SetPenStyle(CGraphicsContext::ENullPen);
	aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	aGc.SetBrushColor(aLafEnv.ControlColor(EColorMenubarTitleBackground, aMenuPaneTitle));
	aGc.DrawRect(TRect(aInnerRect.iTl, TPoint(aInnerRect.iBr.iX, rect.iBr.iY)));

	aGc.SetPenStyle(CGraphicsContext::ESolidPen);

	// get rid of the bit of border on the left
	aGc.DrawLine(TPoint(rect.iTl.iX+1,rect.iBr.iY-4),TPoint(rect.iTl.iX+1,rect.iBr.iY));
	aGc.DrawLine(TPoint(rect.iTl.iX+2,rect.iBr.iY-4),TPoint(rect.iTl.iX+2,rect.iBr.iY));
	aGc.DrawLine(TPoint(rect.iTl.iX+3,rect.iBr.iY-4),TPoint(rect.iTl.iX+3,rect.iBr.iY));

	// get rid of the bit of border frame on the right bottom side.
	TGulBorder::TColors borderColors;
	LafMenuPaneTitle::GetBorderColors(borderColors, aLafEnv, aMenuPaneTitle);
	aGc.SetPenColor(borderColors.iMid);
	aGc.DrawLine(TPoint(rect.iBr.iX-2,rect.iBr.iY-1),TPoint(rect.iBr.iX-5,rect.iBr.iY-1));
	}

/**
 * Draws aText into the graphics context aGc, in the rectangle aRect. Called by the menu
 * bar control from its Draw() method after the aGc has been set up.
 */
EXPORT_C void LafMenuPaneTitle::DrawText(const MLafEnv& aLafEnv, const CCoeControl& /*aMenuPaneTitle*/, CWindowGc& aGc, const TRect& aRect, const TDesC& aText, LafMenuBar::TTitleAttributes aMenuBarAttributes)
	{
	TInt menuPaneTitleBaseLine = aMenuBarAttributes.iBaseLine - KLafSpaceBetweenMenuPaneTitleAndMenuBar;
	CGraphicsContext::TTextAlign align=(aMenuBarAttributes.iFlags&EEikMenuTitleRightAlign? 
												CGraphicsContext::ERight : CGraphicsContext::ELeft);

	TBuf<SLafMenuBar::ENominalTextLength> text = aText;
	TextUtils::ClipToFit(text, *LafMenuBar::NormalFont(aLafEnv),aRect.Width());
	aGc.DrawText(text, aRect, menuPaneTitleBaseLine, align);
	}

/**
 * Prepares the graphics context aGc for drawing the title by setting the pen and brush.
 */
EXPORT_C void LafMenuPaneTitle::PrepareGcForDrawingTitle(const MLafEnv& aLafEnv, const CCoeControl& aMenuPaneTitle, CWindowGc& aGc)
	{
	aGc.UseFont(LafMenuBar::NormalFont(aLafEnv));
	aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	aGc.SetBrushColor(aLafEnv.ControlColor(EColorMenubarTitleBackground, aMenuPaneTitle));
	aGc.SetPenColor(aLafEnv.ControlColor(EColorMenubarTitleText, aMenuPaneTitle));
	}

EXPORT_C void LafMenuPaneTitle::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList)
	{ // static
	TInt commonAttributes = TCoeColorUse::EActive|TCoeColorUse::ESurrounds|TCoeColorUse::ENormal|TCoeColorUse::ENeutral;
	TCoeColorUse colorUse;

	colorUse.SetLogicalColor(EColorMenubarTitleText);
	colorUse.SetUse(TCoeColorUse::EFore|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorMenubarTitleBackground);
	colorUse.SetUse(TCoeColorUse::EBack|commonAttributes);
	aColorUseList.AppendL(colorUse);
	}

//
// class LafMenuBarTitle
//

/**
 * Draws the icon for the title to the graphics context aGc, in the middle of the rectangle aRect
 */
EXPORT_C void LafMenuBarTitle::DrawIcon(CWindowGc& aGc, const TRect& aRect, const CGulIcon& aIcon)
	{

	// Determine the rect available for the bitmap
	TRect rect = aRect;
	// put the image in the middle of available rect
	const CFbsBitmap* bitmap = aIcon.Bitmap();
	TSize bmpSize = bitmap->SizeInPixels();
	TInt yoffset = (aRect.Size().iHeight - bmpSize.iHeight) / 2;
	TInt xoffset =  (aRect.Size().iWidth - bmpSize.iWidth) / 2;;
	TPoint offset(xoffset,yoffset);
	const CFbsBitmap* mask = aIcon.Mask();
	if (mask)
		{
		TRect bmpRect(TPoint(0,0), TPoint(bmpSize.iWidth, bmpSize.iHeight));
		aGc.BitBltMasked(rect.iTl+offset, bitmap, bmpRect, mask, ETrue);
		}
	else
		aGc.BitBlt(rect.iTl+offset, bitmap);
	}
