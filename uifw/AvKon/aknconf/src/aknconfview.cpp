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
* Description:  AknConf view
*
*/

// INCLUDE FILES
#include <aknViewAppUi.h>
#include <aknconf.rsg>

#include "aknconfappui.h"
#include "aknconfsettinglist.h"
#include "aknconfgesturesettinglist.h"
#include "aknconfphysicssettinglist.h"
#include "aknconfview.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknConfView::CAknConfView()
// -----------------------------------------------------------------------------
//
CAknConfView::CAknConfView( const TInt aViewId )
    :
    iSettingList( NULL ),
    iId( aViewId )
    {
    }


// ----------------------------------------------------------------------------
// CAknConfView::ConstructL()
// Symbian 2nd phase constructor.
// ----------------------------------------------------------------------------
void CAknConfView::ConstructL( TInt aResId )
    {
    BaseConstructL( aResId );

    // Create container
    if ( iId == KPhysicsViewUid )
        {
        iSettingList = CAknConfPhysicsSettingList::NewL();
        }
    else
        {
        iSettingList = CAknConfGestureSettingList::NewL();
        }
    // Destructor will delete iSettingList.
    iSettingList->SetMopParent( this );
    iSettingList->ActivateL();
    iSettingList->MakeVisible( EFalse );
    }


// -----------------------------------------------------------------------------
// CAknConfView::~CAknConfView()
// -----------------------------------------------------------------------------
//
CAknConfView::~CAknConfView()
    {
    delete iSettingList;
    }


// ----------------------------------------------------------------------------
// CAknConfView::Id()
// Return Uid.
// ----------------------------------------------------------------------------
TUid CAknConfView::Id() const
    {
    return TUid::Uid( iId );
    }


// ----------------------------------------------------------------------------
// CAknConfView::HandleCommandL().
// Takes care of command handling.
// ----------------------------------------------------------------------------
void CAknConfView::HandleCommandL( TInt aCommand )
    {
    if ( aCommand == EResetValues )
        {
        iSettingList->ResetValues();
        }
    else
        {
        AppUi()->HandleCommandL( aCommand );
        }
    }


// ----------------------------------------------------------------------------
// CAknConfView::DoActivateL().
// Handles the view activation.
// ----------------------------------------------------------------------------
void CAknConfView::DoActivateL( const TVwsViewId& /*aPrevViewId*/,
                                      TUid /*aCustomMessageId*/, 
                                      const TDesC8& /*aCustomMessage*/ )
    {
    if ( iSettingList )
        {
        AppUi()->AddToStackL( iSettingList );
        iSettingList->SetRect( ClientRect() );
        iSettingList->MakeVisible( ETrue );
        }
    CAknConfAppUi* appUi = static_cast<CAknConfAppUi*>( AppUi() );
    if ( appUi )
        {
        appUi->SetTabIndex( iId );
        }
    }


// ----------------------------------------------------------------------------
// CAknConfView::DoDeactivate()
// Handles the view deactivation.
// ----------------------------------------------------------------------------
void CAknConfView::DoDeactivate()
    {
    if ( iSettingList && iSettingList->IsVisible() )
        {
        iSettingList->MakeVisible( EFalse );
        AppUi()->RemoveFromStack( iSettingList );
        }
    }


// ----------------------------------------------------------------------------
// CAknConfView::DynInitMenuPaneL()
// This function is called by the UIKON framework just before it displays
// a menu pane. Its default implementation is empty, and by overriding it,
// the application can set the state of menu items dynamically according
// to the state of application data.
// ----------------------------------------------------------------------------
void CAknConfView::DynInitMenuPaneL(
        TInt aResourceId,
        CEikMenuPane* aMenuPane )
    {
    if ( aResourceId == R_MENU && aMenuPane )
        {
        aMenuPane->SetItemDimmed( KPhysicsViewUid, EFalse );
        aMenuPane->SetItemDimmed( KGestureViewUid, EFalse );
        aMenuPane->SetItemDimmed( iId, ETrue );
        }
    }

// End of File
