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
* Description:  Implement of functions
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkuifwutil.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestAknBidiTextUtilsConvertToVisualAndClipL", CTestSDKUiFwUtil::TestAknBidiTextUtilsConvertToVisualAndClipL ),
        ENTRY( "TestAknBidiTextUtilsPrepareRunInfoArray", CTestSDKUiFwUtil::TestAknBidiTextUtilsPrepareRunInfoArray ),
        ENTRY( "TestAknBidiTextUtilsConvertToVisualAndWrapToArrayL", CTestSDKUiFwUtil::TestAknBidiTextUtilsConvertToVisualAndWrapToArrayL ),
        ENTRY( "TestAknBidiTextUtilsConvertToVisualAndChopToArrayL", CTestSDKUiFwUtil::TestAknBidiTextUtilsConvertToVisualAndChopToArrayL ),
        ENTRY( "TestAknBidiTextUtilsConvertToVisualAndWrapToStringL", CTestSDKUiFwUtil::TestAknBidiTextUtilsConvertToVisualAndWrapToStringL ),
        ENTRY( "TestAknBidiTextUtilsConvertToVisualAndWrapToArrayWholeTextL", CTestSDKUiFwUtil::TestAknBidiTextUtilsConvertToVisualAndWrapToArrayWholeTextL ),
        ENTRY( "TestAknBidiTextUtilsMeasureTextBoundsWidth", CTestSDKUiFwUtil::TestAknBidiTextUtilsMeasureTextBoundsWidth ),
        ENTRY( "TestAknEnvStatic", CTestSDKUiFwUtil::TestAknEnvStatic ),
        ENTRY( "TestAknEnvExecuteEmptyPopupListL", CTestSDKUiFwUtil::TestAknEnvExecuteEmptyPopupListL ),
        ENTRY( "TestAknEnvSetAndGetObserverL", CTestSDKUiFwUtil::TestAknEnvSetAndGetObserverL ),
        ENTRY( "TestAknEnvEditingStateIndicator", CTestSDKUiFwUtil::TestAknEnvEditingStateIndicator ),
        ENTRY( "TestAknEnvSwapEditingStateIndicatorL", CTestSDKUiFwUtil::TestAknEnvSwapEditingStateIndicatorL ),
        ENTRY( "TestAknEnvExitForegroundAppL", CTestSDKUiFwUtil::TestAknEnvExitForegroundAppL ),
        ENTRY( "TestAknEnvRegisterIntermediateStateL", CTestSDKUiFwUtil::TestAknEnvRegisterIntermediateStateL ),
        ENTRY( "TestAknEnvUnRegisterIntermediateStateL", CTestSDKUiFwUtil::TestAknEnvUnRegisterIntermediateStateL ),
        ENTRY( "TestAknEnvCloseAllIntermediateStates", CTestSDKUiFwUtil::TestAknEnvCloseAllIntermediateStates ),
        ENTRY( "TestAknEnvRunAppShutterL", CTestSDKUiFwUtil::TestAknEnvRunAppShutterL ),
        ENTRY( "TestAknEnvAppWithShutterRunningL", CTestSDKUiFwUtil::TestAknEnvAppWithShutterRunningL ),
        ENTRY( "TestAknEnvStopSchedulerWaitWithBusyMessage", CTestSDKUiFwUtil::TestAknEnvStopSchedulerWaitWithBusyMessage ),
        ENTRY( "TestAknEnvProcessObserverL", CTestSDKUiFwUtil::TestAknEnvProcessObserverL ),
        ENTRY( "TestAknEnvProcessCommandMediationL", CTestSDKUiFwUtil::TestAknEnvProcessCommandMediationL ),
        ENTRY( "TestAknEnvGetCurrentLayoutId", CTestSDKUiFwUtil::TestAknEnvGetCurrentLayoutId ),
        ENTRY( "TestAknEnvGetCurrentGlobalUiZoom", CTestSDKUiFwUtil::TestAknEnvGetCurrentGlobalUiZoom ),
        ENTRY( "TestAknEnvStatusPaneResIdForCurrentLayout", CTestSDKUiFwUtil::TestAknEnvStatusPaneResIdForCurrentLayout ),
        ENTRY( "TestAknEnvRequestWsBuffer", CTestSDKUiFwUtil::TestAknEnvRequestWsBuffer ),
        ENTRY( "TestAknEnvSettingCache", CTestSDKUiFwUtil::TestAknEnvSettingCache ),
        ENTRY( "TestAknEnvLoadAknLayoutL", CTestSDKUiFwUtil::TestAknEnvLoadAknLayoutL ),
        ENTRY( "TestAknEnvAvkonColor", CTestSDKUiFwUtil::TestAknEnvAvkonColor ),
        ENTRY( "TestAknEnvSplitViewActive", CTestSDKUiFwUtil::TestAknEnvSplitViewActive ),
        ENTRY( "TestAknEnvTransparencyEnabled", CTestSDKUiFwUtil::TestAknEnvTransparencyEnabled ),
        ENTRY( "TestCAknIconArrayConstructorL", CTestSDKUiFwUtil::TestCAknIconArrayConstructorL ),
        ENTRY( "TestCAknIconArrayConstructFromResourceL", CTestSDKUiFwUtil::TestCAknIconArrayConstructFromResourceL ),
        ENTRY( "TestCAknIconArrayAppendFromResourceL", CTestSDKUiFwUtil::TestCAknIconArrayAppendFromResourceL ),
        ENTRY( "TestAknTextUtilsClipToFitL", CTestSDKUiFwUtil::TestAknTextUtilsClipToFitL ),
        ENTRY( "TestAknTextUtilsWrapToArrayL", CTestSDKUiFwUtil::TestAknTextUtilsWrapToArrayL ),
        ENTRY( "TestAknTextUtilsWrapToArrayAndClipL", CTestSDKUiFwUtil::TestAknTextUtilsWrapToArrayAndClipL ),
        ENTRY( "TestAknTextUtilsChopToArrayAndClipL", CTestSDKUiFwUtil::TestAknTextUtilsChopToArrayAndClipL ),
        ENTRY( "TestAknTextUtilsWrapToStringL", CTestSDKUiFwUtil::TestAknTextUtilsWrapToStringL ),
        ENTRY( "TestAknTextUtilsWrapToStringAndClipL", CTestSDKUiFwUtil::TestAknTextUtilsWrapToStringAndClipL ),
        ENTRY( "TestAknTextUtilsProcessCharacters", CTestSDKUiFwUtil::TestAknTextUtilsProcessCharacters ),
        ENTRY( "TestAknTextUtilsLanguageSpecificNumberConversion", CTestSDKUiFwUtil::TestAknTextUtilsLanguageSpecificNumberConversion ),
        ENTRY( "TestAknTextUtilsConvertDigitsTo", CTestSDKUiFwUtil::TestAknTextUtilsConvertDigitsTo ),
        ENTRY( "TestAknTextUtilsCurrentScriptDirectionality", CTestSDKUiFwUtil::TestAknTextUtilsCurrentScriptDirectionality ),
        ENTRY( "TestAknTextUtilsNumericEditorDigitType", CTestSDKUiFwUtil::TestAknTextUtilsNumericEditorDigitType ),
        ENTRY( "TestAknTextUtilsDisplayTextLanguageSpecificNumberConversion", CTestSDKUiFwUtil::TestAknTextUtilsDisplayTextLanguageSpecificNumberConversion ),
        ENTRY( "TestAknTextUtilsTextEditorDigitType", CTestSDKUiFwUtil::TestAknTextUtilsTextEditorDigitType ),
        ENTRY( "TestAknTextUtilsDigitModeQuery", CTestSDKUiFwUtil::TestAknTextUtilsDigitModeQuery ),
        ENTRY( "TestAknTextUtilsConvertFileNameL", CTestSDKUiFwUtil::TestAknTextUtilsConvertFileNameL ),
        ENTRY( "TestAknTextUtilsLoadTextL", CTestSDKUiFwUtil::TestAknTextUtilsLoadTextL ),
        ENTRY( "TestAknTextUtilsClipAccordingScreenOrientationLCL", CTestSDKUiFwUtil::TestAknTextUtilsClipAccordingScreenOrientationLCL ),
        ENTRY( "TestAknTextUtilsChooseScalableText", CTestSDKUiFwUtil::TestAknTextUtilsChooseScalableText ),
        ENTRY( "TestAknSelectServHandleSelectionListProcessCommandL", CTestSDKUiFwUtil::TestAknSelectServHandleSelectionListProcessCommandL ),
        ENTRY( "TestAknSelectServHandleMultiselectionListProcessCommandL", CTestSDKUiFwUtil::TestAknSelectServHandleMultiselectionListProcessCommandL ),
        ENTRY( "TestAknSelectServHandleMarkableListProcessCommandL", CTestSDKUiFwUtil::TestAknSelectServHandleMarkableListProcessCommandL ),
        ENTRY( "TestAknSelectServHandleMenuListOfferKeyEventL", CTestSDKUiFwUtil::TestAknSelectServHandleMenuListOfferKeyEventL ),
        ENTRY( "TestAknSelectServHandleMarkableListDynInitMenuPaneL", CTestSDKUiFwUtil::TestAknSelectServHandleMarkableListDynInitMenuPaneL ),
        ENTRY( "TestAknSelectServHandleMarkableListDynInitMenuItemL", CTestSDKUiFwUtil::TestAknSelectServHandleMarkableListDynInitMenuItemL ),
        ENTRY( "TestAknSelectServHandleMarkableListUpdateAfterCommandExecutionL", CTestSDKUiFwUtil::TestAknSelectServHandleMarkableListUpdateAfterCommandExecutionL ),
        ENTRY( "TestAknSelectServHandleItemRemovalAndPositionHighlightL", CTestSDKUiFwUtil::TestAknSelectServHandleItemRemovalAndPositionHighlightL ),
        ENTRY( "TestAknFindHandleFindPopupProcessCommandL", CTestSDKUiFwUtil::TestAknFindHandleFindPopupProcessCommandL ),
        ENTRY( "TestAknFindHandleFindOfferKeyEventL", CTestSDKUiFwUtil::TestAknFindHandleFindOfferKeyEventL ),
        ENTRY( "TestAknFindHandleSizeChangeL", CTestSDKUiFwUtil::TestAknFindHandleSizeChangeL ),
        ENTRY( "TestAknFindProcessStrL", CTestSDKUiFwUtil::TestAknFindProcessStrL ),
        ENTRY( "TestAknFindConstructEditingL", CTestSDKUiFwUtil::TestAknFindConstructEditingL ),
        ENTRY( "TestCListBoxNumbersL", CTestSDKUiFwUtil::TestCListBoxNumbersL ),
        ENTRY( "TestFilterTextListBoxModelProcessFilterL", CTestSDKUiFwUtil::TestFilterTextListBoxModelProcessFilterL ),
        ENTRY( "TestFilterTextListBoxModelParaInfoL", CTestSDKUiFwUtil::TestFilterTextListBoxModelParaInfoL ),
        ENTRY( "TestCAknListBoxFilterItemsConstructorL", CTestSDKUiFwUtil::TestCAknListBoxFilterItemsConstructorL ),
        ENTRY( "TestCAknListBoxFilterItemsConstructL", CTestSDKUiFwUtil::TestCAknListBoxFilterItemsConstructL ),
        ENTRY( "TestCAknListBoxFilterItemsResetFilteringL", CTestSDKUiFwUtil::TestCAknListBoxFilterItemsResetFilteringL ),
        ENTRY( "TestCAknListBoxFilterItemsUpdateCachedDataL", CTestSDKUiFwUtil::TestCAknListBoxFilterItemsUpdateCachedDataL ),
        ENTRY( "TestCAknListBoxFilterItemsProcessSelectionIndexL", CTestSDKUiFwUtil::TestCAknListBoxFilterItemsProcessSelectionIndexL ),
        ENTRY( "TestCAknListBoxFilterItemsFilteredItemL", CTestSDKUiFwUtil::TestCAknListBoxFilterItemsFilteredItemL ),
        ENTRY( "TestCAknListBoxFilterItemsHandleOfferkeyEventL", CTestSDKUiFwUtil::TestCAknListBoxFilterItemsHandleOfferkeyEventL ),
        ENTRY( "TestCAknListBoxFilterItemsHandleItemArrayChangeL", CTestSDKUiFwUtil::TestCAknListBoxFilterItemsHandleItemArrayChangeL ),
        ENTRY( "TestCAknListBoxFilterItemsDoObserverFuncL", CTestSDKUiFwUtil::TestCAknListBoxFilterItemsDoObserverFuncL ),
        ENTRY( "TestCAknListBoxFilterItemsDoFuncFromFepL", CTestSDKUiFwUtil::TestCAknListBoxFilterItemsDoFuncFromFepL ),
        ENTRY( "TestCAknListBoxFilterItemsSetNewParaL", CTestSDKUiFwUtil::TestCAknListBoxFilterItemsSetNewParaL ),
        ENTRY( "TestCAknListBoxFilterItemsProcessControlL", CTestSDKUiFwUtil::TestCAknListBoxFilterItemsProcessControlL ),
        ENTRY( "TestCAknGenericReaderFuncsL", CTestSDKUiFwUtil::TestCAknGenericReaderFuncsL ),
        ENTRY( "TestAknLayoutUtilsLayoutLabelL", CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutLabelL ),
        ENTRY( "TestAknLayoutUtilsLayoutEdwinL", CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutEdwinL ),
        ENTRY( "TestAknLayoutUtilsMinimizedEdwinRectL", CTestSDKUiFwUtil::TestAknLayoutUtilsMinimizedEdwinRectL ),
        ENTRY( "TestAknLayoutUtilsLayoutMfneL", CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutMfneL ),
        ENTRY( "TestAknLayoutUtilsLayoutControlL", CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutControlL ),
        ENTRY( "TestAknLayoutUtilsLayoutImageL", CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutImageL ),
        ENTRY( "TestAknLayoutUtilsLayoutSecretEditorL", CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutSecretEditorL ),
        ENTRY( "TestAknLayoutUtilsRectFromCoords", CTestSDKUiFwUtil::TestAknLayoutUtilsRectFromCoords ),
        ENTRY( "TestAknLayoutUtilsFontFromId", CTestSDKUiFwUtil::TestAknLayoutUtilsFontFromId ),
        ENTRY( "TestAknLayoutUtilsCreateLayoutFontFromSpecificationL", CTestSDKUiFwUtil::TestAknLayoutUtilsCreateLayoutFontFromSpecificationL ),
        ENTRY( "TestAknLayoutUtilsSomeSimpleFunc", CTestSDKUiFwUtil::TestAknLayoutUtilsSomeSimpleFunc ),
        ENTRY( "TestAknLayoutUtilsOverrideControlColorL", CTestSDKUiFwUtil::TestAknLayoutUtilsOverrideControlColorL ),
        ENTRY( "TestAknLayoutUtilsScrollBarTypeL", CTestSDKUiFwUtil::TestAknLayoutUtilsScrollBarTypeL ),
        ENTRY( "TestAknLayoutUtilsLayoutMetrics", CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutMetrics ),
        ENTRY( "TestAknLayoutUtilsEdwinLine", CTestSDKUiFwUtil::TestAknLayoutUtilsEdwinLine ),
        ENTRY( "TestTAknLayoutTextConstructorL", CTestSDKUiFwUtil::TestTAknLayoutTextConstructorL ),
        ENTRY( "TestTAknLayoutTextLayoutTextL", CTestSDKUiFwUtil::TestTAknLayoutTextLayoutTextL ),
        ENTRY( "TestTAknLayoutTextDrawTextL", CTestSDKUiFwUtil::TestTAknLayoutTextDrawTextL ),
        ENTRY( "TestTAknLayoutRectConstructorL", CTestSDKUiFwUtil::TestTAknLayoutRectConstructorL ),
        ENTRY( "TestTAknLayoutRectLayoutRectL", CTestSDKUiFwUtil::TestTAknLayoutRectLayoutRectL ),
        ENTRY( "TestTAknLayoutRectSimpleFuncL", CTestSDKUiFwUtil::TestTAknLayoutRectSimpleFuncL ),
        ENTRY( "TestAknDrawDoDrawFuncsL", CTestSDKUiFwUtil::TestAknDrawDoDrawFuncsL ),
        ENTRY( "TestAknDrawWithSkinsDoDrawFuncsL", CTestSDKUiFwUtil::TestAknDrawWithSkinsDoDrawFuncsL ),
        ENTRY( "TestAknUtilsGlobalFuncsL", CTestSDKUiFwUtil::TestAknUtilsGlobalFuncsL ),
        ENTRY( "TestFilterTextListBoxModelRemoveFilterL", CTestSDKUiFwUtil::TestFilterTextListBoxModelRemoveFilterL ),
        ENTRY( "TestAknPopupUtilsPosition", CTestSDKUiFwUtil::TestAknPopupUtilsPositionFuncs ),
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


//  [End of File]
