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
* Description:  Implementation for CAknTreeListView class.
*
*/


#include <AknUtils.h>
#include <skinlayout.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknsBasicBackgroundControlContext.h>
#include <AknsDrawUtils.h>
#include <barsread.h>
#include <aknappui.h>
#include <aknitemactionmenu.h>
#include <AknTasHook.h> // for testability hooks
#include <AknPriv.hrh>
#include "akntreelistview.h"
#include "akntree.h"
#include "akntreelist.h"
#include "akntreeiterator.h"
#include "akntreelistphysicshandler.h"



#ifdef RD_UI_TRANSITION_EFFECTS_LIST

#include <aknlistboxtfxinternal.h> // LISTBOX EFFECTS IMPLEMENTATION
#include <aknlistloadertfx.h>

#endif // RD_UI_TRANSITION_EFFECTS_LIST
// Value selected so that enough items fit in the array with vga resolution.
const TInt KVisibleItemsArrayGranularity = 16;

// Timeout for long keypress used in markable lists.
const TInt KLongPressInterval = 600000; // 0.6 seconds

// Number of additional items to draw
const TInt KAdditionalItems = 2;


// Tree list view flag definitions.
enum TAknTreeListViewFlags
    {
    EFlagStructureLines,
    EFlagIndention,
    EFlagLooping,
    EFlagUpdateBackground,
    EFlagMarkingEnabled, // Marking of list items is enabled.
    EFlagMarkingMode, // List in marking mode (MSK controlled by list). 
    EFlagMark, // List items are being marked.
    EFlagUnmark, // List items are being unmarked.
    EFlagSimultaneousMarking, // Simultaneous marking ongoing.
    EFlagHashKeyPressed,
    EFlagCtrlKeyPressed,
    EFlagShiftKeyPressed,
    EFlagSaveFocusAfterSorting,
    EFlagSingleClickEnabled,
    EFlagHighlightEnabled, // Is highlight drawing enabled
    EFlagIgnoreButtonUpEvent // Up event ignored (when styluspopup menu open)
    };


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTreeListView* CAknTreeListView::NewL( const CCoeControl& aContainer,
    CAknTree& aTree, CAknTreeList& aList )
    {
    CAknTreeListView* self = new( ELeave ) CAknTreeListView( aTree, aList );
    CleanupStack::PushL( self );
    self->ConstructL( aContainer );
    CleanupStack::Pop( self );
    AKNTASHOOK_ADDL( self, "CAknTreeListView" );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknTreeListView::~CAknTreeListView()
    {
    AKNTASHOOK_REMOVE();
    AknsUtils::DeregisterControlPosition( this );
    iItems.Close();
    iFocusedItem = NULL; // Not owned.
    delete iEmptyListText;
    delete iScrollbarFrame;
    delete iAnimation;
    delete iLongPressTimer;
    delete iPhysicsHandler;

    if ( iItemActionMenu )
        {
        iItemActionMenu->RemoveCollection( *this );
        }
    delete iLongTapDetector;

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( CAknListLoader::TfxApiInternal( iGc ) )
        {
        delete iGc;
        }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
    }


// ---------------------------------------------------------------------------
// Returns the specified layout rectangle.
// ---------------------------------------------------------------------------
//
TRect CAknTreeListView::RectFromLayout( const TRect& aParent,
    const TAknWindowComponentLayout& aComponentLayout )
    {
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParent, aComponentLayout.LayoutLine() );
    return layoutRect.Rect();
    }


// ---------------------------------------------------------------------------
// Sets the focused item and its position in the view.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::SetFocusedItem( CAknTreeItem* aItem,
    TInt aIndex, TBool aDrawNow )
    {
    if ( FocusedItem() != aItem || FocusIndex() != aIndex )
        {
        SetFocusedItem( aItem );
        if ( aItem )
            {
            UpdateVisibleItems( aIndex, aItem );
            UpdateViewLevel();
            if ( IsMarkable() )
                {
                UpdateMSKCommand();
                }
            }
        }

    // Updates the highlight animation, if the size or background of focused
    // item has been changed.
    UpdateAnimation();

    if ( aDrawNow )
        {
        Window().Invalidate( Rect() );
        }
    UpdateScrollbars();
    }


// ---------------------------------------------------------------------------
// Sets the focused item and its position in the view.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::SetFocusedItemAndView( CAknTreeItem* aItem )
    {
    if ( FocusedItem() != aItem)
        {
           
        SetFocusedItem( aItem );

        iPreviouslyFocusedItem = FocusedItem();

        if ( aItem )
            {   
            TInt index = iTree.ItemIndex( aItem );
            if ( index < iItems.Count() )
            {
                // focused item in first page,
                // set focused item to correct line and update view
                // to the beginning of list
                UpdateVisibleItems( index, aItem );
            }
            else
            {
                // focused item not in first page,
                // set focused item and update view so that focused item
                // is at the lowest line on the screen
                UpdateVisibleItems( iItems.Count() - 1, aItem );
            }
            UpdateViewLevel();
                        
            if ( IsMarkable() )
                {
                UpdateMSKCommand();
                }
            }
        }

    // Updates the highlight animation, if the size or background of focused
    // item has been changed.
    UpdateAnimation();
            
    // Draw always
    Window().Invalidate( Rect() );
        
    UpdateScrollbars();
    }



// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
//
TInt CAknTreeListView::FocusedItemIndex() const
    {
    if ( FocusedItemVisible() )
        {
        return FocusIndex();
        }
    return -1;  
    }
    
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
//  
TInt CAknTreeListView::VisibleItemIndex( CAknTreeItem* aItem ) const
    {
    for ( TInt ii = 0; ii < iItems.Count(); ++ii )
        {
        if ( aItem == iItems[ii].Item() )
            {
            return ii;
            }
        }
    return -1;
    }


    
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
//  
void CAknTreeListView::SetFocusBehaviour( TBool saveFocus )
{
    if ( saveFocus)
        {
        iFlags.Set( EFlagSaveFocusAfterSorting );
        }
    else
        {
        iFlags.Clear( EFlagSaveFocusAfterSorting );
        }
}


// ---------------------------------------------------------------------------
// Returns pointer to the focused item.
// ---------------------------------------------------------------------------
//
CAknTreeItem* CAknTreeListView::FocusedItem() const
    {
    return iFocusedItem;
    }


// ---------------------------------------------------------------------------
// Returns the highlight rectangle for the focused item.
// ---------------------------------------------------------------------------
//
TRect CAknTreeListView::HighlightRect() const
    {
    if ( IsFocused() && FocusedItemVisible() )
        {
        TRect rect = iItems[FocusIndex()].HighlightRect( iViewLevel,
            Indention(), IndentionWidth() );

        TPoint position;
        if ( AknsUtils::GetControlPosition( this, position ) != KErrNone )
            {
            position = PositionRelativeToScreen();
            }

        rect.Move( position );
        return rect;
        }
    else
        {
        return TRect();
        }
    }


// ---------------------------------------------------------------------------
// Returns whether the list is set looping.
// ---------------------------------------------------------------------------
//
TBool CAknTreeListView::IsLooping() const
    {
    return iFlags.IsSet( EFlagLooping );
    }


// ---------------------------------------------------------------------------
// Sets the list to looping or non-looping mode.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::SetLooping( TBool aLooping )
    {
    iFlags.Assign( EFlagLooping, aLooping );
    }


// ---------------------------------------------------------------------------
// Returns whether the structure lines are set visible.
// ---------------------------------------------------------------------------
//
TBool CAknTreeListView::StructureLines() const
    {
    return iFlags.IsSet( EFlagStructureLines ) && 
        iFlags.IsSet( EFlagIndention );
    }


// ---------------------------------------------------------------------------
// Sets the visibility of structure lines.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::SetStructureLineVisibility( TBool aVisible )
    {
    iFlags.Assign( EFlagStructureLines, aVisible );
    Window().Invalidate( Rect() );
    }


// ---------------------------------------------------------------------------
// Checks whether indention is enabled.
// ---------------------------------------------------------------------------
//
TBool CAknTreeListView::Indention() const
    {
    return iFlags.IsSet( EFlagIndention );
    }


// ---------------------------------------------------------------------------
// Enables or disables indention of list items.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::EnableIndention( TBool aEnable )
    {
    iFlags.Assign( EFlagIndention, aEnable );
    iMaxViewLevel = aEnable ? iTree.Depth() - 1 : 0;
    Window().Invalidate( Rect() );
    }


// ---------------------------------------------------------------------------
// Returns the width of single indention step.
// ---------------------------------------------------------------------------
//
TInt CAknTreeListView::IndentionWidth() const
    {
    if ( StructureLines() )
        {
        return -1;
        }
    else
        {
        return iIndentionWidth;
        }
    }


// ---------------------------------------------------------------------------
// Sets the width of one indention step.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::SetIndentionWidth( TInt aIndentionWidth )
    {
    iIndentionWidth = aIndentionWidth;
    }


// ---------------------------------------------------------------------------
// Checks whether marking is enabled.
// ---------------------------------------------------------------------------
//
TBool CAknTreeListView::IsMarkable() const
    {
    return iFlags.IsSet( EFlagMarkingEnabled );
    }


// ---------------------------------------------------------------------------
// Enables or disables the marking of list items.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::EnableMarking( TBool aEnable )
    {
    iFlags.Assign( EFlagMarkingEnabled, aEnable );
    }
    
// ---------------------------------------------------------------------------
// Sets text for the empty list.
// ---------------------------------------------------------------------------
//   
void CAknTreeListView::SetEmptyTextL(const TDesC& aText)
    {
    delete iEmptyListText;
    iEmptyListText = NULL;
    iEmptyListText = aText.AllocL();
    }


// ---------------------------------------------------------------------------
// InitPhysicsL
// ---------------------------------------------------------------------------
//   
void CAknTreeListView::InitPhysicsL()
    {
    if ( iPhysicsHandler )
        {
        iPhysicsHandler->InitPhysicsL();
        }
    }


// ---------------------------------------------------------------------------
// SetHighlight
// ---------------------------------------------------------------------------
//     
void CAknTreeListView::SetHighlight( CAknTreeItem* aItemToBeFocused,
                                     const TInt& aIndexToBeFocused )
    {
    if ( aItemToBeFocused )
        {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iGc );

        if ( transApi && !transApi->EffectsDisabled() && !aItemToBeFocused->Node() )
            {
            transApi->SetMoveType( MAknListBoxTfxInternal::EListTap );
            }
#endif

        SetFocusedItem( aItemToBeFocused, aIndexToBeFocused, ETrue );
        iPreviouslyFocusedItem = aItemToBeFocused;
        }
    }


