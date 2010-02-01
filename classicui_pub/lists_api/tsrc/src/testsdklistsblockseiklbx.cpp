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
* Description:  
*
*/

// [INCLUDE FILES]
#include <e32base.h>
#include <aknlists.h>
#include <testsdklists.rsg>
#include <coemain.h>
#include <coeaui.h>
#include <eiklbx.h>
#include <barsread.h>
#include <stringloader.h>
#include <eiktxlbx.h>
#include <eikbutb.h>
#include <eiklbed.h>

#include "testsdklists.h"
#include "testsdkcontainer.h"
#include "testsdklistslbicobserver.h"
#include "testsdklistslbsobserver.h"
#include "testsdklistslistbox.h"
#include "testsdkliststextlistbox.h"
#include "testsdklistssnakinglistbox.h"

const TInt KZero = 0;
const TInt KFour = 4;
const TInt KFive = 5;
const TInt KEight = 8;
const TInt KNine = 9;
const TInt KHundred = 100;


// ============================ MEMBER FUNCTIONS ===============================

// ============================class CEikListBox================================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox = new( ELeave ) CEikListBox();
    STIF_ASSERT_NOT_NULL( iListBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDestructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDestructor( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBDestructor" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    delete iListBox;
    iListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBConstructL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    iListBox->ConstructL( model, drawer, 
        iContainer, EAknListBoxSelectionList | EAknListBoxViewerFlags );

    CleanupStack::Pop( 3 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBConstructWithTGulBorderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBConstructWithTGulBorderL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBConstructWithTGulBorderL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    iListBox->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    iListBox->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    CleanupStack::Pop( 3 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBOfferKeyEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt err = KErrNone;
    TKeyEvent keyEvent = { EKeyPause, EStdKeySpace, 0, 0  };
    TRAP( err, iListBox->OfferKeyEventL( keyEvent, EEventKey ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt err = KErrNone;
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KNine );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TRAP( err, iListBox->HandlePointerEventL( event ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetContainerWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetContainerWindowL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetContainerWindowL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt err = KErrNone;
    TRAP( err, iListBox->SetContainerWindowL( *iContainer ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBMinimumSize
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBMinimumSize( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBMinimumSize" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->MinimumSize();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetDimmed
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetDimmed( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetDimmed" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->SetDimmed( ETrue );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBHandleScrollEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBHandleScrollEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBHandleScrollEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer();
    CleanupStack::PushL( drawer );
    drawer->ConstructL( iEikonEnvPointer->NormalFont() );

    CEikListBox* listBox = new ( ELeave ) CEikListBox;
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
    
    CleanupStack::PopAndDestroy( scrollBar );
    CleanupStack::PopAndDestroy( listBox );
    CleanupStack::Pop( drawer );
    CleanupStack::Pop( model );
    CleanupStack::Pop( textArray );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBModelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBModelL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBModelL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    MListBoxModel* model = iListBox->Model();
    STIF_ASSERT_NOT_NULL( model );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBViewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBViewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBViewL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CListBoxView* view = iListBox->View();
    STIF_ASSERT_NOT_NULL( view );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBTopItemIndex
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBTopItemIndex( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBTopItemIndex" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt index = iListBox->TopItemIndex();
    STIF_ASSERT_EQUALS( KZero, index );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetTopItemIndex
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetTopItemIndex( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetTopItemIndex" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->SetTopItemIndex( KEight );
    TInt index = iListBox->TopItemIndex();
    STIF_ASSERT_EQUALS( KEight, index );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBBottomItemIndex
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBBottomItemIndex( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBBottomItemIndex" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt index = iListBox->BottomItemIndex();
    STIF_ASSERT_EQUALS( KEight, index );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBCurrentItemIndex
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBCurrentItemIndex( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBCurrentItemIndex" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt index = iListBox->CurrentItemIndex();
    STIF_ASSERT_EQUALS( KZero, index );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetCurrentItemIndex
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetCurrentItemIndex( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetCurrentItemIndex" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->SetCurrentItemIndex( KFive );
    TInt index = iListBox->CurrentItemIndex();
    STIF_ASSERT_EQUALS( KFive, index );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetCurrentItemIndexAndDraw
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetCurrentItemIndexAndDraw( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetCurrentItemIndexAndDraw" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->SetCurrentItemIndexAndDraw( KFive );
    TInt index = iListBox->CurrentItemIndex();
    STIF_ASSERT_EQUALS( KFive, index );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSelectionIndexesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSelectionIndexesL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSelectionIndexesL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    const CArrayFixFlat<TInt>* selectionArray =
        static_cast< const CArrayFixFlat<TInt>* > ( iListBox->SelectionIndexes() );
    STIF_ASSERT_NOT_NULL( selectionArray );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetSelectionIndexesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetSelectionIndexesL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetSelectionIndexesL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CEikTextListBox* list = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    CArrayFixFlat<TInt>* selectionArray = new( ELeave ) 
        CArrayFixFlat<TInt>( KFour );
    CleanupStack::PushL( selectionArray );
    selectionArray->AppendL( 0 );
    selectionArray->AppendL( 1 );
    selectionArray->AppendL( KFour );
    list->SetSelectionIndexesL( selectionArray );

    const CArrayFix<TInt>* getSelectionArray = list->SelectionIndexes();
    STIF_ASSERT_TRUE( ( selectionArray->Length() == getSelectionArray->Length() )
            && ( selectionArray->At( 0 ) == getSelectionArray->At( 0 ) ) );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy( selectionArray );
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBClearSelection
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBClearSelection( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBClearSelection" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->ClearSelection();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBHandleItemAdditionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBHandleItemAdditionL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBHandleItemAdditionL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt err = KErrNone;
    TRAP( err, iListBox->HandleItemAdditionL() );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBHandleItemRemovalL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBHandleItemRemovalL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBHandleItemRemovalL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt err = KErrNone;
    TRAP( err, iListBox->HandleItemRemovalL() );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBHandleItemAdditionWIthParaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBHandleItemAdditionWIthParaL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBHandleItemAdditionWIthParaL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CArrayFixFlat<TInt>* indexArray = new( ELeave ) CArrayFixFlat<TInt>( KFour );
    CleanupStack::PushL( indexArray );
    indexArray->AppendL( KEight );
    indexArray->AppendL( KNine );
    
    TInt err = KErrNone;
    TRAP( err, iListBox->HandleItemAdditionL( *indexArray ) );
    CleanupStack::PopAndDestroy( indexArray );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBHandleItemRemovalWIthParaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBHandleItemRemovalWIthParaL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBHandleItemRemovalWIthParaL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CArrayFixFlat<TInt>* indexArray = new( ELeave ) CArrayFixFlat<TInt>( KFour );
    CleanupStack::PushL( indexArray );
    indexArray->AppendL( KEight );
    indexArray->AppendL( KNine );
    
    TInt err = KErrNone;
    TRAP( err, iListBox->HandleItemRemovalL( *indexArray ) );
    CleanupStack::PopAndDestroy( indexArray );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBReset
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBReset( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBReset" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->Reset();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBAddItemChangeObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBAddItemChangeObserverL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBAddItemChangeObserverL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsLBICObserver* observer = new( ELeave ) CTestSDKListsLBICObserver();
    CleanupStack::PushL( observer );
    iListBox->AddItemChangeObserverL( observer );
    CleanupStack::PopAndDestroy( observer );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBRemoveItemChangeObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBRemoveItemChangeObserverL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBRemoveItemChangeObserverL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsLBICObserver* observer = new( ELeave ) CTestSDKListsLBICObserver();
    CleanupStack::PushL( observer );
    TBool flag = iListBox->RemoveItemChangeObserver( observer );
    STIF_ASSERT_FALSE( flag );

    iListBox->AddItemChangeObserverL( observer );
    flag = iListBox->RemoveItemChangeObserver( observer );
    STIF_ASSERT_TRUE( flag );
    CleanupStack::PopAndDestroy( observer );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetItemHeightL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetItemHeightL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetItemHeightL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->SetItemHeightL( KFive );
    TInt height = iListBox->ItemHeight();
    STIF_ASSERT_EQUALS( KFive, height );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBItemHeight
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBItemHeight( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetItemHeightL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->ItemHeight();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBCreateScrollBarFrameL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBCreateScrollBarFrameL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBCreateScrollBarFrameL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CEikScrollBarFrame* scrollBar = iListBox->CreateScrollBarFrameL( ETrue );
    CleanupStack::PushL( scrollBar );
    STIF_ASSERT_NOT_NULL( scrollBar );
    CleanupStack::Pop( scrollBar );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetScrollBarFrameL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetScrollBarFrameL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetScrollBarFrameL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CEikScrollBarFrame* scrollBarFrame = new( ELeave) CEikScrollBarFrame(
        iContainer, iListBox, ETrue );
    CleanupStack::PushL( scrollBarFrame );
    iListBox->SetScrollBarFrame( scrollBarFrame, CEikListBox::ENotOwnedExternally );

    CEikScrollBarFrame* getFrame = iListBox->ScrollBarFrame();
    STIF_ASSERT_TRUE( scrollBarFrame == getFrame );
    CleanupStack::Pop( scrollBarFrame );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBScrollBarFrameL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBScrollBarFrameL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBScrollBarFrameL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CEikScrollBarFrame* scrollBarFrame = iListBox->ScrollBarFrame();
    STIF_ASSERT_NULL( scrollBarFrame );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBUpdateScrollBarsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBUpdateScrollBarsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBUpdateScrollBarsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt err = KErrNone;
    TRAP( err, iListBox->UpdateScrollBarsL() );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBCalculatePopoutRect
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBCalculatePopoutRect( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBCalculatePopoutRect" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TRect rect = iContainer->Rect();
    iListBox->CalculatePopoutRect( 0, 0, rect );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBCalcSizeInPixels
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBCalcSizeInPixels( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBCalcSizeInPixels" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->CalcSizeInPixels( KFive, KFive );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBCalcWidthBasedOnNumOfChars
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBCalcWidthBasedOnNumOfChars( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBCalcWidthBasedOnNumOfChars" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->CalcWidthBasedOnNumOfChars( KFive );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBCalcHeightBasedOnNumOfItems
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBCalcHeightBasedOnNumOfItems( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBCalcHeightBasedOnNumOfItems" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->CalcHeightBasedOnNumOfItems( KFive );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBCalcWidthBasedOnRequiredItemWidth
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBCalcWidthBasedOnRequiredItemWidth( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBCalcWidthBasedOnRequiredItemWidth" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->CalcWidthBasedOnRequiredItemWidth( KFive );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDrawItem
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDrawItem( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBDrawItem" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->DrawItem( 0 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBScrollToMakeItemVisible
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBScrollToMakeItemVisible( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBScrollToMakeItemVisible" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt flags = CEikListBox::EIncrementalMatching | 
                    EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );
    
    CTestSDKListsTextListBox* listBox = new ( ELeave ) CTestSDKListsTextListBox;
    CleanupStack::PushL( listBox );
    listBox->ConstructL( iContainer, flags );
    listBox->Model()->SetItemTextArray( textArray );
    listBox->Model()->SetOwnershipType( ELbmOwnsItemArray );
    
    CEikScrollBarFrame* scrollBarFrame = new( ELeave) CEikScrollBarFrame(
        iContainer, listBox, ETrue );
    CleanupStack::PushL( scrollBarFrame );
    listBox->SetScrollBarFrame( scrollBarFrame, 
        CEikListBox::ENotOwnedExternally );
    CleanupStack::Pop( scrollBarFrame );
    
    iContainer->SetControlL( listBox );
    listBox->SetViewRectHeightAdjustment( KFive );
    listBox->ScrollToMakeItemVisible( KFive );
    
    iContainer->ResetControl();
    CleanupStack::Pop( listBox );
    CleanupStack::Pop( textArray );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBRedrawItem
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBRedrawItem( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBRedrawItem" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->RedrawItem( 0 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetListBoxObserver
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetListBoxObserver( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetListBoxObserver" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    MEikListBoxObserver* observer = NULL;
    iListBox->SetListBoxObserver( observer );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVerticalInterItemGap
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVerticalInterItemGap( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetListBoxObserver" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->VerticalInterItemGap();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetLaunchingButton
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetLaunchingButton( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetLaunchingButton" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->SetLaunchingButton( NULL );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetItemEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetItemEditorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetItemEditorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CEikListBoxTextEditor* editor = new( ELeave ) CEikListBoxTextEditor( NULL );
    CleanupStack::PushL( editor );
    iListBox->SetItemEditor( editor );
    CleanupStack::Pop( editor );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBResetItemEditor
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBResetItemEditor( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBResetItemEditor" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->ResetItemEditor();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBItemEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBItemEditorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBItemEditorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CEikListBoxTextEditor* editor = new( ELeave ) CEikListBoxTextEditor( NULL );
    CleanupStack::PushL( editor );
    iListBox->SetItemEditor( editor );

    MEikListBoxEditor* getEditor = iListBox->ItemEditor();
    STIF_ASSERT_TRUE( editor == getEditor );

    iListBox->ResetItemEditor();
    getEditor = iListBox->ItemEditor();
    STIF_ASSERT_NULL( getEditor );
    CleanupStack::Pop( editor );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBEditItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBEditItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBEditItemL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CEikTextListBox* list = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    list->EditItemL( KHundred );

    iContainer->ResetControl();
    CleanupStack::Pop( 2 );
    list = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBStopEditingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBStopEditingL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBStopEditingL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt err = KErrNone;
    TRAP( err, iListBox->StopEditingL( ETrue ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBShortcutValueForNextList
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBShortcutValueForNextList( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBShortcutValueForNextList" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->ShortcutValueForNextList();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetShortcutValueFromPrevList
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetShortcutValueFromPrevList( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetShortcutValueFromPrevList" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->SetShortcutValueFromPrevList( 0 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBHighlightRect
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBHighlightRect( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBHighlightRect" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->HighlightRect();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBGetColorUseListL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( KFour );
    CleanupStack::PushL( colorUseList );
    iListBox->GetColorUseListL( *colorUseList );
    CleanupStack::PopAndDestroy( colorUseList );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBHandleResourceChange
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBHandleResourceChange( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBHandleResourceChange" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->HandleResourceChange( KAknsMessageSkinChange );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBActivateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBActivateL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBActivateL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->ActivateL();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBInputCapabilities
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBInputCapabilities( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBInputCapabilities" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->InputCapabilities();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBEventModifiers
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBEventModifiers( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBEventModifiers" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt modifiers = iListBox->EventModifiers();
    STIF_ASSERT_EQUALS( KZero, modifiers );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBIsMultiselection
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBIsMultiselection( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBIsMultiselection" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TBool flag = iListBox->IsMultiselection();
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBCreateScrollBarFrameWithTwoParaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBCreateScrollBarFrameWithTwoParaL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBCreateScrollBarFrameWithTwoParaL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CEikScrollBarFrame* scrollBar = iListBox->CreateScrollBarFrameL( ETrue, EFalse );
    CleanupStack::PushL( scrollBar );
    STIF_ASSERT_NOT_NULL( scrollBar );
    CleanupStack::Pop( scrollBar );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBCreateScrollBarFrameWithThreeParaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBCreateScrollBarFrameWithThreeParaL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBCreateScrollBarFrameWithThreeParaL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CEikScrollBarFrame* scrollBar = iListBox->CreateScrollBarFrameL( ETrue, EFalse, ETrue );
    CleanupStack::PushL( scrollBar );
    STIF_ASSERT_NOT_NULL( scrollBar );
    CleanupStack::Pop( scrollBar );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBEnableMSKObserver
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBEnableMSKObserver( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBEnableMSKObserver" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->EnableMSKObserver( ETrue );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBAddSelectionObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBAddSelectionObserverL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBAddSelectionObserverL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsLBSObserver* observer = new( ELeave ) CTestSDKListsLBSObserver();
    CleanupStack::PushL( observer );
    TInt err = KErrNone;
    TRAP( err, iListBox->AddSelectionObserverL( observer ) );
    CleanupStack::PopAndDestroy( observer );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBRemoveSelectionObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBRemoveSelectionObserverL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBRemoveSelectionObserver" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsLBSObserver* observer = new( ELeave ) CTestSDKListsLBSObserver();
    CleanupStack::PushL( observer );
    TInt err = KErrNone;
    TRAP( err, iListBox->AddSelectionObserverL( observer ) );
    iListBox->RemoveSelectionObserver( observer );
    CleanupStack::PopAndDestroy( observer );


    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBFocusChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBFocusChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBFocusChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->FocusChanged( ENoDrawNow );
    list->FocusChanged( EDrawNow );
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->SizeChanged();
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBHandleViewRectSizeChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBHandleViewRectSizeChangeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBHandleViewRectSizeChangeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->HandleViewRectSizeChangeL();
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBCountComponentControlsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TInt count = list->CountComponentControls();
    STIF_ASSERT_EQUALS( KZero, count );
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBComponentControlL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBComponentControlL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );

    CEikScrollBarFrame* scrollBarFrame = new( ELeave) CEikScrollBarFrame(
        iContainer, list, ETrue );
    CleanupStack::PushL( scrollBarFrame );
    list->SetScrollBarFrame( scrollBarFrame, CEikListBox::ENotOwnedExternally );                

    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    CCoeControl* control = list->ComponentControl( 0 );
    STIF_ASSERT_NULL( control );
    CleanupStack::Pop( 4 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBCreateMatchBufferL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBCreateMatchBufferL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBCreateMatchBufferL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->CreateMatchBufferL();
    list->ClearMatchBuffer();
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBClearMatchBufferL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBClearMatchBufferL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBClearMatchBufferL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->ClearMatchBuffer();
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBMatchTypedCharL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBMatchTypedCharL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBMatchTypedCharL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CTestSDKListsTextListBox* list = new( ELeave ) CTestSDKListsTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    list->MatchTypedCharL( '0' );
    iContainer->ResetControl();
    CleanupStack::Pop( 2 );
    list = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBUndoLastCharL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBUndoLastCharL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBUndoLastCharL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->CreateMatchBufferL();
    list->UndoLastChar();
    list->ClearMatchBuffer();
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLastCharMatchedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLastCharMatchedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBLastCharMatchedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->LastCharMatched();
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBUpdateScrollBarThumbsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBUpdateScrollBarThumbsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBUpdateScrollBarThumbsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->UpdateScrollBarThumbs();
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBHorizScrollGranularityInPixelsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBHorizScrollGranularityInPixelsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBHorizScrollGranularityInPixelsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->HorizScrollGranularityInPixels();
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBHorizontalNudgeValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBHorizontalNudgeValueL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBHorizontalNudgeValueL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->HorizontalNudgeValue();
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBAdjustTopItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBAdjustTopItemIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBAdjustTopItemIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->AdjustTopItemIndex();
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSimulateArrowKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSimulateArrowKeyEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSimulateArrowKeyEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CTestSDKListsTextListBox* list = new( ELeave ) CTestSDKListsTextListBox;
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );
    TInt err = KErrNone;
    TRAP( err, list->SimulateArrowKeyEventL( EKeyDownArrow ) );
    iContainer->ResetControl();
    CleanupStack::Pop( 2 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBHandleLeftArrowKeyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBHandleLeftArrowKeyL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBHandleLeftArrowKeyL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TInt err = KErrNone;
    TRAP( err, list->HandleLeftArrowKeyL( CListBoxView::ESingleSelection ) );
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBHandleRightArrowKeyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBHandleRightArrowKeyL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBHandleRightArrowKeyL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TInt err = KErrNone;
    TRAP( err, list->HandleRightArrowKeyL( CListBoxView::EContiguousSelection ) );
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBRestoreCommonListBoxPropertiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBRestoreCommonListBoxPropertiesL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBRestoreCommonListBoxPropertiesL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    TInt err = KErrNone;
    TRAP( err, list->RestoreCommonListBoxPropertiesL( reader ) );
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBProtectedConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBProtectedConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBProtectedConstructL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;

    CTestSDKListsTextListBox* list = new( ELeave ) CTestSDKListsTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );

    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBCreateViewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBCreateViewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBCreateViewL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TInt err = KErrNone;
    TRAP( err, list->CreateViewL() );
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBMakeViewClassInstanceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBMakeViewClassInstanceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBMakeViewClassInstanceL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    CListBoxView* view = list->MakeViewClassInstanceL();
    STIF_ASSERT_NOT_NULL( view );
    delete view;
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetViewRectFromClientRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetViewRectFromClientRectL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetViewRectFromClientRectLL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TRect rect = iContainer->Rect();
    list->SetViewRectFromClientRect( rect );
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBRestoreClientRectFromViewRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBRestoreClientRectFromViewRectL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBRestoreClientRectFromViewRectL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TRect rect = iContainer->Rect();
    list->RestoreClientRectFromViewRect( rect );
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBAdjustRectHeightToWholeNumberOfItemsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBAdjustRectHeightToWholeNumberOfItemsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBAdjustRectHeightToWholeNumberOfItemsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TRect rect = iContainer->Rect();
    list->AdjustRectHeightToWholeNumberOfItems( rect );
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBListBoxMarginsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBListBoxMarginsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBListBoxMarginsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TMargins8 margins = list->ListBoxMargins();
    STIF_ASSERT_NOT_NULL( &margins );
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBHorizontalMarginL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBHorizontalMarginL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBHorizontalMarginL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->HorizontalMargin();
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVerticalMarginL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVerticalMarginL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBVerticalMarginL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->VerticalMargin();
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetHorizontalMarginL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetHorizontalMarginL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetHorizontalMarginL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->SetHorizontalMargin( KNine );
    TInt margins = list->HorizontalMargin();
    STIF_ASSERT_EQUALS( KNine, margins );
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetVerticalMarginL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetVerticalMarginL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetVerticalMarginL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->SetVerticalMargin( KNine );
    TInt margins = list->VerticalMargin();
    STIF_ASSERT_EQUALS( KNine, margins );
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBMatchBufferL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBMatchBufferL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBMatchBufferL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    RIncrMatcherBase* baMatch = list->MatchBuffer();
    STIF_ASSERT_NULL( baMatch );
    list->CreateMatchBufferL();

    baMatch = list->MatchBuffer();
    STIF_ASSERT_NOT_NULL( baMatch );
    list->ClearMatchBuffer();
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBViewRectHeightAdjustmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBViewRectHeightAdjustmentL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBViewRectHeightAdjustmentL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->ViewRectHeightAdjustment();

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBBackColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBBackColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBBackColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->BackColor();

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetViewRectHeightAdjustmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetViewRectHeightAdjustmentL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetViewRectHeightAdjustmentL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->SetViewRectHeightAdjustment( KFive );
    TInt adjustment = list->ViewRectHeightAdjustment();
    STIF_ASSERT_EQUALS( KFive, adjustment );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBReportListBoxEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBReportListBoxEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBReportListBoxEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TInt err = KErrNone;
    TRAP( err, list->ReportListBoxEventL( MEikListBoxObserver::EEventEnterKeyPressed ) );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDrawL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBDrawL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CTestSDKListsTextListBox* list = new( ELeave ) CTestSDKListsTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    TRect rect = iContainer->Rect();
    list->Draw( rect );
    iContainer->ResetControl();
    CleanupStack::Pop( 2 );
    list = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBClearMarginsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBClearMarginsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBClearMarginsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->ClearMargins();

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBUpdateCurrentItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBUpdateCurrentItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBUpdateCurrentItemL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->UpdateCurrentItem( 0 );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBHandleDragEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBHandleDragEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBHandleDragEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TInt err = KErrNone;
    TRAP( err, list->HandleDragEventL( TPoint( 0, 0 ) ) );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBItemExistsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBItemExistsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBItemExistsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TBool flag;
    for ( TInt i = 0; i <= list->BottomItemIndex(); i++ )
        {
        flag = list->ItemExists( i );
        STIF_ASSERT_TRUE( flag );
        }

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDrawMatcherCursorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDrawMatcherCursorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBDrawMatcherCursorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->DrawMatcherCursor();

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBInterItemGapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBInterItemGapL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBInterItemGapL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->InterItemGap();

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBUpdateViewColorsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBUpdateViewColorsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBUpdateViewColorsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->UpdateViewColors();

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBUpdateItemDrawerColorsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBUpdateItemDrawerColorsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBUpdateItemDrawerColorsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->UpdateItemDrawerColors();

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBFireItemChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBFireItemChangeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBFireItemChangeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->FireItemChange();

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetReasonForFocusLostL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetReasonForFocusLostL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetReasonForFocusLostL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TInt err = KErrNone;
    TRAP( err,
        list->SetReasonForFocusLostL( CTestSDKListsListBox::EFocusLostToExternalControl ) );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBReasonForFocusLostL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBReasonForFocusLostL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBReasonForFocusLostL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    CTestSDKListsListBox::TReasonForFocusLost reason =
            CTestSDKListsListBox::EFocusLostToExternalControl;
    list->SetReasonForFocusLostL( reason );
    CTestSDKListsListBox::TReasonForFocusLost getReason = list->ReasonForFocusLostL();
    STIF_ASSERT_EQUALS( reason, getReason );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBIsMatchBufferL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBIsMatchBufferL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBIsMatchBufferL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TBool flag = list->IsMatchBuffer();
    STIF_ASSERT_FALSE( flag );

    list->CreateMatchBufferL();
    flag = list->IsMatchBuffer();
    STIF_ASSERT_TRUE( flag );
    list->ClearMatchBuffer();
    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBCreateScrollBarFrameLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBCreateScrollBarFrameLayoutL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBCreateScrollBarFrameLayoutL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsListBox* list = new( ELeave ) CTestSDKListsListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TEikScrollBarFrameLayout frameLayout;
    list->CreateScrollBarFrameLayout( frameLayout );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// ==========================class CEikSnakingListBox===========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CEikSnakingListBox* list = new( ELeave ) CEikSnakingListBox();
    CleanupStack::PushL( list );
    STIF_ASSERT_NOT_NULL( list )
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBDestructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBDestructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CEikSnakingListBox* list = new( ELeave ) CEikSnakingListBox();
    CleanupStack::PushL( list );
    STIF_ASSERT_NOT_NULL( list )
    CleanupStack::Pop( list );
    delete list;
    list = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBMakeViewClassInstanceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBMakeViewClassInstanceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBMakeViewClassInstanceL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CEikSnakingListBox* list = new( ELeave ) CEikSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    CListBoxView* view = list->MakeViewClassInstanceL();
    STIF_ASSERT_NOT_NULL( view );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBSetTopItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBSetTopItemIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBSetTopItemIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CEikSnakingListBox* list = new( ELeave ) CEikSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->SetTopItemIndex( KEight );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBColumnWidthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBColumnWidthL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBColumnWidthL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CEikSnakingListBox* list = new( ELeave ) CEikSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->ColumnWidth();

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBSetColumnWidthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBSetColumnWidthL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBSetColumnWidthL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CEikSnakingListBox* list = new( ELeave ) CEikSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->SetColumnWidth( KFive );
    TInt width = list->ColumnWidth();
    STIF_ASSERT_EQUALS( KFive, width );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CEikSnakingListBox* list = new( ELeave ) CEikSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TInt err = KErrNone;
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KNine );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TRAP( err, list->HandlePointerEventL( event ) );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBHandleViewRectSizeChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBHandleViewRectSizeChangeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBHandleViewRectSizeChangeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsSnakingListBox* list = new( ELeave ) CTestSDKListsSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TInt err = KErrNone;
    TRAP( err, list->HandleViewRectSizeChangeL() );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBHandleLeftArrowKeyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBHandleLeftArrowKeyL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBHandleLeftArrowKeyL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsSnakingListBox* list = new( ELeave ) CTestSDKListsSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TInt err = KErrNone;
    TRAP( err, list->HandleLeftArrowKeyL( CListBoxView::ESingleSelection ) );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBHandleRightArrowKeyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBHandleRightArrowKeyL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBHandleRightArrowKeyL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsSnakingListBox* list = new( ELeave ) CTestSDKListsSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TInt err = KErrNone;
    TRAP( err, list->HandleRightArrowKeyL( CListBoxView::EContiguousSelection ) );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBHorizontalNudgeValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBHorizontalNudgeValueL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBHorizontalNudgeValueL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsSnakingListBox* list = new( ELeave ) CTestSDKListsSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->HorizontalNudgeValue();

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBHorizScrollGranularityInPixelsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBHorizScrollGranularityInPixelsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBHorizScrollGranularityInPixelsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsSnakingListBox* list = new( ELeave ) CTestSDKListsSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->HorizScrollGranularityInPixels();

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBAdjustTopItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBAdjustTopItemIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBAdjustTopItemIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsSnakingListBox* list = new( ELeave ) CTestSDKListsSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->AdjustTopItemIndex();

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBHandleDragEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBHandleDragEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBHandleDragEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsSnakingListBox* list = new( ELeave ) CTestSDKListsSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TInt err = KErrNone;
    TRAP( err, list->HandleDragEventL( TPoint( 0, 0 ) ) );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBRestoreClientRectFromViewRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBRestoreClientRectFromViewRectL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBRestoreClientRectFromViewRectL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsSnakingListBox* list = new( ELeave ) CTestSDKListsSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TRect rect = iContainer->Rect();
    list->RestoreClientRectFromViewRect( rect );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBAdjustRectHeightToWholeNumberOfItemsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBAdjustRectHeightToWholeNumberOfItemsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBAdjustRectHeightToWholeNumberOfItemsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsSnakingListBox* list = new( ELeave ) CTestSDKListsSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TRect rect = iContainer->Rect();
    list->AdjustRectHeightToWholeNumberOfItems( rect );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBMoveToNextOrPreviousItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBMoveToNextOrPreviousItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBMoveToNextOrPreviousItemL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsSnakingListBox* list = new( ELeave ) CTestSDKListsSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    TInt err = KErrNone;
    TRAP( err, list->MoveToNextOrPreviousItemL( TPoint( 0 , 0 ) ) );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsSnakingListBox* list = new( ELeave ) CTestSDKListsSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->SizeChanged();

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBGetColorUseListL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsSnakingListBox* list = new( ELeave ) CTestSDKListsSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();      
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( KFour );
    CleanupStack::PushL( colorUseList );
    list->GetColorUseListL( *colorUseList );
    CleanupStack::PopAndDestroy( colorUseList );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestSLBHandleResourceChangeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    CTestSDKListsSnakingListBox* list = new( ELeave ) CTestSDKListsSnakingListBox();
    CleanupStack::PushL( list );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( textArray );
    
    CTextListItemDrawer* drawer =
        new( ELeave ) CTextListItemDrawer( model, iEikonEnvPointer->NormalFont() );
    CleanupStack::PushL( drawer );

    TGulBorder border( TGulBorder::ESingleGray );
    list->ConstructL( model, drawer, 
        iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );
    list->SetExtent( iContainer->Rect().iTl, iContainer->Rect().Size() );

    list->HandleResourceChange( KAknsMessageSkinChange );

    CleanupStack::Pop( 3 );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDisableScrolling
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDisableScrolling( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBDisableScrolling" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->DisableScrolling( EFalse );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSetItemsInSingleLine
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSetItemsInSingleLine( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBSetItemsInSingleLine" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->SetItemsInSingleLine( 1 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBBackgroundDrawingSuppressed
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBBackgroundDrawingSuppressed( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBBackgroundDrawingSuppressed" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->BackgroundDrawingSuppressed();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBHandlePhysicsScrollEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBHandlePhysicsScrollEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBHandlePhysicsScrollEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->HandlePhysicsScrollEventL( 0 );

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDisableSingleClick
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDisableSingleClick( CStifItemParser& /*aItem*/)
    { 
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBDisableSingleClick" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->DisableSingleClick( EFalse );
    iListBox->DisableSingleClick( ETrue );
    return KErrNone;    
    }


// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDisableItemSpecificMenu
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDisableItemSpecificMenu( CStifItemParser& /*aItem*/)
    { 
    // Print to UI
    _LIT( KTestModule, "EIKLBXTestModule" );
    _LIT( KTestEIKLBX, "In TestLBDisableItemSpecificMenu" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBX );
    // Print to log file
    iLog->Log( KTestEIKLBX );

    iListBox->DisableItemSpecificMenu();
    return KErrNone;    
    }

// [End of file]
