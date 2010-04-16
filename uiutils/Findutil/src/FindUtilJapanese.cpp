/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:         Japanese Find Utilities implementation file.
*
*/










// INCLUDE FILES
#include "FindUtilJapanese.h"
#include <jplangutil.h>

// CONSTANTS
_LIT(KDesWildCard, "*");

const TInt KLitTab('\t');
const TInt KLitSpace(' ');
const TInt KLitHyphen('-');
const TInt KLitQuestion('?');
const TInt KLitWildCard('*');
const TInt KLitFullWidthSpace(0x3000);
const TInt KLitFullWidthHyphen(0x2015);
const TInt KLitFullWidthQuestion(0xff1f);
const TInt KLitFullWidthWildCard(0xff0a);
const TInt KLitStartHiragana(0x3041);
const TInt KLitEndHiragana(0x3096);
const TInt KLitStartKatakana(0x30A1);
const TInt KLitLineFeed(8233);

const TInt KMaxWordLength = 200;
const TUint KFullWidthSpace = 0x3000;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CFindUtilJapanese::CFindUtilJapanese
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CFindUtilJapanese::CFindUtilJapanese()
    {
    }

// Destructor
CFindUtilJapanese::~CFindUtilJapanese()
    {
    }

// -----------------------------------------------------------------------------
// CFindUtilJapanese::IsFindWordSeparator
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TBool CFindUtilJapanese::IsFindWordSeparator(TChar aCh)
    {
    return aCh == KLitSpace || aCh == KLitHyphen || aCh == KLitTab ||
        aCh == KLitFullWidthSpace || aCh == KLitFullWidthHyphen ||
        aCh == KLitLineFeed;
    }


// -----------------------------------------------------------------------------
// CFindUtilJapanese::RemoveWordSeparatorsAndWildChars
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CFindUtilJapanese::RemoveWordSeparatorsAndWildChars( TDes16& aSearchPtr )
    {
    TInt len = aSearchPtr.Length();

    for ( TInt ii(0); ii < len; ii++ )
        {
        if ( IsFindWordSeparator(static_cast<TChar>(aSearchPtr[ii])) || 
            aSearchPtr[ii] == KLitWildCard || aSearchPtr[ii] == KLitQuestion ||
            aSearchPtr[ii] == KLitFullWidthWildCard || 
            aSearchPtr[ii] == KLitFullWidthQuestion)
            {
            aSearchPtr.Delete(ii, 1);
            len--;
            continue;
            }
        }

    }

inline TBool IsFindWordSeparator(TChar aCh)
    {
    return (aCh == ' '|| aCh == '-' || aCh == '\t' || aCh==KFullWidthSpace);
    }

void ReplaceCharacters(TDes &aDes, const TDesC &aChars, TChar aReplacement)
    //
    // Running time O(aDes.Length() * aChars.Length())
    // Does not change length of the string.
    // 
    {
    TInt src = 0;
    TInt srclength = aDes.Length();
    while(src < srclength)
        {
        TChar c = aDes[src];
        if (aChars.LocateF(c) != KErrNotFound)
            aDes[src] = TUint16(aReplacement);
        ++src;
        }
    }


// -----------------------------------------------------------------------------
// CFindUtilJapanese::MyFindC
// (other items were commented in a header).
// This method is called by MatchRefineL().
// -----------------------------------------------------------------------------
//
TInt CFindUtilJapanese::MyFindC(const TDesC &aItemString, const TDesC &aSearchText)
    {
    TBuf<KMaxWordLength> searchText;
    TBuf<KMaxWordLength> itemString;
    searchText.Append(aSearchText);
    // The replacecharacters are to disable regexp matching provided
    // by MatchC().
    _LIT(KQuestion,"?");
    _LIT(KStar,"*");
    ReplaceCharacters(searchText, KQuestion, TChar('\t'));
    ReplaceCharacters(searchText, KStar, TChar('\r'));
    searchText.Append(KStar);
    if (aItemString.Length() < KMaxWordLength)
        {
        itemString.Append(aItemString);
        }
    else
        {
        itemString.Append(aItemString.Left(KMaxWordLength));
        }
    ReplaceCharacters(itemString, KQuestion, TChar('\t'));
    ReplaceCharacters(itemString, KStar, TChar('\r'));

    CnvKatakana(searchText);
    CnvKatakana(itemString);

    TInt length = itemString.Length();
    for(int i=0;i<length;i++)
        {
        if (i==0 || IsFindWordSeparator(aItemString[i-1]))
            {
            if (itemString.Mid(i).MatchC(searchText) != KErrNotFound)
                {
                return i;
                }
            }
        }
    return KErrNotFound;
    }

