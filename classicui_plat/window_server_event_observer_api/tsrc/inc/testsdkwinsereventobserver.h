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
* Description:  test AknWsEventObserver.h
*
*/



#ifndef C_TESTSDKWINSEREVENTOBSERVER_H
#define C_TESTSDKWINSEREVENTOBSERVER_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <aknwseventobserver.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkwinsereventobserverLogPath, "\\logs\\testframework\\testsdkwinsereventobserver\\" ); 
// Log file
_LIT( KtestsdkwinsereventobserverLogFile, "testsdkwinsereventobserver.txt" ); 
_LIT( KtestsdkwinsereventobserverLogFileWithTitle, "testsdkwinsereventobserver_[%S].txt" );

/**
*  CTestSDKWinSerEventObserver test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKWinSerEventObserver ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKWinSerEventObserver* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKWinSerEventObserver();

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
    CTestSDKWinSerEventObserver( CTestModuleIf& aTestModuleIf );

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
     * TestWEMAddObserverL test function for testing the 
     *     AddObserverL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestWEMAddObserverL( CStifItemParser& aItem );
    
    /**
     * TestWEMRemoveObserverL test function for testing the 
     *     RemoveObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestWEMRemoveObserverL( CStifItemParser& aItem );
    
    /**
     * TestWEMHandleWsEventL test function for testing the 
     *     HandleWsEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestWEMHandleWsEventL( CStifItemParser& aItem );
    
    /**
     * TestWEMEnableL test function for testing the 
     *     Enable function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestWEMEnableL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };


#endif      // C_TESTSDKWINSEREVENTOBSERVER_H

// End of File
