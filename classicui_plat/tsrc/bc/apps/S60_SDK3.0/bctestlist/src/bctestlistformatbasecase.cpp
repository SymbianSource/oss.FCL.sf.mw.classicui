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
* Description:         test case for CEikFormattedCellListBox
*
*/









#include <w32std.h>
#include <eikenv.h>
#include <aknlists.h>
#include <barsread.h>
#include <akndef.h>
#include <aknsconstants.h>
#include <eiktxlbm.h>
#include <eikfrlbd.h>

#include "bctestlistcolumnbasecase.h"
#include "bctestlistformatbasecase.h"
#include "bctestlistcontainer.h"
#include "bctestlist.hrh"
#include <bctestlist.rsg>
#include <bctestlist.mbg>

_LIT( KFormatBaseCreate, "Create CEikFormattedCellListBox" );

_LIT( KFormatTest1, "CEikFormattedCellListBox::UseLogicalToVisualConversion" );
_LIT( KFormatTest2, "CEikFormattedCellListBox::FocusChanged" );
_LIT( KFormatTest3, "CEikFormattedCellListBox::GetColorUseListL" );
_LIT( KFormatTest4, "CEikFormattedCellListBox::HandleResourceChange" );

_LIT( KFormatItemDrawerTest1, "CFormattedCellListBoxItemDrawer::ClearAllPropertiesL" );
_LIT( KFormatItemDrawerTest2, "CFormattedCellListBoxItemDrawer::SetPropertiesL" );
_LIT( KFormatItemDrawerTest3, "CFormattedCellListBoxItemDrawer::ItemWidthInPixels" );
_LIT( KFormatItemDrawerTest4, "CFormattedCellListBoxItemDrawer::DrawItemMark" );

