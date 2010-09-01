/*
* Copyright (c) 2009-2010 Nokia Corporation and/or its subsidiary(-ies).
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
#include "akntrace.h"
#include "aknmarkingmode.h"

/**
 * Index for invalid list index.
 */
const TInt KInvalidListIndex( -1 );

// ---------------------------------------------------------------------------
// CAknItemActionMenu::NewL
// ---------------------------------------------------------------------------
//
CAknItemActionMenu* CAknItemActionMenu::NewL(
        MAknCollection& aCollection, MObjectProvider* aOwner )
    {
    _AKNTRACE_FUNC_ENTER;
    CAknItemActionMenu* self = CAknItemActionMenu::NewLC( 
            aCollection, aOwner );
    CleanupStack::Pop( self );
    _AKNTRACE_FUNC_EXIT;
    return self;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::NewLC
// ---------------------------------------------------------------------------
//
CAknItemActionMenu* CAknItemActionMenu::NewLC(
        MAknCollection& aCollection, MObjectProvider* aOwner )
    {
    _AKNTRACE_FUNC_ENTER;
    CAknItemActionMenu* self = new ( ELeave ) CAknItemActionMenu( aOwner );
    CleanupStack::PushL( self );
    self->ConstructL( aCollection );
    _AKNTRACE_FUNC_EXIT;
    return self;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::~CAknItemActionMenu
// ---------------------------------------------------------------------------
//
CAknItemActionMenu::~CAknItemActionMenu()
    {
    _AKNTRACE_FUNC_ENTER;
    AKNTASHOOK_REMOVE();
    delete iPopupMenu;
    delete iMenuPane;
    delete iMenuData;
    delete iMarking;
    iStates.Close();
    
    for ( TInt i = 0; i < iObservers.Count(); ++i )
        {
        iObservers[i]->SetItemActionMenu( NULL );
        }

    iObservers.Close();
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::RegisterCollectionL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknItemActionMenu* CAknItemActionMenu::RegisterCollectionL(
        MAknCollection& aCollection )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE_FUNC_EXIT;
    return AknItemActionMenuRegister::RegisterCollectionL(
            aCollection, NULL );
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::RegisterCollectionL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknItemActionMenu* CAknItemActionMenu::RegisterCollectionL(
        MAknCollection& aCollection, MObjectProvider* aMenuBarOwner )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE_FUNC_EXIT;
    return AknItemActionMenuRegister::RegisterCollectionL( 
            aCollection, aMenuBarOwner );
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::RemoveCollection
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknItemActionMenu::RemoveCollection(
        MAknCollection& aCollection )
    {
    _AKNTRACE_FUNC_ENTER;
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
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::InitMenuL
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknItemActionMenu::InitMenuL()
    {
    _AKNTRACE_FUNC_ENTER;
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

    _AKNTRACE_FUNC_EXIT;
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
    _AKNTRACE_FUNC_ENTER;
    if ( iMenuData->Count() )
        {
        if ( !iPopupMenu )
            {
            iPopupMenu = CAknStylusPopUpMenu::NewL( this, TPoint(), NULL,
                    CAknStylusPopUpMenu::EConsumeKeyEvents );
            }
        iPopupMenu->Clear();
        iMenuData->AddMenuItemsToStylusPopupMenuL( iPopupMenu );
        iPopupMenu->SetPosition(
                aPosition,
                CAknStylusPopUpMenu::EPositionTypeRightBottom );
        iPopupMenu->ShowMenu();
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::CollectionChanged
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknItemActionMenu::CollectionChanged(
        MAknCollection& aCollection )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iObservers.Count() && iStates.Find( &aCollection ) != KErrNotFound )
        {
        TBool collectionVisible( aCollection.CollectionState()
                & MAknCollection::EStateCollectionVisible );
        NotifyChangeToActiveObserver( collectionVisible );
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::AddCollectionStateL
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::AddCollectionStateL(
        MAknCollection& aCollection )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iStates.Find( &aCollection ) == KErrNotFound )
        {
        iStates.InsertL( &aCollection, 0 );
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::SetMenuBar
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::SetMenuBar(
        MEikMenuObserver* aMenuObserver,
        CEikMenuBar* aMenuBar )
    {
    _AKNTRACE_FUNC_ENTER;
    iMenuBarObserver = aMenuObserver;
    iMenuBar = aMenuBar;
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::CollectionHighlightVisible
// ---------------------------------------------------------------------------
//
TBool CAknItemActionMenu::CollectionHighlightVisible() const
    {
    _AKNTRACE_FUNC_ENTER;
    TBool highlightVisible( ETrue );
    for ( TInt i = 0; i < iStates.Count(); i++ )
        {
        MAknCollection* collection( iStates[ i ] );
        TUint state = collection->CollectionState();

        highlightVisible = state & MAknCollection::EStateHighlightVisible;
        
        if ( highlightVisible )
            {
            // Highlight can't be visible if the collection is not visible.
            highlightVisible = state & MAknCollection::EStateCollectionVisible;
            break;
            }
        }
    _AKNTRACE_FUNC_EXIT;
    return highlightVisible;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::CollectionSoftkeyVisible
// ---------------------------------------------------------------------------
//
TBool CAknItemActionMenu::CollectionSoftkeyVisible(
        TBool aVisibleCollection ) const
    {
    _AKNTRACE_FUNC_ENTER;
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
    _AKNTRACE_FUNC_EXIT;
    return softkeyVisible;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::MenuData
// ---------------------------------------------------------------------------
//
CAknItemActionMenuData& CAknItemActionMenu::MenuData()
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE_FUNC_EXIT;
    return *iMenuData;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::RegisterCollectionObserverL
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::RegisterCollectionObserverL(
        MAknCollectionObserver& aObserver )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iObservers.Find( &aObserver ) == KErrNotFound )
        {
        iObservers.InsertL( &aObserver, 0 );
        aObserver.SetItemActionMenu( this );
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::RemoveCollectionObserver
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::RemoveCollectionObserver(
        MAknCollectionObserver& aObserver )
    {
    _AKNTRACE_FUNC_ENTER;
    TInt index( iObservers.Find( &aObserver ) );
    if ( index != KErrNotFound )
        {
        iObservers.Remove( index );
        UnregisterMenu(); 
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::CollectionCount
// ---------------------------------------------------------------------------
//
TInt CAknItemActionMenu::CollectionCount() const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE_FUNC_EXIT;
    return iStates.Count();
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::Owner
// ---------------------------------------------------------------------------
//
 MObjectProvider* CAknItemActionMenu::Owner() const
     {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE_FUNC_EXIT;
     return iOwner;
     }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::MarkingMode
// ---------------------------------------------------------------------------
//
CAknMarkingMode& CAknItemActionMenu::MarkingMode()
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE_FUNC_EXIT;
    return *iMarking;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::CollectionHasMarkedItems
// ---------------------------------------------------------------------------
//
TBool CAknItemActionMenu::CollectionHasMarkedItems()
    {
    _AKNTRACE_FUNC_ENTER;
    TBool markedItems( EFalse );
    for ( TInt i = 0; i < iStates.Count(); i++ )
        {
        TInt state( iStates[ i ]->CollectionState() );
        if ( state & MAknCollection::EStateCollectionVisible )
            {
            if ( state & MAknCollection::EStateMarkedItems )
                {
                markedItems = ETrue;
                }
            }
        }
    _AKNTRACE_FUNC_EXIT;
    return markedItems;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::HideMenu
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::HideMenu()
    {
    if ( iPopupMenu && !iProcessingCommand )
        {
        iPopupMenu->HideMenu();
        }
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::CAknItemActionMenu
// ---------------------------------------------------------------------------
//
CAknItemActionMenu::CAknItemActionMenu( MObjectProvider* aOwner )
    : iPopupMenu( NULL ),
    iMenuBarObserver( NULL ),
    iMenuBar( NULL ),
    iMenuPane( NULL ),
    iMenuData( NULL ),
    iOwner( aOwner ),
    iMarking( NULL )
    {
    _AKNTRACE_FUNC_ENTER;
    AKNTASHOOK_ADD( this, "CAknItemActionMenu" );
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::ConstructL
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::ConstructL( MAknCollection& aCollection )
    {
    _AKNTRACE_FUNC_ENTER;
    AddCollectionStateL( aCollection );
    iMenuData = CAknItemActionMenuData::NewL();
    iMarking = CAknMarkingMode::NewL( *this, iStates );
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::LaunchSubMenuQueryL
// ---------------------------------------------------------------------------
//
TInt CAknItemActionMenu::LaunchSubMenuQueryL( const TDesC& aHeading )
    {
    _AKNTRACE_FUNC_ENTER;
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
    _AKNTRACE_FUNC_EXIT;
    return ++selectedIndex;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::NotifyChangeToActiveObserver
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::NotifyChangeToActiveObserver(
        TBool aCollectionVisible )
    {
    _AKNTRACE_FUNC_ENTER;
    for ( TInt i = 0; i < iObservers.Count(); i++ )
        {
        MAknCollectionObserver* observer( iObservers[ i ] );
        if ( observer->Active() )
            {
            observer->CollectionChanged( aCollectionVisible );
            break;
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::SetEmphasis
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::SetEmphasis(
        CCoeControl* /*aMenuControl*/,
        TBool /*aEmphasis*/ )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::ProcessCommandL
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::ProcessCommandL( TInt aCommandId )
    {
    _AKNTRACE_FUNC_ENTER;
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
            iMenuPane->AddCascadeMenuItemsToMenuL(
                    cascadeId, EFalse, ETrue, iMenuData );
            aCommandId = LaunchSubMenuQueryL( text );
            }
                
        if ( aCommandId > 0 && iMenuData->MenuItemCommandId( aCommandId ) 
                == EAknCmdMarkingModeMarkOne && iMenuBar )
            {
            MarkingMode().MarkCurrentItemL();
            }
        else if ( aCommandId > 0 && iMenuBarObserver )
            {
            iProcessingCommand = ETrue; 
            iMenuBarObserver->ProcessCommandL(
                    iMenuData->MenuItemCommandId( aCommandId ) );
            iProcessingCommand = EFalse; 
            // Try exit marking mode
            MarkingMode().TryExitMarkingMode();
            }
        }
    // Inform collection that submenu was closed
    if ( informState && iStates.Find( informState ) != KErrNotFound ) 
        {
        informState->ItemActionMenuClosed();
        }
    UnregisterMenu(); 
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenu::UnregisterMenu
// ---------------------------------------------------------------------------
//
void CAknItemActionMenu::UnregisterMenu()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( !iProcessingCommand && !iStates.Count() && !iObservers.Count() )
        {
        delete iPopupMenu;
        iPopupMenu = NULL;
        delete iMenuPane;
        iMenuPane = NULL;
        AknItemActionMenuRegister::UnregisterItemActionMenu( *this );
        }
    _AKNTRACE_FUNC_EXIT;
    }

// End of File

