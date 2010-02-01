/*
* Copyright (c) 2006, 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation for hierarchical list base class.
*
*/


#include <akntreelistobserver.h>
#include <AknsConstants.h>

#include <AknTasHook.h> // for testability hooks
#include "akntreelist.h"
#include "akntreelistview.h"
#include "akntree.h"

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
#include <aknlistboxtfxinternal.h> // LISTBOX EFFECTS IMPLEMENTATION
#include <aknlistloadertfx.h>
#endif
const TInt KObserverArrayGranularity = 1;
const TInt KNotInNotificationSequence = -1;


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknTreeList::~CAknTreeList()
    {
    AKNTASHOOK_REMOVE();
    iObservers.Close();
    delete iTree;
    delete iView;
    }


// ---------------------------------------------------------------------------
// Sets the flags for the list.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::SetFlags( TUint32 aFlags )
    {
    TUint32 diff = aFlags ^ iFlags;
    if ( diff & KAknTreeListLooping )
        {
        View().SetLooping( aFlags & KAknTreeListLooping );
        }

    if ( diff & KAknTreeListNoStructureLines )
        {
        View().SetStructureLineVisibility( 
            !( aFlags & KAknTreeListNoStructureLines ) );
        }

    if ( diff & KAknTreeListMarqueeScrolling )
        {
        Tree().EnableMarquee( aFlags & KAknTreeListMarqueeScrolling );
        }

    if ( diff & KAknTreeListNoIndention )
        {
        View().EnableIndention( !( aFlags & KAknTreeListNoIndention ) );
        }

    if ( diff & KAknTreeListMarkable )
        {
        View().EnableMarking( aFlags & KAknTreeListMarkable );
        }

    iFlags = aFlags;
    }


// ---------------------------------------------------------------------------
// Returns the flags set for the list.
// ---------------------------------------------------------------------------
//
EXPORT_C TUint32 CAknTreeList::Flags() const
    {
    return iFlags;
    }


// ---------------------------------------------------------------------------
// Moves the specified item to specfied target node.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::MoveItemL( TAknTreeItemID aItem,
    TAknTreeItemID aTargetNode, TBool aDrawNow )
    {
    if ( aItem != KAknTreeIIDNone && aTargetNode != KAknTreeIIDNone )
        {
        Tree().MoveItemL( aItem, aTargetNode, aDrawNow );
        }
    else if ( aDrawNow )
        {
        // Redraw is requested, although no item is moved.
        Window().Invalidate( View().Rect() );
        }
    }


// ---------------------------------------------------------------------------
// Removes the specified item from the tree.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::RemoveItem( TAknTreeItemID aItem, TBool aDrawNow )
    {
    if ( aItem != KAknTreeIIDNone )
        {
        Tree().RemoveItem( aItem, aDrawNow );
        }
    else if ( aDrawNow )
        {
        // Redraw is requested, although no item is removed.
        Window().Invalidate( View().Rect() );
        }
    }


// ---------------------------------------------------------------------------
// Expands the specified node.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::ExpandNode( TAknTreeItemID aNode, TBool aDrawNow )
    {
    Tree().ExpandNode( aNode, aDrawNow );
    }


// ---------------------------------------------------------------------------
// Collapses the specified node.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::CollapseNode( TAknTreeItemID aNode, TBool aDrawNow )
    {
    Tree().CollapseNode( aNode, aDrawNow );
    }


// ---------------------------------------------------------------------------
// Checks whether the specified node is expanded.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknTreeList::IsExpanded( TAknTreeItemID aNode ) const
    {
    return Tree().IsExpanded( aNode );
    }


// ---------------------------------------------------------------------------
// Returns the item ID of focused item.
// ---------------------------------------------------------------------------
//
EXPORT_C TAknTreeItemID CAknTreeList::FocusedItem() const
    {
    return Tree().Id( View().FocusedItem() );
    }


