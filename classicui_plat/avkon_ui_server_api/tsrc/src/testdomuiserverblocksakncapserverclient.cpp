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
* Description:  test avkon_ui_server_api
*
*/



// [INCLUDE FILES]
#include "testdomuiserver.h"

// CONSTANTS
const TUid KUidTestAiwAkn = { 0xA000409E }; // UID of the application
const TUid KTestAiwAknViewId = { 1 };
const TInt KBufSize = 64;


_LIT(KGlobalNoteText,"ShowGlobalNoteL");

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSConnectAndSendAppsKeySuppress
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSConnectAndSendAppsKeySuppress( CStifItemParser& /*aItem*/ )
    {
    iUiServer->ConnectAndSendAppsKeySuppress( ETrue );
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSHideApplicationFromFsw
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSHideApplicationFromFsw( CStifItemParser& /*aItem*/ )
    {
    iUiServer->HideApplicationFromFsw( ETrue,KUidTestAiwAkn.iUid );
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSUnlockMedia
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSUnlockMedia( CStifItemParser& /*aItem*/ )
    {
    TRequestStatus status;
    iUiServer->UnlockMedia( EDriveB, ETrue, status );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSCancelUnlockMedia
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSCancelUnlockMedia( CStifItemParser& /*aItem*/ )
    {
    iUiServer->CancelUnlockMedia();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSCancelUnlockMedia
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSEnableTaskList( CStifItemParser& /*aItem*/ )
    {
    iUiServer->EnableTaskList( ETrue );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSMakeTaskListVisible
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSMakeTaskListVisible( CStifItemParser& /*aItem*/ )
    {
    iUiServer->MakeTaskListVisible( ETrue );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSUpdateTaskList
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSUpdateTaskList( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSShutdownAppsL
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSShutdownAppsL( CStifItemParser& /*aItem*/ )
    {
    TRequestStatus status;
    TUid KRequesterUID = { 0xA000409E };
    TInt timeoutInMicroseconds = 5;
    iUiServer->UpdateTaskList();
    iUiServer->ShutdownApps( KRequesterUID, timeoutInMicroseconds, status );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSCancelShutdownApps
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSCancelShutdownApps( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->CancelShutdownApps();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSSetSgcParams
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSSetSgcParams( CStifItemParser& /*aItem*/ )
    {
    TBitFlags appFlags;
    TInt KAknAppUiBaseFlag = 4 ;
    appFlags.Assign( KAknAppUiBaseFlag, EFalse);
    TInt spLayout = 0;
    TInt spFlags = 0;
    iUiServer->UpdateTaskList();
    iUiServer->SetSgcParams( 0,appFlags,spLayout,spFlags );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSSetSgcParamScreenMode
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSSetSgcParamScreenMode( CStifItemParser& /*aItem*/ )
    {
    TInt screenMode = KAknScreenModeUnset;
    TBitFlags appFlags;
    TInt KAknAppUiBaseFlag = 4 ;
    appFlags.Assign( KAknAppUiBaseFlag, EFalse);
    TInt spLayout = 0;
    iUiServer->UpdateTaskList();
    iUiServer->SetSgcParams( 
    CCoeEnv::Static()->RootWin().Identifier(),
    appFlags,
    spLayout,
    screenMode );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSBlockServerStatusPaneRedraws
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSBlockServerStatusPaneRedraws( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->BlockServerStatusPaneRedraws();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSRedrawServerStatusPane
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSRedrawServerStatusPane( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->RedrawServerStatusPane();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSPrepareForAppExit
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSPrepareForAppExit( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->PrepareForAppExit( CCoeEnv::Static()->RootWin().Identifier() );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSSetSystemFaded
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSSetSystemFaded( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->SetSystemFaded( ETrue );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSIsSystemFaded
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSIsSystemFaded( CStifItemParser& /*aItem*/ )
    {
    TBool systemFade = EFalse;
    iUiServer->UpdateTaskList();
    iUiServer->IsSystemFaded( systemFade );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSConnect
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSConnect( CStifItemParser& /*aItem*/ )
    {
    TInt ser = iUiServer->Connect();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSRelinquishPriorityToForegroundApp
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSRelinquishPriorityToForegroundApp( CStifItemParser& /*aItem*/ )
    {
    iUiServer->RelinquishPriorityToForegroundApp();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSGetPackedConfigL 
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSGetPackedConfigL( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->GetPackedConfigL();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSMoveAppInZOrder
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSMoveAppInZOrder( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->MoveAppInZOrder( 2,ETrue );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSSetStatusPaneFlags
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSSetStatusPaneFlags( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->SetStatusPaneFlags( 2 );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSSetStatusPaneLayout
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSSetStatusPaneLayout( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->SetStatusPaneLayout( 2 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSBlankScreen
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSBlankScreen( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->BlankScreen();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSUnblankScreen
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSUnblankScreen( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->UnblankScreen();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSSetKeyboardRepeatRate
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSSetKeyboardRepeatRate( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->SetKeyboardRepeatRate( EAknApplicationDefaulRepeatRate );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSSetKeyblockMode
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSSetKeyblockMode( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->SetKeyblockMode( EDisableKeyBlock );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSDoEikonServerConnect
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSDoEikonServerConnect( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->DoEikonServerConnect();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSShowKeysLockedNote
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSShowKeysLockedNote( CStifItemParser& /*aItem*/ )
    {
    TBool isKeyPadLocked = EFalse;
    iUiServer->UpdateTaskList();
    iUiServer->ShowKeysLockedNote( isKeyPadLocked );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSShowGlobalNoteL 
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSShowGlobalNoteL( CStifItemParser& /*aItem*/ )
    {
    
    TBuf<20> globalNoteText( KGlobalNoteText );
    iUiServer->UpdateTaskList();
    iUiServer->ShowGlobalNoteL( globalNoteText, EAknCancelGlobalNote );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSStatusPaneResourceId
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSStatusPaneResourceId( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->StatusPaneResourceId();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSCreateActivateViewEventL 
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSCreateActivateViewEventL( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    TVwsViewId aiwToAknView( KUidTestAiwAkn,KTestAiwAknViewId );
    iUiServer->CreateActivateViewEventL( aiwToAknView,TUid::Null(),KNullDesC8() );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSCurrentAppStatuspaneResource
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSCurrentAppStatuspaneResource( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->CurrentAppStatuspaneResource();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSSetCurrentAppStatuspaneResource
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSSetCurrentAppStatuspaneResource( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    TInt resourceId = iUiServer->CurrentAppStatuspaneResource();//AppStatuspane
    iUiServer->SetCurrentAppStatuspaneResource( resourceId );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSSetFgSpDataSubscriberId
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSSetFgSpDataSubscriberId( CStifItemParser& /*aItem*/ )
    {
    CEikAppUi* app = CEikonEnv::Static()->EikAppUi();
        if ( app )
            {
            CEikApplication* application = app->Application();
            if ( application )
                {
                TInt iSubscriberId = application->AppDllUid().iUid;
                iUiServer->UpdateTaskList();
                iUiServer->SetFgSpDataSubscriberId(iSubscriberId);
                
                }
            }
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSRotateScreen
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSRotateScreen( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->RotateScreen();
    iUiServer->UpdateTaskList();
    iUiServer->RotateScreen();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSTaskSwitchingSupressed
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSTaskSwitchingSupressed( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->TaskSwitchingSupressed();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSShowLongTapAnimation
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSShowLongTapAnimation( CStifItemParser& /*aItem*/ )
    {
    
    TPointerEvent pointerEvent ;
    pointerEvent.iType = TPointerEvent::EButton1Down;
    pointerEvent.iPosition = TPoint( 5,5) ;
    pointerEvent.iParentPosition = TPoint( 6,6) ;
    if( AknLayoutUtils::PenEnabled() )
        {
        iUiServer->UpdateTaskList();
        iUiServer->ShowLongTapAnimation( pointerEvent );
        }
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSHideLongTapAnimation
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSHideLongTapAnimation( CStifItemParser& /*aItem*/ )
    {
    TPointerEvent pointerEvent ;
    pointerEvent.iType = TPointerEvent::EButton1Down;
    pointerEvent.iPosition = TPoint( 5,5) ;
    pointerEvent.iParentPosition = TPoint( 6,6) ;
    if( AknLayoutUtils::PenEnabled() )
        {
        iUiServer->UpdateTaskList();
        iUiServer->ShowLongTapAnimation( pointerEvent );
        iUiServer->HideLongTapAnimation();
        }
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSGetAliasKeyCode
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSGetAliasKeyCode( CStifItemParser& /*aItem*/ )
    {
    TUint keyCode;
    TKeyEvent keyEvent;
    iUiServer->UpdateTaskList();
    iUiServer->GetAliasKeyCode( keyCode, keyEvent, EEventKey );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSGetPhoneIdleViewId
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSGetPhoneIdleViewId( CStifItemParser& /*aItem*/ )
    {
    TVwsViewId idleView ;
    iUiServer->UpdateTaskList();
    iUiServer->GetPhoneIdleViewId( idleView );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSStartAknCapserverL
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSStartAknCapserverL( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->StartAknCapserverL();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSDoNotifierControllerCommand
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSDoNotifierControllerCommand( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->DoNotifierControllerCommand( CAknNotifierControllerUtility::DoCancelAll );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSPreAllocateDynamicSoftNoteEvent
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSPreAllocateDynamicSoftNoteEvent( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->PreAllocateDynamicSoftNoteEvent( KErrNone );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSNotifyDynamicSoftNoteEventL 
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSNotifyDynamicSoftNoteEventL( CStifItemParser& /*aItem*/ )
    {
    TRequestStatus status;
    _LIT8( KText, "2" );
    TBuf8<KBufSize> buf( KText );
    iUiServer->UpdateTaskList();
    iUiServer->NotifyDynamicSoftNoteEvent( status, buf );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSCancelDynamicSoftNoteEventNotification
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSCancelDynamicSoftNoteEventNotification( CStifItemParser& /*aItem*/ )
    {
    iUiServer->UpdateTaskList();
    iUiServer->CancelDynamicSoftNoteEventNotification();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSAknStartupApaServerProcess
// -----------------------------------------------------------------------------
//

TInt CTestDomUiServer::TestUSAknStartupApaServerProcess( CStifItemParser& /*aItem*/ )
    {
    AknStartupApaServerProcess();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomUiServer::TestUSAknGetInUseDiscreetPopupRect
// -----------------------------------------------------------------------------
//
TInt CTestDomUiServer::TestUSAknGetInUseDiscreetPopupRect( CStifItemParser& /*aItem*/ )
    {
    iUiServer->GetInUseGlobalDiscreetPopupRect();
    return KErrNone;
    }

// End of File


