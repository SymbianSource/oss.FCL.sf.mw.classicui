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
* Description:    Test aiwserviceifbase.h
*
*/





/*
 *  [INCLUDE FILES] - do not remove
 */
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include "testdomserviceib.h"
#include <aiwserviceifbase.h>

#include "testserviceifbaseprotected.h"

const TUid KUidInterface = { 0xA000409E };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMSERVICEIB::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestDOMSERVICEIB::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestDOMSERVICEIB::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMSERVICEIB::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestSERVICEIBDestructorL", CTestDOMSERVICEIB::TestSERVICEIBDestructorL ),
        ENTRY( "TestSERVICEIBExtensionInterfaceL", CTestDOMSERVICEIB::TestSERVICEIBExtensionInterfaceL ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }
// -----------------------------------------------------------------------------
// CTestDOMSERVICEIB::TestSERVICEIBDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSERVICEIB::TestSERVICEIBDestructorL( CStifItemParser& /*aItem*/ )
    {
    CTestServiceIfBaseProtected* serviceifbase = new( ELeave ) CTestServiceIfBaseProtected;
    CleanupStack::PushL( serviceifbase );
    STIF_ASSERT_NOT_NULL( serviceifbase );
    CleanupStack::PopAndDestroy( serviceifbase );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMSERVICEIB::TestSERVICEIBExtensionInterface
// -----------------------------------------------------------------------------
//
TInt CTestDOMSERVICEIB::TestSERVICEIBExtensionInterfaceL( CStifItemParser& /*aItem*/ )
    {
    CTestServiceIfBaseProtected* serviceifbase = new( ELeave ) CTestServiceIfBaseProtected;
    CleanupStack::PushL( serviceifbase );
    void* value = serviceifbase->ExtensionInterface( KUidInterface );
    STIF_ASSERT_NULL( value );
    CleanupStack::PopAndDestroy( serviceifbase );
    return KErrNone;
    }

/*
 *   [End of File] - Do not remove
 */
