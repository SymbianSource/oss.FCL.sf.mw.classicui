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
* Description:  Avkon text wrapper implementation
*                This class is used by AknTextUtils and AknBidiTextUtils.
*
*/



// INCLUDE FILES
#include "AknTextWrapper.h"
#include "aknenv.h"
#include "AknBidiTextUtils.h"
#include <gdi.h>
#include <uikon.hrh>
#include <bidi.h>
#include <bidivisual.h>

// CONSTANTS

// line feed, carriage return, line separator, paragraph separator
_LIT( KSeparators, "\x000a\x000d\x2028\x2029" );

const TText KLineFeed               = 0x000A;
const TText KCarriageReturn         = 0x000D;
const TText KLineSeparator          = 0x2028;
const TText KParagraphSeparator     = 0x2029;
const TText KZeroWidthSpace         = 0x200B;
const TText KFirstThaiCharacter     = 0x0E01;
const TText KLastThaiCharacter      = 0x0E5B;

enum
    {
    EWrapToArray = 0,
    EChopToArrayAndClip = 1
    };

const TText KAknLocVariantSeparator = 0x0001;

// Helper classes for User::QuickSort.

NONSHARABLE_CLASS(TMyKey) : public TKey
    {
    // From TKey
    private:
        TInt Compare( TInt aLeft, TInt aRight ) const;
        TAny* At( TInt aIndex ) const;
    };

TInt TMyKey::Compare( TInt aLeft, TInt aRight ) const
    {
    const TAknLocVariant* ptr = static_cast<const TAknLocVariant*>( iPtr );
    TInt leftLength = ptr[aLeft].iEnd - ptr[aLeft].iStart;
    TInt rightLength = ptr[aRight].iEnd - ptr[aRight].iStart;

    return rightLength - leftLength;
    }

TAny* TMyKey::At( TInt aIndex ) const
    {
    const TAknLocVariant* ptr = static_cast<const TAknLocVariant*>( iPtr );
    return (TAny*)( &ptr[aIndex] );
    }

NONSHARABLE_CLASS(TMySwap) : public TSwap
    {
    // Constructor
    public:
        inline TMySwap( TAknLocVariant* aVariants ) : iVariants( aVariants ) {}
    // From TSwap
    private:
        void Swap( TInt aLeft, TInt aRight ) const;
    // Data
    private: 
        TAknLocVariant* iVariants;
    };

void TMySwap::Swap( TInt aLeft, TInt aRight ) const
    {
    TAknLocVariant temp = iVariants[aLeft];
    iVariants[aLeft] = iVariants[aRight];
    iVariants[aRight] = temp;
    }

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// TAknTextWrapper::TAknTextWrapper
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
TAknTextWrapper::TAknTextWrapper( 
    TDes& aStringToWrap,
    const CArrayFix<TInt>* aLineWidthArray, 
    const CFont& aFont,
    CArrayFix<TPtrC>& aWrappedArray,
    TInt aLineWidth,
    TInt aFlags,
    AknBidiTextUtils::TParagraphDirectionality aDirectionality ) :
        iSourceString( aStringToWrap ),
        iLineWidthArray( aLineWidthArray ),
        iFont( aFont ),
        iResultArray( aWrappedArray ),
        iLineWidth( aLineWidth ),
        iFlags( aFlags ),
        iDirectionality( aDirectionality ),
        iSeparators( KSeparators() ),
        iText( NULL, 0 )
    {
    }

// Destructor
TAknTextWrapper::~TAknTextWrapper()
    {
    }

// -----------------------------------------------------------------------------
// TAknTextWrapper::WrapToArrayL
// -----------------------------------------------------------------------------
//
HBufC* TAknTextWrapper::WrapToArrayL()
    {
    return DoOperationL( EWrapToArray );
    }

// -----------------------------------------------------------------------------
// TAknTextWrapper::ChopToArrayAndClipL
// -----------------------------------------------------------------------------
//
HBufC* TAknTextWrapper::ChopToArrayAndClipL()
    {
    return DoOperationL( EChopToArrayAndClip );
    }

