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
* Description:  test transition_effect_utilities_api
*
*/


// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testdomtransitioneffectutilities.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomTransitionEffectUtilities::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDomTransitionEffectUtilities::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestTUAddObserverL", CTestDomTransitionEffectUtilities::TestTUAddObserverL ),
        ENTRY( "TestTURemoveObserverL", CTestDomTransitionEffectUtilities::TestTURemoveObserverL ),
        ENTRY( "TestTUGetState", CTestDomTransitionEffectUtilities::TestTUGetState ),
        ENTRY( "TestTUGetState", CTestDomTransitionEffectUtilities::TestTUGetState ),
        ENTRY( "TestTUSetData", CTestDomTransitionEffectUtilities::TestTUSetData ),
        ENTRY( "TestTUGetData", CTestDomTransitionEffectUtilities::TestTUGetData ),
        ENTRY( "TestTURemoveData", CTestDomTransitionEffectUtilities::TestTURemoveData ),
        ENTRY( "TestTUSetAllParents", CTestDomTransitionEffectUtilities::TestTUSetAllParents ),
        ENTRY( "TestTUTransitionsEnabled", CTestDomTransitionEffectUtilities::TestTUTransitionsEnabled ),
        ENTRY( "TestTUMakeVisibleSubComponents", CTestDomTransitionEffectUtilities::TestTUMakeVisibleSubComponents ),
        ENTRY( "TestTUGetDemarcation", CTestDomTransitionEffectUtilities::TestTUGetDemarcation ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDomTransitionEffectUtilities::TestTUAddObserverL
// -----------------------------------------------------------------------------
//
TInt CTestDomTransitionEffectUtilities::TestTUAddObserverL( CStifItemParser& /*aItem*/ )
    {
    CTestDomUtilitiesObserver* observer = new ( ELeave ) CTestDomUtilitiesObserver;
    CleanupStack::PushL( observer );
    CAknTransitionUtils::AddObserver( observer, CAknTransitionUtils::EEventWsBufferRedirection );
    CleanupStack::PopAndDestroy( observer );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomTransitionEffectUtilities::TestTURemoveObserverL
// -----------------------------------------------------------------------------
//
TInt CTestDomTransitionEffectUtilities::TestTURemoveObserverL( CStifItemParser& /*aItem*/ )
    {
    CTestDomUtilitiesObserver* observer = new ( ELeave ) CTestDomUtilitiesObserver;
    CleanupStack::PushL( observer );
    TInt rec = CAknTransitionUtils::RemoveObserver( observer, CAknTransitionUtils::EEventWsBufferRedirection );
    CleanupStack::PopAndDestroy( observer );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomTransitionEffectUtilities::TestTUGetState
// -----------------------------------------------------------------------------
//
TInt CTestDomTransitionEffectUtilities::TestTUGetState( CStifItemParser& /*aItem*/ )
    {
    TInt stat;
    CAknTransitionUtils::GetState( CAknTransitionUtils::EEventWsBufferRedirection, &stat );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomTransitionEffectUtilities::TestTUSetData
// -----------------------------------------------------------------------------
//
TInt CTestDomTransitionEffectUtilities::TestTUSetData( CStifItemParser& /*aItem*/ )
    {
    TInt skey( 0 ),sdata( 0 );
    CAknTransitionUtils::SetData( skey, &sdata );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomTransitionEffectUtilities::TestTUGetData
// -----------------------------------------------------------------------------
//
TInt CTestDomTransitionEffectUtilities::TestTUGetData( CStifItemParser& /*aItem*/ )
    {
    TInt skey( 0 );
    CAknTransitionUtils::GetData( skey );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomTransitionEffectUtilities::TestTURemoveData
// -----------------------------------------------------------------------------
//
TInt CTestDomTransitionEffectUtilities::TestTURemoveData( CStifItemParser& /*aItem*/ )
    {
    TInt skey( 0 );
    CAknTransitionUtils::RemoveData( skey );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomTransitionEffectUtilities::TestTUSetAllParents
// -----------------------------------------------------------------------------
//
TInt CTestDomTransitionEffectUtilities::TestTUSetAllParents( CStifItemParser& /*aItem*/ )
    {
    CAknTransitionUtils::SetAllParents( iContainer );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomTransitionEffectUtilities::TestTUTransitionsEnabled
// -----------------------------------------------------------------------------
//
TInt CTestDomTransitionEffectUtilities::TestTUTransitionsEnabled( CStifItemParser& /*aItem*/ )
    {
    TInt sdata( 0 );
    CAknTransitionUtils::TransitionsEnabled( sdata );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestDomTransitionEffectUtilities::TestTUMakeVisibleSubComponents
// -----------------------------------------------------------------------------
//
TInt CTestDomTransitionEffectUtilities::TestTUMakeVisibleSubComponents( CStifItemParser& /*aItem*/ )
    {
    CAknTransitionUtils::MakeVisibleSubComponents( iContainer,CAknTransitionUtils::EForceInvisible );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomTransitionEffectUtilities::TestTUGetDemarcation
// -----------------------------------------------------------------------------
//
TInt CTestDomTransitionEffectUtilities::TestTUGetDemarcation( CStifItemParser& /*aItem*/ )
    {
    TRect rect;
    CAknTransitionUtils::GetDemarcation( CAknTransitionUtils::EOptionsMenu, rect );
    return KErrNone;
    }


//  [End of File]
