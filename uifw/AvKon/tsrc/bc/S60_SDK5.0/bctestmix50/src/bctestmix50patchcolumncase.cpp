/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test case for column list classes
*
*/


#include <aknlists.h>
#include <eikenv.h>
#include <barsread.h>
#include <eikclbd.h>
#include <eikclb.h>
#include <eiklbed.h>
#include <e32std.h> 
#include <s32file.h>
#include <eikdef.h>
#include <w32std.h>
#include <aknutils.h>
#include <AknSelectionList.h>
#include <bctestmix50.mbg>
#include <eikconso.h>       // CEikConsoleControl
#include <eikcapc.h> 
#include <eikcapca.h>                // CEikCaptionedControl
#include <eiktxlbx.h>

#include <bctestmix50.rsg>
#include "bctestmix50patchcolumncase.h"
#include "bctestmix50container.h"
#include "bctestmix50.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestMix50ListColumnCase* CBCTestMix50ListColumnCase::NewL( 
		CBCTestMix50Container* aContainer, CEikonEnv* aEikEnv )
    {
    CBCTestMix50ListColumnCase* self = new( ELeave ) CBCTestMix50ListColumnCase( 
        aContainer, aEikEnv );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestMix50ListColumnCase::CBCTestMix50ListColumnCase( 
		CBCTestMix50Container* aContainer, CEikonEnv* aEikEnv )
    : CBCTestMix50ListBaseCase( aContainer, aEikEnv )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestMix50ListColumnCase::~CBCTestMix50ListColumnCase()
    {   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::ConstructL()
    {    
    BuildScriptL();
    }
    
// ---------------------------------------------------------------------------
// CBCTestMix50ListColumnCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::BuildScriptL()
    {
    AddTestL( DELAY( 1 ), LeftCBA, Down, LeftCBA, TEND );
    }
    
// ---------------------------------------------------------------------------
// CBCTestMix50ListColumnCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::RunL( TInt aCmd )
    {    
    switch( aCmd )
        {
        case EBCTestCmdOutline2:
            TestSnakingTextListBoxL();
			TestEikTextListBoxL();
			TestTextListBoxModelL();
			TestEikSnakingListBoxL();
			TestEikListBoxL();
			TestSnakingListBoxViewL();
			TestListBoxViewL();
			TestTextListItemDrawerL();
			TestListBoxTextEditorL();
			TestListBoxDataL();
			TestFormattedCellListBoxDataL();
			TestFormattedCellListBoxL();
			TestColumnListBoxDataL();
			TestColumnListBoxL();
			TestSelectionListDialogL();
			TestListBoxLayoutsL();
			TestConsoleScreenL();
			TestCapCArrayL();
			break;
        default:
            break;           
        }   
    }
	
//----------------------------------------------------------------------------
//Test CEikSnakingTextListBox
//----------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestSnakingTextListBoxL()
{
	_LIT( KSnakingList1, 
		"CEikSnakingTextListBox::CEikSnakingTextListBox() invoked" );
	_LIT( KSnakingList2 , "CEikSnakingTextListBox::ConstructL() invoked" );
	_LIT( KSnakingList3 , "CEikSnakingTextListBox::Model() invoked" );
	_LIT( KSnakingList4 , 
		"CEikSnakingTextListBox::GetColorUseListL() invoked" );
	_LIT( KSnakingList5 , 
		"CEikSnakingTextListBox::HandleResourceChange() invoked" );
	_LIT( KSnakingList6 , 
		"CEikSnakingTextListBox::HandlePointerEventL() invoked" );
	_LIT( KSnakingList7 , 
		"CEikSnakingTextListBox::~CEikSnakingTextListBox() invoked" );
	
	TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0 , 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
	
	CEikSnakingTextListBox * listBox =  new( ELeave ) CEikSnakingTextListBox();
	CleanupStack::PushL( listBox );
	AssertTrueL( ETrue , KSnakingList1 );
	
	listBox->ConstructL( iContainer );
	AssertTrueL( ETrue, KSnakingList2 );
	
	CTextListBoxModel * listBoxModel = listBox->Model();
	AssertNotNullL( listBoxModel , KSnakingList3 );

	CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( 4 );
    CleanupStack::PushL( colorUseList );
    listBox->GetColorUseListL( *colorUseList );
    AssertTrueL( ETrue, KSnakingList4 );
    colorUseList->Reset();    
    listBox->GetColorUseListL( *colorUseList );
    CleanupStack::PopAndDestroy( colorUseList ); 
	
	TInt type( 1 );
	listBox->HandleResourceChange( type );
	AssertTrueL(ETrue , KSnakingList5);
	listBox->HandlePointerEventL( event );
	AssertTrueL( ETrue , KSnakingList6 );
	CleanupStack::Pop( listBox );
	delete listBox;
	AssertTrueL( ETrue , KSnakingList7 );
    }

//---------------------------------------------------------------------------
//Test CEikTextListBox
//---------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestEikTextListBoxL()
	{
	_LIT( KStreamName, "C:\\bctestlog\\bctestlog1.txt" );
	_LIT( KTextList1 , "CEikTextListBox::CEikTextListBox() invoked" );
	_LIT( KTextList2 , "CEikTextListBox::ConstructL() invoked" );
	_LIT( KTextList3 , "CEikTextListBox::Model() invoked" );
	_LIT( KTextList4 , "CEikTextListBox::GetColorUseListL() invoked" );
	_LIT( KTextList5 , "CEikTextListBox::CreateItemDrawerL() invoked" );
	_LIT( KTextList6 , "CEikTextListBox::WriteInternalStateL() invoked" );
	_LIT( KTextList7 , "CEikTextListBox::~CEikTextListBox() invoked" );
	_LIT( KTextList8 , "CEikTextListBox::CEikTextListBox() invoked" );
	_LIT( KTextList9 , "CreateResourceReaderLC() invoked" );
	_LIT( KTextList10 , "CEikTextListBox::ConstructFromResourceL() invoked" );
	_LIT( KTextList11 , "CEikTextListBox::~CEikTextListBox() invoked" );

	
	CSubEikTextListBox * listbox = new ( ELeave )CSubEikTextListBox();
	CleanupStack::PushL( listbox );
	AssertNotNullL( listbox , KTextList1 );
	
	listbox->ConstructL( iContainer );
	AssertTrueL( ETrue , KTextList2 );
	
	CTextListBoxModel * listboxModel = listbox->Model();
	AssertNotNullL( listboxModel , KTextList3 );
	
	CArrayFix<TCoeColorUse>* indexArray = new ( ELeave ) 
                                   CArrayFixFlat<TCoeColorUse>( 1 );
    CleanupStack::PushL( indexArray );
	listbox->GetColorUseListL(*indexArray);
	AssertTrueL(ETrue , KTextList4);
	CleanupStack::PopAndDestroy( indexArray );

	listbox->TestCreateItemDrawerL();
	AssertTrueL(ETrue , KTextList5);
	
	
    RFs& tempServer = iEikEnv->FsSession();
    tempServer.Delete( KStreamName );    
    RFileWriteStream fWrite;
    User::LeaveIfError( fWrite.Create( tempServer, 
        KStreamName, EFileWrite ) );    
    CleanupClosePushL( fWrite );
    listbox->TestWriteInternalStateL( fWrite );
    CleanupStack::PopAndDestroy( &fWrite );
	AssertTrueL(ETrue , KTextList6);
	CleanupStack::Pop(listbox);
	
	delete listbox;
	AssertTrueL(ETrue , KTextList7);
	
	//test ContructFromResurceL 
	CSubEikTextListBox * listbox2 = new( ELeave )CSubEikTextListBox();
	CleanupStack::PushL(listbox2);
	AssertNotNullL(listbox2 , KTextList8);
	
	listbox2->SetContainerWindowL( *iContainer ); 
	TResourceReader resourceReader;
    iEikEnv->CreateResourceReaderLC( resourceReader, 
                             R_BCTESTMIX50_LIST_MARKABLELIST_BIG_SINGLE );
    AssertTrueL( ETrue, KTextList9 );
    listbox2->ConstructFromResourceL( resourceReader );
    AssertTrueL( ETrue, KTextList10 );
	
	CleanupStack::PopAndDestroy(); //resourceReader
	CleanupStack::Pop(); //listbox2
	delete listbox2;
	AssertTrueL(ETrue , KTextList11);
	
	}
//----------------------------------------------------------------------------
// Test CTextListBoxModel
//----------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestTextListBoxModelL()
	{
	_LIT( KModel1 , "CTextListBoxModel::CTextListBoxModel() invoked" );
	_LIT( KModel2 , "CTextListBoxModel::MatchableTextArray() invoked" );
	_LIT( KModel3 , "CTextListBoxModel::ItemArrayOwnershipType() invoked" );
	_LIT( KModel4 , "CTextListBoxModel::SetItemTextArray() invoked" );
	_LIT( KModel5 , "CTextListBoxModel::SetOwnershipType() invoked" );
	_LIT( KModel6 , "CTextListBoxModel::~CTextListBoxModel() invoked" );
	
	CSubTextListBoxModel* model = new( ELeave ) CSubTextListBoxModel();      
    CleanupStack::PushL( model );
    AssertNotNullL( model, KModel1 );

	CDesCArray* textArray = iEikEnv->ReadDesCArrayResourceL( 
		R_BCTESTMIX50_LIST_ITEM_SINGLE1 );
	CleanupStack::PushL( textArray );
	
	const MDesCArray* array = model->MatchableTextArray();
    AssertTrueL( ETrue, KModel2 );
    delete array;
    
	TListBoxModelItemArrayOwnership type = 
		model->TestItemArrayOwnershipType();
    AssertTrueL( ETrue, KModel3 );
	
	model->SetItemTextArray( textArray );
    AssertTrueL( ETrue, KModel4 );

	model->SetOwnershipType( ELbmOwnsItemArray );
    AssertTrueL( ETrue, KModel5 );
	
	CleanupStack::Pop(); // textArray
	CleanupStack::Pop(); // model
	delete model;
    AssertTrueL( ETrue, KModel6 );
	}

//----------------------------------------------------------------------------
//Test CEikSnakingListBoxL
//----------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestEikSnakingListBoxL()
	{
	_LIT( KSnakeList1 , "CEikSnakingListBox::CEikSnakingListBox() invoked" );
	_LIT( KSnakeList2 , "CEikSnakingListBox::ConstructL() invoked" );
	_LIT( KSnakeList3 , 
		"CEikSnakingListBox::MakeViewClassInstanceL() invoked" );
	_LIT( KSnakeList4 , "CEikSnakingListBox::ColumnWidth() invoked" );
	_LIT( KSnakeList5 , "CEikSnakingListBox::SetColumnWidth() invoked" );
	_LIT( KSnakeList6 , "CEikSnakingListBox::HandlePointerEventL() invoked" );
	_LIT( KSnakeList7 , "CEikSnakingListBox::SetTopItemIndex() invoked" );
	_LIT( KSnakeList8 , 
			"CEikSnakingListBox::HandleViewRectSizeChangeL() invoked" );
	_LIT( KSnakeList9 , 
		"CEikSnakingListBox::HandleLeftArrowKeyL() invoked" );
	_LIT( KSnakeList10 , 
		"CEikSnakingListBox::HorizontalNudgeValue() invoked" );
	_LIT( KSnakeList11 , 
			"CEikSnakingListBox::HorizScrollGranularityInPixels() invoked" );
	_LIT( KSnakeList12 , 
		"CEikSnakingListBox::AdjustTopItemIndex() invoked" );
	_LIT( KSnakeList13 , "CEikSnakingListBox::HandleDragEventL() invoked" );
	_LIT( KSnakeList14 , 
		"CEikSnakingListBox::RestoreClientRectFromViewRect() invoked" );
	_LIT( KSnakeList15 , 
		"CEikSnakingListBox::AdjustRectHeightToWholeNumberOfItems() \
		invoked" );
	_LIT( KSnakeList16 , 
			"CEikSnakingListBox::MoveToNextOrPreviousItemL() invoked" );
	_LIT( KSnakeList17 , 
			"CEikSnakingListBox::SizeChanged() invoked" );
	_LIT( KSnakeList18 , "CEikSnakingListBox::GetColorUseListL() invoked" );
	_LIT( KSnakeList19 , 
		"CEikSnakingListBox::HandleResourceChange() invoked" );
    _LIT( KSnakeList20 , 
		"CEikSnakingListBox::HandleRightArrowKeyL() invoked" );
	_LIT( KSnakeList21 , 
		"CEikSnakingListBox::~CEikSnakingListBox() invoked" );

	CDesCArray* textArray = iEikEnv->ReadDesCArrayResourceL( 
		R_BCTESTMIX50_LIST_ITEM_SINGLE1 );
    CleanupStack::PushL( textArray );    
    
   	CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer = new( ELeave ) CTextListItemDrawer( model , 
		iEikEnv->NormalFont() );
    CleanupStack::PushL( drawer );
	CSubListBoxData *boxData = new( ELeave )CSubListBoxData();
	boxData->ConstructL( iEikEnv->NormalFont() );
	boxData->AddActualFontL( iEikEnv->NormalFont() );
	drawer->SetData( boxData );
		
	CSubEikSnakingListBox *snakeList = new ( ELeave ) CSubEikSnakingListBox();
	CleanupStack::PushL( snakeList );
	AssertNotNullL( snakeList, KSnakeList1 );
	
	TGulBorder border( TGulBorder::ESingleGray );
    snakeList->ConstructL( model, drawer, iContainer, border,
		EAknListBoxSelectionList | EAknListBoxViewerFlags ); 
    AssertTrueL( ETrue, KSnakeList2 );
	
	CListBoxView* view = snakeList->MakeViewClassInstanceL();
    AssertNotNullL( view, KSnakeList3 );
    delete view;
	
	TInt width = snakeList->ColumnWidth();
    AssertTrueL( ETrue, KSnakeList4 );
	
	snakeList->SetColumnWidth( 10 );
    AssertTrueL( ETrue, KSnakeList5 );
	
	TPointerEvent event;
	event.iType = TPointerEvent::EButton1Down;
	event.iModifiers = 0;
	TPoint eventPos( 0, 30 );
	event.iPosition = eventPos;
	event.iParentPosition = eventPos;
	snakeList->HandlePointerEventL( event );
    AssertTrueL( ETrue, KSnakeList6 );
	
	snakeList->SetTopItemIndex( 1 );
    AssertNotNullL( view, KSnakeList7 );
    
	snakeList->HandleViewRectSizeChangeL();
    AssertTrueL( ETrue , KSnakeList8 );
    
	snakeList->HandleLeftArrowKeyL( CListBoxView::ESingleSelection );
    AssertTrueL( ETrue , KSnakeList9 );
	
	TInt nudgeValue = snakeList->HorizontalNudgeValue();
    AssertTrueL( ETrue , KSnakeList10 );
	
	TInt granularity = snakeList->HorizScrollGranularityInPixels();
    AssertTrueL( ETrue , KSnakeList11 );
	
	snakeList->AdjustTopItemIndex();
    AssertTrueL( ETrue , KSnakeList12 );
	
	snakeList->HandleDragEventL(TPoint( 0, 0 ));
    AssertTrueL( ETrue , KSnakeList13 );
	
	TRect rect = iContainer->Rect();	
	snakeList->RestoreClientRectFromViewRect( rect );
    AssertTrueL( ETrue , KSnakeList14 );
	
	TInt pixelReduced = 
		snakeList->AdjustRectHeightToWholeNumberOfItems( rect );
    AssertTrueL( ETrue , KSnakeList15 );
	
	snakeList->MoveToNextOrPreviousItemL( TPoint( 10, 50 ) );
    AssertTrueL( ETrue , KSnakeList16 );
	
	snakeList->SizeChanged();
    AssertTrueL( ETrue , KSnakeList17 );
	
	CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
		CArrayFixFlat<TCoeColorUse>( 4 );
    CleanupStack::PushL( colorUseList );
	snakeList->GetColorUseListL( *colorUseList );
	AssertTrueL( ETrue , KSnakeList18 );
	CleanupStack::PopAndDestroy( colorUseList );
    
	snakeList->HandleResourceChange( KAknsMessageSkinChange );
    AssertTrueL( ETrue , KSnakeList19 );
	snakeList->HandleRightArrowKeyL( CListBoxView::ESingleSelection );
    AssertTrueL( ETrue , KSnakeList20 );

	CleanupStack::Pop( snakeList );
	CleanupStack::Pop( drawer );
	CleanupStack::Pop( model );
	CleanupStack::Pop( textArray );
	delete snakeList;
    AssertTrueL( ETrue, KSnakeList21 );
	}

//----------------------------------------------------------------------------
// test CEikListBox
//----------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestEikListBoxL() 
	{
	_LIT( KEikListBox1 , "CEikListBox::CEikListBox() invoked" );
	_LIT( KEikListBox2 , "CEikListBox::ConstructL() invoked" );
	_LIT( KEikListBox3 , "CEikListBox::HandleScrollEventL() invoked" );
	_LIT( KEikListBox4 , "CEikListBox::VerticalInterItemGap() invoked" );
    _LIT( KEikListBox5 , "CEikListBox::GetColorUseListL() invoked" );
	_LIT( KEikListBox6 , "CEikListBox::GetColorUseListL2() invoked" );
	_LIT( KEikListBox7 , "CEikListBox::GetColorUseListL3() invoked" );
	_LIT( KEikListBox8 , "CEikListBox::GetColorUseListL4() invoked" );
	_LIT( KEikListBox9 , "CEikListBox::HighlightRect() invoked" );
	_LIT( KEikListBox10 , "CEikListBox::UndoLastChar() invoked" );
	_LIT( KEikListBox11 , "CEikListBox::HandleLeftArrowKeyL() invoked" );
	_LIT( KEikListBox12 , "CEikListBox::HandleRightArrowKeyL() invoked" );
	_LIT( KEikListBox13 , "CEikListBox::MakeViewClassInstanceL() invoked" );
	_LIT( KEikListBox14 , "CEikListBox::SetReasonForFocusLostL() invoked" );
	_LIT( KEikListBox15 , "CEikListBox::ReasonForFocusLostL() invoked" );
	_LIT( KEikListBox16 , "CEikListBox::EnableMSKObserver() invoked" );
		
	CDesCArray* textArray = iEikEnv->ReadDesCArrayResourceL( 
        R_BCTESTMIX50_LIST_ITEM_SINGLE1 );
    CleanupStack::PushL( textArray );    
   
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer = new( ELeave ) CTextListItemDrawer();
    CleanupStack::PushL( drawer );
    drawer->ConstructL( iEikEnv->NormalFont() );
	CEikListBox* listBox1 = new( ELeave ) CEikListBox();
    CleanupStack::PushL( listBox1 );    
	AssertNotNullL( listBox1, KEikListBox1 );
	 
    listBox1->ConstructL( model, drawer, 
        iContainer,  EAknListBoxSelectionList | EAknListBoxViewerFlags );    
    AssertNotNullL( listBox1, KEikListBox2 );

    CleanupStack::PopAndDestroy( listBox1 );
    CleanupStack::Pop( drawer );
    CleanupStack::Pop( model );
    CleanupStack::Pop( textArray );

 	textArray = iEikEnv->ReadDesCArrayResourceL( 
        R_BCTESTMIX50_LIST_ITEM_SINGLE1 );
    CleanupStack::PushL( textArray );    
   
    model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    drawer = new ( ELeave ) CTextListItemDrawer( model, iEikEnv->NormalFont() );
    CleanupStack::PushL( drawer ); 
    
    CSubEikListBox* listBox = new( ELeave ) CSubEikListBox();
    CleanupStack::PushL( listBox ); 
	
    TGulBorder border( TGulBorder::ESingleGray );
    listBox->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );    
	listBox->SetDimmed( ETrue );

	CEikScrollBar* scrollBar = new( ELeave ) CEikScrollBar();
    CleanupStack::PushL( scrollBar );
    scrollBar->ConstructL( listBox , iContainer , CEikScrollBar::EVertical ,
        iContainer->Rect().Size().iHeight );    
	listBox->HandleScrollEventL( scrollBar , EEikScrollDown );
    AssertNotNullL( listBox, KEikListBox3 );

	TInt botIndex = listBox->BottomItemIndex();
	
	TRect rect = iContainer->Rect();
    listBox->CalculatePopoutRect( 0 , 0 , rect );

	TSize size = listBox->CalcSizeInPixels( 5 , 2 );
	TInt width = listBox->CalcWidthBasedOnNumOfChars( 5 );
	listBox->CalcHeightBasedOnNumOfItems( 2 );
	listBox->CalcWidthBasedOnRequiredItemWidth( 30 );
		
	TInt verticalInterItemGap = listBox->VerticalInterItemGap();
    AssertTrueL( ETrue, KEikListBox4 );

	listBox->SetLaunchingButton( NULL );
	listBox->SetItemEditor( NULL);
	MEikListBoxEditor* editor = listBox->ItemEditor();
	listBox->EditItemL( 10 );
	listBox->StopEditingL( EFalse );
	TInt shortcutValue = listBox->ShortcutValueForNextList();
	listBox->SetShortcutValueFromPrevList( 1 );

	CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( 4 );
    CleanupStack::PushL( colorUseList );
    listBox->GetColorUseListL( *colorUseList );
    AssertTrueL( ETrue, KEikListBox5 );
	
    colorUseList->Reset(); 
    AssertTrueL( ETrue, KEikListBox6 );
	
    listBox->GetColorUseListL( *colorUseList );
    AssertTrueL( ETrue, KEikListBox7 );
	
    CleanupStack::PopAndDestroy( colorUseList ); 
    AssertTrueL( ETrue, KEikListBox8 );
	
	TRect hightlightRect = listBox->HighlightRect();
    AssertTrueL( ETrue, KEikListBox9 );
	
	listBox->CreateMatchBufferL();
	listBox->UndoLastChar();
    AssertTrueL( ETrue , KEikListBox10 );
  
	TInt scrollGraInPixels = listBox->HorizScrollGranularityInPixels();
	
	TInt horizontalNudge = listBox->HorizontalNudgeValue();
	listBox->SimulateArrowKeyEventL( EKeyDownArrow );
	listBox->HandleLeftArrowKeyL( CListBoxView::ESingleSelection );
    AssertTrueL( ETrue, KEikListBox11 );
	
	listBox->HandleRightArrowKeyL( CListBoxView::ENoSelection );
    AssertTrueL( ETrue, KEikListBox12 );
	
	CListBoxView* view = listBox->MakeViewClassInstanceL();
	AssertTrueL( ETrue, KEikListBox13 );
	delete view;
    
	TInt height = listBox->ViewRectHeightAdjustment();
	listBox->SetViewRectHeightAdjustment( 10 );
	listBox->HandleDragEventL( TPoint( 0, 0 ) );
	TInt interItemGap = listBox->InterItemGap();
	listBox->SetReasonForFocusLostL( 
		CEikListBox::EFocusLostToExternalControl );
   	AssertTrueL( ETrue, KEikListBox14 );
	
   	CEikListBox::TReasonForFocusLost rffl = listBox->ReasonForFocusLostL();
	AssertTrueL( ETrue, KEikListBox15 );
	
	TEikScrollBarFrameLayout frameLayout;
	listBox->CreateScrollBarFrameLayout( frameLayout );
    
	TInt eventModified = listBox->EventModifiers();
	CEikScrollBarFrame* scrollBar2 = listBox->CreateScrollBarFrameL();
	listBox->EnableMSKObserver(ETrue);
    AssertTrueL( ETrue , KEikListBox16 );
	
	CleanupStack::PopAndDestroy( scrollBar );
    CleanupStack::PopAndDestroy( listBox );
    CleanupStack::Pop( drawer );
    CleanupStack::Pop( model );
    CleanupStack::Pop( textArray );
	}

//----------------------------------------------------------------------------
//Test CSnakingListBoxView
//----------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestSnakingListBoxViewL()
	{
	_LIT( KSnakeList1 , 
		"CSubEikSnakingListBox::CSubEikSnakingListBox() invoked" );
	_LIT( KListView1 , "CSnakingListBoxView::SetColumnWidth()  invoked" );
	_LIT( KListView2 , "CSnakingListBoxView::SetItemHeight()  invoked" );
	_LIT( KListView3 , 
		"CSnakingListBoxView::NumberOfItemsThatFitInRect()  invoked" );
	_LIT( KListView4 , "CSnakingListBoxView::HScroll()  invoked" );
	_LIT( KListView5 , "CSnakingListBoxView::CalcDataWidth()  invoked" );
	_LIT( KListView6 , 
		"CSnakingListBoxView::CalcBottomItemIndex()  invoked" );
	_LIT( KListView7 , "CSnakingListBoxView::Draw()  invoked" );
	_LIT( KListView8 , "CSnakingListBoxView::VisibleWidth()  invoked" );
	_LIT( KListView9 , 
		"CSnakingListBoxView::ScrollToMakeItemVisible() invoked" );
	_LIT( KListView10 , 
		"CSnakingListBoxView::CalculateHScrollOffsetSoItemIsVisible() \
		invoked" );
	_LIT( KListView11 , 
		"CSnakingListBoxView::CalcNewTopItemIndexSoItemIsVisible() invoked" );
	_LIT( KListView12 , "CSnakingListBoxView::ItemPos()  invoked" );
	_LIT( KListView13 , 
		"CSnakingListBoxView::CalcRowAndColIndexesFromItemIndex() invoked" );
	_LIT( KListView14 , 
		"CSnakingListBoxView::ItemSize()  invoked" );
	_LIT( KListView15 , 
		"CSnakingListBoxView::CalcItemIndexFromRowAndColIndexes()  invoked" );
	_LIT( KListView16 , 
		"CSnakingListBoxView::NumberOfItemsPerColumn()  invoked" );
	_LIT( KListView17 , "CSnakingListBoxView::DrawItemRange()  invoked" );
	_LIT( KListView18, "CSnakingListBoxView::DrawColumnRange()  invoked" );
	_LIT( KListView19 , 
		"CSnakingListBoxView::MoveToPreviousColumnL()  invoked" );
	_LIT( KListView20 , "CSnakingListBoxView::MoveToNextColumnL()  invoked" );
	_LIT( KListView21 , 
		"CSnakingListBoxView::ClearUnusedItemSpace()  invoked" );
	_LIT( KListView22 , 
		"CSnakingListBoxView::UpdateHScrollOffsetBasedOnTopItemIndex()\
		invoked" );
	_LIT( KSnakeList23 , 
	"CSubEikSnakingListBox::~CSubEikSnakingListBox() invoked" );

	
	CDesCArray* textArray = iEikEnv->ReadDesCArrayResourceL
		( R_BCTESTMIX50_LIST_ITEM_SINGLE1 );
    CleanupStack::PushL( textArray );    
    
   	CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );

    CTextListItemDrawer* drawer = new( ELeave ) CTextListItemDrawer( model , 
		iEikEnv->NormalFont() );
    CleanupStack::PushL( drawer );
	CSubListBoxData *boxData = new(ELeave)CSubListBoxData();
	boxData->ConstructL( iEikEnv->NormalFont() );
	boxData->AddActualFontL( iEikEnv->NormalFont() );
	drawer->SetData( boxData );

	CSubEikSnakingListBox *snakeList = new ( ELeave ) CSubEikSnakingListBox();
	CleanupStack::PushL( snakeList );
    AssertNotNullL( snakeList, KSnakeList1 );
	
	TGulBorder border( TGulBorder::ESingleGray );
    snakeList->ConstructL( model, drawer, iContainer, border, 
		EAknListBoxSelectionList | EAknListBoxViewerFlags );

	//Test CSnakingListBoxViewL
	snakeList->CreateViewL();
	CSubSnakingListBoxView * listView = 
		( CSubSnakingListBoxView * )snakeList->iView;
	listView->SetColumnWidth( 10 );
    AssertTrueL( ETrue , KListView1 );

	listView->MoveCursorL( CListBoxView::ECursorNextItem, 
		CListBoxView::ENoSelection );
	listView->SetTopItemIndex( 1 );
	listView->SetItemHeight ( 10 );
	
    AssertTrueL( ETrue , KListView2 );
	TPoint point( 0 , 0 );
	TInt index = 1;
	listView->XYPosToItemIndex( point , index);
	
	TRect rect = iContainer->Rect();
	TInt numbers = listView->NumberOfItemsThatFitInRect( rect );
    AssertTrueL( ETrue , KListView3 );
	
	listView->HScroll( 2 );
    AssertTrueL( ETrue , KListView4 );
	
	listView->CalcDataWidth();
    AssertTrueL( ETrue , KListView5 );
	
	listView->CalcBottomItemIndex();
    AssertTrueL( ETrue , KListView6);
	
	listView->Draw();
    AssertTrueL( ETrue , KListView7 );
	
	TInt width = listView->VisibleWidth(rect);
    AssertTrueL( ETrue , KListView8 );
	
	listView->ScrollToMakeItemVisible( 1 );
    AssertTrueL( ETrue , KListView9 );
	
	listView->CalculateHScrollOffsetSoItemIsVisible( 1 );
    AssertTrueL( ETrue , KListView10 );
	
	listView->CalcNewTopItemIndexSoItemIsVisible( 2 );
    AssertTrueL( ETrue , KListView11 );
	
	TPoint point2 = listView->ItemPos(2);
    AssertTrueL( ETrue , KListView12 );
	
	TSize size = listView->ItemSize();
    AssertTrueL( ETrue , KListView13 );
	
	TInt itemIndex = 1 ; 
	TInt rowIndex = 0 ;
	TInt colIndex = 0 ;
	listView->CalcRowAndColIndexesFromItemIndex( itemIndex , rowIndex ,
		colIndex );
    AssertTrueL( ETrue , KListView14 );
	
	colIndex = 0;
	listView->CalcItemIndexFromRowAndColIndexes( itemIndex , rowIndex ,
		colIndex );
    AssertTrueL( ETrue , KListView15 );
    
	TInt perColumn = listView->NumberOfItemsPerColumn();
    AssertTrueL( ETrue , KListView16 );
	
	listView->DrawItemRange( 1 , 5 );
    AssertTrueL( ETrue , KListView17 );
	
	listView->DrawColumnRange( 2 ,4 );
    AssertTrueL( ETrue , KListView18 );
	
	listView->MoveToPreviousColumnL(CListBoxView::ESingleSelection);
    AssertTrueL( ETrue , KListView19 );
	
	listView->MoveToNextColumnL(CListBoxView::ESingleSelection);
    AssertTrueL( ETrue , KListView20 );
	
	listView->ClearUnusedItemSpace( 1 , 2 );
    AssertTrueL( ETrue , KListView21 );
	
	listView->UpdateHScrollOffsetBasedOnTopItemIndex();
    AssertTrueL( ETrue , KListView22 );

	CleanupStack::Pop( snakeList );
	CleanupStack::Pop( drawer );
	CleanupStack::Pop( model );
	CleanupStack::Pop( textArray );
	delete snakeList;
    AssertTrueL( ETrue, KSnakeList23 );	
	}

