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
* Description:  test avkon_ui_server_api
*
*/



#ifndef C_TESTDOMUISERVER_H
#define C_TESTDOMUISERVER_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <akncapserverclient.h>
#include <aknconsts.h>
#include <aknnotifystd.h>
#include <eikapp.h>
#include <aknutils.h>
#include <aknnotifiercontrollerutilities.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdomuiserverLogPath, "\\logs\\testframework\\testdomuiserver\\" ); 
// Log file
_LIT( KtestdomuiserverLogFile, "testdomuiserver.txt" ); 
_LIT( KtestdomuiserverLogFileWithTitle, "testdomuiserver_[%S].txt" );

/**
*  CTestDomUiServer test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDomUiServer ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */

    static CTestDomUiServer* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDomUiServer();

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
    CTestDomUiServer( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Test akncapserverclient.h
    /**
    * TestUSConnectAndSendAppsKeySuppress test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSConnectAndSendAppsKeySuppress( CStifItemParser& aItem );
    
    /**
    * TestUSHideApplicationFromFswL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSHideApplicationFromFsw( CStifItemParser& aItem );
    
    /**
    * TestUSUnlockMedia test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSUnlockMedia( CStifItemParser& aItem );
    
    /**
    * TestUSCancelUnlockMedia test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSCancelUnlockMedia( CStifItemParser& aItem );
    
    /**
    * TestUSEnableTaskListL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSEnableTaskList( CStifItemParser& aItem );
    
    /**
    * TestUSMakeTaskListVisibleL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSMakeTaskListVisible( CStifItemParser& aItem );
    
    /**
    * TestUSUpdateTaskListL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSUpdateTaskList( CStifItemParser& aItem );
    
    /**
    * TestUSShutdownAppsL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSShutdownAppsL( CStifItemParser& aItem );
    
    /**
    * TestUSCancelShutdownAppsL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSCancelShutdownApps( CStifItemParser& aItem );
    
    /**
    * TestUSSetSgcParamsL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSSetSgcParams( CStifItemParser& aItem );
    
    /**
    * TestUSSetSgcParamScreenModeL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSSetSgcParamScreenMode( CStifItemParser& aItem );
    
    /**
    * TestUSBlockServerStatusPaneRedrawsL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSBlockServerStatusPaneRedraws( CStifItemParser& aItem );
    
    /**
    * TestUSRedrawServerStatusPaneL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSRedrawServerStatusPane( CStifItemParser& aItem );
    
    /**
    * TestUSPrepareForAppExitL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSPrepareForAppExit( CStifItemParser& aItem );
    
    /**
    * TestUSSetSystemFadedL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSSetSystemFaded( CStifItemParser& aItem );
    
    /**
    * TestUSIsSystemFadedL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSIsSystemFaded( CStifItemParser& aItem );
    
    /**
    * TestUSConnectL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSConnect( CStifItemParser& aItem );
    
    
    /**
    * TestUSRelinquishPriorityToForegroundAppL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSRelinquishPriorityToForegroundApp( CStifItemParser& aItem );
    
    /**
    * TestUSGetPackedConfigL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSGetPackedConfigL( CStifItemParser& aItem );
    
    /**
    * TestUSMoveAppInZOrder test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSMoveAppInZOrder( CStifItemParser& aItem );
    
    /**
    * TestUSSetStatusPaneFlagsL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSSetStatusPaneFlags( CStifItemParser& aItem );
    
    /**
    * TestUSSetStatusPaneLayoutL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSSetStatusPaneLayout( CStifItemParser& aItem );
    
    /**
    * TestUSBlankScreenL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSBlankScreen( CStifItemParser& aItem );
    
    /**
    * TestUSUnblankScreenL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSUnblankScreen( CStifItemParser& aItem );
    
    /**
    * TestUSUnblankScreenL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSSetKeyboardRepeatRate( CStifItemParser& aItem );
    
    /**
    * TestUSSetKeyblockModeL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSSetKeyblockMode( CStifItemParser& aItem );
    
    /**
    * TestUSDoEikonServerConnectL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSDoEikonServerConnect( CStifItemParser& aItem );
    
    /**
    * TestUSShowKeysLockedNoteL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSShowKeysLockedNote( CStifItemParser& aItem );
    
    /**
    * TestUSShowGlobalNoteL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSShowGlobalNoteL( CStifItemParser& aItem );
    
    /**
    * TestUSStatusPaneResourceIdL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSStatusPaneResourceId( CStifItemParser& aItem );
    
    /**
    * TestUSCreateActivateViewEventL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSCreateActivateViewEventL( CStifItemParser& aItem );
    
    /**
    * TestUSCurrentAppStatuspaneResourceL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSCurrentAppStatuspaneResource( CStifItemParser& aItem );
    
    /**
    * TestUSSetCurrentAppStatuspaneResourceL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSSetCurrentAppStatuspaneResource( CStifItemParser& aItem );
    
    /**
    * TestUSSetFgSpDataSubscriberIdL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSSetFgSpDataSubscriberId( CStifItemParser& aItem );
    
    /**
    * TestUSRotateScreenL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSRotateScreen( CStifItemParser& aItem );
    
    /**
    * TestUSTaskSwitchingSupressedL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSTaskSwitchingSupressed( CStifItemParser& aItem );
    
    /**
    * TestUSShowLongTapAnimationL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSShowLongTapAnimation( CStifItemParser& aItem );
    
    /**
    * TestUSHideLongTapAnimationL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSHideLongTapAnimation( CStifItemParser& aItem );
    
    /**
    * TestUSGetAliasKeyCodeL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSGetAliasKeyCode( CStifItemParser& aItem );
    
    /**
    * TestUSGetPhoneIdleViewIdL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSGetPhoneIdleViewId( CStifItemParser& aItem );
    
    /**
    * TestUSStartAknCapserverL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSStartAknCapserverL( CStifItemParser& aItem );
    
    /**
    * TestUSDoNotifierControllerCommandL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSDoNotifierControllerCommand( CStifItemParser& aItem );
    
    /**
    * TestUSPreAllocateDynamicSoftNoteEventL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSPreAllocateDynamicSoftNoteEvent( CStifItemParser& aItem );
    
    /**
    * TestUSNotifyDynamicSoftNoteEventLL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSNotifyDynamicSoftNoteEventL( CStifItemParser& aItem );
    
    /**
    * TestUSCancelDynamicSoftNoteEventNotificationL test function of class RAknUiServer in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSCancelDynamicSoftNoteEventNotification( CStifItemParser& aItem );
    
    /**
    * TestUSAknStartupApaServerProcessL test function in akncapserverclient.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSAknStartupApaServerProcess( CStifItemParser& aItem );
    

    /**
    * TestUSAknGetInUseDiscreetPopupRect test function in akncapserverclient.h
    * @since S60 5.2
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestUSAknGetInUseDiscreetPopupRect( CStifItemParser& aItem );
    
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * Pointer of RAknUiServer
     * Own.
     */
    RAknUiServer* iUiServer;

    };

#endif      // C_TESTDOMUISERVER_H

// End of File
