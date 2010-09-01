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
* Description:         Implements test bc for ocr view.
*
*/









#include <aknviewappui.h>
#include <bctestocr.rsg>

#include "bctestocr.hrh"
#include "bctestocrview.h"
#include "bctestocrcontainer.h"
#include "bctestutil.h"
#include "bctestocrcase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestOCRView* CBCTestOCRView::NewL()
    {
    CBCTestOCRView* self = new ( ELeave ) CBCTestOCRView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestOCRView::CBCTestOCRView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestOCRView::ConstructL()
    {
    BaseConstructL( R_BCTESTOCR_VIEW );

    iContainer = new( ELeave ) CBCTestOCRContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    _LIT( KOCRCaseComment, "OCR case" );
    iTestUtil->AddTestCaseL( CBCTestOCRCase::NewL( iContainer ),
        KOCRCaseComment );       
                   
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestOCRView::~CBCTestOCRView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestOCRView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestOCRView::Id() const
    {
    return KBCTestOCRViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestOCRView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestOCRView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestOCRView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestOCRView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestOCRView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestOCRView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EBCTestOCRCmdAutotest:
            iTestUtil->RunL();
            break;
        default:
            if ( aCommand > EBCTestOCRCmdEmptyOutline &&
                 aCommand < EBCTestOCRCmdMaxOutline )
                {
                iTestUtil->RunL( aCommand );
                }
            break;
        }
    }
