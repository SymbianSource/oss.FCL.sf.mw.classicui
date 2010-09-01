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
* Description:  test class for screen_saver_api
*
*/



#ifndef C_TESTSDKSCREENSAVER_H
#define C_TESTSDKSCREENSAVER_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <ScreensaverpluginIntDef.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkscreensaverLogPath, "\\logs\\testframework\\testsdkscreensaver\\" ); 
// Log file
_LIT( KtestsdkscreensaverLogFile, "testsdkscreensaver.txt" ); 
_LIT( KtestsdkscreensaverLogFileWithTitle, "testsdkscreensaver_[%S].txt" );

/**
*  Ctestsdkscreensaver test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKScreenSaver ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKScreenSaver* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKScreenSaver();

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
    CTestSDKScreenSaver( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();
    
        /**
     * Turn off ScreenSaver
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    void TurnOffScreenSaver();

    /**
     * Restore ScreenSaver
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    void RestoreScreenSaver();

private: // Test ScreensaverpluginIntDef.h
    /**
     * TestSPIDNewL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPIDNewL(CStifItemParser& aItem );

    /**
     * TestSPIDListImplementationsL test function for testing the ImplementationsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPIDListImplementationsL(CStifItemParser& aItem );

    /**
     * TestSPIDDelete test function for testing the destruction function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPIDDelete(CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    /**
     * Own : test functions in ScreensaverpluginIntDef.h
     */
    CScreensaverPluginInterfaceDefinition* iSPIDef;

    };

#endif      // C_TESTSDKSCREENSAVER_H

// End of File
