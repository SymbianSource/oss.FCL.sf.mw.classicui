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
* Description:         Korean Find Utilities implementation.
*
*/


#include "FindUtilKorean.h"
#include <e32svr.h>

#ifdef _DEBUG
#include <charconv.h>
#endif

const TInt KSBase = 0xac00; // base address for hangul syllables
const TInt KLBase = 0x1100; // base address for L-jamo
const TInt KVBase = 0x1161; // base address for V-jamo
const TInt KTBase = 0x11a7; // base address for T-jamo
const TInt KCBase = 0x3131; // base address for hangul compatibility jamo

const TInt KLCount = 19; // count of L-jamos
const TInt KVCount = 21; // count of V-jamos
const TInt KTCount = 28; // count of T-jamos
const TInt KNCount = KVCount * KTCount; // count of V&T-jamo combinations
const TInt KSCount = KLCount * KNCount; // total count of hangul syllables

const TInt KMaxLengthDecomposedSyllable = 3; // syllable can contain 3 jamos

const TInt KLitTab('\t'); // word separator: <tab>
const TInt KLitSpace(' '); // word separator: <space>
const TInt KLitHyphen('-'); // word separator: <hyphen>
const TInt KLitStar('*'); // wildcard matching: <star>
const TInt KLitQuestion('?'); // wildcard matching <question>

// Conversion table for hangul compatibility jamo
const TUint16 conversionTableFromCompatibilityJamoToJamo[] = {
0x1100,
0x1101,
0x11AA,
0x1102,
0x11AC,
0x11AD,
0x1103,
0x1104,
0x1105,
0x11B0,
0x11B1,
0x11B2,
0x11B3,
0x11B4,
0x11B5,
0x11B6,
0x1106,
0x1107,
0x1108,
0x11B9,
0x1109,
0x110A,
0x110B,
0x110C,
0x110D,
0x110E,
0x110F,
0x1110,
0x1111,
0x1112,
0x1161,
0x1162,
0x1163,
0x1164,
0x1165,
0x1166,
0x1167,
0x1168,
0x1169,
0x116A,
0x116B,
0x116C,
0x116D,
0x116E,
0x116F,
0x1170,
0x1171,
0x1172,
0x1173,
0x1174,
0x1175,
};

const TUint16 conversionTableFromLJamoToCompatibilityJamo[] = {
0x3131, /* ? */
0x3132, /* ? */
0x3134, /* ? */
0x3137, /* ? */
0x3138, /* ? */
0x3139, /* ? */
0x3141, /* ? */
0x3142, /* ? */
0x3143, /* ? */
0x3145, /* ? */
0x3146, /* ? */
0x3147, /* ? */
0x3148, /* ? */
0x3149, /* ? */
0x314A, /* ? */
0x314B, /* ? */
0x314C, /* ? */
0x314D, /* ? */
0x314E  /* ? */
};

#define KCCount (sizeof(conversionTableFromCompatibilityJamoToJamo) / sizeof(TUint16))

#define KCountCompToJamo (sizeof(conversionTableFromCompatibilityJamoToJamo) / sizeof(TUint16))

#define KCountLJamoToComp (sizeof(conversionTableFromLJamoToCompatibilityJamo) / sizeof(TUint16))

#define ISLJamo(a) (KLBase <= a && a <= KLBase + KLCount)

#define IsCompatibilityJamo(a) (0x3130 <= a && a <= 0x318F)

const TInt KNextCharsGranuarity = 20;

const TUid KUidPhoneBook = {0x101F4CCE};
const TUid KUidPhoneBookServer = {0x10207277};
const TUid KUidSymbianContactModel = {0x10003A73};

#define IsPhoneBookProcess(a) ( a == KUidSymbianContactModel || a == KUidPhoneBook || a == KUidPhoneBookServer )



// ============================ MEMBER FUNCTIONS =============================


