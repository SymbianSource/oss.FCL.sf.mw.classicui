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
* Description:  for testing the indicators api module
*
*/



#ifndef C_TESTSDKINDICATORS_H
#define C_TESTSDKINDICATORS_H

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
_LIT( KtestsdkindicatorsLogPath, "\\logs\\testframework\\testsdkindicators\\" ); 
// Log file
_LIT( KtestsdkindicatorsLogFile, "testsdkindicators.txt" ); 
_LIT( KtestsdkindicatorsLogFileWithTitle, "testsdkindicators_[%S].txt" );

class CAknIndicatorContainer;
/**
*  Ctestsdkindicators test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKIndicators ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKIndicators* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKIndicators();

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
    CTestSDKIndicators( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

    	// [TestMethods]
private:// for testing the aknindicatorcontainer.h
	
    /**
    * TestIndiCntnerCAknIndicatorContainer test method for testing the CAknIndicatorContainer method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerCAknIndicatorContainerL( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerDelete test method for testing the destructor method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerDelete( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerConstructL test method for testing the ConstructL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerConstructL( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerSetIndicatorState test method for testing the SetIndicatorState method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerSetIndicatorState( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerIndicatorState test method for testing the CAknIndicatorContainer method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerIndicatorState( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerSetIndicatorValueL test method for testing the SetIndicatorValueL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerSetIndicatorValueL( CStifItemParser& aItem );
	
	
    /**
    * TestIndiCntnerSetIncallBubbleFlags test method for testing the SetIncallBubbleFlags method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerSetIncallBubbleFlags( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerConstructFromResourceL test method for testing the CAknIndicatorContainer method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerConstructFromResourceL( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerIndicatorContext test method for testing the IndicatorContext method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerIndicatorContext( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerHandleStatusPaneSizeChange test method for testing the HandleStatusPaneSizeChange method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerHandleStatusPaneSizeChange( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerHandlePointerEventL test method for testing the HandlePointerEventL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerHandlePointerEventL( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerSetIndicatorValue test method for testing the SetIndicatorValue method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerSetIndicatorValue( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerSetIncallBubbleAllowedInIdle test method for testing the SetIncallBubbleAllowedInIdle method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerSetIncallBubbleAllowedInIdle( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerSetIncallBubbleAllowedInUsual test method for testing the SetIncallBubbleAllowedInUsual method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerSetIncallBubbleAllowedInUsual( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerSetIndicatorObserver test method for testing the SetIndicatorObserver method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerSetIndicatorObserverL( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerCreateIndicatorFromResourceL test method for testing the CreateIndicatorFromResourceL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerCreateIndicatorFromResourceL( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerReplaceIndicatorIconL test method for testing the ReplaceIndicatorIconL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerReplaceIndicatorIconL( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerHandleResourceChange test method for testing the HandleResourceChange method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerHandleResourceChangeL( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerSizeChanged test method for testing the SizeChanged method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerSizeChangedL( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerPositionChanged test method for testing the PositionChanged method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerPositionChangedL( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerCountComponentControls test method for testing the CountComponentControls method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerCountComponentControlsL( CStifItemParser& aItem );
	
    /**
    * TestIndiCntnerComponentControl test method for testing the ComponentControl method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIndiCntnerComponentControlL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    //Own: Aknindicatorcontainer.h
    CAknIndicatorContainer* iIndicatorContn;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKINDICATORS_H

// End of File
