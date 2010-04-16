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
* Description:  Test server application services api
*
*/



#ifndef C_TESTDOMSERVERAPPSERVICE_H
#define C_TESTDOMSERVERAPPSERVICE_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <aknlaunchappservice.h>
#include <aknnullservice.h>
#include <aknopenfileservice.h>
#include <aiwgenericparam.h>
#include <coemain.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdomserverappserviceLogPath, "\\logs\\testframework\\testdomserverappservice\\" ); 
// Log file
_LIT( KtestdomserverappserviceLogFile, "testdomserverappservice.txt" ); 
_LIT( KtestdomserverappserviceLogFileWithTitle, "testdomserverappservice_[%S].txt" );

/**
*  CTestDomServerAppService test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDomServerAppService ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDomServerAppService* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDomServerAppService();

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
    CTestDomServerAppService( CTestModuleIf& aTestModuleIf );

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
    * TestCAknLaunchAppServiceNewL test NewL function of CAknLaunchAppService
    * in aknlaunchappservice.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknLaunchAppServiceNewL( CStifItemParser& aItem );
    
    /**
    * TestCAknLaunchAppServiceNewL test NewL function of CAknNullService
    * in aknnullservice.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknNullServiceNewL( CStifItemParser& aItem );
    
    /**
    * TestCAknOpenFileServiceNewL test NewL functions of CAknOpenFileService
    * in aknopenfileservice.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknOpenFileServiceNewL( CStifItemParser& aItem );
    
    /**
    * TestCAknOpenFileServiceSecNewL test another NewL functions of 
    * CAknOpenFileService in aknopenfileservice.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknOpenFileServiceSecNewL( CStifItemParser& aItem );
    
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    };

#endif      // C_TESTDOMSERVERAPPSERVICE_H

// End of File