//---------------------------------------------------------------------------
//Test CListBoxView
//---------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestListBoxViewL()
	{
	_LIT( KListBoxView1 , "CEikListBox::CEikListBox() invoked" );
	_LIT( KListBoxView2 , "CEikListBox::ConstructL() invoked" );
	_LIT( KListBoxView3 , "CEikListBox::CreateViewL() invoked" );
	_LIT( KListBoxView4 , "CListBoxView::SetDimmed() invoked" );
	_LIT( KListBoxView5 , "CListBoxView::SetPaintedSelection() invoked" );
	_LIT( KListBoxView6 , "CListBoxView::HScroll() invoked" );
	_LIT( KListBoxView7 , "CListBoxView::Draw() invoked" );
	_LIT( KListBoxView8 , "CListBoxView::TextColor() invoked" );
	_LIT( KListBoxView9 , "CListBoxView::DrawEmptyList() invoked" );
	_LIT( KListBoxView10 , "CListBoxView::DeselectRangeL() invoked" );
	_LIT( KListBoxView11 , "CListBoxView::SelectRangeL() invoked" );
	_LIT( KListBoxView12 , "PopAndDestroy invoked" );

	CDesCArray* textArray = iEikEnv->ReadDesCArrayResourceL( 
        R_BCTESTMIX50_LIST_ITEM_SINGLE1 );
    CleanupStack::PushL( textArray );    
   
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer = new( ELeave ) CTextListItemDrawer();
    CleanupStack::PushL( drawer );
	CSubListBoxData *boxData = new( ELeave )CSubListBoxData();
	boxData->ConstructL( iEikEnv->NormalFont() );
	boxData->AddActualFontL( iEikEnv->NormalFont() );
	drawer->SetData( boxData );

	
    CSubEikListBox* listBox = new( ELeave ) CSubEikListBox();
    CleanupStack::PushL( listBox ); 
    AssertTrueL( ETrue, KListBoxView1 );
	
    TGulBorder border( TGulBorder::ESingleGray );
    listBox->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    AssertTrueL( ETrue, KListBoxView2 );
	
	listBox->CreateViewL();
	AssertTrueL( ETrue, KListBoxView3 );
	
	CSubListBoxView * listView = ( CSubListBoxView * )listBox->iView;
	//begin test CListBoxView
	listView->SetDimmed( ETrue );
    AssertTrueL( ETrue, KListBoxView4 );
	
	listView->SetPaintedSelection( ETrue );
    AssertTrueL( ETrue, KListBoxView5 );

	listView->HScroll( 10 );
    AssertTrueL( ETrue, KListBoxView6 );
	
	listView->Draw();
    AssertTrueL( ETrue, KListBoxView7 );
	
	TRgb rgb = listView->TextColor();
    AssertTrueL( ETrue, KListBoxView8 );
	
	listView->DrawEmptyList( iContainer->Rect() );
    AssertTrueL( ETrue, KListBoxView9);
	
	listView->DeselectRangeL( 0 , 4 );
    AssertTrueL( ETrue, KListBoxView10 );
	
	listView->SelectRangeL( 1 , 3 );
    AssertTrueL( ETrue, KListBoxView11 );

	CleanupStack::PopAndDestroy( listBox );
    AssertTrueL( ETrue, KListBoxView12 );
	
	CleanupStack::Pop( drawer );
	CleanupStack::Pop( model );
	CleanupStack::Pop( textArray );

	}
