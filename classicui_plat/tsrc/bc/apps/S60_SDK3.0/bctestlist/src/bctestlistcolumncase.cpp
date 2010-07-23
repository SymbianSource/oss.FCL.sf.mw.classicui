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
* Description:         test case for column list classes
*
*/









#include <aknlists.h>
#include <eikenv.h>
#include <barsread.h>
#include <eikclbd.h>
#include <eikclb.h>
#include <aknutils.h>

#include "bctestlistcolumncase.h"
#include "bctestlistcontainer.h"
#include "bctestlist.hrh"
#include <bctestlist.rsg>
#include <bctestlist.mbg>

_LIT( KNewSingle, "Create CAknSingleStyleListBox" );
_LIT( KNewSingleNumber, "Create CAknSingleNumberStyleListBox" );
_LIT( KNewSingleHeading, "Create CAknSingleHeadingStyleListBox" );
_LIT( KNewSingleGraphic, "Create CAknSingleGraphicStyleListBox" );
_LIT( KNewSingleGraphicHeading, "Create CAknSingleGraphicHeadingStyleListBox" );
_LIT( KNewSingleNumberHeading, "Create CAknSingleNumberHeadingStyleListBox" );
_LIT( KNewSingleLarge, "Create CAknSingleLargeStyleListBox" );
_LIT( KNewSingleNoRes, "Create CAknSingleStyleListBox without resource" );

_LIT( KSingleSizeChanged, "CAknSingleStyleListBox::SizeChanged" );
_LIT( KSingleMinimumSize, "CAknSingleStyleListBox::MinimumSize" );
_LIT( KSingleHandlePointer, "CAknSingleStyleListBox::HandlePointerEventL" );

_LIT( KSingleNumberSizeChanged, "CAknSingleNumberStyleListBox::SizeChanged" );
_LIT( KSingleNumberMinimumSize, "CAknSingleNumberStyleListBox::MinimumSize" );
_LIT( KSingleNumberHandlePointer, "CAknSingleNumberStyleListBox::HandlePointerEventL" );
_LIT( KListBoxUtilHandleItemRemoval, 
    "AknListBoxUtils::HandleItemRemovalAndPositionHighlightL" );
    
_LIT( KSingleHeadingSizeChanged, "CAknSingleHeadingStyleListBox::SizeChanged" );
_LIT( KSingleHeadingMinimumSize, "CAknSingleHeadingStyleListBox::MinimumSize" );
_LIT( KSingleHeadingHandlePointer, "CAknSingleHeadingStyleListBox::HandlePointerEventL" );
_LIT( KSingleHeadingViewDrawEmpty, "CSingleHeadingStyleView::DrawEmptyList" );

_LIT( KSingleGraphicSizeChanged, "CAknSingleGraphicStyleListBox::SizeChanged" );
_LIT( KSingleGraphicMinimumSize, "CAknSingleGraphicStyleListBox::MinimumSize" );
_LIT( KSingleGraphicHandlePointer, "CAknSingleGraphicStyleListBox::HandlePointerEventL" );

_LIT( KSingleGraphicHeadingSizeChanged, "CAknSingleGraphicHeadingStyleListBox::SizeChanged" );
_LIT( KSingleGraphicHeadingMinimumSize, "CAknSingleGraphicHeadingStyleListBox::MinimumSize" );
_LIT( KSingleGraphicHeadingHandlePointer, "CAknSingleGraphicHeadingStyleListBox::HandlePointerEventL" );

_LIT( KSingleNumberHeadingSizeChanged, "CAknSingleNumberHeadingStyleListBox::SizeChanged" );
_LIT( KSingleNumberHeadingMinimumSize, "CAknSingleNumberHeadingStyleListBox::MinimumSize" );
_LIT( KSingleNumberHeadingHandlePointer, "CAknSingleNumberHeadingStyleListBox::HandlePointerEventL" );

_LIT( KSingleLargeSizeChanged, "CAknSingleNumberHeadingStyleListBox::SizeChanged" );
_LIT( KSingleLargeMinimumSize, "CAknSingleNumberHeadingStyleListBox::MinimumSize" );
_LIT( KSingleLargeHandlePointer, "CAknSingleNumberHeadingStyleListBox::HandlePointerEventL" );

