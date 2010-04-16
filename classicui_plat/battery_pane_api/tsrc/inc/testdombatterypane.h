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
* Description:  battery_pane_api
*
*/



#ifndef C_TESTDOMBATTERYPANE_H
#define C_TESTDOMBATTERYPANE_H

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
_LIT( KtestdombatterypaneLogPath, "\\logs\\testframework\\testdombatterypane\\" ); 
// Log file
_LIT( KtestdombatterypaneLogFile, "testdombatterypane.txt" ); 
_LIT( KtestdombatterypaneLogFileWithTitle, "testdombatterypane_[%S].txt" );

/**
*  CTestDOMBatteryPane test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
class CAknBatteryPane;
NONSHARABLE_CLASS( CTestDOMBatteryPane ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMBatteryPane* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMBatteryPane();
    
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
    CTestDOMBatteryPane( CTestModuleIf& aTestModuleIf );

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
    * ConstructorL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDOMBPConstructorL( CStifItemParser& /*aItem*/ );
    /**
    * Destructor test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDOMBPDestructor( CStifItemParser& /*aItem*/ );
    /**
    * ConstructFromResourceL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDOMBPConstructFromResourceL( CStifItemParser& /*aItem*/ );
    /**
    * SetBatteryLevel test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDOMBPSetBatteryLevel( CStifItemParser& /*aItem*/ );
    /**
    * SizeChanged test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDOMBPSizeChangedL( CStifItemParser& /*aItem*/ );
    /**
    * PositionChanged test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDOMBPPositionChangedL( CStifItemParser& /*aItem*/ );
    /**
    * HandleResourceChange test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDOMBPHandleResourceChangeL( CStifItemParser& /*aItem*/ );    
    /**
    * CountComponentControls test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDOMBPCountComponentControlsL( CStifItemParser& /*aItem*/ );    
    /**
    * ComponentControl test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDOMBPComponentControlL( CStifItemParser& /*aItem*/ );    

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
//for test
    CAknBatteryPane *iBatteryPane;
    // Resource file offset
    TInt iOffset;

    };

#endif      // C_TESTDOMBATTERYPANE_H

// End of File
