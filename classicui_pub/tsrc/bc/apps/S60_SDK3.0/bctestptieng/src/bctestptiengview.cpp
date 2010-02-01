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

#include "BCTestPtiEng.hrh"
#include <bctestptieng.rsg>
#include "BCTestPtiEngview.h"
#include "BCTestPtiEngcontainer.h"
#include "bctestutil.h"
#include "BCTestuserdict.h"
#include "bctestlan.h"
#include "bctestkeymap.h"
#include "bctestqwertymap.h"
#include "bctestlandb.h"
#include "bctestptiengine.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestPtiEngView* CBCTestPtiEngView::NewL()
    {
    CBCTestPtiEngView* self = new( ELeave ) CBCTestPtiEngView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestPtiEngView::CBCTestPtiEngView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestPtiEngView::ConstructL()
    {
    BaseConstructL( R_BCTESTPTIENG_VIEW );

    iContainer = new( ELeave ) CBCTestPtiEngContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    iTestUtil->AddTestCaseL( CBCTestUserDict::NewL( iContainer ),
        _L("Test Pti User Dict") );
	iTestUtil->AddTestCaseL( CBCTestLanguage::NewL(), 
		_L("Test Pti Language") );
	iTestUtil->AddTestCaseL( CBCTestKeymap::NewL(), 
		_L("Test Pti Keymap") );
	iTestUtil->AddTestCaseL( CBCTestQwertyMap::NewL(), 
		_L("Test Qwerty map") );
	iTestUtil->AddTestCaseL( CBCTestLanDB::NewL(), 
		_L("Test Language Database") );
	iTestUtil->AddTestCaseL( CBCTestPtiEngine::NewL(), 
		_L("Test Pti Engine") );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestPtiEngView::~CBCTestPtiEngView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestPtiEngView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestPtiEngView::Id() const
    {
    return KBCTestPtiEngViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestPtiEngView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestPtiEngView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestPtiEngView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestPtiEngView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestPtiEngView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestPtiEngView::HandleCommandL( TInt aCommand )
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