_LIT( KFormateDataTest1, "CFormattedCellListBoxData::SetSkinEnabledL" );
_LIT( KFormateDataTest2, "CFormattedCellListBoxData::SetSkinHighlightFrame" );
_LIT( KFormateDataTest3, "CFormattedCellListBoxData::SetSkinPopupFrame" );
_LIT( KFormateDataTest4, "CFormattedCellListBoxData::SetSkinPopupFramePosition" );
_LIT( KFormateDataTest5, "CFormattedCellListBoxData::UseLogicalToVisualConversion" );
_LIT( KFormateDataTest6, "CFormattedCellListBoxData::SetRespectFocus" );
_LIT( KFormateDataTest7, "CFormattedCellListBoxData::EnableMarqueeL" );
_LIT( KFormateDataTest8, "CFormattedCellListBoxData::SetSubCellFontForRowL" );
_LIT( KFormateDataTest9, "CFormattedCellListBoxData::SetDrawBackground" );
_LIT( KFormateDataTest10, "CFormattedCellListBoxData::SetMarqueeParams" );
_LIT( KFormateDataTest11, "CFormattedCellListBoxData::SetSubcellUnderlined" );
_LIT( KFormateDataTest12, "CFormattedCellListBoxData::ConstructLD" );
_LIT( KFormateDataTest13, "CFormattedCellListBoxData::HighlightAnim" );
_LIT( KFormateDataTest14, "CFormattedCellListBoxData::SetHighlightAnimBackgroundDrawer" );
_LIT( KFormateDataTest15, "CFormattedCellListBoxData::AboutToDrawHighlightAnim" );
_LIT( KFormateDataTest16, "CFormGraphicListBoxData::NewL" );
_LIT( KFormateDataTest17, "CFormGraphicListBoxData::Draw" );
_LIT( KFormateDataTest18, "CPopupFormattedListBoxData::NewL" );
_LIT( KFormateDataTest19, "CFormGraphicListBoxData::Draw" );
_LIT( KFormatDataTestText, "Test text for draw" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestListFormatBaseCase* CBCTestListFormatBaseCase::NewL( 
    CBCTestListContainer* aContainer, CEikonEnv* aEikEnv )
    {
    CBCTestListFormatBaseCase* self = new( ELeave ) CBCTestListFormatBaseCase( 
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
CBCTestListFormatBaseCase::CBCTestListFormatBaseCase( CBCTestListContainer* aContainer,
    CEikonEnv* aEikEnv )
    : CBCTestListBaseCase( aContainer, aEikEnv )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestListFormatBaseCase::~CBCTestListFormatBaseCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestListFormatBaseCase::ConstructL()
    {    
    BuildScriptL(); 
    }
    
// ---------------------------------------------------------------------------
// CBCTestListFormatBaseCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestListFormatBaseCase::BuildScriptL()
    {    
    for ( TInt i=0; i <= EBCTestCmdOutline50 - EBCTestCmdOutline48; i++ )
        {
        AddTestL( LeftCBA, REP( Down, 7 ), KeyOK, TEND );
        AddTestL( REP( Down, i ), KeyOK, TEND );
        }      
    }
    
// ---------------------------------------------------------------------------
// CBCTestListFormatBaseCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestListFormatBaseCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline48 || aCmd > EBCTestCmdOutline50 )
        {
        return;
        }
    ReleaseCase();
    PrepareCaseL();
    switch ( aCmd )
        {
        case EBCTestCmdOutline48:
            TestFormatListL();
            break;
        case EBCTestCmdOutline49:
            TestFormatItemDrawerL();
            break;
        case EBCTestCmdOutline50:
            TestFormatListDataL();
            break;
        default:
            break;    
        }
    }

// ---------------------------------------------------------------------------
// CBCTestListFormatBaseCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestListFormatBaseCase::PrepareCaseL()
    {
    iListBox = new( ELeave ) CAknDoubleStyle2ListBox();
    AssertNotNullL( iListBox, KFormatBaseCreate );    
    
    CDesCArray* textArray = iEikEnv->ReadDesCArrayResourceL( 
        R_BCTESTLIST_DOUBLE2_ITEM );
    
    if ( iListBox )
        {
        if ( textArray )
            {
            SetListBoxFromInnerDescriptionL( iListBox, 
                EAknListBoxSelectionList, textArray );
            }
        SetGraphicIconL( iListBox );
        
        iContainer->SetControl( iListBox );
        }
    }

// ---------------------------------------------------------------------------
// CBCTestListFormatBaseCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestListFormatBaseCase::ReleaseCase()
    {
    iContainer->ResetControl();
    iListBox = NULL;
    }    

// ---------------------------------------------------------------------------
// CBCTestListFormatBaseCase::TestFormatListL
// ---------------------------------------------------------------------------
// 
void CBCTestListFormatBaseCase::TestFormatListL()
    {
    iListBox->UseLogicalToVisualConversion( ETrue );
    iListBox->UseLogicalToVisualConversion( EFalse );
    AssertTrueL( ETrue, KFormatTest1 );
        
    iListBox->FocusChanged( EDrawNow );
    iListBox->FocusChanged( ENoDrawNow );
    AssertTrueL( ETrue, KFormatTest2 );
        
    TInt granularity = 4;
    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( granularity );
    CleanupStack::PushL( colorUseList );
    iListBox->GetColorUseListL( *colorUseList );
    AssertTrueL( ( colorUseList->Count() > 0 ), KFormatTest3 );
    colorUseList->Reset();
    CleanupStack::PopAndDestroy( colorUseList );
    
    iListBox->HandleResourceChange( KAknsMessageSkinChange );    
    iListBox->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    AssertTrueL( ETrue, KFormatTest4 );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListFormatBaseCase::TestFormatItemDrawerL
// ---------------------------------------------------------------------------
// 
void CBCTestListFormatBaseCase::TestFormatItemDrawerL()
    {
    CFormattedCellListBoxItemDrawer* itemDrawer = iListBox->ItemDrawer();

    itemDrawer->ClearAllPropertiesL();
    AssertTrueL( ETrue, KFormatItemDrawerTest1 );
        
    TListItemProperties itemProp;
    itemProp.SetBold( ETrue );
    itemProp.SetItalics( ETrue );
    itemProp.SetUnderlined( ETrue );
    itemProp.SetDimmed( ETrue );
    itemProp.SetColor( KRgbGray );
    itemProp.SetSeparatorAfter( ETrue ); 
    itemDrawer->SetPropertiesL( 0, itemProp );
    AssertTrueL( ETrue, KFormatItemDrawerTest2 );
        
    TInt width = itemDrawer->ItemWidthInPixels( 0 );
    AssertTrueL( ETrue, KFormatItemDrawerTest3 );
        
    TPoint pt( 0, 0 );
    itemDrawer->DrawItemMark( ETrue, EFalse, pt );
    AssertTrueL( ETrue, KFormatItemDrawerTest4 );
    }
    
// ---------------------------------------------------------------------------
// CBCTestListFormatBaseCase::TestFormatListDataL
// ---------------------------------------------------------------------------
// 
void CBCTestListFormatBaseCase::TestFormatListDataL()
    {
    CFormattedCellListBoxData* data = 
        iListBox->ItemDrawer()->FormattedCellData();
    
    data->SetSkinEnabledL( ETrue );
    TBool skin = data->SkinEnabled();
    AssertTrueL( skin, KFormateDataTest1 );
    
    TAknsItemID id;
    id.Set( KAknsIIDDefault );
    data->SetSkinHighlightFrame( &id, &id );
    AssertTrueL( ETrue, KFormateDataTest2 );    
    
    data->SetSkinPopupFrame( &id, &id );
    AssertTrueL( ETrue, KFormateDataTest3 ); 
        
    TRect rect = iContainer->Rect();
    TRect innerRect( rect.iTl.iX + 2, rect.iTl.iY + 2, rect.iBr.iX - 2, 
        rect.iBr.iY - 2 );
    data->SetSkinPopupFramePosition( rect, innerRect );
    AssertTrueL( ETrue, KFormateDataTest4 );    
    
    data->UseLogicalToVisualConversion( ETrue );
    AssertTrueL( ETrue, KFormateDataTest5 );
        
    data->SetRespectFocus( ETrue );
    AssertTrueL( ETrue, KFormateDataTest6 );
    
    data->EnableMarqueeL( ETrue );
    AssertTrueL( ETrue, KFormateDataTest7 );
    
    data->SetSubCellFontForRowL( 0, 0, iEikEnv->NormalFont() );
    AssertTrueL( ETrue, KFormateDataTest8 );
    
    data->SetDrawBackground( ETrue );
    AssertTrueL( ETrue, KFormateDataTest9 );
    
    data->SetMarqueeParams( 1, 6, 1000000, 100000 );
    AssertTrueL( ETrue, KFormateDataTest10 );
    
    TBitFlags32 flags;
    data->SetSubcellUnderlined( flags );
    AssertTrueL( ETrue, KFormateDataTest11 );
#ifdef __S60_32__    
    iListBox->SetCurrentItemIndex( 2 );//item 3;
        
    TUint32 tInt = data->CurrentItemTextWasClipped();
    _LIT( KColumnDataTest35, 
        "Test CurrentItemTextWasClipped() at short item." ); 
    AssertTrueL( ETrue, KColumnDataTest35 );
    iListBox->SetCurrentItemIndex( 3 );//item 4;
    tInt = data->CurrentItemTextWasClipped();
    _LIT( KColumnDataTest36, 
        "Test CurrentItemTextWasClipped() at long item." ); 
    AssertTrueL( ETrue, KColumnDataTest36 );    
    iListBox->DrawNow(); 
#endif //__S60_32__
    CBCTestListFormatData* bcData = new( ELeave ) 
        CBCTestListFormatData();
    CleanupStack::PushL( bcData );
    bcData->TestConstructLD( id );
    AssertTrueL( ETrue, KFormateDataTest12 );
    
    CleanupStack::PopAndDestroy( bcData );
        
    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    DrawCaseL( gc );
    iContainer->DeactivateGc();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListFormatBaseCase::DrawCaseL
// ---------------------------------------------------------------------------
//
void CBCTestListFormatBaseCase::DrawCaseL( CWindowGc& aGc )
    {
    CFormattedCellListBoxData* data = 
        iListBox->ItemDrawer()->FormattedCellData();
    data->HighlightAnim();
    AssertTrueL( ETrue, KFormateDataTest13 );
    
    data->SetHighlightAnimBackgroundDrawer( &iDrawer );
    AssertTrueL( ETrue, KFormateDataTest14 );
    
    data->AboutToDrawHighlightAnim();
    AssertTrueL( ETrue, KFormateDataTest15 );
        
    TListItemProperties itemProp;
    itemProp.SetBold( ETrue );
    itemProp.SetItalics( ETrue );
    itemProp.SetUnderlined( ETrue );
    itemProp.SetDimmed( ETrue );
    itemProp.SetColor( KRgbGray );
    itemProp.SetSeparatorAfter( ETrue );     
    TSize size = iListBox->ItemDrawer()->ItemCellSize();
    TRect rect( iContainer->Rect().iTl.iX, iContainer->Rect().iTl.iY, 
        iContainer->Rect().iTl.iX + size.iWidth, 
        iContainer->Rect().iTl.iY + size.iHeight );
    const CFormattedCellListBoxData::TColors& colors = 
        data->SubCellColors( 0 );    
    TPtrC text( KFormatDataTestText );
    
    CFormGraphicListBoxData* graphicData = 
        CFormGraphicListBoxData::NewL();
    CleanupStack::PushL( graphicData );
    AssertNotNullL( graphicData, KFormateDataTest16 );    
    graphicData->Draw( itemProp, aGc, &text, rect, ETrue, colors );    
    AssertTrueL( ETrue, KFormateDataTest17 );    
    CleanupStack::PopAndDestroy( graphicData );
    
    CPopupFormattedListBoxData* popupData = 
        CPopupFormattedListBoxData::NewL();
    CleanupStack::PushL( popupData );
    AssertNotNullL( popupData, KFormateDataTest18 );
    popupData->Draw( itemProp, aGc, &text, rect, ETrue, colors );
    AssertTrueL( ETrue, KFormateDataTest19 );    
    CleanupStack::PopAndDestroy( popupData );
    }
    
// ---------------------------------------------------------------------------
// CBCTestListFormatBaseCase::GraphicIconL
// ---------------------------------------------------------------------------
//
void CBCTestListFormatBaseCase::GraphicIconL( CArrayPtr<CGulIcon>* aIcons )
    {
    if ( aIcons )
        {
        CreateIconAndAddToArrayL(
            aIcons, KBCTestListMifFileName,
            EMbmBctestlistQgn_indi_marked_add,
            EMbmBctestlistQgn_indi_marked_add_mask );
        CreateIconAndAddToArrayL(
            aIcons, KBCTestListMbmFileName,
            EMbmBctestlistGolgo3,
            EMbmBctestlistGolgo3_mask );
        }
    }
    
// ======== MEMBER FUNCTIONS ========
// CBCTestListFormatData

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CBCTestListFormatData::CBCTestListFormatData()
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestListFormatData::~CBCTestListFormatData()
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListFormatData::ConstructLD
// ---------------------------------------------------------------------------
//
void CBCTestListFormatData::TestConstructLD( 
    const TAknsItemID& aAnimationIID )
    {
    CFormattedCellListBoxData::ConstructLD( aAnimationIID );
    }
    
// ======== MEMBER FUNCTIONS ========
// TBCTestListFormatAnimBgDrawer

// ---------------------------------------------------------------------------
// TBCTestListFormatAnimBgDrawer::DrawHighlightAnimBackground
// ---------------------------------------------------------------------------
//
TBool TBCTestListFormatAnimBgDrawer::
    DrawHighlightAnimBackground( CFbsBitGc& ) const
    {
    return ETrue;
    }
