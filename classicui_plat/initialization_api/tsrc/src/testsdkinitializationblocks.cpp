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
* Description:  test EIKCOLIB.H EIKCTLIB.H
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkinitialization.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKInitialization::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKInitialization::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestCCLResourceFile", CTestSDKInitialization::TestCCLResourceFile ),
        ENTRY( "TestCCLControlFactory", CTestSDKInitialization::TestCCLControlFactory ),
        ENTRY( "TestCCLButtonGroupFactory", CTestSDKInitialization::TestCCLButtonGroupFactory ),
        ENTRY( "TestAUFCEikAppUiFactoryL", CTestSDKInitialization::TestAUFCEikAppUiFactoryL ),
        ENTRY( "TestAUFTouchPaneL", CTestSDKInitialization::TestAUFTouchPaneL ),
        ENTRY( "TestAUFPopupToolbarL", CTestSDKInitialization::TestAUFPopupToolbarL ),
        ENTRY( "TestAUFCurrentPopupToolbarL", CTestSDKInitialization::TestAUFCurrentPopupToolbarL ),
        ENTRY( "TestAUFSetViewPopupToolbarL", CTestSDKInitialization::TestAUFSetViewPopupToolbarL ),
        ENTRY( "TestAUFCurrentFixedToolbarL", CTestSDKInitialization::TestAUFCurrentFixedToolbarL ),
        ENTRY( "TestAUFSetViewFixedToolbarL", CTestSDKInitialization::TestAUFSetViewFixedToolbarL ),
        ENTRY( "TestCLResourceFile", CTestSDKInitialization::TestCLResourceFile ),
        ENTRY( "TestCLControlFactory", CTestSDKInitialization::TestCLControlFactory ),
        ENTRY( "TestCLInitializeL", CTestSDKInitialization::TestCLInitializeL ),
        ENTRY( "TestCLButtonGroupFactory", CTestSDKInitialization::TestCLButtonGroupFactory ),
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }



//  [End of File]
