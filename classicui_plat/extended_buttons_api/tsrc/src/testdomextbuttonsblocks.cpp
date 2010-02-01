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
* Description:  test function implement of CTestDomExtButtons
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testdomextbuttons.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtButtons::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDomExtButtons::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function.

        // For EikSoftkeyImage in EikSoftkeyImage.h
        ENTRY( "TestEikSoftkeyImageSetImageL",
                CTestDomExtButtons::TestEikSoftkeyImageSetImageL ),
        ENTRY( "TestEikSoftkeyImageSetLabelL",
                CTestDomExtButtons::TestEikSoftkeyImageSetLabelL ),

        // For EikSoftkeyPostingTransparency in eiksoftkeypostingtransparency.h
        ENTRY( "TestEikSoftkeyPostTransMakeTransparentL",
                CTestDomExtButtons::TestEikSoftkeyPostTransMakeTransparentL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


//  [End of File]
