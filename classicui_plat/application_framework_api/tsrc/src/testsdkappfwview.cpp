/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test application_framework_api
*
*/



// INCLUDE FILES
#include <testsdkappfw.rsg>

#include "testsdkappfwview.h"

// CONSTANTS
const TUid KTestViewId = { 1 };

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CTestSDKAppFWView* CTestSDKAppFWView::NewL()
    {
    CTestSDKAppFWView* self = new( ELeave ) CTestSDKAppFWView;
    CleanupStack::PushL( self );
    self->BaseConstructL( R_TEST_VIEW );
    self->ConstructMenuAndCbaEarlyL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWView::CTestSDKAppFWView
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKAppFWView::CTestSDKAppFWView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CTestSDKAppFWView::ConstructL()
    {
    }

// -----------------------------------------------------------------------------
// Destructor.
// -----------------------------------------------------------------------------
//
CTestSDKAppFWView::~CTestSDKAppFWView()
    { 
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWView::Id
// -----------------------------------------------------------------------------
//
TUid CTestSDKAppFWView::Id() const
    {
    return KTestViewId;
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWView::DoActivateL
// -----------------------------------------------------------------------------
//
void CTestSDKAppFWView::DoActivateL( const TVwsViewId& /*aPrevViewId*/,
    TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWView::DoDeactivate
// -----------------------------------------------------------------------------
//
void CTestSDKAppFWView::DoDeactivate()
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWView::ProtectedAppUi
// -----------------------------------------------------------------------------
//
CAknViewAppUi* CTestSDKAppFWView::ProtectedAppUi() const
    {
    return AppUi();
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWView::ProtectedStatusPane
// -----------------------------------------------------------------------------
//
CEikStatusPane* CTestSDKAppFWView::ProtectedStatusPane() const
    {
    return StatusPane();
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWView::ProtectedCba
// -----------------------------------------------------------------------------
//
CEikButtonGroupContainer* CTestSDKAppFWView::ProtectedCba() const
    {
    return Cba();
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWView::ProtectedViewActivatedL
// -----------------------------------------------------------------------------
//
void CTestSDKAppFWView::ProtectedViewActivatedL( const TVwsViewId& aPrevViewId,
    TUid aCustomMessageId, const TDesC8& aCustomMessage )
    {
    ViewActivatedL( aPrevViewId, aCustomMessageId, aCustomMessage );
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWView::ProtectedViewDeactivated
// -----------------------------------------------------------------------------
//
void CTestSDKAppFWView::ProtectedViewDeactivated()
    {
    ViewDeactivated();
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWView::ProtectedViewScreenDeviceChangedL
// -----------------------------------------------------------------------------
//
TVwsViewIdAndMessage CTestSDKAppFWView::ProtectedViewScreenDeviceChangedL()
    {
    return ViewScreenDeviceChangedL();
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWView::ProtectedMopSupplyObject
// -----------------------------------------------------------------------------
//
TTypeUid::Ptr CTestSDKAppFWView::ProtectedMopSupplyObject( TTypeUid aId )
    {
    return MopSupplyObject( aId );
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWView::ProtectedMopNext
// -----------------------------------------------------------------------------
//
MObjectProvider* CTestSDKAppFWView::ProtectedMopNext()
    {
    return MopNext();
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWView::ProtectedSetEmphasis
// -----------------------------------------------------------------------------
//
void CTestSDKAppFWView::ProtectedSetEmphasis( CCoeControl* aMenuControl,
    TBool aEmphasis )
    {
    SetEmphasis( aMenuControl, aEmphasis );
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWView::ProtectedHandleForegroundEventL
// -----------------------------------------------------------------------------
//
void CTestSDKAppFWView::ProtectedHandleForegroundEventL( TBool aForeground )
    {
    HandleForegroundEventL( aForeground );
    }

//  End of File
