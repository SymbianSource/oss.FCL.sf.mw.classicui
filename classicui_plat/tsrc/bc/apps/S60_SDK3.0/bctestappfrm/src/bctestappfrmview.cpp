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

#include "bctestappfrm.hrh"
#include <bctestappfrm.rsg>
#include "bctestappfrmview.h"
#include "bctestappfrmcontainer.h"
#include "bctestutil.h"
#include "bctestaknapplication.h"
#include "bctestakndoc.h"
#include "bctestaknviewappui.h"
#include "bctesteikmobs.h"
#include "bctestvcurs.h"
#include "bctesteikenvcase.h"

#include "bctestappfrmcase.h"
#include "bctestappfrmaknappuicase.h"
#include "bctestappfrmaknviewcase.h"
#include "bctestappfrmeikappuicase.h"
#include "bctestappfrmeiksrvcase.h"



_LIT( KAppFrmAknAppUICase, "Application Framework AknAppUi case");
_LIT( KAppFrmAknViewCase, "Application Framework AknView case");
_LIT( KAppFrmEikAppUICase, "Application Framework EikAppUi case");
_LIT( KAppFrmEikSrvCase, "Application Framework EikSrv case");

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestAppFrmView* CBCTestAppFrmView::NewL(CAknViewAppUi* aUI)
    {
    CBCTestAppFrmView* self = new( ELeave ) CBCTestAppFrmView();
    CleanupStack::PushL( self );
    self->ConstructL(aUI);
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestAppFrmView::CBCTestAppFrmView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmView::ConstructL(CAknViewAppUi* aUI)
    {
    BaseConstructL( R_BCTESTAPPFRM_VIEW );

    iContainer = new( ELeave ) CBCTestAppFrmContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestAknApplication::NewL(), _L("CBCTestAknApplication") );
    iTestUtil->AddTestCaseL( CBCTestAknDoc::NewL(), _L("CBCTestAknDoc") );
    iTestUtil->AddTestCaseL( CBCTestAknViewAppUi::NewL(aUI, Id()), _L("CBCTestAknViewAppUi") );
    iTestUtil->AddTestCaseL( CBCTestEikMObserver::NewL(), _L("CBCTestEikMObserver") );
    iTestUtil->AddTestCaseL( CBCTestVCursor::NewL(), _L("CBCTestVCursor") );
    iTestUtil->AddTestCaseL( CBCTestEikenv::NewL( iContainer ), _L("CBCTestEikEnv") );
    iTestUtil->AddTestCaseL( CBCTestAppFrmAknAppUICase::NewL(iContainer),
        KAppFrmAknAppUICase );
    iTestUtil->AddTestCaseL( CBCTestAppFrmAknViewCase::NewL(iContainer,this),
        KAppFrmAknViewCase );
    iTestUtil->AddTestCaseL( CBCTestAppFrmEikAppUICase::NewL(iContainer),
        KAppFrmEikAppUICase );
    iTestUtil->AddTestCaseL( CBCTestAppFrmEikSrvCase::NewL(iContainer),
        KAppFrmEikSrvCase );

    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestAppFrmView::~CBCTestAppFrmView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestAppFrmView::Id() const
    {
    return KBCTestAppFrmViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmView::HandleCommandL( TInt aCommand )
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

// ---------------------------------------------------------------------------
// CBCTestAppFrmView::AppFrmView_cba
// ---------------------------------------------------------------------------
//  
void CBCTestAppFrmView::AppFrmView_cba()
    {
    Cba();
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmView::AppFrmView_StatusPane
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmView::AppFrmView_StatusPane()
    {
    StatusPane();
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmView::AppFrmView_ViewScreenDeviceChangedL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmView::AppFrmView_ViewScreenDeviceChangedL()
    {
    ViewScreenDeviceChangedL();
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmView::AppFrmView_DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmView::AppFrmView_DoActivateL( const TVwsViewId& aViewId,
                                           TUid  aId , const TDesC8& aDes)
    {
    DoActivateL(aViewId,aId,aDes);
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmView::AppFrmView_MopNext
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmView::AppFrmView_MopNext()
    {
    MopNext();
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmView::AppFrmView_MopSupplyObject
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmView::AppFrmView_MopSupplyObject( TTypeUid aId )
    {
    MopSupplyObject( aId );
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmView::AppFrmView_HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmView::AppFrmView_HandleCommandL( TInt aCommand )
    {
	CAknView::HandleCommandL( aCommand );
    }
 