// -----------------------------------------------------------------------------
// TAknTextWrapper::DoOperationL
// -----------------------------------------------------------------------------
//
HBufC* TAknTextWrapper::DoOperationL( TInt aOp )
    {
    iResultArray.Reset();

    if ( !iSourceString.Length() )
        {
        if ( iFlags & EReserveVisualBuffer )
            {
            return HBufC::NewL( 0 );
            }
        else
            {
            return NULL;
            }
        }

    HBufC* ret = NULL;

    TAknLocVariant variants[KAknMaxLocVariants];
    TInt numVariants = GetLocVariants( iSourceString, variants );

    iFlags &= ~EFits;
    TInt i = 0;

    HBufC* backupBuf = iSourceString.AllocLC();

    for ( ; i < numVariants && !(iFlags & EFits); i++ )
        {
        delete ret;
        ret = NULL;

        TInt start = variants[i].iStart;

        iSourceString.Copy( 
            backupBuf->Mid( start, variants[i].iEnd - start ) );

        iFlags |= EFits;
        // Clears EFits if truncated.
        if ( aOp == EWrapToArray )
            {
            ret = DoWrapToArrayL();
            }
        else
            {
            ret = DoChopToArrayAndClipL();
            }
        }

    CleanupStack::PopAndDestroy(); // backupBuf
    return ret;
    }

// -----------------------------------------------------------------------------
// TAknTextWrapper::DoWrapToArrayL
// -----------------------------------------------------------------------------
//
HBufC* TAknTextWrapper::DoWrapToArrayL()
    {
    iResultArray.Reset();

    // TBidiLogicalToVisual crashes with length 0 text so we check that case here
    if ( !iSourceString.Length() )
        {
        if ( iFlags & EReserveVisualBuffer )
            {
            return HBufC::NewL( 0 );
            }
        else
            {
            return NULL;
            }
        }

    TInt index( 0 );
    TInt lineIndex( 0 );

    TInt maxLines( KMaxTInt );
    
    if ( iLineWidthArray && !( iFlags & EWrapAllText ) )
        {
        maxLines = iLineWidthArray->Count();
        }
        
    while ( index < iSourceString.Length() && iResultArray.Count() < maxLines )
        {
        TInt lineWidth = iLineWidth;
        
        if ( iLineWidthArray )
            {
            TInt givenWidths = iLineWidthArray->Count();
            TInt usedLineWidthIndex = lineIndex;
            if ( lineIndex >= givenWidths )
                {
                usedLineWidthIndex = givenWidths - 1;
                }

            lineWidth = (*iLineWidthArray)[usedLineWidthIndex];
            }

        iText.Set( iSourceString.Right( iSourceString.Length() - index ) );

        TInt fitsInLine = iFont.TextCount( iText, lineWidth );
        // If the line width is constant and no characters fit in it, stop.
        if ( !fitsInLine && 
           (!iLineWidthArray || lineIndex >= iLineWidthArray->Count()) )
            {
            break;
            }

        // Is there an explicit line break in the part that fits in line
        TInt newLine = FindLineBreak( iText.Left( fitsInLine ) );

        if ( newLine != KErrNotFound )
            {
            iNextLineStart = newLine;
            PassLineBreak(); // updates iNextLineStart

            if ( iNextLineStart == iText.Length() )
                {
                AppendToArrayL( iText.Left( newLine ) );
                break;
                }
            }

        // All remaining text fits in line?
        else if ( iText.Length() == fitsInLine )
            {
            AppendToArrayL( iText );
            break;
            }

        TInt wrapIndex( 0 );

        // Last line? If so, clip it if required...

        if ( iFlags & EClip && lineIndex == maxLines - 1 )
            {
            if ( newLine != KErrNotFound )
                {
                iText.Set( iText.Left( newLine ) );
                }

            // This actually inserts ellipsis in text only if logical to
            // visual conversion is not used.
            wrapIndex = InsertEllipsis( iText, lineWidth );
            // This flag informs logical to visual conversion to insert
            // truncation character
            iFlags |= EClipRequired;
            iFlags &= ~EFits;
            AppendToArrayL( iText.Left( wrapIndex ) );
            break;
            }

        // Not last line, so no clipping required yet
        if ( newLine != KErrNotFound )
            {
            wrapIndex = newLine;
            }
        // No explicit line break in the part that fits in line,
        // find wrapping potision
        else
            {
            if ( GetWrappingPosition( iText, fitsInLine, lineWidth, ETrue ) )
                {
                wrapIndex = iBreakPos;
                }

            else
                {
                // No legal wrapping position found => illegal line breaking.
                // Put all that fits in line.
                wrapIndex = fitsInLine;
                iNextLineStart = fitsInLine;
                }

            PassLineBreak(); // updates iNextLineStart
            }

        AppendToArrayL( iText.Left( wrapIndex ) );
        index += iNextLineStart;

        // next line to be wrapped
        lineIndex++;
        }

    return ConvertToVisualIfRequiredL();
    }

