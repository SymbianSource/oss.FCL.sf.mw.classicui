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
* Description:  Test grids_api
*
*/


/*
 *  INCLUDE FILES
 */
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <e32property.h>
#include <coeaui.h>

#include "testsdkgridsview.h"
#include "testsdkgridscontainer.h"
#include "testsdkgrids.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkgrids::Ctestsdkgrids
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKGrids::CTestSDKGrids( CTestModuleIf& aTestModuleIf ):
    CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestSDKGrids::ConstructL()
    {
    iView = CTestSDKGridsView::NewL();
    iContainer = new( ELeave ) CTestSDKGridsContainer();

    iContainer->SetMopParent( iView );
    iContainer->ConstructL( iView->ClientRect() );
    CCoeEnv::Static()->AppUi()->AddToStackL( iContainer );
    iContainer->MakeVisible( ETrue );
    
    RSettingServer settingServer;
    TInt ret = settingServer.Connect();
    if(ret != KErrNone)
        {
        User::Leave(ret);
        }
    TLoggerSettings loggerSettings; 
    ret = settingServer.GetLoggerSettings(loggerSettings);
    if(ret != KErrNone)
        {
        User::Leave(ret);
        } 
    settingServer.Close();

    TFileName logFileName;
    
    if(loggerSettings.iAddTestCaseTitle)
        {
        TName title;
        TestModuleIf().GetTestCaseTitleL(title);
        logFileName.Format(KtestsdkgridsLogFileWithTitle, &title);
        }
    else
        {
        logFileName.Copy(KtestsdkgridsLogFile);
        }

    iLog = CStifLogger::NewL( KtestsdkgridsLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );

    iOffset = CCoeEnv::Static()->AddResourceFileL( _L( "C:\\resource\\testsdkgrids.rsc" ) );

    SendTestClassVersion();
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestSDKGrids* CTestSDKGrids::NewL( CTestModuleIf& aTestModuleIf )
    {
    CTestSDKGrids* self = new( ELeave ) CTestSDKGrids( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

/*
 * Destructor
 */
CTestSDKGrids::~CTestSDKGrids()
    { 

    Delete();
    CCoeEnv::Static()->AppUi()->RemoveFromStack( iContainer );
    delete iContainer;
    delete iView;

    delete iLog; 

    CCoeEnv::Static()->DeleteResourceFile( iOffset );
    }

//-----------------------------------------------------------------------------
// Ctestsdkgrids::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestSDKGrids::SendTestClassVersion()
    {
    TVersion moduleVersion;
    moduleVersion.iMajor = TEST_CLASS_VERSION_MAJOR;
    moduleVersion.iMinor = TEST_CLASS_VERSION_MINOR;
    moduleVersion.iBuild = TEST_CLASS_VERSION_BUILD;

    TFileName moduleName;
    moduleName = _L( "testsdkgrids.dll" );

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
    return ( CScriptBase* ) CTestSDKGrids::NewL( aTestModuleIf );
    }
/*
 *   End of File
 */
