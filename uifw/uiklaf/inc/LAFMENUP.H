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


#ifndef __LAFMENUP_H__
#define __LAFMENUP_H__


#include <e32std.h>
#include <gulbordr.h>
#include <coecntrl.h>
#include <uiklaf/private/lafenv.h>
#include <lafmain.h>
#include <lafpublc.h>
#include "LAFSBFRM.H"

class CGulIcon;
class TMargins8;

//
// class LafMenuPane
//

class LafMenuPane
	{
public:
	enum TInternalFlags
        {
        EMenuHasIcon			= 0x1,
        EMenuHasHotkey			= 0x2,
        EMenuHasLeftAdornment	= 0x4,
        EMenuHasRightAdornment	= 0x8,
        EMenuIsLeftAdornment	= 0x10,
        EMenuIsRightAdornment	= 0x20
        };
public:
	class TItemAttributes
		{
	public:
		IMPORT_C TItemAttributes();
	public:
		TInt iBaseLine;
		TInt iFlags;
		TInt iInternalFlags;
		TInt iHeight;
		SLafMenuPane::THighlightType iHighlightType;
		TInt iHPosition;
		};
public:
	IMPORT_C static TBool FadeBehind();
	IMPORT_C static void GetDefaultBorder(TGulBorder& aBorder);
	IMPORT_C static void GetBorderColors(TGulBorder::TColors& aBorderColors,const MLafEnv& aLafEnv,const CCoeControl& aMatchedControl);
	IMPORT_C static const TMargins8 CascadeMargins();
	IMPORT_C static const TMargins8 Margins();
	IMPORT_C static const TMargins8 ScrollBarMargins();
	IMPORT_C static TBool ShowHotKeys();
	IMPORT_C static void GetDefaultScrollBarAttributes(TInt aOrientation, LafScrollBarFrame::TScrollBarAttributes& aAttributes);
	IMPORT_C static TInt DefaultScrollBarFlags(TInt aOrientation);
	IMPORT_C static TInt AdornmentSpace(const TItemAttributes& aItemAttributes);
	IMPORT_C static TInt InputCapabilities();
	IMPORT_C static TBool SelectFirstItemOnConstruction();
	IMPORT_C static TInt DefaultCbaResId();
	IMPORT_C static void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList);
	IMPORT_C static TUint MapKeyCode(const TKeyEvent& aKeyEvent,TEventCode aType);
// Drawing
	IMPORT_C static void DrawVisualFeedback(const MLafEnv& aLafEnv, const CCoeControl& aMenuPane, CWindowGc& aGc, const TRect& aRect);
	IMPORT_C static void DrawHotKeyText(const MLafEnv& aLafEnv, const CCoeControl& aMenuPane, CWindowGc& aGc, const TRect& aRect, const TDesC& aHotKeysText, const TItemAttributes& aItemAttributes);
	IMPORT_C static void DrawLeftAdornment(const MLafEnv& aLafEnv, const CCoeControl& aMenuPane, CWindowGc& aGc, const TRect& aRect, const TItemAttributes& aItemAttributes);
	IMPORT_C static void DrawRightAdornment(const MLafEnv& aLafEnv, const CCoeControl& aMenuPane, CWindowGc& aGc, const TRect& aRect, const TItemAttributes& aItemAttributes);
	IMPORT_C static void DrawSeperator(const MLafEnv& aLafEnv, const CCoeControl& aMenuPane, CWindowGc& aGc, const TRect& aRect, const TItemAttributes& aItemAttributes);
	IMPORT_C static void DrawText(const MLafEnv& aLafEnv, const CCoeControl& aMenuPane, CWindowGc& aGc, const TRect& aRect, const TDesC& aText, const TItemAttributes& aItemAttributes);
	IMPORT_C static void DrawTitlePaneJoint(const MLafEnv& aLafEnv, const CCoeControl& aMenuPane, CWindowGc& aGc, const CCoeControl* aMenuPaneTitle, const TRect& aInnerRect);
	IMPORT_C static void PrepareGcForDrawingItems(const MLafEnv& aLafEnv, const CCoeControl& aMenuPane, CWindowGc& aGc);
	IMPORT_C static void PrepareGcForHighlight(const MLafEnv& aLafEnv, const CCoeControl& aMenuPane, CWindowGc& aGc, const TItemAttributes& aItemAttributes);
public:
// Constants
	inline static TInt ExtraBaselineOffset();
	inline static TInt MenuCascadeOverlap();
	inline static TInt MenuPaneTextTopSpace();
	inline static TInt MenuPaneTextBottomSpace();
	inline static TInt MenuPaneSeparatorAfterSpace();
	inline static TInt MenuPaneSeparatorMargin();
	inline static TInt MenuSeparatorYOffset();
	inline static TInt OffsetBetweenMenuPaneAndMenuPaneTitle();
	inline static TInt PostIconSpace();
	inline static TInt PostRightAdornmentSpace();
	inline static TInt PreIconSpace();
	inline static TInt ShadowHeight();
	inline static TInt SpaceBetweenTextAndHotkey();
	inline static TInt NumberOfItemsInView();
