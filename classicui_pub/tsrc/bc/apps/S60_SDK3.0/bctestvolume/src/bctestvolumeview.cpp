/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Avkon volume test application
*
*/









// INCLUDE FILES
#include <avkon.hrh>
#include <avkon.rsg>
#include <akntitle.h>
#include <aknviewappui.h>
#include <bctestvolume.rsg>
#include <aknconsts.h>

#include "BCTestvolume.hrh"
#include "BCTestVolumeView.h"
#include "BCTestVolumeContainer.h"

// CONSTANTS
const TUid KViewId = { 1 }; // UID of view
const TInt KBCTestVolumeTitleBufLength = 256;

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestVolumeView::CBCTestVolumeView()
// Default constructor.
// ----------------------------------------------------------------------------
//
CBCTestVolumeView::CBCTestVolumeView()
    : iCurrentOutline(EBCTestVolumeCmdEmptyOutline), iContainer( NULL )
    {
    }

// -----------------------------------------------------------------------------
// CBCTestVolumeView::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CBCTestVolumeView::ConstructL()
    {
    BaseConstructL( R_BCTESTVOLUME_VIEW );
    }

// -----------------------------------------------------------------------------
// CBCTestVolumeView::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBCTestVolumeView* CBCTestVolumeView::NewL()
    {
    CBCTestVolumeView* self = new( ELeave ) CBCTestVolumeView;

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestVolumeView::~CBCTestVolumeView()
// Destructor.
// ----------------------------------------------------------------------------
CBCTestVolumeView::~CBCTestVolumeView()
    {
    // Deletes the container class object.
    if ( iContainer )
        {
        // Removes container from view control stack.
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ----------------------------------------------------------------------------
// void CBCTestVolumeView::DisplayNextOutlineL( const TInt )
// Requires to display next outline screen.
// ----------------------------------------------------------------------------
//
void CBCTestVolumeView::DisplayNextOutlineL()
    {
    int outlineNumber = EBCTestVolumeCmdMaxOutline-EBCTestVolumeCmdEmptyOutline;
    iCurrentOutline = (iCurrentOutline-EBCTestVolumeCmdEmptyOutline+1) % outlineNumber + EBCTestVolumeCmdEmptyOutline;
    AppUi()->ProcessCommandL( iCurrentOutline );
    }

// ----------------------------------------------------------------------------
// TUid CBCTestVolumeView::Id()
// Returns ID of view.
// ----------------------------------------------------------------------------
TUid CBCTestVolumeView::Id() const
    {
    return KViewId;
    }

// ----------------------------------------------------------------------------
// void CBCTestVolumeView::HandleCommandL( TInt )
// Handles the commands.
// ----------------------------------------------------------------------------
//
void CBCTestVolumeView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
            AppUi()->ProcessCommandL( EAknCmdExit );
            break;
        case EAknCmdExit:
            AppUi()->HandleCommandL( EAknCmdExit );
            break;

        case EBCTestVolumeCbaCmdNext:
            DisplayNextOutlineL();
            break;
        default:
            break;
        }
    if(aCommand<EBCTestVolumeCmdMaxOutline && aCommand>EBCTestVolumeCmdEmptyOutline)
        IndicateTitlePaneTextL( aCommand);
    }

// ----------------------------------------------------------------------------
// void CBCTestVolumeView::IndicateTitlePaneTextL( const TInt )
// Sets title text to status-pane.
// ----------------------------------------------------------------------------
//
void CBCTestVolumeView::IndicateTitlePaneTextL( const TInt aOutlineId )
    {
    iCurrentOutline = aOutlineId;

    CAknTitlePane* titlePane = STATIC_CAST(
        CAknTitlePane*,
        StatusPane()->ControlL( TUid::Uid( EEikStatusPaneUidTitle ) ) );

    if(aOutlineId<EBCTestVolumeCmdMaxOutline && aOutlineId>EBCTestVolumeCmdEmptyOutline)
        {
        _LIT(KTitleFormat, "OUTLINE%d");
        TBuf<KBCTestVolumeTitleBufLength> titleText( 0 );
        titleText.Format(KTitleFormat, (aOutlineId - EBCTestVolumeCmdEmptyOutline) );
        titlePane->SetTextL( titleText ); // Sets title text to status-pane.
        }
    else
        {
        titlePane->SetTextToDefaultL();
        }
    }

// ----------------------------------------------------------------------------
// void CBCTestVolumeView::DoActivateL( const TVwsViewId&, TUid, const TDesC& )
// Creates the container class object.
// ----------------------------------------------------------------------------
//
void CBCTestVolumeView::DoActivateL(const TVwsViewId& /* aPrevViewId */,
                   TUid /* aCustomMessageId */,
                   const TDesC8& /* aCustomMessage */ )
    {
    // Creates the container class object.
    if ( !iContainer )
        {
        iContainer = new( ELeave ) CBCTestVolumeContainer( this );
        iContainer->SetMopParent(this);
        iContainer->ConstructL( ClientRect() );

        // Adds container to view control stack.
        AppUi()->AddToStackL( *this, iContainer );

        // Requires to display the default screen.
        iContainer->DisplayOutlineL( EBCTestVolumeCmdEmptyOutline );
        iContainer->MakeVisible( ETrue );
        }
    }

// ----------------------------------------------------------------------------
// void CBCTestVolumeView::DoDeactivate()
// Deletes the container class object.
// ----------------------------------------------------------------------------
//
void CBCTestVolumeView::DoDeactivate()
    {
    // Deletes the container class object.
    if ( iContainer )
        {
        // Removes container from view control stack.
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer;
    iContainer = NULL;
    }

// ----------------------------------------------------------------------------
// Getter of the container.
// ----------------------------------------------------------------------------
//
CBCTestVolumeContainer* CBCTestVolumeView::Container() const
    { 
    return iContainer; 
    }

// End of File
