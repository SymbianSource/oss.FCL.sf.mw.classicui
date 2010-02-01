/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Floating point field for CEikMfne
*
*/


// INCLUDE FILES
#include <e32math.h>
#include <AknUtils.h>
#include <numberconversion.h>

#include "aknmfnefloat.h"

namespace {

const TInt KNumOtherSymbols( 2 ); // +/- and decimal point
const TInt KTextBufferSize( 32 ); // should be enough
const TInt KEventCodeStarSign( 42 );
const TInt KEventCodeMinusSign( 45 );
const TInt KKeyToMatchPoint( 35 ); // Shift/Hash

#if defined(_DEBUG)
void Panic(TInt aReason)
    {
    _LIT(KPanicCategory, "MFNE_FLT2");
    User::Panic(KPanicCategory, aReason);
    }
#endif
    
TReal Nan()
    {
    TRealX nan;
    nan.SetNaN();
    return nan;
    }

TBool IsAnyDigit(TChar aCharacter)
	{
	return (aCharacter.GetNumericValue() != KErrNotFound);
	}
}


CAknMfneFloat::CAknMfneFloat( TInt aMaxFractionalDigits ) : 
        iMaxFractionalDigits( aMaxFractionalDigits )
    {
    __ASSERT_DEBUG( aMaxFractionalDigits > 0, Panic( KErrArgument ) );
    }


CAknMfneFloat::~CAknMfneFloat()
    {
    delete iText;
    }


CAknMfneFloat* CAknMfneFloat::NewL( TInt aMaxFractionalDigits )
    {
    CAknMfneFloat* self = new ( ELeave )
        CAknMfneFloat( aMaxFractionalDigits );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    }


void CAknMfneFloat::ConstructL()
    {
    iText = HBufC::NewL( KTextBufferSize );
    RefreshDigitType();
    UpdateAllowedInput();
    }
    
// ---------------------------------------------------------
// Makes sure that the value in the editor is normalized,
// i.e. within limits and formatted correctly.
// ---------------------------------------------------------
TBool CAknMfneFloat::SetTextFromValueAndNormalize( TReal aValue )
    {
    TBool reportError( EFalse );
    TPtr ptr( iText->Des() );
    
    if ( Math::IsNaN( aValue ) && !( iFlags & EAllowNaN ) )
        {
        aValue = iMaximumValue;
        reportError = ETrue;
        }
        
    if ( !Math::IsNaN( aValue ) )
        {
        // 1) Check the minimum and maximum limits
        if ( aValue < iMinimumValue )
            {
            aValue = iMinimumValue;
            reportError = ETrue;
            }
        else if ( aValue > iMaximumValue )
            {
            aValue = iMaximumValue;
            reportError = ETrue;
            }
            
        // 2) Round according to iMaxFractionalDigits
        TReal roundedValue;
        Math::Round( roundedValue, aValue, iMaxFractionalDigits );

        // 3) Enforce the limits in case change in fractional digits
        //    causes erroneous rounding. An example case is where
        //    max limit = 1.56, value = 1.55, max frac digits becomes = 1
        //    roundedValue = 1.6 ( > max limit, no good )
        TReal corrector;
        Math::Pow10( corrector, -iMaxFractionalDigits );
        
        if ( roundedValue > iMaximumValue )
            {
            roundedValue -= corrector;
            }
        else if ( roundedValue < iMinimumValue )
            {
            roundedValue += corrector;
            }

        // 4) Convert real value to a string, TRealFormat is mandatory
        TRealFormat format;
        format.iType   = KRealFormatFixed;
        format.iTriLen = 0; // no triad separations
        format.iWidth  = MaxNumOfChars();
        format.iPlaces = ( roundedValue == 0 ) ? 0 : iMaxFractionalDigits;

        ptr.Num( roundedValue, format );
        
        // 5) Cut trailing zeroes and separator from decimal part
        TChar decimalSeparator( DecimalSeparator() );
        TInt separatorPos = ptr.Locate( decimalSeparator );
        
        if ( separatorPos != KErrNotFound )
            {
            TInt len = ptr.Length();
            
            while ( len > separatorPos && ( ptr[len-1] == '0' || ptr[len-1] == decimalSeparator ) )
                {
                len--;
                }
            
            ptr.SetLength( len );
            }

        // 6) Finally convert to iDigitType
        AknTextUtils::ConvertDigitsTo( ptr, iDigitType );
        }
    else
        {
        iText->Des().Zero();
        }

    iIsBeingEditedWithCursor = EFalse;
    
    UpdateAllowedInput();
    
    return reportError;         
    }

TChar CAknMfneFloat::DecimalSeparator() const
    {
    TLocale locale;
    return locale.DecimalSeparator();
    }