// ---------------------------------------------------------------------------
// Sets the focused item.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::SetFocusedItem( TAknTreeItemID aItem,
    TInt aIndex, TBool aDrawNow )
    {
    View().SetFocusedItem( Tree().Item( aItem ), aIndex, aDrawNow );
    }


// ---------------------------------------------------------------------------
// Returns the highlight rectangle of currently focused item.
// ---------------------------------------------------------------------------
//
EXPORT_C TRect CAknTreeList::HighlightRect() const
    {
    return View().HighlightRect();
    }


// ---------------------------------------------------------------------------
// Adds icon to the tree.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknTreeList::AddIconL( const TAknsItemID& aId,
    const TDesC& aFilename, TInt aBitmapId, TInt aMaskId,
    TScaleMode aScaleMode )
    {
    return Tree().AddIconL( aId, aFilename, aBitmapId, aMaskId, aScaleMode );
    }


// ---------------------------------------------------------------------------
// Adds icon to the tree. This overload gets only the bitmaps instead of 
// parameters for creating the bitmaps.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknTreeList::AddIconL( CFbsBitmap* aIcon, CFbsBitmap* aMask,
    TBool aTransferOwnership, TScaleMode aScaleMode )
    {
    return Tree().AddIconL( aIcon, aMask, aTransferOwnership, aScaleMode );
    }


// ---------------------------------------------------------------------------
// Adds colored icon to the tree.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknTreeList::AddColorIconL( const TAknsItemID& aId,
    const TAknsItemID& aColorId, TInt aColorIndex, const TDesC& aFilename,
    TInt aBitmapId, TInt aMaskId, TRgb aDefaultColor, TScaleMode aScaleMode )
    {
    return Tree().AddColorIconL( aId, aColorId, aColorIndex, aFilename,
        aBitmapId, aMaskId, aDefaultColor, aScaleMode );
    }


// ---------------------------------------------------------------------------
// Assigns icon for specified icon ID.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::AssignIconL( TInt aIconId, const TAknsItemID& aId,
    const TDesC& aFilename, TInt aBitmapId, TInt aMaskId,
    TScaleMode aScaleMode )
    {
    if ( aIconId <= AknTreeListIconID::KLineStraightIndication )
        {
        // Specified icon ID is out of allowed range.
        User::Leave( KErrArgument );
        }

    Tree().SetIconL( aIconId, aId, aFilename, aBitmapId, aMaskId, aScaleMode );
    }


// ---------------------------------------------------------------------------
// Assigns icon for specified icon ID.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::AssignIconL( TInt aIconId, CFbsBitmap* aIcon,
    CFbsBitmap* aMask, TBool aTransferOwnership, TScaleMode aScaleMode )
    {
    if ( aIconId <= AknTreeListIconID::KLineStraightIndication )
        {
        // Specified icon ID is out of allowed range.
        User::Leave( KErrArgument );
        }

    Tree().SetIconL( aIconId, aIcon, aMask, aTransferOwnership, aScaleMode );
    }


// ---------------------------------------------------------------------------
// Assigns color icon for specified icon ID.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::AssignColorIconL( TInt aIconId,
    const TAknsItemID& aId, const TAknsItemID& aColorId, TInt aColorIndex,
    const TDesC& aFilename, TInt aBitmapId, TInt aMaskId, TRgb aDefaultColor,
    TScaleMode aScaleMode )
    {
    if ( aIconId <= AknTreeListIconID::KLineStraightIndication )
        {
        // Specified icon ID is out of allowed range.
        User::Leave( KErrArgument );
        }

    Tree().SetColorIconL( aIconId, aId, aColorId, aColorIndex, aFilename,
        aBitmapId, aMaskId, aDefaultColor, aScaleMode );
    }


// ---------------------------------------------------------------------------
// Removes previously added icon from the tree.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::RemoveIconL( TInt aIconId )
    {
    Tree().RemoveIconL( aIconId );
    }


