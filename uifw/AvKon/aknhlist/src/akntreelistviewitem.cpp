/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation for TAknTreeListViewItem class.
*
*/


#include <AknUtils.h>
#include <skinlayout.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknsBasicBackgroundControlContext.h>
#include <AknsDrawUtils.h>

#include "akntreelistview.h"
#include "akntreelistviewitem.h"
#include "akntree.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Default C++ constructor.
// ---------------------------------------------------------------------------
//
TAknTreeListViewItem::TAknTreeListViewItem()
    : iItem( NULL ),
      iRect(),
      iLineSegmentRect()
    {
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
TAknTreeListViewItem::TAknTreeListViewItem( CAknTreeItem* aItem,
    const TRect& aRect )
    : iItem( aItem ),
      iRect( aRect ),
      iLineSegmentRect()
    {
    // Call this to calculate also the line segment rectangle.
    SetRect( aRect );
    }


// ---------------------------------------------------------------------------
// Copy constructor.
// ---------------------------------------------------------------------------
//
TAknTreeListViewItem::TAknTreeListViewItem( const TAknTreeListViewItem& aItem )
    : iItem( aItem.iItem ),
      iRect( aItem.iRect ),
      iLineSegmentRect( aItem.iLineSegmentRect )
    {
    }


// ---------------------------------------------------------------------------
// Returns the tree item contained in view item.
// ---------------------------------------------------------------------------
//
CAknTreeItem* TAknTreeListViewItem::Item() const
    {
    return iItem;
    }


// ---------------------------------------------------------------------------
// Sets the tree item the view item is representing.
// ---------------------------------------------------------------------------
//
void TAknTreeListViewItem::SetItem( CAknTreeItem* aItem )
    {
    iItem = aItem;
    }


// ---------------------------------------------------------------------------
// Returns the view item rectangle.
// ---------------------------------------------------------------------------
//
TRect TAknTreeListViewItem::Rect() const
    {
    return iRect;
    }


// ---------------------------------------------------------------------------
// Sets the view item rectangle.
// ---------------------------------------------------------------------------
//
void TAknTreeListViewItem::SetRect( const TRect& aRect )
    {
    iRect = aRect;
    
    // Get rectangle for structure lines.
    TInt lineVariety = 0; // Type.
    iLineSegmentRect = CAknTreeListView::RectFromLayout( aRect,
        AknLayoutScalable_Avkon::list_single_graphic_hl_pane_g1( lineVariety ) );
    }


// ---------------------------------------------------------------------------
// Returns the rectangle reserved for the tree item.
// ---------------------------------------------------------------------------
//
TRect TAknTreeListViewItem::ItemRect( TInt aViewLevel, TBool aIndention,
    TInt aIndentionWidth ) const
    {
    __ASSERT_DEBUG( aViewLevel >= NULL, User::Invariant() );

    TRect itemRect;
    if ( iItem )
        {
        TInt itemLevel = aIndention ? iItem->Level() : 1;
        TInt indentLevel = ( itemLevel - 1 ) - aViewLevel;
        TInt indentWidth = ( aIndentionWidth < 0 ) ?
            LineSegmentWidth() : aIndentionWidth;
        TInt indent = indentLevel * indentWidth;

        itemRect = TRect( TPoint( iRect.iTl.iX + indent, iRect.iTl.iY ),
            TSize( Max( iRect.Width() - indent, iItem->MinimumSize().iWidth ),
                iRect.Height() ) );

        if ( AknLayoutUtils::LayoutMirrored() )
            {
            itemRect.Move( ( iRect.iBr.iX - itemRect.iBr.iX ) - indent, 0 );
            }
        }
    return itemRect;
    }


// ---------------------------------------------------------------------------
// Returns the rectangle reserved for the tree item highlight.
// ---------------------------------------------------------------------------
//
TRect TAknTreeListViewItem::HighlightRect( TInt aViewLevel,
    TBool aIndention, TInt aIndentionWidth ) const
    {
    TRect highlightRect;
    if ( iItem )
        {
        TRect itemRect( ItemRect( aViewLevel, aIndention, aIndentionWidth ) );

        TInt variety = 0;
        highlightRect = CAknTreeListView::RectFromLayout( itemRect,
            AknLayoutScalable_Avkon::list_highlight_pane_cp34( variety ) );
        }
    return highlightRect;
    }


// ---------------------------------------------------------------------------
// Returns the rectangle for tree structure line segment at given index.
// ---------------------------------------------------------------------------
//
TRect TAknTreeListViewItem::LineSegmentRect( TUint aIndex ) const
    {
    TRect rect = iLineSegmentRect;
    if ( AknLayoutUtils::LayoutMirrored() )
        {
        rect.Move( -iLineSegmentRect.Width() * aIndex, 0 );
        }
    else
        {
        rect.Move( iLineSegmentRect.Width() * aIndex, 0 );
        }
    return rect;
    }


// ---------------------------------------------------------------------------
// Returns the width of one tree structure line segment.
// ---------------------------------------------------------------------------
//
TInt TAknTreeListViewItem::LineSegmentWidth() const
    {
    return iLineSegmentRect.Width();
    }


// ---------------------------------------------------------------------------
// Draws the tree structure lines for one list row, highlight, and item.
// ---------------------------------------------------------------------------
//
void TAknTreeListViewItem::Draw( CWindowGc& aGc, CAknTree& aTree,
    const TRect& aRect, TBool aFocused, TInt aViewLevel, 
    TBool aStructureLines, TBool aIndention, TInt aIndentionWidth ) const
    {
    if ( iItem )
        {
        const TRect itemRect =
            ItemRect( aViewLevel, aIndention, aIndentionWidth );

        // Draw the tree structure lines for the item.
        TInt itemLevel = aIndention ? iItem->Level() : 1; 
        TInt indentLevel = ( itemLevel - 1 ) - aViewLevel;
        if ( aStructureLines && indentLevel > 0 )
            {
            const CAknTreeNode* parent = iItem->Parent();

            TRect segmentRect = LineSegmentRect( --indentLevel );
         
            if ( parent->Index( iItem ) == parent->ChildCount() - 1 )
                {
                DrawLineSegment( aGc, aTree, segmentRect, ELineEnd );
                }
            else
                {
                DrawLineSegment( aGc, aTree, segmentRect, ELineBranch );
                }
 
            while ( indentLevel > 0 )
                {
                segmentRect = LineSegmentRect( --indentLevel );
                if ( parent->Parent()->Index( parent ) <
                     parent->Parent()->ChildCount() - 1 )
                    {
                    DrawLineSegment( aGc, aTree, segmentRect, ELineStraight );
                    }
                parent = parent->Parent();
                }
            }

        TRect intersection = aRect;
        intersection.Intersection( itemRect );
        
        TRect newRect( itemRect );
        newRect.iBr.iY -= iView->Offset();
        newRect.iTl.iY -= iView->Offset();
           
        iItem->Draw( aGc, newRect, intersection, aFocused );        
        }
    }


// ---------------------------------------------------------------------------
// Mediates pointer events to the contained tree item.
// ---------------------------------------------------------------------------
//
void TAknTreeListViewItem::HandlePointerEventL( 
    const TPointerEvent& aPointerEvent, TInt aViewLevel, TBool aIndention,
    TInt aIndentionWidth )
    {
    if ( iItem )
        {
        TRect itemRect = ItemRect( aViewLevel, aIndention, aIndentionWidth );
        if ( itemRect.Contains( aPointerEvent.iPosition ) )
            {
            iItem->HandlePointerEventL( aPointerEvent, itemRect );
            }
        }
    }


// ---------------------------------------------------------------------------
// Draws one segment of tree structure lines.
// ---------------------------------------------------------------------------
//
void TAknTreeListViewItem::DrawLineSegment( CWindowGc& aGc, CAknTree& aTree,
    const TRect& aSegmentRect, TLineSegmentType aType ) const
    {
    TRect newRect( aSegmentRect );
    newRect.iBr.iY -= iView->Offset();
    newRect.iTl.iY -= iView->Offset();
        
    switch( aType )
        {
        case ELineStraight:
            {
            aTree.DrawIcon( CAknTree::ELineStraightIndication,
                newRect.Size(), aGc,
                newRect.iTl, newRect.Size() );
            break;
            }
        case ELineEnd:
            {
            aTree.DrawIcon( CAknTree::ELineEndIndication,
                newRect.Size(), aGc,
                newRect.iTl, newRect.Size() );
            break;
            }
        case ELineBranch:
            {
            aTree.DrawIcon( CAknTree::ELineBranchIndication,
                newRect.Size(), aGc,
                newRect.iTl, newRect.Size() );
            break;
            }
        default:
            break;
        }
    }


// ---------------------------------------------------------------------------
// Sets view
// ---------------------------------------------------------------------------
//
void TAknTreeListViewItem::SetView( CAknTreeListView* aView )
    {
    iView = aView;
    }
    
