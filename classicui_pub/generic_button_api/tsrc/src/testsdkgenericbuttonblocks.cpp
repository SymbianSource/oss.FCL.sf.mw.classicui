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
* Description:  Test AknButton.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknbutton.h>
#include <gulicon.h>
#include <avkon.mbg>
#include <aknutils.h>
#include <e32cmn.h>
#include <testsdkgenericbutton.rsg>
#include <barsread.h>
#include <coemain.h>
#include <e32def.h>
#include <aknpictographinterface.h>
#include <aknpictographdrawerinterface.h>
#include <eikdef.h>

#include "testsdkgenericbuttoninclude.h"
#include "testbuttonstate.h"
#include "testbutton.h"
#include "animatorcallback.h"
#include "testparentcontrol.h"
#include "testsdkgenericbutton.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKGENERICBUTTON::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        /*
         * Follow entry is CAknButtonState class's public function's entry
         */
        ENTRY( "TestGBDestructorStateL", CTestSDKGENERICBUTTON::TestGBDestructorStateL ),
        ENTRY( "TestGBIconL", CTestSDKGENERICBUTTON::TestGBIconL ),
        ENTRY( "TestGBDimmedIconL", CTestSDKGENERICBUTTON::TestGBDimmedIconL ),
        ENTRY( "TestGBPressedIconL", CTestSDKGENERICBUTTON::TestGBPressedIconL ),
        ENTRY( "TestGBHoverIconL", CTestSDKGENERICBUTTON::TestGBHoverIconL ),
        ENTRY( "TestGBTextL", CTestSDKGENERICBUTTON::TestGBTextL ),
        ENTRY( "TestGBHelpTextL", CTestSDKGENERICBUTTON::TestGBHelpTextL ),
        ENTRY( "TestGBFlagsL", CTestSDKGENERICBUTTON::TestGBFlagsL ),
        ENTRY( "TestGBSetIconL", CTestSDKGENERICBUTTON::TestGBSetIconL ),
        ENTRY( "TestGBSetDimmedIconL", CTestSDKGENERICBUTTON::TestGBSetDimmedIconL ),
        ENTRY( "TestGBSetPressedIconL", CTestSDKGENERICBUTTON::TestGBSetPressedIconL ),
        ENTRY( "TestGBSetHoverIconL", CTestSDKGENERICBUTTON::TestGBSetHoverIconL ),
        ENTRY( "TestGBSetTextLL", CTestSDKGENERICBUTTON::TestGBSetTextLL ),
        ENTRY( "TestGBSetHelpTextLL", CTestSDKGENERICBUTTON::TestGBSetHelpTextLL ),
        ENTRY( "TestGBSetFlagsL", CTestSDKGENERICBUTTON::TestGBSetFlagsL ),
        /*
         * Follow entry is CAknButtonState class's protected function's entry
         */
        ENTRY( "TestGBCAknButtonStateL", CTestSDKGENERICBUTTON::TestGBCAknButtonStateL ),
        ENTRY( "TestGBConstructLfleetL", CTestSDKGENERICBUTTON::TestGBConstructLfleetL ),
        ENTRY( "TestGBConstructLdeepL", CTestSDKGENERICBUTTON::TestGBConstructLdeepL ),
        ENTRY( "TestGBConstructFromResourceLL", CTestSDKGENERICBUTTON::TestGBConstructFromResourceLL ),
        ENTRY( "TestGBSizeChangedStateL", CTestSDKGENERICBUTTON::TestGBSizeChangedStateL ),
        ENTRY( "TestGBHasTextL", CTestSDKGENERICBUTTON::TestGBHasTextL ),
        ENTRY( "TestGBHasHelpL", CTestSDKGENERICBUTTON::TestGBHasHelpL ),
        /*
         * Follow entry is CAknButton class's public function's entry
         */
        ENTRY( "TestGBNewLNullL", CTestSDKGENERICBUTTON::TestGBNewLNullL ),
        ENTRY( "TestGBNewLCNullL", CTestSDKGENERICBUTTON::TestGBNewLCNullL ),
        ENTRY( "TestGBNewLReaderL", CTestSDKGENERICBUTTON::TestGBNewLReaderL ),
        ENTRY( "TestGBNewLCReaderL", CTestSDKGENERICBUTTON::TestGBNewLCReaderL ),
        ENTRY( "TestGBNewLIdL", CTestSDKGENERICBUTTON::TestGBNewLIdL ),
        ENTRY( "TestGBNewLCIdL", CTestSDKGENERICBUTTON::TestGBNewLCIdL ),
        ENTRY( "TestGBNewLComplexL", CTestSDKGENERICBUTTON::TestGBNewLComplexL ),
        ENTRY( "TestGBNewLCComplexL", CTestSDKGENERICBUTTON::TestGBNewLCComplexL ),
        ENTRY( "TestGBNewLMoreComplexL", CTestSDKGENERICBUTTON::TestGBNewLMoreComplexL ),
        ENTRY( "TestGBNewLCMoreComplexL", CTestSDKGENERICBUTTON::TestGBNewLCMoreComplexL ),
        ENTRY( "TestGBDestructorL", CTestSDKGENERICBUTTON::TestGBDestructorL ),
        ENTRY( "TestGBActivateLL", CTestSDKGENERICBUTTON::TestGBActivateLL ),
        ENTRY( "TestGBConstructFromResourceLReaderL", CTestSDKGENERICBUTTON::TestGBConstructFromResourceLReaderL ),
        ENTRY( "TestGBHandleResourceChangeL", CTestSDKGENERICBUTTON::TestGBHandleResourceChangeL ),
        ENTRY( "TestGBMinimumSizeL", CTestSDKGENERICBUTTON::TestGBMinimumSizeL ),
        ENTRY( "TestGBSetDimmedL", CTestSDKGENERICBUTTON::TestGBSetDimmedL ),
        ENTRY( "TestGBOfferKeyEventLL", CTestSDKGENERICBUTTON::TestGBOfferKeyEventLL ),
        ENTRY( "TestGBMakeVisibleL", CTestSDKGENERICBUTTON::TestGBMakeVisibleL ),
        ENTRY( "TestGBPrepareForFocusLossLL", CTestSDKGENERICBUTTON::TestGBPrepareForFocusLossLL ),
        ENTRY( "TestGBPrepareForFocusGainLL", CTestSDKGENERICBUTTON::TestGBPrepareForFocusGainLL ),
        ENTRY( "TestGBHandlePointerEventL", CTestSDKGENERICBUTTON::TestGBHandlePointerEventL ),
        ENTRY( "TestGBPositionChangedL", CTestSDKGENERICBUTTON::TestGBPositionChangedL ),
        ENTRY( "TestGBConstructFromResourceLIdL", CTestSDKGENERICBUTTON::TestGBConstructFromResourceLIdL ),
        ENTRY( "TestGBSetCurrentStateL", CTestSDKGENERICBUTTON::TestGBSetCurrentStateL ),
        ENTRY( "TestGBAddStateLL", CTestSDKGENERICBUTTON::TestGBAddStateLL ),
        ENTRY( "TestGBAddStateLComplexL", CTestSDKGENERICBUTTON::TestGBAddStateLComplexL ),
        ENTRY( "TestGBSetButtonFlagsL", CTestSDKGENERICBUTTON::TestGBSetButtonFlagsL ),
        ENTRY( "TestGBSetFrameAndCenterIdsL", CTestSDKGENERICBUTTON::TestGBSetFrameAndCenterIdsL ),
        ENTRY( "TestGBSetBackgroundIdsL", CTestSDKGENERICBUTTON::TestGBSetBackgroundIdsL ),
        ENTRY( "TestGBSetTextFontL", CTestSDKGENERICBUTTON::TestGBSetTextFontL ),
        ENTRY( "TestGBSetTextColorIdsL", CTestSDKGENERICBUTTON::TestGBSetTextColorIdsL ),
        ENTRY( "TestGBSetTextHorizontalAlignmentL", CTestSDKGENERICBUTTON::TestGBSetTextHorizontalAlignmentL ),
        ENTRY( "TestGBSetTextVerticalAlignmentL", CTestSDKGENERICBUTTON::TestGBSetTextVerticalAlignmentL),
        ENTRY( "TestGBSetTextAndIconAlignmentL", CTestSDKGENERICBUTTON::TestGBSetTextAndIconAlignmentL ),
        ENTRY( "TestGBSetTextUnderlineStyleL", CTestSDKGENERICBUTTON::TestGBSetTextUnderlineStyleL ),
        ENTRY( "TestGBSetIconScaleModeL", CTestSDKGENERICBUTTON::TestGBSetIconScaleModeL ),
        ENTRY( "TestGBSetIconHorizontalAlignmentL", CTestSDKGENERICBUTTON::TestGBSetIconHorizontalAlignmentL ),
        ENTRY( "TestGBSetIconVerticalAlignmentL", CTestSDKGENERICBUTTON::TestGBSetIconVerticalAlignmentL ),
        ENTRY( "TestGBSetHelpNoteTimeoutsL", CTestSDKGENERICBUTTON::TestGBSetHelpNoteTimeoutsL ),
        ENTRY( "TestGBSetKeyRepeatIntervalL", CTestSDKGENERICBUTTON::TestGBSetKeyRepeatIntervalL ),
        ENTRY( "TestGBSetLongPressIntervalL", CTestSDKGENERICBUTTON::TestGBSetLongPressIntervalL ),
        ENTRY( "TestGBStateIndexL", CTestSDKGENERICBUTTON::TestGBStateIndexL ),
        ENTRY( "TestGBEnablePictographsLL", CTestSDKGENERICBUTTON::TestGBEnablePictographsLL ),
        ENTRY( "TestGBDisablePictographsL", CTestSDKGENERICBUTTON::TestGBDisablePictographsL ),
        ENTRY( "TestGBSetHighlightRectL", CTestSDKGENERICBUTTON::TestGBSetHighlightRectL ),
        ENTRY( "TestGBHighlightRectL", CTestSDKGENERICBUTTON::TestGBHighlightRectL ),
        ENTRY( "TestGBSetTooltipPositionL", CTestSDKGENERICBUTTON::TestGBSetTooltipPositionL ),
        ENTRY( "TestGBSetRequestExitL", CTestSDKGENERICBUTTON::TestGBSetRequestExitL ),
        ENTRY( "TestGBIsDimmedL", CTestSDKGENERICBUTTON::TestGBIsDimmedL ),
        ENTRY( "TestGBSetDimmedHelpTextLL", CTestSDKGENERICBUTTON::TestGBSetDimmedHelpTextLL ),
        ENTRY( "TestGBStateL", CTestSDKGENERICBUTTON::TestGBStateL ),
        ENTRY( "TestGBStateComplexL", CTestSDKGENERICBUTTON::TestGBStateComplexL ),
        ENTRY( "TestGBButtonFlagsL", CTestSDKGENERICBUTTON::TestGBButtonFlagsL ),
        ENTRY( "TestGBSetMarginsL", CTestSDKGENERICBUTTON::TestGBSetMarginsL ),
        ENTRY( "TestGBSetIconSizeL", CTestSDKGENERICBUTTON::TestGBSetIconSizeL ),
        ENTRY( "TestGBResetStateL", CTestSDKGENERICBUTTON::TestGBResetStateL ),
        /*
         * Follow entry is CAknButton class's protected function's entry
         */
        ENTRY( "TestGBConstructorL", CTestSDKGENERICBUTTON::TestGBConstructorL ),
        ENTRY( "TestGBConstructLL", CTestSDKGENERICBUTTON::TestGBConstructLL ),
        ENTRY( "TestGBConstructLComplexL", CTestSDKGENERICBUTTON::TestGBConstructLComplexL ),
        ENTRY( "TestGBConstructLMoreComplexL", CTestSDKGENERICBUTTON::TestGBConstructLMoreComplexL ),
        ENTRY( "TestGBSizeChangedL", CTestSDKGENERICBUTTON::TestGBSizeChangedL ),
        ENTRY( "TestGBFocusChangedL", CTestSDKGENERICBUTTON::TestGBFocusChangedL ),
        ENTRY( "TestGBExtensionInterfaceL", CTestSDKGENERICBUTTON::TestGBExtensionInterfaceL ),
        ENTRY( "TestGBChangeStateL", CTestSDKGENERICBUTTON::TestGBChangeStateL ),
        ENTRY( "TestGBGetCurrentTextL", CTestSDKGENERICBUTTON::TestGBGetCurrentTextL ),
        ENTRY( "TestGBGetCurrentIconL", CTestSDKGENERICBUTTON::TestGBGetCurrentIconL ),
        ENTRY( "TestGBShowHelpLL", CTestSDKGENERICBUTTON::TestGBShowHelpLL ),
        ENTRY( "TestGBHideHelpL", CTestSDKGENERICBUTTON::TestGBHideHelpL ),
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

