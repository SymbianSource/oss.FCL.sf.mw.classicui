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
* Description:  test AknDlgShut.h
*
*/



#ifndef C_TESTSDKDIALOGSHUTTER_H
#define C_TESTSDKDIALOGSHUTTER_H

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
_LIT( KtestsdkdialogshutterLogPath, "\\logs\\testframework\\testsdkdialogshutter\\" ); 
// Log file
_LIT( KtestsdkdialogshutterLogFile, "testsdkdialogshutter.txt" ); 
_LIT( KtestsdkdialogshutterLogFileWithTitle, "testsdkdialogshutter_[%S].txt" );

/**
*  CTestSDKDialogShutter test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKDialogShutter) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKDialogShutter* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKDialogShutter();

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
    CTestSDKDialogShutter( CTestModuleIf& aTestModuleIf );

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

private: // Test AknDlgShut.h
/*                           class AknDialogShutter                         */
    /**
     * TestDSShutDialogsL test function for testing the 
     *     ShutDialogsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSShutDialogsL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKDIALOGSHUTTER_H

// End of File
