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
* Description:  
*
*/



// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <e32property.h>
#include <coemain.h>
#include <coeaui.h>
#include <eikclb.h>
#include <eiklbd.h>
#include <eiklbi.h>
#include <eiktxlbm.h>

#include "testsdklists.h"
#include "testsdkview.h"
#include "testsdkcontainer.h"
// CONSTANTS
_LIT( KModuleName, "testsdklists.dll" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdklists::Ctestsdklists
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKLists::CTestSDKLists( CTestModuleIf& aTestModuleIf ):
    CScriptBase( aTestModuleIf )
    {
    iEikonEnvPointer = CEikonEnv::Static();
    }

// -----------------------------------------------------------------------------
// Ctestsdklists::~Ctestsdklists
// Destructor.
// -----------------------------------------------------------------------------
//
CTestSDKLists::~CTestSDKLists()
    {
    // Delete logger
    delete iLog; 

    CCoeEnv::Static()->AppUi()->RemoveFromStack( iContainer );

    if ( iView )
        {
        delete iView;
        iView = NULL;
        }
    
    if ( iContainer )
        {
        delete iContainer;
        iContainer = NULL;
        }
    
    if ( iItemDrawer )
        {
        delete iItemDrawer;
        iItemDrawer = NULL;
        }

    if ( iLBData )
        {
        delete iLBData;
        iLBData = NULL;
        }

    if ( iTLIDrawer )
        {
        delete iTLIDrawer;
        iTLIDrawer = NULL;
        }

    if ( iTLBModel )
        {
        delete iTLBModel;
        iTLBModel = NULL;
        }

    if ( iSLBView )
        {
        delete iSLBView;
        iSLBView = NULL;
        }

    if ( iListBox )
        {
        delete iListBox;
        iListBox = NULL;
        }
    
    if ( iMarkedItems )
        {
        delete iMarkedItems;
        iMarkedItems = NULL;
        }
    
    if ( iTextArray )
        {
        delete iTextArray;
        iTextArray = NULL;
        }

    CCoeEnv::Static()->DeleteResourceFile( iOffset );
    }

// -----------------------------------------------------------------------------
// Ctestsdklists::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestSDKLists::ConstructL()
    {
    iView = CTestSDKView::NewL();
    iContainer = new( ELeave ) CTestSDKContainer();

    iContainer->SetMopParent( iView );
    iContainer->ConstructL( iView->ClientRect() );
    CCoeEnv::Static()->AppUi()->AddToStackL( iContainer );
    iContainer->MakeVisible( ETrue );
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
        logFileName.Format( KtestsdklistsLogFileWithTitle, &title );
        }
    else
        {
        logFileName.Copy( KtestsdklistsLogFile );
        }

    iLog = CStifLogger::NewL( KtestsdklistsLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
#ifdef __WINSCW__
    iOffset = CCoeEnv::Static()->AddResourceFileL(_L("z:\\resource\\testsdklists.rsc"));
#else                          
    iOffset = CCoeEnv::Static()->AddResourceFileL(_L("C:\\resource\\testsdklists.rsc"));
#endif // __WINSCW__
    
    SendTestClassVersion();
    }

// -----------------------------------------------------------------------------
// Ctestsdklists::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestSDKLists* CTestSDKLists::NewL( CTestModuleIf& aTestModuleIf )
    {
    CTestSDKLists* self = new( ELeave ) CTestSDKLists( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;

    }

//-----------------------------------------------------------------------------
// Ctestsdklists::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestSDKLists::SendTestClassVersion()
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
    return ( CScriptBase* ) CTestSDKLists::NewL( aTestModuleIf );
    }
//  End of File
