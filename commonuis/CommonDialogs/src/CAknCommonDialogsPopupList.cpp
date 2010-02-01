/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/


#include <eikbtgpc.h>   // CEikButtonGroupContainer
#include <eiklbv.h>
#include <aknenv.h>
#include <aknPopupHeadingPane.h>
#include <eiklabel.h>
#include <avkon.rsg>

#include <AknTasHook.h> // for testability hooks
#include "CAknCommonDialogsPopupList.h"
#include "MAknCommonDialogsEventObserver.h"
#include "CAknCommonDialogsBase.h"  // TReturnKey

#include <eiklbi.h>

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknCommonDialogsPopupList::CAknCommonDialogsPopupList
//
//
// -----------------------------------------------------------------------------
//
CAknCommonDialogsPopupList::CAknCommonDialogsPopupList(
    MAknCommonDialogsEventObserver& aObserver, TBool& aIsEndKeyPress  )
    :   iObserver( aObserver ), iEndKey( aIsEndKeyPress )
    {
    }

// -----------------------------------------------------------------------------
// CAknCommonDialogsPopupList::ConstructL
//
// -----------------------------------------------------------------------------
//
void CAknCommonDialogsPopupList::ConstructL(
    CEikListBox* aListBox,
    AknPopupLayouts::TAknPopupLayouts aType )
    {
    CAknPopupList::ConstructL( aListBox, R_AVKON_SOFTKEYS_OK_CANCEL__OK, aType );
    }

// -----------------------------------------------------------------------------
// CAknCommonDialogsPopupList::NewL
//
// -----------------------------------------------------------------------------
//
CAknCommonDialogsPopupList* CAknCommonDialogsPopupList::NewL(
    MAknCommonDialogsEventObserver& aObserver,
    CEikListBox* aListBox,
    AknPopupLayouts::TAknPopupLayouts aType,
    TBool& aIsEndKeyPress )
    {
    CAknCommonDialogsPopupList* self = new( ELeave )
        CAknCommonDialogsPopupList( aObserver, aIsEndKeyPress );
    CleanupStack::PushL( self );
    self->ConstructL( aListBox, aType );
    CleanupStack::Pop();
    AKNTASHOOK_ADDL( self, "CAknCommonDialogsPopupList" );
    return self;
    }

// Destructor
CAknCommonDialogsPopupList::~CAknCommonDialogsPopupList()
    {
    AKNTASHOOK_REMOVE();
    }


// -----------------------------------------------------------------------------
// CAknCommonDialogsPopupList::ProcessCommandL
//
//
// -----------------------------------------------------------------------------
//
void CAknCommonDialogsPopupList::ProcessCommandL( TInt aCommandId )
    {
    switch( aCommandId )
        {
        // Fall through: All softkeys which can be received from the popup list
        case EAknSoftkeyOk:
        case EAknSoftkeyCancel:
        case EAknSoftkeyBack:
            {
            MAknCommonDialogsEventObserver::TEvent event(
                aCommandId == EAknSoftkeyOk?
                MAknCommonDialogsEventObserver::ELeftSoftkeyPress :
                MAknCommonDialogsEventObserver::ERightSoftkeyPress );

            if( !ReportPopupEventL( event ) )
                {
                // Returned false, do not allow exit from popup, return
                return;
                }

            break;
            }

        default:
            {
            break;
            }

        }
    CAknPopupList::ProcessCommandL( aCommandId );
    }

