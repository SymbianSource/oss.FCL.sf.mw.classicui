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
* Description:  text aknmarqueecontrol.h
*
*/



#ifndef C_TESTDOMTEXTSCROLLER_H
#define C_TESTDOMTEXTSCROLLER_H

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
_LIT( KtestdomtextscrollerLogPath, "\\logs\\testframework\\testdomtextscroller\\" ); 
// Log file
_LIT( KtestdomtextscrollerLogFile, "testdomtextscroller.txt" ); 
_LIT( KtestdomtextscrollerLogFileWithTitle, "testdomtextscroller_[%S].txt" );

/**
*  CTestDOMTextScroller test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDOMTextScroller ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMTextScroller* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMTextScroller();

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
    CTestDOMTextScroller( CTestModuleIf& aTestModuleIf );

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
    * test NewL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestNewL( CStifItemParser& aItem );

    /**
    * test NewLC method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestNewLCL( CStifItemParser& aItem );

    /**
    * test SetRedrawCallBack method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetRedrawCallBackL( CStifItemParser& aItem );

    /**
    * test DrawText method.
    * @since S60 5.0
    * @param aItem referred to different params.
    * @return Symbian OS error code.
    */
    virtual TInt TestDrawTextL( CStifItemParser& aItem );

    /**
    * test UseLogicalToVisualConversion method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestUseLogicalToVisualConversionL( CStifItemParser& aItem );

    /**
    * test Start method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestStartL( CStifItemParser& aItem );

    /**
    * test Stop method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestStopL( CStifItemParser& aItem );

    /**
    * test Reset method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestResetL( CStifItemParser& aItem );

    /**
    * test IsMarqueeOn method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestIsMarqueeOnL( CStifItemParser& aItem );

    /**
    * test SetSpeedInPixels method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetSpeedInPixelsL( CStifItemParser& aItem );

    /**
    * test SetDelay method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetDelayL( CStifItemParser& aItem );

    /**
    * test SetInterval method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetIntervalL( CStifItemParser& aItem );

    /**
    * test SetLoops method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetLoopsL( CStifItemParser& aItem );

    /**
    * test EnableMarquee method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEnableMarqueeL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };

#endif      // C_TESTDOMTEXTSCROLLER_H

// End of File
