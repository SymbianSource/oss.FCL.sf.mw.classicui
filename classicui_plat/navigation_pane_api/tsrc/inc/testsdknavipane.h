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
* Description:  test case for navigation_pane_api module
*
*/



#ifndef C_TESTSDKNAVIPANE_H
#define C_TESTSDKNAVIPANE_H

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
_LIT( KtestsdknavipaneLogPath, "\\logs\\testframework\\testsdknavipane\\" ); 
// Log file
_LIT( KtestsdknavipaneLogFile, "testsdknavipane.txt" ); 
_LIT( KtestsdknavipaneLogFileWithTitle, "testsdknavipane_[%S].txt" );

//Function Declaration
class CAknNavigationControlContainer;
class CAknNavigationControlContainerExt;
class CAknNavigationDecorator;
class CTestSDKNavipaneNaviDeExt;
class CAknNaviLabel;
class CTestSDKNavipaneNaviLblExt;
/**
*  Ctestsdknavipane test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKNaviPane) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKNaviPane* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKNaviPane();

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
    CTestSDKNaviPane( CTestModuleIf& aTestModuleIf );

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
    
private:
    
    //test aknnavi.h
    /**
    * TestNaviCAknNavigationControlContainerL test method for testing the 
    * construct function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviCAknNavigationControlContainerL( CStifItemParser& aItem );

    /**
    * TestNaviDelete test method for testing the 
    * Deconstruct function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDelete( CStifItemParser& aItem );

    /**
    * TestNaviConstructL test method for testing the 
    * seco-construct function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviConstructL( CStifItemParser& aItem );

    /**
    * TestNaviConstructFromResourceL test method for testing the 
    * ConstructFromResourceL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviConstructFromResourceL( CStifItemParser& aItem );

    /**
    * TestNaviConstructNavigationDecoratorFromResourceL test method for testing the 
    * ConstructNavigationDecoratorFromResourceL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviConstructNavigationDecoratorFromResourceL( CStifItemParser& aItem );

    /**
    * TestNaviCreateTabGroupL test method for testing the 
    * CreateTabGroupL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviCreateTabGroupL( CStifItemParser& aItem );

    /**
    * TestNaviCreateTabGroupLWithObserver test method for testing the 
    * CreateTabGroupL function with the Observer param.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviCreateTabGroupLWithObserverL( CStifItemParser& aItem );

    /**
    * TestNaviCreateTabGroupLWithObserver test method for testing the 
    * CreateTabGroupL function with the resourcereader param.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviCreateTabGroupLWithResL( CStifItemParser& aItem );

    /**
    * TestNaviCreateTabGroupLWithResAndObserver test method for testing the 
    * CreateTabGroupL function with the resourcereader and observer param.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviCreateTabGroupLWithResAndObserverL( CStifItemParser& aItem );

    /**
    * TestNaviCreateNavigationLabelL test method for testing the 
    * CreateNavigationLabelL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviCreateNavigationLabelL( CStifItemParser& aItem );

    /**
    * TestNaviCreateNavigationLabelL test method for testing the 
    * CreateNavigationLabelL function with the resource param.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviCreateNavigationLabelLWithResL( CStifItemParser& aItem );

    /**
    * TestNaviCreateNavigationImageL test method for testing the 
    * CreateNavigationImageL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviCreateNavigationImageL( CStifItemParser& aItem );

    /**
    * TestNaviCreateNavigationImageLWithResL test method for testing the 
    * CreateNavigationLabelL function with the resource param.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviCreateNavigationImageLWithResL( CStifItemParser& aItem );
    /**
    * TestNaviCreateMessageLabelL test method for testing the 
    * CreateMessageLabelL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviCreateMessageLabelL( CStifItemParser& aItem );

    /**
    * TestNaviCreateMessageLabelLWithResL test method for testing the 
    * CreateMessageLabelL function with the resource param.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviCreateMessageLabelLWithResL( CStifItemParser& aItem );

    /**
    * TestNaviCreateVolumeIndicatorL test method for testing the 
    * CreateVolumeIndicatorL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviCreateVolumeIndicatorL( CStifItemParser& aItem );

    /**
    * TestNaviCreateEditorIndicatorContainerL test method for testing the 
    * CreateEditorIndicatorContainerL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviCreateEditorIndicatorContainerL( CStifItemParser& aItem );

    /**
    * TestNaviPushDefaultL test method for testing the 
    * PushDefaultL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviPushDefaultL( CStifItemParser& aItem );

    /**
    * TestNaviPushL test method for testing the 
    * PushL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviPushL( CStifItemParser& aItem );

    /**
    * TestNaviPop test method for testing the 
    * Pop function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviPop( CStifItemParser& aItem );

    /**
    * TestNaviPopWithControl test method for testing the 
    * Pop function with the control param.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviPopWithControl( CStifItemParser& aItem );

    /**
    * TestNaviTop test method for testing the 
    * Top function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviTopL( CStifItemParser& aItem );

    /**
    * TestNaviTopWithBool test method for testing the 
    * Top function with a TBool param.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviTopWithBoolL( CStifItemParser& aItem );

    /**
    * TestNaviReplaceL test method for testing the 
    * ReplaceL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviReplaceL( CStifItemParser& aItem );

    /**
    * TestNaviResourceDecorator test method for testing the 
    * ResourceDecorator function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviResourceDecorator( CStifItemParser& aItem );

    /**
    * TestNaviSetPreferredNaviDecoratorLayoutStyle test method for testing the 
    * SetPreferredNaviDecoratorLayoutStyle function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviSetPreferredNaviDecoratorLayoutStyle( CStifItemParser& aItem );
    
    /**
    * TestNaviColorScheme test method for testing the 
    * ColorScheme function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviColorScheme( CStifItemParser& aItem );
    
    /**
    * TestNaviHandlePointerEventL test method for testing the 
    * HandlePointerEventL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviHandlePointerEventL( CStifItemParser& aItem );
    
    /**
    * TestNaviSizeChangedL test method for testing the 
    * SizeChanged function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviSizeChangedL( CStifItemParser& aItem );
    
    /**
    * TestNaviHandleResourceChange test method for testing the 
    * HandleResourceChange function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
    * TestNaviCountComponentControlsL test method for testing the 
    * CountComponentControls function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviCountComponentControlsL( CStifItemParser& aItem );
    
    /**
    * TestNaviComponentControlL test method for testing the 
    * ComponentControl function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviComponentControlL( CStifItemParser& aItem );
    
    /**
    * TestNaviHandleControlEventL test method for testing the 
    * HandleControlEventL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviHandleControlEventL( CStifItemParser& aItem );
    
public: //aknnavide.h

    
    /**
    * TestNaviDeNewL test method for testing the 
    * NewL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeNewL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeDelete test method for testing the 
    * Delete function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeDelete( CStifItemParser& aItem );

    
    /**
    * TestNaviDeDecoratedControlL test method for testing the 
    * DecoratedControl function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeDecoratedControlL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeMakeScrollButtonVisibleL test method for testing the 
    * MakeScrollButtonVisible function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeMakeScrollButtonVisibleL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeScrollButtonVisibleL test method for testing the 
    * ScrollButtonVisible function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeScrollButtonVisibleL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeSetScrollButtonDimmedL test method for testing the 
    * SetScrollButtonDimmed function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeSetScrollButtonDimmedL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeIsScrollButtonDimmedL test method for testing the 
    * IsScrollButtonDimmed function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeIsScrollButtonDimmedL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeSetControlTypeL test method for testing the 
    * SetControlType function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeSetControlTypeL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeControlTypeL test method for testing the 
    * ControlType function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeControlTypeL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeSetNaviDecoratorObserverL test method for testing the 
    * SetNaviDecoratorObserver function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeSetNaviDecoratorObserverL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeHandlePointerEventL test method for testing the 
    * HandlePointerEventL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeHandlePointerEventL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeSetNaviControlLayoutStyleL test method for testing the 
    * SetNaviControlLayoutStyle function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeSetNaviControlLayoutStyleL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeNaviControlLayoutStyle test method for testing the 
    * NaviControlLayoutStyle function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeNaviControlLayoutStyleL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeNaviControlLayoutStyleSupportedL test method for testing the 
    * NaviControlLayoutStyleSupported function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeNaviControlLayoutStyleSupportedL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeSetNaviControlLayoutModeL test method for testing the 
    * SetNaviControlLayoutMode function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeSetNaviControlLayoutModeL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeNaviControlLayoutModeL test method for testing the 
    * NaviControlLayoutMode function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeNaviControlLayoutModeL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeHandleResourceChange test method for testing the 
    * HandleResourceChange function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeHandleResourceChangeL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeSizeChangedL test method for testing the 
    * SizeChanged function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeSizeChangedL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeCountComponentControls test method for testing the 
    * CountComponentControls function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeCountComponentControlsL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeComponentControl test method for testing the 
    * ComponentControl function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeComponentControlL( CStifItemParser& aItem );

    
    /**
    * TestNaviDeHandleControlEventL test method for testing the 
    * HandleControlEventL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviDeHandleControlEventL( CStifItemParser& aItem );

public: //aknnavilabel.h
    
    /**
    * TestNaviLblCAknNaviLabelL test method for testing the 
    * CAknNaviLabel function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviLblCAknNaviLabelL( CStifItemParser& aItem );  
    
    /**
    * TestNaviLblDelete test method for testing the 
    * Destructor function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviLblDelete( CStifItemParser& aItem );   
    
    /**
    * TestNaviLblSetNaviLabelType test method for testing the 
    * SetNaviLabelType function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviLblSetNaviLabelType( CStifItemParser& aItem );    
    
    /**
    * TestNaviLblNaviLabelType test method for testing the 
    * NaviLabelType function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviLblNaviLabelType( CStifItemParser& aItem );    
    
    /**
    * TestNaviLblSetTextL test method for testing the 
    * SetTextL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviLblSetTextL( CStifItemParser& aItem );    
    
    /**
    * TestNaviLblHandlePointerEventL test method for testing the 
    * HandlePointerEventL function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviLblHandlePointerEventL( CStifItemParser& aItem );    
    
    /**
    * TestNaviLblSizeChangedL test method for testing the 
    * SizeChanged function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviLblSizeChangedL( CStifItemParser& aItem );        
    
    /**
    * TestNaviLblDrawL test method for testing the 
    * Draw function.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNaviLblDrawL( CStifItemParser& aItem );   
	

  
	
public: //
	
	
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    

    //Own : test functions in aknnavi.h
    CAknNavigationControlContainer* iNaviContainer;
    CAknNavigationControlContainerExt* iNaviContainerExt;
    
    //Own : test functions in aknnavide.h
    CAknNavigationDecorator* iNaviContainerDe;
    CTestSDKNavipaneNaviDeExt* iNaviContainerDeExt;
    
    //Own : test functions in aknnavilbl.h
    CAknNaviLabel* iNaviLbl;
    CTestSDKNavipaneNaviLblExt* iNaviLblExt;
    
    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKNAVIPANE_H

// End of File
