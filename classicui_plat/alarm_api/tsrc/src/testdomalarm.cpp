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
* Description:  Test alarm_api
*
*/



/*
 *  INCLUDE FILES
 */
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <e32property.h>

#include "testdomalarm.h"

/*
 *  CONSTANTS
 */
_LIT( KModuleName, "testdomalarm.dll" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestdomalarm::Ctestdomalarm
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
Ctestdomalarm::Ctestdomalarm( CTestModuleIf& aTestModuleIf ):
    CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// Ctestdomalarm::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void Ctestdomalarm::ConstructL()
    {
    RSettingServer settingServer;
    CleanupClosePushL( settingServer );
    TInt ret = settingServer.Connect();
    if ( ret != KErrNone )
        {
        User::Leave(ret);
        }
    TLoggerSettings loggerSettings; 
    ret = settingServer.GetLoggerSettings( loggerSettings );
    if ( ret != KErrNone )
        {
        User::Leave( ret );
        } 
    settingServer.Close();
    CleanupStack::PopAndDestroy( &settingServer );

    TFileName logFileName;
    
    if ( loggerSettings.iAddTestCaseTitle )
        {
        TName title;
        TestModuleIf().GetTestCaseTitleL( title );
        logFileName.Format( KtestdomalarmLogFileWithTitle, &title );
        }
    else
        {
        logFileName.Copy( KtestdomalarmLogFile );
        }

    iLog = CStifLogger::NewL( KtestdomalarmLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
    SendTestClassVersion();
    }

// -----------------------------------------------------------------------------
// Ctestdomalarm::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
Ctestdomalarm* Ctestdomalarm::NewL( CTestModuleIf& aTestModuleIf )
    {
    Ctestdomalarm* self = new( ELeave ) Ctestdomalarm( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;

    }

/*
 *  Destructor
 */
Ctestdomalarm::~Ctestdomalarm()
    { 

    Delete();

    delete iLog; 

    }

//-----------------------------------------------------------------------------
// Ctestdomalarm::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void Ctestdomalarm::SendTestClassVersion()
    {
    TVersion moduleVersion;
    moduleVersion.iMajor = TEST_CLASS_VERSION_MAJOR;
    moduleVersion.iMinor = TEST_CLASS_VERSION_MINOR;
    moduleVersion.iBuild = TEST_CLASS_VERSION_BUILD;

    TFileName moduleName;
    moduleName = KModuleName;

    TBool newVersionOfMethod = ETrue;
    TestModuleIf().SendTestModuleVersion( moduleVersion, moduleName, 
        newVersionOfMethod );
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
    return ( CScriptBase* ) Ctestdomalarm::NewL( aTestModuleIf );
    }
/*
 *   End of File
 */
