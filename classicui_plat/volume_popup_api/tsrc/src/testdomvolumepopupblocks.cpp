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
* Description:  volume_popup_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknvolumepopup.h>
#include <avkon.hrh>

#include "testdomvolumepopupcontainer.h"
#include "testdomvolumepopup.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestVPNewL", CTestDOMVolumePopup::TestVPNewL ),
        ENTRY( "TestVPDefaultNewL", CTestDOMVolumePopup::TestVPDefaultNewL ),
        ENTRY( "TestVPConstructFromResourceL", CTestDOMVolumePopup::TestVPConstructFromResourceL ),
        ENTRY( "TestVPNewControlL", CTestDOMVolumePopup::TestVPNewControlL ),
        ENTRY( "TestVPHandleVolumeKeyEventL", CTestDOMVolumePopup::TestVPHandleVolumeKeyEventL ),
        ENTRY( "TestVPSetValue", CTestDOMVolumePopup::TestVPSetValue ),
        ENTRY( "TestVPSetRange", CTestDOMVolumePopup::TestVPSetRange ),
        ENTRY( "TestVPGetRange", CTestDOMVolumePopup::TestVPGetRange ),
        ENTRY( "TestVPValue", CTestDOMVolumePopup::TestVPValue ),
        ENTRY( "TestVPSetTitleTextL", CTestDOMVolumePopup::TestVPSetTitleTextL ),
        ENTRY( "TestVPShowProfileName", CTestDOMVolumePopup::TestVPShowProfileName ),
        ENTRY( "TestVPShowVolumePopupL", CTestDOMVolumePopup::TestVPShowVolumePopupL ),
        ENTRY( "TestVPCloseVolumePopup", CTestDOMVolumePopup::TestVPCloseVolumePopup ),
        ENTRY( "TestVPSetValueType", CTestDOMVolumePopup::TestVPSetValueType ),
        ENTRY( "TestVPSetStepSize", CTestDOMVolumePopup::TestVPSetStepSize ),
        ENTRY( "TestVPSetAdjustmentIndicatorDisplay", 
                CTestDOMVolumePopup::TestVPSetAdjustmentIndicatorDisplay ),
        ENTRY( "TestVPSetTimeOutAsSecond", CTestDOMVolumePopup::TestVPSetTimeOutAsSecond ),
        ENTRY( "TestVPSetDecimalPlaces", CTestDOMVolumePopup::TestVPSetDecimalPlaces ),
        ENTRY( "TestVPSetGraphicsL", CTestDOMVolumePopup::TestVPSetGraphicsL ),
        ENTRY( "TestVPUseMutedIcon", CTestDOMVolumePopup::TestVPUseMutedIcon ),
        ENTRY( "TestVPClosePopupWhenTappedOutside", 
                CTestDOMVolumePopup::TestVPClosePopupWhenTappedOutside ),
        ENTRY( "TestVPSetDefaultValue", CTestDOMVolumePopup::TestVPSetDefaultValue ),
        ENTRY( "TestVPEnableResetViaValueField", CTestDOMVolumePopup::TestVPEnableResetViaValueField ),
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPNewL, "In TestVPNewL" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPNewL );
    // Print to log file
    iLog->Log( KTestVPNewL );
    TUid uid = TUid::Uid( 0x000000001 );
    _LIT( KTitle, "Title" );
    TBool err = KErrNone;
    TRAP( err, iVolumePopup = CAknVolumePopup::NewL( uid, KTitle) );
    STIF_ASSERT_NOT_NULL( iVolumePopup );
    return err;

    }

// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPDefaultNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPDefaultNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPDefaultNewL, "In TestVPDefaultNewL" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPDefaultNewL );
    // Print to log file
    iLog->Log( KTestVPDefaultNewL );
    TBool err = KErrNone;
    TRAP( err, iVolumePopup = CAknVolumePopup::NewL() );
    STIF_ASSERT_NOT_NULL( iVolumePopup );
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPConstructFromResourceL, "In TestVPConstructFromResourceL" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPConstructFromResourceL );
    // Print to log file
    iLog->Log( KTestVPConstructFromResourceL );

    TBool err = KErrNone;
    TRAP( err, iVolumePopup->ConstructFromResourceL( R_AVKON_POPUP_VOLUME_INDICATOR ) );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPNewControlL
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPNewControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPNewControlL, "In TestVPNewControlL" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPNewControlL );
    // Print to log file
    iLog->Log( KTestVPNewControlL );

    TInt err = KErrNone;
    TRAP( err, iVolumePopup = CAknVolumePopup::NewL( NULL, EFalse ) );
    STIF_ASSERT_NOT_NULL( iVolumePopup );
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPHandleVolumeKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPHandleVolumeKeyEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPHandleVolumeKeyEventL, "In TestVPHandleVolumeKeyEventL" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPHandleVolumeKeyEventL );
    // Print to log file
    iLog->Log( KTestVPHandleVolumeKeyEventL );
    TBool err = KErrNone;
    TKeyEvent keyEvent = { EKeyPause, EStdKeySpace, 0, 0 };
    TRAP( err, iVolumePopup->HandleVolumeKeyEventL( keyEvent, EEventKey ) );
 
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPSetValue
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPSetValue( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPSetValue, "In TestVPSetValue" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPSetValue );
    // Print to log file
    iLog->Log( KTestVPSetValue );
    TInt value = 10;
    iVolumePopup->SetValue( value );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPSetRange
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPSetRange( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPSetRange, "In TestVPSetRange" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPSetRange );
    // Print to log file
    iLog->Log( KTestVPSetRange );
    TInt minimumValue = 0;
    TInt maximumValue = 100;
    iVolumePopup->SetRange( minimumValue, maximumValue );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPGetRange
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPGetRange( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPGetRange, "In TestVPGetRange" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPGetRange );
    // Print to log file
    iLog->Log( KTestVPGetRange );
    TInt minimumValue;
    TInt maximumValue;
    iVolumePopup->GetRange( minimumValue, maximumValue );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPValue
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPValue( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPValue, "In TestVPValue" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPValue );
    // Print to log file
    iLog->Log( KTestVPValue );
    TInt value = iVolumePopup->Value();

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPSetTitleTextL
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPSetTitleTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPSetTitleTextL, "In TestVPSetTitleTextL" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPSetTitleTextL );
    // Print to log file
    iLog->Log( KTestVPSetTitleTextL );
    TBool err = KErrNone;
    _LIT( KText, "test" );
    TRAP( err, iVolumePopup->SetTitleTextL( KText ) );

    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPShowProfileName
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPShowProfileName( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPShowProfileName, "In TestVPShowProfileName" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPShowProfileName );
    // Print to log file
    iLog->Log( KTestVPShowProfileName );

    iVolumePopup->ShowProfileName( ETrue );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPShowVolumePopupL
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPShowVolumePopupL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPShowVolumePopupL, "In TestVPShowVolumePopupL" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPShowVolumePopupL );
    // Print to log file
    iLog->Log( KTestVPShowVolumePopupL );
    TBool err = KErrNone;
    TRAP( err, iVolumePopup->ShowVolumePopupL() );

    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPCloseVolumePopup
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPCloseVolumePopup( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPCloseVolumePopup, "In TestVPCloseVolumePopup" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPCloseVolumePopup );
    // Print to log file
    iLog->Log( KTestVPCloseVolumePopup );
    iVolumePopup->CloseVolumePopup();
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPSetValueType
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPSetValueType( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPSetValueType, "In TestVPSetValueType" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPSetValueType );
    // Print to log file
    iLog->Log( KTestVPSetValueType );
    iVolumePopup->SetValueType( EAknSliderValueNone );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPSetStepSize
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPSetStepSize( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPSetStepSize, "In TestVPSetStepSize" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPSetStepSize );
    // Print to log file
    iLog->Log( KTestVPSetStepSize );
    TInt stepSize = 2; 
    iVolumePopup->SetStepSize( stepSize );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPSetAdjustmentIndicatorDisplay
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPSetAdjustmentIndicatorDisplay( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPSetAdjustmentIndicatorDisplay, "In TestVPSetAdjustmentIndicatorDisplay" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPSetAdjustmentIndicatorDisplay );
    // Print to log file
    iLog->Log( KTestVPSetAdjustmentIndicatorDisplay );

    iVolumePopup->SetAdjustmentIndicatorDisplay( ETrue );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPSetTimeOutAsSecond
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPSetTimeOutAsSecond( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPSetTimeOutAsSecond, "In TestVPSetTimeOutAsSecond" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPSetTimeOutAsSecond );
    // Print to log file
    iLog->Log( KTestVPSetTimeOutAsSecond );
    TInt second = 1;
    iVolumePopup->SetTimeOutAsSecond( second );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPSetDecimalPlaces
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPSetDecimalPlaces( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPSetDecimalPlaces, "In TestVPSetDecimalPlaces" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPSetDecimalPlaces );
    // Print to log file
    iLog->Log( KTestVPSetDecimalPlaces );
    TInt decimalPlaces = 1;
    iVolumePopup->SetDecimalPlaces( decimalPlaces );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPSetGraphicsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPSetGraphicsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPSetGraphicsL, "In TestVPSetGraphicsL" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPSetGraphicsL );
    // Print to log file
    iLog->Log( KTestVPSetGraphicsL );
    TInt element = 100;
    CFbsBitmap* bitmap = new (ELeave) CFbsBitmap();
    CleanupStack::PushL( bitmap );
    iVolumePopup->SetGraphics( element, bitmap, bitmap );
    CleanupStack::Pop( bitmap );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPUseMutedIcon
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPUseMutedIcon( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPUseMutedIcon, "In TestVPUseMutedIcon" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPUseMutedIcon );
    // Print to log file
    iLog->Log( KTestVPUseMutedIcon );
    iVolumePopup->UseMutedIcon( ETrue );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPClosePopupWhenTappedOutside
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPClosePopupWhenTappedOutside( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPClosePopupWhenTappedOutside, "In TestVPClosePopupWhenTappedOutside" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPClosePopupWhenTappedOutside );
    // Print to log file
    iLog->Log( KTestVPClosePopupWhenTappedOutside );
    iVolumePopup->ClosePopupWhenTappedOutside( ETrue );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPSetDefaultValue
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPSetDefaultValue( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPSetDefaultValue, "In TestVPSetDefaultValue" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPSetDefaultValue );
    // Print to log file
    iLog->Log( KTestVPSetDefaultValue );
    TInt value = 0;
    iVolumePopup->SetDefaultValue( value );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMVolumePopup::TestVPEnableResetViaValueField
// -----------------------------------------------------------------------------
//
TInt CTestDOMVolumePopup::TestVPEnableResetViaValueField( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomvolumepopup, "testdomvolumepopup" );
    _LIT( KTestVPEnableResetViaValueField, "In TestVPEnableResetViaValueField" );
    TestModuleIf().Printf( 0, Ktestdomvolumepopup, KTestVPEnableResetViaValueField );
    // Print to log file
    iLog->Log( KTestVPEnableResetViaValueField );

    iVolumePopup->EnableResetViaValueField();
    return KErrNone;
    }
//  [End of File]
