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
* Description:  Avkon text wrapper implementation class
*
*
*/



#ifndef AKNTEXTWRAPPER_H
#define AKNTEXTWRAPPER_H

//  INCLUDES
#include <e32base.h>
#include "AknLineBreaker.h"
#include "AknBidiTextUtils.h"

// FORWARD DECLARATIONS

class CFont;

// CONSTANTS

struct TAknLocVariant
    {
    TInt iStart;
    TInt iEnd;
    };

const TInt KAknMaxLocVariants = 5;

// CLASS DECLARATION

/**
* Text wrapper implementation class
*
*  @lib avkon.dll
*  @since 2.0
*
*  @internal
*/
class TAknTextWrapper
    {
    public:

        enum // used with bit flags, values must be powers of two
            {
            EClip                   = 0x0001,
            EConvertToVisual        = 0x0002,
            EReserveVisualBuffer    = 0x0004,
            EWrapAllText            = 0x0008,
            // internal flags    
            EClipRequired           = 0x4000,
            EFits                   = 0x8000
            };

    public:  // Constructors and destructor

        /**
        * C++ default constructor.
        */
        TAknTextWrapper(
            TDes& aStringToWrap,
            const CArrayFix<TInt>* aLineWidthArray, 
            const CFont& aFont,
            CArrayFix<TPtrC>& aWrappedArray,
            TInt aLineWidth,
            TInt aFlags,
            AknBidiTextUtils::TParagraphDirectionality aDirectionality );

        /**
        * Destructor.
        */
        ~TAknTextWrapper();

    public: // New functions

        /**
        * Wrap implementation.
        *
        * @return If flag EReserveVisualBuffer was set, allocated visual buffer.
        *         Otherwise, NULL.
        */
        HBufC* WrapToArrayL();

        /**
        * Chop implementation.
        *
        * @return If flag EReserveVisualBuffer was set, allocated visual buffer.
        *         Otherwise, NULL.
        */
        HBufC* ChopToArrayAndClipL();

        /*
        * Separates localisation variants from the given text.
        * Those variants are separated with the character 0x0001.
        * They are sorted in descending order of character count
        * and returned in the array aVariants.
        *
        * @param aText
        * @param aVariants Pointer to an array containing room for at least
        * 'KAknMaxLocVariants' elements.
        *
        * @ret Number of the localisation variants returned in aVariants.
        * The minimum value is 1 and the maximum value is KAknMaxLocVariants.
        */
        static TInt GetLocVariants(
            const TDesC& aText, TAknLocVariant* aVariants );

    private: // New functions

        HBufC* DoOperationL( TInt aOp );
        HBufC* DoWrapToArrayL();
        HBufC* DoChopToArrayAndClipL();

        /*
        * Finds last legal position to break the line in given text,
        * according to the given line width.
        *
        * If a legal breaking position is found, iBreakPos is set to it.
        *
        * @param aText text
        * @param aFitsInLine max amount of characters fitting in line
        * @param aLineWidth line width in pixels
        * @param aReplaceSoftHyphen whether to replace soft hyphen with real hyphen or not,
        *        if the line is broken after a soft hyphen
        *
        * @return ETrue if a legal breaking position was found, EFalse otherwise.
        */
        TBool GetWrappingPosition( 
            const TDesC& aText,
            TInt aFitsInLine,
            TInt aLineWidth,
            TBool aReplaceSoftHyphen );

        /*
        * Appends the given line in the result array.
        *
        * @param aLine line to be appended
        */
        void AppendToArrayL( const TDesC& aLine );

        /*
        * Finds the first explicit line break character in given text.
        *
        * @param aText text
        *
        * @return offset of first explicit line break character or KErrNotFound
        */
        TInt FindLineBreak( const TDesC& aText );

        /*
        * Examines character at position iNextLineStart in descriptor iText
        * and if character is recognized as a separator, increases iNextLineStart
        * by 1. In case of combination CR+LF, iNextLineStart is increased by 2.
        */
        void PassLineBreak();

        /*
        * Inserts ellipsis in given text in the last possible position so that
        * the line fits in the given pixel width. If flag EConvertToVisual is set,
        * this method returns the position of where ellipsis would be added, but
        * does not actually add it. It will be added in logical to visual
        * conversion.
        *
        * @param aText text
        * @param aLineWidth line width in pixels
        *
        * @return If EConvertToVisual flag is set,
        *         position of where ellipsis should be inserted.
        *         otherwise, position after the inserted ellipsis.
        */
        TInt InsertEllipsis( const TDesC& aText, TInt aLineWidth );

        HBufC* ConvertToVisualIfRequiredL();

        TBool ResultFits();

    private: // Data

        TDes& iSourceString;
        const CArrayFix<TInt>* iLineWidthArray;
        const CFont& iFont;
        CArrayFix<TPtrC>& iResultArray;
        TInt iLineWidth;
        TInt iFlags;
        AknBidiTextUtils::TParagraphDirectionality iDirectionality;

        TAknLineBreaker iBreaker;
        const TDesC& iSeparators;

        TPtrC iText;
        TInt iBreakPos;
        TInt iNextLineStart;
    };

#endif      // AKNTEXTWRAPPER_H
            
// End of File