void CAknMfneFloat::UpdateAllowedInput()
    {
    TInt textLength = iText->Length();
    
    // Various highly annoyingly non-generic cases:
    // 1) Highlighted or "": Allow conditional digit and conditional minus sign
    // 2) Starts with only "0" or "-0": Allow only conditional decimal separator
    // 3) Starts with only "-": Allow only digit
    // 4) Allow digits depending on the length of integer and fractional part
    
    TInt decimalSeparatorFlag = ( iMaxFractionalDigits > 0 ? EDecimalSeparator : 0 );
    TInt minusSignFlag = ( iMinimumValue < 0 ? EMinusSign : 0 );

    // 1) .. and return without doing anything else
    if ( !iIsBeingEditedWithCursor || textLength == 0 )
        {
        iAllowedInputFlags = minusSignFlag | ( iMaximumValue >= 0 ? EDigit : 0 );
        return;
        }
        
    // 2) .. also return without doing anything else
    TBuf<2> minusAndZero;
    minusAndZero.Append( iMinusSign );
    minusAndZero.Append( iZero );
    
    if ( textLength == 1 && (*iText)[0] == iZero ||
         iText->Des() == minusAndZero )
        {
        iAllowedInputFlags = decimalSeparatorFlag;
        return;
        }
        
    // 3) .. also return without doing anything else
    if ( textLength == 1 && (*iText)[0] == iMinusSign )
        {
        iAllowedInputFlags = EDigit;
        return;
        }

    TChar separator( DecimalSeparator() );
    TChar lastChar( 0 );
    TInt separatorPos( KErrNotFound );
    TInt minusPos( KErrNotFound );
    TInt integerDigits( 0 );
    TInt fractionalDigits( 0 );
    
    // For 4), more info needed, find everything in one loop
    for ( TInt i = 0; i < textLength; ++i )
        {
        lastChar = (*iText)[i];
        
        if ( IsAnyDigit( lastChar ) )
            {
            if ( separatorPos >= 0 )
                {
                fractionalDigits++;    
                }
            else
                {
                integerDigits++;
                }
            }
        else if ( lastChar == iMinusSign )
            {
            minusPos = i;
            }
        else if ( lastChar == separator )
            {
            separatorPos = i;
            }
        }
    
    iAllowedInputFlags = 0;
    
    // 4)
    if ( separatorPos < 0 )
        {
        iAllowedInputFlags = decimalSeparatorFlag;
        
        if ( ( minusPos >= 0 && integerDigits < iMaxNegativeIntegerDigits ) ||
             ( minusPos < 0 && integerDigits < iMaxPositiveIntegerDigits ) )
            {
            iAllowedInputFlags |= EDigit;
            }        
        }
    else if ( fractionalDigits < iMaxFractionalDigits )
        {
        iAllowedInputFlags = EDigit;
        }
    }


void CAknMfneFloat::ClearFieldIfNecessary( TBool& aDataAltered )
    {
    if ( !iIsBeingEditedWithCursor )
        {
        iIsBeingEditedWithCursor = ETrue;
        TPtr ptr( iText->Des() );
        ptr.Zero();
        UpdateAllowedInput();
        aDataAltered = ETrue;
        }
    }
    
    
void CAknMfneFloat::TryAppend( TChar aChar, TUint aAllowedFlags, TBool& aDataAltered )
    {
    if ( iAllowedInputFlags & aAllowedFlags )
        {
        ClearFieldIfNecessary( aDataAltered );
        iText->Des().Append( aChar );
        aDataAltered = ETrue;
        }
    }
    
    
void CAknMfneFloat::TryDelete( TInt aDigits, TBool& aDataAltered )
    {
    ClearFieldIfNecessary( aDataAltered );
    
    TPtr ptr( iText->Des() );
    TInt delLength( ptr.Length() - aDigits );
    
    if ( delLength >= 0 )
        {
        ptr.SetLength( delLength );
        aDataAltered = ETrue;
        }
    }

TChar CAknMfneFloat::NormalizeDigit( TChar aChar ) const
	{
	TBuf<1> buf;
	buf.Append( aChar );
	NumberConversion::ConvertDigits( buf, iDigitType );
	return buf[0];
	}    

TBool CAknMfneFloat::SetLimits(
    TReal aMinimumValue, 
    TReal aMaximumValue)
    {
    __ASSERT_DEBUG(
        Math::IsNaN(aMinimumValue) ||
        Math::IsNaN(aMaximumValue) ||
        (aMinimumValue <= aMaximumValue), Panic(KErrArgument));
        
    // In release, silently fix client's error?
    if ( aMinimumValue > aMaximumValue )
        {
        iMinimumValue = aMaximumValue;
        iMaximumValue = aMinimumValue;
        }
    else
        {
        iMinimumValue = aMinimumValue;
        iMaximumValue = aMaximumValue;
        }
    
    TBuf<KTextBufferSize> numDigits;
    numDigits.Num( Abs( aMinimumValue ) ); // implicit truncation to TInt
    iMaxNegativeIntegerDigits = numDigits.Length();
    numDigits.Num( Abs( aMaximumValue ) );
    iMaxPositiveIntegerDigits = numDigits.Length();
    
    return NormalizeValue();
    }


void CAknMfneFloat::GetLimits(
    TReal& aMinimumValue, 
    TReal& aMaximumValue) const
    {
    aMinimumValue = iMinimumValue;
    aMaximumValue = iMaximumValue;
    }


