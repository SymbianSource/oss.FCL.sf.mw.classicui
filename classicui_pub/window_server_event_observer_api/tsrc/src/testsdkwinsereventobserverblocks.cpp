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
* Description:  test AknWsEventObserver.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknwseventobserver.h>
#include <aknappui.h>

#include "testsdkwinsereventobserver.h"
#include "testsdkeventobserver.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKWinSerEventObserver::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKWinSerEventObserver::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestWEMAddObserverL", CTestSDKWinSerEventObserver::TestWEMAddObserverL ),
        ENTRY( "TestWEMRemoveObserverL", CTestSDKWinSerEventObserver::TestWEMRemoveObserverL ),
        ENTRY( "TestWEMHandleWsEventL", CTestSDKWinSerEventObserver::TestWEMHandleWsEventL ),
        ENTRY( "TestWEMEnableL", CTestSDKWinSerEventObserver::TestWEMEnableL ),
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKWinSerEventObserver::TestWEMAddObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKWinSerEventObserver::TestWEMAddObserverL( CStifItemParser& /*aItem*/ )
    {
    CAknAppUi* appUi = static_cast<CAknAppUi*>( CCoeEnv::Static()->AppUi() );
    
    CAknWsEventMonitor* monitor  = appUi->EventMonitor();
    
    CTestSDKEventObserver* observer = CTestSDKEventObserver::NewL();
    CleanupStack::PushL( observer );
    
    monitor->AddObserverL( observer );
    
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKWinSerEventObserver::TestWEMRemoveObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKWinSerEventObserver::TestWEMRemoveObserverL( CStifItemParser& /*aItem*/ )
    {
    CAknAppUi* appUi = static_cast<CAknAppUi*>( CCoeEnv::Static()->AppUi() );
    
    CAknWsEventMonitor* monitor  = appUi->EventMonitor();
    
    CTestSDKEventObserver* observer = CTestSDKEventObserver::NewL();
    CleanupStack::PushL( observer );
    
    monitor->AddObserverL( observer );
    monitor->RemoveObserver( observer );
    
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKWinSerEventObserver::TestWEMHandleWsEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKWinSerEventObserver::TestWEMHandleWsEventL( CStifItemParser& /*aItem*/ )
    {
    CAknAppUi* appUi = static_cast<CAknAppUi*>( CCoeEnv::Static()->AppUi() );
    
    CAknWsEventMonitor* monitor  = appUi->EventMonitor();
    
    CTestSDKEventObserver* observer = CTestSDKEventObserver::NewL();
    CleanupStack::PushL( observer );
    
    monitor->AddObserverL( observer );
    
    TWsEvent event;
    monitor->HandleWsEventL( event, observer );
    
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKWinSerEventObserver::TestWEMEnableL
// -----------------------------------------------------------------------------
//
TInt CTestSDKWinSerEventObserver::TestWEMEnableL( CStifItemParser& /*aItem*/ )
    {
    CAknAppUi* appUi = static_cast<CAknAppUi*>( CCoeEnv::Static()->AppUi() );
    
    CAknWsEventMonitor* monitor  = appUi->EventMonitor();
    
    CTestSDKEventObserver* observer = CTestSDKEventObserver::NewL();
    CleanupStack::PushL( observer );
    
    monitor->AddObserverL( observer );
    monitor->Enable( EFalse );
    
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    
    }

//  [End of File]