// -----------------------------------------------------------------------------
// CAknCommonDialogsPopupList::OfferKeyEventL
//
//
// -----------------------------------------------------------------------------
//
TKeyResponse CAknCommonDialogsPopupList::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    if( aType == EEventKey )
        {

        switch( aKeyEvent.iCode )
            {
            case EKeyUpArrow:
            case EKeyDownArrow:
                {
                // Get current item index
                TInt oldIndex( iListBox->CurrentItemIndex() );
                // Call OfferKeyEventL
                TKeyResponse response(
                    iListBox->OfferKeyEventL( aKeyEvent, aType ) );
                // Get new item index
                TInt newIndex( iListBox->CurrentItemIndex() );
                // Compare new and old index
                if( oldIndex != newIndex )
                    {
                    // Notify focus change only if focus actually changes
                    // Top item index value is zero because there is no need to
                    // know what it is in focus change.
                    oldIndex = 0;
                    iObserver.HandleEventL( MAknCommonDialogsEventObserver::EFocusChange,
                        newIndex, oldIndex, iPopoutCba );
                    }
                return response;
                // No break needed after return
                }

            case EKeyOK:
                {
                if( !ReportPopupEventL( MAknCommonDialogsEventObserver::ESelectionKeyPress ) )
                    {
                    // Returned false, do not allow exit from popup.
                    return EKeyWasConsumed;
                    }
                break;
                }

            case EKeyEscape:
                {
                TInt oldFocus( 0 );
                TInt oldTopIndex( 0 );
                MAknCommonDialogsEventObserver::TAction action(
                    iObserver.HandleEventL( MAknCommonDialogsEventObserver::ECancelAllActions, 
                        oldFocus, oldTopIndex, iPopoutCba ) );
                if ( action == MAknCommonDialogsEventObserver::EDidNothing || 
                       action == MAknCommonDialogsEventObserver::ETryingToExit )
                    {
                    iEndKey = ETrue;
                    MakeVisible( EFalse );
                    AttemptExitL( EFalse );
                    }
                return EKeyWasConsumed;
                // No break needed after return
                }

            default:
                {
                break;
                }

            }
        }
    return iListBox->OfferKeyEventL( aKeyEvent, aType );
    }