// ---------------------------------------------------------------------------
// Symbian constructor
// ---------------------------------------------------------------------------
//
CFindUtilKorean* CFindUtilKorean::NewL()
    {
    CFindUtilKorean* self = new ( ELeave ) CFindUtilKorean();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// Symbian second-phase constructor
// ---------------------------------------------------------------------------
//
void CFindUtilKorean::ConstructL()
    {
#ifdef _DEBUG
    User::LeaveIfError( iFs.Connect() );
    iConv = CCnvCharacterSetConverter::NewL();
    iConv->PrepareToConvertToOrFromL(0x200100FF, iFs);
#endif
    
    iCurrentProcessUid3 = ( RProcess().Type() )[2];
    }

// ---------------------------------------------------------------------------
// Default constructor
// ---------------------------------------------------------------------------
//
CFindUtilKorean::CFindUtilKorean()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CFindUtilKorean::~CFindUtilKorean()
    {
#ifdef _DEBUG
    delete iConv;
    iFs.Close();
#endif
    }

// ---------------------------------------------------------------------------
// Checks that is given character korean language or not.
// ---------------------------------------------------------------------------
//
TBool CFindUtilKorean::IsKoreanLanguage( const TDesC& aDes )
    {
    for ( TInt i = 0; i < aDes.Length(); i++ )
    	{
    	if ( IsHangulSyllable( aDes[ i ] ) || IsHangulCompatibilityJamo( aDes[ i ] ) )
    		{
    		return ETrue;
    		}
    	}

    return EFalse;
    }

// ---------------------------------------------------------------------------
// Compares two strings against others.
// ---------------------------------------------------------------------------
//
TInt CFindUtilKorean::IsFindMatch( 
        const TDesC& aItemString, 
        const TDesC& aSearchText,
        const TMatchFlag aFlag)
    {
    
#ifdef _DEBUG
    TRAP_IGNORE(
        HBufC8* bufItemString = HBufC8::NewLC((aItemString.Length() + 1) * 2);
        HBufC8* bufSearchText = HBufC8::NewLC((aSearchText.Length() + 1) * 2);
        TPtr8 ptrItemString(bufItemString->Des());
        ptrItemString.FillZ(ptrItemString.MaxLength());
        TPtr8 ptrSearchText(bufSearchText->Des());
        ptrSearchText.FillZ(ptrSearchText.MaxLength());
        iConv->ConvertFromUnicode(ptrItemString, aItemString);
        iConv->ConvertFromUnicode(ptrSearchText, aSearchText);
        RDebug::Printf("DBG: comparing %s, %s", bufItemString->Ptr(), bufSearchText->Ptr());
        CleanupStack::PopAndDestroy(2);
    );
#endif
    
    // To disable the wildchar matching provided by MatchC.
    if ( aFlag == EMatchFlagNone &&
        KErrNotFound != aSearchText.Locate( KLitQuestion ) && 
        KErrNotFound != aSearchText.Locate( KLitStar ) )
    	{
#ifdef _DEBUG
    	RDebug::Printf("DBG: comparing includes wild");
#endif
    	return KErrNotFound;
    	}

#if 1 // 2009.08.14 consonent based search
    TUint flag = aFlag;

    TInt lenItemString = aItemString.Length();
    TInt lenSearchText = aSearchText.Length();

    // detect asterik in end of string
    if (lenSearchText > 0 && aSearchText[lenSearchText - 1] == KLitStar)
        {
        flag |= EMatchFlagAsterikInLast;
        lenSearchText--;
        }

    // set asterik start
    if (!IsPhoneBookProcess(iCurrentProcessUid3) || 
        (aSearchText.Length() > 0 && aSearchText[0] == KLitStar))
        {
        flag |= EMatchFlagAsterikInStart;
        }

    if (lenItemString < lenSearchText)
        {
        return KErrNotFound;
        }

    if (IsPhoneBookProcess(iCurrentProcessUid3))
        {
        TInt i = 0;
        TInt j = 0;
        for (; i < lenItemString && j < lenSearchText; i++)
            {
            TChar ch(aItemString[i]);
            if (IsFindWordSeparator(ch))
                {
                continue;
                }
            
            if (MatchConsonentBased(ch, aSearchText[j]))
                {
                j++;
                }
            else
                {
                break;
                }
            }
        
        if (j == lenSearchText)
            return 0;
        }

    for (TInt i = 0; i < lenItemString - lenSearchText + 1; i++)
        {
        if (!(flag & EMatchFlagAsterikInStart))
            {
            if (0 != i && !IsFindWordSeparator(aItemString[i - 1]))
                {
                continue;
                }
            }

        TBool matched(ETrue);
        for (TInt j = 0; j < lenSearchText; j++)
            {
            if (!MatchConsonentBased(aItemString[i + j], aSearchText[j]))
                {
#ifdef _DEBUG
                RDebug::Printf("DBG: mismatch between %d %d", i + j, j);
#endif
                matched = EFalse;
                break;
                }
            }

        if (matched)
            {
#ifdef _DEBUG
            RDebug::Print(_L("DBG: comparing matched"));
#endif
            return i;
            }
        }

    return KErrNotFound;

#else
    // Convert aItemString to single jamo's.
    HBufC* itemString = HBufC::NewLC( aItemString.Length() * KMaxLengthDecomposedSyllable );
    DecomposeToPlainJamos( aItemString, itemString );

    HBufC* searchText = HBufC::NewLC( aSearchText.Length() * KMaxLengthDecomposedSyllable + 2 );
    searchText->Des().Append( KLitStar );

    // Convert aSearchText to single jamo's.
    DecomposeToPlainJamos( aSearchText, searchText );
    searchText->Des().Append( KLitStar );

    // Compare strings containing plain jamo's against others.
    for ( TInt i = 0; i < itemString->Length() && !result; i++ )
        {
        if ( 0 == i || IsFindWordSeparator(
                        static_cast<TChar>( itemString->Des()[ i - 1 ] ) ) )
            {
            if ( KErrNotFound != itemString->Mid( i ).MatchC( *searchText ) )
                {
                result = ETrue; // match found
                }
            }
        }

    CleanupStack::PopAndDestroy( searchText );
    CleanupStack::PopAndDestroy( itemString );

    return result;
#endif
    }

// ---------------------------------------------------------------------------
// Decomposes given string to plain jamos.
// ---------------------------------------------------------------------------
//
void CFindUtilKorean::DecomposeToPlainJamos( 
    const TDesC& aString,
    HBufC* aDecomposedString )
    {
    // Go thought all characters and decompose if needed.
    for ( TInt i = 0; i < aString.Length(); i++ )
        {
        // If character is 'hangul syllable', decompose it to single jamos.
        if ( IsHangulSyllable( aString[ i ] ) )
            {
            TBuf<KMaxLengthDecomposedSyllable> buf ( KNullDesC );
            Decompose( aString[ i ], buf );
            aDecomposedString->Des().Append( buf );
            }
        else if ( IsHangulCompatibilityJamo( aString[ i ] ) )
	        {
	        TUint16 jamo = conversionTableFromCompatibilityJamoToJamo[ aString[i] - KCBase ];
	        aDecomposedString->Des().Append( jamo );	
	        }
        // Otherwise append character directly to 'decomposed string'.
        else
            {
            aDecomposedString->Des().Append( aString[ i ] );
            }
        }
    }

void CFindUtilKorean::DecomposeChar( TChar aChar, TDes& aDecomposedString )
    {
    aDecomposedString.Zero();
    if ( IsHangulSyllable( aChar ) )
        {
        Decompose( aChar, aDecomposedString );
        }
    else if ( IsHangulCompatibilityJamo( aChar ) )
        {
        TUint16 jamo = conversionTableFromCompatibilityJamoToJamo[ (TInt)aChar - KCBase ];
        aDecomposedString.Append( jamo );    
        }
    // Otherwise append character directly to 'decomposed string'.
    else
        {
        aDecomposedString.Append( aChar );
        }    
    }

// ---------------------------------------------------------------------------
// Decomposes hangul syllables to single jamos.
// ---------------------------------------------------------------------------
//
void CFindUtilKorean::Decompose( TChar aChar, TDes& aDecomposedString )
    {
    // Calculate single jamo's.
    TInt index = static_cast<TInt> ( aChar ) - KSBase;
    TInt l = KLBase + index / KNCount;
    TInt v = KVBase + ( index % KNCount ) / KTCount;
    TInt t = KTBase + index % KTCount;
    
    // Append single jamo's to 'decomposed string'.
    aDecomposedString.Append( static_cast<TChar> ( l ) );
    aDecomposedString.Append( static_cast<TChar> ( v ) );
    if ( t != KTBase )
        {
        aDecomposedString.Append( static_cast<TChar> ( t ) );
        }
    }

// ---------------------------------------------------------------------------
// Checks that is given character hangul syllable or not.
// ---------------------------------------------------------------------------
//
TBool CFindUtilKorean::IsHangulSyllable( TChar aChar )
    {
    // Character is 'hangul syllable' 
    // if it's numeric value is between KSBase and KSBase + KSCount.
    TInt index = static_cast<TInt> ( aChar ) - KSBase;
    if ( index < 0 || index >= KSCount )
        {
        return EFalse;
        }
    return ETrue;
    }

// ---------------------------------------------------------------------------
// Checks that is given character word separator or not.
// ---------------------------------------------------------------------------
//
TBool CFindUtilKorean::IsFindWordSeparator( TChar aChar )
    {
    return aChar == KLitSpace || aChar == KLitHyphen || aChar == KLitTab;
    }


// ---------------------------------------------------------------------------
// Checks that is given character hangul syllable or not.
// ---------------------------------------------------------------------------
//
TBool CFindUtilKorean::IsHangulCompatibilityJamo( TChar aChar )
    {
    // Character is 'hangul compatibility jamo' 
    // if it's numeric value is between KCBase and KCBase + KCCount.
    TInt index = static_cast<TInt>( aChar ) - KCBase;
    if ( index < 0 || index >= KCCount )
        {
        return EFalse;
        }
    return ETrue;
    }
	
// ---------------------------------------------------------------------------
// It tests a matching.
// ---------------------------------------------------------------------------
//
TBool CFindUtilKorean::Match( const TDesC& aContactsField, const TDesC& aWord )
    {
    TBool retVal = EFalse;
    // Match does not occur if string where search is made,
    // does not contain any characters.
    if ( aContactsField.Length() )
        {
	    // In case that both of strings contain some characters,
	    // matching is made with function below.
#ifdef _DEBUG
        RDebug::Printf("DBG: Comparing from Match");
#endif
	    retVal = (IsFindMatch( aContactsField, aWord ) != KErrNotFound);
        }
	
	return retVal;
    }

// ---------------------------------------------------------------------------
// It tests a partial matching.
// ---------------------------------------------------------------------------
//
TBool CFindUtilKorean::MatchRefineL( 
    const TDesC& aItemString, 
    const TDesC& aSearchText )
    {
    // Match does not occur if string where search is made,
    // does not contain any characters.
    if ( aItemString.Length() == 0 )
        {
        return EFalse;
        }

    // Match occurs if string to be used in searching, 
    // does not contain any characters.
    if ( aSearchText.Length() == 0 )
        {
        return ETrue;
        }

    // In case that both of strings contain some characters,
    // matching is made with function below.
#ifdef _DEBUG
    RDebug::Printf("DBG: Comparing from MatchRefineL");
#endif
    
    return (IsFindMatch( aItemString, aSearchText ) != KErrNotFound);
    }

// -----------------------------------------------------------------------------
// CFindUtilKorean::MatchAdaptiveRefineL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//  
TBool CFindUtilKorean::MatchAdaptiveRefineL(const TDesC& aItemString,
        const TDesC& aSearchText, HBufC*& aNextChars)
    {
    if (aSearchText.Length() == 0)
        {
        TakeIntoNextCharsL(aNextChars, aItemString[0]);
        return ETrue;
        }
    else
        {
        const TInt lenItemString = aItemString.Length();
        const TInt lenSearchText = aSearchText.Length();

        if (lenItemString < lenSearchText)
            {
            return EFalse;
            }

#ifdef _DEBUG
        RDebug::Printf("DBG: Comparing from MatchAdaptiveRefineL");
#endif
        TInt idx = IsFindMatch(aItemString, aSearchText,
                EMatchFlagAsterikInLast);

        if (idx == KErrNotFound)
            {
            return EFalse;
            }

        TLex lexItemString(aItemString);
        if (IsPhoneBookProcess(iCurrentProcessUid3) && idx == 0)
            {
            // find out the position next to last matched string.
            // work through strings when it reaches length of search string,
            // while skipping spaces due to ingnoring space matching scheme.
            for (TInt compareCount = 0; compareCount < lenSearchText;)
                {
                if (!IsFindWordSeparator(lexItemString.Get()))
                    {
                    compareCount++;
                    }
                }
            
            if (lexItemString.Eos())
                return EFalse;

            // Skip spaces
            while (IsFindWordSeparator(lexItemString.Peek()))
                {
                lexItemString.Inc();
                }
            
            if (lexItemString.Eos())
                {
                return EFalse;
                }
            }
        else
            {
            lexItemString.Inc(idx + lenSearchText);
            }

        TChar next = lexItemString.Peek();
        if (next == 0)
            {
            // nothing to take
            }
        else
            {
            TakeIntoNextCharsL(aNextChars, next);
            }
        }
    
    return ETrue;
    }

void CFindUtilKorean::TakeIntoNextCharsL(HBufC*& aNextChars,
        TChar aCharToInsert)
    {
    // examine the characters to be inserted
    TBuf<3> jamo;
    if (IsHangulSyllable(aCharToInsert))
        {
        Decompose(aCharToInsert, jamo);
        }
    else if (IsHangulCompatibilityJamo(aCharToInsert))
        {
        TUint16 ljamo = 
                conversionTableFromCompatibilityJamoToJamo[(TInt)aCharToInsert - KCBase];
        jamo.Append(ljamo);
        }
    else
        {
        aCharToInsert.UpperCase();
        }

    TPtr nextChar(aNextChars->Des());
    TBool reAlloced(EFalse);

    // in case there is no character in the list
    if (nextChar.Length() == 0)
        {
        __ASSERT_ALWAYS(nextChar.MaxLength() > 2, User::Panic(_L("FINDUTIL"), __LINE__));
        
        // Hangul only
        if (jamo.Length() && ISLJamo(jamo[0]))
            {
            const TChar consonentToInsert =
                    conversionTableFromLJamoToCompatibilityJamo[jamo[0] - KLBase];
            
            InsertNextCharsL(aNextChars, reAlloced, consonentToInsert);

            // if Jamo only character, return...
            if (jamo.Length() == 1)
                {
                return;
                }
            }
        
        InsertNextCharsL(aNextChars, reAlloced, aCharToInsert);
        return;
        }

    TBool jamoInserted(EFalse);
    TInt length = nextChar.Length();
    const TBool isPB(IsPhoneBookProcess(iCurrentProcessUid3));
    
    for (TInt i = 0; i < length; i++)
        {
        const TChar ch = nextChar[i];
        // Hangul consonent check
        if (!jamoInserted && jamo.Length() && ISLJamo(jamo[0]))
            {
            const TChar consonentToInsert =
                    conversionTableFromLJamoToCompatibilityJamo[jamo[0] - KLBase];
            
            if (ch == consonentToInsert)
                {
                // Jamo only character finished
                if (jamo.Length() == 1)
                    {
                    return;
                    }

                jamoInserted = ETrue;
                }
            else if ((isPB && !IsCompatibilityJamo(ch)) || (ch > consonentToInsert))
                {
                InsertNextCharsL(aNextChars, reAlloced, consonentToInsert, i);
                // Jamo only character finished
                if (jamo.Length() == 1)
                    {
                    return;
                    }

                jamoInserted = ETrue;
                }
            else
                {
                // pass
                }
            }
        // Hangul or Latin
        else
            {
            if (ch == aCharToInsert)
                {
                return; // already exist
                }
            else if (isPB && IsCompatibilityJamo(ch))
                {
                // pass
                }
            else if (ch > aCharToInsert)
                {
                InsertNextCharsL(aNextChars, reAlloced, aCharToInsert, i);
                return; // finished
                }
            else
                {
                // pass
                }
            }
        
        if (reAlloced)
            {
            nextChar.Set(aNextChars->Des());
            length = nextChar.Length();
            }
        }
    
    InsertNextCharsL(aNextChars, reAlloced, aCharToInsert);
    }

void CFindUtilKorean::InsertNextCharsL(HBufC*& aNextChars, TBool& aReAlloced,
        const TChar& aChar, const TInt aIndex)
    {
    aReAlloced = EFalse;
    TPtr ptr(aNextChars->Des());
    const TInt len = ptr.Length();
    const TInt maxLen = ptr.MaxLength();

    if (KErrNotFound != ptr.Locate(aChar))
        {
        // Do not insert duplicate characters
        return;
        }

    if (len == maxLen)
        {
        aNextChars = aNextChars->ReAllocL(maxLen + KNextCharsGranuarity);
        ptr.Set(aNextChars->Des());
        aReAlloced = ETrue;
        
#ifdef _DEBUG
        RDebug::Printf("DBG: Next Character buffer created with %d",
                ptr.MaxLength());
#endif
        }

    if (aIndex == KErrNotFound)
        {
        ptr.Append(aChar);
        }
    else
        {
        TBuf<1> buf;
        buf.Append(aChar);
        ptr.Insert(aIndex, buf);
        }
    }

// ---------------------------------------------------------------------------
// It checks whether aWord is valid.
// ---------------------------------------------------------------------------
//
TBool CFindUtilKorean::IsWordValidForMatching(const TDesC& /*aWord*/)
    {
    return ETrue;
    }

TBool CFindUtilKorean::MatchConsonentBased(const TChar& aA, const TChar& aB)
    {
    TBuf<3> jamoItemString;
    TBuf<3> jamoSearchText;
    DecomposeChar(aA, jamoItemString);
    DecomposeChar(aB, jamoSearchText);
    const TInt lenJamoItemString = jamoItemString.Length();
    const TInt lenJamoSearchText = jamoSearchText.Length();

    // check consonent match for one character
    if (lenJamoSearchText == 1 && 
        ISLJamo(jamoItemString[0]) && ISLJamo(jamoSearchText[0]))
        {
        if (jamoItemString[0] == jamoSearchText[0])
            {
            return ETrue;
            }
        }
    else
        {
        TChar chItemString(aA);
        TChar chSearchText(aB);
        chItemString.UpperCase();
        chSearchText.UpperCase();
        if (chItemString == chSearchText)
            {
            return ETrue;
            }
        }
    return EFalse;
    }
// End of file
