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
* Description:  Text utilities e.g. truncating and wrapping to be used with
*                text that requires conversion from logical to visual form.
*                E.g. Arabic/Hebrew, Thai, Hindi. Logical text is given as input
*                to all methods. Output text is in visual form.
*
*/


// INCLUDE FILES
#include "AknBidiTextUtils.h"
#include "aknenv.h"
#include "AknUtils.h"
#include "AknPanic.h"
#include "AknTextWrapper.h"
#include <e32std.h>
#include <bidivisual.h>

// CONSTANTS

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// AknBidiTextUtils::ConvertToVisualAndClipL
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknBidiTextUtils::ConvertToVisualAndClipL(
    TDes& aLogicalText,
    const CFont& aFont,
    TInt aMaxWidthInPixels,
    TInt aMaxClippedWidthInPixels,
    AknBidiTextUtils::TParagraphDirectionality aDirectionality,
    TChar aClipChar )
    {
    HBufC* visualBuffer = HBufC::NewL(
        aLogicalText.Length() + KAknBidiExtraSpacePerLine );
    TPtr ptr = visualBuffer->Des();

    TBool clipped = ConvertToVisualAndClip(
        aLogicalText,
        ptr,
        aFont,
        aMaxWidthInPixels,
        aMaxClippedWidthInPixels,
        aDirectionality,
        aClipChar );

    aLogicalText = *visualBuffer;
    delete visualBuffer;
    return clipped;
    }


// -----------------------------------------------------------------------------
// AknBidiTextUtils::ConvertToVisualAndClip
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknBidiTextUtils::ConvertToVisualAndClip(
    const TDesC& aLogicalText,
    TDes& aVisualText,
    const CFont& aFont,
    TInt aMaxWidthInPixels,
    TInt aMaxClippedWidthInPixels,
    AknBidiTextUtils::TParagraphDirectionality aDirectionality,
    TChar aClipChar )
    {
    TAknLocVariant variants[KAknMaxLocVariants];
    TInt numVariants = TAknTextWrapper::GetLocVariants( aLogicalText, variants );

    TBool clipped = ETrue;
    TInt i = 0;

    while ( i < numVariants && clipped )
        {
        TInt start = variants[i].iStart;
        TInt length = variants[i].iEnd - start;
        
        clipped = DoConvertToVisualAndClip(
            aLogicalText.Mid( start, length ),
            aVisualText,
            aFont,
            aMaxWidthInPixels,
            aMaxClippedWidthInPixels,
            aDirectionality,
            aClipChar );

        i++;
        }

    return clipped;
    }

// -----------------------------------------------------------------------------
// AknBidiTextUtils::DoConvertToVisualAndClip
// -----------------------------------------------------------------------------
//
TBool AknBidiTextUtils::DoConvertToVisualAndClip(
    const TDesC& aLogicalText,
    TDes& aVisualText,
    const CFont& aFont,
    TInt aMaxWidthInPixels,
    TInt aMaxClippedWidthInPixels,
    AknBidiTextUtils::TParagraphDirectionality aDirectionality,
    TChar aClipChar )
    {
    /* TODO: Commented out temporarily.
    __ASSERT_DEBUG( aVisualText.MaxLength() >= 
        aLogicalText.Length() + KAknBidiExtraSpacePerLine,
        Panic( EAknPanicInvalidValue ) );
    __ASSERT_DEBUG( aMaxWidthInPixels >= 0, 
        Panic( EAknPanicInvalidValue ) );
    __ASSERT_DEBUG( aMaxClippedWidthInPixels >= 0,
        Panic( EAknPanicInvalidValue ) );
    */
    TInt chars = aLogicalText.Length();

    // TBidiLogicalToVisual crashes with length 0 text so we check that case here
    if ( !chars )
        {
        aVisualText = KNullDesC; // null text 
        return EFalse;
        }

    TBool clipped = EFalse;
    // Give 0xffff as parameter to TBidiLogicalToVisual if no clipping required.
    TChar clipChar = 0xffff;

    // TextCount() converts text to visual form and then checks it
    if ( aFont.TextCount( aLogicalText, aMaxWidthInPixels ) < chars )
        {
        clipped = ETrue;

        TInt clipCharWidth = 
            aClipChar == 0xffff ? 0 : aFont.CharWidthInPixels( aClipChar );

        // Not enough space even for clip char alone - return empty descriptor.
        if ( aMaxClippedWidthInPixels < clipCharWidth )
            {
            aVisualText.Zero();
            return ETrue;
            }

        // Check how many characters fit in given space with truncation char.
        // We need to give this information to TBidiLogicalToVisual.
        chars = aFont.TextCount( 
            aLogicalText, aMaxClippedWidthInPixels - clipCharWidth );

        // This is "avkon rule": should not insert ellipsis right after a space.
        if ( chars > 1 && 
             aLogicalText[chars - 1] == ' ' &&
             aLogicalText[chars - 2] != ' ' )
            {
            chars--;
            }

        clipChar = aClipChar;
        }
        
    CAknEnv& env = *CAknEnv::Static();

    // Ignore error - nothing we can do. If we are out of memory,
    // this might cause incorrect text rendering in such lines,
    // which require large run info array.
    env.PrepareRunInfoArray( aLogicalText );

    TInt count;
    TBidirectionalState::TRunInfo* array = env.RunInfoArray( count );

    TBidiLogicalToVisual converter =
        aDirectionality == EImplicit ? 
        TBidiLogicalToVisual( aLogicalText, array, count ) :
        TBidiLogicalToVisual( aLogicalText, aDirectionality == ERightToLeft, array, count );

    converter.Reorder();
    converter.GetVisualLine( aVisualText, 0, chars, clipChar );

    return clipped;
    }

