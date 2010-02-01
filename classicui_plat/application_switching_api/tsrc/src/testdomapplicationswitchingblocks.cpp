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
* Description:  test EIKSRVUI.H
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <uikon/eiksrvui.h>
#include <coemain.h>
#include <documenthandler.h>
#include <eikdialg.h>

#include "testdomapplicationswitching.h"
#include "testdomserappuiderive.h"

const TInt KLength = 50;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {
        ENTRY( "TestSAUBNewLC", CTestDOMApplicationSwitching::TestSAUBNewLC ),
        ENTRY( "TestSAUBDeconstructor", CTestDOMApplicationSwitching::TestSAUBDeconstructor ),
        ENTRY( "TestSAUBNotifyAlarmServerOfTaskChangeL", CTestDOMApplicationSwitching::TestSAUBNotifyAlarmServerOfTaskChangeL ),
        ENTRY( "TestSAUBEnableTaskListL", CTestDOMApplicationSwitching::TestSAUBEnableTaskListL ),
        ENTRY( "TestSAUBLaunchTaskListL", CTestDOMApplicationSwitching::TestSAUBLaunchTaskListL ),
        ENTRY( "TestSAUBCycleTasksL", CTestDOMApplicationSwitching::TestSAUBCycleTasksL ),
        ENTRY( "TestSAUBSetStatusPaneFlags", CTestDOMApplicationSwitching::TestSAUBSetStatusPaneFlags ),
        ENTRY( "TestSAUBSetStatusPaneLayoutL", CTestDOMApplicationSwitching::TestSAUBSetStatusPaneLayoutL ),
        ENTRY( "TestSAUBBlankScreen", CTestDOMApplicationSwitching::TestSAUBBlankScreen ),
        ENTRY( "TestSAUBUnblankScreen", CTestDOMApplicationSwitching::TestSAUBUnblankScreen ),
        ENTRY( "TestSAUBShutdownAppsL", CTestDOMApplicationSwitching::TestSAUBShutdownAppsL ),
        ENTRY( "TestSAUBHandleForegroundEventL", CTestDOMApplicationSwitching::TestSAUBHandleForegroundEventL ),
        ENTRY( "TestSAUBAlertGroupWin", CTestDOMApplicationSwitching::TestSAUBAlertGroupWin ),
        ENTRY( "TestSAUBBringAlertGroupWinForwards", CTestDOMApplicationSwitching::TestSAUBBringAlertGroupWinForwards ),
        ENTRY( "TestSAUBConstruct", CTestDOMApplicationSwitching::TestSAUBConstruct ),
        ENTRY( "TestSAUBInitialize", CTestDOMApplicationSwitching::TestSAUBInitialize ),
        ENTRY( "TestSAUBCEikServAppUiBase", CTestDOMApplicationSwitching::TestSAUBCEikServAppUiBase ),
        ENTRY( "TestSAUBHandleWsEventL", CTestDOMApplicationSwitching::TestSAUBHandleWsEventL ),
        ENTRY( "TestSAUBHandleThreadExit", CTestDOMApplicationSwitching::TestSAUBHandleThreadExit ),
        ENTRY( "TestSAUBHandleResourceChangeL", CTestDOMApplicationSwitching::TestSAUBHandleResourceChangeL ),
        ENTRY( "TestSAUSuppressAppSwitching", CTestDOMApplicationSwitching::TestSAUSuppressAppSwitching ),
        ENTRY( "TestSAUActivateDisplayIfNeeded", CTestDOMApplicationSwitching::TestSAUActivateDisplayIfNeeded ),
        ENTRY( "TestSAUCreateSessionL", CTestDOMApplicationSwitching::TestSAUCreateSessionL ),
        ENTRY( "TestSAUHideApplicationFromFswL", CTestDOMApplicationSwitching::TestSAUHideApplicationFromFswL ),
        ENTRY( "TestSAUStartNewServerApplication", CTestDOMApplicationSwitching::TestSAUStartNewServerApplication ),
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBNewLC
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBNewLC( CStifItemParser& /*aItem*/ )
    {
    CEikServAppUiBase* appuiBase = CEikServAppUiBase::NewLC();
    STIF_ASSERT_NULL( appuiBase );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBDeconstructor
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBDeconstructor( CStifItemParser& /*aItem*/ )
    {
// when the mobile turn off,will it be invoked?
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBNotifyAlarmServerOfTaskChangeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBNotifyAlarmServerOfTaskChangeL( CStifItemParser& /*aItem*/ )
    {
    MEikServAppUiSessionHandler* appui = static_cast<CEikServAppUi*>( iEnv->AppUi() );
    appui->NotifyAlarmServerOfTaskChangeL();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBEnableTaskListL
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBEnableTaskListL( CStifItemParser& /*aItem*/ )
    {
    //the function will leave directly
    CEikServAppUi* appui = static_cast<CEikServAppUi*>( iEnv->AppUi() );
    TRAPD( err, appui->CEikServAppUiBase::EnableTaskListL() );
    STIF_ASSERT_TRUE( err == KErrNotSupported );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBLaunchTaskListL
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBLaunchTaskListL( CStifItemParser& /*aItem*/ )
    {
    //the function will leave directly
    CEikServAppUi* appui = static_cast<CEikServAppUi*>( iEnv->AppUi() );
    TRAPD( err, appui->CEikServAppUiBase::LaunchTaskListL() );
    STIF_ASSERT_TRUE( err == KErrNotSupported );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBCycleTasksL
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBCycleTasksL( CStifItemParser& /*aItem*/ )
    {
    MEikServAppUiSessionHandler* hand = static_cast<CEikServAppUi*>( iEnv->AppUi() );
    hand->CycleTasksL( EBackwards );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBSetStatusPaneFlags
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBSetStatusPaneFlags( CStifItemParser& /*aItem*/ )
    {
    //the function will leave directly
    CEikServAppUi* appui = static_cast<CEikServAppUi*>( iEnv->AppUi() );
    TRAPD( err, appui->CEikServAppUiBase::SetStatusPaneFlags( 0 ) );
    STIF_ASSERT_TRUE( err == KErrNotSupported );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBSetStatusPaneLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBSetStatusPaneLayoutL( CStifItemParser& /*aItem*/ )
    {
    //the function will leave directly
    CEikServAppUi* appui = static_cast<CEikServAppUi*>( iEnv->AppUi() );
    TRAPD( err, appui->CEikServAppUiBase::SetStatusPaneLayoutL( 0 ) );
    STIF_ASSERT_TRUE( err == KErrNotSupported );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBBlankScreen
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBBlankScreen( CStifItemParser& /*aItem*/ )
    {
    //the function will leave directly
    CEikServAppUi* appui = static_cast<CEikServAppUi*>( iEnv->AppUi() );
    TRAPD( err, appui->CEikServAppUiBase::BlankScreenL() );
    STIF_ASSERT_TRUE( err == KErrNotSupported );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBUnblankScreen
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBUnblankScreen( CStifItemParser& /*aItem*/ )
    {
    //the function will leave directly
    CEikServAppUi* appui = static_cast<CEikServAppUi*>( iEnv->AppUi() );
    TRAPD( err, appui->CEikServAppUiBase::UnblankScreen() );
    STIF_ASSERT_TRUE( err == KErrNotSupported );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBShutdownAppsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBShutdownAppsL( CStifItemParser& /*aItem*/ )
    {
    CEikServAppUi* appui = static_cast<CEikServAppUi*>( iEnv->AppUi() );
    
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEnv->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "\\system\\apps\\testapplicationswitching.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEnv->FsSession();
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType;
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    TInt flag = documentHandler->OpenFileL( file, dataType );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    const TInt KTextUid = 0x1000599d;
    TUid textUid( TUid::Uid( KTextUid ) );
    RMessage2 message;
    const TInt timeoutInMicroseconds = 10000000;
    appui->CEikServAppUiBase::ShutdownAppsL( textUid, message, timeoutInMicroseconds );
    
    //the simulator will switch off( standby )
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBHandleForegroundEventL
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBHandleForegroundEventL( CStifItemParser& /*aItem*/ )
    {
    CEikServAppUi* appui = static_cast<CEikServAppUi*>( iEnv->AppUi() );
    appui->CEikServAppUiBase::HandleForegroundEventL( EFalse );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBAlertGroupWin
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBAlertGroupWin( CStifItemParser& /*aItem*/ )
    {
    CEikServAppUi* appui = static_cast<CEikServAppUi*>( iEnv->AppUi() );
    RWindowGroup windwoGroup = appui->CEikServAppUiBase::AlertGroupWin();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBBringAlertGroupWinForwards
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBBringAlertGroupWinForwards( CStifItemParser& /*aItem*/ )
    {
    CEikServAppUi* appui = static_cast<CEikServAppUi*>( iEnv->AppUi() );
    
    appui->CEikServAppUiBase::BringAlertGroupWinForwards( ETrue );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBConstruct
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBConstruct( CStifItemParser& /*aItem*/ )
    {
    //when the simulator launched the function will be invoked
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBInitialize
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBInitialize( CStifItemParser& /*aItem*/ )
    {
    //when the simulator launched the function will be invoked
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBCEikServAppUiBase
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBCEikServAppUiBase( CStifItemParser& /*aItem*/ )
    {
    //when the simulator launched the function will be invoked
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBHandleWsEventL
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBHandleWsEventL( CStifItemParser& /*aItem*/ )
    {
    CTestDOMSerAppuiDerive* appui = static_cast<CTestDOMSerAppuiDerive*>( iEnv->AppUi() );
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    TWsEvent wsEvent;
    appui->HandleWsEventL( wsEvent, dialog );
    
    CleanupStack::PopAndDestroy( dialog );
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBHandleThreadExit
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBHandleThreadExit( CStifItemParser& /*aItem*/ )
    {
    //when the simulator launched the function will be invoked
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUBHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUBHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CTestDOMSerAppuiDerive* appui = static_cast<CTestDOMSerAppuiDerive*>( iEnv->AppUi() );
    appui->HandleResourceChangeL( 0 );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUSuppressAppSwitching
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUSuppressAppSwitching( CStifItemParser& /*aItem*/ )
    {
    CEikServAppUi* appui = static_cast<CEikServAppUi*>( iEnv->AppUi() );
    appui->SuppressAppSwitching( ETrue );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUActivateDisplayIfNeeded
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUActivateDisplayIfNeeded( CStifItemParser& /*aItem*/ )
    {
    CEikServAppUi* appui = static_cast<CEikServAppUi*>( iEnv->AppUi() );
    appui->ActivateDisplayIfNeeded();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUCreateSessionL
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUCreateSessionL( CStifItemParser& /*aItem*/ )
    {
    CEikServAppUi* appui = static_cast<CEikServAppUi*>( iEnv->AppUi() );
    CEikServAppUiSession* session = appui->CreateSessionL();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUHideApplicationFromFswL
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUHideApplicationFromFswL( CStifItemParser& /*aItem*/ )
    {
    CEikServAppUi* appui = static_cast<CEikServAppUi*>( iEnv->AppUi() );
    appui->HideApplicationFromFswL( 0x2001CB80, EFalse );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMApplicationSwitching::TestSAUStartNewServerApplication
// -----------------------------------------------------------------------------
//
TInt CTestDOMApplicationSwitching::TestSAUStartNewServerApplication( CStifItemParser& /*aItem*/ )
    {
    //when the simulator launched the function will be invoked
    return KErrNone;
    
    }



//  [End of File]