// ---------------------------------------------------------------------------
// SelectItem
// ---------------------------------------------------------------------------
//     
void CAknTreeListView::SelectItem( CAknTreeItem* aSelectedItem )
    {
    SelectItem( aSelectedItem, EFalse );
    }


// ---------------------------------------------------------------------------
// VisibleItemCount
// ---------------------------------------------------------------------------
//     
TInt CAknTreeListView::VisibleItemCount() const
    {
    TInt count( iItems.Count() );
    count += KAdditionalItems;
    return count;
    }


// ---------------------------------------------------------------------------
// SetPressedDownState
// ---------------------------------------------------------------------------
//     
void CAknTreeListView::SetPressedDownState( const TBool& aPressedDown )
    {
    iIsPressedDownState = aPressedDown;
    }
    

// ---------------------------------------------------------------------------
// UpdateTreeListView
// ---------------------------------------------------------------------------
//     
void CAknTreeListView::UpdateTreeListView( const TInt& aFirstItem,
                                           const TBool& aDrawNow )
    {
    CAknTreeItem* first = iTree.VisibleItem( aFirstItem );
    UpdateVisibleItems( 0, first );
    UpdateScrollbars();
    UpdateAnimation();
    
    if ( aDrawNow )
        {
        DrawNow();
        }
    else
        {
        Window().Invalidate( Rect() );
        } 
    }


// ---------------------------------------------------------------------------
// Offset
// ---------------------------------------------------------------------------
//     
TInt CAknTreeListView::Offset() const
    {
    return iPhysicsHandler->Offset();
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// Handles key events.
// ---------------------------------------------------------------------------
//
TKeyResponse CAknTreeListView::OfferKeyEventL( const TKeyEvent& aKeyEvent,
    TEventCode aType )
    {
    TKeyResponse response = EKeyWasNotConsumed;
    if ( aType == EEventKey )
        {
        response = EKeyWasConsumed;

        // In single click mode first key press enables highlight
        if ( SingleClickEnabled() && !HighlightEnabled() )
            {
            if ( ( aKeyEvent.iCode == EKeyUpArrow || 
                   aKeyEvent.iCode == EKeyDownArrow || 
                   aKeyEvent.iCode == EKeyEnter ||
                   aKeyEvent.iCode == EKeyOK ) && iItems.Count() ) 
                {
                TInt index = FirstVisibleItemIndex();
                EnableHighlight( ETrue );   
                // Check if marquee needs to be enabled              
                if ( iList.Flags() & KAknTreeListMarqueeScrolling )
                    {
                    iTree.EnableMarquee( ETrue );
                    }
                if ( iPhysicsHandler->Offset() == 0 )
                    {
                    SetFocusedItem( iItems[0].Item(), index, ETrue );
                    }
                else
                    {
                    SetFocusedItem( iItems[0].Item(), index, EFalse );
                    HandleDownArrowKeyEvent();
                    }
                return EKeyWasConsumed;                
                }
            }
        
        switch ( aKeyEvent.iCode )
            {
            case EKeyLeftArrow:
                {
                HandleLeftArrowKeyEvent();
                break;
                }
            case EKeyRightArrow:
                {
                HandleRightArrowKeyEvent();
                break;
                }
            case EKeyUpArrow:
                {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            // LISTBOX EFFECTS IMPLEMENTATION
            // 
            // Set type of momement
            //
            MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iGc );
            if ( transApi )
                {
                transApi->SetMoveType( MAknListBoxTfxInternal::EListMoveUp );
                }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
   
                HandleUpArrowKeyEvent();
                break;
                }
            case EKeyDownArrow:
                {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            // LISTBOX EFFECTS IMPLEMENTATION
            // 
            // Set type of momement
            //
            MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iGc );
            if ( transApi )
                {
                transApi->SetMoveType( MAknListBoxTfxInternal::EListMoveDown );
                }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
                HandleDownArrowKeyEvent();
                break;
                }
            case EKeyEnter: // fall-through intended here
            case EKeyOK:
                {
                // Ignore repeated events.
                if ( aKeyEvent.iRepeats == 0 )
                    {   
                    HandleSelectionKeyEvent();
                    }
                break;
                }
            default:
                response = EKeyWasNotConsumed;
                break;
            }
        }

    else if ( aType == EEventKeyDown )
        {
        if ( aKeyEvent.iScanCode == EStdKeyLeftShift ||
             aKeyEvent.iScanCode == EStdKeyRightShift )
            {
            iFlags.Set( EFlagShiftKeyPressed );
            if ( !MarkingOngoing() )
                {
                BeginMarkingL();
                }
            response = EKeyWasConsumed;
            }

        else if ( aKeyEvent.iScanCode == EStdKeyLeftCtrl ||
                  aKeyEvent.iScanCode == EStdKeyRightCtrl )
            {
            iFlags.Set( EFlagCtrlKeyPressed );
            if ( !MarkingOngoing() )
                {
                BeginMarkingL();
                }
            response = EKeyWasConsumed;
            }

        else if ( aKeyEvent.iScanCode == EStdKeyHash )
            {
            iFlags.Set( EFlagHashKeyPressed );
            if ( !MarkingOngoing() )
                {
                BeginMarkingL();
                }
            response = EKeyWasConsumed;
            }
        }

    else if ( aType == EEventKeyUp )
        {
        const TInt KShiftModifiers =
            EModifierLeftShift | EModifierRightShift | EModifierShift;

        const TInt KCtrlModifiers =
            EModifierLeftCtrl | EModifierRightCtrl | EModifierCtrl;

        if ( aKeyEvent.iScanCode == EStdKeyLeftCtrl ||
             aKeyEvent.iScanCode == EStdKeyRightCtrl ||
             aKeyEvent.iScanCode == EStdKeyLeftShift ||
             aKeyEvent.iScanCode == EStdKeyRightShift )
            {
            if ( !( aKeyEvent.iModifiers & KShiftModifiers ) )
                {
                iFlags.Clear( EFlagShiftKeyPressed );
                }

            if ( !( aKeyEvent.iModifiers & KCtrlModifiers ) )
                {
                iFlags.Clear( EFlagCtrlKeyPressed );
                }

            if ( iFlags.IsClear( EFlagShiftKeyPressed ) &&
                 iFlags.IsClear( EFlagCtrlKeyPressed ) &&
                 iFlags.IsClear( EFlagHashKeyPressed ) &&
                 MarkingOngoing() )
                {
                EndMarking();
                }
            response = EKeyWasConsumed;
            }

        else if ( aKeyEvent.iScanCode == EStdKeyHash )
            {
            iFlags.Clear( EFlagHashKeyPressed );

            if ( iFlags.IsClear( EFlagShiftKeyPressed ) &&
                 iFlags.IsClear( EFlagCtrlKeyPressed ) )
                {
                if ( iFlags.IsClear( EFlagSimultaneousMarking ) )
                    {
                    // Item marking is changed when several items have not
                    // been marked by moving focus while pressing hash key.
                    if ( FocusedItem() )
                        {
                        MarkItem( FocusedItem(), !FocusedItem()->IsMarked(),
                            ETrue );
                        }
                    }

                if ( MarkingOngoing() )
                    {
                    EndMarking();
                    }
                }
            response = EKeyWasConsumed;
            }
        }
      
    if ( aType == EEventKey )
        {
        // Check if view offset needs to be restored
        iPhysicsHandler->HandleKeyEvent( aKeyEvent.iCode );
        }

    return response;
    }


