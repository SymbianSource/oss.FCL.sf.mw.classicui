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
* Description: Item action menu.
*
*/

#include <aknappui.h>
#include <akncollection.h>
#include <aknitemactionmenu.h>
#include <aknlistquerydialog.h>
#include <aknstyluspopupmenu.h>
#include <AknTasHook.h>
#include <avkon.rsg>
#include <eikmenub.h>
#include <eikpanic.h>

#include "akncollectionobserver.h"
#include "aknitemactionmenudata.h"
#include "aknitemactionmenuregister.h"

/**
 * Index for invalid list index.
 */
const TInt KInvalidListIndex( -1 );

// ---------------------------------------------------------------------------
// CAknItemActionMenu::NewL
// ---------------------------------------------------------------------------
//
CAknItemActionMenu* CAknItemActionMenu::NewL(
        MAknCollection& aCollection )
    {
    CAknItemActionMenu* self = CAknItemActionMenu::NewLC( aCollection );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::NewLC
// ---------------------------------------------------------------------------
//
CAknItemActionMenu* CAknItemActionMenu::NewLC( MAknCollection& aCollection )
    {
    CAknItemActionMenu* self = new ( ELeave ) CAknItemActionMenu();
    CleanupStack::PushL( self );
    self->ConstructL( aCollection );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::~CAknItemActionMenu
// ---------------------------------------------------------------------------
//
CAknItemActionMenu::~CAknItemActionMenu()
    {
    AKNTASHOOK_REMOVE();
    delete iPopupMenu;
    delete iMenuPane;
    delete iMenuData;
    iStates.Close();
    iObservers.Close();
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::RegisterCollectionL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknItemActionMenu* CAknItemActionMenu::RegisterCollectionL(
        MAknCollection& aCollection )
    {
    return AknItemActionMenuRegister::RegisterCollectionL( aCollection );
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::RemoveCollection
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknItemActionMenu::RemoveCollection(
        MAknCollection& aCollection )
    {
    for ( TInt i = 0; i < iStates.Count(); i++ )
        {
        MAknCollection* state( iStates[ i ] );
        if ( state == &aCollection )
            {
            iStates.Remove( i );
            break;
            }
        }
    UnregisterMenu(); 
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::InitMenuL
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknItemActionMenu::InitMenuL()
    {
    iMenuData->Reset();
    if ( !iMenuBar )
        {
        AknItemActionMenuRegister::RegisterItemActionMenuL( *this );
        }
    if ( iMenuBar )
        {
        if ( iMenuPane )
            {
            delete iMenuPane;
            iMenuPane = NULL;
            }
        iMenuPane = iMenuBar->PopulateItemActionMenuL( *this );
        }
    else
        {
        return EFalse;
        }

    return iMenuData->Count();
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::ShowMenuL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknItemActionMenu::ShowMenuL(
        const TPoint& aPosition,
        TUint /*aFlags*/ )
    {
    if ( iMenuData->Count() )
        {
        if ( !iPopupMenu )
            {
            iPopupMenu = CAknStylusPopUpMenu::NewL( this, TPoint() );
            }
        iPopupMenu->Clear();
        iMenuData->AddMenuItemsToStylusPopupMenuL( iPopupMenu );
        iPopupMenu->SetPosition(
                aPosition,
                CAknStylusPopUpMenu::EPositionTypeRightBottom );
        iPopupMenu->ShowMenu();
        }
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::CollectionChanged
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknItemActionMenu::CollectionChanged(
        MAknCollection& aCollection )
    {
    if ( iObservers.Count() && iStates.Find( &aCollection ) != KErrNotFound )
        {
        TBool collectionVisible( aCollection.CollectionState()
                & MAknCollection::EStateCollectionVisible );
        NotifyChangeToActiveObserver( collectionVisible );
        }
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::AddCollectionStateL
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::AddCollectionStateL(
        MAknCollection& aCollection )
    {
    if ( iStates.Find( &aCollection ) == KErrNotFound )
        {
        iStates.InsertL( &aCollection, 0 );
        }
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::SetMenuBar
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::SetMenuBar(
        MEikMenuObserver* aMenuObserver,
        CEikMenuBar* aMenuBar )
    {
    iMenuBarObserver = aMenuObserver;
    iMenuBar = aMenuBar;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::CollectionHighlightVisible
// ---------------------------------------------------------------------------
//
TBool CAknItemActionMenu::CollectionHighlightVisible() const
    {
    TBool highlightVisible( ETrue );
    for ( TInt i = 0; i < iStates.Count(); i++ )
        {
        MAknCollection* state( iStates[ i ] );
        if ( state->CollectionState() &
                MAknCollection::EStateCollectionVisible )
            {
            highlightVisible = state->CollectionState()
                & MAknCollection::EStateHighlightVisible;
            break;
            }
        }
    return highlightVisible;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::CollectionSoftkeyVisible
// ---------------------------------------------------------------------------
//
TBool CAknItemActionMenu::CollectionSoftkeyVisible(
        TBool aVisibleCollection ) const
    {
    TBool softkeyVisible( ETrue );
    for ( TInt i = 0; i < iStates.Count(); i++ )
        {
        TInt state( iStates[ i ]->CollectionState() );
        if ( !aVisibleCollection
                || state & MAknCollection::EStateCollectionVisible )
            {
            if ( state & MAknCollection::EStateMultipleSelection
                    || state & MAknCollection::EStateViewOnly )
                {
                softkeyVisible = ETrue;
                }
            else
                {
                softkeyVisible =
                    state & MAknCollection::EStateHighlightVisible;
                }
            break;
            }
        }
    return softkeyVisible;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::MenuData
// ---------------------------------------------------------------------------
//
CAknItemActionMenuData& CAknItemActionMenu::MenuData()
    {
    return *iMenuData;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::RegisterCollectionObserverL
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::RegisterCollectionObserverL(
        MAknCollectionObserver& aObserver )
    {
    if ( iObservers.Find( &aObserver ) == KErrNotFound )
        {
        iObservers.InsertL( &aObserver, 0 );
        aObserver.SetItemActionMenu( this );
        }
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::RemoveCollectionObserver
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::RemoveCollectionObserver(
        MAknCollectionObserver& aObserver )
    {
    TInt index( iObservers.Find( &aObserver ) );
    if ( index != KErrNotFound )
        {
        iObservers.Remove( index );
        UnregisterMenu(); 
        }
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::CollectionCount
// ---------------------------------------------------------------------------
//
TInt CAknItemActionMenu::CollectionCount() const
    {
    return iStates.Count();
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::CAknItemActionMenu
// ---------------------------------------------------------------------------
//
CAknItemActionMenu::CAknItemActionMenu()
    : iPopupMenu( NULL ),
    iMenuBarObserver( NULL ),
    iMenuBar( NULL ),
    iMenuPane( NULL ),
    iMenuData( NULL )
    {
    AKNTASHOOK_ADD( this, "CAknItemActionMenu" );
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::ConstructL
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::ConstructL( MAknCollection& aCollection )
    {
    AddCollectionStateL( aCollection );
    iMenuData = CAknItemActionMenuData::NewL();
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::LaunchSubMenuQueryL
// ---------------------------------------------------------------------------
//
TInt CAknItemActionMenu::LaunchSubMenuQueryL( const TDesC& aHeading )
    {
    TInt selectedIndex( KInvalidListIndex );
    if ( iMenuData->Count() )
        {
        CAknListQueryDialog* queryDialog
            = new ( ELeave ) CAknListQueryDialog( &selectedIndex );
        queryDialog->PrepareLC( R_AVKON_ITEM_ACTION_SUB_MENU_QUERY );
        MDesCArray* itemArray = iMenuData->MenuItemsForQueryDialogL();
        queryDialog->SetItemTextArray( itemArray );
        queryDialog->SetOwnershipType( ELbmOwnsItemArray );
        if ( aHeading != KNullDesC && queryDialog->QueryHeading() )
            {
            queryDialog->QueryHeading()->SetTextL( aHeading );
            }
        queryDialog->RunLD();
        }
    return ++selectedIndex;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::NotifyChangeToActiveObserver
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::NotifyChangeToActiveObserver(
        TBool aCollectionVisible )
    {
    for ( TInt i = 0; i < iObservers.Count(); i++ )
        {
        MAknCollectionObserver* observer( iObservers[ i ] );
        if ( observer->Active() )
            {
            observer->CollectionChanged( aCollectionVisible );
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::SetEmphasis
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::SetEmphasis(
        CCoeControl* /*aMenuControl*/,
        TBool /*aEmphasis*/ )
    {
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::ProcessCommandL
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::ProcessCommandL( TInt aCommandId )
    {
    MAknCollection* informState ( NULL );
    // Store collection state before sending the command
    for ( TInt i = 0; i < iStates.Count(); i++ )
        {
        MAknCollection* state( iStates[ i ] );
        if ( state->CollectionState()
                & MAknCollection::EStateCollectionVisible )
            {
            informState = state;
            break;
            }
        }       
    
    if ( aCommandId > 0 )
        {
        TInt cascadeId( iMenuData->MenuItemCascadeId( aCommandId ) );
        if ( cascadeId && iMenuPane )
            {
            TMenuItemTextBuf text = iMenuData->MenuItemText( aCommandId );
            iMenuData->Reset();
            iMenuPane->AddCascadeMenuItemsToActionMenuL(
                    cascadeId, EFalse, *iMenuData );
            aCommandId = LaunchSubMenuQueryL( text );
            }
                
        if ( aCommandId > 0 && iMenuBarObserver )
            {
            iProcessingCommand = ETrue; 
            iMenuBarObserver->ProcessCommandL(
                    iMenuData->MenuItemCommandId( aCommandId ) );
            iProcessingCommand = EFalse; 
            }
        }
    // Inform collection that submenu was closed
    if ( iStates.Find( informState ) != KErrNotFound ) 
        {
        informState->ItemActionMenuClosed();
        }
    UnregisterMenu(); 
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::UnregisterMenu
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::UnregisterMenu()
    {
    if ( !iProcessingCommand && !iStates.Count() && !iObservers.Count() )
        {
        delete iPopupMenu;
        iPopupMenu = NULL;
        delete iMenuPane;
        iMenuPane = NULL;
        AknItemActionMenuRegister::UnregisterItemActionMenu( *this );
        }
    }

// End of File
