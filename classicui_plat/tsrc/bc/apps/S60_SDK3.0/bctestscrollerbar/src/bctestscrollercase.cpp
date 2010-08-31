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
#include <eikscrlb.h>
#include <eiksbfrm.h>
#include <eikcba.h>
#include <eikscbut.h>
#include <eikbtgpc.h>
#include <eikedwin.h>

#include "bctestmedi.h"
#include "bctestScrollercase.h"
#include "bctestScrollercontainer.h"
#include "bctestScroller.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestScrollerCase* CBCTestScrollerCase::NewL(
    CBCTestScrollerContainer* aContainer , CBCTestScrollerView* aView  )
    {
    CBCTestScrollerCase* self = new( ELeave ) CBCTestScrollerCase(
        aContainer ,aView);
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestScrollerCase::CBCTestScrollerCase(
    CBCTestScrollerContainer* aContainer ,CBCTestScrollerView* aView )
    : iContainer( aContainer ),iView( aView )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestScrollerCase::~CBCTestScrollerCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestScrollerCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestScrollerCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestScrollerCase::BuildScriptL()
    {
    // Add script as your need.
    AddTestL( LeftCBA, KeyOK,LeftCBA,Down,KeyOK,LeftCBA,Down,Down,KeyOK,TEND );
    }

// ---------------------------------------------------------------------------
// CBCTestScrollerCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestScrollerCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline3 )
        {
        return;
        }
    // Call release before prepare to let container has time to draw the
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
             TestScroBarL();
            break;
        case EBCTestCmdOutline2:
            TestScroBarFrameL();
            break;
        case EBCTestCmdOutline3:
            TestScrollButtonL();;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestScrollerCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestScrollerCase::PrepareCaseL( TInt aCmd )
    {
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
        case EBCTestCmdOutline2:
        case EBCTestCmdOutline3:
            // Here is a simple demo. You should create your control
            // instead of this.
            iControl = new( ELeave ) CCoeControl();
            iControl->SetContainerWindowL( *iContainer );
            iControl->MakeVisible( ETrue );
            break;
        default:
            break;
        }
    // Pass the owner of iControl to iContainer.
    iContainer->SetControl( iControl );
    }

// ---------------------------------------------------------------------------
// CBCTestScrollerCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//
void CBCTestScrollerCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestScrollerCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//
void CBCTestScrollerCase::TestScroBarL()
    {

    // Test some API here
           CEikScrollBar *sBar = new ( ELeave ) CEikScrollBar();
           CleanupStack::PushL(sBar);

           sBar->DefaultScrollBarBreadth();
           _LIT( defScroBread," Test DefaultScrollBarBreadth() " );;
           AssertTrueL( ETrue,defScroBread );

            TPointerEvent ptEvnt;
            ptEvnt.iType = TPointerEvent::EButton1Down;
            sBar->HandlePointerEventL(ptEvnt);
            _LIT( handPtEvnt,"Test HandlePointEventL()" );
            AssertTrueL( ETrue,handPtEvnt);

            sBar->MinVisibleLength( TInt( 1 ) );
            _LIT( minVisible," Test MinVisibleLength() " );
            AssertTrueL( ETrue,minVisible);

            sBar->SetAllButtonsDimmed( ETrue );
            _LIT( stButnDim," Test SetAllButtonsDimmed() " );
            AssertTrueL( ETrue,stButnDim );

            sBar->SetDecreaseButtonsDimmed( ETrue );
            _LIT(stDeButtonDim," Test SetDecreaseButtonsDimmed() " );
            AssertTrueL( ETrue,stDeButtonDim );

            sBar->SetIncreaseButtonsDimmed( ETrue );
            _LIT( stInBtnDim," Test SetIncreaseButtonDimmed() ");
            AssertTrueL( ETrue,stInBtnDim );

            TEikScrollBarModel* model = new ( ELeave ) TEikScrollBarModel();
            CleanupStack::PushL( model );
            sBar->SetLengthAndModelL( TInt(3),model );
            CleanupStack::Pop();
            _LIT( stLenAndModel," Test SetLengthAndModelL() " );
            AssertTrueL( ETrue,stLenAndModel);

            sBar->SetLengthL(TInt( 5 ) );
            _LIT( stLength," Test SetLengthL() " );
            AssertTrueL( ETrue,stLength );

            sBar->SetModelThumbPosition( TInt( 2 ) );
            _LIT( stModelThumPsition," Test SetModelThumbPosition() " );
            AssertTrueL( ETrue,stModelThumPsition);

            sBar->ThumbPosition();
            _LIT( thumPosition," Test thumPosition() ");
            AssertTrueL( ETrue,thumPosition );

            sBar->SetFocusPosToThumbPos( TInt( 9 ));
            _LIT( stFocPosToPos," Test SetFocusPosToThumbPos() " );
            AssertTrueL( ETrue,stFocPosToPos );

            sBar->SetModelL( model );
            _LIT( stMod," Test SetModelL() " );
            AssertTrueL( ETrue,stMod );

            delete model;
            CleanupStack::PopAndDestroy();
    }

