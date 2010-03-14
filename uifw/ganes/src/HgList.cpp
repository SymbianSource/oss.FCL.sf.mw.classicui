/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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


// INCLUDE FILES
#include <ganes/HgList.h>
#include <ganes/HgItem.h>

#include "HgLayoutData.h"
#include "HgDrawUtils.h"

#include <aknphysics.h>

#include "HgConstants.h"
#include "HgMarquee.h"

#include <AknIconUtils.h>
#include <avkon.mbg>
#include <AknUtils.h> //AknLayoutUtils
#include <gdi.h> // CFont
#include <AknsUtils.h>
#include <AknsDrawUtils.h>
#include <AknsConstants.h>
#include <AknsFrameBackgroundControlContext.h>
#include <gulicon.h>

#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>

// UI Constants

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CHgList::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CHgList::ConstructL (const TRect& aRect, RWsSession* aSession )
    {
    // Inherited classes might use some custom layout data, so lets use the
    // default one only if not yet initialized.
    if( !iLayoutData )
        iLayoutData = CHgListLayoutData::NewL();
    
    CHgScroller::ConstructL( aRect, aSession );
    
    // Activate the window, which makes it ready to be drawn
    ActivateL ( );
    }

// -----------------------------------------------------------------------------
// CHgList::CHgList()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHgList::CHgList( TInt aItemCount, 
        CGulIcon* aDefaultIcon )
: CHgScroller( aItemCount, aDefaultIcon ),
    iColor( KRgbBlack ),
    iColorBack( AKN_LAF_COLOR( 0 ) ),
    iHighlightedColor( KRgbBlack ),
    iHighlightedColorBack( AKN_LAF_COLOR( 0 ) )    
    {
    SetFlags(EHgScrollerSearchWithQWERTY); // Set QWERTY search on
    }

// -----------------------------------------------------------------------------
// CHgList::~CHgList()
// Destructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CHgList::~CHgList ( )
    {
    delete iLayoutData;
    }

// -----------------------------------------------------------------------------
// CHgList::InitItemsL()
// -----------------------------------------------------------------------------
//
void CHgList::InitItemsL()
    {
    for(TInt i = 0; i < iItemCount; ++i)
        {
        iItems.Append(CHgItem::NewL());
        }
    }

// -----------------------------------------------------------------------------
// CHgList::DrawHighlight()
// Called by Draw function to draw the higlighted item effect.
// -----------------------------------------------------------------------------
//
void CHgList::DrawHighlight( const TRect& aRect, TRgb& aTextColor ) const
    {
    // Init drawing options
    TRect outerRect( aRect );
    TRect innerRect( aRect );
    innerRect.Shrink(KListHighlightInnerRectShrink,KListHighlightInnerRectShrink);
    
    CWindowGc& gc = SystemGc();
    
    // Draw "selected item" rect for the row. Bitmaps to draw the rect are feched from 
    // current skin instance.
    if( HasHighlight() )
        {
        if( iPointerDown && !iPanning && iFocusedIndex != KErrNotFound && iSelectionToFocusedItem )
            {
            AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                        gc,
                                        outerRect,
                                        innerRect,
                                        KAknsIIDQsnFrListPressed,
                                        KAknsIIDQsnFrListCenterPressed );
            }
        else
            {
            AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                        gc,
                                        outerRect,
                                        innerRect,
                                        KAknsIIDQsnFrList,
                                        KAknsIIDQsnFrListCenter );
            }
        aTextColor = iHighlightedColor;
        }
    else if( iPointerDown && !iPanning )
        {
        AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                    gc,
                                    outerRect,
                                    innerRect,
                                    KAknsIIDQsnFrList,
                                    KAknsIIDQsnFrListCenter );
        }
    }

