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
* Description:  For test extended utilities api modules
*
*/



#ifndef C_TESTDOMEXTENDEDUTLTS_H
#define C_TESTDOMEXTENDEDUTLTS_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <akndateformatutils.h>
#include <biditext.h>
#include <e32std.h>
#include <aknlinebreaker.h>
#include <aknsettingcache.h>
#include <aknenv.h> 

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdomextendedutltsLogPath, "\\logs\\testframework\\testdomextendedutlts\\" ); 
// Log file
_LIT( KtestdomextendedutltsLogFile, "testdomextendedutlts.txt" ); 
_LIT( KtestdomextendedutltsLogFileWithTitle, "testdomextendedutlts_[%S].txt" );

class AknDateFormatUtils;
class TAknLineBreaker;
class CAknSettingCache;
class MAknSettingCacheUpdatePlugin;
/**
*  CTestDOMExtendedUtlts test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDOMExtendedUtlts ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMExtendedUtlts* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMExtendedUtlts();

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
    CTestDOMExtendedUtlts( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

	// [TestMethods]
private:// for testing the akndateformatutils.h
	
    /**
    * TestDFUMapSymbianDateFormatToVisualDateFormat test method for testing the MapSymbianDateFormatToVisualDateFormat method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDFUMapSymbianDateFormatToVisualDateFormat( CStifItemParser& aItem );
    /**
    * TestDFUMapVisualDateFormatToSymbianDateForma test method for testing the MapVisualDateFormatToSymbianDateForma method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDFUMapVisualDateFormatToSymbianDateFormat( CStifItemParser& aItem );
    // for testing the aknlinebreaker.h
    /**
    * TestLineBrkerIsSpecialVaritChar test method for testing the IsSpecialVariantChar method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLineBrkerIsSpecialVaritChar( CStifItemParser& aItem );
    // for testing the aknsettingcache.h
    /**
    * TestSetCacheInputLanguage test method for testing the InputLanguage method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetCacheInputLanguage( CStifItemParser& aItem );
    /**
    * TestSetCacheLayoutId test method for testing the LayoutId method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetCacheLayoutId( CStifItemParser& aItem );
    /**
    * TestSetCacheHardwareLayoutState test method for testing the HardwareLayoutState method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetCacheHardwareLayoutState( CStifItemParser& aItem );
    /**
    * TestSetCachePreferredOrientation test method for testing the PreferredOrientation method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetCachePreferredOrientation( CStifItemParser& aItem );
    /**
    * TestSetCacheTestSetCacheGlobalUiZoom test method for testing the GlobalUiZoom method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetCacheGlobalUiZoom( CStifItemParser& aItem );
    /**
    * TestSetCacheUpdate test method for testing the Update( TInt aEventId ) method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetCacheUpdate( CStifItemParser& aItem );
    /**
    * TestSetCacheRegisterPluginL test method for testing the RegisterPluginL(MAknSettingCacheUpdatePlugin* aPlugin) method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetCacheRegisterPluginL( CStifItemParser& aItem );
    /**
    * TestSetCacheDeRegisterPlugin test method for testing the DeRegisterPlugin(MAknSettingCacheUpdatePlugin* aPlugin) method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetCacheDeRegisterPlugin( CStifItemParser& aItem );
    /**
    * TestSetCachePluginValue test method for testing the PluginValue(TInt aEventId, TInt& aValue) method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetCachePluginValue( CStifItemParser& aItem );
    /**
    * TestSetCacheTransparencyEnabled test method for testing the TransparencyEnabled() method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetCacheTransparencyEnabled( CStifItemParser& aItem );  

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    };

#endif      // C_TESTDOMEXTENDEDUTLTS_H

// End of File
