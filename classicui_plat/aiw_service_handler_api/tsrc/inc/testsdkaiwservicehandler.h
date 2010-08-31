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
* Description:    For testing aiw_service_handler_api
*
*/





#ifndef C_TESTSDKAIWSERVICEHANDLER_H
#define C_TESTSDKAIWSERVICEHANDLER_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <coemain.h>
#include <aiwservicehandler.h>
#include <eikmenup.h>
#include <eikmobs.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkaiwservicehandlerLogPath, "\\logs\\testframework\\testsdkaiwservicehandler\\" ); 
// Log file
_LIT( KtestsdkaiwservicehandlerLogFile, "testsdkaiwservicehandler.txt" ); 
_LIT( KtestsdkaiwservicehandlerLogFileWithTitle, "testsdkaiwservicehandler_[%S].txt" );


/**
*  CTestSDKAiwServiceHandler test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKAiwServiceHandler) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKAiwServiceHandler* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKAiwServiceHandler();

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
    CTestSDKAiwServiceHandler( CTestModuleIf& aTestModuleIf );

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

private: // for aiw_service_handler_api

    /**
    * Test NewL and NewLC function of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is a number, 1 for NewL, 2 for NewLC
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerNewFuncL( CStifItemParser& aItem );
    
    /**
    * Test decontructor function of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is not used
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerDeconstructorL( CStifItemParser& aItem );
    
    /**
    * Test Reset function of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is not used
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerResetL( CStifItemParser& aItem );
    
    /**
    * Test NbrOfProviders function of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is not used
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerNbrOfProvidersL( CStifItemParser& aItem );
    
    /**
    * Test two AttachL functions of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is a number, 1 is test resource id as parameter, 2 is test array as parameter
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerAttachAndDetachL( CStifItemParser& aItem );
    
    /**
    * Test GetInterest function of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is not used
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerGetInterestL( CStifItemParser& aItem );
    
    /**
    * Test GetCriteria function of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is not used
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerGetCriteriaL( CStifItemParser& aItem );
    
    /**
    * Test InParamListL and OutParamListL function of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is a number, 1 is test resource id as parameter, 2 is test array as parameter
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerInAndOutParamListL( CStifItemParser& aItem );
    
    /**
    * Test two InitializeMenuPaneL functions of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is a number, 1 is test function with four parameters, 2 is test function with five parameters
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerInitializeMenuPaneL( CStifItemParser& aItem );
    
    /**
    * Test two ServiceCmdByMenuCmd functions of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is not used.
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerServiceCmdByMenuCmdL( CStifItemParser& aItem );
    
    /**
    * Test two ExecuteMenuCmdL functions of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is not used.
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerServiceExecuteMenuCmdL( CStifItemParser& aItem );
    
    /**
    * Test three AttachMenuL functions of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is a number, 
    * 1 test AttachMenuL(TInt aMenuResourceId, TInt aInterestResourceId)
    * 2 test AttachMenuL(TInt aMenuResourceId, TResourceReader& aReader)
    * 3 test AttachMenuL(TInt aMenuResourceId, const RCriteriaArray& aInterest)
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerServiceAttachMenuL( CStifItemParser& aItem );
    
    /**
    * Test DetachMenu function of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is not used
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerServiceDetachMenuL( CStifItemParser& aItem );
    
    /**
    * Test IsSubMenuEmpty function of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is not used
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerServiceIsSubMenuEmptyL( CStifItemParser& aItem );
    
    /**
    * Test IsAiwMenu function of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is not used
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerServiceIsAiwMenuL( CStifItemParser& aItem );
    
    /**
    * Test HandleSubmenuL function of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is not used
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerServiceHandleSubmenuL( CStifItemParser& aItem );
    
    /**
    * Test ReportMenuLaunch function of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is not used
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerServiceReportMenuLaunch( CStifItemParser& aItem );
    
    /**
    * Test ExecuteServiceCmdL function of CAiwServiceHandler
    * @since S60 5.0
    * @aItem is not used
    * return Symbian OS error code.
    */
    virtual TInt TestAiwServiceHandlerServiceExecuteServiceCmdL( CStifItemParser& aItem );
    
    //[TestMethods]

private:    // Data
    enum TSwitchId
        {
        ECaseOne = 1,
        ECaseTwo,
        ECaseThree
        };
    
    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    // Resource file offset
    TInt iOffset;

    };

#endif      // C_TESTSDKAIWSERVICEHANDLER_H

// End of File
