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
* Description:  Description
*
*/



#ifndef C_TESTSDKSCREENMODE_H
#define C_TESTSDKSCREENMODE_H

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
_LIT( KtestsdkscreenmodeLogPath, "\\logs\\testframework\\testsdkscreenmode\\" ); 
// Log file
_LIT( KtestsdkscreenmodeLogFile, "testsdkscreenmode.txt" ); 
_LIT( KtestsdkscreenmodeLogFileWithTitle, "testsdkscreenmode_[%S].txt" );

/**
*  Ctestsdkscreenmode test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKScreenMode) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKScreenMode* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKScreenMode();

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
    CTestSDKScreenMode( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * Frees all resources allocated from test methods.
    * @since S60 5.0
    */
    void Delete();

    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

    //[TestMethods]
private: // Test AknScreenMode.h  class TAknScreenMode
        /**
         * TestSMSizeInPixels test function for testing the SizeInPixels function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestSMSizeInPixels(CStifItemParser& aItem );
        
        /**
         * TestSMDisplayMode test function for testing the DisplayMode function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestSMDisplayMode(CStifItemParser& aItem );
        
        /**
         * TestSMModeNumber test function for testing the ModeNumber function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestSMModeNumber(CStifItemParser& aItem );
        
private: // Test AknScreenMode.h  class TAknScreenModes
        /**
         * TestSMSGetModes test function for testing the GetModes function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestSModesGetModes(CStifItemParser& aItem );
        
        /**
         * TestSModeSCount test function for testing the Count function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestSModesCount(CStifItemParser& aItem );
        
        /**
         * TestSModeSoperator test function for testing the operator[] function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestSModesoperator(CStifItemParser& aItem );
        
        /**
         * TestSModeSSetAppUiScreenModeL test function for testing the SetAppUiScreenModeL function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestSModesSetAppUiScreenModeL(CStifItemParser& aItem );
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };

#endif      // C_TESTSDKSCREENMODE_H

// End of File
