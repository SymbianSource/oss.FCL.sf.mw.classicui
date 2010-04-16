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
* Description:  slider_api
*
*/



#ifndef C_TESTSDKSLIDER_H
#define C_TESTSDKSLIDER_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <coecntrl.h>
#include <aknslider.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdksliderLogPath, "\\logs\\testframework\\testsdkslider\\" ); 
// Log file
_LIT( KtestsdksliderLogFile, "testsdkslider.txt" ); 
_LIT( KtestsdksliderLogFileWithTitle, "testsdkslider_[%S].txt" );

/**
*  CTestSDKSlider test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
//test protected methods
class CAknSlider;
class CSliderContainer;
class CSliderView;


NONSHARABLE_CLASS(CTestSDKSlider) : public CScriptBase 
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKSlider* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKSlider();
    

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
    CTestSDKSlider( CTestModuleIf& aTestModuleIf );

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
    /**
    * ConstructorL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderConstructorL( CStifItemParser& aItem );
    /**
    * Delete test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderDelete( CStifItemParser& aItem );
    /**
    * SetValueL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderSetValueL( CStifItemParser& aItem );

    /**
    * Value test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderValue( CStifItemParser& aItem );
    /**
    * SetRange test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderSetRange( CStifItemParser& aItem );
    /**
    * GetRange test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderGetRange( CStifItemParser& aItem );
    /**
    * SetStepSize test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderSetStepSize( CStifItemParser& aItem );
    /**
    * SetMinimumTextL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderSetMinimumTextL( CStifItemParser& aItem );
    /**
    * SetMaximumTextL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderSetMaximumTextL( CStifItemParser& aItem );
    /**
    * SetDecimalPlaces test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderSetDecimalPlaces( CStifItemParser& aItem );
    /**
    * DecimalPlaces test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderDecimalPlaces( CStifItemParser& aItem );
    /**
    * SetGraphicsL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderSetGraphicsL( CStifItemParser& aItem );
    /**
    * UseDefaultGraphics test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderUseDefaultGraphics( CStifItemParser& aItem );
    /**
    * UsesDefaultGraphicsReturnTBool test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderUsesDefaultGraphicsReturnTBool( CStifItemParser& aItem );
    /**
    * SetPositionIndicators test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderSetPositionIndicators( CStifItemParser& aItem );
    /**
    * PositionIndicators test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderPositionIndicators( CStifItemParser& aItem );
    /**
    * Orientation test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderOrientation( CStifItemParser& aItem );
    /**
    * SetTicksEnabled test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderSetTicksEnabled( CStifItemParser& aItem );
    /**
    * TicksEnabled test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderTicksEnabled( CStifItemParser& aItem );
    /**
    * SetTickInterval test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderSetTickInterval( CStifItemParser& aItem );
    /**
    * TickInterval test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderTickInterval( CStifItemParser& aItem );
    /**
    * CreateBitmapL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderCreateBitmapL( CStifItemParser& aItem );
    /**
    * CreateBitmapWithValuL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderCreateBitmapWithValuL( CStifItemParser& aItem );
    /**
    * CreateSetStyleListBoxIconL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderCreateSetStyleListBoxIconL( CStifItemParser& aItem );
    /**
    * CreateSetStyleListBoxIconWithValuL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderCreateSetStyleListBoxIconWithValuL( CStifItemParser& aItem );
    /**
    * EnableDragL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderEnableDragL( CStifItemParser& aItem );
    /**
    * ConstructFromResourceL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderConstructFromResourceL( CStifItemParser& aItem );
    /**
    * ConstructFromResourceWithControlL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderConstructFromResourceWithControlL( CStifItemParser& aItem );
    /**
    * HandleResourceChange test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderHandleResourceChange( CStifItemParser& aItem );
    /**
    * NumberOfLines test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderNumberOfLines( CStifItemParser& aItem );
    /**
    * CreateValueTextInHBufCL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderCreateValueTextInHBufCL( CStifItemParser& aItem );
    /**
    * CountComponentControls test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderCountComponentControlsL( CStifItemParser& aItem );
    /**
    * ComponentControl test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderComponentControlL( CStifItemParser& aItem );
    /**
    * HandlePointerEventL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderHandlePointerEventL( CStifItemParser& aItem );
    /**
    * SetValueTextL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderSetValueTextL( CStifItemParser& aItem );
    /**
    * FocusChanged test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSliderFocusChanged( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    //for test Aknslider.h
    CAknSlider* iSlider;
    CSliderContainer* iSliderContainer;
    CSliderView *iSliderView;
    
    // Resource file offset
    TInt iOffset;


    };

#endif      // C_TESTSDKSLIDER_H

// End of File
