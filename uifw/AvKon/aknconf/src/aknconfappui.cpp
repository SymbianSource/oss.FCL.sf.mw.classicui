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
* Description:  CAknConfAppUi implementation
 *
*/


// INCLUDE FILES
#include <avkon.hrh>
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
#include <aknnavide.h>
#include <akntabgrp.h>
#include <StringLoader.h>

#include <aknconf.rsg>

#include "aknconf.hrh"
#include "aknconf.pan"
#include "aknconfapplication.h"
#include "aknconfappui.h"
#include "aknconfview.h"

const TInt KPhysicsTabIndex( 0 );
const TInt KGestureTabIndex( 1 );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknConfAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CAknConfAppUi::ConstructL()
    {
    // Initialise app UI with standard value.
    BaseConstructL( CAknAppUi::EAknEnableSkin );

    CEikStatusPane* statusPane = StatusPane();
    if ( statusPane )
        {
        CAknNavigationControlContainer* naviPane =
            static_cast<CAknNavigationControlContainer*>(
                statusPane->ControlL( TUid::Uid( EEikStatusPaneUidNavi ) ) );
        if ( naviPane )
            {
            iDecorator = naviPane->ResourceDecorator();
            static_cast<CAknTabGroup*>(
                    iDecorator->DecoratedControl() )->SetObserver( this ); 
            }
        }

    CAknConfView* physicsView = 
        new( ELeave ) CAknConfView( KPhysicsViewUid );
    CleanupStack::PushL( physicsView );
    physicsView->ConstructL( R_PHYSICS_VIEW );
    CleanupStack::Pop( physicsView );
    AddViewL( physicsView );  // transfer ownership to CAknViewAppUi
    
    CAknConfView* gestureView = 
        new( ELeave ) CAknConfView( KGestureViewUid );
    CleanupStack::PushL( gestureView );
    gestureView->ConstructL( R_GESTURE_VIEW );
    CleanupStack::Pop( gestureView );
    AddViewL( gestureView );  // transfer ownership to CAknViewAppUi

    iCurrentViewId = physicsView->Id().iUid;

    }
// -----------------------------------------------------------------------------
// CAknConfAppUi::CAknConfAppUi()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CAknConfAppUi::CAknConfAppUi()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CAknConfAppUi::~CAknConfAppUi()
// Destructor.
// -----------------------------------------------------------------------------
//
CAknConfAppUi::~CAknConfAppUi()
    {
    delete iDecorator;
    }


// -----------------------------------------------------------------------------
// CAknConfAppUi::SetTabIndex
// -----------------------------------------------------------------------------
//
void CAknConfAppUi::SetTabIndex( TInt aViewId )
    {
    TInt tabIndex( 0 );
    if ( aViewId == KPhysicsViewUid )
        {
        tabIndex = KPhysicsTabIndex;
        }
    else
        {
        tabIndex = KGestureTabIndex;
        }
    static_cast<CAknTabGroup*>(
            iDecorator->DecoratedControl() )->SetActiveTabByIndex(
                    tabIndex );

    }


// -----------------------------------------------------------------------------
// CAknConfAppUi::TabChangedL
// -----------------------------------------------------------------------------
//
void CAknConfAppUi::TabChangedL( TInt aIndex )
    {
    if ( iCurrentViewId != KPhysicsViewUid && aIndex == KPhysicsTabIndex )
        {
        ActivateLocalViewL( TUid::Uid( KPhysicsViewUid ) );
        iCurrentViewId = KPhysicsViewUid;
        }
    else if ( iCurrentViewId != KGestureViewUid
            && aIndex == KGestureTabIndex )
        {
        ActivateLocalViewL( TUid::Uid( KGestureViewUid ) );
        iCurrentViewId = KGestureViewUid;
        } 
    }


// -----------------------------------------------------------------------------
// CAknConfAppUi::ActivateViewL
// -----------------------------------------------------------------------------
//
void CAknConfAppUi::ActivateViewL( TUid aViewId )
    {
    CAknViewAppUi::ActivateLocalViewL( aViewId );
    iCurrentViewId = aViewId.iUid;
    SetTabIndex( aViewId.iUid );
    }


// -----------------------------------------------------------------------------
// CAknConfAppUi::ActivateNextViewL
// -----------------------------------------------------------------------------
//
CAknConfView* CAknConfAppUi::CurrentView()
    {
    return static_cast<CAknConfView*>( 
            View( TUid::Uid( iCurrentViewId ) ) );
    }


// -----------------------------------------------------------------------------
// CAknConfAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CAknConfAppUi::HandleCommandL(TInt aCommand)
    {
    switch (aCommand)
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;
        case EAbout:
            {
            CAknMessageQueryDialog* dlg = new ( ELeave ) CAknMessageQueryDialog();
            dlg->PrepareLC( R_ABOUT_QUERY_DIALOG );
            HBufC* title = iEikonEnv->AllocReadResourceLC( R_ABOUT_DIALOG_TITLE );
            dlg->QueryHeading()->SetTextL( *title );
            CleanupStack::PopAndDestroy(); //title
            HBufC* msg = iEikonEnv->AllocReadResourceLC( R_ABOUT_DIALOG_TEXT );
            dlg->SetMessageTextL( *msg );
            CleanupStack::PopAndDestroy(); //msg
            dlg->RunLD();
            }
            break;
        case EAknConfView:
            ActivateViewL( TUid::Uid( KPhysicsViewUid ) );
            break;
        case EGestureConfView:
            ActivateViewL( TUid::Uid( KGestureViewUid ) );
            break;
        default:
            Panic(EAknConfUi);
            break;
        }
    }


// -----------------------------------------------------------------------------
//  Called by the framework when the application status pane
//  size is changed.  Passes the new client rectangle to the
//  AppView
// -----------------------------------------------------------------------------
//
void CAknConfAppUi::HandleStatusPaneSizeChange()
    {
    }

// End of File
