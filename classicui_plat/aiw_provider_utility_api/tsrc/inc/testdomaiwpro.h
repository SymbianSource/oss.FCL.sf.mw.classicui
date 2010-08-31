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
* Description:    Test aiw_provider_utility_api
 *
*/




#ifndef C_TESTDOMAIWPRO_H
#define C_TESTDOMAIWPRO_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <coemain.h>
#include <coeaui.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdomaiwproLogPath, "\\logs\\testframework\\testdomaiwpro\\" );
// Log file
_LIT( KtestdomaiwproLogFile, "testdomaiwpro.txt" );
_LIT( KtestdomaiwproLogFileWithTitle, "testdomaiwpro_[%S].txt" );

_LIT( KResourcePath, "C:\\resource\\testdomaiwpro.rsc" );

// FORWARD DECLARATIONS
class CTestDOMAIWPro;
class CAiwMenuPane;

/**
 *  CTestDOMAIWPro test class for STIF Test Framework TestScripter.
 *
 *  @since S60 5.0
 */
NONSHARABLE_CLASS( CTestDOMAIWPro ):public CScriptBase
    {
public: // Constructors and destructor

    /**
     * Two-phased constructor.
     */
    static CTestDOMAIWPro* NewL( CTestModuleIf& aTestModuleIf );

    /**
     * Destructor.
     */
    virtual ~CTestDOMAIWPro();

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
    CTestDOMAIWPro( CTestModuleIf& aTestModuleIf );

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

private: // Test AiwMenu.h
    /**
     * TestAMConstructor test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAMConstructorL( CStifItemParser& /*aItem*/ );

    /**
     * TestAMAddMenuItemL test function for testing the AddMenuItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAMAddMenuItemL( CStifItemParser& /*aItem*/ );

    /**
     * TestAMAddMenuItemLTextL test function for testing the AddMenuItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAMAddMenuItemLTextL( CStifItemParser& /*aItem*/ );

    /**
     * TestAMAddMenuItemsL test function for testing the AddMenuItemsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAMAddMenuItemsL( CStifItemParser& /*aItem*/ );

    /**
     * TestAMAddMenuItemsLFileNameL test function for testing the AddMenuItemsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAMAddMenuItemsLFileNameL( CStifItemParser& /*aItem*/ );

    /**
     * TestAMMenuCmdIdL test function for testing the MenuCmdId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAMMenuCmdIdL( CStifItemParser& /*aItem*/ );

    /**
     * TestAMDynCmdIdL test function for testing the DynCmdId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAMDynCmdIdL( CStifItemParser& /*aItem*/ );

    /**
     * TestAMServiceCmdIdL test function for testing the ServiceCmdId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAMServiceCmdIdL( CStifItemParser& /*aItem*/ );

    /**
     * TestAMAddTitleItemL test function for testing the AddTitleItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAMAddTitleItemL( CStifItemParser& /*aItem*/ );

private: // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTDOMAIWPRO_H
// End of File