// -----------------------------------------------------------------------------
// TAknTextWrapper::DoChopToArrayAndClipL
// -----------------------------------------------------------------------------
//
HBufC* TAknTextWrapper::DoChopToArrayAndClipL()
    {
    iResultArray.Reset();

    // First determine succifient amount of text lines for visual buffer.

    TInt maxLines = 0;

    if ( iLineWidthArray )
        {
        maxLines = iLineWidthArray->Count();
        }

    else
        {
        TInt length = iSourceString.Length();
        const TText* text = iSourceString.Ptr();

        // This counts 2 lines for lines ending to CR+LF but it does not
        // really matter as we are determining a succifient number of lines.
        for ( TInt i = 0 ; i < length ; i++ )
            {
            if ( iSeparators.Locate( text[i] ) != KErrNotFound )
                {
                maxLines++;
                }
            }

        maxLines++; // add one extra for the line after the last line break.
        }

    // Allocate visual buffer.
    HBufC* visualBuffer = HBufC::NewLC( 
        iSourceString.Length() + maxLines * KAknBidiExtraSpacePerLine );

    TInt index( 0 );        // index in iSourceString
    TInt lineIndex( 0 );    // line number
    TInt visualIndex( 0 );  // index in visualBuffer

    // We utilize wrapping functionality for each line to be chopped.
    // These temp arrays are for that purpose.
    CArrayFix<TInt>* tempLineWidthArray =
        new( ELeave ) CArrayFixFlat<TInt>( 1 );
    CleanupStack::PushL( tempLineWidthArray );
    tempLineWidthArray->AppendL( 0 );

    CArrayFix<TPtrC>* tempResultArray =
        new( ELeave ) CArrayFixFlat<TPtrC>( 1 );
    CleanupStack::PushL( tempResultArray );

    while ( index < iSourceString.Length() && iResultArray.Count() < maxLines )
        {
        iText.Set( iSourceString.Right( iSourceString.Length() - index ) );

        // Locate line break
        iNextLineStart = FindLineBreak( iText );

        if ( iNextLineStart == KErrNotFound )
            {
            iNextLineStart = iText.Length();
            }

        TInt flags( TAknTextWrapper::EClip );
        
        if ( iFlags & EConvertToVisual )
            {
            flags |= EConvertToVisual;
            }

        // chop the line in visual buffer

        TInt visualRemainingSpace = 
            visualBuffer->Des().MaxLength() - visualIndex;

        const TText* nextLine = visualBuffer->Ptr();
        nextLine += visualIndex;

        TPtr ptr( 
            const_cast<TText*>( nextLine ),
            visualRemainingSpace,
            visualRemainingSpace );

        ptr.Copy( iText.Left( iNextLineStart ) );

        // we only wrap 1 line
        (*tempLineWidthArray)[0] =
            iLineWidthArray ? (*iLineWidthArray)[lineIndex] : iLineWidth;

        TAknTextWrapper wrapper(
            ptr,
            tempLineWidthArray,
            iFont,
            *tempResultArray,
            0,
            flags,
            iDirectionality );

        wrapper.WrapToArrayL();

        if ( !wrapper.ResultFits() )
            {
            iFlags &= ~EFits;
            }

        TInt lineLength = 0;
        if ( tempResultArray->Count() )
            {
            lineLength = (*tempResultArray)[0].Length();
            }

        visualBuffer->Des().SetLength( visualIndex + lineLength );

        if ( iFlags & EReserveVisualBuffer )
            {
            AppendToArrayL( visualBuffer->Right( lineLength ) );
            }
        else
            {
            // Cannot use AppendToArrayL here, because iResultArray is set to point to iSourceString,
            // which does not contain the final visual text yet. This would screw up removing trailing spaces.
            // It is copied there in the end of this method.

            TPtrC currentLine = visualBuffer->Right( lineLength );

            TInt trailingSpaces = 0;
            TInt trailingIndex = currentLine.Length() - 1;

            // Count how many spaces there are in the end of the line.
            // Without removing them, text that is aligned to the end of line looks bad.
            while ( trailingIndex >= 0 && currentLine[trailingIndex] == ' ' )
                {
                trailingIndex--;
                trailingSpaces++;
                }

            iResultArray.AppendL( iSourceString.Mid( visualIndex, lineLength - trailingSpaces ) );
            }

        visualIndex += lineLength;

        PassLineBreak();
        index += iNextLineStart;

        // next line to be wrapped
        lineIndex++;
        }

    CleanupStack::PopAndDestroy( 2 ); // tempLineWidthArray, tempResultArray

    if ( iFlags & EReserveVisualBuffer )
        {
        CleanupStack::Pop();
        return visualBuffer;
        }

    else
        {
        iSourceString = *visualBuffer;
        CleanupStack::PopAndDestroy(); // visualBuffer;
        return NULL;
        }
    }

