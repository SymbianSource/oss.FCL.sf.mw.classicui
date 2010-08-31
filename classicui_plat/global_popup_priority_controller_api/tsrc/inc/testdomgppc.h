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
* Description:  global_popup_priority_controller_api
*
*/



#ifndef C_TESTDOMGPPC_H
#define C_TESTDOMGPPC_H

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
_LIT( KtestdomgppcLogPath, "\\logs\\testframework\\testdomgppc\\" ); 
// Log file
_LIT( KtestdomgppcLogFile, "testdomgppc.txt" ); 
_LIT( KtestdomgppcLogFileWithTitle, "testdomgppc_[%S].txt" );

/**
*  CTestDOMGPPC test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDOMGPPC ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMGPPC* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMGPPC();

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
    CTestDOMGPPC( CTestModuleIf& aTestModuleIf );

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
    * TestGPPCEnablePriorityControlL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestGPPCEnablePriorityControlL( CStifItemParser& aItem );
    /**
    * TestGPPCAllowGlobalPopups test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestGPPCAllowGlobalPopups( CStifItemParser& aItem );
    /**
    * TestGPPCSetPopupPriorityL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestGPPCSetPopupPriorityL( CStifItemParser& aItem );
    /**
    * TestGPPCRemovePopupPriorityL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestGPPCRemovePopupPriorityL( CStifItemParser& aItem );
    /**
    * TestGPPCShowPopupL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestGPPCShowPopupL( CStifItemParser& aItem );
    /**
    * TestGPPCSetRootWinOrdinalPosition test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestGPPCSetRootWinOrdinalPosition( CStifItemParser& aItem );
    /**
    * TestGPPCAddSubPopupL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestGPPCAddSubPopupL( CStifItemParser& aItem );
    /**
    * TestGPPCAddPopupToControlStackL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestGPPCAddPopupToControlStackL( CStifItemParser& aItem );
    /**
    * TestGPPCRouseSleepingPopupL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestGPPCRouseSleepingPopupL( CStifItemParser& aItem );
    /**
    * TestGPPCFadeBehindPopupL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestGPPCFadeBehindPopupL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    

    };

#endif      // C_TESTDOMGPPC_H

// End of File