//----------------------------------------------------------------------------
// test TextListItemDrawer()
//----------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestTextListItemDrawerL()
	{
	_LIT( KTestItemDrawer1, 
		"CTextListItemDrawer::ItemWidthInPixels () invoked" );
	_LIT( KTestItemDrawer2,
		"CTextListItemDrawer::MatcherCursorRect () invoked" );
	_LIT( KTestItemDrawer3, 
		"CTextListItemDrawer::MatcherCursorAscent () invoked" );
	_LIT( KTestItemDrawer4, "CTextListItemDrawer::SetFont () invoked" );
	_LIT( KTestItemDrawer5, 
		"CTextListItemDrawer::SetSearchStringL () invoked" );
	_LIT( KTestItemDrawer6, "CTextListItemDrawer::Font () invoked" );
	_LIT( KTestItemDrawer7, "CTextListItemDrawer::ItemCellSize () invoked" );
	_LIT( KTestItemDrawer8, "CTextListItemDrawer::DrawItemText () invoked" );
	_LIT( KListItemDrawer9, 
		"CListItemDrawer::ItemWidthInPixels () invoked" );
	_LIT( KListItemDrawer10, "CListItemDrawer::MinimumCellSize () invoked" );
	_LIT( KListItemDrawer11, "CListItemDrawer::SetGc () invoked" );
	_LIT( KListItemDrawer12, 
		"CListItemDrawer::SetMarkColumnWidth () invoked" );
	_LIT( KListItemDrawer13, "CListItemDrawer::SetMarkGutter () invoked" );
	_LIT( KListItemDrawer14, "CListItemDrawer::MarkColumn () invoked" );
	_LIT( KListItemDrawer15, "CListItemDrawer::MarkGutter () invoked" );
	_LIT( KListItemDrawer16, 
		"CListItemDrawer::MatcherCursorRect () invoked" );
	_LIT( KListItemDrawer17, 
		"CListItemDrawer::MatcherCursorAscent () invoked" );
	_LIT( KListItemDrawer18, "CListItemDrawer::DrawItemMark () invoked" );
	_LIT( KListItemDrawer19, "CListItemDrawer::SetSymbolFont () invoked" );
	_LIT( KListItemDrawer20, "CListItemDrawer::DrawFrame () invoked" );

	CDesCArray* textArray = iEikEnv->ReadDesCArrayResourceL( 
        R_BCTESTMIX50_LIST_ITEM_SINGLE1 );
    CleanupStack::PushL( textArray );    
   
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );

	CSubTextListItemDrawer* textDrawer = new( ELeave ) CSubTextListItemDrawer(
		model , iEikEnv->NormalFont() );
    CleanupStack::PushL( textDrawer );
	CSubListBoxData *boxData = new(ELeave)CSubListBoxData();
	CleanupStack::PushL( boxData );
	boxData->ConstructL( iEikEnv->NormalFont() );
	boxData->AddActualFontL( iEikEnv->NormalFont() );

	textDrawer->SetData( boxData );
	textDrawer->ItemWidthInPixels( 1 );
    AssertTrueL( ETrue, KTestItemDrawer1 );
	TRect cursorRect = iContainer->Rect();
	
	cursorRect = textDrawer->MatcherCursorRect( KTestItemDrawer3 ,
		0 , 0 , 0 );
    AssertTrueL( ETrue, KTestItemDrawer2 );
	TInt cursorAscent = textDrawer->MatcherCursorAscent( 0 );
    AssertTrueL( ETrue, KTestItemDrawer3 );
	textDrawer->SetFont( iEikEnv->TitleFont() );
    AssertTrueL( ETrue, KTestItemDrawer4 );
	
	TPtrC ptr( KTestItemDrawer6 ); 
	textDrawer->SetSearchStringL( &ptr );
    AssertTrueL( ETrue, KTestItemDrawer5 );
	
	const CFont* font = textDrawer->Font( 0 );
    AssertTrueL( ETrue, KTestItemDrawer6 );
	
	iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    textDrawer->SetGc( &gc );    
    TSize size = textDrawer->ItemCellSize();
    AssertTrueL( ETrue, KTestItemDrawer7 );
	
    TRect rect( TPoint( 0 , 0 ), size );    
	textDrawer->DrawItemText( 0 , rect , ETrue , EFalse , EFalse );
    AssertTrueL( ETrue, KTestItemDrawer8 );
	iContainer->DeactivateGc();
	//Test CListItemDrawer
	textDrawer->CListItemDrawer::ItemWidthInPixels( 0 );
    AssertTrueL( ETrue, KListItemDrawer9 );
	
	size = textDrawer->CListItemDrawer::MinimumCellSize();
    AssertTrueL( ETrue, KListItemDrawer10 );
	
	textDrawer->CListItemDrawer::SetGc( &gc );
    AssertTrueL( ETrue, KListItemDrawer11 );
	
	textDrawer->CListItemDrawer::SetMarkColumnWidth( 30 );
    AssertTrueL( ETrue, KListItemDrawer12 );
	
	textDrawer->CListItemDrawer::SetMarkGutter( 10 );
    AssertTrueL( ETrue, KListItemDrawer13 );
	
	TInt colum = textDrawer->CListItemDrawer::MarkColumn();
    AssertTrueL( ETrue, KListItemDrawer14 );
	
	TInt gutter = textDrawer->CListItemDrawer::MarkGutter();
    AssertTrueL( ETrue, KListItemDrawer15 );
	
	cursorRect = textDrawer->CListItemDrawer::MatcherCursorRect(
		KTestItemDrawer3 , 0 , 0 , 0 );
    AssertTrueL( ETrue, KListItemDrawer16 );
	
	cursorAscent = textDrawer->CListItemDrawer::MatcherCursorAscent( 0 );
    AssertTrueL( ETrue, KListItemDrawer17 );
	
	TPoint pt( 0, 0 );
	textDrawer->CListItemDrawer::DrawItemMark( ETrue , EFalse , pt );
    AssertTrueL( ETrue, KListItemDrawer18 );
	
	textDrawer->CListItemDrawer::SetSymbolFont( iEikEnv->NormalFont() );
    AssertTrueL( ETrue, KListItemDrawer19 );
	
	CFont* itemFont = textDrawer->CListItemDrawer::Font( 0 );
	textDrawer->CListItemDrawer::DrawFrame( gc , rect , 0 );
    AssertTrueL( ETrue, KListItemDrawer20 );
	
	CleanupStack::Pop( boxData );
    CleanupStack::PopAndDestroy( textDrawer );
	CleanupStack::PopAndDestroy( model );
	CleanupStack::Pop( textArray );
	}

