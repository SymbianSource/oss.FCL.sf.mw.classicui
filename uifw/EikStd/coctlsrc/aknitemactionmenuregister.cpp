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
* Description: Item action menu register.
*
*/
#include <aknappui.h>
#include <aknview.h>
#include <aknViewAppUi.h>
#include <aknitemactionmenu.h>
#include <eikdialg.h>
#include <eikmenub.h>

#include "aknitemactionmenuregister.h"
#include "aknitemactionmenuregisterarray.h"

const TUid KAknItemActionMenuRegister = { 0x20028760 };
const TInt KRegisterDestructionPriority( -1 );

// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::SetConstructingMenuBarOwnerL
// ---------------------------------------------------------------------------
//
EXPORT_C void AknItemActionMenuRegister::SetConstructingMenuBarOwnerL(
        MObjectProvider* aMenuBarOwner )
    {
    if ( AppUiSingleClickCompatible() )
        {
        AknItemActionMenuRegister* instance( Instance() );
        if ( instance )
            {
            instance->iMenuBarOwner = aMenuBarOwner;
            }
        }
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::SetOverridingMenuBarOwnerL
// ---------------------------------------------------------------------------
//
EXPORT_C void AknItemActionMenuRegister::SetOverridingMenuBarOwnerL(
        MObjectProvider* aMenuBarOwner, TUint /*aFlags*/ )
    {
    if ( AppUiSingleClickCompatible() )
        {
        AknItemActionMenuRegister* instance( Instance() );
        if ( instance )
            {
            instance->iOverridingMenuBarOwner = aMenuBarOwner;
            }
        }
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::RegisterCollectionL
// ---------------------------------------------------------------------------
//
CAknItemActionMenu* AknItemActionMenuRegister::RegisterCollectionL(
        MAknCollection& aCollectionState )
    {
    CAknItemActionMenu* menu( NULL );
    if ( AppUiSingleClickCompatible() )
        {
        AknItemActionMenuRegister* instance( Instance() );
        if ( instance )
            {
            menu = instance->DoRegisterCollectionL( aCollectionState );
            }
        }
    return menu;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::RegisterMenuBarL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::RegisterMenuBarL(
        CEikMenuBar& aMenuBar )
    {
    if ( AppUiSingleClickCompatible() )
        {
        AknItemActionMenuRegister* instance( Instance() );
        if ( instance )
            {
            instance->DoRegisterMenuBarL( aMenuBar );
            }
        }
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::UnregisterMenuBar
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::UnregisterMenuBar(
        CEikMenuBar& aMenuBar )
    {
    if ( AppUiSingleClickCompatible() )
        {
        AknItemActionMenuRegister* instance( Instance() );
        if ( instance )
            {
            instance->DoUnregisterMenuBar( aMenuBar );
            }
        }
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::RegisterItemActionMenuL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::RegisterItemActionMenuL(
        CAknItemActionMenu& aItemActionMenu )
    {
    AknItemActionMenuRegister* instance( Instance() );
    if ( instance )
        {
        instance->DoRegisterItemActionMenuL( aItemActionMenu );
        }
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::UnregisterItemActionMenu
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::UnregisterItemActionMenu(
        CAknItemActionMenu& aItemActionMenu )
    {
    if ( AppUiSingleClickCompatible() )
        {
        AknItemActionMenuRegister* instance( Instance() );
        if ( instance )
            {
            instance->DoUnregisterItemActionMenu( aItemActionMenu );
            }
        }
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::RegisterCollectionObserverL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::RegisterCollectionObserverL(
        MAknCollectionObserver& aObserver )
    {
    if ( AppUiSingleClickCompatible() )
        {
        AknItemActionMenuRegister* instance( Instance() );
        if ( instance )
            {
            instance->DoRegisterCollectionObserverL( aObserver );
            }
        }
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::UnregisterCollectionObserver
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::UnregisterCollectionObserver(
        MAknCollectionObserver& aObserver )
    {
    if ( AppUiSingleClickCompatible() )
        {
        AknItemActionMenuRegister* instance( Instance() );
        if ( instance )
            {
            instance->DoUnregisterCollectionObserver( aObserver );
            }
        }
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::~AknItemActionMenuRegister
// ---------------------------------------------------------------------------
//
AknItemActionMenuRegister::~AknItemActionMenuRegister()
    {
    for ( TInt i = 0; i < iUnregisteredMenus.Count(); i++ )
        {
        TAknUnregisteredMenuData& data( iUnregisteredMenus[ i ] );
        delete data.iMenu;
        data.iMenu = NULL;
        }
    iUnregisteredMenus.Close();
    iUnregisteredObservers.Close();
    delete iRegisterArray;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::AknItemActionMenuRegister
// ---------------------------------------------------------------------------
//
AknItemActionMenuRegister::AknItemActionMenuRegister()
    : CCoeStatic( KAknItemActionMenuRegister, KRegisterDestructionPriority ),
    iMenuBarOwner( NULL )
    {
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::ConstructL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::ConstructL()
    {
    iRegisterArray = CAknItemActionMenuRegisterArray::NewL();
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::AppUiSingleClickCompatible
// ---------------------------------------------------------------------------
//
TBool AknItemActionMenuRegister::AppUiSingleClickCompatible()
    {
    CAknAppUi* appUi =
        static_cast<CAknAppUi*>( CEikonEnv::Static()->AppUi() );
    return appUi->IsSingleClickCompatible();
    }

// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::Instance
// ---------------------------------------------------------------------------
//
AknItemActionMenuRegister* AknItemActionMenuRegister::Instance()
    {
    AknItemActionMenuRegister* instance =
        static_cast<AknItemActionMenuRegister*>(
                CCoeEnv::Static( KAknItemActionMenuRegister ) );
    if ( !instance )
        {
        TRAP_IGNORE( instance = CreateInstanceL() ); 
        }
    return instance;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::DoRegisterCollectionL
// ---------------------------------------------------------------------------
//
CAknItemActionMenu* AknItemActionMenuRegister::DoRegisterCollectionL(
        MAknCollection& aCollectionState )
    {
    CAknItemActionMenu* menu( NULL );
    CEikMenuBar* menuBar = FindCurrentMenuBarL();
    menu = RegisterStateToItemActionMenuL( menuBar, aCollectionState );
    return menu;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::DoRegisterMenuBarL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::DoRegisterMenuBarL( CEikMenuBar& aMenuBar )
    {
    CAknItemActionMenu* menu( NULL );
    for ( TInt i = 0; i < iUnregisteredMenus.Count(); i++ )
        {
        TAknUnregisteredMenuData& data( iUnregisteredMenus[ i ] );
        CEikMenuBar* ownerMenubar( NULL );
        data.iOwner->MopGetObjectNoChaining( ownerMenubar );
        if ( ownerMenubar == &aMenuBar )
            {
            menu = data.iMenu;
            if ( menu )
                {
                AddRegisterEntryL( aMenuBar, *menu );
                }
            iUnregisteredMenus.Remove( i );
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::DoUnregisterMenuBar
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::DoUnregisterMenuBar( CEikMenuBar& aMenuBar )
    {
    iRegisterArray->UnregisterMenuBar( aMenuBar );
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::DoRegisterItemActionMenuL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::DoRegisterItemActionMenuL(
        CAknItemActionMenu& aItemActionMenu )
    {
    CEikMenuBar* menuBar( NULL );
    for ( TInt i = 0; i < iUnregisteredMenus.Count(); i++ )
        {
        TAknUnregisteredMenuData& data( iUnregisteredMenus[ i ] );
        if ( data.iMenu == &aItemActionMenu )
            {
            data.iOwner->MopGetObjectNoChaining( menuBar );
            if ( menuBar )
                {
                AddRegisterEntryL( *menuBar, aItemActionMenu );
                }
            iUnregisteredMenus.Remove( i );
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::DoUnregisterItemActionMenu
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::DoUnregisterItemActionMenu(
        CAknItemActionMenu& aItemActionMenu )
    {
    iRegisterArray->UnregisterItemActionMenu( aItemActionMenu );
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::DoRegisterCollectionObserverL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::DoRegisterCollectionObserverL(
        MAknCollectionObserver& aObserver )
    {
    CEikMenuBar* menuBar = FindCurrentMenuBarL();
    if ( !menuBar || !iRegisterArray->RegisterCollectionObserverL(
            *menuBar, aObserver ) )
        {
        TAknUnregisteredObserverData newData( menuBar, aObserver );
        iUnregisteredObservers.AppendL( newData );
        }
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::DoUnregisterCollectionObserver
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::DoUnregisterCollectionObserver(
        MAknCollectionObserver& aObserver )
    {
    iRegisterArray->UnregisterCollectionObserver( aObserver );
    for ( TInt i = 0; i < iUnregisteredObservers.Count(); i++ )
        {
        TAknUnregisteredObserverData& data( iUnregisteredObservers[ i ] );
        if ( &data.iObserver == &aObserver )
            {
            iUnregisteredObservers.Remove( i );
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::DialogMenuBar
// ---------------------------------------------------------------------------
//
CEikMenuBar* AknItemActionMenuRegister::DialogMenuBar( CAknAppUi* aAppUi )
    {
    CEikMenuBar* menuBar( NULL );
    // Check if there is an active dialog and fetch its menubar
    if ( aAppUi->IsDisplayingMenuOrDialog() )
        {
        CCoeControl* ctrl = aAppUi->TopFocusedControl();
        if ( ctrl )
            {
            CEikDialog* dialog = ctrl->MopGetObjectNoChaining( dialog );
            if ( dialog )
                {
                dialog->MopGetObject( menuBar );
                }
            }
        }
    return menuBar;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::ViewMenuBar
// ---------------------------------------------------------------------------
//
CEikMenuBar* AknItemActionMenuRegister::ViewMenuBar( CAknAppUi* aAppUi )
    {
    CEikMenuBar* menuBar( NULL );
    CAknViewAppUi* appUi( static_cast<CAknViewAppUi*>( aAppUi ) );

    // Check if there is an active view
    TVwsViewId uid;
    if ( appUi->GetActiveViewId( uid ) == KErrNone )
        {
        if ( uid.iAppUid != uid.iViewUid )
            {
            CAknView* view = appUi->View( uid.iViewUid );
            if ( view )
                {
                menuBar = view->MenuBar();
                }
            }
        }
    return menuBar;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::ConstructingObjectMenuBar
// ---------------------------------------------------------------------------
//
CEikMenuBar* AknItemActionMenuRegister::ConstructingObjectMenuBar()
    {
    CEikMenuBar* menuBar( NULL );
    if ( iMenuBarOwner )
        {
        iMenuBarOwner->MopGetObjectNoChaining( menuBar );
        }
    return menuBar;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::OverridingObjectMenuBar
// ---------------------------------------------------------------------------
//
CEikMenuBar* AknItemActionMenuRegister::OverridingObjectMenuBar()
    {
    CEikMenuBar* menuBar( NULL );
    if ( iOverridingMenuBarOwner )
        {
        iOverridingMenuBarOwner->MopGetObjectNoChaining( menuBar );
        }
    return menuBar;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::RegisterStateToItemActionMenuL
// ---------------------------------------------------------------------------
//
CAknItemActionMenu* AknItemActionMenuRegister::RegisterStateToItemActionMenuL(
        CEikMenuBar* aMenuBar,
        MAknCollection& aCollectionState )
    {
    CAknItemActionMenu* menu( NULL );

    // View / dialog / appUi menubar was found
    if ( aMenuBar )
        {
        menu = aMenuBar->ItemActionMenu();
        // menubar does not have item action menu -> create one
        if ( !menu )
            {
            menu = CAknItemActionMenu::NewLC( aCollectionState );
            AddRegisterEntryL( *aMenuBar, *menu );
            CleanupStack::Pop( menu );
            }
        // add new collection state to existing item action menu
        else
            {
            menu->AddCollectionStateL( aCollectionState );
            }
        }
    // View / dialog / appUi menubar was not found
    // Constructing menu bar owner is existing
    else if ( iMenuBarOwner )
        {
        // Go through unregistered menus
        TBool viewRegistered( EFalse );
        for ( TInt i = 0; i < iUnregisteredMenus.Count(); i++ )
            {
            TAknUnregisteredMenuData& data( iUnregisteredMenus[ i ] );
            // This view already has unregistered menu
            // Add collection state to it
            if ( data.iOwner == iMenuBarOwner )
                {
                viewRegistered = ETrue;
                data.iMenu->AddCollectionStateL( aCollectionState );
                menu = data.iMenu;
                break;
                }
            }
        // No unregistered menu found -> create one and add to list
        if ( !viewRegistered )
            {
            menu = CAknItemActionMenu::NewL( aCollectionState );
            TAknUnregisteredMenuData newData;
            newData.iOwner = iMenuBarOwner;
            newData.iMenu = menu;
            iUnregisteredMenus.AppendL( newData );
            }
        }
    if ( menu )
        {
        // Set observers with menubar to menu
        AddObserversToItemActionMenuL( aMenuBar, *menu );
        }
    return menu;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::FindCurrentMenuBarL
// ---------------------------------------------------------------------------
//
CEikMenuBar* AknItemActionMenuRegister::FindCurrentMenuBarL()
    {
    CEikonEnv* eikonEnv( CEikonEnv::Static() );
    CAknAppUi* appUi( static_cast<CAknAppUi*>( eikonEnv->AppUi() ) );
    TBool isConstructingDialog( EFalse );
    CEikMenuBar* menuBar( NULL );
    
    // If overriding menubar owner is set then it's the one to obey. If the
    // overriding menubar owner doesn't supply a menubar object then there
    // isn't proper one available.
    if ( iOverridingMenuBarOwner )
        {
        return OverridingObjectMenuBar();
        }
    
    // Check if there is existing constructing dialog
    if ( iMenuBarOwner )
        {
        CEikDialog* dialog( NULL );
        iMenuBarOwner->MopGetObjectNoChaining( dialog );
        if ( dialog )
            {
            isConstructingDialog = ETrue;
            }
        }
    // No constructing dialog
    if ( !isConstructingDialog )
        {
        // Fetch pointer to dialog that is currently displayed
        menuBar = DialogMenuBar( appUi );
        // No dialog - pointer to active view menu bar
        if ( !menuBar )
            {
            menuBar = ViewMenuBar( appUi );
            }
        }
    
    // Fetch pointer to constructing object menu bar
    if ( !menuBar )
        {
        menuBar = ConstructingObjectMenuBar();
        }

    // Finally, if no luck with others, fetch pointer to appUi menu bar.
    if ( !menuBar )
        {
        menuBar = eikonEnv->AppUiFactory()->MenuBar();
        }
    return menuBar;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::AddRegisterEntryL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::AddRegisterEntryL(
        CEikMenuBar& aMenuBar, CAknItemActionMenu& aItemActionMenu )
    {
    aMenuBar.SetItemActionMenu( &aItemActionMenu );
    iRegisterArray->AddEntryL( aMenuBar, aItemActionMenu );
    AddObserversToItemActionMenuL( &aMenuBar, aItemActionMenu );
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::AddObserversToItemActionMenuL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::AddObserversToItemActionMenuL(
        CEikMenuBar* aMenuBar, CAknItemActionMenu& aItemActionMenu )
    {
    for ( TInt i = 0; i < iUnregisteredObservers.Count(); i++ )
        {
        TAknUnregisteredObserverData& data( iUnregisteredObservers[ i ] );
        // Add if matching menubar or observer with no menubar
        if ( data.iMenuBar == aMenuBar || !data.iMenuBar )
            {
            aItemActionMenu.RegisterCollectionObserverL(
                    data.iObserver );
            }
        }
    iUnregisteredObservers.Reset();
    }

// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::CreateInstanceL
// ---------------------------------------------------------------------------
//
AknItemActionMenuRegister* AknItemActionMenuRegister::CreateInstanceL()
    {
    AknItemActionMenuRegister* instance = NULL; 
    instance = new ( ELeave ) AknItemActionMenuRegister();
    CleanupStack::PushL( instance );
    instance->ConstructL();
    CleanupStack::Pop( instance );
    return instance;
    }

// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::TAknUnregisteredObserverData
// ::TAknUnregisteredObserverData
// ---------------------------------------------------------------------------
//
AknItemActionMenuRegister::TAknUnregisteredObserverData::\
    TAknUnregisteredObserverData(
        CEikMenuBar* aMenuBar, MAknCollectionObserver& aObserver )
    : iMenuBar( aMenuBar ),
    iObserver( aObserver )
    {
    }


// End of File