// Fonts
	inline static const CFont* AnnotationFont(const MLafEnv& aLafEnv);
	inline static const CFont* NormalFont(const MLafEnv& aLafEnv);
	inline static const CFont* SymbolFont(const MLafEnv& aLafEnv);
private:
	enum TConstantType
		{
		EPostRightAdornmentSpace,
		EMenuPaneTextTopSpace,
		EMenuPaneTextBottomSpace,
		ESpaceBetweenTextAndHotkey,
		EOffsetBetweenMenuPaneAndMenuPaneTitle,
		EMenuPaneSeparatorMargin,
		EShadowHeight,
		EPreIconSpace,
		EPostIconSpace,
		EExtraBaselineOffset,
		EMenuPaneSeparatorAfterSpace,
		EMenuCascadeOverlap,
		EMenuSeparatorYOffset,
		ENumberOfItemsInView
		};
	enum TFontType
		{
		EAnnotation,
		ENormal,
		ESymbol
		};
private:
	IMPORT_C static TInt Constant(TConstantType aConstantType);
	IMPORT_C static const CFont* Font(const MLafEnv& aLafEnv, TFontType aFontType);
	};

//
// class LafMenuPaneItem
//

class LafMenuPaneItem
	{
public:
	IMPORT_C static void DrawIcon(const MLafEnv& aLafEnv, const CCoeControl& aMenuPane, CWindowGc& aGc, const TRect& aRect, const CGulIcon* aIcon, SLafMenuPane::THighlightType aHighlightType);
	};


//
// Inlines
//

/**
 * Returns the post right adornment space.
 */
inline TInt LafMenuPane::PostRightAdornmentSpace()
	{//static	
	return Constant(EPostRightAdornmentSpace);	
	};

/**
 * Returns an extra space which will be added to the height of item font.
 */
inline TInt LafMenuPane::MenuPaneTextTopSpace()
	{//static	
	return Constant(EMenuPaneTextTopSpace);	
	}

/**
 * Returns an extra space which will be added to the height of item font.
 */
inline TInt LafMenuPane::MenuPaneTextBottomSpace()
	{//static	
	return Constant(EMenuPaneTextBottomSpace);	
	}

/**
 * Returns the space between the item text and the hotkey.
 */
inline TInt LafMenuPane::SpaceBetweenTextAndHotkey()
	{//static	
	return Constant(ESpaceBetweenTextAndHotkey);	
	}

inline TInt LafMenuPane::OffsetBetweenMenuPaneAndMenuPaneTitle()
	{//static	
	return Constant(EOffsetBetweenMenuPaneAndMenuPaneTitle);	
	}

/**
 * Returns the shadow height for the menu pane.
 */
inline TInt LafMenuPane::ShadowHeight()
	{//static	
	return Constant(EShadowHeight);	
	}

inline TInt LafMenuPane::MenuPaneSeparatorMargin()
	{//static	
	return Constant(EMenuPaneSeparatorMargin);	
	}

inline TInt LafMenuPane::PreIconSpace()
	{//static	
	return Constant(EPreIconSpace);
	}

inline TInt LafMenuPane::PostIconSpace()
	{//static	
	return Constant(EPostIconSpace);	
	}

inline TInt LafMenuPane::ExtraBaselineOffset()
	{//static	
	return Constant(EExtraBaselineOffset);	
	}

inline TInt LafMenuPane::MenuPaneSeparatorAfterSpace()
	{//static	
	return Constant(EMenuPaneSeparatorAfterSpace);	
	}

inline TInt LafMenuPane::MenuCascadeOverlap()
	{//static	
	return Constant(EMenuCascadeOverlap);	
	}

inline TInt LafMenuPane::MenuSeparatorYOffset()
	{//static	
	return Constant(EMenuSeparatorYOffset);	
	}

inline TInt LafMenuPane::NumberOfItemsInView()
	{//static	
	return Constant(ENumberOfItemsInView);	
	}

// Fonts
/**
 * Returns the menu pane annotation font.
 */
inline const CFont* LafMenuPane::AnnotationFont(const MLafEnv& aLafEnv)
	{//static	
	return Font(aLafEnv, EAnnotation);	
	}

/**
 * Returns the menu pane normal font.
 */
inline const CFont* LafMenuPane::NormalFont(const MLafEnv& aLafEnv)
	{//static	
	return Font(aLafEnv, ENormal);	
	}

/**
 * Returns the menu pane symbol font.
 */
inline const CFont* LafMenuPane::SymbolFont(const MLafEnv& aLafEnv)
	{//static	
	return Font(aLafEnv, ESymbol);	
	}



#endif //__LAFMENUP_H__