// -----------------------------------------------------------------------------
// CHgList::HandleSizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CHgList::HandleSizeChanged ( )
    {
    iLandscapeScrolling = EFalse; // list always scrolls in portrait mode
    iRows = iItemCount;
    
    // Resolve colors for normal and higlighted items            
    if ( AknsUtils::AvkonSkinEnabled() )
        {
        // this does not modify color unless it gets a correct one
        // no real need to check errors
        AknsUtils::GetCachedColor( 
                AknsUtils::SkinInstance(),
                iColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG6 );                
        
        AknsUtils::GetCachedColor( 
                AknsUtils::SkinInstance(),
                iHighlightedColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG10 );
        }
    iLayoutData->SetBaseLayout(AknLayoutScalable_Avkon::list_gen_pane(0));

    if( iFlags & CHgScroller::EHgScrollerFlatStatusPane )
        {
        iListOffset = TPoint(0,0);
        }
    else
        {
        TAknLayoutRect foobar;
        foobar.LayoutRect(Rect(), AknLayoutScalable_Avkon::listscroll_gen_pane(0));
        
        iWidth = foobar.Rect().Width();
        iHeight = foobar.Rect().Height();
        iListOffset = foobar.Rect().iTl;
        }
    }

// -----------------------------------------------------------------------------
// CHgList::DoDraw()
// -----------------------------------------------------------------------------
//
void CHgList::DoDraw(const TRect& /*aRect*/ ) const
    {
    // Calculate the displacement. How much of the first row is showing.
    TInt ydiff = (iViewPosition.iY-(iHeight/2))%(iRowHeight);
    
    CWindowGc& gc = SystemGc();
    
    if( iItemCount == 0 )
        {
        if( iEmptyText )
            iDrawUtils->DrawEmptyText(gc, Rect(), *iEmptyText, iColor);
        }
    else
        {
        // Get the row rect
        TAknLayoutRect layout;
        layout.LayoutRect(ListRect(), iLayoutData->ItemLayout());
        
        ResetClippingRect(gc);
        
        // Draw rows
        for(TInt i = iCurrentRow; i < iRows && i < iItems.Count(); ++i)
            {
            // Topleft position of the row.
            TPoint point(
                    0, 
                    ((i-iCurrentRow)*iRowHeight) - ydiff);

            if( i < 0 || point.iY < iListOffset.iY - layout.Rect().Height() )
                continue; // Not a real row
            else if( point.iY + iListOffset.iY > iHeight )
                break; // Row is now showing on the screen, we can stop. 
            
            
            TRect rect(layout.Rect());
            // Move to correct y-position
            rect.Move(point);
            DrawItem( i, rect );
            
            if( i!= iItems.Count() - 1)
                AknListUtils::DrawSeparator( gc, rect, iColor );
            }
        gc.CancelClippingRect();
        }
    }


void CHgList::ResetClippingRect( CWindowGc& aGc ) const
    {
    if( !(iFlags & CHgScroller::EHgScrollerFlatStatusPane) )
        aGc.SetClippingRect( TRect(iListOffset, TSize(iWidth, iHeight+2)) );
    }

// -----------------------------------------------------------------------------
// CHgList::TotalSize()
// -----------------------------------------------------------------------------
//
TSize CHgList::TotalSize() const 
    {
    return TSize( iWidth, iRows*iRowHeight );
    }

// -----------------------------------------------------------------------------
// CHgList::GetSelected()
// -----------------------------------------------------------------------------
//
TInt CHgList::GetSelected( TPoint aPosition ) const
    {
    // Real position is current screen pos + world pos
    TInt y = aPosition.iY + (iViewPosition.iY - (iHeight/2)) - iListOffset.iY;
    y /= iRowHeight;
    return y >= iItems.Count() || y < 0 ? KErrNotFound : y;
    }

// -----------------------------------------------------------------------------
// CHgList::DoHandleKeyEvent()
// -----------------------------------------------------------------------------
//
TBool CHgList::DoHandleKeyEvent(const TKeyEvent& aKeyEvent)
    {        
    TBool ret = ETrue;
    switch( aKeyEvent.iCode )
        {
        case EKeyUpArrow:
            HandleUpArrow();
            break;
        case EKeyDownArrow:
            HandleDownArrow();
            break;
        case EKeyLeftArrow:
        case EKeyRightArrow:
        default:
            ret = EFalse;
            break;
        }
    
    return ret;
    }