// ---------------------------------------------------------------------------
// Returns the child count for specified node.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknTreeList::ChildCount( TAknTreeItemID aNode ) const
    {
    return Tree().ChildCount( aNode );
    }


// ---------------------------------------------------------------------------
// Returns the specified child.
// ---------------------------------------------------------------------------
//
EXPORT_C TAknTreeItemID CAknTreeList::Child( TAknTreeItemID aNode,
                                             TInt aIndex ) const
    {
    return Tree().Child( aNode, aIndex );
    }


// ---------------------------------------------------------------------------
// Returns the ID of specified item's parent.
// ---------------------------------------------------------------------------
//
EXPORT_C TAknTreeItemID CAknTreeList::Parent( TAknTreeItemID aItem ) const
    {
    return Tree().Parent( aItem );
    }


// ---------------------------------------------------------------------------
// Returns whether the list contains the specified item.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknTreeList::Contains( TAknTreeItemID aItem ) const
    {
    CAknTreeItem* item;
    TInt error = Tree().GetItem( aItem, item );
    if ( !error )
        {
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }


// ---------------------------------------------------------------------------
// Checks whether the specified item is a node.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknTreeList::IsNode( TAknTreeItemID aItem ) const
    {
    CAknTreeItem* item = Tree().Item( aItem );
    return item->IsNode();
    }


// ---------------------------------------------------------------------------
// Checks whether the specified item is a leaf.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknTreeList::IsLeaf( TAknTreeItemID aItem ) const
    {
    CAknTreeItem* item = Tree().Item( aItem );
    return item->IsLeaf();
    }


// ---------------------------------------------------------------------------
// Checks whether the specified item is marked.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknTreeList::IsMarked( TAknTreeItemID aItem ) const
    {
    return Tree().IsMarked( aItem );
    }


// ---------------------------------------------------------------------------
// Changes the specified item marked or unmarked.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::SetMarked( TAknTreeItemID aItem,
    TBool aMarked, TBool aDrawNow )
    {
    if ( aItem != KAknTreeIIDNone )
        {
        Tree().SetMarked( aItem, aMarked, aDrawNow );
        }
    else if ( aDrawNow )
        {
        Window().Invalidate( View().Rect() );
        }
    }


// ---------------------------------------------------------------------------
// Enables/disables marking for specified list item.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::EnableMarking( TAknTreeItemID aItem,
    TBool aEnable )
    {
    Tree().EnableMarking( aItem, aEnable );
    }


// ---------------------------------------------------------------------------
// Appends all the marked item from the list to the given array.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::GetMarkedItemsL(
    RArray<TAknTreeItemID>& aMarkedItems ) const
    {
    Tree().GetMarkedItemsL( KAknTreeIIDRoot, aMarkedItems );
    }


// ---------------------------------------------------------------------------
// Appends marked items from the specified node to the given array.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::GetMarkedItemsL( TAknTreeItemID aNode,
    RArray<TAknTreeItemID>& aMarkedItems ) const
    {
    Tree().GetMarkedItemsL( aNode, aMarkedItems );
    }


// ---------------------------------------------------------------------------
// Returns whether the specified node is empty.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknTreeList::IsEmpty( TAknTreeItemID aNode ) const
    {
    return Tree().IsEmpty( aNode );
    }


// ---------------------------------------------------------------------------
// Sets the specified item to appear non-empty, or removes the setting.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::SetNonEmpty( TAknTreeItemID aNode,
    TBool aNonEmpty, TBool aDrawNow )
    {
    Tree().SetNonEmpty( aNode, aNonEmpty, aDrawNow );
    }


// ---------------------------------------------------------------------------
// Checks whether the specified item is persistent.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknTreeList::IsPersistent( TAknTreeItemID aItem ) const
    {
    return Tree().IsPersistent( aItem );
    }


