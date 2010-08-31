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
* Description:  test transition_effect_utilities_api
*
*/



// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <e32property.h>

#include "testdomtransitioneffectutilities.h"

// CONSTANTS
_LIT( KModuleName, "testdomtransitioneffectutilities.dll" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomTransitionEffectUtilities::CTestDomTransitionEffectUtilities
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestDomTransitionEffectUtilities::CTestDomTransitionEffectUtilities( CTestModuleIf& aTestModuleIf ):
    CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CTestDomTransitionEffectUtilities::~CTestDomTransitionEffectUtilities
// Destructor.
// -----------------------------------------------------------------------------
//
CTestDomTransitionEffectUtilities::~CTestDomTransitionEffectUtilities()
    {
    // Delete logger
    delete iLog; 
    if ( iControl )
        {
        CCoeEnv::Static()->AppUi()->RemoveFromStack( iContainer );
        }
    delete iControl;

    }

    

// -----------------------------------------------------------------------------
// CTestDomTransitionEffectUtilities::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestDomTransitionEffectUtilities::ConstructL()
    {
    //Read logger settings to check whether test case name is to be
    //appended to log file name.
    RSettingServer settingServer;
    CleanupClosePushL( settingServer );
    TInt ret = settingServer.Connect();
    if ( ret != KErrNone )
        {
        User::Leave(ret);
        }
    // Struct to StifLogger settigs.
    TLoggerSettings loggerSettings; 
    // Parse StifLogger defaults from STIF initialization file.
    ret = settingServer.GetLoggerSettings( loggerSettings );
    if ( ret != KErrNone )
        {
        User::Leave( ret );
        } 
    // Close Setting server session
    settingServer.Close();
    CleanupStack::PopAndDestroy( &settingServer );

    TFileName logFileName;
    
    if ( loggerSettings.iAddTestCaseTitle )
        {
        TName title;
        TestModuleIf().GetTestCaseTitleL( title );
        logFileName.Format( KtestdomtransitioneffectutilitiesLogFileWithTitle, &title );
        }
    else
        {
        logFileName.Copy( KtestdomtransitioneffectutilitiesLogFile );
        }

    iLog = CStifLogger::NewL( KtestdomtransitioneffectutilitiesLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
    SendTestClassVersion();

    TRect rect = CEikonEnv::Static()->AppUiFactory()->ClientRect();
    iContainer = CTestDomUtilitiesContainer::NewL( rect );
    CCoeEnv::Static()->AppUi()->AddToStackL( iContainer );
    }

// -----------------------------------------------------------------------------
// CTestDomTransitionEffectUtilities::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestDomTransitionEffectUtilities* CTestDomTransitionEffectUtilities::NewL( CTestModuleIf& aTestModuleIf )
    {
    CTestDomTransitionEffectUtilities* self = new( ELeave ) CTestDomTransitionEffectUtilities( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;

    }

//-----------------------------------------------------------------------------
// CTestDomTransitionEffectUtilities::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestDomTransitionEffectUtilities::SendTestClassVersion()
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
    return ( CScriptBase* ) CTestDomTransitionEffectUtilities::NewL( aTestModuleIf );
    }
//  End of File