/*
 * Follow function is CAknButtonState class's public function
 */

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBDestructorStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBDestructorStateL( CStifItemParser& /*aItem*/ )
    {
    CTestButtonState* buttonstate = new( ELeave ) CTestButtonState( KButtonStateTrue );
    CleanupStack::PushL( buttonstate );
    STIF_ASSERT_NOT_NULL( buttonstate );
    CleanupStack::PopAndDestroy( buttonstate );

    return KErrNone;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBIconL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBIconL( CStifItemParser& aItem )
    {
    TInt err( KErrNone );
    err = TestGBSetIconL( aItem );
    return err;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBDimmedIconL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBDimmedIconL( CStifItemParser& aItem )
    {
    TInt err( KErrNone );
    err = TestGBSetDimmedIconL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBPressedIconL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBPressedIconL( CStifItemParser& aItem )
    {
    TInt err( KErrNone );
    err = TestGBSetPressedIconL( aItem );
    return err;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBHoverIconL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBHoverIconL( CStifItemParser& aItem )
    {
    TInt err( KErrNone );
    err = TestGBSetHoverIconL( aItem );
    return err;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBTextL( CStifItemParser& aItem )
    {
    TInt err( KErrNone );
    err = TestGBSetTextLL( aItem );
    return err;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBHelpTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBHelpTextL( CStifItemParser& aItem )
    {
    TInt err( KErrNone );
    err = TestGBSetHelpTextLL( aItem );
    return err;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBFlagsL( CStifItemParser& aItem )
    {
    TInt err( KErrNone );
    err = TestGBSetFlagsL( aItem );
    return err;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetIconL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetIconL( CStifItemParser& /*aItem*/ )
    {
    CTestButtonState* buttonstate = new( ELeave ) CTestButtonState( KButtonStateTrue );
    CleanupStack::PushL( buttonstate );
    CFbsBitmap* bitmap( NULL );
    CFbsBitmap* bitmapmask( NULL );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    AknIconUtils::CreateIconLC( bitmap, bitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* testicon = CGulIcon::NewL( bitmap, bitmapmask );
    CleanupStack::PushL( testicon );
    
    CGulIcon* nullicon = NULL;
    const TDesC text = KNullDesC;
    buttonstate->DoConstructL( nullicon, nullicon, nullicon, nullicon, text, text );
    
    buttonstate->SetIcon( testicon );
    const CGulIcon* returnIcon( NULL );
    returnIcon = buttonstate->Icon();
    STIF_ASSERT_NOT_NULL( returnIcon );
    STIF_ASSERT_EQUALS( testicon, const_cast<CGulIcon* >( returnIcon ));
    
    CleanupStack::Pop( testicon );
    CleanupStack::Pop( bitmapmask );
    CleanupStack::Pop( bitmap );
    CleanupStack::PopAndDestroy( buttonstate );
    
    return KErrNone;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetDimmedIconL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetDimmedIconL( CStifItemParser& /*aItem*/ )
    {
    CTestButtonState* buttonstate = new( ELeave ) CTestButtonState( KButtonStateTrue );
    CleanupStack::PushL( buttonstate );
    CFbsBitmap* bitmap( NULL );
    CFbsBitmap* bitmapmask( NULL );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    AknIconUtils::CreateIconLC( bitmap, bitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* testicon = CGulIcon::NewL( bitmap, bitmapmask );
    CleanupStack::PushL( testicon );
    
    CGulIcon* nullicon = NULL;
    const TDesC text = KNullDesC;
    buttonstate->DoConstructL( nullicon, nullicon, nullicon, nullicon, text, text );
    
    buttonstate->SetDimmedIcon( testicon );
    const CGulIcon* returnIcon( NULL );
    returnIcon = buttonstate->DimmedIcon();
    STIF_ASSERT_NOT_NULL( returnIcon );
    STIF_ASSERT_EQUALS( testicon, const_cast<CGulIcon* >( returnIcon ));
    
    CleanupStack::Pop( testicon );
    CleanupStack::Pop( bitmapmask );
    CleanupStack::Pop( bitmap );
    CleanupStack::PopAndDestroy( buttonstate );
    
    return KErrNone;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetPressedIconL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetPressedIconL( CStifItemParser& /*aItem*/ )
    {
    CTestButtonState* buttonstate = new( ELeave ) CTestButtonState( KButtonStateTrue );
    CleanupStack::PushL( buttonstate );
    CFbsBitmap* bitmap( NULL );
    CFbsBitmap* bitmapmask( NULL );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    AknIconUtils::CreateIconLC( bitmap, bitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* testicon = CGulIcon::NewL( bitmap, bitmapmask );
    CleanupStack::PushL( testicon );
    
    CGulIcon* nullicon = NULL;
    const TDesC text = KNullDesC;
    buttonstate->DoConstructL( nullicon, nullicon, nullicon, nullicon, text, text );
    
    buttonstate->SetPressedIcon( testicon );
    const CGulIcon* returnIcon( NULL );
    returnIcon = buttonstate->PressedIcon();
    STIF_ASSERT_NOT_NULL( returnIcon );
    STIF_ASSERT_EQUALS( testicon, const_cast<CGulIcon* >( returnIcon ));
    
    CleanupStack::Pop( testicon );
    CleanupStack::Pop( bitmapmask );
    CleanupStack::Pop( bitmap );
    CleanupStack::PopAndDestroy( buttonstate );
    
    return KErrNone;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetHoverIconL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetHoverIconL( CStifItemParser& /*aItem*/ )
    {
    CTestButtonState* buttonstate = new( ELeave ) CTestButtonState( KButtonStateTrue );
    CleanupStack::PushL( buttonstate );
    CFbsBitmap* bitmap( NULL );
    CFbsBitmap* bitmapmask( NULL );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    AknIconUtils::CreateIconLC( bitmap, bitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* testicon = CGulIcon::NewL( bitmap, bitmapmask );
    CleanupStack::PushL( testicon );
    
    CGulIcon* nullicon = NULL;
    const TDesC text = KNullDesC;
    buttonstate->DoConstructL( nullicon, nullicon, nullicon, nullicon, text, text );
    
    buttonstate->SetHoverIcon( testicon );
    const CGulIcon* returnIcon( NULL );
    returnIcon = buttonstate->HoverIcon();
    STIF_ASSERT_NOT_NULL( returnIcon );
    STIF_ASSERT_EQUALS( testicon, const_cast<CGulIcon* >( returnIcon ));
    
    CleanupStack::Pop( testicon );
    CleanupStack::Pop( bitmapmask );
    CleanupStack::Pop( bitmap );
    CleanupStack::PopAndDestroy( buttonstate );
    
    return KErrNone;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetTextLL( CStifItemParser& /*aItem*/ )
    {
    CTestButtonState* buttonstate = new( ELeave ) CTestButtonState( KButtonStateTrue );
    CleanupStack::PushL( buttonstate );
    
    const TDesC simpletext( KSimpleText );
    buttonstate->SetTextL( simpletext );
    
    TDesC returntext( KNullDesC );
    TDesC comparetext( KNullDesC );
    returntext = buttonstate->Text();
    STIF_ASSERT_NOT_EQUALS( comparetext, returntext );
    CleanupStack::PopAndDestroy( buttonstate );
    
    return KErrNone;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetHelpTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetHelpTextLL( CStifItemParser& /*aItem*/ )
    {
    CTestButtonState* buttonstate = new( ELeave ) CTestButtonState( KButtonStateTrue );
    CleanupStack::PushL( buttonstate );
    
    const TDesC simpletext( KSimpleText );
    
    buttonstate->SetHelpTextL( simpletext );
    
    TDesC returntext( KNullDesC );
    TDesC comparetext( KNullDesC );
    returntext = buttonstate->HelpText();
    STIF_ASSERT_NOT_EQUALS( comparetext, returntext );
    CleanupStack::PopAndDestroy( buttonstate );
    
    return KErrNone;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetFlagsL( CStifItemParser& /*aItem*/ )
    {
    CTestButtonState* buttonstate = new( ELeave ) CTestButtonState( KButtonStateTrue );
    CleanupStack::PushL( buttonstate );
    
    buttonstate->SetFlags( KFlags );
    TInt returnflag = buttonstate->Flags();
    STIF_ASSERT_EQUALS( KFlags, returnflag );
    
    CleanupStack::PopAndDestroy( buttonstate );
    
    return KErrNone;
    }

/*
 * Follow function is CAknButtonState class's protected function
 */

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBCAknButtonStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBCAknButtonStateL( CStifItemParser& /*aItem*/ )
    {
    CTestButtonState* buttonstate = new( ELeave ) CTestButtonState( KButtonStateTrue );
    CleanupStack::PushL( buttonstate );
    STIF_ASSERT_NOT_NULL( buttonstate );
    CleanupStack::PopAndDestroy( buttonstate );

    return KErrNone;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBConstructLfleetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBConstructLfleetL( CStifItemParser& /*aItem*/ )
    {
    CTestButtonState* buttonstate = new( ELeave ) CTestButtonState( KButtonStateTrue );
    CleanupStack::PushL( buttonstate );
    CFbsBitmap* normalbitmap( NULL );
    CFbsBitmap* normalbitmapmask( NULL );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    AknIconUtils::CreateIconLC( normalbitmap, normalbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* normalicon = CGulIcon::NewL( normalbitmap, normalbitmapmask );
    CleanupStack::PushL( normalicon );
    
    CFbsBitmap* dimmedbitmap( NULL );
    CFbsBitmap* dimmedbitmapmask( NULL );
    AknIconUtils::CreateIconLC( dimmedbitmap, dimmedbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* dimmedicon = CGulIcon::NewL( dimmedbitmap, dimmedbitmapmask );
    CleanupStack::PushL( dimmedicon );
    
    CFbsBitmap* pressedbitmap( NULL );
    CFbsBitmap* pressedbitmapmask( NULL );
    AknIconUtils::CreateIconLC( pressedbitmap, pressedbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* pressedicon = CGulIcon::NewL( pressedbitmap, pressedbitmapmask );
    CleanupStack::PushL( pressedicon );
        
    CFbsBitmap* hoverbitmap( NULL );
    CFbsBitmap* hoverbitmapmask( NULL );
    AknIconUtils::CreateIconLC( hoverbitmap, hoverbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* hovericon = CGulIcon::NewL( hoverbitmap, hoverbitmapmask );
    CleanupStack::PushL( hovericon );
    const TDesC text( KSimpleText );
    const TDesC helptext( KSimpleText );
    buttonstate->DoConstructL( normalicon, dimmedicon, pressedicon, hovericon,
        text, helptext );
    
    TDesC returntext( KNullDesC );
    TDesC returnhelptext( KNullDesC );
    TDesC comparetext( KNullDesC );
    const CGulIcon* returnnormalIcon = buttonstate->Icon();
    const CGulIcon* returndimmedIcon = buttonstate->DimmedIcon();
    const CGulIcon* returnpressIcon = buttonstate->PressedIcon();
    const CGulIcon* returnhoverIcon = buttonstate->HoverIcon();
    returntext = buttonstate->Text();
    returnhelptext = buttonstate->HelpText();
    
    STIF_ASSERT_EQUALS( normalicon, const_cast<CGulIcon* >( returnnormalIcon ));
    STIF_ASSERT_EQUALS( dimmedicon, const_cast<CGulIcon* >( returndimmedIcon ));
    STIF_ASSERT_EQUALS( pressedicon, const_cast<CGulIcon* >( returnpressIcon ));
    STIF_ASSERT_EQUALS( hovericon, const_cast<CGulIcon* >( returnhoverIcon ));
    STIF_ASSERT_NOT_EQUALS( comparetext, returntext );
    STIF_ASSERT_NOT_EQUALS( comparetext, returnhelptext );
    
    CleanupStack::Pop( hovericon );
    CleanupStack::Pop( hoverbitmapmask );
    CleanupStack::Pop( hoverbitmap );
    CleanupStack::Pop( pressedicon );
    CleanupStack::Pop( pressedbitmapmask );
    CleanupStack::Pop( pressedbitmap );
    CleanupStack::Pop( dimmedicon );
    CleanupStack::Pop( dimmedbitmapmask );
    CleanupStack::Pop( dimmedbitmap );
    CleanupStack::Pop( normalicon );
    CleanupStack::Pop( normalbitmapmask );
    CleanupStack::Pop( normalbitmap );
    CleanupStack::PopAndDestroy( buttonstate );
    
    return KErrNone;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBConstructLdeepL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBConstructLdeepL( CStifItemParser& /*aItem*/ )
    {
    CTestButtonState* buttonstate = new( ELeave ) CTestButtonState( KButtonStateTrue );
    CleanupStack::PushL( buttonstate );

    CGulIcon* nullicon = NULL;
    const TDesC textnull = KNullDesC;
    buttonstate->DoConstructL( nullicon, nullicon, nullicon, nullicon, textnull, textnull );
    
    TDesC returntext( KNullDesC );
    TDesC returnhelptext( KNullDesC );
    TDesC comparetext( KNullDesC );
    const CGulIcon* returnnormalIcon = buttonstate->Icon();
    const CGulIcon* returndimmedIcon = buttonstate->DimmedIcon();
    const CGulIcon* returnpressIcon = buttonstate->PressedIcon();
    const CGulIcon* returnhoverIcon = buttonstate->HoverIcon();
    returntext = buttonstate->Text();
    returnhelptext = buttonstate->HelpText();
    
    STIF_ASSERT_EQUALS( nullicon, const_cast<CGulIcon* >( returnnormalIcon ));
    STIF_ASSERT_EQUALS( nullicon, const_cast<CGulIcon* >( returndimmedIcon ));
    STIF_ASSERT_EQUALS( nullicon, const_cast<CGulIcon* >( returnpressIcon ));
    STIF_ASSERT_EQUALS( nullicon, const_cast<CGulIcon* >( returnhoverIcon ));
    STIF_ASSERT_EQUALS( comparetext, returntext );
    STIF_ASSERT_EQUALS( comparetext, returnhelptext );
    
    const TDesC text( KSimpleText );
    const TDesC helptext( KSimpleText );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    buttonstate->DoConstructDeepL( file, EMbmAvkonQgn_indi_mic,
            EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
            EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
            EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
            EMbmAvkonQgn_indi_mic_mask, text, helptext );
    
    returnnormalIcon = buttonstate->Icon();
    returndimmedIcon = buttonstate->DimmedIcon();
    returnpressIcon = buttonstate->PressedIcon();
    returnhoverIcon = buttonstate->HoverIcon();
    returntext = buttonstate->Text();
    returnhelptext = buttonstate->HelpText();
    
    STIF_ASSERT_NOT_EQUALS( nullicon, const_cast<CGulIcon* >( returnnormalIcon ));
    STIF_ASSERT_NOT_EQUALS( nullicon, const_cast<CGulIcon* >( returndimmedIcon ));
    STIF_ASSERT_NOT_EQUALS( nullicon, const_cast<CGulIcon* >( returnpressIcon ));
    STIF_ASSERT_NOT_EQUALS( nullicon, const_cast<CGulIcon* >( returnhoverIcon ));
    STIF_ASSERT_NOT_EQUALS( comparetext, returntext );
    STIF_ASSERT_NOT_EQUALS( comparetext, returnhelptext );
    
    CleanupStack::PopAndDestroy( buttonstate );
    
    return KErrNone;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBConstructFromResourceLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBConstructFromResourceLL( CStifItemParser& /*aItem*/ )
    {
    CTestButtonState* buttonstate = new( ELeave ) CTestButtonState( KButtonStateTrue );
    CleanupStack::PushL( buttonstate );
    
    CGulIcon* nullicon = NULL;
    const TDesC textnull = KNullDesC;
    buttonstate->DoConstructL( nullicon, nullicon, nullicon, nullicon, textnull, textnull );
    
    TDesC returntext( KNullDesC );
    TDesC returnhelptext( KNullDesC );
    TDesC comparetext( KNullDesC );
    const CGulIcon* returnnormalIcon = buttonstate->Icon();
    const CGulIcon* returndimmedIcon = buttonstate->DimmedIcon();
    const CGulIcon* returnpressIcon = buttonstate->PressedIcon();
    const CGulIcon* returnhoverIcon = buttonstate->HoverIcon();
    returntext = buttonstate->Text();
    returnhelptext = buttonstate->HelpText();
    
    STIF_ASSERT_EQUALS( nullicon, const_cast<CGulIcon* >( returnnormalIcon ));
    STIF_ASSERT_EQUALS( nullicon, const_cast<CGulIcon* >( returndimmedIcon ));
    STIF_ASSERT_EQUALS( nullicon, const_cast<CGulIcon* >( returnpressIcon ));
    STIF_ASSERT_EQUALS( nullicon, const_cast<CGulIcon* >( returnhoverIcon ));
    STIF_ASSERT_EQUALS( comparetext, returntext );
    STIF_ASSERT_EQUALS( comparetext, returnhelptext );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_BUTTON_STATE );
    buttonstate->DoConstructFromResourceL( reader );
    
    returnnormalIcon = buttonstate->Icon();
    returndimmedIcon = buttonstate->DimmedIcon();
    returnpressIcon = buttonstate->PressedIcon();
    returnhoverIcon = buttonstate->HoverIcon();
    returntext = buttonstate->Text();
    returnhelptext = buttonstate->HelpText();
    
    STIF_ASSERT_NOT_EQUALS( nullicon, const_cast<CGulIcon* >( returnnormalIcon ));
    STIF_ASSERT_NOT_EQUALS( nullicon, const_cast<CGulIcon* >( returndimmedIcon ));
    STIF_ASSERT_NOT_EQUALS( nullicon, const_cast<CGulIcon* >( returnpressIcon ));
    STIF_ASSERT_NOT_EQUALS( nullicon, const_cast<CGulIcon* >( returnhoverIcon ));
    STIF_ASSERT_NOT_EQUALS( comparetext, returntext );
    STIF_ASSERT_NOT_EQUALS( comparetext, returnhelptext );
    CleanupStack::PopAndDestroy( KFlagTwo );
    
    return KErrNone;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSizeChangedStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSizeChangedStateL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    button->ConstructFromResourceL( R_BUTTON );
    CAknButtonState* buttonstate = button->State();
    TPoint lefttoppoint( KFlagZero, KFlagZero );
    TPoint rightbottompoint( KFlagThree, KFlagThree );
    TRect rect( lefttoppoint, rightbottompoint );
    TScaleMode scalemode = EAspectRatioNotPreserved ;
    static_cast<CTestButtonState*>( buttonstate )->DoSizeChanged( rect, scalemode );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBHasTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBHasTextL( CStifItemParser& /*aItem*/ )
    {
    CTestButtonState* buttonstate = new( ELeave ) CTestButtonState( KButtonStateTrue );
    CleanupStack::PushL( buttonstate );
    
    CGulIcon* nullicon = NULL;
    const TDesC textnull = KNullDesC;
    buttonstate->DoConstructL( nullicon, nullicon, nullicon, nullicon, textnull, textnull );
        
    TBool flag( ETrue );
    flag = buttonstate->DoHasText();
    STIF_ASSERT_FALSE( flag );
    
    TBuf< KBufSize > text( KSimpleText );
    buttonstate->SetTextL( text );
    flag = buttonstate->DoHasText();
    STIF_ASSERT_TRUE( flag );
    
    TBuf< KBufSize > textspace( KTextSpace );
    buttonstate->SetTextL( textspace );
    flag = buttonstate->DoHasText();
    STIF_ASSERT_FALSE( flag );
    CleanupStack::PopAndDestroy( buttonstate );
    
    return KErrNone;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBHasHelpL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBHasHelpL( CStifItemParser& /*aItem*/ )
    {
    CTestButtonState* buttonstate = new( ELeave ) CTestButtonState( KButtonStateTrue );
    CleanupStack::PushL( buttonstate );
    
    CGulIcon* nullicon = NULL;
    const TDesC textnull = KNullDesC;
    buttonstate->DoConstructL( nullicon, nullicon, nullicon, nullicon, textnull, textnull );
        
    TBool flag( ETrue );
    flag = buttonstate->DoHasHelp();
    STIF_ASSERT_FALSE( flag );
    
    TBuf< KBufSize > text( KSimpleText );
    buttonstate->SetHelpTextL( text );
    flag = buttonstate->DoHasHelp();
    STIF_ASSERT_TRUE( flag );
    
    TBuf< KBufSize > textspace( KTextSpace );
    buttonstate->SetHelpTextL( textspace );
    flag = buttonstate->DoHasHelp();
    STIF_ASSERT_FALSE( flag );
    CleanupStack::PopAndDestroy( buttonstate );
    
    return KErrNone;
    }

/*
 * Follow function is CAknButton class's public function
 */

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBNewLNullL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBNewLNullL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    STIF_ASSERT_NOT_NULL( button );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBNewLCNullL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBNewLCNullL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewLC();
    STIF_ASSERT_NOT_NULL( button );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBNewLReaderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBNewLReaderL( CStifItemParser& /*aItem*/ )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_BUTTON );
    CAknButton* button = CAknButton::NewL( reader );
    CleanupStack::PushL( button );
    STIF_ASSERT_NOT_NULL( button );
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBNewLCReaderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBNewLCReaderL( CStifItemParser& /*aItem*/ )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_BUTTON );
    CAknButton* button = CAknButton::NewLC( reader );
    STIF_ASSERT_NOT_NULL( button );
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBNewLIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBNewLIdL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL( R_BUTTON );
    CleanupStack::PushL( button );
    STIF_ASSERT_NOT_NULL( button );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBNewLCIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBNewLCIdL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewLC( R_BUTTON );
    STIF_ASSERT_NOT_NULL( button );
    CleanupStack::PopAndDestroy( button );
        
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBNewLComplexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBNewLComplexL( CStifItemParser& /*aItem*/ )
    {
    CFbsBitmap* normalbitmap( NULL );
    CFbsBitmap* normalbitmapmask( NULL );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    AknIconUtils::CreateIconLC( normalbitmap, normalbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* normalicon = CGulIcon::NewL( normalbitmap, normalbitmapmask );
    CleanupStack::PushL( normalicon );
    
    CFbsBitmap* dimmedbitmap( NULL );
    CFbsBitmap* dimmedbitmapmask( NULL );
    AknIconUtils::CreateIconLC( dimmedbitmap, dimmedbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* dimmedicon = CGulIcon::NewL( dimmedbitmap, dimmedbitmapmask );
    CleanupStack::PushL( dimmedicon );
    
    CFbsBitmap* pressedbitmap( NULL );
    CFbsBitmap* pressedbitmapmask( NULL );
    AknIconUtils::CreateIconLC( pressedbitmap, pressedbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* pressedicon = CGulIcon::NewL( pressedbitmap, pressedbitmapmask );
    CleanupStack::PushL( pressedicon );
        
    CFbsBitmap* hoverbitmap( NULL );
    CFbsBitmap* hoverbitmapmask( NULL );
    AknIconUtils::CreateIconLC( hoverbitmap, hoverbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* hovericon = CGulIcon::NewL( hoverbitmap, hoverbitmapmask );
    CleanupStack::PushL( hovericon );
    const TDesC text( KSimpleText );
    const TDesC helptext( KSimpleText );
    
    CAknButton* button = CAknButton::NewL( normalicon, dimmedicon, pressedicon,
                                              hovericon, text, helptext, 
                                                  KButtonFlagsTrue, KStateFlagsTrue );
    CleanupStack::PushL( button );
    STIF_ASSERT_NOT_NULL( button );
    
    CleanupStack::PopAndDestroy( button );
    CleanupStack::Pop( hovericon );
    CleanupStack::Pop( hoverbitmapmask );
    CleanupStack::Pop( hoverbitmap );
    CleanupStack::Pop( pressedicon );
    CleanupStack::Pop( pressedbitmapmask );
    CleanupStack::Pop( pressedbitmap );
    CleanupStack::Pop( dimmedicon );
    CleanupStack::Pop( dimmedbitmapmask );
    CleanupStack::Pop( dimmedbitmap );
    CleanupStack::Pop( normalicon );
    CleanupStack::Pop( normalbitmapmask );
    CleanupStack::Pop( normalbitmap );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBNewLCComplexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBNewLCComplexL( CStifItemParser& /*aItem*/ )
    {
    CFbsBitmap* normalbitmap( NULL );
    CFbsBitmap* normalbitmapmask( NULL );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    AknIconUtils::CreateIconLC( normalbitmap, normalbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* normalicon = CGulIcon::NewL( normalbitmap, normalbitmapmask );
    CleanupStack::PushL( normalicon );
    
    CFbsBitmap* dimmedbitmap( NULL );
    CFbsBitmap* dimmedbitmapmask( NULL );
    AknIconUtils::CreateIconLC( dimmedbitmap, dimmedbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* dimmedicon = CGulIcon::NewL( dimmedbitmap, dimmedbitmapmask );
    CleanupStack::PushL( dimmedicon );
    
    CFbsBitmap* pressedbitmap( NULL );
    CFbsBitmap* pressedbitmapmask( NULL );
    AknIconUtils::CreateIconLC( pressedbitmap, pressedbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* pressedicon = CGulIcon::NewL( pressedbitmap, pressedbitmapmask );
    CleanupStack::PushL( pressedicon );
        
    CFbsBitmap* hoverbitmap( NULL );
    CFbsBitmap* hoverbitmapmask( NULL );
    AknIconUtils::CreateIconLC( hoverbitmap, hoverbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* hovericon = CGulIcon::NewL( hoverbitmap, hoverbitmapmask );
    CleanupStack::PushL( hovericon );
    const TDesC text( KSimpleText );
    const TDesC helptext( KSimpleText );
    
    CAknButton* button = CAknButton::NewLC( normalicon, dimmedicon, pressedicon,
                                              hovericon, text, helptext, 
                                                  KButtonFlagsTrue, KStateFlagsTrue );
    STIF_ASSERT_NOT_NULL( button );
    
    CleanupStack::PopAndDestroy( button );
    CleanupStack::Pop( hovericon );
    CleanupStack::Pop( hoverbitmapmask );
    CleanupStack::Pop( hoverbitmap );
    CleanupStack::Pop( pressedicon );
    CleanupStack::Pop( pressedbitmapmask );
    CleanupStack::Pop( pressedbitmap );
    CleanupStack::Pop( dimmedicon );
    CleanupStack::Pop( dimmedbitmapmask );
    CleanupStack::Pop( dimmedbitmap );
    CleanupStack::Pop( normalicon );
    CleanupStack::Pop( normalbitmapmask );
    CleanupStack::Pop( normalbitmap );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBNewLMoreComplexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBNewLMoreComplexL( CStifItemParser& /*aItem*/ )
    {
    const TDesC text( KSimpleText );
    const TDesC helptext( KSimpleText );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    CAknButton* button = CAknButton::NewL( file, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, text, helptext, KButtonFlagsTrue,
        KStateFlagsTrue );
    
    CleanupStack::PushL( button );
    STIF_ASSERT_NOT_NULL( button );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBNewLCMoreComplexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBNewLCMoreComplexL( CStifItemParser& /*aItem*/ )
    {
    const TDesC text( KSimpleText );
    const TDesC helptext( KSimpleText );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    CAknButton* button = CAknButton::NewLC( file, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, text, helptext, KButtonFlagsTrue,
        KStateFlagsTrue );
    
    STIF_ASSERT_NOT_NULL( button );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBActivateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBActivateLL( CStifItemParser& /*aItem*/ )
    {
    CTestParentControl* parentcontrol = CTestParentControl::NewL();
    CleanupStack::PushL( parentcontrol );
    CCoeEnv::Static()->AppUi()->AddToStackL( parentcontrol );
    TInt err = parentcontrol->TestAknButtonActivateL();
    CCoeEnv::Static()->AppUi()->RemoveFromStack( parentcontrol );
    CleanupStack::PopAndDestroy( parentcontrol );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBConstructFromResourceLReaderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBConstructFromResourceLReaderL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    TBool flag( EFalse );
    flag = button->DetectiStatesIfNull();
    STIF_ASSERT_TRUE( flag );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_BUTTON );
    button->ConstructFromResourceL( reader );
    flag = button->DetectiStatesIfNull();
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( 2 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    button->ConstructFromResourceL( R_BUTTON );
    button->SetButtonFlags( KButtonFlags );
    button->HandleResourceChange( KAknsMessageSkinChange );
    button->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    button->HandleResourceChange( KAknsMessageSkinChange );
    button->HandleResourceChange( KEikMessageFadeAllWindows );
    
    CleanupStack::PopAndDestroy( button );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    button->SetButtonFlags( KAknButtonNoFrame );
    TSize size = button->MinimumSize();
    STIF_ASSERT_EQUALS( TSize( KFlagZero, KFlagZero ), size );
    
    button->SetButtonFlags( KAknButtonSizeFitText );
    size = button->MinimumSize();
    STIF_ASSERT_NOT_EQUALS( TSize( KFlagZero, KFlagZero ), size );
    
    button->SetButtonFlags( KAknButtonTextInsideFrame );
    TSize returnsize = button->MinimumSize();
    STIF_ASSERT_NOT_EQUALS( TSize( KFlagZero, KFlagZero ), returnsize );
    STIF_ASSERT_NOT_EQUALS( size, returnsize );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetDimmedL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    const TDesC text( KNullDesC );
    const TDesC helptext( KNullDesC );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    button->DoConstructLMoreComplexL( file, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, 0,
        0, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, text, helptext, KFlagOne );
    button->SetDimmed( ETrue );
    TBool dimmedif = button->IsDimmed();
    STIF_ASSERT_TRUE( dimmedif );
    
    button->SetDimmed( EFalse );
    dimmedif = button->IsDimmed();
    STIF_ASSERT_FALSE( dimmedif );
    CleanupStack::PopAndDestroy( button );
    
    CAknButton* buttonresource = CAknButton::NewL();
    CleanupStack::PushL( buttonresource );
    buttonresource->ConstructFromResourceL( R_BUTTON );
    buttonresource->SetDimmed( ETrue );
    dimmedif = buttonresource->IsDimmed();
    STIF_ASSERT_TRUE( dimmedif );
    
    buttonresource->SetDimmed( EFalse );
    dimmedif = buttonresource->IsDimmed();
    STIF_ASSERT_FALSE( dimmedif );
    CleanupStack::PopAndDestroy( buttonresource );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBOfferKeyEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBOfferKeyEventLL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    TKeyEvent keyevent;
    keyevent.iScanCode = EStdKeyDevice3;
    button->SetDimmed( ETrue );
    TKeyResponse response = button->OfferKeyEventL( keyevent, EEventKeyDown );
    STIF_ASSERT_EQUALS( EKeyWasNotConsumed, response );
    
    button->SetDimmed( EFalse );
    button->SetiKeyDownReported( EFalse );
    button->SetiButtonPressed( EFalse );
    button->SetButtonFlags( KAknButtonReportOnKeyDown );
    response = button->OfferKeyEventL( keyevent, EEventKeyDown );
    TBool keydownreported = button->GetiKeyDownReported();
    TBool buttonpressed = button->GetiButtonPressed();
    STIF_ASSERT_EQUALS( EKeyWasConsumed, response );
    STIF_ASSERT_TRUE( keydownreported );
    STIF_ASSERT_TRUE( buttonpressed );
    
    button->SetDimmed( EFalse );
    button->SetiKeyDownReported( EFalse );
    button->SetiButtonPressed( EFalse );
    button->SetButtonFlags( KAknButtonKeyRepeat );
    response = button->OfferKeyEventL( keyevent, EEventKeyDown );
    keydownreported = button->GetiKeyDownReported();
    buttonpressed = button->GetiButtonPressed();
    STIF_ASSERT_EQUALS( EKeyWasConsumed, response );
    STIF_ASSERT_TRUE( keydownreported );
    STIF_ASSERT_TRUE( buttonpressed );
    
    button->SetDimmed( EFalse );
    button->SetiKeyDownReported( EFalse );
    button->SetiButtonPressed( EFalse );
    button->SetButtonFlags( KAknButtonReportOnLongPress );
    response = button->OfferKeyEventL( keyevent, EEventKeyDown );
    keydownreported = button->GetiKeyDownReported();
    buttonpressed = button->GetiButtonPressed();
    STIF_ASSERT_EQUALS( EKeyWasConsumed, response );
    STIF_ASSERT_TRUE( keydownreported );
    STIF_ASSERT_TRUE( buttonpressed );
    CleanupStack::PopAndDestroy( button );
    
    CTestButton* buttontwo = CTestButton::NewL();
    CleanupStack::PushL( buttontwo );
    buttontwo->SetButtonFlags( KAknButtonReportOnLongPress );
    buttontwo->SetiButtonPressed( ETrue );
    buttontwo->SetiKeyDownReported( ETrue );
    buttontwo->OfferKeyEventL( keyevent, EEventKeyDown );
    response = buttontwo->OfferKeyEventL( keyevent, EEventKeyUp );
    keydownreported = button->GetiKeyDownReported();
    buttonpressed = button->GetiButtonPressed();
    STIF_ASSERT_EQUALS( EKeyWasConsumed, response );
    STIF_ASSERT_FALSE( keydownreported );
    STIF_ASSERT_FALSE( buttonpressed );
    
    buttontwo->SetButtonFlags( KAknButtonRequestExitOnButtonUpEvent );
    buttontwo->SetiButtonPressed( ETrue );
    buttontwo->SetiKeyDownReported( ETrue );
    response = buttontwo->OfferKeyEventL( keyevent, EEventKeyUp );
    keydownreported = button->GetiKeyDownReported();
    buttonpressed = button->GetiButtonPressed();
    STIF_ASSERT_EQUALS( EKeyWasConsumed, response );
    STIF_ASSERT_FALSE( keydownreported );
    STIF_ASSERT_FALSE( buttonpressed );
    
    CleanupStack::PopAndDestroy( buttontwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBMakeVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBMakeVisibleL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    button->ConstructFromResourceL( R_BUTTON );
    
    TBool controlifvisible = button->IsVisible();
    STIF_ASSERT_TRUE( controlifvisible );
    
    button->MakeVisible( EFalse );
    controlifvisible = button->IsVisible();
    STIF_ASSERT_FALSE( controlifvisible );
    
    CleanupStack::PopAndDestroy( button );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBPrepareForFocusLossLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBPrepareForFocusLossLL( CStifItemParser& /*aItem*/ )
    {
    CTestParentControl* parentcontrol = CTestParentControl::NewL();
    CleanupStack::PushL( parentcontrol );
    CCoeEnv::Static()->AppUi()->AddToStackL( parentcontrol );
    TInt err = parentcontrol->TestAknButtonPrepareForFocusLossLL();
    CCoeEnv::Static()->AppUi()->RemoveFromStack( parentcontrol );
    CleanupStack::PopAndDestroy( parentcontrol );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBPrepareForFocusGainLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBPrepareForFocusGainLL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    button->ConstructFromResourceL( R_BUTTON );
    
    button->PrepareForFocusGainL();
    TBool showhelpif = button->DetectIfShowHelp();
    STIF_ASSERT_TRUE( showhelpif );
    
    button->MakeVisible( EFalse );
    button->PrepareForFocusGainL();
    showhelpif = button->DetectIfShowHelp();
    STIF_ASSERT_FALSE( showhelpif );
    
    CleanupStack::PopAndDestroy( button );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBPrepareForFocusGainLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    button->ConstructFromResourceL( R_BUTTON );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TInt err = KErrNone;
    TRAP( err, button->HandlePointerEventL( event ) );
    
    CleanupStack::PopAndDestroy( button );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBPositionChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBPositionChangedL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    button->PositionChanged();
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBConstructFromResourceLIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBConstructFromResourceLIdL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    TBool flag( EFalse );
    flag = button->DetectiStatesIfNull();
    STIF_ASSERT_TRUE( flag );
    
    button->ConstructFromResourceL( R_BUTTON );
    flag = button->DetectiStatesIfNull();
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetCurrentStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetCurrentStateL( CStifItemParser& aItem )
    {
    TInt err( KErrNone );
    err = TestGBChangeStateL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBAddStateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBAddStateLL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    TBool flag = button->DetectiStatesIfNull();
    STIF_ASSERT_TRUE( flag );
    TInt returncount = button->DetectiStatesCount();
    STIF_ASSERT_EQUALS( KFlagZero, returncount );
    
    CFbsBitmap* normalbitmap( NULL );
    CFbsBitmap* normalbitmapmask( NULL );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    AknIconUtils::CreateIconLC( normalbitmap, normalbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* normalicon = CGulIcon::NewL( normalbitmap, normalbitmapmask );
    CleanupStack::PushL( normalicon );
    
    CFbsBitmap* dimmedbitmap( NULL );
    CFbsBitmap* dimmedbitmapmask( NULL );
    AknIconUtils::CreateIconLC( dimmedbitmap, dimmedbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* dimmedicon = CGulIcon::NewL( dimmedbitmap, dimmedbitmapmask );
    CleanupStack::PushL( dimmedicon );
    
    CFbsBitmap* pressedbitmap( NULL );
    CFbsBitmap* pressedbitmapmask( NULL );
    AknIconUtils::CreateIconLC( pressedbitmap, pressedbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* pressedicon = CGulIcon::NewL( pressedbitmap, pressedbitmapmask );
    CleanupStack::PushL( pressedicon );
        
    CFbsBitmap* hoverbitmap( NULL );
    CFbsBitmap* hoverbitmapmask( NULL );
    AknIconUtils::CreateIconLC( hoverbitmap, hoverbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* hovericon = CGulIcon::NewL( hoverbitmap, hoverbitmapmask );
    CleanupStack::PushL( hovericon );
    const TDesC text( KSimpleText );
    const TDesC helptext( KSimpleText );
    button->AddStateL( normalicon, dimmedicon, pressedicon, 
                          hovericon, text,helptext, KAknButtonNoFrame );
    flag = button->DetectiStatesIfNull();
    STIF_ASSERT_FALSE( flag );
    returncount = button->DetectiStatesCount();
    STIF_ASSERT_EQUALS( KFlagOne, returncount );

    CleanupStack::Pop( hovericon );
    CleanupStack::Pop( hoverbitmapmask );
    CleanupStack::Pop( hoverbitmap );
    CleanupStack::Pop( pressedicon );
    CleanupStack::Pop( pressedbitmapmask );
    CleanupStack::Pop( pressedbitmap );
    CleanupStack::Pop( dimmedicon );
    CleanupStack::Pop( dimmedbitmapmask );
    CleanupStack::Pop( dimmedbitmap );
    CleanupStack::Pop( normalicon );
    CleanupStack::Pop( normalbitmapmask );
    CleanupStack::Pop( normalbitmap );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBAddStateLComplexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBAddStateLComplexL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    TBool flag = button->DetectiStatesIfNull();
    STIF_ASSERT_TRUE( flag );
    TInt returncount = button->DetectiStatesCount();
    STIF_ASSERT_EQUALS( KFlagZero, returncount );
    
    const TDesC text( KSimpleText );
    const TDesC helptext( KSimpleText );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    button->AddStateL( file, EMbmAvkonQgn_indi_mic,
            EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
            EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
            EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
            EMbmAvkonQgn_indi_mic_mask, text, helptext, KAknButtonNoFrame,
            KAknsIIDNone, KAknsIIDNone, KAknsIIDNone, KAknsIIDNone );
    flag = button->DetectiStatesIfNull();
    STIF_ASSERT_FALSE( flag );
    returncount = button->DetectiStatesCount();
    STIF_ASSERT_EQUALS( KFlagOne, returncount );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetButtonFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetButtonFlagsL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    TInt returnflags = button->ButtonFlags();
    STIF_ASSERT_EQUALS( KFlagZero, returnflags );
    
    button->SetButtonFlags( KAknButtonNoFrame );
    returnflags = button->ButtonFlags();
    STIF_ASSERT_EQUALS( KAknButtonNoFrame, returnflags );
    
    button->SetButtonFlags( KAknButtonHitTest );
    returnflags = button->ButtonFlags();
    STIF_ASSERT_EQUALS( KAknButtonHitTest, returnflags );
    
    CleanupStack::PopAndDestroy( button );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetFrameAndCenterIdsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetFrameAndCenterIdsL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    TAknsItemID testid = KAknsIIDNone;
    button->SetFrameAndCenterIds( testid, testid, testid, testid,
        testid, testid, testid, testid, testid, testid );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetBackgroundIdsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetBackgroundIdsL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    TAknsItemID testid = KAknsIIDNone;
    button->SetBackgroundIds( testid, testid, testid, testid, testid );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetTextFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetTextFontL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    const CFont* testfont = CEikonEnv::Static( )->DenseFont();
    button->SetTextFont( testfont );
    const CFont* returnfont = button->GetiFont();
    STIF_ASSERT_EQUALS( testfont, returnfont );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetTextColorIdsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetTextColorIdsL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    TAknsItemID testid = KAknsIIDNone;
    TInt textcolorindex = KFlagThree;
    button->SetTextColorIds( testid, textcolorindex );
    TAknsItemID returnId = button->GetiTextColorTableId();
    TInt returnindex = button->GetiTextColorIndex();
    STIF_ASSERT_EQUALS( testid, returnId );
    STIF_ASSERT_EQUALS( textcolorindex, returnindex );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetTextHorizontalAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetTextHorizontalAlignmentL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    CGraphicsContext::TTextAlign testalign = CGraphicsContext::ERight;
    button->SetTextHorizontalAlignment( testalign );
    CGraphicsContext::TTextAlign returntextalign = 
        button->GetiHorizontalAlignment();
    STIF_ASSERT_EQUALS( testalign, returntextalign );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetTextVerticalAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetTextVerticalAlignmentL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    CAknButton::TAlignment testalignment = CAknButton::EBottom;
    button->SetTextVerticalAlignment( testalignment );
    CAknButton::TAlignment returntextalign = 
        button->GetiVerticalAlignment();
    STIF_ASSERT_EQUALS( testalignment, returntextalign );
    
    CleanupStack::PopAndDestroy( button );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetTextAndIconAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetTextAndIconAlignmentL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    CAknButton::TTextAndIconAlignment testalignment = CAknButton::EIconOverText;
    button->SetTextAndIconAlignment( testalignment );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetTextUnderlineStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetTextUnderlineStyleL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    TFontUnderline underline = EUnderlineOn;
    button->SetTextUnderlineStyle( underline );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetIconScaleModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetIconScaleModeL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    TScaleMode scalemode = EAspectRatioPreservedAndUnusedSpaceRemoved;
    button->SetIconScaleMode( scalemode );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetIconHorizontalAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetIconHorizontalAlignmentL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    CAknButton::TAlignment testalignment = CAknButton::EBottom;
    button->SetIconHorizontalAlignment( testalignment );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetIconVerticalAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetIconVerticalAlignmentL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    CAknButton::TAlignment testalignment = CAknButton::EBottom;
    button->SetIconVerticalAlignment( testalignment );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetHelpNoteTimeoutsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetHelpNoteTimeoutsL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    TInt beforetimeout = KMinusone;
    TInt viewtimeout = KMinusone;
    button->SetHelpNoteTimeouts( beforetimeout, viewtimeout );
    TInt returnbeforetimeout = button->GetiHelpNoteWaitInterval();
    TInt returnviewtimeout = button->GetiHelpNoteInViewInterval();
    STIF_ASSERT_EQUALS( KTimeoutBeforeHelpNote, returnbeforetimeout );
    STIF_ASSERT_EQUALS( KTimeoutInViewHelpNote, returnviewtimeout );
    
    beforetimeout = KFlagTwo;
    viewtimeout = KFlagTwo;
    button->SetHelpNoteTimeouts( beforetimeout, viewtimeout );
    returnbeforetimeout = button->GetiHelpNoteWaitInterval();
    returnviewtimeout = button->GetiHelpNoteInViewInterval();
    STIF_ASSERT_EQUALS( KFlagTwo, returnbeforetimeout );
    STIF_ASSERT_EQUALS( KFlagTwo, returnviewtimeout );
    
    CleanupStack::PopAndDestroy( button );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetKeyRepeatIntervalL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetKeyRepeatIntervalL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    TInt keyrepeatdelay = KFlagTwo;
    TInt keyrepeatinterval = KFlagTwo;
    button->SetKeyRepeatInterval( keyrepeatdelay, keyrepeatinterval );
    TInt returnkeyrepeatdelay = button->GetiKeyRepeatDelay();
    TInt returnkeyrepeatinterval = button->GetiKeyRepeatInterval();
    STIF_ASSERT_EQUALS( KKeyRepeatDelay, returnkeyrepeatdelay );
    STIF_ASSERT_EQUALS( KKeyRepeatInterval, returnkeyrepeatinterval );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetLongPressIntervalL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetLongPressIntervalL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    button->SetLongPressInterval( KFlagTwo );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBStateIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBStateIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    TInt returnindex = button->StateIndex();
    STIF_ASSERT_EQUALS( KFlagZero, returnindex );
    
    button->ConstructFromResourceL( R_BUTTON );
    button->SetCurrentState( KFlagThree, ETrue );
    returnindex = button->StateIndex();
    STIF_ASSERT_EQUALS( KFlagOne, returnindex );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBEnablePictographsLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBEnablePictographsLL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    CPictographAnimatorCallBack callback;
    CAknPictographInterface* pictographinterface = CAknPictographInterface::NewL(
        *button, callback );
    TInt err( KErrNone );
    TRAP( err, button->EnablePictographsL( *pictographinterface ) );
    CleanupStack::PopAndDestroy( button );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBDisablePictographsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBDisablePictographsL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    button->DisablePictographs();
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetHighlightRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetHighlightRectL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    TRect rect = button->HighlightRect();
    TRect comparerect( KFlagZero, KFlagZero, KFlagZero, KFlagZero );
    STIF_ASSERT_EQUALS( comparerect, rect );
    
    const TRect setrect( KFlagThree, KFlagThree, KFlagThree, KFlagThree );
    button->SetHighlightRect( setrect );
    TRect returnrect = button->HighlightRect();
    STIF_ASSERT_NOT_EQUALS( comparerect, returnrect );
    STIF_ASSERT_EQUALS( setrect, returnrect );
    
    CleanupStack::PopAndDestroy( button );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBHighlightRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBHighlightRectL( CStifItemParser& aItem )
    {
    TInt err = TestGBSetHighlightRectL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetTooltipPositionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetTooltipPositionL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    CAknButton::TTooltipPosition position = CAknButton::EPositionRight;
    button->SetTooltipPosition( position );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetRequestExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetRequestExitL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    button->SetButtonFlags( KAknButtonNoFrame );
    button->SetRequestExit( ETrue );
    TInt returnflags = button->ButtonFlags();
    STIF_ASSERT_EQUALS( KFlagSixtyEight, returnflags );
    
    button->SetRequestExit( EFalse );
    returnflags = button->ButtonFlags();
    STIF_ASSERT_EQUALS( KFlagFour, returnflags );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBIsDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBIsDimmedL( CStifItemParser& aItem )
    {
    TInt err = TestGBSetDimmedL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetDimmedHelpTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetDimmedHelpTextLL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    TBool flag = button->DetectIfiDimmedHelpText();
    STIF_ASSERT_FALSE( flag );
    
    const TDesC dimmedhelptext( KSimpleText );
    button->SetDimmedHelpTextL( dimmedhelptext );
    flag = button->DetectIfiDimmedHelpText();
    STIF_ASSERT_TRUE( flag );
    
    CleanupStack::PopAndDestroy( button );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBStateL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    CAknButtonState* buttonstate = button->State();
    STIF_ASSERT_NULL( buttonstate );
    
    button->ConstructFromResourceL( R_BUTTON );
    buttonstate = button->State( KFlagZero );
    STIF_ASSERT_NOT_NULL( buttonstate );
    
    button->SetCurrentState( KFlagThree, ETrue );
    buttonstate = button->State();
    STIF_ASSERT_NOT_NULL( buttonstate );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBStateComplexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBStateComplexL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    CAknButtonState* buttonstate = button->State( KFlagZero );
    STIF_ASSERT_NULL( buttonstate );
    
    buttonstate = button->State( KFlagOne );
    STIF_ASSERT_NULL( buttonstate );
    
    button->ConstructFromResourceL( R_BUTTON );
    buttonstate = button->State( KFlagZero );
    STIF_ASSERT_NOT_NULL( buttonstate );
    
    buttonstate = button->State( KFlagOne );
    STIF_ASSERT_NOT_NULL( buttonstate );
    
    buttonstate = button->State( KMinusone );
    STIF_ASSERT_NULL( buttonstate );
    
    buttonstate = button->State( KFlagTen );
    STIF_ASSERT_NULL( buttonstate );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBButtonFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBButtonFlagsL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    TInt buttonflag = button->ButtonFlags();
    STIF_ASSERT_EQUALS( KFlagZero, buttonflag );
    
    CAknButton* buttonresource = CAknButton::NewL( R_BUTTON );
    CleanupStack::PushL( buttonresource );
    buttonflag = buttonresource->ButtonFlags();
    STIF_ASSERT_EQUALS( KAknButtonNoFrame, buttonflag );
    CleanupStack::PopAndDestroy( buttonresource );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetMarginsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetMarginsL( CStifItemParser& /*aItem*/ )
    {
    CTestParentControl* parentcontrol = CTestParentControl::NewL();
    CleanupStack::PushL( parentcontrol );
    CCoeEnv::Static()->AppUi()->AddToStackL( parentcontrol );
    TInt err = parentcontrol->TestAknButtonSetMarginsL();
    CCoeEnv::Static()->AppUi()->RemoveFromStack( parentcontrol );
    CleanupStack::PopAndDestroy( parentcontrol );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSetIconSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSetIconSizeL( CStifItemParser& /*aItem*/ )
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    TInt returnvalue = button->SetIconSize( TSize( KFlagTwo, KFlagTwo ) );
    STIF_ASSERT_EQUALS( KErrNone, returnvalue );

    CFbsBitmap* normalbitmap( NULL );
    CFbsBitmap* normalbitmapmask( NULL );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    AknIconUtils::CreateIconLC( normalbitmap, normalbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* normalicon = CGulIcon::NewL( normalbitmap, normalbitmapmask );
    CleanupStack::PushL( normalicon );
    
    CFbsBitmap* pressedbitmap( NULL );
    CFbsBitmap* pressedbitmapmask( NULL );
    AknIconUtils::CreateIconLC( pressedbitmap, pressedbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* pressedicon = CGulIcon::NewL( pressedbitmap, pressedbitmapmask );
    CleanupStack::PushL( pressedicon );
        
    CFbsBitmap* hoverbitmap( NULL );
    CFbsBitmap* hoverbitmapmask( NULL );
    AknIconUtils::CreateIconLC( hoverbitmap, hoverbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* hovericon = CGulIcon::NewL( hoverbitmap, hoverbitmapmask );
    CleanupStack::PushL( hovericon );
    const TDesC text( KSimpleText );
    const TDesC helptext( KSimpleText );
    button->AddStateL( normalicon, NULL, pressedicon, 
                          hovericon, text,helptext, KAknButtonNoFrame );
    button->SetDimmed( ETrue );
    returnvalue = button->SetIconSize( TSize( KFlagTwo, KFlagTwo ) );
    STIF_ASSERT_EQUALS( KFlagZero, returnvalue );
    
    button->ConstructFromResourceL( R_BUTTON );
    returnvalue = button->SetIconSize( TSize( KFlagTwo, KFlagTwo ) );
    STIF_ASSERT_EQUALS( KMinusone, returnvalue );
    
    CleanupStack::Pop( hovericon );
    CleanupStack::Pop( hoverbitmapmask );
    CleanupStack::Pop( hoverbitmap );
    CleanupStack::Pop( pressedicon );
    CleanupStack::Pop( pressedbitmapmask );
    CleanupStack::Pop( pressedbitmap );
    CleanupStack::Pop( normalicon );
    CleanupStack::Pop( normalbitmapmask );
    CleanupStack::Pop( normalbitmap );
    CleanupStack::PopAndDestroy( button );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBResetStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBResetStateL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    TBool buttonpressed = button->GetiButtonPressed();
    STIF_ASSERT_FALSE( buttonpressed );
    button->SetiButtonPressed( ETrue );
    buttonpressed = button->GetiButtonPressed();
    STIF_ASSERT_TRUE( buttonpressed );
    
    button->ResetState();
    buttonpressed = button->GetiButtonPressed();
    STIF_ASSERT_FALSE( buttonpressed );
    
    CleanupStack::PopAndDestroy( button );
    return KErrNone;
    }
/*
 * Follow function is CAknButton class's protected function
 */

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBConstructorL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    STIF_ASSERT_NOT_NULL( button );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBConstructLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBConstructLL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    button->SetButtonFlags( KAknButtonHitTest );
    button->DoConstructL();
    CGraphicsContext::TTextAlign textalignment = button->GetiHorizontalAlignment();
    STIF_ASSERT_EQUALS( CGraphicsContext::ECenter, textalignment );
    CleanupStack::PopAndDestroy( button );
    
    CTestButton* buttontwo = CTestButton::NewL();
    CleanupStack::PushL( buttontwo );
    buttontwo->SetButtonFlags( KAknButtonNoFrame );
    buttontwo->DoConstructL();
    textalignment = buttontwo->GetiHorizontalAlignment();
    STIF_ASSERT_EQUALS( CGraphicsContext::ECenter, textalignment );
    CleanupStack::PopAndDestroy( buttontwo );
    
    CTestButton* buttonthree = CTestButton::NewL();
    CleanupStack::PushL( buttonthree );
    buttonthree->SetButtonFlags( KAknButtonTextLeft );
    buttonthree->DoConstructL();
    textalignment = buttonthree->GetiHorizontalAlignment();
    STIF_ASSERT_EQUALS( CGraphicsContext::ELeft, textalignment );
    
    CleanupStack::PopAndDestroy( buttonthree );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBConstructLComplexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBConstructLComplexL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    TBool flag = button->DetectiStatesIfNull();
    STIF_ASSERT_TRUE( flag );
    
    TInt returncount = button->DetectiStatesCount();
    STIF_ASSERT_EQUALS( KFlagZero, returncount );
    
    CFbsBitmap* normalbitmap( NULL );
    CFbsBitmap* normalbitmapmask( NULL );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    AknIconUtils::CreateIconLC( normalbitmap, normalbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* normalicon = CGulIcon::NewL( normalbitmap, normalbitmapmask );
    CleanupStack::PushL( normalicon );
    
    CFbsBitmap* dimmedbitmap( NULL );
    CFbsBitmap* dimmedbitmapmask( NULL );
    AknIconUtils::CreateIconLC( dimmedbitmap, dimmedbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* dimmedicon = CGulIcon::NewL( dimmedbitmap, dimmedbitmapmask );
    CleanupStack::PushL( dimmedicon );
    
    CFbsBitmap* pressedbitmap( NULL );
    CFbsBitmap* pressedbitmapmask( NULL );
    AknIconUtils::CreateIconLC( pressedbitmap, pressedbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* pressedicon = CGulIcon::NewL( pressedbitmap, pressedbitmapmask );
    CleanupStack::PushL( pressedicon );
        
    CFbsBitmap* hoverbitmap( NULL );
    CFbsBitmap* hoverbitmapmask( NULL );
    AknIconUtils::CreateIconLC( hoverbitmap, hoverbitmapmask, 
        file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* hovericon = CGulIcon::NewL( hoverbitmap, hoverbitmapmask );
    CleanupStack::PushL( hovericon );
    const TDesC text( KSimpleText );
    const TDesC helptext( KSimpleText );
    
    button->DoConstructLComplexL( normalicon, dimmedicon, 
        pressedicon, hovericon, text, helptext, KFlagOne );
    
    flag = button->DetectiStatesIfNull();
    STIF_ASSERT_FALSE( flag );
    
    returncount = button->DetectiStatesCount();
    STIF_ASSERT_EQUALS( KFlagOne, returncount );
    
    CleanupStack::Pop( hovericon );
    CleanupStack::Pop( hoverbitmapmask );
    CleanupStack::Pop( hoverbitmap );
    CleanupStack::Pop( pressedicon );
    CleanupStack::Pop( pressedbitmapmask );
    CleanupStack::Pop( pressedbitmap );
    CleanupStack::Pop( dimmedicon );
    CleanupStack::Pop( dimmedbitmapmask );
    CleanupStack::Pop( dimmedbitmap );
    CleanupStack::Pop( normalicon );
    CleanupStack::Pop( normalbitmapmask );
    CleanupStack::Pop( normalbitmap );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBConstructLMoreComplexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBConstructLMoreComplexL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    TBool flag = button->DetectiStatesIfNull();
    STIF_ASSERT_TRUE( flag );
    
    TInt returncount = button->DetectiStatesCount();
    STIF_ASSERT_EQUALS( KFlagZero, returncount );
    
    const TDesC text( KSimpleText );
    const TDesC helptext( KSimpleText );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    button->DoConstructLMoreComplexL( file, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, text, helptext, KFlagOne );
    
    flag = button->DetectiStatesIfNull();
    STIF_ASSERT_FALSE( flag );
    
    returncount = button->DetectiStatesCount();
    STIF_ASSERT_EQUALS( KFlagOne, returncount );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    CTestParentControl* parentcontrol = CTestParentControl::NewL();
    CleanupStack::PushL( parentcontrol );
    CCoeEnv::Static()->AppUi()->AddToStackL( parentcontrol );
    TInt err = parentcontrol->TestAknButtonSizeChangedL();
    CCoeEnv::Static()->AppUi()->RemoveFromStack( parentcontrol );
    CleanupStack::PopAndDestroy( parentcontrol );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBFocusChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBFocusChangedL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    button->SetFocus( EFalse );
    button->SetiShowHelp( ETrue );
    button->SetiButtonPressed( ETrue );
    button->DoFocusChanged( EDrawNow );
    TBool showhelp = button->GetiShowHelp();
    STIF_ASSERT_FALSE( showhelp );
    
    button->DoFocusChanged( ENoDrawNow );
    showhelp = button->GetiShowHelp();
    STIF_ASSERT_FALSE( showhelp );
    
    button->DoFocusChanged( ENoDrawNow );
    button->SetiShowHelp( ETrue );
    button->SetFocus( ETrue );
    button->DoFocusChanged( ENoDrawNow );
    showhelp = button->GetiShowHelp();
    STIF_ASSERT_FALSE( showhelp );
    
    button->DoFocusChanged( EDrawNow );
    showhelp = button->GetiShowHelp();
    STIF_ASSERT_FALSE( showhelp );
    
    CleanupStack::PopAndDestroy( button );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBExtensionInterfaceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBExtensionInterfaceL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    void* returnvalue = button->DoExtensionInterface( KUidInterface );
    STIF_ASSERT_NULL( returnvalue );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBChangeStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBChangeStateL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    TInt returnindex = button->DoChangeState( ETrue );
    STIF_ASSERT_EQUALS( KMinusone, returnindex );
    
    button->ConstructFromResourceL( R_BUTTON );
    button->SetCurrentState( KFlagTwo, ETrue );
    returnindex = button->DoChangeState( ETrue );
    STIF_ASSERT_EQUALS( KFlagOne, returnindex );
    
    returnindex = KFlagZero;
    button->SetCurrentState( KFlagTwo, EFalse );
    returnindex = button->DoChangeState( EFalse );
    STIF_ASSERT_EQUALS( KFlagOne, returnindex );
    
    button->SetCurrentState( KFlagThree, ETrue );
    returnindex = button->DoChangeState( ETrue );
    STIF_ASSERT_EQUALS( KFlagZero, returnindex );
    
    button->SetCurrentState( KFlagThree, EFalse );
    returnindex = button->DoChangeState( EFalse );
    STIF_ASSERT_EQUALS( KFlagZero, returnindex );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBGetCurrentTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBGetCurrentTextL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    TDesC nullvalue( KNullDesC );
    TDesC returnvalue( KNullDesC );
    TBool flag = button->DetectiStatesIfNull();
    STIF_ASSERT_TRUE( flag );
    returnvalue = button->DoGetCurrentText();
    STIF_ASSERT_EQUALS( nullvalue, returnvalue );
    
    button->ConstructFromResourceL( R_BUTTON );
    flag = button->DetectiStatesIfNull();
    STIF_ASSERT_FALSE( flag );
    returnvalue = button->DoGetCurrentText();
    STIF_ASSERT_NOT_EQUALS( nullvalue, returnvalue );
    CleanupStack::PopAndDestroy( button );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBGetCurrentIconL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBGetCurrentIconL( CStifItemParser& /*aItem*/ )
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    const CGulIcon* compareicon = button->DoGetCurrentIcon();
    STIF_ASSERT_NULL( compareicon );
    
    button->ConstructFromResourceL( R_BUTTON );
    button->SetiButtonPressed( ETrue );
    compareicon = button->DoGetCurrentIcon();
    STIF_ASSERT_NOT_NULL( compareicon );
    
    button->SetiButtonPressed( EFalse );
    button->SetDimmed( ETrue );
    compareicon = button->DoGetCurrentIcon();
    STIF_ASSERT_NOT_NULL( compareicon );
    
    button->SetDimmed( EFalse );
    compareicon = button->DoGetCurrentIcon();
    STIF_ASSERT_NOT_NULL( compareicon );
    
    CleanupStack::PopAndDestroy( button );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBShowHelpLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBShowHelpLL( CStifItemParser& /*aItem*/ )
    {
    CTestParentControl* parentcontrol = CTestParentControl::NewL();
    CleanupStack::PushL( parentcontrol );
    CCoeEnv::Static()->AppUi()->AddToStackL( parentcontrol );
    TInt err = parentcontrol->TestAknButtonShowHelpLL();
    CCoeEnv::Static()->AppUi()->RemoveFromStack( parentcontrol );
    CleanupStack::PopAndDestroy( parentcontrol );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGENERICBUTTON::TestGBHideHelpL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGENERICBUTTON::TestGBHideHelpL( CStifItemParser& aItem )
    {
    TInt err = TestGBShowHelpLL( aItem );
    return err;
    }
//End file


