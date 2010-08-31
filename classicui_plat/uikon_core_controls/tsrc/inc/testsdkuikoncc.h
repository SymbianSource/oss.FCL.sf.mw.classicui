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
* Description:  Test EIKBTGRP.H
*
*/



#ifndef C_TESTSDKUIKONCC_H
#define C_TESTSDKUIKONCC_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <eikbtgrp.h>
#include <eikcba.h>
#include <eikenv.h>
#include <eikcmbut.h>
#include <eiklbbut.h>
#include <eikmnbut.h>

#include "testsdkuikonccobserver.h"

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkuikonccLogPath, "\\logs\\testframework\\testsdkuikoncc\\" ); 
// Log file
_LIT( KtestsdkuikonccLogFile, "testsdkuikoncc.txt" ); 
_LIT( KtestsdkuikonccLogFileWithTitle, "testsdkuikoncc_[%S].txt" );

/**
*  CTestSdkUikoncc test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
//
NONSHARABLE_CLASS(CTestSdkUikoncc) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSdkUikoncc* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSdkUikoncc();

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
    CTestSdkUikoncc( CTestModuleIf& aTestModuleIf );

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

private:    // EIKBTGRP.H
    /**
     * Test  AnimateCommandL of MEikButtonGroup in 
     * eikbtgrp.h
     * @since S60 5.0
     * Parameter aItem is not used
     * @return Symbian OS error code.
     */
    virtual TInt TestBGAnimateCommandL(CStifItemParser& aItem);

private: // Data
    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * CEikonEnv pointer
     * Not own.
     */
    CEikonEnv* iEnv;

    // Resource file offset
    TInt iOffset;
    };


#endif      // C_TESTSDKUIKONCC_H

// End of File
