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
* Description:  avkon_secondary_display_support_api
*
*/



#ifndef C_TESTDOMASDS_H
#define C_TESTDOMASDS_H

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
_LIT( KtestdomasdsLogPath, "\\logs\\testframework\\testdomasds\\" ); 
// Log file
_LIT( KtestdomasdsLogFile, "testdomasds.txt" ); 
_LIT( KtestdomasdsLogFileWithTitle, "testdomasds_[%S].txt" );

/**
*  CTestDOMASDS test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
class CAknMediatorFacade;
NONSHARABLE_CLASS( CTestDOMASDS ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMASDS* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMASDS();

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
    CTestDOMASDS( CTestModuleIf& aTestModuleIf );

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
    * TestMFNewL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMFNewL( CStifItemParser& aItem );
    /**
    * TestMFIssueCommandL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMFIssueCommandL( CStifItemParser& aItem );
    /**
    * TestMFCancelCommandL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMFCancelCommandL( CStifItemParser& aItem );
    /**
    * TestMFResetBufferL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMFResetBufferL( CStifItemParser& aItem );
    /**
    * TestMFSetObserverL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMFSetObserverL( CStifItemParser& aItem );
    /**
    * TestMFPostUpdatedDataL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMFPostUpdatedDataL( CStifItemParser& aItem );
    /**
    * TestSDDExternalizeL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSDDExternalizeL( CStifItemParser& aItem );
    /**
    * TestSDDInternalizeL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSDDInternalizeL( CStifItemParser& aItem );
    /**
    * TestSDDInsertGlobalListQueryItemIdsL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSDDInsertGlobalListQueryItemIdsL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * for test
     * Not own.
     */
    CAknMediatorFacade* iMediatorFacade;

    };

#endif      // C_TESTDOMASDS_H

// End of File
