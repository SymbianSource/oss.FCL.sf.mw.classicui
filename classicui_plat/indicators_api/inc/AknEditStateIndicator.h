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
*	Avkon Editing State Indicator Interface
*
*
*/


#ifndef AKNEDITSTATEINDICATOR_H
#define AKNEDITSTATEINDICATOR_H

#include <coemop.h>

class CAknIndicatorContainer;

enum TAknEditingState
	{
	/** No input mode */
	EStateNone,
	/** Predictive upper case input mode */
	ET9Upper,
	/** Predictive lower case input mode */
	ET9Lower,
	/** Predictive shifted input mode */
	ET9Shifted,
	/** Numeric input mode */
	ENumeric,
	/** Multitap upper case input mode */
	EMultitapUpper,
	/** Multitap lower case input mode */
	EMultitapLower,
	/** Multitap shifted input mode */	
	EMultitapShifted,
	/** Predictive Arabic input mode */
    ET9Arabic,
	/** Predictive Hebrew input mode */
    ET9Hebrew,
	/** Multitap Arabic input mode */
    EMultitapArabic, 
	/** Multitap Hebrew input mode */    
    EMultitapHebrew,
	/** Arabic-Indic numeric input mode */
    EArabicIndicNumeric,
    /** Multitap Thai input mode */
    EMultitapThai,
    /** Predictive Thai input mode */
    ET9Thai,
    /** QWERTY shifted input mode */
    EQwertyShift,
    /** Predictive Farsi and Urdu input mode */
    ET9FarsiAndUrdu,
    /** Multitap Farsi and Urdu input mode */    
    EMultitapFarsiAndUrdu,
	
	//
	// Chinese states
	//
	/** Pinyin input mode */
	EIndicatorStatePinyin =20,
	/** Zhuyin inout mode */
	EIndicatorStateZhuyin,	
	/** Stroke input mode */
	EIndicatorStateStroke,
	/** Zhuyin find input mode */	
	EIndicatorStateZhuyinFind,
	/** Stroke find input mode */    
    EIndicatorStateStrokeFind,
	/** Stroke trad input mode */    
    EIndicatorStateStrokeTrad,
	/** Cang Jie input mode */        
    EIndicatorStateCangJie,
	/** Pinyin phrase pinput mode */
	EIndicatorStatePinyinPhrase,
	/** Zhuyin phrase inout mode */
	EIndicatorStateZhuyinPhrase,	
	/** Stroke phrase input mode */
	EIndicatorStateStrokePhrase,
	/** Stroke phrase trad input mode */    
    EIndicatorStateStrokeTradPhrase,
    
    //
    // Japanese states
	//
	/** Kanji and Hiragana input mode */
    EIndicatorStateHiraganaKanji = 40,  
    /** Hiragana input mode */
    EIndicatorStateHiragana,        
    /** Half-width Katakana input mode */
    EIndicatorStateHalfKatakana,    
    /** Full-width Katakana input mode */
    EIndicatorStateFullKatakana,    
    /** Full-width LatinUpper input mode */
    EIndicatorStateFullLatinUpper,  
    /** Full-width LatinLower input mode */
    EIndicatorStateFullLatinLower,  
    /** Full-width LatinText input mode */
    EIndicatorStateFullLatinText,   
    /** Numeric input mode */
    EIndicatorStateFullNumeric,     
    /** japanese predictive mode */
    EIndicatorStateJapanesePredictive,	
    
    //
    // Vietnamese
    //
    /** Predictive Vietnamese upper case input mode */
    ET9UpperVietnamese = 60,
    /** Predictive Vietnamese lower case input mode */
    ET9LowerVietnamese,
    /** Predictive Vietnamese shifted input mode */
    ET9ShiftedVietnamese,        
    /** Multitap Vietnamese upper case input mode */
    EMultitapUpperVietnamese,
    /** Multitap Vietnamese lower case input mode */
    EMultitapLowerVietnamese,
    /** Multitap Vietnamese shifted input mode */
    EMultitapShiftedVietnamese,
    
    //
    // Hindi
    //
    /** Multitap Hindi input mode */
    EIndicatorStateMultitapHindi= 80,
    /** Predictive Hindi input mode */
    EIndicatorStatePredictiveHindi,
    EDevanagariIndicNumeric,
    
    /** Devangari Indic numeric input mode */
    EIndicatorStateHindiPhoneticUpper,
    EIndicatorStateHindiPhoneticLower,
	/** Multitap Marathi input mode */
    EIndicatorStateMultitapMarathi,
    /** Predictive Marathi input mode */
    EIndicatorStatePredictiveMarathi,
    
    // Korean
    // Multitap hangul input mode   
    EIndicatorStateHangul,
    
    // Auto Word Completion
    //
    /**  Auto Word Completion upper case input mode */
    EAutoCompleteUpper = 100,
    /**  Auto Word Completion lower case input mode */
    EAutoCompleteLower,
    /**  Auto Word Completion shifted input mode */
    EAutoCompleteShifted,
    /**   Auto Word Completion Hindi input mode */
    EAutoCompleteHindi,
    /**  Auto Word Completion Arabic input mode */
    EAutoCompleteArabic,
    /**  Auto Word Completion Hebrew input mode */
    EAutoCompleteHebrew,
    /**  Auto Word Completion Farsi - Urdu input mode */
    EAutoCompleteFarsiAndUrdu,
    /**  Auto Word Completion Thai input mode */
    EAutoCompleteThai,
    /** Auto Word Completion Vietnamese upper case input mode */
    EAutoCompleteUpperVietnamese,
    /** Auto Word Completion Vietnamese lower case input mode */
    EAutoCompleteLowerVietnamese,
    /** Auto Word Completion Vietnamese shifted input mode */
    EAutoCompleteShiftedVietnamese,
    // AutoComplete - End 

    // Fn Mode input
    /** Functionized input mode is activated for the subsequent key press **/
    EFnKeyPressed,
    /** Functionized input is enabled untill turned off **/
    EFnKeyLocked,
    
    //
    // Greek
    //
    /** Predictive Greek upper case input mode */
    ET9UpperGreek = 200,
    /** Predictive Greek lower case input mode */
    ET9LowerGreek,
    /** Predictive Greek shifted input mode */
    ET9ShiftedGreek,        
    /** Multitap Greek upper case input mode */
    EMultitapUpperGreek,
    /** Multitap Greek lower case input mode */
    EMultitapLowerGreek,
    /** Multitap Greek shifted input mode */
    EMultitapShiftedGreek,
    
    //
    // Cyrillic
    //
    /** Predictive Cyrillic upper case input mode */
    ET9UpperCyrillic = 220,
    /** Predictive Cyrillic lower case input mode */
    ET9LowerCyrillic,
    /** Predictive Cyrillic shifted input mode */
    ET9ShiftedCyrillic,        
    /** Multitap Cyrillic upper case input mode */
    EMultitapUpperCyrillic,
    /** Multitap Cyrillic lower case input mode */
    EMultitapLowerCyrillic,
    /** Multitap Cyrillic shifted input mode */
    EMultitapShiftedCyrillic,
    
    /** Hybrid indicator for easy dialing */
    EHybridModeLatin = 240
	};

