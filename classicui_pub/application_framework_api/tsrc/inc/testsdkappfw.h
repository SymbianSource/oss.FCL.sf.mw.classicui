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
* Description:  Test application_framework_api
*
*/



#ifndef C_TESTSDKAPPFW_H
#define C_TESTSDKAPPFW_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

#include <aknapp.h>
#include <aknappui.h>
#include <akndoc.h>
#include <aknview.h>
#include <aknviewappui.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkappfwLogPath, "\\logs\\testframework\\testsdkappfw\\" ); 
// Log file
_LIT( KtestsdkappfwLogFile, "testsdkappfw.txt" ); 
_LIT( KtestsdkappfwLogFileWithTitle, "testsdkappfw_[%S].txt" );

/**
*  CTestSDKAppFW test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKAppFW ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKAppFW* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKAppFW();

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
    CTestSDKAppFW( CTestModuleIf& aTestModuleIf );

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

private:    // For aknApp.h

    /**
     * TestAppPreDocConstructL test function for testing the PreDocConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppPreDocConstructL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppOpenIniFileLC test function for testing the OpenIniFileLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppOpenIniFileLC( CStifItemParser& /*aItem*/ );

    /**
     * TestAppNewAppServerL test function for testing the NewAppServerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppNewAppServerL( CStifItemParser& /*aItem*/ );

private:    // For AknAppUi.h

    /**
     * TestAppUiBaseCAknAppUiBaseL test function for testing the CAknAppUiBase function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseCAknAppUiBaseL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBBaseConstructL test function for testing the BaseConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBBaseConstructL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseHandleForegroundEventL test function for testing the 
     * HandleForegroundEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseHandleForegroundEventL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBConstructL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBConstructL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseExitL test function for testing the Exit function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseExitL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseSetFadedL test function for testing the SetFadedL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseSetFadedL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseHandleResourceChangeL test function for testing the HandleResourceChangeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseHandleResourceChangeL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseApplicationRect test function for testing the ApplicationRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseApplicationRect( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBasePrepareToExit test function for testing the PrepareToExit function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBasePrepareToExit( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseIsFadedL test function for testing the IsFaded function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseIsFadedL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseEventMonitor test function for testing the EventMonitor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseEventMonitor( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseKeySounds test function for testing the KeySounds function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseKeySounds( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseIsFullScreenAppL test function for testing the IsFullScreenApp function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseIsFullScreenAppL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseIsLayoutAwareApp test function for testing the IsLayoutAwareApp function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseIsLayoutAwareApp( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseSetLayoutAwareApp test function for testing the SetLayoutAwareApp function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseSetLayoutAwareApp( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseIsForeground test function for testing the IsForeground function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseIsForeground( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseIsPartialForeground test function for testing the IsPartialForeground function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseIsPartialForeground( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseOrientationL test function for testing the Orientation function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseOrientationL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseOrientationCanBeChanged test function for testing the OrientationCanBeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseOrientationCanBeChanged( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseSetOrientationL test function for testing the SetOrientationL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseSetOrientationL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseLocalUiZoom test function for testing the LocalUiZoom function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseLocalUiZoom( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseSetLocalUiZoom test function for testing the SetLocalUiZoom function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseSetLocalUiZoom( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseApplyLayoutChangeL test function for testing the ApplyLayoutChangeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseApplyLayoutChangeL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseSetKeyEventFlags test function for testing the SetKeyEventFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseSetKeyEventFlags( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBasePointerEventModifier test function for testing the PointerEventModifier function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBasePointerEventModifier( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseHandleScreenDeviceChangedL test function for testing the 
     * HandleScreenDeviceChangedL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseHandleScreenDeviceChangedL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseHandleApplicationSpecificEventL test function for testing the 
     * HandleApplicationSpecificEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseHandleApplicationSpecificEventL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseSetFullScreenAppL test function for testing the SetFullScreenApp function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseSetFullScreenAppL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseReplaceKeySoundsL test function for testing the ReplaceKeySoundsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseReplaceKeySoundsL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseMopSupplyObject test function for testing the MopSupplyObject function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseMopSupplyObject( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseConstructL test function for testing the BaseConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseConstructL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiConstructL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiConstructL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiStatusPaneL test function for testing the StatusPane function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiStatusPaneL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiCba test function for testing the Cba function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiCba( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiTouchPane test function for testing the TouchPane function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiTouchPane( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiPopupToolbar test function for testing the PopupToolbar function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiPopupToolbar( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiCurrentPopupToolbar test function for testing the CurrentPopupToolbar function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiCurrentPopupToolbar( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiCurrentFixedToolbar test function for testing the CurrentFixedToolbar function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiCurrentFixedToolbar( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiProcessCommandL test function for testing the ProcessCommandL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiProcessCommandL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiHandleError test function for testing the HandleError function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiHandleError( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiRunAppShutterL test function for testing the RunAppShutter function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiRunAppShutterL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiIsAppShutterRunning test function for testing the IsAppShutterRunning function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiIsAppShutterRunning( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiHandleViewDeactivation test function for testing the HandleViewDeactivation function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiHandleViewDeactivation( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiPrepareToExit test function for testing the PrepareToExit function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiPrepareToExit( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiHandleTouchPaneSizeChange test function for testing the HandleTouchPaneSizeChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiHandleTouchPaneSizeChange( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiHandleStatusPaneSizeChange test function for testing the HandleStatusPaneSizeChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiHandleStatusPaneSizeChange( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiHandleSystemEventL test function for testing the HandleSystemEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiHandleSystemEventL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiReserved_MtsmPosition test function for testing the 
     * Reserved_MtsmPosition function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiReserved_MtsmPosition( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiReserved_MtsmObject test function for testing the 
     * Reserved_MtsmObject function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiReserved_MtsmObject( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiHandleForegroundEventL test function for testing the 
     * HandleForegroundEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiHandleForegroundEventL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiHandleWsEventL test function for testing the HandleWsEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiHandleWsEventL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiSetKeyBlockMode test function for testing the SetKeyBlockMode function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiSetKeyBlockMode( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiHandleErrorL test function for testing the HandleErrorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiHandleErrorL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiHideApplicationFromFSW test function for testing the 
     * HideApplicationFromFSW function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiHideApplicationFromFSW( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiGetAliasKeyCodeL test function for testing the GetAliasKeyCodeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiGetAliasKeyCodeL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiSetAliasKeyCodeResolverL test function for testing the 
     * SetAliasKeyCodeResolverL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiSetAliasKeyCodeResolverL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiCaptureKey test function for testing the CaptureKey function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiCaptureKey( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiCaptureKeyL test function for testing the CaptureKeyL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiCaptureKeyL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiExitHidesInBackground test function for testing the 
     * ExitHidesInBackground function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiExitHidesInBackground( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiHideInBackground test function for testing the HideInBackground function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiHideInBackground( CStifItemParser& /*aItem*/ );

