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
*
*/


#include <barsread.h>
#include "aknenv.h"
#include "avkon.hrh"
#include <avkon.rsg>
#include "AknUtils.h"
#include "aknqueryeditorindicator.h"
#include "aknQueryControl.h"

#include <AknTasHook.h> // for testability hooks
//
// CAknQueryEditIndicator
//  Handles editor indicator for queries
CAknQueryEditIndicator* CAknQueryEditIndicator::NewL(CCoeControl* aControl)
    {
    CAknQueryEditIndicator* self = new(ELeave)CAknQueryEditIndicator();
    CleanupStack::PushL(self);
    self->ConstructL(aControl);
    CleanupStack::Pop();    //self
    AKNTASHOOK_ADDL( self, "CAknQueryEditIndicator" );
    return self;
    }

CAknQueryEditIndicator::~CAknQueryEditIndicator()
    {
    AKNTASHOOK_REMOVE();
    }

CAknQueryEditIndicator::CAknQueryEditIndicator()
    : CAknIndicatorContainer(CAknIndicatorContainer::EQueryEditorIndicators),
    iQueryType(-1)
    {
    }

void CAknQueryEditIndicator::ConstructL(CCoeControl* aControl)
    {
    if ( CAknEnv::Static()->TransparencyEnabled() )
        {
        // In transparency everything broke when this had its own
        // window.
        SetContainerWindowL( *aControl );
        }
    else
        {
        CreateWindowL(aControl);
        }
    
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader, R_AVKON_NAVI_PANE_EDITOR_INDICATORS);
    ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();  // resource reader

    // Set to zero size - derived queries must set extent in PreDynInitLayout
    SetExtent(TPoint(0,0), TSize(0,0));
    ActivateL();
    }