// ---------------------------------------------------------------------------
// Sets the specified item persistent or non-persistent.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::SetPersistent( TAknTreeItemID aItem,
    TBool aPersistent )
    {
    Tree().SetPersistent( aItem, aPersistent );
    }


// ---------------------------------------------------------------------------
// Sets the interface used for custom tree ordering.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::Sort( MAknCustomTreeOrdering* aOrdering,
    TBool aDrawNow )
    {
    // move view to beginning, lose focus
    View().SetFocusBehaviour( EFalse );
    
    Tree().SetCustomOrdering( aOrdering, aDrawNow );
    }


// ---------------------------------------------------------------------------
// Sorts the specified node content with previously set ordering.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::Sort( TAknTreeItemID aNode,
    TBool aSortDescendants, TBool aDrawNow )
    {
    // move view to beginning, lose focus
    View().SetFocusBehaviour( EFalse );
    
    Tree().Sort( aNode, aSortDescendants, aDrawNow );
    }


// ---------------------------------------------------------------------------
// Adds the observer to the list of observers.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::AddObserverL( MAknTreeListObserver* aObserver )
    {
    // Append observer to the end of the array. This does not affect the
    // index used in notification sequence.
    iObservers.AppendL( aObserver );
    }


// ---------------------------------------------------------------------------
// Removes the specified observer from the list of observers.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::RemoveObserver( MAknTreeListObserver* aObserver )
    {
    TInt index = iObservers.Find( aObserver );
    if ( index != KErrNotFound )
        {
        iObservers.Remove( index );
        }
    }


// ---------------------------------------------------------------------------
// Notifies all of the tree list observers of the specified event.
// ---------------------------------------------------------------------------
//
void CAknTreeList::NotifyObservers( MAknTreeListObserver::TEvent aEvent,
    TAknTreeItemID aItem )
    {
    // Note: Local variable index is used instead of iIndex
    // Nested calls to NotifyObservers don't work with iIndex
    for ( TInt index = 0; index < iObservers.Count(); ++index )
        {
        iObservers[index]->HandleTreeListEvent( *this, aItem, aEvent );
        }

    // Change index to indicate that no notification sequence is ongoing.
    iIndex = KNotInNotificationSequence;

    // Notify also control observer.
    if ( Observer() )
        {
        TRAP_IGNORE( Observer()->HandleControlEventL( this,
            MCoeControlObserver::EEventStateChanged ) );
        }
    }


// ---------------------------------------------------------------------------
// Checks whether tabulator mode function indicators are used.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknTreeList::TabModeFunctionIndicators() const
    {
    return Tree().TabModeFunctionIndicators();
    }


// ---------------------------------------------------------------------------
// Changes expand and collapse function indicators.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTreeList::EnableTabModeFunctionIndicatorsL( TBool aEnable )
    {
    Tree().EnableTabModeFunctionIndicatorsL( aEnable );
    }
    
// ---------------------------------------------------------------------------
//  Sets the focused item and moves view so that focused item is visible
// ---------------------------------------------------------------------------
//    
EXPORT_C void CAknTreeList::SetFocusedItem( TAknTreeItemID aItem )
	{
	View().SetFocusedItemAndView( Tree().Item( aItem ) );
	}

// ---------------------------------------------------------------------------
//  Returns the index of focused item
// ---------------------------------------------------------------------------
// 
EXPORT_C TInt CAknTreeList::FocusedItemIndex() const
	{
	return View().FocusedItemIndex();
	}
	
	
// ---------------------------------------------------------------------------
//  Returns the index of requested visible item
// ---------------------------------------------------------------------------
// 
EXPORT_C TInt CAknTreeList::VisibleItemIndex( TAknTreeItemID aItem ) const
	{
	return View().VisibleItemIndex( Tree().Item( aItem ) );
	}
	
	

