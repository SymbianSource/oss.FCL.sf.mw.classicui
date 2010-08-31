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
* Description:  Test AknTasHook.h
*
*/


#ifndef C_TESTPLATTESTABILITY_H
#define C_TESTPLATTESTABILITY_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

#include <AknTasHook.h>
// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KTestPlatTestAbilityLogPath, "\\logs\\testframework\\testplattestability\\" ); 
// Log file
_LIT( KTestPlatTestAbilityLogFile, "testplattestability.txt" ); 
_LIT( KTestPlatTestAbilityLogFileWithTitle, "testplattestability_[%S].txt" );

/**
*  CTestPlatTestAbility test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestPlatTestAbility ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestPlatTestAbility* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestPlatTestAbility();

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
    CTestPlatTestAbility( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * Example test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */

    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // [TestMethods]
    /**
     * TestCAknTasHookAddL test AddL of CAknTasHook
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknTasHookAddL( CStifItemParser& aItem );

    /**
     * TestCAknTasHookRemoveL test Remove of CAknTasHook
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknTasHookRemoveL( CStifItemParser& aItem );

    /**
     * TestCAknTasHookGetL test Get of CAknTasHook
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknTasHookGetL( CStifItemParser& aItem );

    /**
     * TestCAknTasHookGetAllL test GetAll of CAknTasHook
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknTasHookGetAllL( CStifItemParser& aItem );

    /**
     * TestCAknTasHookGetAknUiLCL test GetAknUiLC of CAknTasHook
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknTasHookGetAknUiLCL( CStifItemParser& aItem );



private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    };

#endif      // C_TESTPLATTESTABILITY_H

// End of File

