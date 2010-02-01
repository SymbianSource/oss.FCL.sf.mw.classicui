/*
* Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#include <eiklbi.h>
#include <eiklbm.h>
#include <badesca.h>
#include <eikpanic.h>
#include <w32std.h>		// Is this really needed?
#include <gdi.h>
#include <gulutil.h>
#include <eiksfont.h>
#include <eikenv.h>
#include <gulcolor.h>
#include <coemain.h>		// Is this really needed?
#include <eiklbd.h>
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
#include <aknlistloadertfx.h>
#include <aknlistboxtfxinternal.h>
#endif //RD_UI_TRANSITION_EFFECTS_LIST
#include <aknappui.h>

#include "laflbi.h"
#include "laflbx.h"
#include "akntrace.h"

const TUint KListItemDrawerAllowedFlags = 0x00ff;

const TInt KDefaultMarkColumnWidth = 10;
const TInt KDefaultMarkGutter = 2;

//
// class TListItemProperties
//

EXPORT_C TListItemProperties::TListItemProperties()
	: iFlags(0) 
	{}

//
// class CListItemDrawer
//

EXPORT_C MAknsControlContext *CListItemDrawer::SkinBackgroundControlContext() const
	{
	if (iData)
		{
		return iData->SkinBackgroundControlContext();
		}
	return NULL;
	}
EXPORT_C void CListItemDrawer::SetSkinEnabledL(TBool aEnabled)
	{
	if(iData)
		{
		iData->SetSkinEnabledL(aEnabled);
		}
	}

/**
 * Sets the item drawer flags to aFlags, masking off all
 * but the lower 3 bits.
 */
EXPORT_C void CListItemDrawer::SetFlags(TInt aFlags)
    {
    // Pressed down highlight is blocked out if
    // single click mode is enabled
    if ( aFlags & EPressedDownState 
           &&  iFlags & ESingleClickEnabled )
        {
        aFlags &= ~EPressedDownState;
        }
    
    iFlags |= aFlags; 
    iFlags &= KListItemDrawerAllowedFlags;
    }

/**
 * Clears the item drawer flags aFlags, masking off all
 * but the lower 3 bits.
 */
EXPORT_C void CListItemDrawer::ClearFlags(TInt aFlags)
	{iFlags&=(~aFlags); iFlags&=KListItemDrawerAllowedFlags;}


