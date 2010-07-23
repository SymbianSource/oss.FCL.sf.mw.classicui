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
* Description:  test akndef.h
*
*/



#ifndef C_TESTSDKUIFRAMEDEFINITIONS_H
#define C_TESTSDKUIFRAMEDEFINITIONS_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkuiframedefinitionsLogPath, "\\logs\\testframework\\testsdkuiframedefinitions\\" ); 
// Log file
_LIT( KtestsdkuiframedefinitionsLogFile, "testsdkuiframedefinitions.txt" ); 
_LIT( KtestsdkuiframedefinitionsLogFileWithTitle, "testsdkuiframedefinitions_[%S].txt" );

/**
*  CTestSDKUiFrameDefinitions test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKUiFrameDefinitions ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKUiFrameDefinitions* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKUiFrameDefinitions();

public: // Functions from base classes

    /**
    * From CScriptBase Runs a script line.
    * @since S60 5.0
    * @param aItem Script line containing method name and parameters
    * @return Symbian OS error code
    */
    virtual TInt RunMethodL( CStifItemParser& aItem );

private:

    /**
    * C++ default constructor.
    */
    CTestSDKUiFrameDefinitions( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Test akndef.h
/*                               class AknDef                            */
    /**
     * TestADGetPhoneIdleViewId test function for testing the 
     *     GetPhoneIdleViewId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADGetPhoneIdleViewId( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };

#endif      // C_TESTSDKUIFRAMEDEFINITIONS_H

// End of File
