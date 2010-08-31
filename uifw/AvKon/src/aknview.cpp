/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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

// AknView.cpp
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// INCLUDE FILES
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikdefmacros.h>
#endif
#include "aknview.h"
#include "aknViewAppUi.h"
#include "AknPanic.h"
#include "avkon.hrh"
#include "aknenv.h"
#include <eikenv.h>
#include <eikapp.h>
#include <barsread.h>
#include <eikmenub.h>
#include <eikcba.h>
#include <eikmop.h>
#include <eikcolib.h>
#include <akntoolbar.h>
#include <AknPriv.hrh>

#ifdef RD_SCALABLE_UI_V2
#include <akntouchpane.h>
#endif // RD_SCALABLE_UI_V2

#include <AknUtils.h>
#include "aknitemactionmenuregister.h"

// MODULE DATA STRUCTURES
enum TAknViewFlags
	{
	EAknViewForeground
	};


// CLASS DECLARATION

/**
* Extension class.
*/
NONSHARABLE_CLASS(CAknViewExtension) : public CBase
    {
    public:
        static CAknViewExtension* NewL(CAknView* aView);
        ~CAknViewExtension();

    private:
        CAknViewExtension(CAknView* aView);
        void ConstructL();
        void ChangeToolbar( CAknToolbar* aOldToolbar ); 

    public:
        void CreateToolbarL( TInt aResourceId );
        void PrepareToolbar();
        void DestroyToolbars();
        void StopDisplayingToolbar( TBool aAlways );
        void StopDisplayingFixedToolbar();
        CAknToolbar* Toolbar() const;
        void SetToolbar( CAknToolbar* aToolbar ); 
        void CreateAndSetToolbarL( TInt aResourceId ); 
        
    public:
        TBool iToolbarVisible; 
        TBool iToolbarFocusing; 
        TBool iViewActivated;
    private: // data
        CAknToolbar* iToolbar;
        CAknToolbar* iFixedToolbar;
        CAknView* iView;
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknViewExtension::CAknViewExtension
// C++ default constructor.
// -----------------------------------------------------------------------------
//
CAknViewExtension::CAknViewExtension(CAknView* aView)
: iView(aView)
	{
	}

// -----------------------------------------------------------------------------
// CAknViewExtension::~CAknViewExtension
// Destructor.
// -----------------------------------------------------------------------------
//
CAknViewExtension::~CAknViewExtension()
    {
    DestroyToolbars();
    }

// -----------------------------------------------------------------------------
// CAknViewExtension::NewL
// Symbian two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknViewExtension* CAknViewExtension::NewL(CAknView* aView)
	{
	CAknViewExtension* ext = new ( ELeave ) CAknViewExtension(aView);
	CleanupStack::PushL( ext );
	ext->ConstructL();
	CleanupStack::Pop(); // ext
	return ext;
	}

// -----------------------------------------------------------------------------
// CAknViewExtension::ConstructL
// Symbian 2nd stage constructor.
// -----------------------------------------------------------------------------
//
void CAknViewExtension::ConstructL()
	{
	}
	

// -----------------------------------------------------------------------------
// CAknViewExtension::CreateToolbarL
// toolbar is created from the resource files.
// -----------------------------------------------------------------------------
//
void CAknViewExtension::CreateToolbarL( TInt aResourceId )
    {
    if ( aResourceId )
    	{
    	if ( !iToolbar )
        	{
            iToolbar = CAknToolbar::NewL( aResourceId );
            iToolbar->SetMopParent( iView );
    
#ifdef RD_SCALABLE_UI_V2
            CAknTouchPane* touchPane = static_cast<CEikAppUiFactory*>( 
                CEikonEnv::Static()->AppUiFactory() )->TouchPane(); 
            if ( touchPane )
                {
                iToolbar->SetObserver( touchPane );
                }

            // Checking if toolbar is fixed so setting it to iFixedToolbar
            if ( iToolbar->ToolbarFlags() & KAknToolbarFixed )
                {
                iFixedToolbar = iToolbar; 
                iToolbar = NULL; 
                }

#endif // RD_SCALABLE_UI_V2
            }
    	}
    }
    
// -----------------------------------------------------------------------------
// CAknViewExtension::PrepareToolbar
// application informed and the old toolbar is hidden
// -----------------------------------------------------------------------------
//
void CAknViewExtension::PrepareToolbar()
    {
    CAknToolbar* oldCurrentToolbar = static_cast<CEikAppUiFactory*>( 
        CEikonEnv::Static()->AppUiFactory() )->CurrentPopupToolbar();

    // set view specific toolbar	
    static_cast<CEikAppUiFactory*>( 
        CEikonEnv::Static()->AppUiFactory() )->SetViewPopupToolbar( iToolbar );

    CAknToolbar* newToolbar = static_cast<CEikAppUiFactory*>( 
        CEikonEnv::Static()->AppUiFactory() )->CurrentPopupToolbar();

    if ( oldCurrentToolbar && oldCurrentToolbar != newToolbar )
        {
        oldCurrentToolbar->SetToolbarVisibility( EFalse );
        }
    
    if ( newToolbar )
        {
#ifdef RD_SCALABLE_UI_V2
        if ( !iToolbarFocusing && iToolbarVisible )
            {
            newToolbar->SetToolbarVisibility( ETrue, EFalse ); 
            }
        else 
#endif //RD_SCALABLE_UI_V2
            {
            newToolbar->SetToolbarVisibility( iToolbarVisible ); 
            }
        }

#ifdef RD_SCALABLE_UI_V2
        
    // Here is code for fixed toolbar
    CAknToolbar* oldFixedToolbar = static_cast<CEikAppUiFactory*>( 
        CEikonEnv::Static()->AppUiFactory() )->CurrentFixedToolbar();

    // set view specific fixed toolbar	
    static_cast<CEikAppUiFactory*>( 
        CEikonEnv::Static()->AppUiFactory() )->SetViewFixedToolbar( iFixedToolbar );

    CAknToolbar* newFixedToolbar = static_cast<CEikAppUiFactory*>( 
        CEikonEnv::Static()->AppUiFactory() )->CurrentFixedToolbar();

    if ( newFixedToolbar )
        {
        newFixedToolbar->HandleResourceChange( KAknToolbarSetVisible );
        }

    if ( oldFixedToolbar && oldFixedToolbar != newFixedToolbar )
        {
        
        if ( newFixedToolbar && newFixedToolbar->ToolbarFlags() & KAknToolbarDefault )
        	{
        	oldFixedToolbar->HandleResourceChange( KAknToolbarSetHiddenAndDrawBackground );
        	return;
        	}
        
        oldFixedToolbar->HandleResourceChange( KAknToolbarSetHidden );         
        }
#endif 
    }
    
// -----------------------------------------------------------------------------
// CAknViewExtension::DestroyToolbar
// toolbar is created from the resource files.
// -----------------------------------------------------------------------------
//
void CAknViewExtension::DestroyToolbars()
    {
    delete iToolbar;
    iToolbar = NULL;
    
    static_cast<CEikAppUiFactory*>( 
        CEikonEnv::Static()->AppUiFactory() )->SetViewPopupToolbar( NULL );

    delete iFixedToolbar; 
    iFixedToolbar = NULL; 
    
    }
    
    
// -----------------------------------------------------------------------------
// CAknViewExtension::StopDisplayingToolbar
// toolbar is hidden.
// -----------------------------------------------------------------------------
//
void CAknViewExtension::StopDisplayingToolbar( TBool aAlways )
    {
    if ( iToolbar )
        {
        if ( aAlways || ( iToolbar->ToolbarFlags() & KAknToolbarFixed ) )
            {
            iToolbar->SetToolbarVisibility( EFalse );
            }
        }
    }
    
// -----------------------------------------------------------------------------
// CAknViewExtension::TryDisplayToolbar
// Toolbar is hidden.
// -----------------------------------------------------------------------------
//
void CAknViewExtension::StopDisplayingFixedToolbar()
    {
    if ( iFixedToolbar )
        {
        iFixedToolbar->SetToolbarVisibility( EFalse );
        }
    }
    
// -----------------------------------------------------------------------------
// CAknViewExtension::Toolbar
// Return toolbar object, either floating of fixed
// -----------------------------------------------------------------------------
//
CAknToolbar* CAknViewExtension::Toolbar() const
    {
    if ( iToolbar )
        {
        return iToolbar;
        }
    else
        {
        return iFixedToolbar; 
        }
    }



// -----------------------------------------------------------------------------
// CAknViewExtension::SetToolbar
// Sets toolbar for view
// -----------------------------------------------------------------------------
//
void CAknViewExtension::SetToolbar( CAknToolbar* aToolbar )
    {
    CAknToolbar* oldToolbar = NULL; 
    if ( iToolbar )
        {
        oldToolbar = iToolbar;
        iToolbar = NULL;
        }
    if ( iFixedToolbar )
        {
        oldToolbar = iFixedToolbar; 
        iFixedToolbar = NULL; 
        }
    if ( aToolbar && aToolbar->ToolbarFlags() & KAknToolbarFixed )
        {
        iFixedToolbar = aToolbar; 
        }
    else if ( aToolbar )
        {
        iToolbar = aToolbar; 
        }

    ChangeToolbar( oldToolbar ); 
    }

// -----------------------------------------------------------------------------
// CAknViewExtension::CreateAndSetToolbar
// Creates and sets toolbar for the view
// -----------------------------------------------------------------------------
//
void CAknViewExtension::CreateAndSetToolbarL( TInt aResourceId )
    {
    CAknToolbar* oldToolbar = NULL; 
    if ( iToolbar )
        {
        oldToolbar = iToolbar;
        iToolbar = NULL;  
        }
    if ( iFixedToolbar )
        {
        oldToolbar = iFixedToolbar; 
        iFixedToolbar = NULL; 
        }
        
    CreateToolbarL( aResourceId ); 

    ChangeToolbar( oldToolbar ); 
    }


// -----------------------------------------------------------------------------
// CAknViewExtension::ChangeToolbar
// Changes current toolbar. If old toolbar was visible, then the new will 
// also be shown. 
// -----------------------------------------------------------------------------
//
void CAknViewExtension::ChangeToolbar( CAknToolbar* aOldToolbar )
    {
    TBool shown(EFalse); 
    if ( aOldToolbar )
        {
        if ( aOldToolbar->IsShown() )
            {
            shown = ETrue; 
            }
        }

    if ( iToolbar )
        {
        static_cast<CEikAppUiFactory*>( 
            CEikonEnv::Static()->AppUiFactory() )->SetViewPopupToolbar( iFixedToolbar );

        if ( shown )
            {
#ifdef RD_SCALABLE_UI_V2
            iToolbar->SetToolbarVisibility( ETrue, iToolbarFocusing ); 
#endif //RD_SCALABLE_UI_V2
            iToolbar->SetToolbarVisibility( ETrue ); 
            }
        }
    if ( iFixedToolbar )
        {
        static_cast<CEikAppUiFactory*>( 
            CEikonEnv::Static()->AppUiFactory() )->SetViewFixedToolbar( iFixedToolbar );
        if ( shown )
            {
            iFixedToolbar->HandleResourceChange( KAknToolbarSetVisible );
            }
        }

    delete aOldToolbar; 
    aOldToolbar = NULL; 
    }

// -----------------------------------------------------------------------------
// CAknView::CAknView
// C++ default constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknView::CAknView() : iCoeEnv( CCoeEnv::Static() ), 
  iAppUi( (CAknViewAppUi*)(CEikonEnv::Static()->EikAppUi()) )
	{
	}

// -----------------------------------------------------------------------------
// CAknView::~CAknView
// Destructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknView::~CAknView()
	{
	if ( iMenu )
		{
		iAppUi->RemoveFromStack( iMenu );
		delete iMenu;
		}

	delete iCba;
	delete iExtension;
	}

// -----------------------------------------------------------------------------
// CAknView::BaseConstructL
// Second-phase base class constructor. Must be called from a derived classes
// second stage construction function.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::BaseConstructL( TInt aResId )
	{
	iExtension = CAknViewExtension::NewL( this );

	if ( aResId )
		{
		// If this assert fails, you have probably constructed your view twice
		ASSERT(!iViewInfo.iMenu && !iViewInfo.iCba && !iViewInfo.iHotKeys);

        TResourceReader r;
        iCoeEnv->CreateResourceReaderLC( r, aResId );

        iViewInfo.iVersion = r.ReadInt8();
        iViewInfo.iHotKeys = r.ReadInt32();
        iViewInfo.iMenu = r.ReadInt32();
        iViewInfo.iCba = r.ReadInt32();
        iViewInfo.iToolbar = r.ReadInt32();
        r.ReadInt32(); // extension
        CleanupStack::PopAndDestroy(); // r
        }
        
    Extension()->CreateToolbarL( iViewInfo.iToolbar );

    if ( iViewInfo.iMenu )
        {
        AknItemActionMenuRegister::SetConstructingMenuBarOwnerL( this );
        }
    }

// -----------------------------------------------------------------------------
// CAknView::AppUi
// Accessor for the app UI as a CAknViewAppUi.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknViewAppUi* CAknView::AppUi() const
	{
	return iAppUi;
	}

// -----------------------------------------------------------------------------
// CAknView::ActivateViewL
// Activates any view in the product.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::ActivateViewL( const TVwsViewId& aViewId )
	{
	// this is here to assert that BaseConstructL has been called properly.
	Extension();

	iAppUi->ActivateViewL( aViewId );
	}

// -----------------------------------------------------------------------------
// CAknView::ActivateViewL
// Activates any view in the product and passes a message.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::ActivateViewL( const TVwsViewId& aViewId, TUid aCustomMessageId, const TDesC8& aCustomMessage )
	{
	iAppUi->ActivateViewL( aViewId, aCustomMessageId, aCustomMessage );
	}

// -----------------------------------------------------------------------------
// CAknView::StatusPane
// Status pane accessor method.
// -----------------------------------------------------------------------------
//
EXPORT_C CEikStatusPane* CAknView::StatusPane() const
	{
	return iAppUi->StatusPane();
	}

// -----------------------------------------------------------------------------
// CAknView::Cba
// CBA accessor method. This returns view's CBA if there is one. Otherwise UI's
// CBA is returned.
// -----------------------------------------------------------------------------
//
EXPORT_C CEikButtonGroupContainer* CAknView::Cba() const
	{
	if ( iCba )
	    {
		return iCba;
	    }

	return iAppUi->Cba();
	}

// -----------------------------------------------------------------------------
// CAknView::HandleStatusPaneSizeChange
// Event handler for status pane size changes. The default implementation is
// empty.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::HandleStatusPaneSizeChange()
	{
	}

// -----------------------------------------------------------------------------
// CAknView::SetEmphasis
// Menu emphasis function.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::SetEmphasis( CCoeControl* aMenuControl, TBool aEmphasis )
	{
	iAppUi->UpdateStackedControlFlags( aMenuControl, aEmphasis? 0: ECoeStackFlagRefusesFocus, ECoeStackFlagRefusesFocus );
	iAppUi->HandleStackChanged();
	}

// -----------------------------------------------------------------------------
// CAknView::ViewActivatedL
// Handles a view activation event from viewserv.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::ViewActivatedL( const TVwsViewId& aPrevViewId, TUid aCustomMessageId, const TDesC8& aCustomMessage )
	{
	// this is here to assert that BaseConstructL has been called properly.
	Extension();

	iAppUi->ViewActivatedL( this, aPrevViewId, aCustomMessageId, aCustomMessage );
	}

// -----------------------------------------------------------------------------
// CAknView::ViewDeactivatedL
// Handles a view deactivation event from viewserv.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::ViewDeactivated()
	{
	iAppUi->ViewDeactivated(this);
	}

// -----------------------------------------------------------------------------
// CAknView::AknViewActivatedL
// Called by the application UI when a view is activated.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::AknViewActivatedL( const TVwsViewId& aPrevViewId, TUid aCustomMessageId, const TDesC8& aCustomMessage )
	{
	ConstructMenuAndCbaL( ETrue );
    if ( !Extension()->iViewActivated )
        {
        // Reset menu bar owner when view first activated
        AknItemActionMenuRegister::SetConstructingMenuBarOwnerL( NULL );
        Extension()->iViewActivated = ETrue;
        }
	
	Extension()->PrepareToolbar();

	DoActivateL( aPrevViewId, aCustomMessageId, aCustomMessage );

#ifdef RD_SCALABLE_UI_V2
    if ( iAvkonAppUi->TouchPane() )
        {
        iAvkonAppUi->TouchPane()->RefreshL();
        }
#endif // RD_SCALABLE_UI_V2

	ProcessForegroundEventL( ETrue );
	}

// -----------------------------------------------------------------------------
// CAknView::AknViewActivatedL
// Called by the application UI when a view is deactivated.
// -----------------------------------------------------------------------------
//
void CAknView::AknViewDeactivated()
	{
	TRAP_IGNORE( ProcessForegroundEventL( EFalse ) );

    Extension()->StopDisplayingToolbar( EFalse );

	DoDeactivate();

	if ( iCba )
		{
		iCba->MakeVisible( EFalse );
		}
	}

// -----------------------------------------------------------------------------
// CAknView::ViewScreenDeviceChangedL
// Screen device changed function from viewserv.
// -----------------------------------------------------------------------------
//
EXPORT_C TVwsViewIdAndMessage CAknView::ViewScreenDeviceChangedL()
	{
	TVwsViewIdAndMessage r;
	return r;
	}

// -----------------------------------------------------------------------------
// CAknView::ViewId
// Returns the full view Id for this view.
// -----------------------------------------------------------------------------
//
EXPORT_C TVwsViewId CAknView::ViewId() const
	{
	return TVwsViewId( iAppUi->Application()->AppDllUid(), Id() );
	}

// -----------------------------------------------------------------------------
// CAknView::MenuBar
// Menu bar accessor method. This returns the views menu if available, otherwise
// applications menu bar is returned.
// -----------------------------------------------------------------------------
//
EXPORT_C CEikMenuBar* CAknView::MenuBar() const
	{
	if ( iMenu )
	    {
		return iMenu;
	    }

	return iEikonEnv->AppUiFactory()->MenuBar();
	}

// -----------------------------------------------------------------------------
// CAknView::ClientRect
// Calculates the client rectangle of the view, taking the applications client
// rectangle and the views CBA into account.
// -----------------------------------------------------------------------------
//
EXPORT_C TRect CAknView::ClientRect() const
	{
#ifdef RD_SPLIT_VIEW
	TRect rect( iAppUi->ViewRect( Id() ) );
#else
    TRect rect( iAppUi->ClientRect() );
#endif // RD_SPLIT_VIEW
	
#ifdef RD_SPLIT_VIEW
	if ( !iAppUi->SplitViewActive() && iCba )
#else
    if ( iCba )	
#endif // RD_SPLIT_VIEW
        {
		iCba->SetBoundingRect( TRect() );
		iCba->ReduceRect( rect );
        }

#ifdef RD_SCALABLE_UI_V2
    // touch pane needs to be reduced here, otherwise cba area is not taken
    // into account
	if ( iAppUi->TouchPane() )
	    {
	    iAppUi->TouchPane()->ReduceRect( rect );
	    }
#endif // RD_SCALABLE_UI_V2	    
            
	return rect;
	}

// -----------------------------------------------------------------------------
// CAknView::ProcessCommandL
// Handles menu launching command and forwards the rest to HandleCommandL().
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::ProcessCommandL( TInt aCommand )
	{
	// most of the contents are based on CEikAppUi::ProcessCommandL()
	if ( iMenu )
	    {
		iMenu->StopDisplayingMenuBar();
	    }
	    
	// Test for 'options' command
	if ( aCommand == EAknSoftkeyOptions )
		{
		if ( iMenu )
		    {
			iMenu->TryDisplayMenuBarL();
		    }
		else
		    {
			iEikonEnv->AppUiFactory()->MenuBar()->TryDisplayMenuBarL();
		    }
		    
		return;
		}
	if (aCommand == EAknSoftkeyContextOptions)
		{
		if ( iMenu )
            {
            iMenu->TryDisplayContextMenuBarL();
            }
		else
            {
            iEikonEnv->AppUiFactory()->MenuBar()->TryDisplayContextMenuBarL();
            }
		    
		return;
		}
		
	if ( aCommand == EAknCmdExit )
		{
		Extension()->StopDisplayingToolbar( ETrue );
		CAknEnv::RunAppShutter();
		return;
		}
		
	if ( aCommand != EEikCmdCanceled )
	    {
		HandleCommandL( aCommand );
	    }
	}

// -----------------------------------------------------------------------------
// CAknView::HandleCommandL
// Command handling function intended for overriding by derived classes.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::HandleCommandL( TInt /*aCommand*/ )
	{
	}

// -----------------------------------------------------------------------------
// CAknView::StopDisplayingMenuBar
// Dismisses the menu bar.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::StopDisplayingMenuBar()
	{
	if ( iMenu )
	    {
		iMenu->StopDisplayingMenuBar();
	    }
	}

// -----------------------------------------------------------------------------
// CAknView::HandleForegroundEventL
// Called by the framework when view's foreground status changes. The default
// implementation is empty.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::HandleForegroundEventL( TBool /*aForeground*/ )
	{
	}

// -----------------------------------------------------------------------------
// CAknView::Reserved_MtsmPosition
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::Reserved_MtsmPosition()
	{
	}

// -----------------------------------------------------------------------------
// CAknView::Reserved_MtsmObject
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::Reserved_MtsmObject()
	{
	}

// -----------------------------------------------------------------------------
// CAknView::IsForeground
// Checks if the view is on foreground.
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknView::IsForeground() const
	{
	return iFlags[EAknViewForeground];
	}

// -----------------------------------------------------------------------------
// CAknView::ProcessForegroundEventL
// Called by the application UI when view's foreground status changes.
// -----------------------------------------------------------------------------
//
void CAknView::ProcessForegroundEventL( TBool aForeground )
	{
	if ( !COMPARE_BOOLS( aForeground, iFlags[EAknViewForeground] ) )
		{
		iFlags.Assign( EAknViewForeground, aForeground );
		HandleForegroundEventL( aForeground );
		}
	}

// -----------------------------------------------------------------------------
// CAknView::MopSupplyObject
// Retrieves an object of the given type.
// -----------------------------------------------------------------------------
//
EXPORT_C TTypeUid::Ptr CAknView::MopSupplyObject( TTypeUid aId )
	{
	return SupplyMopObject( aId, iCba, iMenu );
	}

// -----------------------------------------------------------------------------
// CAknView::MopNext
// Returns the parent object (application UI).
// -----------------------------------------------------------------------------
//
EXPORT_C MObjectProvider* CAknView::MopNext()
	{
	return iAppUi;
	}

// -----------------------------------------------------------------------------
// CAknView::ConstructMenuAndCbaEarlyL
// Constructs both menu bar and CBA but does not make them visible.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::ConstructMenuAndCbaEarlyL()
	{
	ConstructMenuAndCbaL( EFalse );
	}

// -----------------------------------------------------------------------------
// CAknView::ConstructMenuAndCbaL
// Constructs both menu bar and CBA.
// -----------------------------------------------------------------------------
//
void CAknView::ConstructMenuAndCbaL( TBool aVisible )
	{
	if ( !iMenu )
		{
		if ( iViewInfo.iMenu )
			{
			CEikMenuBar* menu = new ( ELeave ) CEikMenuBar;
			CleanupStack::PushL( menu );
			menu->ConstructL( this, iViewInfo.iHotKeys, iViewInfo.iMenu );
			iAppUi->AddToStackL( *this, menu, ECoeStackPriorityMenu, ECoeStackFlagRefusesFocus );
			CleanupStack::Pop(); // menu
			iMenu = menu;
			}
		}

	if ( iCba )
		{
		if ( aVisible )
			{
			iCba->DrawableWindow()->SetOrdinalPosition( 0 );
			iCba->MakeVisible( ETrue );
			iCba->DrawNow(); // This is needed because problems if TRANSPARENCY is set, see MTVN-6HXCN4
			}
		}
	else
		{
		if ( iViewInfo.iCba != 0 )
			{
				CEikButtonGroupContainer* bgc( CEikButtonGroupContainer::NewL(CEikButtonGroupContainer::ECba,
				CEikButtonGroupContainer::EHorizontal, this, iViewInfo.iCba ) );
			CleanupStack::PushL( bgc );
			bgc->SetBoundingRect( iAppUi->ClientRect() );
			// cba needs to be placed on the view stack instead of the application stack
			CEikCba* cba( static_cast<CEikCba*>( bgc->ButtonGroup() ) ); // downcast from MEikButtonGroup
			iEikonEnv->EikAppUi()->RemoveFromStack( cba ); // remove from the current app ui stack
			iAppUi->AddToStackL( *this, cba, ECoeStackPriorityCba, ECoeStackFlagRefusesFocus );
			CleanupStack::Pop(); // bgc
			iCba = bgc;
			iCba->MakeVisible( aVisible );
			}
		}
	}

// -----------------------------------------------------------------------------
// CAknView::HandleViewRectChange
// Called by the framework when view's rectangle changes. The default 
// implementation is empty.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::HandleViewRectChange()
    {
    }
    
// -----------------------------------------------------------------------------
// CAknView::Redraw
// Orders the view to redraw its area. The default implementation is empty.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::Redraw() const
    {
    }

// -----------------------------------------------------------------------------
// CAknView::Extension
// Asserts that extension object has been created.
// -----------------------------------------------------------------------------
//
CAknViewExtension* CAknView::Extension() const
    {
    __ASSERT_ALWAYS( iExtension, Panic( EAknPanicObjectNotFullyConstructed ) );
    return iExtension;
    }


// -----------------------------------------------------------------------------
// CAknView::Toolbar
// -----------------------------------------------------------------------------
//
EXPORT_C CAknToolbar* CAknView::Toolbar() const
    {
    return Extension()->Toolbar();
    }

// -----------------------------------------------------------------------------
// CAknView::StopDisplayingToolbar
// Hides the toolbar if it is visible
// -----------------------------------------------------------------------------
//  
EXPORT_C void CAknView::StopDisplayingToolbar()
    {
    Extension()->StopDisplayingToolbar( ETrue );
    }

// -----------------------------------------------------------------------------
// CAknView::ToolbarShownOnViewActivation
// 
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknView::ToolbarShownOnViewActivation() const
    {
    return Extension()->iToolbarVisible;
    }

// -----------------------------------------------------------------------------
// CAknView::ShowToolbarOnViewActivation
// Sets value to determine if toolbar is shown on view activation
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::ShowToolbarOnViewActivation( TBool aVisible )
    {
    Extension()->iToolbarVisible = aVisible;
    }

// -----------------------------------------------------------------------------
// CAknView::SaveToolbarStatus
// Saves toolbar visibility and focusing values
// -----------------------------------------------------------------------------
//
void CAknView::SaveToolbarStatus( TBool aVisible, TBool aFocused )
    {
    Extension()->iToolbarVisible = aVisible;
    Extension()->iToolbarFocusing = aFocused;
    }

// -----------------------------------------------------------------------------
// CAknView::SetToolbar
// Using this the applications can set new toolbar for the view. Old is deleted.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::SetToolbar( CAknToolbar* aToolbar )
    {
    Extension()->SetToolbar( aToolbar ); 
    }


// -----------------------------------------------------------------------------
// CAknView::CreateAndSetToolbarL
// Using this the applications can set new toolbar for the view. Old is deleted.
// Creates a toolbar with the resource id and then sets it to view toolbar.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknView::CreateAndSetToolbarL( TInt aResourceId )
    {
    Extension()->CreateAndSetToolbarL( aResourceId ); 
    }

// End of File