// ---------------------------------------------------------------------------
// Sets the interface used for custom tree ordering.
// ---------------------------------------------------------------------------
// 
EXPORT_C void CAknTreeList::Sort( MAknCustomTreeOrdering* aOrdering,
    TFocusBehaviour aFocusBehaviour, TBool aDrawNow )
    {
    View().SetFocusBehaviour( ( aFocusBehaviour == ESaveFocus ) ? ETrue : EFalse );
    Tree().SetCustomOrdering( aOrdering, aDrawNow );
    }

// ---------------------------------------------------------------------------
// Sorts the specified node content with previously set ordering.
// ---------------------------------------------------------------------------
// 
EXPORT_C void CAknTreeList::Sort( TAknTreeItemID aNode,
    TFocusBehaviour aFocusBehaviour, TBool aSortDescendants, TBool aDrawNow )
    {
    View().SetFocusBehaviour( ( aFocusBehaviour == ESaveFocus ) ? ETrue : EFalse );
    Tree().Sort( aNode, aSortDescendants, aDrawNow );
    }

// ---------------------------------------------------------------------------
// Sets text for the empty list.
// ---------------------------------------------------------------------------
// 
EXPORT_C void CAknTreeList::SetEmptyTextL(const TDesC& aText)
	{
	View().SetEmptyTextL( aText );
	}


// ---------------------------------------------------------------------------
// Handles key events by mediating them to the view.
// ---------------------------------------------------------------------------
//
TKeyResponse CAknTreeList::OfferKeyEventL( const TKeyEvent& aKeyEvent,
    TEventCode aType )
    {
    if ( IsFocused() )
        {
        return View().OfferKeyEventL( aKeyEvent, aType );
        }
    else
        {
        return EKeyWasNotConsumed;
        }
    }


// ---------------------------------------------------------------------------
// Changes the visibility of the list.
// ---------------------------------------------------------------------------
//
void CAknTreeList::MakeVisible( TBool aVisible )
    {
    CAknControl::MakeVisible( aVisible );
    View().MakeVisible( aVisible );
    }