TBool CAknMfneFloat::SetValue( TReal aValue )
    {
    return SetTextFromValueAndNormalize( aValue );
    }


TReal CAknMfneFloat::Value() const
    {
    return ValueFromText( *iText );
    }


TBool CAknMfneFloat::NormalizeValue()
    {
    return SetTextFromValueAndNormalize( Value() );
    }
    

TInt CAknMfneFloat::MaximumWidthInPixels(
    const CFont& aFont, 
    TBool /*aShrinkToMinimumSize*/)
    {
    TLocale locale;
    TInt digitWidth = 
        TFindWidthOfWidestDigitType(locale.DigitType()).MaximumWidthInPixels(aFont);
        
    return MaxNumOfChars() * digitWidth;
    }


TCoeInputCapabilities CAknMfneFloat::InputCapabilities() const
    {
    return TCoeInputCapabilities(TCoeInputCapabilities::EWesternNumericReal);
    }


TBool CAknMfneFloat::IsEditable() const
    {
    return ETrue;
    }


CEikMfneField::THighlightType CAknMfneFloat::HighlightType() const
    {
    return iIsBeingEditedWithCursor ? ECursor : EInverseVideo;
    }


void CAknMfneFloat::HandleDeHighlight(
    const CFont& /*aFont*/, 
    CEikonEnv& /*aEikonEnv*/, 
    TBool& /*aDataAltered*/, 
    TBool& aError)
    {
    if ( NormalizeValue() )
        {
        CEikMfne::InvalidFieldAlert();
        aError = ETrue;
        }
    }


void CAknMfneFloat::HandleKey(
    const CFont& /*aFont*/, 
    const TKeyEvent& aKeyEvent, 
    TBool /*aInterpretLeftAndRightAsEarEvents*/, 
    TBool& aDataAltered, 
    TInt& aHighlightIncrement)
    {
    TChar ch( aKeyEvent.iCode );
    TChar decimalSeparator( DecimalSeparator() );
    
    switch ( ch )
        {
        case EKeyLeftArrow:
        case EKeyRightArrow:
            HandleLeftOrRightArrow( ch, aDataAltered, aHighlightIncrement );
            break;

        case EKeyBackspace:
            TryDelete( 1, aDataAltered );
            break;

        case KEventCodeStarSign:
        case KEventCodeMinusSign:
            TryAppend( iMinusSign, EMinusSign, aDataAltered );
            break;
            
        default:
            if ( IsAnyDigit( ch ) )
                {
                TryAppend( NormalizeDigit( ch ), EDigit, aDataAltered );
                }
            else if ( ch == KKeyToMatchPoint || ch == decimalSeparator )
                {
                TryAppend( decimalSeparator, EDecimalSeparator, aDataAltered );
                }
            break;
        }
        
    UpdateAllowedInput();
    
    if ( !iAllowedInputFlags )
        {
        aHighlightIncrement = 1;
        }
    }


const TDesC& CAknMfneFloat::Text() const
    {
    return *iText;
    }


TInt CAknMfneFloat::MaxNumOfChars() const
    {
    return Max( iMaxNegativeIntegerDigits, iMaxPositiveIntegerDigits )
        + iMaxFractionalDigits + KNumOtherSymbols;
    }


TReal CAknMfneFloat::ValueFromText( const TDesC& aText ) const
    {
    if ( aText.Length() == 0 )
        {
        return Nan();
        }
        
    // Sadly, TLex doesn't seem to handle arabic digits
    TReal real( 0 );
    
    HBufC* buf = HBufC::New( aText.Length() );
    
    if ( buf )
        {
        TPtr ptr( buf->Des() );
        ptr.Copy( aText );
        AknTextUtils::ConvertDigitsTo( ptr, EDigitTypeWestern );
        TLex lex( ptr );
        lex.Val( real );
        delete buf;
        }
        
    return real;
    }

        
void CAknMfneFloat::SetMaxFractionalDigits( TInt aMaxFractionalDigits )
    {
    iMaxFractionalDigits = aMaxFractionalDigits;
    
    NormalizeValue();
    
    iIsBeingEditedWithCursor = EFalse;
    }
    
    
TInt CAknMfneFloat::MaxFractionalDigits() const
    {
    return iMaxFractionalDigits;
    }
    
    
void CAknMfneFloat::RefreshDigitType()
    {
    SetDigitType( AknTextUtils::NumericEditorDigitType() );
    }


void CAknMfneFloat::SetDigitType( TDigitType aDigitType )
    {
    iDigitType = aDigitType;
    iZero      = iDigitType;
    iMinusSign = TChar( '-' );
    
    NormalizeValue();
    }


TDigitType CAknMfneFloat::DigitType() const
    {
    return iDigitType;
    }
    
        
void CAknMfneFloat::SetFlags( TUint aFlags )
    {
    iFlags = aFlags;
    NormalizeValue();
    }
    
TUint CAknMfneFloat::Flags() const
    {
    return iFlags;
    }
