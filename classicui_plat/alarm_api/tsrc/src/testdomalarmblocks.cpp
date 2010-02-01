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
* Description:  Test alarm_api
*
*/



/*
 *  [INCLUDE FILES]
 */
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eiknotifyalert.h>
#endif //SYMBIAN_ENABLE_SPLIT_HEADERS
#include <eikalmct.h>

#include "testdomalarm.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestdomalarm::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctestdomalarm::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctestdomalarm::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctestdomalarm::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {
        /*
        * ENTRY
        */
        ENTRY( "TestALARMAllFunctionL", Ctestdomalarm::TestALARMAllFunctionL ),

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctestdomalarm::TestALARMAllFunctionL
// -----------------------------------------------------------------------------
//
TInt Ctestdomalarm::TestALARMAllFunctionL( CStifItemParser& /*aItem*/ )
    {
    CEikAlarmControl* contrl = new ( ELeave ) CEikAlarmControl( NULL, NULL );
    CleanupStack::PushL( contrl );
    STIF_ASSERT_NOT_NULL( contrl );
    contrl->ConstructL();
    
    CleanupStack::PopAndDestroy( contrl );

    return KErrNone;
    }

/*
 *   [End of File]
 */
