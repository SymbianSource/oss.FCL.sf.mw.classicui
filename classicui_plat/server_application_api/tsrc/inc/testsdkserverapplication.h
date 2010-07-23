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
* Description:  Test AknServerApp.h 
*
*/

#ifndef C_TESTSDKSERVERAPPLICATION_H
#define C_TESTSDKSERVERAPPLICATION_H

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
_LIT( KtestsdkserverapplicationLogPath, "\\logs\\testframework\\testsdkserverapplication\\" ); 
// Log file
_LIT( KtestsdkserverapplicationLogFile, "testsdkserverapplication.txt" ); 
_LIT( KtestsdkserverapplicationLogFileWithTitle, "testsdkserverapplication_[%S].txt" );

/**
*  CTestSDKserverApplication test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKserverApplication ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKserverApplication* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKserverApplication();

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
    CTestSDKserverApplication( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Test AknServerApp.h
/*                               class RAknAppServiceBase                   */
    /**
     * TestASBConnectChainedAppL test function for testing the 
     *     ConnectChainedAppL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASBConnectChainedAppL( CStifItemParser& aItem );
    
    /**
     * TestASBCloseL test function for testing the 
     *     Close function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASBCloseL( CStifItemParser& aItem );
    
/*                         class MAknServerAppExitObserver                   */
    /**
     * TestSAEOHandleServerAppExitL test function for testing the 
     *     HandleServerAppExit function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAEOHandleServerAppExitL( CStifItemParser& aItem );
    
/*                            class CAknAppServiceBase                       */
    /**
     * TestASBCAknAppServiceBaseL test function for testing the 
     *     CAknAppServiceBase function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASBCAknAppServiceBaseL( CStifItemParser& aItem );
    
    /**
     * TestASBDeconstructorL test function for testing the 
     *     ~CAknAppServiceBase function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASBDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestASBCreateL test function for testing the 
     *     CreateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASBCreateL( CStifItemParser& aItem );
    
    /**
     * TestASBServiceL test function for testing the 
     *     ServiceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASBServiceL( CStifItemParser& aItem );
    
    /**
     * TestASBServiceErrorL test function for testing the 
     *     ServiceError function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASBServiceErrorL( CStifItemParser& aItem );
    
/*                               class CAknAppServer                         */
    
    /**
     * TestASDeconstructorL test function for testing the 
     *     ~CAknAppServer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestASConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASConstructL( CStifItemParser& aItem );
    
    /**
     * TestASCreateServiceL test function for testing the 
     *     CreateServiceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASCreateServiceL( CStifItemParser& aItem );
    
    /**
     * TestASHandleAllClientsClosedL test function for testing the 
     *     HandleAllClientsClosed function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASHandleAllClientsClosedL( CStifItemParser& aItem );
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;


    };

#endif      // C_TESTSDKSERVERAPPLICATION_H

// End of File