// ---------------------------------------------------------------------------
// CBCTestScrollerCase::TestScroBarFrameL
// ---------------------------------------------------------------------------

void CBCTestScrollerCase::TestScroBarFrameL()
   {
            CCoeControl* container = new (ELeave) CCoeControl;
            CEikScrollBarFrame * sBarFrame = new ( ELeave )
                                CEikScrollBarFrame(container, NULL);
            CleanupStack::PushL( sBarFrame );

            sBarFrame->VerticalScrollBar();
            _LIT(vtScrollBar," Test VerticalScrollBar() " );
            AssertTrueL( ETrue, vtScrollBar);

            sBarFrame->CreateDoubleSpanScrollBarsL( EFalse,EFalse );
            _LIT(  crtDoubleSpanScrBar," Test CreateDoubleSpanScrollBarsL()" );
            AssertTrueL( ETrue,crtDoubleSpanScrBar );

            sBarFrame->DrawScrollBarsNow();
            _LIT( drwScrBar," Test DrawScrollBarsNow() " );
            AssertTrueL( ETrue,drwScrBar );

            sBarFrame->IsArrowHeadScrollBar( TInt( 1 ) );
            _LIT( isArwHedScrBar," Test IsArrowHeadScrollBar()" ) ;
            AssertTrueL( ETrue,isArwHedScrBar );

            sBarFrame->MoveThumbsBy( TInt( 1 ),TInt( 1 ) );
            _LIT( mvThumBy," Test MoveThumbsBy() " );
            AssertTrueL( ETrue,mvThumBy );

            sBarFrame->SetTypeOfHScrollBar( sBarFrame->TypeOfHScrollBar() );
            _LIT( stTypeHScrBar," Test SetTypeOfHscrollBar() " );
            AssertTrueL( ETrue,stTypeHScrBar );

            sBarFrame->SetTypeOfVScrollBar( sBarFrame->TypeOfVScrollBar() );
            _LIT( stTypeVScrBar," Test SetTypeOfVscrollBar() " );
            AssertTrueL( ETrue,stTypeVScrBar );

            TEikScrollBarModel *scrBarModel = new ( ELeave )
                                                    TEikScrollBarModel();
            sBarFrame->Tile( scrBarModel );
            _LIT( tile," Test Tile(onePara) " );
            AssertTrueL( ETrue,tile);

            TEikScrollBarModel *hModel = new ( ELeave ) TEikScrollBarModel();
            TEikScrollBarModel *vModel = new ( ELeave ) TEikScrollBarModel();
            TRect           rect;
            TRect           rect1;
            TEikScrollBarFrameLayout aLayout;
            sBarFrame->TileL(hModel, vModel,rect,rect1,aLayout);

            sBarFrame->Tile(hModel,vModel);

            delete  hModel;
            delete  vModel;
            delete scrBarModel;
            AssertTrueL( ETrue,tile );

            sBarFrame->SetAdjustsHorizontalModel( EFalse );
            _LIT( stAdjHModel," Test SetAdjustsHorizontalModel() ");
            AssertTrueL( ETrue,stAdjHModel );

            sBarFrame->SetAdjustsVerticalModel( EFalse );
            _LIT( stAdjVModel," Test SetAdjustVerticalModel() " );
            AssertTrueL( ETrue,stAdjVModel );

            CleanupStack::PopAndDestroy();
            delete container;
   }

// ---------------------------------------------------------------------------
// CBCTestScrollerCase::TestScrollButtonL
// ---------------------------------------------------------------------------