// -----------------------------------------------------------------------------
// TAknTextWrapper::InsertEllipsis
// -----------------------------------------------------------------------------
//
TInt TAknTextWrapper::InsertEllipsis( const TDesC& aText, TInt aLineWidth )
    {
    // place ellipsis in the last possible place so that
    // the line still fits

    TInt count = iFont.TextCount( aText,
        aLineWidth - iFont.CharWidthInPixels( KEllipsis ) );

    if ( !(iFlags & EConvertToVisual) )
        {
        TText* text = (TText*)( aText.Ptr() );
        text[ count ] = KEllipsis;
        return count + 1;
        }
    else
        {
        // ellipsis will be added in logical to visual conversion
        return count;
        }
    }

// -----------------------------------------------------------------------------
// TAknTextWrapper::AppendToArrayL
// -----------------------------------------------------------------------------
//
void TAknTextWrapper::AppendToArrayL( const TDesC& aLine )
    {
    const TText* line = aLine.Ptr();
    TInt index = aLine.Length() - 1;

    // Remove spaces from the end of the line.
    // Otherwise, text that is aligned to the end of line looks bad.

    while ( index >= 0 && line[index] == ' ' )
        {
        index--;
        }

    iResultArray.AppendL( aLine.Left( index + 1 ) );
    }

// -----------------------------------------------------------------------------
// TAknTextWrapper::FindLineBreak
// -----------------------------------------------------------------------------
//
TInt TAknTextWrapper::FindLineBreak( const TDesC& aText )
    {
    const TText* text = aText.Ptr();
    TInt length( aText.Length() );

    for ( TInt i = 0 ; i < length ; i++ )
        {
        if ( iSeparators.Locate( text[i] ) != KErrNotFound )
            {
            return i;
            }
        }

    return KErrNotFound;
    }

