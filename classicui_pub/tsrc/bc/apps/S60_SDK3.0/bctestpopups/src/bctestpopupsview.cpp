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
* Description:         Implements test bc for popups control view.
*
*/









#include <aknviewappui.h>
#include <bctestpopups.rsg>

#include "bctestpopups.hrh"
#include "bctestpopupsview.h"
#include "bctestpopupscontainer.h"
#include "bctestutil.h"
#include "bctestpopupfieldtextcase.h"
#include "bctestpopupcase.h"
#include "bctestheadingpanecase.h"
#include "bctestpopupsettingpagecase.h"

// constant
_LIT( KPopupFieldTextCaseComment, "Popupfieldtext case" );
_LIT( KPopupCaseComment, "Popup case" );
_LIT( KHeadingPaneCaseComment, "Heading pane case" );
_LIT( KPopupsSettingPageCaseComment, "PopupSettingPage case" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestPopupsView* CBCTestPopupsView::NewL()
    {
    CBCTestPopupsView* self = new ( ELeave ) CBCTestPopupsView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestPopupsView::CBCTestPopupsView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestPopupsView::ConstructL()
    { 
    BaseConstructL( R_BCTESTPOPUPS_VIEW );

    iContainer = new( ELeave ) CBCTestPopupsContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestPopupFieldTextCase::NewL( iContainer ),
        KPopupFieldTextCaseComment );

    iTestUtil->AddTestCaseL( CBCTestPopupCase::NewL( iContainer ),
        KPopupCaseComment );

    iTestUtil->AddTestCaseL( CBCTestHeadingPaneCase::NewL( iContainer ),
        KHeadingPaneCaseComment );

    iTestUtil->AddTestCaseL( CBCTestPopupSettingPageCase::NewL( iContainer ),
        KPopupsSettingPageCaseComment );

    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestPopupsView::~CBCTestPopupsView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer; 
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestPopupsView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestPopupsView::Id() const
    {
    return KBCTestPopupsViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestPopupsView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestPopupsView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
  
    }

// ---------------------------------------------------------------------------
// CBCTestPopupsView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestPopupsView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestPopupsView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestPopupsView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EBCTestPopupsCmdAutotest:
            iTestUtil->RunL();
            break;
        default:
            if ( aCommand > EBCTestPopupsCmdEmptyOutline &&
                 aCommand < EBCTestPopupsCmdMaxOutline )
                {
                iTestUtil->RunL( aCommand );
                }
            break;
        }
    }