void CBCTestScrollerCase::TestScrollButtonL()
   {
            CEikScrollButton *scrButton = new CEikScrollButton(
                                                CEikScrollButton::ENudgeLeft );

            TPointerEvent ptEvnt;
            ptEvnt.iType = TPointerEvent::EButton1Down;
            scrButton->HandlePointerEventL(ptEvnt);
            _LIT( handPtEvnt,"Test HandlePointEventL()" );
            AssertTrueL( ETrue,handPtEvnt);

            scrButton->Type();
            _LIT( tp," Test Type() " );
            AssertTrueL( ETrue,tp );
            delete scrButton;

            CEikArrowHeadScrollButton *hButton = CEikArrowHeadScrollButton::NewL(
                        iContainer , CEikScrollButton::ENudgeLeft);
            delete hButton;

            CEikArrowHeadScrollBar *hBar = new ( ELeave )
                                        CEikArrowHeadScrollBar( iContainer );

           //---------- head button construct -----------------------------//
           CEikCba* mopCba = 0;

            hBar->ConstructL(mopCba,iContainer,CEikScrollBar::EVertical,TInt( 9 ));
            _LIT( cstrct," Test ConstructL() " );
            AssertTrueL( ETrue,cstrct );

            hBar->HandlePointerEventL( ptEvnt );
            AssertTrueL( ETrue,handPtEvnt);

            delete hBar;
          //**** end of head button

            TEikScrollBarModel * sBarMod = new ( ELeave ) TEikScrollBarModel();

            sBarMod->CheckBounds();
            _LIT( chkBound," Test CheckBounds() " );
            AssertTrueL( ETrue,chkBound );

            sBarMod->MaxThumbPos();
            _LIT( mxThumPos," Test MaxThumbPos() " );
            AssertTrueL( ETrue,mxThumPos );
            delete sBarMod;

            CAknDoubleSpanScrollBar *dSpanScrBar = new
                            ( ELeave ) CAknDoubleSpanScrollBar( iContainer );
            _LIT( newSpanBar," Test CAknDoubleSpanScrollBar ");
            AssertNotNullL( dSpanScrBar,newSpanBar );

            dSpanScrBar->ConstructL(EFalse,NULL,iContainer,
                                        CEikScrollBar::EVertical,TInt( 9 ) );
            _LIT(constr," Test ConstructL() " );
            AssertTrueL( ETrue,constr );

            TPointerEvent pEvnt;
            pEvnt.iType = TPointerEvent::EButton1Up;
            dSpanScrBar->HandlePointerEventL(pEvnt);
            _LIT( hPtEvnt,"Test HandlePointEventL()" );
            AssertTrueL( ETrue,hPtEvnt);
            delete dSpanScrBar;

            TAknDoubleSpanScrollBarModel *dSpaScrBarMod = new ( ELeave )
                                        TAknDoubleSpanScrollBarModel();

            dSpaScrBarMod->SetFieldPosition( TInt( 9 ) );
            _LIT( stFldPos," Test SetFieldPosition() " );
            AssertTrueL( ETrue,stFldPos);

            dSpaScrBarMod->SetFieldSize( TInt( 8 ) );
            _LIT( stFldSiz," Test SetFieldSize() " );
            AssertTrueL( ETrue,stFldSiz );
            delete dSpaScrBarMod;

            CAknScrollButton *aknScrBut =CAknScrollButton::NewL(
                    CAknScrollButton::ENudgeLeft, CAknScrollButton::ENormal );

            aknScrBut->IsNormalScrollBarUsingButton();
            _LIT(isNorBar," Test IsNormalScrollBarUsingButton()" );
            AssertTrueL( ETrue,isNorBar);

            aknScrBut->SetPosition( TInt( 3 ), TInt( 14 ) );
            _LIT(stPos," Test SetPosition()" );
            AssertTrueL( ETrue,stPos );

            aknScrBut->CreateWindowOnlyForArrowsL( iContainer );
            _LIT(crtWinForArrow," Test CreateWindowOnlyForArrowsL() " );
            AssertTrueL( ETrue,crtWinForArrow );
            delete aknScrBut;

            CAknScrollButton *aknScrBut1 =CAknScrollButton::NewL(
                                        CAknScrollButton::ENudgeLeft);

            aknScrBut1->SetTypeOfScrollBarUsingButton(CAknScrollButton::ENormal);
            _LIT( stTypeBarUseBut," Test SetTypeOfScrollBarUsingButton() " );
            AssertTrueL( ETrue,stTypeBarUseBut );

            CBCTestMedi * medi = new ( ELeave ) CBCTestMedi();
            medi->SetButtonPositionL( aknScrBut1 );
            _LIT(stButPos," Test SetButtonPositionL() " );
            AssertTrueL( ETrue,stButPos );

            medi->ComponentControl( TInt( 1 ) );
            _LIT( cmpntControl," Test ComponentControl() " );
            AssertTrueL( ETrue,cmpntControl );

            delete medi;
            delete aknScrBut1;

            CEikScrollBarFrame * sBarFrame = new ( ELeave )
                                CEikScrollBarFrame(iContainer, NULL);

            sBarFrame->ScrollBarExists( CEikScrollBar::EVertical );
            _LIT( sBarExist," Test ScrollBarExists() " );
            AssertTrueL( ETrue,sBarExist );

            delete sBarFrame;
   }
