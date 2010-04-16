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
* Description:  test functions in touch_ui_utilities_api
*
*/



#ifndef C_TESTSDKTOUCHUIUTIL_H
#define C_TESTSDKTOUCHUIUTIL_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <aknlongtapdetector.h>
#include <aknpointereventsuppressor.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdktouchuiutilLogPath, "\\logs\\testframework\\testsdktouchuiutil\\" ); 
// Log file
_LIT( KtestsdktouchuiutilLogFile, "testsdktouchuiutil.txt" ); 
_LIT( KtestsdktouchuiutilLogFileWithTitle, "testsdktouchuiutil_[%S].txt" );

/**
*  CTestSDKTouchUiUtil test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKTouchUiUtil ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKTouchUiUtil* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKTouchUiUtil();

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
    CTestSDKTouchUiUtil( CTestModuleIf& aTestModuleIf );

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
    * TestCAknLongTapDetectorNewL test NewL of CAknLongTapDetector
    * in aknlongtapdetector.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknLongTapDetectorNewL( CStifItemParser& aItem );
    
    /**
    * TestCAknLongTapDetectorNewLC test NewLC of CAknLongTapDetector
    * in aknlongtapdetector.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknLongTapDetectorNewLC( CStifItemParser& aItem );
    
    /**
    * TestCAknLongTapDetectorPointerEventL test PointerEventL of CAknLongTapDetector
    * in aknlongtapdetector.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknLongTapDetectorPointerEventL( CStifItemParser& aItem );
    
    /**
    * TestCAknLongTapDetectorSetTimeDelayBeforeAnimationL test SetTimeDelayBeforeAnimation of 
    * CAknLongTapDetector in aknlongtapdetector.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknLongTapDetectorSetTimeDelayBeforeAnimationL( CStifItemParser& aItem );
    
    /**
    * TestCAknLongTapDetectorSetLongTapDelayL test SetLongTapDelay of 
    * CAknLongTapDetector in aknlongtapdetector.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknLongTapDetectorSetLongTapDelayL( CStifItemParser& aItem );
    
    /**
    * TestCAknLongTapDetectorEnableLongTapAnimationL test EnableLongTapAnimation of 
    * CAknLongTapDetector in aknlongtapdetector.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknLongTapDetectorEnableLongTapAnimationL( CStifItemParser& aItem );
    
    /**
    * TestCAknLongTapDetectorIsAnimationRunningL test IsAnimationRunning of 
    * CAknLongTapDetector in aknlongtapdetector.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknLongTapDetectorIsAnimationRunningL( CStifItemParser& aItem );
    
    /**
    * TestCAknLongTapDetectorCancelAnimationL test CancelAnimationL of 
    * CAknLongTapDetector in aknlongtapdetector.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknLongTapDetectorCancelAnimationL( CStifItemParser& aItem );
    
    /**
    * TestCAknPointerSuppressorNewL test NewL of 
    * CAknPointerEventSuppressor in aknpointereventsuppressor.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknPointerSuppressorNewL( CStifItemParser& aItem );
    
    /**
    * TestCAknPointerSuppressorSuppressPointerEventL test SuppressPointerEvent of 
    * CAknPointerEventSuppressor in aknpointereventsuppressor.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknPointerSuppressorSuppressPointerEventL( CStifItemParser& aItem );
    
    /**
    * TestCAknPointerSuppressorSetMaxTapDurationL test SetMaxTapDuration of 
    * CAknPointerEventSuppressor in aknpointereventsuppressor.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknPointerSuppressorSetMaxTapDurationL( CStifItemParser& aItem );
    
    /**
    * TestCAknPointerSuppressorSetMaxTapMoveL test SetMaxTapMove of 
    * CAknPointerEventSuppressor in aknpointereventsuppressor.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknPointerSuppressorSetMaxTapMoveL( CStifItemParser& aItem );
    
    /**
    * TestCAknPointerSuppressorSetMinInterDragIntervalL test SetMinInterDragInterval of 
    * CAknPointerEventSuppressor in aknpointereventsuppressor.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknPointerSuppressorSetMinInterDragIntervalL( CStifItemParser& aItem );
    
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    };

#endif      // C_TESTSDKTOUCHUIUTIL_H

// End of File
