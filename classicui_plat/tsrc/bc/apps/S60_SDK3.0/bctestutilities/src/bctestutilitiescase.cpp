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
#include <GULUTIL.h>
#include <aknutils.h>
#include <eikfrlb.h>
#include <eikclb.h>
#include <eikmenup.h>
#include <aknsfld.h>
#include <aknlists.h>
#include <akndialog.h>
#include <bctestutilities.rsg>
#include <eikclbd.h>
#include <aknsfld.h>
#include <eikmfne.h>
#include <eikseced.h>
#include <aknlayoutfont.h>
#include <aknfontspecification.h>
#include <aknbiditextutils.h>
#include <akniconarray.h>
#include <akndef.h>

#include "bctestutilitiescase.h"
#include "bctestutilitiescontainer.h"
#include "bctestutilities.hrh"

const TInt KShortBuffer = 20;
const TInt KBufferSize = 64;
const TInt KSearchFieldMaxLength = 256;

_LIT( KShortStr, "Short" );
_LIT( KLongStr, "A long string buffer to clip" );
_LIT( KChopText, "Chop Text.\nClip Text for test" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestUtilitiesCase* CBCTestUtilitiesCase::NewL(
    CBCTestUtilitiesContainer* aContainer )
    {
    CBCTestUtilitiesCase* self = new( ELeave ) 
        CBCTestUtilitiesCase( aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestUtilitiesCase::CBCTestUtilitiesCase(
    CBCTestUtilitiesContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestUtilitiesCase::~CBCTestUtilitiesCase()
    {    
    delete iFormatList;
    delete iColumnList;       
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesCase::ConstructL()
    {
    BuildScriptL();
    iEnv = CEikonEnv::Static();
    
    iFormatList = new( ELeave ) CEikFormattedCellListBox();
    iFormatList->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, 
        R_BCTESTUTILITIES_DOUBLE );
    iFormatList->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // resource stuffs.
            
    iColumnList = new( ELeave ) CAknSingleStyleListBox();
    iColumnList->SetContainerWindowL( *iContainer );
    iEnv->CreateResourceReaderLC( reader, 
        R_BCTESTUTILITIES_SINGLE );
    iColumnList->ConstructFromResourceL( reader );
        CleanupStack::PopAndDestroy(); // reader
    }

// ---------------------------------------------------------------------------
// CBCTestUtilitiesCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesCase::BuildScriptL()
    {    
    AddTestL( DELAY( 1 ), TEND );
    TInt loop = EBCTestCmdOtherAknUtils - EBCTestCmdTextUtils;
    for ( TInt i = 0; i <= loop; i++ )
        {
        AddTestL( LeftCBA, KeyOK, REP( Down, i ), KeyOK, TEND );
        }
    // for EBCTestCmdAknBidiTextUtils
    AddTestL( LeftCBA, Down, KeyOK, TEND );    
    
    // for EBCTestCmdAknEnv
    AddTestL( LeftCBA, REP( Down, 2 ), KeyOK, TEND );
    AddTestL( RightCBA, RightCBA, TEND );
    }

// ---------------------------------------------------------------------------
// CBCTestUtilitiesCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesCase::RunL( TInt aCmd )
    {    
    ReleaseCase();    
    switch ( aCmd )
        {
        case EBCTestCmdTextUtils:
            TestTextUtilsL();
            break;
        case EBCTestCmdSelectionService:
            TestSelectionServiceL();
            break;
        case EBCTestCmdAknFind:
            TestAknFindL();
            break;
        case EBCTestCmdAknEditUtils:
            TestAknEditUtilsL();
            break;
        case EBCTestCmdFilter:
            TestFilterModelAndItemL();
            break;
        case EBCTestCmdAknLayoutUtils:
            TestAknLayoutUtilsL();
            break;
        case EBCTestCmdAknDraw:            
            TestAknDrawL();           
            break;
        case EBCTestCmdOtherAknUtils:
            TestOtherAknUtilsL();
            break;
        case EBCTestCmdAknBidiTextUtils:
            TestAknBidiTextUtilsL();
            break;
        case EBCTestCmdAknEnv:
            TestAknEnvL();
            break;
        default:
            break;
        }
    }
    
// ---------------------------------------------------------------------------
// CBCTestUtilitiesCase::ReleaseCase
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesCase::ReleaseCase()
    {
    iContainer->ResetControl();     
    }

// ---------------------------------------------------------------------------
// CBCTestUtilitiesCase::TestTextUtils
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesCase::TestTextUtilsL()
    {    
    TBool result;    
    TBuf<KShortBuffer> smallBuffer( KShortStr );    
    TBuf<KBufferSize> longBuffer( KLongStr );
      
    const CFont& font = *(iEnv->TitleFont());
    TInt maxWidthInPixels = 20;
    result = AknTextUtils::ClipToFit( smallBuffer, font, maxWidthInPixels);
    _LIT( KTextUtilTest1, "AknTextUtils::ClipToFit(TDes&,const CFont& TInt, TClipDirection,TInt,const TDesC&)" );
    AssertTrueL( result, KTextUtilTest1 );
    
    TInt itemIndex = 0;   
    TInt columnNumber = 0;     
    CColumnListBoxData *data = iColumnList->ItemDrawer()->ColumnData();
    data->SetColumnFontL( columnNumber, iEnv->NormalFont() );
    result = AknTextUtils::ClipToFit(
        longBuffer, AknTextUtils::EClipFromEnd, iColumnList,
        itemIndex, columnNumber );
    _LIT( KTextUtilTest2, "AknTextUtils::ClipToFit with CEikColumnListBox" );
    AssertTrueL( result, KTextUtilTest2 );
                     
    longBuffer.Copy( KLongStr );
    TInt subCellNumber = 0;
    CFormattedCellListBoxData* formatData = 
        iFormatList->ItemDrawer()->FormattedCellData();
    formatData->SetSubCellFontL( subCellNumber, iEnv->NormalFont() );
    result = AknTextUtils::ClipToFit(
        longBuffer, AknTextUtils::EClipFromEnd, iFormatList, itemIndex,
        subCellNumber );
    _LIT( KTextUtilTest3, 
        "AkntextUtils::ClipToFit with CEikFormattedCellListBox" );
    AssertTrueL( result, KTextUtilTest3 );
    
    TInt lineWidth = 10;
    CArrayFixFlat<TPtrC>* arrayPtrC = new( ELeave )CArrayFixFlat<TPtrC>( 5 );
    CleanupStack::PushL( arrayPtrC );
    AknTextUtils::WrapToArrayL( longBuffer, lineWidth, font, *arrayPtrC );    
    _LIT( KTextUtilTest4, "AkntextUtils::WrapToArrayL with TInt" );
    AssertTrueL( ETrue, KTextUtilTest4 );
    arrayPtrC->Reset();

    CArrayFixFlat<TInt>* arrayWidth = new( ELeave )CArrayFixFlat<TInt>( 1 );
    CleanupStack::PushL( arrayWidth );
    arrayWidth->AppendL(20);
    arrayWidth->AppendL(20);
    arrayWidth->AppendL(20);
    AknTextUtils::WrapToArrayL( longBuffer, *arrayWidth, font, *arrayPtrC );
    _LIT( KTextUtilTest5, "AknTextUtils::WrapToArrayL with CArrayFix" );
    AssertTrueL( ETrue, KTextUtilTest5 );
    arrayPtrC->Reset();

    AknTextUtils::WrapToArrayAndClipL( longBuffer, *arrayWidth, font, *arrayPtrC );
    _LIT( KTextUtilTest6, "AknTextUtils::WrapToArrayAndClipL with CArryFix" );
    AssertTrueL( ETrue, KTextUtilTest6 );
    arrayPtrC->Reset();
        
    longBuffer.Zero();
    longBuffer.Copy( KChopText );
    AknTextUtils::ChopToArrayAndClipL( longBuffer, *arrayWidth, font, *arrayPtrC );
    _LIT( KTextUtilTest7, "AknTextUtils::ChopToArrayAndClipL with width array" );
    AssertTrueL( ETrue, KTextUtilTest7 );
    arrayPtrC->Reset();
        
    AknTextUtils::ChopToArrayAndClipL( longBuffer, lineWidth, font, *arrayPtrC );
    _LIT( KTextUtilTest8, "AknTextUtils::ChopToArrayAndClipL with integer width" );
    AssertTrueL( ETrue, KTextUtilTest8 );
    arrayPtrC->Reset();
    
    longBuffer.Zero();
    AknTextUtils::WrapToStringL( KLongStr, *arrayWidth, font, longBuffer );
    _LIT( KTextUtilTest9, "AknTextUtils::WrapToStringL" );
    AssertTrueL( ETrue, KTextUtilTest9 );
    
    longBuffer.Zero();
    AknTextUtils::WrapToStringAndClipL( KLongStr, *arrayWidth, font, longBuffer );
    _LIT( KTextUtilTest10, "AknTextUtils::WrapToStringAndClipL" );
    AssertTrueL( ETrue, KTextUtilTest10 );
    
    CleanupStack::PopAndDestroy(2); // arrayWidth, arrayPtrC
    
    _LIT( KStripText, "Test\t text\t" );
    longBuffer.Copy( KStripText );
    AknTextUtils::StripCharacters( longBuffer, KAknStripTabs );
    _LIT( KTextUtilTest11, "AknTextUtils::StripCharacters" );
    AssertTrueL( ETrue, KTextUtilTest11 );
    
    TChar charReplace = 'F';
    longBuffer.Copy( KStripText );
    AknTextUtils::ReplaceCharacters( longBuffer, KAknReplaceTabs, charReplace );
    _LIT( KTextUtilTest12, "AknTextUtils::ReplaceCharacters" );
    AssertTrueL( ETrue, KTextUtilTest12 );
        
    _LIT( KSpace, " " );
    longBuffer.Copy( KStripText );
    AknTextUtils::PackWhiteSpaces( longBuffer, KSpace );
    _LIT( KTextUtilTest13, "AknTextUtils::PackWhiteSpaces" );
    AssertTrueL( ETrue, KTextUtilTest13 );
    
    _LIT(KWesternDigits, "12,000,000");
    longBuffer.Copy( KWesternDigits );
    AknTextUtils::LanguageSpecificNumberConversion( longBuffer );
    _LIT( KTextUtilTest14, "AknTextUtils::LanguageSpecificNumberConversion" );
    AssertTrueL( ETrue, KTextUtilTest14 );
    
    longBuffer.Copy( KWesternDigits );
    AknTextUtils::ConvertDigitsTo( longBuffer, EDigitTypeArabicIndic );
    _LIT( KTextUtilTest15, "AknTextUtils::ConvertDigitsTo" );
    AssertTrueL( ETrue, KTextUtilTest15 );
    
    TBidiText::TDirectionality direct = 
        AknTextUtils::CurrentScriptDirectionality();
    _LIT( KTextUtilTest16, "AknTextUtils::CurrentScriptDirectionality" );
    AssertTrueL( direct == TBidiText::ELeftToRight, KTextUtilTest16 );
                
    TDigitType digitType = AknTextUtils::NumericEditorDigitType();
    _LIT( KTextUtilTest17, "AknTextUtils::NumericEditorDigitType" );
    AssertTrueL( digitType == EDigitTypeWestern, KTextUtilTest17 );

    longBuffer.Copy( KWesternDigits );
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion( longBuffer );
    _LIT( KTextUtilTest18, 
        "AknTextUtils::DisplayTextLanguageSpecificNumberConversion" );
    AssertTrueL( ETrue, KTextUtilTest18 );

    digitType = AknTextUtils::TextEditorDigitType();
    _LIT( KTextUtilTest19, "AknTextUtils::TextEditorDigitType" );
    AssertTrueL( ETrue, KTextUtilTest19 );

    TBool digitModeQuery = AknTextUtils::DigitModeQuery();
    _LIT( KTextUtilTest20, "AknTextUtils::DigitModeQuery" );
    AssertTrueL( ETrue, KTextUtilTest20 );

    _LIT( KTestFileName, "import.jpg" );
    longBuffer.Copy( KTestFileName );
    HBufC* buf = AknTextUtils::ConvertFileNameL( longBuffer );
    _LIT( KTextUtilTest21, "AknTextUtils::ConvertFileNameL" );
    AssertNotNullL( buf, KTextUtilTest21 );
    delete buf;

    _LIT( KScalableText, "shorttext\0x0001Long text for test" );    
    TPtrC chooseST ( AknTextUtils::ChooseScalableText( KScalableText, font, 60 ));
    _LIT( KTextUtilTest22, "AknTextUtils::ChooseScalableText" );
    AssertTrueL( ETrue, KTextUtilTest22 );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestUtilitiesCase::TestSelectionServiceL
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesCase::TestSelectionServiceL()
    {
    iContainer->SetControl( iColumnList );
    
    TInt command = EAknSoftkeyOk;
    AknSelectionService::HandleSelectionListProcessCommandL( 
        command, iColumnList );
    _LIT( KSelectionTest1, 
        "AknSelectionService::HandleSelectionListProcessCommandL" );
    AssertTrueL( ETrue, KSelectionTest1 );
    
    AknSelectionService::HandleMultiselectionListProcessCommandL( 
        command, iColumnList );
    _LIT( KSelectionTest2, 
        "AknSelectionService::HandleMultiselectionListProcessCommandL" );
    AssertTrueL( ETrue, KSelectionTest2 );
    
    AknSelectionService::HandleMarkableListProcessCommandL(
        EAknCmdMark, iColumnList );
    AknSelectionService::HandleMarkableListProcessCommandL(
        EAknCmdUnmark, iColumnList );
    AknSelectionService::HandleMarkableListProcessCommandL(
        EAknMarkAll, iColumnList );
    AknSelectionService::HandleMarkableListProcessCommandL(
        EAknUnmarkAll, iColumnList );
    _LIT( KSelectionTest3, 
        "AknSelectionService::HandleMarkableListProcessCommandL" );
    AssertTrueL( ETrue, KSelectionTest3 );
    
    TKeyEvent event1 = { '1', '1', 0, 0 };
    TKeyEvent eventLeftShift = { EKeyLeftShift, 0, 0, 0 };
    AknSelectionService::HandleMenuListOfferKeyEventL(
        event1, EEventKey, iColumnList );
    AknSelectionService::HandleMenuListOfferKeyEventL(
        eventLeftShift, EEventKey, iColumnList );
    _LIT( KSelectionTest4, 
        "AknSelectionService::HandleMenuListOfferKeyEventL" );
    AssertTrueL( ETrue, KSelectionTest4 );
    
    CAknDialog* dlg = new( ELeave ) CAknDialog();
    CleanupStack::PushL( dlg );
    CEikMenuPane* menuPane = new( ELeave ) CEikMenuPane( dlg );
    CleanupStack::PushL( menuPane );
    AknSelectionService::HandleMarkableListDynInitMenuPane(
        R_BCTESTUTILITIES_CASE_MENU, menuPane, iColumnList );
    _LIT( KSelectionTest5, 
        "AknSelectionService::HandleMarkableListDynInitMenuPane" );
    AssertTrueL( ETrue, KSelectionTest5 );
        
    _LIT( KMenuItemText, "SelectionService" );
    menuPane->ConstructL( NULL, dlg );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EBCTestCmdSelectionService;
    item.iCascadeId = 0;
    item.iFlags = 0;
    item.iText.Copy( KMenuItemText );
        
    menuPane->AddMenuItemL( item );
    AknSelectionService::HandleMarkableListDynInitMenuItem(
        menuPane, iColumnList, EBCTestCmdSelectionService, ETrue );
    _LIT( KSelectionTest6, 
        "AknSelectionService::HandleMarkableListDynInitMenuItem" );
    AssertTrueL( ETrue, KSelectionTest6 );
    
    AknSelectionService::HandleMarkableListUpdateAfterCommandExecution(
        iColumnList );
    _LIT( KSelectionTest7, "AknSelectionService::HandleMarkableListUpdateAfterCommandExecution" );
    AssertTrueL( ETrue, KSelectionTest7 );

    CDesCArray* textArray = static_cast<CDesCArray*>( 
        iColumnList->Model()->ItemTextArray() );
    textArray->Delete( 0 );    
    AknSelectionService::HandleItemRemovalAndPositionHighlightL(
        iColumnList, 0, ETrue );
    _LIT( KSelectionTest8, "AknSelectionService::HandleItemRemovalAndPositionHighlightL" );
    AssertTrueL( ETrue, KSelectionTest8 );
    
    textArray->Delete( 0 );
    textArray->Delete( 2 );
    CArrayFixFlat<TInt>* indexArray = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( indexArray );
    indexArray->AppendL( 0 );
    indexArray->AppendL( 2 );
    AknSelectionService::HandleItemRemovalAndPositionHighlightL(
        iColumnList, 3, *indexArray );
    _LIT( KSelectionTest9, "AknSelectionService::HandleItemRemovalAndPositionHighlightL with array" );
    AssertTrueL( ETrue, KSelectionTest9 );
    CleanupStack::PopAndDestroy( indexArray );
    
    CleanupStack::PopAndDestroy( 2 ); // menuPane, dlg
    
    iContainer->SetControl( NULL );
    }
    
// ---------------------------------------------------------------------------
// CBCTestUtilitiesCase::TestAknFindL
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesCase::TestAknFindL()
    {    
    CAknSearchField* search = CAknSearchField::NewL( *iContainer, 
        CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( search );
    TBCTestControlObserver observer;    
    search->SetObserver( &observer );
    
    AknFind::HandleFindPopupProcessCommandL( EAknSoftkeyOk, iFormatList, 
        search, iContainer );
    _LIT( KAknFindTest1, "AknFind::HandleFindPopupProcessCommandL" );
    AssertTrueL( ETrue, KAknFindTest1 );
        
    CAknFilteredTextListBoxModel* model = 
        static_cast<CAknFilteredTextListBoxModel*>( iFormatList->Model() );
    model->CreateFilterL( iFormatList, search );
    _LIT( KAknFindTest8, "CAknFilteredTextListBoxModel::CreateFilterL" );
    AssertTrueL( ETrue, KAknFindTest8 );
    
    TKeyEvent event4 = { '4', '4', 0 , 0 };
    TBool needRefresh( EFalse );    
    AknFind::HandleFindOfferKeyEventL( event4, EEventKey, iContainer, 
        iFormatList, search, ETrue, needRefresh );
    _LIT( KAknFindTest2, "AknFind::HandleFindOfferKeyEventL" );
    AssertTrueL( ETrue, KAknFindTest2 );
    
    AknFind::HandleFindSizeChanged( iContainer, iFormatList, search );
    _LIT( KAknFindTest3, "AknFind::HandleFindSizeChanged" );
    AssertTrueL( ETrue, KAknFindTest3 );
    
    CAknColumnListBox* listbox = static_cast<CAknColumnListBox*>(
        iColumnList );
    
    AknFind::HandleFixedFindSizeChanged( iContainer, listbox, search );
    _LIT( KAknFindTest4, "AknFind::HandleFixedFindSizeChanged" );
    AssertTrueL( ETrue, KAknFindTest4 );
    
    AknFind::HandlePopupFindSizeChanged( iContainer, iColumnList, search );
    _LIT( KAknFindTest5, "AknFind::HandlePopupFindSizeChanged" );
    AssertTrueL( ETrue, KAknFindTest5 );
    
    _LIT( KSearchText, "Search Text" );
    TBool match = AknFind::IsFindMatch( KSearchText, KSearchText );
    _LIT( KAknFindTest6, "AknFind::IsFindMatch" );
    AssertTrueL( ETrue, KAknFindTest6 );
    
    TChar seperateChar = '\t';
    TBool seperator = AknFind::IsFindWordSeparator( seperateChar );
    _LIT( KAknFindTest7, "AknFind::IsFindWordSeparator" );
    AssertTrueL( ETrue, KAknFindTest7 );
    
    model->RemoveFilter();
    _LIT( KAknFindTest9, "CAknFilteredTextListBoxModel::RemoveFilter" );
    AssertTrueL( ETrue, KAknFindTest9 );
    
    CleanupStack::PopAndDestroy( search );
    }
    
// ---------------------------------------------------------------------------
// CBCTestUtilitiesCase::TestAknEditUtilsL
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesCase::TestAknEditUtilsL()
    {
    CEikEdwin* edwin = new( ELeave ) CEikEdwin();
    CleanupStack::PushL( edwin );
    
    AknEditUtils::ConstructEditingL( edwin, R_BCTESTUTIL_EDWIN );
    _LIT( KAknEditTest1, "AknEditUtils::ConstructEditingL with resource Id" );
    AssertTrueL( ETrue, KAknEditTest1 );
    CleanupStack::PopAndDestroy( edwin );
    
    edwin = new( ELeave ) CEikEdwin();
    CleanupStack::PushL( edwin ); 
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_BCTESTUTIL_EDWIN );
    AknEditUtils::ConstructEditingL( edwin, reader );
    CleanupStack::PopAndDestroy(); // reader    
    _LIT( KAknEditTest2, 
        "AknEditUtils::ConstructEditingL with resource reader" );
    AssertTrueL( ETrue, KAknEditTest2 );
    CleanupStack::PopAndDestroy( edwin );
    
    edwin = new( ELeave ) CEikEdwin();
    CleanupStack::PushL( edwin );    
    AknEditUtils::SAknEditorParameters param;
    param.iEditingSpace = 30;
    param.iEditingWindow = 1;
    param.iCharacterCase = EAknEditorLowerCase;
    param.iJustification = EAknEditorAlignLeft;
    param.iAllowedToMoveInsertionPoint = ETrue;
    param.iCursorYesNo = ETrue;
    param.iOverflowYesNo = EFalse;
    AknEditUtils::ConstructEditingL( edwin, param );
    _LIT( KAknEditTest3, 
        "AknEditUtils::ConstructEditingL with SAknEditorParameters" );
    AssertTrueL( ETrue, KAknEditTest3 );    
    CleanupStack::PopAndDestroy( edwin );
    
    edwin = new( ELeave ) CEikEdwin();
    CleanupStack::PushL( edwin );
    AknEditUtils::ConstructEditingL( edwin, 30, 1, EAknEditorLowerCase,
        EAknEditorAlignLeft, ETrue, ETrue, ETrue );
    _LIT( KAknEditTest4, 
        "AknEditUtils::ConstructEditingL with many parameters" );
    AssertTrueL( ETrue, KAknEditTest4 );
    CleanupStack::PopAndDestroy( edwin );
    
    edwin = new( ELeave ) CEikEdwin();
    CleanupStack::PushL( edwin );
    AknEditUtils::ConstructEditingL( edwin, 30, 2, EAknEditorLowerCase,
        EAknEditorAlignLeft, ETrue, ETrue, ETrue, ETrue );
    _LIT( KAknEditTest5, 
        "AknEditUtils::ConstructEditingL with Resizable" );
    AssertTrueL( ETrue, KAknEditTest5 );
    CleanupStack::PopAndDestroy( edwin );
    }

// ---------------------------------------------------------------------------
// CBCTestUtilitiesCase::TestFilterModelAndItemL
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesCase::TestFilterModelAndItemL()
    {
    CAknFilteredTextListBoxModel* model = 
        static_cast<CAknFilteredTextListBoxModel*>( iFormatList->Model() );
    TInt numberOfItems = model->NumberOfItems();
    _LIT( KFilterTest1, "CAknFilteredTextListBoxModel::NumberOfItems" );
    AssertTrueL( ETrue, KFilterTest1 );
    
    TPtrC itemText = model->ItemText( 0 );
    _LIT( KFilterTest2, "CAknFilteredTextListBoxModel::ItemText" );
    AssertTrueL( ETrue, KFilterTest2 );
    
    const MDesCArray* array = model->MatchableTextArray();
    _LIT( KFilterTest3, "CAknFilteredTextListBoxModel::MatchableTextArray" );
    AssertTrueL( ETrue, KFilterTest3 );
    
    CAknSearchField* search = CAknSearchField::NewL( *iContainer, 
        CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( search );
    
    CAknListBoxFilterItems* item = new( ELeave ) CAknListBoxFilterItems(
        iFormatList, search, model, iFormatList->View() );
    CleanupStack::PushL( item );
    _LIT( KFilterTest4, "CAknListBoxFilterItems::CAknListBoxFilterItems" );
    AssertNotNullL( item, KFilterTest4 );
    
    item->SetParentControl( iContainer );
    _LIT( KFilterTest21, "CAknListBoxFilterItems::SetParentControl" );
    AssertNotNullL( item, KFilterTest21 );
    
    item->ConstructL();
    _LIT( KFilterTest5, "CAknListBoxFilterItems::ConstructL" );
    AssertNotNullL( item, KFilterTest5 );
    
    TBCTestControlObserver observer;
    item->SetObserver( &observer );
    _LIT( KFilterTest18, "CAknListBoxFilterItems::SetObserver" );
    AssertNotNullL( item, KFilterTest18 );
    
    item->ResetFilteringL();
    _LIT( KFilterTest6, "CAknListBoxFilterItems::ResetFilteringL" );
    AssertNotNullL( item, KFilterTest6 );
    
    item->UpdateCachedDataL();
    _LIT( KFilterTest7, "CAknListBoxFilterItems::UpdateCachedDataL" );
    AssertNotNullL( item, KFilterTest7 );
    
    CArrayFix<TInt>* indexArray = item->SelectionIndexes();
    _LIT( KFilterTest8, "CAknListBoxFilterItems::SelectionIndexes" );
    AssertNotNullL( item, KFilterTest8 );
    
    item->UpdateSelectionIndexesL();
    _LIT( KFilterTest9, "CAknListBoxFilterItems::UpdateSelectionIndexesL" );
    AssertNotNullL( item, KFilterTest9 );
    
    item->UpdateSelectionIndexL( 0 );
    _LIT( KFilterTest10, "CAknListBoxFilterItems::UpdateSelectionIndexL" );
    AssertNotNullL( item, KFilterTest10 );
    
    TInt number = item->FilteredNumberOfItems();
    _LIT( KFilterTest11, "CAknListBoxFilterItems::FilteredNumberOfItems" );
    AssertNotNullL( item, KFilterTest11 );
    
    TInt index = item->FilteredItemIndex( 0 );
    _LIT( KFilterTest12, "CAknListBoxFilterItems::FilteredItemIndex" );
    AssertNotNullL( item, KFilterTest12 );
    
    TInt nonIndex = item->NonFilteredNumberOfItems();
    _LIT( KFilterTest13, 
        "CAknListBoxFilterItems::NonFilteredNumberOfItems" );
    AssertNotNullL( item, KFilterTest13 );
    
    TInt visibleIndex = item->VisibleItemIndex( 2 );
    _LIT( KFilterTest14, 
        "CAknListBoxFilterItems::VisibleItemIndex" );
    AssertNotNullL( item, KFilterTest14 );
    
    _LIT( KFilterItemDefaultText, "Default text" );
    TPtrC defaultText( KFilterItemDefaultText );
    TPtrC text = item->DefaultMatchableItemFromItem( defaultText );
    _LIT( KFilterTest15, 
        "CAknListBoxFilterItems::DefaultMatchableItemFromItem" );
    AssertNotNullL( item, KFilterTest15 );
    
    item->HandleOfferkeyEventL();
    _LIT( KFilterTest16, 
        "CAknListBoxFilterItems::HandleOfferkeyEventL" );
    AssertNotNullL( item, KFilterTest16 );
    
    item->HandleItemArrayChangeL();
    _LIT( KFilterTest17, 
        "CAknListBoxFilterItems::HandleItemArrayChangeL" );
    AssertNotNullL( item, KFilterTest17 ); 
    
    item->HandleControlEventL( iContainer, 
        MCoeControlObserver::EEventRequestFocus );
    _LIT( KFilterTest19, 
        "CAknListBoxFilterItems::HandleControlEventL" );
    AssertNotNullL( item, KFilterTest19 ); 
    
    item->DeferredSendKeyEventToFepL( 'c' );
    _LIT( KFilterTest20, 
        "CAknListBoxFilterItems::DeferredSendKeyEventToFepL" );
    AssertNotNullL( item, KFilterTest20 );
    
    item->SetPopup();
    _LIT( KFilterTest22, 
        "CAknListBoxFilterItems::SetPopup" );
    AssertNotNullL( item, KFilterTest22 );
    
    CCoeControl* findBox = item->FindBox();
    _LIT( KFilterTest23, 
        "CAknListBoxFilterItems::FindBox" );
    AssertNotNullL( item, KFilterTest23 );
    
    item->SetListBox( NULL );
    _LIT( KFilterTest24, 
        "CAknListBoxFilterItems::SetListBox" );
    AssertNotNullL( item, KFilterTest24 );
    
    item->SetSearchField( NULL );
    _LIT( KFilterTest25, 
        "CAknListBoxFilterItems::SetSearchField" );
    AssertNotNullL( item, KFilterTest25 );
    
    item->SetModel( NULL );
    _LIT( KFilterTest26, 
        "CAknListBoxFilterItems::SetModel" );
    AssertNotNullL( item, KFilterTest26 );
    
    item->SetView( NULL );
    _LIT( KFilterTest27, 
        "CAknListBoxFilterItems::SetView" );
    AssertNotNullL( item, KFilterTest27 );
        
    CleanupStack::PopAndDestroy( 2 ); // item, search
    }

// ---------------------------------------------------------------------------
// CBCTestUtilitiesCase::TestAknLayoutUtilsL
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesCase::TestAknLayoutUtilsL()
    {    
    TRect parentRect = iContainer->Rect();
    
    CEikEdwin* edwin = new( ELeave ) CEikEdwin();
    CleanupStack::PushL( edwin );
    edwin->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_BCTESTUTIL_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // reader
    
    AknLayoutUtils::SAknLayoutEdwin edwinLayout;
    edwinLayout.iC = 0;
    edwinLayout.iB = 5;
    edwinLayout.iL = 5;
    edwinLayout.iR = 5;    
    edwinLayout.iFont = ELatinPlain12;
    edwinLayout.iJ = ELayoutAlignLeft;
    edwinLayout.iW = 100;
    edwinLayout.iNumberOfLinesShown = 1;
    edwinLayout.iNextLineB = 25;
    AknLayoutUtils::LayoutEdwin( edwin, parentRect, edwinLayout );
    _LIT( KAknLayoutTest1, "AknLayoutUtils::LayoutEdwin with SAknLayoutEdwin" );
    AssertTrueL( ETrue, KAknLayoutTest1 );
    
    AknLayoutUtils::MinimizedEdwinRect( edwin );
    _LIT( KAknLayoutTest2, "AknLayoutUtils::MinimizedEdwinRect" );
    AssertTrueL( ETrue, KAknLayoutTest2 );
    
    CleanupStack::PopAndDestroy( edwin );
    
    CEikNumberEditor* mfne = new( ELeave ) CEikNumberEditor();
    CleanupStack::PushL( mfne );
    mfne->SetContainerWindowL( *iContainer );
    mfne->ConstructL( 0, 10000, 100 );
    
    AknLayoutUtils::SAknLayoutMfne mfneLayout;
    mfneLayout.iFont = ELatinPlain12;
    mfneLayout.iC = 0;
    mfneLayout.iL = 5;
    mfneLayout.iR = 5;
    mfneLayout.iB = 5;
    mfneLayout.iW = 100;
    mfneLayout.iJ = ELayoutAlignLeft;
    AknLayoutUtils::LayoutMfne( mfne, parentRect, mfneLayout );
    _LIT( KAknLayoutTest3, "AknLayoutUtils::LayoutMfne" );
    AssertTrueL( ETrue, KAknLayoutTest3 );
    
    CleanupStack::PopAndDestroy( mfne );
    
    CEikImage* image = new( ELeave ) CEikImage();
    CleanupStack::PushL( image );
    image->SetContainerWindowL( *iContainer );
    iEnv->CreateResourceReaderLC( reader, R_BCTESTUTIL_IMAGE );
    image->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // reader
    
    AknLayoutUtils::SAknLayoutControl imageLayout;
    imageLayout.iC = 0;
    imageLayout.iL = 5;
    imageLayout.iT = 5;
    imageLayout.iR = 5;
    imageLayout.iB = 5;
    imageLayout.iW = 100;
    imageLayout.iH = 50;
    AknLayoutUtils::LayoutImage( image, parentRect, imageLayout );
    _LIT( KAknLayoutTest4, "AknLayoutUtils::LayoutImage" );
    AssertTrueL( ETrue, KAknLayoutTest4 );
    
    CleanupStack::PopAndDestroy( image );
    
    CEikSecretEditor* seced = new( ELeave ) CEikSecretEditor();
    CleanupStack::PushL( seced );
    seced->SetContainerWindowL( *iContainer );
    iEnv->CreateResourceReaderLC( reader, R_BCTESTUTIL_SECED );
    seced->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // reader
        
    AknLayoutUtils::LayoutSecretEditor( seced, parentRect, mfneLayout );
    _LIT( KAknLayoutTest5, "AknLayoutUtils::LayoutSecretEditor" );
    AssertTrueL( ETrue, KAknLayoutTest5 );
    
    CleanupStack::PopAndDestroy( seced );
    
    TPoint pt;
    TBool result = AknLayoutUtils::LayoutMetricsPosition( 
        AknLayoutUtils::EMainPane, pt );
    _LIT( KAknLayoutTest6, "AknLayoutUtils::LayoutMetricsPosition" );
    AssertTrueL( ETrue, KAknLayoutTest6 );
    
    TSize size;
    result = AknLayoutUtils::LayoutMetricsSize( 
        AknLayoutUtils::EMainPane, size );
    _LIT( KAknLayoutTest7, "AknLayoutUtils::LayoutMetricsSize" );
    AssertTrueL( ETrue, KAknLayoutTest7 );
    
    result = AknLayoutUtils::ScalableLayoutInterfaceAvailable();
    _LIT( KAknLayoutTest8, "AknLayoutUtils::ScalableLayoutInterfaceAvailable" );
    AssertTrueL( ETrue, KAknLayoutTest8 );
    
    EVariantFlag variant = AknLayoutUtils::Variant();
    _LIT( KAknLayoutTest9, "AknLayoutUtils::Variant" );
    AssertTrueL( ETrue, KAknLayoutTest9 );
    
    ESubVariantFlag subVariant = AknLayoutUtils::SubVariant();
    _LIT( KAknLayoutTest10, "AknLayoutUtils::SubVariant" );
    AssertTrueL( ETrue, KAknLayoutTest10 );
    
    AknLayoutUtils::TAknCbaLocation cbaLocation = 
        AknLayoutUtils::CbaLocation();
    _LIT( KAknLayoutTest11, "AknLayoutUtils::CbaLocation" );
    AssertTrueL( ETrue, KAknLayoutTest11 );
    
    TAknFontSpecification fontSpec( ELatinPlain12 );
    CAknLayoutFont* layoutFont = AknLayoutUtils::
        CreateLayoutFontFromSpecificationL( fontSpec );        
    _LIT( KAknLayoutTest12, "AknLayoutUtils::CreateLayoutFontFromSpecificationL" );
    delete layoutFont;
    AssertTrueL( ETrue, KAknLayoutTest12 );
        
    TTypeface typeFace;
    layoutFont = AknLayoutUtils::CreateLayoutFontFromSpecificationL( 
        typeFace, fontSpec );
    _LIT( KAknLayoutTest13, "AknLayoutUtils::CreateLayoutFontFromSpecificationL with TTypeFace" );
    delete layoutFont;
    AssertTrueL( ETrue, KAknLayoutTest13 );
    
    TFontSpec spec;
    TInt cursorAscent = AknLayoutUtils::CursorAscentFromFont( spec );
    _LIT( KAknLayoutTest14, "AknLayoutUtils::CursorAscentFromFont" );
    AssertTrueL( ETrue, KAknLayoutTest14 );
    
    TInt first;
    TInt second;
    AknLayoutUtils::CursorExtensionsFromFont( spec, first, second );
    _LIT( KAknLayoutTest15, "AknLayoutUtils::CursorExtensionsFromFont" );
    AssertTrueL( ETrue, KAknLayoutTest15 );
    
    TInt height = AknLayoutUtils::CursorHeightFromFont( spec );
    _LIT( KAknLayoutTest16, "AknLayoutUtils::CursorHeightFromFont" );
    AssertTrueL( ETrue, KAknLayoutTest16 );
    
    height = AknLayoutUtils::CursorWidthFromFont( spec );
    _LIT( KAknLayoutTest17, "AknLayoutUtils::CursorWidthFromFont" );
    AssertTrueL( ETrue, KAknLayoutTest17 );
    
    height = AknLayoutUtils::HighlightLeftPixelsFromFont( spec );
    _LIT( KAknLayoutTest18, "AknLayoutUtils::HighlightLeftPixelsFromFont" );
    AssertTrueL( ETrue, KAknLayoutTest18 );
    
    height = AknLayoutUtils::HighlightRightPixelsFromFont( spec );
    _LIT( KAknLayoutTest19, "AknLayoutUtils::HighlightRightPixelsFromFont" );
    AssertTrueL( ETrue, KAknLayoutTest19 );
    
    TAknLayoutText layoutText;
            
    layoutText.LayoutText( parentRect, mfneLayout );
    _LIT( KLayoutTextTest2, "TAknLayoutText::LayoutText with SAknLayoutText" );
    AssertTrueL( ETrue, KLayoutTextTest2 );
    
    TAknLayoutRect layoutRect;
    
    layoutRect.LayoutRect( parentRect, imageLayout );
    _LIT( KLayoutRectTest1, "TAknLayoutText::LayoutRect with SAknLayoutRect" );
    AssertTrueL( ETrue, KLayoutRectTest1 );
    
    TRect rect = iContainer->Rect();
    layoutText.LayoutText( rect, R_BCTESTUTIL_LAYOUT_TEXT );
    _LIT( KLayoutTextTest1, "TAknLayoutText::LayoutText with resource Id" );
    AssertTrueL( ETrue, KLayoutTextTest1 );
            
    iContainer->ActivateGc();
    CWindowGc& gc = iEnv->SystemGc();
            
    _LIT( KDrawText, "DrawText" );
    layoutText.DrawText( gc, KDrawText, ETrue );
    _LIT( KLayoutTextTest4, "TAknLayoutText::DrawText" );
    AssertTrueL( ETrue, KLayoutTextTest4 );
            
    layoutText.DrawText( gc, KDrawText, ETrue, KRgbBlack );
    _LIT( KLayoutTextTest5, "TAknLayoutText::DrawText with color" );
    AssertTrueL( ETrue, KLayoutTextTest5 );
        
    layoutRect.LayoutRect( rect, R_BCTESTUTIL_LAYOUT_RECT );
    _LIT( KLayoutRectTest2, "TAknLayoutText::LayoutRect with resource Id" );
    AssertTrueL( ETrue, KLayoutRectTest2 );
        
    layoutRect.DrawRect( gc );
    _LIT( KLayoutRectTest3, "TAknLayoutText::DrawRect" );
    AssertTrueL( ETrue, KLayoutRectTest3 );
        
    layoutRect.DrawOutLineRect( gc );
    _LIT( KLayoutRectTest4, "TAknLayoutText::DrawOutLineRect" );
    AssertTrueL( ETrue, KLayoutRectTest4 );
        
    CFbsBitmap* bitmap = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bitmap );
    CFbsBitmap* mask = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( mask );
                
    layoutRect.DrawImage( gc, bitmap, mask );
        
    CleanupStack::PopAndDestroy( mask );
    CleanupStack::PopAndDestroy( bitmap ); 
    
    iContainer->DeactivateGc();   
    }
    
// ---------------------------------------------------------------------------
// CBCTestUtilitiesCase::TestOtherAknUtilsL
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesCase::TestOtherAknUtilsL()
    {
    // test API of CListBoxNumbers
    CListBoxNumbers* numbers = new( ELeave ) CListBoxNumbers( iColumnList );
    CleanupStack::PushL( numbers );
    _LIT( KListBoxNumbersTest1, "CListBoxNumbers constructor" );
    AssertNotNullL( numbers, KListBoxNumbersTest1 );
    
    numbers->ConstructL();
    _LIT( KListBoxNumbersTest2, "CListBoxNumbers::ConstructL" );
    AssertNotNullL( numbers, KListBoxNumbersTest2 );
    
    numbers->UpdateL();
    _LIT( KListBoxNumbersTest3, "CListBoxNumbers::UpdateL" );
    AssertNotNullL( numbers, KListBoxNumbersTest3 );
    
    CleanupStack::PopAndDestroy( numbers );
    
    const CFont* font = LatinPlain12();
    _LIT( KFontTest1, "LatinPlain12" );
    AssertNotNullL( numbers, KFontTest1 );
    
    font = LatinBold12();
    _LIT( KFontTest2, "LatinBold12" );
    AssertNotNullL( numbers, KFontTest2 );
    
    font = LatinBold13();
    _LIT( KFontTest3, "LatinBold13" );
    AssertNotNullL( numbers, KFontTest3 );
    
    font = LatinBold16();
    _LIT( KFontTest4, "LatinBold16" );
    AssertNotNullL( numbers, KFontTest4 );
    
    font = LatinBold17();
    _LIT( KFontTest5, "LatinBold17" );
    AssertNotNullL( numbers, KFontTest5 );
    
    font = LatinBold19();
    _LIT( KFontTest6, "LatinBold19" );
    AssertNotNullL( numbers, KFontTest6 );
    
    font = NumberPlain5();
    _LIT( KFontTest7, "NumberPlain5" );
    AssertNotNullL( numbers, KFontTest7 );
    
    font = ClockBold30();
    _LIT( KFontTest8, "ClockBold30" );
    AssertNotNullL( numbers, KFontTest8 );
    
    font = LatinClock14();
    _LIT( KFontTest9, "LatinClock14" );
    AssertNotNullL( numbers, KFontTest9 );
    
    _LIT( KFilePath, "bctestutilities.exe" );
    TBuf<KBufferSize> filename( KFilePath );
    TInt result = CompleteWithAppPath( filename );
    _LIT( KAknUtilTest1, "CompleteWithAppPath" );
    AssertNotNullL( numbers, KAknUtilTest1 );
    
    TInt language = DefaultInputLanguageFromUILanguage( ELangAmerican );
    _LIT( KAknUtilTest2, "DefaultInputLanguageFromUILanguage" );
    AssertNotNullL( numbers, KAknUtilTest2 );
    
    CAknIconArray* iconArray = new( ELeave ) CAknIconArray( 2 );
    CleanupStack::PushL( iconArray );    
    iconArray->ConstructFromResourceL( R_BCTESTUTIL_ICONARRAY );
    _LIT( KIconArrayTest1, "CAknIconArray::ConstructFromResourceL with resource Id" );
    AssertTrueL( ETrue, KIconArrayTest1 );
    CleanupStack::PopAndDestroy( iconArray );
    
    iconArray = new( ELeave ) CAknIconArray( 2 );
    CleanupStack::PushL( iconArray );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_BCTESTUTIL_ICONARRAY );
    iconArray->ConstructFromResourceL( reader );
    _LIT( KIconArrayTest2, "CAknIconArray::ConstructFromResourceL with resource reader" );
    AssertTrueL( ETrue, KIconArrayTest2 );
    CleanupStack::PopAndDestroy(); // reader
    CleanupStack::PopAndDestroy( iconArray );
    }
    
// ---------------------------------------------------------------------------
// CBCTestUtilitiesCase::TestAknDrawL
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesCase::TestAknDrawL()
    {        
    iContainer->ActivateGc();
    CWindowGc& gc = iEnv->SystemGc();
    
    TRect rect = iContainer->Rect();
    _LIT( KEmptyListText, "Empty List\nNo Data" );
    TPtrC emptyText( KEmptyListText ); 
    
    AknDraw::DrawEmptyList( rect, gc, emptyText );
    _LIT( KAknDrawTest1, "AknDraw::DrawEmptyList" );
    AssertTrueL( ETrue, KAknDrawTest1 );
    
    AknDraw::DrawEmptyListForSettingPage( rect, gc, emptyText );
    _LIT( KAknDrawTest2, "AknDraw::DrawEmptyListForSettingPage" );
    AssertTrueL( ETrue, KAknDrawTest2 );
    
    AknDraw::DrawEmptyListWithFind( rect, gc, emptyText );
    _LIT( KAknDrawTest3, "AknDraw::DrawEmptyListWithFind" );
    AssertTrueL( ETrue, KAknDrawTest3 );
    
    AknDraw::DrawEmptyListHeading( rect, gc, emptyText );
    _LIT( KAknDrawTest4, "AknDraw::DrawEmptyListHeading" );
    AssertTrueL( ETrue, KAknDrawTest4 );
        
    TAknLayoutRect cover;        
    TAknLayoutRect secondShadow;
    TAknLayoutRect firstShadow;
    TAknLayoutRect outlineFrame;
    TAknLayoutRect insideArea;
    
    AknLayoutUtils::SAknLayoutRect layoutRect;
    layoutRect.iC = 0;
    layoutRect.iL = 5;
    layoutRect.iT = 5;
    layoutRect.iR = 65;
    layoutRect.iB = 35;
    layoutRect.iW = 60;
    layoutRect.iH = 30;
    cover.LayoutRect( rect, layoutRect );
    firstShadow.LayoutRect( rect, layoutRect );
    secondShadow.LayoutRect( rect, layoutRect );
    outlineFrame.LayoutRect( rect, layoutRect );
    insideArea.LayoutRect( rect, layoutRect );
    
    AknDraw::DrawWindowShadow( gc, cover, secondShadow, firstShadow, 
        outlineFrame, insideArea );
    _LIT( KAknDrawTest5, "AknDraw::DrawWindowShadow" );
    AssertTrueL( ETrue, KAknDrawTest5 );
    
    AknDraw::DrawEmptyListImpl( rect, gc, emptyText, 
        R_BCTESTUTIL_LAYOUT_TEXT, R_BCTESTUTIL_LAYOUT_TEXT ); 
    _LIT( KAknDrawTest6, "AknDraw::DrawEmptyListImpl" );
    AssertTrueL( ETrue, KAknDrawTest6 );
    
    AknDrawWithSkins::DrawEmptyList( rect, gc, emptyText, iContainer );
    _LIT( KAknDrawSkinTest1, "AknDrawWithSkins::DrawEmptyList" );
    AssertTrueL( ETrue, KAknDrawSkinTest1 );
    
    AknDrawWithSkins::DrawEmptyListForSettingPage( rect, gc, emptyText, 
        iContainer );
    _LIT( KAknDrawSkinTest2, "AknDrawWithSkins::DrawEmptyListForSettingPage" );
    AssertTrueL( ETrue, KAknDrawSkinTest2 );
    
    CColumnListBoxItemDrawer *itemDrawer = 
        static_cast<CColumnListBoxItemDrawer*>( iColumnList->ItemDrawer() );
    AknDrawWithSkins::DrawEmptyListWithFind( rect, gc, emptyText, 
        itemDrawer->ColumnData()->Control() );
    _LIT( KAknDrawSkinTest3, "AknDrawWithSkins::DrawEmptyListWithFind" );
    AssertTrueL( ETrue, KAknDrawSkinTest3 );
    
    AknDrawWithSkins::DrawEmptyListHeading( rect, gc, emptyText, 
        iContainer );
    _LIT( KAknDrawSkinTest4, "AknDrawWithSkins::DrawEmptyListHeading" );
    AssertTrueL( ETrue, KAknDrawSkinTest4 );
    
    AknDrawWithSkins::DrawWindowShadow( gc, cover, secondShadow, 
        firstShadow, outlineFrame, insideArea, iContainer );
    _LIT( KAknDrawSkinTest5, "AknDrawWithSkins::DrawWindowShadow" );
    AssertTrueL( ETrue, KAknDrawSkinTest5 );
    
    iContainer->DeactivateGc();
    }       
    
// ---------------------------------------------------------------------------
// Test AknBidiTextUtils
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesCase::TestAknBidiTextUtilsL()
    {
    TBuf<KBufferSize> logicalText( KLongStr );
    const CFont* font = iEnv->NormalFont();
    
    TBool bret = AknBidiTextUtils::ConvertToVisualAndClipL( logicalText, 
        *font, 100, 50 );
    _LIT( KBidiTextTest1, "AknBidiTextUtils::ConvertToVisualAndClipL" );
    AssertTrueL( ETrue, KBidiTextTest1 );
    
    AknBidiTextUtils::PrepareRunInfoArray( logicalText );
    _LIT( KBidiTextTest2, "AknBidiTextUtils::PrepareRunInfoArray" );
    AssertTrueL( ETrue, KBidiTextTest2 );
    
    CArrayFixFlat<TInt>* lineArray = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( lineArray );
    lineArray->AppendL( 20 );
    lineArray->AppendL( 30 );
    
    CArrayFixFlat<TPtrC>* wrapArray = new( ELeave ) 
        CArrayFixFlat<TPtrC>( 2 );
    CleanupStack::PushL( wrapArray );
    
    AknBidiTextUtils::ConvertToVisualAndWrapToArrayL( logicalText, 
        *lineArray, *font, *wrapArray, ETrue );
    _LIT( KBidiTextTest3, "AknBidiTextUtils::ConvertToVisualAndWrapToArrayL with lineWidthArray" );
    AssertTrueL( ETrue, KBidiTextTest3 );
    wrapArray->Reset();
    
    TInt lineWidth = 30;
    HBufC* buf = AknBidiTextUtils::ConvertToVisualAndWrapToArrayL( logicalText, 
        lineWidth, *font, *wrapArray );
    delete buf;
    _LIT( KBidiTextTest4, "AknBidiTextUtils::ConvertToVisualAndWrapToArrayL" );
    AssertTrueL( ETrue, KBidiTextTest4 );
    wrapArray->Reset();
        
    logicalText.Copy( KChopText );
    AknBidiTextUtils::ConvertToVisualAndChopToArrayL( logicalText, 
        *lineArray, *font, *wrapArray );
    _LIT( KBidiTextTest5, "AknBidiTextUtils::ConvertToVisualAndChopToArrayL with lineWidthArray" );
    AssertTrueL( ETrue, KBidiTextTest5 );
    
    buf = AknBidiTextUtils::ConvertToVisualAndChopToArrayL( logicalText, 
        lineWidth, *font, *wrapArray );
    delete buf;
    _LIT( KBidiTextTest6, "AknBidiTextUtils::ConvertToVisualAndChopToArrayL" );
    AssertTrueL( ETrue, KBidiTextTest6 );
    
    buf = AknBidiTextUtils::ConvertToVisualAndWrapToArrayWholeTextL(
        logicalText, *lineArray, *font, *wrapArray );
    delete buf;
    _LIT( KBidiTextTest7, 
        "AknBidiTextUtils::ConvertToVisualAndWrapToArrayWholeTextL" );    
    AssertTrueL( ETrue, KBidiTextTest7 );  
    
    CleanupStack::PopAndDestroy( wrapArray );
    CleanupStack::PopAndDestroy( lineArray );  
    }

// ---------------------------------------------------------------------------
// Test CAknEnv
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesCase::TestAknEnvL()
    {
    CAknEnv* aknEnv = CAknEnv::Static();
       
    aknEnv->ExecuteEmptyPopupListL();
    _LIT( KAknEnv1, "CAknEnv::ExecuteEmptyPopupListL with one parameter" );
    AssertTrueL( ETrue, KAknEnv1 );
    
    _LIT( KEmptyText, "Empty list" );    
    aknEnv->ExecuteEmptyPopupListL( &KEmptyText, &KEmptyText );
    _LIT( KAknEnv2, "CAknEnv::ExecuteEmptyPopupListL with three parameter" );
    AssertTrueL( ETrue, KAknEnv2 );
    
    aknEnv->EditingStateIndicator();
    _LIT( KAknEnv3, "CAknEnv::EditingStateIndicator" );
    AssertTrueL( ETrue, KAknEnv3 );
    
    aknEnv->AknLayout();
    _LIT( KAknEnv4, "CAknEnv::AknLayout" );
    AssertTrueL( ETrue, KAknEnv4 );
    
    TBool load = aknEnv->LoadAknLayoutL();
    _LIT( KAknEnv5, "CAknEnv::LoadAknLayoutL" );
    AssertTrueL( ETrue, KAknEnv5 );
    
    aknEnv->SplitViewActive();
    _LIT( KAknEnv6, "CAknEnv::SplitViewActive" );
    AssertTrueL( ETrue, KAknEnv6 );
    
    aknEnv->CreateCbaObserverL( CEikButtonGroupContainer::Current(), 
        iColumnList );
    _LIT( KAknEnv7, "CAknEnv::CreateCbaObserverL" );
    AssertTrueL( ETrue, KAknEnv7 );    
    aknEnv->RemoveCbaObserver();
    
    CAknAppUi* appUi = aknEnv->AppWithShutterRunning();
    _LIT( KAknEnv8, "CAknEnv::AppWithShutterRunning" );
    AssertTrueL( ETrue, KAknEnv8 );
    
    TAknUiZoom uiZoom;
    aknEnv->GetCurrentGlobalUiZoom( uiZoom );
    _LIT( KAknEnv9, "CAknEnv::GetCurrentGlobalUiZoom" );
    AssertTrueL( ETrue, KAknEnv9 );
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// HandleControlEventL
// ---------------------------------------------------------------------------
//
void TBCTestControlObserver::HandleControlEventL( CCoeControl*, TCoeEvent )
    {    
    }