// -----------------------------------------------------------------------------
// CAknCommonDialogsPopupList::ReportPopupEventL
//
//
// -----------------------------------------------------------------------------
//
TBool CAknCommonDialogsPopupList::ReportPopupEventL(
    MAknCommonDialogsEventObserver::TEvent aEvent )
    {
    // Get current indices in listbox.
    const TInt oldFocus( iListBox->CurrentItemIndex() );
    const TInt oldTopIndex( iListBox->View()->TopItemIndex() );
    // Create variables for new indices.
    TInt newFocus( oldFocus );
    TInt newTopIndex( oldTopIndex );

    // Report the event to event handler
    MAknCommonDialogsEventObserver::TAction action(
        iObserver.HandleEventL( aEvent, newFocus, newTopIndex, iPopoutCba ) );

    // Do what the event handler says.
    switch( action )
        {
        case MAknCommonDialogsEventObserver::EDidNothing:
            {
            return EFalse;
            }
        case MAknCommonDialogsEventObserver::EItemsUpdated:
            {
            UpdateItemsAndRedrawPopupL( newFocus, newTopIndex );
            return EFalse;
            }
        case MAknCommonDialogsEventObserver::ELaunchEmptyPopup:
            {
            MakeVisible( EFalse );
            // Trap empty popup launching in order to set popup visible again.
            TPtr promptText = iTitle->PromptText();
            TRAPD( error,
                iAvkonEnv->ExecuteEmptyPopupListL(
                NULL, &promptText, R_AVKON_SOFTKEYS_OK_BACK ) );
            MakeVisible( ETrue );
            User::LeaveIfError( error );
            return EFalse;
            }
        case MAknCommonDialogsEventObserver::ECanceled:
            {
            AttemptExitL(EFalse);
            return EFalse;
            }
        default:
            {
            break;
            }
        }
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CAknCommonDialogsPopupList::UpdateItemsAndRedrawPopupL
//
//
// -----------------------------------------------------------------------------
//
void CAknCommonDialogsPopupList::UpdateItemsAndRedrawPopupL( TInt aFocus, TInt aTopIndex )
    {
    iListBox->Reset();
    iListBox->HandleItemRemovalL();
    
    // If indices have been defined, set then after reset
    CListBoxView* view = iListBox->View();
    if( aFocus >= 0 )
        {
        view->SetCurrentItemIndex( aFocus );
        
        if( aTopIndex >= 0 )
            {
            view->SetTopItemIndex( aTopIndex );
            }
        }
    // Report focus change event
    iObserver.HandleEventL(
        MAknCommonDialogsEventObserver::EFocusChange, aFocus, aTopIndex, iPopoutCba );

    // Change window size and update screen
    MakeVisible( EFalse );
    SetupWindowLayout( iWindowType );
    ( (RWindow*)DrawableWindow() )->ClearRedrawStore();
    MakeVisible( ETrue );
    DrawNow();
    }

// -----------------------------------------------------------------------------
// CAknCommonDialogsPopupList::HandleListBoxEventL
// Override CAknPopupList's HandleListBoxEventL function
// Processes key & point (for S60 4.0) events from the listbox.
// -----------------------------------------------------------------------------
//
void CAknCommonDialogsPopupList::HandleListBoxEventL(CEikListBox* aListBox,
        TListBoxEvent aEventType)
    {
    // Respond to events from listbox
    if (aListBox == iListBox)
        {
        // if left softkey is empty, we do not handle enter key either.
        if (iPopoutCba && iPopoutCba->ButtonGroup())
            if (iPopoutCba->ButtonGroup()->CommandId( 0 ) != 0) // CommandId(0) is left softkey.
                {
                if ( ( aEventType == MEikListBoxObserver::EEventEnterKeyPressed )
                    || ( aEventType == MEikListBoxObserver::EEventItemDoubleClicked )
                    || ( aEventType == MEikListBoxObserver::EEventItemClicked )
                    || ( aEventType == MEikListBoxObserver::EEventPanningStopped)
                    || ( aEventType == MEikListBoxObserver::EEventFlickStopped )
                    || ( aEventType == MEikListBoxObserver::EEventItemSingleClicked )
                    && AknLayoutUtils::PenEnabled() )
                    {
                    MAknCommonDialogsEventObserver::TEvent event;
                    
                    if( aEventType == MEikListBoxObserver::EEventItemDoubleClicked 
                    || aEventType == MEikListBoxObserver::EEventItemSingleClicked
                    )
                        {
                        event = MAknCommonDialogsEventObserver::EEventClicked;
                        iListBox->View()->ItemDrawer()->ClearFlags( CListItemDrawer::EPressedDownState );
                        }
                    else if ( aEventType == MEikListBoxObserver::EEventItemClicked 
                           || aEventType == MEikListBoxObserver::EEventPanningStopped 
                           || aEventType == MEikListBoxObserver::EEventFlickStopped )
                        {
                        event = MAknCommonDialogsEventObserver::EFocusChange;
                        }
                    else
                        event = MAknCommonDialogsEventObserver::ESelectionKeyPress;
                    
                    if ( !ReportPopupEventL( event ) )
                        {
                        return;
                        }
                    AttemptExitL(ETrue);
                    }
                }
        }
    }
    
// -----------------------------------------------------------------------------
// CAknCommonDialogsPopupList::HandlePointerEventL
// -----------------------------------------------------------------------------
//

void CAknCommonDialogsPopupList::HandlePointerEventL( const TPointerEvent& aPointerEvent )
	{
	if( AknLayoutUtils::PenEnabled() )
        { 
        TInt oldHighlight = iListBox->CurrentItemIndex();
        
        CCoeControl::HandlePointerEventL( aPointerEvent );
        
        if ( oldHighlight != iListBox->CurrentItemIndex() )
            {
            HandleListBoxHighlightChangedL( iListBox );
            }
        }
	}


// -----------------------------------------------------------------------------
// CAknCommonDialogsPopupList::NotifyDrivesChangedL
//
//
// -----------------------------------------------------------------------------
//
void CAknCommonDialogsPopupList::NotifyDrivesChangedL(
    const MDesCArray* aItemArray )
    {
    TInt focus = iListBox->CurrentItemIndex();
    TInt topIndex = iListBox->View()->TopItemIndex();
    if ( focus < 0 )
        {
        focus = aItemArray->MdcaCount() - 1;
        }
    UpdateItemsAndRedrawPopupL( focus, topIndex );
    }

// -----------------------------------------------------------------------------
// CAknCommonDialogsPopupList::HandleListBoxHighlightChangedL
//
//
// -----------------------------------------------------------------------------
//
void CAknCommonDialogsPopupList::HandleListBoxHighlightChangedL( CEikListBox* aListBox )
    {
    TInt oldFocus( aListBox->CurrentItemIndex() );
    TInt oldTopIndex( aListBox->View()->TopItemIndex() );
    // Report focus change event
    iObserver.HandleEventL(
        MAknCommonDialogsEventObserver::EFocusChange, oldFocus, oldTopIndex, iPopoutCba );
    }

//  End of File
