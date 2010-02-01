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
* Description:         test case for list classes in eikstd
*
*/









#include <w32std.h>
#include <eikenv.h>
#include <aknlists.h>
#include <aknscontrolcontext.h>
#include <eikedwin.h>
#include <s32file.h>
#include <eiklbm.h>
#include <barsread.h>
#include <bamatch.h>

#include "bctestlisteiklistcase.h"
#include "bctestlistcontainer.h"
#include "bctestlist.hrh"
#include <bctestlist.rsg>

_LIT( KStreamName, "c:\\BCTestLog\\test.txt" );
_LIT( KEikTestText, "Test text" );

_LIT( KListBoxDataCreate, "Create CListBoxData" );
_LIT( KTextItemDrawerCreate, "Create CTextListItemDrawer" );
_LIT( KTextListCreate, "Create CEikTextListBox" );
_LIT( KSnakingListCreate, "Create CEikSnakingTextListBox" );

_LIT( KListDataTest1, "CListBoxData::SkinBackgroundControlContext" );
_LIT( KListDataTest2, "CListBoxData::FontBoundValues" );
_LIT( KListDataTest3, "CListBoxData::SetFontHeight" );
_LIT( KListDataTest4, "CListBoxData::ConstructFontL" );
_LIT( KListDataTest5, "CListBoxData::RegenerateFontsL" );
_LIT( KListDataTest6, "CListBoxData::UpdateFontBoundValues" );
_LIT( KListDataTest7, "CListBoxData::CFontsWithStyle::SetFontStyle" );
_LIT( KListDataTest8, "CListBoxData::CFontsWithStyle::FontStyle" );
_LIT( KListDataTest9, "CListBoxData::SetSearchStringL" );
_LIT( KListDataTest10, "CListBoxData::IsSearchString" );
_LIT( KListDataTest11, "CListBoxData::DrawItem" );
_LIT( KEikSearchString, "abc" );

_LIT( KTestListModelTest1, "CTextListBoxModel::TestItemArrayOwnershipType" );

_LIT( KListBoxEditorTest1, "CEikListBoxEditor::SetFont" );
_LIT( KListBoxEditorTest2, "CEikListBoxEditor::StartEditingL" );
_LIT( KListBoxEditorTest3, "CEikListBoxEditor::SetListBoxEditorObserver" );
_LIT( KListBoxEditorTest4, "CEikListBoxEditor::OfferKeyEventL" );
_LIT( KListBoxEditorTest5, "CEikListBoxEditor::ItemText" );
_LIT( KListBoxEditorTest6, "CEikListBoxEditor::WriteInternalStateL" );
_LIT( KListBoxEditorTest7, "CEikListBoxEditor::UpdateModelL" );

_LIT( KListItemDrawerTest1, "CListItemDrawer::MatcherCursorRect" );
_LIT( KListItemDrawerTest2, "CListItemDrawer::MatcherCursorAscent" );
_LIT( KListItemDrawerTest3, "CListItemDrawer::SetSkinEnabledL" );
_LIT( KListItemDrawerTest4, "CListItemDrawer::SkinBackgroundControlContext" );
_LIT( KListItemDrawerTest5, "CListItemDrawer::SetSkinEnabledL" );
_LIT( KListItemDrawerTest6, "CListItemDrawer::SetFont" );
_LIT( KListItemDrawerTest7, "CListItemDrawer::Font" );
_LIT( KListItemDrawerTest8, "CTextListItemDrawer::Font" );
_LIT( KListItemDrawerTest9, "CListItemDrawer::SetMarkColumnWidth" );
_LIT( KListItemDrawerTest10, "CListItemDrawer::SetMarkGutter" );
_LIT( KListItemDrawerTest11, "CListItemDrawer::MarkGutter" );
_LIT( KListItemDrawerTest12, "CListItemDrawer::MarkColumn" );
_LIT( KListItemDrawerTest13, "CListItemDrawer::DrawItemMark" );
_LIT( KListItemDrawerTest14, "CListItemDrawer::MinimumCellSize" );
_LIT( KListItemDrawerTest15, "CListItemDrawer::ItemWidthInPixels" );
_LIT( KListItemDrawerTest16, "CListItemDrawer::SetSymbolFont" );
_LIT( KListItemDrawerTest17, "CTextListItemDrawer::MatcherCursorRect" );
_LIT( KListItemDrawerTest18, "CTextListItemDrawer::MatcherCursorAscent" );
_LIT( KListItemDrawerTest19, "CTextListItemDrawer::SetSearchStringL" );
_LIT( KListItemDrawerTest20, "CTextListItemDrawer::DrawItemText" );

_LIT( KListViewTest1, "CListBoxView::ToggleItemL" );
_LIT( KListViewTest2, "CListBoxView::SetAnchor" );
_LIT( KListViewTest3, "CListBoxView::DeselectRangeL" );
_LIT( KListViewTest4, "CListBoxView::ScrollToMakeItemVisible" );
_LIT( KListViewTest5, "CListBoxView::SetPaintedSelection" );
_LIT( KListViewTest6, "CListBoxView::SetTextColor" );
_LIT( KListViewTest7, "CListBoxView::TextColor" );
_LIT( KListViewTest8, "CListBoxView::DrawEmptyList" );
_LIT( KListViewTest9, "CListBoxView::SetSelectionIndexesL" );
_LIT( KListViewTest10, "CListBoxView::GetSelectionIndexesL" );

_LIT( KTextItemDrawerMatchText, "Add Items" );   

