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
* Description:         test case for list view and item drawer classes
*
*/









#include <w32std.h>
#include <eikenv.h>
#include <aknlists.h>
#include <barsread.h>
#include <akndef.h>
#include <aknsconstants.h>
#include <eiktxlbm.h>
#include <eikclbd.h>

#include "bctestlistcolumnbasecase.h"
#include "bctestlistcontainer.h"
#include "bctestlist.hrh"
#include <bctestlist.rsg>

_LIT( KColumnBaseCreate, "Create CEikColumnListBox" );

_LIT( KColumnListTest1, "CEikColumnListBox::EditItemL" );
_LIT( KColumnListTest2, "CEikColumnListBox::GetColorUseListL" );
_LIT( KColumnListTest3, "CEikColumnListBox::HandleResourceChange" );
_LIT( KColumnListTest4, "CEikColumnListBox::FocusChanged" );
_LIT( KColumnListTest5, "CAknColumnListBox::MakeViewClassInstanceL" );
_LIT( KColumnListTest6, "CEikColumnListBox::MakeViewClassInstanceL" );

_LIT( KColumnItemDrawerTest1, "CColumnListBoxItemDrawer::ClearAllPropertiesL" );
_LIT( KColumnItemDrawerTest2, "CColumnListBoxItemDrawer::SetPropertiesL" );
_LIT( KColumnItemDrawerTest3, "CColumnListBoxItemDrawer::ItemWidthInPixels" );
_LIT( KColumnItemDrawerTest4, "CColumnListBoxItemDrawer::DrawItemMark" );

_LIT( KColumnEditorTest1, "CEikColumnListBoxEditor::ConstructL" );
_LIT( KColumnEditorTest2, "CEikColumnListBoxEditor::ItemText" );
_LIT( KColumnEditorTest3, "CEikColumnListBoxEditor::UpdateModelL" );
_LIT( KColumnEditorTest4, "CEikColumnListBoxEditor::Column" );
_LIT( KColumnEditorTest5, "CEikColumnListBoxEditor::HandlePointerEventL" );

