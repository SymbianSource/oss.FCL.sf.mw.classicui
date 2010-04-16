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
* Description:  test aknsgcc.h, aknstatuspaneutils.h and aknsyncdraw.h
*
*/



#ifndef C_TESTDOMSTATUSPANE_H
#define C_TESTDOMSTATUSPANE_H

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
_LIT( KtestdomstatuspaneLogPath, "\\logs\\testframework\\testdomstatuspane\\" ); 
// Log file
_LIT( KtestdomstatuspaneLogFile, "testdomstatuspane.txt" ); 
_LIT( KtestdomstatuspaneLogFileWithTitle, "testdomstatuspane_[%S].txt" );

/**
*  CTestDOMStatusPane test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDOMStatusPane ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMStatusPane* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMStatusPane();

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
    CTestDOMStatusPane( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // test functions of test aknsgcc.h

    /**
    * test CreateL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccCreateL( CStifItemParser& aItem );

    /**
    * test HandleChangeL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccHandleChangeL( CStifItemParser& aItem );

    /**
    * test AknSrv method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccAknSrvL( CStifItemParser& aItem );

    /**
    * test SetStatusPaneRedrawCoordinator method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccSetStatusPaneRedrawCoordinator( CStifItemParser& aItem );

    /**
    * test BlockServerStatusPaneRedrawsL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccBlockServerStatusPaneRedrawsL( CStifItemParser& aItem );

    /**
    * test RedrawServerStatusPane method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccRedrawServerStatusPane( CStifItemParser& aItem );

    /**
    * test DrawSynchronizer method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccDrawSynchronizerL( CStifItemParser& aItem );

    /**
    * test PrepareForAppExit method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccPrepareForAppExit( CStifItemParser& aItem );

    /**
    * test SetSystemFaded method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccSetSystemFaded( CStifItemParser& aItem );

    /**
    * test IsSystemFaded method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccIsSystemFaded( CStifItemParser& aItem );

    /**
    * test PixelsAndRotation method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccPixelsAndRotation( CStifItemParser& aItem );

    /**
    * test CalculatePixelsAndRotation method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccCalculatePixelsAndRotation( CStifItemParser& aItem );

    /**
    * test ScreenMode method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccScreenMode( CStifItemParser& aItem );

    /**
    * test CalculateScreenMode method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccCalculateScreenMode( CStifItemParser& aItem );

    /**
    * test CalculateScreenMode method with TInt param.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccCalculateScreenModeWithInt( CStifItemParser& aItem );

    /**
    * test SetKeyBlockMode method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccSetKeyBlockMode( CStifItemParser& aItem );

    /**
    * test SetKeyboardRepeatRate method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccSetKeyboardRepeatRate( CStifItemParser& aItem );

    /**
    * test CurrentStatuspaneResource method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccCurrentStatuspaneResource( CStifItemParser& aItem );

    /**
    * test LayoutConfig method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccLayoutConfig( CStifItemParser& aItem );

    /**
    * test LayoutConfigBuf method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccLayoutConfigBuf( CStifItemParser& aItem );

    /**
    * test MoveApp method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccMoveApp( CStifItemParser& aItem );

    /**
    * test SetImpl method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSgccSetImplL( CStifItemParser& aItem );

private: // test functions of test aknstatuspaneutils.h

    /**
    * test StaconPaneActive method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestUtilsStaconPaneActive( CStifItemParser& aItem );

    /**
    * test StaconSoftKeysLeft method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestUtilsStaconSoftKeysLeft( CStifItemParser& aItem );

    /**
    * test StaconSoftKeysRight method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestUtilsStaconSoftKeysRight( CStifItemParser& aItem );

    /**
    * test IdleLayoutActive method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestUtilsIdleLayoutActive( CStifItemParser& aItem );

    /**
    * test FlatLayoutActive method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestUtilsFlatLayoutActive( CStifItemParser& aItem );

    /**
    * test UsualLayoutActive method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestUtilsUsualLayoutActive( CStifItemParser& aItem );

    /**
    * test SmallLayoutActive method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestUtilsSmallLayoutActive( CStifItemParser& aItem );

    /**
    * test TouchPaneCompatibleLayoutActive method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestUtilsTouchPaneCompatibleLayoutActive( CStifItemParser& aItem );

    /**
    * test ExtendedStaconPaneActive method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestUtilsExtendedStaconPaneActive( CStifItemParser& aItem );

    /**
    * test ExtendedFlatLayoutActive method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestUtilsExtendedFlatLayoutActive( CStifItemParser& aItem );

private: // test functions of test aknsyncdraw.h

    /**
    * test default constructor method of TAknSyncControlDrawer.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSyncDefConL( CStifItemParser& aItem );

    /**
    * test SetControl method of TAknSyncControlDrawer.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSyncSetControlL( CStifItemParser& aItem );

    /**
    * test MasrPrepareForDraw method of TAknSyncControlDrawer.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSyncMasrPrepareForDrawL( CStifItemParser& aItem );

    /**
    * test MasrDraw method of TAknSyncControlDrawer.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSyncMasrDrawL( CStifItemParser& aItem );

    /**
    * test MasrDeactivateGc method of TAknSyncControlDrawer.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSyncMasrDeactivateGcL( CStifItemParser& aItem );

    /**
    * test MasrActivateGc method of TAknSyncControlDrawer.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSyncMasrActivateGcL( CStifItemParser& aItem );

    /**
    * test NewL method of CAknDrawSynchronizer.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSynchNewL( CStifItemParser& aItem );

    /**
    * test AddL method of CAknDrawSynchronizer.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSynchAddL( CStifItemParser& aItem );

    /**
    * test Remove method of CAknDrawSynchronizer.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSynchRemoveL( CStifItemParser& aItem );

    /**
    * test Signal method of CAknDrawSynchronizer.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSynchSignalL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };

#endif      // C_TESTDOMSTATUSPANE_H

// End of File
