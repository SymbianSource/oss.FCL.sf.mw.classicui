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
#include "testsdkappfwviewappui.h"

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CTestSDKAppFWViewAppUi* CTestSDKAppFWViewAppUi::NewL()
    {
    CTestSDKAppFWViewAppUi* self = new( ELeave ) CTestSDKAppFWViewAppUi;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWViewAppUi::CTestSDKAppFWViewAppUi
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKAppFWViewAppUi::CTestSDKAppFWViewAppUi()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CTestSDKAppFWViewAppUi::ConstructL()
    {
    }

// -----------------------------------------------------------------------------
// Destructor.
// -----------------------------------------------------------------------------
//
CTestSDKAppFWViewAppUi::~CTestSDKAppFWViewAppUi()
    { 
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWViewAppUi::ProtectedHandleStatusPaneSizeChange
// -----------------------------------------------------------------------------
//
void CTestSDKAppFWViewAppUi::ProtectedHandleStatusPaneSizeChange()
    {
    HandleStatusPaneSizeChange();
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWViewAppUi::ProtectedHandleForegroundEventL
// -----------------------------------------------------------------------------
//
void CTestSDKAppFWViewAppUi::ProtectedHandleForegroundEventL( TBool aForeground )
    {
    HandleForegroundEventL( aForeground );
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFWViewAppUi::ProtectedHandleWsEventL
// -----------------------------------------------------------------------------
//
void CTestSDKAppFWViewAppUi::ProtectedHandleWsEventL( const TWsEvent& aEvent,
    CCoeControl* aDestination )
    {
    HandleWsEventL( aEvent, aDestination );
    }

//  End of File
