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
* Description:  test aknchoicelist.h
*
*/



// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <e32property.h>
#include <aknbutton.h>
#include <coemain.h>
#include <coeaui.h>

#include "testsdkchoicelist.h"
#include "testsdkchoicelistcontrol.h"

//CONST
const TInt KLength = 20;

_LIT( KModuleName, "testsdkchoicelist.dll" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::CTestSDKChoiceList
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKChoiceList::CTestSDKChoiceList( CTestModuleIf& aTestModuleIf ):
    CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestSDKChoiceList::ConstructL()
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
        logFileName.Format( KtestsdkchoicelistLogFileWithTitle, &title );
        }
    else
        {
        logFileName.Copy( KtestsdkchoicelistLogFile );
        }

    iLog = CStifLogger::NewL( KtestsdkchoicelistLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    _LIT( KFile, "C:\\resource\\testsdkchoicelist.rsc" );
    iOffset = CCoeEnv::Static()->AddResourceFileL( KFile );
    SendTestClassVersion();
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestSDKChoiceList* CTestSDKChoiceList::NewL( CTestModuleIf& aTestModuleIf )
    {
    CTestSDKChoiceList* self = new( ELeave ) CTestSDKChoiceList( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;

    }

// Destructor
CTestSDKChoiceList::~CTestSDKChoiceList()
    { 

    // Delete resources allocated from test methods
    Delete();

    // Delete ChoiceList
    delete iChoiceList;
    
    // Delete logger
    delete iLog; 

    CCoeEnv::Static()->DeleteResourceFile( iOffset );
    }

//-----------------------------------------------------------------------------
// CTestSDKChoiceList::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestSDKChoiceList::SendTestClassVersion()
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
    return ( CScriptBase* ) CTestSDKChoiceList::NewL( aTestModuleIf );
    }

void CTestSDKChoiceList::TestCLInitializeL()
    {
    if(iChoiceList)
        {
        delete iChoiceList;
        iChoiceList = NULL;
        }
    
    const TInt num = 5;
    CDesCArrayFlat* array = new (ELeave) CDesCArrayFlat( num );
    CleanupStack::PushL( array );
    
    _LIT( KItem, "item" );
    TBuf<KLength> item( KItem );
    array->AppendL( item );
    
    _LIT( KButton, "button" );
    TBuf<KLength> button( KButton );
    CAknButton* btn = CAknButton::NewLC( NULL, NULL, NULL, NULL, button, KNullDesC, KAknButtonNoFrame, 0 );
    
    CTestSDKChoiceListControl* control = CTestSDKChoiceListControl::NewLC();
    
    CleanupStack::Pop( control );
    CleanupStack::Pop( btn );
    CleanupStack::Pop( array );
    
    iChoiceList = CAknChoiceList::NewL( control, array, CAknChoiceList::EAknChoiceListWithCurrentSelection, btn );

    }

//  End of File
