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
* Description:  test aknchoicelist.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknchoicelist.h>
#include <aknbutton.h>
#include <eiklabel.h> 
#include <coecobs.h>
#include <testsdkchoicelist.rsg>

#include "testsdkchoicelist.h"
#include "testsdkchoicelistcontrol.h"

//CONST
const TInt KLength = 20;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKChoiceList::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKChoiceList::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestCLNewL", CTestSDKChoiceList::TestCLNewL ),
        ENTRY( "TestCLNewLC", CTestSDKChoiceList::TestCLNewLC ),
        ENTRY( "TestCLShowChoiceListL", CTestSDKChoiceList::TestCLShowChoiceListL ),
        ENTRY( "TestCLSetSelectedIndexL", CTestSDKChoiceList::TestCLSetSelectedIndexL ),
        ENTRY( "TestCLSelectedIndexL", CTestSDKChoiceList::TestCLSelectedIndexL ),
        ENTRY( "TestCLSetItemsL", CTestSDKChoiceList::TestCLSetItemsL ),
        ENTRY( "TestCLSetItemsLeaveL", CTestSDKChoiceList::TestCLSetItemsLeaveL ),
        ENTRY( "TestCLAddItemL", CTestSDKChoiceList::TestCLAddItemL ),
        ENTRY( "TestCLRemoveItemL", CTestSDKChoiceList::TestCLRemoveItemL ),
        ENTRY( "TestCLSetFlagsL", CTestSDKChoiceList::TestCLSetFlagsL ),
        ENTRY( "TestCLFlagsL", CTestSDKChoiceList::TestCLFlagsL ),
        ENTRY( "TestCLSetButtonL", CTestSDKChoiceList::TestCLSetButtonL ),
        ENTRY( "TestCLHideChoiceListL", CTestSDKChoiceList::TestCLHideChoiceListL ),
        ENTRY( "TestCLSetTooltipTextL", CTestSDKChoiceList::TestCLSetTooltipTextL ),
        ENTRY( "TestCLSetTooltipTimeoutsL", CTestSDKChoiceList::TestCLSetTooltipTimeoutsL ),
        ENTRY( "TestCLSetTooltipPositionL", CTestSDKChoiceList::TestCLSetTooltipPositionL ),
        ENTRY( "TestCLComponentControlL", CTestSDKChoiceList::TestCLComponentControlL ),
        ENTRY( "TestCLCountComponentControlsL", CTestSDKChoiceList::TestCLCountComponentControlsL ),
        ENTRY( "TestCLMinimumSizeL", CTestSDKChoiceList::TestCLMinimumSizeL ),
        ENTRY( "TestCLHandleResourceChangeL", CTestSDKChoiceList::TestCLHandleResourceChangeL ),
        ENTRY( "TestCLOfferKeyEventL", CTestSDKChoiceList::TestCLOfferKeyEventL ),
        ENTRY( "TestCLDrawL", CTestSDKChoiceList::TestCLDrawL ),
        ENTRY( "TestCLPositionChangedL", CTestSDKChoiceList::TestCLPositionChangedL ),
        ENTRY( "TestCLHandleControlEventL", CTestSDKChoiceList::TestCLHandleControlEventL ),
        ENTRY( "TestCLInsertItemL", CTestSDKChoiceList::TestCLInsertItemL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLNewL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLNewL( CStifItemParser& /*aItem*/ )
    {
    if(iChoiceList)
        {
        delete iChoiceList;
        iChoiceList = NULL;
        }
    
    const TInt num = 5;
    CDesCArrayFlat* array = new (ELeave) CDesCArrayFlat( num );
    CleanupStack::PushL( array );
    STIF_ASSERT_NOT_NULL( array );
    
    _LIT( KItem, "item" );
    TBuf<KLength> item( KItem );
    array->AppendL( item );
    
    _LIT( KButton, "button" );
    TBuf<KLength> button( KButton );
    CAknButton* btn = CAknButton::NewLC( NULL, NULL, NULL, NULL, button, KNullDesC, KAknButtonNoFrame, 0 );
    STIF_ASSERT_NOT_NULL( btn );
    
    CTestSDKChoiceListControl* control = CTestSDKChoiceListControl::NewLC();
    STIF_ASSERT_NOT_NULL( control );
    
    CleanupStack::Pop( control );
    CleanupStack::Pop( btn );
    CleanupStack::Pop( array );
    
    iChoiceList = CAknChoiceList::NewL( control, array, CAknChoiceList::EAknChoiceListWithCurrentSelection, btn );
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLNewLC
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLNewLC( CStifItemParser& /*aItem*/ )
    {
    if(iChoiceList)
        {
        delete iChoiceList;
        iChoiceList = NULL;
        }
    
    const TInt num = 5;
    CDesCArrayFlat* array = new (ELeave) CDesCArrayFlat( num );
    CleanupStack::PushL( array );
    STIF_ASSERT_NOT_NULL( array );
    
    _LIT( KItem, "item" );
    TBuf<KLength> item( KItem );
    array->AppendL( item );
    
    _LIT( KButton, "button" );
    TBuf<KLength> button( KButton );
    CAknButton* btn = CAknButton::NewLC( NULL, NULL, NULL, NULL, button, KNullDesC, KAknButtonNoFrame, 0 );
    STIF_ASSERT_NOT_NULL( btn );
    
    CTestSDKChoiceListControl* control = CTestSDKChoiceListControl::NewLC();
    STIF_ASSERT_NOT_NULL( control );
    
    CleanupStack::Pop( control );
    CleanupStack::Pop( btn );
    CleanupStack::Pop( array );
    
    CAknChoiceList* choiceList = CAknChoiceList::NewLC( control, array, CAknChoiceList::EAknChoiceListWithCurrentSelection, btn );
    STIF_ASSERT_NOT_NULL( choiceList );
    
    CleanupStack::PopAndDestroy( choiceList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLShowChoiceListL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLShowChoiceListL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    TInt flag = iChoiceList->ShowChoiceListL();
    STIF_ASSERT_EQUALS( KErrNone, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLSetSelectedIndexL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLSetSelectedIndexL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetSelectedIndex( 0 );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLSelectedIndexL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLSelectedIndexL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetSelectedIndex( 0 );
    TInt index = iChoiceList->SelectedIndex();
    STIF_ASSERT_EQUALS( 0, index );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLSetItemsL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLSetItemsL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    const TInt num = 5;
    CDesCArrayFlat* array = new (ELeave) CDesCArrayFlat( num );
    CleanupStack::PushL( array );
    STIF_ASSERT_NOT_NULL( array );
    
    _LIT( KItem1, "item1" );
    TBuf<KLength> item1( KItem1 );
    array->AppendL( item1 );
    
    _LIT( KItem2, "item2" );
    TBuf<KLength> item2( KItem2 );
    array->AppendL( item2 );
    
    CleanupStack::Pop( array );
    iChoiceList->SetItems( array );
    iChoiceList->SetSelectedIndex( 1 );
    TInt index = iChoiceList->SelectedIndex();
    STIF_ASSERT_EQUALS( 1, index );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLSetItemsLeaveL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLSetItemsLeaveL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    const TInt item = 2;
    iChoiceList->SetSelectedIndex( item );
    TInt index = iChoiceList->SelectedIndex();
    STIF_ASSERT_EQUALS( item, index );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLAddItemL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLAddItemL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    
    _LIT( KItem, "item4" );
    TBuf<KLength> itembuf( KItem );
    HBufC* item = itembuf.AllocLC();
    
    iChoiceList->AddItemL( item );
    CleanupStack::PopAndDestroy( item );
    
    const TInt num = 3;
    iChoiceList->SetSelectedIndex( num );
    TInt index = iChoiceList->SelectedIndex();
    STIF_ASSERT_EQUALS( num, index );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLRemoveItemL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLRemoveItemL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    
    const TInt item = 2;
    iChoiceList->RemoveItem( item );
    iChoiceList->SetSelectedIndex( 1 );
    TInt index = iChoiceList->SelectedIndex();
    STIF_ASSERT_EQUALS( 1, index );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLSetFlagsL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLSetFlagsL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    
    iChoiceList->SetFlags( CAknChoiceList::EAknChoiceListPositionBottom );
    TInt flagGet = iChoiceList->Flags();
    TInt flag = CAknChoiceList::EAknChoiceListPositionBottom | CAknChoiceList::EAknChoiceListWithCurrentSelection;
    STIF_ASSERT_TRUE( flagGet == flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLFlagsL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLFlagsL( CStifItemParser& aItem )
    {
    return TestCLSetFlagsL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLSetButtonL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLSetButtonL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    
    _LIT( KButton, "buttonSet" );
    TBuf<KLength> button( KButton );
    CAknButton* btn = CAknButton::NewLC( NULL, NULL, NULL, NULL, button, KNullDesC, KAknButtonNoFrame, 0 );
    STIF_ASSERT_NOT_NULL( btn );
    CleanupStack::Pop( btn );
    
    iChoiceList->SetButtonL( btn );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLHideChoiceListL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLHideChoiceListL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    
    iChoiceList->HideChoiceList();
    TInt index = iChoiceList->SelectedIndex();
    const TInt nochoice = -1; 
    STIF_ASSERT_EQUALS( nochoice, index );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLSetTooltipTextL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLSetTooltipTextL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    
    _LIT( KText, "text" );
    TBuf<KLength> text( KText );
    iChoiceList->SetTooltipTextL( text );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLSetTooltipTimeoutsL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLSetTooltipTimeoutsL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    
    const TInt beforeTimeout = 150;
    const TInt inViewTimeout = 3000;
    iChoiceList->SetTooltipTimeouts( beforeTimeout, inViewTimeout );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLSetTooltipPositionL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLSetTooltipPositionL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    
    iChoiceList->SetTooltipPosition( CAknChoiceList::EPositionTop );
    iChoiceList->SetTooltipPosition( CAknChoiceList::EPositionBottom );
    iChoiceList->SetTooltipPosition( CAknChoiceList::EPositionLeft );
    iChoiceList->SetTooltipPosition( CAknChoiceList::EPositionRight );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLComponentControlL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLComponentControlL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    
    CAknButton* button = static_cast<CAknButton*>( iChoiceList->ComponentControl( 0 ) );
    STIF_ASSERT_NOT_NULL( button );
    
    CEikLabel* label = static_cast<CEikLabel*>( iChoiceList->ComponentControl( 1 ) );
    STIF_ASSERT_NOT_NULL( label );
    
    const TInt num = 2;
    CCoeControl* control = iChoiceList->ComponentControl( num );
    STIF_ASSERT_NULL( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLCountComponentControlsL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    
    TInt count = iChoiceList->CountComponentControls();
    const TInt num = 2;
    STIF_ASSERT_EQUALS( num, count );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLMinimumSizeL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    iChoiceList->SetFlags( CAknChoiceList::EAknChoiceListWithoutCurrentSelection );
    
    TSize size = iChoiceList->MinimumSize();
    
    CAknButton* button = static_cast<CAknButton*>( iChoiceList->ComponentControl( 0 ) );
    STIF_ASSERT_NOT_NULL( button );
    
    TSize sizeButton = button->MinimumSize();
    STIF_ASSERT_TRUE( size == sizeButton );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLHandleResourceChangeL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    
    iChoiceList->HandleResourceChange( KAknsMessageSkinChange );
    iChoiceList->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLOfferKeyEventL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    
    TKeyEvent keyEvent;
    keyEvent.iScanCode = EStdKeyEnter;
    TInt consume = iChoiceList->OfferKeyEventL( keyEvent, EEventKey );
    STIF_ASSERT_TRUE( consume == EKeyWasConsumed );
    
    keyEvent.iScanCode = EStdKeyDevice3;
    consume = iChoiceList->OfferKeyEventL( keyEvent, EEventKey );
    STIF_ASSERT_TRUE( consume == EKeyWasConsumed );
    
    consume = iChoiceList->OfferKeyEventL( keyEvent, EEventKeyUp );
    STIF_ASSERT_TRUE( consume == EKeyWasNotConsumed );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLDrawL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLDrawL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    
    iChoiceList->Draw( TRect() );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLPositionChangedL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLPositionChangedL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    
    iChoiceList->PositionChanged();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLHandleControlEventL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLHandleControlEventL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    
    CAknButton* button = static_cast<CAknButton*>( iChoiceList->ComponentControl( 0 ) );
    STIF_ASSERT_NOT_NULL( button );
    iChoiceList->HandleControlEventL( button, MCoeControlObserver::EEventStateChanged );
    
    CEikLabel* label = static_cast<CEikLabel*>( iChoiceList->ComponentControl( 1 ) );
    STIF_ASSERT_NOT_NULL( label );
    iChoiceList->HandleControlEventL( label, MCoeControlObserver::EEventRequestCancel );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceList::TestCLInsertItemL
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceList::TestCLInsertItemL( CStifItemParser& /*aItem*/ )
    {
    TestCLInitializeL();
    STIF_ASSERT_NOT_NULL( iChoiceList );
    
    iChoiceList->SetItemsL( R_TESTSDK_LISTITEMS );
    
    _LIT( KItem, "iteminsert" );
    TBuf<KLength> item( KItem );
    TInt index = iChoiceList->InsertItemL( 1, item );
    
    STIF_ASSERT_EQUALS( index, 1 );
    
    return KErrNone;
    
    }
//  [End of File]
