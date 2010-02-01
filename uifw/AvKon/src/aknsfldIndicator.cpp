/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*  Implements the search mode indicators used in Chinese find.
*  Only for internal use of CAknSearchField class.
*
*/


// INCLUDES
#include "aknsfldIndicator.h"
#include <aknEditStateIndicator.h>
#include <gulicon.h>
#include <AknIconArray.h>
#include <aknenv.h>
#include <avkon.rsg>
#include <coecntrl.h>
#include <barsread.h>
    
#include <appapaclayout.cdl.h>
#include <AknIconUtils.h>
#include <AknLayout2ScalableDef.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include "akntrace.h"


// -----------------------------------------------------------------------------
// Constructors and destructor
// -----------------------------------------------------------------------------

CAknSearchFieldIndicator::CAknSearchFieldIndicator()
    : CAknIndicatorContainer( CAknIndicatorContainer::EFindIndicators )
    {
    }

CAknSearchFieldIndicator* CAknSearchFieldIndicator::NewL()
    {
    CAknSearchFieldIndicator* self = new( ELeave ) CAknSearchFieldIndicator;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

CAknSearchFieldIndicator::~CAknSearchFieldIndicator()
    {
    _AKNTRACE_FUNC_ENTER;
    delete iIndicatorArray;
    _AKNTRACE_FUNC_EXIT;
    }

void CAknSearchFieldIndicator::ConstructL()
    {
    _AKNTRACE_FUNC_ENTER;
    iIndicatorArray = new( ELeave ) CAknIconArray( 8 );

    iIndicatorArray->ConstructFromResourceL( 
        R_AVKON_FIND_PANE_INDICATOR_ICONS );

    // construct CAknIndicatorContainer base

    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader, R_AVKON_DUMMY_FIND_INDICATORS );
    ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // reader
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknSearchFieldIndicator::Draw()
// -----------------------------------------------------------------------------

void CAknSearchFieldIndicator::Draw( const TRect& /*aRect*/ ) const
    {
    // Draw the search mode indicator
    CWindowGc& gc = SystemGc();
    iIndicatorLayout.DrawImage( gc,
        (*iIndicatorArray)[ iIndicatorIndex ]->Bitmap(), NULL );
    }

// -----------------------------------------------------------------------------
// CAknSearchFieldIndicator::SizeChanged()
// -----------------------------------------------------------------------------

void CAknSearchFieldIndicator::SizeChanged()
    {
    switch ( iFlags )
        {
        case CAknSearchField::EPopup:
            iIndicatorLayout.LayoutRect( Rect(),
                                         AknLayoutScalable_Avkon::find_popup_pane());
            iIndicatorLayout.LayoutRect( iIndicatorLayout.Rect(),
                                         AknLayoutScalable_Avkon::input_popup_find_pane_cp() );    
            iIndicatorLayout.LayoutRect( iIndicatorLayout.Rect(),
                                         AknLayoutScalable_Avkon::input_popup_find_pane_g1( 0 ) );
            break;
            
        case CAknSearchField::EPopupWindow:
            iIndicatorLayout.LayoutRect( Rect(),
                                         AknLayoutScalable_Avkon::input_popup_find_pane_cp() );
            iIndicatorLayout.LayoutRect( iIndicatorLayout.Rect(),
                                         AknLayoutScalable_Avkon::input_popup_find_pane_g1( 0 ) );
            break;
            
        case CAknSearchField::EPinb:
            iIndicatorLayout.LayoutRect( Rect(),
                                         AppApacLayout::Find_pane_elements__pinb__Line_5() );
            break;
            
        case CAknSearchField::EPopupAdaptiveSearch:
            iIndicatorLayout.LayoutRect( Rect(),
                                         AKN_LAYOUT_WINDOW_Find_pop_up_window_elements_Line_5 );
            break;
            
        case CAknSearchField::EPopupAdaptiveSearchWindow:
            iIndicatorLayout.LayoutRect( Rect(),
                                         AknLayoutScalable_Avkon::input_popup_find_pane_cp() );
            iIndicatorLayout.LayoutRect( iIndicatorLayout.Rect(),
                                         AknLayoutScalable_Avkon::input_popup_find_pane_g1( 0 ) );
            break;    
            
        default: //(fixed find)
            iIndicatorLayout.LayoutRect( Rect(),
                                         AKN_LAYOUT_WINDOW_Find_pane_elements_Line_6 );
            break;
        }

    for ( TInt a=0 ; a < iIndicatorArray->Count() ; a++ )
        {
        AknIconUtils::SetSize( (*iIndicatorArray)[ a ]->Bitmap(), iIndicatorLayout.Rect().Size() );
        }

    }

// -----------------------------------------------------------------------------
// CAknSearchFieldIndicator::SetState()
// -----------------------------------------------------------------------------

void CAknSearchFieldIndicator::SetState( TAknEditingState aState )
    {
    TSearchIndicatorIndex oldIndex( iIndicatorIndex );
    _AKNTRACE( "[%s][%s] editing state is : %d", "CAknSearchFieldIndicator", __FUNCTION__, aState );

    switch ( aState )
        {
        case EMultitapLower:            // abc search
            iIndicatorIndex = ESearchSmall;
            break;

        case ENumeric:                  // number search
            iIndicatorIndex = ESearchNumeric;
            break;

        case EIndicatorStatePinyin:     // pinyin search
            iIndicatorIndex = ESearchPinyin;
            break;

        case EIndicatorStateZhuyin:     // zhuyin search
            iIndicatorIndex = ESearchZhuyin;
            break;
            
        case EIndicatorStateStroke:     // stroke search
            // for simple Chinese
            iIndicatorIndex = ESearchStrokeSimple;
            break;
            
        case EIndicatorStateCangJie:
            iIndicatorIndex = ESearchCangJie;
            break;
            
        case EIndicatorStateStrokeTrad:
            // for traditional Chinese
            iIndicatorIndex = ESearchStrokeTraditional;
            break;

        case EIndicatorStateZhuyinFind: // zhuyin symbol search
            iIndicatorIndex = ESearchZhuyinSymbol;
            break;

        case EIndicatorStateStrokeFind: // stroke symbol search
            iIndicatorIndex = ESearchStrokeSymbol;
            break;

        case EIndicatorStateJapanesePredictive:
            iIndicatorIndex = ESearchPredictiveJapanese;
            break;

        case EIndicatorStateHiraganaKanji:
            iIndicatorIndex = ESearchHiraganaKanji;
            break;

        case EIndicatorStateHalfKatakana:
            iIndicatorIndex = ESearchKatakana;
            break;

        case EIndicatorStateFullKatakana:
            iIndicatorIndex = ESearchFullKatakana;
            break;

        case EIndicatorStateFullLatinLower:
            iIndicatorIndex = ESearchFullSmall;
            break;

        case EIndicatorStateFullNumeric:
            iIndicatorIndex = ESearchFullNumeric;
            break;

        case EIndicatorStateHiragana:
            iIndicatorIndex = ESearchHiragana;
            break;

        case EMultitapThai:
            iIndicatorIndex = ESearchThai;
            break;

        default:
            break;
        }
    _AKNTRACE( "[%s][%s] indicator index is : %d", "CAknSearchFieldIndicator", __FUNCTION__, iIndicatorIndex );

    if ( iIndicatorIndex != oldIndex )
        {
        DrawDeferred(); // update the new indicator on the screen
        }
    }
    

// -----------------------------------------------------------------------------
// CAknSearchFieldIndicator::IndicatorContainer()
// -----------------------------------------------------------------------------

CAknIndicatorContainer* CAknSearchFieldIndicator::IndicatorContainer()
    {
    return this;
    }
    
void CAknSearchFieldIndicator::SetSearchFieldStyle(CAknSearchField::TSearchFieldStyle aflags)
    {
    _AKNTRACE( "[%s][%s] search field style is : %d", "CAknSearchFieldIndicator", __FUNCTION__, aflags );
    iFlags = aflags;
    }

// End of File
