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
* Description:  test errorui.h
*
*/



#ifndef C_TESTSDKERRUI_H
#define C_TESTSDKERRUI_H

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
_LIT( KTestSDKErrorUILogPath, "\\logs\\testframework\\testsdkerrui\\" ); 
// Log file
_LIT( KTestSDKErrorUILogFile, "testsdkerrui.txt" ); 
_LIT( KTestSDKErrorUILogFileWithTitle, "testsdkerrui_[%S].txt" );

/**
*  CTestSDKErrorUI test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKErrorUI ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKErrorUI* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKErrorUI();

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
    CTestSDKErrorUI( CTestModuleIf& aTestModuleIf );

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
     * test ShowGlobalErrorNoteL function with different errors
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestErrUIErrorNoteL( CStifItemParser& aItem );

    /**
     * test ShowGlobalErrorQueryL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestErrUIErrorQueryL( CStifItemParser& aItem );

    /**
     * test NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestErrUINewL( CStifItemParser& aItem );

    /**
     * test NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestErrUINewLCL( CStifItemParser& aItem );

    /**
     * test NewL function with param
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestErrUINewLWithParamL( CStifItemParser& aItem );

    /**
     * test NewLC function with param
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestErrUINewLCWithParamL( CStifItemParser& aItem );

    /**
     * test TextResolver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestErrUITextResolverL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };

#endif      // C_TESTSDKERRUI_H

// End of File
