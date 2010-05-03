/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  appui
*
*/


#include <avkon.hrh>
#include <aknsutils.h>
#include "bctestdomaknanimview.h"  // test aknanimview.h

#include "bctestdomaiwaknappui.h"
#include "bctestdomaiwakn.hrh"
#include "bctestdomaiwaknview.h"
#include "bctestutil.h"
#include "bctestdomaiwcase.h" 
#include "bctestdomaknrclasscase.h" 
#include "bctestdomaknnoctrlcase.h" 
#include "bctestdomaknctrlcase.h" 

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// constructor do nothing
// ---------------------------------------------------------------------------
//
CBCTestDomAiwAknAppUi::CBCTestDomAiwAknAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwAknAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

	// init test util
	iTestUtil = CBCTestUtil::NewL();

    // init view
    CBCTestDomAiwAknView* view = CBCTestDomAiwAknView::NewL( iTestUtil );
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );

    
    CWindowGc& gc = CCoeEnv::Static()->SystemGc();
    // test aknanimview.h
    iAnimView =
        CBCTestDomAknAnimatedView::NewLC();  
    AddViewL( iAnimView );
    CleanupStack::Pop( iAnimView );    
    //ActivateLocalViewL( iAnimView->Id() ); // panic


	// Add test case here.
    iTestUtil->AddTestCaseL( CBCTestDomAiwCase::NewL( view->Container() ),
        _L( "Aiw test case" ) );
        
    iTestUtil->AddTestCaseL( 
        CBCTestDomAknNoCtrlCase::NewL( view->Container() ),
        _L( "AknNoCtrl test case" ) );        

    iTestUtil->AddTestCaseL( CBCTestDomAknCtrlCase::NewL( view->Container() ),
        _L( "AknCtrl test case" ) );        
         
    iTestUtil->AddTestCaseL( 
        CBCTestDomAknRClassCase::NewL( view->Container() ),
        _L( "AknRClass test case" ) );       

    }

// ---------------------------------------------------------------------------
// CBCTestDomAiwAknAppUi::~CBCTestDomAiwAknAppUi()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestDomAiwAknAppUi::~CBCTestDomAiwAknAppUi()
    { 
	delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// handle menu command events
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwAknAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
        case EEikCmdExit:
            {
            Exit();
            return;
            }
        default:
            break;
        }    
    }

// End of File
