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
* Description:  for testing APIs in aknanimview.h
*
*/


#include <aknviewappui.h>
#include <bctestdomaiwakn.rsg>

#include "bctestdomaiwakn.hrh"
#include "bctestdomaknanimview.h" 

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknAnimatedView* CBCTestDomAknAnimatedView::NewLC( )
    {
    CBCTestDomAknAnimatedView* self = 
        new( ELeave ) CBCTestDomAknAnimatedView();
    CleanupStack::PushL( self );
    self->ConstructL( );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknAnimatedView::CBCTestDomAknAnimatedView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomAknAnimatedView::ConstructL( )
    {
    BaseConstructL( R_BCTESTDOMAIWAKN_VIEW );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknAnimatedView::~CBCTestDomAknAnimatedView()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknAnimatedView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestDomAknAnimatedView::Id() const
    {
    return KBCTestAknAnimatedViewId;
    }

// ---------------------------------------------------------------------------
// From CAknAnimatedView
// CBCTestDomAknAnimatedView::AknViewActivatedL
// ---------------------------------------------------------------------------
//
EXPORT_C void CBCTestDomAknAnimatedView::AknViewActivatedL(
	const TVwsViewId& aPrevViewId,
	TUid aCustomMessageId,
	const TDesC8& aCustomMessage )
    {
    CAknAnimatedView::AknViewActivatedL(
        aPrevViewId,
        aCustomMessageId,
        aCustomMessage);
    }
    
// ---------------------------------------------------------------------------
// From CAknAnimatedView
// CBCTestDomAknAnimatedView::PreAnimateSetup
// ---------------------------------------------------------------------------
//
EXPORT_C void CBCTestDomAknAnimatedView::PreAnimateSetup()
    {
    CAknAnimatedView::PreAnimateSetup();
    }
 	
// ---------------------------------------------------------------------------
// From CAknAnimatedView
// CBCTestDomAknAnimatedView::PostAnimateSetup
// ---------------------------------------------------------------------------
// 	
EXPORT_C void CBCTestDomAknAnimatedView::PostAnimateSetup()
    {
    CAknAnimatedView::PostAnimateSetup();
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAknAnimatedView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestDomAknAnimatedView::DoActivateL( const TVwsViewId&, TUid, 
    const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknAnimatedView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestDomAknAnimatedView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknAnimatedView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestDomAknAnimatedView::HandleCommandL( TInt /*aCommand*/ )
    {
 
    }
