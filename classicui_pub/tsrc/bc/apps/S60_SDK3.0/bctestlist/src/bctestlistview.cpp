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
* Description:         view class
*
*/









#include <aknviewappui.h>

#include <bctestlist.rsg>
#include "bctestlistview.h"
#include "bctestlistcontainer.h"
#include "bctestlist.hrh"
#include "bctestutil.h"
#include "bctestlistcolumncase.h"
#include "bctestlistformattedcase.h"
#include "bctestlistsettingcase.h"
#include "bctestlistpopupcase.h"
#include "bctestlistgridcase.h"
#include "bctestlistdecoratorcase.h"
#include "bctestlistcolumnbasecase.h"
#include "bctestlistformatbasecase.h"
#include "bctestlisteiklistcase.h"
#include "bctestlistselectioncase.h"

_LIT( KColumnListCase, "Column Lists" );
_LIT( KFormattedCase, "Formatted Lists" );
_LIT( KSettingListCase, "Settings Lists" );
_LIT( KPopupCase, "Popup Lists" );
_LIT( KGridCase, "Grid pane Lists" );
_LIT( KDecoratorCase, "Decorator test case" );
_LIT( KColumnBaseCase, "Eikon column list" );
_LIT( KFormattedBaseCase, "Eikon formatted cell list" );
_LIT( KEikListCase, "Eikon list box" );
_LIT( KSelectionListCase, "Selection list" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestListView* CBCTestListView::NewL()
    {
    CBCTestListView* self = new( ELeave ) CBCTestListView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestListView::CBCTestListView()
    {    
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestListView::ConstructL()
    {
    BaseConstructL( R_BCTESTLIST_VIEW );
    
    iContainer = new( ELeave ) CBCTestListContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );    
    iContainer->MakeVisible( ETrue );
    
    CEikonEnv* eikEnv = CEikonEnv::Static();    
    iTestUtil = CBCTestUtil::NewL();
    iTestUtil->AddTestCaseL( 
        CBCTestListColumnCase::NewL( iContainer, eikEnv ),
        KColumnListCase );
    iTestUtil->AddTestCaseL( 
        CBCTestListFormattedCase::NewL( iContainer, eikEnv ), 
        KFormattedCase );
    iTestUtil->AddTestCaseL(
        CBCTestListSettingCase::NewL( iContainer, eikEnv ), 
        KSettingListCase );
    iTestUtil->AddTestCaseL(
        CBCTestListPopupCase::NewL( iContainer, eikEnv ),
        KPopupCase );
    iTestUtil->AddTestCaseL(
        CBCTestListGridCase::NewL( iContainer, eikEnv ),
        KGridCase );
    iTestUtil->AddTestCaseL(
        CBCTestListDecoratorCase::NewL( iContainer, eikEnv ),
        KDecoratorCase );
    iTestUtil->AddTestCaseL(
        CBCTestListColumnBaseCase::NewL( iContainer, eikEnv ),
        KColumnBaseCase );
    iTestUtil->AddTestCaseL(
        CBCTestListFormatBaseCase::NewL( iContainer, eikEnv ),
        KFormattedBaseCase );
    iTestUtil->AddTestCaseL(
        CBCTestListEiklistCase::NewL( iContainer, eikEnv ),
        KEikListCase );
    iTestUtil->AddTestCaseL(
        CBCTestListSelectionCase::NewL( iContainer, eikEnv ),
        KSelectionListCase );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestListView::~CBCTestListView()
    {    
    delete iTestUtil;
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestListView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestListView::Id() const
    {
    return KBCTestListViewId;
    }
    
// ---------------------------------------------------------------------------
// CBCTestListView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestListView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestListView::DoDeactivate()
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListView::Container
// ---------------------------------------------------------------------------
//
CBCTestListContainer* CBCTestListView::Container()
    {
    return iContainer;
    }
    
// ---------------------------------------------------------------------------
// CBCTestListView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestListView::HandleCommandL( TInt aCommand )
    { 
    switch ( aCommand )
        {
        case EProgCmdAutoTest:
            iTestUtil->RunL();
            break;       
        default:
            if ( aCommand > EBCTestCmdEmptyOutline && 
                 aCommand < EProgSoftkeyNextOutline )
                {
                iTestUtil->RunL( aCommand );
                }
            break;
        }
    }