EXPORT_C CListItemDrawer::CListItemDrawer()
    : iFlags(0)
    {
    _AKNTRACE_FUNC_ENTER;
	iMarkColumnWidth = KDefaultMarkColumnWidth;
	iMarkGutter = KDefaultMarkGutter;
	CEikonEnv* eikEnv=CEikonEnv::Static();
	iMarkColor = eikEnv->Color(EColorControlText);
	iBackColor = eikEnv->Color(EColorControlBackground);
	iHighlightedBackColor = eikEnv->Color(EColorControlHighlightBackground);
    if ( iAvkonAppUi && 
         iAvkonAppUi->IsSingleClickCompatible() )
        {
        SetFlags( ESingleClickEnabled | EDisableMarquee );
        }
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C CListItemDrawer::~CListItemDrawer()
    {
    _AKNTRACE_FUNC_ENTER;
    delete iData;
    _AKNTRACE_FUNC_EXIT;
    }

/**
 * Sets the font storage data for the item drawer to aFontStorage and transfers ownership.
 *
 * @since ER5U
 */
EXPORT_C void CListItemDrawer::SetData(CListBoxData* aData)
    {
    iData=aData;
    }

/**
 * Returns the font for the item at index aItemIndex. Returns NULL if no font storage data 
 * has been set.
 *
 * @since ER5U
 */
EXPORT_C CFont* CListItemDrawer::Font(TInt aItemIndex) const
    {
    if (iData)
        return iData->Font( Properties( aItemIndex ) );
    else
		return NULL;
    }

/**
 * Returns the properties of the item at index aItemIndex.
 * 
 * @since ER5U
 */
EXPORT_C TListItemProperties CListItemDrawer::Properties(TInt /*aItemIndex*/) const
    {
	TListItemProperties properties;
	properties.SetColor(iTextColor);
    return properties;
    }

EXPORT_C void CListItemDrawer::ResetGc() const
	{
	_AKNTRACE_FUNC_ENTER;
	iGc->SetPenStyle(CGraphicsContext::ESolidPen);
	iGc->SetBrushStyle(CGraphicsContext::ENullBrush);
	iGc->SetBrushColor(iBackColor);
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CListItemDrawer::SetGc(CWindowGc* aGc)
	{
	_AKNTRACE_FUNC_ENTER;
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
	// assert that aGc is not null
    MAknListBoxTfxInternal *transApi = CAknListLoader::TfxApiInternal( iGc );
    if ( transApi )
        {
        if ( aGc )
            {
            transApi->SetGc( *aGc );
            }
        }
    else
        {
#endif //RD_UI_TRANSITION_EFFECTS_LIST
    	iGc = aGc;

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        }

#endif //RD_UI_TRANSITION_EFFECTS_LIST
    _AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CListItemDrawer::SetMarkColumnWidth(TInt aWidthInPixels)
	{
	iMarkColumnWidth = aWidthInPixels;
	}

EXPORT_C void CListItemDrawer::SetMarkGutter(TInt aGapInPixels)
	{
	iMarkGutter = aGapInPixels;
	}

EXPORT_C TInt CListItemDrawer::MarkColumn() const
	{
	return iMarkColumnWidth;
	}

EXPORT_C TInt CListItemDrawer::MarkGutter() const
	{
	return iMarkGutter;
	}

EXPORT_C void CListItemDrawer::SetItemCellSize(const TSize& aSizeInPixels)
	{
	iItemCellSize = aSizeInPixels;
	}

EXPORT_C TSize CListItemDrawer::ItemCellSize() const
    {
    return iItemCellSize;
    }

EXPORT_C void CListItemDrawer::SetViewRect(const TRect& aRect)
	{
	iViewRect = aRect;
	}

EXPORT_C CWindowGc* CListItemDrawer::Gc() const
	{
	return(iGc);
	}

/**
 * Returns the rectangle occupied by the matcher cursor in the text aMatchableText. The pixel position of
 * the rectangle is determined by specifying the character position of the cursor in the text aCharPos and the
 * vertical position of the item cell aItemCellYPos. The size of the rectangle can be determined by giving the 
 * index of the current item aCurrentItemIndex.
 *
 * Returns the rectangle occupied by the item drawer by default.
 */
EXPORT_C TRect CListItemDrawer::MatcherCursorRect(const TDesC& /*aMatchableText*/, TInt /*aCharPos*/, TInt /*aItemCellYPos*/, TInt /*aCurrentItemIndex*/ ) const
	{
	// derived classes that deal with text and want to support incremental matching in
	// listboxes need to redefine this function
	return TRect();
	}

/**
 * Returns the ascent of the matcher cursor for the item at index aCurrentItemIndex determined from the 
 * ascent of the font used for that item.
 *
 * Returns 0 by default.
 */
EXPORT_C TInt CListItemDrawer::MatcherCursorAscent( TInt /*aCurrentItemIndex*/ ) const
	{
	// derived classes that deal with text and want to support incremental matching in
	// listboxes need to redefine this function
	return 0;
	}

EXPORT_C void CListItemDrawer::DrawItem(TInt aItemIndex, TPoint aItemRectPos, TBool aItemIsSelected, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed) const
	{
	_AKNTRACE_FUNC_ENTER;
	TRect actualItemRect(aItemRectPos, iItemCellSize);

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal *transApi = CAknListLoader::TfxApiInternal( iGc );
    if ( transApi )
        {
        transApi->BeginRedraw( MAknListBoxTfxInternal::EListItem, actualItemRect, aItemIndex );
        }
#endif //RD_UI_TRANSITION_EFFECTS_LIST

	DrawActualItem(aItemIndex, actualItemRect, aItemIsCurrent, aViewIsEmphasized, aViewIsDimmed, aItemIsSelected);
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        transApi->EndRedraw( MAknListBoxTfxInternal::EListItem, aItemIndex );
        }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
    _AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CListItemDrawer::DrawItemMark(TBool /*aItemIsSelected*/, TBool /*aViewIsDimmed*/, const TPoint& /*aItemRectPos*/) const
	{
        // not used in S60
	}

EXPORT_C void CListItemDrawer::ClearRect(const TRect& aRect) const
	{
	if (iGc)
		{
		iGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
		iGc->SetBrushColor(iBackColor);
		iGc->SetPenStyle(CGraphicsContext::ENullPen);
		iGc->DrawRect(aRect);
		ResetGc();
		}
	}

EXPORT_C TInt CListItemDrawer::ItemWidthInPixels(TInt /*aItemIndex*/) const
	{
	return(0);
	}

EXPORT_C void CListItemDrawer::SetDrawMark(TBool aDrawMark)
	{
	if ( aDrawMark )
		SetFlags( EDrawMarkSelection );
	else
		ClearFlags( EDrawMarkSelection );
	}

EXPORT_C TSize CListItemDrawer::MinimumCellSize() const
	{
	return TSize(0, 0);
	}

EXPORT_C void CListItemDrawer::SetSymbolFont(const CFont* aFont)
	{
	iSymbolFont = aFont;
	}

EXPORT_C void CListItemDrawer::SetVerticalInterItemGap(TInt aGapInPixels)
	{
	iVerticalInterItemGap = aGapInPixels;
	}

EXPORT_C TInt CListItemDrawer::VerticalInterItemGap() const
	{
	return iVerticalInterItemGap;
	}

EXPORT_C void CListItemDrawer::SetupGc(TInt aItemIndex) const
    {
    if (iData)
        {
        iData->SetupGc(Properties(aItemIndex),*iGc);
        }
    }

EXPORT_C TAny* CListItemDrawer::Reserved_1()
	{
	return NULL;
	}

EXPORT_C void CListItemDrawer::DrawFrame(CWindowGc& aGc,const TRect& aRect,TInt aFlags) const
	{
	LafListItemDrawer::TLidColors colors(iTextColor,iBackColor,iHighlightedTextColor,
	iHighlightedBackColor,iDimmedTextColor,iDimmedBackColor,iMarkColor);

	LafListItemDrawer::DrawFrame(aGc,aRect,aFlags,colors);
	}

//
// class CTextListItemDrawer
//

EXPORT_C CTextListItemDrawer::CTextListItemDrawer()
	{
	_AKNTRACE_FUNC_ENTER;
	iItemMarkPos = -1;
	iItemMarkReplacement.Set(KNullDesC);
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C CTextListItemDrawer::~CTextListItemDrawer()
	{
	_AKNTRACE_FUNC_ENTER;
	iItemMarkPos = -1;
	iItemMarkReplacement.Set(KNullDesC);
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C CTextListItemDrawer::CTextListItemDrawer(MTextListBoxModel* aTextListBoxModel,const CFont* aFont)
	: iModel(aTextListBoxModel), iFont(aFont),
 	iItemMarkPos(-1),
 	iItemMarkReplacement(KNullDesC)
	{
	_AKNTRACE_FUNC_ENTER;
	CEikonEnv* eikEnv=CEikonEnv::Static();
	iTextColor = eikEnv->Color(EColorControlText); // KDefaultLbxTextColor
	iHighlightedTextColor = eikEnv->Color(EColorControlHighlightText); // KDefaultLbxHighlightedTextColor
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CTextListItemDrawer::ConstructL(const CFont* aFont /*, CEikListBox* aOwnerListBox*/)
    {
    _AKNTRACE_FUNC_ENTER;
    CListBoxData* data=new(ELeave) CListBoxData();
    CleanupStack::PushL(data);
    data->ConstructL(aFont);
    CleanupStack::Pop(); // data
    SetData(data);
    _AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CTextListItemDrawer::ResetGc() const
	{
	_AKNTRACE_FUNC_ENTER;
	CListItemDrawer::ResetGc();
	iGc->SetPenColor(iTextColor);
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CTextListItemDrawer::SetGc(CWindowGc* aGc)
    {
    _AKNTRACE_FUNC_ENTER;
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    // assert that aGc is not null
    MAknListBoxTfxInternal *transApi = CAknListLoader::TfxApiInternal( iGc );
    if ( transApi )
        {
        if ( aGc )
            {
            transApi->SetGc( *aGc );
            }
        }
    else
        {
#endif //RD_UI_TRANSITION_EFFECTS_LIST
        iGc = aGc;
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        }

#endif //RD_UI_TRANSITION_EFFECTS_LIST
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TRect CTextListItemDrawer::MatcherCursorRect(const TDesC& aMatchableText,
        TInt aCharPos, TInt aItemCellYPos, TInt aCurrentItemIndex ) const
	{
    // iFont replaced with Font(currentItem)
	_AKNTRACE_FUNC_ENTER;
	TPoint cursorPos;
	TSize cursorSize;
	TPtrC stringBeforeCursor = aMatchableText.Left(aCharPos);
	TInt cursorWidth = 0;
	if (aCharPos < aMatchableText.Length())
		{
		TPtrC charAtCursor = aMatchableText.Mid(aCharPos,1);
        cursorWidth = Font(aCurrentItemIndex)->TextWidthInPixels(charAtCursor);
		}
	else
        cursorWidth = Font(aCurrentItemIndex)->MaxNormalCharWidthInPixels();
    cursorPos.iX = Font(aCurrentItemIndex)->TextWidthInPixels(stringBeforeCursor);
    if( Flags() & EDrawMarkSelection )
		cursorPos.iX += iMarkColumnWidth + iMarkGutter;
	cursorPos.iX += LafListBox::InnerGutter();
    cursorPos.iY = Font(aCurrentItemIndex)->AscentInPixels() + aItemCellYPos;
	cursorSize.iWidth = cursorWidth;
    cursorSize.iHeight = Font(aCurrentItemIndex)->HeightInPixels();
	TRect cursorRect(cursorPos, cursorSize);
	_AKNTRACE_FUNC_EXIT;
	return cursorRect;
	}

EXPORT_C TInt CTextListItemDrawer::MatcherCursorAscent( TInt aCurrentItemIndex ) const
	{
	// derived classes that deal with text and want to support incremental matching in
	// listboxes need to redefine this function

    // iFont replaced with Font(currentItem)
    return Font(aCurrentItemIndex)->AscentInPixels() - (VerticalInterItemGap()/2);
	}

EXPORT_C void CTextListItemDrawer::SetCellWidthInChars(TInt aNumOfCharsToDisplayInCell)
	{
	iNumOfCharsInCell = aNumOfCharsToDisplayInCell;
	}

EXPORT_C TSize CTextListItemDrawer::MinimumCellSize() const
	{
	//__ASSERT_DEBUG(0, Panic(EEikPanicOutOfRange));
	return TSize(0,0);
#ifdef THIS_IS_NOT_USED_IN_SERIES60
    TInt width;
    TInt height;
    
	if (iData && iData->FontBoundValues().iMaxNormalCharWidthInPixels)
        {
        //iFont->MaxNormalCharWidthInPixels() replaced with FontBoundValues().iMaxNormalCharWidthInPixels
        width = iNumOfCharsInCell * iData->FontBoundValues().iMaxNormalCharWidthInPixels;
        // iFont->HeightInPixels() replaced with FontBoundValues().iHeightInPixels
        height = iData->FontBoundValues().iHeightInPixels + VerticalInterItemGap();
        }
    else  // original code.
        {
		const CFont* font = ((iFont != NULL) ? iFont : CEikonEnv::Static()->NormalFont());
        width = iNumOfCharsInCell * font->MaxNormalCharWidthInPixels();
        height = font->HeightInPixels() + VerticalInterItemGap();
        }

	if (Flags()&CListItemDrawer::EDrawMarkSelection)
		{
		width += iMarkColumnWidth + iMarkGutter;
		}
	width+=LafListBox::InnerGutter();
	return TSize(width, height);
#endif
	}

/**
 * Draws the actual item contents for the item at index aItemIndex in the rectangle aActualItemRect.
 */
EXPORT_C void CTextListItemDrawer::DrawActualItem(TInt aItemIndex, const TRect& aActualItemRect,
        TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool /*aViewIsDimmed*/, TBool aItemIsSelected) const
	{
	_AKNTRACE_FUNC_ENTER;
	if (Properties(aItemIndex).IsSelectionHidden()) { aItemIsSelected = EFalse; }

    if ( Flags() & EDisableHighlight
            || Flags() & ESingleClickDisabledHighlight )
        {
        aItemIsCurrent = EFalse;
        }

	DrawItemText(aItemIndex,aActualItemRect,aItemIsCurrent,aViewIsEmphasized,aItemIsSelected);
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C TInt CTextListItemDrawer::ItemWidthInPixels(TInt aItemIndex) const
	{
	return CListItemDrawer::ItemWidthInPixels(aItemIndex);
#ifdef THIS_IS_NOT_USED_IN_SERIES60
	TInt itemWidth = 0;
    if ( Flags() & EDrawMarkSelection )
		itemWidth += (iMarkColumnWidth + iMarkGutter);
	TPtrC des = iModel->ItemText(aItemIndex);
	if (des.Length())
        // iFont changed to Font(aItemIndex)
        itemWidth += Font(aItemIndex)->TextWidthInPixels(des);
	return itemWidth;
#endif
	}

EXPORT_C void CTextListItemDrawer::DoDrawItemText(const TDesC& aDes, const TRect& aItemTextRect,
		TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aItemIsSelected, TInt aItemIndex) const
	{
	//TRgb penColor=iTextColor; // original
    // New. If extended item drawer is used, pen color will be set setupGc function.
    //TRgb penColor;
	//TRgb brushColor=iBackColor;
	_AKNTRACE_FUNC_ENTER;
	iGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	iGc->SetBrushColor(iBackColor); 
    if (!iData)
		{
		iGc->SetPenColor(Properties(aItemIndex).Color());
		}

	if (Properties(aItemIndex).IsDimmed()) iGc->SetBrushColor(iDimmedBackColor);
    if (Flags()&EPaintedSelection)
		{
		if ( aItemIsSelected && aViewIsEmphasized)
			{
			iGc->SetPenColor(CEikonEnv::Static()->Color(EColorControlHighlightText));
			iGc->SetBrushColor(CEikonEnv::Static()->Color(EColorControlHighlightBackground));
			}
		}
	else
		{
		if (aItemIsCurrent && aViewIsEmphasized) // original code
			{
			iGc->SetPenColor(iHighlightedTextColor);
			iGc->SetBrushColor(iHighlightedBackColor); 
			}
		}
	if (Properties(aItemIndex).IsDimmed()) iGc->SetPenColor(iDimmedTextColor);

    const TInt extraVerticalSpace=aItemTextRect.Height()-Font(aItemIndex)->HeightInPixels();
    const TInt baseLineOffset=extraVerticalSpace/2 + Font(aItemIndex)->AscentInPixels();
	CGraphicsContext::TTextAlign align = iData ? iData->Alignment() : CGraphicsContext::ELeft;

	if ( iData && iData->IsSearchString() )
		{
		iData->DrawItem(*iGc,aItemTextRect,aDes,*Font(aItemIndex),baseLineOffset,align);
		}
	else
		{
		/*Call to the laf code which is responsible for drawing a text string in a rectangle*/
		LafTextListItemDrawer::DrawNormalText(aDes,*Font(aItemIndex),*iGc,aItemTextRect,baseLineOffset,align);
		}

	TInt attribute=0;
	if (!(Flags()&EPaintedSelection))
		{
		if (aItemIsCurrent && !aViewIsEmphasized)
			attribute|=CListItemDrawer::ECurrent;
		}
	else
		{
		if (aItemIsCurrent)
			attribute|=CListItemDrawer::ECurrent;
		else if ( !(Flags()&EDrawMarkSelection) && aItemIsSelected )
			attribute|=CListItemDrawer::ESelected;
		}
	if (attribute)
	CListItemDrawer::DrawFrame(*iGc,aItemTextRect,attribute);

	ResetGc();
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C
void CTextListItemDrawer::DrawItemText( TInt aItemIndex,
                                        const TRect& aItemTextRect,
                                        TBool aItemIsCurrent,
                                        TBool aViewIsEmphasized,
                                        TBool aItemIsSelected ) const
    {
    _AKNTRACE_FUNC_ENTER;
    if (iData)
        {
        SetupGc(aItemIndex); // added
        }
    else
        {
        iGc->UseFont(iFont); // Original
        }
    
    TBufC<200> des = iModel->ItemText(aItemIndex);
    TPtrC target;
    target.Set(des);
    
    DoDrawItemText( target, aItemTextRect, aItemIsCurrent,
                    aViewIsEmphasized, aItemIsSelected, aItemIndex );

    iGc->DiscardFont();
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C inline const CFont* CTextListItemDrawer::Font(TInt aItemIndex) const
    {
    if (iData)
        return CListItemDrawer::Font(aItemIndex);
    else
		return iFont;
	}

EXPORT_C void CTextListItemDrawer::SetFont(const CFont* aFont)
	{
	iFont=aFont;
	}

EXPORT_C void CTextListItemDrawer::SetSearchStringL(const TDesC* aSearchString)
	{
	if (iData)
		iData->SetSearchStringL(aSearchString);
	}

EXPORT_C TAny* CTextListItemDrawer::Reserved_1()
	{
	return NULL;
	}