// -----------------------------------------------------------------------------
// AknBidiTextUtils::PrepareRunInfoArray
// -----------------------------------------------------------------------------
//
EXPORT_C TInt AknBidiTextUtils::PrepareRunInfoArray( const TDesC& aLogicalText )
    {
    return CAknEnv::Static()->PrepareRunInfoArray( aLogicalText );
    }

// -----------------------------------------------------------------------------
// AknBidiTextUtils::ConvertToVisualAndWrapToArrayL
// -----------------------------------------------------------------------------
//
EXPORT_C void AknBidiTextUtils::ConvertToVisualAndWrapToArrayL(
    TDes& aStringToWrap,
    const CArrayFix<TInt>& aLineWidthArray,
    const CFont& aFont,
    CArrayFix<TPtrC>& aWrappedArray,
    TBool aInsertTruncationChar,
    AknBidiTextUtils::TParagraphDirectionality aDirectionality )
    {
    // Ensure that there is the required free space in descriptor

    __ASSERT_ALWAYS( 
        aStringToWrap.MaxLength() - aStringToWrap.Length() >=
        aLineWidthArray.Count() * KAknBidiExtraSpacePerLine,
        Panic( EAknPanicInvalidValue ) );

    // Perform wrapping

    TInt flags( TAknTextWrapper::EConvertToVisual );

    if ( aInsertTruncationChar )
        {
        flags |= TAknTextWrapper::EClip;
        }

    TAknTextWrapper wrapper(
        aStringToWrap,
        &aLineWidthArray,
        aFont,
        aWrappedArray,
        0,
        flags,
        aDirectionality );

    wrapper.WrapToArrayL();
    }

// -----------------------------------------------------------------------------
// AknBidiTextUtils::ConvertToVisualAndWrapToArrayL
// -----------------------------------------------------------------------------
//
EXPORT_C HBufC* AknBidiTextUtils::ConvertToVisualAndWrapToArrayL(
    const TDesC& aStringToWrap,
    TInt aLineWidth,
    const CFont& aFont,
    CArrayFix<TPtrC>& aWrappedArray,
    AknBidiTextUtils::TParagraphDirectionality aDirectionality )
    {
    TInt length = aStringToWrap.Length();
    TPtr ptr( const_cast<TText*>( aStringToWrap.Ptr() ), length, length );

    TAknTextWrapper wrapper(
        ptr,
        NULL,
        aFont,
        aWrappedArray,
        aLineWidth,
        TAknTextWrapper::EReserveVisualBuffer |
        TAknTextWrapper::EConvertToVisual,
        aDirectionality );

    return wrapper.WrapToArrayL();
    }

// -----------------------------------------------------------------------------
// AknBidiTextUtils::ConvertToVisualAndChopToArrayL
// -----------------------------------------------------------------------------
//
EXPORT_C void AknBidiTextUtils::ConvertToVisualAndChopToArrayL(
    TDes& aStringToChop,             
    const CArrayFix<TInt>& aLineWidthArray, 
    const CFont& aFont,                    
    CArrayFix<TPtrC>& aChoppedArray,
    AknBidiTextUtils::TParagraphDirectionality aDirectionality )
    {
    // Ensure that there is the required free space in descriptor

    __ASSERT_ALWAYS( 
        aStringToChop.MaxLength() - aStringToChop.Length() >=
        aLineWidthArray.Count() * KAknBidiExtraSpacePerLine,
        Panic( EAknPanicInvalidValue ) );

    // Perform chopping

    TAknTextWrapper wrapper(
        aStringToChop,
        &aLineWidthArray,
        aFont,
        aChoppedArray,
        0,
        TAknTextWrapper::EClip | TAknTextWrapper::EConvertToVisual,
        aDirectionality );

    wrapper.ChopToArrayAndClipL();
    }

