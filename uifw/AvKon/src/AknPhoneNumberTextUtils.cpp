/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
*       This utility class allows the client to wrap phone numbers (previously 
*       number grouped) on to lines of display.  A facility to measure text from the 
*       end is provided for simple cases. 
* 
*
*/


// INCLUDE FILES

#include <e32std.h>

#include "AknPhoneNumberTextUtils.h"
#include "AknUtils.h"
#include "AknPanic.h"

// CONSTANTS

const TInt KLineArrayGranularity(2);

// ============================ MEMBER FUNCTIONS ===============================

void ReverseDescriptor( TDes& aPtr )
    {
    TInt count = aPtr.Length();
    TInt halfCount = count/2; // rounded down
    TInt target(count-1);
    for ( TInt index = 0; index < halfCount; index++, target-- )
        {
        TText temp = aPtr[target];
        aPtr[target] = aPtr[index];
        aPtr[index] = temp;
        }   
    }

EXPORT_C TBool AknPhoneNumberTextUtils::WrapPhoneNumberToArrayL( 
    const TDesC& aPhoneNumberToWrap,
    TInt aLineWidthInPixels,
    TInt aMaxLines,
    const CFont& aFont,
    CArrayFix<TPtrC>& aWrappedArray )
    {
    TBool retVal( EFalse ); // Not truncated
 
    HBufC* reversedText = aPhoneNumberToWrap.AllocLC();
    TPtr revPtr = reversedText->Des();

    ReverseDescriptor( revPtr );

    CArrayFix<TInt>* lineWidthArray = new (ELeave) CArrayFixFlat<TInt>(KLineArrayGranularity);
    CleanupStack::PushL( lineWidthArray );

    lineWidthArray->AppendL( aLineWidthInPixels, aMaxLines );

    // Perform the wrap on the reversed text
    AknTextUtils::WrapToArrayL( revPtr, *lineWidthArray, aFont, aWrappedArray );

    // Now rearrange the TPtrCs to point to the original array
    TInt totalLen = reversedText->Length();
    TInt count = aWrappedArray.Count();
    TInt usedLen = 0; // Accumulates the length actually used
    for ( TInt index = 0; index < count; index++)
        {
        TPtrC& currentPtr = aWrappedArray.At(index);
        // The TPtrCs have to be moved. The reversing is taken into effect, but not purely reversed
        // because their otherwise they would have negative lengths.  That is, {a,b} does not go to
        // { final - a, final - b }, but rather to {final - b, final - a}; they are flipped, to get
        // their start points before the end points
        //
        // Now, representing the start position by pos, and the end by pos+len-1 we have the TPtrC at
        // {pos, pos+len-1} inclusive, in reversed array. 
        // The TPtrC must be modified to point to {total_len-1 - (pos+len-1), total_len-1 - pos} 
        // in the unreversed array:
        TInt len = currentPtr.Length();
        usedLen += len;
        TInt pos = currentPtr.Ptr() - reversedText->Ptr(); // pointer arithmetic
        TInt newPos = totalLen - pos - len;
        // If the TPtr is zero length then it must get special treatment, as the normal
        // calculations give an end point before the start point! i.e. {pos, pos-1}
        // We handle this by NOT flipping in this case.
        // { pos, pos-1 } -> {totalLen-1-pos, totalLen-1 - (pos-1)}
        // Note that a zero length wrapped line is completely possible amoung a bunch of other 
        // lines with characters on them, as the line lengths may be of wildly different lengths.
        if ( len == 0 ) 
            newPos--;
        currentPtr.Set( aPhoneNumberToWrap.Mid(newPos, len) );
        }

    // If the accumulated length is less than that in the entire input descriptor, then text does not fit
    if ( usedLen < totalLen )
        retVal = ETrue;

    CleanupStack::PopAndDestroy(2); // lineWidthArray first, and then reversedText
    return retVal;
    }

EXPORT_C void AknPhoneNumberTextUtils::ClipLineOnLeft( 
    TPtrC& aLine, TDes& aOriginalBuffer, TInt aWidth, const CFont& aFont )
    {
    // Main work of this routine is to make a TPtr of the input TPtrC, then we can clip using existing
    // utils.
 
    // But first check if the line points to the provided modifiable buffer
    TText* linePtr = (TText*)aLine.Ptr();
    TInt lineLen = aLine.Length();
    TText* pastEndOfLine = linePtr + lineLen; // pointer arithmetic

    TText* modBufPtr = (TText*)aOriginalBuffer.Ptr();
    TInt len = aOriginalBuffer.Length(); // length actually with text in it (not maxlength)
    TText* pastEndOfModBufPtr = modBufPtr + len; // pointer arithmetic

    // This Panics if the input aLine is not encompassed within the modifiable buffer ->Programmer error
    __ASSERT_ALWAYS( (modBufPtr <= linePtr && pastEndOfLine <= pastEndOfModBufPtr ), Panic( EAknPanicInconsistentDescriptors ) );

    // Set the TPtr now to extend from the start of the original buffer to the end of the input aLine
    TInt enlargedLength = (pastEndOfLine - modBufPtr);//  Pointer arithmetic; 
    TPtr ptr( modBufPtr, enlargedLength, enlargedLength );

    // Should have a safe modifiable buffer now.
    AknTextUtils::ClipToFit( ptr, aFont, aWidth, AknTextUtils::EClipFromBeginning );
    aLine.Set( ptr );
    }

EXPORT_C TInt AknPhoneNumberTextUtils::CharsThatFitOnRight(
    const TDesC& aText, 
    TInt aLineWidth, 
    const CFont& aFont )
    {
    // Current candidate text for fitting text
    TPtrC currentText(aText); 

    // These two variables are converged by this algorithm until they differ by one
    // Set max chars to be total length + 1, for the sake of the algorithm
    TInt minCharsFromRightThatDoNotFit( aText.Length() + 1 );
    TInt maxCharsFromRightThatFit(0); // must start at 0

    // some incidentally used lengths 
    TInt currentLength(0);      // arbitrary init value
    TInt charsThatFitOnLeft(0); // arbitrary init value
    TInt newLength(0);          // arbitrary init value

    while ( (minCharsFromRightThatDoNotFit - maxCharsFromRightThatFit) != 1 )
        {
        // At the top of the loop, all state is held by currentText itself, and the two 
        // maxCharsXXX variables.
        currentLength = currentText.Length();
        charsThatFitOnLeft = aFont.TextCount( currentText, aLineWidth);  

        if ( charsThatFitOnLeft == currentLength ) // Does this text fit ?
            {
            maxCharsFromRightThatFit = Max( maxCharsFromRightThatFit, charsThatFitOnLeft );

            // If this text cannot be made any bigger, and still fit, then bail out
            if ( (maxCharsFromRightThatFit + 1) >= minCharsFromRightThatDoNotFit )
                {
                // We can exit the loop now. Just fall out and the while test will handle it.
                break;
                }
            else // if this string did fit, and it might have been too small, try making it bigger
                {
                // we know this is still be < minCharsFromRightThatDoNotFit
                newLength = maxCharsFromRightThatFit + 1; 
                }
            }
        else // currentText does not fit. Repeat loop 
            {
            // we know that this many characters did not fit on the line
            minCharsFromRightThatDoNotFit = Min( minCharsFromRightThatDoNotFit, currentLength );

            // Try using the number that fit on the left as the number we will fit on the right.
            newLength = charsThatFitOnLeft;
            }

        currentText.Set(aText.Right(newLength)); 
        }

    return maxCharsFromRightThatFit;
    }

// End of File  