//----------------------------------------------------------------------------
// Test CEikListBoxTextEditor
//----------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestListBoxTextEditorL()
	{
	_LIT( KStreamName, "C:\\bctestlog\\bctestlog1.txt" );

	_LIT( KTextEditor1, "CEikListBoxTextEditor::UpdateModelL() invoked" );
	_LIT( KTextEditor2, 
		"CEikListBoxTextEditor::HandlePointerEventL() invoked" );
	_LIT( KTextEditor3, "CEikListBoxTextEditor::ListBoxModel() invoked" );
	_LIT( KTextEditor4, "CEikListBoxTextEditor::ItemIndex() invoked" );
    _LIT( KTextEditor5, "CEikListBoxTextEditor::Editor() invoked" );
	_LIT( KTextEditor6, "CEikListBoxTextEditor::StopEditingL() invoked" );
	_LIT( KTextEditor7, "CEikListBoxTextEditor::Release() invoked" );

	CDesCArray* textArray = iEikEnv->ReadDesCArrayResourceL( 
        R_BCTESTMIX50_LIST_ITEM_SINGLE1 );
    CleanupStack::PushL( textArray );    
   
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );

	CSubEikListBoxTextEditor * textEditor = new CSubEikListBoxTextEditor( model );
	CleanupStack::PushL( textEditor );
	
	textEditor->SetFont( iEikEnv->NormalFont() );
    textEditor->SetListBoxEditorObserver( NULL );
	TPtrC text = textEditor->ItemText();

	TRect rect = iContainer->Rect();
    rect.iBr.iY = rect.iTl.iY + rect.Size().iHeight / 2;
  
	TKeyEvent eventEnter = { EKeyEnter , EKeyEnter , 0 , 0 };
	textEditor->OfferKeyEventL( eventEnter, EEventKey );

	textEditor->UpdateModelL();
    AssertTrueL( ETrue, KTextEditor1 );
	
	TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0 ;
    TPoint eventPos(0, 30) ;
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
	textEditor->HandlePointerEventL(event);
    AssertTrueL( ETrue, KTextEditor2 );
	
	CTextListBoxModel* listModel = 
		(CTextListBoxModel*)textEditor->ListBoxModel();
    AssertTrueL( ETrue, KTextEditor3 );
	
	TInt index = textEditor->ItemIndex();
    AssertTrueL( ETrue, KTextEditor4 );

	textEditor->StartEditingL( *iContainer, rect , 0 , 30 );
    CEikEdwin* edWin = textEditor->Editor();
    AssertTrueL( ETrue, KTextEditor5 );
	
	RFs& tempServer = iEikEnv->FsSession();
    tempServer.Delete( KStreamName );
    AssertTrueL( ETrue, KStreamName );
	
    RFileWriteStream fWrite;
    User::LeaveIfError( fWrite.Create( tempServer, 
        KStreamName, EFileWrite ) );
    CleanupClosePushL( fWrite );
    textEditor->WriteInternalStateL( fWrite );
    CleanupStack::PopAndDestroy( &fWrite );

	textEditor->StopEditingL();
    AssertTrueL( ETrue, KTextEditor6 );
	
	textEditor->Release();
    AssertTrueL( ETrue, KTextEditor7 );
	
	CleanupStack::Pop( textEditor );
	CleanupStack::PopAndDestroy( model );
	CleanupStack::Pop( textArray );
	}
