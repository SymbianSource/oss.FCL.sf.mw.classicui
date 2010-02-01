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
#include <bctestEditor.rsg>

#include "bctestEditor.hrh"
#include "bctestEditorview.h"
#include "bctestEditorcontainer.h"
#include "bctestutil.h"
#include "bctestEditorcase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestEditorView* CBCTestEditorView::NewL()
    {
    CBCTestEditorView* self = new( ELeave ) CBCTestEditorView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestEditorView::CBCTestEditorView()
    {    
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestEditorView::ConstructL()
    {
    _LIT( strTestCase,"Editor test case");
    BaseConstructL( R_BCTESTEDITOR_VIEW );
    
    iContainer = new( ELeave ) CBCTestEditorContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );
    
    iTestUtil = CBCTestUtil::NewL();
    
    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestEditorCase::NewL( iContainer ),
    strTestCase );    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEditorView::~CBCTestEditorView()
    {    
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestEditorView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestEditorView::Id() const
    {
    return KBCTestEditorViewId;
    }
    
// ---------------------------------------------------------------------------
// CBCTestEditorView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestEditorView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestEditorView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestEditorView::DoDeactivate()
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestEditorView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestEditorView::HandleCommandL( TInt aCommand )
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
