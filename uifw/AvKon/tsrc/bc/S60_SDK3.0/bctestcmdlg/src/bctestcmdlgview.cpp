/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  view class
*
*/


#include <aknviewappui.h>

#include "BCTestCmDlg.hrh"
#include <bctestcmdlg.rsg>
#include "BCTestCmDlgview.h"
#include "BCTestCmDlgcontainer.h"
#include "bctestutil.h"
#include "BCTestCmDlgcase.h"
#include "bctestmemselpage.h"
#include "bctestfileseldlg.h"
#include "bctestfilenamedlg.h"
#include "bctestcommondlg.h"
#include "bctestmemselitem.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestCmDlgView* CBCTestCmDlgView::NewL()
    {
    CBCTestCmDlgView* self = new( ELeave ) CBCTestCmDlgView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestCmDlgView::CBCTestCmDlgView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestCmDlgView::ConstructL()
    {
    BaseConstructL( R_BCTESTCMDLG_VIEW );

    iContainer = new( ELeave ) CBCTestCmDlgContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestCmDlgCase::NewL(),
        _L("Mem selection dialog") );
	iTestUtil->AddTestCaseL( CBCTestMemSelSettingPage::NewL(),
        _L("Mem selection setting page") );
	iTestUtil->AddTestCaseL( CBCTestFileSelDlg::NewL(),
        _L("File selection dialog") );
	iTestUtil->AddTestCaseL( CBCTestFileNameDlg::NewL(),
        _L("File name prompt dialog") );
	iTestUtil->AddTestCaseL( CBCTestCommonDlg::NewL(),
        _L("Common dialog") );
	iTestUtil->AddTestCaseL( CBCTestMemSelSettingItem::NewL(),
        _L("Mem selection setting item") );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestCmDlgView::~CBCTestCmDlgView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestCmDlgView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestCmDlgView::Id() const
    {
    return KBCTestCmDlgViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestCmDlgView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestCmDlgView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestCmDlgView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestCmDlgView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestCmDlgView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestCmDlgView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EProgCmdAutoTest:
            iTestUtil->RunL();
            break;
        default:
            if ( aCommand > EBCTestCmdEmptyOutline &&
                 aCommand < EBCTestCmdMaxOutline )
                {
                iTestUtil->RunL( aCommand );
                }
            break;
        }
    }