void CAknQueryEditIndicator::SetState(TAknEditingState aState)
    {
    iState = aState;
    if (Observer())
    	{
    	Observer()->HandleControlEventL( this, MCoeControlObserver::EEventStateChanged );
    	}
    
    if ( iFlags.IsSet(CAknQueryControl::EEditorIndicatorOff) )
        {
        return;
        }

    if ( AknLayoutUtils::Variant() == EEuropeanVariant )
        {
        TBool t9IsOn = ((aState >= ET9Upper) && (aState <= ET9Shifted) || 
            aState == ET9FarsiAndUrdu || aState == ET9Arabic || aState == ET9Hebrew 
            || aState == ET9Thai || aState == EIndicatorStatePredictiveHindi
#ifdef RD_MARATHI
            || aState == EIndicatorStatePredictiveMarathi
#endif
            );
        TBool upper = (( aState == ET9Upper) || ( aState == EMultitapUpper));
        TBool lower = (( aState == ET9Lower) || ( aState == EMultitapLower));
        TBool shifted = (( aState == ET9Shifted) || ( aState == EMultitapShifted));
        TBool arabic = (( aState == ET9Arabic ) || (aState == EMultitapArabic ));
        TBool hebrew = (( aState == ET9Hebrew ) || (aState == EMultitapHebrew ));
        TBool farsiandurdu = (( aState == ET9FarsiAndUrdu ) || (aState == EMultitapFarsiAndUrdu ));

    	TBool hindi = (( aState == EIndicatorStatePredictiveHindi ) || (aState == EIndicatorStateMultitapHindi ));

        TBool thai = (( aState == ET9Thai ) || (aState == EMultitapThai ));
#ifdef RD_MARATHI
    	TBool marathi = (( aState == EIndicatorStatePredictiveMarathi ) || (aState == EIndicatorStateMultitapMarathi ));
#endif

        SetIndicator(EAknNaviPaneEditorIndicatorTextCase, 
            shifted ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorLowerCase, 
            lower ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorUpperCase, 
            upper ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorArabicCase, 
            arabic ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorHebrewCase, 
            hebrew ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorFarsiAndUrduCase, 
            farsiandurdu
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);

        // for Hindi ( One of a call for setindicator for Hindi Language needs 
		// to be removed)    
        SetIndicator(EAknNaviPaneEditorIndicatorDevanagariCase,
        	hindi
        	? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse); 
        SetIndicator(EAknNaviPaneEditorIndicatorDevanagariIndicNumberCase, 
            (aState == EDevanagariIndicNumeric) ? EAknIndicatorStateOn : EAknIndicatorStateOff, 
            EFalse);	   

SetIndicator(EAknNaviPaneEditorIndicatorThai, 
            thai
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse); 

#ifdef RD_MARATHI
        SetIndicator(EAknNaviPaneEditorIndicatorDevanagariCase,
        	marathi
        	? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse); 
        SetIndicator(EAknNaviPaneEditorIndicatorDevanagariIndicNumberCase, 
            (aState == EDevanagariIndicNumeric) ? EAknIndicatorStateOn : EAknIndicatorStateOff, 
            EFalse);
#endif

#ifdef RD_HINDI_PHONETIC_INPUT
SetIndicator(EAknNaviPaneEditorIndicatorDevanagariPhoneticUpperCase,
            (aState == EIndicatorStateHindiPhoneticUpper) ? EAknIndicatorStateOn : EAknIndicatorStateOff,
            EFalse); 
        SetIndicator(EAknNaviPaneEditorIndicatorDevanagariPhoneticLowerCase, 
            (aState == EIndicatorStateHindiPhoneticLower) ? EAknIndicatorStateOn : EAknIndicatorStateOff, 
            EFalse);
#endif

        SetIndicator(EAknNaviPaneEditorIndicatorNumberCase, 
            (aState == ENumeric) ? EAknIndicatorStateOn : EAknIndicatorStateOff, 
            EFalse);    
        SetIndicator(EAknNaviPaneEditorIndicatorArabicIndicNumberCase, 
            (aState == EArabicIndicNumeric) ? EAknIndicatorStateOn : EAknIndicatorStateOff, 
            EFalse);    
        SetIndicator(EAknNaviPaneEditorIndicatorQuery, 
            (t9IsOn || aState == EStateNone)  ? 
            EAknIndicatorStateOff : EAknIndicatorStateOn, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorT9, 
            t9IsOn ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        }
    else    // APAC
        {
        TBool query = !( aState == EIndicatorStatePinyin ||
            aState == EIndicatorStateZhuyin ||
			aState == EIndicatorStateZhuyinFind ||
			aState == EIndicatorStateStrokeFind ||
            aState == EIndicatorStateStroke ||
			aState == EIndicatorStateCangJie ||
            aState == EIndicatorStateStrokeTrad ||
            aState == EIndicatorStatePinyinPhrase ||
            aState == EIndicatorStateZhuyinPhrase ||
            aState == EIndicatorStateStrokePhrase ||
            aState == EIndicatorStateStrokeTradPhrase ||
            aState == EIndicatorStateJapanesePredictive); 
        TBool thai = (( aState == ET9Thai ) || (aState == EMultitapThai ));

		TBool hindi = (( aState == EIndicatorStatePredictiveHindi ) || (aState == EIndicatorStateMultitapHindi ));

#ifdef RD_MARATHI 
        TBool marathi = (( aState == EIndicatorStatePredictiveMarathi ) || (aState == EIndicatorStateMultitapMarathi ));
#endif
               
        SetIndicator(EAknNaviPaneEditorIndicatorNumberCase, 
            (aState == ENumeric) 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff,  EFalse);
        
        TBool upper = (( aState == ET9Upper) || ( aState == EMultitapUpper));
        TBool lower = (( aState == ET9Lower) || ( aState == EMultitapLower));
        TBool shifted = (( aState == ET9Shifted) || ( aState == EMultitapShifted));
        SetIndicator(EAknNaviPaneEditorIndicatorLowerCase, 
            lower
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorUpperCase, 
            upper
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);        
        SetIndicator(EAknNaviPaneEditorIndicatorTextCase, 
            shifted 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        
        TBool predictiveMode = 
            (( aState == EIndicatorStatePinyin) ||
             ( aState == EIndicatorStateZhuyin) ||
             ( aState == EIndicatorStateZhuyinFind) ||
             ( aState == EIndicatorStateStrokeFind) ||
             ( aState == EIndicatorStateStroke) || 
			 ( aState == EIndicatorStateCangJie) ||
             ( aState == EIndicatorStateStrokeTrad) || 
             ( aState == EIndicatorStatePinyinPhrase) ||
             ( aState == EIndicatorStateZhuyinPhrase) ||
             ( aState == EIndicatorStateStrokePhrase) ||  
             ( aState == EIndicatorStateStrokeTradPhrase) ||           
             ( aState == ET9Upper) ||
             ( aState == ET9Shifted) ||
             ( aState == ET9Lower) ||
             ( aState == ET9Arabic) ||
             ( aState == ET9Hebrew) ||
             ( aState == ET9Thai) ||

             ( aState == EIndicatorStatePredictiveHindi) ||

#ifdef RD_MARATHI
             ( aState == EIndicatorStatePredictiveMarathi) ||
#endif
             ( aState == EIndicatorStateJapanesePredictive) ||
             ( aState == ET9UpperVietnamese) ||
             ( aState == ET9LowerVietnamese) ||
             ( aState == EMultitapShiftedVietnamese) );                     
                
        SetIndicator(EAknNaviPaneEditorIndicatorQuery, 
            (!predictiveMode) && query && (aState != EStateNone)
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorT9,             
            predictiveMode
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
            
        SetIndicator(EAknNaviPaneEditorIndicatorThai, 
            thai
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);    
        SetIndicator(EAknNaviPaneEditorIndicatorPinyin, 
            aState == EIndicatorStatePinyin 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorPinyinPhrase, 
            aState == EIndicatorStatePinyinPhrase 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);            
        SetIndicator(EAknNaviPaneEditorIndicatorZhuyin, 
            aState == EIndicatorStateZhuyin 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorZhuyinPhrase, 
            aState == EIndicatorStateZhuyinPhrase 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
		// for japanese
        SetIndicator(EAknNaviPaneEditorIndicatorJapaneseHiraganaKanji, 
            (aState == EIndicatorStateHiraganaKanji || aState == EIndicatorStateJapanesePredictive)
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorJapaneseFullKatakana, 
            aState == EIndicatorStateFullKatakana 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorJapaneseHalfKatakana, 
            aState == EIndicatorStateHalfKatakana 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorJapaneseFullTextAlphabet, 
            aState == EIndicatorStateFullLatinText 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorJapaneseFullUpperAlphabet, 
            aState == EIndicatorStateFullLatinUpper 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorJapaneseFullLowerAlphabet, 
            aState == EIndicatorStateFullLatinLower 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorJapaneseFullNumeric, 
            aState == EIndicatorStateFullNumeric 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorJapaneseHiragana, 
            aState == EIndicatorStateHiragana 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);

        SetIndicator(EAknNaviPaneEditorIndicatorStroke, 
            aState == EIndicatorStateStroke 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);

        SetIndicator(EAknNaviPaneEditorIndicatorStrokeTradPhrase, 
            aState == EIndicatorStateStrokeTradPhrase 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
            
        SetIndicator(EAknNaviPaneEditorIndicatorStrokePhrase, 
            aState == EIndicatorStateStrokePhrase 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);

        SetIndicator(EAknNaviPaneEditorIndicatorCangJie, 
            aState == EIndicatorStateCangJie 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);

        SetIndicator(EAknNaviPaneEditorIndicatorStrokeTrad, 
            aState == EIndicatorStateStrokeTrad 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);

        SetIndicator(EAknNaviPaneEditorIndicatorZhuyinFind, 
            aState == EIndicatorStateZhuyinFind 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorStrokeFind, 
            aState == EIndicatorStateStrokeFind 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);

		// for Hindi ( One of a call for setindicator for Hindi Language needs 
		// to be removed)
		SetIndicator(EAknNaviPaneEditorIndicatorDevanagariCase,
        	hindi
        	? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorDevanagariIndicNumberCase, 
            (aState == EDevanagariIndicNumeric) ? EAknIndicatorStateOn : EAknIndicatorStateOff, 
            EFalse);	

        SetIndicator(EAknNaviPaneEditorIndicatorKoreanHangul, 
            aState == EIndicatorStateHangul 
            ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);

#ifdef RD_MARATHI
		SetIndicator(EAknNaviPaneEditorIndicatorDevanagariCase,
        	marathi
        	? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);
        SetIndicator(EAknNaviPaneEditorIndicatorDevanagariIndicNumberCase, 
            (aState == EDevanagariIndicNumeric) ? EAknIndicatorStateOn : EAknIndicatorStateOff, 
            EFalse);	
#endif        
        }

    SetIndicator(EAknNaviPaneEditorIndicatorQwertyShift, 
        aState == EQwertyShift ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse);

#ifdef RD_INTELLIGENT_TEXT_INPUT
	SetIndicator(EAknNaviPaneEditorIndicatorFnKeyPressed,
            (aState == EFnKeyPressed) ? EAknIndicatorStateOn : EAknIndicatorStateOff,
            EFalse); 
    SetIndicator(EAknNaviPaneEditorIndicatorFnKeyLocked, 
            (aState == EFnKeyLocked) ? EAknIndicatorStateOn : EAknIndicatorStateOff, 
            EFalse);
#endif
    // for Vietnamese
    TBool upperVietnamese = ( (aState == ET9UpperVietnamese) || (aState == EMultitapUpperVietnamese) );
    TBool lowerVietnamese = ( (aState == ET9LowerVietnamese) || (aState == EMultitapLowerVietnamese) );
    TBool shiftedVietnamese = ( (aState == ET9ShiftedVietnamese) || (aState == EMultitapShiftedVietnamese) );

    SetIndicator( EAknNaviPaneEditorIndicatorVietnameseTextCase,
        shiftedVietnamese ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse );
    SetIndicator( EAknNaviPaneEditorIndicatorVietnameseLowerCase,
        lowerVietnamese ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse );
    SetIndicator( EAknNaviPaneEditorIndicatorVietnameseUpperCase,
        upperVietnamese ? EAknIndicatorStateOn : EAknIndicatorStateOff, EFalse );
     
    if( CAknEnv::Static()->TransparencyEnabled() )
        {
        CWindowGc& controlGc = SystemGc();
        CWindowGc& systemGc = iCoeEnv->SystemGc();
        // If Gc's do not match there is ongoing transition effect.
        // Drawing indicator will cause background flicker in that 
        // situation.
        if( &controlGc == &systemGc )
            {
            DrawDeferred();
            }
        }
    else
        {
        DrawDeferred();
        }
    }

CAknIndicatorContainer* CAknQueryEditIndicator::IndicatorContainer()
    {
    return this;
    }


void CAknQueryEditIndicator::SetIndicator(TInt aIndicator, TInt aState, TBool aDrawNow)
    {
    SetIndicatorState(TUid::Uid(aIndicator), aState, aDrawNow);
    }

void CAknQueryEditIndicator::SetFlags(TBitFlags16 aFlags)
    {
    iFlags = aFlags;
    }
    
TAknEditingState CAknQueryEditIndicator::State()
	{
	return iState;
	}
	
void CAknQueryEditIndicator::SetQueryType(TInt aQueryType)
	{
	iQueryType = aQueryType;
	}
	
void CAknQueryEditIndicator::HandlePointerEventL( const TPointerEvent& aPointerEvent )
	{
	CAknIndicatorContainer::HandlePointerEventL( aPointerEvent );
	}

// End of File
