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
* Description:  test aknpopupform.h
*
*/



#ifndef C_TESTDOMPOPUPFORM_H
#define C_TESTDOMPOPUPFORM_H

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
_LIT( KTestDOMPopupFormLogPath, "\\logs\\testframework\\testdompopupform\\" ); 
// Log file
_LIT( KTestDOMPopupFormLogFile, "testdompopupform.txt" ); 
_LIT( KTestDOMPopupFormLogFileWithTitle, "testdompopupform_[%S].txt" );

/**
*  CTestDOMPopupForm test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDOMPopupForm ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMPopupForm* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMPopupForm();

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
    CTestDOMPopupForm( CTestModuleIf& aTestModuleIf );

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
    * test default constructor method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfDefConsL( CStifItemParser& aItem );

    /**
    * test default constructor method with param.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfDefConsWithPaL( CStifItemParser& aItem );

    /**
    * test NewLC method with param.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfNewLCWithPaL( CStifItemParser& aItem );

    /**
    * test NewL method with param.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfNewLWithPaL( CStifItemParser& aItem );

    /**
    * test NewLC method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfNewLCL( CStifItemParser& aItem );

    /**
    * test NewL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfNewL( CStifItemParser& aItem );

    /**
    * test ConstructL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfConstructL( CStifItemParser& aItem );

    /**
    * test SetTimeout method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfSetTimeoutL( CStifItemParser& aItem );

    /**
    * test SetTone method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfSetToneL( CStifItemParser& aItem );

    /**
    * test SetPopupFormType method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfSetPopupFormTypeL( CStifItemParser& aItem );

    /**
    * test PrepareLC method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfPrepareLCL( CStifItemParser& aItem );

    /**
    * test SetTitleL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfSetTitleL( CStifItemParser& aItem );

    /**
    * test SetTextL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfSetTextL( CStifItemParser& aItem );

    /**
    * test IncrementProgressBarAndDraw method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfIncProBarAndDrawL( CStifItemParser& aItem );

    /**
    * test SetProgressBarAndDraw method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfSetProBarAndDrawL( CStifItemParser& aItem );

    /**
    * test Draw method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfDrawL( CStifItemParser& aItem );

    /**
    * test GetControlByControlType method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfGetControL( CStifItemParser& aItem );

    /**
    * test ProgressInfo method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfProgressInfoL( CStifItemParser& aItem );

    /**
    * test SetImageL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfSetImageL( CStifItemParser& aItem );

    /**
    * test SetCallback method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfSetCallbackL( CStifItemParser& aItem );

    /**
    * test ProcessFinishedL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfProcessFinishedL( CStifItemParser& aItem );

    /**
    * test RunLD method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfRunLDL( CStifItemParser& aItem );

    /**
    * test SetSizeAndPosition method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfSetSizeAndPosL( CStifItemParser& aItem );

    /**
    * test ActivateL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfActivateL( CStifItemParser& aItem );

    /**
    * test OkToExitL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfOkToExitL( CStifItemParser& aItem );

    /**
    * test HandleResourceChange method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfHandleResourceChangeL( CStifItemParser& aItem );

    /**
    * test PlayTone method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfPlayToneL( CStifItemParser& aItem );

    /**
    * test StaticDeleteL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfStaticDeleteL( CStifItemParser& aItem );

    /**
    * test SoundSystem method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfSoundSystemL( CStifItemParser& aItem );

    /**
    * test LayoutAndDraw method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfLayoutAndDrawL( CStifItemParser& aItem );

    /**
    * test PostLayoutDynInitL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfPostLayoutDynInitL( CStifItemParser& aItem );

    /**
    * test SizeChanged method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfSizeChangedL( CStifItemParser& aItem );

    /**
    * test OfferKeyEventL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfOfferKeyEventL( CStifItemParser& aItem );

    /**
    * test HandlePointerEventL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfHandlePointerEventL( CStifItemParser& aItem );

    /**
    * test InsertControlL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfInsertControlL( CStifItemParser& aItem );

    /**
    * test DeleteControl method with TInt type param.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfDeleteControlWithIntL( CStifItemParser& aItem );

    /**
    * test TextIsScrollable method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfTextIsScrollableL( CStifItemParser& aItem );

    /**
    * test Flags method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfFlagsL( CStifItemParser& aItem );

    /**
    * test GetControlByControlTypeL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfGetControlL( CStifItemParser& aItem );

    /**
    * test DeleteControl method with TPopupFormControlType type param.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfDeleteControlWithCtrlL( CStifItemParser& aItem );

    /**
    * test SetWaitAnimationResourceIndex method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfSetWaitIndexL( CStifItemParser& aItem );

    /**
    * test InsertControlL method with TBool param.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestPfInsertControlWithBoolL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTDOMPOPUPFORM_H

// End of File
