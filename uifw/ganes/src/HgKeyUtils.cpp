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

#include "HgKeyUtils.h"
#include "HgConstants.h"
#include <ganes/HgScroller.h>
#include <ganes/HgItem.h>

#include <w32std.h>
#include <eikbtgpc.h>
#include <eikcba.h>
#include <avkon.rsg>
#include <avkon.hrh>
#include <AknUtils.h>

// -----------------------------------------------------------------------------
// CHgKeyUtils::NewL()
// -----------------------------------------------------------------------------
//
CHgKeyUtils* CHgKeyUtils::NewL( CHgScroller& aScroller )
    {
    CHgKeyUtils* self = new (ELeave) CHgKeyUtils( aScroller );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// -----------------------------------------------------------------------------
// CHgKeyUtils::CHgKeyUtils()
// -----------------------------------------------------------------------------
//
CHgKeyUtils::~CHgKeyUtils()
    {
    RemoveMSKObserver();
    // Stop listening CenRep.
    if (iCenRepNotifyHandler)
        {
        iCenRepNotifyHandler->StopListening();
        }
    delete iCenRepNotifyHandler;
    delete iCenRep; 
    }

// -----------------------------------------------------------------------------
// CHgKeyUtils::HandleNotifyInt()
// -----------------------------------------------------------------------------
//
void CHgKeyUtils::HandleNotifyInt(TUint32 aId, TInt aNewValue)
    {
    if (aId == KAknFepHashKeySelection)
         {
         iAknFepHashKeySelection = (TBool)aNewValue;
         }    
    }
    
// -----------------------------------------------------------------------------
// CHgKeyUtils::CHgKeyUtils()
// -----------------------------------------------------------------------------
//
CHgKeyUtils::CHgKeyUtils( CHgScroller& aScroller ):
    iScroller( aScroller )
    {
    
    }
    
// -----------------------------------------------------------------------------
// CHgKeyUtils::ConstructL()
// -----------------------------------------------------------------------------
//
void CHgKeyUtils::ConstructL()
    {
    iMskEnabledInPlatform = AknLayoutUtils::MSKEnabled();        

    // Start listening a CenRep key indicating whether hash key selection is active.
    TRAPD(err, iCenRep = CRepository::NewL(KCRUidAknFep));
    if (err == KErrNone)
        {
        iCenRepNotifyHandler = CCenRepNotifyHandler::NewL(*this,
            *iCenRep,
            CCenRepNotifyHandler::EIntKey,
            KAknFepHashKeySelection);

        iCenRepNotifyHandler->StartListeningL();
        iCenRep->Get(KAknFepHashKeySelection, iAknFepHashKeySelection);
        } 
    }

// -----------------------------------------------------------------------------
// CHgKeyUtils::SelectionMode()
// -----------------------------------------------------------------------------
//
TBool CHgKeyUtils::SelectionMode( const TKeyEvent& aKeyEvent )
    {
    return (iAknFepHashKeySelection && aKeyEvent.iScanCode == EStdKeyHash) ||
        aKeyEvent.iScanCode == EStdKeyLeftShift ||
        aKeyEvent.iScanCode == EStdKeyRightShift ||
        aKeyEvent.iScanCode == EStdKeyLeftCtrl ||
        aKeyEvent.iScanCode == EStdKeyRightCtrl;
    }

// -----------------------------------------------------------------------------
// CHgKeyUtils::ProcessCommandL()
// -----------------------------------------------------------------------------
//
void CHgKeyUtils::ProcessCommandL(TInt aCommandId)
    {
    if( !iMskEnabledInPlatform )
        return;

    switch ( aCommandId )
        {
        case EAknSoftkeyShiftMSK:
            {
            const TInt selectedIndex = iScroller.SelectedIndex();
            if ( selectedIndex != KErrNotFound ) 
                {
                if( iScroller.ItemL( selectedIndex ).Flags() & CHgItem::EHgItemFlagMarked )
                    {
                    iScroller.UnMark(selectedIndex);
                    iScroller.SetSelectionMode( CHgScroller::ESelectionUnMark );
                    }
                else 
                    {
                    iScroller.Mark(selectedIndex);
                    iScroller.SetSelectionMode( CHgScroller::ESelectionMark );
                    }
                }
            }
            break;
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CHgKeyUtils::CreateMSKObserverL()
// -----------------------------------------------------------------------------
//
void CHgKeyUtils::CreateMSKObserver()
    {
    if( !iMskEnabledInPlatform )
        return;

    RemoveMSKObserver();
    
    UpdateMSKVars();
    
    if( !iCba )
        return;

    iCba->SetMSKCommandObserver(this);
    iMSKButtonGroupAlive = ETrue;
    }

// -----------------------------------------------------------------------------
// CHgKeyUtils::RemoveMSKObserver()
// -----------------------------------------------------------------------------
//
void CHgKeyUtils::RemoveMSKObserver()
    {
    if( !iMSKButtonGroupAlive || !iMskEnabledInPlatform )
        return;
    
    UpdateMSKVars();
    
    if( !iCba )
        return;
    
    iCba->SetMSKCommandObserver(NULL);
    iMSKButtonGroupAlive = EFalse;
    }

// -----------------------------------------------------------------------------
// CHgKeyUtils::UpdateMSKVars()
// -----------------------------------------------------------------------------
//
void CHgKeyUtils::UpdateMSKVars()
    {
    if( !iMskEnabledInPlatform )
        return;

    CEikButtonGroupContainer* bgc;
    iCba = NULL;
    
    iScroller.MopGetObject( bgc );
    if ( bgc )
        {
        iCba = ( static_cast<CEikCba*>( bgc->ButtonGroup() ) ); // downcast from MEikButtonGroup
        }    
    }

// -----------------------------------------------------------------------------
// CHgKeyUtils::OfferKeyEventL()
// -----------------------------------------------------------------------------
//
TKeyResponse CHgKeyUtils::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
    {    
    TKeyResponse response = EKeyWasNotConsumed;
    
    // if we have markable list and either shift, ctrl or hash is long pressed
    // down, we will enter selection (marking) mode, where MSK is Mark/Unmark
    if( SelectionMode( aKeyEvent ) )
        {
        if( aType == EEventKeyDown )
            {
            iShiftKeyPressed = ETrue;
            iScroller.SetSelectionMode( CHgScroller::ESelectionPossible );
            }
        else if( aType == EEventKeyUp )
            {
            iShiftKeyPressed = EFalse;
            iScroller.SetSelectionMode( CHgScroller::ENoSelection );
            }
        response = EKeyWasConsumed;
        }
    
    const TInt selectedIndex = iScroller.SelectedIndex();
    if( iShiftKeyPressed 
            && aType == EEventKey 
            && selectedIndex != KErrNotFound
            && iScroller.SelectionMode() != CHgScroller::ENoSelection )
        {
        TBool itemMarked = iScroller.ItemL( selectedIndex ).Flags() & CHgItem::EHgItemFlagMarked; 

        if( (iAknFepHashKeySelection && aKeyEvent.iScanCode == EStdKeyHash) ||
                aKeyEvent.iScanCode == EStdKeyEnter )
            {
            if( itemMarked )
                {
                iScroller.UnMark(selectedIndex);
                // Change also the selection mode. After this arrow keys
                // can be used to unmark items.
                iScroller.SetSelectionMode( CHgScroller::ESelectionUnMark );
                }
            else 
                {
                iScroller.Mark(selectedIndex);
                // Change also the selection mode. After this arrow keys
                // can be used to mark items.
                iScroller.SetSelectionMode( CHgScroller::ESelectionMark );
                }
            response = EKeyWasConsumed;
            iScroller.RefreshScreen(selectedIndex);
            }
        else if (iScroller.SelectionMode() == CHgScroller::ESelectionPossible)
            {
            if(itemMarked)
                {
                iScroller.SetSelectionMode( CHgScroller::ESelectionUnMark );
                }
            else
                {
                iScroller.SetSelectionMode( CHgScroller::ESelectionMark );
                }            
            }
        }
    
    return response;
    }

// -----------------------------------------------------------------------------
// CHgKeyUtils::HandleLosingForeground()
// -----------------------------------------------------------------------------
//
void CHgKeyUtils::HandleLosingFocus()
    {
    // switch off selection (marking) mode when we lose focus
    iShiftKeyPressed = EFalse;
    iSelectionModeEnabled = EFalse;
    iScroller.SetSelectionMode( CHgScroller::ENoSelection );
    RemoveMSKObserver();    
    }

// -----------------------------------------------------------------------------
// CHgKeyUtils::HandleGainingForeground()
// -----------------------------------------------------------------------------
//
void CHgKeyUtils::HandleGainingFocus()
    {
    CreateMSKObserver();
    }

// End of file