//---------------------------------------------------------------------------
// Test CListBoxData and CFontsWithStyle
//---------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestListBoxDataL()
	{
	_LIT( KEikSearchString, "searching" );
	_LIT( KEikTestText, "test text" );
	
	_LIT( KLbData1, "CListBoxData::CListBoxData() invoked" );
	_LIT( KLbData2, "CListBoxData::ConstructL() invoked" );
	_LIT( KLbData3, "CListBoxData::FontBoundValues() invoked" );
	_LIT( KLbData4, "CListBoxData::SetFontHeight() invoked" );
	_LIT( KLbData5, "CListBoxData::ConstructFontL() invoked" );
	_LIT( KLbData6, "CListBoxData::UpdateFontBoundValues() invoked" );
	_LIT( KLbData7, "CListBoxData::IsSearchString() invoked" );
	_LIT( KLbData8, "CListBoxData::DrawItem() invoked" );
	_LIT( KLbData9, "CFontsWithStyle class function invoked" ); 


	CSubListBoxData *listdata = new( ELeave ) CSubListBoxData();
	CleanupStack::PushL( listdata );
	AssertTrueL( ETrue, KLbData1 );
	
    listdata->ConstructL( iEikEnv->NormalFont() ); 
	AssertTrueL( ETrue, KLbData2 );
	
	const TListFontBoundValues& boundValue = listdata->FontBoundValues();
	AssertTrueL( ETrue, KLbData3 );
	
	TInt fontHeightInTwips = 10;
    TInt height = listdata->SetFontHeight( fontHeightInTwips );
	AssertTrueL( ETrue, KLbData4 );
	
	TFontStyle style( EPostureItalic, EStrokeWeightBold, 
        EPrintPosSuperscript );    
    listdata->ConstructFontL( iEikEnv->TitleFont(), style,
		listdata->iItalicFont ); 
	AssertTrueL( ETrue, KLbData5 );
	
	listdata->UpdateFontBoundValues( *( iEikEnv->NormalFont() ) );
	fontHeightInTwips = 20;
    TInt ret = listdata->RegenerateFonts( listdata->iNormalFont, 
		fontHeightInTwips );  
    AssertTrueL( ETrue, KLbData6 );
	
	TPtrC ptr( KEikSearchString ); 
    listdata->SetSearchStringL( &ptr );
    TBool search = listdata->IsSearchString();
	AssertTrueL( ETrue, KLbData7 );
	
	iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    const TInt KRectHeight = 30;
    TRect rect = iContainer->Rect();
    rect.iBr.iY = rect.iTl.iY + KRectHeight;            
    const CFont& font = *iEikEnv->NormalFont();
    gc.UseFont( &font );
    listdata->DrawItem( gc, rect, KEikTestText, font, 0 );
	AssertTrueL( ETrue, KLbData8 );
	
	listdata->TestCFontWithStyle();
	AssertTrueL( ETrue, KLbData9 );
	
    iContainer->DeactivateGc();
	CleanupStack::PopAndDestroy(listdata);
	}
