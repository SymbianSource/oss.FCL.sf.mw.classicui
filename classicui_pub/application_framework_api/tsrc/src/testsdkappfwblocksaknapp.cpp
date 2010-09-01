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
* Description:  Test aknApp.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkappfw.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppPreDocConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppPreDocConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppPreDocConstructL, "TestAppPreDocConstructL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppPreDocConstructL );
    // Print to log file
    iLog->Log( KTestAppPreDocConstructL );

    CAknApplication* app = static_cast<CAknApplication*>
        ( iEikonEnvPointer->EikAppUi()->Application() );
    app->CAknApplication::PreDocConstructL();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppOpenIniFileLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppOpenIniFileLC( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppOpenIniFileLC, "TestAppOpenIniFileLC" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppOpenIniFileLC );
    // Print to log file
    iLog->Log( KTestAppOpenIniFileLC );

    CAknApplication* app = static_cast<CAknApplication*>
        ( iEikonEnvPointer->EikAppUi()->Application() );
    RFs& fs = iEikonEnvPointer->FsSession();
    STIF_ASSERT_LEAVES( app->OpenIniFileLC( fs ) );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppNewAppServerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppNewAppServerL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppNewAppServerL, "TestAppNewAppServerL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppNewAppServerL );
    // Print to log file
    iLog->Log( KTestAppNewAppServerL );

    CAknApplication* app = static_cast<CAknApplication*>
        ( iEikonEnvPointer->EikAppUi()->Application() );
    CApaAppServer* server = NULL;
    app->NewAppServerL( server );
    CleanupStack::PushL( server );
    CleanupStack::PopAndDestroy( server );

    return KErrNone;

    }

//  [End of File]
