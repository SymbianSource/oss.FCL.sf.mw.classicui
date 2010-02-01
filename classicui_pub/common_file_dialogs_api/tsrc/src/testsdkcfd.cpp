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
* Description:  Test Common File Dialogs
*
*/



// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <screensaverinternalpskeys.h>
#include <e32property.h>

#include "testsdkcfd.h"

_LIT( KResourcePath, "C:\\resource\\testsdkcfd.rsc" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKCFD::CTestSDKCFD
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKCFD::CTestSDKCFD( CTestModuleIf& aTestModuleIf ):
    CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestSDKCFD::ConstructL()
    {
    //Read logger settings to check whether test case name is to be
    //appended to log file name.
    RSettingServer settingServer;
    CleanupClosePushL( settingServer );
    TInt ret = settingServer.Connect();
    if(ret != KErrNone)
        {
        User::Leave(ret);
        }
    // Struct to StifLogger settigs.
    TLoggerSettings loggerSettings; 
    // Parse StifLogger defaults from STIF initialization file.
    ret = settingServer.GetLoggerSettings(loggerSettings);
    if(ret != KErrNone)
        {
        User::Leave(ret);
        } 
    // Close Setting server session
    settingServer.Close();
    CleanupStack::PopAndDestroy( &settingServer );

    TFileName logFileName;
    
    if(loggerSettings.iAddTestCaseTitle)
        {
        TName title;
        TestModuleIf().GetTestCaseTitleL(title);
        logFileName.Format(KtestsdkcfdLogFileWithTitle, &title);
        }
    else
        {
        logFileName.Copy(KtestsdkcfdLogFile);
        }

    iLog = CStifLogger::NewL( KtestsdkcfdLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    iOffset = CCoeEnv::Static()->AddResourceFileL( KResourcePath );

    TurnOffScreenSaver();

    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestSDKCFD* CTestSDKCFD::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CTestSDKCFD* self = new( ELeave ) CTestSDKCFD( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CTestSDKCFD::~CTestSDKCFD()
    { 

    // Delete resources allocated from test methods
    Delete();

    if ( iFDlg )
        {
        delete iFDlg;
        iFDlg = NULL;
        }

    if ( iFNPDialog )
        {
        delete iFNPDialog;
        iFNPDialog = NULL;
        }

    if ( iSettingPage )
        {
        delete iSettingPage;
        iSettingPage = NULL;
        }
    
    if ( iSettingItemList )
        {
        delete iSettingItemList;
        iSettingItemList = NULL;
        }
    
    if ( iSettingItemListMulti )
        {
        delete iSettingItemListMulti;
        iSettingItemListMulti = NULL;
        }
    
    delete iLog; 

    CCoeEnv::Static()->DeleteResourceFile( iOffset );

    RestoreScreenSaver();

    }

// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// LibEntryL is a polymorphic Dll entry point.
// Returns: CScriptBase: New CScriptBase derived object
// -----------------------------------------------------------------------------
//
EXPORT_C CScriptBase* LibEntryL( 
    CTestModuleIf& aTestModuleIf ) // Backpointer to STIF Test Framework
    {

    return ( CScriptBase* ) CTestSDKCFD::NewL( aTestModuleIf );

    }

// -----------------------------------------------------------------------------
// Turn off ScreenSaver
// -----------------------------------------------------------------------------
//
void CTestSDKCFD::TurnOffScreenSaver()
    {
    TInt err1 = RProperty::Get(KPSUidScreenSaver, KScreenSaverAllowScreenSaver,
        iOldScreenSaverProperty);
    TInt err2 = RProperty::Set(KPSUidScreenSaver, KScreenSaverAllowScreenSaver,
        KScreenSaverAllowScreenSaver);    
    RDebug::Printf("screensaver property=%d err1=%d err2=%d\n",
        iOldScreenSaverProperty, err1, err2);
    }

// -----------------------------------------------------------------------------
// Restore ScreenSaver
// -----------------------------------------------------------------------------
//
void CTestSDKCFD::RestoreScreenSaver()
    {
    RProperty::Set(KPSUidScreenSaver, KScreenSaverAllowScreenSaver,
        iOldScreenSaverProperty);
    User::ResetInactivityTime();
    }

//  End of File
