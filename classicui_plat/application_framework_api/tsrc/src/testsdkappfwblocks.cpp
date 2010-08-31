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



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkappfw.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKAppFW::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKAppFW::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::RunMethodL( CStifItemParser& aItem )
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        // for aknApp.h
        ENTRY( "TestAppPreDocConstructL", CTestSDKAppFW::TestAppPreDocConstructL ),
        ENTRY( "TestAppOpenIniFileLC", CTestSDKAppFW::TestAppOpenIniFileLC ),
        ENTRY( "TestAppNewAppServerL", CTestSDKAppFW::TestAppNewAppServerL ),

        // for AknAppUi.h
        ENTRY( "TestAppUiBaseCAknAppUiBaseL", CTestSDKAppFW::TestAppUiBaseCAknAppUiBaseL ),
        ENTRY( "TestAppUiBBaseConstructL", CTestSDKAppFW::TestAppUiBBaseConstructL ),
        ENTRY( "TestAppUiBaseHandleForegroundEventL", CTestSDKAppFW::TestAppUiBaseHandleForegroundEventL ),
        ENTRY( "TestAppUiBConstructL", CTestSDKAppFW::TestAppUiBConstructL ),
        ENTRY( "TestAppUiBaseExitL", CTestSDKAppFW::TestAppUiBaseExitL ),
        ENTRY( "TestAppUiBaseSetFadedL", CTestSDKAppFW::TestAppUiBaseSetFadedL ),
        ENTRY( "TestAppUiBaseHandleResourceChangeL", CTestSDKAppFW::TestAppUiBaseHandleResourceChangeL ),
        ENTRY( "TestAppUiBaseApplicationRect", CTestSDKAppFW::TestAppUiBaseApplicationRect ),
        ENTRY( "TestAppUiBasePrepareToExit", CTestSDKAppFW::TestAppUiBasePrepareToExit ),
        ENTRY( "TestAppUiBaseIsFadedL", CTestSDKAppFW::TestAppUiBaseIsFadedL ),
        ENTRY( "TestAppUiBaseEventMonitor", CTestSDKAppFW::TestAppUiBaseEventMonitor ),
        ENTRY( "TestAppUiBaseKeySounds", CTestSDKAppFW::TestAppUiBaseKeySounds ),
        ENTRY( "TestAppUiBaseIsFullScreenAppL", CTestSDKAppFW::TestAppUiBaseIsFullScreenAppL ),
        ENTRY( "TestAppUiBaseIsLayoutAwareApp", CTestSDKAppFW::TestAppUiBaseIsLayoutAwareApp ),
        ENTRY( "TestAppUiBaseSetLayoutAwareApp", CTestSDKAppFW::TestAppUiBaseSetLayoutAwareApp ),
        ENTRY( "TestAppUiBaseIsForeground", CTestSDKAppFW::TestAppUiBaseIsForeground ),
        ENTRY( "TestAppUiBaseIsPartialForeground", CTestSDKAppFW::TestAppUiBaseIsPartialForeground ),
        ENTRY( "TestAppUiBaseOrientationL", CTestSDKAppFW::TestAppUiBaseOrientationL ),
        ENTRY( "TestAppUiBaseOrientationCanBeChanged", CTestSDKAppFW::TestAppUiBaseOrientationCanBeChanged ),
        ENTRY( "TestAppUiBaseSetOrientationL", CTestSDKAppFW::TestAppUiBaseSetOrientationL ),
        ENTRY( "TestAppUiBaseLocalUiZoom", CTestSDKAppFW::TestAppUiBaseLocalUiZoom ),
        ENTRY( "TestAppUiBaseSetLocalUiZoom", CTestSDKAppFW::TestAppUiBaseSetLocalUiZoom ),
        ENTRY( "TestAppUiBaseApplyLayoutChangeL", CTestSDKAppFW::TestAppUiBaseApplyLayoutChangeL ),
        ENTRY( "TestAppUiBaseSetKeyEventFlags", CTestSDKAppFW::TestAppUiBaseSetKeyEventFlags ),
        ENTRY( "TestAppUiBasePointerEventModifier", CTestSDKAppFW::TestAppUiBasePointerEventModifier ),
        ENTRY( "TestAppUiBaseHandleScreenDeviceChangedL", CTestSDKAppFW::TestAppUiBaseHandleScreenDeviceChangedL ),
        ENTRY( "TestAppUiBaseHandleApplicationSpecificEventL", CTestSDKAppFW::TestAppUiBaseHandleApplicationSpecificEventL ),
        ENTRY( "TestAppUiBaseSetFullScreenAppL", CTestSDKAppFW::TestAppUiBaseSetFullScreenAppL ),
        ENTRY( "TestAppUiBaseReplaceKeySoundsL", CTestSDKAppFW::TestAppUiBaseReplaceKeySoundsL ),
        ENTRY( "TestAppUiBaseMopSupplyObject", CTestSDKAppFW::TestAppUiBaseMopSupplyObject ),
        ENTRY( "TestAppUiBaseConstructL", CTestSDKAppFW::TestAppUiBaseConstructL ),
        ENTRY( "TestAppUiConstructL", CTestSDKAppFW::TestAppUiConstructL ),
        ENTRY( "TestAppUiStatusPaneL", CTestSDKAppFW::TestAppUiStatusPaneL ),
        ENTRY( "TestAppUiCba", CTestSDKAppFW::TestAppUiCba ),
        ENTRY( "TestAppUiTouchPane", CTestSDKAppFW::TestAppUiTouchPane ),
        ENTRY( "TestAppUiPopupToolbar", CTestSDKAppFW::TestAppUiPopupToolbar ),
        ENTRY( "TestAppUiCurrentPopupToolbar", CTestSDKAppFW::TestAppUiCurrentPopupToolbar ),
        ENTRY( "TestAppUiCurrentFixedToolbar", CTestSDKAppFW::TestAppUiCurrentFixedToolbar ),
        ENTRY( "TestAppUiProcessCommandL", CTestSDKAppFW::TestAppUiProcessCommandL ),
        ENTRY( "TestAppUiHandleError", CTestSDKAppFW::TestAppUiHandleError ),
        ENTRY( "TestAppUiRunAppShutterL", CTestSDKAppFW::TestAppUiRunAppShutterL ),
        ENTRY( "TestAppUiIsAppShutterRunning", CTestSDKAppFW::TestAppUiIsAppShutterRunning ),
        ENTRY( "TestAppUiHandleViewDeactivation", CTestSDKAppFW::TestAppUiHandleViewDeactivation ),
        ENTRY( "TestAppUiPrepareToExit", CTestSDKAppFW::TestAppUiPrepareToExit ),
        ENTRY( "TestAppUiHandleTouchPaneSizeChange", CTestSDKAppFW::TestAppUiHandleTouchPaneSizeChange ),
        ENTRY( "TestAppUiHandleStatusPaneSizeChange", CTestSDKAppFW::TestAppUiHandleStatusPaneSizeChange ),
        ENTRY( "TestAppUiHandleSystemEventL", CTestSDKAppFW::TestAppUiHandleSystemEventL ),
        ENTRY( "TestAppUiReserved_MtsmPosition", CTestSDKAppFW::TestAppUiReserved_MtsmPosition ),
        ENTRY( "TestAppUiReserved_MtsmObject", CTestSDKAppFW::TestAppUiReserved_MtsmObject ),
        ENTRY( "TestAppUiHandleForegroundEventL", CTestSDKAppFW::TestAppUiHandleForegroundEventL ),
        ENTRY( "TestAppUiHandleWsEventL", CTestSDKAppFW::TestAppUiHandleWsEventL ),
        ENTRY( "TestAppUiSetKeyBlockMode", CTestSDKAppFW::TestAppUiSetKeyBlockMode ),
        ENTRY( "TestAppUiHandleErrorL", CTestSDKAppFW::TestAppUiHandleErrorL ),
        ENTRY( "TestAppUiHideApplicationFromFSW", CTestSDKAppFW::TestAppUiHideApplicationFromFSW ),
        ENTRY( "TestAppUiGetAliasKeyCodeL", CTestSDKAppFW::TestAppUiGetAliasKeyCodeL ),
        ENTRY( "TestAppUiSetAliasKeyCodeResolverL", CTestSDKAppFW::TestAppUiSetAliasKeyCodeResolverL ),
        ENTRY( "TestAppUiCaptureKey", CTestSDKAppFW::TestAppUiCaptureKey ),
        ENTRY( "TestAppUiCaptureKeyL", CTestSDKAppFW::TestAppUiCaptureKeyL ),
        ENTRY( "TestAppUiExitHidesInBackground", CTestSDKAppFW::TestAppUiExitHidesInBackground ),
        ENTRY( "TestAppUiHideInBackground", CTestSDKAppFW::TestAppUiHideInBackground ),

        // for AknDoc.h
        ENTRY( "TestDocOpenFileL", CTestSDKAppFW::TestDocOpenFileL ),
        ENTRY( "TestDocOpenFileLStoreL", CTestSDKAppFW::TestDocOpenFileLStoreL ),
        ENTRY( "TestDocCAknDocumentL", CTestSDKAppFW::TestDocCAknDocumentL ),

        // for aknview.h
        ENTRY( "TestViewCAknViewL", CTestSDKAppFW::TestViewCAknViewL ),
        ENTRY( "TestViewBaseConstructL", CTestSDKAppFW::TestViewBaseConstructL ),
        ENTRY( "TestViewConstructMenuAndCbaEarlyL", CTestSDKAppFW::TestViewConstructMenuAndCbaEarlyL ),
        ENTRY( "TestViewActivateViewL", CTestSDKAppFW::TestViewActivateViewL ),
        ENTRY( "TestViewActivateViewLCustomL", CTestSDKAppFW::TestViewActivateViewLCustomL ),
        ENTRY( "TestViewIdL", CTestSDKAppFW::TestViewIdL ),
        ENTRY( "TestViewHandleStatusPaneSizeChangeL", CTestSDKAppFW::TestViewHandleStatusPaneSizeChangeL ),
        ENTRY( "TestViewViewIdL", CTestSDKAppFW::TestViewViewIdL ),
        ENTRY( "TestViewProcessCommandL", CTestSDKAppFW::TestViewProcessCommandL ),
        ENTRY( "TestViewHandleCommandL", CTestSDKAppFW::TestViewHandleCommandL ),
        ENTRY( "TestViewMenuBarL", CTestSDKAppFW::TestViewMenuBarL ),
        ENTRY( "TestViewClientRectL", CTestSDKAppFW::TestViewClientRectL ),
        ENTRY( "TestViewStopDisplayingMenuBarL", CTestSDKAppFW::TestViewStopDisplayingMenuBarL ),
        ENTRY( "TestViewIsForegroundL", CTestSDKAppFW::TestViewIsForegroundL ),
        ENTRY( "TestViewHandleViewRectChangeL", CTestSDKAppFW::TestViewHandleViewRectChangeL ),
        ENTRY( "TestViewRedrawL", CTestSDKAppFW::TestViewRedrawL ),
        ENTRY( "TestViewAknViewActivatedL", CTestSDKAppFW::TestViewAknViewActivatedL ),
        ENTRY( "TestViewAppUiL", CTestSDKAppFW::TestViewAppUiL ),
        ENTRY( "TestViewStatusPaneL", CTestSDKAppFW::TestViewStatusPaneL ),
        ENTRY( "TestViewCbaL", CTestSDKAppFW::TestViewCbaL ),
        ENTRY( "TestViewDoActivateL", CTestSDKAppFW::TestViewDoActivateL ),
        ENTRY( "TestViewViewActivatedL", CTestSDKAppFW::TestViewViewActivatedL ),
        ENTRY( "TestViewViewDeactivatedL", CTestSDKAppFW::TestViewViewDeactivatedL ),
        ENTRY( "TestViewViewScreenDeviceChangedL", CTestSDKAppFW::TestViewViewScreenDeviceChangedL ),
        ENTRY( "TestViewMopSupplyObjectL", CTestSDKAppFW::TestViewMopSupplyObjectL ),
        ENTRY( "TestViewMopNextL", CTestSDKAppFW::TestViewMopNextL ),
        ENTRY( "TestViewSetEmphasisL", CTestSDKAppFW::TestViewSetEmphasisL ),
        ENTRY( "TestViewHandleForegroundEventL", CTestSDKAppFW::TestViewHandleForegroundEventL ),
        ENTRY( "TestViewToolbarL", CTestSDKAppFW::TestViewToolbarL ),
        ENTRY( "TestViewStopDisplayingToolbarL", CTestSDKAppFW::TestViewStopDisplayingToolbarL ),
        ENTRY( "TestViewToolbarShownOnViewActivationL", CTestSDKAppFW::TestViewToolbarShownOnViewActivationL ),
        ENTRY( "TestViewShowToolbarOnViewActivationL", CTestSDKAppFW::TestViewShowToolbarOnViewActivationL ),
        ENTRY( "TestViewSetToolbarL", CTestSDKAppFW::TestViewSetToolbarL ),
        ENTRY( "TestViewCreateAndSetToolbarL", CTestSDKAppFW::TestViewCreateAndSetToolbarL ),

        // for aknViewAppUi.h
        ENTRY( "TestViewAppUiBaseConstructL", CTestSDKAppFW::TestViewAppUiBaseConstructL ),
        ENTRY( "TestViewAppUiActivateLocalViewL", CTestSDKAppFW::TestViewAppUiActivateLocalViewL ),
        ENTRY( "TestViewAppUiActivateLocalViewLCustomL", CTestSDKAppFW::TestViewAppUiActivateLocalViewLCustomL ),
        ENTRY( "TestViewAppUiViewL", CTestSDKAppFW::TestViewAppUiViewL ),
        ENTRY( "TestViewAppUiAddViewL", CTestSDKAppFW::TestViewAppUiAddViewL ),
        ENTRY( "TestViewAppUiRemoveViewL", CTestSDKAppFW::TestViewAppUiRemoveViewL ),
        ENTRY( "TestViewAppUiProcessCommandL", CTestSDKAppFW::TestViewAppUiProcessCommandL ),
        ENTRY( "TestViewAppUiStopDisplayingMenuBarL", CTestSDKAppFW::TestViewAppUiStopDisplayingMenuBarL ),
        ENTRY( "TestViewAppUiSetSplitViewL", CTestSDKAppFW::TestViewAppUiSetSplitViewL ),
        ENTRY( "TestViewAppUiRemoveSplitViewL", CTestSDKAppFW::TestViewAppUiRemoveSplitViewL ),
        ENTRY( "TestViewAppUiSplitViewActiveL", CTestSDKAppFW::TestViewAppUiSplitViewActiveL ),
        ENTRY( "TestViewAppUiFocusedViewL", CTestSDKAppFW::TestViewAppUiFocusedViewL ),
        ENTRY( "TestViewAppUiViewShownL", CTestSDKAppFW::TestViewAppUiViewShownL ),
        ENTRY( "TestViewAppUiEnableLocalScreenClearerL", CTestSDKAppFW::TestViewAppUiEnableLocalScreenClearerL ),
        ENTRY( "TestViewAppUiHandleStatusPaneSizeChangeL", CTestSDKAppFW::TestViewAppUiHandleStatusPaneSizeChangeL ),
        ENTRY( "TestViewAppUiHandleForegroundEventL", CTestSDKAppFW::TestViewAppUiHandleForegroundEventL ),
        ENTRY( "TestViewAppUiHandleWsEventL", CTestSDKAppFW::TestViewAppUiHandleWsEventL ),

        ENTRY( "TestAppUiBaseIsSingleClickCompatible", CTestSDKAppFW::TestAppUiBaseIsSingleClickCompatible ),
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

//  [End of File]
