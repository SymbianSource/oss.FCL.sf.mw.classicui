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
* Description:  Hierarchical list view item.
*
*/


#ifndef T_AKNTREELISTVIEWITEM_H
#define T_AKNTREELISTVIEWITEM_H


#include <e32std.h>

class CAknTreeItem;
class CWindowGc;
class CAknTreeListView;

/**
 *  Tree list view element responsible for drawing a row in tree list view.
 *
 *  Each tree list view item contains a pointer to a tree list item that it is
 *  representing in the view and a rectangle for the list item. The view item
 *  is responsible for drawing the highlight for the focused item, the tree
 *  structure lines for the tree list item, and mediating the redraw request
 *  to the actual tree item with appropriate parameters.
 *
 *  @lib aknhlist.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TAknTreeListViewItem )
    {

public:

    /** Types for hierarchical list tree structure line segments. */
    enum TLineSegmentType
        {
        /** Straight line segment. */
        ELineStraight,
        /** Angled ending line segment. */
        ELineEnd,
        /** Branching line segment. */
        ELineBranch
        };

    /**
     * Default C++ constructor.
     */
    TAknTreeListViewItem();

    /**
     * C++ Constructor.
     *
     * @param aItem Tree item.
     *
     * @param aRect Rectangle of the view item.
     */
    TAknTreeListViewItem( CAknTreeItem* aItem, const TRect& aRect );

    /**
     * Copy constructor.
     *
     * @param aItem The instance to be copied.
     */
    TAknTreeListViewItem( const TAknTreeListViewItem& aItem );

    /**
     * Returns the tree item.
     *
     * @return The tree item. @c NULL, if not set.
     */
    CAknTreeItem* Item() const;

    /**
     * Sets the tree item.
     *
     * @param aItem Tree item.
     */
    void SetItem( CAknTreeItem* aItem );

    /** 
     * Returns the rectangle set for the view item.
     *
     * @return Size and position of the view item as rectangle.
     */
    TRect Rect() const;

    /**
     * Sets the rectangle for the view item.
     *
     * @param aRect Rectangle specifying the size and position of the view item.
     */
    void SetRect( const TRect& aRect );
    
    
    /**
     * Sets the pointer to CAknTreeListView for the view item.
     *
     * @param aView Pointer to CAknTreeListView instance
     */
    void SetView( CAknTreeListView* aView );


    /**
     * Returns the rectangle for the tree item.
     *
     * @param aViewLevel The horizontal position of the view as indent steps.
     *
     * @param aIndention Specifies whether indention of items is enabled.
     *
     * @param aIndentionWidth Width of single indention step. Negative, if
     *      default indention width is to be used.
     *
     * @return The rectange for the tree item.
     */
    TRect ItemRect( TInt aViewLevel, TBool aIndention,
        TInt aIndentionWidth ) const;

    /**
     * Returns the highlight rectangle for the item.
     *
     * @param aViewLevel The horizontal position of the view as indent steps.
     *
     * @param aIndention Specifies whether indention of items is enabled.
     *
     * @param aIndentionWidth Width of single indention step. Negative, if
     *      default indention width is to be used.
     *
     * @return The highlight rectangle.
     */
    TRect HighlightRect( TInt aViewLevel, TBool aIndention,
        TInt aIndentionWidth ) const;

    /**
     * Returns the rectangle for tree structure line segment at the specified
     * horizontal position of the row.
     *
     * @param aIndex Index specifiyin the horizontal position of the
     *      requested line segment rectangle.
     *
     * @return Requested tree structure line segment rectangle.
     */
    TRect LineSegmentRect( TUint aIndex ) const;

    /**
     * Returns the width of one segment of tree structure lines. This value is
     * used to determine how much each tree item should be intended depending
     * on their position in tree structure.
     *
     * @return Width of one segment of tree structure lines.
     */
    TInt LineSegmentWidth() const;

    /**
     * Draws the view item.
     *
     * @param aGc Graphic context.
     *
     * @param aTree Reference to the tree structure.
     *
     * @param aRect The rectangle that needs to be redrawn.
     * 
     * @param aHighlight @c ETrue, if the item has highlight.
     *
     * @param aViewLevel Current level (horizontal position) of the view.
     *
     * @param aStructureLines @c ETrue, if the tree structure lines are to
     *      be drawn.
     *
     * @param aIndention Specifies whether indention of items is enabled.
     *
     * @param aIndentionWidth Width of single indention step. Negative, if
     *      default indention width is to be used.
     */
    void Draw( CWindowGc& aGc, CAknTree& aTree, const TRect& aRect,
        TBool aHighlight, TInt aViewLevel, TBool aStructureLines,
        TBool aIndention, TInt aIndentionWidth ) const;

    /**
     * Handles pointer events.
     *
     * @param aPointerEvent Pointer event.
     *
     * @param aViewLevel The current horizontal position of the view.
     *
     * @param aIndention Specifies whether indention of items is enabled.
     *
     * @param aIndentionWidth Width of single indention step. Negative, if
     *      default indention width is to be used.
     */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent,
        TInt aViewLevel, TBool aIndention, TInt aIndentionWidth );

private:

    /**
     * Draws a segment of hierarchical structure lines to appointed graphic
     * context.
     *
     * @param aGc Graphic context.
     *
     * @param aTree Reference to the tree structure.
     *
     * @param aSegmentRect Rectangle on graphic context co-ordinates to which
     *      the tree structure line segement is drawn.
     *
     * @param aType Type of the tree structure line segment to be drawn.
     */
    void DrawLineSegment( CWindowGc& aGc, CAknTree& aTree,
        const TRect& aSegmentRect, TLineSegmentType aType ) const;

    /**
     * Assignement operator.
     */
    TAknTreeListViewItem& operator=( const TAknTreeListViewItem& );

private: // data

    /**
     * Pointer to tree item represented by this view item. 
     * Not own.
     */
    CAknTreeItem* iItem;

    /**
     * Rectangle assigned for the view item.
     */
    TRect iRect;
    
    /**
     * The rectangle for the first segment of tree structure lines.
     */ 
    TRect iLineSegmentRect;
    
    /**
     * CAknTreeListView
     */
    CAknTreeListView* iView;

    };


#endif // T_AKNTREELISTVIEWITEM_H