_LIT( KTextListTest1, "CEikListBox::SetScrollBarFrame" );
_LIT( KTextListTest2, "CEikListBox::ConstructL" );
_LIT( KTextListTest3, "CEikListBox::Reset" );
_LIT( KTextListTest4, "CEikListBox::CreateMatchBufferL" );
_LIT( KTextListTest5, "CEikListBox::MatchBuffer" );
_LIT( KTextListTest6, "CEikListBox::ClearMatchBuffer" );
_LIT( KTextListTest7, "CEikListBox::CalcWidthBasedOnNumOfChars" );
_LIT( KTextListTest8, "CEikListBox::CalcWidthBasedOnRequiredItemWidth" );
_LIT( KTextListTest9, "CEikListBox::CalcHeightBasedOnNumOfItems" );
_LIT( KTextListTest10, "CEikListBox::MinimumSize" );
_LIT( KTextListTest11, "CEikListBox::CalcSizeInPixels" );
_LIT( KTextListTest12, "CEikListBox::SetViewRectFromClientRect" );
_LIT( KTextListTest13, "CEikListBox::CalculatePopoutRect" );
_LIT( KTextListTest14, "CEikListBox::BottomItemIndex" );
_LIT( KTextListTest15, "CEikListBox::SetTopItemIndex" );
_LIT( KTextListTest16, "CEikListBox::AdjustTopItemIndex" );
_LIT( KTextListTest17, "CEikListBox::SetCurrentItemIndexAndDraw" );
_LIT( KTextListTest18, "CEikListBox::SetListBoxObserver" );
_LIT( KTextListTest19, "CEikListBox::MakeViewClassInstanceL" );
_LIT( KTextListTest20, "CEikListBox::DrawMatcherCursor" );
_LIT( KTextListTest21, "CEikListBox::InterItemGap" );
_LIT( KTextListTest22, "CEikListBox::CreateScrollBarFrameLayout" );
_LIT( KTextListTest23, "CEikListBox::HorizScrollGranularityInPixels" );
_LIT( KTextListTest24, "CEikListBox::SetViewRectHeightAdjustment" );
_LIT( KTextListTest25, "CEikListBox::VerticalInterItemGap" );
_LIT( KTextListTest26, "CEikListBox::SetSelectionIndexesL" );
_LIT( KTextListTest27, "CEikListBox::SelectionIndexes" );
_LIT( KTextListTest28, "CEikListBox::IsMultiselection" );
_LIT( KTextListTest29, "CEikListBox::ClearSelection" );
_LIT( KTextListTest30, "CEikListBox::HandleLeftArrowKeyL" );
_LIT( KTextListTest31, "CEikListBox::HandleRightArrowKeyL" );
_LIT( KTextListTest32, "CEikListBox::OfferKeyEventL" );
_LIT( KTextListTest33, "CEikListBox::HorizontalNudgeValue" );
_LIT( KTextListTest34, "CEikListBox::HandleScrollEventL" );
_LIT( KTextListTest35, "CEikListBox::HandleDragEventL" );
_LIT( KTextListTest36, "CEikListBox::SimulateArrowKeyEventL" );
_LIT( KTextListTest37, "CEikListBox::SetDimmed" );
_LIT( KTextListTest38, "CEikListBox::UndoLastChar" );
_LIT( KTextListTest39, "CEikListBox::SetShortcutValueFromPrevList" );
_LIT( KTextListTest40, "CEikListBox::ShortcutValueForNextList" );
_LIT( KTextListTest41, "CEikListBox::HighlightRect" );
_LIT( KTextListTest42, "CEikListBox::MatchTypedCharL" );
_LIT( KTextListTest43, "CEikListBox::LastCharMatched" );
_LIT( KTextListTest44, "CEikListBox::SetLaunchingButton" );
_LIT( KTextListTest45, "CEikListBox::EventModifiers" );
_LIT( KTextListTest46, "CEikListBox::ReasonForFocusLostL" );
_LIT( KTextListTest47, "CEikListBox::EditItemL" );
_LIT( KTextListTest48, "CEikListBox::StopEditingL" );
_LIT( KTextListTest49, "CEikListBox::HandleItemAdditionL" );
_LIT( KTextListTest50, "CEikListBox::HandleItemRemovalL" );
_LIT( KTextListTest51, "CEikListBox::HandleItemRemovalL()" );
_LIT( KTextListTest52, "CEikTextListBox::Model" );
_LIT( KTextListTest53, "CEikTextListBox::WriteInternalStateL" );
_LIT( KTextListTest54, "CEikTextListBox::ConstructFromResourceL" );
_LIT( KEikAddItem, "One added text" );

_LIT( KSnakingViewTest1, "CSnakingListBoxView::VisibleWidth" );
_LIT( KSnakingViewTest2, "CSnakingListBoxView::HScroll" );
_LIT( KSnakingViewTest3, "CSnakingListBoxView::SetItemHeight" );
_LIT( KSnakingViewTest4, "CSnakingListBoxView::CalculateHScrollOffsetSoItemIsVisible" );

