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
* Description:  test functions in layout_configuration_api
*
*/



#ifndef C_TESTDOMLAYOUTCFG_H
#define C_TESTDOMLAYOUTCFG_H

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
_LIT( KtestdomlayoutcfgLogPath, "\\logs\\testframework\\testdomlayoutcfg\\" ); 
// Log file
_LIT( KtestdomlayoutcfgLogFile, "testdomlayoutcfg.txt" ); 
_LIT( KtestdomlayoutcfgLogFileWithTitle, "testdomlayoutcfg_[%S].txt" );

/**
*  CTestDomLayoutCfg test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDomLayoutCfg ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDomLayoutCfg* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDomLayoutCfg();

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
    CTestDomLayoutCfg( CTestModuleIf& aTestModuleIf );

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
    * TestTSMPixelsTwipsAndRotationL tests PixelsTwipsAndRotation
    * of CAknLayoutConfig::TScreenMode in AknLayoutConfig.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTSMPixelsTwipsAndRotationL( CStifItemParser& aItem );

    /**
    * TestTSMSoftkeyLocationL tests SoftkeyLocation
    * of CAknLayoutConfig::TScreenMode in AknLayoutConfig.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTSMSoftkeyLocationL( CStifItemParser& aItem );

    /**
    * TestTSMScreenStyleHashL tests ScreenStyleHash
    * of CAknLayoutConfig::TScreenMode in AknLayoutConfig.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTSMScreenStyleHashL( CStifItemParser& aItem );

    /**
    * TestTSMAAtL tests At
    * of CAknLayoutConfig::TScreenModeArray in AknLayoutConfig.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTSMAAtL( CStifItemParser& aItem );

    /**
    * TestTSMAFindL tests Find
    * of CAknLayoutConfig::TScreenModeArray in AknLayoutConfig.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTSMAFindL( CStifItemParser& aItem );

    /**
    * TestTHSStateNumberL tests StateNumber
    * of CAknLayoutConfig::THardwareState in AknLayoutConfig.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTHSStateNumberL( CStifItemParser& aItem );

    /**
    * TestTHSKeyCodeL tests KeyCode
    * of CAknLayoutConfig::THardwareState in AknLayoutConfig.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTHSKeyCodeL( CStifItemParser& aItem );

    /**
    * TestTHSScreenModeL tests ScreenMode
    * of CAknLayoutConfig::THardwareState in AknLayoutConfig.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTHSScreenModeL( CStifItemParser& aItem );

    /**
    * TestTHSAlternateScreenModeL tests AlternateScreenMode
    * of CAknLayoutConfig::THardwareState in AknLayoutConfig.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTHSAlternateScreenModeL( CStifItemParser& aItem );

    /**
    * TestTHSACountL tests Count
    * of CAknLayoutConfig::THardwareStateArray in AknLayoutConfig.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTHSACountL( CStifItemParser& aItem );

    /**
    * TestTHSAAtL tests At
    * of CAknLayoutConfig::THardwareStateArray in AknLayoutConfig.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTHSAAtL( CStifItemParser& aItem );

    /**
    * TestTHSAFindL tests Find
    * of CAknLayoutConfig::THardwareStateArray in AknLayoutConfig.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTHSAFindL( CStifItemParser& aItem );

    /**
    * TestCALCHardwareStatesL tests HardwareStates
    * of CAknLayoutConfig in AknLayoutConfig.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCALCHardwareStatesL( CStifItemParser& aItem );

    /**
    * TestCALCScreenModesL tests ScreenModes
    * of CAknLayoutConfig in AknLayoutConfig.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCALCScreenModesL( CStifItemParser& aItem );


    /**
    * TestCALCConstructorL tests Constructor
    * of CAknLayoutConfig in AknLayoutConfig.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCALCConstructorL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    };

#endif      // C_TESTDOMLAYOUTCFG_H

// End of File