_LIT( KColumnDataTest1, "CColumnListBoxData::SetSkinEnabledL" );
_LIT( KColumnDataTest2, "CColumnListBoxData::SetSkinHighlightFrame" );
_LIT( KColumnDataTest3, "CColumnListBoxData::EnableMarqueeL" );
_LIT( KColumnDataTest4, "CColumnListBoxData::SetColumnHorizontalGapL" );
_LIT( KColumnDataTest5, "CColumnListBoxData::SetColumnHorizontalGapL" );
_LIT( KColumnDataTest6, "CColumnListBoxData::MakeColumnRect" );
_LIT( KColumnDataTest7, "CColumnListBoxData::SetColumnFontForRowL" );
_LIT( KColumnDataTest8, "CColumnListBoxData::SetMarqueeParams" );
_LIT( KColumnDataTest9, "CColumnListBoxData::SetColumnUnderlined" );
_LIT( KColumnDataTest10, "CColumnListBoxData::HighlightAnim" );
_LIT( KColumnDataTest11, "CColumnListBoxData::SetHighlightAnimBackgroundDrawer" );
_LIT( KColumnDataTest12, "CColumnListBoxData::AboutToDrawHighlightAnim" );
_LIT( KColumnDataTest13, "CColumnListBoxData::ConstructLD" );
_LIT( KColumnDataTest14, "CColumnListBoxData::DrawText" );
_LIT( KColumnDataText, "Test text for DrawText" );
_LIT( KClippedText, "Test text" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestListColumnBaseCase* CBCTestListColumnBaseCase::NewL( 
    CBCTestListContainer* aContainer, CEikonEnv* aEikEnv )
    {
    CBCTestListColumnBaseCase* self = new( ELeave ) CBCTestListColumnBaseCase( 
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
CBCTestListColumnBaseCase::CBCTestListColumnBaseCase( CBCTestListContainer* aContainer,
    CEikonEnv* aEikEnv )
    : CBCTestListBaseCase( aContainer, aEikEnv )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestListColumnBaseCase::~CBCTestListColumnBaseCase()
    {      
    delete iBCData;
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestListColumnBaseCase::ConstructL()
    {    
    BuildScriptL(); 
    
    iBCData = new( ELeave ) CBCTestColumnListBoxData();
    }
    
// ---------------------------------------------------------------------------
// CBCTestListColumnBaseCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestListColumnBaseCase::BuildScriptL()
    {    
    for ( TInt i=0; i <= EBCTestCmdOutline47 - EBCTestCmdOutline45; i++ )
        {
        AddTestL( LeftCBA, REP( Down, 6 ), KeyOK, TEND );
        AddTestL( REP( Down, i ), KeyOK, TEND );
        }      
    }
    
// ---------------------------------------------------------------------------
// CBCTestListColumnBaseCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestListColumnBaseCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline45 || aCmd > EBCTestCmdOutline47 )
        {
        return;
        }
    ReleaseCase();
    PrepareCaseL( aCmd );
    switch ( aCmd )
        {
        case EBCTestCmdOutline45:
            TestColumnListL();
            break;
        case EBCTestCmdOutline46:
            TestColumnItemDrawerAndEditorL();
            break;
        case EBCTestCmdOutline47:
            TestColumnListDataL();
            break;
        default:
            break;    
        }
    }

// ---------------------------------------------------------------------------
// CBCTestListColumnBaseCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestListColumnBaseCase::PrepareCaseL( TInt )
    {
    iListBox = new( ELeave ) CAknSingleStyleListBox();
    AssertNotNullL( iListBox, KColumnBaseCreate );
    TInt resourceId = R_BCTESTLIST_SINGLE_1_ADD_RM;
    SetListBoxFromResourceL( iListBox, resourceId );    
    
    iContainer->SetControl( iListBox );
    }

// ---------------------------------------------------------------------------
// CBCTestListColumnBaseCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestListColumnBaseCase::ReleaseCase()
    {
    iContainer->ResetControl();
    iListBox = NULL;
    }    

// ---------------------------------------------------------------------------
// CBCTestListColumnBaseCase::TestColumnListL
// ---------------------------------------------------------------------------
// 
void CBCTestListColumnBaseCase::TestColumnListL()
    {    
    TInt maxLength = 3;
    iListBox->EditItemL( 0, maxLength );
    iListBox->StopEditingL( 0 );
    AssertTrueL( ETrue, KColumnListTest1 );
    
    TInt granularity = 4;
    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( granularity );
    CleanupStack::PushL( colorUseList );
    iListBox->GetColorUseListL( *colorUseList );
    AssertTrueL( ( colorUseList->Count() > 0 ),  KColumnListTest2 );
    colorUseList->Reset();
    CleanupStack::PopAndDestroy( colorUseList );
    
    iListBox->HandleResourceChange( KAknsMessageSkinChange );    
    iListBox->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    AssertTrueL( ETrue, KColumnListTest3 );
        
    iListBox->FocusChanged( EDrawNow );
    iListBox->FocusChanged( ENoDrawNow );
    AssertTrueL( ETrue, KColumnListTest4 );    
    
    CListBoxView* view = iListBox->MakeViewClassInstanceL();
    AssertNotNullL( view, KColumnListTest5 );
    delete view;
    
    CEikColumnListBox* columnList = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( columnList );
    TInt resourceId = R_BCTESTLIST_SINGLE_1_ADD_RM;
    SetListBoxFromResourceL( columnList, resourceId );    
    view = columnList->MakeViewClassInstanceL();
    AssertNotNullL( view, KColumnListTest6 );    
    delete view;
    columnList->EditItemL( 0, 1 );
    columnList->StopEditingL( EFalse );
    CleanupStack::PopAndDestroy( columnList );
    
    CEikColumnListBox* listBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( listBox );
    listBox->ConstructL( iContainer );
    view = listBox->MakeViewClassInstanceL();
    delete view;
    CleanupStack::PopAndDestroy( listBox );
    }
    
// ---------------------------------------------------------------------------
// CBCTestListColumnBaseCase::TestColumnItemDrawerAndEditorL
// ---------------------------------------------------------------------------
// 
void CBCTestListColumnBaseCase::TestColumnItemDrawerAndEditorL()
    {
    // for column item drawer    
    CColumnListBoxItemDrawer* itemDrawer = iListBox->ItemDrawer();
    
    itemDrawer->ClearAllPropertiesL();
    AssertTrueL( ETrue, KColumnItemDrawerTest1 );    
    
    TListItemProperties itemProp;
    itemProp.SetBold( ETrue );
    itemProp.SetItalics( ETrue );
    itemProp.SetUnderlined( ETrue );
    itemProp.SetDimmed( ETrue );
    itemProp.SetColor( KRgbGray );
    itemProp.SetSeparatorAfter( ETrue ); 
    itemDrawer->SetPropertiesL( 0, itemProp );
    AssertTrueL( ETrue, KColumnItemDrawerTest2 );    
    
    TInt width = itemDrawer->ItemWidthInPixels( 0 );
    AssertTrueL( ETrue, KColumnItemDrawerTest3 );    
    
    TPoint pt( 0, 0 );
    itemDrawer->DrawItemMark( ETrue, EFalse, pt );
    AssertTrueL( ETrue, KColumnItemDrawerTest4 );
    
    // for column list editor
    CBCTestColumnListBoxEditor* editor = new( ELeave ) 
        CBCTestColumnListBoxEditor( iListBox->Model() );
    CleanupStack::PushL( editor );
    
    editor->ConstructL( 0 );
    AssertTrueL( ETrue, KColumnEditorTest1 );
    
    TPtrC text = editor->ItemText();
    AssertTrueL( ETrue, KColumnEditorTest2 );
        
    TBool update = editor->UpdateModelL();
    AssertTrueL( ETrue, KColumnEditorTest3 );
        
    TInt column = editor->Column();
    AssertTrueL( ETrue, KColumnEditorTest4 );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos(0, 30);
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    editor->HandlePointerEventL( event );
    AssertTrueL( ETrue, KColumnEditorTest5 );    
    
    CleanupStack::PopAndDestroy( editor ); 
    }
    
// ---------------------------------------------------------------------------
// CBCTestListColumnBaseCase::TestColumnListDataL
// ---------------------------------------------------------------------------
// 
void CBCTestListColumnBaseCase::TestColumnListDataL()
    {
    CColumnListBoxData* data = iListBox->ItemDrawer()->ColumnData();
    data->SetSkinEnabledL( ETrue );
    AssertTrueL( ETrue, KColumnDataTest1 );
    
    TAknsItemID id;
    id.Set( KAknsIIDDefault );
    data->SetSkinHighlightFrame( &id, &id );
    AssertTrueL( ETrue, KColumnDataTest2 );
        
    data->EnableMarqueeL( ETrue );
    AssertTrueL( ETrue, KColumnDataTest3 );
#ifdef __S60_32__     
    iListBox->SetCurrentItemIndex( 0 );//item 1
    
    TUint32 tInt = data->CurrentItemTextWasClipped();
    _LIT( KColumnDataTest35, "Test CurrentItemTextWasClipped() at long item" ); 
    AssertTrueL( ETrue, KColumnDataTest35 );
    iListBox->SetCurrentItemIndex( 1 );//item 2
    tInt = data->CurrentItemTextWasClipped();
    _LIT( KColumnDataTest36, "Test CurrentItemTextWasClipped() at short item" ); 
    AssertTrueL( ETrue, KColumnDataTest36 );    
    iListBox->DrawNow();
#endif //__S60_32__
    TInt setGap = 5;
    data->SetColumnHorizontalGapL( 0, setGap );
    AssertTrueL( ETrue, KColumnDataTest4 );

    TInt gap = data->ColumnHorizontalGap( 0 );
    AssertIntL( setGap, gap, KColumnDataTest5 );
    
    TRect rect = iContainer->Rect();
    rect.iBr.iX /= 2;
    TBool setRect = data->MakeColumnRect( 0, rect );
    AssertTrueL( setRect, KColumnDataTest6 );
    
    data->SetColumnFontForRowL( 0, 0, iEikEnv->NormalFont() );
    AssertTrueL( setRect, KColumnDataTest7 );
    
    data->SetMarqueeParams( 1, 6, 1000000 );
    data->SetMarqueeParams( 2, 8, 1000000, 100000 );
    AssertTrueL( setRect, KColumnDataTest8 );
    
    TBitFlags32 flags;
    data->SetColumnUnderlined( flags );
    AssertTrueL( setRect, KColumnDataTest9 );
    
    data->HighlightAnim();
    AssertTrueL( setRect, KColumnDataTest10 );
    
    data->SetHighlightAnimBackgroundDrawer( &iDrawer );
    AssertTrueL( setRect, KColumnDataTest11 );
    
    data->AboutToDrawHighlightAnim();
    AssertTrueL( setRect, KColumnDataTest12 );
        
    iBCData->TestConstructLD( id );
    AssertTrueL( setRect, KColumnDataTest13 );
        
    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    gc.UseFont( iEikEnv->NormalFont() );
    
    rect = iContainer->Rect();
    rect.iBr.iX = rect.iTl.iX + 
        iListBox->ItemDrawer()->ItemCellSize().iWidth;
    rect.iBr.iY = rect.iTl.iY + 
        iListBox->ItemDrawer()->ItemCellSize().iHeight;        
    iBCData->TestDrawText( gc, rect,  KColumnDataText, KClippedText, 
        0, CGraphicsContext::ELeft, *iEikEnv->NormalFont(), ETrue, EFalse ); 
    AssertTrueL( ETrue, KColumnDataTest14 );
    
    iContainer->DeactivateGc();
    }
    
// ======== MEMBER FUNCTIONS ========
// CBCTestColumnListBoxData

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CBCTestColumnListBoxData::CBCTestColumnListBoxData()
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestColumnListBoxData::~CBCTestColumnListBoxData()
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestColumnListBoxData::ConstructLD
// ---------------------------------------------------------------------------
//
void CBCTestColumnListBoxData::TestConstructLD( 
    const TAknsItemID& aAnimationIID )
    {
    CColumnListBoxData::ConstructLD( aAnimationIID );
    }
    
// ---------------------------------------------------------------------------
// CBCTestColumnListBoxData::TestDrawText
// ---------------------------------------------------------------------------
//
void CBCTestColumnListBoxData::TestDrawText( 
    CWindowGc& aGc, const TRect& aTextRect, 
    const TDesC& aText, const TDesC& aClippedText, const TInt aBaselineOffset,
	const CGraphicsContext::TTextAlign aAlign, const CFont& aFont,
	const TBool aHighlight, const TBool aIsTextClipped )
    {
    DrawText( aGc, aTextRect, aText, aClippedText, 
            aBaselineOffset, aAlign, aFont, aHighlight, aIsTextClipped );    
    }
    
// ======== MEMBER FUNCTIONS ========
// TBCTestListBoxAnimBgDrawer

// ---------------------------------------------------------------------------
// TBCTestListBoxAnimBgDrawer::DrawHighlightAnimBackground
// ---------------------------------------------------------------------------
//
TBool TBCTestListBoxAnimBgDrawer::
    DrawHighlightAnimBackground( CFbsBitGc& ) const
    {
    return ETrue;
    }
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestListBoxAnimBgDrawer::DrawHighlightAnimBackground
// ---------------------------------------------------------------------------
//
CBCTestColumnListBoxEditor::CBCTestColumnListBoxEditor( 
    MListBoxModel* aModel ): CEikColumnListBoxEditor( aModel )
    {    
    }