// -----------------------------------------------------------------------------
// CFindUtilJapanese::IsMatch
// (other items were commented in a header).
// This method is called by MatchRefineL(). 
// This method separates by 4 characters, and this method calls MyFindC().
// -----------------------------------------------------------------------------
//
TBool CFindUtilJapanese::IsMatch( const TDesC& aItemString, const TDesC& aSearchText)
    {
    TPtrC itemptr(aItemString);
    TPtrC searchptr(aSearchText);

    TBool match = EFalse;
    
    FOREVER 
        {
        // Loop invariant: itemptr is next character from ' ' or '-'
        // Loop invariant: seachptr is at beginning of searched item
        TInt val = MyFindC(itemptr,searchptr);
        if (val == 0)
            {
            match = ETrue;
            break;
            }
        if (val != KErrNotFound && IsFindWordSeparator(itemptr[val-1]))
            {
            match = ETrue;
            break;
            }

        // find the word separator characters from list item
        const TInt maxFindChar = 4;
        TChar findchar = KFullWidthSpace;
        TInt findindex;
        for (findindex=0; findindex < maxFindChar; findindex++)
            {
            switch(findindex)
                {
                case 0: findchar = (' ');  break;   // space
                case 1: findchar = KFullWidthSpace; break;   // full space
                case 2: findchar = ('-');  break;   // minus
                case 3: findchar = ('\t'); break;   // tab
                }
            const TInt findpos = itemptr.LocateF(findchar);
            if (findpos != KErrNotFound)
                {
                itemptr.Set(itemptr.Mid(findpos+1));
                break;
                }
            }
        if (findindex >= maxFindChar)
            {
            match = EFalse;
            break;
            }
        if (itemptr.Length() == 0)
            {
            match = EFalse;
            break;
            }
        }
    return match;
    }

// -----------------------------------------------------------------------------
// CFindUtilJapanese::CnvKatakana
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CFindUtilJapanese::CnvKatakana(TDes& aDes)
    {
    TInt len = aDes.Length();
    for (TInt i(0); i < len; i++)
        {
        TUint16& ch = aDes[i];
        if (ch >= KLitStartHiragana && ch <= KLitEndHiragana)
            {
            ch += (KLitStartKatakana - KLitStartHiragana);
            }
        }
    }

// -----------------------------------------------------------------------------
// CFindUtilJapanese::Match
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TBool CFindUtilJapanese::Match(const TDesC& aContactsField, const TDesC& aWord)
    {
    if (!aContactsField.Length())
        {
        return EFalse;
        }

    TBuf<KMaxWordLength> searchText(aWord);
    TBuf<KMaxWordLength> itemString(aContactsField);

    searchText.Append(KDesWildCard);
    CnvKatakana(searchText);
    CnvKatakana(itemString);

    if (itemString.MatchC(searchText) != KErrNotFound)
        {
        return ETrue;
        }

    return EFalse;
    }

// -----------------------------------------------------------------------------
// CFindUtilJapanese::MatchRefineL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TBool CFindUtilJapanese::MatchRefineL( const TDesC& aItemString, const TDesC &aSearchText)
    {
    if ( aItemString.Length() == 0 )
        {
        return EFalse;
        }

    if ( aSearchText.Length() == 0 )
        {
        return ETrue;
        }

    return IsMatch(aItemString, aSearchText);
    }

// -----------------------------------------------------------------------------
// CFindUtilJapanese::IsWordValidForMatching
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TBool CFindUtilJapanese::IsWordValidForMatching(const TDesC& /*aWord*/)
    {
    return ETrue;
    }


// -----------------------------------------------------------------------------
// CFindUtilJapanese::MatchAdaptiveRefineL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//  
TBool CFindUtilJapanese::MatchAdaptiveRefineL( const TDesC& /*aItemString*/, 
	                                           const TDesC& /*aSearchText*/,
	                                           HBufC*& /*aNextChars*/ )
	{	
  	return EFalse;	
	}
	
// ---------------------------------------------------------
// Match arithmetic for accurate search, special conversion 
// for aItemString is implemented with MFindStringConverter
// before the final match
// ---------------------------------------------------------
//
TBool CFindUtilJapanese::MatchRefineL( const TDesC& /*aItemString*/, const TDesC& /*aSearchText*/, 
                                       TMatchPolicy /*aPolicy*/, MFindStringConverter* /*aConverter*/)
    {
    return EFalse;
    }	

// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// FindUtilFactoryFunctionL
// Factory function at first ordinal
// Returns: MFindUtil: It returns MFindUtil I/F.
// -----------------------------------------------------------------------------
//
EXPORT_C MFindUtil* FindUtilFactoryFunctionL()
    {
    return new( ELeave ) CFindUtilJapanese();
    }

//  End of File  
