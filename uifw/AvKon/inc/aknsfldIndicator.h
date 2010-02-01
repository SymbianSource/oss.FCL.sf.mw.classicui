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
*
*/


#ifndef __AknSearchFieldIndicator_H__
#define __AknSearchFieldIndicator_H__

// INCLUDES
#include <aknEditStateIndicator.h>
#include <AknIndicatorContainer.h>
#include <AknUtils.h>
#include "aknsfld.h"

// CONSTANTS

enum TSearchIndicatorIndex
    {
    // Must be in the same order as in avkon.rss
    ESearchSmall = 0,
    ESearchNumeric,
    ESearchPinyin,
    ESearchZhuyin,
    ESearchZhuyinSymbol,
    ESearchStrokeSimple,
    ESearchStrokeTraditional,
    ESearchStrokeSymbol,
    ESearchPredictiveJapanese,
    ESearchHiraganaKanji,
    ESearchKatakana,
    ESearchFullKatakana,
    ESearchFullSmall,
    ESearchFullNumeric,
    ESearchHiragana,
    ESearchThai,
    ESearchCangJie
    };

// FORWARD DECLARATIONS
class CAknIconArray;

/**
 * The CAknSearchFieldIndicator class implements the search mode
 * indicators used in Chinese find.
 * ONLY for internal use of CAknSearchField.
 */
NONSHARABLE_CLASS(CAknSearchFieldIndicator) : public CAknIndicatorContainer,
                                 public MAknEditingStateIndicator
    {
    public:     // constructors and destructor

        static CAknSearchFieldIndicator* NewL();
        ~CAknSearchFieldIndicator();

    public:     // functions from base classes

        // From CCoeControl
        void Draw( const TRect& aRect ) const;
        void SizeChanged();

        // From MAknEditingStateIndicator
        void SetState( TAknEditingState aState );
	    CAknIndicatorContainer* IndicatorContainer();

    public:     // new functions
    
        void SetSearchFieldStyle(CAknSearchField::TSearchFieldStyle aFlags);
    
    private:    // private constructors

        CAknSearchFieldIndicator();
        void ConstructL();

    private:    // data

        TAknLayoutRect iIndicatorLayout;
        CAknIconArray* iIndicatorArray;
        TSearchIndicatorIndex iIndicatorIndex;
        CAknSearchField::TSearchFieldStyle iFlags;
    };

#endif // __AknSearchFieldIndicator_H__
