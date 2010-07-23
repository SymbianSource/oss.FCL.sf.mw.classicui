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
* Description:  test functions in aknutils.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <testsdkuifwutil.rsg>
#include <eikclb.h>
#include <eikfrlbd.h>
#include <e32const.h>
#include <akndialog.h>
#include <aknlists.h>
#include <eikclbd.h>
#include <aknsfld.h>
#include <aknlayout2def.h>
#include <aknlayout2scalabledef.h>
#include <eikmfne.h>
#include <eikseced.h>
#include <aknfontspecification.h>
#include <akniconutils.h>
#include <avkon.mbg>
#include <gulfont.h>

#include "testsdkuifwutil.h"

// CONSTANTS
const TInt KArraySize = 10;
const TInt KBufSize = 64;
const TInt KGeneralWidth = 50;
const TInt KSearchFieldMaxLength = 20;
_LIT( KTextExample, "textexample" );
_LIT( KBitmapFile, "Z:\\resource\\apps\\avkon2.mbm" );

// FORWARD DECLARATIONS
// This class only for test, not any value.
class CScrollBarObserver : public CBase, public MEikScrollBarObserver
    {
public:
    // From MEikScrollBarObserver
    void HandleScrollEventL( CEikScrollBar* /*aScrollBar*/, TEikScrollEvent /*aEventType*/ ){}
    };

