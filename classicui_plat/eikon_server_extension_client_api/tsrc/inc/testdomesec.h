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
* Description:  eikon_server_extension_client_api
*
*/



#ifndef C_TESTDOMESEC_H
#define C_TESTDOMESEC_H

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
_LIT( KtestdomesecLogPath, "\\logs\\testframework\\testdomesec\\" ); 
// Log file
_LIT( KtestdomesecLogFile, "testdomesec.txt" ); 
_LIT( KtestdomesecLogFileWithTitle, "testdomesec_[%S].txt" );

/**
*  CTestDOMESEC test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDOMESEC ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMESEC* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMESEC();

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
    CTestDOMESEC( CTestModuleIf& aTestModuleIf );

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
    * TestEAUSConstructorL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEAUSConstructorL( CStifItemParser& aItem );
    /**
    * TestEAUSSetSgcParamsL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEAUSSetSgcParamsL( CStifItemParser& aItem );
    /**
    * TestEAUSBlockServerStatusPaneRedrawsL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEAUSBlockServerStatusPaneRedrawsL( CStifItemParser& aItem );
    /**
    * TestEAUSRedrawServerStatusPaneL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEAUSRedrawServerStatusPaneL( CStifItemParser& aItem );
    /**
    * TestEAUSPrepareForAppExitL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEAUSPrepareForAppExitL( CStifItemParser& aItem );
    /**
    * TestEAUSSetSystemFadedL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEAUSSetSystemFadedL( CStifItemParser& aItem );
    /**
    * TestEAUSIsSystemFadedL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEAUSIsSystemFadedL( CStifItemParser& aItem );
    /**
    * TestEAUSShutdownAppsL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEAUSShutdownAppsL( CStifItemParser& aItem );
    /**
    * TestEAUSAllowNotifierAppServersToLoadL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEAUSAllowNotifierAppServersToLoadL( CStifItemParser& aItem );
    /**
    * TestEAUSDoSynchWaitForAknCapServerL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEAUSDoSynchWaitForAknCapServerL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;


    };

#endif      // C_TESTDOMESEC_H

// End of File
