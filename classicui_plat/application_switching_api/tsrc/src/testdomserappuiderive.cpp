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
* Description:  test AknServerApp.h
*
*/



// INCLUDE FILES
#include "testdomserappuiderive.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestDOMSerAppuiDerive::CTestDOMSerAppuiDerive
// -----------------------------------------------------------------------------
CTestDOMSerAppuiDerive::CTestDOMSerAppuiDerive() : CEikServAppUiBase()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestDOMSerAppuiDerive::ServiceUid
// -----------------------------------------------------------------------------
CTestDOMSerAppuiDerive::~CTestDOMSerAppuiDerive()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestDOMSerAppuiDerive::ConstructL
// -----------------------------------------------------------------------------
void CTestDOMSerAppuiDerive::ConstructL()
    {
    CEikServAppUiBase::ConstructL();
    }

// -----------------------------------------------------------------------------
// CTestDOMSerAppuiDerive::InitializeL
// -----------------------------------------------------------------------------
void CTestDOMSerAppuiDerive::InitializeL( TEikServCtrlFactories& aCtrlFactories )
    {
    CEikServAppUiBase::InitializeL( aCtrlFactories );
    }

// -----------------------------------------------------------------------------
// CTestDOMSerAppuiDerive::InitializeL
// -----------------------------------------------------------------------------
void CTestDOMSerAppuiDerive::HandleWsEventL( const TWsEvent& aEvent, CCoeControl* aDestination )
    {
    CEikServAppUiBase::HandleWsEventL( aEvent, aDestination );
    }

// -----------------------------------------------------------------------------
// CTestDOMSerAppuiDerive::Extension
// -----------------------------------------------------------------------------
void CTestDOMSerAppuiDerive::Extension( TUid /*aExtensionUid*/, const TDesC8& /*aBuffer*/, RMessagePtr2 /*aMessage*/ )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestDOMSerAppuiDerive::HandleThreadExitL
// -----------------------------------------------------------------------------
void CTestDOMSerAppuiDerive::HandleThreadExitL( RThread& aThread )
    {
    CEikServAppUiBase::HandleThreadExitL( aThread );
    }

// -----------------------------------------------------------------------------
// CTestDOMSerAppuiDerive::HandleResourceChangeL
// -----------------------------------------------------------------------------
void CTestDOMSerAppuiDerive::HandleResourceChangeL( TInt aType )
    {
    CEikServAppUiBase::HandleResourceChangeL( aType );
    }


