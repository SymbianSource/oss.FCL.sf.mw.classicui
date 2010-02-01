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
* Description:  Text utilities e.g. truncating and wrapping to be used in code
*                that needs to support text that requires conversion from logical
*                to visual order, e.g. Arabic/Hebrew.
*                Logical text is given as input to all methods.
*                Output text is in visual order.
*
*
*/



#ifndef AKN_BIDI_TEXT_UTILS_H
#define AKN_BIDI_TEXT_UTILS_H

//  INCLUDES
#include <e32base.h>
#include <uikon.hrh> // KEllipsis
#include <gdi.h>     // For CCFont::TMeasureTextInput::TFlags

// CONSTANTS

const TInt KAknBidiExtraSpacePerLine = 4;

// FORWARD DECLARATIONS


// CLASS DECLARATION

/**
* Text utilities e.g. truncating and wrapping to be used in code that needs to
* support text that requires conversion from logical to visual order,
* e.g. Arabic/Hebrew Logical text is given as input to all
* methods. Output text is in visual order.
*
* Input text buffers given as parameters must contain extra space for some additional
* characters as stated in method descriptions.
*
* @lib avkon.dll
* @since 2.0
*/
class AknBidiTextUtils
    {
    public:

    /**
    * Overall paragraph directionality
    */
    enum TParagraphDirectionality
        {
        EImplicit = 0, // implicit directionality of input text
        ELeftToRight = 1,
        ERightToLeft = 2
        };

    public: // New functions

    /** 
    * Generic text clipping. This method allocates memory for visual buffer,
    * and can leave in OOM situations.
    *
    * @since 2.0
    *   
    * @param aLogicalText   String to be clipped in logical order. This method
    *                       converts it in visual order and clips it if necessary.
    *                       The descriptor must contain extra space of at least
    *                       KAknBidiExtraSpacePerLine. Otherwise, a panic is raised.
    *
    * @param aFont          Font used when drawing the text.
    *
    * @param aMaxWidthInPixels Maximum width of text that is not be clipped.
    *
    * @param aMaxClippedWidthInPixels Maximum width of text that is clipped.
    *    Note that this should not be many pixels bigger than aMaxWidthInPixels
    *    because then truncation character could appear after fully fitting text.
    *
    * @param aDirectionality Paragraph directionality.
    *
    * @param aClipChar      The truncation character.
    *                       0xFFFF if no truncation character is to be used.
    * 
    * @return ETrue if the text was clipped, EFalse otherwise.
    */
    IMPORT_C static TBool ConvertToVisualAndClipL(
        TDes& aLogicalText,
        const CFont& aFont,
        TInt aMaxWidthInPixels,
        TInt aMaxClippedWidthInPixels,
        AknBidiTextUtils::TParagraphDirectionality aDirectionality = EImplicit,
        TChar aClipChar = KEllipsis );

    /** 
    * Generic text clipping. This method does not allocate memory and can
    * be used in non-leaving functions. You must give a preallocated visual
    * buffer as a parameter.
    *
    * @since 2.0
    *   
    * @param aLogicalText   String to be clipped in logical order.
    *
    * @param aVisualText    The reordered text in visual form is returned here.
    *                       This method converts aLogicalText into visual order
    *                       and clips it if necessary. Maximum length of this 
    *                       descriptor must be at least 
    *                       aLogicalText.Length() + KAknBidiExtraSpacePerLine.
    *                       otherwise a panic is raised.
    *
    * @param aFont          Font used when drawing the text.
    *
    * @param aMaxWidthInPixels Maximum width of text that is not clipped.
    *
    * @param aMaxClippedWidthInPixels Maximum width of text that is clipped.
    *    Note that this should not be many pixels bigger than aMaxWidthInPixels
    *    because then truncation character could appear after fully fitting text.
    *
    * @param aDirectionality Paragraph directionality.
    *
    * @param aClipChar      The truncation character.
    *                       0xFFFF if no truncation character is to be used.
    * 
    * @return ETrue if the text was clipped, EFalse otherwise.
    */
    IMPORT_C static TBool ConvertToVisualAndClip(
        const TDesC& aLogicalText,
        TDes& aVisualText,
        const CFont& aFont,
        TInt aMaxWidthInPixels,
        TInt aMaxClippedWidthInPixels,
        AknBidiTextUtils::TParagraphDirectionality aDirectionality = EImplicit,
        TChar aClipChar = KEllipsis );

    /**
    * Tests how big run info array the given text requires and
    * tries to increase the size of the array if required (stored in CAknEnv).
    *
    * This method is useful with the non-leaving version of
    * ConvertToVisualAndClip(). By calling this method successfully
    * (means KErrNone is returned) at any point during the lifetime of the application
    * it is guaranteed that the text gets correctly converted in visual form even
    * in out-of-memory situation when calling ConvertToVisualAndClip().
    *
    * Note that there is no use calling this method if you do not handle the
    * return code, because the truncating methods already do that.
    *
    * @since 2.0
    *   
    * @param aLogicalText Text in logical order.
    *
    * @return KErrNone or KErrNoMemory.
    */
    IMPORT_C static TInt PrepareRunInfoArray( const TDesC& aLogicalText );

    /**
    * Converts a string in visual order and wraps it to an array of pointers.
    * The maximum number of lines and line widths are specified in
    * aLineWidthArray. The pointers in aWrappedArray are set to point to
    * positions inside descriptor given in aLogicalText.
    *
    * @since 2.0
    *   
    * @param aLogicalText       Logical text to be wrapped. This method
    *                           converts it in visual form (in strictly left to
    *                           right order) and wraps it to lines.
    *                           These lines can then be renderered using e.g.
    *                           CGraphicsContext::DrawText().
    *                           The descriptor must contain extra space of at least
    *                           (aLineWidthArray.Count() * KAknBidiExtraSpacePerLine).
    *                           Otherwise, a panic is raised.
    *
    * @param aLineWidthArray    Line widths in pixels. Also determines maximum
    *                           number of lines.
    *
    * @param aFont              Used font.
    *
    * @param aWrappedArray      Pointers to wrapped lines.
    *
    * @param aInsertTruncationChar Whether to insert truncation character
    *                           (KEllipsis) or not if the text does not fit in
    *                           given maximum number of lines.
    *
    * @param aDirectionality    Paragraph directionality.
    */
    IMPORT_C static void ConvertToVisualAndWrapToArrayL(
        TDes& aLogicalText,
        const CArrayFix<TInt>& aLineWidthArray,
        const CFont& aFont,
        CArrayFix<TPtrC>& aWrappedArray,
        TBool aInsertTruncationChar,
        AknBidiTextUtils::TParagraphDirectionality aDirectionality = EImplicit );

    /**
    * Converts a string in visual order and wraps it to an array of pointers.
    * Constant line width is given. The pointers in aWrappedArray are set to
    * point to positions inside the returned heap descriptor.
    *
    * @since 2.0
    *   
    * @param aLogicalText       Logical text to be wrapped. This method
    *                           converts it in visual form (in strictly left to
    *                           right order) and wraps it to lines. (The returned
    *                           heap descriptor contains the string in visual
    *                           order.)
    *                           These lines can then be renderered using e.g.
    *                           CGraphicsContext::DrawText().
    *
    * @param aLineWidth         Constant line width in pixels.
    *
    * @param aFont              Used font.
    *
    * @param aWrappedArray      Pointers to wrapped lines.
    *
    * @param aDirectionality    Paragraph directionality.
    *
    * @return Heap descriptor containing the wrapped string in visual form.
    *         Ownership is transferred to the caller.
    */
    IMPORT_C static HBufC* ConvertToVisualAndWrapToArrayL( 
        const TDesC& aLogicalText,
        TInt aLineWidth,
        const CFont& aFont,
        CArrayFix<TPtrC>& aWrappedArray,
        AknBidiTextUtils::TParagraphDirectionality aDirectionality = EImplicit );
    
    /**
    * Converts a string in visual order and chops each line when a line break
    * character is encountered.
    * Clips at the end of each line if there isn't enough space
    * on that line. When clipping, KEllipsis (shown as 3 dots) is inserted at
    * the end of the line. The pointers in aChoppedArray are set to point to
    * positions inside aLogicalText.
    *
    * @since 2.0
    *   
    * @param aLogicalText       Logical text to be chopped. This method
    *                           converts it in visual form (in strictly left to
    *                           right order) and chops each line when a line break
    *                           character is encountered.
    *                           These lines can then be renderered using e.g.
    *                           CGraphicsContext::DrawText().
    *                           The descriptor must contain extra space of at least
    *                           (aLineWidthArray.Count() * KAknBidiExtraSpacePerLine).
    *                           Otherwise, a panic is raised.
    *
    * @param aLineWidthArray    Line widths in pixels. Also determines maximum
    *                           number of lines.
    *
    * @param aFont              Used font.
    *
    * @param aChoppedArray      Pointers to chopped lines.
    *
    * @param aDirectionality    Paragraph directionality.
    */
    IMPORT_C static void ConvertToVisualAndChopToArrayL(
        TDes& aLogicalText,
        const CArrayFix<TInt>& aLineWidthArray, 
        const CFont& aFont,                    
        CArrayFix<TPtrC>& aChoppedArray,
        AknBidiTextUtils::TParagraphDirectionality aDirectionality = EImplicit );

    /**
    * Converts a string in visual order and chops each line when a line break
    * character is encountered.
    * Clips at the end of each line if there isn't enough space
    * on that line. When clipping, KEllipsis (shown as 3 dots) is inserted at
    * the end of the line. The pointers in aChoppedArray are set to point to
    * positions inside the returned heap descriptor.
    *
    * @since 2.0
    *   
    * @param aLogicalText       Logical text to be chopped. This method
    *                           converts it in visual form (in strictly left to
    *                           right order) and chops each line when a line break
    *                           character is encountered. (The returned
    *                           heap descriptor contains the string in visual
    *                           order.)
    *                           These lines can then be renderered using e.g.
    *                           CGraphicsContext::DrawText().
    *
    * @param aLineWidth         Constant line width in pixels
    *
    * @param aFont              Used font.
    *
    * @param aChoppedArray      Pointers to chopped lines.
    *
    * @param aDirectionality Paragraph directionality.
    *
    * @return Heap descriptor containing the chopped string in visual form.
    *         Ownership is transferred to the caller.
    */
    IMPORT_C static HBufC* ConvertToVisualAndChopToArrayL(
        const TDesC& aLogicalText,
        TInt aLineWidth,
        const CFont& aFont,
        CArrayFix<TPtrC>& aChoppedArray,
        TParagraphDirectionality aDirectionality = EImplicit );

    /**
    * Converts a string in visual order and wraps it to lines by inserting
    * '\n' after each line in text.
    * The result is copied into aWrappedString.
    *
    * @since 2.0
    *   
    * @param aLogicalText       Logical text to be wrapped. This method
    *                           converts it in visual form (in strictly left to
    *                           right order) and wraps it to lines in aWrappedString.
    *                           '\n' is inserted after each line. 
    *                           These lines can then be renderered using e.g.
    *                           CGraphicsContext::DrawText().
    *                           
    * @param aLineWidthArray    Line widths in pixels. Also determines maximum
    *                           number of lines.
    *
    * @param aFont              Used font.
    *
    * @param aWrappedString     Wrapped string. The maximum length of the descriptor
    *                           must be at least
    *                   ( aLogicalText.Length() +
    *                     aLineWidthArray.Count() * (KAknBidiExtraSpacePerLine+1) ).
    *                           Otherwise, a panic is raised.
    *
    * @param aInsertTruncationChar Whether to insert truncation character
    *                           (KEllipsis) or not if the text does not fit in
    *                           given maximum number of lines.
    *
    * @param aDirectionality    Paragraph directionality.
    */
    IMPORT_C static void ConvertToVisualAndWrapToStringL( 
        const TDesC& aLogicalText,
        const CArrayFix<TInt>& aLineWidthArray,
        const CFont& aFont,
        TDes& aWrappedString,
        TBool aInsertTruncationChar,
        AknBidiTextUtils::TParagraphDirectionality aDirectionality = EImplicit );

    // -------------------------------------------------------------------------
    // The following methods are introduced in release 2.1
    // -------------------------------------------------------------------------

    /**
    * Converts a string in visual order and wraps it to an array of pointers.
    * Line widths are specified in aLineWidthArray. If all the text does not fit
    * in the amount of lines in aLineWidthArray, the last line width in the array
    * is used for all the remaining lines. The pointers in aWrappedArray are set
    * to point to positions inside the returned heap descriptor.
    *
    * @since 2.1
    *
    * @param aLogicalText       Logical text to be wrapped. This method
    *                           converts it in visual form (in strictly left to
    *                           right order) and wraps it to lines. (The returned
    *                           heap descriptor contains the string in visual
    *                           order.)
    *                           These lines can then be renderered using e.g.
    *                           CGraphicsContext::DrawText().
    *
    * @param aLineWidthArray    Line widths in pixels. If the whole text does
    *                           not fit in the number of lines specified in the
    *                           array, the last width is used for the remaining
    *                           lines.
    *
    * @param aFont              Used font.
    *
    * @param aWrappedArray      Pointers to wrapped lines.
    *
    * @param aDirectionality    Paragraph directionality.
    *
    * @return Heap descriptor containing the wrapped string in visual form.
    *         Ownership is transferred to the caller.
    */
    IMPORT_C static HBufC* ConvertToVisualAndWrapToArrayWholeTextL( 
        const TDesC& aLogicalText,
        const CArrayFix<TInt>& aLineWidthArray,
        const CFont& aFont,
        CArrayFix<TPtrC>& aWrappedArray,
        AknBidiTextUtils::TParagraphDirectionality aDirectionality = EImplicit );

    /**
    * Measures the full horizontal width in pixels of the passed-in text using a particular font, 
    * including in the width any side-bearings of the glyphs at the ends of the text, and any
    * declared "advance" of the run of glyphs. 
    * 
    * It cannot be used for vertical text measurement.
    * 
    * Side-bearings are parts of glyphs that extend left or right from the normal width
    * or "advance" of the glyph. A left side-bearing, for instance, will overlap with a glyph
    * to its left. Another way of thinking about this is that the origin (0,0) of the glyph is 
    * not at its bottom left. 
    *
    * The advance of a run of glyphs is the sum of the advances - once in visual ordering and 
    * shaping has been performed - of all the glyphs. It is defined relative to a drawing origin.
    * 
    * Within runs of text, side-bearings do not contribute to the width of the text. However,
    * at the (visual) ends of text, they are likely to need to be counted, depending upon the
    * exact use case.
    * 
    * This method returns the width of the horizontal envelope of the text by taking the extreme 
    * horizontal extents of the text bounds rectangle (which includes side-bearings on either end)
    * and the extent of the advance. Thus it returns the width of :
    *   Min(<left_text_bound>, 0), Max( <right_text_bound>, <advance>)
    *   
    * This method should be used when the proposed text is going to be drawn using any horizontal
    * CGraphicsContext::DrawText drawing API. 
    *
    * The text can be in visual or logical order.
    *
    * @since 3.1
    * @param aFont  Font to use
    * @param aText  Text to be measured
    * @param aOrder Whether the text provided is in visual or logical order
    * @return       width of the text in pixels.
    */
    IMPORT_C static TInt AknBidiTextUtils::MeasureTextBoundsWidth(
        const CFont& aFont,
        const TDesC& aText,
        CFont::TMeasureTextInput::TFlags aOrder);

    private:

        static TBool DoConvertToVisualAndClip(
            const TDesC& aLogicalText,
            TDes& aVisualText,
            const CFont& aFont,
            TInt aMaxWidthInPixels,
            TInt aMaxClippedWidthInPixels,
            AknBidiTextUtils::TParagraphDirectionality aDirectionality,
            TChar aClipChar );

        /**
        * C++ default constructor.
        */
        AknBidiTextUtils();
    };

#endif      // AKN_BIDI_TEXT_UTILS_H
            
// End of File
