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
* Description:  test aknindicatorplugin.h
*
*/



#ifndef C_TESTDOMINDIPLUGIN_H
#define C_TESTDOMINDIPLUGIN_H

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
_LIT( KtestdomindipluginLogPath, "\\logs\\testframework\\testdomindiplugin\\" ); 
// Log file
_LIT( KtestdomindipluginLogFile, "testdomindiplugin.txt" ); 
_LIT( KtestdomindipluginLogFileWithTitle, "testdomindiplugin_[%S].txt" );

/**
*  CTestDOMIndiPlugin test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDOMIndiPlugin ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMIndiPlugin* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMIndiPlugin();

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
    CTestDOMIndiPlugin( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // [TestMethods]

    /**
    * test NewL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestNewL( CStifItemParser& aItem );

    /**
    * test TextL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextL( CStifItemParser& aItem );

    /**
    * test IconL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestIconL( CStifItemParser& aItem );

    /**
    * test UpdateL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestUpdateL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };

#endif      // C_TESTDOMINDIPLUGIN_H

// End of File
