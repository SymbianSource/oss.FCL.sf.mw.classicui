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
* Description:  Test AknButton.h
*
*/



#ifndef C_TESTSDKGENERICBUTTON_H
#define C_TESTSDKGENERICBUTTON_H

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
_LIT( KtestsdkgenericbuttonLogPath, "\\logs\\testframework\\testsdkgenericbutton\\" ); 
// Log file
_LIT( KtestsdkgenericbuttonLogFile, "testsdkgenericbutton.txt" ); 
_LIT( KtestsdkgenericbuttonLogFileWithTitle, "testsdkgenericbutton_[%S].txt" );

/**
*  CTestSDKGENERICBUTTON test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKGENERICBUTTON) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKGENERICBUTTON* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKGENERICBUTTON();

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
    CTestSDKGENERICBUTTON( CTestModuleIf& aTestModuleIf );

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
 * CAknButtonState class's public function test
 */
    /**
     * TestGBDestructorStateL test function for testing the Destructor function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBDestructorStateL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBIconL test function for testing the Icon function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBIconL( CStifItemParser& aItem );
    /**
     * TestGBDimmedIconL test function for testing the DimmedIcon function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBDimmedIconL( CStifItemParser& aItem );
    /**
     * TestGBPressedIconL test function for testing the PressedIcon function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBPressedIconL( CStifItemParser& aItem );
    /**
     * TestGBHoverIconL test function for testing the HoverIcon function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBHoverIconL( CStifItemParser& aItem );
    /**
     * TestGBTextL test function for testing the Text function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBTextL( CStifItemParser& aItem );
    /**
     * TestGBHelpTextL test function for testing the HelpText function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBHelpTextL( CStifItemParser& aItem );
    /**
     * TestGBFlagsL test function for testing the Flags function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBFlagsL( CStifItemParser& aItem );
    /**
     * TestGBSetIconL test function for testing the SetIcon function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetIconL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetDimmedIconL test function for testing the SetDimmedIcon function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetDimmedIconL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetPressedIconL test function for testing the SetPressedIcon function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetPressedIconL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetHoverIconL test function for testing the SetHoverIcon function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetHoverIconL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetTextLL test function for testing the SetTextL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetTextLL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetHelpTextLL test function for testing the SetHelpTextL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetHelpTextLL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetFlagsL test function for testing the SetFlags function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetFlagsL( CStifItemParser& /*aItem*/ );
    
/**
 * CAknButtonState class's protected function test
 */
    /**
     * TestGBCAknButtonStateL test function for testing the CAknButtonState function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBCAknButtonStateL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBConstructLfleetL test function for testing the ConstructL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBConstructLfleetL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBConstructLdeepL test function for testing the ConstructL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBConstructLdeepL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBConstructFromResourceLL test function for testing the ConstructFromResourceL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBConstructFromResourceLL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSizeChangedStateL test function for testing the SizeChanged function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSizeChangedStateL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBHasTextL test function for testing the HasText function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBHasTextL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBHasHelpL test function for testing the HasHelp function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBHasHelpL( CStifItemParser& /*aItem*/ );
    
