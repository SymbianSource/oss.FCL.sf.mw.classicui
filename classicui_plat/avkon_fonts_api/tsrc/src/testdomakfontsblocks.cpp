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
* Description:  Test avkon_fonts_api
*
*/



/*
 * [INCLUDE FILES]
 */
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testdomakfonts.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestdomakfonts::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestDOMAKFONTS::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctestdomakfonts::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMAKFONTS::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY("TestSTFONTNewL", CTestDOMAKFONTS::TestSTFONTNewL ),
        ENTRY("TestSTFONTFontL", CTestDOMAKFONTS::TestSTFONTFontL ),
        ENTRY("TestSTFONTUidL", CTestDOMAKFONTS::TestSTFONTUidL ),
        ENTRY("TestLOFONTNewL", CTestDOMAKFONTS::TestLOFONTNewL ),
        ENTRY("TestLOFONTFontIdL", CTestDOMAKFONTS::TestLOFONTFontIdL ),
        ENTRY("TestLOFONTUpdateIdL", CTestDOMAKFONTS::TestLOFONTUpdateIdL ),
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );
    }

/*
 * [End of File]
 */
