/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies).
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
*   This class provides facilities to allow previously grouped and digit-type converted
*   phone number descriptors to be laid out into a set of lines of given width.
* 
*   This class is intended for descriptors of phone number content only.  It has the following
*   limitations:
*   - it cannot deal with bidirectional text. All text is taken to be left to right.
*   - it cannot deal with surrogate pairs    
*   - it cannot deal with ligatures, diacritical constructions or other compounding of 
*       glyphs.
*   
*   However, if the descriptor content is restricted to digits (possibliy in localized digit
*   types) and to a restricted range of ASCII text used for phone numbers and their separators
*   ( *+pw()-[] and <SPC> )  it will work properly.
*
*   Methods here may be used to lay out text into several lines.  The methods generally take CFont
*   references and available widths in pixels, and either return width information, perform
*   wrapping or truncation.  
*
*   Phone numbers are treated specially for layout and truncation.  If several lines are involved,
*   they should fill from the bottom up to the top, and truncation should occur on the left, that is, 
*   from the beginning of the text. Hence methods here refer to clipping text on the left, or counting
*   characters from the right. Visibility of the numbers is improved by attempting layout first
*   with larger fonts. It should be possible to use these methods to decide on the font 
*   to be used for the available space, and then finally to perform the layout in that font.
*   
*
*/


#ifndef AKNPHONENUMBERTEXTUTILS_H
#define AKNPHONENUMBERTEXTUTILS_H

// INCLUDES

#include <e32std.h>
#include <gdi.h>

// CONSTANTS
/**
* Layout utilities specifically targetted at phone numbers
*
* Grouping and digit type conversion of the phone number descriptor should already have been
* performed
*
*  @lib Avkon.dll
*  @since 2.6
*/
class AknPhoneNumberTextUtils
    {
    public:

    /**
    * Wrap phone number text to a maximum number of lines of the same width in pixels, 
    * using a specified font. 
    * 
    * The array of lines is returned.  Text is wrapped according to phone number rules; 
    * wrapping procedes from the end of the text, back toward the beginning;
    * 
    * Note that aWrappedArray[0] holds the end (logical and visual) of the text, while the 
    * beginning of the text (or the first characters to fit into the given lines) is in the 
    * highest indexed line, i.e. the line at aWrappedArray.Count()-1
    * 
    * These lines should normally be rendered with the aWrappedArray[0] text physically lowest 
    * on the display.
    * 
    * The input descriptor is not modified by this method. The modification required to place the 
    * truncation marker into the last line is in a separate method in this class, ClipLineOnLeft.
    * 
    * The return value indicates that not all the text was accomodated in the given number
    * of lines.
    * 
    * @since 2.6
    * @param    aPhoneNumberToWrap  input descriptor
    * @param    aLineWidthInPixels  maximum width of each line
    * @param    aMaxLines,          maximum number of lines to wrap into
    * @param    aFont,              font to use to measure text
    * @param    aWrappedArray       array of TPtrs to the lines of wrapped number
    * @return                       EFalse if the text fits into the available lines
    */
    IMPORT_C static TBool WrapPhoneNumberToArrayL( 
        const TDesC& aPhoneNumberToWrap,
        TInt aLineWidthInPixels, 
        TInt aMaxLines,
        const CFont& aFont,
        CArrayFix<TPtrC>& aWrappedArray );

    /**
    * Modify a previously wrapped line to exhibit truncation on the left. 
    * For all expected use cases, the line passed will be the last line returned by a 
    * call to WrapPhoneNumberToArrayL()
    *  e.g.
    *   ClipLineOnLeft( wrappedArray->At( count-1 ), phoneNumberToWrap, font, widthInPixels);
    * 
    * This deferral of the truncation is useful so that WrapPhoneNumberToArrayL() may be called
    * more than once, trying different fonts, until the layout is decided, and then the last line
    * can be modified by the truncation.
    *
    * For consistent behaviour, the font and width parameters should be the same as those
    * passed to WrapPhoneNumberToArrayL().
    *
    * A call to this method invariably will result in the aOriginalBuffer being modified.
    * The modification will be limited to 
    * - that part of this buffer pointed to by aLine,
    * - lower indices in aOriginalBuffer than those pointed to by aLine 
    * 
    * Truncation is performed with a default Series 60 truncation marker.
    * 
    * @since 2.6
    * @param    aLine           As input, points to a section of aOriginalBuffer that contains
    *                           the last line of text that fitted.
    *                           As output, this points to a section of aOriginalBuffer now 
    *                           containing a truncation marker and the remainder of the text 
    *                           fitting on the line.
    * @param    aOriginalBuffer Modifiable descriptor encompassing aLine. Under normal 
    *                           circumstances, the first characters in aOriginalBuffer will
    *                           precede the first characters in aLine - i.e. trunctation
    *                           marking is needed.
    * @param    aLineWidthInPixels  Width that the text needs to fit into.
    * @param    aFont               Font to use to measure text.
    */
    IMPORT_C static void ClipLineOnLeft( 
        TPtrC& aLine, 
        TDes& aOriginalBuffer, 
        TInt aLineWidthInPixels,
        const CFont& aFont );

    /**
    * Determine how many characers in the passed descriptor, measuring from the end, 
    * fit in the given width in pixels, using the provided font.
    * 
    * It is recommended only for content that will be found in a phone number, including
    * Arabic or other variant numeric characters.
    * 
    * @since 2.6
    * @param    aPhoneNumber        phone number for displaying
    * @param    aLineWidthInPixels  width of the field to render to
    * @param    aFont               font to use
    * @return                       number of characters that fit on the right    
    */
    IMPORT_C static TInt CharsThatFitOnRight(
        const TDesC& aPhoneNumber,
        TInt aLineWidthInPixels,
        const CFont& aFont );
    };

#endif

// End of File
