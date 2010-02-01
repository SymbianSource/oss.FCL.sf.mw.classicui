// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//



// INCLUDE FILES
#include "languagespecificnumberconverter.h"
#include <e32std.h>

// ============================ MEMBER FUNCTIONS ===============================

static TChar NumberToBase(const TChar& aCharacter )
    {
    const TDigitType d[] = { EDigitTypeWestern, 
                       EDigitTypeArabicIndic, 
                       EDigitTypeEasternArabicIndic, 
                       EDigitTypeDevanagari, 
                       EDigitTypeThai };
    
    const TInt num = sizeof( d ) / sizeof( d[0] );
    
    TInt i = 0;
    while( i < num )
        {
        if (aCharacter > TChar( d[i] ) && aCharacter < TChar( d[i]+10 )) 
        	return d[i];
        
        i++;
        }
        
    return aCharacter;
    }

/**
This routine is used to convert between European digits and 
Arabic-Indic, Eastern Arabic-Indic, Devanagari or Thai digits 
based on existing digit type setting. 

@param aDes  Parameter to change
*/
void LanguageSpecificNumberConverter::Convert( TDes &aDes )
    {   
    TLocale locale;
    locale.Refresh();
    const TDigitType digitType = locale.DigitType();
    TChar toArea = 0x030;
    switch( digitType )
        {
        case EDigitTypeWestern:
        case EDigitTypeArabicIndic:
        case EDigitTypeEasternArabicIndic:
        case EDigitTypeDevanagari:
        case EDigitTypeThai:
            toArea = digitType;
            break;
        case EDigitTypeUnknown:
        case EDigitTypeAllTypes:
            return;
        }
    
    const TInt length = aDes.Length();
    for( TInt i = 0; i < length; i++ )
        {
        TChar character = aDes[i];
        TChar fromArea = NumberToBase( character );
        TChar::TBdCategory cat = character.GetBdCategory();
        switch( cat )
            {
            case TChar::EArabicNumber:
            case TChar::EEuropeanNumber:
				character += toArea;
				character -= fromArea;
                aDes[i] = TUint16( character );
                break;
            default: 
            	break;
            }
        }
    }

/**
This routine is used to convert Arabic-Indic, Eastern Arabic-Indic
or Devanagari digits to European digits. 

@param aDes Parameter to change
*/
void LanguageSpecificNumberConverter::ConvertToWesternNumbers( TDes &aDes )
    {   
    const TChar toArea = 0x030;
    const TInt KLastDevanagariDigit = 0x96F;
    const TInt KFirstDevanagariDigit = 0x966;
    const TInt length = aDes.Length();

    for( TInt i=0; i<length; i++ )
        {
        TChar character = aDes[i];
        TChar fromArea = NumberToBase( character );
        TChar::TBdCategory cat = character.GetBdCategory();

        if ( cat == TChar::EArabicNumber || cat == TChar::EEuropeanNumber ||
           ( KFirstDevanagariDigit <= character && character <= KLastDevanagariDigit ) )
            {
            character += toArea;
			character -= fromArea;
            aDes[i] = TUint16( character );    
            }        
        }
    }

/**
This routine is used to check if conversion of digits is needed.
Conversion is needed if user language is   
- Arabic, Urdu or Farsi and if digit type is Arabic-Indic
- Urdu or Farsi and digit type is Eastern Arabic_indic
- Hindi and digit type is Devanagari. 

@return  ETrue if conversion is needed, EFalse if not
*/
TBool LanguageSpecificNumberConverter::IsConversionNeeded()
	{
    TLocale locale;
    locale.Refresh();
    const TLanguage language = User::Language();
	const TDigitType digitType = locale.DigitType();
    
    if ( ( ( language == ELangArabic || language == ELangUrdu || language == ELangFarsi ) &&
         digitType == EDigitTypeArabicIndic ) 
         || ( ( language == ELangUrdu || language == ELangFarsi ) &&
         digitType == EDigitTypeEasternArabicIndic )
         || ( language == ELangHindi && digitType == EDigitTypeDevanagari )
        )
        {
        return ETrue;
        }

	return EFalse;
	}


// End of File
