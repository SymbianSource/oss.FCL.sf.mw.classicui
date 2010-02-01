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
* Description:  test AknKeyRotator.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknkeyrotator.h>

#include "testdomkeyrotator.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMKeyRotator::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMKeyRotator::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestKRFCreateAknKeyRotatorL", CTestDOMKeyRotator::TestKRFCreateAknKeyRotatorL ),
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestDOMKeyRotator::TestKRFCreateAknKeyRotatorL
// -----------------------------------------------------------------------------
//
TInt CTestDOMKeyRotator::TestKRFCreateAknKeyRotatorL( CStifItemParser& /*aItem*/ )
    {
    CAknKeyRotator* rotator = AknKeyRotatorFactory::CreateAknKeyRotatorL();
    CleanupStack::PushL( rotator );
    
    STIF_ASSERT_NOT_NULL( rotator );
    CleanupStack::PopAndDestroy( rotator );
    
    return KErrNone;
    
    }

//  [End of File]
