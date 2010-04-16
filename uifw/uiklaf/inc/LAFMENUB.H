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


#ifndef	__LAFMENUB_H__
#define __LAFMENUB_H__

#include <uiklaf/private/lafenv.h>
#include <lafmain.h>
#include <lafpublc.h>
#include "LAFMENUP.H"
#include <e32std.h>
#include <gulbordr.h>
#include <coecntrl.h>

/**
 * @internal
 * Do not use
 */
class LafMenuBar
	{
public:
	enum TAnchor
		{
		ERelativeToScreen,
		ERelativeToApplication
		};
	enum TWidth
		{
		EMinPossible,
		EScreenWidth,
		EAppWidth,
		EClientWidth
		};
public:
	class TTitleAttributes
		{
	public:
		IMPORT_C TTitleAttributes();
	public:
		TInt iBaseLine;
		TInt iFlags;
		};
public:
	IMPORT_C static TBool FadeBehind();
	IMPORT_C static TBool IsAlwaysVisible();
	IMPORT_C static void GetDefaultBorder(TGulBorder& aBorder);
	IMPORT_C static void GetBorderColors(TGulBorder::TColors& aBorderColors,const MLafEnv& aLafEnv,const CCoeControl& aMatchedControl);
	IMPORT_C static TWidth DefaultSpan();
	IMPORT_C static TBool ShowHotKeys();
	IMPORT_C static void TopLeftCornerPosition(TPoint & aPosition,TAnchor& aMenuAnchor);
	IMPORT_C static TInt InputCapabilities();
	IMPORT_C static void DrawBetweenRects(const MLafEnv& aLafEnv, const CCoeControl& aMenuBar, CWindowGc& aGc, const TRect& aInnerRect, const TRect& aClientRect);
	IMPORT_C static void DrawText(const MLafEnv& aLafEnv, const CCoeControl& aMenuBar, CWindowGc& aGc, const TRect& aRect, const TDesC& aText, const TTitleAttributes& aTitleAttributes);
	IMPORT_C static void PrepareGcForDrawingTitle(const MLafEnv& aLafEnv, const CCoeControl& aMenuBar, CWindowGc& aGc);
	IMPORT_C static void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList);
	IMPORT_C static TUint MapKeyCode(const TKeyEvent& aKeyEvent,TEventCode aType);
public:
// Constants
	inline static TInt DefaultMenuPaneIndex();
	inline static TInt ExtraBaselineOffsetForFirstPaneItem();
	inline static TInt HorizontalBorder();
	inline static TInt VerticalBorder();
	inline static TInt MnemonicPad();
	inline static TInt MenuPaneOverlap();
	inline static TInt MenuTitleLeftSpace();
	inline static TInt MenuTitleRightSpace();
	inline static TInt MenuTitleLeftSmallSpace();
	inline static TInt MenuTitleRightSmallSpace();
	inline static TInt NumOfSideButtons();
	inline static TInt ShadowHeight();
	inline static TInt SidebarPopupXPos();
	inline static TInt SpaceBetweenMenuPaneTitleAndMenuBar();
//
	inline static const CFont* NormalFont(const MLafEnv& aLafEnv);
private:
	enum TFontType
		{
		EAnnotation,
		ENormal,
		ESymbol
		};
	enum TConstantType
		{
		EDefaultMenuPaneIndex,
		EExtraBaselineOffsetForFirstPaneItem,
		EHorizontalBorder,
		EVerticalBorder,
		EMnemonicPad,
		EMenuPaneOverlap,
		EMenuTitleLeftSpace,
		EMenuTitleRightSpace,
		EMenuTitleLeftSmallSpace,
		EMenuTitleRightSmallSpace,
		ENumOfSideButtons,
		EShadowHeight,
		ESidebarPopupXPos,
		ESpaceBetweenMenuPaneTitleAndMenuBar
		};
private:
	IMPORT_C static const CFont* Font(const MLafEnv& aLafEnv, TFontType aFontType);
	IMPORT_C static TInt Constant(TConstantType aConstant);
	};


//
// class LafMenuPaneTitle
//

/**
 * @internal
 * Do not use
 */
class LafMenuPaneTitle
	{
public:
	IMPORT_C static void GetDefaultBorder(TGulBorder& aBorder);
	IMPORT_C static void GetBorderColors(TGulBorder::TColors& aBorderColors,const MLafEnv& aLafEnv,const CCoeControl& aMatchedControl);
	IMPORT_C static void DrawTitlePaneJoint(const MLafEnv& aLafEnv, const CCoeControl& aMenuPaneTitle, CWindowGc& aGc, const TRect& aInnerRect);
	IMPORT_C static void DrawText(const MLafEnv& aLafEnv, const CCoeControl& aMenuPaneTitle, CWindowGc& aGc, const TRect& aRect, const TDesC& aText, LafMenuBar::TTitleAttributes aMenuBarAttributes);
	IMPORT_C static void PrepareGcForDrawingTitle(const MLafEnv& aLafEnv, const CCoeControl& aMenuPaneTitle, CWindowGc& aGc);
	IMPORT_C static void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList);
