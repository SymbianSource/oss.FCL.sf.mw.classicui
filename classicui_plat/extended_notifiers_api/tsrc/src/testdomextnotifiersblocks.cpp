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
* Description:  test function implements of CTestDomExtNotifiers
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testdomextnotifiers.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function.

        // For TAknDynamicSoftNotificationParams in AknDynamicSoftNotificationParams.h
        ENTRY( "TestTADSNPTAknDynamicSoftNotificationParamsL",
                CTestDomExtNotifiers::TestTADSNPTAknDynamicSoftNotificationParamsL ),
        ENTRY( "TestTADSNPSetViewActivationParams",
                CTestDomExtNotifiers::TestTADSNPSetViewActivationParams ),
        ENTRY( "TestTADSNPSetSoftkeys",
                CTestDomExtNotifiers::TestTADSNPSetSoftkeys ),
        ENTRY( "TestTADSNPSetNoteLabels",
                CTestDomExtNotifiers::TestTADSNPSetNoteLabels ),
        ENTRY( "TestTADSNPSetGroupLabels",
                CTestDomExtNotifiers::TestTADSNPSetGroupLabels ),
        ENTRY( "TestTADSNPSetImageData",
                CTestDomExtNotifiers::TestTADSNPSetImageData ),
        ENTRY( "TestTADSNPEnableObserver",
                CTestDomExtNotifiers::TestTADSNPEnableObserver ),

        // For CAknDynamicSoftNotifier in AknDynamicSoftNotifier.h
        ENTRY( "TestCADSNNewL",
                CTestDomExtNotifiers::TestCADSNNewL ),
        ENTRY( "TestCADSNNewLCL",
                CTestDomExtNotifiers::TestCADSNNewLCL ),
        ENTRY( "TestCADSNAddDynamicNotificationL",
                CTestDomExtNotifiers::TestCADSNAddDynamicNotificationL ),
        ENTRY( "TestCADSNSetDynamicNotificationCountL",
                CTestDomExtNotifiers::TestCADSNSetDynamicNotificationCountL ),
        ENTRY( "TestCADSNCancelDynamicNotificationL",
                CTestDomExtNotifiers::TestCADSNCancelDynamicNotificationL ),
        ENTRY( "TestCADSNStartObservingL",
                CTestDomExtNotifiers::TestCADSNStartObservingL ),
        ENTRY( "TestCADSNStopObservingL",
                CTestDomExtNotifiers::TestCADSNStopObservingL ),
        ENTRY( "TestCADSNSetSecondaryDisplayDataL",
                CTestDomExtNotifiers::TestCADSNSetSecondaryDisplayDataL ),

        // For CAknIncallBubble in AknIncallBubbleNotify.h
        ENTRY( "TestCAIBNewL",
                CTestDomExtNotifiers::TestCAIBNewL ),
        ENTRY( "TestCAIBNewLCL",
                CTestDomExtNotifiers::TestCAIBNewLCL ),
        ENTRY( "TestCAIBSetIncallBubbleFlagsL",
                CTestDomExtNotifiers::TestCAIBSetIncallBubbleFlagsL ),
        ENTRY( "TestCAIBSetIncallBubbleAllowedInIdleL",
                CTestDomExtNotifiers::TestCAIBSetIncallBubbleAllowedInIdleL ),
        ENTRY( "TestCAIBSetIncallBubbleAllowedInUsualL",
                CTestDomExtNotifiers::TestCAIBSetIncallBubbleAllowedInUsualL ),

        // For CAknNotifierAppServerApplication in AknNotiferAppServerApplication.h
        ENTRY( "TestCANASACAknNotifierAppServerApplicationL",
                CTestDomExtNotifiers::TestCANASACAknNotifierAppServerApplicationL ),
        ENTRY( "TestCANASANewAppServerL",
                CTestDomExtNotifiers::TestCANASANewAppServerL ),
        ENTRY( "TestCANASACreateDocumentL",
                CTestDomExtNotifiers::TestCANASACreateDocumentL ),

        // For CAknNotifierAppServerAppUi in AknNotiferAppServerApplication.h
        ENTRY( "TestCANASAUiCAknNotifierAppServerAppUiL",
                CTestDomExtNotifiers::TestCANASAUiCAknNotifierAppServerAppUiL ),
        ENTRY( "TestCANASAUiConstructL",
                CTestDomExtNotifiers::TestCANASAUiConstructL ),
        ENTRY( "TestCANASAUiHandleCommandL",
                CTestDomExtNotifiers::TestCANASAUiHandleCommandL ),
        ENTRY( "TestCANASAUiHandleKeyEventL",
                CTestDomExtNotifiers::TestCANASAUiHandleKeyEventL ),
        ENTRY( "TestCANASAUiSetFadedL",
                CTestDomExtNotifiers::TestCANASAUiSetFadedL ),
        ENTRY( "TestCANASAUiHandleErrorL",
                CTestDomExtNotifiers::TestCANASAUiHandleErrorL ),
        ENTRY( "TestCANASAUiHandleSystemEventL",
                CTestDomExtNotifiers::TestCANASAUiHandleSystemEventL ),
        ENTRY( "TestCANASAUiSuppressAppSwitchingL",
                CTestDomExtNotifiers::TestCANASAUiSuppressAppSwitchingL ),
        ENTRY( "TestCANASAUiSetManagerL",
                CTestDomExtNotifiers::TestCANASAUiSetManagerL ),
        ENTRY( "TestCANASAUiManagerL",
                CTestDomExtNotifiers::TestCANASAUiManagerL ),
        ENTRY( "TestCANASAUiEikSrvBlockedL",
                CTestDomExtNotifiers::TestCANASAUiEikSrvBlockedL ),
        ENTRY( "TestCANASAUiSetOrdinalPositionL",
                CTestDomExtNotifiers::TestCANASAUiSetOrdinalPositionL ),

        // For CAknNotifierAppServer in AknNotifierAppServer.h
        ENTRY( "TestCANASCAknNotifierAppServerL",
                CTestDomExtNotifiers::TestCANASCAknNotifierAppServerL ),
        ENTRY( "TestCANASStartNotifierL",
                CTestDomExtNotifiers::TestCANASStartNotifierL ),
        ENTRY( "TestCANASCancelNotifierL",
                CTestDomExtNotifiers::TestCANASCancelNotifierL ),
        ENTRY( "TestCANASUpdateNotifierL",
                CTestDomExtNotifiers::TestCANASUpdateNotifierL ),
        ENTRY( "TestCANASStartNotifierAndGetResponseL",
                CTestDomExtNotifiers::TestCANASStartNotifierAndGetResponseL ),
        ENTRY( "TestCANASAppendNotifierLibNameL",
                CTestDomExtNotifiers::TestCANASAppendNotifierLibNameL ),
        ENTRY( "TestCANASLoadNotifiersL",
                CTestDomExtNotifiers::TestCANASLoadNotifiersL ),
        ENTRY( "TestCANASCreateServiceL",
                CTestDomExtNotifiers::TestCANASCreateServiceL ),
        ENTRY( "TestCANASSetImplementationFinderL",
                CTestDomExtNotifiers::TestCANASSetImplementationFinderL ),
        ENTRY( "TestCANASUnbalanceReferenceCountForNotifL",
                CTestDomExtNotifiers::TestCANASUnbalanceReferenceCountForNotifL ),
        ENTRY( "TestCANASUpdateNotifierAndGetResponseL",
                CTestDomExtNotifiers::TestCANASUpdateNotifierAndGetResponseL ),

        // For CAknNotifierServerAppService in AknNotifierAppServerSession.h
        ENTRY( "TestCANSASCAknNotifierServerAppServiceL",
                CTestDomExtNotifiers::TestCANSASCAknNotifierServerAppServiceL ),
        ENTRY( "TestCANSASServiceL",
                CTestDomExtNotifiers::TestCANSASServiceL ),
        ENTRY( "TestCANSASAllowClientL",
                CTestDomExtNotifiers::TestCANSASAllowClientL ),
        ENTRY( "TestCANSASHandleMessageL",
                CTestDomExtNotifiers::TestCANSASHandleMessageL ),

        // For AknNotifierController in aknnotifiercontroller.h
        ENTRY( "TestANCtlHideAllNotifications",
                CTestDomExtNotifiers::TestANCtlHideAllNotifications ),
        ENTRY( "TestANCtlCancelAllNotifications",
                CTestDomExtNotifiers::TestANCtlCancelAllNotifications ),

        // For CAknNotifierControllerUtility in AknNotifierControllerUtilities.h
        ENTRY( "TestCANCUDoAllowNotificationsL",
                CTestDomExtNotifiers::TestCANCUDoAllowNotificationsL ),
        ENTRY( "TestCANCUDoStopNotificationsL",
                CTestDomExtNotifiers::TestCANCUDoStopNotificationsL ),
        ENTRY( "TestCANCUDoCancelAllNotificatonsL",
                CTestDomExtNotifiers::TestCANCUDoCancelAllNotificatonsL ),

        // For MAknNotifierWrapper in AknNotifierWrapper.h
        ENTRY( "TestMANWUpdateNotifierL",
                CTestDomExtNotifiers::TestMANWUpdateNotifierL ),

        // For CAknNotifierMessageObserver in AknNotifierWrapper.h
        ENTRY( "TestCANMONewServerRequestL",
                CTestDomExtNotifiers::TestCANMONewServerRequestL ),

        // For CAknNotifierWrapperLight in AknNotifierWrapper.h
        ENTRY( "TestCANWLCAknNotifierWrapperLightL",
                CTestDomExtNotifiers::TestCANWLCAknNotifierWrapperLightL ),
        ENTRY( "TestCANWLMostFunction1L",
                CTestDomExtNotifiers::TestCANWLMostFunction1L ),
        ENTRY( "TestCANWLMostFunction2L",
                CTestDomExtNotifiers::TestCANWLMostFunction2L ),
        ENTRY( "TestCANWLMostFunction3L",
                CTestDomExtNotifiers::TestCANWLMostFunction3L ),
        ENTRY( "TestCANWLStartWithRetL",
                CTestDomExtNotifiers::TestCANWLStartWithRetL ),
        ENTRY( "TestCANWLInfoL",
                CTestDomExtNotifiers::TestCANWLInfoL ),
        ENTRY( "TestCANWStartNotifierWithRetL", 
                CTestDomExtNotifiers::TestCANWStartNotifierWithRetL ),

        // For CAknSmallIndicator in AknSmallIndicator.h
        ENTRY( "TestCASINewL",
                CTestDomExtNotifiers::TestCASINewL ),
        ENTRY( "TestCASINewLCL",
                CTestDomExtNotifiers::TestCASINewLCL ),
        ENTRY( "TestCASISetIndicatorStateL",
                CTestDomExtNotifiers::TestCASISetIndicatorStateL ),
        ENTRY( "TestCASIHandleIndicatorTapL",
                CTestDomExtNotifiers::TestCASIHandleIndicatorTapL ),

        // For CAknSoftNotificationParameters in aknSoftNotificationParameters.h
        ENTRY( "TestCASNPNewL",
                CTestDomExtNotifiers::TestCASNPNewL ),
        ENTRY( "TestCASNPNewWith5ParamL",
                CTestDomExtNotifiers::TestCASNPNewWith5ParamL ),
        ENTRY( "TestCASNPNewWith9ParamL",
                CTestDomExtNotifiers::TestCASNPNewWith9ParamL ),
        ENTRY( "TestCASNPSetGroupedTextsL",
                CTestDomExtNotifiers::TestCASNPSetGroupedTextsL ),
        ENTRY( "TestCASNPSetPluralViewIdL",
                CTestDomExtNotifiers::TestCASNPSetPluralViewIdL ),

        // For CAknSoftNotifier in AknSoftNotifier.h
        ENTRY( "TestCASNNewL",
                CTestDomExtNotifiers::TestCASNNewL ),
        ENTRY( "TestCASNNewLCL",
                CTestDomExtNotifiers::TestCASNNewLCL ),
        ENTRY( "TestCASNAddNotificationL",
                CTestDomExtNotifiers::TestCASNAddNotificationL ),
        ENTRY( "TestCASNAddNotificationWithCountL",
                CTestDomExtNotifiers::TestCASNAddNotificationWithCountL ),
        ENTRY( "TestCASNSetNotificationCountL",
                CTestDomExtNotifiers::TestCASNSetNotificationCountL ),
        ENTRY( "TestCASNCancelSoftNotificationL",
                CTestDomExtNotifiers::TestCASNCancelSoftNotificationL ),
        ENTRY( "TestCASNAddCustomNotificationL",
                CTestDomExtNotifiers::TestCASNAddCustomNotificationL ),
        ENTRY( "TestCASNSetCustomNotificationCountL",
                CTestDomExtNotifiers::TestCASNSetCustomNotificationCountL ),
        ENTRY( "TestCASNCancelCustomSoftNotificationL",
                CTestDomExtNotifiers::TestCASNCancelCustomSoftNotificationL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


//  [End of File]
