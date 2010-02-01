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
* Description:  view
*
*/

#include <eikmenub.h> 
#include <aknviewappui.h>
#include <bctestdomaiwakn.rsg>
#include <avkon.rsg>

#include "bctestdomaiwakn.hrh"
#include "bctestdomaiwaknview.h"
#include "bctestdomaiwakncontainer.h"
#include "bctestutil.h"





// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAiwAknView* CBCTestDomAiwAknView::NewL( CBCTestUtil* aUtil )
    {
    CBCTestDomAiwAknView* self = new( ELeave ) CBCTestDomAiwAknView();
    CleanupStack::PushL( self );
    self->ConstructL( aUtil );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAiwAknView::CBCTestDomAiwAknView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwAknView::ConstructL( CBCTestUtil* aUtil )
    {
    BaseConstructL( R_BCTESTDOMAIWAKN_VIEW );

    iContainer = new( ELeave ) CBCTestDomAiwAknContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = aUtil;

    iAutotestCounter = 0;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomAiwAknView::~CBCTestDomAiwAknView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestDomAiwAknView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestDomAiwAknView::Id() const
    {
    return KBCTestAiwAknViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestDomAiwAknView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwAknView::DynInitMenuPaneL(
    TInt aResourceId,
    CEikMenuPane* aMenuPane)
    {    
    if( aResourceId && aMenuPane)
        {
        
        }
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAiwAknView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwAknView::DoActivateL( const TVwsViewId&, TUid, 
    const TDesC8& )
    {
    
    }

// ---------------------------------------------------------------------------
// CBCTestDomAiwAknView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwAknView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomAiwAknView::Container
// ---------------------------------------------------------------------------
//
CBCTestDomAiwAknContainer* CBCTestDomAiwAknView::Container()
    {
	return iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestDomAiwAknView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwAknView::HandleCommandL( TInt aCommand )
    {
    
    if( iAutotestCounter >1 )
        {
        //User::Exit( 0 );        
        }
    
    switch ( aCommand )
        {
        case EProgCmdAutoTest:
            {
            iTestUtil->RunL();   

            // increment AutoTest counter                              
            iAutotestCounter += 1;
            
            }
            break;
        default:
            if ( aCommand > EBCTestDomCmdEmptyOutline &&
                 aCommand < EBCTestDomCmdMaxOutline )
                {
                iTestUtil->RunL( aCommand );
                
                }
            break;
        }
    }
