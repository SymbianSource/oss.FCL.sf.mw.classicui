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

#include <bctestquery.rsg>
#include "bctestqueryview.h"
#include "bctestquerycontainer.h"
#include "bctestquery.hrh"
#include "bctestutil.h"
#include "bctestlistquery.h"
#include "bctestquerydialog.h"
#include "bctestqueryvalue.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestQueryView* CBCTestQueryView::NewL( CBCTestUtil* aUtil )
    {
    CBCTestQueryView* self = new( ELeave ) CBCTestQueryView( aUtil );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestQueryView::CBCTestQueryView( CBCTestUtil* aUtil): iTestUtil( aUtil )
    {
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestQueryView::ConstructL()
    {
    BaseConstructL( R_BCTESTQUERY_VIEW );
    
    iContainer = new( ELeave ) CBCTestQueryContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );   
    iContainer->MakeVisible( ETrue );
    
    CEikonEnv* env = CEikonEnv::Static();
    
    _LIT( KListQueryCase, "List Query" );
    _LIT( KQueryDialogCase, "Query Dialog" );
    _LIT( KQueryValueCase, "Query Value" );
    
    iTestUtil->AddTestCaseL( CBCTestListQuery::NewL( iContainer, env ), 
        KListQueryCase );
    iTestUtil->AddTestCaseL( CBCTestQueryDialog::NewL( iContainer, env ), 
        KQueryDialogCase );
    iTestUtil->AddTestCaseL( CBCTestQueryValue::NewL( iContainer, env ), 
        KQueryValueCase );    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestQueryView::~CBCTestQueryView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestQueryView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestQueryView::Id() const
    {
    return KBCTestListViewId;
    }
    
// ---------------------------------------------------------------------------
// CBCTestQueryView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestQueryView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestQueryView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestQueryView::DoDeactivate()
    {    
    }
   
// ---------------------------------------------------------------------------
// CBCTestQueryView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestQueryView::HandleCommandL( TInt aCommand )
    { 
    switch( aCommand )
        {
        case EProgCmdAutoTest:
            AppUi()->HandleCommandL( aCommand );
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
