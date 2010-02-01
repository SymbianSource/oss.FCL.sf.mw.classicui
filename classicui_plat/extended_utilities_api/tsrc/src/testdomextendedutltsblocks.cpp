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



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akndateformatutils.h>
#include <biditext.h>
#include <e32std.h>
#include <e32const.h>
#include <aknlinebreaker.h>
#include <aknsettingcache.h>
#include <aknenv.h> 

#include "testdomextendedutlts.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMExtendedUtlts::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMExtendedUtlts::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestDFUMapSymbianDateFormatToVisualDateFormat", 
        		CTestDOMExtendedUtlts::TestDFUMapSymbianDateFormatToVisualDateFormat ),
        ENTRY( "TestDFUMapVisualDateFormatToSymbianDateFormat", 
        		CTestDOMExtendedUtlts::TestDFUMapVisualDateFormatToSymbianDateFormat ),
        ENTRY( "TestLineBrkerIsSpecialVaritChar", 
        		CTestDOMExtendedUtlts::TestLineBrkerIsSpecialVaritChar ),
        ENTRY( "TestSetCacheInputLanguage", 
        		CTestDOMExtendedUtlts::TestSetCacheInputLanguage ),
        ENTRY( "TestSetCacheLayoutId", 
        		CTestDOMExtendedUtlts::TestSetCacheLayoutId ),
        ENTRY( "TestSetCacheHardwareLayoutState", 
        		CTestDOMExtendedUtlts::TestSetCacheHardwareLayoutState ),
        ENTRY( "TestSetCachePreferredOrientation", 
        		CTestDOMExtendedUtlts::TestSetCachePreferredOrientation ),
        ENTRY( "TestSetCacheGlobalUiZoom", 
        		CTestDOMExtendedUtlts::TestSetCacheGlobalUiZoom ),
        ENTRY( "TestSetCacheUpdate", 
        		CTestDOMExtendedUtlts::TestSetCacheUpdate ),
        ENTRY( "TestSetCacheRegisterPluginL", 
        		CTestDOMExtendedUtlts::TestSetCacheRegisterPluginL ),
        ENTRY( "TestSetCacheDeRegisterPlugin", 
        		CTestDOMExtendedUtlts::TestSetCacheDeRegisterPlugin ),
        ENTRY( "TestSetCachePluginValue", 
        		CTestDOMExtendedUtlts::TestSetCachePluginValue ),
        ENTRY( "TestSetCacheTransparencyEnabled", 
        		CTestDOMExtendedUtlts::TestSetCacheTransparencyEnabled ),
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }
// -----------------------------------------------------------------------------
// CTestDOMExtendedUtlts::TestDFUMapSymbianDateFormatToVisualDateFormat
// -----------------------------------------------------------------------------
//
TInt CTestDOMExtendedUtlts::TestDFUMapSymbianDateFormatToVisualDateFormat( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomextendedutlts, "testdomextendedutlts" );
    _LIT( KTestDFUMapSymbianDateFormatToVisualDateFormat, "In TestDFUMapSymbianDateFormatToVisualDateFormat" );
    TestModuleIf().Printf( 0, Ktestdomextendedutlts, KTestDFUMapSymbianDateFormatToVisualDateFormat );
    // Print to log file
    iLog->Log( KTestDFUMapSymbianDateFormatToVisualDateFormat );

    TInt err = KErrNone;
    
    TLanguage forceLanguage = { ELangEnglish };
    TAknVisualDateFormat visualDateFormat = AknDateFormatUtils::MapSymbianDateFormatToVisualDateFormat( 
    EDateAmerican, &forceLanguage );  
    
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMExtendedUtlts::TestDFUMapVisualDateFormatToSymbianDateFormat
// -----------------------------------------------------------------------------
//
TInt CTestDOMExtendedUtlts::TestDFUMapVisualDateFormatToSymbianDateFormat( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomextendedutlts, "testdomextendedutlts" );
    _LIT( KTestDFUMapVisualDateFormatToSymbianDateFormat, "In TestDFUMapVisualDateFormatToSymbianDateFormat" );
    TestModuleIf().Printf( 0, Ktestdomextendedutlts, KTestDFUMapVisualDateFormatToSymbianDateFormat );
    // Print to log file
    iLog->Log( KTestDFUMapVisualDateFormatToSymbianDateFormat );

    TInt err = KErrNone;
    
    TLanguage forceLanguage = { ELangEnglish };
    TAknVisualDateFormat visualDateFormat = 
    AknDateFormatUtils::MapSymbianDateFormatToVisualDateFormat( 
    EDateAmerican, &forceLanguage );
    
    TDateFormat dateFormat = 
    AknDateFormatUtils::MapVisualDateFormatToSymbianDateFormat( 
    visualDateFormat, &forceLanguage );
    
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMExtendedUtlts::TestLineBrkerIsSpecialVaritChar
// -----------------------------------------------------------------------------
//
TInt CTestDOMExtendedUtlts::TestLineBrkerIsSpecialVaritChar( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomextendedutlts, "testdomextendedutlts" );
    _LIT( KTestLineBrkerIsSpecialVaritChar, "In TestLineBrkerLineBreakClass" );
    TestModuleIf().Printf( 0, Ktestdomextendedutlts, KTestLineBrkerIsSpecialVaritChar );
    // Print to log file
    iLog->Log( KTestLineBrkerIsSpecialVaritChar );

    TInt err = KErrNone;
    
    TUint code=0x003C;
    TUint startCode=0x003A;
    TUint &copyStartCode = startCode;
    TUint endCode=0x003F;
    TUint &copyEndCode = endCode;
    TUint classes;
    TBool breakClassCode = TAknLineBreaker::IsSpecialVariantChar( 
          code, copyStartCode, copyEndCode, classes );
    
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMExtendedUtlts::TestSetCacheInputLanguage
// -----------------------------------------------------------------------------
//
TInt CTestDOMExtendedUtlts::TestSetCacheInputLanguage( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomextendedutlts, "testdomextendedutlts" );
    _LIT( KTestSetCacheInputLanguage, "In TestSetCacheInputLanguage" );
    TestModuleIf().Printf( 0, Ktestdomextendedutlts, KTestSetCacheInputLanguage );
    // Print to log file
    iLog->Log( KTestSetCacheInputLanguage );

    TInt err = KErrNone;
   
    CAknSettingCache& settingCache = CAknEnv::Static()->SettingCache();
    TLanguage language = settingCache.InputLanguage();
    
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMExtendedUtlts::TestSetCacheLayoutId
// -----------------------------------------------------------------------------
//
TInt CTestDOMExtendedUtlts::TestSetCacheLayoutId( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomextendedutlts, "testdomextendedutlts" );
    _LIT( KTestSetCacheLayoutId, "In TestSetCacheLayoutId" );
    TestModuleIf().Printf( 0, Ktestdomextendedutlts, KTestSetCacheLayoutId );
    // Print to log file
    iLog->Log( KTestSetCacheLayoutId );

    TInt err = KErrNone;
   
    CAknSettingCache& settingCache = CAknEnv::Static()->SettingCache();
    TAknLayoutId layoutId = settingCache.LayoutId();
   
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMExtendedUtlts::TestSetCacheHardwareLayoutState
// -----------------------------------------------------------------------------
//
TInt CTestDOMExtendedUtlts::TestSetCacheHardwareLayoutState( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomextendedutlts, "testdomextendedutlts" );
    _LIT( KTestSetCacheHardwareLayoutState, "In TestSetCacheHardwareLayoutState" );
    TestModuleIf().Printf( 0, Ktestdomextendedutlts, KTestSetCacheHardwareLayoutState );
    // Print to log file
    iLog->Log( KTestSetCacheHardwareLayoutState );

    TInt err = KErrNone;
    
    CAknSettingCache& settingCache = CAknEnv::Static()->SettingCache();
    TInt hardLayState = settingCache.HardwareLayoutState();
   
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMExtendedUtlts::TestSetCachePreferredOrientation
// -----------------------------------------------------------------------------
//
TInt CTestDOMExtendedUtlts::TestSetCachePreferredOrientation( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomextendedutlts, "testdomextendedutlts" );
    _LIT( KTestSetCachePreferredOrientation, "In TestSetCachePreferredOrientation" );
    TestModuleIf().Printf( 0, Ktestdomextendedutlts, KTestSetCachePreferredOrientation );
    // Print to log file
    iLog->Log( KTestSetCachePreferredOrientation );

    TInt err = KErrNone;
    
    CAknSettingCache& settingCache = CAknEnv::Static()->SettingCache();
    TInt preOrientation = settingCache.PreferredOrientation();
    
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMExtendedUtlts::TestSetCacheGlobalUiZoom
// -----------------------------------------------------------------------------
//
TInt CTestDOMExtendedUtlts::TestSetCacheGlobalUiZoom( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomextendedutlts, "testdomextendedutlts" );
    _LIT( KTestSetCacheGlobalUiZoom, "In TestSetCacheGlobalUiZoom" );
    TestModuleIf().Printf( 0, Ktestdomextendedutlts, KTestSetCacheGlobalUiZoom );
    // Print to log file
    iLog->Log( KTestSetCacheGlobalUiZoom );

    TInt err = KErrNone;
    
    CAknSettingCache& settingCache = CAknEnv::Static()->SettingCache();
    TAknUiZoom globalUiZoom = settingCache.GlobalUiZoom();
    
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMExtendedUtlts::TestSetCacheUpdate
// -----------------------------------------------------------------------------
//
TInt CTestDOMExtendedUtlts::TestSetCacheUpdate( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomextendedutlts, "testdomextendedutlts" );
    _LIT( KTestSetCacheUpdate, "In TestSetCacheUpdate" );
    TestModuleIf().Printf( 0, Ktestdomextendedutlts, KTestSetCacheUpdate );
    // Print to log file
    iLog->Log( KTestSetCacheUpdate );

    TInt err = KErrNone;
    
    CAknSettingCache& settingCache = CAknEnv::Static()->SettingCache();
    TBool update = settingCache.Update( KEikDynamicLayoutVariantSwitch );
    
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMExtendedUtlts::TestSetCacheRegisterPluginL
// -----------------------------------------------------------------------------
//
TInt CTestDOMExtendedUtlts::TestSetCacheRegisterPluginL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomextendedutlts, "testdomextendedutlts" );
    _LIT( KTestSetCacheRegisterPluginL, "In TestSetCacheRegisterPluginL" );
    TestModuleIf().Printf( 0, Ktestdomextendedutlts, KTestSetCacheRegisterPluginL );
    // Print to log file
    iLog->Log( KTestSetCacheRegisterPluginL );

    TInt err = KErrNone;
    
    CAknSettingCache& settingCache = CAknEnv::Static()->SettingCache();
    MAknSettingCacheUpdatePlugin* tplugin = NULL;
    TRAP( err, settingCache.RegisterPluginL( tplugin ) );
    
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMExtendedUtlts::TestSetCacheDeRegisterPlugin
// -----------------------------------------------------------------------------
//
TInt CTestDOMExtendedUtlts::TestSetCacheDeRegisterPlugin( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomextendedutlts, "testdomextendedutlts" );
    _LIT( KTestSetCacheDeRegisterPlugin, "In TestSetCacheUpdate" );
    TestModuleIf().Printf( 0, Ktestdomextendedutlts, KTestSetCacheDeRegisterPlugin );
    // Print to log file
    iLog->Log( KTestSetCacheDeRegisterPlugin );

    TInt err = KErrNone;
    
    CAknSettingCache& settingCache = CAknEnv::Static()->SettingCache();
    MAknSettingCacheUpdatePlugin* tplugin = NULL;  
    TRAP( err, settingCache.RegisterPluginL( tplugin ) );
    settingCache.DeRegisterPlugin( tplugin );
    
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMExtendedUtlts::TestSetCachePluginValue
// -----------------------------------------------------------------------------
//
TInt CTestDOMExtendedUtlts::TestSetCachePluginValue( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomextendedutlts, "testdomextendedutlts" );
    _LIT( KTestSetCachePluginValue, "In TestSetCachePluginValue" );
    TestModuleIf().Printf( 0, Ktestdomextendedutlts, KTestSetCachePluginValue );
    // Print to log file
    iLog->Log( KTestSetCachePluginValue );

    TInt err = KErrNone;
    
    CAknSettingCache& settingCache = CAknEnv::Static()->SettingCache();
    TInt value = 1;
    TInt &otherValue = value;
    TInt pluginValue = settingCache.PluginValue( KEikInputLanguageChange, otherValue );
    
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMExtendedUtlts::TestSetCacheTransparencyEnabled
// -----------------------------------------------------------------------------
//
TInt CTestDOMExtendedUtlts::TestSetCacheTransparencyEnabled( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomextendedutlts, "testdomextendedutlts" );
    _LIT( KTestSetCacheTransparencyEnabled, "In TestSetCacheTransparencyEnabled" );
    TestModuleIf().Printf( 0, Ktestdomextendedutlts, KTestSetCacheTransparencyEnabled );
    // Print to log file
    iLog->Log( KTestSetCacheTransparencyEnabled );

    TInt err = KErrNone;
    
    CAknSettingCache& settingCache = CAknEnv::Static()->SettingCache();
    TBool transpaEnabled = settingCache.TransparencyEnabled();
   
    return err;
    }

//  [End of File]
