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
* Description:  test EIKSRVUI.H
*
*/



#ifndef C_TESTDOMAPPLICATIONSWITCHING_H
#define C_TESTDOMAPPLICATIONSWITCHING_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <coemain.h>
#include <eikenv.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdomapplicationswitchingLogPath, "\\logs\\testframework\\testdomapplicationswitching\\" ); 
// Log file
_LIT( KtestdomapplicationswitchingLogFile, "testdomapplicationswitching.txt" ); 
_LIT( KtestdomapplicationswitchingLogFileWithTitle, "testdomapplicationswitching_[%S].txt" );

/**
*  CTestDOMApplicationSwitching test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDOMApplicationSwitching ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMApplicationSwitching* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMApplicationSwitching();

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
    CTestDOMApplicationSwitching( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Test EIKSRVUI.h
/*                               class CEikServAppUiBase                     */
    /**
     * TestSAUBNewLC test function for testing the 
     *     NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBNewLC( CStifItemParser& aItem );
    
    /**
     * TestSAUBDeconstructor test function for testing the 
     *     ~CEikServAppUiBase function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBDeconstructor( CStifItemParser& aItem );
    
    /**
     * TestSAUBNotifyAlarmServerOfTaskChangeL test function for testing the 
     *     NotifyAlarmServerOfTaskChangeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBNotifyAlarmServerOfTaskChangeL( CStifItemParser& aItem );
    
    /**
     * TestSAUBEnableTaskListL test function for testing the 
     *     EnableTaskListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBEnableTaskListL( CStifItemParser& aItem );
    
    /**
     * TestSAUBLaunchTaskListL test function for testing the 
     *     LaunchTaskListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBLaunchTaskListL( CStifItemParser& aItem );
    
    /**
     * TestSAUBCycleTasksL test function for testing the 
     *     CycleTasksL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBCycleTasksL( CStifItemParser& aItem );
    
    /**
     * TestSAUBSetStatusPaneFlags test function for testing the 
     *     SetStatusPaneFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBSetStatusPaneFlags( CStifItemParser& aItem );
    
    /**
     * TestSAUBSetStatusPaneLayoutL test function for testing the 
     *     SetStatusPaneLayoutL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBSetStatusPaneLayoutL( CStifItemParser& aItem );
    
    /**
     * TestSAUBBlankScreen test function for testing the 
     *     BlankScreenL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBBlankScreen( CStifItemParser& aItem );
    
    /**
     * TestSAUBUnblankScreen test function for testing the 
     *     UnblankScreen function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBUnblankScreen( CStifItemParser& aItem );
    
    /**
     * TestSAUBShutdownAppsL test function for testing the 
     *     ShutdownAppsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBShutdownAppsL( CStifItemParser& aItem );
    
    /**
     * TestSAUBHandleForegroundEventL test function for testing the 
     *     HandleForegroundEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBHandleForegroundEventL( CStifItemParser& aItem );
    
    /**
     * TestSAUBAlertGroupWin test function for testing the 
     *     AlertGroupWin function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBAlertGroupWin( CStifItemParser& aItem );
    
    /**
     * TestSAUBBringAlertGroupWinForwards test function for testing the 
     *     BringAlertGroupWinForwards function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBBringAlertGroupWinForwards( CStifItemParser& aItem );
    
    /**
     * TestSAUBConstruct test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBConstruct( CStifItemParser& aItem );
    
    /**
     * TestSAUBInitialize test function for testing the 
     *     InitializeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBInitialize( CStifItemParser& aItem );
    
    /**
     * TestSAUBCEikServAppUiBase test function for testing the 
     *     CEikServAppUiBase function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBCEikServAppUiBase( CStifItemParser& aItem );
    
    /**
     * TestSAUBHandleWsEventL test function for testing the 
     *     HandleWsEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBHandleWsEventL( CStifItemParser& aItem );
    
    /**
     * TestSAUBHandleThreadExit test function for testing the 
     *     HandleThreadExitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBHandleThreadExit( CStifItemParser& aItem );
    
    /**
     * TestSAUBHandleResourceChangeL test function for testing the 
     *     HandleResourceChangeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUBHandleResourceChangeL( CStifItemParser& aItem );

/*                               class CEikServAppUi                        */
    /**
     * TestSAUSuppressAppSwitching test function for testing the 
     *     SuppressAppSwitching function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUSuppressAppSwitching( CStifItemParser& aItem );
    
    /**
     * TestSAUActivateDisplayIfNeeded test function for testing the 
     *     ActivateDisplayIfNeeded function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUActivateDisplayIfNeeded( CStifItemParser& aItem );
    
    /**
     * TestSAUCreateSessionL test function for testing the 
     *     CreateSessionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUCreateSessionL( CStifItemParser& aItem );
    
    /**
     * TestSAUHideApplicationFromFswL test function for testing the 
     *     HideApplicationFromFswL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUHideApplicationFromFswL( CStifItemParser& aItem );
    
    /**
     * TestSAUStartNewServerApplication test function for testing the 
     *     StartNewServerApplicationL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSAUStartNewServerApplication( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * CEikonEnv Property
     * not own
     */
    CEikonEnv* iEnv;

    };

#endif      // C_TESTDOMAPPLICATIONSWITCHING_H

// End of File

