/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <barsread.h>

#include <aknchoicelist.h>
#include <aknlongtapdetector.h>
#include <aknstyluspopupmenu.h>
#include <aknbutton.h>

#include "BCTestChoicelistcase.h"
#include "BCTestChoicelistcontainer.h"
#include "BCTestChoicelist.hrh"
#include <bctestchoicelist.rsg>

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCPopupChoicelistCase* CBCPopupChoicelistCase::NewL(
    CBCPopupChoicelistContainer* aContainer )
    {
    CBCPopupChoicelistCase* self = new( ELeave ) CBCPopupChoicelistCase(
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCPopupChoicelistCase::CBCPopupChoicelistCase(
    CBCPopupChoicelistContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCPopupChoicelistCase::~CBCPopupChoicelistCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCPopupChoicelistCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCPopupChoicelistCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCPopupChoicelistCase::BuildScriptL()
    {

    const TInt scripts[] =
        {
        DELAY( 1 ),  // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        LeftCBA,

        //outline2
        LeftCBA,
        Down,
        LeftCBA,

        //outline3
        LeftCBA,
        REP( Down, 2 ),
        LeftCBA,
        };

      AddTestScriptL( scripts, sizeof( scripts )/sizeof( TInt ) );
    }

// ---------------------------------------------------------------------------
// CBCPopupChoicelistCase::RunL
// ---------------------------------------------------------------------------
//
void CBCPopupChoicelistCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline3 )
        {
        return;
        }

    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
             TestFunctionL();
             break;
        case EBCTestCmdOutline2:
             TestDetectorFunctionL();
             break;
        case EBCTestCmdOutline3:
             TestPopMenuFunctionL();
             break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCPopupChoicelistCase::TestFunctionL
// ---------------------------------------------------------------------------
//
void CBCPopupChoicelistCase::TestFunctionL()
    {
    // Test some API here

    CAknButton* btn = CAknButton::NewLC( NULL, NULL, NULL,
                          NULL, _L("LeftButton"), KNullDesC,
                          KAknButtonNoFrame, 0 );
    
    CleanupStack::PopAndDestroy();
    btn = NULL;    
    
    btn = CAknButton::NewL( NULL, NULL, NULL,
                          NULL, _L("LeftButton"), KNullDesC,
                          KAknButtonNoFrame, 0 );

    CDesCArrayFlat* itemArray = new ( ELeave ) CDesCArrayFlat( 8 );
    CleanupStack::PushL( itemArray );
    itemArray->AppendL( _L("orking") );
    itemArray->AppendL( _L("ll") );
    itemArray->AppendL( _L("sti") );
    itemArray->AppendL( _L("w") );


    CAknChoiceList *choList = 
    	CAknChoiceList::NewL( iContainer, itemArray,
      CAknChoiceList::EAknChoiceListWithCurrentSelection, btn );

    CleanupStack::PushL( choList );
    _LIT( aknChoiceList, " ChoiceList create successfully " );
    AssertNotNullL(  choList, aknChoiceList );

    CleanupStack::Pop( choList );
    CleanupStack::Pop( itemArray );
    delete btn;

    choList->ShowChoiceListL();
    _LIT( showList, " ShowChoiceList! " );
    AssertTrueL( ETrue, showList);

    choList->SetSelectedIndex( TInt( 1 ) );
    _LIT( setIndex, " SetSelectedIndex()!" );
    AssertTrueL( ETrue, setIndex );

    choList->SelectedIndex();
    _LIT( selectedIndex, " SelectedIndex() " );
    AssertTrueL( ETrue, selectedIndex );

    choList->SetItemsL( R_MYCHOICELIST_ITEMS );
    _LIT( setItemsL, " SetItemsL( TInt aResourceId ) " );
    AssertTrueL( ETrue, setItemsL );
    
    _LIT( setItems, " SetItems( CDesCArray* aArray ) " );
    CDesCArray* array = new ( ELeave ) CDesCArrayFlat( 1 );
    array->AppendL( setItems );	
    choList->SetItems( array ); 
    AssertTrueL( ETrue, setItems );

    TBuf<20> *bf = new ( ELeave ) TBuf<20>;
    choList->AddItemL( bf );
    _LIT( addItemL, " AddItemL() " );
    AssertTrueL( ETrue, addItemL );

    choList->RemoveItem( TInt( 1 ) );
    _LIT( removeItem, " RemoveItem() " );
    AssertTrueL( ETrue, removeItem );

    choList->SetFlags( TInt( 1 ) );
    _LIT( setFlags, " SetFlags() " );
    AssertTrueL( ETrue, setFlags );

    choList->Flags();
    _LIT( flg, " Flags() " );
    AssertTrueL( ETrue, flg );

    choList->SetButtonL( CAknButton::NewL() );
    _LIT( setButtonL, " SetButtonL() " );
    AssertTrueL( ETrue, setButtonL );

    choList->HideChoiceList();
    _LIT( hideChoiceList, " HideChoiceList() " );
    AssertTrueL( ETrue, hideChoiceList );

    _LIT( setTooltipTextL, " SetTooltipTextL() " );
    choList->SetTooltipTextL( setTooltipTextL );
    AssertTrueL( ETrue, setTooltipTextL );
    
    choList->SetTooltipTimeouts( 150, 3000 ); // 150 and 3000 are the defaults
    _LIT( setTooltipTimeouts, " SetTooltipTimeouts() " );
    AssertTrueL( ETrue, setTooltipTimeouts );
    
    choList->SetTooltipPosition( CAknChoiceList::EPositionTop );
    _LIT( setTooltipPosition, " SetTooltipPosition() " );
    AssertTrueL( ETrue, setTooltipPosition );    
    
    choList->ComponentControl( TInt( 1 ) );
    _LIT( componentControl, " componentControl() " );
    AssertTrueL( ETrue, componentControl );

    choList->CountComponentControls();
    _LIT( countComponentControls, " CountComponentControls() " );
    AssertTrueL( ETrue, countComponentControls );

    choList->MinimumSize();
    _LIT( minimumSize, " MinimumSize() " );
    AssertTrueL( ETrue, minimumSize );

    choList->HandleResourceChange( TInt( 1 ) );
    _LIT( handleResourceChange, " HandleResourceChange() " );
    AssertTrueL( ETrue, handleResourceChange );

    TKeyEvent keyEvent;
    choList->OfferKeyEventL( keyEvent, EEventNull );
     _LIT( offerKeyEventL, " OfferKeyEventL() " );
    AssertTrueL( ETrue, offerKeyEventL );

    choList->Draw( TRect() );
    _LIT( draw, " Draw() " );
    AssertTrueL( ETrue, draw );
    
    choList->PositionChanged();
    _LIT( KPositionChanged, "PositionChanged()!");
    AssertTrueL( ETrue, KPositionChanged );

    choList->HandleControlEventL( iContainer, 
    	MCoeControlObserver::EEventRequestFocus );
    _LIT( handleControlEventL, " HandleControlEventL() " );
    AssertTrueL( ETrue, handleControlEventL );

    choList->InsertItemL( TInt( 2 ), *bf );
    _LIT( insertItemL, " InsertItemL() " );
    AssertTrueL( ETrue, insertItemL );

    delete bf;
    delete choList;
}

void CBCPopupChoicelistCase::TestDetectorFunctionL()
    {
#ifdef RD_SCALABLE_UI_V2
    CAknLongTapDetector* tapDetector =
                CAknLongTapDetector::NewL( NULL );
    _LIT( tpDectector," its NULL" );
    AssertNotNullL(tapDetector, tpDectector );
    CleanupStack::PushL( tapDetector );

    TPointerEvent pEvent;
    tapDetector->PointerEventL( pEvent );
    _LIT( ptEvent,"PointerEventL()!" );
    AssertTrueL( ETrue, ptEvent );

    tapDetector->SetTimeDelayBeforeAnimation( 100 );
    _LIT( stTimeDelay," SetTimeDelayBeforeAnimation()!" );
    AssertTrueL( ETrue, stTimeDelay );

    tapDetector->SetLongTapDelay(50);
    _LIT( stLongDelay,"SetLongTapDelay(50);!" );
    AssertTrueL( ETrue, stLongDelay );
    
    tapDetector->EnableLongTapAnimation( ETrue );
    _LIT( ELongTAnim, "EnableLongTapAnimation(ETrue);!");
    AssertTrueL( ETrue, ELongTAnim );
    
    TWsEvent wEvent;
    tapDetector->MonitorWsMessage( wEvent );
    _LIT( MoniWsMsg, "MonitorWsMessage(wEvent);!");
    AssertTrueL( ETrue, MoniWsMsg );
    
    TBool check;
    check = tapDetector->IsAnimationRunning();
    _LIT(IsAniRunning, "IsAnimationRunnin();!");
    AssertTrueL(ETrue, IsAniRunning );
   
    CleanupStack::PopAndDestroy( tapDetector );

    CBCTapDetectorCallBack listcase;
    MAknLongTapDetectorCallBack* callback = &listcase;
    TPoint tp1, tp2;
    
    callback->HandleLongTapEventL( tp1, tp2 );
    _LIT(KHandleLongTapEventL, "HandleLongTapEventL();!");
    AssertTrueL(ETrue, KHandleLongTapEventL );
    
    
#endif
   }


void CBCPopupChoicelistCase::TestPopMenuFunctionL()
   {
#ifdef RD_SCALABLE_UI_V2
    TPoint aPoint;

		    CAknStylusPopUpMenu* popMenu =
        CAknStylusPopUpMenu::NewL( NULL, aPoint, NULL);
        _LIT( pMenu,"CAknStylusPopUpMenu::NewL()!" );
    AssertNotNullL( popMenu, pMenu);
    CleanupStack::PushL( popMenu );

    TBuf<20> *bf = new (ELeave) TBuf<20>;
    _LIT(adMenuItem," addMenuItemL()" );
    popMenu->AddMenuItemL( *bf, EBCTestCmdOutline1);
    AssertTrueL( ETrue, adMenuItem );
    delete bf;

	  popMenu->RemoveMenuItem( EBCTestCmdOutline1 );
    _LIT( remMenuFuc," popMenu()!" );
    AssertTrueL( ETrue, remMenuFuc);

    popMenu->SetItemDimmed( EBCTestCmdOutline1, ETrue);
    _LIT( setItemFuc," SetItemDimmed()! " );
    AssertTrueL( ETrue, setItemFuc);
    
    popMenu->ShowMenu();
    _LIT(ShMenu, "ShowMenu()!");
    AssertTrueL(ETrue, ShMenu);
    
    TPoint point;
    popMenu->SetPosition(point);
    _LIT(SetPos, "SetPosition()!");
    AssertTrueL(ETrue, SetPos);
    
    
    CCoeControl* cntrlptr = new (ELeave) CCoeControl;
    MCoeControlObserver::TCoeEvent cEvent;
    
    popMenu->HandleControlEventL(cntrlptr, cEvent);
    _LIT(HandleCtrlEvent, "HandleControlEventL()!");
    AssertTrueL(ETrue, HandleCtrlEvent);
    
    delete cntrlptr;
    
    CleanupStack::PopAndDestroy( popMenu );
#endif

    }

void CBCTapDetectorCallBack::HandleLongTapEventL(const TPoint& aPenEventLocation,
																								 const TPoint& aPenEventScreenLocation )
{
	//Nothing here.
}																								 