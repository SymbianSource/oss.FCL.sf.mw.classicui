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
* Description:         Korean Find Utilities header file. 
*
*/



#ifndef __FINDUTILKOREAN__
#define __FINDUTILKOREAN__

#include <e32std.h>

#include "FindUtilBase.h"

/**
 *  CFindUtilKorean utils class
 *
 *  This class is Korean find utils class. It handle Korean variant find
 *  in PhoneBook, LandMark, Clock and so on.
 *
 *  @lib FindUtil.dll
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS(CFindUtilKorean)
    {
    public:  // Constructors and destructor
        
        /**
         * Symbian constructor
         *
         * @since S60 v3.2
         * @return Pointer to created CFindUtilKorean object
         */    
        static CFindUtilKorean* NewL();

        /**
         * Destructor
         *
         * @since S60 v3.2
         */
        virtual ~CFindUtilKorean();

    public:
        TBool IsKoreanLanguage( const TDesC& aDes );   
 
    private:
    
        CFindUtilKorean();

        void ConstructL();
    
        /**
         * Compares two strings against others.
         *
         * @since S60 v3.2
         * @param aItemString for string to being compared
         * @param aSearchText for text to be used in searching
         * @return ETrue if match found, EFalse otherwise
         */    
        TBool IsFindMatchL( 
            const TDesC& aItemString, 
            const TDesC& aSearchText );
        
        /**
         * Decomposes given string to plain jamos.
         *
         * @since S60 v3.2
         * @param aString for string where decomposition is made
         * @param aDecomposedString for plain jamos
         */    
        void DecomposeToPlainJamos( 
            const TDesC& aString,
            HBufC* aDecomposedString );
        
        /**
         * Decomposes hangul syllables to single jamos.
         *
         * @since S60 v3.2
         * @param aChar for char to be decomposed
         * @param aDecomposedString for chars where jamos are gathered
         */    
        void Decompose( TChar aChar, TDes& aDecomposedString );
    
        /**
         * Checks that is given character hangul syllable or not.
         *
         * @since S60 v3.2
         * @param aChar for char to be checked
         * @return ETrue if given input is hangul syllable, EFalse otherwise
         */    
        TBool IsHangulSyllable( TChar aChar );
    
        /**
         * Checks that is given character word separator or not.
         *
         * @since S60 v3.2
         * @param aChar for char to be checked
         * @return ETrue if given character is word separator, EFalse otherwise
         */    
        TBool IsFindWordSeparator( TChar aChar );
     
       /**
         * Checks that is given character hangul compatibility jamo or not.
         *
         * @since S60 v3.2
         * @param aChar for char to be checked
         * @return ETrue if given input is hangul syllable, EFalse otherwise
         */    
        TBool IsHangulCompatibilityJamo( TChar aChar );

    public: 
        /**
         *
         * @since 3.2
         * @param aContactsField is a contact field string.
         * @param aWord is a search string.
         * @return If aWord has been matched with aContactsField, 
         *         ETrue is returned.
         */
        TBool Match( const TDesC& aContactsField, const TDesC& aWord );

        /**
         *
         * @since 3.2
         * @param aItemString is a Contact field string
         * @param aSearchText is a search string
         * @return If aSearchText has been found in aItemString, 
         *         ETrue is returned.
         */
        TBool MatchRefineL( 
            const TDesC& aItemString, 
            const TDesC &aSearchText );

        /**
         *
         * @since 3.2
         * @param aWord 
         * @return ETrue is returned always.
         */
        TBool IsWordValidForMatching(const TDesC& aWord);
        
         /**
         * @since 5.0
         * @param aItemString is a field string
         * @param aSearchText is a search string
         * @param aNextChars is a reference to buffer where next possible characters are saved. 
         *        The HBufC buffer may be re-allocated by this method. 
         *        In that case the pointer reference is modified to point to the re-allocated object.                              
         * @return If aSearchText has been found in aItemString, 
         *         ETrue is returned.
         * NOT IMPLMENTED
         */
        TBool MatchAdaptiveRefineL( const TDesC& aItemString, 
        							const TDesC& aSearchText, 
        							HBufC*& aNextChars);

    };

#endif // __FINDUTILKOREAN__

// End of File
