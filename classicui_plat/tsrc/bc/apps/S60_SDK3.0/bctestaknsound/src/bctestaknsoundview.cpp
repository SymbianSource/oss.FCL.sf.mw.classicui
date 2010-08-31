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

#include "bctestaknsound.hrh"
#include <bctestaknsound.rsg>
#include "bctestaknsoundview.h"
#include "bctestaknsoundcontainer.h"
#include "bctestutil.h"
#include "bctestaknsoundinfocase.h"
#include "bctestaknsoundsystemcase.h"

_LIT( KAknSoundInfoCase, "Avkon Sound Info test case" );
_LIT( KAknSoundSystemCase, "Avkon Sound System test case" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestAknSoundView* CBCTestAknSoundView::NewL()
    {
    CBCTestAknSoundView* self = new( ELeave ) CBCTestAknSoundView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestAknSoundView::CBCTestAknSoundView()
    {    
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestAknSoundView::ConstructL()
    {
    BaseConstructL( R_BCTESTAKNSOUND_VIEW );
    
    iContainer = new( ELeave ) CBCTestAknSoundContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );
    
    iTestUtil = CBCTestUtil::NewL();
    
    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestAknSoundInfoCase::NewL( iContainer ), 
        KAknSoundInfoCase );    
    iTestUtil->AddTestCaseL( CBCTestAknSoundSystemCase::NewL( iContainer ), 
        KAknSoundSystemCase );            
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestAknSoundView::~CBCTestAknSoundView()
    {    
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestAknSoundView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestAknSoundView::Id() const
    {
    return KBCTestAknSoundViewId;
    }
    
// ---------------------------------------------------------------------------
// CBCTestAknSoundView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestAknSoundView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestAknSoundView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestAknSoundView::DoDeactivate()
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestAknSoundView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestAknSoundView::HandleCommandL( TInt aCommand )
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
