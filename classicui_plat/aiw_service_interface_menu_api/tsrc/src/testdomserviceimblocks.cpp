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
* Description:    Test aiwserviceifmenu
*
*/





/*
 *  [INCLUDE FILES] - do not remove
 */
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aiwserviceifmenu.h>

#include "testserviceifmenuprotected.h"
#include "testdomserviceim.h"

const TUid KUidInterface = { 0xA000409E };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMSERVICEIM::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestDOMSERVICEIM::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestDOMSERVICEIM::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMSERVICEIM::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY("TestSERVICEIMDestructorL", CTestDOMSERVICEIM::TestSERVICEIMDestructorL ),
        ENTRY("TestSERVICEIMMenuPaneL", CTestDOMSERVICEIM::TestSERVICEIMMenuPaneL ),
        ENTRY("TestSERVICEIMExtensionInterfaceL", CTestDOMSERVICEIM::TestSERVICEIMExtensionInterfaceL ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMSERVICEIM::TestSERVICEIMDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSERVICEIM::TestSERVICEIMDestructorL( CStifItemParser& /*Item*/ )
    {
    CTestServiceIfMenu* serviceifmenu = new( ELeave ) CTestServiceIfMenu;
    CleanupStack::PushL( serviceifmenu );
    STIF_ASSERT_NOT_NULL( serviceifmenu );
    
    CleanupStack::Pop( serviceifmenu );
    delete serviceifmenu;
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMSERVICEIM::TestSERVICEIMMenuPaneL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSERVICEIM::TestSERVICEIMMenuPaneL( CStifItemParser& /*Item*/ )
    {
    CTestServiceIfMenu* serviceifmenu = new( ELeave ) CTestServiceIfMenu;
    CleanupStack::PushL( serviceifmenu );
    serviceifmenu->MenuPane();
    CleanupStack::PopAndDestroy( serviceifmenu );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMSERVICEIB::TestSERVICEIBExtensionInterface
// -----------------------------------------------------------------------------
//
TInt CTestDOMSERVICEIM::TestSERVICEIMExtensionInterfaceL( CStifItemParser& /*aItem*/ )
    {
    CTestServiceIfMenu* serviceifmenu = new( ELeave ) CTestServiceIfMenu;
    CleanupStack::PushL( serviceifmenu );
    void* value = serviceifmenu->ExtensionInterface( KUidInterface );
    STIF_ASSERT_NULL( value );
    CleanupStack::PopAndDestroy( serviceifmenu );

    return KErrNone;
    }

/*
 *   [End of File] - Do not remove
 */
