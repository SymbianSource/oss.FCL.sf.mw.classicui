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
* Description:         Implements test bc for note control view.
*
*/









#include <aknviewappui.h>
#include <bctestnote.rsg>

#include "bctestnote.hrh" 
#include "bctestnoteview.h"
#include "bctestnotecontainer.h"
#include "bctestutil.h"
#include "bctestnotewrappercase.h"
#include "bctestwaitdialogcase.h"
#include "bcteststaticnotecase.h"
#include "bctesteikinfodialogcase.h"
#include "bctesteikprogressinfocase.h"
#include "bctestwaitnotewrappercase.h"
#include "bctestnotedialogcase.h"
#include "bctestnotecontrolcase.h"

// constant
_LIT( KNoteWrapperCaseComment, "Note wrapper case" );
_LIT( KWaitDialogCaseComment, "Wait dialog case" );
_LIT( KStaticNoteCaseComment, "Static note case" );
_LIT( KEikInfoDialogCaseComment, "Eik info dialog case" );
_LIT( KEikProgressInfoCaseComment, "Eik progress info case" );
_LIT( KWaitNoteWrapperCaseComment, "Wait note wrapper case" );
_LIT( KNoteDialogCaseComment, "Note dialog case" );
_LIT( KNoteControlCaseComment, "Note control case" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestNoteView* CBCTestNoteView::NewL()
    {
    CBCTestNoteView* self = new ( ELeave ) CBCTestNoteView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestNoteView::CBCTestNoteView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestNoteView::ConstructL()
    {
    BaseConstructL( R_BCTESTNOTE_VIEW );

    iContainer = new( ELeave ) CBCTestNoteContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestNoteWrapperCase::NewL( iContainer ),
        KNoteWrapperCaseComment );
        
    iTestUtil->AddTestCaseL( CBCTestWaitDialogCase::NewL( iContainer ),
        KWaitDialogCaseComment );
        
    iTestUtil->AddTestCaseL( CBCTestStaticNoteCase::NewL( iContainer ),
        KStaticNoteCaseComment ); 
                       
    iTestUtil->AddTestCaseL( CBCTestEikInfoDialogCase::NewL( iContainer ),
        KEikInfoDialogCaseComment );
         
    iTestUtil->AddTestCaseL( CBCTestEikProgressInfoCase::NewL( iContainer ),
        KEikProgressInfoCaseComment );
        
    iTestUtil->AddTestCaseL( CBCTestWaitNoteWrapperCase::NewL( iContainer ),
        KWaitNoteWrapperCaseComment );     

    iTestUtil->AddTestCaseL( CBCTestNoteDialogCase::NewL( iContainer ),
        KNoteDialogCaseComment ); 
        
    iTestUtil->AddTestCaseL( CBCTestNoteControlCase::NewL( iContainer ),
        KNoteControlCaseComment );                     
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestNoteView::~CBCTestNoteView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestNoteView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestNoteView::Id() const
    {
    return KBCTestNoteViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestNoteView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestNoteView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestNoteView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestNoteView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestNoteView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestNoteView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EProgCmdAutoTest:
            iTestUtil->RunL();
            break;
        default:
            if ( aCommand > EBCTestNoteCmdEmptyOutline &&
                 aCommand < EBCTestNoteCmdOutline159 )
                {
                iTestUtil->RunL( aCommand );
                }
            break;
        }
    }
