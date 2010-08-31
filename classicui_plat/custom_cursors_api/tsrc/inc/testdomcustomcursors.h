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
* Description:  test AknCustomCursorSupport.h
*
*/



#ifndef C_TESTDOMCUSTOMCURSORS_H
#define C_TESTDOMCUSTOMCURSORS_H

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
_LIT( KtestdomcustomcursorsLogPath, "\\logs\\testframework\\testdomcustomcursors\\" ); 
// Log file
_LIT( KtestdomcustomcursorsLogFile, "testdomcustomcursors.txt" ); 
_LIT( KtestdomcustomcursorsLogFileWithTitle, "testdomcustomcursors_[%S].txt" );

/**
*  CTestDOMCustomCursors test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDOMCustomCursors ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMCustomCursors* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMCustomCursors();

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
    CTestDOMCustomCursors( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Test AknCustomCursorSupport.h
/*                         class AknCustomCursorSupport                  */
    /**
     * TestCCSCustomBidiTextCursorId test function for testing the 
     *     CustomBidiTextCursorId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCSCustomBidiTextCursorId( CStifItemParser& aItem );
    
    /**
     * TestCCSGetBidiTextCursorFromFontSpec test function for testing the 
     *     GetBidiTextCursorFromFontSpec function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCSGetBidiTextCursorFromFontSpec( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };

#endif      // C_TESTDOMCUSTOMCURSORS_H

// End of File