//-------------------------------------------------------------------------------------
// Test CFormattedCellListBoxData
//-------------------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestFormattedCellListBoxDataL()
	{
	_LIT( KFCListData1, "CFormattedCellListBoxData::NewL() invoked" );
	_LIT( KTColors, "TColors::TColors() invoked" );
	_LIT( KFCListData2, 
		"CFormattedCellListBoxData::SetSubCellRightSeparatorStyleL() invoked" );
	_LIT( KFCListData3, 
		"CFormattedCellListBoxData::SetSubCellTextClipGapL() invoked" );
	_LIT( KFCListData4, 
		"CFormattedCellListBoxData::HasHighlightAnim() invoked" );
	_LIT( KFCListData5, "CFormattedCellListBoxData::Rect() invoked" );
	_LIT( KFCListData6, 
		"CFormattedCellListBoxData::DrawHighlightAnim() invoked" );
	
	CFormattedCellListBoxData* data = CFormattedCellListBoxData::NewL();
	AssertTrueL( ETrue, KFCListData1 );
	
	CFormattedCellListBoxData::TColors * color =
		new (ELeave)CFormattedCellListBoxData::TColors();
	AssertTrueL( ETrue, KTColors );
	delete color;
	
	CGraphicsContext::TPenStyle pen = data->SubCellRightSeparatorStyle( 1 );
	data->SetSubCellRightSeparatorStyleL( 1 , CGraphicsContext::ESolidPen);
    AssertTrueL( ETrue, KFCListData2 );
	
	data->SetSubCellTextClipGapL( 1 , 10);
    AssertTrueL( ETrue, KFCListData3 );
	
	TBool ret  = data->HasHighlightAnim();
    AssertTrueL( ETrue, KFCListData4 );
	
	TRect rect = iContainer->Rect();
    AssertTrueL( ETrue, KFCListData5 );
	
	CWindowGc& gc = iContainer->SystemGc();
	data->DrawHighlightAnim( gc ,rect );
    AssertTrueL( ETrue, KFCListData6 );
	
	delete data;
	}

//----------------------------------------------------------------------------
// Test CEikFormattedCellListBox
//----------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestFormattedCellListBoxL()
	{

	CEikFormattedCellListBox* fcListBox = new CEikFormattedCellListBox();
	fcListBox->ConstructL( iContainer , EAknListBoxSelectionList);
	fcListBox->EnableStretching(ETrue);
	fcListBox->HideSecondRow(ETrue);
	delete fcListBox;
	}

//----------------------------------------------------------------------------
// Test CColumnListBoxData
//----------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestColumnListBoxDataL()
	{
	_LIT( KListData1, "CColumnListBoxData::SetColumnMarginsL() invoked" );
	_LIT( KListData2, "CColumnListBoxData::SetColumnAlignmentL() invoked" );
	_LIT( KListData3, 
		"CColumnListBoxData::SetColumnSeparatorStyleL() invoked" );
	_LIT( KListData4, "CColumnListBoxData::SetNumberColumnL() invoked" );
	_LIT( KListData5, "CColumnListBoxData::SetColumnTextClipGapL() invoked" );
	_LIT( KListData6, "CColumnListBoxData::HasHighlightAnim() invoked" );
	_LIT( KListData7, 
		"CColumnListBoxData::SubCellsMightIntersect() invoked" );
	_LIT( KListData8, "CColumnListBoxData::StretchingEnabled() invoked" );

	CColumnListBoxData* listData = CColumnListBoxData::NewL();
	TMargins margin;
	const TInt KLeft = 0;
	const TInt KTop = 0;
	const TInt KRight = 50;
	const TInt KBottom = 50;
    margin.iLeft = KLeft;
    margin.iRight = KRight;
    margin.iBottom = KBottom;
    margin.iTop = KTop;

	CColumnListBoxData::TColors *color = new CColumnListBoxData::TColors();
	delete color;
	listData->SetColumnMarginsL( 1 , margin );
    AssertTrueL( ETrue, KListData1 );
	
	listData->SetColumnAlignmentL( 1 , CGraphicsContext::ELeft );
    AssertTrueL( ETrue, KListData2 );
	
	listData->SetColumnSeparatorStyleL( 1 , CGraphicsContext::ESolidPen);
    AssertTrueL( ETrue, KListData3 );
	
	listData->SetNumberColumnL(2 , ETrue);
    AssertTrueL( ETrue, KListData4 );
	
	listData->SetColumnTextClipGapL( 3 , 10);
    AssertTrueL( ETrue, KListData5 );
	
	TBool hasHeighLight = listData->HasHighlightAnim();
    AssertTrueL( ETrue, KListData6 );
	
	CWindowGc& gc = iContainer->SystemGc();
	TRect rect = iContainer->Rect();
	listData->DrawHighlightAnim(gc, rect);
	listData->SubCellsMightIntersect(ETrue);
    AssertTrueL( ETrue, KListData7 );
	
	TBool stretch = listData->StretchingEnabled();
    AssertTrueL( ETrue, KListData8 );
	
	delete listData;
	}