// -----------------------------------------------------------------------------
// TAknTextWrapper::GetWrappingPosition
// -----------------------------------------------------------------------------
//
TBool TAknTextWrapper::GetWrappingPosition( 
    const TDesC& aText,
    TInt aFitsInLine,
    TInt aLineWidth,
    TBool aReplaceSoftHyphen )
    {
    // If there is an explicit line break character right after the fitting
    // characters, then wrap there.

    if ( aText.Length() > aFitsInLine &&
         iSeparators.Locate( aText[aFitsInLine] ) != KErrNotFound )
        {
        iBreakPos = aFitsInLine;
        iNextLineStart = aFitsInLine;
        return ETrue;
        }

    TBool foundLineBreak( EFalse );
    TText* text = const_cast<TText*>( iText.Ptr() );

    while ( aFitsInLine > 0 )
        {
        // use linebreak routine to find the last possible line break

        if ( !iBreaker.GetLineBreak(
                aText,
                1,
                aFitsInLine,
                EFalse,
                NULL,
                iBreakPos,
                iNextLineStart ) )
            {
            // no legal wrapping positions found at all
            break;
            }

        /////////////////////////////////////////////////////////////
        // Special rule for Thai wrapping:
        // Wrapping between two Thai characters is not done if the line 
        // contains at least one zero-width-space or usual space. In this   
        // situation the line is wrapped from the latest zero width space
        // or space.
        TInt newWrapPosition = -1;        
        TInt charactersToCheck = iBreakPos - 1;
        TChar breakChar1 = text[charactersToCheck];
        TChar breakChar2 = ' ';

        if (aText.Length() > aFitsInLine)
            {
            // The character after the usual line break needs to be Thai character as well.
            charactersToCheck += 1;
            breakChar2 = text[charactersToCheck];
            }

        // Did the line break were made between two Thai characters.
        if ( ( breakChar1 >= KFirstThaiCharacter && breakChar1 <= KLastThaiCharacter ) &&
             ( breakChar2 >= KFirstThaiCharacter && breakChar2 <= KLastThaiCharacter ) )
            {
            for (TInt ii = charactersToCheck; ii >= 0; ii--)
                {
                const TChar charTemp = text[ii];
                if ( (charTemp == ' ' || charTemp == KZeroWidthSpace) )
                    {
                    // Space or zero-width-space found. We use it for wrapping.
                    newWrapPosition = ii;
                    break;
                    }
                }
            }
            
        if ( newWrapPosition >= 0 )
            {
            // The special wrapping rule is used.
            iBreakPos = newWrapPosition;
            iNextLineStart = iBreakPos + 1;
            foundLineBreak = ETrue;
            }
        /////////////////////////////////////////////////////////////

            
        // Wrapping after hyphen (or soft hyphen) is allowed only
        // if there is no space right before the hyphen.
        TInt lastCharIndex( iBreakPos - 1 );
        const TText lastChar = text[lastCharIndex];

        if ( lastChar == '-' ||
             lastChar == KHyphen ||
             lastChar == KSoftHyphen )
            {
            if ( lastCharIndex > 0 && text[lastCharIndex - 1] == ' ' )
                {
                aFitsInLine = lastCharIndex;
                continue;
                }
            }

        if ( lastChar != KSoftHyphen )
            {
            foundLineBreak = ETrue;
            break;
            }

        // If the chosen wrapping char was soft hyphen,
        // try replace it with real hyphen.

        text[lastCharIndex] = KHyphen;

        // still fits in line?
        if ( iFont.TextWidthInPixels( 
             iText.Left( lastCharIndex + 1 ) ) <= aLineWidth )
            {
            foundLineBreak = ETrue;

            if ( !aReplaceSoftHyphen )
                {
                text[lastCharIndex] = KSoftHyphen;
                }

            break;
            }

        else
            {
            // This soft hyphen could not be used, because
            // expanding it to real hyphen would have made
            // the line too long to fit.

            text[lastCharIndex] = KSoftHyphen;
            aFitsInLine = lastCharIndex;
            }
        }

    return foundLineBreak;
    }