_LIT( KAknColumnViewTest1, "CAknColumnListBoxView::EnableFindEmptyList" );
_LIT( KAknColumnViewTest2, "CAknColumnListBoxView::SetFindEmptyListState" );
_LIT( KAknColumnViewTest3, "CAknColumnListBoxView::CalcBottomItemIndex" );
_LIT( KAknColumnViewTest4, "CAknColumnListBoxView::DrawEmptyList" );

_LIT( KSingleHeadingViewTest1, "CSingleHeadingStyleView::Draw" );
_LIT( KSingleHeadingViewTest2, "CSingleHeadingStyleView::DrawEmptyList" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestListColumnCase* CBCTestListColumnCase::NewL( 
    CBCTestListContainer* aContainer, CEikonEnv* aEikEnv )
    {
    CBCTestListColumnCase* self = new( ELeave ) CBCTestListColumnCase( 
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
CBCTestListColumnCase::CBCTestListColumnCase( 
    CBCTestListContainer* aContainer, CEikonEnv* aEikEnv )
    : CBCTestListBaseCase( aContainer, aEikEnv )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestListColumnCase::~CBCTestListColumnCase()
    {   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestListColumnCase::ConstructL()
    {    
    BuildScriptL();
    }
    
// ---------------------------------------------------------------------------
// CBCTestListColumnCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestListColumnCase::BuildScriptL()
    {
    AddTestL( DELAY( 1 ), TEND );    
    for ( TInt i=0; i <= EBCTestCmdOutline09 - EBCTestCmdOutline01; i++ )
        {
        AddTestL( LeftCBA, KeyOK, TEND );
        AddTestL( REP( Down, i ), KeyOK, TEND );
        }      
    }
    
// ---------------------------------------------------------------------------
// CBCTestListColumnCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestListColumnCase::RunL( TInt aCmd )
    {    
    if ( aCmd < EBCTestCmdOutline01 ||
         aCmd > EBCTestCmdOutline09 )
        {
        return;
        }
    iOutlineId = aCmd;
    ReleaseCase();
    PrepareCaseL( aCmd );
    TestColumnListL( aCmd );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListColumnCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestListColumnCase::PrepareCaseL( TInt aCmd )
    {
    TInt resourceId( KBCTestListInitListResourceId );       // For listbox.    
    TBool useGraphics( EFalse );

    // Creates ListBox control object and sets resource ID.
    switch ( aCmd )
        {        
        case EBCTestCmdOutline01:
            resourceId = R_BCTESTLIST_SINGLE_1_ADD_RM;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            AssertNotNullL( iListBox, KNewSingle );
            break;

        case EBCTestCmdOutline02:
            resourceId = R_BCTESTLIST_SINGLE_NUMBER_INDICATOR;            
            iListBox = new( ELeave ) CAknSingleNumberStyleListBox();
            AssertNotNullL( iListBox, KNewSingleNumber );
            break;

        case EBCTestCmdOutline03:
            resourceId = R_BCTESTLIST_SINGLE_HEADING;
            iListBox = new( ELeave ) CAknSingleHeadingStyleListBox();
            AssertNotNullL( iListBox, KNewSingleHeading );
            break;

        case EBCTestCmdOutline04:
            resourceId = R_BCTESTLIST_SINGLE_GRAPHIC;
            useGraphics = ETrue;
            iListBox = new( ELeave ) CAknSingleGraphicStyleListBox();
            AssertNotNullL( iListBox, KNewSingleGraphic );
            break;

        case EBCTestCmdOutline05:
            resourceId = R_BCTESTLIST_SINGLE_GRAPHIC_HEADING;
            useGraphics = ETrue;
            iListBox = new( ELeave ) CAknSingleGraphicHeadingStyleListBox();
            AssertNotNullL( iListBox, KNewSingleGraphicHeading );
            break;

        case EBCTestCmdOutline06:
            resourceId = R_BCTESTLIST_SINGLE_NUMBER_HEADING;            
            iListBox = new( ELeave ) CAknSingleNumberHeadingStyleListBox();
            AssertNotNullL( iListBox, KNewSingleNumberHeading );
            break;
            
        case EBCTestCmdOutline07:
            resourceId = R_BCTESTLIST_SINGLE_LARGE_GRAPHIC;
            useGraphics = ETrue;
            iListBox = new( ELeave ) CAknSingleLargeStyleListBox();
            AssertNotNullL( iListBox, KNewSingleLarge );
            break;
            
        case EBCTestCmdOutline08:            
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            AssertNotNullL( iListBox, KNewSingleNoRes );
            break;
        case EBCTestCmdOutline09:
            resourceId = R_BCTESTLIST_SINGLE_1_ADD_RM;
            iListBox = new( ELeave ) CAknSingleStyleListBox();            
            break;               
        case EBCTestCmdOutline10:
            resourceId = R_BCTESTLIST_SINGLE_HEADING;
            iListBox = new( ELeave ) CAknSingleHeadingStyleListBox();
            break;
            
        default:
            break;
        }

    if ( iListBox )
        {
        if ( resourceId )
            {
            SetListBoxFromResourceL( iListBox, resourceId );
            }
        else
            {
            SetListBoxFromInnerDescriptionL( iListBox );
            }
            
        if ( useGraphics )
            {
            SetGraphicIconL( iListBox );
            }
        
        iContainer->SetControl( iListBox );        
        }    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListColumnCase::TestColumnListL
// ---------------------------------------------------------------------------
//
void CBCTestListColumnCase::TestColumnListL( TInt aCmd )
    {
    if ( !iListBox )
        {
        return;
        }
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos(0, 30);
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    TSize size;
    switch( aCmd )
        {
        case EBCTestCmdOutline01:
        case EBCTestCmdOutline08:
            {
            CAknSingleStyleListBox* listbox = 
                static_cast<CAknSingleStyleListBox*>( iListBox );
            listbox->SizeChanged();
            AssertTrueL( ETrue, KSingleSizeChanged );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KSingleMinimumSize );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KSingleHandlePointer );            
            }            
            break;
        case EBCTestCmdOutline02:
            {            
            CAknSingleNumberStyleListBox* listbox = 
                static_cast<CAknSingleNumberStyleListBox*>( iListBox );

            listbox->SizeChanged();
            AssertTrueL( ETrue, KSingleNumberSizeChanged );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KSingleNumberMinimumSize );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KSingleNumberHandlePointer );
            
            AknListBoxUtils::HandleItemRemovalAndPositionHighlightL(
                listbox, 0, ETrue );
            CArrayFixFlat<TInt>* indexArray = new( ELeave ) 
                CArrayFixFlat<TInt>( 5 );
            CleanupStack::PushL( indexArray );
            indexArray->AppendL( 0 );
            indexArray->AppendL( 1 );
            AknListBoxUtils::HandleItemRemovalAndPositionHighlightL(
                listbox, 0, *indexArray );
            CleanupStack::PopAndDestroy( indexArray );
            AssertTrueL( ETrue, KListBoxUtilHandleItemRemoval );
            listbox->ComponentControl( 0 );
            }
            break;
        case EBCTestCmdOutline03:
            {
            CAknSingleHeadingStyleListBox* listbox = 
                static_cast<CAknSingleHeadingStyleListBox*>( iListBox );
            listbox->SizeChanged();
            AssertTrueL( ETrue, KSingleHeadingSizeChanged );
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KSingleHeadingMinimumSize );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KSingleHeadingHandlePointer );
            CSingleHeadingStyleView* singleView = 
                static_cast<CSingleHeadingStyleView*>( listbox->View() );
            singleView->DrawEmptyList( iContainer->Rect() );
            AssertTrueL( ETrue, KSingleHeadingViewDrawEmpty );
            }
            break;
        case EBCTestCmdOutline04:
            {
            CAknSingleGraphicStyleListBox* listbox = 
                static_cast<CAknSingleGraphicStyleListBox*>( iListBox );
            listbox->SizeChanged();
            AssertTrueL( ETrue, KSingleGraphicSizeChanged );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KSingleGraphicMinimumSize );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KSingleGraphicHandlePointer );            
            }
            break;
        case EBCTestCmdOutline05:
            {
            CAknSingleGraphicHeadingStyleListBox* listbox = 
                static_cast<CAknSingleGraphicHeadingStyleListBox*>( iListBox );
            listbox->SizeChanged();
            AssertTrueL( ETrue, KSingleGraphicHeadingSizeChanged );
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KSingleGraphicHeadingMinimumSize );
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KSingleGraphicHeadingHandlePointer );
            }
            break;
        case EBCTestCmdOutline06:
            {
            CAknSingleNumberHeadingStyleListBox* listbox = 
                static_cast<CAknSingleNumberHeadingStyleListBox*>( iListBox );
            listbox->SizeChanged();
            AssertTrueL( ETrue, KSingleNumberHeadingSizeChanged );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KSingleNumberHeadingMinimumSize );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KSingleNumberHeadingHandlePointer );            
            }
            break;
        case EBCTestCmdOutline07:
            {
            CAknSingleLargeStyleListBox* listbox = 
                static_cast<CAknSingleLargeStyleListBox*>( iListBox );
            listbox->SizeChanged();
            AssertTrueL( ETrue, KSingleLargeSizeChanged );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KSingleLargeMinimumSize );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KSingleLargeHandlePointer );            
            }
        case EBCTestCmdOutline09:        
            {
            CAknSingleStyleListBox* listbox = 
                static_cast<CAknSingleStyleListBox*>( iListBox );

            // test CAknColumnListBoxView API
            CAknColumnListBoxView* view = 
                static_cast<CAknColumnListBoxView*>( listbox->View() );
            CleanupStack::PushL( view );
            
            view->EnableFindEmptyList();
            AssertTrueL( ETrue, KAknColumnViewTest1 );            
            view->SetFindEmptyListState( ETrue );
            AssertTrueL( ETrue, KAknColumnViewTest2 );            
            view->CalcBottomItemIndex();
            AssertTrueL( ETrue, KAknColumnViewTest3 );            
            view->DrawEmptyList( iContainer->Rect() );
            AssertTrueL( ETrue, KAknColumnViewTest4 );
            
            CleanupStack::Pop( view );
            }
            break;
        case EBCTestCmdOutline10:
            {
            CSingleHeadingStyleView* view = 
                static_cast<CSingleHeadingStyleView*>( iListBox->View() );
            TRect rect = iContainer->Rect();
            view->Draw( &rect );
            AssertTrueL( ETrue, KSingleHeadingViewTest1 );            
            view->DrawEmptyList( rect );
            AssertTrueL( ETrue, KSingleHeadingViewTest2 );            
            }
            break;
            
        default:
            break;           
        }
    }
    
