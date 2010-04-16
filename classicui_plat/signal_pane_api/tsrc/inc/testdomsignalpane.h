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
* Description:  signal_pane_api
*
*/



#ifndef C_TESTDOMSIGNALPANE_H
#define C_TESTDOMSIGNALPANE_H

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
_LIT( KtestdomsignalpaneLogPath, "\\logs\\testframework\\testdomsignalpane\\" ); 
// Log file
_LIT( KtestdomsignalpaneLogFile, "testdomsignalpane.txt" ); 
_LIT( KtestdomsignalpaneLogFileWithTitle, "testdomsignalpane_[%S].txt" );

/**
*  CTestDOMSignalPane test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
class CAknSignalPane;
NONSHARABLE_CLASS( CTestDOMSignalPane ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMSignalPane* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMSignalPane();

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
    CTestDOMSignalPane( CTestModuleIf& aTestModuleIf );

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
    * TestSPConstructorL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPConstructorL( CStifItemParser& aItem );
    /**
    * TestSPDestructor test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPDestructor( CStifItemParser& aItem );
    /**
    * TestSPConstructFromResourceL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPConstructFromResourceL( CStifItemParser& aItem );
    /**
    * TestSPSetSignalLevel test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPSetSignalLevel( CStifItemParser& aItem );
    /**
    * TestSPShowGprsIcon test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPShowGprsIcon( CStifItemParser& aItem );
    /**
    * TestSPShowCommonPacketDataIcon test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPShowCommonPacketDataIcon( CStifItemParser& aItem );
    /**
    * TestSPShowWcdmaIcon test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPShowWcdmaIcon( CStifItemParser& aItem );
    /**
    * TestSPShowHsdpaIcon test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPShowHsdpaIcon( CStifItemParser& aItem );
    /**
    * TestSPShowCdmaIcon test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPShowCdmaIcon( CStifItemParser& aItem );
    /**
    * TestSPShowEdgeIcon test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPShowEdgeIcon( CStifItemParser& aItem );
    /**
    * TestSPSetNaviPaneBackgroundType test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPSetNaviPaneBackgroundType( CStifItemParser& aItem );
    /**
    * TestSPSizeChangedL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPSizeChangedL( CStifItemParser& aItem );
    /**
    * TestSPPositionChangedL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPPositionChangedL( CStifItemParser& aItem );
    /**
    * TestSPHandleResourceChangeL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPHandleResourceChangeL( CStifItemParser& aItem );
    /**
    * TestSPCountComponentControlsL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPCountComponentControlsL( CStifItemParser& aItem );
    /**
    * TestSPComponentControlL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPComponentControlL( CStifItemParser& aItem );
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * for test
     */
    CAknSignalPane* iSignalPane;
    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTDOMSIGNALPANE_H

// End of File
