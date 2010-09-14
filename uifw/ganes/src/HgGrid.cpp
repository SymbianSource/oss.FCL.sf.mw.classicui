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
#include <ganes/HgGrid.h>
#include <ganes/HgItem.h>

#include "HgLayoutData.h"
#include "HgIndicatorManager.h"
#include "HgDrawUtils.h"


#include <aknphysics.h>

#include "HgConstants.h"

#include <AknIconUtils.h>
#include <avkon.mbg>
#include <AknUtils.h>
#include <AknsUtils.h>
#include <AknsDrawUtils.h>
#include <AknsConstants.h>
#include <gulicon.h>
#include <AknUtils.h>

#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_apps.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>

using namespace AknLayoutScalable_Apps;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CHgGrid::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CHgGrid* CHgGrid::NewL ( 
        const TRect& aRect, 
        TInt aItemCount, 
        CGulIcon* aDefaultIcon,
        RWsSession* aSession ) 
    {
    CHgGrid* self = new ( ELeave ) CHgGrid( 
            aItemCount, 
            aDefaultIcon);
    CleanupStack::PushL (self );
    self->ConstructL( aRect, aSession );
    CleanupStack::Pop (self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgGrid::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CHgGrid::ConstructL (const TRect& aRect, RWsSession* aSession )
    {
    TAknLayoutScalableParameterLimits limits = cell_gallery2_pane_ParamLimits(0);
    TInt cols = limits.LastColumn() + 1;
    iLayoutData = CHgGridLayoutData::NewL( cols );
    
    CHgScroller::ConstructL( aRect, aSession );
    
    // Activate the window, which makes it ready to be drawn
    ActivateL ( );
    }

// -----------------------------------------------------------------------------
// CHgGrid::CHgGrid()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHgGrid::CHgGrid( 
        TInt aItemCount, 
        CGulIcon* aDefaultIcon )
: CHgScroller( aItemCount, aDefaultIcon ),
  iToolbarVisible( ETrue )
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CHgGrid::~CHgGrid()
// Destructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CHgGrid::~CHgGrid ( )
    {
    delete iLayoutData;
    }

// -----------------------------------------------------------------------------
// CHgGrid::PreferredImageSize()
// -----------------------------------------------------------------------------
//
EXPORT_C TSize CHgGrid::PreferredImageSize()
    {
    TAknLayoutRect gridAppPane;
    TAknLayoutRect gridItem;
    TAknLayoutRect gridImage;
    
    gridAppPane.LayoutRect( TRect(), grid_gallery2_pane(0)); 
    gridItem.LayoutRect( gridAppPane.Rect(), cell_gallery2_pane(1, 0, 0));
    gridImage.LayoutRect(gridItem.Rect(), cell_gallery2_pane_g2(1));
    
    return gridImage.Rect().Size();
    }

// -----------------------------------------------------------------------------
// CHgGrid::InitItemsL()
// -----------------------------------------------------------------------------
//
void CHgGrid::InitItemsL()
    {
    for(TInt i = 0; i < iItemCount; ++i)
        {
        iItems.Append( CHgItem::NewL() );
        }
    }

// -----------------------------------------------------------------------------
// CHgGrid::DoDraw()
// -----------------------------------------------------------------------------
//
void CHgGrid::DoDraw (const TRect& /*aRect*/) const
    {
    // Get the standard graphics context
    TInt xdiff = (iViewPosition.iX-(iWidth/2))% (iLandscapeScrolling ? iRowHeight : iRowWidth);
    TInt ydiff = (iViewPosition.iY-(iHeight/2))%( iLandscapeScrolling ? iRowWidth : iRowHeight);

    if( iItemCount == 0 )
        {
        TRgb color( KRgbBlack );
        if ( AknsUtils::AvkonSkinEnabled() )
            {
            AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
                                          color,
                                          KAknsIIDQsnTextColors,
                                          EAknsCIQsnTextColorsCG6 );
            }
        if( iEmptyText )
            iDrawUtils->DrawEmptyText(SystemGc(), Rect(), *iEmptyText, color);
        }
    else
        {
        TAknLayoutRect gridAppPane;
        gridAppPane.LayoutRect( GridRect(), iLayoutData->ItemLayout() ); 
        
        if( iLandscapeScrolling )
            {
            if( AknLayoutUtils::LayoutMirrored() )
                {
                for(TInt i = iCurrentRow; i < iCols; ++i)
                    {
                    TInt xPos = - (((i-iCurrentRow)*iRowHeight) - xdiff); 
                    if( i < 0 )
                        continue;
                    else if( xPos  < -iWidth )
                        break;
                  
                    DrawRows( i, gridAppPane.Rect(), xPos );
                    }                        
                }
            else
                {
                for(TInt i = iCurrentRow; i < iCols; ++i)
                    {
                    TInt xPos = ((i-iCurrentRow)*iRowHeight) - xdiff; 
                    if( i < 0 )
                        continue;
                    else if( xPos > iWidth )
                        break;
                  
                    DrawRows( i, gridAppPane.Rect(), xPos );
                    }                        
                }
            }
        else
            {
            for(TInt i = iCurrentRow; i < iRows; ++i)
                {
                TInt yPos = ((i-iCurrentRow)*iRowHeight) - ydiff; 
                if( i < 0 )
                    continue;
                else if( yPos > iHeight )
                    break;
              
                DrawCols( i, gridAppPane.Rect(), yPos );
                }            
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgGrid::DrawRows()
// -----------------------------------------------------------------------------
//
void CHgGrid::DrawRows( TInt aCol, const TRect& aRect, TInt aXPos ) const
    {
    for(TInt j = 0; j < iRows; ++j)
        {
        TInt index = aCol*iRows + j;
        if( index < iItems.Count())
            {
            TAknLayoutRect gridItem;
            gridItem.LayoutRect( aRect,iLayoutData->ColumnLayout(j) );

            TRect rect(gridItem.Rect());
            rect.Move( aXPos, 0 );
            
            DrawItem( index, rect );
            }
        else
            {
            break;
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgGrid::DrawCols()
// -----------------------------------------------------------------------------
//
void CHgGrid::DrawCols(TInt aRow, const TRect& aRect, TInt aYPos) const
    {
    for(TInt j = 0; j < iCols; ++j)
        {
        TInt index = aRow*iCols + j;
        if( index < iItems.Count())
            {
            TAknLayoutRect gridItem;
            gridItem.LayoutRect( aRect,iLayoutData->ColumnLayout(j) );

            TRect rect(gridItem.Rect());
            rect.Move( 0, aYPos );
            
            DrawItem( index, rect );
            }
        else
            {
            break;
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgGrid::DoDraw()
// -----------------------------------------------------------------------------
//
void CHgGrid::DrawItem(TInt aIndex, const TRect& aRect ) const
    {
    CHgItem* item = iItems[aIndex];
    CGulIcon* icon = item->Icon() ? item->Icon() : iDefaultIcon;

    if( aIndex == iSelectedIndex )
        {
        DrawHighlight(aRect);
        }

    CWindowGc& gc = SystemGc();
    
    iDrawUtils->DrawImage(gc, aRect, iLayoutData->IconLayout(), *icon);
    
    // Draw the indicators.
    iIndicatorManager->DrawIndicators(
            gc,
            aRect, 
            item->Flags(), 
            iLayoutData->FirstIndicatorLayout(), 
            iLayoutData->SecondIndicatorLayout(),
            iFlags & EHgScrollerSelectionMode || iSelectionMode != ENoSelection );            
    }

// -----------------------------------------------------------------------------
// CHgGrid::HandleSizeChanged()
// -----------------------------------------------------------------------------
//
void CHgGrid::HandleSizeChanged ( )
    {    
    iLandscapeScrolling = Layout_Meta_Data::IsLandscapeOrientation() && iLandScapeScrollingSupported;

    TInt oldCount = iLandscapeScrolling ? iRows : iCols;
    
    CalculateSizes();
    
    if( iLandscapeScrolling )
        {
        iCols = iItemCount / iRows;
        if(iItemCount%iRows)
            {
            ++iCols; // partially filled col
            }        
        
        iItemsOnScreen = iWidth / iRowHeight;
        if((iWidth % iRowHeight))
            iItemsOnScreen += 2;
        else
            iItemsOnScreen++;

        iItemsOnScreen *= iRows;

        FitTopItemToView( iCurrentRow*oldCount );        
        }
    else
        {
        iRows = iItemCount / iCols;
        if(iItemCount%iCols)
            {
            ++iRows; // partially filled row
            }        

        iItemsOnScreen = iHeight / iRowHeight;
        if((iHeight % iRowHeight))
            iItemsOnScreen += 2;
        else
            iItemsOnScreen++;

        iItemsOnScreen *= iCols;

        FitTopItemToView( iCurrentRow*oldCount );        
        }        
    }

// -----------------------------------------------------------------------------
// CHgGrid::CalculateSizes()
// -----------------------------------------------------------------------------
//
void CHgGrid::CalculateSizes()
    {
    // Count number of visible rows
    // First is checked if 3x4 or 4x3 items fits to the grid.

    TInt mainVariety = iToolbarVisible ? 0 : 1;
    TInt gridVariety = iToolbarVisible ? 0 : 2;
    TInt cellVariety = iToolbarVisible ? 0 : 4;

    if( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        ++gridVariety;
        ++cellVariety;
        }
    
    TAknLayoutScalableParameterLimits limits = cell_gallery2_pane_ParamLimits(cellVariety);
    iCols = limits.LastColumn() + 1;
    iRows = limits.LastRow() + 1;
    
    iLayoutData->ChangeCols( iCols );
    
    iLayoutData->SetBaseLayout(main_gallery2_pane(mainVariety));
    iLayoutData->SetItemLayout(grid_gallery2_pane(gridVariety));
    iLayoutData->SetIconLayout(cell_gallery2_pane_g2(cellVariety));        
    
    if( iLandscapeScrolling )
        {
        for(TInt i = 0; i < iRows; ++i)
            {
            iLayoutData->SetColumnLayout(i, cell_gallery2_pane(cellVariety, 0, i));            
            }
        }
    else
        {
        for(TInt i = 0; i < iCols; ++i)
            {
            iLayoutData->SetColumnLayout(i, cell_gallery2_pane(cellVariety, i, 0));            
            }
        }
    iLayoutData->SetFirstIndicatorLayout(cell_gallery2_pane_g5(cellVariety));
    iLayoutData->SetSecondIndicatorLayout(cell_gallery2_pane_g4(cellVariety));
    
    TAknLayoutRect gridAppPane;
    TAknLayoutRect gridItem;
    TAknLayoutRect gridImage;
    
    gridAppPane.LayoutRect( GridRect(),  iLayoutData->ItemLayout()); 
    gridItem.LayoutRect( gridAppPane.Rect(),  iLayoutData->ColumnLayout(0));
    gridImage.LayoutRect( gridItem.Rect(),  iLayoutData->IconLayout());
    
    if( iLandscapeScrolling )
        {
        iRowHeight = gridItem.Rect().Width();
        iRowWidth = gridItem.Rect().Height();        
        }
    else
        {
        iRowHeight = gridItem.Rect().Height();
        iRowWidth = gridItem.Rect().Width();        
        }

    iImageSize = gridImage.Rect().Size();

    TAknLayoutRect indicator;
    indicator.LayoutRect( gridItem.Rect(), iLayoutData->FirstIndicatorLayout() );
    iIndicatorSize = indicator.Rect().Size();
    }

// -----------------------------------------------------------------------------
// CHgGrid::GetSelected()
// -----------------------------------------------------------------------------
//
TInt CHgGrid::GetSelected( TPoint aPosition ) const
    {
    TAknLayoutRect gridAppPane;
    gridAppPane.LayoutRect( GridRect(), iLayoutData->ItemLayout()); 
    aPosition -= gridAppPane.Rect().iTl;
    
    TInt index = 0;
    if( iLandscapeScrolling )
        {
        TInt y = aPosition.iY + ((iViewPosition.iY - (iHeight/2)) % iRowWidth);
        y /= iRowWidth;
        TInt x = 0;
        if( AknLayoutUtils::LayoutMirrored() )
            {
            x = aPosition.iX - ((iViewPosition.iX - (iWidth/2)) % iRowHeight);

            if(x < 0) // to correct the division
                x-= iRowHeight;
            x /= iRowHeight;
            x = ((iWidth / iRowHeight) - 1) - x; // mirrored correction to x
            }
        else
            {
            x = aPosition.iX + ((iViewPosition.iX - (iWidth/2)) % iRowHeight);
            x /= iRowHeight;
            }
        index = (iCurrentRow*iRows) + (x*iRows) + y;        
        }
    else
        {
        TInt x = aPosition.iX + ((iViewPosition.iX - (iWidth/2)) % iRowWidth);
        TInt y = aPosition.iY + ((iViewPosition.iY - (iHeight/2)) % iRowHeight);
        x /= iRowWidth;
        y /= iRowHeight;
        
        if( AknLayoutUtils::LayoutMirrored() )
            {
            x = (iCols - 1) - x;
            }

        index = (iCurrentRow*iCols) + (y*iCols) + x;        
        }
    

    return index >= iItems.Count() || index < 0 ? KErrNotFound : index;
    }

// -----------------------------------------------------------------------------
// CHgGrid::TotalSize()
// -----------------------------------------------------------------------------
//
TSize CHgGrid::TotalSize() const
    {
    return iLandscapeScrolling ? TSize( iCols*iRowHeight, iHeight ) : TSize(iWidth, iRows*iRowHeight);
    }

// -----------------------------------------------------------------------------
// CHgGrid::DrawHighlight()
// -----------------------------------------------------------------------------
//
void CHgGrid::DrawHighlight( const TRect& aOuterRect ) const
    {
    TRect innerRect( aOuterRect );
    innerRect.Shrink(2,2);

    CWindowGc& gc = SystemGc();

    if( HasHighlight() )
        {
        if( iPointerDown && !iPanning && iFocusedIndex != KErrNotFound && iSelectionToFocusedItem )
            {
            AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                   gc,
                   aOuterRect,
                   innerRect,
                   KAknsIIDQsnFrGridPressed,
                   KAknsIIDQsnFrGridCenterPressed );        
            }
        else
            {
            AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                   gc,
                   aOuterRect,
                   innerRect,
                   KAknsIIDQsnFrGrid,
                   KAknsIIDQsnFrGridCenter );        
            }
        }
    else if( iPointerDown && !iPanning )
        {
        AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
               gc,
               aOuterRect,
               innerRect,
               KAknsIIDQsnFrGrid,
               KAknsIIDQsnFrGridCenter );        
        }
    }

// -----------------------------------------------------------------------------
// CHgGrid::DoHandleKeyEvent()
// -----------------------------------------------------------------------------
//
TBool CHgGrid::DoHandleKeyEvent( const TKeyEvent& aEvent )
    {
    TBool ret = ETrue;
    switch( aEvent.iCode )
        {
        case EKeyUpArrow:
            HandleUpArrow();
            break;
        case EKeyDownArrow:
            HandleDownArrow();
            break;
        case EKeyLeftArrow:
            HandleLeftArrow();
            break;
        case EKeyRightArrow:
            HandleRightArrow();
            break;
        default:
            ret = EFalse;
            break;
        }    
    
    return ret;
    }

// -----------------------------------------------------------------------------
// CHgGrid::HandleDownArrow()
// -----------------------------------------------------------------------------
//
void CHgGrid::HandleDownArrow()
    {
    if( iSelectedIndex == KErrNotFound )
        {
        SelectDefaultItem();
        }
    else
        {
        if( iLandscapeScrolling )
            {
            ChangeSelectedIndex( 1 );
            }
        else
            {
            ChangeSelectedIndex( iCols );
            }
        FitSelectionToView();
        SelectionChanged();
        DrawDeferred();
        }
    }

// -----------------------------------------------------------------------------
// CHgGrid::GridRect()
// -----------------------------------------------------------------------------
//
TRect CHgGrid::GridRect() const
    {
    TAknLayoutRect listscrollAppPane;
    listscrollAppPane.LayoutRect( Rect(), iLayoutData->BaseLayout()); 
    return listscrollAppPane.Rect();
    }

// -----------------------------------------------------------------------------
// CHgGrid::HandleUpArrow()
// -----------------------------------------------------------------------------
//
void CHgGrid::HandleUpArrow()
    {
    if( iSelectedIndex == KErrNotFound )
        {
        SelectDefaultItem();
        }
    else
        {
        if( iLandscapeScrolling )
            {
            ChangeSelectedIndex( -1 );
            }
        else
            {
            ChangeSelectedIndex( -iCols );
            }
        FitSelectionToView();
        SelectionChanged();
        DrawDeferred();
        }
    }

// -----------------------------------------------------------------------------
// CHgGrid::HandleRightArrow()
// -----------------------------------------------------------------------------
//
void CHgGrid::HandleRightArrow()
    {
    if( iSelectedIndex == KErrNotFound )
        {
        SelectDefaultItem();
        }
    else
        {
        TInt mul = AknLayoutUtils::LayoutMirrored() ? -1 : 1; 
        if( iLandscapeScrolling )
            {
            ChangeSelectedIndex( mul * iRows );
            }
        else
            {
            ChangeSelectedIndex( mul );
            }
        FitSelectionToView();
        SelectionChanged();
        DrawDeferred();
        }
    }

// -----------------------------------------------------------------------------
// CHgGrid::HandleLeftArrow()
// -----------------------------------------------------------------------------
//
void CHgGrid::HandleLeftArrow()
    {
    if( iSelectedIndex == KErrNotFound )
        {
        SelectDefaultItem();
        }
    else
        {
        TInt mul = AknLayoutUtils::LayoutMirrored() ? 1 : -1; 
        if( iLandscapeScrolling )
            {
            ChangeSelectedIndex( mul * iRows );
            }
        else
            {
            ChangeSelectedIndex( mul );
            }
        FitSelectionToView();
        SelectionChanged();
        DrawDeferred();
        }
    }

// -----------------------------------------------------------------------------
// CHgGrid::FitSelectionToView()
// -----------------------------------------------------------------------------
//
void CHgGrid::FitSelectionToView()
    {
    const TInt index = iLandscapeScrolling ? 
        iSelectedIndex/iRows : iSelectedIndex/iCols;
    FitRowToView( index );
    }

// -----------------------------------------------------------------------------
// CHgGrid::SelectDefaultItem()
// -----------------------------------------------------------------------------
//
void CHgGrid::SelectDefaultItem()
    {
    iSelectedIndex = CurrentIndex();
    if( iSelectedIndex >= 0 && iSelectedIndex < iItems.Count() )
        {
        FitSelectionToView();
        DrawDeferred();
        }
    }

// -----------------------------------------------------------------------------
// CHgGrid::CurrentIndex()
// -----------------------------------------------------------------------------
//
TInt CHgGrid::CurrentIndex()
    {
    return iLandscapeScrolling ? iCurrentRow * iRows : iCurrentRow * iCols;
    }

// -----------------------------------------------------------------------------
// CHgGrid::IsDisplayed()
// -----------------------------------------------------------------------------
//
TBool CHgGrid::IsDisplayed( TInt aIndex )
    {
    TInt start = CurrentIndex();
    TInt end = start + iItemsOnScreen;
    return aIndex >= start && aIndex < end;
    }

// -----------------------------------------------------------------------------
// CHgGrid::FitTopItemToView()
// -----------------------------------------------------------------------------
//
void CHgGrid::FitTopItemToView( TInt aIndex )
    {
    if( iLandscapeScrolling )
        {
        // Higlighted item is set to top of the list
        const TInt newCol = aIndex/iRows;
        TInt newPos = newCol*iRowWidth + iWidth/2;
        
        if( ItemsOnScreen() >= iItems.Count() )
            {
            newPos = iWidth/2;
            }
        else
            {
            const TInt endMid = TotalSize().iWidth - iWidth/2;
            if( newPos > endMid )
                {
                // We are presenting last items in the list
                newPos = endMid;
                }
            }
        
        iViewPosition.iX = newPos;        
        }
    else
        {            
        // Higlighted item is set to top of the list
        const TInt newRow = aIndex/iCols;
        TInt newPos = newRow*iRowHeight + iHeight/2;
        
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
        }
    
    HandleViewPositionChanged();    
    }

// -----------------------------------------------------------------------------
// CHgGrid::SetLandscapeScrollingSupport()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgGrid::SetLandscapeScrollingSupport( TBool aSupportLandscapeScrolling )
    {
    iLandScapeScrollingSupported = aSupportLandscapeScrolling;
    }

// -----------------------------------------------------------------------------
// CHgGrid::ChangeSelectedIndex()
// -----------------------------------------------------------------------------
//
void CHgGrid::ChangeSelectedIndex( TInt aMove )
    {
    TInt nextIndex = 0;
    if( iSelectedIndex + aMove > iItems.Count() - 1 )
        {
        // go to beginning
        nextIndex = 0;
        }
    else if( iSelectedIndex + aMove < 0 )
        {
        // go to end
        nextIndex = iItems.Count() - 1;
        }
    else
        {
        nextIndex = iSelectedIndex + aMove;
        }
    
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
    }

// -----------------------------------------------------------------------------
// CHgGrid::HandleScrollbarVisibilityChange()
// -----------------------------------------------------------------------------
//
void CHgGrid::HandleScrollbarVisibilityChange( TBool /*aVisible*/ )
    {
    
    }

// -----------------------------------------------------------------------------
// CHgGrid::SetToolbarVisibility()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgGrid::SetToolbarVisibility( TBool aToolbarVisible )
    {
    iToolbarVisible = aToolbarVisible;
    HandleSizeChanged();
    }

// End of File
