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
* Description:  task_list_api
*
*/



#ifndef C_TESTDOMTASKLIST_H
#define C_TESTDOMTASKLIST_H

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
_LIT( KtestdomtasklistLogPath, "\\logs\\testframework\\testdomtasklist\\" ); 
// Log file
_LIT( KtestdomtasklistLogFile, "testdomtasklist.txt" ); 
_LIT( KtestdomtasklistLogFileWithTitle, "testdomtasklist_[%S].txt" );

/**
*  CTestDOMTaskList test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
class CAknTaskList;
NONSHARABLE_CLASS( CTestDOMTaskList ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMTaskList* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMTaskList();

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
    CTestDOMTaskList( CTestModuleIf& aTestModuleIf );

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
    * TestTLNewL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTLNewL( CStifItemParser& aItem );
    /**
    * TestTLNewLC test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTLNewLC( CStifItemParser& aItem );
    /**
    * TestTLDestructor test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTLDestructor( CStifItemParser& aItem );
    /**
    * TestTLUpdateListL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTLUpdateListL( CStifItemParser& aItem );
    /**
    * TestTLWgArray test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTLWgArray( CStifItemParser& aItem );
    /**
    * TestTLFindRootApp test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTLFindRootApp( CStifItemParser& aItem );
    /**
    * TestTLIsRootWindowGroup test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTLIsRootWindowGroup( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * for test
     * Not own.
     */
    CAknTaskList* iTaskList;

    };

#endif      // C_TESTDOMTASKLIST_H

// End of File