// -----------------------------------------------------------------------------
// AknBidiTextUtils::ConvertToVisualAndChopToArrayL
// -----------------------------------------------------------------------------
//
EXPORT_C HBufC* AknBidiTextUtils::ConvertToVisualAndChopToArrayL(
    const TDesC& aStringToChop,
    TInt aLineWidth,
    const CFont& aFont,
    CArrayFix<TPtrC>& aChoppedArray,
    AknBidiTextUtils::TParagraphDirectionality aDirectionality )
    {
    TInt length = aStringToChop.Length();
    TPtr ptr( const_cast<TText*>( aStringToChop.Ptr() ), length, length );

    TAknTextWrapper wrapper(
        ptr,
        NULL,
        aFont,
        aChoppedArray,
        aLineWidth,
        TAknTextWrapper::EReserveVisualBuffer | 
        TAknTextWrapper::EConvertToVisual,
        aDirectionality );

    return wrapper.ChopToArrayAndClipL();
    }

// -----------------------------------------------------------------------------
// AknBidiTextUtils::ConvertToVisualAndWrapToStringL
// -----------------------------------------------------------------------------
//
EXPORT_C void AknBidiTextUtils::ConvertToVisualAndWrapToStringL(
    const TDesC& aStringToWrap,
    const CArrayFix<TInt>& aLineWidthArray,
    const CFont& aFont,
    TDes& aWrappedString,
    TBool aInsertTruncationChar,
    AknBidiTextUtils::TParagraphDirectionality aDirectionality )
    {
    // Ensure that there is the required free space in descriptor

    __ASSERT_ALWAYS( 
        aWrappedString.MaxLength() - aStringToWrap.Length() >=
        aLineWidthArray.Count() * (KAknBidiExtraSpacePerLine + 1),
        Panic( EAknPanicInvalidValue ) );

    // Perform wrapping

    TInt flags( TAknTextWrapper::EConvertToVisual );

    if ( aInsertTruncationChar )
        {
        flags |= TAknTextWrapper::EClip;
        }

    AknTextUtils::WrapToStringL(
        aStringToWrap,
        aLineWidthArray, 
        aFont, 
        aWrappedString,
        flags,
        aDirectionality );
    }

// -----------------------------------------------------------------------------
// AknBidiTextUtils::ConvertToVisualAndWrapToArrayWholeTextL
// -----------------------------------------------------------------------------
//
EXPORT_C HBufC* AknBidiTextUtils::ConvertToVisualAndWrapToArrayWholeTextL( 
    const TDesC& aLogicalText,
    const CArrayFix<TInt>& aLineWidthArray,
    const CFont& aFont,
    CArrayFix<TPtrC>& aWrappedArray,
    AknBidiTextUtils::TParagraphDirectionality aDirectionality )
    {
    __ASSERT_DEBUG( aLineWidthArray.Count(), Panic( EAknPanicInvalidValue ) );

    TInt length = aLogicalText.Length();
    TPtr ptr( const_cast<TText*>( aLogicalText.Ptr() ), length, length );

    TAknTextWrapper wrapper(
        ptr,
        &aLineWidthArray,
        aFont,
        aWrappedArray,
        0,
        TAknTextWrapper::EReserveVisualBuffer |
        TAknTextWrapper::EWrapAllText |
        TAknTextWrapper::EConvertToVisual,
        aDirectionality );

    return wrapper.WrapToArrayL();
    }

EXPORT_C TInt AknBidiTextUtils::MeasureTextBoundsWidth(
    const CFont& aFont,
    const TDesC& aText,
    CFont::TMeasureTextInput::TFlags aOrder)
    {
    TInt textAdvance;
    CFont::TMeasureTextInput input; 
    input.iFlags = aOrder;
    CFont::TMeasureTextOutput output; 
    textAdvance = aFont.MeasureText( aText, &input, &output );
	TRect bounds = output.iBounds;
	bounds.iTl.iX = Min(bounds.iTl.iX, 0);
	bounds.iBr.iX = Max(bounds.iBr.iX, textAdvance);    
    return bounds.Width();
    }
//  End of File  