_LIT( KSnakingTest1, "CEikSnakingListBox::MakeViewClassInstanceL" );
_LIT( KSnakingTest2, "CEikSnakingListBox::SetColumnWidth" );
_LIT( KSnakingTest3, "CEikSnakingListBox::ColumnWidth" );
_LIT( KSnakingTest4, "CEikSnakingListBox::HandleLeftArrowKeyL" );
_LIT( KSnakingTest5, "CEikSnakingListBox::HandleRightArrowKeyL" );
_LIT( KSnakingTest6, "CEikSnakingListBox::HorizontalNudgeValue" );
_LIT( KSnakingTest7, "CEikSnakingListBox::HorizScrollGranularityInPixels" );
_LIT( KSnakingTest8, "CEikSnakingListBox::SetTopItemIndex" );
_LIT( KSnakingTest9, "CEikSnakingListBox::AdjustTopItemIndex" );
_LIT( KSnakingTest10, "CEikSnakingListBox::SizeChanged" );
_LIT( KSnakingTest11, "CEikSnakingListBox::HandleDragEventL" );
_LIT( KSnakingTest12, "CEikSnakingListBox::HandleViewRectSizeChangeL" );
_LIT( KSnakingTest13, "CEikSnakingListBox::MoveToNextOrPreviousItemL" );
_LIT( KSnakingTest14, "CEikSnakingListBox::RestoreClientRectFromViewRect" );
_LIT( KSnakingTest15, "CEikSnakingListBox::AdjustRectHeightToWholeNumberOfItems" );
_LIT( KSnakingTest16, "CEikSnakingListBox::GetColorUseListL" );
_LIT( KSnakingTest17, "CEikSnakingTextListBox::GetColorUseListL" );
_LIT( KSnakingTest18, "CEikSnakingListBox::HandlePointerEventL" );
_LIT( KSnakingTest19, "CEikSnakingTextListBox::HandlePointerEventL" );
_LIT( KSnakingTest20, "CEikSnakingListBox::HandleResourceChange" );
_LIT( KSnakingTest21, "CEikSnakingTextListBox::HandleResourceChange" );
_LIT( KSnakingTest22, "CEikSnakingTextListBox::Model" );


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestListEiklistCase* CBCTestListEiklistCase::NewL( 
    CBCTestListContainer* aContainer, CEikonEnv* aEikEnv )
    {
    CBCTestListEiklistCase* self = new( ELeave ) CBCTestListEiklistCase( 
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
CBCTestListEiklistCase::CBCTestListEiklistCase( CBCTestListContainer* aContainer,
    CEikonEnv* aEikEnv )
    : CBCTestListBaseCase( aContainer, aEikEnv )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestListEiklistCase::~CBCTestListEiklistCase()
    {
    ReleaseCase(); 
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestListEiklistCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListEiklistCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestListEiklistCase::BuildScriptL()
    {    
    for ( TInt i=0; i <= EBCTestCmdOutline55 - EBCTestCmdOutline51; i++ )
        {
        AddTestL( LeftCBA, REP( Down, 8 ), KeyOK, TEND );
        AddTestL( REP( Down, i ), KeyOK, TEND );
        }      
    }
    
// ---------------------------------------------------------------------------
// CBCTestListEiklistCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestListEiklistCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline51 || aCmd > EBCTestCmdOutline55 )
        {
        return;
        }
    iCurrentCmd = aCmd;
    ReleaseCase();
    PrepareCaseL( aCmd );
    switch( aCmd )
        {
        case EBCTestCmdOutline51:
            TestListBoxDataL();
            break;
        case EBCTestCmdOutline52:
            TestCEikListBoxEditorL();
            break;
        case EBCTestCmdOutline53:
            TestCTextListItemDrawerL();
            break;
        case EBCTestCmdOutline54:
            TestEikListBoxL();
            TestListBoxViewL();
            break;
        case EBCTestCmdOutline55:
            TestSnakingListBoxL();
            TestSnakingListBoxViewL();
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestListEiklistCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestListEiklistCase::PrepareCaseL( TInt aCmd )
    {    
    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;  
    CDesCArray* textArray = NULL;
    
    if ( aCmd != EBCTestCmdOutline51 )
        {
        textArray = iEikEnv->ReadDesCArrayResourceL( 
                R_BCTESTLIST_ITEM_SINGLE1_ADD_RM );
        CleanupStack::PushL( textArray );
        }
        
    if ( aCmd == EBCTestCmdOutline52 || aCmd == EBCTestCmdOutline53 )
        {
        iModel = new( ELeave ) CBCTestTextListModel();            
        iModel->ConstructL( textArray );
        }

    switch ( aCmd )
        {
        case EBCTestCmdOutline51:
            iData = new( ELeave ) CBCTestListBoxData();
            AssertNotNullL( iData, KListBoxDataCreate );
            iData->ConstructL( iEikEnv->NormalFont() );            
            break;
        case EBCTestCmdOutline53:
            iTextDrawer = new( ELeave ) CBCTestTextListItemDrawer( iModel, 
                iEikEnv->NormalFont() );
            AssertNotNullL( iTextDrawer, KTextItemDrawerCreate );
            break;
        case EBCTestCmdOutline54:
            {
            iListBox = new( ELeave ) CBCTestTextListBox();
            AssertNotNullL( iListBox, KTextListCreate );
            iListBox->ConstructL( iContainer, flags );
            iListBox->Model()->SetItemTextArray( textArray );
            iListBox->Model()->SetOwnershipType( ELbmOwnsItemArray );
            
            CEikScrollBarFrame* scrollBarFrame = new( ELeave) CEikScrollBarFrame(
                iContainer, iListBox, ETrue );
            CleanupStack::PushL( scrollBarFrame );
            iListBox->SetScrollBarFrame( scrollBarFrame, 
                CEikListBox::ENotOwnedExternally );                
            AssertTrueL( ETrue, KTextListTest1 );
            CleanupStack::Pop( scrollBarFrame );
            
            iContainer->SetControl( iListBox );
            }
            break;
        case EBCTestCmdOutline55:
            iSnakingList = new( ELeave ) CBCTestTextSnakingListBox();
            AssertNotNullL( iSnakingList, KSnakingListCreate );
            flags |= CEikListBox::ELeftDownInViewRect;
            iSnakingList->ConstructL( iContainer, flags );
            iSnakingList->Model()->SetItemTextArray( textArray );
            iSnakingList->Model()->SetOwnershipType( ELbmOwnsItemArray );           
            
            iContainer->SetControl( iSnakingList );
        default:
            break;
        }
        
    if ( aCmd != EBCTestCmdOutline51 )
        {
        CleanupStack::Pop( textArray );
        }
    }

// ---------------------------------------------------------------------------
// CBCTestListEiklistCase::ReleaseCase
// ---------------------------------------------------------------------------
//   
void CBCTestListEiklistCase::ReleaseCase()
    {
    iContainer->ResetControl();    
    iListBox = NULL;
    iSnakingList = NULL;  
    
    delete iModel;
    delete iData;    
    delete iTextDrawer;    
    
    iModel = NULL; 
    iData = NULL;
    iTextDrawer = NULL;    
    }
    
// ---------------------------------------------------------------------------
// Test CListBoxData
// ---------------------------------------------------------------------------
//
void CBCTestListEiklistCase::TestListBoxDataL()
    {   
    MAknsControlContext* controlCtx = iData->SkinBackgroundControlContext();
    AssertTrueL( ETrue, KListDataTest1 );    
    
    const TListFontBoundValues& boundValue = iData->FontBoundValues();
    AssertTrueL( ETrue, KListDataTest2 );
    
    TInt fontHeightInTwips = 10;
    TInt height = iData->SetFontHeight( fontHeightInTwips );    
    AssertTrueL( ETrue, KListDataTest3 );
    
    // Test protected API
    iData->TestConstructFontL( iEikEnv->TitleFont() );
    AssertTrueL( ETrue, KListDataTest4 );
    TInt testRet = iData->TestRegenerateFonts();
    AssertTrueL( ETrue, KListDataTest5 );
    iData->TestUpdateFontBoundValues( iEikEnv->NormalFont() );
    AssertTrueL( ETrue, KListDataTest6 );
    TBool ret = iData->TestCFontWithStyle();
    AssertTrueL( ret, KListDataTest7 );
    AssertTrueL( ret, KListDataTest8 );
    
    
    TPtrC ptr( KEikSearchString ); 
    iData->SetSearchStringL( &ptr );
    AssertTrueL( ETrue, KListDataTest9 );    
    TBool search = iData->IsSearchString();
    AssertTrueL( ETrue, KListDataTest10 );
    
    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    const TInt KRectHeight = 30;
    TRect rect = iContainer->Rect();
    rect.iBr.iY = rect.iTl.iY + KRectHeight;            
    const CFont& font = *iEikEnv->NormalFont();
    gc.UseFont(&font);
    iData->DrawItem( gc, rect, KEikTestText, font, 0 );
    AssertTrueL( ETrue, KListDataTest11 );    
    iContainer->DeactivateGc();
    }
    
// ---------------------------------------------------------------------------
// Test CEikListBoxEditor
// ---------------------------------------------------------------------------
//
void CBCTestListEiklistCase::TestCEikListBoxEditorL()
    {
    // test CTextListBoxModel
    const MDesCArray* array = iModel->MatchableTextArray();
    TListBoxModelItemArrayOwnership type = 
        iModel->TestItemArrayOwnershipType();
    AssertIntL( ELbmOwnsItemArray, type, KTestListModelTest1 );

    // test CBCTestListBoxEditor
    CBCTestListBoxEditor* editor = new( ELeave ) CBCTestListBoxEditor(
        iModel, iEikEnv );
    CleanupStack::PushL( editor );
    editor->SetFont( iEikEnv->NormalFont() );
    AssertTrueL( ETrue, KListBoxEditorTest1 );
    
    TRect rect = iContainer->Rect();
    rect.iBr.iY = rect.iTl.iY + rect.Size().iHeight / 2;
    editor->StartEditingL( *iContainer, rect, 0, 30 );
    AssertTrueL( ETrue, KListBoxEditorTest2 );
    
    TBCTestListBoxEditorObserver observer;
    editor->SetListBoxEditorObserver( &observer );
    AssertTrueL( ETrue, KListBoxEditorTest3 );
    
    TKeyEvent eventEnter = { EKeyEnter, EKeyEnter, 0, 0 };
    TKeyEvent eventShift = { '1', '1', EModifierCtrl | EModifierShift, 0 };
    TKeyEvent eventT = { 'T', 'T', 0, 0 };
    TKeyEvent evente = { 'e', 'e', 0, 0 };
    TKeyEvent events = { 's', 's', 0, 0 };
    TKeyEvent eventt = { 't', 't', 0, 0 };
    
    editor->OfferKeyEventL( eventEnter, EEventKey );
    editor->SetListBoxEditorObserver( NULL );
    
    editor->OfferKeyEventL( eventT, EEventKey );
    editor->OfferKeyEventL( evente, EEventKey );
    editor->OfferKeyEventL( events, EEventKey );
    editor->OfferKeyEventL( eventt, EEventKey );    
    editor->OfferKeyEventL( eventShift, EEventKey );    
    AssertTrueL( ETrue, KListBoxEditorTest4 );
    
    TPtrC text = editor->ItemText();
    AssertTrueL( ETrue, KListBoxEditorTest5 );
    
    editor->TestWriteInternalStateL();
    AssertTrueL( ETrue, KListBoxEditorTest6 );
    
    editor->OfferKeyEventL( eventEnter, EEventKey );
    AssertTrueL( ETrue, KListBoxEditorTest7 );
        
    CleanupStack::PopAndDestroy( editor );
    }
    
// ---------------------------------------------------------------------------
// Test CTextListItemDrawer
// ---------------------------------------------------------------------------
//
void CBCTestListEiklistCase::TestCTextListItemDrawerL()
    {
    CTextListItemDrawer* textDrawer = new( ELeave ) CTextListItemDrawer();
    CleanupStack::PushL( textDrawer );
    _LIT( KTestItemDrawer1, 
        "CTextListItemDrawer::CTextListItemDrawer without parameter" );
    AssertNotNullL( textDrawer, KTestItemDrawer1 );
    
    textDrawer->ConstructL( iEikEnv->NormalFont() );
    _LIT( KTestItemDrawer2, "CTextListItemDrawer::ConstructL" );
    AssertNotNullL( textDrawer, KTestItemDrawer2 );
    CleanupStack::PopAndDestroy( textDrawer );
    
    // test CListItemDrawer        
    TRect cursorRect = iTextDrawer->CListItemDrawer::MatcherCursorRect(
        KTextItemDrawerMatchText, 0, 0, 0 );
    AssertTrueL( ETrue, KListItemDrawerTest1 );
       
    TInt cursorAscent = iTextDrawer->CListItemDrawer::
        MatcherCursorAscent( 0 );
    AssertTrueL( ETrue, KListItemDrawerTest2 );
    
    iTextDrawer->SetSkinEnabledL( ETrue );
    AssertTrueL( ETrue, KListItemDrawerTest3 );
    
    MAknsControlContext* context = 
        iTextDrawer->SkinBackgroundControlContext();
    AssertTrueL( ETrue, KListItemDrawerTest4 );
    
    iTextDrawer->SetSkinEnabledL( EFalse );
    AssertTrueL( ETrue, KListItemDrawerTest5 );
    
    iTextDrawer->SetFont( iEikEnv->TitleFont() );
    AssertTrueL( ETrue, KListItemDrawerTest6 );
    
    const CFont* font = iTextDrawer->CListItemDrawer::Font( 0 );
    AssertTrueL( ETrue, KListItemDrawerTest7 );
    
    const CFont* textFont = iTextDrawer->Font( 0 );
    AssertTrueL( ETrue, KListItemDrawerTest8 );
    
    iTextDrawer->SetMarkColumnWidth( 50 );
    AssertTrueL( ETrue, KListItemDrawerTest9 );
    
    iTextDrawer->SetMarkGutter( 20 );
    AssertTrueL( ETrue, KListItemDrawerTest10 );
    
    TInt markGutter = iTextDrawer->MarkGutter();
    AssertTrueL( ETrue, KListItemDrawerTest11 );
    
    TInt markColumn = iTextDrawer->MarkColumn();
    AssertTrueL( ETrue, KListItemDrawerTest12 );
    
    iTextDrawer->DrawItemMark( ETrue, EFalse, TPoint( 0, 0 ) );    
    AssertTrueL( ETrue, KListItemDrawerTest13 );
    
    TRect rect = iContainer->Rect();
    TSize size = iTextDrawer->CListItemDrawer::MinimumCellSize();
    AssertTrueL( ETrue, KListItemDrawerTest14 );
    
    size = iTextDrawer->ItemCellSize();
    rect.iBr.iY = rect.iTl.iY + size.iHeight;
    rect.iBr.iX = rect.iTl.iX + size.iWidth;
    iTextDrawer->ClearRect( rect );
    TInt itemWidthInPixel = iTextDrawer->ItemWidthInPixels( 0 );
    AssertTrueL( ETrue, KListItemDrawerTest15 );
    
    iTextDrawer->SetSymbolFont( iEikEnv->NormalFont() );
    AssertTrueL( ETrue, KListItemDrawerTest16 );
    
    // test CTextListItemDrawer
    cursorRect = iTextDrawer->MatcherCursorRect( KTextItemDrawerMatchText, 0, 0, 0 );
    AssertTrueL( ETrue, KListItemDrawerTest17 );
    
    cursorAscent = iTextDrawer->MatcherCursorAscent( 0 );
    AssertTrueL( ETrue, KListItemDrawerTest18 );
    
    TPtrC ptr( KTextItemDrawerMatchText );    
    iTextDrawer->SetSearchStringL( &ptr );
    AssertTrueL( ETrue, KListItemDrawerTest19 );
    
    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    iTextDrawer->TestDrawItemText( gc );
    AssertTrueL( ETrue, KListItemDrawerTest20 );    
    iContainer->DeactivateGc();
    }
    
// ---------------------------------------------------------------------------
// Test CListBoxView
// ---------------------------------------------------------------------------
//
void CBCTestListEiklistCase::TestListBoxViewL()
    {
    CListBoxView* view = iListBox->View();
    view->ToggleItemL( 0 );
    AssertTrueL( ETrue, KListViewTest1 );
    
    view->SetAnchor( 8 );
    AssertTrueL( ETrue, KListViewTest2 );
    
    view->DeselectRangeL( 0, 4 );
    AssertTrueL( ETrue, KListViewTest3 );
    
    TBool visible = view->ScrollToMakeItemVisible( 8 );
    AssertTrueL( ETrue, KListViewTest4 );
    
    view->SetPaintedSelection( ETrue );
    AssertTrueL( ETrue, KListViewTest5 );
    
    view->SetTextColor( KRgbBlack );
    AssertTrueL( ETrue, KListViewTest6 );
    
    TRgb rgb = view->TextColor();    
    AssertTrueL( rgb == KRgbBlack, KListViewTest7 );
    
    view->DrawEmptyList( iContainer->Rect() );
    AssertTrueL( ETrue, KListViewTest8 );
    
    TInt topIndex = view->CalcNewTopItemIndexSoItemIsVisible( 8 );
    _LIT( KListViewTest11, 
        "CListBoxView::CalcNewTopItemIndexSoItemIsVisible" );
    AssertTrueL( ETrue, KListViewTest11 );
    
    CArrayFixFlat<TInt>* selectionArray = new( ELeave ) 
        CArrayFixFlat<TInt>( 5 );
    CleanupStack::PushL( selectionArray );
    selectionArray->AppendL( 0 );
    selectionArray->AppendL( 1 );
    selectionArray->AppendL( 2 );
    view->SetSelectionIndexesL( selectionArray );
    AssertTrueL( ETrue, KListViewTest9 );
    
    selectionArray->Reset();    
    view->GetSelectionIndexesL( selectionArray );
    AssertTrueL( ( selectionArray->Length() == 4 && 
        selectionArray->At(0) == 0), 
        KListViewTest10 );
    
    CleanupStack::PopAndDestroy( selectionArray );
    }
    
// ---------------------------------------------------------------------------
// Test CEikListBox
// ---------------------------------------------------------------------------
//
void CBCTestListEiklistCase::TestEikListBoxL()
    {
    // test constructL of CEikListBox
    CDesCArray* textArray = iEikEnv->ReadDesCArrayResourceL( 
        R_BCTESTLIST_ITEM_SINGLE1 );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer = new( ELeave ) CTextListItemDrawer();
    CleanupStack::PushL( drawer );
    drawer->ConstructL( iEikEnv->NormalFont() );
    
    CEikListBox* listBox = new( ELeave ) CEikListBox();
    CleanupStack::PushL( listBox );    
    TGulBorder border( TGulBorder::ESingleGray );
    listBox->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );    

    CleanupStack::PopAndDestroy( listBox );
    CleanupStack::Pop( drawer );
    CleanupStack::Pop( model );
    CleanupStack::Pop( textArray );
    AssertTrueL( ETrue, KTextListTest2 );

    // test CEikListBox
    TRect rect = iContainer->Rect();
    iListBox->Reset();
    AssertTrueL( ETrue, KTextListTest3 );
    iListBox->CreateMatchBufferL();
    AssertTrueL( ETrue, KTextListTest4 );
    RIncrMatcherBase* baMatch = iListBox->MatchBuffer();
    AssertTrueL( ETrue, KTextListTest5 );
    iListBox->ClearMatchBuffer();
    AssertTrueL( ETrue, KTextListTest6 );
    iListBox->CalcWidthBasedOnNumOfChars( 5 );
    AssertTrueL( ETrue, KTextListTest7 );
    iListBox->CalcWidthBasedOnRequiredItemWidth( 30 );
    AssertTrueL( ETrue, KTextListTest8 );
    iListBox->CalcHeightBasedOnNumOfItems( 2 );
    AssertTrueL( ETrue, KTextListTest9 );
    TSize size = iListBox->MinimumSize();
    AssertTrueL( ETrue, KTextListTest10 );
    iListBox->CalcSizeInPixels( 5, 2 );
    AssertTrueL( ETrue, KTextListTest11 );
    iListBox->SetViewRectFromClientRect( rect );
    AssertTrueL( ETrue, KTextListTest12 );   
    iListBox->CalculatePopoutRect( 0, 0, rect );
    AssertTrueL( ETrue, KTextListTest13 );
    TInt bottomIndex = iListBox->BottomItemIndex();
    AssertTrueL( ETrue, KTextListTest14 );
    iListBox->SetTopItemIndex( 1 );
    AssertTrueL( ETrue, KTextListTest15 );
    iListBox->AdjustTopItemIndex();
    AssertTrueL( ETrue, KTextListTest16 );
    iListBox->SetCurrentItemIndexAndDraw( 0 );
    AssertTrueL( ETrue, KTextListTest17 );
    TBCTestListBoxObserver observer;
    iListBox->SetListBoxObserver( &observer );
    AssertTrueL( ETrue, KTextListTest18 );
    CListBoxView* view = iListBox->MakeViewClassInstanceL();
    delete view;
    AssertTrueL( ETrue, KTextListTest19 );
    iListBox->DrawMatcherCursor();
    AssertTrueL( ETrue, KTextListTest20 );
    TInt interItemGap = iListBox->InterItemGap();
    AssertTrueL( ETrue, KTextListTest21 );
    TEikScrollBarFrameLayout frameLayout;
    iListBox->CreateScrollBarFrameLayout( frameLayout );
    AssertTrueL( ETrue, KTextListTest22 );
    TInt scrollGraInPixels = iListBox->HorizScrollGranularityInPixels();
    AssertTrueL( ETrue, KTextListTest23 );
    iListBox->SetViewRectHeightAdjustment( 5 );
    AssertTrueL( ETrue, KTextListTest24 );
    TInt verticalInterItemGap = iListBox->VerticalInterItemGap();
    AssertTrueL( ETrue, KTextListTest25 );
    iListBox->ScrollToMakeItemVisible( 5 );
    
    CArrayFixFlat<TInt>* selectionArray = new( ELeave ) 
        CArrayFixFlat<TInt>( 4 );
    CleanupStack::PushL( selectionArray );
    selectionArray->AppendL( 0 );
    selectionArray->AppendL( 1 );
    selectionArray->AppendL( 3 );
    iListBox->SetSelectionIndexesL( selectionArray );
    AssertTrueL( ETrue, KTextListTest26 );
    const CArrayFix<TInt>* getSelectionArray = iListBox->SelectionIndexes();
    AssertTrueL( 
        ( selectionArray->Length() == getSelectionArray->Length() )
        && ( selectionArray->At( 0 ) == getSelectionArray->At( 0 ) ), 
        KTextListTest27 );
    TBool multiselection = iListBox->IsMultiselection();
    AssertTrueL( !multiselection, KTextListTest28 );
    CleanupStack::PopAndDestroy( selectionArray );
    iListBox->ClearSelection();
    AssertTrueL( ETrue, KTextListTest29 );
    iListBox->HandleLeftArrowKeyL( CListBoxView::ESingleSelection );
    AssertTrueL( ETrue, KTextListTest30 );
    iListBox->HandleRightArrowKeyL( CListBoxView::ENoSelection );
    AssertTrueL( ETrue, KTextListTest31 );
    TKeyEvent eventT = { 'T', 'T', 0, 0 };
    iListBox->OfferKeyEventL( eventT, EEventKey );
    AssertTrueL( ETrue, KTextListTest32 );
    TInt horizontalNudge = iListBox->HorizontalNudgeValue();
    AssertTrueL( ETrue, KTextListTest33 );
    CEikScrollBar* scrollBar = new( ELeave ) CEikScrollBar();
    CleanupStack::PushL( scrollBar );
    scrollBar->ConstructL( iListBox, iContainer, CEikScrollBar::EVertical,
        iContainer->Rect().Size().iHeight );    
    iListBox->HandleScrollEventL( scrollBar, EEikScrollDown );
    AssertTrueL( ETrue, KTextListTest34 );
    CleanupStack::PopAndDestroy( scrollBar );
    iListBox->HandleDragEventL( TPoint( 0, 0 ) );
    AssertTrueL( ETrue, KTextListTest35 );
    iListBox->SimulateArrowKeyEventL( EKeyDownArrow );
    AssertTrueL( ETrue, KTextListTest36 );
    iListBox->SetDimmed( ETrue );    
    iListBox->SetDimmed( EFalse );
    AssertTrueL( ETrue, KTextListTest37 );
    iListBox->UndoLastChar();
    AssertTrueL( ETrue, KTextListTest38 );
    
    iListBox->SetShortcutValueFromPrevList( 1 );
    AssertTrueL( ETrue, KTextListTest39 );
    TInt shortcutValue = iListBox->ShortcutValueForNextList();
    AssertTrueL( ETrue, KTextListTest40 );
    TRect hightlightRect = iListBox->HighlightRect();
    AssertTrueL( ETrue, KTextListTest41 );
    iListBox->MatchTypedCharL( 'm' );
    AssertTrueL( ETrue, KTextListTest42 );
    TBool lastCharMatched = iListBox->LastCharMatched();
    AssertTrueL( ETrue, KTextListTest43 );
    iListBox->SetLaunchingButton( NULL );
    AssertTrueL( ETrue, KTextListTest44 );
    
    TInt eventModified = iListBox->EventModifiers();
    AssertTrueL( ETrue, KTextListTest45 );
    CEikListBox::TReasonForFocusLost reason = 
        iListBox->ReasonForFocusLostL();
    AssertTrueL( ETrue, KTextListTest46 );
    iListBox->EditItemL( 40 );
    AssertTrueL( ETrue, KTextListTest47 );
    iListBox->StopEditingL( EFalse );
    AssertTrueL( ETrue, KTextListTest48 );
    
    CArrayFixFlat<TInt>* indexArray = new( ELeave ) CArrayFixFlat<TInt>( 4 );
    CleanupStack::PushL( indexArray );
    indexArray->AppendL( 9 );
    indexArray->AppendL( 10 );    
    CDesCArray* array = static_cast<CDesCArray*>( 
        iListBox->Model()->ItemTextArray() );
    array->AppendL( KEikAddItem );
    array->AppendL( KEikAddItem );    
    iListBox->HandleItemAdditionL( *indexArray );
    AssertTrueL( ETrue, KTextListTest49 );
    iListBox->HandleItemRemovalL( *indexArray );
    AssertTrueL( ETrue, KTextListTest50 );
    iListBox->HandleItemRemovalL();
    AssertTrueL( ETrue, KTextListTest51 );
    CleanupStack::PopAndDestroy( indexArray );
    
    // test CEikTextListBox
    CTextListBoxModel* textModel = iListBox->Model();
    AssertTrueL( ETrue, KTextListTest52 );
    
    RFs& tempServer = iEikEnv->FsSession();    
    tempServer.Delete( KStreamName );    
    RFileWriteStream fWrite;
    User::LeaveIfError( fWrite.Create( tempServer, 
        KStreamName, EFileWrite ) );
    CleanupClosePushL( fWrite );
    iListBox->WriteInternalStateL( fWrite );
    AssertTrueL( ETrue, KTextListTest53 );
    CleanupStack::PopAndDestroy( &fWrite );
    
    CEikTextListBox* textList = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( textList );
    textList->SetContainerWindowL( *iContainer );
    TResourceReader textReader;
    iEikEnv->CreateResourceReaderLC( textReader, 
        R_BCTESTLIST_SINGLE_1_ADD_RM );
    textList->ConstructFromResourceL( textReader );
    CleanupStack::PopAndDestroy(); // textReader
    CleanupStack::PopAndDestroy( textList );
    AssertTrueL( ETrue, KTextListTest54 );
    }

// ---------------------------------------------------------------------------
// Test CSnakingListBoxView
// ---------------------------------------------------------------------------
//
void CBCTestListEiklistCase::TestSnakingListBoxViewL()
    {
    CSnakingListBoxView* view = 
        static_cast<CSnakingListBoxView*>( iSnakingList->View() );
    TInt num = view->VisibleWidth( view->ViewRect() );
    AssertTrueL( ETrue, KSnakingViewTest1 );
    view->HScroll( num - 1 );
    AssertTrueL( ETrue, KSnakingViewTest2 );
    view->SetItemHeight( 30 );
    AssertTrueL( ETrue, KSnakingViewTest3 );
    TInt visible = view->CalculateHScrollOffsetSoItemIsVisible( 0 );
    AssertTrueL( ETrue, KSnakingViewTest4 );
    }

// ---------------------------------------------------------------------------
// Test CEikSnakingListBox
// ---------------------------------------------------------------------------
//
void CBCTestListEiklistCase::TestSnakingListBoxL()
    {
    TRect rect = iContainer->Rect();
    CListBoxView* view = iSnakingList->MakeViewClassInstanceL();
    delete view;
    AssertTrueL( ETrue, KSnakingTest1 );
    iSnakingList->SetColumnWidth( 100 );
    AssertTrueL( ETrue, KSnakingTest2 );
    TInt columnWidth = iSnakingList->ColumnWidth();
    AssertIntL( 100, columnWidth, KSnakingTest3 );
    iSnakingList->HandleLeftArrowKeyL( CListBoxView::ESingleSelection );
    AssertTrueL( ETrue, KSnakingTest4 );
    iSnakingList->HandleRightArrowKeyL( CListBoxView::EContiguousSelection );
    AssertTrueL( ETrue, KSnakingTest5 );
    TInt horizontalNudge = iSnakingList->HorizontalNudgeValue();
    AssertTrueL( ETrue, KSnakingTest6 );
    TInt horizGranuInPixel = iSnakingList->HorizScrollGranularityInPixels();
    AssertTrueL( ETrue, KSnakingTest7 );
    iSnakingList->SetTopItemIndex( 1 );
    AssertTrueL( ETrue, KSnakingTest8 );
    iSnakingList->AdjustTopItemIndex();
    AssertTrueL( ETrue, KSnakingTest9 );
    iSnakingList->SizeChanged();
    AssertTrueL( ETrue, KSnakingTest10 );
    iSnakingList->HandleDragEventL( TPoint( 0, 0 ) );
    AssertTrueL( ETrue, KSnakingTest11 );
    iSnakingList->HandleViewRectSizeChangeL();
    AssertTrueL( ETrue, KSnakingTest12 );
    iSnakingList->MoveToNextOrPreviousItemL( TPoint( 10, 50 ) );
    AssertTrueL( ETrue, KSnakingTest13 );
    iSnakingList->RestoreClientRectFromViewRect( rect );
    AssertTrueL( ETrue, KSnakingTest14 );
    TInt height = iSnakingList->AdjustRectHeightToWholeNumberOfItems( 
        rect );
    AssertTrueL( ETrue, KSnakingTest15 );
    
    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( 4 );
    CleanupStack::PushL( colorUseList );
    iSnakingList->CEikSnakingListBox::GetColorUseListL( *colorUseList );
    AssertTrueL( ETrue, KSnakingTest16 );
    colorUseList->Reset();    
    iSnakingList->GetColorUseListL( *colorUseList );
    AssertTrueL( ETrue, KSnakingTest17 );
    CleanupStack::PopAndDestroy( colorUseList );    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos(0, 30);
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    iSnakingList->CEikSnakingListBox::HandlePointerEventL( event );
    AssertTrueL( ETrue, KSnakingTest18 );
    iSnakingList->HandlePointerEventL( event );
    AssertTrueL( ETrue, KSnakingTest19 );
    iSnakingList->CEikSnakingListBox::HandleResourceChange( 
        KAknsMessageSkinChange );
    AssertTrueL( ETrue, KSnakingTest20 );
    iSnakingList->HandleResourceChange( KAknsMessageSkinChange );
    AssertTrueL( ETrue, KSnakingTest21 );
    CTextListBoxModel* model = iSnakingList->Model();
    AssertTrueL( ETrue, KSnakingTest22 );
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestListBoxData::TestConstructFont
// ---------------------------------------------------------------------------
//
void CBCTestListBoxData::TestConstructFontL( const CFont* aBaseFont )
    {
    TFontStyle style( EPostureItalic, EStrokeWeightBold, 
        EPrintPosSuperscript );    
    ConstructFontL( aBaseFont, style, iItalicFont );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListBoxData::TestRegenerateFonts
// ---------------------------------------------------------------------------
//
TInt CBCTestListBoxData::TestRegenerateFonts()
    {       
    TInt fontHeightInTwips = 20;
    TInt ret = RegenerateFonts( iNormalFont, fontHeightInTwips );    
    return ret;
    }
    
// ---------------------------------------------------------------------------
// CBCTestListBoxData::TestUpdateFontBoundValues
// ---------------------------------------------------------------------------
//
void CBCTestListBoxData::TestUpdateFontBoundValues( const CFont* aBaseFont )
    {    
    UpdateFontBoundValues( *aBaseFont );
    }

// ---------------------------------------------------------------------------
// CBCTestListBoxData::TestCFontWithStyle
// ---------------------------------------------------------------------------
//
TBool CBCTestListBoxData::TestCFontWithStyle()
    {
    TFontStyle style( EPostureItalic, EStrokeWeightBold, 
        EPrintPosSuperscript );    
    iNormalFont.SetFontStyle( style );
    TFontStyle fontStyle = iNormalFont.FontStyle();
    iNormalFont.ReleaseFonts();    
    return ( fontStyle == style );
    }
    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// TBCTestListBoxEditorObserver::HandleListBoxEditorEventL
// Empty functions for test CEikListBoxTextEditor
// ---------------------------------------------------------------------------
//
TKeyResponse TBCTestListBoxEditorObserver::HandleListBoxEditorEventL(
    MEikListBoxEditor* , const TKeyEvent& )
    {
    return EKeyWasConsumed;
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ constructor
// ---------------------------------------------------------------------------
//
CBCTestListBoxEditor::CBCTestListBoxEditor( MListBoxModel* aModel, 
    CEikonEnv* aEikEnv ): CEikListBoxTextEditor( aModel ), iEikEnv( aEikEnv )
    {
    }

// ---------------------------------------------------------------------------
// Test protected API WriteInternalStateL
// ---------------------------------------------------------------------------
//
void CBCTestListBoxEditor::TestWriteInternalStateL()
    {
    RFs& tempServer = iEikEnv->FsSession();
    tempServer.Delete( KStreamName );
    
    RFileWriteStream fWrite;
    User::LeaveIfError( fWrite.Create( tempServer, 
        KStreamName, EFileWrite ) );
    CleanupClosePushL( fWrite );
    WriteInternalStateL( fWrite );
    CleanupStack::PopAndDestroy( &fWrite );
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CBCTestTextListItemDrawer::CBCTestTextListItemDrawer( 
    MTextListBoxModel* aTextListBoxModel, const CFont* aFont ):
    CTextListItemDrawer( aTextListBoxModel, aFont )
    {    
    }

// ---------------------------------------------------------------------------
// Test protected API of CTextListItemDrawer and CListItemDrawer
// ---------------------------------------------------------------------------
//
void CBCTestTextListItemDrawer::TestDrawItemText( CWindowGc& aGc )
    {
    CListItemDrawer::SetGc( &aGc );
    SetGc( &aGc );    
    TSize size = ItemCellSize();
    TRect rect( TPoint( 0, 0 ), size );    
    DrawItemText( 0, rect, ETrue, EFalse, EFalse );
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Fake list box observer
// ---------------------------------------------------------------------------
//
void TBCTestListBoxObserver::HandleListBoxEventL( CEikListBox*, 
        TListBoxEvent )
    {    
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Test protected API: ItemArrayOwnershipType
// ---------------------------------------------------------------------------
//
TListBoxModelItemArrayOwnership CBCTestTextListModel::
    TestItemArrayOwnershipType()
    {
    return ItemArrayOwnershipType();   
    }