//---------------------------------------------------------------------------
// Test CEikColumnListBox
//---------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestColumnListBoxL()
	{
	_LIT( KCListBox1, "CEikColumnListBox::ConstructL() invoked" );
	_LIT( KCListBox2, "CEikColumnListBox::EnableStretching() invoked" );

	CEikColumnListBox* columnList = new( ELeave ) CEikColumnListBox();
	columnList->ConstructL( iContainer );
	AssertTrueL( ETrue, KCListBox1 );
	
	columnList->EnableStretching(ETrue);
	AssertTrueL( ETrue, KCListBox2 );
	
	delete columnList;
	}

//----------------------------------------------------------------------------
// Test CAknSelectionListDialog CAknMarkableListDialog
//----------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestSelectionListDialogL()
	{
	_LIT( KSelListDlg1, "textArray::ReadDesCArrayResourceL() invoked" );
	_LIT( KSelListDlg2, "CAknSelectionListDialog::NewL() invoked" );
	_LIT( KSelListDlg3, 
		"CAknSelectionListDialog::beforeHandlePointerEventL() invoked" );
	_LIT( KSelListDlg4, 
		"CAknSelectionListDialog::HandlePointerEventL() invoked" );
	_LIT( KMarkedDlg1, 
		"CAknMarkableListDialog::CAknMarkableListDialog() invoked" );
	_LIT( KMarkedDlg2, 
		"CAknMarkableListDialog::HandlePointerEventL() invoked" );
  	_LIT( KMarkedDlg3, 
		"CAknMarkableListDialog::DynInitMenuPaneL() invoked" );
  	_LIT( KCAknMarkableListDialog,
  		"CAknMarkableListDialog::CAknMarkableListDialog()#1 invoked");
	
	TInt value( -1 );    
    CArrayFix<TInt>* markedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( markedItems );
    CDesCArray* textArray = NULL;   
    textArray = iEikEnv->ReadDesCArrayResourceL( R_BCTESTMIX50_LIST_ITEM_SINGLE1 );
    CleanupStack::PushL( textArray );
    AssertTrueL( ETrue, KSelListDlg1);
	
	CAknSelectionListDialog* selDlg = CAknSelectionListDialog::NewL(
        value, textArray, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    AssertTrueL( ETrue, KSelListDlg2);
	selDlg->PrepareLC( R_BCTESTMIX50_LIST_SINGLE_SELECTION_LIST_DIALOG );
    AssertTrueL( ETrue, KSelListDlg3 );
	
	TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos(0, 30);
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
	selDlg->HandlePointerEventL(event);
    AssertTrueL( ETrue, KSelListDlg4 );
	
	CleanupStack::PopAndDestroy( ); // PrepareLC
	CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( markedItems );	

	markedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( markedItems );
    textArray = NULL;   
    textArray = iEikEnv->ReadDesCArrayResourceL( R_BCTESTMIX50_LIST_ITEM_SINGLE1 );
    CleanupStack::PushL( textArray );
	
	CSubAknMarkableListDialog* markedDlg = CSubAknMarkableListDialog::NewL(
        value, markedItems, textArray ); 
    AssertTrueL( ETrue, KMarkedDlg1 );
    CleanupStack::PushL( markedDlg );    
    markedDlg->PrepareLC( R_BCTESTMIX50_LIST_MARKABLE_DIALOG );
	markedDlg->HandlePointerEventL(event);
    AssertTrueL( ETrue, KMarkedDlg2 );
	
	CEikMenuPane* menuPane = new( ELeave ) CEikMenuPane( markedDlg );
    CleanupStack::PushL( menuPane );    
    markedDlg->DynInitMenuPaneL( R_BCTESTMIX50_LIST_COLUMN_MENU, menuPane );    
    AssertTrueL( ETrue, KMarkedDlg3 );
    
    CDesCArrayFlat* array = new ( ELeave ) CDesCArrayFlat( 4 );
    CleanupStack::PushL( array );
    
    array->AppendL( _L( "0\tLabel1\t0\t0" ) ); 
    array->AppendL(_L( "0\tLabel2\t0\t0" ) );
    
    CArrayFix<TInt> *selectedItems = new(ELeave) CArrayFixFlat<TInt>( 4 );
    CleanupStack::PushL( selectedItems );

	//IMPORT_C CAknMarkableListDialog(
    //		TInt &aValue, CArrayFix<TInt> *aSelectedItems, 
    //		MDesCArray *aArray, TInt aMenuBarResourceId, 
    //		TInt aOkMenuBarResourceId, 
    //		MEikCommandObserver *aObserver );
    CSubAknMarkableListDialog* dialog = new (ELeave) CSubAknMarkableListDialog(
    		value, selectedItems, array, 0, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( dialog );	
    AssertNotNullL( dialog, KCAknMarkableListDialog );
    
	CleanupStack::PopAndDestroy( dialog );
	CleanupStack::PopAndDestroy( selectedItems );
	CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( menuPane );
	CleanupStack::PopAndDestroy( ); // PrepareLC
    CleanupStack::Pop( markedDlg ); 
	CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( markedItems );	
	}
//------------------------------------------------------------------------------
// Test AknListBoxLayouts  AknListBoxLinesTemplate
//------------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestListBoxLayoutsL()
	{
    _LIT( KListBox1, "AknListBoxLayouts::SetupColumnGfxCell() invoked" );
	_LIT( KListBox2, "AknListBoxLayouts::SetupColumnTextCell() invoked" );
	_LIT( KListBox3, 
		"AknListBoxLayouts::SetupColumnTextCell() another invoked" );
	_LIT( KLBLineTemplate1, 
		"AknListBoxLinesTemplate::AknListBoxLinesTemplate() invoked" );
	_LIT( KLBLineTemplate2, 
		"AknListBoxLinesTemplate::ComponentControl() invoked" );
	_LIT( KLBLineTemplate3, 
		"AknListBoxLinesTemplate::AknListBoxLinesTemplate() invoked" );

	CEikColumnListBox* listBox = new( ELeave ) CEikColumnListBox();
	listBox->ConstructL( iContainer );
	TRect rect = iContainer->Rect();
    TSize size = listBox->MinimumSize();
    TPoint pt1( rect.iTl );
    TPoint pt2( rect.iTl.iX + size.iWidth, 
                rect.iTl.iY + size.iHeight );
	AknListBoxLayouts::SetupColumnGfxCell(*listBox, listBox->ItemDrawer() , 0,
			rect.iTl.iX, rect.iTl.iY, rect.iBr.iX, rect.iBr.iY, 
			size.iWidth, size.iHeight, 0 , 5);
    AssertTrueL( ETrue, KListBox1 );  
	AknListBoxLayouts::SetupColumnTextCell(*listBox, 
		listBox->ItemDrawer(), 0, iEikEnv->NormalFont(),
                0, rect.iTl.iX, rect.iTl.iY, rect.iBr.iY, size.iWidth,
                CGraphicsContext::ELeft, 0 , 5);
    AssertTrueL( ETrue, KListBox2 ); 
	
	TAknTextLineLayout textLine ;
	AknListBoxLayouts::SetupColumnTextCell(*listBox, listBox->ItemDrawer(), 0,
		textLine, 0 , 20);
    AssertTrueL( ETrue, KListBox3 );
	delete listBox;
	
	AknListBoxLinesTemplate<CAknColumnListBox>* listbox = 
    	new (ELeave) AknListBoxLinesTemplate<CAknColumnListBox>
    	( R_LIST_PANE_LINES_BC_COLUMN );
    CleanupStack::PushL( listbox );
	AssertTrueL( ETrue, KLBLineTemplate1 );
    listbox->ComponentControl( 0 );
	AssertTrueL( ETrue, KLBLineTemplate2 );
    CleanupStack::PopAndDestroy( listbox );
    
    AknListBoxLinesTemplate< CEikSettingsListBox >* settinglb = 
    	new (ELeave)AknListBoxLinesTemplate< CEikSettingsListBox >
    	( R_LIST_PANE_LINES_BC_COLUMN );
	AssertTrueL( ETrue, KLBLineTemplate3 );
    delete settinglb;
	}

//----------------------------------------------------------------------------
// Test CEikConsoleScreen 
//----------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestConsoleScreenL()
	{
	_LIT(KTitle, "Console Screen" );
	_LIT( KConsoleScreen1, "CEikConsoleScreen::CEikConsoleScreen() invoked" );
	_LIT( KConsoleScreen2, "CEikConsoleScreen::ConstructL() invoked" );
	_LIT( KConsoleScreen3, "CEikConsoleScreen::SetTitleL() invoked" );
	_LIT( KConsoleScreen4, "CEikConsoleScreen::SetConsWin() invoked" );
	_LIT( KConsoleControl1, "CEikScrollBar::CEikScrollBar() invoked" );
	_LIT( KConsoleControl2, "CEikConsoleControl::HandleScrollEventL() invoked" );
	
	CSubEikConsoleScreen * consoleScreen = new( ELeave ) CSubEikConsoleScreen();
    CleanupStack::PushL( consoleScreen );
    AssertTrueL( ETrue, KConsoleScreen1 );  
	
    consoleScreen->ConstructL( KTitle, 
        CEikConsoleScreen::ENoInitialCursor );
    AssertTrueL( ETrue, KConsoleScreen2 );  

	consoleScreen->SetTitleL( KTitle );
    AssertTrueL( ETrue, KConsoleScreen3 ); 
	CEikConsoleControl* eikConsoleControl = 
        new( ELeave ) CEikConsoleControl();
    CleanupStack::PushL( eikConsoleControl );
	
	 TPoint point( 0, 0 );
    TSize  ss( 20, 20 );
    eikConsoleControl->ConstructL( point, ss, 
        CEikConsoleScreen::EUseBackedUpWindow, EEikConsWinInPixels  );
	consoleScreen->SetConsWin( eikConsoleControl );
    AssertTrueL( ETrue, KConsoleScreen4 ); 
	
	CEikScrollBar* scrollBar = new( ELeave ) CEikScrollBar();
    CleanupStack::PushL( scrollBar );
    AssertTrueL( ETrue, KConsoleControl1 ); 
	
    scrollBar->ConstructL( eikConsoleControl, iContainer,
		CEikScrollBar::EVertical,iContainer->Rect().Size().iHeight );   
	eikConsoleControl->HandleScrollEventL( scrollBar, EEikScrollDown );
    AssertTrueL( ETrue, KConsoleControl2 ); 
	
    CleanupStack::PopAndDestroy( scrollBar );
	CleanupStack::Pop( eikConsoleControl );
	CleanupStack::PopAndDestroy( consoleScreen );
	}
// ---------------------------------------------------------------------------
// test CEikCapCArray
// ---------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::TestCapCArrayL()
	{
	_LIT( KCapCArray1, "CEikCapCArray::CEikCapCArray() invoked" );
	_LIT( KCapCArray2, "CEikCapCArray::DeleteLine() invoked" );
	
	CEikCapCArray* eikCapCArray = new (ELeave)CEikCapCArray( 3 ) ;
    AssertTrueL( ETrue, KCapCArray1 ); 
    CleanupStack::PushL( eikCapCArray );

	CEikCaptionedControl* coeControl = new( ELeave ) CEikCaptionedControl();
    CleanupStack::PushL( coeControl );
	eikCapCArray->AppendL(coeControl);
	eikCapCArray->DeleteLine( 0 );
    AssertTrueL( ETrue, KCapCArray2 );
	
	CleanupStack::Pop( coeControl ); 
	CleanupStack::PopAndDestroy( eikCapCArray ); 
	}

// ---------------------------------------------------------------------------
// CBCTestMix50ListColumnCase::ReleaseCase
// ---------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::ReleaseCase()
    {
    iContainer->ResetControl();    
    iListBox = NULL;
    }
    
// ---------------------------------------------------------------------------
// CBCTestMix50ListColumnCase::GraphicIconL
// ---------------------------------------------------------------------------
//
void CBCTestMix50ListColumnCase::GraphicIconL( CArrayPtr<CGulIcon>* /* aIcons */ )
    {
   
    }

// ---------------------------------------------------------------------------
// Test  CEikTextListBox WriteInternalStateL
// ---------------------------------------------------------------------------
//
void CSubEikTextListBox::TestWriteInternalStateL(RWriteStream& aWriteStream) 
	const
    {
	WriteInternalStateL( aWriteStream );
    }

// ---------------------------------------------------------------------------
// Test CEikTextListBox CreateItemDrawerL
// ---------------------------------------------------------------------------
//
void CSubEikTextListBox::TestCreateItemDrawerL()
	{
	CreateItemDrawerL();
	if(iItemDrawer)
	    delete iItemDrawer;
	}

// ---------------------------------------------------------------------------
// Test TListBoxModelItemArrayOwnership ItemArrayOwnershipType
// ---------------------------------------------------------------------------
//
TListBoxModelItemArrayOwnership CSubTextListBoxModel
	::TestItemArrayOwnershipType() const
	{
	return ItemArrayOwnershipType();
	}

// ---------------------------------------------------------------------------
// CSubTextListItemDrawer c++ constructor
// ---------------------------------------------------------------------------
//
CSubTextListItemDrawer::CSubTextListItemDrawer(
	MTextListBoxModel* aTextListBoxModel, const CFont* aFont)
	:CTextListItemDrawer( aTextListBoxModel, aFont )
	{
	
	}

// ---------------------------------------------------------------------------
// CSubEikListBoxTextEditor c++ constructor
// ---------------------------------------------------------------------------
//
CSubEikListBoxTextEditor::CSubEikListBoxTextEditor( MListBoxModel* aModel )
	: CEikListBoxTextEditor( aModel )
	{
	
	}

// ---------------------------------------------------------------------------
// Test AddActualFontL
// ---------------------------------------------------------------------------
//
TInt CSubListBoxData::AddActualFontL( const CFont* aBaseFont )
	{
	if (!iNormalFont.iFonts)
       {
       iNormalFont.iFonts=new ( ELeave ) CArrayPtrFlat<CFont> ( 1 );
       iBoldFont.iFonts=new ( ELeave ) CArrayPtrFlat<CFont> ( 1 );
       iItalicFont.iFonts=new ( ELeave ) CArrayPtrFlat<CFont> ( 1 );
       iBoldItalicFont.iFonts=new ( ELeave ) CArrayPtrFlat<CFont> ( 1 );
       }

    // Reserves extra space for each font array.
    TInt fontCount=iNormalFont.iFonts->Count()+1;
    iNormalFont.iFonts->SetReserveL( fontCount );
    iBoldFont.iFonts->SetReserveL( fontCount );
    iItalicFont.iFonts->SetReserveL( fontCount );
    iBoldItalicFont.iFonts->SetReserveL( fontCount );

    // Add Fonts.
    TFontStyle style=aBaseFont->FontSpecInTwips().iFontStyle;
    ConstructFontL( aBaseFont, style, iNormalFont );
    ConstructFontL( aBaseFont, style, iBoldFont );
    ConstructFontL( aBaseFont, style, iItalicFont );
    ConstructFontL( aBaseFont, style, iBoldItalicFont );
    return fontCount-1;
	}

// ---------------------------------------------------------------------------
// Test CFontWithStyle
// ---------------------------------------------------------------------------
//
TBool CSubListBoxData::TestCFontWithStyle()
    {
    TFontStyle style( EPostureItalic, EStrokeWeightBold, 
        EPrintPosSuperscript );    
    iNormalFont.SetFontStyle( style );
    TFontStyle fontStyle = iNormalFont.FontStyle();
    iNormalFont.ReleaseFonts();    
    return ( fontStyle == style );
    }
// ---------------------------------------------------------------------------
// CSubAknMarkableListDialog Symbian 2nd constructor
// ---------------------------------------------------------------------------
//
CSubAknMarkableListDialog* CSubAknMarkableListDialog::NewL( TInt &aValue, 
    CArrayFix<TInt> *aSelectedItems, MDesCArray *aArray )
    {
    CSubAknMarkableListDialog* self = new( ELeave ) CSubAknMarkableListDialog(
        aValue, aSelectedItems, aArray, 
        R_AVKON_DIALOG_EMPTY_MENUBAR, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( self );
    self->ConstructL( R_AVKON_DIALOG_EMPTY_MENUBAR );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CSubAknMarkableListDialog C++ constructor
// ---------------------------------------------------------------------------
//
CSubAknMarkableListDialog::CSubAknMarkableListDialog( 
    TInt &aValue, CArrayFix<TInt> *aSelectedItems, 
    MDesCArray *aArray, TInt aMenuBarResourceId, 
    TInt aOkMenuBarResourceId, MEikCommandObserver *aObserver ):
    CAknMarkableListDialog( aValue, aSelectedItems, aArray, aMenuBarResourceId,
        aOkMenuBarResourceId, aObserver )
    {    
    }
  