public:
// Constants
	inline static TInt ShadowHeight();
	inline static TInt TitleLeftSpace();
	inline static TInt TitleRightSpace();
	inline static TInt TitleSmallLeftSpace();
	inline static TInt TitleSmallRightSpace();
private:
	enum TConstantType
		{
		EShadowHeight,
		ETitleLeftSpace,
		ETitleRightSpace,
		ETitleSmallLeftSpace,
		ETitleSmallRightSpace
		};
private:
	IMPORT_C static TInt Constant(TConstantType aConstant);
	};

//
// class LafMenuBarTitle
//

/**
 * @internal
 * Do not use
 */
class LafMenuBarTitle
	{
public:
	IMPORT_C static void DrawIcon(CWindowGc& aGc, const TRect& aRect, const CGulIcon& aIcon);
	};


// Inlines
inline TInt LafMenuBar::HorizontalBorder()
	{//static	
	return Constant(EHorizontalBorder);	
	};

inline TInt LafMenuBar::VerticalBorder()
	{//static	
	return Constant(EVerticalBorder);	
	}

inline TInt LafMenuBar::MnemonicPad()
	{//static	
	return Constant(EMnemonicPad);	
	}

inline TInt LafMenuBar::NumOfSideButtons()
	{//static	
	return Constant(ENumOfSideButtons);	
	}

inline TInt LafMenuBar::SidebarPopupXPos()
	{//static	
	return Constant(ESidebarPopupXPos);	
	}

inline TInt LafMenuBar::MenuPaneOverlap()
	{//static	
	return Constant(EMenuPaneOverlap);	
	}

inline TInt LafMenuBar::MenuTitleLeftSpace()
	{//static	
	return Constant(EMenuTitleLeftSpace);	
	}

inline TInt LafMenuBar::MenuTitleRightSpace()
	{//static	
	return Constant(EMenuTitleRightSpace);	
	}

inline TInt LafMenuBar::MenuTitleLeftSmallSpace()
	{//static	
	return Constant(EMenuTitleLeftSmallSpace);	
	}

inline TInt LafMenuBar::MenuTitleRightSmallSpace()
	{//static	
	return Constant(EMenuTitleRightSmallSpace);	
	}

inline TInt LafMenuBar::ExtraBaselineOffsetForFirstPaneItem()
	{//static	
	return Constant(EExtraBaselineOffsetForFirstPaneItem);	
	}

/**
 * Sets the first menu pane to be displayed.  Defaults to 0.
 * Can only be set as an offset from 0 so setting "the last pane" isn't possible
 */
inline TInt LafMenuBar::DefaultMenuPaneIndex()
	{ // static
	return Constant(EDefaultMenuPaneIndex);
	}

/**
 * Returns the shadow height for the menu bar.
 */
inline TInt LafMenuBar::ShadowHeight()
	{//static	
	return Constant(EShadowHeight);	
	}

/**
 * Returns the space between the menu bar and the relative menu pane title.
 */
inline TInt LafMenuBar::SpaceBetweenMenuPaneTitleAndMenuBar()
	{//static	
	return Constant(ESpaceBetweenMenuPaneTitleAndMenuBar);	
	}
		
/**
 * Returns the menu bar normal font.
 */
inline const CFont* LafMenuBar::NormalFont(const MLafEnv& aLafEnv)
	{ // static
	return Font(aLafEnv, ENormal);	
	}

/**
 * Returns the shadow height for the menu pane title.
 */
inline TInt LafMenuPaneTitle::ShadowHeight()
	{//static	
	return Constant(EShadowHeight);	
	}

/**
 * Returns the left space between the border and the text.
 */
inline TInt LafMenuPaneTitle::TitleLeftSpace()
	{//static	
	return Constant(ETitleLeftSpace);	
	}

/**
 * Returns the right space between the border and the text.
 */
inline TInt LafMenuPaneTitle::TitleRightSpace()
	{//static	
	return Constant(ETitleRightSpace);	
	}

/**
 * Returns the small left space between the border and the text. This is used instead of TitleLeftSpace
 * when the menu bar size is to big.
 */
inline TInt LafMenuPaneTitle::TitleSmallLeftSpace()
	{//static	
	return Constant(ETitleSmallLeftSpace);	
	}

/**
 * Returns the small right space between the border and the text. This is used instead of TitleRightSpace
 * when the menu bar size is to big.
 */
inline TInt LafMenuPaneTitle::TitleSmallRightSpace()
	{//static	
	return Constant(ETitleSmallRightSpace);	
	}

#endif //__LAFMENUB_H__