/*
 * CAknButton class's public function
 */
    /**
     * TestGBNewLNullL test function for testing the NewL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBNewLNullL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBNewLCNullL test function for testing the NewLC function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBNewLCNullL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBNewLReaderL test function for testing the NewL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBNewLReaderL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBNewLCReaderL test function for testing the NewLC function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBNewLCReaderL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBNewLIdL test function for testing the NewL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBNewLIdL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBNewLCIdL test function for testing the NewLC function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBNewLCIdL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBNewLComplexL test function for testing the NewL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBNewLComplexL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBNewLCComplexL test function for testing the NewLC function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBNewLCComplexL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBNewLMoreComplexL test function for testing the NewL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBNewLMoreComplexL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBNewLCMoreComplexL test function for testing the NewLC function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBNewLCMoreComplexL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBDestructorL test function for testing the Destructor function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBDestructorL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBActivateLL test function for testing the ActivateL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBActivateLL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBConstructFromResourceLReaderL test function for testing the ConstructFromResourceL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBConstructFromResourceLReaderL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBHandleResourceChangeL test function for testing the HandleResourceChange function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBHandleResourceChangeL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBMinimumSizeL test function for testing the MinimumSize function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBMinimumSizeL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetDimmedL test function for testing the SetDimmed function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetDimmedL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBOfferKeyEventLL test function for testing the OfferKeyEventL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBOfferKeyEventLL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBMakeVisibleL test function for testing the MakeVisible function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBMakeVisibleL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBPrepareForFocusLossLL test function for testing the PrepareForFocusLossL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBPrepareForFocusLossLL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBPrepareForFocusGainLL test function for testing the PrepareForFocusGainL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBPrepareForFocusGainLL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBHandlePointerEventL test function for testing the HandlePointerEventL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBHandlePointerEventL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBPositionChangedL test function for testing the PositionChanged function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBPositionChangedL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBConstructFromResourceLIdL test function for testing the ConstructFromResourceLId function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBConstructFromResourceLIdL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetCurrentStateL test function for testing the SetCurrentState function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetCurrentStateL( CStifItemParser& aItem );
    /**
     * TestGBAddStateLL test function for testing the AddStateL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBAddStateLL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBAddStateLComplexL test function for testing the AddStateLComplex function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBAddStateLComplexL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetButtonFlagsL test function for testing the SetButtonFlags function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetButtonFlagsL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetFrameAndCenterIdsL test function for testing the SetFrameAndCenterIds function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetFrameAndCenterIdsL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetBackgroundIdsL test function for testing the SetBackgroundIds function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetBackgroundIdsL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetTextFontL test function for testing the SetTextFont function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetTextFontL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetTextColorIdsL test function for testing the SetTextColorIds function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetTextColorIdsL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetTextHorizontalAlignmentL test function for testing the SetTextHorizontalAlignment function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetTextHorizontalAlignmentL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetTextVerticalAlignmentL test function for testing the SetTextVerticalAlignment function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetTextVerticalAlignmentL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetTextAndIconAlignmentL test function for testing the SetTextAndIconAlignment function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetTextAndIconAlignmentL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetTextUnderlineStyleL test function for testing the SetTextUnderlineStyle function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetTextUnderlineStyleL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetIconScaleModeL test function for testing the SetIconScaleMode function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetIconScaleModeL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetIconHorizontalAlignmentL test function for testing the SetIconHorizontalAlignment function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetIconHorizontalAlignmentL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetIconVerticalAlignmentL test function for testing the SetIconVerticalAlignment function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetIconVerticalAlignmentL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetHelpNoteTimeoutsL test function for testing the SetHelpNoteTimeouts function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetHelpNoteTimeoutsL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetKeyRepeatIntervalL test function for testing the SetKeyRepeatInterval function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetKeyRepeatIntervalL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetLongPressIntervalL test function for testing the SetLongPressInterval function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetLongPressIntervalL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBStateIndexL test function for testing the StateIndex function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBStateIndexL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBEnablePictographsLL test function for testing the EnablePictographsL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBEnablePictographsLL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBDisablePictographsL test function for testing the DisablePictographs function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBDisablePictographsL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetHighlightRectL test function for testing the SetHighlightRect function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetHighlightRectL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBHighlightRectL test function for testing the HighlightRect function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBHighlightRectL( CStifItemParser& aItem );
    /**
     * TestGBSetTooltipPositionL test function for testing the SetTooltipPosition function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetTooltipPositionL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetRequestExitL test function for testing the SetRequestExit function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetRequestExitL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBIsDimmedL test function for testing the IsDimmed function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBIsDimmedL( CStifItemParser& aItem );
    /**
     * TestGBSetDimmedHelpTextLL test function for testing the SetDimmedHelpTextL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetDimmedHelpTextLL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBStateL test function for testing the State function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBStateL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBStateComplexL test function for testing the State function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBStateComplexL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBButtonFlagsL test function for testing the BButtonFlags function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBButtonFlagsL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetMarginsL test function for testing the SetMargins function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetMarginsL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSetIconSizeL test function for testing the SetIconSize function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSetIconSizeL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBResetStateL test function for testing the ResetState function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBResetStateL( CStifItemParser& /*aItem*/ );
    
/*
 * CAknButton class's protected functon
 */
    /**
     * TestGBConstructorL test function for testing the Constructor function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBConstructorL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBConstructLL test function for testing the ConstructL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBConstructLL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBConstructLComplexL test function for testing the ConstructL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBConstructLComplexL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBConstructLMoreComplexL test function for testing the ConstructL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBConstructLMoreComplexL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBSizeChangedL test function for testing the SizeChanged function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBSizeChangedL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBFocusChangedL test function for testing the FocusChanged function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBFocusChangedL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBExtensionInterfaceL test function for testing the ExtensionInterface function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBExtensionInterfaceL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBChangeStateL test function for testing the ChangeState function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBChangeStateL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBGetCurrentTextL test function for testing the GetCurrentText function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBGetCurrentTextL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBGetCurrentIconL test function for testing the GetCurrentIcon function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBGetCurrentIconL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBShowHelpLL test function for testing the ShowHelpL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBShowHelpLL( CStifItemParser& /*aItem*/ );
    /**
     * TestGBHideHelpL test function for testing the HideHelp function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGBHideHelpL( CStifItemParser& aItem );
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: 

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    // Resource file offset
    TInt iOffset;
    };

#endif      
/*
 * C_TESTSDKGENERICBUTTON_H
 */

//End file