// -----------------------------------------------------------------------------
// CHgList::HandleDownArrow()
// -----------------------------------------------------------------------------
//
void CHgList::HandleDownArrow()
    {
    if( iSelectedIndex == KErrNotFound )
        {
        SelectDefaultItem();
        }
    else
        {
        if( iSelectedIndex <= iRows - 1 )
            {
            const TInt nextIndex = iSelectedIndex == (iRows - 1) ? 
                0 : iSelectedIndex + 1;

            if( iSelectionMode == ESelectionMark )
                {
                Mark( iSelectedIndex );
                Mark( nextIndex );
                }
            else if( iSelectionMode == ESelectionUnMark )
                {
                UnMark( iSelectedIndex );
                UnMark( nextIndex );
                }
            iSelectedIndex = nextIndex;
            FitSelectionToView();
            SelectionChanged();
            DrawDeferred();
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgList::HandleUpArrow()
// -----------------------------------------------------------------------------
//
void CHgList::HandleUpArrow()
    {    
    if( iSelectedIndex == KErrNotFound )
        {
        SelectDefaultItem();
        }
    else
        {
        if( iSelectedIndex >= 0 )
            {
            const TInt nextIndex = iSelectedIndex == 0 ? 
                iRows - 1 : iSelectedIndex - 1;
            
            if( iSelectionMode == ESelectionMark )
                {
                Mark( iSelectedIndex );
                Mark( nextIndex );
                }
            else if( iSelectionMode == ESelectionUnMark )
                {
                UnMark( iSelectedIndex );
                UnMark( nextIndex );
                }
            iSelectedIndex = nextIndex;
            FitSelectionToView();
            SelectionChanged();
            DrawDeferred();
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgList::FitSelectionToView()
// -----------------------------------------------------------------------------
//
void CHgList::FitSelectionToView()
    {
    FitRowToView( iSelectedIndex );
    }

// -----------------------------------------------------------------------------
// CHgList::ListRect()
// -----------------------------------------------------------------------------
//
TRect CHgList::ListRect() const
    {
    TRect rect(iListOffset, TSize(iWidth,iHeight));
    TAknLayoutRect areaaftersb;
    areaaftersb.LayoutRect(rect, iLayoutData->BaseLayout());
    return areaaftersb.Rect();
    }

// -----------------------------------------------------------------------------
// CHgList::SelectDefaultItem()
// -----------------------------------------------------------------------------
//
void CHgList::SelectDefaultItem()
    {
    iSelectedIndex = iCurrentRow;
    FitSelectionToView();
    SelectionChanged();

    DrawDeferred();
    }

TInt CHgList::CurrentIndex()
    {
    return iCurrentRow;
    }

TBool CHgList::IsDisplayed( TInt aIndex )
    {
    TInt start = CurrentIndex();
    TInt rowsPerView = ItemsOnScreen();
    if( (iViewPosition.iY-(iHeight/2))%(iRowHeight) )
        ++rowsPerView;
    TInt end = start + rowsPerView;
    return aIndex >= start && aIndex <= end;
    }

// -----------------------------------------------------------------------------
// CHgList::FitTopItemToView()
// -----------------------------------------------------------------------------
//
void CHgList::FitTopItemToView( TInt aIndex )
    {
    // Higlighted item is set to top of the list
    TInt newPos = aIndex*iRowHeight + iHeight/2;
    
    if( ItemsOnScreen() >= iItems.Count() )
        {
        newPos = iHeight/2;
        }
    else
        {
        const TInt endMid = TotalSize().iHeight - iHeight/2;
        if( newPos > endMid )
            {
            // We are presenting last items in the list
            newPos = endMid;
            }
        }
    
    iViewPosition.iY = newPos;
    HandleViewPositionChanged();    
    }

// End of File