// -----------------------------------------------------------------------------
// TAknTextWrapper::ConvertToVisualIfRequiredL
// -----------------------------------------------------------------------------
//
HBufC* TAknTextWrapper::ConvertToVisualIfRequiredL()
    {
    if ( !(iFlags & EConvertToVisual) )
        {
        return NULL;
        }

    TInt lines = iResultArray.Count();

    HBufC* visualBuffer = HBufC::NewLC( 
        iSourceString.Length() + lines * KAknBidiExtraSpacePerLine );

    CAknEnv& env = *CAknEnv::Static();
    TChar truncationChar = 0xffff;

    TInt sourceStringLength = iSourceString.Length();

    // initialize run info array
    User::LeaveIfError( env.PrepareRunInfoArray( iSourceString ) );

    // get run info array
    TInt count;
    TBidirectionalState::TRunInfo* array = env.RunInfoArray( count );

    // convert from logical to visual
    TBidiLogicalToVisual converter( 
        iDirectionality == AknBidiTextUtils::EImplicit ? 
            TBidiLogicalToVisual( 
                iSourceString,
                array,
                count ) :
            TBidiLogicalToVisual( 
                iSourceString,
                iDirectionality == AknBidiTextUtils::ERightToLeft,
                array,
                count ) );

    converter.Reorder();

    // Convert each line from logical to visual form,
    // and update array of wrapped lines accordingly.

    for ( TInt i = 0 ; i < lines ; i++ )
        {
        TPtrC logicalLine = iResultArray[i];

        TInt start = (TText*)logicalLine.Ptr() - (TText*)iSourceString.Ptr();
        TInt length = logicalLine.Length();

        TInt currentLength = visualBuffer->Length();
        TInt visualLineLength = visualBuffer->Des().MaxLength() - currentLength; 

        TPtr visualLine(
            ((TText*)visualBuffer->Ptr()) + currentLength,
            0,
            visualLineLength );

        // if last line, set clip char if required
        if ( i == lines - 1 && iFlags & EClipRequired )
            {
            truncationChar = KEllipsis;
            }

        converter.GetVisualLine(
            visualLine,
            start,
            start + length,
            truncationChar );

        visualBuffer->Des().SetLength( 
            visualBuffer->Length() + visualLine.Length() );

        // update array of wrapped lines accordingly.

        iResultArray.Delete( i );

        if ( iFlags & EReserveVisualBuffer )
            {
            iResultArray.InsertL( 
                i, visualBuffer->Right( visualLine.Length() ) );
            }
        else
            {
            iSourceString.SetMax();
            iResultArray.InsertL( 
                i, iSourceString.Mid( currentLength, visualLine.Length() ) );
            iSourceString.SetLength( sourceStringLength );
            }
        }

    if ( iFlags & EReserveVisualBuffer )
        {
        CleanupStack::Pop();
        return visualBuffer;
        }

    else
        {
        iSourceString = *visualBuffer;
        CleanupStack::PopAndDestroy(); // iVisualBuffer;
        return NULL;
        }
    }

// -----------------------------------------------------------------------------
// TAknTextWrapper::PassLineBreak
// -----------------------------------------------------------------------------
//
void TAknTextWrapper::PassLineBreak()
    {
    TText* text = const_cast<TText*>( iText.Ptr() );
    TInt length = iText.Length();

    if ( iNextLineStart < length )
        {
        const TText c = text[iNextLineStart]; 

        if ( c == KLineFeed ||
             c == KLineSeparator ||
             c == KParagraphSeparator )
            {
            iNextLineStart++;
            }
        else if ( c == KCarriageReturn )
            {
            iNextLineStart++;
            // after CR, also skip possible matching LF
            if ( iNextLineStart < length && text[iNextLineStart] == KLineFeed )
                {
                iNextLineStart++;
                }
            }
        }
    }

// -----------------------------------------------------------------------------
// TAknTextWrapper::ResultFits
// -----------------------------------------------------------------------------
//
TBool TAknTextWrapper::ResultFits()
    {
    return iFlags & EFits;
    }

// -----------------------------------------------------------------------------
// TAknTextWrapper::GetLocVariants
// -----------------------------------------------------------------------------
//
TInt TAknTextWrapper::GetLocVariants(
    const TDesC& aText, TAknLocVariant* aVariants )
    {
    TPtrC remaining( aText );

    TInt start = 0;
    TInt end = remaining.Locate( KAknLocVariantSeparator );

    TInt i = 0;

    while ( end >= 0 && i < KAknMaxLocVariants )
        {
        end += start;
        aVariants[i].iStart = start;
        aVariants[i].iEnd = end;
        
        start = end + 1;
        remaining.Set( aText.Mid( start ) );
        end = remaining.Locate( KAknLocVariantSeparator );

        i++;
        }

    if ( i < KAknMaxLocVariants )
        {
        // Handle the last variant.
        aVariants[i].iStart = start;
        aVariants[i].iEnd = aText.Length();
        i++;
        }

    // Put the variants in descending character count order.
    if ( i > 1 )
        {
        TMyKey key;
        key.SetPtr( aVariants );

        TMySwap swap( aVariants );

        // Return value ignored.
        User::QuickSort( i, key, swap );
        }

    return i;
    }

//  End of File  
