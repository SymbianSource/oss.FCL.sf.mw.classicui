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
* Description: Item action menu register.
*
*/
#include <aknappui.h>
#include <aknview.h>
#include <aknViewAppUi.h>
#include <aknitemactionmenu.h>
#include <eikdialg.h>
#include <eikmenub.h>
#include <akntrace.h>

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
    _AKNTRACE_FUNC_ENTER;

    AknItemActionMenuRegister* instance( Instance() );

    if ( instance )
        {
        instance->DoSetConstructingMenuBarOwnerL( aMenuBarOwner ); 
        }

    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::SetOverridingMenuBarOwnerL
// ---------------------------------------------------------------------------
//
EXPORT_C void AknItemActionMenuRegister::SetOverridingMenuBarOwnerL(
        MObjectProvider* aMenuBarOwner, TUint /*aFlags*/ )
    {
    _AKNTRACE_FUNC_ENTER;

    if ( AppUiSingleClickCompatible() )
        {
        AknItemActionMenuRegister* instance( Instance() );
        if ( instance )
            {
            instance->iOverridingMenuBarOwner = aMenuBarOwner;
            }
        }

    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::RegisterCollectionL
// ---------------------------------------------------------------------------
//
CAknItemActionMenu* AknItemActionMenuRegister::RegisterCollectionL(
        MAknCollection& aCollectionState )
    {
    _AKNTRACE_FUNC_ENTER;

    CAknItemActionMenu* menu( NULL );
    if ( AppUiSingleClickCompatible() )
        {
        AknItemActionMenuRegister* instance( Instance() );
        if ( instance )
            {
            menu = instance->DoRegisterCollectionL( aCollectionState );
            }
        }

    _AKNTRACE_FUNC_EXIT;
    return menu;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::RegisterMenuBarL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::RegisterMenuBarL(
        CEikMenuBar& aMenuBar )
    {
    _AKNTRACE_FUNC_ENTER;

    if ( AppUiSingleClickCompatible() )
        {
        AknItemActionMenuRegister* instance( Instance() );
        if ( instance )
            {
            instance->DoRegisterMenuBarL( aMenuBar );
            }
        }

    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::UnregisterMenuBar
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::UnregisterMenuBar(
        CEikMenuBar& aMenuBar )
    {
    _AKNTRACE_FUNC_ENTER;

    if ( AppUiSingleClickCompatible() )
        {
        AknItemActionMenuRegister* instance( Instance() );
        if ( instance )
            {
            instance->DoUnregisterMenuBar( aMenuBar );
            }
        }

    _AKNTRACE_FUNC_EXIT;
   }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::RegisterItemActionMenuL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::RegisterItemActionMenuL(
        CAknItemActionMenu& aItemActionMenu )
    {
    _AKNTRACE_FUNC_ENTER;

    AknItemActionMenuRegister* instance( Instance() );
    if ( instance )
        {
        instance->DoRegisterItemActionMenuL( aItemActionMenu );
        }

    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::UnregisterItemActionMenu
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::UnregisterItemActionMenu(
        CAknItemActionMenu& aItemActionMenu )
    {
    _AKNTRACE_FUNC_ENTER;

    if ( AppUiSingleClickCompatible() )
        {
        AknItemActionMenuRegister* instance( Instance() );
        if ( instance )
            {
            instance->DoUnregisterItemActionMenu( aItemActionMenu );
            }
        }

    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::RegisterCollectionObserverL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::RegisterCollectionObserverL(
        MAknCollectionObserver& aObserver )
    {
    _AKNTRACE_FUNC_ENTER;

    if ( AppUiSingleClickCompatible() )
        {
        AknItemActionMenuRegister* instance( Instance() );
        if ( instance )
            {
            instance->DoRegisterCollectionObserverL( aObserver );
            }
        }

    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::UnregisterCollectionObserver
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::UnregisterCollectionObserver(
        MAknCollectionObserver& aObserver )
    {
    _AKNTRACE_FUNC_ENTER;

    if ( AppUiSingleClickCompatible() )
        {
        AknItemActionMenuRegister* instance( Instance() );
        if ( instance )
            {
            instance->DoUnregisterCollectionObserver( aObserver );
            }
        }

    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::~AknItemActionMenuRegister
// ---------------------------------------------------------------------------
//
AknItemActionMenuRegister::~AknItemActionMenuRegister()
    {
    _AKNTRACE_FUNC_ENTER;

    for ( TInt i = 0; i < iUnregisteredMenus.Count(); i++ )
        {
        TAknUnregisteredMenuData& data( iUnregisteredMenus[ i ] );
        delete data.iMenu;
        data.iMenu = NULL;
        }
    iUnregisteredMenus.Close();
    iUnregisteredObservers.Close();
    delete iRegisterArray;

    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::AknItemActionMenuRegister
// ---------------------------------------------------------------------------
//
AknItemActionMenuRegister::AknItemActionMenuRegister()
    : CCoeStatic( KAknItemActionMenuRegister, KRegisterDestructionPriority ),
    iMenuBarOwner( NULL )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::ConstructL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::ConstructL()
    {
    _AKNTRACE_FUNC_ENTER;

    iRegisterArray = CAknItemActionMenuRegisterArray::NewL();

    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::AppUiSingleClickCompatible
// ---------------------------------------------------------------------------
//
TBool AknItemActionMenuRegister::AppUiSingleClickCompatible()
    {
    _AKNTRACE_FUNC_ENTER;

    TBool isCompatible = EFalse;
    CAknAppUi* appUi = AppUI();
    
    if ( appUi )
        {
        isCompatible = appUi->IsSingleClickCompatible();
        }
    
    _AKNTRACE_FUNC_EXIT;

    return isCompatible;
    }

// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::Instance
// ---------------------------------------------------------------------------
//
AknItemActionMenuRegister* AknItemActionMenuRegister::Instance()
    {
    _AKNTRACE_FUNC_ENTER;

    AknItemActionMenuRegister* instance =
        static_cast<AknItemActionMenuRegister*>(
                CCoeEnv::Static( KAknItemActionMenuRegister ) );
    if ( !instance )
        {
        TRAP_IGNORE( instance = CreateInstanceL() ); 
        }

    _AKNTRACE_FUNC_EXIT;

    return instance;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::DoRegisterCollectionL
// ---------------------------------------------------------------------------
//
CAknItemActionMenu* AknItemActionMenuRegister::DoRegisterCollectionL(
        MAknCollection& aCollectionState )
    {
    _AKNTRACE_FUNC_ENTER;
    
    CAknItemActionMenu* menu( NULL );
    CEikMenuBar* menuBar = FindCurrentMenuBarL();
    menu = RegisterStateToItemActionMenuL( menuBar, aCollectionState );

    _AKNTRACE_FUNC_EXIT;

    return menu;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::DoRegisterMenuBarL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::DoRegisterMenuBarL( CEikMenuBar& aMenuBar )
    {
    _AKNTRACE_FUNC_ENTER;
    
    CAknItemActionMenu* menu( NULL );
    for ( TInt i = 0; i < iUnregisteredMenus.Count(); i++ )
        {
        TAknUnregisteredMenuData& data( iUnregisteredMenus[ i ] );
        if ( data.iOwner ) 
            {
            CEikMenuBar* ownerMenubar( NULL );
            data.iOwner->MopGetObjectNoChaining( ownerMenubar );
            if ( ownerMenubar == &aMenuBar )
                {
                menu = data.iMenu;
                if ( menu )
                    {
                    AddRegisterEntryL( aMenuBar, *menu );
                    iUnregisteredMenus.Remove( i );
                    }
                break;
                }
            }
        }

    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::DoUnregisterMenuBar
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::DoUnregisterMenuBar( CEikMenuBar& aMenuBar )
    {
    _AKNTRACE_FUNC_ENTER;

    iRegisterArray->UnregisterMenuBar( aMenuBar );

    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::DoRegisterItemActionMenuL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::DoRegisterItemActionMenuL(
        CAknItemActionMenu& aItemActionMenu )
    {
    _AKNTRACE_FUNC_ENTER;

    CEikMenuBar* menuBar( NULL );
    for ( TInt i = 0; i < iUnregisteredMenus.Count(); i++ )
        {
        TAknUnregisteredMenuData& data( iUnregisteredMenus[ i ] );
        if ( data.iMenu == &aItemActionMenu )
            {
            if ( data.iOwner ) 
                {
                data.iOwner->MopGetObjectNoChaining( menuBar );
                if ( menuBar )
                    {
                    AddRegisterEntryL( *menuBar, aItemActionMenu );
                    iUnregisteredMenus.Remove( i );
                    }
                }
            break;
            }
        }

    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::DoUnregisterItemActionMenu
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::DoUnregisterItemActionMenu(
        CAknItemActionMenu& aItemActionMenu )
    {
    _AKNTRACE_FUNC_ENTER;

    iRegisterArray->UnregisterItemActionMenu( aItemActionMenu );

    for ( TInt i = 0; i < iUnregisteredMenus.Count(); i++ )
        {
        TAknUnregisteredMenuData& data( iUnregisteredMenus[ i ] );
        if ( data.iMenu == &aItemActionMenu )
            {
            delete data.iMenu;
            iUnregisteredMenus.Remove( i ); 
            break; 
            }
        }

    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::DoRegisterCollectionObserverL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::DoRegisterCollectionObserverL(
        MAknCollectionObserver& aObserver )
    {
    _AKNTRACE_FUNC_ENTER;

    CEikMenuBar* menuBar = FindCurrentMenuBarL();
    if ( !menuBar || !iRegisterArray->RegisterCollectionObserverL(
            *menuBar, aObserver ) )
        {
        TAknUnregisteredObserverData newData( menuBar, 
                aObserver, Owner() );
        
        
        _AKNTRACE( "    Added observer %d", &aObserver );
        iUnregisteredObservers.AppendL( newData );
        }

    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::DoUnregisterCollectionObserver
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::DoUnregisterCollectionObserver(
        MAknCollectionObserver& aObserver )
    {
    _AKNTRACE_FUNC_ENTER;

    iRegisterArray->UnregisterCollectionObserver( aObserver );

    for ( TInt i = 0; i < iUnregisteredObservers.Count(); i++ )
        {
        TAknUnregisteredObserverData& data( iUnregisteredObservers[ i ] );
        if ( &data.iObserver == &aObserver )
            {
            iUnregisteredObservers.Remove( i );
            _AKNTRACE_FUNC_EXIT;

            return;
            }
        }

    for ( TInt i = 0; i < iUnregisteredMenus.Count(); i++ )
        {
        TAknUnregisteredMenuData& data( iUnregisteredMenus[ i ] );
        data.iMenu->RemoveCollectionObserver( aObserver ); 
        }

    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::DialogMenuBar
// ---------------------------------------------------------------------------
//
CEikMenuBar* AknItemActionMenuRegister::DialogMenuBar( CAknAppUi* aAppUi )
    {
    _AKNTRACE_FUNC_ENTER;

    CEikMenuBar* menuBar( NULL );
    // Check if there is an active dialog and fetch its menubar
    if ( aAppUi && aAppUi->IsDisplayingMenuOrDialog() )
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

    _AKNTRACE_FUNC_EXIT;

    return menuBar;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::ViewMenuBar
// ---------------------------------------------------------------------------
//
CEikMenuBar* AknItemActionMenuRegister::ViewMenuBar( CAknAppUi* aAppUi )
    {
    _AKNTRACE_FUNC_ENTER;

    CEikMenuBar* menuBar( NULL );
    CAknView* view = View( aAppUi );
        
    if ( view )
        {
        menuBar = view->MenuBar();
        }

    _AKNTRACE_FUNC_EXIT;

    return menuBar;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::ConstructingObjectMenuBar
// ---------------------------------------------------------------------------
//
CEikMenuBar* AknItemActionMenuRegister::ConstructingObjectMenuBar()
    {
    _AKNTRACE_FUNC_ENTER;

    CEikMenuBar* menuBar( NULL );
    if ( iMenuBarOwner )
        {
        iMenuBarOwner->MopGetObjectNoChaining( menuBar );
        }

    _AKNTRACE_FUNC_EXIT;

    return menuBar;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::OverridingObjectMenuBar
// ---------------------------------------------------------------------------
//
CEikMenuBar* AknItemActionMenuRegister::OverridingObjectMenuBar()
    {
    _AKNTRACE_FUNC_ENTER;

    CEikMenuBar* menuBar( NULL );
    if ( iOverridingMenuBarOwner )
        {
        iOverridingMenuBarOwner->MopGetObjectNoChaining( menuBar );
        }

    _AKNTRACE_FUNC_EXIT;

    return menuBar;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::Owner
// ---------------------------------------------------------------------------
//
MObjectProvider* AknItemActionMenuRegister::Owner() const
    {
    _AKNTRACE_FUNC_ENTER;

    MObjectProvider* owner = NULL;
    CAknAppUi* appUi = AppUI();
    
    if ( iOverridingMenuBarOwner )
        {
        owner = iOverridingMenuBarOwner;
        }
    else
        {
        owner = View( appUi );

        if ( !owner )
            {
            owner = iMenuBarOwner;
            }
        }
    
    if ( !owner )
        {
        owner = appUi;
        }

    __ASSERT_DEBUG( owner, User::Invariant() );
    _AKNTRACE_FUNC_EXIT;

    return owner;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::View
// ---------------------------------------------------------------------------
//
CAknView* AknItemActionMenuRegister::View( CAknAppUi* aAppUi ) const
    {
    _AKNTRACE_FUNC_ENTER;

    CAknView* view = NULL;

    if ( aAppUi )
        {
        // Check if there is an active view
        TVwsViewId uid;
    
        if ( aAppUi->GetActiveViewId( uid ) == KErrNone )
            {
            if ( uid.iAppUid != uid.iViewUid )
                {
                view = static_cast<CAknViewAppUi*>(
                        aAppUi )->View( uid.iViewUid );
                }
            }
        }

    _AKNTRACE_FUNC_EXIT;

    return view;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::AppUI
// ---------------------------------------------------------------------------
//
CAknAppUi* AknItemActionMenuRegister::AppUI()
    {
    _AKNTRACE_FUNC_ENTER;

   CAknAppUi* appUi = NULL;
    CCoeEnv* env = CCoeEnv::Static();
    
    if ( env )
        {
        appUi = static_cast<CAknAppUi*>( env->AppUi() );
        }
    

    _AKNTRACE_FUNC_EXIT;

    return appUi;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::RegisterStateToItemActionMenuL
// ---------------------------------------------------------------------------
//
CAknItemActionMenu* AknItemActionMenuRegister::RegisterStateToItemActionMenuL(
        CEikMenuBar* aMenuBar,
        MAknCollection& aCollectionState )
    {
    _AKNTRACE_FUNC_ENTER;

    CAknItemActionMenu* menu( NULL );

    // View / dialog / appUi menubar was found
    if ( aMenuBar )
        {
        menu = aMenuBar->ItemActionMenu();
        // menubar does not have item action menu -> create one
        if ( !menu )
            {
            menu = CAknItemActionMenu::NewLC( aCollectionState, Owner() );
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
            menu = CAknItemActionMenu::NewLC( aCollectionState, Owner() );
            TAknUnregisteredMenuData newData;
            newData.iOwner = iMenuBarOwner;
            newData.iMenu = menu;
            iUnregisteredMenus.AppendL( newData );
            CleanupStack::Pop( menu );
            }
        }
    if ( menu )
        {
        // Set observers with menubar to menu
        AddObserversToItemActionMenuL( *menu );
        }

    _AKNTRACE_FUNC_EXIT;

    return menu;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::FindCurrentMenuBarL
// ---------------------------------------------------------------------------
//
CEikMenuBar* AknItemActionMenuRegister::FindCurrentMenuBarL()
    {
    _AKNTRACE_FUNC_ENTER;

    CAknAppUi* appUi = AppUI();
    CEikonEnv* eikonEnv( CEikonEnv::Static() );
    TBool isConstructingDialog( EFalse );
    CEikMenuBar* menuBar( NULL );
    
    // If overriding menubar owner is set then it's the one to obey. If the
    // overriding menubar owner doesn't supply a menubar object then there
    // isn't proper one available.
    if ( iOverridingMenuBarOwner )
        {
        _AKNTRACE_FUNC_EXIT;
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
    if ( !menuBar && eikonEnv )
        {
        menuBar = eikonEnv->AppUiFactory()->MenuBar();
        }

    _AKNTRACE_FUNC_EXIT;

    return menuBar;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::AddRegisterEntryL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::AddRegisterEntryL(
        CEikMenuBar& aMenuBar, CAknItemActionMenu& aItemActionMenu )
    {
    _AKNTRACE_FUNC_ENTER;

    aMenuBar.SetItemActionMenu( &aItemActionMenu );
    iRegisterArray->AddEntryL( aMenuBar, aItemActionMenu );
    AddObserversToItemActionMenuL( aItemActionMenu );

    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::AddObserversToItemActionMenuL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::AddObserversToItemActionMenuL(
        CAknItemActionMenu& aItemActionMenu )
    {
    _AKNTRACE_FUNC_ENTER;

    TInt i = 0;
    
    while ( i  < iUnregisteredObservers.Count() )
        {
        TAknUnregisteredObserverData& data( iUnregisteredObservers[i] );
        
        // Register to item action menu if observer's owner matches item action
        // menu's owner.
        if ( data.iOwner == aItemActionMenu.Owner() )
            {
            _AKNTRACE( "    Observer %d added to item action menu", &data.iObserver );

            aItemActionMenu.RegisterCollectionObserverL(
                    data.iObserver );
            
            iUnregisteredObservers.Remove( i );
            }
        else
            {
            ++i;
            }
        }

    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::CreateInstanceL
// ---------------------------------------------------------------------------
//
AknItemActionMenuRegister* AknItemActionMenuRegister::CreateInstanceL()
    {
    _AKNTRACE_FUNC_ENTER;

    AknItemActionMenuRegister* instance = NULL; 
    instance = new ( ELeave ) AknItemActionMenuRegister();
    CleanupStack::PushL( instance );
    instance->ConstructL();
    CleanupStack::Pop( instance );

    _AKNTRACE_FUNC_EXIT;
    return instance;
    }

// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::DoSetConstructingMenuBarOwnerL
// ---------------------------------------------------------------------------
//
void AknItemActionMenuRegister::DoSetConstructingMenuBarOwnerL( 
        MObjectProvider* aMenuBarOwner )
    {
    if ( aMenuBarOwner )
        {
        CEikDialog* dialog( NULL );
        aMenuBarOwner->MopGetObjectNoChaining( dialog );
        // Get information if the constructing menu bar owner is a dialog  
        // and store it to iIsConstructingDialog
        if ( dialog )
            {
            iIsConstructingDialog = ETrue; 
            }
        }
    else if ( !aMenuBarOwner && iIsConstructingDialog )
        {
        // When setting constructing menubar owner to NULL from a dialog check
        // if there is item with the same menubar owner in iUnregisteredMenus 
        // and try to find correct menubar for it.
        for ( TInt i = 0; i < iUnregisteredMenus.Count(); i++ )
            {
            TAknUnregisteredMenuData& data( iUnregisteredMenus[ i ] );
            if ( data.iOwner == iMenuBarOwner ) 
                {
                data.iOwner = iMenuBarOwner = NULL; 
                CEikMenuBar* menuBar = FindCurrentMenuBarL(); 
                if ( menuBar )
                    {
                    AddRegisterEntryL( *menuBar, *data.iMenu );
                    iUnregisteredMenus.Remove( i );
                    }
                iIsConstructingDialog = EFalse; 
                return; 
                }
            }
        }
    iMenuBarOwner = aMenuBarOwner;
    }

// ---------------------------------------------------------------------------
// AknItemActionMenuRegister::TAknUnregisteredObserverData
// ::TAknUnregisteredObserverData
// ---------------------------------------------------------------------------
//
AknItemActionMenuRegister::TAknUnregisteredObserverData::\
    TAknUnregisteredObserverData(
        CEikMenuBar* aMenuBar, MAknCollectionObserver& aObserver,
        MObjectProvider* aOwner )
    : iMenuBar( aMenuBar ),
    iObserver( aObserver ),
    iOwner( aOwner )
    {
    }

// End of File

