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
* Description:  test ui framework utilities api
*
*/



#ifndef C_TESTSDKUIFWUTIL_H
#define C_TESTSDKUIFWUTIL_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <aknbiditextutils.h>
#include <aknenv.h>
#include <e32base.h>
#include <akniconarray.h>
#include <aknutils.h>
#include <coemain.h>
#include <aknindicatorcontainer.h>
#include <akneditstateindicator.h>
#include <barsread.h>
#include <coemain.h>

#include "testsdkuifwutilview.h"
#include "testsdkuifwutilcontainer.h"
// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkuifwutilLogPath, "\\logs\\testframework\\testsdkuifwutil\\" ); 
// Log file
_LIT( KtestsdkuifwutilLogFile, "testsdkuifwutil.txt" ); 
_LIT( KtestsdkuifwutilLogFileWithTitle, "testsdkuifwutil_[%S].txt" );

/**
*  CTestSDKUiFwUtil test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKUiFwUtil ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKUiFwUtil* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKUiFwUtil();

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
    CTestSDKUiFwUtil( CTestModuleIf& aTestModuleIf );

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
    * TestAknBidiTextUtilsConvertToVisualAndClipL test ConvertToVisualAndClipL
    * of AknBidiTextUtils in aknbiditextutils.h
    * @since S60 5.0
    * @param aItem is a number, 0 test ConvertToVisualAndClipL, 1 test ConvertToVisualAndClip.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknBidiTextUtilsConvertToVisualAndClipL( CStifItemParser& aItem );
    
    /**
    * TestAknBidiTextUtilsPrepareRunInfoArray test PrepareRunInfoArray
    * of AknBidiTextUtils in aknbiditextutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknBidiTextUtilsPrepareRunInfoArray( CStifItemParser& aItem );
    
    /**
    * TestAknBidiTextUtilsConvertToVisualAndWrapToArrayL test two ConvertToVisualAndWrapToArrayL
    * of AknBidiTextUtils in aknbiditextutils.h
    * @since S60 5.0
    * @param aItem is a number, 0 test function wiht line width array, 1 test the other.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknBidiTextUtilsConvertToVisualAndWrapToArrayL( CStifItemParser& aItem );
    
    /**
    * TestAknBidiTextUtilsConvertToVisualAndChopToArrayL test two ConvertToVisualAndChopToArrayL
    * of AknBidiTextUtils in aknbiditextutils.h
    * @since S60 5.0
    * @param aItem is a number, 0 test function wiht line width array, 1 test the other.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknBidiTextUtilsConvertToVisualAndChopToArrayL( CStifItemParser& aItem );
    
    /**
    * TestAknBidiTextUtilsConvertToVisualAndWrapToStringL test ConvertToVisualAndWrapToStringL
    * of AknBidiTextUtils in aknbiditextutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknBidiTextUtilsConvertToVisualAndWrapToStringL( CStifItemParser& aItem );
    
    /**
    * TestAknBidiTextUtilsConvertToVisualAndWrapToArrayWholeTextL test ConvertToVisualAndWrapToArrayWholeTextL
    * of AknBidiTextUtils in aknbiditextutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknBidiTextUtilsConvertToVisualAndWrapToArrayWholeTextL( CStifItemParser& aItem );
    
    /**
    * TestAknBidiTextUtilsMeasureTextBoundsWidth test MeasureTextBoundsWidth
    * of AknBidiTextUtils in aknbiditextutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknBidiTextUtilsMeasureTextBoundsWidth( CStifItemParser& aItem );
    
    /**
    * TestAknEnvStatic test Static
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvStatic( CStifItemParser& aItem );
    
    /**
    * TestAknEnvExecuteEmptyPopupListL test ExecuteEmptyPopupListL
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is a number, 0 test function with only on parameter, 1test the other.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvExecuteEmptyPopupListL( CStifItemParser& aItem );
    
    /**
    * TestAknEnvSetAndGetObserverL test SetFepMenuObserver and FepMenuObserver
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvSetAndGetObserverL( CStifItemParser& aItem );
    
    /**
    * TestAknEnvEditingStateIndicator test EditingStateIndicator
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvEditingStateIndicator( CStifItemParser& aItem );
    
    /**
    * TestAknEnvSwapEditingStateIndicatorL test SwapEditingStateIndicatorL
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvSwapEditingStateIndicatorL( CStifItemParser& aItem );
    
    /**
    * TestAknEnvExitForegroundAppL test ExitForegroundAppL 
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvExitForegroundAppL( CStifItemParser& aItem );
    
    /**
    * TestAknEnvRegisterIntermediateStateL test RegisterIntermediateStateL 
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvRegisterIntermediateStateL( CStifItemParser& aItem );
    
    /**
    * TestAknEnvUnRegisterIntermediateStateL test UnRegisterIntermediateState 
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvUnRegisterIntermediateStateL( CStifItemParser& aItem );
    
    /**
    * TestAknEnvCloseAllIntermediateStates test CloseAllIntermediateStates 
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvCloseAllIntermediateStates( CStifItemParser& aItem );
    
    /**
    * TestAknEnvRunAppShutterL test RunAppShutter 
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvRunAppShutterL( CStifItemParser& aItem );
    
    /**
    * TestAknEnvAppWithShutterRunningL test AppWithShutterRunning 
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvAppWithShutterRunningL( CStifItemParser& aItem );
    
    /**
    * TestAknEnvStopSchedulerWaitWithBusyMessage test StopSchedulerWaitWithBusyMessage 
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvStopSchedulerWaitWithBusyMessage( CStifItemParser& aItem );
    
    /**
    * TestAknEnvProcessObserverL test CreateCbaObserverL, RemoveCbaObserver and InformCbaDeletion
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvProcessObserverL( CStifItemParser& aItem );
    
    /**
    * TestAknEnvProcessCommandMediationL test RequestCommandMediationL and EndCommandMediation
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvProcessCommandMediationL( CStifItemParser& aItem );
    
    /**
    * TestAknEnvGetCurrentLayoutId test GetCurrentLayoutId
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvGetCurrentLayoutId( CStifItemParser& aItem );
    
    /**
    * TestAknEnvGetCurrentGlobalUiZoom test GetCurrentGlobalUiZoom
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvGetCurrentGlobalUiZoom( CStifItemParser& aItem );
    
    /**
    * TestAknEnvStatusPaneResIdForCurrentLayout test StatusPaneResIdForCurrentLayout
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvStatusPaneResIdForCurrentLayout( CStifItemParser& aItem );
    
    /**
    * TestAknEnvRequestWsBuffer test RequestWsBuffer and CancelWsBufferRequest
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvRequestWsBuffer( CStifItemParser& aItem );
    
    /**
    * TestAknEnvSettingCache test SettingCache
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvSettingCache( CStifItemParser& aItem );
    
    /**
    * TestAknEnvLoadAknLayoutL test two LoadAknLayoutL functions and AknLayout
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvLoadAknLayoutL( CStifItemParser& aItem );
    
    /**
    * TestAknEnvAvkonColor test AvkonColor
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvAvkonColor( CStifItemParser& aItem );
    
    /**
    * TestAknEnvSplitViewActive test SplitViewActive
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvSplitViewActive( CStifItemParser& aItem );
    
    /**
    * TestAknEnvTransparencyEnabled test TransparencyEnabled
    * of CAknEnv in aknenv.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknEnvTransparencyEnabled( CStifItemParser& aItem );
    
    /**
    * TestCAknIconArrayConstructor test CAknIconArray
    * of CAknEnv in akniconarray.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknIconArrayConstructorL( CStifItemParser& aItem );
    
    /**
    * TestCAknIconArrayConstructFromResourceL test two ConstructFromResourceL
    * of CAknEnv in akniconarray.h
    * @since S60 5.0
    * @param aItem is a number, 0 test Construct From Resource, 
    * 1 test Construct From Reader.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknIconArrayConstructFromResourceL( CStifItemParser& aItem );
    
    /**
    * TestCAknIconArrayAppendFromResourceL test two AppendFromResourceL
    * of CAknEnv in akniconarray.h
    * @since S60 5.0
    * @param aItem is a number, 0 test append From Resource, 
    * 1 test append From Reader.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknIconArrayAppendFromResourceL( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsClipToFitL test three ClipToFit
    * of AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is a number, 
    * 0 test function with default parameter 
    * 1 test function with CEikColumnListBox parameter
    * 2 test function with CEikFormattedCellListBox parameter 
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsClipToFitL( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsWrapToArrayL test two WrapToArrayL
    * of AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is a number, 0 test function with CArrayFix<TInt> parameters, 
    * 1 test the other.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsWrapToArrayL( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsWrapToArrayAndClipL test WrapToArrayAndClipL
    * of AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsWrapToArrayAndClipL( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsChopToArrayAndClipL test two ChopToArrayAndClipL
    * of AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is a number, 0 test function with CArrayFix<TInt> parameters, 
    * 1 test the other.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsChopToArrayAndClipL( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsWrapToStringL test WrapToStringL
    * of AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsWrapToStringL( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsWrapToStringAndClipL test WrapToStringAndClipL
    * of AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsWrapToStringAndClipL( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsProcessCharacters test three function
    * of AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is a number, 
    * 0 test function StripCharacters
    * 1 test function ReplaceCharacters
    * 2 test function PackWhiteSpaces
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsProcessCharacters( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsLanguageSpecificNumberConversion test LanguageSpecificNumberConversion
    * of AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsLanguageSpecificNumberConversion( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsConvertDigitsTo test ConvertDigitsTo
    * of AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsConvertDigitsTo( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsCurrentScriptDirectionality test CurrentScriptDirectionality
    * of AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsCurrentScriptDirectionality( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsNumericEditorDigitType test NumericEditorDigitType of 
    * AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsNumericEditorDigitType( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsDisplayTextLanguageSpecificNumberConversion test 
    * DisplayTextLanguageSpecificNumberConversion of
    * AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsDisplayTextLanguageSpecificNumberConversion( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsTextEditorDigitType test TextEditorDigitType of 
    * AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsTextEditorDigitType( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsDigitModeQuery test DigitModeQuery of 
    * AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsDigitModeQuery( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsConvertFileNameL test ConvertFileNameL of 
    * AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsConvertFileNameL( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsLoadTextL test LoadScalableTextL, LoadScalableTextLC
    * and LoadScalableText of 
    * AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsLoadTextL( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsClipAccordingScreenOrientationLCL test ClipAccordingScreenOrientationLC
    * AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsClipAccordingScreenOrientationLCL( CStifItemParser& aItem );
    
    /**
    * TestCAknTextUtilsChooseScalableText test ChooseScalableText
    * AknTextUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknTextUtilsChooseScalableText( CStifItemParser& aItem );
    
    /**
    * TestAknSelectServHandleSelectionListProcessCommandL test 
    * HandleSelectionListProcessCommandL of AknSelectionService in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknSelectServHandleSelectionListProcessCommandL( CStifItemParser& aItem );
    
    /**
    * TestAknSelectServHandleMultiselectionListProcessCommandL test 
    * HandleMultiselectionListProcessCommandL of AknSelectionService in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknSelectServHandleMultiselectionListProcessCommandL( CStifItemParser& aItem );

    /**
    * TestAknSelectServHandleMarkableListProcessCommandL test 
    * HandleMarkableListProcessCommandL of AknSelectionService in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknSelectServHandleMarkableListProcessCommandL( CStifItemParser& aItem );

    /**
    * TestAknSelectServHandleMenuListOfferKeyEventL test 
    * HandleMenuListOfferKeyEventL of AknSelectionService in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknSelectServHandleMenuListOfferKeyEventL( CStifItemParser& aItem );

    /**
    * TestAknSelectServHandleMarkableListDynInitMenuPaneL test 
    * HandleMarkableListDynInitMenuPane of AknSelectionService in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknSelectServHandleMarkableListDynInitMenuPaneL( CStifItemParser& aItem );

    /**
    * TestAknSelectServHandleMarkableListDynInitMenuItemL test 
    * HandleMarkableListDynInitMenuItem of AknSelectionService in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknSelectServHandleMarkableListDynInitMenuItemL( CStifItemParser& aItem );

    /**
    * TestAknSelectServHandleMarkableListUpdateAfterCommandExecutionL test 
    * HandleMarkableListUpdateAfterCommandExecution of AknSelectionService in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknSelectServHandleMarkableListUpdateAfterCommandExecutionL( CStifItemParser& aItem );

    /**
    * TestAknSelectServHandleItemRemovalAndPositionHighlightL test two
    * HandleItemRemovalAndPositionHighlightL  of AknSelectionService in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknSelectServHandleItemRemovalAndPositionHighlightL( CStifItemParser& aItem );
    
    /**
    * TestAknFindHandleFindPopupProcessCommandL test HandleFindPopupProcessCommandL
    * of AknFind in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknFindHandleFindPopupProcessCommandL( CStifItemParser& aItem );
    
    /**
    * TestAknFindHandleFindOfferKeyEventL test HandleFindOfferKeyEventL
    * of AknFind in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknFindHandleFindOfferKeyEventL( CStifItemParser& aItem );
    
    /**
    * TestAknFindHandleSizeChangeL test HandleFindSizeChanged,HandleFixedFindSizeChanged,
    * HandlePopupFindSizeChanged and HandleFindSizeChangedLayouts
    * of AknFind in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknFindHandleSizeChangeL( CStifItemParser& aItem );
    
    /**
    * TestAknFindProcessStrL test IsFindMatch, IsFindWordSeparator, IsAdaptiveFindMatch,
    * UpdateNextCharsFromString and UpdateItemTextAccordingToFlag of AknFind in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknFindProcessStrL( CStifItemParser& aItem );
    
    /**
    * TestAknFindConstructEditingL test five ConstructEditingL of AknEditUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknFindConstructEditingL( CStifItemParser& aItem );
    
    /**
    * TestCListBoxNumbersL test three export functions of CListBoxNumbers in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCListBoxNumbersL( CStifItemParser& aItem );
    
    /**
    * TestFilterTextListBoxModelProcessFilterL test CreateFilterL, RemoveFilter,
    * Filter of CAknFilteredTextListBoxModel in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestFilterTextListBoxModelProcessFilterL( CStifItemParser& aItem );
    
    /**
    * TestFilterTextListBoxModelParaInfoL test NumberOfItems, ItemText,
    * MatchableTextArray of CAknFilteredTextListBoxModel in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestFilterTextListBoxModelParaInfoL( CStifItemParser& aItem );
    
    /**
    * TestCAknListBoxFilterItemsConstructorL test constructor
    * of CAknListBoxFilterItems in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknListBoxFilterItemsConstructorL( CStifItemParser& aItem );
    
    /**
    * TestCAknListBoxFilterItemsConstructL test ConstructL
    * of CAknListBoxFilterItems in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknListBoxFilterItemsConstructL( CStifItemParser& aItem );
    
    /**
    * TestCAknListBoxFilterItemsResetFilteringL test ResetFilteringL
    * of CAknListBoxFilterItems in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknListBoxFilterItemsResetFilteringL( CStifItemParser& aItem );
    
    /**
    * TestCAknListBoxFilterItemsUpdateCachedDataL test UpdateCachedDataL
    * of CAknListBoxFilterItems in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknListBoxFilterItemsUpdateCachedDataL( CStifItemParser& aItem );
    
    /**
    * TestCAknListBoxFilterItemsProcessSelectionIndexL test SelectionIndexes,
    * two UpdateSelectionIndexesL of CAknListBoxFilterItems in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknListBoxFilterItemsProcessSelectionIndexL( CStifItemParser& aItem );
    
    /**
    * TestCAknListBoxFilterItemsFilteredItemL test FilteredNumberOfItems,
    * FilteredItemIndex, NonFilteredNumberOfItems, VisibleItemIndex, DefaultMatchableItemFromItem
    * of CAknListBoxFilterItems in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknListBoxFilterItemsFilteredItemL( CStifItemParser& aItem );
    
    /**
    * TestCAknListBoxFilterItemsHandleOfferkeyEventL test HandleOfferkeyEventL
    * of CAknListBoxFilterItems in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknListBoxFilterItemsHandleOfferkeyEventL( CStifItemParser& aItem );
    
    /**
    * TestCAknListBoxFilterItemsHandleItemArrayChangeL test HandleItemArrayChangeL
    * of CAknListBoxFilterItems in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknListBoxFilterItemsHandleItemArrayChangeL( CStifItemParser& aItem );
    
    /**
    * TestCAknListBoxFilterItemsDoObserverFuncL test SetObserver and HandleControlEventL
    * of CAknListBoxFilterItems in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknListBoxFilterItemsDoObserverFuncL( CStifItemParser& aItem );
    
    /**
    * TestCAknListBoxFilterItemsDoFuncFromFepL test DeferredSendKeyEventToFepL
    * of CAknListBoxFilterItems in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknListBoxFilterItemsDoFuncFromFepL( CStifItemParser& aItem );
    
    /**
    * TestCAknListBoxFilterItemsSetNewParaL test SetListBox, SetSearchField,
    * SetModel and SetView of CAknListBoxFilterItems in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknListBoxFilterItemsSetNewParaL( CStifItemParser& aItem );
    
    /**
    * TestCAknListBoxFilterItemsProcessControlL test SetParentControl, SetPopup,
    * FindBox of CAknListBoxFilterItems in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknListBoxFilterItemsProcessControlL( CStifItemParser& aItem );
    
    /**
    * TestAknLAFUtilsReplaceColumn test ReplaceColumn of AknLAFUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLAFUtilsReplaceColumn( CStifItemParser& aItem );
    
    /**
    * TestCAknGenericReaderFuncsL test ConstructL, ConstructFromResourceL,  of CAknGenericReader,
    * GfxItem, TextItem, CmdItem and AreaItem of CAknGenericReader in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknGenericReaderFuncsL( CStifItemParser& aItem );
    
    /**
    * TestAknLayoutUtilsLayoutLabelL test six overload function LayoutLabel 
    * of AknLayoutUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLayoutUtilsLayoutLabelL( CStifItemParser& aItem );
    
    /**
    * TestAknLayoutUtilsLayoutLabelL test ten overload function LayoutEdwin 
    * of AknLayoutUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLayoutUtilsLayoutEdwinL( CStifItemParser& aItem );
    
    /**
    * TestAknLayoutUtilsMinimizedEdwinRectL test MinimizedEdwinRect 
    * of AknLayoutUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLayoutUtilsMinimizedEdwinRectL( CStifItemParser& aItem );
    
    /**
    * TestAknLayoutUtilsLayoutMfneL test five overload function LayoutMfne 
    * of AknLayoutUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLayoutUtilsLayoutMfneL( CStifItemParser& aItem );
    
    /**
    * TestAknLayoutUtilsLayoutControlL test five overload function LayoutControl 
    * of AknLayoutUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLayoutUtilsLayoutControlL( CStifItemParser& aItem );
    
    /**
    * TestAknLayoutUtilsLayoutImageL test five overload function LayoutImage 
    * of AknLayoutUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLayoutUtilsLayoutImageL( CStifItemParser& aItem );
    
    /**
    * TestAknLayoutUtilsLayoutSecretEditorL test two overload function LayoutSecretEditor 
    * of AknLayoutUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLayoutUtilsLayoutSecretEditorL( CStifItemParser& aItem );
    
    /**
    * TestAknLayoutUtilsRectFromCoords test TextRectFromCoords and RectFromCoords
    * of AknLayoutUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLayoutUtilsRectFromCoords( CStifItemParser& aItem );
    
    /**
    * TestAknLayoutUtilsFontFromId test LayoutFontFromId and FontFromId
    * of AknLayoutUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLayoutUtilsFontFromId( CStifItemParser& aItem );
    
    /**
    * TestAknLayoutUtilsCreateLayoutFontFromSpecificationL test two overload function
    * CreateLayoutFontFromSpecificationL of AknLayoutUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLayoutUtilsCreateLayoutFontFromSpecificationL( CStifItemParser& aItem );
    
    /**
    * TestAknLayoutUtilsSomeSimpleFunc test FontFromName, TextAlignFromId,GulAlignFromId,
    * CursorHeightFromFont,CursorWidthFromFont, CursorAscentFromFont, CursorExtensionsFromFont,
    * HighlightLeftPixelsFromFont, HighlightRightPixelsFromFont, LayoutMirrored,
    * Variant, SubVariant of AknLayoutUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLayoutUtilsSomeSimpleFunc( CStifItemParser& aItem );
    
    /**
    * TestAknLayoutUtilsOverrideControlColorL test OverrideControlColorL
    * of AknLayoutUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLayoutUtilsOverrideControlColorL( CStifItemParser& aItem );
    
    /**
    * TestAknLayoutUtilsScrollBarTypeL test DefaultScrollBarType,LayoutVerticalScrollBar
    * and LayoutHorizontalScrollBar of AknLayoutUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLayoutUtilsScrollBarTypeL( CStifItemParser& aItem );
    
    /**
    * TestAknLayoutUtilsLayoutMetrics test LayoutMetricsPosition,LayoutMetricsSize
    * and LayoutMetricsPosition of AknLayoutUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLayoutUtilsLayoutMetrics( CStifItemParser& aItem );
    
    /**
    * TestAknLayoutUtilsScalableLayoutInterfaceAvailable test ScalableLayoutInterfaceAvailable
    * of AknLayoutUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLayoutUtilsScalableLayoutInterfaceAvailable( CStifItemParser& aItem );
    
    /**
    * TestAknLayoutUtilsSimpleFunc test CbaLocation, MainPaneState, PenEnabled
    * and MSKEnabled of AknLayoutUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLayoutUtilsSimpleFunc( CStifItemParser& aItem );
    
    /**
    * TestAknLayoutUtilsEdwinLine test GetEdwinVerticalPositionAndHeightFromLines
    * and EdwinLinesWithinHeight of AknLayoutUtils in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknLayoutUtilsEdwinLine( CStifItemParser& aItem );
    
    /**
    * TestTAknLayoutTextConstructorL test constructor of TAknLayoutText in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAknLayoutTextConstructorL( CStifItemParser& aItem );
    
    /**
    * TestTAknLayoutTextLayoutTextL test five overload functions LayoutText
    * of TAknLayoutText in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAknLayoutTextLayoutTextL( CStifItemParser& aItem );
    
    /**
    * TestTAknLayoutTextDrawTextL test three overload functions DrawText and
    * TextRect of TAknLayoutText in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAknLayoutTextDrawTextL( CStifItemParser& aItem );
    
    /**
    * TestTAknLayoutRectConstructorL test constructor of TAknLayoutRect in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAknLayoutRectConstructorL( CStifItemParser& aItem );
    
    /**
    * TestTAknLayoutRectLayoutRectL test five overload functions LayoutRect
    * of TAknLayoutRect in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAknLayoutRectLayoutRectL( CStifItemParser& aItem );
    
    /**
    * TestTAknLayoutRectSimpleFuncL test Color, Rect, DrawImage, DrawRect and 
    * DrawOutLineRect of TAknLayoutRect in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAknLayoutRectSimpleFuncL( CStifItemParser& aItem );
    
    /**
    * TestAknDrawDoDrawFuncsL test DrawEmptyList, DrawEmptyListForSettingPage,
    * DrawEmptyListWithFind, DrawEmptyListHeading, DrawWindowShadow and 
    * DrawEmptyListImpl of AknDraw in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknDrawDoDrawFuncsL( CStifItemParser& aItem );
    
    /**
    * TestAknDrawWithSkinsDoDrawFuncsL test DrawEmptyList, DrawEmptyListForSettingPage,
    * DrawEmptyListWithFind, DrawEmptyListHeading and DrawWindowShadow
    * of AknDrawWithSkins in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknDrawWithSkinsDoDrawFuncsL( CStifItemParser& aItem );
    
    /**
    * TestAknUtilsGlobalFuncsL test LatinPlain12,LatinBold12, LatinBold13, LatinBold16, LatinBold17,
    * LatinBold19, NumberPlain5, ClockBold30, LatinClock14,ApacPlain12, ApacPlain16, CompleteWithAppPath,
    * DefaultInputLanguageFromUILanguage, SetKeyblockMode,ConvertUtcTimeToHomeTime and DisplayLanguageTagL
    * in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknUtilsGlobalFuncsL( CStifItemParser& aItem );
    
    /**
    * TestFilterTextListBoxModelRemoveFilterL test Remove
    * of AknDrawWithSkins in aknutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestFilterTextListBoxModelRemoveFilterL( CStifItemParser& aItem );
    
    /**
    * TestAknPopupUtilsPosition test popup position in aknutils.h.
    * @since S60 5.2
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknPopupUtilsPositionFuncs( CStifItemParser& aItem );
    
private:    // Data
    
    enum TSwitchCaseId
        {
        ECaseZero = 0,
        ECaseOne,
        ECaseTwo,
        ECaseThree,
        ECaseFour
        };

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * Font
     * Not own.
     */
    const CFont* iFont;
    
    /**
     * View
     * Own.
     */
    CTestUiFwUtilView* iUiFwUtilView;
    
    /**
     * Container for control, get from iUiFwUtilView
     * Not own.
     */
    CTestUiFwUtilContainer* iContainer;

    /**
     * Resource file offset
     */
    TInt iOffset;
    
    /**
     * Pointer to get system parameter
     * Remove warning
     */
    CEikonEnv* iEnv;

    };

#endif      // C_TESTSDKUIFWUTIL_H

// End of File