private:    // For AknDoc.h

    /**
     * TestDocOpenFileL test function for testing the OpenFileL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDocOpenFileL( CStifItemParser& /*aItem*/ );

    /**
     * TestDocOpenFileLStoreL test function for testing the OpenFileL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDocOpenFileLStoreL( CStifItemParser& /*aItem*/ );

    /**
     * TestDocCAknDocumentL test function for testing the CAknDocument function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDocCAknDocumentL( CStifItemParser& /*aItem*/ );

private:    // For aknview.h

    /**
     * TestViewCAknViewL test function for testing the CAknView function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewCAknViewL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewBaseConstructL test function for testing the BaseConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewBaseConstructL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewConstructMenuAndCbaEarlyL test function for testing the 
     * ConstructMenuAndCbaEarlyL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewConstructMenuAndCbaEarlyL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewActivateViewL test function for testing the ActivateViewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewActivateViewL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewActivateViewLCustomL test function for testing the ActivateViewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewActivateViewLCustomL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewIdL test function for testing the Id function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewIdL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewHandleStatusPaneSizeChangeL test function for testing the 
     * HandleStatusPaneSizeChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewHandleStatusPaneSizeChangeL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewViewIdL test function for testing the ViewId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewViewIdL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewProcessCommandL test function for testing the ProcessCommandL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewProcessCommandL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewHandleCommandL test function for testing the HandleCommandL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewHandleCommandL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewMenuBarL test function for testing the MenuBar function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewMenuBarL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewClientRectL test function for testing the ClientRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewClientRectL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewStopDisplayingMenuBarL test function for testing the 
     * StopDisplayingMenuBar function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewStopDisplayingMenuBarL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewIsForegroundL test function for testing the IsForeground function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewIsForegroundL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewHandleViewRectChangeL test function for testing the 
     * HandleViewRectChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewHandleViewRectChangeL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewRedrawL test function for testing the Redraw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewRedrawL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAknViewActivatedL test function for testing the 
     * AknViewActivatedL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAknViewActivatedL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAppUiL test function for testing the AppUi function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewStatusPaneL test function for testing the StatusPane function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewStatusPaneL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewCbaL test function for testing the Cba function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewCbaL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewDoActivateL test function for testing the DoActivateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewDoActivateL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewViewActivatedL test function for testing the ViewActivatedL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewViewActivatedL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewViewDeactivatedL test function for testing the ViewDeactivated function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewViewDeactivatedL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewViewScreenDeviceChangedL test function for testing the 
     * ViewScreenDeviceChangedL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewViewScreenDeviceChangedL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewMopSupplyObjectL test function for testing the MopSupplyObject function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewMopSupplyObjectL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewMopNextL test function for testing the MopNext function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewMopNextL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewSetEmphasisL test function for testing the SetEmphasis function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewSetEmphasisL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewHandleForegroundEventL test function for testing the 
     * HandleForegroundEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewHandleForegroundEventL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewToolbarL test function for testing the Toolbar function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewToolbarL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewStopDisplayingToolbarL test function for testing the 
     * StopDisplayingToolbar function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewStopDisplayingToolbarL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewToolbarShownOnViewActivationL test function for testing the 
     * ToolbarShownOnViewActivation function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewToolbarShownOnViewActivationL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewShowToolbarOnViewActivationL test function for testing the 
     * ShowToolbarOnViewActivation function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewShowToolbarOnViewActivationL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewSetToolbarL test function for testing the SetToolbar function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewSetToolbarL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewCreateAndSetToolbarL test function for testing the 
     * CreateAndSetToolbarL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewCreateAndSetToolbarL( CStifItemParser& /*aItem*/ );

