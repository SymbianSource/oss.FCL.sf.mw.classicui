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
* Description:  test aknPopup.h aknpopupfader.h AknPopupField.h AknPopupFieldList.h 
*                     AknPopupFieldText.h aknPopupHeadingPane.h aknpopuplayout.h 
*                     AknPopupSettingPage.h
*
*/



#ifndef C_TESTSDKPOPUPS_H
#define C_TESTSDKPOPUPS_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <aknlists.h>
#include <aknpopup.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkpopupsLogPath, "\\logs\\testframework\\testsdkpopups\\" ); 
// Log file
_LIT( KtestsdkpopupsLogFile, "testsdkpopups.txt" ); 
_LIT( KtestsdkpopupsLogFileWithTitle, "testsdkpopups_[%S].txt" );

/**
*  CTestSDKPopups test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKPopups) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKPopups* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKPopups();

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
    CTestSDKPopups( CTestModuleIf& aTestModuleIf );

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

    //[TestMethods]

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    // Resource file offset
    TInt iOffset;
    
private: // Test aknPopup.h
/*                               class CAknPopupList                       */
    /**
     * TestPLNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLNewL( CStifItemParser& aItem );
    
    /**
     * TestPLExecuteLD test function for testing the 
     *     ExecuteLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLExecuteLD( CStifItemParser& aItem );
    
    /**
     * TestPLSetTitleL test function for testing the 
     *     SetTitleL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLSetTitleL( CStifItemParser& aItem );
    
    /**
     * TestPLCancelPopupL test function for testing the 
     *     CancelPopup function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLCancelPopupL( CStifItemParser& aItem );
    
    /**
     * TestPLButtonGroupContainerL test function for testing the 
     *     ButtonGroupContainer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLButtonGroupContainerL( CStifItemParser& aItem );
    
    /**
     * TestPLHeadingL test function for testing the 
     *     Heading function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLHeadingL( CStifItemParser& aItem );
    
    /**
     * TestPLHeadingConstL test function for testing the 
     *     Heading function const
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLHeadingConstL( CStifItemParser& aItem );
    
    /**
     * TestPLListBoxL test function for testing the 
     *     ListBox function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLListBoxL( CStifItemParser& aItem );
    
    /**
     * TestPLSetMaximumHeightL test function for testing the 
     *     SetMaximumHeight function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLSetMaximumHeightL( CStifItemParser& aItem );
    
    /**
     * TestPLEnableFindL test function for testing the 
     *     EnableFind function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLEnableFindL( CStifItemParser& aItem );
    
    /**
     * TestPLEnableAdaptiveFindL test function for testing the 
     *     EnableAdaptiveFind function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLEnableAdaptiveFindL( CStifItemParser& aItem );
    
    /**
     * TestPLFindBoxL test function for testing the 
     *     FindBox function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLFindBoxL( CStifItemParser& aItem );
    
    /**
     * TestPLHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestPLProcessCommandL test function for testing the 
     *     ProcessCommandL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLProcessCommandL( CStifItemParser& aItem );
    
    /**
     * TestPLHandleListBoxEventL test function for testing the 
     *     HandleListBoxEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLHandleListBoxEventL( CStifItemParser& aItem );
    
    /**
     * TestPLHandleControlEventL test function for testing the 
     *     HandleControlEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLHandleControlEventL( CStifItemParser& aItem );
    
    /**
     * TestPLCAknPopupListL test function for testing the 
     *     CAknPopupList function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLCAknPopupListL( CStifItemParser& aItem );
    
    /**
     * TestPLDeconstrutorL test function for testing the 
     *     ~CAknPopupList function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLDeconstrutorL( CStifItemParser& aItem );
    
    /**
     * TestPLConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLConstructL( CStifItemParser& aItem );
    
    /**
     * TestPLAttemptExitL test function for testing the 
     *     AttemptExitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLAttemptExitL( CStifItemParser& aItem );
    
    /**
     * TestPLSetupWindowLayoutL test function for testing the 
     *     SetupWindowLayout function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLSetupWindowLayoutL( CStifItemParser& aItem );
    
    /**
     * TestPLListBoxConstL test function for testing the 
     *     ListBox function const
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLListBoxConstL( CStifItemParser& aItem );
    
    /**
     * TestPLLayoutConstL test function for testing the 
     *     Layout function const
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLLayoutConstL( CStifItemParser& aItem );
    
    /**
     * TestPLLayoutL test function for testing the 
     *     Layout function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLLayoutL( CStifItemParser& aItem );
    
    /**
     * TestPLMopSupplyObjectL test function for testing the 
     *     MopSupplyObject function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLMopSupplyObjectL( CStifItemParser& aItem );
    
    /**
     * TestPLHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestPLFadeBehindPopupL test function for testing the 
     *     FadeBehindPopup function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPLFadeBehindPopupL( CStifItemParser& aItem );
    
private: // Test AknPopupFader.h
/*                               class MAknFadedComponent                   */
    /**
     * TestMFCCountFadedComponentsL test function for testing the 
     *     CountFadedComponents function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFCCountFadedComponentsL( CStifItemParser& aItem );
    
    /**
     * TestMFCFadedComponentL test function for testing the 
     *     FadedComponent function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFCFadedComponentL( CStifItemParser& aItem );
    
/*                               class TAknPopupFader                       */
    /**
     * TestTPFFadeBehindPopupL test function for testing the 
     *     FadeBehindPopup function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTPFFadeBehindPopupL( CStifItemParser& aItem );
    
private: // Test AknPopupField.h
/*                               class CAknPopupField                      */
    /**
     * TestCPFCAknPopupFieldL test function for testing the 
     *     CAknPopupField function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFCAknPopupFieldL( CStifItemParser& aItem );
    
    /**
     * TestCPFDeconstructorL test function for testing the 
     *     ~CAknPopupField function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestCPFConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFConstructL( CStifItemParser& aItem );
    
    /**
     * TestCPFSetAllowsUserDefinedEntryL test function for testing the 
     *     SetAllowsUserDefinedEntry function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFSetAllowsUserDefinedEntryL( CStifItemParser& aItem );
    
    /**
     * TestCPFActivateSelectionListL test function for testing the 
     *     ActivateSelectionListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFActivateSelectionListL( CStifItemParser& aItem );
    
    /**
     * TestCPFSetQueryValueL test function for testing the 
     *     SetQueryValueL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFSetQueryValueL( CStifItemParser& aItem );
    
    /**
     * TestCPFSetFontL test function for testing the 
     *     SetFont function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFSetFontL( CStifItemParser& aItem );
    
    /**
     * TestCPFSetShowIndicatorsL test function for testing the 
     *     SetShowIndicatorsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFSetShowIndicatorsL( CStifItemParser& aItem );
    
    /**
     * TestCPFNumLinesL test function for testing the 
     *     NumLines function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFNumLinesL( CStifItemParser& aItem );
    
    /**
     * TestCPFSetPopupFieldObserverL test function for testing the 
     *     SetPopupFieldObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFSetPopupFieldObserverL( CStifItemParser& aItem );
    
    /**
     * TestCPFSetEmptyListNoteL test function for testing the 
     *     SetEmptyListNoteL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFSetEmptyListNoteL( CStifItemParser& aItem );
    
    /**
     * TestCPFSetEmptyTextL test function for testing the 
     *     SetEmptyTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFSetEmptyTextL( CStifItemParser& aItem );
    
    /**
     * TestCPFSetOtherTextL test function for testing the 
     *     SetOtherTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFSetOtherTextL( CStifItemParser& aItem );
    
    /**
     * TestCPFSetInvalidTextL test function for testing the 
     *     SetInvalidTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFSetInvalidTextL( CStifItemParser& aItem );
    
    /**
     * TestCPFOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestCPFConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestCPFMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFMinimumSizeL( CStifItemParser& aItem );
    
    /**
     * TestCPFHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestCPFHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestCPFSetMaxNumberOfLinesPermittedL test function for testing the 
     *     SetMaxNumberOfLinesPermitted function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFSetMaxNumberOfLinesPermittedL( CStifItemParser& aItem );
    
    /**
     * TestCPFSetFormFieldRectL test function for testing the 
     *     SetFormFieldRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFSetFormFieldRectL( CStifItemParser& aItem );
    
    /**
     * TestCPFHandleControlEventL test function for testing the 
     *     HandleControlEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFHandleControlEventL( CStifItemParser& aItem );
    
    /**
     * TestCPFProcessCommandL test function for testing the 
     *     ProcessCommandL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFProcessCommandL( CStifItemParser& aItem );
    
    /**
     * TestCPFHandleListBoxEventL test function for testing the 
     *     HandleListBoxEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFHandleListBoxEventL( CStifItemParser& aItem );
    
    /**
     * TestCPFCountComponentControlsL test function for testing the 
     *     CountComponentControls function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFCountComponentControlsL( CStifItemParser& aItem );
    
    /**
     * TestCPFComponentControlL test function for testing the 
     *     ComponentControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFComponentControlL( CStifItemParser& aItem );
    
    /**
     * TestCPFSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFSizeChangedL( CStifItemParser& aItem );
    
    /**
     * TestCPFFocusChangedL test function for testing the 
     *     FocusChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFFocusChangedL( CStifItemParser& aItem );
    
    /**
     * TestCPFDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFDrawL( CStifItemParser& aItem );
    
    /**
     * TestCPFMopSupplyObjectL test function for testing the 
     *     MopSupplyObject function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFMopSupplyObjectL( CStifItemParser& aItem );
    
private: // Test AknPopupFieldText.h
/*                         class CAknPopupFieldText                      */
    /**
     * TestCPFTCAknPopupFieldTextL test function for testing the 
     *     CAknPopupFieldText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFTCAknPopupFieldTextL( CStifItemParser& aItem );
    
    /**
     * TestCPFTDeconstructorL test function for testing the 
     *     CAknPopupFieldText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFTDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestCPFTCurrentValueTextLC test function for testing the 
     *     CurrentValueTextLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFTCurrentValueTextLC( CStifItemParser& aItem );
    
    /**
     * TestCPFTCurrentValueIndexL test function for testing the 
     *     CurrentValueIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFTCurrentValueIndexL( CStifItemParser& aItem );
    
    /**
     * TestCPFTSetCurrentValueIndexL test function for testing the 
     *     SetCurrentValueIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFTSetCurrentValueIndexL( CStifItemParser& aItem );
    
    /**
     * TestCPFTMdcArrayL test function for testing the 
     *     MdcArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFTMdcArrayL( CStifItemParser& aItem );
    
    /**
     * TestCPFTSetAutoAppendL test function for testing the 
     *     SetAutoAppend function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFTSetAutoAppendL( CStifItemParser& aItem );
    
    /**
     * TestCPFTConstructFromResourceLL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFTConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestCPFTHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPFTHandlePointerEventL( CStifItemParser& aItem );
    
private: // Test AknPopupHeadingPane.h
/*                         class CAknPopupHeadingPane                   */
    /**
     * TestCPHPCAknPopupHeadingPaneL test function for testing the 
     *     CAknPopupHeadingPane function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPCAknPopupHeadingPaneL( CStifItemParser& aItem );
    
    /**
     * TestCPHPDeconstructorL test function for testing the 
     *     ~CAknPopupHeadingPane function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestCPHPSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPSizeChangedL( CStifItemParser& aItem );
    
    /**
     * TestCPHPMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPMinimumSizeL( CStifItemParser& aItem );
    
    /**
     * TestCPHPConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPConstructL( CStifItemParser& aItem );
    
    /**
     * TestCPHPConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestCPHPPromptL test function for testing the 
     *     Prompt function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPPromptL( CStifItemParser& aItem );
    
    /**
     * TestCPHPPromptTextL test function for testing the 
     *     PromptText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPPromptTextL( CStifItemParser& aItem );
    
    /**
     * TestCPHPSetTextL test function for testing the 
     *     SetTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPSetTextL( CStifItemParser& aItem );
    
    /**
     * TestCPHPSetHeaderImageOwnedL test function for testing the 
     *     SetHeaderImageOwnedL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPSetHeaderImageOwnedL( CStifItemParser& aItem );
    
    /**
     * TestCPHPSetHeaderImageL test function for testing the 
     *     SetHeaderImageL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPSetHeaderImageL( CStifItemParser& aItem );
    
    /**
     * TestCPHPSetHeaderAnimationL test function for testing the 
     *     SetHeaderAnimationL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPSetHeaderAnimationL( CStifItemParser& aItem );
    
    /**
     * TestCPHPSetLayoutL test function for testing the 
     *     SetLayout function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPSetLayoutL( CStifItemParser& aItem );
    
    /**
     * TestCPHPStartAnimationL test function for testing the 
     *     StartAnimationL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPStartAnimationL( CStifItemParser& aItem );
    
    /**
     * TestCPHPCancelAnimationL test function for testing the 
     *     CancelAnimation function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPCancelAnimationL( CStifItemParser& aItem );
    
    /**
     * TestCPHPHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestCPHPHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestCPHPSetSkinFrameIdL test function for testing the 
     *     SetSkinFrameId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPSetSkinFrameIdL( CStifItemParser& aItem );
    
    /**
     * TestCPHPSetSkinFrameCenterIdL test function for testing the 
     *     SetSkinFrameCenterId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPHPSetSkinFrameCenterIdL( CStifItemParser& aItem );
    
private: // Test AknPopupLayout.h
/*                         class AknPopupLayouts                       */
    /**
     * TestCPLHandleSizeChangedL test function for testing the 
     *     HandleSizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLHandleSizeChangedL( CStifItemParser& aItem );
    
    /**
     * TestCPLHandleSizeChangedListBoxL test function for testing the 
     *     HandleSizeChanged function with ListBox
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLHandleSizeChangedListBoxL( CStifItemParser& aItem );
    
    /**
     * TestCPLHandleDrawL test function for testing the 
     *     HandleDraw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLHandleDrawL( CStifItemParser& aItem );
    
    /**
     * TestCPLModifyWindowGraphicForHeadingL test function for testing the 
     *     ModifyWindowGraphicForHeading function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLModifyWindowGraphicForHeadingL( CStifItemParser& aItem );
    
    /**
     * TestCPLModifyWindowGraphicForMessageBoxL test function for testing the 
     *     ModifyWindowGraphicForMessageBox function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLModifyWindowGraphicForMessageBoxL( CStifItemParser& aItem );
    
    /**
     * TestCPLCalcPopupMenuWindowL test function for testing the 
     *     CalcPopupMenuWindow function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLCalcPopupMenuWindowL( CStifItemParser& aItem );
    
    /**
     * TestCPLCalcPopupMenuGraphicWindowL test function for testing the 
     *     CalcPopupMenuGraphicWindow function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLCalcPopupMenuGraphicWindowL( CStifItemParser& aItem );
    
    /**
     * TestCPLCalcPopupMenuGraphicHeadingWindowL test function for testing the 
     *     CalcPopupMenuGraphicHeadingWindow function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLCalcPopupMenuGraphicHeadingWindowL( CStifItemParser& aItem );
    
    /**
     * TestCPLCalcPopupMenuDoubleWindowL test function for testing the 
     *     CalcPopupMenuDoubleWindow function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLCalcPopupMenuDoubleWindowL( CStifItemParser& aItem );
    
    /**
     * TestCPLCalcPopupMenuDoubleLargeGraphicWindowL test function for testing the 
     *     CalcPopupMenuDoubleLargeGraphicWindow function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLCalcPopupMenuDoubleLargeGraphicWindowL( CStifItemParser& aItem );
    
    /**
     * TestCPLCalcPopupSNoteGroupWindowL test function for testing the 
     *     CalcPopupSNoteGroupWindow function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLCalcPopupSNoteGroupWindowL( CStifItemParser& aItem );
    
    /**
     * TestCPLSetupMenuPopupWindowL test function for testing the 
     *     SetupMenuPopupWindow function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLSetupMenuPopupWindowL( CStifItemParser& aItem );
    
    /**
     * TestCPLSetupPopupMenuGraphicWindowL test function for testing the 
     *     SetupPopupMenuGraphicWindow function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLSetupPopupMenuGraphicWindowL( CStifItemParser& aItem );
    
    /**
     * TestCPLSetupPopupMenuGraphicHeadingWindowL test function for testing the 
     *     SetupPopupMenuGraphicHeadingWindow function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLSetupPopupMenuGraphicHeadingWindowL( CStifItemParser& aItem );
    
    /**
     * TestCPLSetupPopupMenuDoubleWindowL test function for testing the 
     *     SetupPopupMenuDoubleWindow function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLSetupPopupMenuDoubleWindowL( CStifItemParser& aItem );
    
    /**
     * TestCPLSetupImageSelectionMenuPopupWindowL test function for testing the 
     *     SetupImageSelectionMenuPopupWindow function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLSetupImageSelectionMenuPopupWindowL( CStifItemParser& aItem );
    
    /**
     * TestCPLSetupPopupSNoteGroupWindowL test function for testing the 
     *     SetupPopupSNoteGroupWindow function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLSetupPopupSNoteGroupWindowL( CStifItemParser& aItem );
    
    /**
     * TestCPLHandleSizeAndPositionOfComponentsL test function for testing the 
     *     HandleSizeAndPositionOfComponents function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLHandleSizeAndPositionOfComponentsL( CStifItemParser& aItem );
    
    /**
     * TestCPLSetupDefaultsL test function for testing the 
     *     SetupDefaults function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLSetupDefaultsL( CStifItemParser& aItem );
    
    /**
     * TestCPLWindowRectL test function for testing the 
     *     WindowRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLWindowRectL( CStifItemParser& aItem );
    
    /**
     * TestCPLMenuRectL test function for testing the 
     *     MenuRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLMenuRectL( CStifItemParser& aItem );
    
    /**
     * TestCPLCheckRangeL test function for testing the 
     *     CheckRange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLCheckRangeL( CStifItemParser& aItem );
    
    /**
     * TestCPLMenuPopupWindowGraphicsL test function for testing the 
     *     MenuPopupWindowGraphics function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPLMenuPopupWindowGraphicsL( CStifItemParser& aItem );
    
private: // Test AknPopupSettingPage.h
/*                         class CAknPopupSettingList                  */
    /**
     * TestCPSLCAknPopupSettingListL test function for testing the 
     *     CAknPopupSettingList function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSLCAknPopupSettingListL( CStifItemParser& aItem );
    
    /**
     * TestCPSLDeconstructorL test function for testing the 
     *     ~CAknPopupSettingList function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSLDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestCPSLConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSLConstructL( CStifItemParser& aItem );
    
    /**
     * TestCPSLSetAllowsUserDefinedEntryL test function for testing the 
     *     SetAllowsUserDefinedEntry function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSLSetAllowsUserDefinedEntryL( CStifItemParser& aItem );
    
    /**
     * TestCPSLSetQueryValueL test function for testing the 
     *     SetQueryValueL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSLSetQueryValueL( CStifItemParser& aItem );
    
    /**
     * TestCPSLSetShowIndicatorsL test function for testing the 
     *     SetShowIndicators function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSLSetShowIndicatorsL( CStifItemParser& aItem );
    
    /**
     * TestCPSLNumLinesL test function for testing the 
     *     NumLines function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSLNumLinesL( CStifItemParser& aItem );
    
    /**
     * TestCPSLSetPopupSettingListObserverL test function for testing the 
     *     SetPopupSettingListObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSLSetPopupSettingListObserverL( CStifItemParser& aItem );
    
    /**
     * TestCPSLConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSLConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestCPSLCreateMenuListL test function for testing the 
     *     CreateMenuListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSLCreateMenuListL( CStifItemParser& aItem );
    
    /**
     * TestCPSLActivateMenuListL test function for testing the 
     *     ActivateMenuListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSLActivateMenuListL( CStifItemParser& aItem );
    
    /**
     * TestCPSLConfigureMenuListL test function for testing the 
     *     ConfigureMenuListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSLConfigureMenuListL( CStifItemParser& aItem );
    
    /**
     * TestCPSLDestroyMenuListL test function for testing the 
     *     DestroyMenuList function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSLDestroyMenuListL( CStifItemParser& aItem );
    
    /**
     * TestCPSLHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSLHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestCPSLHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSLHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestCPSLHandleListBoxEventL test function for testing the 
     *     HandleListBoxEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSLHandleListBoxEventL( CStifItemParser& aItem );
    
/*                         class CAknPopupSettingPage                  */
    /**
     * TestCPSPCAknPopupSettingPageL test function for testing the 
     *     CAknPopupSettingPage function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSPCAknPopupSettingPageL( CStifItemParser& aItem );
    
    /**
     * TestCPSPCAknPopupSettingPageTextL test function for testing the 
     *     CAknPopupSettingPage function with Text
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSPCAknPopupSettingPageTextL( CStifItemParser& aItem );
    
    /**
     * TestCPSPConstructLL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSPConstructLL( CStifItemParser& aItem );
    
    /**
     * TestCPSPListBoxControlL test function for testing the 
     *     ListBoxControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSPListBoxControlL( CStifItemParser& aItem );
    
    /**
     * TestCPSPPopupSettingListBoxL test function for testing the 
     *     PopupSettingListBox function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSPPopupSettingListBoxL( CStifItemParser& aItem );
    
    /**
     * TestCPSPHandlePopupSettingListEventL test function for testing the 
     *     HandlePopupSettingListEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSPHandlePopupSettingListEventL( CStifItemParser& aItem );
    
    /**
     * TestCPSPUpdateQueryValueL test function for testing the 
     *     UpdateQueryValueL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSPUpdateQueryValueL( CStifItemParser& aItem );
    
    /**
     * TestCPSPHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSPHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestCPSPDeconstructorL test function for testing the 
     *     ~CAknPopupSettingPage function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSPDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestCPSPQueryValueL test function for testing the 
     *     QueryValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSPQueryValueL( CStifItemParser& aItem );
    
    /**
     * TestCPSPSelectCurrentItemL test function for testing the 
     *     SelectCurrentItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSPSelectCurrentItemL( CStifItemParser& aItem );
    
    /**
     * TestCPSPWriteInternalStateL test function for testing the 
     *     WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSPWriteInternalStateL( CStifItemParser& aItem );
    
    /**
     * TestCPSPReservedL test function for testing the 
     *     Reserved_2 function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCPSPReservedL( CStifItemParser& aItem );
    };

#endif      // C_TESTSDKPOPUPS_H

// End of File
