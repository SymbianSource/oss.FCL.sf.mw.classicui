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


// INCLUDES
#include "CAknCommonDialogsRadioButtonSettingPage.h"
#include "MAknCommonDialogsEventObserver.h"
#include "CAknMemorySelectionDialog.h"
#include "CAknMemorySelectionModel.h"

#include <AknTasHook.h> // for testability hooks
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknCommonDialogsRadioButtonSettingPage::CAknCommonDialogsRadioButtonSettingPage
//
//
// -----------------------------------------------------------------------------
//
CAknCommonDialogsRadioButtonSettingPage::CAknCommonDialogsRadioButtonSettingPage(
    TInt aResourceId,
    TInt& aCurrentSelectionItem,
    const MDesCArray* aItemArray,
    MAknCommonDialogsEventObserver& aObserver, 
    CAknMemorySelectionModel* aModel )
    :   CAknRadioButtonSettingPage( aResourceId, aCurrentSelectionItem, aItemArray ),
        iObserver( aObserver ), iModel( aModel )
    {
    AKNTASHOOK_ADD( this, "CAknCommonDialogsRadioButtonSettingPage" );
    }

// Destructor
CAknCommonDialogsRadioButtonSettingPage::~CAknCommonDialogsRadioButtonSettingPage()
    {
    AKNTASHOOK_REMOVE();
    }


// -----------------------------------------------------------------------------
// CAknCommonDialogsRadioButtonSettingPage::Cba
//
//
// -----------------------------------------------------------------------------
//
CEikButtonGroupContainer* CAknCommonDialogsRadioButtonSettingPage::Cba() const
    {
    return CAknSettingPage::Cba();
    }

// -----------------------------------------------------------------------------
// CAknCommonDialogsRadioButtonSettingPage::OkToExitL
//
//
// -----------------------------------------------------------------------------
//
TBool CAknCommonDialogsRadioButtonSettingPage::OkToExitL( TBool aAccept )
    {
    // If user accepts a selection
    if( aAccept )
        {
        CAknSetStyleListBox* lb = ListBoxControl();
        TInt focus( lb->CurrentItemIndex() );
        TInt topIndex( lb->TopItemIndex() );
        if( iObserver.HandleEventL(
            MAknCommonDialogsEventObserver::ELeftSoftkeyPress, focus, topIndex, NULL )
            != MAknCommonDialogsEventObserver::ETryingToExit )
            {
            return EFalse;
            }
        else
            {
            UpdateAndRedrawItemL();
            }
       
        }
    return CAknRadioButtonSettingPage::OkToExitL( aAccept );
    }

// -----------------------------------------------------------------------------
// CAknCommonDialogsRadioButtonSettingPage::OfferKeyEventL
//
//
// -----------------------------------------------------------------------------
//
TKeyResponse CAknCommonDialogsRadioButtonSettingPage::OfferKeyEventL(
        const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    if( aType == EEventKey )
        {
        CAknSetStyleListBox* lb = ListBoxControl();
        switch( aKeyEvent.iCode )
            {
            case EKeyUpArrow:
            case EKeyDownArrow:
                {
                // Get current item index
                TInt oldIndex( lb->CurrentItemIndex() );
                // Call OfferKeyEventL
                TKeyResponse response(
                    CAknSettingPage::OfferKeyEventL( aKeyEvent, aType ) );
                // Get new item index
                TInt newIndex( lb->CurrentItemIndex() );
                // Compare new and old index
                if( oldIndex != newIndex )
                    {
                    // Notify focus change only if focus actually changes
                    // Top item index value is zero because there is no need to
                    // know what it is in focus change.
                    oldIndex = 0;
                    iObserver.HandleEventL( MAknCommonDialogsEventObserver::EFocusChange,
                        newIndex, oldIndex, Cba() );
                    }
                iUpdateItem = EFalse;    
                return response;
                // No break needed after return
                }

            case EKeyOK:
                {
                TInt focus( lb->CurrentItemIndex() );
                TInt topIndex( lb->TopItemIndex() );

                if( iObserver.HandleEventL(
                    MAknCommonDialogsEventObserver::ESelectionKeyPress, focus, topIndex, Cba() )
                    == MAknCommonDialogsEventObserver::ETryingToExit )
                    {
                    HideMenu();
                    SelectCurrentItemL();
                    AttemptExitL( ETrue );
                    }
                return EKeyWasConsumed;
                // No break needed after return
                }

            case EKeyEscape:
                {
                AttemptExitL( EFalse );
                return EKeyWasConsumed;
                // No break needed after return
                }

            default:
                {
                break;
                }
            }
        }
    else if( aType == EEventKeyUp )
        {
        if( iUpdateItem )
            {
            UpdateAndRedrawItemL();	
            }
        else
            {
        	iUpdateItem = ETrue;
            }
        }    
    return CAknSettingPage::OfferKeyEventL( aKeyEvent, aType );
    }
    
// -----------------------------------------------------------------------------
// CAknCommonDialogsRadioButtonSettingPage::UpdateAndRedrawItemL( )
//
//
// -----------------------------------------------------------------------------
//     
void CAknCommonDialogsRadioButtonSettingPage::UpdateAndRedrawItemL()
    {
    iModel->UpdateItemsL();
    const CListBoxView::CSelectionIndexArray* selections =
                            ListBoxControl()->View()->SelectionIndexes();
    SetItemArrayAndSelectionL(iModel, (*selections)[0]);
    }

// -----------------------------------------------------------------------------
// CAknCommonDialogsRadioButtonSettingPage::ProcessCommandL(TInt aCommandId)
//
//
// -----------------------------------------------------------------------------
//  
void CAknCommonDialogsRadioButtonSettingPage::ProcessCommandL(TInt aCommandId)
    {
    if(!IsEditable() && !(aCommandId == EAknSoftkeyBack || aCommandId == EAknSoftkeyCancel))
        {
        return;
        }
    
    HideMenu();
    
    // Respond to softkey events
    switch (aCommandId)
        {
        case EAknSoftkeyOk:
        case EAknSoftkeySelect:  
        case EAknSoftkeyDone:            
            {
            SelectCurrentItemL(); // has non-trivial implemenations in listbox type 
            // controls to put the selection on the current item
            AttemptExitL(ETrue);
            break;  
            }
        case EAknSoftkeyBack:
        case EAknSoftkeyCancel:
            AttemptExitL(EFalse);
            break;
        case EAknSoftkeyOptions:
            DisplayMenuL();
            break;
        default:
            break;
        }
    }
// -----------------------------------------------------------------------------
// CAknCommonDialogsRadioButtonSettingPage::NotifyDrivesChangedL
//
//
// -----------------------------------------------------------------------------
//
void CAknCommonDialogsRadioButtonSettingPage::NotifyDrivesChangedL(
    const MDesCArray* aItemArray)
    {
    // Update memory names & keep old selection
    const CListBoxView::CSelectionIndexArray* selections =
        ListBoxControl()->View()->SelectionIndexes();
    SetItemArrayAndSelectionL(aItemArray, (*selections)[0]);

    // Enable button in CBA
    CEikButtonGroupContainer* cba = Cba();
    MEikButtonGroup* buttonGroup = cba->ButtonGroup();
    cba->MakeCommandVisible( buttonGroup->CommandId( 0 ),
                                TBool( ETrue ) );
    }

//  End of File
