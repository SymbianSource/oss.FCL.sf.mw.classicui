/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:         Korean Find Utilities implementation.
*
*/


#include "FindUtilKorean.h"

const TInt KSBase = 0xac00; // base address for hangul syllables
const TInt KLBase = 0x1100; // base address for L-jamo
const TInt KVBase = 0x1161; // base address for V-jamo
const TInt KTBase = 0x11a7; // base address for T-jamo
const TInt KCBase = 0x3131; // base address for hangul compatibility jamo

const TInt KLCount = 19; // count of L-jamos
const TInt KVCount = 21; // count of V-jamos
const TInt KTCount = 28; // count of T-jamos
const TInt KNCount = KVCount * KTCount; // count of V&T-jamo combinations
const TInt KSCount = KLCount * KNCount; // total count of hangul syllables

const TInt KMaxLengthDecomposedSyllable = 3; // syllable can contain 3 jamos

const TInt KLitTab('\t'); // word separator: <tab>
const TInt KLitSpace(' '); // word separator: <space>
const TInt KLitHyphen('-'); // word separator: <hyphen>
const TInt KLitStar('*'); // wildcard matching: <star>
const TInt KLitQuestion('?'); // wildcard matching <question>

// Conversion table for hangul compatibility jamo
const TUint16 conversionTableFromCompatibilityJamoToJamo[] = {
0x1100,
0x1101,
0x11AA,
0x1102,
0x11AC,
0x11AD,
0x1103,
0x1104,
0x1105,
0x11B0,
0x11B1,
0x11B2,
0x11B3,
0x11B4,
0x11B5,
0x11B6,
0x1106,
0x1107,
0x1108,
0x11B9,
0x1109,
0x110A,
0x110B,
0x110C,
0x110D,
0x110E,
0x110F,
0x1110,
0x1111,
0x1112,
0x1161,
0x1162,
0x1163,
0x1164,
0x1165,
0x1166,
0x1167,
0x1168,
0x1169,
0x116A,
0x116B,
0x116C,
0x116D,
0x116E,
0x116F,
0x1170,
0x1171,
0x1172,
0x1173,
0x1174,
0x1175,
};

#define KCCount (sizeof(conversionTableFromCompatibilityJamoToJamo) / sizeof(TUint16))

// ============================ MEMBER FUNCTIONS =============================