// ---------------------------------------------------------------------------
// Changes the dimming of the list.
// ---------------------------------------------------------------------------
//
void CAknTreeList::SetDimmed( TBool aDimmed )
    {
    CAknControl::SetDimmed( aDimmed );
    View().SetDimmed( aDimmed );
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// Sets the control's containing window by copying it from aContainer.
// ---------------------------------------------------------------------------
//
void CAknTreeList::SetContainerWindowL( const CCoeControl& aContainer )
    {
    CAknControl::SetContainerWindowL( aContainer );
    if ( iView )
        {
        iView->SetContainerWindowL( *this );
        }
    }


// ---------------------------------------------------------------------------
// Sets the control as ready to be drawn.
// ---------------------------------------------------------------------------
//
void CAknTreeList::ActivateL()
    {
    CAknControl::ActivateL();
    }


// ---------------------------------------------------------------------------
// Handles resource changes. The tree needs notification of skin change, so
// it can reconstruct the icons for the new skin.
// ---------------------------------------------------------------------------
//
void CAknTreeList::HandleResourceChange( TInt aType )
    {
    CAknControl::HandleResourceChange( aType );
    if ( aType == KAknsMessageSkinChange )
        {
        TRAP_IGNORE( Tree().HandleSkinChangeL() );
        }
    }


// ---------------------------------------------------------------------------
// Gets the control's input capabilities.
// ---------------------------------------------------------------------------
//
TCoeInputCapabilities CAknTreeList::InputCapabilities() const
    {
    return TCoeInputCapabilities::ENavigation;
    }


// ---------------------------------------------------------------------------
// Handles pointer events. The pointer events are mediated to the view by
// control framework, as the view is set as component control of the list.
// ---------------------------------------------------------------------------
//
void CAknTreeList::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    CAknControl::HandlePointerEventL( aPointerEvent );
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// ---------------------------------------------------------------------------
//
TInt CAknTreeList::CountComponentControls() const
    {
    return iView ? 1 : 0;
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// ---------------------------------------------------------------------------
//
CCoeControl* CAknTreeList::ComponentControl( TInt /*aIndex*/ ) const
    {
    return iView;
    }


// ---------------------------------------------------------------------------
// Default C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTreeList::CAknTreeList()
    : iObservers( KObserverArrayGranularity ),
      iIndex( KNotInNotificationSequence )
    {
    AKNTASHOOK_ADD( this, "CAknTreeList" );
    }


// ---------------------------------------------------------------------------
// Completes the construction of the base class. This variant creates a new
// window for the list and activates it.
// ---------------------------------------------------------------------------
//
void CAknTreeList::BaseConstructL()
    {
    CreateWindowL();
    BaseConstructL( *this );
    ActivateL();
    }


// ---------------------------------------------------------------------------
// Completes the construction of the base class. This variant assigns the
// window of the given container to the list.
// ---------------------------------------------------------------------------
//
void CAknTreeList::BaseConstructL( const CCoeControl& aContainer )
    {
    if ( this != &aContainer )
        {
        SetContainerWindowL( aContainer );
        }
    EnableDragEvents();
    iTree = CAknTree::NewL( *this, NULL );
    iView = CAknTreeListView::NewL( *this, *iTree, *this );
    
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
	// LISTBOX EFFECTS IMPLEMENTATION
	//
	// Creates a CTfxGc and replaces the original CWindowGc with that gc.
	//
    CWindowGc* transGc = CAknListLoader::CreateTfxGc( *this, iView->TopIndex(), 
    												iView->BottomIndex(), 
    												iView->HighlightIndex(), 
    												iView->ItemCountLimit()); 
    if( transGc )
        {
		iView->SetGc(transGc);
        }
	// END OF LISTBOX EFFECTS IMPLEMENTATION
#endif // RD_UI_TRANSITION_EFFECTS_LIST
    
    iTree->AddObserverL( iView );
    }


// ---------------------------------------------------------------------------
// References to the tree.
// ---------------------------------------------------------------------------
//
CAknTree& CAknTreeList::Tree()
    {
    __ASSERT_DEBUG( iTree != NULL, User::Invariant() );
    return *iTree;
    }


const CAknTree& CAknTreeList::Tree() const
    {
    __ASSERT_DEBUG( iTree != NULL, User::Invariant() );
    return *iTree;
    }


// ---------------------------------------------------------------------------
// References to the view.
// ---------------------------------------------------------------------------
//
CAknTreeListView& CAknTreeList::View()
    {
    __ASSERT_DEBUG( iView != NULL, User::Invariant() );
    return *iView;
    }


const CAknTreeListView& CAknTreeList::View() const
    {
    __ASSERT_DEBUG( iView != NULL, User::Invariant() );
    return *iView;
    }


// ---------------------------------------------------------------------------
// Mediates the focus change to the view.
// ---------------------------------------------------------------------------
//
void CAknTreeList::FocusChanged( TDrawNow aDrawNow )
    {
    View().SetFocus( IsFocused(), aDrawNow );
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// Mediates the size and position change to the view.
// ---------------------------------------------------------------------------
//
void CAknTreeList::SizeChanged()
    {
    View().SetRect( Rect() );
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// Mediates the position change to the view.
// ---------------------------------------------------------------------------
//
void CAknTreeList::PositionChanged()
    {
    View().SetPosition( TPoint() );
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// Retrieves an object of the same type as that encapsulated in aId.
// ---------------------------------------------------------------------------
//
TTypeUid::Ptr CAknTreeList::MopSupplyObject( TTypeUid aId )
    {
    return CAknControl::MopSupplyObject( aId );
    }


// ---------------------------------------------------------------------------
// Does nothing, the draw request is mediated to the view through component
// control structure.
// ---------------------------------------------------------------------------
//
void CAknTreeList::Draw( const TRect& /*aRect*/ ) const
    {
    }

