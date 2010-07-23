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

#include "bctesteikbctrl.hrh"
#include <bctesteikbctrl.rsg>
#include "bctesteikbctrlview.h"
#include "bctesteikbctrlcontainer.h"
#include "bctestutil.h"
#include "bctesteikbctrlcase.h"
#include "bctesteikbdialgcase.h"
#include "bctesteikaligncase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTesteikbctrlView* CBCTesteikbctrlView::NewL()
    {
    CBCTesteikbctrlView* self = new( ELeave ) CBCTesteikbctrlView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------

CBCTesteikbctrlView::CBCTesteikbctrlView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTesteikbctrlView::ConstructL()
    {
    BaseConstructL( R_BCTESTEIKBCTRL_VIEW );
    _LIT(CtrlCase,"eikbctrl test case");
    _LIT(DialgCase,"eikdialg test case");
    _LIT(AlignCase, "align test case" );
    iContainer = new( ELeave ) CBCTesteikbctrlContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTesteikbctrlCase::NewL( iContainer ),
         CtrlCase);
    iTestUtil->AddTestCaseL( CBCTesteikalignCase::NewL( iContainer),
         AlignCase);
    iTestUtil->AddTestCaseL( CBCTesteikbdialgCase::NewL( iContainer ),
        DialgCase);

    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTesteikbctrlView::~CBCTesteikbctrlView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTesteikbctrlView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTesteikbctrlView::Id() const
    {
    return KBCTesteikbctrlViewId;
    }

// ---------------------------------------------------------------------------
// CBCTesteikbctrlView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTesteikbctrlView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTesteikbctrlView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTesteikbctrlView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTesteikbctrlView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTesteikbctrlView::HandleCommandL( TInt aCommand )
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
