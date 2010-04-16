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
* Description:  AknTreeListView physics handler
*
*/

#include <aknphysics.h>
#include <aknphysicsobserveriface.h>
#include <babitflags.h>
#include <eiksbobs.h>
#include <eikon.hrh> // EKeyOK
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
#include <aknlistloadertfx.h>
#include <aknlistboxtfx.h>
#endif // RD_UI_TRANSITION_EFFECTS_LIST

#include <touchfeedback.h>

#include "akntree.h"
#include "akntreelistview.h"
#include "akntreelistphysicshandler.h"
#include "akntreelist.h"
#include "akntrace.h" // trace

// Tree list view physics handler flag definitions.
enum TAknTreeListPhysicsHandlerFlags
    {
    // pressed-down highlight should be drawn to focused item
    EFlagPDHighlightToFocusedItem,
    // pressed-down highlight should be drawn to nonfocused item
    EFlagPDHighlightToNonFocusedItem,
    EFlagButtonUpReceived,
    EFlagUpdatingView
    };



// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknTreeListPhysicsHandler::NewL
// ---------------------------------------------------------------------------
//
CAknTreeListPhysicsHandler* CAknTreeListPhysicsHandler::NewL(
    CAknTreeListView* aTreeListView,
    CAknTree* aTree,
    RArray<TAknTreeListViewItem>* aItems )
    {
    CAknTreeListPhysicsHandler* self = 
        CAknTreeListPhysicsHandler::NewLC( aTreeListView, aTree, aItems );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknTreeListPhysicsHandler::NewLC
// ---------------------------------------------------------------------------
//
CAknTreeListPhysicsHandler* CAknTreeListPhysicsHandler::NewLC( 
    CAknTreeListView* aTreeListView,
    CAknTree* aTree,
    RArray<TAknTreeListViewItem>* aItems )
    {
    CAknTreeListPhysicsHandler* self 
        = new ( ELeave ) CAknTreeListPhysicsHandler( 
            aTreeListView, aTree, aItems );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// CAknTreeListPhysicsHandler::~CAknTreeListPhysicsHandler
// ---------------------------------------------------------------------------
//
CAknTreeListPhysicsHandler::~CAknTreeListPhysicsHandler()
    {
    delete iHighlightTimer;
    delete iPhysics;
    }


// ---------------------------------------------------------------------------
// CAknTreeListPhysicsHandler::HandlePointerEventL
// ---------------------------------------------------------------------------
//
void CAknTreeListPhysicsHandler::HandlePointerEventL(
    const TPointerEvent& aPointerEvent, const TInt& aViewLevel,
    TBool aMarking, TBool aShiftPressed, TBool aCtrlPressed )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( aPointerEvent.iType == TPointerEvent::EButton1Down && iEnableEvents )
        {
        iEventsBlocked = EFalse;
        iEnableEvents = EFalse;
        }
    if ( iEventsBlocked )
        {
        _AKNTRACE("CAknTreeListPhysicsHandler::%s Return due to event blocked", __FUNCTION__);
        _AKNTRACE_FUNC_EXIT;
	    return;
        }
    
    // Panning/flicking logic    

    // EButton1Down

    TBool wasFlicking( EFalse );
    TBool wasScrolling = ( iPhysics->OngoingPhysicsAction() != 
        CAknPhysics::EAknPhysicsActionNone );

    if ( aPointerEvent.iType == TPointerEvent::EButton1Down &&
        iViewRect.Contains( aPointerEvent.iPosition ) )
        {
        iPenDown = ETrue;
        if ( iPhysics->OngoingPhysicsAction() == CAknPhysics::EAknPhysicsActionFlicking )
            {
            // flicking was ongoing when content stopped
            if ( iFeedback )
                {
                iFeedback->InstantFeedback( ETouchFeedbackBasic );
                }
            wasFlicking = ETrue;
            }
        
        iFlags.Clear( EFlagButtonUpReceived );
        iPosition = aPointerEvent.iPosition;
        iStartPosition = aPointerEvent.iPosition;

        iPhysics->StopPhysics();
        iPhysics->ResetFriction();
    
        iStartTime.HomeTime();
        iHighlightTimer->Cancel();
        
        iItemToBeFocused = NULL;
        iIndexToBeFocused = -1;
        iItemToBeSelected = NULL;
        
        iPanningActivated = EFalse;

        iPlayFeedbackOnUp = EFalse;

        // Check if marquee needs to be disabled
        if ( iTreeListView->SingleClickEnabled()
                && iTree->IsMarqueeOn() )
            {
            iTree->EnableMarquee( EFalse );
            }
           
        iEmptyAreaClicked = EmptyAreaClicked( aPointerEvent.iPosition ); 
        }
    
    // EDrag    
   
    if ( aPointerEvent.iType == TPointerEvent::EDrag )
        {
        TInt distanceFromStart( iStartPosition.iY - aPointerEvent.iPosition.iY );
        
        if ( !iPanningActivated && Abs( distanceFromStart ) > DragThreshold() )
            {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            MAknListBoxTfx* tfxApi = CAknListLoader::TfxApi( iTfxGc );

            if ( tfxApi )
                {
                tfxApi->EnableEffects( EFalse );
                }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

            iPanningActivated = ETrue;
            iEmptyAreaClicked = EFalse;        
            
            iHighlightTimer->Cancel();
            iItemToBeFocused = NULL;
            iItemToBeSelected = NULL;
            iIndexToBeFocused = -1;
            iTreeListView->SetPressedDownState( EFalse );
            iPosition = aPointerEvent.iPosition;

            _AKNTRACE(
                "CAknTreeListPhysicsHandler::[%s] Report EEventPanningStarted",
                __FUNCTION__);

			if ( iTreeListView->SingleClickEnabled() )
                {
                iTreeListView->EnableHighlight( EFalse );
                iTreeListView->CancelLongTapDetectorL();
                }

            iTreeListView->ReportTreeListEvent( 
                MAknTreeListObserver::EEventPanningStarted,
                KAknTreeIIDNone );
            }

        if ( iPanningActivated )
            {
            TInt deltaY( iPosition.iY - aPointerEvent.iPosition.iY );
            iPosition = aPointerEvent.iPosition;

            TPoint deltaPoint( 0, deltaY );
            _AKNTRACE(
                "CAknTreeListPhysicsHandler::[%s] Panning deltaPoint.iY = %d",
                __FUNCTION__, deltaY );
            iPhysics->RegisterPanningPosition( deltaPoint );
            }
        else if ( iTreeListView->SingleClickEnabled() )
            {
            iTreeListView->LongTapPointerEventL( aPointerEvent );
            }        
        }

    // EButton1Up   
   
    if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        iTreeListView->SetPressedDownState( EFalse );
        if ( iTreeListView->SingleClickEnabled() && !aMarking )
            {
            iHighlightTimer->Cancel();
            iTreeListView->EnableHighlight( EFalse );
            iTreeListView->LongTapPointerEventL( aPointerEvent );
            }
        iFlags.Set( EFlagButtonUpReceived );
        iTreeListView->DrawDeferred();

        TInt distance = iStartPosition.iY - aPointerEvent.iPosition.iY;
        TPoint drag( 0, distance );

        if ( iPhysics->StartPhysics( drag, iStartTime ) )
            {
            if ( iPanningActivated )
                {
                _AKNTRACE(
                    "CAknTreeListPhysicsHandler::[%s] Report EEventPanningStopped",
                    __FUNCTION__);
                iTreeListView->ReportTreeListEvent( 
                    MAknTreeListObserver::EEventPanningStopped,
                    KAknTreeIIDNone );
                }
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            // Transitions are already suspended if listbox was panned.
            if ( !iPanningActivated )
                {
                MAknListBoxTfx* tfxApi = CAknListLoader::TfxApi( iTfxGc );

                if ( tfxApi )
                    {
                    tfxApi->EnableEffects( EFalse );
                    }
                }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
            
            if ( iPhysics->OngoingPhysicsAction() == CAknPhysics::EAknPhysicsActionFlicking )
                {
                iItemToBeFocused = NULL;
                iItemToBeSelected = NULL;
                iIndexToBeFocused = -1;
                iHighlightTimer->Cancel();
                }
                  
            if ( iItemToBeSelected != NULL )
                {
                iTreeListView->SelectItem( iItemToBeSelected );
                iItemToBeSelected = NULL;
                }     
            _AKNTRACE(
                "CAknTreeListPhysicsHandler::[%s] Report EEventFlickStarted",
                __FUNCTION__);
            iTreeListView->ReportTreeListEvent( 
                MAknTreeListObserver::EEventFlickStarted,
                KAknTreeIIDNone );
            _AKNTRACE_FUNC_EXIT;
            return;
            }

        if ( iPlayFeedbackOnUp )
            {
            // touch down has occured on an item, which requires feedback
            // also on up event -> play basic list feedback
            if ( iFeedback )
                 {
                 TTouchLogicalFeedback fbType = ETouchFeedbackBasicItem;
                 if ( iItemToBeSelected != NULL )
                     {
                     if ( iItemToBeSelected->IsLeaf() && iItemToBeSelected->IsMarkable() )
                         {
                         fbType = ETouchFeedbackCheckbox;
                         }
                     else if ( iItemToBeSelected->Node() != NULL )
                         {
                         if ( iItemToBeSelected->Node()->ChildCount() == 0 && 
                                 iItemToBeSelected->Node()->IsMarkable() )
                             {
                             fbType = ETouchFeedbackCheckbox;
                             }
                         }
                     iFeedback->InstantFeedback( iTreeListView, 
                                                 fbType,
                                                 ETouchFeedbackVibra,
                                                 aPointerEvent );
                     }
                 
                 }
            }

        if ( iItemToBeSelected != NULL && !aMarking)
            {
            iTreeListView->SelectItem( iItemToBeSelected );
            iItemToBeSelected = NULL;
            }

        if ( iItemToBeSelected == NULL && iEmptyAreaClicked )
            {
            if ( iTree->VisibleItemCount() > 0 )
                {
                iTreeListView->ReportTreeListEvent( 
                            MAknTreeListObserver::EEmptyAreaClicked,
                            KAknTreeIIDNone );
                }
            else
                {
                iTreeListView->ReportTreeListEvent( 
                            MAknTreeListObserver::EEmptyListClicked,
                            KAknTreeIIDNone );                
                }
            }       
        }
    
    // Item handling logic    

    TPoint adjustedPosition( aPointerEvent.iPosition );
    adjustedPosition.iY += Offset();

    for ( TInt ii = 0; ii < iItems->Count(); ++ii )
        {
        CAknTreeItem* item = (*iItems)[ii].Item();
    
        if ( item && (*iItems)[ii].Rect().Contains( adjustedPosition ) )
            {        
            if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
                {            
                // Marking mode 
                if ( aMarking )
                    {
                    TBool drawNow = ( item == iTreeListView->FocusedItem() );    
                    if ( aShiftPressed )
                        {
                        iTreeListView->MarkItems( iTreeListView->FocusedItem(), item,
                            !item->IsMarked(), drawNow );
                        }
                    else if ( aCtrlPressed )
                        {
                        iTreeListView->MarkItem( item, !item->IsMarked(), drawNow );
                        }
                    }  
                else if ( iTreeListView->SingleClickEnabled() 
                          && !wasFlicking  )                    
                    {
                    iItemToBeSelected = item;             
                    iTreeListView->SetFocusedItem( item, ii, EFalse );
                    // Start long tap detector 
                    if ( !iTreeListView->HasMarkedItemsL() )
                        {
                        iTreeListView->LongTapPointerEventL( aPointerEvent );
                        }
                    }
                if ( ii != iTreeListView->FocusedItemIndex() )
                    {
                    iItemToBeFocused = item;
                    iIndexToBeFocused = ii;
                    // node will be collapsed/expanded only if flicking was not ongoing
                    if ( item->Node() && !wasFlicking )
                        {
                        iItemToBeSelected = item;
                        // Pressed down highlight to nonfocused item
                        iFlags.Set( EFlagPDHighlightToNonFocusedItem );                            
                        }
                    // touch down on non-focused item, while not flicking
                    if ( iFeedback && !wasFlicking )
                        {
                        if ( item->Node() )
                            {
                            // item is a non-focused node, play basic list
                            // feedback
                            iFeedback->InstantFeedback( iTreeListView, 
                                                        ETouchFeedbackBasicItem );
                            
                            // next up event causes for the node to collapse,
                            // play feedback on up event
                            iPlayFeedbackOnUp = ETrue;
                            }
                        else
                            {
                            // item is a non-focused leaf, play sensitive 
                            // feedback
                            iFeedback->InstantFeedback( iTreeListView, 
                                                        ETouchFeedbackSensitiveItem );
                            }
                        }
                    }
                 // item will be selected only if flicking was not ongoing   
                 else if ( !wasFlicking )
                    {
                    iItemToBeSelected = item;
                    // Pressed down highlight to focused item
                    iFlags.Set( EFlagPDHighlightToFocusedItem );
                    // touch down on focused item, while not flicking
                    if ( iFeedback )
                        {
                        iFeedback->InstantFeedback( iTreeListView,
                                                    ETouchFeedbackBasicItem );
                        
                        // next up event cause an action on the screen,
                        // play feedback on up event
                        iPlayFeedbackOnUp = ETrue;
                        }
                    }
                if ( !aMarking )
                    {
                    // timer will be launched everytime, but not
                    // if flicking was ongoing AND it was stopped by tapping 
                    // to highlighted item or to folder (=node)   
                    if ( !( wasFlicking && iItemToBeSelected != NULL ) )
                        {
                        LaunchHighlightTimer( wasScrolling );
                        }
                    }
                else
                    {
                    // Pressed down highlight or highlight timer 
                    // are not used in marking mode.
                    SetHighlight();   
                    }
                }
            (*iItems)[ii].HandlePointerEventL( aPointerEvent, aViewLevel,
                iTreeListView->Indention(), iTreeListView->IndentionWidth() );
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------------------------
// CAknTreeListPhysicsHandler::HandleScrollEventL
// ---------------------------------------------------------------------------
//
void CAknTreeListPhysicsHandler::HandleScrollEventL( 
    TEikScrollEvent aEventType, const TInt& aThumbPosition )
    {
    switch ( aEventType )
        {
        case EEikScrollUp:
        case EEikScrollDown:
        case EEikScrollPageUp:
        case EEikScrollPageDown:
        case EEikScrollThumbDragVert:
            {
            iScrollIndex = aThumbPosition;
            ScrollView( ETrue );
            }
        // fall through
        default:
            {
            StopPhysics();
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknTreeListPhysicsHandler::HandleKeyEvent
// -----------------------------------------------------------------------------
//
void CAknTreeListPhysicsHandler::HandleKeyEvent( TInt aKeyCode )
    {
   
    if ( aKeyCode != EKeyLeftArrow && aKeyCode != EKeyRightArrow &&
         aKeyCode != EKeyUpArrow && aKeyCode != EKeyDownArrow && 
         aKeyCode != EKeyEnter && aKeyCode != EKeyOK )
        {
        return;
        }  
        
    TInt lastItem = LastVisibleItemIndex();  
    TInt firstItem = FirstVisibleItemIndex();
    TInt focusedItem = iTreeListView->FocusedItemIndex();   
    
    // Offset used in drawing
    TInt panningOffset = Offset();
    // When physics is activated view contains partial items 
    TInt viewOffset(
        iItemHeight * ( lastItem - firstItem + 1 ) - iViewRect.Height() + iListTopOffset );
        
    // Handle list top item  
    if ( panningOffset != 0 && ( firstItem == focusedItem || 
         firstItem == focusedItem + 1 ) )
        {
        iScrollIndex -= panningOffset;
        ScrollView( EFalse );
        }   
    // Handle list bottom item   
    else if ( panningOffset != viewOffset && ( lastItem == focusedItem || 
         lastItem == focusedItem - 1 ) )
        {
        iScrollIndex -= panningOffset - viewOffset;   
        ScrollView( EFalse );
        }                                     
    }
   
// ---------------------------------------------------------------------------
// CAknTreeListPhysicsHandler::SetViewRect
// ---------------------------------------------------------------------------
//
void CAknTreeListPhysicsHandler::SetViewRect( const TRect& aRect )
    {
    iViewRect = aRect;

    // Calculate list top offset
   	TRect firstItemRect( ( *iItems )[ 0 ].Rect() );
	if ( iViewRect.iTl.iY < firstItemRect.iTl.iY )
	    {
	    iListTopOffset = firstItemRect.iTl.iY - iViewRect.iTl.iY;
	    }
    }
    
    
// ---------------------------------------------------------------------------
// CAknTreeListPhysicsHandler::ViewRect
// ---------------------------------------------------------------------------
//
TRect CAknTreeListPhysicsHandler::ViewRect() const
    {
    return iViewRect;
    }


// ---------------------------------------------------------------------------
// CAknTreeListPhysicsHandler::SetItemHeight
// ---------------------------------------------------------------------------
//
void CAknTreeListPhysicsHandler::SetItemHeight( const TInt& aHeight )
    {
    iItemHeight = aHeight;
    }


// ---------------------------------------------------------------------------
// Offset
// ---------------------------------------------------------------------------
//
TInt CAknTreeListPhysicsHandler::Offset() const 
	{
	if ( iItemHeight == 0)
	    {
	    return 0;
	    }
	    
	TInt currentLine = iScrollIndex / iItemHeight;
	    
	if ( currentLine < 0)
        {
        return iScrollIndex % iItemHeight + iItemHeight * currentLine;
        }
    else if ( currentLine >= iTree->VisibleItemCount() )
        {
        return iScrollIndex - ( iItemHeight * ( iTree->VisibleItemCount() - 1 ) );
        }
    return iScrollIndex % iItemHeight;
	}


// ---------------------------------------------------------------------------
// InitPhysicsL
// ---------------------------------------------------------------------------
//   
void CAknTreeListPhysicsHandler::InitPhysicsL()
    {
	TSize totalSize( iViewRect.Width(), WorldHeight() );
	TSize viewSize( iViewRect.Width(), iViewRect.Height() );
	
	iPhysics->InitPhysicsL( totalSize, viewSize, EFalse );
	
	if ( iScrollIndex < 0 )
	    {
	    iScrollIndex = 0;
	    ScrollView( EFalse );
	    }
    }


// ---------------------------------------------------------------------------
// CAknTreeListPhysicsHandler::ResetEventBlockingStatus
// ---------------------------------------------------------------------------
//
void CAknTreeListPhysicsHandler::ResetEventBlockingStatus()
    {
    iEventsBlocked = EFalse;
    iEnableEvents = EFalse;
    }


// ---------------------------------------------------------------------------
// GetVScrollbarParams
// ---------------------------------------------------------------------------
//     
void CAknTreeListPhysicsHandler::GetVScrollbarParams( TInt& aThumbSpan, 
                                                      TInt& aThumbPos, 
                                                      TInt& aScrollSpan )
    {
    aThumbSpan = iViewRect.Height() - iViewRect.Height() % 2;	
    aThumbPos = iScrollIndex;

    TInt span1( aThumbPos + aThumbSpan );
    TInt totalHeight( iTree->VisibleItemCount() * iItemHeight );
    TInt span2( totalHeight - aThumbSpan );
   
    aScrollSpan = Max( Min( span1, span2 ), totalHeight );
    }


// ---------------------------------------------------------------------------
// FocusedItemVisible
// ---------------------------------------------------------------------------
//     
TBool CAknTreeListPhysicsHandler::FocusedItemVisible(
    const TInt& aFocusedIndex ) const
    {
    TBool visible( EFalse );
    if ( aFocusedIndex > -1 && aFocusedIndex < iItems->Count() )
        {
        visible = ETrue;
        TInt topY( ( *iItems )[ aFocusedIndex ].Rect().iTl.iY - Offset() );
        TInt bottomY( ( *iItems )[ aFocusedIndex ].Rect().iBr.iY - Offset() );
        if ( bottomY < iViewRect.iTl.iY || topY > iViewRect.iBr.iY )
            {
            visible = EFalse;
            }
        }
    return visible;
    }


// ---------------------------------------------------------------------------
// FirstVisibleItemIndex
// ---------------------------------------------------------------------------
//     
TInt CAknTreeListPhysicsHandler::FirstVisibleItemIndex() const
    {
    TInt firstItemIndex( -1 );
    if ( iItems->Count() )
        {
        firstItemIndex = 0;
        TBool firstItemFound( EFalse );
        while ( firstItemIndex < iItems->Count() && !firstItemFound )
            {
            TInt bottomY( 
                ( *iItems )[ firstItemIndex ].Rect().iBr.iY - Offset() );
            if ( bottomY < iViewRect.iTl.iY )
                {
                firstItemIndex++;
                }
            else
                {
                firstItemFound = ETrue;
                break;
                }
            }
        if ( !firstItemFound )
            {
            firstItemIndex = 0;
            }
        }
    return firstItemIndex;
    }


// ---------------------------------------------------------------------------
// LastVisibleItemIndex
// ---------------------------------------------------------------------------
//     
TInt CAknTreeListPhysicsHandler::LastVisibleItemIndex() const
    {
    TInt lastItemIndex( -1 );
    if ( iItems->Count() )
        {
        lastItemIndex = iItems->Count() - 1;
        TBool lastItemFound( EFalse );
        while ( lastItemIndex > -1 && !lastItemFound )
            {
            TInt topY( ( *iItems )[ lastItemIndex ].Rect().iTl.iY - Offset() );
            if ( topY > iViewRect.iBr.iY )
                {
                lastItemIndex--;
                }
            else
                {
                lastItemFound = ETrue;
                break;
                }
            }
        }
    return lastItemIndex;
    }


// ---------------------------------------------------------------------------
// UpdateScrollIndex
// ---------------------------------------------------------------------------
//     
void CAknTreeListPhysicsHandler::UpdateScrollIndex( const TBool& aScrollTop )
    {
    // Do nothing if handler itself is updating the view
    if ( iFlags.IsSet( EFlagUpdatingView ) )
        {
        return;
        }
        
    TInt first( 0 );
    TInt scrollOffset( 0 );
    TInt previousScrollIndex( iScrollIndex );

    // Check that scroll index is within worldSizeLimit
    TInt worldSizeLimit( WorldHeight() - iViewRect.Height() );
    if ( worldSizeLimit < iScrollIndex && worldSizeLimit > 0 )
        {
        iScrollIndex = worldSizeLimit;
        }
        
    // Adjusting scroll index according to first visible item
    if ( aScrollTop )
        {
        first = FirstVisibleItemIndex();
        }

    // Adjusting scroll index according to last visible item
    else
        {
        scrollOffset = iViewRect.Height();
        first = iItems->Count() - 1;
        while ( scrollOffset > iItemHeight && first >= 0 )
            {
            scrollOffset -= iItemHeight;
            first--;
            }
        }

    if ( first >= 0 && first < iItems->Count() )
        {
        // First visible item index of the whole item list
        TInt topIndex( iTree->VisibleItemIndex( (*iItems)[ first ].Item() ) );
        TInt currentIndex( iScrollIndex / iItemHeight );
        
        // Scrollindex needs updating
        if ( topIndex != currentIndex || scrollOffset != 0 )
            {
            iScrollIndex = topIndex * iItemHeight + scrollOffset;
            
            // Check that scroll index is within boundaries.
            if ( iScrollIndex < 0 )
                {
                iScrollIndex = 0;
                }
            else if ( iScrollIndex > worldSizeLimit )
                {
                if ( worldSizeLimit < 0 ) 
                    {
                    // if worldSizeLimit<0, means the world height is less than view rect, no scroll needed,
                    // it is safe to set iScrollIndex to 0
                    iScrollIndex = 0;
                    }
                else
                    {
                    iScrollIndex = worldSizeLimit;
                    }
                }

            // Update view if needed
            if ( previousScrollIndex != iScrollIndex )
                {
                ScrollView( EFalse );                
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// ViewPositionChanged
// ---------------------------------------------------------------------------
//
void CAknTreeListPhysicsHandler::ViewPositionChanged(
    const TPoint& aNewPosition,
    TBool aDrawNow,
    TUint /*aFlags*/ )
    {
    iScrollIndex = aNewPosition.iY - iViewRect.Height() / 2;
    TTouchFeedbackType feedbackType = ETouchFeedbackVibra;
    if ( iPhysics->OngoingPhysicsAction() 
        == CAknPhysics::EAknPhysicsActionDragging )
        {
        feedbackType = static_cast<TTouchFeedbackType>(ETouchFeedbackAudio | ETouchFeedbackVibra);
        }
    if ( iPhysics->OngoingPhysicsAction() 
            == CAknPhysics::EAknPhysicsActionBouncing )
        {
        iEventsBlocked = ETrue;
        iEnableEvents = EFalse;
        }
    else
        {
        ResetEventBlockingStatus();
        }

    TInt viewBottom = aNewPosition.iY + iViewRect.Height() - iViewRect.Height() / 2;
    if ( iPenDown )
        {
        iPenDown = EFalse;
        if ( iScrollIndex <= iListTopOffset - iItemHeight )
            {
            iOldTopItem = -1;
            }
        else
            {
            iOldTopItem = ( iScrollIndex - iListTopOffset ) / iItemHeight;
            if ( iOldTopItem >= iTree->VisibleItemCount() )
                {
                iOldTopItem = iTree->VisibleItemCount();
                }
            }
        
        if ( viewBottom < iListTopOffset )
            {
            iOldBottomItem = -1;
            }
        else
            {
            iOldBottomItem = ( viewBottom - iListTopOffset ) / iItemHeight;
            if ( iOldBottomItem >= iTree->VisibleItemCount() )
                {
                iOldBottomItem = iTree->VisibleItemCount();
                }
            }
        }
    else
        {
        TInt bottomItem, upperItem;
        if ( iScrollIndex <= iListTopOffset - iItemHeight )
            {
            upperItem = -1;
            }
        else
            {
            upperItem = ( iScrollIndex - iListTopOffset ) / iItemHeight;
            if ( upperItem >= iTree->VisibleItemCount() )
                {
                upperItem = iTree->VisibleItemCount();
                }
            }
        if ( viewBottom < iListTopOffset )
            {
            bottomItem = -1;
            }
        else
            {
            bottomItem = ( viewBottom - iListTopOffset ) / iItemHeight;
            if ( bottomItem >= iTree->VisibleItemCount() )
                {
                bottomItem = iTree->VisibleItemCount();
                }
            }
        if ( upperItem == -1 )
            {
            if ( bottomItem != iOldBottomItem )
                {
                if ( bottomItem != iTree->VisibleItemCount() - 1 )
                    iFeedback->InstantFeedback( iTreeListView,
                                                ETouchFeedbackSensitiveItem,
                                                feedbackType,
                                                TPointerEvent() );
                }
            }
        else if ( bottomItem == iTree->VisibleItemCount() )
            {
            if ( upperItem != iOldTopItem )
                {
                iFeedback->InstantFeedback( iTreeListView,
                                            ETouchFeedbackSensitiveItem,
                                            feedbackType,
                                            TPointerEvent() );
                }
            }
        else if ( upperItem >= 0 || bottomItem < iTree->VisibleItemCount() )
            {
            if ( upperItem < iOldTopItem || bottomItem > iOldBottomItem )
                {
                iFeedback->InstantFeedback( iTreeListView,
                                            ETouchFeedbackSensitiveItem,
                                            feedbackType,
                                            TPointerEvent() );
                }
            }
            iOldTopItem = upperItem;
            iOldBottomItem = bottomItem;
        }
    ScrollView( aDrawNow );
    }
    
    
// ---------------------------------------------------------------------------
// PhysicEmulationEnded
// ---------------------------------------------------------------------------
//    
void CAknTreeListPhysicsHandler::PhysicEmulationEnded()
    {
    iEnableEvents = ETrue;
    _AKNTRACE("CAknTreeListPhysicsHandler::%s Report EEventFlickStopped",
              __FUNCTION__);
    iTreeListView->ReportTreeListEvent( 
        MAknTreeListObserver::EEventFlickStopped, 
        KAknTreeIIDNone );
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfx* tfxApi = CAknListLoader::TfxApi( iTfxGc );

    if ( tfxApi )
        {
        tfxApi->EnableEffects( ETrue );
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
    }



// ---------------------------------------------------------------------------
// CAknTreeListPhysicsHandler::ViewPosition
// ---------------------------------------------------------------------------
//    
TPoint CAknTreeListPhysicsHandler::ViewPosition() const
    {
    TPoint viewPosition( iViewRect.Width() / 2, 
                         iScrollIndex + iViewRect.Height() / 2 ); 
    return viewPosition;
    }


// ---------------------------------------------------------------------------
// CAknTreeListPhysicsHandler::SetGc
// ---------------------------------------------------------------------------
//    
void CAknTreeListPhysicsHandler::SetGc( CWindowGc* aGc )
    {
    iTfxGc = aGc;
    }


// ---------------------------------------------------------------------------
// CAknTreeListPhysicsHandler::CAknTreeListPhysicsHandler
// ---------------------------------------------------------------------------
//
CAknTreeListPhysicsHandler::CAknTreeListPhysicsHandler( 
    CAknTreeListView* aTreeListView,
    CAknTree* aTree,
    RArray<TAknTreeListViewItem>* aItems )
    :
    iPhysics( NULL ),
    iHighlightTimer( NULL ),
    iTree( aTree ),
    iTreeListView( aTreeListView ),
    iItems( aItems ), 
    iPlayFeedbackOnUp( EFalse )
    {
    }


// ---------------------------------------------------------------------------
// CAknTreeListPhysicsHandler::ConstructL
// ---------------------------------------------------------------------------
//
void CAknTreeListPhysicsHandler::ConstructL()
    {
    iPhysics = CAknPhysics::NewL( *this, iTreeListView );
    iHighlightTimer = CPeriodic::NewL( CActive::EPriorityStandard );
    iFeedback = MTouchFeedback::Instance();
    }


// ---------------------------------------------------------------------------
// DragThreshold
// ---------------------------------------------------------------------------
//     
TInt CAknTreeListPhysicsHandler::DragThreshold()
    {
    return iPhysics->DragThreshold();
    }


// ---------------------------------------------------------------------------
// LaunchHighlightTimer
// ---------------------------------------------------------------------------
//
void CAknTreeListPhysicsHandler::LaunchHighlightTimer( TBool aWasScrolling )
    {
    if ( !aWasScrolling )
        {
        HighlightTimerCallback( this );
        CCoeEnv::Static()->WsSession().Finish();
        }
    else
        {
        TInt highlightTimeout = iPhysics->HighlightTimeout() * 1000;

        iHighlightTimer->Start( 
            TTimeIntervalMicroSeconds32( highlightTimeout ),
            TTimeIntervalMicroSeconds32( highlightTimeout ), 
            TCallBack( HighlightTimerCallback, this ) );
        }
    }


// ---------------------------------------------------------------------------
// HighlightTimerCallback
// ---------------------------------------------------------------------------
//     
TInt CAknTreeListPhysicsHandler::HighlightTimerCallback( TAny* aPtr )
    {
    CAknTreeListPhysicsHandler* handler = 
        static_cast<CAknTreeListPhysicsHandler*>( aPtr );
    if ( handler && handler->iTreeListView )
        {
        if ( handler->iTreeListView->SingleClickEnabled() 
             && !handler->iEnableEvents )
            {
            handler->iTreeListView->EnableHighlight(ETrue);
            }
        // Pressed down highlight if item still pressed down
        if ( !handler->iFlags.IsSet( EFlagButtonUpReceived )
            && handler->iFlags.IsSet( EFlagPDHighlightToFocusedItem ) )
            {
            handler->iTreeListView->SetPressedDownState( ETrue );
            handler->iTreeListView->DrawNow();
            }
        else 
            {
            // Pressed down highlight if item still pressed down
            if ( !handler->iFlags.IsSet( EFlagButtonUpReceived ) 
                && handler->iFlags.IsSet( EFlagPDHighlightToNonFocusedItem ) )
                {
                handler->iTreeListView->SetPressedDownState( ETrue );
                }
            handler->SetHighlight();
            }
        handler->iFlags.Clear( EFlagPDHighlightToFocusedItem );
        handler->iFlags.Clear( EFlagPDHighlightToNonFocusedItem );
        }
    return NULL;
    }


// ---------------------------------------------------------------------------
// SetHighlight
// ---------------------------------------------------------------------------
//     
void CAknTreeListPhysicsHandler::SetHighlight()
    {
    iHighlightTimer->Cancel();
    if ( iItemToBeFocused )
        {
        iTreeListView->SetHighlight( iItemToBeFocused, iIndexToBeFocused );
        iItemToBeFocused = NULL;
        }
    }


// ---------------------------------------------------------------------------
// ScrollView
// ---------------------------------------------------------------------------
//     
void CAknTreeListPhysicsHandler::ScrollView( TBool aDrawNow )
    {
    iFlags.Set( EFlagUpdatingView );
    if ( iPreviousIndex != iScrollIndex )
        {
        iPreviousIndex = iScrollIndex;
        TInt currentLine = iScrollIndex / iItemHeight;           
      
        TInt line = currentLine;            
        if ( currentLine < 0 )
            {
            line = 0;
            }
        else if ( currentLine >= iTree->VisibleItemCount() )
            {
            line = iTree->VisibleItemCount() - 1;
            }

        iTreeListView->UpdateTreeListView( line, aDrawNow );
        }
    iFlags.Clear( EFlagUpdatingView );
    }


// ---------------------------------------------------------------------------
// CAknTreeListPhysicsHandler::StopPhysics
// ---------------------------------------------------------------------------
//
void CAknTreeListPhysicsHandler::StopPhysics()
    {
    iPhysics->StopPhysics();
    iPhysics->ResetFriction();
    }


// ---------------------------------------------------------------------------
// CAknTreeListPhysicsHandler::WorldHeight
// ---------------------------------------------------------------------------
//
TInt CAknTreeListPhysicsHandler::WorldHeight()
    {
   	return iTree->VisibleItemCount() * iItemHeight + iListTopOffset;
    }


// ---------------------------------------------------------------------------
// CAknTreeListPhysicsHandler::EmptyAreaClicked
// ---------------------------------------------------------------------------
//
TBool CAknTreeListPhysicsHandler::EmptyAreaClicked( TPoint aPosition )
    { 
    if ( aPosition.iY <= WorldHeight() )
        {
        return EFalse;
        }
    return ETrue;
    }