// ---------------------------------------------------------------------------
// CBCTestListColumnCase::ReleaseCase
// ---------------------------------------------------------------------------
//
void CBCTestListColumnCase::ReleaseCase()
    {
    iContainer->ResetControl();    
    iListBox = NULL;
    }
    
// ---------------------------------------------------------------------------
// CBCTestListColumnCase::GraphicIconL
// ---------------------------------------------------------------------------
//
void CBCTestListColumnCase::GraphicIconL( CArrayPtr<CGulIcon>* aIcons )
    {
    if ( aIcons )
        {
        // Appends icon according to iOutlineId.
        switch ( iOutlineId )
            {            
            case EBCTestCmdOutline04:
            case EBCTestCmdOutline05:                            
                //Use .svg icons.
                CreateIconAndAddToArrayL(
                    aIcons, KBCTestListMifFileName,
                    EMbmBctestlistQgn_indi_marked_add,
                    EMbmBctestlistQgn_indi_marked_add_mask);
                                                                                  
                CreateIconAndAddToArrayL(
                    aIcons, KBCTestListMbmFileName,
                    EMbmBctestlistGolgo3,
                    EMbmBctestlistGolgo3_mask);
                break;
                
            case EBCTestCmdOutline07:
                CreateIconAndAddToArrayL(
                    aIcons, KBCTestListMifFileName,
                    EMbmBctestlistQgn_indi_marked_add,
                    EMbmBctestlistQgn_indi_marked_add_mask);
                CreateIconAndAddToArrayL(
                    aIcons, KBCTestListMbmFileName,
                    EMbmBctestlistGolgo2,
                    EMbmBctestlistGolgo2_mask);
                break;

            default:
                break;
            }
        }
    }
