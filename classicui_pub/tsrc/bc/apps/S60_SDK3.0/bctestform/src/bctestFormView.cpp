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
* Description:         For bctestform application
*
*/









// INCLUDE FILES
#include <avkon.hrh>
#include <akntitle.h>
#include <aknviewappui.h>
#include <bctestform.rsg>

#include <eikmfne.h>
#include <eikedwin.h>
#include <eikcapc.h>

#include "BCTestForm.hrh"
#include "BCTestFormView.h"
#include "BCTestFormContainer.h"

// CONSTANTS
const TUid KViewId = { 1 }; // UID of view
const TInt KBCTestFormTitleBufLength = 256;
const TInt KBCTestFormResourceIdInitialize = 0;

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestFormView::CBCTestFormView()
// Default constructor.
// ----------------------------------------------------------------------------
//
CBCTestFormView::CBCTestFormView()
    :   iContainer( NULL ),
        iCurrentOutline( EBCTestFormCmdEmptyOutline )
    {
    }

// -----------------------------------------------------------------------------
// CAknAtVolumeView::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBCTestFormView* CBCTestFormView::NewL()
    {
    CBCTestFormView* self = new( ELeave ) CBCTestFormView;

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    }


// ----------------------------------------------------------------------------
// void CBCTestFormView::ConstructL()
// Symbian 2nd phase constructor.
// ----------------------------------------------------------------------------
//
void CBCTestFormView::ConstructL()
    {
    BaseConstructL( R_BCTESTFORM_VIEW );
    }

// ----------------------------------------------------------------------------
// CBCTestFormView::~CBCTestFormView()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestFormView::~CBCTestFormView()
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
// void CBCTestFormView::DisplayNextOutlineL( TInt )
//
// ----------------------------------------------------------------------------
//
void CBCTestFormView::DisplayNextOutlineL()
    {
    switch ( iCurrentOutline )
        {
        case EBCTestFormCmdEmptyOutline:
            HandleCommandL( EBCTestFormCmdOutline01 );
            break;
        case EBCTestFormCmdOutline01:
            HandleCommandL( EBCTestFormCmdOutline02 );
            break;
        case EBCTestFormCmdOutline02:
            HandleCommandL( EBCTestFormCmdOutline03 );
            break;
        default:
            HandleCommandL( EBCTestFormCmdEmptyOutline );
            break;
        }
    }

// ----------------------------------------------------------------------------
// TUid CBCTestFormView::Id()
// Returns ID of view.
// ----------------------------------------------------------------------------
//
TUid CBCTestFormView::Id() const
    {
    return KViewId;
    }

// ----------------------------------------------------------------------------
// void CBCTestFormView::HandleCommandL( TInt )
// Handles the commands.
// ----------------------------------------------------------------------------
//
void CBCTestFormView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
            AppUi()->ProcessCommandL( EAknCmdExit );
            break;
        case EAknCmdExit:
            AppUi()->HandleCommandL( EAknCmdExit );
            break;

        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// void CBCTestFormView::IndicateTitlePaneTextL( TInt )
// Set title text to status-pane
// ----------------------------------------------------------------------------
//
void CBCTestFormView::IndicateTitlePaneTextL( TInt aCommand )
    {
    TBool useDefaultText( EFalse );
    TInt resourceId( KBCTestFormResourceIdInitialize );
    switch ( aCommand )
        {
        case EBCTestFormCmdEmptyOutline:
            useDefaultText = ETrue;
            break;
        case EBCTestFormCmdOutline01:
            resourceId = R_BCTESTFORM_TEXT_STATUS_PANE_TITLE01;
            break;
        case EBCTestFormCmdOutline02:
            resourceId = R_BCTESTFORM_TEXT_STATUS_PANE_TITLE02;
            break;
        default:
            useDefaultText = ETrue;
            break;
        }

    CAknTitlePane* titlePane = STATIC_CAST(
        CAknTitlePane*,
        StatusPane()->ControlL( TUid::Uid( EEikStatusPaneUidTitle ) ) );
    if ( useDefaultText )
        {
        titlePane->SetTextToDefaultL();
        }
    else
        {
        TBuf<KBCTestFormTitleBufLength> titleText( NULL );
        iEikonEnv->ReadResourceL( titleText, resourceId );
        titlePane->SetTextL( titleText );
        }
    }

// ----------------------------------------------------------------------------
// void CBCTestFormView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
// Creates container class object.
// ----------------------------------------------------------------------------
//
void CBCTestFormView::DoActivateL(
    const TVwsViewId& /*aPrevViewId*/,
    TUid /*aCustomMessageId*/,
    const TDesC8& /*aCustomMessage*/ )
    {
    // Creates container object.
    if ( !iContainer )
        {
        iContainer = new( ELeave ) CBCTestFormContainer( this );
        iContainer->SetMopParent(this);
        iContainer->ConstructL( ClientRect() );
        // Adds container to view control stack.
        AppUi()->AddToStackL( *this, iContainer );
        }
    }

// ----------------------------------------------------------------------------
// void CBCTestFormView::DoDeactivate()
// Deletes container class object.
// ----------------------------------------------------------------------------
//
void CBCTestFormView::DoDeactivate()
    {
    // Deletes the container class object.
    if ( iContainer )
        {
        // Removes container from view control stack.
        AppUi()->RemoveFromStack( iContainer );
        delete iContainer;
        iContainer = NULL;
        }
    }

void CBCTestFormView::SetupAPIOutlineL(TInt aCommand)
    {
    iCurrentOutline = aCommand;
    IndicateTitlePaneTextL( aCommand );
    iContainer->SetTextToLabelL( R_BCTESTFORM_TEXT_LABEL_OPERATION );
    }

// ----------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that
// might leave.
// ----------------------------------------------------------------------------
//
CBCTestFormTestAdd::CBCTestFormTestAdd()
    {
    iNewItemId = EBCTestFormDlgCtrlIdEdwin02 + 1;
    }

// Destructor
CBCTestFormTestAdd::~CBCTestFormTestAdd()
    {
    }

// ----------------------------------------------------------------------------
// void CBCTestFormTestAdd::AddItemL()
// Add item for testing uses customised dialog.
// ----------------------------------------------------------------------------
//


void CBCTestFormTestAdd::AddItemL()
    {
    // Add Edwin control
    _LIT( caption, "Add ed" ) ;

    CCoeControl* myEdControl = CreateLineByTypeL(caption, ActivePageId(),
                                                 iNewItemId ,
                                                 EEikCtEdwin,
                                                 NULL) ;

    CEikEdwin* myEdwin = STATIC_CAST(CEikEdwin*, myEdControl) ;
    myEdwin->ConstructL(EEikEdwinNoHorizScrolling | EEikEdwinResizable, 10,
                        64, 10);
    myEdwin->CreateTextViewL();
    Line(iNewItemId )->ActivateL();

    SetEditableL(IsEditable()) ;
    DrawNow() ;
    // In order to prevent adding controls which ID is the same,
    // Id of next adding control is different from the others.
    iNewItemId++;
    }

CBCTestFormContainer* CBCTestFormView::Container() const
    {
    return iContainer;
    }