// ---------------------------------------------------------------------------
// Changes the visibility of the view.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::MakeVisible( TBool aVisible )
    {
    CAknControl::MakeVisible( aVisible );

    if ( aVisible )
        {
        UpdateScrollbars();
        }
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// Sets the control's containing window by copying it from aContainer.
// Method also reconstructs the scrollbars for the view. Otherwise, they would
// still be using the previously set, possibly deleted container window.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::SetContainerWindowL( const CCoeControl& aContainer )
    {
    if ( iScrollbarFrame )
        {
        delete iScrollbarFrame;
        iScrollbarFrame = NULL;
        }

    CAknControl::SetContainerWindowL( aContainer );
    
    Window().SetPointerGrab( ETrue );

    iScrollbarFrame = new ( ELeave ) CEikScrollBarFrame( this, this );
    iScrollbarFrame->CreateDoubleSpanScrollBarsL( EFalse, EFalse );
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// Handles changes in resources.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::HandleResourceChange( TInt aType )
    {
    CAknControl::HandleResourceChange( aType );
    if ( aType == KAknsMessageSkinChange )
        {
        TRAPD( error, CreateAnimationL() )
        if ( error )
            {
            delete iAnimation;
            iAnimation = NULL;
            }
        }
    else if ( aType == KEikDynamicLayoutVariantSwitch && FocusedItem() )
        {
        if ( !FocusedItemVisible() )
            {
            TInt firstItemIndex = 0;
            if ( iItems.Count() && iItems[0].Item() )
                {
                firstItemIndex = iTree.VisibleItemIndex( iItems[0].Item() );
                }

            TInt index = 0;
            if ( firstItemIndex < iTree.VisibleItemIndex( FocusedItem() ) )
                {
                index = iItems.Count() - 1;
                }

            SetFocusedItem( FocusedItem(), index, ETrue );
            }
        else
            {
            SetFocusedItem( FocusedItem(), FocusIndex(), ETrue );
            
            
            // This block moves visible view after layout switch
            // if there are not enough items to fill whole screen
            TInt visibleItemIndex = iTree.VisibleItemIndex( FocusedItem() );
            if ( visibleItemIndex != KErrNotFound)
                {
                TInt focusedItemIndex = FocusedItemIndex();
                if (focusedItemIndex != -1)
                    {
                    TInt height =  iTree.VisibleItemCount() - visibleItemIndex + focusedItemIndex;
                    TInt itemCountLimit = iItems.Count();
                    
                    if ( height < itemCountLimit && height < iTree.VisibleItemCount() )
                        {
                        TInt move = itemCountLimit - height;                
                        UpdateVisibleItems( focusedItemIndex + move, FocusedItem() );
                        }
                    }
                }
            // end of block
            }
        }
    else if ( aType == KAknMessageFocusLost && HighlightEnabled() )
        {
        EnableHighlight( EFalse );
        }
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// Handles pointer events. Moves the focus on stylus down events to the
// pointed item, and selects the item on stylus up event if the pointed item
// is the same as on stylus down event. Otherwise, the pointed item is set
// focused.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    if ( iFlags.IsSet( EFlagIgnoreButtonUpEvent ) 
         && aPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        return;
        }
    
    if ( GrabbingComponent() != NULL )
        {
        iPhysicsHandler->ResetEventBlockingStatus();
        }
    else
        {
        if( aPointerEvent.iType == TPointerEvent::EButton1Down )  
            {
            iPreviouslyFocusedItem = FocusedItem(); 
            }

        iPhysicsHandler->HandlePointerEventL( aPointerEvent, iViewLevel, 
            MarkingOngoing(), iFlags.IsSet( EFlagShiftKeyPressed ), 
            iFlags.IsSet( EFlagCtrlKeyPressed )  );
        }
    CAknControl::HandlePointerEventL( aPointerEvent );
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// ---------------------------------------------------------------------------
//
TInt CAknTreeListView::CountComponentControls() const
    {
    return iScrollbarFrame ? iScrollbarFrame->CountComponentControls() : NULL;
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// ---------------------------------------------------------------------------
//
CCoeControl* CAknTreeListView::ComponentControl( TInt aIndex ) const
    {
    return iScrollbarFrame ? iScrollbarFrame->ComponentControl( aIndex ) : NULL;
    }


// ---------------------------------------------------------------------------
// From class MEikScrollBarObserver.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::HandleScrollEventL( CEikScrollBar* aScrollBar,
    TEikScrollEvent aEventType )
    {
    __ASSERT_DEBUG( aScrollBar, User::Invariant() );
    __ASSERT_DEBUG( iScrollbarFrame, User::Invariant() );

    if ( SingleClickEnabled() )
        {
        EnableHighlight( EFalse );
        }

    TInt thumbPosition = aScrollBar->ThumbPosition();
    if ( AknLayoutUtils::LayoutMirrored() &&
         aScrollBar != iScrollbarFrame->VerticalScrollBar() )
        {
        const TEikScrollBarModel* model = aScrollBar->Model();
        thumbPosition = ( model->iScrollSpan - model->iThumbSpan )
            - thumbPosition;
        }

    switch ( aEventType )
        {
        case EEikScrollThumbReleaseVert:
            // Ignored.
            break;

        case EEikScrollLeft:
        case EEikScrollRight:
        case EEikScrollPageLeft:
        case EEikScrollPageRight:
            iViewLevel = thumbPosition;
            UpdateScrollbars();
            UpdateAnimation();
            Window().Invalidate( Rect() );
            break;

        case EEikScrollThumbDragHoriz:
            iViewLevel = thumbPosition;
            UpdateAnimation();
            Window().Invalidate( Rect() );
            break;

        case EEikScrollThumbReleaseHoriz:
            UpdateScrollbars();
            break;

        case EEikScrollHome:
            // Not in use!
            break;

       case EEikScrollEnd:
           // Not in use!
           break;

        default:
            break;
        }

    iPhysicsHandler->HandleScrollEventL( aEventType, thumbPosition );
    }


// ---------------------------------------------------------------------------
// From class MAknTreeObserver.
// Handles tree events.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::HandleTreeEvent( TEvent aEvent, CAknTreeItem* aItem,
    TBool aDrawNow )
    {
    
    // Note: max view level is needed only for scrollbar updating

    if ( Indention() )
        {
        switch ( aEvent )
            {
            case EItemAdded:
            case EItemRemoveBegin:
            case EItemRemoveEnd:
                {
                if ( aDrawNow )
                    {
                    iMaxViewLevel = iTree.Depth() - 1;
                    }
                break;
                }
            
            case EItemMoved:
            case ENodeExpanded:
            case ENodeCollapsed:
            case ETreeSorted:
                {
                iMaxViewLevel = iTree.Depth() - 1;
                break;
                }

            case EItemModified:
                break;

            default:
                break;
            }
        }

    switch ( aEvent )
        {
        case EItemAdded:
            HandleItemAddedEvent( aItem, aDrawNow );
            TRAP_IGNORE( InitPhysicsL() );
            break;

        case EItemMoved:
            HandleItemMovedEvent( aItem );
            TRAP_IGNORE( InitPhysicsL() );
            break;

        case EItemRemoveBegin:
            PrepareForItemRemoval( aItem, aDrawNow );
            break;

        case EItemRemoveEnd:
            HandleItemRemovedEvent( aItem, aDrawNow );
            TRAP_IGNORE( InitPhysicsL() );
            break;

        case ENodeExpanded:
            HandleNodeExpandedEvent( aItem->Node() );
            TRAP_IGNORE( InitPhysicsL() );
            break;

        case ENodeCollapsed:
            HandleNodeCollapsedEvent( aItem->Node() );
            TRAP_IGNORE( InitPhysicsL() );
            break;

        case EItemModified:
            HandleItemModifiedEvent( aItem );
            break;

        case ETreeSorted:
            HandleTreeSortedEvent( aDrawNow );
            break;

        default:
            break;
        }

    if ( aDrawNow )
        {
        Window().Invalidate( Rect() );
        }
    }


// ---------------------------------------------------------------------------
// From class MAknsEffectAnimObserver.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::AnimFrameReady( TInt aError, TInt /*aAnimId*/ )
    {
    __ASSERT_DEBUG( iAnimation, User::Invariant() );

    if ( aError )
        {
        delete iAnimation;
        iAnimation = NULL;
        }
    else if ( IsFocused() && FocusedItemVisible() )
        {
        DrawNow( iItems[FocusIndex()].Rect() );
        }
    else
        {
        iAnimation->Stop();
        }
    }


// ---------------------------------------------------------------------------
// From class MEikCommandObserver.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::ProcessCommandL( TInt /*aCommandId*/ )
    {
    // Any event coming from MSK changes the marking of currently focused
    // item, as MSK is being observed only when shift is pressed.
    if ( MarkingOngoing() && FocusedItem() )
        {
        MarkItem( FocusedItem(), !FocusedItem()->IsMarked(), ETrue );
        }
    }

// ---------------------------------------------------------------------------
// CAknTreeListView::ReportTreeListEvent
// ---------------------------------------------------------------------------
//
void CAknTreeListView::ReportTreeListEvent(
    MAknTreeListObserver::TEvent aEvent, TAknTreeItemID aItem )
    {
    iList.NotifyObservers( aEvent, aItem );
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// Handles focus change.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::FocusChanged( TDrawNow aDrawNow )
    {
    if ( iAnimation )
        {
        if ( IsFocused() )
            {
            iAnimation->Start();
            }
        else
            {
            iAnimation->Stop();
            }
        }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal *transApi = CAknListLoader::TfxApiInternal( iGc );
    if ( aDrawNow || (transApi && !transApi->EffectsDisabled()) )
#else
    if (aDrawNow)
#endif //RD_UI_TRANSITION_EFFECTS_LIST
        {
        Window().Invalidate( Rect() );
        }
    else if ( IsFocused() && FocusedItemVisible() )
        {
        TRect rect = iItems[FocusIndex()].HighlightRect( iViewLevel, Indention(), IndentionWidth() );
        Window().Invalidate( rect );
        }
        
    ReportTreeListEvent( MAknTreeListObserver::EItemFocused,
        iTree.Id( FocusedItem() ) );
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// Responds to changes to the size and position of this control.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::SizeChanged()
    {
    // Get layout for the view.
    LayoutView();

    // Update scrollbars.
    UpdateScrollbars();

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    UpdateIndexes();
#endif
    AknsUtils::RegisterControlPosition( this, PositionRelativeToScreen() );
    
    TRAP_IGNORE( InitPhysicsL() );
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// Responds to changes in the position of a control.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::PositionChanged()
    {
    AknsUtils::RegisterControlPosition( this, PositionRelativeToScreen() );
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// Retrieves an object of the same type as that encapsulated in aId.
// ---------------------------------------------------------------------------
//
TTypeUid::Ptr CAknTreeListView::MopSupplyObject( TTypeUid aId )
    {
    return CAknControl::MopSupplyObject( aId );
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTreeListView::CAknTreeListView( CAknTree& aTree, CAknTreeList& aList )
    : iTree( aTree ),
      iList( aList ),
      iItems( KVisibleItemsArrayGranularity ),
      iViewLevel( 0 ),
      iMaxViewLevel( 0 ),
      iStylusDownItemIndex( -1 ),
      iAnimationIID( KAknsIIDQsnAnimList ),
      iIndentionWidth( -1 ),
      iPhysicsHandler( NULL ),
      iScrollPhysicsTop( ETrue )
      #ifdef RD_UI_TRANSITION_EFFECTS_LIST
      ,iGc(NULL)
      #endif //RD_UI_TRANSITION_EFFECTS_LIST
      ,iItemActionMenu( NULL ),
      iLongTapDetector( NULL )       
    {
    if ( static_cast<CAknAppUi*>( 
            iCoeEnv->AppUi() )->IsSingleClickCompatible() )
        {
        iFlags.Set( EFlagSingleClickEnabled );
        }
  
    iFlags.Set( EFlagStructureLines );
    iFlags.Set( EFlagIndention );
    }


// ---------------------------------------------------------------------------
// Second phase constructor.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::ConstructL( const CCoeControl& aContainer )
    {
    // Get the empty list text from resources.
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader,
        R_AVKON_LISTBOX_DEFAULT_EMPTY_TEXT );
    iEmptyListText = reader.ReadHBufCL();
    CleanupStack::PopAndDestroy(); // reader

    // Setting container window also constructs scrollbars for the view.
    SetContainerWindowL( aContainer );

    // Construct highlight animation for the view.
    TRAPD( error, CreateAnimationL() )
    if ( error )
        {
        delete iAnimation;
        iAnimation = NULL;
        }

    // Long press timer for markable list.
    iLongPressTimer = CPeriodic::NewL( CActive::EPriorityStandard );

    if ( !iPhysicsHandler )
        {
        iPhysicsHandler = CAknTreeListPhysicsHandler::NewL( this,
                                                            &iTree,
                                                            &iItems );
        }

    iIsPressedDownState = EFalse;
    iIsDragged = EFalse;
    iItemActionMenu = CAknItemActionMenu::RegisterCollectionL( *this );
    if ( iItemActionMenu )
        {
        iLongTapDetector = CAknLongTapDetector::NewL( this );
        }

    if ( SingleClickEnabled() )
        {
        EnableHighlight( EFalse );
        }
    else
        {
        EnableHighlight( ETrue );
        }
    }


// ---------------------------------------------------------------------------
// Handles an addition of new item into tree list. The focused item is kept
// in the same position of the view, and the set of tree items in the view is
// modified to contain the added item when necessary.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::HandleItemAddedEvent( CAknTreeItem* /*aItem*/, TBool aDrawNow )
    {
    UpdateVisibleItems();
    if (aDrawNow)
        {
        UpdateScrollbars();
        }
    }


// ---------------------------------------------------------------------------
// Handles the movement of a tree item. Movement of focused item has to be
// handled as a special case.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::HandleItemMovedEvent( CAknTreeItem* /*aItem*/ )
    {
    // Note: This method cannot deduce, which items in the view have actually
    // been changed, unless the it receives information from where the
    // specified item was moved.
    UpdateVisibleItems();
    UpdateScrollbars();
    }


// ---------------------------------------------------------------------------
// Prepares view for the item removal by moving the focus from the removed
// item.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::PrepareForItemRemoval( CAknTreeItem* aItem, TBool /*aDrawNow*/ )
    {
    __ASSERT_DEBUG( aItem, User::Invariant() );

    if ( FocusedItem() == aItem )
        {
        TAknTreeIterator iterator = iTree.Iterator();
        
        CAknTreeItem* currentItem = FocusedItem();
        
        iterator.SetCurrent( currentItem );
        if ( iterator.HasNext() )
            {
            // if next item with same parent exists, set focus to it
            CAknTreeItem* nextItem = iterator.Next(); 
            if ( currentItem->Parent() == nextItem->Parent() )
                {
                SetFocusedItem( nextItem );
                return;
                }
            }
        
        iterator.SetCurrent( currentItem );    
        if ( iterator.HasPrevious() )
            {
            // otherwise if previous item exists, set focus to it
            SetFocusedItem( iterator.Previous() );
            SetFocusIndex( FocusIndex() - 1 );
            }
        else
            {
            // no focus
            SetFocusedItem( NULL );
            SetFocusIndex( KMinTInt );
            }
        }
    }


// ---------------------------------------------------------------------------
// Handles the removal of a tree item. 
// ---------------------------------------------------------------------------
//
void CAknTreeListView::HandleItemRemovedEvent( CAknTreeItem* /*aItem*/, TBool aDrawNow )
    {
    UpdateVisibleItems();
    if (aDrawNow)
        {
        UpdateScrollbars();
        }
    }


// ---------------------------------------------------------------------------
// Handles an expansion of a tree node. If the expanded node is focused, it is
// moved upwards in the view enough to make its currently expanded content
// visible.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::HandleNodeExpandedEvent( CAknTreeNode* aNode )
    {
    if ( FocusedItem() == aNode )
        {
        TInt count = aNode->VisibleDescendantCount();
        TInt index = Min( Max( FocusIndex(), 0 ),
             Max( ( iItems.Count() - count ) - 1, 0 ) );
        UpdateVisibleItems( index, aNode );
        }
    else
        {
        UpdateVisibleItems();
        }
    UpdateScrollbars();
    }


// ---------------------------------------------------------------------------
// Handles a collapse of a tree node. If one of the items in collapsed node
// is focused, the focus has to be moved to collapsed node.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::HandleNodeCollapsedEvent( CAknTreeNode* aNode )
    {
    __ASSERT_DEBUG( aNode, User::Invariant() );

    if ( FocusedItem() && FocusedItem() != aNode )
        {
        TAknTreeIterator iterator = iTree.Iterator();
        iterator.SetCurrent( aNode );

        // Get next visible item after collapsed node.
        CAknTreeItem* next = iterator.Next();

        TInt collapsedIndex = iTree.ItemIndex( aNode );
        TInt focusedIndex = iTree.ItemIndex( FocusedItem() );
        if ( focusedIndex > collapsedIndex )
            {
            if ( !next || iTree.ItemIndex( next ) > focusedIndex )
                {
                // Move focus to collapsed node from its descendant.
                SetFocusedItem( aNode, FocusIndex(), EFalse );
                }
            }
        }
    else if ( FocusedItem() && FocusedItem() == aNode && !FocusedItemVisible() )
        {
        // If focused node is not visible, adjust the items so that it becomes
        // visible
        UpdateViewItemAsVisible( aNode );
        }

    UpdateVisibleItems();
    UpdateScrollbars();
    }


// ---------------------------------------------------------------------------
// Handles a change in tree item.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::HandleItemModifiedEvent( CAknTreeItem* /*aItem*/ )
    {
    }


// ---------------------------------------------------------------------------
// Sets the items to the view from the beginning of the list after the
// tree has been sorted.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::HandleTreeSortedEvent( TBool aDrawNow )
    {
    if ( iFlags.IsClear( EFlagSaveFocusAfterSorting) )
        {
        TInt count = iItems.Count();
        if ( count > 0)
            {
            TAknTreeIterator iterator = iTree.Iterator();
            for ( TInt ii = 0; ii < count; ++ii )
                {
                iItems[ii].SetItem( iterator.Next() );
                }
            
            SetFocusIndex( 0 );
            SetFocusedItem( iItems[0].Item() );
            }
        else
            {
            SetFocusIndex( KMinTInt );
            SetFocusedItem( NULL );
            }
        }
    else 
        {
        TInt count = iItems.Count();
        if ( count > 0)
            {
            TAknTreeIterator iterator = iTree.Iterator();
            for ( TInt ii = 0; ii < count; ++ii )
                {
                iItems[ii].SetItem( iterator.Next() );
                }
            }
        }
    if ( aDrawNow )
        {
        UpdateScrollbars();
        }
    }


// ---------------------------------------------------------------------------
// Updates the view items so that the specified item is located at the
// specified location of the view. The index is adjusted so that the
// beginning of the list is not left empty.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::UpdateVisibleItems( TInt aIndex, CAknTreeItem* aItem )
    {
    SetFocusIndex( KMinTInt );
    if ( !iItems.Count() )
        {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        UpdateIndexes();
#endif
        return;
        }

    TInt index = Min( aIndex, iTree.VisibleItemIndex( aItem ) );

    TAknTreeIterator iterator = iTree.Iterator();
    if ( index < 0 || index > iItems.Count() || !aItem )
        {
        index = 0;
        aItem = iterator.Next();
        }

    iItems[index].SetItem( aItem );
    if ( aItem == FocusedItem() )
        {
        SetFocusIndex( index );
        }

    iterator.SetCurrent( aItem );
    for ( TInt ii = index - 1; ii >= 0; --ii )
        {
        iItems[ii].SetItem( iterator.Previous() );
        if ( iItems[ii].Item() == FocusedItem() )
            {
            SetFocusIndex( ii );
            }
        }

    iterator.SetCurrent( aItem );
    for ( TInt ii = index + 1; ii < iItems.Count(); ++ii )
        {
        iItems[ii].SetItem( iterator.Next() );
        if ( iItems[ii].Item() == FocusedItem() )
            {
            SetFocusIndex( ii );
            }
        }
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    UpdateIndexes();
#endif
    }


// ---------------------------------------------------------------------------
// Updates the view items so that the focused item remains in the same
// position unless the list contains fewer items the view can contain.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::UpdateVisibleItems()
    {
    // Set the first item in the list focused, if no item is focused.
    if ( !FocusedItem() )
        {
        TAknTreeIterator iterator = iTree.Iterator();
        if ( iterator.HasNext() )
            {
            SetFocusedItem( iterator.Next() );
            SetFocusIndex( KMinTInt );
            
            iPreviouslyFocusedItem = FocusedItem(); 
            }
        }

    // Number of items in the expanded part of the tree.
    const TInt itemCount = iTree.VisibleItemCount();

    // Update the set of items in the view.
    if ( itemCount <= iItems.Count() )
        {
        // Set the tree items in the beginning of the view.
        TAknTreeIterator iterator = iTree.Iterator();
        CAknTreeItem* item = iterator.Next();
        SetFocusIndex( KMinTInt );
        for ( TInt ii = 0; ii < iItems.Count(); ++ii )
            {
            iItems[ii].SetItem( item );
            if ( item )
                {
                if ( item == FocusedItem() )
                    {
                    SetFocusIndex( ii );
                    }
                item = iterator.Next();
                }
            }
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        UpdateIndexes();
#endif
        }
    else if ( itemCount && iItems.Count() )
        {
        if ( FocusedItemVisible() )
            {
            // Keep the focused item in position, if possible.
            UpdateVisibleItems( FocusIndex(), FocusedItem() );
            }
        else if ( iItems[0].Item() )
            {
            // Keep the first item in position, if possible.
            UpdateVisibleItems( 0, iItems[0].Item() );
            }
        else
            {
            // Set items to the view from the beginning of the list.
            UpdateVisibleItems( 0, iTree.VisibleItem( 0 ) );
            }
        }
    }


// ---------------------------------------------------------------------------
// Handles the selection key by marking the item, if marking is ongoing, or
// otherwise selecting the focused item.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::HandleSelectionKeyEvent()
    {
    CAknTreeItem* item = FocusedItem();
    if ( item )
        {
        if ( MarkingOngoing() )
            {
            MarkItem( item, !item->IsMarked(), ETrue );
            }
        else
            {
            SelectItem( item, true );
            }
        }
    }


// ---------------------------------------------------------------------------
// Handles right arrow key event.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::HandleRightArrowKeyEvent()
    {
    if ( AknLayoutUtils::LayoutMirrored() )
        {
        AscendFocus();
        }
    else
        {
        DescendFocus();
        }
    }


// ---------------------------------------------------------------------------
// Handles left arrow key event.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::HandleLeftArrowKeyEvent()
    {
    if ( AknLayoutUtils::LayoutMirrored() )
        {
        DescendFocus();
        }
    else
        {
        AscendFocus();
        }
    }


// ---------------------------------------------------------------------------
// Handles up arrow key event by moving focus upwards. If the focus is already
// in the top-most item of the list and the list is set looping, the focus is
// moved to the bottom-most item.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::HandleUpArrowKeyEvent()
    {
    if ( iFlags.IsClear( EFlagSimultaneousMarking ) &&
         ( iFlags.IsSet( EFlagMark ) || iFlags.IsSet( EFlagUnmark ) ) )
        {
        MarkItem( FocusedItem(), iFlags.IsSet( EFlagMark ), ETrue );
        iFlags.Set( EFlagSimultaneousMarking );
        }

    TAknTreeIterator iterator = iTree.Iterator();
    iterator.SetCurrent( FocusedItem() );

    TInt index = LastVisibleItemIndex();
    if ( iterator.HasPrevious() )
        {
        if ( FocusedItemVisible() )
            {
            index = Min( 
                Max( FocusIndex() - 1, FirstVisibleItemIndex() ), index );
            }
        else
            {
            __ASSERT_DEBUG( iItems.Count(), User::Invariant() );

            TInt firstIndex = iTree.VisibleItemIndex( iItems[0].Item() );
            if ( firstIndex > iTree.VisibleItemIndex( FocusedItem() ) )
                {
                index = FirstVisibleItemIndex();
                }
            }
        SetFocusedItem( iterator.Previous(), index, ETrue );
        }
    else if ( IsLooping() )
        {
        // Move focus to the bottom-most item in the list.
        SetFocusedItem( iterator.Last(), index, ETrue );
        }

    if ( iFlags.IsSet( EFlagSimultaneousMarking ) )
        {
        MarkItem( FocusedItem(), iFlags.IsSet( EFlagMark ), ETrue );
        }
    }


// ---------------------------------------------------------------------------
// Handles down arrow key event by moving focus downwards. If the focus is
// already in the bottom-most item of the list and the list is set looping,
// the focus is moved to the top-most item.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::HandleDownArrowKeyEvent()
    {
    if ( iFlags.IsClear( EFlagSimultaneousMarking ) &&
         ( iFlags.IsSet( EFlagMark ) || iFlags.IsSet( EFlagUnmark ) ) )
        {
        MarkItem( FocusedItem(), iFlags.IsSet( EFlagMark ), ETrue );
        iFlags.Set( EFlagSimultaneousMarking );
        }

    TAknTreeIterator iterator = iTree.Iterator();
    iterator.SetCurrent( FocusedItem() );

    TInt index = FirstVisibleItemIndex();
    if ( iterator.HasNext() )
        {
        if ( FocusedItemVisible() )
            {
            index = Min( Max( FocusIndex() + 1, 0 ), LastVisibleItemIndex() );
            }
        else
            {
            __ASSERT_DEBUG( iItems.Count(), User::Invariant() );

            TInt firstIndex = iTree.VisibleItemIndex( iItems[0].Item() );
            if ( firstIndex < iTree.VisibleItemIndex( FocusedItem() ) )
                {
                index = LastVisibleItemIndex();
                }
            }
        SetFocusedItem( iterator.Next(), index, ETrue );
        }
    else if ( IsLooping() )
        {
        // Move focus to the top-most item in the list.
        SetFocusedItem( iterator.First(), index, ETrue );
        }

    if ( iFlags.IsSet( EFlagSimultaneousMarking ) )
        {
        MarkItem( FocusedItem(), iFlags.IsSet( EFlagMark ), ETrue );
        }
    }


// ---------------------------------------------------------------------------
// Moves focus deeper in the tree hierarchy. This is done by expanding the
// focused item, if it is a collapsed node; or moving focus to the first child
// of the item, if the item is an expanded node.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::DescendFocus()
    {
    if ( FocusedItem() )
        {
        CAknTreeNode* node = FocusedItem()->Node();
        if ( node )
            {
            if ( node->IsExpanded() )
                {
                if ( node->ChildCount() )
                    {
                    HandleDownArrowKeyEvent();
                    }
                }
            else
                {
                iTree.ExpandNode( iTree.Id( node ), ETrue );
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// Moves focus higher in the tree hierarchy. This is done by collapsing the
// focused item, if it is an expanded node; or moving focus to the item's
// parent, if the item is a collapsed node or a leaf.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::AscendFocus()
    {
    if ( FocusedItem() )
        {
        CAknTreeNode* node = FocusedItem()->Node();
        if ( node && node->IsExpanded() )
            {
            iTree.CollapseNode( iTree.Id( node ), ETrue );
            }
        else
            {
            CAknTreeNode* parent = FocusedItem()->Parent();
            if ( parent && iTree.Id( parent ) != KAknTreeIIDRoot )
                {
                TInt index = 0;
                for ( TInt ii = 0; ii < iItems.Count(); ++ii )
                    {
                    if ( iItems[ii].Item() == parent )
                        {
                        index = ii;
                        break;
                        }
                    }

                SetFocusedItem( parent, index, ETrue );

                if ( iFlags.IsSet( EFlagMark ) || iFlags.IsSet( EFlagUnmark ) )
                    {
                    MarkItem( parent, iFlags.IsSet( EFlagMark ), ETrue );
                    iFlags.Set( EFlagSimultaneousMarking );
                    }
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// Checks whether the list view is empty.
// ---------------------------------------------------------------------------
//
TBool CAknTreeListView::IsEmpty() const
    {
    for ( TInt ii = 0; ii < iItems.Count(); ++ii )
        {
        if ( iItems[ii].Item() )
            {
            // Item found, list is not empty.
            return EFalse;
            }
        }
    return ETrue;
    }


// ---------------------------------------------------------------------------
// Sets the layout for the view from the layout data.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::LayoutView()
    {
    // Subpane for list and scroll bar.
    TInt subpaneVariety = 0; // No find.
    TRect subpaneRect = RectFromLayout( Rect(), 
        AknLayoutScalable_Avkon::listscroll_gen_pane( subpaneVariety ) );

    // Check scrollbar visibilities to get correct variety for list pane.
    TInt listPaneVariety = 1; // No scrollbars.
    if ( iScrollbarFrame )
        {
        TBool hScrollbar = iScrollbarFrame->ScrollBarVisibility(
            CEikScrollBar::EHorizontal ) != CEikScrollBarFrame::EOff;
        TBool vScrollbar = iScrollbarFrame->ScrollBarVisibility(
            CEikScrollBar::EVertical ) != CEikScrollBarFrame::EOff;

        // Set list pane variety depending on scrollbar visibilities.
        if ( vScrollbar && hScrollbar )
            {
            listPaneVariety = 4;
            }
        else if ( vScrollbar )
            {
            listPaneVariety = 0;
            }
        else if ( hScrollbar )
            {
            listPaneVariety = 3;
            }

        // Layout scrollbars.
        TInt sbVariety = vScrollbar ? 2 : 1; // horizontal scrollbar variety
        AknLayoutUtils::LayoutHorizontalScrollBar( iScrollbarFrame, subpaneRect,
            AknLayoutScalable_Avkon::scroll_pane( sbVariety ).LayoutLine() );

        if ( hScrollbar )
            {
            AknLayoutUtils::LayoutVerticalScrollBar( iScrollbarFrame, subpaneRect,
                AknLayoutScalable_Avkon::scroll_pane_cp14().LayoutLine() );
            }
        else
            {
            sbVariety = 0; // vertical scrollbar variety
            AknLayoutUtils::LayoutVerticalScrollBar( iScrollbarFrame, subpaneRect,
                AknLayoutScalable_Avkon::scroll_pane( sbVariety ).LayoutLine() );
            }
        }

    // List.
    TRect listRect = RectFromLayout( subpaneRect,
        AknLayoutScalable_Avkon::list_gen_pane( listPaneVariety ) );

    // Hierarchial list item.
    TInt itemVariety = 0;
    TRect itemRect = RectFromLayout( listRect,
        AknLayoutScalable_Avkon::list_single_graphic_hl_pane( itemVariety ) );

    // Rect for structure line element.
    TInt lineVariety = 0; // Type.
    TRect lineSegmentRect = RectFromLayout( itemRect,
        AknLayoutScalable_Avkon::list_single_graphic_hl_pane_g1( lineVariety ) );

    // Minimum item width.
    TRect minimumItemRect = RectFromLayout( itemRect,
        AknLayoutScalable_Avkon::aid_size_min_hl_cp1() );

    // Calculate horizontal view span, which can be negative when items of
    // minimum width do not fit within the view.
    iHorizontalViewSpan = ( itemRect.Width() - minimumItemRect.Width() ) /
         lineSegmentRect.Width();

    // Count the maximum number of visible items for the new size.
    TInt itemCountLimit = Max( 0, listRect.Height() / itemRect.Height() );
    itemCountLimit += KAdditionalItems;

#ifdef RD_UI_TRANSITION_EFFECTS_LIST    
    iItemCountLimit = itemCountLimit;
#endif  

    if ( iItems.Count() > itemCountLimit )
        {
        // Remove items from the view.
        for ( TInt ii = iItems.Count() - 1; ii >= itemCountLimit; --ii )
            {
            iItems.Remove( ii );
            }
        }
    else
        {
        // Add items to the view.
        for ( TInt ii = iItems.Count(); ii < itemCountLimit; ++ii )
            {
            // This should not fail, if enough space was reserved for the
            // array, and if it fails, it results only fewer items being
            // shown in the list.
            iItems.Append( TAknTreeListViewItem() );
            }
        }

    // Get iterator and set it to point at the first item in the view, or at
    // the first item in the list, if the view does not contain any items.
    TAknTreeIterator iterator = iTree.Iterator();
    CAknTreeItem* first = iItems.Count() ? iItems[0].Item() : NULL;
    if ( first )
        {
        iterator.SetCurrent( first );
        iterator.Previous();
        }

    // Update items and their rectangles.
    for ( TInt ii = 0; ii < iItems.Count(); ++ii )
        {
        CAknTreeItem* item = iterator.Next();
        iItems[ii].SetItem( item );
        iItems[ii].SetRect( itemRect );
        itemRect.Move( 0, itemRect.Height() );

        // this is needed also when feature is not enabled
        iItems[ii].SetView( this );
        
       
        if ( item && FocusedItem() == item )
            {
            SetFocusIndex( ii );
            }
        }

    TRect viewRect( listRect );
    
    // Fill whole control area with list items when physics enabled
    // and threre is no horizontal scrollbar.  
    if ( iScrollbarFrame &&
         iScrollbarFrame->ScrollBarVisibility( CEikScrollBar::EHorizontal ) != CEikScrollBarFrame::EOn && 
         viewRect.Height() < Rect().Height() )
        {
        viewRect.iTl.iY = Rect().iTl.iY;
        viewRect.iBr.iY = Rect().iBr.iY;
        }
    iPhysicsHandler->SetViewRect( viewRect );
    iPhysicsHandler->SetItemHeight( itemRect.Height() );
    TRAP_IGNORE( InitPhysicsL() );    
    }


// ---------------------------------------------------------------------------
// Updates the span, thumb size and position for both of the scrollbars. New
// layout for the view is applied, if the visibility of either of the
// scrollbars changes.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::UpdateScrollbars()
    {
    if ( iScrollbarFrame )
        {
        iPhysicsHandler->UpdateScrollIndex( iScrollPhysicsTop );
        iScrollPhysicsTop = ETrue;
        
        // Get values for horizontal scrollbar.
        TInt hThumbPos = iViewLevel;
        TInt hThumbSpan = iHorizontalViewSpan;
        TInt hScrollSpan = Max( hThumbPos + hThumbSpan, iMaxViewLevel );

        if ( iHorizontalViewSpan <= 1 && iItems.Count() )
            {
            TInt a = iItems[0].Rect().Width();
            TInt b = iItems[0].LineSegmentRect( 0 ).Width();
            TInt c = iItems[0].ItemRect( iViewLevel, Indention(),
                IndentionWidth() ).Width();
            hThumbSpan = a/b;
            hScrollSpan = Max( hThumbPos + hThumbSpan, c/b );
            }

        if ( AknLayoutUtils::LayoutMirrored() )
            {
            hThumbPos = hScrollSpan - ( hThumbPos + hThumbSpan );
            }
        TEikScrollBarModel hModel( hScrollSpan, hThumbSpan, hThumbPos );


        // Values for empty vertical scrollbar.
        TInt vThumbSpan( 10 ); // nonzero value is needed to draw "empty scrollbar"
        TInt vThumbPos( 0 );
        TInt vScrollSpan( 0 );
       
        TAknTreeIterator iterator = iTree.Iterator();
        if ( iterator.HasNext() )
            {
            iPhysicsHandler->GetVScrollbarParams( vThumbSpan, 
                                                  vThumbPos, 
                                                  vScrollSpan );
            }
        TEikScrollBarModel vModel( vScrollSpan, vThumbSpan, vThumbPos );


        // Change visibilities when necessary.
        CEikScrollBarFrame::TScrollBarVisibility hVisibility = 
            CEikScrollBarFrame::EOn;
        CEikScrollBarFrame::TScrollBarVisibility vVisibility = 
            CEikScrollBarFrame::EOn;
                  
        if ( iMaxViewLevel <= iHorizontalViewSpan )
            {
            hVisibility = CEikScrollBarFrame::EOff;
            // when horizontal scrollbar not visible, adjust view to left
            iViewLevel = 0;
            }
        
        if ( hVisibility != iScrollbarFrame->ScrollBarVisibility( 
                CEikScrollBar::EHorizontal ) ||
             vVisibility != iScrollbarFrame->ScrollBarVisibility(
                CEikScrollBar::EVertical ) )
            {
            TRAP_IGNORE( iScrollbarFrame->SetScrollBarVisibilityL(
                hVisibility, vVisibility ) );

            // Set new model for scrollbars.
            iScrollbarFrame->Tile( &hModel, &vModel );

            LayoutView();
            UpdateScrollbars(); // Recursion
            
            // Update animation in case that scrollbar visibility change
            // has affected the highlight size of focused item.
            UpdateAnimation();
            }
        else
            {
            // Set new model for scrollbars.
            iScrollbarFrame->Tile( &hModel, &vModel );  
            }        
        }
       
    }
    
    
    
  


// ---------------------------------------------------------------------------
// Adjusts the horizontal position of the view items. The adjustment is made
// so that the beginning of the focused item is visible, including one
// indention segment in front of the item, if it has such, and if possible,
// the visible item width exeeds the specified minimum width.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::UpdateViewLevel()
    {
    if ( FocusedItemVisible() )
        {
        __ASSERT_DEBUG( FocusedItem(), User::Invariant() );

        // Adjust view's horizontal position.
        TInt itemLevel = Indention() ? FocusedItem()->Level() : 1;
        TInt maxViewLevel = Max( itemLevel - 2, 0 );
        if ( iViewLevel > maxViewLevel )
            {
            // The beginning of the focused item is not seen, move the view
            // so that the beginning of focused item and possibly one
            // indention segment in front of it can be seen.
            iViewLevel = maxViewLevel;
            }
        else if ( iViewLevel < maxViewLevel )
            {
            // View is moved until the visible part of the item exeeds the
            // specified minimum, and if the minimum cannot be exeeded, the
            // beginning of the item has to remain visible.
            TAknTreeListViewItem viewItem = iItems[FocusIndex()];
            TInt minimumWidth = FocusedItem()->MinimumSize().iWidth;
            TInt indentCount = ( itemLevel - 1 ) - iViewLevel;
            TInt lineWidth = viewItem.Rect().Width();
            TInt indentWidth = ( IndentionWidth() < 0 ) ?
                viewItem.LineSegmentWidth() : IndentionWidth();
            TInt itemWidth = lineWidth - indentCount * indentWidth;
            while ( itemWidth < minimumWidth && iViewLevel < maxViewLevel )
                {
                iViewLevel += 1;
                itemWidth += indentWidth;
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// Updates the highlight animation.
// ---------------------------------------------------------------------------
//
TBool CAknTreeListView::UpdateAnimation() const
    {
    if ( FocusedItemVisible() && iAnimation )
        {
        TRect rect = iItems[FocusIndex()].HighlightRect( iViewLevel,
            Indention(), IndentionWidth() );
        return UpdateAnimation( rect );
        }
    return EFalse;
    }


TBool CAknTreeListView::UpdateAnimation( const TRect& aRect ) const
    {
    if ( !iAnimation )
        {
        return EFalse;
        }

   if ( iAnimation->Size() != aRect.Size() || iAnimation->NeedsInputLayer() )
        {
        iFlags.Clear( EFlagUpdateBackground );
        TRAPD( error, ResizeAnimationL( aRect.Size(), ETrue ) )
        if ( error )
            {
            delete iAnimation;
            iAnimation = NULL;
            return EFalse;
            }
        }
    else if ( iFlags.IsSet( EFlagUpdateBackground ) )
        {
        iFlags.Clear( EFlagUpdateBackground );
        if ( iAnimation->InputRgbGc() )
            {
            DrawHighlightBackground( *iAnimation->InputRgbGc() );
            if ( iAnimation->UpdateOutput() != KErrNone )
                {
                delete iAnimation;
                iAnimation = NULL;
                return EFalse;
                }
            }
        }
    return ETrue;
    }


// ---------------------------------------------------------------------------
// Sets focused item.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::SetFocusedItem( CAknTreeItem* aFocusedItem )
    {
    if ( iAnimation )
        {
        if ( !iFocusedItem && aFocusedItem )
            {
            iAnimation->Start();
            }
        else if ( !aFocusedItem )
            {
            iAnimation->Stop();
            }
        }

    if ( iFocusedItem != aFocusedItem )
        {
        iFocusedItem = aFocusedItem;

        // Although the focused item is changed even though the list itself
        // is not focused, the client is notified of focus change only when
        // list is set focused.
        if ( IsFocused() )
            {
            ReportTreeListEvent( MAknTreeListObserver::EItemFocused,
                iTree.Id( iFocusedItem ) );
            }
        }
    }


// ---------------------------------------------------------------------------
// Checks whether the focused item is currently visible.
// ---------------------------------------------------------------------------
//
TBool CAknTreeListView::FocusedItemVisible() const
    {
    if ( iFocusedItem && iFocusedItemIndex >= 0 && 
        iFocusedItemIndex < iItems.Count() )
        {
        if ( iPhysicsHandler->FocusedItemVisible( iFocusedItemIndex ) )
            {
            return ETrue;            
            }
        }
    return EFalse;
    }


// ---------------------------------------------------------------------------
// Sets the focused item index.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::SetFocusIndex( TInt aIndex )
    {
    if ( iFocusedItemIndex != aIndex )
        {
        iFocusedItemIndex = aIndex;
        iFlags.Set( EFlagUpdateBackground );

        if ( iAnimation )
            {
            if ( aIndex >= 0 && aIndex < iItems.Count() )
                {
                iAnimation->Continue();
                }
            else
                {
                iAnimation->Pause();
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// Return the index of focused item.
// ---------------------------------------------------------------------------
//
TInt CAknTreeListView::FocusIndex() const
    {
    return iFocusedItemIndex;
    }


// ---------------------------------------------------------------------------
// Creates highlight animation for the list view.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::CreateAnimationL()
    {
    delete iAnimation; iAnimation = NULL;

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        MAknListBoxTfxInternal *transApi = CAknListLoader::TfxApiInternal( iGc );
        if ( transApi && transApi->VerifyKml() == KErrNone )
            {
            return;
            }
#endif //RD_UI_TRANSITION_EFFECTS_LIST   

    iAnimation = CAknsEffectAnim::NewL( this );
    if ( !iAnimation->ConstructFromSkinL( iAnimationIID ) )
        {
        User::Leave( KErrNotFound );
        }
    }


// ---------------------------------------------------------------------------
// Draws animation background to given graphic context.
// ---------------------------------------------------------------------------
//
TBool CAknTreeListView::DrawHighlightBackground( CFbsBitGc& aGc ) const
    {
    if ( iAnimation && FocusedItemVisible() )
        {
        TRect rect = iItems[FocusIndex()].HighlightRect( iViewLevel,
            Indention(), IndentionWidth() );

        MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

        return AknsDrawUtils::DrawBackground( AknsUtils::SkinInstance(), cc,
            this, aGc, TPoint(), rect, KAknsDrawParamBottomLevelRGBOnly );
        }
    return EFalse;
    }


// ---------------------------------------------------------------------------
// Resize animation.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::ResizeAnimationL( const TSize& aHighlightSize,
    TBool aAboutToStart ) const
    {
    iAnimation->BeginConfigInputLayersL( aHighlightSize, aAboutToStart );

    if ( iAnimation->InputRgbGc() )
        {
        DrawHighlightBackground( *iAnimation->InputRgbGc() );
        }

    iAnimation->EndConfigInputLayersL();
    }


// ---------------------------------------------------------------------------
// Draws animation.
// ---------------------------------------------------------------------------
//
TBool CAknTreeListView::DrawAnimation( CBitmapContext& aGc,
    const TRect& aRect ) const
    {
    if ( !UpdateAnimation( aRect ) )
        {
        return EFalse;
        }

    return iAnimation->Render( aGc, aRect );
    }


// ---------------------------------------------------------------------------
// Draws highlight to the given rectangle.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::DrawHighlight( CWindowGc& aGc,
                                      const TRect& aRect, TBool aPressedDown ) const
    {
    TRect newRect( aRect );
    newRect.iBr.iY -= Offset();
    newRect.iTl.iY -= Offset();
    
    TAknLayoutRect tlRect;
    tlRect.LayoutRect( newRect,
        SkinLayout::List_highlight_skin_placing__general__Line_2() );

    TAknLayoutRect brRect;
    brRect.LayoutRect( newRect,
        SkinLayout::List_highlight_skin_placing__general__Line_5() );

    TRect outerRect( tlRect.Rect().iTl, brRect.Rect().iBr );
    TRect innerRect( tlRect.Rect().iBr, brRect.Rect().iTl );

    // No pressed highlight if single click enabled
    if ( SingleClickEnabled() )
        {
        aPressedDown = EFalse;
        }

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    AknsDrawUtils::DrawFrame( skin, aGc, outerRect, innerRect,
                              aPressedDown ? 
                              KAknsIIDQsnFrListPressed : KAknsIIDQsnFrList,
                              KAknsIIDDefault );
    }


// ---------------------------------------------------------------------------
// Handles selection of the specified item. If the item is collapsed node, it
// is expande; if the item is expanded node, it is collapsed; or if it is a
// leaf, the selection event is sent to observers of the list. 
// ---------------------------------------------------------------------------
//
void CAknTreeListView::SelectItem( CAknTreeItem* aItem, bool aKeyPressed )
    {
    __ASSERT_DEBUG( aItem, User::Invariant() );

    CAknTreeNode* node = aItem->Node();
    if ( node )
        {
        if ( node->IsExpanded() )
            {
            iTree.CollapseNode( iTree.Id( node ), ETrue );
            }
        else
            {
            iTree.ExpandNode( iTree.Id( node ), ETrue );
            }
        }
    else if ( aKeyPressed || iPreviouslyFocusedItem == aItem
            || SingleClickEnabled() )
        {
        // Notify client of selection event.
        ReportTreeListEvent( MAknTreeListObserver::EItemSelected,
            iTree.Id( aItem ) );
        }
    }


// ---------------------------------------------------------------------------
// Changes the marking of specified item, when marking is enabled.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::MarkItem( CAknTreeItem* aItem, TBool aMarked,
    TBool aDrawNow )
    {
    if ( iFlags.IsSet( EFlagMarkingEnabled ) )
        {
        TAknTreeItemID item = iTree.Id( aItem );
        if ( item != KAknTreeIIDNone )
            {
            iTree.SetMarked( item, aMarked, aDrawNow );
            if ( FocusedItem() == aItem )
                {
                UpdateMSKCommand();
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// Changes the marking of specified items, when marking is enabled.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::MarkItems( CAknTreeItem* aFirst, CAknTreeItem* aLast,
    TBool aMarked, TBool aDrawNow )
    {
    if ( iFlags.IsSet( EFlagMarkingEnabled ) )
        {
        TAknTreeIterator iterator = iTree.Iterator();

        TInt first = iTree.VisibleItemIndex( aFirst );
        TInt last = iTree.VisibleItemIndex( aLast );
        if ( first != KErrNotFound && last != KErrNotFound )
            {
            TAknTreeIterator iterator = iTree.Iterator();
            CAknTreeItem* item = NULL;
            if ( first < last )
                {
                item = aFirst;
                iterator.SetCurrent( aFirst );
                }
            else
                {
                item = aLast;
                iterator.SetCurrent( aLast );
                aLast = aFirst;
                }

            while ( item && item != aLast && iterator.HasNext() )
                {
                MarkItem( item, aMarked, EFalse );
                item = iterator.Next();
                }

            MarkItem( aLast, aMarked, aDrawNow );
            }
        }
    }


// ---------------------------------------------------------------------------
// Begins marking.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::BeginMarkingL()
    {
    __ASSERT_DEBUG( iFlags.IsClear( EFlagUnmark ), User::Invariant() );
    __ASSERT_DEBUG( iFlags.IsClear( EFlagMark ), User::Invariant() );

    if ( iFlags.IsSet( EFlagMarkingEnabled ) && FocusedItem() )
        {
        if ( FocusedItem()->IsMarked() )
            {
            iFlags.Set( EFlagUnmark );
            }
        else
            {
            iFlags.Set( EFlagMark );
            }

        // Start long press timer to enable marking mode after delay.
        StartLongPressTimerL();

        // Set view as cba observer.
        CEikButtonGroupContainer* cba;
        MopGetObject( cba );
        CAknEnv::Static()->RequestCommandMediationL( *cba, *this );
        }
    }


// ---------------------------------------------------------------------------
// Ends ongoing marking.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::EndMarking()
    {
    __ASSERT_DEBUG( iFlags.IsSet( EFlagMark ) || iFlags.IsSet( EFlagUnmark ),
        User::Invariant() );

    // Stop long press timer.
    if ( iLongPressTimer && iLongPressTimer->IsActive() )
        {
        iLongPressTimer->Cancel();
        }

    // Exits marking mode.
    if ( iFlags.IsSet( EFlagMarkingMode ) )
        {
        ExitMarkingMode();
        }

    // Remove MSK observer.
    CEikButtonGroupContainer* cba;
    MopGetObject( cba );
    CAknEnv::Static()->EndCommandMediation( *this );

    iFlags.Clear( EFlagMark );
    iFlags.Clear( EFlagUnmark );
    iFlags.Clear( EFlagSimultaneousMarking );
    }


// ---------------------------------------------------------------------------
// Checks whether marking is currently ongoing.
// ---------------------------------------------------------------------------
//
TBool CAknTreeListView::MarkingOngoing() const
    {
    return iFlags.IsSet( EFlagUnmark ) || iFlags.IsSet( EFlagMark );
    }


// ---------------------------------------------------------------------------
// Starts the long press timer.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::StartLongPressTimerL()
    {
    if ( iLongPressTimer )
        {
        if ( iLongPressTimer->IsActive() )
            {
            iLongPressTimer->Cancel();
            }

        iLongPressTimer->Start( KLongPressInterval, KLongPressInterval,
            TCallBack( ReportLongPressL, this ) );
        }
    }


// ---------------------------------------------------------------------------
// Callback method for long press timer.
// ---------------------------------------------------------------------------
//
TInt CAknTreeListView::ReportLongPressL( TAny* aThis )
    {
    __ASSERT_DEBUG( aThis, User::Invariant() );
    static_cast<CAknTreeListView*>( aThis )->DoHandleLongPressL();
    return NULL;
    }


// ---------------------------------------------------------------------------
// Handles long press.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::DoHandleLongPressL()
    {
    if ( iFlags.IsClear( EFlagMarkingMode ) )
        {
        EnterMarkingMode();
        }
    }


// ---------------------------------------------------------------------------
// Enters marking mode.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::EnterMarkingMode()
    {
    CEikButtonGroupContainer* bgc;
    CCoeControl* MSK = NULL;
    MopGetObject( bgc );
    if ( bgc )
        {
        CEikCba* cba = static_cast<CEikCba*>( bgc->ButtonGroup() );
        if ( cba )
            {
            MSK = cba->Control( 3 );
            }
        }

    TInt newResourceId = NULL;
    if ( MSK && FocusedItem() )
        {
        if ( FocusedItem()->IsMarked() )
            {
            newResourceId = R_AVKON_SOFTKEY_UNMARK;
            }
        else
            {
            newResourceId = R_AVKON_SOFTKEY_MARK;
            }
        }

    if ( newResourceId )
        {
        TRAPD( err, bgc->AddCommandToStackL( 3, newResourceId ) );
        if ( !err )
            {
            ReportTreeListEvent( MAknTreeListObserver::EMarkingModeEnabled,
                iTree.Id( FocusedItem() ) );
            iFlags.Set( EFlagMarkingMode );
            bgc->DrawNow();
            }
        }
    }


// ---------------------------------------------------------------------------
// Exits marking mode.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::ExitMarkingMode()
    {
    if ( iFlags.IsSet( EFlagMarkingMode ) )
        {
        CEikButtonGroupContainer* bgc = NULL;
        CCoeControl* MSK = NULL;
        MopGetObject( bgc );
        if ( bgc )
            {
            CEikCba* cba = static_cast<CEikCba*>( bgc->ButtonGroup() );
            if ( cba )
                {
                MSK = cba->Control( 3 );
                if ( MSK && ( cba->ControlId( MSK ) == EAknSoftkeyMark ||
                     cba->ControlId( MSK ) == EAknSoftkeyUnmark ) )
                    {
                    bgc->RemoveCommandFromStack( 3, cba->ControlId( MSK ) );
                    }
                }
            }
        ReportTreeListEvent( MAknTreeListObserver::EMarkingModeDisabled,
            iTree.Id( FocusedItem() ) );
        iFlags.Clear( EFlagMarkingMode );
        }
    }


// ---------------------------------------------------------------------------
// Updates MSK command.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::UpdateMSKCommand()
    {
    CEikButtonGroupContainer* bgc = NULL;
    MopGetObject( bgc );
    if ( bgc )
        {
        TInt newResourceId = NULL;
        MEikButtonGroup* bg = bgc->ButtonGroup();
        if ( FocusedItem() && bg )
            {
            if ( FocusedItem()->IsMarked() && 
                bg->CommandId( 3 ) == EAknSoftkeyMark )
                {
                newResourceId = R_AVKON_SOFTKEY_UNMARK;
                }
            else if ( !FocusedItem()->IsMarked() &&
                bg->CommandId( 3 ) == EAknSoftkeyUnmark )
                {
                newResourceId = R_AVKON_SOFTKEY_MARK;
                }
            }

        if ( newResourceId )
            {
            TRAP_IGNORE( bgc->SetCommandL( 3, newResourceId ) );
            bgc->DrawNow();
            }
        }
    }

// ---------------------------------------------------------------------------
// Draws the items when physics is enabled.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::DrawItemsWithPhysics( const TRect& aRect ) const
    {
    TBool empty = IsEmpty();

#ifdef RD_UI_TRANSITION_EFFECTS_LIST    
    CWindowGc& gc = iGc && !empty ? *iGc : SystemGc();
    TInt offset = Offset();
#else
    CWindowGc& gc = SystemGc();
#endif

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( &gc );
    if ( !empty && transApi )
        {
        
        //fix scrollbar flickering by adding nondrawingrect
        if ( iScrollbarFrame &&  iScrollbarFrame->ScrollBarVisibility
            (CEikScrollBar::EHorizontal ) != CEikScrollBarFrame::EOff )
            {
            //why doesn't this link?
            //transApi->AddNonDrawingRect( iScrollbarFrame->HorizontalScrollBar()->Rect() );
            }
        if ( iScrollbarFrame &&  iScrollbarFrame->ScrollBarVisibility
            (CEikScrollBar::EVertical ) != CEikScrollBarFrame::EOff )
            {
            transApi->ResetNonDrawingRects ();
            transApi->AddNonDrawingRect( iScrollbarFrame->VerticalScrollBar()->Rect() );
            }
        
        transApi->SetListType( MAknListBoxTfxInternal::EListBoxTypeTreeList );
        transApi->BeginRedraw( MAknListBoxTfxInternal::EListView, Rect() );
        transApi->StartDrawing( MAknListBoxTfxInternal::EListView );
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    AknsDrawUtils::Background( skin, cc, this, gc, aRect );

    if ( empty )
        {
        __ASSERT_DEBUG( iEmptyListText, User::Invariant() );
        AknDrawWithSkins::DrawEmptyList( Rect(), gc, iEmptyListText->Des(),
            const_cast<CAknTreeListView*>( this ) );
        }
    else
        {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( transApi )
            {
            transApi->StopDrawing();
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

        const TInt itemCount = iItems.Count();
        for ( TInt ii = 0; ii < itemCount; ++ii )
            {
            TRect drawRect( iItems[ii].Rect() );

            if ( iItems[ii].Item() )
                {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                TRect tfxDrawRect( drawRect );
                tfxDrawRect.Move( 0, -offset );

                if ( transApi )
                    {
                    transApi->StartDrawing( MAknListBoxTfxInternal::EListNotSpecified );
                    }

  
                TRect clippingRect( tfxDrawRect );
                
                // If horizontal scrollbar on, reduce clipping rect
                // based on view rect from layout data 
                if ( iScrollbarFrame->ScrollBarVisibility( CEikScrollBar::EHorizontal )
                    == CEikScrollBarFrame::EOn )
                    {
                    TRect viewRect( iPhysicsHandler->ViewRect( ) );
                    if ( clippingRect.iBr.iY > viewRect.iBr.iY )
                        {
                        clippingRect.iBr.iY = viewRect.iBr.iY;
                        }
                    }
                
                // Set clipping rect.    
                gc.SetClippingRect( clippingRect );


                if ( transApi )
                    {
                    transApi->StopDrawing();
                    }
#endif
                TBool focused = ( IsFocused() && FocusedItem() &&
                    iItems[ii].Item() == FocusedItem() );

                if ( SingleClickEnabled() && !HighlightEnabled() )
                    {
                    focused = EFalse;
                    }

                if ( focused )
                    {
                    // Draw highlight for focused item.
                    TRect highlightRect( iItems[ii].HighlightRect(
                        iViewLevel, Indention(), IndentionWidth() ) );

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                        TRect tfxHighlightRect( highlightRect );
                        tfxHighlightRect.Move( 0, -offset );
#endif //RD_UI_TRANSITION_EFFECTS_LIST

                    if ( iIsPressedDownState || !DrawAnimation( gc, highlightRect ) )
                        {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                        if ( transApi )
                            {
                            transApi->Invalidate(MAknListBoxTfxInternal::EListHighlight );
                            transApi->BeginRedraw( MAknListBoxTfxInternal::EListHighlight, tfxHighlightRect );
                            transApi->StartDrawing( MAknListBoxTfxInternal::EListHighlight );
                            }
#endif //RD_UI_TRANSITION_EFFECTS_LIST

                        DrawHighlight( gc, highlightRect, iIsPressedDownState );

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                        if ( transApi )
                            {
                            transApi->StopDrawing();
                            transApi->EndRedraw(MAknListBoxTfxInternal::EListHighlight);
                            }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
                        }
                        
                    drawRect.BoundingRect( highlightRect );

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                    tfxDrawRect.BoundingRect( tfxHighlightRect );
#endif //RD_UI_TRANSITION_EFFECTS_LIST
                    }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                if (iItems[ii].Item()) 
                {
                if ( transApi )
                    {
                    transApi->BeginRedraw(MAknListBoxTfxInternal::EListItem, tfxDrawRect, iTree.VisibleItemIndex(iItems[ii].Item()));
                    transApi->StartDrawing( MAknListBoxTfxInternal::EListItem );
                    }
#endif //RD_UI_TRANSITION_EFFECTS_LIST

                // Draw item.
                iItems[ii].Draw( gc, iTree, drawRect, focused, iViewLevel,
                    StructureLines(), Indention(), IndentionWidth() );

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                if ( transApi )
                    {
                    transApi->StopDrawing();
                    transApi->EndRedraw(MAknListBoxTfxInternal::EListItem, iTree.VisibleItemIndex(iItems[ii].Item()));
                    }
                }
#endif //RD_UI_TRANSITION_EFFECTS_LIST

                }
            }
        }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( !empty && transApi )
        {
        transApi->EndViewRedraw( Rect() );
    }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
    }


// ---------------------------------------------------------------------------
// Returns first visible item index.
// ---------------------------------------------------------------------------
//
TInt CAknTreeListView::FirstVisibleItemIndex() const
    {
    return iPhysicsHandler->FirstVisibleItemIndex();
    }


// ---------------------------------------------------------------------------
// Returns last visible item index.
// ---------------------------------------------------------------------------
//
TInt CAknTreeListView::LastVisibleItemIndex() const
    {
    return iPhysicsHandler->LastVisibleItemIndex();
    }


// ---------------------------------------------------------------------------
// Updates view items so that aItem is visible.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::UpdateViewItemAsVisible( CAknTreeItem* aItem )
    {
    
    // Do nothing if all items fit to view
    if ( iItems.Count() >= iTree.VisibleItemCount() )
        {
        return;
        }
    
    // Items after this item
    TInt itemsAfterVisible( 
        iTree.VisibleItemCount() - 1 - iTree.VisibleItemIndex( aItem ) );

    CAknTreeItem* item( aItem );
    TAknTreeIterator iterator( iTree.Iterator() );
    iterator.SetCurrent( item );
    SetFocusIndex( KMinTInt );

    // If there are enough items to fill the view after this item,
    // set this item as first in the item list    
    if ( itemsAfterVisible > iItems.Count() )
        {
        for ( TInt ii = 0; ii < iItems.Count(); ++ii )
            {
            iItems[ii].SetItem( item );
            if ( item )
                {
                if ( item == FocusedItem() )
                    {
                    SetFocusIndex( ii );
                    }
                item = iterator.Next();
                }
            }
        }

    // Else adjust the visible items from the last item
    else
        {
        item = iTree.VisibleItem( iTree.VisibleItemCount() - 1 );
        iterator.SetCurrent( item );
        for ( TInt ii = iItems.Count() - 1; ii >= 0; ii-- )
            {
            iItems[ii].SetItem( item );
            if ( item )
                {
                if ( item == FocusedItem() )
                    {
                    SetFocusIndex( ii );
                    }
                item = iterator.Previous();
                }
            }
        iScrollPhysicsTop = EFalse;
        }
        
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// Draws the tree list view.
// ---------------------------------------------------------------------------
//
void CAknTreeListView::Draw( const TRect& aRect ) const
    {
    DrawItemsWithPhysics( aRect );
    }


// ---------------------------------------------------------------------------
// Enables or disables the highlight drawing
// ---------------------------------------------------------------------------
//
void CAknTreeListView::EnableHighlight( TBool aEnabled )
    {
    if ( aEnabled )
        {
        iFlags.Set( EFlagHighlightEnabled );
        }
    else
        {
        iFlags.Clear( EFlagHighlightEnabled );
        }
    }

// ---------------------------------------------------------------------------
// Returns ETrue if highlight is enabled
// ---------------------------------------------------------------------------
//
TBool CAknTreeListView::HighlightEnabled() const
    {
    return iFlags.IsSet( EFlagHighlightEnabled );
    }

// ---------------------------------------------------------------------------
// Returns ETrue if single click is enabled
// ---------------------------------------------------------------------------
//
TBool CAknTreeListView::SingleClickEnabled() const
    {
    if ( iFlags.IsSet( EFlagSingleClickEnabled ) )
        {
        return ETrue;
        }
    return EFalse;
    }

// -----------------------------------------------------------------------------
// CAknTreeListView::CollectionState
// -----------------------------------------------------------------------------
//
TUint CAknTreeListView::CollectionState() const
    {
    TUint state( 0 );
    if ( IsVisible() )
        {
        state |= MAknCollection::EStateCollectionVisible;
        }
    if ( HighlightEnabled() )
        {
        state |= MAknCollection::EStateHighlightVisible;
        }
    return state;
    }

// -----------------------------------------------------------------------------
// CAknTreeListView::ItemActionMenuClosed
// -----------------------------------------------------------------------------
//
void CAknTreeListView::ItemActionMenuClosed()
    {
    iFlags.Clear( EFlagIgnoreButtonUpEvent );
    EnableHighlight( EFalse );
    DrawDeferred();
    }

// -----------------------------------------------------------------------------
// CAknTreeListView::CollectionExtension
// -----------------------------------------------------------------------------
//
TInt CAknTreeListView::CollectionExtension( TUint /*aExtensionId*/,
        TAny*& /*a0*/, TAny* /*a1*/ )
    {
    return KErrNone;
    }

// ---------------------------------------------------------------------------
// CAknTreeListView::HandleLongTapEventL
// ---------------------------------------------------------------------------
//
void CAknTreeListView::HandleLongTapEventL(
        const TPoint& /*aPenEventLocation*/,
        const TPoint& aPenEventScreenLocation)
    {
    iFlags.Set( EFlagIgnoreButtonUpEvent );
    iItemActionMenu->ShowMenuL( aPenEventScreenLocation, 0 );
    }

// ---------------------------------------------------------------------------
// CAknTreeListView::LongTapPointerEventL
// ---------------------------------------------------------------------------
//
void CAknTreeListView::LongTapPointerEventL(
        const TPointerEvent& aPointerEvent)
    {
    if ( iLongTapDetector && iItemActionMenu && iItemActionMenu->InitMenuL() )
        {
        iLongTapDetector->PointerEventL( aPointerEvent );
        }
    }

// ---------------------------------------------------------------------------
// CAknTreeListView::CancelLongTapDetector
// ---------------------------------------------------------------------------
//
void CAknTreeListView::CancelLongTapDetectorL()
    {
    if ( iLongTapDetector )
        {
        iLongTapDetector->CancelAnimationL();
        }
    }

// ---------------------------------------------------------------------------
// CAknTreeListView::HasMarkedItemsL
// ---------------------------------------------------------------------------
//
TBool CAknTreeListView::HasMarkedItemsL()
    {
    RArray<TInt> selection;
    CleanupClosePushL( selection );
    iList.GetMarkedItemsL( selection );
    TInt count( selection.Count() );
    CleanupStack::PopAndDestroy( &selection );
    if ( count > 0 )
         {
         return ETrue;
         }
    return EFalse;
    }


#ifdef RD_UI_TRANSITION_EFFECTS_LIST
// ---------------------------------------------------------------------------
// Sets the tfxgc for effects
// ---------------------------------------------------------------------------
//
void CAknTreeListView::SetGc( CWindowGc* aGc) 
    {
    iGc = aGc;
    iPhysicsHandler->SetGc( aGc );
    }

TInt& CAknTreeListView::ItemCountLimit( ) 
    {
    return iItemCountLimit;
    }

TInt& CAknTreeListView::HighlightIndex()
    {
    return iHighlightIndex;
    }
    
    
TInt& CAknTreeListView::TopIndex()
    {
    return iTopIndex;
    }

TInt& CAknTreeListView::BottomIndex()
    {
    return iBottomIndex;
    }
    
void CAknTreeListView::UpdateIndexes()
    {
    iTopIndex = iBottomIndex = iHighlightIndex = 0;
    
    if ( iItems.Count() )
        {
        for (TInt i=iItems.Count()-1; i>=0; i--)
            {
            if (iItems[i].Item())   
                {
                iBottomIndex = iTree.VisibleItemIndex(iItems[i].Item());
                break;
                }
            }
    
        iTopIndex = iTree.VisibleItemIndex(iItems[0].Item());
        iHighlightIndex = iTree.VisibleItemIndex(FocusedItem());
        } 
    }

#endif //RD_UI_TRANSITION_EFFECTS_LIST
