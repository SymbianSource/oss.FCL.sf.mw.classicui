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
#include <bctestfontinput.rsg>

#include "bctestfontinput.hrh"
#include "bctestfontinputview.h"
#include "bctestfontinputcontainer.h"
#include "bctestutil.h"
#include "bctestfontinputcase.h"
#include "bctestframeinfocase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestFontInputView* CBCTestFontInputView::NewL()
    {
    CBCTestFontInputView* self = new( ELeave ) CBCTestFontInputView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestFontInputView::CBCTestFontInputView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestFontInputView::ConstructL()
    {
    BaseConstructL( R_BCTESTFONTINPUT_VIEW );

    iContainer = new( ELeave ) CBCTestFontInputContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    _LIT( fntInput,"FontInput test case" );
    _LIT( frmInfo," Frame Information " );
    
     iTestUtil->AddTestCaseL( CBCTestFontInputCase::NewL( iContainer ),
        fntInput);


    iTestUtil->AddTestCaseL( CBCTestFrameInfoCase::NewL( iContainer ),
   	       frmInfo);
   	       
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestFontInputView::~CBCTestFontInputView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestFontInputView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestFontInputView::Id() const
    {
    return KBCTestFontInputViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestFontInputView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestFontInputView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestFontInputView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestFontInputView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestFontInputView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestFontInputView::HandleCommandL( TInt aCommand )
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
