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
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testdomuiserver.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomUiServer::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDomUiServer::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestUSConnectAndSendAppsKeySuppress", CTestDomUiServer::TestUSConnectAndSendAppsKeySuppress ),
        ENTRY( "TestUSHideApplicationFromFsw", CTestDomUiServer::TestUSHideApplicationFromFsw ),
        ENTRY( "TestUSUnlockMedia", CTestDomUiServer::TestUSUnlockMedia ),
        ENTRY( "TestUSCancelUnlockMedia", CTestDomUiServer::TestUSCancelUnlockMedia ),
        ENTRY( "TestUSEnableTaskList", CTestDomUiServer::TestUSEnableTaskList ),
        ENTRY( "TestUSMakeTaskListVisible", CTestDomUiServer::TestUSMakeTaskListVisible ),
        ENTRY( "TestUSUpdateTaskList", CTestDomUiServer::TestUSUpdateTaskList ),
        ENTRY( "TestUSShutdownAppsL", CTestDomUiServer::TestUSShutdownAppsL ),
        ENTRY( "TestUSCancelShutdownApps", CTestDomUiServer::TestUSCancelShutdownApps ),
        ENTRY( "TestUSSetSgcParams", CTestDomUiServer::TestUSSetSgcParams ),
        ENTRY( "TestUSSetSgcParamScreenMode", CTestDomUiServer::TestUSSetSgcParamScreenMode ),
        ENTRY( "TestUSBlockServerStatusPaneRedraws", CTestDomUiServer::TestUSBlockServerStatusPaneRedraws ),
        ENTRY( "TestUSRedrawServerStatusPane", CTestDomUiServer::TestUSRedrawServerStatusPane ),
        ENTRY( "TestUSPrepareForAppExit", CTestDomUiServer::TestUSPrepareForAppExit ),
        ENTRY( "TestUSSetSystemFaded", CTestDomUiServer::TestUSSetSystemFaded ),
        ENTRY( "TestUSIsSystemFaded", CTestDomUiServer::TestUSIsSystemFaded ),
        ENTRY( "TestUSConnect", CTestDomUiServer::TestUSConnect ),
        ENTRY( "TestUSRelinquishPriorityToForegroundApp", CTestDomUiServer::TestUSRelinquishPriorityToForegroundApp ),
        ENTRY( "TestUSGetPackedConfigL", CTestDomUiServer::TestUSGetPackedConfigL ),
        ENTRY( "TestUSMoveAppInZOrder", CTestDomUiServer::TestUSMoveAppInZOrder ),
        ENTRY( "TestUSSetStatusPaneFlags", CTestDomUiServer::TestUSSetStatusPaneFlags ),
        ENTRY( "TestUSSetStatusPaneLayout", CTestDomUiServer::TestUSSetStatusPaneLayout ),
        ENTRY( "TestUSBlankScreen", CTestDomUiServer::TestUSBlankScreen ),
        ENTRY( "TestUSUnblankScreen", CTestDomUiServer::TestUSUnblankScreen ),
        ENTRY( "TestUSSetKeyboardRepeatRate", CTestDomUiServer::TestUSSetKeyboardRepeatRate ),
        ENTRY( "TestUSSetKeyblockMode", CTestDomUiServer::TestUSSetKeyblockMode ),
        ENTRY( "TestUSDoEikonServerConnect", CTestDomUiServer::TestUSDoEikonServerConnect ),
        ENTRY( "TestUSShowKeysLockedNote", CTestDomUiServer::TestUSShowKeysLockedNote ),
        ENTRY( "TestUSShowGlobalNoteL", CTestDomUiServer::TestUSShowGlobalNoteL ),
        ENTRY( "TestUSStatusPaneResourceId", CTestDomUiServer::TestUSStatusPaneResourceId ),
        ENTRY( "TestUSCreateActivateViewEventL", CTestDomUiServer::TestUSCreateActivateViewEventL ),
        ENTRY( "TestUSCurrentAppStatuspaneResource", CTestDomUiServer::TestUSCurrentAppStatuspaneResource ),
        ENTRY( "TestUSSetCurrentAppStatuspaneResource", CTestDomUiServer::TestUSSetCurrentAppStatuspaneResource ),
        ENTRY( "TestUSSetFgSpDataSubscriberId", CTestDomUiServer::TestUSSetFgSpDataSubscriberId ),
        ENTRY( "TestUSRotateScreen", CTestDomUiServer::TestUSRotateScreen ),
        ENTRY( "TestUSTaskSwitchingSupressed", CTestDomUiServer::TestUSTaskSwitchingSupressed ),
        ENTRY( "TestUSShowLongTapAnimation", CTestDomUiServer::TestUSShowLongTapAnimation ),
        ENTRY( "TestUSHideLongTapAnimation", CTestDomUiServer::TestUSHideLongTapAnimation ),
        ENTRY( "TestUSGetAliasKeyCode", CTestDomUiServer::TestUSGetAliasKeyCode ),
        ENTRY( "TestUSGetPhoneIdleViewId", CTestDomUiServer::TestUSGetPhoneIdleViewId ),
        ENTRY( "TestUSStartAknCapserverL", CTestDomUiServer::TestUSStartAknCapserverL ),
        ENTRY( "TestUSDoNotifierControllerCommand", CTestDomUiServer::TestUSDoNotifierControllerCommand ),
        ENTRY( "TestUSPreAllocateDynamicSoftNoteEvent", CTestDomUiServer::TestUSPreAllocateDynamicSoftNoteEvent ),
        ENTRY( "TestUSNotifyDynamicSoftNoteEventL", CTestDomUiServer::TestUSNotifyDynamicSoftNoteEventL ),
        ENTRY( "TestUSCancelDynamicSoftNoteEventNotification", CTestDomUiServer::TestUSCancelDynamicSoftNoteEventNotification ),
        ENTRY( "TestUSAknStartupApaServerProcess", CTestDomUiServer::TestUSAknStartupApaServerProcess ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


//  [End of File]


