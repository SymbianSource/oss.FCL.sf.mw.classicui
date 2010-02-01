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
* Description:  test AknTransEffect.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akntranseffect.h>
#include <e32const.h>

#include "testdomtransitioneffectpara.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMTransitionEffectPara::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMTransitionEffectPara::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestTETParameterPL", CTestDOMTransitionEffectPara::TestTETParameterPL ),
        ENTRY( "TestTETParameterL", CTestDOMTransitionEffectPara::TestTETParameterL ),
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestDOMTransitionEffectPara::TestTETParameterPL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTransitionEffectPara::TestTETParameterPL( CStifItemParser& /*aItem*/ )
    {
    const TUid KNotDefinedUid = {KNullUidValue};
    AknTransEffect::TParameter parameter( KNotDefinedUid, KNotDefinedUid, AknTransEffect::TParameter::EFlagNone );
    STIF_ASSERT_NOT_NULL( &parameter );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMTransitionEffectPara::TestTETParameterL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTransitionEffectPara::TestTETParameterL( CStifItemParser& /*aItem*/ )
    {
    AknTransEffect::TParameter parameter;
    STIF_ASSERT_NOT_NULL( &parameter );
    
    return KErrNone;
    
    }
//  [End of File]