// This class only for test, not any value.
class CControlObserver : public CBase, public MCoeControlObserver
    {
public:
    // From MCoeControlObserver
    void HandleControlEventL( CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/ ){}
    };
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknTextUtilsClipToFitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsClipToFitL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    const CFont& font = *(iEnv->TitleFont());
    TBool result;
    TBuf<KBufSize> buf( KTextExample );
    switch ( num )
        {
        case ECaseZero:
            {
            result = AknTextUtils::ClipToFit( buf, font, KGeneralWidth);
            break;
            }
        case ECaseOne:
            {
            TInt itemindex = 0;   
            TInt columnnumber = 0;
            CEikColumnListBox* collist = new ( ELeave ) CAknSingleStyleListBox;
            CleanupStack::PushL( collist );
            collist->SetContainerWindowL( *iContainer );
            iContainer->SetComponentControlL( collist );
            TResourceReader reader;
            iEnv->CreateResourceReaderLC( reader, R_SINGLE_LISTBOX );
            collist->ConstructFromResourceL( reader );
            CleanupStack::PopAndDestroy();
            CColumnListBoxData *data = collist->ItemDrawer()->ColumnData();
            data->SetColumnFontL( columnnumber, &font );
            result = AknTextUtils::ClipToFit( buf, AknTextUtils::EClipFromEnd, collist,
                    itemindex, columnnumber );
            CleanupStack::PopAndDestroy( collist );
            break;
            }
        case ECaseTwo:
            {
            TInt itemindex = 0;   
            TInt subcellnumber = 0;
            CEikFormattedCellListBox* celllist = new ( ELeave ) CEikFormattedCellListBox;
            CleanupStack::PushL( celllist );
            celllist->SetContainerWindowL( * iContainer );
            
            TResourceReader reader;
            iEnv->CreateResourceReaderLC( reader, R_DOUBLE_LISTBOX );
            celllist->ConstructFromResourceL( reader );
            CleanupStack::PopAndDestroy();
            CFormattedCellListBoxData* formatData = celllist->ItemDrawer()->FormattedCellData();
            formatData->SetSubCellFontL( subcellnumber, &font );
            result = AknTextUtils::ClipToFit( buf, AknTextUtils::EClipFromEnd, celllist,
                    itemindex, subcellnumber );
            CleanupStack::PopAndDestroy( celllist );
            break;
            }
        default:
            {
            return KErrNotSupported;
            }
        }
    STIF_ASSERT_TRUE( result );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAKnTextUtilsWrapToArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsWrapToArrayL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    TBuf<KBufSize> buf( KTextExample );
    CArrayFix<TPtrC>* wraparray = new ( ELeave ) CArrayFixFlat<TPtrC>( KArraySize );
    CleanupStack::PushL( wraparray );
    const CFont& font = *(iEnv->TitleFont());
    switch ( num )
        {
        case ECaseZero:
            {
            AknTextUtils::WrapToArrayL( buf, KGeneralWidth, font, *wraparray );
            break;
            }
        case ECaseOne:
            {
            CArrayFix<TInt>* widtharray = new ( ELeave ) CArrayFixFlat<TInt>( KArraySize );
            CleanupStack::PushL( widtharray );
            AknTextUtils::WrapToArrayL( buf, *widtharray, font, *wraparray );
            CleanupStack::PopAndDestroy( widtharray );
            break;
            }
        default:
            {
            CleanupStack::PopAndDestroy( wraparray );
            return KErrNotSupported;
            }
        }
    
    CleanupStack::PopAndDestroy( wraparray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknTextUtilsWrapToArrayAndClipL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsWrapToArrayAndClipL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KTextExample );
    CArrayFix<TPtrC>* wraparray = new ( ELeave ) CArrayFixFlat<TPtrC>( KArraySize );
    CleanupStack::PushL( wraparray );
    const CFont& font = *(iEnv->TitleFont());
    CArrayFix<TInt>* widtharray = new ( ELeave ) CArrayFixFlat<TInt>( KArraySize );
    CleanupStack::PushL( widtharray );
    AknTextUtils::WrapToArrayAndClipL( buf, *widtharray, font, *wraparray );
    
    CleanupStack::PopAndDestroy( widtharray );
    CleanupStack::PopAndDestroy( wraparray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknTextUtilsChopToArrayAndClipL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsChopToArrayAndClipL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    TBuf<KBufSize> buf( KTextExample );
    CArrayFix<TPtrC>* wraparray = new ( ELeave ) CArrayFixFlat<TPtrC>( KArraySize );
    CleanupStack::PushL( wraparray );
    const CFont& font = *(iEnv->TitleFont());
    switch ( num )
        {
        case ECaseZero:
            {
            AknTextUtils::ChopToArrayAndClipL( buf, KGeneralWidth, font, *wraparray );
            break;
            }
        case ECaseOne:
            {
            CArrayFix<TInt>* widtharray = new ( ELeave ) CArrayFixFlat<TInt>( KArraySize );
            CleanupStack::PushL( widtharray );
            AknTextUtils::ChopToArrayAndClipL( buf, *widtharray, font, *wraparray );
            CleanupStack::PopAndDestroy( widtharray );
            break;
            }
        default:
            {
            CleanupStack::PopAndDestroy( wraparray );
            return KErrNotSupported;
            }
        }
    
    CleanupStack::PopAndDestroy( wraparray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknTextUtilsWrapToStringL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsWrapToStringL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KTextExample );
    TBuf<KBufSize> wrapbuf;
    const CFont& font = *(iEnv->TitleFont());
    CArrayFix<TInt>* widtharray = new ( ELeave ) CArrayFixFlat<TInt>( KArraySize );
    CleanupStack::PushL( widtharray );
    AknTextUtils::WrapToStringL( buf, *widtharray, font, wrapbuf );
    
    CleanupStack::PopAndDestroy( widtharray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknTextUtilsWrapToStringAndClipL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsWrapToStringAndClipL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KTextExample );
    TBuf<KBufSize> wrapbuf;
    const CFont& font = *(iEnv->TitleFont());
    CArrayFix<TInt>* widtharray = new ( ELeave ) CArrayFixFlat<TInt>( KArraySize );
    CleanupStack::PushL( widtharray );
    AknTextUtils::WrapToStringAndClipL( buf, *widtharray, font, wrapbuf );
    
    CleanupStack::PopAndDestroy(widtharray);
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknTextUtilsProcessCharacters
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsProcessCharacters( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    TBuf<KBufSize> buf( KTextExample );
    TBuf<KBufSize> charactor;
    charactor.FillZ();
    charactor.Append( ' ' );
    TChar replacechar( 'a' );
    switch ( num )
        {
        case ECaseZero:
            {
            AknTextUtils::StripCharacters( buf, charactor );
            break;
            }
        case ECaseOne:
            {
            AknTextUtils::ReplaceCharacters( buf, charactor, replacechar );
            break;
            }
        case ECaseTwo:
            {
            AknTextUtils::PackWhiteSpaces( buf, charactor );
            break;
            }
        default:
            {
            return KErrNotSupported;
            }
        }
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknTextUtilsLanguageSpecificNumberConversion
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsLanguageSpecificNumberConversion( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KTextExample );
    AknTextUtils::LanguageSpecificNumberConversion( buf );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknTextUtilsConvertDigitsTo
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsConvertDigitsTo( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KTextExample );
    AknTextUtils::ConvertDigitsTo( buf, EDigitTypeAllTypes );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknTextUtilsCurrentScriptDirectionality
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsCurrentScriptDirectionality( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KTextExample );
    AknTextUtils::CurrentScriptDirectionality();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknTextUtilsNumericEditorDigitType
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsNumericEditorDigitType( CStifItemParser& /*aItem*/ )
    {
    AknTextUtils::NumericEditorDigitType();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknTextUtilsDisplayTextLanguageSpecificNumberConversion
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsDisplayTextLanguageSpecificNumberConversion( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KTextExample );
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion( buf );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknTextUtilsTextEditorDigitType
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsTextEditorDigitType( CStifItemParser& /*aItem*/ )
    {
    AknTextUtils::TextEditorDigitType();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknTextUtilsDigitModeQuery
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsDigitModeQuery( CStifItemParser& /*aItem*/ )
    {
    AknTextUtils::DigitModeQuery( AknTextUtils::EDigitModeNumberEditor );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknTextUtilsConvertFileNameL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsConvertFileNameL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KTextExample );
    AknTextUtils::ConvertFileNameL( buf );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknTextUtilsLoadTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsLoadTextL( CStifItemParser& /*aItem*/ )
    {
    TBuf<64> buf;
    AknTextUtils::LoadScalableText( *(CCoeEnv::Static()), 
        R_AKNTEXTUTILS_BUFZERO, buf );
    AknTextUtils::LoadScalableTextL( *(CCoeEnv::Static()), R_AKNTEXTUTILS_BUF );
    AknTextUtils::LoadScalableTextLC( *(CCoeEnv::Static()), R_AKNTEXTUTILS_BUF );
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknTextUtilsClipAccordingScreenOrientationLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsClipAccordingScreenOrientationLCL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KTextExample );
    HBufC* hbuf = HBufC::NewL( KBufSize );
    *hbuf = buf;    
    AknTextUtils::ClipAccordingScreenOrientationLC( *(CCoeEnv::Static()), hbuf );
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknTextUtilsChooseScalableText
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknTextUtilsChooseScalableText( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KTextExample );
    const CFont& font = *(iEnv->TitleFont());
    AknTextUtils::ChooseScalableText( buf, font, KGeneralWidth );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknSelectServHandleSelectionListProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknSelectServHandleSelectionListProcessCommandL( CStifItemParser& /*aItem*/ )
    {
    CEikListBox* list = new ( ELeave ) CEikListBox;
    CleanupStack::PushL( list );
    AknSelectionService::HandleSelectionListProcessCommandL( 0, list );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknSelectServHandleMultiselectionListProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknSelectServHandleMultiselectionListProcessCommandL( CStifItemParser& /*aItem*/ )
    {
    CEikListBox* list = new ( ELeave ) CEikListBox;
    CleanupStack::PushL( list );
    AknSelectionService::HandleMultiselectionListProcessCommandL( 0, list );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknSelectServHandleMarkableListProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknSelectServHandleMarkableListProcessCommandL( CStifItemParser& /*aItem*/ )
    {
    CEikListBox* list = new ( ELeave ) CEikListBox;
    CleanupStack::PushL( list );
    AknSelectionService::HandleMarkableListProcessCommandL( 0, list );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknSelectServHandleMenuListOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknSelectServHandleMenuListOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CEikListBox* list = new ( ELeave ) CAknSingleStyleListBox;
    CleanupStack::PushL( list );
    list->SetContainerWindowL( *iContainer );
    iContainer->SetComponentControlL( list );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_SINGLE_LISTBOX );
    list->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    TKeyEvent keyevent = { EKeyLeftShift, 0, 0, 0 };
    AknSelectionService::HandleMenuListOfferKeyEventL( keyevent, EEventKey, list );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknSelectServHandleMarkableListDynInitMenuPaneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknSelectServHandleMarkableListDynInitMenuPaneL( CStifItemParser& /*aItem*/ )
    {
    CAknDialog* dlg = new( ELeave ) CAknDialog();
    CleanupStack::PushL( dlg );
    CEikMenuPane* menuPane = new( ELeave ) CEikMenuPane( dlg );
    CleanupStack::PushL( menuPane );
    CEikListBox* list = new ( ELeave ) CEikListBox;
    CleanupStack::PushL( list );
    list->SetContainerWindowL( *iContainer );
    iContainer->SetComponentControlL( list );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_SINGLE_LISTBOX );
    list->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    AknSelectionService::HandleMarkableListDynInitMenuPane(
            R_AKNSELECTIONSERVICE_MENUPANE, menuPane, list );
    CleanupStack::PopAndDestroy( 3 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknSelectServHandleMarkableListDynInitMenuItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknSelectServHandleMarkableListDynInitMenuItemL( CStifItemParser& /*aItem*/ )
    {
    CAknDialog* dlg = new( ELeave ) CAknDialog();
    CleanupStack::PushL( dlg );
    CEikMenuPane* menuPane = new( ELeave ) CEikMenuPane( dlg );
    CleanupStack::PushL( menuPane );
    menuPane->ConstructL( NULL, dlg );
    CEikMenuPaneItem::SData item;
    item.iCommandId = 0;
    item.iCascadeId = 0;
    item.iFlags = 0;
    item.iText.Copy( KTextExample );
        
    menuPane->AddMenuItemL( item );
    CEikListBox* list = new ( ELeave ) CEikListBox;
    CleanupStack::PushL( list );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_SINGLE_LISTBOX );
    list->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    AknSelectionService::HandleMarkableListDynInitMenuItem(
            menuPane, list, 0, ETrue );
    CleanupStack::PopAndDestroy( 3 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknSelectServHandleMarkableListUpdateAfterCommandExecutionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknSelectServHandleMarkableListUpdateAfterCommandExecutionL( CStifItemParser& /*aItem*/ )
    {
    CEikListBox* list = new ( ELeave ) CAknSingleNumberStyleListBox;
    CleanupStack::PushL( list );
    list->SetContainerWindowL( *iContainer );
    iContainer->SetComponentControlL( list );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_SINGLE_LISTBOX );
    list->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    AknSelectionService::HandleMarkableListUpdateAfterCommandExecution( list );
    CleanupStack::PopAndDestroy( list );
    // these two methods fail for no view.
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknSelectServHandleItemRemovalAndPositionHighlightL
// -----------------------------------------------------------------------------
// 
TInt CTestSDKUiFwUtil::TestAknSelectServHandleItemRemovalAndPositionHighlightL( CStifItemParser& /*aItem*/ )
    {//!!! crash
    CAknDoubleLargeStyleListBox* list = new ( ELeave ) CAknDoubleLargeStyleListBox;
    CleanupStack::PushL( list );
    list->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_SINGLE_LISTBOX );
    list->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    list->SetCurrentItemIndex( 0 );
    CArrayFixFlat<TInt>* indexArray = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( indexArray );
    indexArray->AppendL( 0 );
    list->SetTopItemIndex( 1 );
    CDesCArray* textArray = static_cast<CDesCArray*>( list->Model()->ItemTextArray() );
    TInt num = textArray->Count();
    textArray->Delete( 0 );
    AknSelectionService::HandleItemRemovalAndPositionHighlightL( list, 0, ETrue );
    list->HandleItemAdditionL();
    list->SetTopItemIndex( 1 );
    AknSelectionService::HandleItemRemovalAndPositionHighlightL( list, 0, *indexArray );
    CleanupStack::PopAndDestroy( indexArray );
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknFindHandleFindPopupProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknFindHandleFindPopupProcessCommandL( CStifItemParser& /*aItem*/ )
    {
    TInt cmd = 0;
    CEikListBox* list = new ( ELeave ) CAknSingleStyleListBox;
    CleanupStack::PushL( list );
    list->SetContainerWindowL( *iContainer );
    iContainer->SetComponentControlL( list );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_SINGLE_LISTBOX );
    list->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    CAknSearchField* searchfield = CAknSearchField::NewL( *iContainer, 
            CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( searchfield );
    AknFind::HandleFindPopupProcessCommandL( cmd, list, searchfield, iContainer );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknFindHandleFindOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknFindHandleFindOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    TBool reflash = ETrue;
    TKeyEvent keyevent = { 'a', 'b', 1, 0 };
    CEikListBox* list = new ( ELeave ) CAknSingleStyleListBox;
    CleanupStack::PushL( list );
    list->SetContainerWindowL( *iContainer );
    iContainer->SetComponentControlL( list );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_SINGLE_LISTBOX );
    list->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    AknFind::HandleFindOfferKeyEventL( keyevent, EEventKey, iContainer, list, NULL, ETrue, reflash );
    
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknFindHandleSizeChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknFindHandleSizeChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikListBox* list = new ( ELeave ) CAknSingleStyleListBox;
    CleanupStack::PushL( list );
    list->SetContainerWindowL( *iContainer );
    iContainer->SetComponentControlL( list );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_SINGLE_LISTBOX );
    list->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    AknFind::HandleFindSizeChanged( iContainer, list, NULL );
    CAknColumnListBox* listbox = static_cast<CAknColumnListBox*>( list );
    AknFind::HandleFixedFindSizeChanged( iContainer, listbox, NULL );
    AknFind::HandlePopupFindSizeChanged( iContainer, list, NULL );
    TAknWindowLineLayout findarea;
    TAknWindowLineLayout listarea;
    TAknWindowLineLayout paraentarea;
    AknFind::HandleFindSizeChangedLayouts( iContainer, list, NULL, findarea, listarea, EFalse, paraentarea );
    
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknFindProcessStrL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknFindProcessStrL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> itembuf( KTextExample );
    TBuf<KBufSize> searchbuf( KTextExample );
    HBufC* hbuf = HBufC::NewL( KBufSize );
    CleanupStack::PushL( hbuf );
    *hbuf = itembuf;
    TChar ch( 'a' );
    AknFind::IsFindMatch( itembuf, searchbuf );
    AknFind::IsFindWordSeparator( ch );
    AknFind::IsAdaptiveFindMatch( itembuf, searchbuf, hbuf );
    AknFind::UpdateNextCharsFromString( hbuf,itembuf );
    AknFind::UpdateItemTextAccordingToFlag( itembuf, 0, searchbuf );
    CleanupStack::PopAndDestroy( hbuf );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknFindConstructEditingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknFindConstructEditingL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    AknEditUtils::ConstructEditingL( edwin, R_AKNEDITUTILS_EDWIN );
    CleanupStack::PopAndDestroy( edwin );
    edwin = NULL;
    edwin = new( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_AKNEDITUTILS_EDWIN );
    AknEditUtils::ConstructEditingL( edwin, reader );
    CleanupStack::PopAndDestroy( 2 );
    edwin = NULL;
    edwin = new( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    AknEditUtils::SAknEditorParameters para;
    para.iEditingSpace = 1;
    para.iEditingWindow = 1;
    para.iCharacterCase = 1;
    para.iJustification = 1;
    para.iAllowedToMoveInsertionPoint = ETrue;
    para.iCursorYesNo = ETrue;
    para.iOverflowYesNo = ETrue;
    AknEditUtils::ConstructEditingL( edwin, para );
    CleanupStack::PopAndDestroy( edwin );
    edwin = NULL;
    edwin = new( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    AknEditUtils::ConstructEditingL( edwin, 1, 1, 1, 1, ETrue, ETrue, ETrue );
    CleanupStack::PopAndDestroy( edwin );
    edwin = NULL;
    edwin = new( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    AknEditUtils::ConstructEditingL( edwin, 1, 1, 1, 1, ETrue, ETrue, ETrue, EFalse );
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestCListBoxNumbersL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestCListBoxNumbersL( CStifItemParser& /*aItem*/ )
    {
    CEikColumnListBox* collist = new ( ELeave ) CAknSingleStyleListBox;
    CleanupStack::PushL( collist );
    collist->SetContainerWindowL( *iContainer );
    iContainer->SetComponentControlL( collist );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_SINGLE_LISTBOX );
    collist->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    CListBoxNumbers* numberlist = new ( ELeave ) CListBoxNumbers( collist );
    CleanupStack::PushL( numberlist );
    numberlist->ConstructL();
    numberlist->UpdateL();
    CleanupStack::PopAndDestroy( numberlist );
    CleanupStack::PopAndDestroy( collist );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestFilterTextListBoxModelProcessFilterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestFilterTextListBoxModelProcessFilterL( CStifItemParser& /*aItem*/ )
    {
    CEikListBox* celllist = new ( ELeave ) CAknSingleNumberStyleListBox;
    CleanupStack::PushL( celllist );
    celllist->SetContainerWindowL( * iContainer );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_DOUBLE_LISTBOX );
    celllist->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    CAknSearchField* search = CAknSearchField::NewL( *iContainer,
        CAknSearchField::ESearch, NULL, 10 );
    CleanupStack::PushL( search );
    CAknFilteredTextListBoxModel* model = 
        static_cast<CAknFilteredTextListBoxModel*>( celllist->Model() );
    model->CreateFilterL( celllist, search );
    model->Filter();
    model->RemoveFilter();
    CleanupStack::PopAndDestroy( search );
    CleanupStack::PopAndDestroy( celllist );
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestFilterTextListBoxModelParaInfoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestFilterTextListBoxModelParaInfoL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* celllist = new ( ELeave ) CEikFormattedCellListBox;
    CleanupStack::PushL( celllist );
    celllist->SetContainerWindowL( * iContainer );
    
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_DOUBLE_LISTBOX );
    celllist->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CAknFilteredTextListBoxModel* model = 
        static_cast<CAknFilteredTextListBoxModel*>( celllist->Model() );
    model->ItemText( 0 );
    model->NumberOfItems();
    model->MatchableTextArray();
    
    CleanupStack::PopAndDestroy( celllist );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestCAknListBoxFilterItemsConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestCAknListBoxFilterItemsConstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* celllist = new ( ELeave ) CEikFormattedCellListBox;
    CleanupStack::PushL( celllist );
    celllist->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_DOUBLE_LISTBOX );
    celllist->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CAknSearchField* search = CAknSearchField::NewL( *iContainer, 
            CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( search );
    
    CAknFilteredTextListBoxModel* model = 
            static_cast<CAknFilteredTextListBoxModel*>( celllist->Model() );
            
    CAknListBoxFilterItems* item = new( ELeave ) CAknListBoxFilterItems(
            celllist, search, model, celllist->View() );
    CleanupStack::PushL( item );
    
    STIF_ASSERT_NOT_NULL( item );
    
    CleanupStack::PopAndDestroy( 3 );
    return KErrNone;
    }



// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestCAknListBoxFilterItemsConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestCAknListBoxFilterItemsConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* celllist = new ( ELeave ) CEikFormattedCellListBox;
    CleanupStack::PushL( celllist );
    celllist->SetContainerWindowL( * iContainer );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_DOUBLE_LISTBOX );
    celllist->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CAknSearchField* search = CAknSearchField::NewL( *iContainer, 
            CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( search );
    
    CAknFilteredTextListBoxModel* model = 
            static_cast<CAknFilteredTextListBoxModel*>( celllist->Model() );
            
    CAknListBoxFilterItems* item = new( ELeave ) CAknListBoxFilterItems(
            celllist, search, model, celllist->View() );
    CleanupStack::PushL( item );
    
    item->ConstructL();
    
    CleanupStack::PopAndDestroy( 3 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestCAknListBoxFilterItemsResetFilteringL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestCAknListBoxFilterItemsResetFilteringL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* celllist = new ( ELeave ) CEikFormattedCellListBox;
    CleanupStack::PushL( celllist );
    celllist->SetContainerWindowL( * iContainer );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_DOUBLE_LISTBOX );
    celllist->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CAknSearchField* search = CAknSearchField::NewL( *iContainer, 
            CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( search );
    
    CAknFilteredTextListBoxModel* model = 
            static_cast<CAknFilteredTextListBoxModel*>( celllist->Model() );
            
    CAknListBoxFilterItems* item = new( ELeave ) CAknListBoxFilterItems(
            celllist, search, model, celllist->View() );
    CleanupStack::PushL( item );
    item->ConstructL();
    item->ResetFilteringL();
    
    CleanupStack::PopAndDestroy( 3 );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestCAknListBoxFilterItemsUpdateCachedDataL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestCAknListBoxFilterItemsUpdateCachedDataL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* celllist = new ( ELeave ) CEikFormattedCellListBox;
    CleanupStack::PushL( celllist );
    celllist->SetContainerWindowL( * iContainer );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_DOUBLE_LISTBOX );
    celllist->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CAknSearchField* search = CAknSearchField::NewL( *iContainer, 
            CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( search );
    
    CAknFilteredTextListBoxModel* model = 
            static_cast<CAknFilteredTextListBoxModel*>( celllist->Model() );
            
    CAknListBoxFilterItems* item = new( ELeave ) CAknListBoxFilterItems(
            celllist, search, model, celllist->View() );
    CleanupStack::PushL( item );
    item->ConstructL();
    item->UpdateCachedDataL();
    
    CleanupStack::PopAndDestroy( 3 );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestCAknListBoxFilterItemsProcessSelectionIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestCAknListBoxFilterItemsProcessSelectionIndexL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* celllist = new ( ELeave ) CEikFormattedCellListBox;
    CleanupStack::PushL( celllist );
    celllist->SetContainerWindowL( * iContainer );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_DOUBLE_LISTBOX );
    celllist->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CAknSearchField* search = CAknSearchField::NewL( *iContainer, 
            CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( search );
    
    CAknFilteredTextListBoxModel* model = 
            static_cast<CAknFilteredTextListBoxModel*>( celllist->Model() );
            
    CAknListBoxFilterItems* item = new( ELeave ) CAknListBoxFilterItems(
            celllist, search, model, celllist->View() );
    CleanupStack::PushL( item );
    item->SetParentControl( iContainer );
    item->ConstructL();
    item->SelectionIndexes();
    item->UpdateSelectionIndexesL();
    item->UpdateSelectionIndexL( 0 );
    
    CleanupStack::PopAndDestroy( 3 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestCAknListBoxFilterItemsFilteredItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestCAknListBoxFilterItemsFilteredItemL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* celllist = new ( ELeave ) CEikFormattedCellListBox;
    CleanupStack::PushL( celllist );
    celllist->SetContainerWindowL( * iContainer );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_DOUBLE_LISTBOX );
    celllist->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CAknSearchField* search = CAknSearchField::NewL( *iContainer, 
            CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( search );
    
    CAknFilteredTextListBoxModel* model = 
            static_cast<CAknFilteredTextListBoxModel*>( celllist->Model() );
            
    CAknListBoxFilterItems* item = new( ELeave ) CAknListBoxFilterItems(
            celllist, search, model, celllist->View() );
    CleanupStack::PushL( item );
    item->SetParentControl( iContainer );
    item->ConstructL();
    item->FilteredNumberOfItems();
    item->FilteredItemIndex( 0 );
    item->NonFilteredNumberOfItems();
    item->VisibleItemIndex( 0 );
    TBufC<KBufSize> buf( KTextExample );
    TPtrC ptrc( buf );
    item->DefaultMatchableItemFromItem( ptrc );
    CleanupStack::PopAndDestroy( 3 );
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestCAknListBoxFilterItemsHandleOfferkeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestCAknListBoxFilterItemsHandleOfferkeyEventL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* celllist = new ( ELeave ) CEikFormattedCellListBox;
    CleanupStack::PushL( celllist );
    celllist->SetContainerWindowL( * iContainer );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_DOUBLE_LISTBOX );
    celllist->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CAknSearchField* search = CAknSearchField::NewL( *iContainer, 
            CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( search );
    
    CAknFilteredTextListBoxModel* model = 
            static_cast<CAknFilteredTextListBoxModel*>( celllist->Model() );
            
    CAknListBoxFilterItems* item = new( ELeave ) CAknListBoxFilterItems(
            celllist, search, model, celllist->View() );
    CleanupStack::PushL( item );
    item->SetParentControl( iContainer );
    item->ConstructL();
    item->HandleOfferkeyEventL();
    
    CleanupStack::PopAndDestroy( 3 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestCAknListBoxFilterItemsHandleItemArrayChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestCAknListBoxFilterItemsHandleItemArrayChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* celllist = new ( ELeave ) CEikFormattedCellListBox;
    CleanupStack::PushL( celllist );
    celllist->SetContainerWindowL( * iContainer );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_DOUBLE_LISTBOX );
    celllist->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CAknSearchField* search = CAknSearchField::NewL( *iContainer, 
            CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( search );
    
    CAknFilteredTextListBoxModel* model = 
            static_cast<CAknFilteredTextListBoxModel*>( celllist->Model() );
            
    CAknListBoxFilterItems* item = new( ELeave ) CAknListBoxFilterItems(
            celllist, search, model, celllist->View() );
    CleanupStack::PushL( item );
    item->SetParentControl( iContainer );
    item->ConstructL();
    item->HandleItemArrayChangeL();
    
    CleanupStack::PopAndDestroy( 3 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestCAknListBoxFilterItemsDoObserverFuncL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestCAknListBoxFilterItemsDoObserverFuncL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* celllist = new ( ELeave ) CEikFormattedCellListBox;
    CleanupStack::PushL( celllist );
    celllist->SetContainerWindowL( * iContainer );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_DOUBLE_LISTBOX );
    celllist->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CAknSearchField* search = CAknSearchField::NewL( *iContainer, 
            CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( search );
    
    CAknFilteredTextListBoxModel* model = 
            static_cast<CAknFilteredTextListBoxModel*>( celllist->Model() );
            
    CAknListBoxFilterItems* item = new( ELeave ) CAknListBoxFilterItems(
            celllist, search, model, celllist->View() );
    CleanupStack::PushL( item );
    item->SetParentControl( iContainer );
    item->ConstructL();
    CControlObserver* ob = new ( ELeave ) CControlObserver;
    CleanupStack::PushL( ob );
    item->SetObserver( ob );
    item->HandleControlEventL( celllist, MCoeControlObserver::EEventRequestCancel );
    CleanupStack::PopAndDestroy( ob );
    CleanupStack::PopAndDestroy( 3 );
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestCAknListBoxFilterItemsDoFuncFromFepL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestCAknListBoxFilterItemsDoFuncFromFepL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* celllist = new ( ELeave ) CEikFormattedCellListBox;
    CleanupStack::PushL( celllist );
    celllist->SetContainerWindowL( * iContainer );
    
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_DOUBLE_LISTBOX );
    celllist->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CAknSearchField* search = CAknSearchField::NewL( *iContainer, 
            CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( search );
    
    CAknFilteredTextListBoxModel* model = 
            static_cast<CAknFilteredTextListBoxModel*>( celllist->Model() );
            
    CAknListBoxFilterItems* item = new( ELeave ) CAknListBoxFilterItems(
            celllist, search, model, celllist->View() );
    CleanupStack::PushL( item );
    item->SetParentControl( iContainer );
    item->ConstructL();
    item->DeferredSendKeyEventToFepL( 0 );
    CleanupStack::PopAndDestroy( 3 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestCAknListBoxFilterItemsSetNewParaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestCAknListBoxFilterItemsSetNewParaL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* celllist = new ( ELeave ) CEikFormattedCellListBox;
    CleanupStack::PushL( celllist );
    celllist->SetContainerWindowL( * iContainer );
    
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_DOUBLE_LISTBOX );
    celllist->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CAknSearchField* search = CAknSearchField::NewL( *iContainer, 
            CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( search );
    
    CAknFilteredTextListBoxModel* model = 
            static_cast<CAknFilteredTextListBoxModel*>( celllist->Model() );
            
    CAknListBoxFilterItems* item = new( ELeave ) CAknListBoxFilterItems(
            celllist, search, model, celllist->View() );
    CleanupStack::PushL( item );
    item->SetParentControl( iContainer );
    item->ConstructL();
    item->SetListBox( celllist );
    item->SetSearchField( search );
    item->SetModel( model );
    item->SetView( celllist->View() );
    CleanupStack::PopAndDestroy( 3 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestCAknListBoxFilterItemsProcessControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestCAknListBoxFilterItemsProcessControlL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* celllist = new ( ELeave ) CEikFormattedCellListBox;
    CleanupStack::PushL( celllist );
    celllist->SetContainerWindowL( * iContainer );
    
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_DOUBLE_LISTBOX );
    celllist->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CAknSearchField* search = CAknSearchField::NewL( *iContainer, 
            CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( search );
    
    CAknFilteredTextListBoxModel* model = 
            static_cast<CAknFilteredTextListBoxModel*>( celllist->Model() );
            
    CAknListBoxFilterItems* item = new( ELeave ) CAknListBoxFilterItems(
            celllist, search, model, celllist->View() );
    CleanupStack::PushL( item );
    item->SetParentControl( iContainer );
    item->ConstructL();
    item->SetPopup();
    item->FindBox();
    CleanupStack::PopAndDestroy( 3 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLAFUtilsReplaceColumn
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLAFUtilsReplaceColumn( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> bufsrc( KTextExample );
    TBuf<KBufSize> bufdst( KTextExample );
    TPtr ptr = bufdst.MidTPtr( 0 );
    TChar ch( 'a' );
    TInt column = 0;
    AknLAFUtils::ReplaceColumn( ptr, &bufsrc, &bufdst, ch, column );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestCAknGenericReaderFuncsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestCAknGenericReaderFuncsL( CStifItemParser& /*aItem*/ )
    {
    CAknGenericReader* reader = new ( ELeave ) CAknGenericReader;
    CleanupStack::PushL( reader );
    reader->ConstructL( R_CAKNGENERICREADER_RESOURCE );
    CleanupStack::PopAndDestroy();
    reader = NULL;
    reader = new ( ELeave ) CAknGenericReader;
    CleanupStack::PushL( reader );
    TResourceReader resreader;
    iEnv->CreateResourceReaderLC( resreader, R_CAKNGENERICREADER_RESOURCE );
    reader->ConstructFromResourceL( resreader );
    CleanupStack::PopAndDestroy();
    reader->GfxItem( 0 );
    reader->TextItem( 0 );
    reader->CmdItem( 0 );
    reader->AreaItem( 0 );
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutLabelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutLabelL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label  = new ( ELeave ) CEikLabel;
    CleanupStack::PushL( label );
    TRect rect( 20, 20, 40, 40 );
    AknLayoutUtils::LayoutLabel( label, rect, R_AKNLAYOUTUTILS_LABEL );
    CleanupStack::PopAndDestroy( label );
    label = NULL;
    
    label  = new ( ELeave ) CEikLabel;
    CleanupStack::PushL( label );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_AKNLAYOUTUTILS_LABEL );
    AknLayoutUtils::LayoutLabel( label, rect, reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( label );
    label = NULL;
    
    label  = new ( ELeave ) CEikLabel;
    CleanupStack::PushL( label );
    AknLayoutUtils::SAknLayoutLabel labellayout = { ELatinBold12, 0, 1, 1, 1, 5, ELayoutAlignCenter, 1, 1 };
    AknLayoutUtils::LayoutLabel( label, rect, labellayout );
    CleanupStack::PopAndDestroy( label );
    label = NULL;
    
    label  = new ( ELeave ) CEikLabel;
    CleanupStack::PushL( label );
    TAknMultiLineTextLayout multxtlayout;
    multxtlayout.iC = 0;
    multxtlayout.il = 1;
    multxtlayout.ir = 1;
    multxtlayout.iB = 1;
    multxtlayout.iW = 5;
    multxtlayout.iJ = ELayoutAlignCenter;
    multxtlayout.iFont = ELatinBold12;
    multxtlayout.iBaselineSkip = 0;
    multxtlayout.iNumberOfLinesShown = 1;
    AknLayoutUtils::LayoutLabel( label, rect, multxtlayout );
    CleanupStack::PopAndDestroy( label );
    label = NULL;
    
    label  = new ( ELeave ) CEikLabel;
    CleanupStack::PushL( label );
    TAknTextLineLayout txtlayout;
    txtlayout.iC = 0;
    txtlayout.il = 1;
    txtlayout.ir = 1;
    txtlayout.iB = 1;
    txtlayout.iW = 5;
    txtlayout.iJ = ELayoutAlignCenter;
    txtlayout.iFont = ELatinBold12;
    txtlayout.iBaselineSkip = 0;
    txtlayout.iNumberOfLinesShown = 1;
    AknLayoutUtils::LayoutLabel( label, rect, txtlayout );
    CleanupStack::PopAndDestroy( label );
    label = NULL;
    
    label  = new ( ELeave ) CEikLabel;
    CleanupStack::PushL( label );
    AknLayoutUtils::LayoutLabel( label, rect, ELatinBold12, 0, 1, 1, 1, 5, ELayoutAlignCenter );
    CleanupStack::PopAndDestroy( label );
    label = NULL;
    
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutEdwinL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutEdwinL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KTextExample );
    TRect rect( 20, 20, 40, 40 );
    CEikEdwin* edwin = new ( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    edwin->ConstructL( 0, 5, 20, 1 );
    edwin->SetTextL( &buf );
    AknLayoutUtils::LayoutEdwin( edwin, rect, R_AKNLAYOUTUTILS_EDWIN );
    CleanupStack::PopAndDestroy( edwin );
    edwin = NULL;
    
    edwin = new ( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    edwin->ConstructL( 0, 5, 20, 1 );
    edwin->SetTextL( &buf );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_AKNLAYOUTUTILS_EDWIN );
    AknLayoutUtils::LayoutEdwin( edwin, rect, reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( edwin );
    edwin = NULL;
    
    edwin = new ( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    edwin->ConstructL( 0, 5, 20, 1 );
    edwin->SetTextL( &buf );
    AknLayoutUtils::SAknLayoutEdwin edwinLayout = { ELatinBold12, 0, 5, 5, 5, 100, ELayoutAlignLeft, 1, 25 };
    AknLayoutUtils::LayoutEdwin( edwin, rect, edwinLayout );
    CleanupStack::PopAndDestroy( edwin );
    edwin = NULL;
    
    edwin = new ( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    edwin->ConstructL( 0, 5, 20, 1 );
    edwin->SetTextL( &buf );
    TAknMultiLineTextLayout multxtlayout;
    multxtlayout.iC = 0;
    multxtlayout.il = 1;
    multxtlayout.ir = 1;
    multxtlayout.iB = 1;
    multxtlayout.iW = 5;
    multxtlayout.iJ = ELayoutAlignCenter;
    multxtlayout.iFont = ELatinBold12;
    multxtlayout.iBaselineSkip = 0;
    multxtlayout.iNumberOfLinesShown = 1;
    AknLayoutUtils::LayoutEdwin( edwin, rect, multxtlayout );
    CleanupStack::PopAndDestroy( edwin );
    edwin = NULL;
    
    edwin = new ( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    edwin->ConstructL( 0, 5, 20, 1 );
    edwin->SetTextL( &buf );
    AknLayoutUtils::LayoutEdwin( edwin, rect, multxtlayout, EAknsCIQsnTextColorsCG1 );
    CleanupStack::PopAndDestroy( edwin );
    edwin = NULL;
    
    edwin = new ( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    edwin->ConstructL( 0, 5, 20, 1 );
    edwin->SetTextL( &buf );
    TAknTextLineLayout txtlayout;
    txtlayout.iC = 0;
    txtlayout.il = 1;
    txtlayout.ir = 1;
    txtlayout.iB = 1;
    txtlayout.iW = 5;
    txtlayout.iJ = ELayoutAlignCenter;
    txtlayout.iFont = ELatinBold12;
    txtlayout.iBaselineSkip = 0;
    txtlayout.iNumberOfLinesShown = 1;
    AknLayoutUtils::LayoutEdwin( edwin, rect, txtlayout );
    CleanupStack::PopAndDestroy( edwin );
    edwin = NULL;
    
    edwin = new ( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    edwin->ConstructL( 0, 5, 20, 1 );
    edwin->SetTextL( &buf );
    AknLayoutUtils::LayoutEdwin( edwin, rect, txtlayout, EAknsCIQsnTextColorsCG1 );
    CleanupStack::PopAndDestroy( edwin );
    edwin = NULL;
    
    edwin = new ( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    edwin->ConstructL( 0, 5, 20, 1 );
    edwin->SetTextL( &buf );
    TInt numofvisibleline = 1;
    AknLayoutUtils::LayoutEdwin( edwin, rect, txtlayout, 1, 1, EAknsCIQsnTextColorsCG1, numofvisibleline );
    CleanupStack::PopAndDestroy( edwin );
    edwin = NULL;
    
    edwin = new ( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    edwin->ConstructL( 0, 5, 20, 1 );
    edwin->SetTextL( &buf);
    AknLayoutUtils::LayoutEdwin( edwin, rect, ELatinBold12, 0, 5, 5, 5, 100, ELayoutAlignLeft, 1, 25 );
    CleanupStack::PopAndDestroy( edwin );
    edwin = NULL;
    
    edwin = new ( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    edwin->ConstructL( 0, 5, 20, 1 );
    edwin->SetTextL( &buf );
    
    AknLayoutUtils::LayoutEdwin( edwin, rect, ELatinBold12, 0, 5, 5, 5, 100, ELayoutAlignLeft, 1, 25, EAknsCIQsnTextColorsCG1 );
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLayoutUtilsMinimizedEdwinRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLayoutUtilsMinimizedEdwinRectL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KTextExample );
    CEikEdwin* edwin = new ( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    edwin->ConstructL( 0, 5, 20, 1 );
    edwin->SetTextL( &buf );
    AknLayoutUtils::MinimizedEdwinRect( edwin );
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    }
    

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutMfneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutMfneL( CStifItemParser& /*aItem*/ )
    {
    TRect rect( 20, 20, 40, 40 );
    CEikNumberEditor* mfne = new( ELeave ) CEikNumberEditor();
    CleanupStack::PushL( mfne );
    mfne->ConstructL( 0, 1000, 100 );
    AknLayoutUtils::LayoutMfne( mfne, rect, R_CEIKMFNE_LAYOUT );
    CleanupStack::PopAndDestroy( mfne );
    mfne = NULL;
    
    mfne = new( ELeave ) CEikNumberEditor();
    CleanupStack::PushL( mfne );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_AKNLAYOUTUTILS_NUMBEREDWIN );
    mfne->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    iEnv->CreateResourceReaderLC( reader, R_CEIKMFNE_LAYOUT );
    AknLayoutUtils::LayoutMfne( mfne, rect, reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( mfne );
    mfne = NULL;
    
    mfne = new( ELeave ) CEikNumberEditor();
    CleanupStack::PushL( mfne );
    mfne->ConstructL( 0, 1000, 100 );
    AknLayoutUtils::SAknLayoutMfne mfneLayout;
    mfneLayout.iFont = ELatinPlain12;
    mfneLayout.iC = 0;
    mfneLayout.iL = 5;
    mfneLayout.iR = 5;
    mfneLayout.iB = 5;
    mfneLayout.iW = 100;
    mfneLayout.iJ = ELayoutAlignLeft;
    AknLayoutUtils::LayoutMfne( mfne, rect, mfneLayout );
    CleanupStack::PopAndDestroy( mfne );
    mfne = NULL;
    
    mfne = new( ELeave ) CEikNumberEditor();
    CleanupStack::PushL( mfne );
    mfne->ConstructL( 0, 1000, 100 );
    TAknTextLineLayout txtlayout;
    txtlayout.iC = 0;
    txtlayout.il = 1;
    txtlayout.ir = 1;
    txtlayout.iB = 1;
    txtlayout.iW = 5;
    txtlayout.iJ = ELayoutAlignCenter;
    txtlayout.iFont = ELatinBold12;
    txtlayout.iBaselineSkip = 0;
    txtlayout.iNumberOfLinesShown = 1;
    AknLayoutUtils::LayoutMfne( mfne, rect, txtlayout );
    CleanupStack::PopAndDestroy( mfne );
    mfne = NULL;
    
    mfne = new( ELeave ) CEikNumberEditor();
    CleanupStack::PushL( mfne );
    mfne->ConstructL( 0, 1000, 100 );
    AknLayoutUtils::LayoutMfne( mfne, rect, ELatinBold12, 0, 1, 1, 1, 5, ELayoutAlignCenter );
    CleanupStack::PopAndDestroy( mfne );
    mfne = NULL;

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutControlL( CStifItemParser& /*aItem*/ )
    {
    TRect rect( 20, 20, 40, 40 );
    CEikNumberEditor* mfne = new( ELeave ) CEikNumberEditor();
    CleanupStack::PushL( mfne );
    mfne->ConstructL( 0, 1000, 100 );
    AknLayoutUtils::LayoutControl( mfne, rect, R_CEIKMFNE_LAYOUT );
    CleanupStack::PopAndDestroy( mfne );
    mfne = NULL;
    
    mfne = new( ELeave ) CEikNumberEditor();
    CleanupStack::PushL( mfne );
    mfne->ConstructL( 0, 1000, 100 );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_CEIKMFNE_LAYOUT );
    AknLayoutUtils::LayoutControl( mfne, rect, reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( mfne );
    mfne = NULL;
    
    mfne = new( ELeave ) CEikNumberEditor();
    CleanupStack::PushL( mfne );
    mfne->ConstructL( 0, 1000, 100 );
    AknLayoutUtils::SAknLayoutRect layoutrect;
    layoutrect.iC = 0;
    layoutrect.iL = 5;
    layoutrect.iT = 5;
    layoutrect.iR = 65;
    layoutrect.iB = 35;
    layoutrect.iW = 60;
    layoutrect.iH = 30;
    AknLayoutUtils::LayoutControl( mfne, rect, layoutrect );
    CleanupStack::PopAndDestroy( mfne );
    mfne = NULL;
    
    mfne = new( ELeave ) CEikNumberEditor();
    CleanupStack::PushL( mfne );
    mfne->ConstructL( 0, 1000, 100 );
    TAknWindowLineLayout windowlinelayout;
    windowlinelayout.iC = 2;
    windowlinelayout.il = 1;
    windowlinelayout.ir = 1;
    windowlinelayout.ib = 1;
    windowlinelayout.iW = 5;
    windowlinelayout.iH = 5;
    AknLayoutUtils::LayoutControl( mfne, rect, windowlinelayout );
    CleanupStack::PopAndDestroy( mfne );
    mfne = NULL;
    
    mfne = new( ELeave ) CEikNumberEditor();
    CleanupStack::PushL( mfne );
    mfne->ConstructL( 0, 1000, 100 );
    AknLayoutUtils::LayoutMfne( mfne, rect, 1, 2, 1, 1, 1, 5, 5 );
    CleanupStack::PopAndDestroy( mfne );
    mfne = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutImageL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutImageL( CStifItemParser& /*aItem*/ )
    {
    TRect rect( 20, 20, 40, 40 );
    CEikImage* image = new ( ELeave ) CEikImage;
    CleanupStack::PushL( image );
    AknLayoutUtils::LayoutImage( image, rect, R_AKNLAYOUTUTILS_IMAGE );
    CleanupStack::PopAndDestroy( image );
    image = NULL;
    
    image = new ( ELeave ) CEikImage;
    CleanupStack::PushL( image );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_AKNLAYOUTUTILS_IMAGE );
    AknLayoutUtils::LayoutImage( image, rect, reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( image );
    image = NULL;
    
    image = new ( ELeave ) CEikImage;
    CleanupStack::PushL( image );
    
    AknLayoutUtils::SAknLayoutRect layoutrect;
    layoutrect.iC = 0;
    layoutrect.iL = 5;
    layoutrect.iT = 5;
    layoutrect.iR = 10;
    layoutrect.iB = 15;
    layoutrect.iW = 15;
    layoutrect.iH = 12;
    AknLayoutUtils::LayoutImage( image, rect, layoutrect );
    CleanupStack::PopAndDestroy( image );
    image = NULL;
    
    image = new ( ELeave ) CEikImage;
    CleanupStack::PushL( image );
    TAknWindowLineLayout windowlinelayout;
    windowlinelayout.iC = 2;
    windowlinelayout.il = 1;
    windowlinelayout.ir = 1;
    windowlinelayout.ib = 1;
    windowlinelayout.iW = 5;
    windowlinelayout.iH = 5;
    AknLayoutUtils::LayoutImage( image, rect, windowlinelayout );
    CleanupStack::PopAndDestroy( image );
    image = NULL;
    
    image = new ( ELeave ) CEikImage;
    CleanupStack::PushL( image );
    AknLayoutUtils::LayoutImage( image, rect, 1, 2, 1, 1, 1, 5, 5 );
    CleanupStack::PopAndDestroy( image );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutSecretEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutSecretEditorL( CStifItemParser& /*aItem*/ )
    {
    TRect rect( 20, 20, 40, 40 );
    CEikSecretEditor* secretedwin = new ( ELeave ) CEikSecretEditor;
    CleanupStack::PushL( secretedwin );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_AKNLAYOUTUTILS_SECRETEDITOR );
    secretedwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    AknLayoutUtils::SAknLayoutText layouttext = { ELatinBold12, 0, 5, 5, 10, 10, 20 };
    AknLayoutUtils::LayoutSecretEditor( secretedwin, rect, layouttext );
    CleanupStack::PopAndDestroy( secretedwin );
    secretedwin = NULL;
    
    secretedwin = new ( ELeave ) CEikSecretEditor;
    CleanupStack::PushL( secretedwin );
    iEnv->CreateResourceReaderLC( reader, R_AKNLAYOUTUTILS_SECRETEDITOR );
    secretedwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    TAknTextLineLayout txtlayout;
    txtlayout.iC = 0;
    txtlayout.il = 1;
    txtlayout.ir = 1;
    txtlayout.iB = 1;
    txtlayout.iW = 5;
    txtlayout.iJ = ELayoutAlignCenter;
    txtlayout.iFont = ELatinBold12;
    txtlayout.iBaselineSkip = 0;
    txtlayout.iNumberOfLinesShown = 1;
    AknLayoutUtils::LayoutSecretEditor( secretedwin, rect, txtlayout );
    CleanupStack::PopAndDestroy( secretedwin );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLayoutUtilsRectFromCoords
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLayoutUtilsRectFromCoords( CStifItemParser& /*aItem*/ )
    {
    TRect rect( 20, 20, 40, 40 );
    const CFont* font = iEnv->NormalFont();
    AknLayoutUtils::TextRectFromCoords( rect, font, 5, 5, 10, 10, 1 );
    AknLayoutUtils::RectFromCoords( rect, 5, 5, 10, 10, 10, 10 );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLayoutUtilsFontFromId
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLayoutUtilsFontFromId( CStifItemParser& /*aItem*/ )
    {
    AknLayoutUtils::FontFromId( 0 );
    AknLayoutUtils::LayoutFontFromId( 0 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLayoutUtilsCreateLayoutFontFromSpecificationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLayoutUtilsCreateLayoutFontFromSpecificationL( CStifItemParser& /*aItem*/ )
    {
    TAknFontSpecification specialfont( 0 );
    AknLayoutUtils::CreateLayoutFontFromSpecificationL( specialfont );
    TTypeface type;
    type.SetAttributes( 0 );
    type.SetIsProportional( ETrue );
    type.SetIsSerif( ETrue );
    type.SetScriptTypeForMetrics( 0 );
    AknLayoutUtils::CreateLayoutFontFromSpecificationL( type, specialfont );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLayoutUtilsSomeSimpleFunc
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLayoutUtilsSomeSimpleFunc( CStifItemParser& /*aItem*/ )
    {
    _LIT(KLatinPlain12,"LatinPlain12");
    AknLayoutUtils::FontFromName( KLatinPlain12 );
    AknLayoutUtils::TextAlignFromId( 0 );
    AknLayoutUtils::GulAlignFromId( 0 );
    TTypeface type;
    type.SetAttributes( 0 );
    type.SetIsProportional( ETrue );
    type.SetIsSerif( ETrue );
    type.SetScriptTypeForMetrics( 0 );
    TFontSpec fonspec( KLatinPlain12, 5 );
    fonspec.iTypeface = type;
    AknLayoutUtils::CursorHeightFromFont( fonspec );
    AknLayoutUtils::CursorWidthFromFont( fonspec );
    AknLayoutUtils::CursorAscentFromFont( fonspec );
    TInt firstex = 1;
    TInt secondex = 1;
    AknLayoutUtils::CursorExtensionsFromFont( fonspec, firstex, secondex );
    AknLayoutUtils::HighlightLeftPixelsFromFont( fonspec );
    AknLayoutUtils::HighlightRightPixelsFromFont( fonspec );
    AknLayoutUtils::LayoutMirrored();
    AknLayoutUtils::Variant();
    AknLayoutUtils::SubVariant();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLayoutUtilsOverrideControlColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLayoutUtilsOverrideControlColorL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KTextExample );
    CEikEdwin* edwin = new ( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_AKNLAYOUTUTILS_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    edwin->SetTextL( &buf );
    AknLayoutUtils::OverrideControlColorL( *edwin, EColorWindowBackground, KRgbBlue );
    CleanupStack::PopAndDestroy( edwin );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLayoutUtilsScrollBarTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLayoutUtilsScrollBarTypeL( CStifItemParser& /*aItem*/ )
    {
    TAknWindowLineLayout windowlinelayout;
    windowlinelayout.iC = 2;
    windowlinelayout.il = 1;
    windowlinelayout.ir = 1;
    windowlinelayout.ib = 1;
    windowlinelayout.iW = 5;
    windowlinelayout.iH = 5;
    CAknAppUiBase* uibase = new ( ELeave ) CAknAppUiBase;
    CleanupStack::PushL( uibase );
    uibase->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    AknLayoutUtils::DefaultScrollBarType( uibase );
    CScrollBarObserver* ob = new ( ELeave ) CScrollBarObserver;
    CleanupStack::PushL( ob );
    CEikScrollBarFrame* scrollbar = new ( ELeave ) CEikScrollBarFrame( iContainer, ob );
    AknLayoutUtils::LayoutVerticalScrollBar( scrollbar, iContainer->ControlRect(), windowlinelayout );
    AknLayoutUtils::LayoutHorizontalScrollBar( scrollbar, iContainer->ControlRect(), windowlinelayout );
    CleanupStack::PopAndDestroy( ob );
    CleanupStack::PopAndDestroy( uibase );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutMetrics
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLayoutUtilsLayoutMetrics( CStifItemParser& /*aItem*/ )
    {
    TRect rect;
    TSize size;
    TPoint point;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, rect );
    AknLayoutUtils::LayoutMetricsSize( AknLayoutUtils::EMainPane, size );
    AknLayoutUtils::LayoutMetricsPosition( AknLayoutUtils::EMainPane, point );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLayoutUtilsScalableLayoutInterfaceAvailable
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLayoutUtilsScalableLayoutInterfaceAvailable( CStifItemParser& /*aItem*/ )
    {
    AknLayoutUtils::ScalableLayoutInterfaceAvailable();
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLayoutUtilsSimpleFunc
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLayoutUtilsSimpleFunc( CStifItemParser& /*aItem*/ )
    {
    AknLayoutUtils::CbaLocation();
    AknLayoutUtils::MainPaneState();
    AknLayoutUtils::PenEnabled();
    AknLayoutUtils::MSKEnabled();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknLayoutUtilsEdwinLine
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknLayoutUtilsEdwinLine( CStifItemParser& /*aItem*/ )
    {
    TInt vertical = 5;
    TInt edwinheight = 10;
    TAknTextLineLayout txtlayout;
    txtlayout.iC = 0;
    txtlayout.il = 1;
    txtlayout.ir = 1;
    txtlayout.iB = 1;
    txtlayout.iW = 5;
    txtlayout.iJ = ELayoutAlignCenter;
    txtlayout.iFont = ELatinBold12;
    txtlayout.iBaselineSkip = 0;
    txtlayout.iNumberOfLinesShown = 1;
    AknLayoutUtils::GetEdwinVerticalPositionAndHeightFromLines( 20, txtlayout, 1, 1, vertical, edwinheight );
    AknLayoutUtils::EdwinLinesWithinHeight( txtlayout, 1, 20, edwinheight );
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestTAknLayoutTextConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestTAknLayoutTextConstructorL( CStifItemParser& /*aItem*/ )
    {
    TAknLayoutText* txt  = new ( ELeave ) TAknLayoutText;
    CleanupStack::PushL( txt );
    STIF_ASSERT_NOT_NULL( txt );
    CleanupStack::PopAndDestroy( txt );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestTAknLayoutTextLayoutTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestTAknLayoutTextLayoutTextL( CStifItemParser& /*aItem*/ )
    {
    TRect rect( 20, 20, 40, 40 );
    TAknLayoutText* txt  = new ( ELeave ) TAknLayoutText;
    CleanupStack::PushL( txt );
    txt->LayoutText( rect, R_CEIKMFNE_LAYOUT );
    CleanupStack::PopAndDestroy( txt );
    txt = NULL;
    
    txt  = new ( ELeave ) TAknLayoutText;
    CleanupStack::PushL( txt );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_CEIKMFNE_LAYOUT );
    txt->LayoutText( rect, reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( txt );
    txt = NULL;
    
    txt  = new ( ELeave ) TAknLayoutText;
    CleanupStack::PushL( txt );
    AknLayoutUtils::SAknLayoutText layouttext = { ELatinBold12, 0, 5, 5, 10, 10, 20 };
    txt->LayoutText( rect, layouttext );
    CleanupStack::PopAndDestroy( txt );
    txt = NULL;
    
    txt  = new ( ELeave ) TAknLayoutText;
    CleanupStack::PushL( txt );
    TAknTextLineLayout txtlayout;
    txtlayout.iC = 0;
    txtlayout.il = 1;
    txtlayout.ir = 1;
    txtlayout.iB = 1;
    txtlayout.iW = 5;
    txtlayout.iJ = ELayoutAlignCenter;
    txtlayout.iFont = ELatinBold12;
    txtlayout.iBaselineSkip = 0;
    txtlayout.iNumberOfLinesShown = 1;
    txt->LayoutText( rect, txtlayout );
    CleanupStack::PopAndDestroy( txt );
    txt = NULL;
    
    txt  = new ( ELeave ) TAknLayoutText;
    CleanupStack::PushL( txt );
    txt->LayoutText( rect, ELatinBold12, 0, 1, 1, 1, 5, ELayoutAlignCenter );
    CleanupStack::PopAndDestroy( txt );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestTAknLayoutTextDrawTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestTAknLayoutTextDrawTextL( CStifItemParser& /*aItem*/ )
    {
    TRect rect( 20, 20, 40, 40 );
    TAknLayoutText* txt  = new ( ELeave ) TAknLayoutText;
    CleanupStack::PushL( txt );
    AknLayoutUtils::SAknLayoutText layouttext = { ELatinBold12, 0, 5, 5, 10, 10, 20 };
    txt->LayoutText( rect, layouttext );
    CWindowGc& gc = iContainer->SystemGc();
    iContainer->ActiveControlGc();
    txt->DrawText( gc, KTextExample );
    txt->DrawText( gc, KTextExample, EFalse );
    txt->DrawText( gc, KTextExample, EFalse, KRgbBlack );
    txt->TextRect();
    CleanupStack::PopAndDestroy( txt );
    iContainer->DeActiveControlGc();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestTAknLayoutRectConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestTAknLayoutRectConstructorL( CStifItemParser& /*aItem*/ )
    {
    TAknLayoutRect* rect  = new ( ELeave ) TAknLayoutRect;
    CleanupStack::PushL( rect );
    STIF_ASSERT_NOT_NULL( rect );
    CleanupStack::PopAndDestroy( rect );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestTAknLayoutRectLayoutRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestTAknLayoutRectLayoutRectL( CStifItemParser& /*aItem*/ )
    {
    TRect rect( 20, 20, 40, 40 );
    TAknLayoutRect* layoutrect  = new ( ELeave ) TAknLayoutRect;
    CleanupStack::PushL( layoutrect );
    layoutrect->LayoutRect( rect, R_CEIKMFNE_LAYOUT );
    CleanupStack::PopAndDestroy( layoutrect );
    layoutrect = NULL;
    
    layoutrect  = new ( ELeave ) TAknLayoutRect;
    CleanupStack::PushL( layoutrect );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_CEIKMFNE_LAYOUT );
    layoutrect->LayoutRect( rect, reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( layoutrect );
    layoutrect = NULL;
    
    layoutrect  = new ( ELeave ) TAknLayoutRect;
    CleanupStack::PushL( layoutrect );
    AknLayoutUtils::SAknLayoutRect layout;
    layout.iC = 0;
    layout.iL = 5;
    layout.iT = 5;
    layout.iR = 10;
    layout.iB = 15;
    layout.iW = 15;
    layout.iH = 12;
    layoutrect->LayoutRect( rect, layout );
    CleanupStack::PopAndDestroy( layoutrect );
    layoutrect = NULL;
    
    layoutrect  = new ( ELeave ) TAknLayoutRect;
    CleanupStack::PushL( layoutrect );
    TAknWindowLineLayout winlinelayout;
    TAknWindowLineLayout windowlinelayout;
    windowlinelayout.iC = 2;
    windowlinelayout.il = 1;
    windowlinelayout.ir = 1;
    windowlinelayout.ib = 1;
    windowlinelayout.iW = 5;
    windowlinelayout.iH = 5;
    layoutrect->LayoutRect( rect, windowlinelayout );
    CleanupStack::PopAndDestroy( layoutrect );
    layoutrect = NULL;
    
    layoutrect  = new ( ELeave ) TAknLayoutRect;
    CleanupStack::PushL( layoutrect );
    layoutrect->LayoutRect( rect, ELatinBold12, 0, 1, 1, 1, 5, ELayoutAlignCenter );
    CleanupStack::PopAndDestroy( layoutrect );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestTAknLayoutRectSimpleFuncL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestTAknLayoutRectSimpleFuncL( CStifItemParser& /*aItem*/ )
    {
    TRect rect( 20, 20, 40, 40 );
    TAknLayoutRect* layoutrect  = new ( ELeave ) TAknLayoutRect;
    CleanupStack::PushL( layoutrect );
    layoutrect->LayoutRect( rect, ELatinBold12, 0, 1, 1, 1, 5, ELayoutAlignCenter );
    CWindowGc& gc = iContainer->SystemGc();
    iContainer->ActiveControlGc();
    layoutrect->DrawRect( gc );
    layoutrect->DrawOutLineRect( gc );
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CleanupStack::PushL( bitmap );
    CleanupStack::PushL( mask );
    layoutrect->DrawImage( gc, bitmap, mask );
    layoutrect->Color();
    layoutrect->Rect();
    iContainer->DeActiveControlGc();
    CleanupStack::PopAndDestroy( 3 );// bitmap, mask, layoutrect
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknDrawDoDrawFuncsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknDrawDoDrawFuncsL( CStifItemParser& /*aItem*/ )
    {
    TRect rect( 20, 20, 40, 40 );
    CWindowGc& gc = iContainer->SystemGc();
    iContainer->ActiveControlGc();
    TBufC<KBufSize> buf( KTextExample );
    TPtrC ptrc( buf );
    AknDraw::DrawEmptyList( rect, gc, ptrc );
    AknDraw::DrawEmptyListForSettingPage( rect, gc, ptrc );
    AknDraw::DrawEmptyListWithFind( rect, gc, ptrc );
    AknDraw::DrawEmptyListHeading( rect, gc, ptrc );
    AknDraw::DrawEmptyListImpl( rect, gc, ptrc, 1, 1 );
    TAknLayoutRect* layoutrect  = new ( ELeave ) TAknLayoutRect;
    CleanupStack::PushL( layoutrect );
    AknLayoutUtils::SAknLayoutRect layout;
    layout.iC = 0;
    layout.iL = 5;
    layout.iT = 5;
    layout.iR = 10;
    layout.iB = 15;
    layout.iW = 15;
    layout.iH = 12;
    layoutrect->LayoutRect( rect, layout );
    AknDraw::DrawWindowShadow( gc, *layoutrect, *layoutrect, *layoutrect, *layoutrect, *layoutrect );
    CleanupStack::PopAndDestroy( layoutrect );
    iContainer->DeActiveControlGc();
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknDrawWithSkinsDoDrawFuncsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknDrawWithSkinsDoDrawFuncsL( CStifItemParser& /*aItem*/ )
    {
    TRect rect( 20, 20, 40, 40 );
    CWindowGc& gc = iContainer->SystemGc();
    iContainer->ActiveControlGc();
    TBufC<KBufSize> buf( KTextExample );
    TPtrC ptrc( buf );
    AknDrawWithSkins::DrawEmptyList( rect, gc, ptrc, iContainer );
    AknDrawWithSkins::DrawEmptyListForSettingPage( rect, gc, ptrc, iContainer );
    AknDrawWithSkins::DrawEmptyListWithFind( rect, gc, ptrc, iContainer );
    AknDrawWithSkins::DrawEmptyListHeading( rect, gc, ptrc, iContainer );
    TAknLayoutRect* layoutrect  = new ( ELeave ) TAknLayoutRect;
    CleanupStack::PushL( layoutrect );
    AknLayoutUtils::SAknLayoutRect layout;
    layout.iC = 0;
    layout.iL = 5;
    layout.iT = 5;
    layout.iR = 10;
    layout.iB = 15;
    layout.iW = 15;
    layout.iH = 12;
    layoutrect->LayoutRect( rect, layout );
    AknDrawWithSkins::DrawWindowShadow( gc, *layoutrect, *layoutrect, *layoutrect, *layoutrect, *layoutrect, iContainer );
    CleanupStack::PopAndDestroy( layoutrect );
    iContainer->DeActiveControlGc();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknUtilsGlobalFuncsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknUtilsGlobalFuncsL( CStifItemParser& /*aItem*/ )
    {
    LatinPlain12();
    LatinBold12();
    LatinBold13();
    LatinBold16();
    LatinBold17();
    LatinBold19(); 
    NumberPlain5();
    ClockBold30();
    LatinClock14();
    ApacPlain12();
    ApacPlain16();
    
    TBuf<KBufSize> buf( KTextExample );
    CompleteWithAppPath( buf );
    DefaultInputLanguageFromUILanguage( 0 );
    SetKeyblockMode( EDefaultBlockMode );
    TTime time;
    time.HomeTime();
    AknDateTimeUtils::ConvertUtcTimeToHomeTime( time );
    AknLangUtils::DisplayLanguageTagL();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestFilterTextListBoxModelRemoveFilterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestFilterTextListBoxModelRemoveFilterL( CStifItemParser& /*aItem*/ )
    {
    CEikListBox* celllist = new ( ELeave ) CAknSingleNumberStyleListBox;
    CleanupStack::PushL( celllist );
    celllist->SetContainerWindowL( * iContainer );
    
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_DOUBLE_LISTBOX );
    celllist->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    CAknSearchField* search = CAknSearchField::NewL( *iContainer, 
            CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( search );
    
    CAknFilteredTextListBoxModel* model = 
        static_cast<CAknFilteredTextListBoxModel*>( celllist->Model() );
    
    model->RemoveFilter();
    
    CleanupStack::PopAndDestroy( search );
    CleanupStack::PopAndDestroy( celllist );
    
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknPopupUtilsPosition
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknPopupUtilsPositionFuncs( 
    CStifItemParser& /*aItem*/ )
    {
    //TPoint position( AknPopupUtils::Position( TSize(), ETrue ) );
    //position = ( AknPopupUtils::Position( TSize(), EFalse ) );
    //position = ( AknPopupUtils::Position( TSize(), NULL ) );
    return KErrNone;
    }

// End of file