/**
 * An abstact class of which virtual methods implementation should be provided for FEP component.
 */
class MAknEditingStateIndicator
	{
public:

	DECLARE_TYPE_ID(0x101F4108)

    /**
    * Sets editing state indicator state. 
    *
    * @param aState State of the editing indicator. 
    */
	virtual void SetState(TAknEditingState aState) = 0; 
	
    /**
    * Gets pointer to indicator container that contains
    * the editing state indicators.
    *
    * @return Indicator container of the editing indicators.
    */
	virtual CAknIndicatorContainer* IndicatorContainer() = 0;
	};

/**
 * This function should be called from MopSupplyObject() of those 
 * components that supply MAknEditingStateIndicator interface for FEP.
 *
 * Retrieves an object of the same type as that encapsulated in aId.
 *
 * This function is used to allow controls to ask their owners for 
 * access to other objects that they own.
 *
 * Other than in the case where NULL is returned, the object returned 
 * must be of the same object type - that is, the @c ETypeId member of 
 * the object pointed to by the pointer returned by this function must
 * be equal to the @c iUid member of @c aId.
 *
 * @param aId An encapsulated object type ID. 
 * @return Encapsulated pointer to the provided object.
 *         Note that the encapsulated pointer may be NULL. 
 */
inline TTypeUid::Ptr SupplyMopObject( TTypeUid aId,
                                  MAknEditingStateIndicator* aIndicator )
	{
    if ( aIndicator && aId.iUid == MAknEditingStateIndicator::ETypeId )
        {
        return aId.MakePtr( aIndicator );
        }

    return TTypeUid::Null();
	}

#endif
