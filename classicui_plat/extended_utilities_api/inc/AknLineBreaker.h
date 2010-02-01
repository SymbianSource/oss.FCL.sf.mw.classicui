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
* Description:  Line breaker class customized to meet Series 60 specifications.
*
*/


#ifndef AKNLINEBREAKER_H
#define AKNLINEBREAKER_H

// INCLUDES
#include <e32std.h>
#include <linebreak.h>

// FORWARD DECLARATIONS

// CLASS DECLARATIONS

/**
* Customized line breaker to meet Series 60 specifications.
* Customizes the functionality of MLineBreaker by changing the treatment of
* the characters specified to have special treatment in editing spec.
*
* @internal
*/
class TAknLineBreaker : public MLineBreaker
    {
    public: // Functions from base classes

        /**
        * Converts Unicode character into line breaking class.
        * @param aCode Input Unicode value.
        * @param aRangeStart
        *       Returns the start of the contiguous range of characters including
        *       aCode that have the returned line breaking class.
        * @param aRangeEnd
        *       Returns the end of the contiguous range of characters including
        *       aCode that have the returned line breaking class.
        * @return The line breaking class for aCode.
        */
        TUint LineBreakClass(
            TUint aCode, TUint& aRangeStart, TUint& aRangeEnd ) const;

        /**
        * Returns whether line breaks are legal between a character of line
        * breaking class aPrevClass and aNextClass, with intervening spaces or not
        * as determined by aHaveSpaces.
        * @param aPrevClass The class before the potential line break.
        * @param aNextClass The class after the potential line break.
        * @param aHaveSpaces Whether spaces separate the characters.
        * @return
        *       ETrue if and only if a line break is legal in the situation
        *       described.
        */
        TBool LineBreakPossible(
            TUint aPrevClass, TUint aNextClass, TBool aHaveSpaces ) const;


    public: // Functions
        /**
        * Converts Unicode character into line breaking class for special variant.
        * @param aCode Input Unicode value.
        * @param aRangeStart
        *       Returns the start of the contiguous range of characters including
        *       aCode that have the returned line breaking class.
        * @param aRangeEnd
        *       Returns the end of the contiguous range of characters including
        *       aCode that have the returned line breaking class.
        * @param aClass
        *       The line breaking class for aCode.
        * @return ETrue if aCode is special variant character.
        */
        IMPORT_C static TBool IsSpecialVariantChar(TUint aCode, TUint& aRangeStart,
                            TUint& aRangeEnd, TUint& aClass);

    };


#endif // AKNLINEBREAKER_H
            
// End of File