// ---------------------------------------------------------------------------
// Symbian constructor
// ---------------------------------------------------------------------------
//
CFindUtilKorean* CFindUtilKorean::NewL()
    {
    CFindUtilKorean* self = new ( ELeave ) CFindUtilKorean();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// Symbian second-phase constructor
// ---------------------------------------------------------------------------
//
void CFindUtilKorean::ConstructL()
    {
    }

// ---------------------------------------------------------------------------
// Default constructor
// ---------------------------------------------------------------------------
//
CFindUtilKorean::CFindUtilKorean()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CFindUtilKorean::~CFindUtilKorean()
    {
    }

// ---------------------------------------------------------------------------
// Checks that is given character korean language or not.
// ---------------------------------------------------------------------------
//
TBool CFindUtilKorean::IsKoreanLanguage( const TDesC& aDes )
    {
    for ( TInt i = 0; i < aDes.Length(); i++ )
    	{
    	if ( IsHangulSyllable( aDes[ i ] ) || IsHangulCompatibilityJamo( aDes[ i ] ) )
    		{
    		return ETrue;
    		}
    	}

    return EFalse;
    }

// ---------------------------------------------------------------------------
// Compares two strings against others.
// ---------------------------------------------------------------------------
//
TBool CFindUtilKorean::IsFindMatchL( 
    const TDesC& aItemString, 
    const TDesC& aSearchText )
    {
    TBool result( EFalse );
    
    // To disable the wildchar matching provided by MatchC.
    if ( KErrNotFound != aSearchText.Locate( KLitQuestion ) && 
        KErrNotFound != aSearchText.Locate( KLitStar ) )
    	{
    	return EFalse;
    	}
    
    // Convert aItemString to single jamo's.
    HBufC* itemString = HBufC::NewLC( aItemString.Length() * KMaxLengthDecomposedSyllable );
    DecomposeToPlainJamos( aItemString, itemString );
    
    HBufC* searchText = HBufC::NewLC( aSearchText.Length() * KMaxLengthDecomposedSyllable + 2 );
    searchText->Des().Append( KLitStar );

    // Convert aSearchText to single jamo's.
    DecomposeToPlainJamos( aSearchText, searchText );
    searchText->Des().Append( KLitStar );
    
    // Compare strings containing plain jamo's against others.
    for ( TInt i = 0; i < itemString->Length() && !result; i++ )
        {
        if ( 0 == i || IsFindWordSeparator( 
            static_cast<TChar>( itemString->Des()[ i - 1 ] ) ) )
            {
            if ( KErrNotFound != itemString->Mid( i ).MatchC( *searchText ) )
                {
                result = ETrue; // match found
                }
            }
        }
    
    CleanupStack::PopAndDestroy( searchText );
    CleanupStack::PopAndDestroy( itemString );
    
    return result;    
    }

// ---------------------------------------------------------------------------
// Decomposes given string to plain jamos.
// ---------------------------------------------------------------------------
//
void CFindUtilKorean::DecomposeToPlainJamos( 
    const TDesC& aString,
    HBufC* aDecomposedString )
    {
    // Go thought all characters and decompose if needed.
    for ( TInt i = 0; i < aString.Length(); i++ )
        {
        // If character is 'hangul syllable', decompose it to single jamos.
        if ( IsHangulSyllable( aString[ i ] ) )
            {
            TBuf<KMaxLengthDecomposedSyllable> buf ( KNullDesC );
            Decompose( aString[ i ], buf );
            aDecomposedString->Des().Append( buf );
            }
        else if ( IsHangulCompatibilityJamo( aString[ i ] ) )
	        {
	        TUint16 jamo = conversionTableFromCompatibilityJamoToJamo[ aString[i] - KCBase ];
	        aDecomposedString->Des().Append( jamo );	
	        }
        // Otherwise append character directly to 'decomposed string'.
        else
            {
            aDecomposedString->Des().Append( aString[ i ] );
            }
        }
    }

// ---------------------------------------------------------------------------
// Decomposes hangul syllables to single jamos.
// ---------------------------------------------------------------------------
//
void CFindUtilKorean::Decompose( TChar aChar, TDes& aDecomposedString )
    {
    // Calculate single jamo's.
    TInt index = static_cast<TInt> ( aChar ) - KSBase;
    TInt l = KLBase + index / KNCount;
    TInt v = KVBase + ( index % KNCount ) / KTCount;
    TInt t = KTBase + index % KTCount;
    
    // Append single jamo's to 'decomposed string'.
    aDecomposedString.Append( static_cast<TChar> ( l ) );
    aDecomposedString.Append( static_cast<TChar> ( v ) );
    if ( t != KTBase )
        {
        aDecomposedString.Append( static_cast<TChar> ( t ) );
        }
    }

// ---------------------------------------------------------------------------
// Checks that is given character hangul syllable or not.
// ---------------------------------------------------------------------------
//
TBool CFindUtilKorean::IsHangulSyllable( TChar aChar )
    {
    // Character is 'hangul syllable' 
    // if it's numeric value is between KSBase and KSBase + KSCount.
    TInt index = static_cast<TInt> ( aChar ) - KSBase;
    if ( index < 0 || index >= KSCount )
        {
        return EFalse;
        }
    return ETrue;
    }

// ---------------------------------------------------------------------------
// Checks that is given character word separator or not.
// ---------------------------------------------------------------------------
//
TBool CFindUtilKorean::IsFindWordSeparator( TChar aChar )
    {
    return aChar == KLitSpace || aChar == KLitHyphen || aChar == KLitTab;
    }


// ---------------------------------------------------------------------------
// Checks that is given character hangul syllable or not.
// ---------------------------------------------------------------------------
//
TBool CFindUtilKorean::IsHangulCompatibilityJamo( TChar aChar )
    {
    // Character is 'hangul compatibility jamo' 
    // if it's numeric value is between KCBase and KCBase + KCCount.
    TInt index = static_cast<TInt> ( aChar ) - KCBase;
    if ( index < 0 || index >= KCCount )
        {
        return EFalse;
        }
    return ETrue;
    }
	
// ---------------------------------------------------------------------------
// It tests a matching.
// ---------------------------------------------------------------------------
//
TBool CFindUtilKorean::Match( const TDesC& aContactsField, const TDesC& aWord )
    {
    TBool retVal = EFalse;
    // Match does not occur if string where search is made,
    // does not contain any characters.
    if ( aContactsField.Length() )
        {
       // In case that both of strings contain some characters,
       // matching is made with function below.
      TRAPD(err, retVal = IsFindMatchL( aContactsField, aWord ));
    	
      if (err != KErrNone)
    	{
    	retVal = EFalse;
    	}
        }
	
   return retVal;
    }


// ---------------------------------------------------------------------------
// It tests a partial matching.
// ---------------------------------------------------------------------------
//
TBool CFindUtilKorean::MatchRefineL( 
    const TDesC& aItemString, 
    const TDesC& aSearchText )
    {
    // Match does not occur if string where search is made,
    // does not contain any characters.
    if ( aItemString.Length() == 0 )
        {
        return EFalse;
        }

    // Match occurs if string to be used in searching, 
    // does not contain any characters.
    if ( aSearchText.Length() == 0 )
        {
        return ETrue;
        }

    // In case that both of strings contain some characters,
    // matching is made with function below.
    return IsFindMatchL( aItemString, aSearchText );
    }

// -----------------------------------------------------------------------------
// CFindUtilKorean::MatchAdaptiveRefineL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//  
TBool CFindUtilKorean::MatchAdaptiveRefineL( const TDesC& /*aItemString*/, 
	const TDesC& /*aSearchText*/, HBufC*& /*aNextChars*/ )
	{
	return 0;	
	}

// ---------------------------------------------------------------------------
// It checks whether aWord is valid.
// ---------------------------------------------------------------------------
//
TBool CFindUtilKorean::IsWordValidForMatching( const TDesC& /*aWord*/ )
    {
    return ETrue;
    }

// End of file
