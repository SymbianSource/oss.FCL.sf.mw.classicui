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
* Description:  Test alarm_api
*
*/



#ifndef C_TESTDOMALARM_H
#define C_TESTDOMALARM_H

/*
 *   INCLUDES
 */
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

/*
 *  MACROS
 */
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

_LIT( KtestdomalarmLogPath, "\\logs\\testframework\\testdomalarm\\" ); 

_LIT( KtestdomalarmLogFile, "testdomalarm.txt" ); 
_LIT( KtestdomalarmLogFileWithTitle, "testdomalarm_[%S].txt" );

/**
*  Ctestdomalarm test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(Ctestdomalarm) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static Ctestdomalarm* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~Ctestdomalarm();

public:

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
    Ctestdomalarm( CTestModuleIf& aTestModuleIf );

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
     * TestALARMAllFunctionL test function for testing the constructor , destructor ande constructl function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestALARMAllFunctionL( CStifItemParser& /*aItem*/ );
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: 

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    

    };

#endif 

/*
 *  End of File
 */