private:    // For aknViewAppUi.h

    /**
     * TestViewAppUiBaseConstructL test function for testing the 
     * BaseConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiBaseConstructL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAppUiActivateLocalViewL test function for testing the 
     * ActivateLocalViewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiActivateLocalViewL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAppUiActivateLocalViewLCustomL test function for testing the 
     * ActivateLocalViewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiActivateLocalViewLCustomL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAppUiViewL test function for testing the View function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiViewL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAppUiAddViewL test function for testing the AddViewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiAddViewL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAppUiRemoveViewL test function for testing the RemoveView function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiRemoveViewL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAppUiProcessCommandL test function for testing the 
     * ProcessCommandL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiProcessCommandL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAppUiStopDisplayingMenuBarL test function for testing the 
     * StopDisplayingMenuBar function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiStopDisplayingMenuBarL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAppUiSetSplitViewL test function for testing the SetSplitViewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiSetSplitViewL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAppUiRemoveSplitViewL test function for testing the 
     * RemoveSplitViewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiRemoveSplitViewL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAppUiSplitViewActiveL test function for testing the 
     * SplitViewActive function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiSplitViewActiveL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAppUiFocusedViewL test function for testing the FocusedView function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiFocusedViewL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAppUiViewShownL test function for testing the ViewShown function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiViewShownL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAppUiEnableLocalScreenClearerL test function for testing the 
     * EnableLocalScreenClearer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiEnableLocalScreenClearerL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAppUiHandleStatusPaneSizeChangeL test function for testing the 
     * HandleStatusPaneSizeChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiHandleStatusPaneSizeChangeL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAppUiHandleForegroundEventL test function for testing the 
     * HandleForegroundEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiHandleForegroundEventL( CStifItemParser& /*aItem*/ );

    /**
     * TestViewAppUiHandleWsEventL test function for testing the HandleWsEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestViewAppUiHandleWsEventL( CStifItemParser& /*aItem*/ );

    /**
     * TestAppUiBaseIsSingleClickCompatible test function for IsSingleClickCompatible function
     * @since S60 5.2
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAppUiBaseIsSingleClickCompatible( CStifItemParser& /*aItem*/ );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    /**
     * EikonEnv Poniter
     * Not own.
     */
    CEikonEnv* iEikonEnvPointer;

    // Resource file offset
    TInt iOffset;

    };

#endif      // C_TESTSDKAPPFW_H

// End of File
