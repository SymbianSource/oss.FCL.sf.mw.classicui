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
* Description:  test functions of in extended_notifiers_api
*
*/



#ifndef C_TESTDOMEXTNOTIFIERS_H
#define C_TESTDOMEXTNOTIFIERS_H

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
_LIT( KtestdomextnotifiersLogPath, "\\logs\\testframework\\testdomextnotifiers\\" ); 
// Log file
_LIT( KtestdomextnotifiersLogFile, "testdomextnotifiers.txt" ); 
_LIT( KtestdomextnotifiersLogFileWithTitle, "testdomextnotifiers_[%S].txt" );

/**
*  Ctestdomextnotifiers test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDomExtNotifiers ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDomExtNotifiers* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDomExtNotifiers();

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
    CTestDomExtNotifiers( CTestModuleIf& aTestModuleIf );

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
    * TestTADSNPTAknDynamicSoftNotificationParamsL tests TAknDynamicSoftNotificationParams
    * of TAknDynamicSoftNotificationParams in AknDynamicSoftNotificationParams.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTADSNPTAknDynamicSoftNotificationParamsL( CStifItemParser& aItem );

    /**
    * TestTADSNPSetViewActivationParams tests SetViewActivationParams
    * of TAknDynamicSoftNotificationParams in AknDynamicSoftNotificationParams.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTADSNPSetViewActivationParams( CStifItemParser& aItem );

    /**
    * TestTADSNPSetSoftkeys tests SetSoftkeys
    * of TAknDynamicSoftNotificationParams in AknDynamicSoftNotificationParams.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTADSNPSetSoftkeys( CStifItemParser& aItem );

    /**
    * TestTADSNPSetNoteLabels tests SetNoteLabels
    * of TAknDynamicSoftNotificationParams in AknDynamicSoftNotificationParams.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTADSNPSetNoteLabels( CStifItemParser& aItem );

    /**
    * TestTADSNPSetGroupLabels tests SetGroupLabels
    * of TAknDynamicSoftNotificationParams in AknDynamicSoftNotificationParams.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTADSNPSetGroupLabels( CStifItemParser& aItem );

    /**
    * TestTADSNPSetImageData tests SetImageData
    * of TAknDynamicSoftNotificationParams in AknDynamicSoftNotificationParams.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTADSNPSetImageData( CStifItemParser& aItem );

    /**
    * TestTADSNPEnableObserver tests EnableObserver
    * of TAknDynamicSoftNotificationParams in AknDynamicSoftNotificationParams.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTADSNPEnableObserver( CStifItemParser& aItem );

    /**
    * TestCADSNNewL tests NewL
    * of CAknDynamicSoftNotifier in AknDynamicSoftNotifier.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCADSNNewL( CStifItemParser& aItem );

    /**
    * TestCADSNNewLCL tests NewLC
    * of CAknDynamicSoftNotifier in AknDynamicSoftNotifier.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCADSNNewLCL( CStifItemParser& aItem );

    /**
    * TestCADSNAddDynamicNotificationL tests AddDynamicNotificationL
    * of CAknDynamicSoftNotifier in AknDynamicSoftNotifier.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCADSNAddDynamicNotificationL( CStifItemParser& aItem );

    /**
    * TestCADSNSetDynamicNotificationCountL tests SetDynamicNotificationCountL
    * of CAknDynamicSoftNotifier in AknDynamicSoftNotifier.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCADSNSetDynamicNotificationCountL( CStifItemParser& aItem );

    /**
    * TestCADSNCancelDynamicNotificationL tests CancelDynamicNotificationL
    * of CAknDynamicSoftNotifier in AknDynamicSoftNotifier.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCADSNCancelDynamicNotificationL( CStifItemParser& aItem );

    /**
    * TestCADSNStartObservingL tests StartObservingL
    * of CAknDynamicSoftNotifier in AknDynamicSoftNotifier.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCADSNStartObservingL( CStifItemParser& aItem );

    /**
    * TestCADSNStopObservingL tests StopObserving
    * of CAknDynamicSoftNotifier in AknDynamicSoftNotifier.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCADSNStopObservingL( CStifItemParser& aItem );

    /**
    * TestCADSNSetSecondaryDisplayDataL tests SetSecondaryDisplayData
    * of CAknDynamicSoftNotifier in AknDynamicSoftNotifier.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCADSNSetSecondaryDisplayDataL( CStifItemParser& aItem );

    /**
    * TestCAIBNewL tests NewL
    * of CAknIncallBubble in AknIncallBubbleNotify.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAIBNewL( CStifItemParser& aItem );

    /**
    * TestCAIBNewLCL tests NewLC
    * of CAknIncallBubble in AknIncallBubbleNotify.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAIBNewLCL( CStifItemParser& aItem );

    /**
    * TestCAIBSetIncallBubbleFlagsL tests SetIncallBubbleFlagsL
    * of CAknIncallBubble in AknIncallBubbleNotify.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAIBSetIncallBubbleFlagsL( CStifItemParser& aItem );

    /**
    * TestCAIBSetIncallBubbleAllowedInIdleL tests SetIncallBubbleAllowedInIdleL
    * of CAknIncallBubble in AknIncallBubbleNotify.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAIBSetIncallBubbleAllowedInIdleL( CStifItemParser& aItem );

    /**
    * TestCAIBSetIncallBubbleAllowedInUsualL tests SetIncallBubbleAllowedInUsualL
    * of CAknIncallBubble in AknIncallBubbleNotify.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAIBSetIncallBubbleAllowedInUsualL( CStifItemParser& aItem );

    /**
    * TestCANASACAknNotifierAppServerApplicationL tests CAknNotifierAppServerApplication
    * of CAknNotifierAppServerApplication in AknNotiferAppServerApplication.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASACAknNotifierAppServerApplicationL( CStifItemParser& aItem );

    /**
    * TestCANASANewAppServerL tests NewAppServerL
    * of CAknNotifierAppServerApplication in AknNotiferAppServerApplication.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASANewAppServerL( CStifItemParser& aItem );

    /**
    * TestCANASACreateDocumentL tests CreateDocumentL
    * of CAknNotifierAppServerApplication in AknNotiferAppServerApplication.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASACreateDocumentL( CStifItemParser& aItem );

    /**
    * TestCANASAUiCAknNotifierAppServerAppUiL tests CAknNotifierAppServerAppUi
    * of CAknNotifierAppServerAppUi in AknNotiferAppServerApplication.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASAUiCAknNotifierAppServerAppUiL( CStifItemParser& aItem );

    /**
    * TestCANASAUiConstructL tests ConstructL
    * of CAknNotifierAppServerAppUi in AknNotiferAppServerApplication.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASAUiConstructL( CStifItemParser& aItem );

    /**
    * TestCANASAUiHandleCommandL tests HandleCommandL
    * of CAknNotifierAppServerAppUi in AknNotiferAppServerApplication.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASAUiHandleCommandL( CStifItemParser& aItem );

    /**
    * TestCANASAUiHandleKeyEventL tests HandleKeyEventL
    * of CAknNotifierAppServerAppUi in AknNotiferAppServerApplication.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASAUiHandleKeyEventL( CStifItemParser& aItem );

    /**
    * TestCANASAUiSetFadedL tests SetFadedL
    * of CAknNotifierAppServerAppUi in AknNotiferAppServerApplication.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASAUiSetFadedL( CStifItemParser& aItem );

    /**
    * TestCANASAUiHandleErrorL tests HandleError
    * of CAknNotifierAppServerAppUi in AknNotiferAppServerApplication.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASAUiHandleErrorL( CStifItemParser& aItem );

    /**
    * TestCANASAUiHandleSystemEventL tests HandleSystemEventL
    * of CAknNotifierAppServerAppUi in AknNotiferAppServerApplication.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASAUiHandleSystemEventL( CStifItemParser& aItem );

    /**
    * TestCANASAUiSuppressAppSwitchingL tests SuppressAppSwitching
    * of CAknNotifierAppServerAppUi in AknNotiferAppServerApplication.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASAUiSuppressAppSwitchingL( CStifItemParser& aItem );

    /**
    * TestCANASAUiSetManagerL tests SetManager
    * of CAknNotifierAppServerAppUi in AknNotiferAppServerApplication.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASAUiSetManagerL( CStifItemParser& aItem );

    /**
    * TestCANASAUiManagerL tests Manager
    * of CAknNotifierAppServerAppUi in AknNotiferAppServerApplication.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASAUiManagerL( CStifItemParser& aItem );

    /**
    * TestCANASAUiEikSrvBlockedL tests EikSrvBlocked
    * of CAknNotifierAppServerAppUi in AknNotiferAppServerApplication.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASAUiEikSrvBlockedL( CStifItemParser& aItem );

    /**
    * TestCANASAUiSetOrdinalPositionL tests SetOrdinalPositionL
    * of CAknNotifierAppServerAppUi in AknNotiferAppServerApplication.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASAUiSetOrdinalPositionL( CStifItemParser& aItem );

    /**
    * TestCANASCAknNotifierAppServerL tests CAknNotifierAppServer
    * of CAknNotifierAppServer in AknNotifierAppServer.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASCAknNotifierAppServerL( CStifItemParser& aItem );

    /**
    * TestCANASStartNotifierL tests StartNotifierL
    * of CAknNotifierAppServer in AknNotifierAppServer.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASStartNotifierL( CStifItemParser& aItem );

    /**
    * TestCANASCancelNotifierL tests CancelNotifier
    * of CAknNotifierAppServer in AknNotifierAppServer.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASCancelNotifierL( CStifItemParser& aItem );

    /**
    * TestCANASUpdateNotifierL tests UpdateNotifierL
    * of CAknNotifierAppServer in AknNotifierAppServer.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASUpdateNotifierL( CStifItemParser& aItem );

    /**
    * TestCANASStartNotifierAndGetResponseL tests StartNotifierAndGetResponseL
    * of CAknNotifierAppServer in AknNotifierAppServer.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASStartNotifierAndGetResponseL( CStifItemParser& aItem );

    /**
    * TestCANASAppendNotifierLibNameL tests AppendNotifierLibNameL
    * of CAknNotifierAppServer in AknNotifierAppServer.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASAppendNotifierLibNameL( CStifItemParser& aItem );

    /**
    * TestCANASLoadNotifiersL tests LoadNotifiersL
    * of CAknNotifierAppServer in AknNotifierAppServer.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASLoadNotifiersL( CStifItemParser& aItem );

    /**
    * TestCANASCreateServiceL tests CreateServiceL
    * of CAknNotifierAppServer in AknNotifierAppServer.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASCreateServiceL( CStifItemParser& aItem );

    /**
    * TestCANASSetImplementationFinderL tests SetImplementationFinderL
    * of CAknNotifierAppServer in AknNotifierAppServer.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASSetImplementationFinderL( CStifItemParser& aItem );

    /**
    * TestCANASUnbalanceReferenceCountForNotifL tests UnbalanceReferenceCountForNotif
    * of CAknNotifierAppServer in AknNotifierAppServer.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASUnbalanceReferenceCountForNotifL( CStifItemParser& aItem );

    /**
    * TestCANASUpdateNotifierAndGetResponseL tests UpdateNotifierAndGetResponseL
    * of CAknNotifierAppServer in AknNotifierAppServer.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANASUpdateNotifierAndGetResponseL( CStifItemParser& aItem );

    /**
    * TestCANSASCAknNotifierServerAppServiceL tests CAknNotifierServerAppService
    * of CAknNotifierServerAppService in AknNotifierAppServerSession.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANSASCAknNotifierServerAppServiceL( CStifItemParser& aItem );

    /**
    * TestCANSASServiceL tests ServiceL
    * of CAknNotifierServerAppService in AknNotifierAppServerSession.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANSASServiceL( CStifItemParser& aItem );

    /**
    * TestCANSASAllowClientL tests AllowClientL
    * of CAknNotifierServerAppService in AknNotifierAppServerSession.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANSASAllowClientL( CStifItemParser& aItem );

    /**
    * TestCANSASHandleMessageL tests HandleMessageL
    * of CAknNotifierServerAppService in AknNotifierAppServerSession.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANSASHandleMessageL( CStifItemParser& aItem );

    /**
    * TestANCtlHideAllNotifications tests HideAllNotifications
    * of AknNotifierController in aknnotifiercontroller.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestANCtlHideAllNotifications( CStifItemParser& aItem );

    /**
    * TestANCtlCancelAllNotifications tests HideAllNotifications
    * of AknNotifierController in aknnotifiercontroller.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestANCtlCancelAllNotifications( CStifItemParser& aItem );

    /**
    * TestCANCUDoAllowNotificationsL tests DoAllowNotifications
    * of CAknNotifierControllerUtility in AknNotifierControllerUtilities.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANCUDoAllowNotificationsL( CStifItemParser& aItem );

    /**
    * TestCANCUDoStopNotificationsL tests DoStopNotifications
    * of CAknNotifierControllerUtility in AknNotifierControllerUtilities.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANCUDoStopNotificationsL( CStifItemParser& aItem );

    /**
    * TestCANCUDoCancelAllNotificatonsL tests DoCancelAllNotificatonsL
    * of CAknNotifierControllerUtility in AknNotifierControllerUtilities.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANCUDoCancelAllNotificatonsL( CStifItemParser& aItem );

    /**
    * TestMANWUpdateNotifierL tests UpdateNotifierL
    * of MAknNotifierWrapper in AknNotifierWrapper.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMANWUpdateNotifierL( CStifItemParser& aItem );

    /**
    * TestCANMONewServerRequestL tests NewServerRequestL
    * of CAknNotifierMessageObserver in AknNotifierWrapper.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANMONewServerRequestL( CStifItemParser& aItem );

    /**
    * TestCANWLCAknNotifierWrapperLightL tests CAknNotifierWrapperLight
    * of CAknNotifierWrapperLight in AknNotifierWrapper.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANWLCAknNotifierWrapperLightL( CStifItemParser& aItem );

    /**
    * TestCANWLUpdateWithRetL tests UpdateL
    * of CAknNotifierWrapperLight in AknNotifierWrapper.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANWLMostFunction1L( CStifItemParser& aItem );

    /**
    * TestCANWLCancelL tests Cancel
    * of CAknNotifierWrapperLight in AknNotifierWrapper.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANWLMostFunction2L( CStifItemParser& aItem );

    /**
    * TestCANWLStartL tests StartL
    * of CAknNotifierWrapperLight in AknNotifierWrapper.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANWLMostFunction3L( CStifItemParser& aItem );

    /**
    * TestCANWLStartWithBufferL tests StartL
    * of CAknNotifierWrapperLight in AknNotifierWrapper.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANWLStartWithRetL( CStifItemParser& aItem );

    /**
    * TestCANWLInfoL tests Info
    * of CAknNotifierWrapperLight in AknNotifierWrapper.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANWLInfoL( CStifItemParser& aItem );

    /**
    * TestCANWStartNotifierWithRetL tests StartNotifierL
    * of CAknNotifierWrapper in AknNotifierWrapper.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCANWStartNotifierWithRetL( CStifItemParser& aItem );

    /**
    * TestCASINewL tests NewL
    * of CAknSmallIndicator in AknSmallIndicator.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASINewL( CStifItemParser& aItem );

    /**
    * TestCASINewLCL tests NewLC
    * of CAknSmallIndicator in AknSmallIndicator.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASINewLCL( CStifItemParser& aItem );

    /**
    * TestCASISetIndicatorStateL tests SetIndicatorStateL
    * of CAknSmallIndicator in AknSmallIndicator.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASISetIndicatorStateL( CStifItemParser& aItem );

    /**
    * TestCASIHandleIndicatorTapL tests HandleIndicatorTapL
    * of CAknSmallIndicator in AknSmallIndicator.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASIHandleIndicatorTapL( CStifItemParser& aItem );

    /**
    * TestCASNPNewL tests NewL
    * of CAknSoftNotificationParameters in aknSoftNotificationParameters.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASNPNewL( CStifItemParser& aItem );

    /**
    * TestCASNPNewWith5ParamL tests NewL
    * of CAknSoftNotificationParameters in aknSoftNotificationParameters.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASNPNewWith5ParamL( CStifItemParser& aItem );

    /**
    * TestCASNPNewWith9ParamL tests NewL
    * of CAknSoftNotificationParameters in aknSoftNotificationParameters.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASNPNewWith9ParamL( CStifItemParser& aItem );

    /**
    * TestCASNPSetGroupedTextsL tests SetGroupedTexts
    * of CAknSoftNotificationParameters in aknSoftNotificationParameters.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASNPSetGroupedTextsL( CStifItemParser& aItem );

    /**
    * TestCASNPSetPluralViewIdL tests SetPluralViewId
    * of CAknSoftNotificationParameters in aknSoftNotificationParameters.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASNPSetPluralViewIdL( CStifItemParser& aItem );

    /**
    * TestCASNNewL tests NewL
    * of CAknSoftNotifier in AknSoftNotifier.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASNNewL( CStifItemParser& aItem );

    /**
    * TestCASNNewLCL tests NewLC
    * of CAknSoftNotifier in AknSoftNotifier.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASNNewLCL( CStifItemParser& aItem );

    /**
    * TestCASNAddNotificationL tests AddNotificationL
    * of CAknSoftNotifier in AknSoftNotifier.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASNAddNotificationL( CStifItemParser& aItem );

    /**
    * TestCASNAddNotificationWithCountL tests AddNotificationL
    * of CAknSoftNotifier in AknSoftNotifier.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASNAddNotificationWithCountL( CStifItemParser& aItem );

    /**
    * TestCASNSetNotificationCountL tests SetNotificationCountL
    * of CAknSoftNotifier in AknSoftNotifier.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASNSetNotificationCountL( CStifItemParser& aItem );

    /**
    * TestCASNCancelSoftNotificationL tests CancelSoftNotificationL
    * of CAknSoftNotifier in AknSoftNotifier.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASNCancelSoftNotificationL( CStifItemParser& aItem );

    /**
    * TestCASNAddCustomNotificationL tests AddCustomNotificationL
    * of CAknSoftNotifier in AknSoftNotifier.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASNAddCustomNotificationL( CStifItemParser& aItem );

    /**
    * TestCASNSetCustomNotificationCountL tests SetCustomNotificationCountL
    * of CAknSoftNotifier in AknSoftNotifier.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASNSetCustomNotificationCountL( CStifItemParser& aItem );

    /**
    * TestCASNCancelCustomSoftNotificationL tests CancelCustomSoftNotificationL
    * of CAknSoftNotifier in AknSoftNotifier.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCASNCancelCustomSoftNotificationL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    };

#endif      // C_TESTDOMEXTNOTIFIERS_H

// End of File
