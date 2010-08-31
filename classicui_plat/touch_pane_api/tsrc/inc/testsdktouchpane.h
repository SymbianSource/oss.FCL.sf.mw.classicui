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
* Description:  Description
*
*/



#ifndef C_TESTSDKTOUCHPANE_H
#define C_TESTSDKTOUCHPANE_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

class CTestSDKTPView;
class CTestSDKTPContainer;

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdktouchpaneLogPath, "\\logs\\testframework\\testsdktouchpane\\" ); 
// Log file
_LIT( KtestsdktouchpaneLogFile, "testsdktouchpane.txt" ); 
_LIT( KtestsdktouchpaneLogFileWithTitle, "testsdktouchpane_[%S].txt" );

/**
*  Ctestsdktouchpane test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKTouchPane) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKTouchPane* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKTouchPane();

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
    CTestSDKTouchPane( CTestModuleIf& aTestModuleIf );

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
    //AknTouchPane.h
    /**
     * TestTPNewL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTPNewL( CStifItemParser& aItem );

    /**
     * TestTPNewLWithResourceL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTPNewLWithResourceL( CStifItemParser& aItem );

    /**
     * TestTPReduceRectL test function for testing the ReduceRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTPReduceRectL( CStifItemParser& aItem );

    /**
     * TestTPSetObserverL test function for testing the SetObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTPSetObserverL( CStifItemParser& aItem );

    /**
     * TestTPSetVisibilityModeL test function for testing the SetVisibilityMode function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTPSetVisibilityModeL( CStifItemParser& aItem );

    /**
     * TestTPAllowInputMethodActivationL test function for testing the AllowInputMethodActivation function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTPAllowInputMethodActivationL( CStifItemParser& aItem );

    /**
     * TestTPSetInputMethodIconActivatedL test function for testing the SetInputMethodIconActivated function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTPSetInputMethodIconActivatedL( CStifItemParser& aItem );

    /**
     * TestTPRefreshL test function for testing the RefreshL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTPRefreshL( CStifItemParser& aItem );

    /**
     * TestTPSetFepPenSupportInterfaceL test function for testing the SetFepPenSupportInterface function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTPSetFepPenSupportInterfaceL( CStifItemParser& aItem );

    /**
     * TestTPCountComponentControlsL test function for testing the CountComponentControls function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTPCountComponentControlsL( CStifItemParser& aItem );

    /**
     * TestTPComponentControl test function for testing the ComponentControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTPComponentControlL( CStifItemParser& aItem );

    /**
     * TestTPDrawL test function for testing the Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTPDrawL( CStifItemParser& aItem );

    /**
     * TestTPHandleControlEventL test function for testing the HandleControlEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTPHandleControlEventL( CStifItemParser& aItem );

    /**
     * TestTPHandleResourceChangeL test function for testing the HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTPHandleResourceChangeL( CStifItemParser& aItem );

    /**
     * TestTPMakeVisibleL test function for testing the MakeVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTPMakeVisibleL( CStifItemParser& aItem );

    /**
     * TestTPOfferKeyEventL test function for testing the OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTPOfferKeyEventL( CStifItemParser& aItem );
    
    /**
      * TestTPHandlePointerEventL test function for testing the HandlePointerEventL function
      * @since S60 5.0
      * @param aItem never used
      * @return Symbian OS error code.
      */
     virtual TInt TestTPHandlePointerEventL( CStifItemParser& aItem );

     /**
      * TestTPPositionChanged test function for testing the PositionChanged function
      * @since S60 5.0
      * @param aItem never used
      * @return Symbian OS error code.
      */
     virtual TInt TestTPPositionChangedL( CStifItemParser& aItem );

     /**
      * TestTPSizeChangedL test function for testing the SizeChanged function
      * @since S60 5.0
      * @param aItem never used
      * @return Symbian OS error code.
      */
     virtual TInt TestTPSizeChangedL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
   
    /**
     * Own, for initialize container
     */
    CTestSDKTPView* iView;
    
    /**
     * Own
     */
    CTestSDKTPContainer* iContainer;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKTOUCHPANE_H

// End of File
