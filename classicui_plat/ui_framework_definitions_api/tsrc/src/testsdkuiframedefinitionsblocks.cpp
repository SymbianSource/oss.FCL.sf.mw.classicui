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
* Description:  test akndef.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akndef.h>
#include <vwsdef.h>

#include "testsdkuiframedefinitions.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKUiFrameDefinitions::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFrameDefinitions::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestADGetPhoneIdleViewId", CTestSDKUiFrameDefinitions::TestADGetPhoneIdleViewId ),
        
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKUiFrameDefinitions::TestADGetPhoneIdleViewId
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFrameDefinitions::TestADGetPhoneIdleViewId( CStifItemParser& /*aItem*/ )
    {
    TVwsViewId viewId;
    
    TInt flag = AknDef::GetPhoneIdleViewId( viewId );
    
    const TInt KAppUid = 0x2001CB80;
    TUid appUid( TUid::Uid( KAppUid ) );
    
    STIF_ASSERT_TRUE( appUid.iUid = viewId.iAppUid.iUid );
    STIF_ASSERT_TRUE( 0 == flag );
    
    return KErrNone;
    }


//  [End of File]
