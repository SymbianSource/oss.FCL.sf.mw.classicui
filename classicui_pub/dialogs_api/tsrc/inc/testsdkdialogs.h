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
* Description:  Test EIKDIALG.H
*
*/



#ifndef C_TESTSDKDIALOGS_H
#define C_TESTSDKDIALOGS_H

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
_LIT( KtestsdkdialogsLogPath, "\\logs\\testframework\\testsdkdialogs\\" ); 
// Log file
_LIT( KtestsdkdialogsLogFile, "testsdkdialogs.txt" ); 
_LIT( KtestsdkdialogsLogFileWithTitle, "testsdkdialogs_[%S].txt" );

// FORWARD DECLARATIONS
class CTestSDKDialogs;

/**
*  Ctestsdkdialogs test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKDialogs) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKDialogs* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKDialogs();

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
    CTestSDKDialogs( CTestModuleIf& aTestModuleIf );

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

private: // Test EIKDIALG.h
/*                               class CEikDialog                           */
    /**
     * TestDCEikDialogL test function for testing the 
     *     CEikDialog function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDCEikDialogL( CStifItemParser& aItem );
    
    /**
     * TestDDeconstructorL test function for testing the 
     *     ~CEikDialog function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestDExecuteLD test function for testing the 
     *     ExecuteLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDExecuteLD( CStifItemParser& aItem );
    
    /**
     * TestDPrepareLC test function for testing the 
     *     PrepareLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDPrepareLC( CStifItemParser& aItem );
    
    /**
     * TestDReadResourceLC test function for testing the 
     *     ReadResourceLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDReadResourceLC( CStifItemParser& aItem );
    
    /**
     * TestDRunLD test function for testing the 
     *     RunLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDRunLD( CStifItemParser& aItem );
    
    /**
     * TestDSetTitleTDesCL test function for testing the 
     *     SetTitleL function with a Title
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetTitleTDesCL( CStifItemParser& aItem );
    
    /**
     * TestDSetTitleResourceL test function for testing the 
     *     SetTitleL function with a Id
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetTitleResourceL( CStifItemParser& aItem );
    
    /**
     * TestDSetPageDimmedNowL test function for testing the 
     *     SetPageDimmedNow function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetPageDimmedNowL( CStifItemParser& aItem );
    
    /**
     * TestDSetLineNonFocusingL test function for testing the 
     *     SetLineNonFocusing function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetLineNonFocusingL( CStifItemParser& aItem );
    
    /**
     * TestDSetLineDimmedNowL test function for testing the 
     *     SetLineDimmedNow function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetLineDimmedNowL( CStifItemParser& aItem );
    
    /**
     * TestDMakeLineVisibleL test function for testing the 
     *     MakeLineVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDMakeLineVisibleL( CStifItemParser& aItem );
    
    /**
     * TestDMakeWholeLineVisibleL test function for testing the 
     *     MakeWholeLineVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDMakeWholeLineVisibleL( CStifItemParser& aItem );
    
    /**
     * TestDDeleteLineL test function for testing the 
     *     DeleteLine function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDDeleteLineL( CStifItemParser& aItem );
    
    /**
     * TestDInsertLineL test function for testing the 
     *     InsertLineL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDInsertLineL( CStifItemParser& aItem );
    
    /**
     * TestDMakePanelButtonVisibleL test function for testing the 
     *     MakePanelButtonVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDMakePanelButtonVisibleL( CStifItemParser& aItem );
    
    /**
     * TestDTryChangeFocusToL test function for testing the 
     *     TryChangeFocusToL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDTryChangeFocusToL( CStifItemParser& aItem );
    
    /**
     * TestDSwitchLineLatencyL test function for testing the 
     *     SwitchLineLatency function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSwitchLineLatencyL( CStifItemParser& aItem );
    
    /**
     * TestDSetPageDensePackingL test function for testing the 
     *     SetPageDensePacking function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetPageDensePackingL( CStifItemParser& aItem );
    
    /**
     * TestDConstructAutoDialogLC test function for testing the 
     *     ConstructAutoDialogLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDConstructAutoDialogLC( CStifItemParser& aItem );
    
    /**
     * TestDDeclareItemAutoL test function for testing the 
     *     DeclareItemAuto function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDDeclareItemAutoL( CStifItemParser& aItem );
    
    /**
     * TestDLayoutL test function for testing the 
     *     Layout function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLayoutL( CStifItemParser& aItem );
    
    /**
     * TestDPreferredSizeL test function for testing the 
     *     PreferredSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDPreferredSizeL( CStifItemParser& aItem );
    
    /**
     * TestDCreateLineByTypeL test function for testing the 
     *     CreateLineByTypeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDCreateLineByTypeL( CStifItemParser& aItem );
    
    /**
     * TestDCreateLineByTypeL test function for testing the 
     *     CreateLineByTypeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDCreateLineByTypePageIdL( CStifItemParser& aItem );
    
    /**
     * TestDSetControlCaptionTextL test function for testing the 
     *     SetControlCaptionL function with PageId
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetControlCaptionTextL( CStifItemParser& aItem );
    
    /**
     * TestDSetControlCaptionResourceIdL test function for testing the 
     *     SetControlCaptionL function with aText
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetControlCaptionResourceIdL( CStifItemParser& aItem );
    
    /**
     * TestDControlCaptionL test function for testing the 
     *     ControlCaption function with aResourceId
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDControlCaptionL( CStifItemParser& aItem );
    
    /**
     * TestDControlL test function for testing the 
     *     Control function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDControlL( CStifItemParser& aItem );
    
    /**
     * TestDControlOrNullL test function for testing the 
     *     ControlOrNull function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDControlOrNullL( CStifItemParser& aItem );
    
    /**
     * TestDButtonGroupContainerL test function for testing the 
     *     ButtonGroupContainer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDButtonGroupContainerL( CStifItemParser& aItem );
    
    /**
     * TestDTitleL test function for testing the 
     *     Title function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDTitleL( CStifItemParser& aItem );
    
    /**
     * TestDActivePageIdL test function for testing the 
     *     ActivePageId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDActivePageIdL( CStifItemParser& aItem );
    
    /**
     * TestDActivateFirstPageL test function for testing the 
     *     ActivateFirstPageL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDActivateFirstPageL( CStifItemParser& aItem );
    
    /**
     * TestDSetEditableL test function for testing the 
     *     SetEditableL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetEditableL( CStifItemParser& aItem );
    
    /**
     * TestDIsEditableL test function for testing the 
     *     IsEditable function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDIsEditableL( CStifItemParser& aItem );
    
    /**
     * TestDOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestDFocusChangedL test function for testing the 
     *     FocusChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDFocusChangedL( CStifItemParser& aItem );
    
    /**
     * TestDGetColorUseListL test function for testing the 
     *     GetColorUseListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDGetColorUseListL( CStifItemParser& aItem );
    
    /**
     * TestDHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestDInputCapabilitiesL test function for testing the 
     *     InputCapabilities function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDInputCapabilitiesL( CStifItemParser& aItem );
    
    /**
     * TestDMakeVisibleL test function for testing the 
     *     MakeVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDMakeVisibleL( CStifItemParser& aItem );
    
    /**
     * TestDHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestDPrepareForFocusTransitionL test function for testing the 
     *     PrepareForFocusTransitionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDPrepareForFocusTransitionL( CStifItemParser& aItem );
    
    /**
     * TestDPageChangedL test function for testing the 
     *     PageChangedL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDPageChangedL( CStifItemParser& aItem );
    
    /**
     * TestDLineChangedL test function for testing the 
     *     LineChangedL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLineChangedL( CStifItemParser& aItem );
    
    /**
     * TestDCreateCustomControlL test function for testing the 
     *     CreateCustomControlL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDCreateCustomControlL( CStifItemParser& aItem );
    
    /**
     * TestDConvertCustomControlTypeToBaseControlTypeL test function for testing the 
     *     ConvertCustomControlTypeToBaseControlType function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDConvertCustomControlTypeToBaseControlTypeL( CStifItemParser& aItem );
    
    /**
     * TestDGetCustomAutoValueL test function for testing the 
     *     GetCustomAutoValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDGetCustomAutoValueL( CStifItemParser& aItem );
    
    /**
     * TestDPrepareContextL test function for testing the 
     *     PrepareContext function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDPrepareContextL( CStifItemParser& aItem );
    
    /**
     * TestDWriteInternalStateL test function for testing the 
     *     WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDWriteInternalStateL( CStifItemParser& aItem );
    
    /**
     * TestDCountComponentControlsL test function for testing the 
     *     CountComponentControls function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDCountComponentControlsL( CStifItemParser& aItem );
    
    /**
     * TestDComponentControlL test function for testing the 
     *     ComponentControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDComponentControlL( CStifItemParser& aItem );
    
    /**
     * TestDGetNumberOfLinesOnPageL test function for testing the 
     *     GetNumberOfLinesOnPage function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDGetNumberOfLinesOnPageL( CStifItemParser& aItem );
    
    /**
     * TestDGetNumberOfPagesL test function for testing the 
     *     GetNumberOfPages function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDGetNumberOfPagesL( CStifItemParser& aItem );
    
    /**
     * TestDGetLineByLineAndPageIndexL test function for testing the 
     *     GetLineByLineAndPageIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDGetLineByLineAndPageIndexL( CStifItemParser& aItem );
    
    /**
     * TestDHandleControlEventL test function for testing the 
     *     HandleControlEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHandleControlEventL( CStifItemParser& aItem );
    
    /**
     * TestDTryExitL test function for testing the 
     *     TryExitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDTryExitL( CStifItemParser& aItem );
    
    /**
     * TestDAdjustAllIdsOnPageL test function for testing the 
     *     AdjustAllIdsOnPage function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDAdjustAllIdsOnPageL( CStifItemParser& aItem );
    
    /**
     * TestDConstructSleepingDialogL test function for testing the 
     *     ConstructSleepingDialogL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDConstructSleepingDialogL( CStifItemParser& aItem );
    
    /**
     * TestDConstructSleepingAlertDialogL test function for testing the 
     *     ConstructSleepingAlertDialogL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDConstructSleepingAlertDialogL( CStifItemParser& aItem );
    
    /**
     * TestDRouseSleepingDialogL test function for testing the 
     *     RouseSleepingDialog function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDRouseSleepingDialogL( CStifItemParser& aItem );
    
    /**
     * TestDExitSleepingDialogL test function for testing the 
     *     ExitSleepingDialog function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDExitSleepingDialogL( CStifItemParser& aItem );
    
    /**
     * TestDIdOfFocusControlL test function for testing the 
     *     IdOfFocusControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDIdOfFocusControlL( CStifItemParser& aItem );
    
    /**
     * TestDFindLineIndexL test function for testing the 
     *     FindLineIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDFindLineIndexL( CStifItemParser& aItem );
    
    /**
     * TestDLineL test function for testing the 
     *     Line function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLineL( CStifItemParser& aItem );
    
    /**
     * TestDCurrentLineL test function for testing the 
     *     CurrentLine function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDCurrentLineL( CStifItemParser& aItem );
    
    /**
     * TestDRotateFocusByL test function for testing the 
     *     RotateFocusByL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDRotateFocusByL( CStifItemParser& aItem );
    
    /**
     * TestDActivePageIndexL test function for testing the 
     *     ActivePageIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDActivePageIndexL( CStifItemParser& aItem );
    
    /**
     * TestDResetLineMinimumSizesL test function for testing the 
     *     ResetLineMinimumSizes function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDResetLineMinimumSizesL( CStifItemParser& aItem );
    
    /**
     * TestDSwapButtonGroupContainerL test function for testing the 
     *     SwapButtonGroupContainer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSwapButtonGroupContainerL( CStifItemParser& aItem );
    
    /**
     * TestDButtonCommandObserverL test function for testing the 
     *     ButtonCommandObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDButtonCommandObserverL( CStifItemParser& aItem );
    
    /**
     * TestDOkToExitL test function for testing the 
     *     OkToExitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDOkToExitL( CStifItemParser& aItem );
    
    /**
     * TestDPreLayoutDynInitL test function for testing the 
     *     PreLayoutDynInitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDPreLayoutDynInitL( CStifItemParser& aItem );
    
    /**
     * TestDPostLayoutDynInitL test function for testing the 
     *     PostLayoutDynInitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDPostLayoutDynInitL( CStifItemParser& aItem );
    
    /**
     * TestDSetInitialCurrentLineL test function for testing the 
     *     SetInitialCurrentLine function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetInitialCurrentLineL( CStifItemParser& aItem );
    
    /**
     * TestDHandleControlStateChangeL test function for testing the 
     *     HandleControlStateChangeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHandleControlStateChangeL( CStifItemParser& aItem );
    
    /**
     * TestDHandleInteractionRefusedL test function for testing the 
     *     HandleInteractionRefused function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHandleInteractionRefusedL( CStifItemParser& aItem );
    
    /**
     * TestDSetSizeAndPositionL test function for testing the 
     *     SetSizeAndPosition function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetSizeAndPositionL( CStifItemParser& aItem );
    
    /**
     * TestDBorderStyleL test function for testing the 
     *     BorderStyle function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDBorderStyleL( CStifItemParser& aItem );
    
    /**
     * TestDMappedCommandIdL test function for testing the 
     *     MappedCommandId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDMappedCommandIdL( CStifItemParser& aItem );
    
    /**
     * TestDFormFlagsFromActivePageL test function for testing the 
     *     FormFlagsFromActivePage function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDFormFlagsFromActivePageL( CStifItemParser& aItem );
    
    /**
     * TestDGetFirstLineOnFirstPageOrNullL test function for testing the 
     *     GetFirstLineOnFirstPageOrNull function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDGetFirstLineOnFirstPageOrNullL( CStifItemParser& aItem );
    
    /**
     * TestDControlsOnPageL test function for testing the 
     *     ControlsOnPage function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDControlsOnPageL( CStifItemParser& aItem );
    
    /**
     * TestDMopSupplyObjectL test function for testing the 
     *     MopSupplyObject function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDMopSupplyObjectL( CStifItemParser& aItem );
    
    /**
     * TestDExtensionL test function for testing the 
     *     Extension function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDExtensionL( CStifItemParser& aItem );
    
    /**
     * TestDDialogFlagsL test function for testing the 
     *     DialogFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDDialogFlagsL( CStifItemParser& aItem );
    
    /**
     * TestDDeclareAutoTextEditorL test function for testing the 
     *     DeclareAutoTextEditorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDDeclareAutoTextEditorL( CStifItemParser& aItem );
    
    /**
     * TestDDeclareAutoNumberEditorL test function for testing the 
     *     DeclareAutoNumberEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDDeclareAutoNumberEditorL( CStifItemParser& aItem );
    
    /**
     * TestDDeclareAutoRangeEditorL test function for testing the 
     *     DeclareAutoRangeEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDDeclareAutoRangeEditorL( CStifItemParser& aItem );
    
    /**
     * TestDDeclareAutoTimeEditorL test function for testing the 
     *     DeclareAutoTimeEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDDeclareAutoTimeEditorL( CStifItemParser& aItem );
    
    /**
     * TestDDeclareAutoDateEditorL test function for testing the 
     *     DeclareAutoDateEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDDeclareAutoDateEditorL( CStifItemParser& aItem );
    
    /**
     * TestDDeclareAutoTimeAndDateEditorL test function for testing the 
     *     DeclareAutoTimeAndDateEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDDeclareAutoTimeAndDateEditorL( CStifItemParser& aItem );
    
    /**
     * TestDDeclareAutoDurationEditorL test function for testing the 
     *     DeclareAutoDurationEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDDeclareAutoDurationEditorL( CStifItemParser& aItem );
    
    /**
     * TestDDeclareAutoTimeOffsetEditorL test function for testing the 
     *     DeclareAutoTimeOffsetEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDDeclareAutoTimeOffsetEditorL( CStifItemParser& aItem );
    
    /**
     * TestDDeclareAutoFixedPointEditorL test function for testing the 
     *     DeclareAutoFixedPointEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDDeclareAutoFixedPointEditorL( CStifItemParser& aItem );
    
    /**
     * TestDDeclareAutoSecretEditorL test function for testing the 
     *     DeclareAutoSecretEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDDeclareAutoSecretEditorL( CStifItemParser& aItem );
    
    /**
     * TestDAddAutoTextEditorL test function for testing the 
     *     AddAutoTextEditorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDAddAutoTextEditorL( CStifItemParser& aItem );
    
    /**
     * TestDAddAutoGlobalTextEditorL test function for testing the 
     *     AddAutoGlobalTextEditorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDAddAutoGlobalTextEditorL( CStifItemParser& aItem );
    
    /**
     * TestDAddAutoRichTextEditorL test function for testing the 
     *     AddAutoRichTextEditorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDAddAutoRichTextEditorL( CStifItemParser& aItem );
    
    /**
     * TestDAddAutoNumberEditorL test function for testing the 
     *     AddAutoNumberEditorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDAddAutoNumberEditorL( CStifItemParser& aItem );
    
    /**
     * TestDAddAutoRangeEditorL test function for testing the 
     *     AddAutoRangeEditorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDAddAutoRangeEditorL( CStifItemParser& aItem );
    
    /**
     * TestDAddAutoTimeEditorL test function for testing the 
     *     AddAutoTimeEditorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDAddAutoTimeEditorL( CStifItemParser& aItem );
    
    /**
     * TestDAddAutoDateEditorL test function for testing the 
     *     AddAutoDateEditorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDAddAutoDateEditorL( CStifItemParser& aItem );
    
    /**
     * TestDAddAutoTimeAndDateEditorL test function for testing the 
     *     AddAutoTimeAndDateEditorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDAddAutoTimeAndDateEditorL( CStifItemParser& aItem );
    
    /**
     * TestDAddAutoDurationEditorL test function for testing the 
     *     AddAutoDurationEditorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDAddAutoDurationEditorL( CStifItemParser& aItem );
    
    /**
     * TestDAddAutoTimeOffsetEditorL test function for testing the 
     *     AddAutoTimeOffsetEditorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDAddAutoTimeOffsetEditorL( CStifItemParser& aItem );
    
    /**
     * TestDAddAutoFloatEditorL test function for testing the 
     *     AddAutoFloatEditorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDAddAutoFloatEditorL( CStifItemParser& aItem );
    
    /**
     * TestDAddAutoFixedPointEditorL test function for testing the 
     *     AddAutoFixedPointEditorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDAddAutoFixedPointEditorL( CStifItemParser& aItem );
    
    /**
     * TestDAddAutoSecretEditorL test function for testing the 
     *     AddAutoSecretEditorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDAddAutoSecretEditorL( CStifItemParser& aItem );
    
    /**
     * TestDSetLabelByDesL test function for testing the 
     *     SetLabelL function by Des
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetLabelByDesL( CStifItemParser& aItem );
    
    /**
     * TestDSetLabelByResourceIdL test function for testing the 
     *     SetLabelL function by ResourceId
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetLabelByResourceIdL( CStifItemParser& aItem );
    
    /**
     * TestDSetLabelReserveLengthL test function for testing the 
     *     SetLabelReserveLengthL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetLabelReserveLengthL( CStifItemParser& aItem );
    
    /**
     * TestDSetEdwinTextL test function for testing the 
     *     SetEdwinTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetEdwinTextL( CStifItemParser& aItem );
    
    /**
     * TestDSetTextEditorTextL test function for testing the 
     *     SetTextEditorTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetTextEditorTextL( CStifItemParser& aItem );
    
    /**
     * TestDResetSecretEditorL test function for testing the 
     *     ResetSecretEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDResetSecretEditorL( CStifItemParser& aItem );
    
    /**
     * TestDSetFloatingPointEditorValueL test function for testing the 
     *     SetFloatingPointEditorValueL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetFloatingPointEditorValueL( CStifItemParser& aItem );
    
    /**
     * TestDSetFixedPointEditorValueL test function for testing the 
     *     SetFixedPointEditorValueL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetFixedPointEditorValueL( CStifItemParser& aItem );
    
    /**
     * TestDSetFixedPointEditorDecimalL test function for testing the 
     *     SetFixedPointEditorDecimal function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetFixedPointEditorDecimalL( CStifItemParser& aItem );
    
    /**
     * TestDSetNumberEditorMinAndMaxL test function for testing the 
     *     SetNumberEditorMinAndMax function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetNumberEditorMinAndMaxL( CStifItemParser& aItem );
    
    /**
     * TestDSetNumberEditorValueL test function for testing the 
     *     SetNumberEditorValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetNumberEditorValueL( CStifItemParser& aItem );
    
    /**
     * TestDSetFloatEditorMinAndMaxL test function for testing the 
     *     SetFloatEditorMinAndMax function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetFloatEditorMinAndMaxL( CStifItemParser& aItem );
    
    /**
     * TestDSetFloatEditorValueL test function for testing the 
     *     SetFloatEditorValueL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetFloatEditorValueL( CStifItemParser& aItem );
    
    /**
     * TestDSetRangeEditorMinAndMaxL test function for testing the 
     *     SetRangeEditorMinAndMax function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetRangeEditorMinAndMaxL( CStifItemParser& aItem );
    
    /**
     * TestDSetRangeEditorValueL test function for testing the 
     *     SetRangeEditorValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetRangeEditorValueL( CStifItemParser& aItem );
    
    /**
     * TestDSetTTimeEditorMinAndMaxL test function for testing the 
     *     SetTTimeEditorMinAndMax function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetTTimeEditorMinAndMaxL( CStifItemParser& aItem );
    
    /**
     * TestDSetTTimeEditorValueL test function for testing the 
     *     SetTTimeEditorValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetTTimeEditorValueL( CStifItemParser& aItem );
    
    /**
     * TestDSetDurationEditorMinAndMaxL test function for testing the 
     *     SetDurationEditorMinAndMax function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetDurationEditorMinAndMaxL( CStifItemParser& aItem );
    
    /**
     * TestDSetDurationEditorValueL test function for testing the 
     *     SetDurationEditorValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetDurationEditorValueL( CStifItemParser& aItem );
    
    /**
     * TestDSetTimeOffsetEditorMinAndMaxL test function for testing the 
     *     SetTimeOffsetEditorMinAndMax function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetTimeOffsetEditorMinAndMaxL( CStifItemParser& aItem );
    
    /**
     * TestDSetTimeOffsetEditorValueL test function for testing the 
     *     SetTimeOffsetEditorValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetTimeOffsetEditorValueL( CStifItemParser& aItem );
    
    /**
     * TestDSetListBoxCurrentItemL test function for testing the 
     *     SetListBoxCurrentItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetListBoxCurrentItemL( CStifItemParser& aItem );
    
    /**
     * TestDSetFileNameL test function for testing the 
     *     SetFileNameL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetFileNameL( CStifItemParser& aItem );
    
    /**
     * TestDGetLabelTextL test function for testing the 
     *     GetLabelText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDGetLabelTextL( CStifItemParser& aItem );
    
    /**
     * TestDGetEdwinTextL test function for testing the 
     *     GetEdwinText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDGetEdwinTextL( CStifItemParser& aItem );
    
    /**
     * TestDGetTextEditorTextL test function for testing the 
     *     GetTextEditorText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDGetTextEditorTextL( CStifItemParser& aItem );
    
    /**
     * TestDGetSecretEditorTextL test function for testing the 
     *     GetSecretEditorText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDGetSecretEditorTextL( CStifItemParser& aItem );
    
    /**
     * TestDFloatingPointEditorValueL test function for testing the 
     *     FloatingPointEditorValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDFloatingPointEditorValueL( CStifItemParser& aItem );
    
    /**
     * TestDFixedPointEditorValueL test function for testing the 
     *     FixedPointEditorValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDFixedPointEditorValueL( CStifItemParser& aItem );
    
    /**
     * TestDFixedPointEditorDecimalL test function for testing the 
     *     FixedPointEditorDecimal function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDFixedPointEditorDecimalL( CStifItemParser& aItem );
    
    /**
     * TestDFloatEditorValueL test function for testing the 
     *     FloatEditorValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDFloatEditorValueL( CStifItemParser& aItem );
    
    /**
     * TestDNumberEditorValueL test function for testing the 
     *     NumberEditorValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDNumberEditorValueL( CStifItemParser& aItem );
    
    /**
     * TestDRangeEditorValueL test function for testing the 
     *     RangeEditorValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDRangeEditorValueL( CStifItemParser& aItem );
    
    /**
     * TestDTTimeEditorValueL test function for testing the 
     *     TTimeEditorValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDTTimeEditorValueL( CStifItemParser& aItem );
    
    /**
     * TestDDurationEditorValueL test function for testing the 
     *     DurationEditorValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDDurationEditorValueL( CStifItemParser& aItem );
    
    /**
     * TestDTimeOffsetEditorValueL test function for testing the 
     *     TimeOffsetEditorValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDTimeOffsetEditorValueL( CStifItemParser& aItem );
    
    /**
     * TestDGetAutoValuesFromPageL test function for testing the 
     *     GetAutoValuesFromPage function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDGetAutoValuesFromPageL( CStifItemParser& aItem );
    
    /**
     * TestDListBoxCurrentItemL test function for testing the 
     *     ListBoxCurrentItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDListBoxCurrentItemL( CStifItemParser& aItem );
    
    /**
     * TestDGetFileNameL test function for testing the 
     *     GetFileName function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDGetFileNameL( CStifItemParser& aItem );
    
    /**
     * TestDUpdatePageL test function for testing the 
     *     UpdatePageL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDUpdatePageL( CStifItemParser& aItem );
    
    /**
     * TestDHandleDialogPageEventL test function for testing the 
     *     HandleDialogPageEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHandleDialogPageEventL( CStifItemParser& aItem );
    
    /**
     * TestDPublishDialogL test function for testing the 
     *     PublishDialogL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDPublishDialogL( CStifItemParser& aItem );
    
    /**
     * TestDSetMediatorObserverL test function for testing the 
     *     SetMediatorObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetMediatorObserverL( CStifItemParser& aItem );
    
    /**
     * TestDSlideDialogL test function for testing the 
     *     SlideDialog function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSlideDialogL( CStifItemParser& aItem );
    
    /**
     * TestDSetMultilineQueryL test function for testing the 
     *     SetMultilineQuery function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDSetMultilineQueryL( CStifItemParser& aItem );
    
private:    // Data

    TInt iOldScreenSaverProperty;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKDIALOGS_H

// End of File
