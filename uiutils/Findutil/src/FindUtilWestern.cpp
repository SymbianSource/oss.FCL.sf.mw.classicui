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
* Description:         Western Find Utilities implementation file.
*
*/









#include "FindUtilWestern.h"
#include <collate.h>
#include <PtiIndicDefs.h>
#include "FindUtilKorean.h"
#include <avkon.rsg>
#include <StringLoader.h>
const TInt KLitTab('\t');
const TInt KLitSpace(' ');
const TInt KLitHyphen('-');
const TInt KLitLineFeed(8233);
const TInt KLitStar('*');
const TInt KLitQuestion('?');

const TInt KMatchingBufferLength(256);
const TInt KAknStringBufferSize = 256;

namespace {

// ---------------------------------------------------------------------------
// IsFindWordSeparator
// ---------------------------------------------------------------------------
//
inline TBool IsFindWordSeparator(TChar aCh)
    {
    return aCh == KLitSpace || aCh == KLitHyphen || aCh == KLitTab || aCh == KLitLineFeed;
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

inline TInt MyFindC(const TDesC &aItemString, const TDesC &aSearchText)
    {
    TBuf<200> searchText;
    TBuf<200> itemString;
    searchText.Append(aSearchText);
    // The replacecharacters are to disable regexp matching provided
    // by MatchC().
	_LIT(KQuestion,"?");
	_LIT(KStar,"*");
    ReplaceCharacters(searchText, KQuestion, TChar('\t'));
    ReplaceCharacters(searchText, KStar, TChar('\r'));
    searchText.Append(KStar);
    if (aItemString.Length() < 200)
        itemString.Append(aItemString);
    else
        itemString.Append(aItemString.Left(200));
    ReplaceCharacters(itemString, KQuestion, TChar('\t'));
    ReplaceCharacters(itemString, KStar, TChar('\r'));


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
inline TBool IsFindMatchClassic(const TDesC& aItemString, const TDesC& aSearchText, TInt /*aInputLang = 0*/)
    {
    TPtrC itemptr = aItemString;
    TPtrC searchptr = aSearchText;

    TBool match = EFalse;
    
    for(;;) 
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
        TInt spacepos = itemptr.LocateF(TChar(' '));
        TInt minuspos = itemptr.LocateF(TChar('-'));
        TInt tabpos = itemptr.LocateF(TChar('\t'));
        if (spacepos != KErrNotFound)
            {
            itemptr.Set(itemptr.Mid(spacepos+1));
            }
        else if (minuspos != KErrNotFound)
            {
            itemptr.Set(itemptr.Mid(minuspos+1));
            }
        else if (tabpos != KErrNotFound)
            {
            itemptr.Set(itemptr.Mid(tabpos+1));
            }
        else
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

// ---------------------------------------------------------------------------
// IsFindMatch
// ---------------------------------------------------------------------------
//
inline TBool IsFindMatch(const TDesC& aItemString, const TDesC& aSearchText, TInt aInputLang = 0)
    {
    TBuf<200> searchText;
    TInt itemStringLength = aItemString.Length();
    
    if ( aSearchText.Length() < 200 )
        {
        searchText.Append( aSearchText );
        }
    else
        {
        searchText.Append( aSearchText.Left(199) );
        }
    
    // To disable the wildchar matching provided by MatchC
    if (aSearchText.Locate( KLitQuestion ) != KErrNotFound)
        {
        return IsFindMatchClassic(aItemString, aSearchText, aInputLang);
        }
    if (aSearchText.Locate( KLitStar ) != KErrNotFound)
        {
        return IsFindMatchClassic(aItemString, aSearchText, aInputLang);
        }

    searchText.Append( KLitStar );
        
    TInt result = KErrNone;
   
    for( TInt i = 0; i < itemStringLength; i++ )
        {
        if ( i==0 || IsFindWordSeparator( aItemString[i-1] ) )
            {
            
            if(aInputLang == ELangHindi
#ifdef RD_MARATHI
                || aInputLang == ELangMarathi
#endif

#ifdef RD_HINDI_PHONETIC_INPUT
                || aInputLang == KLangHindiPhonetic
#endif            
            )
            {
            TUint flag = ( TCollationMethod::EIgnoreNone | TCollationMethod::EFoldCase | TCollationMethod::EIgnoreCombining );
        	TCollationMethod m = *Mem::GetDefaultMatchingTable();
  			m.iFlags |= flag;
        	result = aItemString.Mid(i).MatchC( searchText, &m, 3);
            }
            else
            {
            	result = aItemString.Mid(i).MatchC( searchText );
            }
                        	
            if(result != KErrNotFound)
            	{
            		return ETrue;
            	}
            }
        }
        
    return EFalse;
	}	
}

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CFindUtilWestern::CFindUtilWestern
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CFindUtilWestern::CFindUtilWestern()
    {
    iRepository = NULL;
    iNotifyHandler = NULL;
    }

// Destructor
CFindUtilWestern::~CFindUtilWestern()
    {
    if ( iNotifyHandler )
        {
        iNotifyHandler->StopListening();
        delete iNotifyHandler;
        iNotifyHandler=NULL;
        }
    if(iRepository)
        {
        delete iRepository;
        iRepository = NULL;    
        }    	
    if ( iFindUtilKorean )
        {
    	delete iFindUtilKorean;
    	iFindUtilKorean = NULL;
        }
    if( iDigraphChars )       
        {
        delete iDigraphChars;
        }
    }


void CFindUtilWestern::OpenL()
	{
	CFindUtilBase::OpenL();
    
    if(!iRepository)
    	{
		iRepository = CRepository::NewL(KCRUidAknFep);
		iRepository->Get(KAknFepInputTxtLang, iInputLanguage);
	    }
	if(!iNotifyHandler)
	    {
		iNotifyHandler = CCenRepNotifyHandler::NewL( *this, 
                                              *iRepository,
                                              CCenRepNotifyHandler::EIntKey,
                                              KAknFepInputTxtLang );
		iNotifyHandler->StartListeningL();
	    }	
//TSW: LYEE-7Q2GRV  
	if(!iFindUtilKorean)
	    {
        iFindUtilKorean = CFindUtilKorean::NewL();
	    }
	}
	
void CFindUtilWestern::HandleNotifyInt( TUint32 aId, TInt aNewValue )
	{
	if(aId == KAknFepInputTxtLang)
	    iInputLanguage = aNewValue;
	}
	
// -----------------------------------------------------------------------------
// CFindUtilWestern::Match
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TBool CFindUtilWestern::Match(const TDesC& aContactsField, const TDesC& aWord)
    {
    if ( iFindUtilKorean->IsKoreanLanguage( aContactsField ) || iFindUtilKorean->IsKoreanLanguage( aWord ) )
        {
        return iFindUtilKorean->Match( aContactsField, aWord );	
        }
    else
    	{
    TInt numChar = 1;
    	if (!aContactsField.Length())
        	{
        	return EFalse;
        	}        
    	if((aWord.Length() > 1) && aWord[aWord.Length()-2] == 0x200B)
    		{
    		numChar = 2;
    		}    	
    	if ( IsFindMatch(aContactsField, aWord.Left(aWord.Length()-numChar), iInputLanguage) )
        	{
        	return ETrue;
        	}
  		return EFalse;
   		}
    }


// -----------------------------------------------------------------------------
// CFindUtilWestern::MatchRefineL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TBool CFindUtilWestern::MatchRefineL( const TDesC& aItemString, const TDesC& aSearchText )
    {
    if ( iFindUtilKorean->IsKoreanLanguage( aItemString ) || iFindUtilKorean->IsKoreanLanguage( aSearchText ) )
        {
        return iFindUtilKorean->MatchRefineL( aItemString, aSearchText );	
        }
    else
    {
    if ( aItemString.Length() == 0 )
        {
        return EFalse;
        }

    if ( aSearchText.Length() == 0 )
        {
        return ETrue;
        }
    return IsFindMatch( aItemString, aSearchText, iInputLanguage );
    	}
    }

// -----------------------------------------------------------------------------
// CFindUtilWestern::IsWordValidForMatching
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TBool CFindUtilWestern::IsWordValidForMatching(const TDesC& /*aWord*/)
    {
    return ETrue;
    }


// ========================= FOR ADAPTIVE FIND ================================

// -----------------------------------------------------------------------------
// For Vietnamese AS
// 
// -----------------------------------------------------------------------------
//
inline TChar ReplaceVietnameseChar( const TChar aCh )   
    {
    TChar Char = aCh.GetUpperCase();
    if ( (Char >= 0x00C0 && Char <= 0x00C3) || Char == 0x102  ||
         ((Char >= 0x1EA0 && Char <= 0x1EB6) && Char%2 == 0) )  
        {
        Char = 0x0041; // A
        return Char; 
        }        
    if ( (Char >= 0x00C8 && Char <= 0x00CA) || 
        ((Char >= 0x1EB8 && Char <= 0x1EC6) && Char%2 == 0) )
        {
        Char = 0x0045; // E
        return Char; 
        }               
    if ( Char == 0x00CC || Char == 0x00CD || Char == 0x0128 || 
         Char == 0x1EC8 || Char == 0x1ECA  )
        {
        Char = 0x0049; // I
        return Char; 
        }    
    if ( (Char >= 0x00D2 && Char <= 0x00D5 ) || Char == 0x1ECE || Char == 0x1ECC ||
        ((Char >= 0x1ED0 && Char <= 0x1ED8) && Char%2 == 0)) 
        {
        Char = 0x004F; // O
        return Char; 
        }            
    if ( Char == 0x1EDA || Char == 0x1EDC || Char == 0x1EDE || 
         Char == 0x1EE0 || Char == 0x1EE2  )
        {
        Char = 0x01A0; // O-horn
        return Char; 
        }          
    if ( Char == 0x00DA || Char == 0x00D9 || Char == 0x0168 || 
         Char == 0x1EE4 || Char == 0x1EE6  )
        {
        Char = 0x0055; // U
        return Char; 
        }         
     if ( (Char >= 0x1EE8 && Char <= 0x1EF0) && Char%2 == 0 )
        {
        Char = 0x01AF; // U-horn        
        return Char; 
        }         
     if ( ((Char >= 0x1EF2 && Char <= 0x1EF8) && Char%2 == 0) || Char == 0x00DD ) 
        {
        Char = 0x0059; // Y
        return Char; 
        }              
    return Char;
    } 
    
 /**
 * Checks current character is it special character from Vietnamese language . 
 *
 * @since 5.0
 * @return @c ETrue If it is accent from Vietnamese language, otherwise EFalse. 
 */	
inline TBool IsVietnameseSpecialCharacter( TChar aCh )
    {   
    if ( ( aCh >= 0x0300 && aCh <= 0x0303 ) ||       
        aCh == 0x0306 || aCh == 0x0309 || aCh == 0x0323 || aCh == 0x031B )
        {
        return ETrue;            
        }  
    return EFalse;
    }
       
/**
 * Update next characters if find pane state was changed.
 *
 * @since 5.0
 * @param aNextChars reference to the next characters for the adaptive search grid
 * @param aCh Criteria from the search field.    
 */
inline void UpdateNextCharsL( HBufC*& aNextChars, TChar aCh )
    {
        TChar ch_temp = aCh;          
    
    TLanguage lang = User::Language();  
    if ( lang == ELangVietnamese )
	   {
	   aCh = ReplaceVietnameseChar ( ch_temp );
	   }
    
    if( ( aNextChars->Locate(aCh.GetLowerCase() ) == KErrNotFound ) &&
        ( aNextChars->Locate(aCh.GetUpperCase() ) == KErrNotFound ) )
        {               
        if( aNextChars->Des().Length() == aNextChars->Des().MaxLength() )
            {
            aNextChars = aNextChars->ReAllocL( aNextChars->Des().MaxLength()+10 );
            TInt length1 = aNextChars->Des().Length();
            TInt maxlength1 = aNextChars->Des().MaxLength();
            }       
        aNextChars->Des().Append( aCh );            
        }
    }

// -----------------------------------------------------------------------------
// For Devanagari AS
// Checks if aCh denotes a consonant with nukta. 
// @return ETrue if aCh is a consonant with nukta EFalse otherwise.
// -----------------------------------------------------------------------------
//
inline TBool IsIndicCombinedChar( const TChar aCh )
    {   
    if ( aCh < 0x0900 || aCh > 0x0980 )
        {
        return EFalse;
        }
    else
        {
        return ( aCh == 0x0929 || aCh == 0x0931 || aCh == 0x0934 || 
                (aCh >= 0x0958 && aCh <= 0x095F) );
        }
    }

// -----------------------------------------------------------------------------
// For Devanagari AS
// Returns the correcponding character without nukta
// @param aCh - character to be stripped of nukta
// @return corresponding character with nukta
// -----------------------------------------------------------------------------
//
inline TChar RemoveIndicNukta( const TChar aCh )
    {
    switch (aCh)
        {
        case 0x0929 : return 0x0928; //vocallic 'nna' to 'na'
        case 0x0931 : return 0x0930; //vocallic 'rra' to 'ra'
        case 0x0934 : return 0x0933; //vocallic 'lllla' to 'lla'
        case 0x0958 : return 0x0915; //vocallic 'qa' to 'ka'
        case 0x0959 : return 0x0916; //vocallic 'khha' to 'kha'
        case 0x095A : return 0x0917; //vocallic 'ghha' to 'ga'
        case 0x095B : return 0x091C; //letter 'za' to 'ja'
        case 0x095C : return 0x0921; //vocallic 'dddha' to 'da'
        case 0x095D : return 0x0922; //vocallic 'rha' to 'ddha'
        case 0x095E : return 0x092B; //letter 'fa' to 'pha'
        case 0x095F : return 0x092F; //letter 'yya' to 'ya'        
        default : return aCh;
        }
    }

// -----------------------------------------------------------------------------
// For Devanagari AS
// Checks if the given character is a Indic consonant.
// @param aSearchChar - character to be checked.  
// @return ETrue if this is an independent character EFalse otherwise       
// -----------------------------------------------------------------------------
//  
inline TBool IsIndicConsonant( const TChar aSearchChar )
    {    
	if  (
	    ( aSearchChar >= 0x0915 && aSearchChar <= 0x0939 ) ||
	    ( aSearchChar >= 0x0958 && aSearchChar <= 0x0961 )
	    )
        {
        return ETrue;
        }
    else 
        {
        return EFalse;
        }
    }
    
// -----------------------------------------------------------------------------
// For Devanagari AS
// Checks if the given character is a Indic matra.
// @param aSearchChar - character to be checked.  
// @return ETrue if this is an matra EFalse otherwise  
// -----------------------------------------------------------------------------
//  
inline TBool IsIndicMatra( const TChar aSearchChar )
    {   
    if ( aSearchChar >= 0x093E && aSearchChar <= 0x094C )
        {
        return ETrue;
        }
    else 
        {
        return EFalse;
        }
    }
    
// -----------------------------------------------------------------------------
// For Devanagari AS
// Checks if the given character is a Devanagari independent character.
// @param aSearchChar - character to be checked.  
// @return ETrue if this is an independent character EFalse otherwise  
// -----------------------------------------------------------------------------
//
inline TBool IsIndicIndependentChar( const TChar aSearchChar )
    {    
	if (( aSearchChar >= 0x0905 && aSearchChar <= 0x0939 ) ||
	    ( aSearchChar >= 0x0958 && aSearchChar <= 0x0961 ))
        {
        return ETrue;
        }
    else 
        {
        return EFalse;
        }
    }    
    
// -----------------------------------------------------------------------------
// For Devanagari AS
// Checks if the passed string denotes one of the four special
// Devanagari ligatures - refer UI specs for the description of special ligatures
// @param aCharString - The string containing set of characters to be checked
// @return ETrue if a special ligature is found EFalse otherwise   
// -----------------------------------------------------------------------------
//  
inline TBool IsSpecialIndicLigature( const TDesC& aCharString )
    {
    TBool ret = EFalse;
    if( aCharString.Length() >= 3 )
        {      
        if( (((aCharString[0] == 0x915) && (aCharString[1] == 0x94D)&& (aCharString[2] == 0x937)) ||
             ((aCharString[0] == 0x91C) && (aCharString[1] == 0x94D)&& (aCharString[2] == 0x91E)) ||
             ((aCharString[0] == 0x936) && (aCharString[1] == 0x94D)&& (aCharString[2] == 0x930)) ||
             ((aCharString[0] == 0x924) && (aCharString[1] == 0x94D)&& (aCharString[2] == 0x930))) )
            {
            ret = ETrue;
            }
         }
    return ret;
    }    
   
// -----------------------------------------------------------------------------
// For Devanagari AS
// Counts the number of Indic syllables in the search string
// For the purpose of supporting mixed language entries, we count each
// non-Devanagari charcter as a single syllable. 
// Also replaces the place holder '-' with '*' for searching 
// @param aSearchText - The search string entered so far
// @param aSearchTextLength - Number of characters in string excluding '*'
// @return the number of Devanagari syllables in aCriteria   
// -----------------------------------------------------------------------------
//  
inline TInt IndicSyllableCount( HBufC* aSearchText, TInt& aSearchTextLength )
	{
	TInt syllableCount = 0;
	TPtr ptrSearchText = aSearchText->Des();
	TInt strLength = ptrSearchText.Length();
	for(TInt index=0 ; index < strLength ; index++)
		{
		if( (index) && ptrSearchText[index] == KLitHyphen && 
		        IsIndicIndependentChar(ptrSearchText[index-1]) )
			{
			syllableCount++;
			ptrSearchText[index] = KLitStar;
			--aSearchTextLength;
			}
		else if ( !IsIndicIndependentChar(ptrSearchText[index]) && ptrSearchText[index]!=0x094D )
			{
			//For any other non Indic-independent-character that was entered 
			//through adaptive grid, we consider it as a seperate syllable. 
			++syllableCount;
			}
		}
	return syllableCount;
	}    
	
// -----------------------------------------------------------------------------
// For Devanagari AS
// Checks if aCriteria[aCurrentIndex] is a fallback rendered character.
// @param aCriteria - string in which we need to check.
// @param aCurrentIndex - position in string of character to be checked
// @return ETrue if aCriteria is a rendered character EFalse otherwise.
// -----------------------------------------------------------------------------
//  
inline TBool IsFallbackRenderedCharacter( const TDesC& aCriteria, TInt aCurrentIndex )
    {    
    if ( aCriteria[aCurrentIndex] >= 0x0900 && aCriteria[aCurrentIndex] <= 0x0980)
        {
        // Check for invalid Nuktas:
        if ( aCriteria[aCurrentIndex] == 0x093C )
            {
            // A Nukta is valid only if placed after a consonant 
            if ( !IsIndicConsonant(aCriteria[(aCurrentIndex-1)]) )
                {
                return ETrue;
                }
            }
        // Check for invalid Matras: 
        else if ( IsIndicMatra(aCriteria[aCurrentIndex]) )
            {
            // These can only be placed after a consonant or a valid nukta
            TChar prevChar = aCriteria[(aCurrentIndex-1)];            
            if ( !(IsIndicConsonant(prevChar) || prevChar == 0x093C) )
                {
                return ETrue;
                }
            }
        // Check for invalid Modifiers:
        else if ( aCriteria[aCurrentIndex] >= 0x0901 && aCriteria[aCurrentIndex] <= 0x0903)
            {
            //These are valid only if placed after an independent vowel or a 
            //consonant or a valid nukta or a valid matra.
            TChar prevChar = aCriteria[(aCurrentIndex-1)];
            //if prev character is nukta or matra, it would have been already validated
            if ( !(IsIndicIndependentChar(prevChar) || prevChar == 0x093C 
                    || IsIndicMatra(prevChar) ) )
                {
                return ETrue;
                }
            }
        // Check for invalid Halant/Virama:
        else if ( aCriteria[aCurrentIndex] == 0x094D )
            {
            //This is valid only if placed immediately after a consonant or a valid nukta
            TChar prevChar = aCriteria[(aCurrentIndex-1)];
            //if prev character is nukta, it would have been already validated
            if ( !(IsIndicConsonant(prevChar) || prevChar == 0x093C) )
                {
                return ETrue;
                }
            }
        } //end of "if devanagari character range"    
    return EFalse;
    }
    
// -----------------------------------------------------------------------------
// For Devanagari AS
// Mark the end boundary of syllables in input string
// @param aCriteria - The search/input string entered so far
// @param aStart - The start boundary of syllable to be marked
// @return the end boundary of the syllable  
// -----------------------------------------------------------------------------
//  
inline TInt IndicSyllableEnd( TInt& aStart, const TDesC& aCriteria )
	{
	TInt maxLength = aCriteria.Length();
	TInt endMarker(-1);
	if(aStart >= (maxLength-1))
		{		
		aStart = endMarker = maxLength-1;
		}
	else 
		{			
		TInt nextCharIndex = aStart + 1 ;
		TChar startingChar = aCriteria[aStart];
		if ( IsIndicIndependentChar(startingChar) )
			{
			//Check if syllable contains a special ligature		
			if(  aStart < (maxLength-2) && IsSpecialIndicLigature(aCriteria.Mid(aStart, 3)) ) 
				{
				//Move nextCharIndex till after the 3rd symbol of special ligature.
				nextCharIndex+=2;
				}					
			//check for the next character that is a matra/halant/nukta/modifier
			//Currently this check only for Devanagari characters. If other Indic language support
			//is required, we will need to add to this list.
			while( (nextCharIndex<maxLength) && 
			      ( ( IsIndicMatra(aCriteria[nextCharIndex]) ) //matra
		          ||( aCriteria[nextCharIndex] == 0x094D ) //Devanagari halant
		          ||( aCriteria[nextCharIndex] == 0x093C ) //Devanagari nukta 
			      ||( aCriteria[nextCharIndex] >= 0x0901 && aCriteria[nextCharIndex] <= 0x0903 ))) //Devanagari modifier			      
			    {
				//check if this is a fallback rendered character. Increment index only if it isn't:
				if ( !IsFallbackRenderedCharacter(aCriteria, nextCharIndex) )
				    {
				    ++nextCharIndex;
				    }
				else
				    {
				    break;
				    }
				}
			}		
		//nextCharIndex should now be pointing to either the start of the next syllable
		//or a non-Devanagari-letter. 
		//End marker of current syllable should be placed just before the nextCharIndex
		endMarker = nextCharIndex-1;		
		}		
	return endMarker;			
	}

// -----------------------------------------------------------------------------
// For Devanagari AS
// Parses through each Devanagari-syllable in the input string.
// It will stop when we have gone through aInputSyllableCount number of syllables. 
// @param aCriteria - The search string entered so far
// @param aStart - The start boundary of the last parsed syllable 
// @param aEnd - The end boundary of the last parsed syllable  
// -----------------------------------------------------------------------------
//  
inline void IndicSyllableBoundary( TInt& aStart, TInt& aEnd, TInt aInputSyllableCount, 
    const TDesC &aCriteria )
	{
	TInt boundaryCount = 0;
	TInt tStart = aStart = 0;
	while( boundaryCount != aInputSyllableCount )
		{
		aEnd = IndicSyllableEnd(tStart, aCriteria);	
		boundaryCount++;
		aStart = tStart;
		tStart = aEnd+1;	
		}
	}

// -----------------------------------------------------------------------------
// For Devanagari AS
// Checks if aItemString contains atleast one Indic letter
// @param aItemString - string to be checked
// @return ETrue if aItemString contains Devanagari letter EFalse otherwise.
// -----------------------------------------------------------------------------
//  
inline TBool IsIndicWord( const TDesC& aItemString )
	{
	TInt strLength = aItemString.Length();
	for ( TInt index = 0; index < strLength; ++index )
		{	
		if ( (aItemString[index] >= 0x900) && (aItemString[index] <= 0x980) )
			return ETrue;
		}
	return EFalse;
	}

// -----------------------------------------------------------------------------
// For Devanagari AS
// Checks if the last character from aNextChars can be displayed on 
// the adaptive search grid or not. For now, this filters out the Devanagari 
// vowels and other special symbol which are represented by the placeholder '-'.
// @param aNextChars list of characters to be displayed on adaptive search grid
// @return ETrue last character is valid for AS Grid, else EFalse.  
// -----------------------------------------------------------------------------
//  
inline TBool IsValidNextChars( const TDesC &aNextChars )
	{
	TBool ret = ETrue;
	if(aNextChars.Length()>0)
		{
		TChar ch = aNextChars[aNextChars.Length()-1];
		if( (ch >= 0x0901 && ch <= 0x0903) || (ch >= 0x093C && ch <= 0x094D) )
			{
			ret = EFalse;
			}	   
        }
	return ret;
	}


// -----------------------------------------------------------------------------
// For Devanagari AS
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//  
inline void UpdateNextCharsL( HBufC*& aNextChars, const TDesC& aItemString )
	{
	TChar searchChar = aItemString[0];
    //Check if this is an Indic special ligature
    if ( IsIndicConsonant(searchChar) && aItemString.Length() > 2
            && IsSpecialIndicLigature(aItemString) 
            && KErrNotFound == (*aNextChars).Find(aItemString.Mid(0,3)) )
        {
        //Check if we have enough space for 3 more characters
        if( aNextChars->Des().Length() >= aNextChars->Des().MaxLength()-3 )
            {
            aNextChars = aNextChars->ReAllocL( aNextChars->Des().MaxLength()+10 );
            }       
        aNextChars->Des().Append( aItemString.Mid(0,3) );        
        }
    else
        {
        //check if this is an Indic combined Char
        if ( IsIndicCombinedChar(searchChar) )
            {
            searchChar = RemoveIndicNukta( searchChar );
            }
        //Now update the nextChars string
        TInt strLength = aNextChars->Length();
        for ( TInt i(0); i < strLength ; ++i )
            {
            if ( IsSpecialIndicLigature( (*aNextChars).Mid( i ) ) )
                {
                //As aItemString is not a special ligature (checked above)
                //we can move directly to the 3rd character from here
                i+=2;
                }
            else if ( searchChar.GetUpperCase() == (*aNextChars)[i] ||
                        searchChar.GetLowerCase() == (*aNextChars)[i] )
                {
                //already exists - do nothing
                return;
                }
            //else continue the loop
            }
        //So this character is not yet in the list of nextChars.
        if ( aNextChars->Des().Length() == aNextChars->Des().MaxLength() )
            {
            aNextChars = aNextChars->ReAllocL( aNextChars->Des().MaxLength()+10 );
            }       
        aNextChars->Des().Append( searchChar );   
        }
   	}

/**
 * Update next chars from the list box item text, when search field is empty.
 * This need to be done for update next characters for adaptive grid
 * works faster then calling IsAdaptiveFindMatch().   
 *
 * @since 5.0
 * @param aNextChars reference to the next characters for the adaptive search grid
 * @param aItemString List box item text.
 */
 
inline void UpdateNextCharsFromString( HBufC*& aNextChars, const TDesC& aItemString )
	{   
	 TInt itemStringLength = aItemString.Length();
	 
	 for( TInt i = 0; i < itemStringLength; i++ )
        {
        if ( i == 0 || IsFindWordSeparator( aItemString[i-1] ) )
            {  
            //If this is an Indic letter 
            if ( aItemString[i] >= 0x0900 && aItemString[i] <= 0x0980 )
                {
                TRAP_IGNORE( UpdateNextCharsL( aNextChars, aItemString.Mid(i) ) );
                }
            else  if (!(IsVietnameseSpecialCharacter( aItemString[i])))
                {
                TRAP_IGNORE( UpdateNextCharsL( aNextChars, aItemString[i] ) );
                }
            }
		}
	}
	
inline TBool IsAdaptiveFindMatchClassic( const TDesC& aItemString, const TDesC& aSearchText )
    {
    TPtrC itemptr = aItemString;
    TPtrC searchptr = aSearchText;

    TBool match = EFalse;
    
    for(;;) 
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
        TInt spacepos = itemptr.LocateF(TChar(' '));
        TInt minuspos = itemptr.LocateF(TChar('-'));
        TInt tabpos = itemptr.LocateF(TChar('\t'));
        if (spacepos != KErrNotFound)
            {
            itemptr.Set(itemptr.Mid(spacepos+1));
            }
        else if (minuspos != KErrNotFound)
            {
            itemptr.Set(itemptr.Mid(minuspos+1));
            }
        else if (tabpos != KErrNotFound)
            {
            itemptr.Set(itemptr.Mid(tabpos+1));
            }
        else
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

/**
 * Checks the current character for special character from Thai language . 
 *
 * @since 5.0
 * @return @c ETrue If tone mark or diatric from Thai language otherwise EFalse. 
 */	
inline TBool IsThaiSpecialCharacter( TChar aCh )
    {    
    if( ( aCh > 0xE46 && aCh < 0xE4F ) ||  aCh == 0xE3A )
		{
		return ETrue;
		}       
	return EFalse;
    }

/**
 * Checks if @c aItemText matches @c aSearchText in the sense described in
 * S60.  Calls UpdateNextCharsL() if findutil is not supported.
 *
 * @since 5.0
 * @param aItemText list box item text.
 * @param aSearchText search text.
 * @param aNextChars reference to the next characters for the adaptive search grid
 * @param aDigraphs digraphs and trigraph text.
 * 
 * @return @c ETrue if list box item text matches aSearchText EFalse otherwise.
 */
inline TBool IsAdaptiveFindMatch( const TDesC& aItemString, 
	const TDesC& aSearchText, HBufC*& aNextChars, TInt /*aInputLang*/, const TDesC& aDigraphs )
	{	    	
	HBufC16* searchText = NULL;
	TRAPD( error, searchText = HBufC16::NewL( KMatchingBufferLength ) );
	TBool wildchar = EFalse;
	if ( error == KErrNone )
	    {
	    TInt itemStringLength = aItemString.Length();
        TInt searchTextLength = aSearchText.Length();    
        
        if ( searchTextLength < KMatchingBufferLength )
        	{
        	searchText->Des().Append( aSearchText );
        	}
        else
        	{
        	searchText->Des().Append( aSearchText.Left(KMatchingBufferLength-1) );
        	}  
        	 
         // To disable the wildchar matching provided by MatchC
        if ( aSearchText.Locate( KLitQuestion ) != KErrNotFound || 
             aSearchText.Locate( KLitStar ) != KErrNotFound )
            {            
            wildchar = IsAdaptiveFindMatchClassic( aItemString, aSearchText );
            if ( wildchar == EFalse )
                {
                delete searchText;
                return wildchar;
                }
            else 
                {  
                TInt val;      
                searchText->Des().Append( KLitStar );
                for( TInt i = 0; i < itemStringLength; i++ )
                    {
                    if ( i == 0 || IsFindWordSeparator( aItemString[i-1] ) )
                        {
                        val = MyFindC(  aItemString, aSearchText );                    
                        if( (val == i) && (i < (itemStringLength-searchTextLength))) 
                            {
                            if( !(IsThaiSpecialCharacter(aItemString[i+searchTextLength])) && !(IsVietnameseSpecialCharacter( aItemString[i+searchTextLength]) ))
                                {
                                TRAP_IGNORE( UpdateNextCharsL( aNextChars, aItemString[i+searchTextLength]) );   
                                }                                
                            }
                        }         
              	    } // for
              	delete searchText;
                return wildchar;	 
                }
            }
      	     	
        searchText->Des().Append( KLitStar );
        searchText->Des().UpperCase();

        TBool isCommonChars = EFalse;
        TInt all_result = KErrNotFound;
        
        TLanguage lang = User::Language();
        
        for( TInt i = 0; i < itemStringLength; i++ )
            {
            if ( i == 0 || IsFindWordSeparator( aItemString[i-1] ) )
                {
                TInt result = KErrNotFound;
                //Some vowels of Thai can not be searched with MatchC(). 
                if( aDigraphs.Length() != 0 || lang == ELangThai )
                    {
                    result = aItemString.Mid(i).Match( searchText->Des() );
                    }
                else
                    {
                    result = aItemString.Mid(i).MatchC( searchText->Des() );
                    }
                
                if( result != KErrNotFound ) 
                    {
                    all_result = result;
                    if( i < (itemStringLength-searchTextLength) )                	   	       	   		
                        {
                        if( !(IsThaiSpecialCharacter( aItemString[i+searchTextLength])) && !(IsVietnameseSpecialCharacter( aItemString[i+searchTextLength]) ))
                            {
                            TRAP_IGNORE( UpdateNextCharsL( aNextChars, aItemString[i+searchTextLength]) );

                            if ( aDigraphs.Length() != 0 )
                                {
                                TBuf<2> digraph;
                                digraph.Append( aItemString[i+searchTextLength-1] );
                                digraph.Append( aItemString[i+searchTextLength] );

                                if( searchTextLength == 1 )
                                    {
                                    if( aDigraphs.Find( digraph ) == KErrNotFound )
                                        {
                                        isCommonChars = ETrue;
                                        }
                                    }
                                else
                                    {
                                    TBuf<3> trigraph;
                                    trigraph.Append( aItemString.Mid(i+searchTextLength-2,3) );
                                    if( digraph[0] == KLitSpace 
                                        || ( aDigraphs.Find( digraph ) == KErrNotFound
                                        && aDigraphs.Find( trigraph ) == KErrNotFound ) )
                                        {
                                        isCommonChars = ETrue;
                                        }
                                    }
                                }
                            }            	   
                        }
                    else
                        {
                        isCommonChars = ETrue;
                        }
                    }                                                                  	   	
                } // if (i==0 ..)  
      	    } // for	 
        
        if(aDigraphs.Length() != 0 && !isCommonChars )   
            {
            all_result = KErrNotFound;
            }
	    
  	    if( all_result != KErrNotFound )
            {
            delete searchText;
            return ETrue;
           	}    
        else 
            {
            delete searchText;
            return EFalse;
            }
        	            		
         } // if (error == KErrNone)   
    delete searchText;                 
    return EFalse;
	}

// -----------------------------------------------------------------------------
// For Devanagari AS
// Checks if @c aItemText matches @c aSearchText.
// @param aItemText list box item text.
// @param aSearchText search text.
// @param aNextChars reference to the next characters for the adaptive search grid
// @return @c ETrue if list box item text matches EFalse otherwise.
// -----------------------------------------------------------------------------
//  
inline TBool IsIndicAdaptiveFindMatch( const TDesC& aItemString, 
	const TDesC& aSearchText, HBufC*& aNextChars, TInt /*aInputLang*/ )
	{	    	
	HBufC16* searchText(NULL);
	TRAPD( error, searchText = HBufC16::NewL( KMatchingBufferLength ) );
	if ( error == KErrNone )
	    {
	    TInt itemStringLength = aItemString.Length();
        TInt searchTextLength = aSearchText.Length();    
        
        if ( searchTextLength < KMatchingBufferLength )
        	{
        	searchText->Des().Append( aSearchText );
        	}
        else
        	{
        	searchText->Des().Append( aSearchText.Left(KMatchingBufferLength-1) );
        	}    
    	
    	TInt indicSyllableCount = -1;
        if( aSearchText.Length()>0 )
    		{
    		//This will replace all placeholder '-' symbols with '*'
     		indicSyllableCount = IndicSyllableCount( searchText, searchTextLength );
    		}
    	    	
    	//Append '*' to the end if not already present.
        if ( (*searchText)[searchText->Length() - 1] != KLitStar)
    		{
    		searchText->Des().Append( KLitStar );
    		}   
    	
    	TInt result = KErrNotFound;
        
        //check if the search string is found in the item string
        for( TInt index = 0; index < itemStringLength; index++ )
            {
            if ( index==0 || IsFindWordSeparator( aItemString[index-1] ) )
                {
                TUint flag = ( TCollationMethod::EFoldCase | TCollationMethod::EIgnoreNone | TCollationMethod::EIgnoreCombining);//TCollationMethod::EIgnoreNone |
        		TCollationMethod collationMethod = *Mem::GetDefaultMatchingTable();
        		collationMethod.iFlags |= flag;
            
           		result = aItemString.Mid(index).MatchC( (*searchText), &collationMethod );
                
                if( result != KErrNotFound ) 
                    {
                    if( index <= (itemStringLength-searchTextLength) )
        	   			{
        	   			//search for the last character in the string
        	   			//We use a TBuf instead of TChar since a special ligature is 
        	   			//represented by 3 characters. Last char would be the '*' wildchar.
	        	   		TBuf<4> lastChar;
	        	   		TInt modifiedStrLength = searchText->Length();
	        	   		if( (*searchText)[modifiedStrLength-1] == KLitStar )
	        	   			{
	        	   			//is this a special ligature?
	        	   			if ( modifiedStrLength > 3 &&
	        	   			        IsSpecialIndicLigature( (*searchText).Mid(modifiedStrLength-4) ) )
	        	   			    {
	        	   			    lastChar = (*searchText).Mid(modifiedStrLength-4);
	        	   			    }
	        	   			else
	        	   			    {
	        	   			    lastChar = (*searchText).Mid(modifiedStrLength-2);
	        	   			    }
	        	   			}
	        	   		else
	        	   			{
	        	   			//No wildchar here
	        	   			lastChar = (*searchText).Mid(modifiedStrLength-1);
	        	   			}
	        	   		
	        	   		lastChar.UpperCase(); //For latin characters as adaptive grid is always in upper case
        	   			TInt charPos = result; //aItemString.Mid(index).MatchC( searchText->Des(), &collationMethod );
        	   			//if found position is not within the substring to be searched, return EFalse.
                        if( charPos == KErrNotFound)
                            {
                            delete searchText;
                            return EFalse;
                            }
                        
        	   			TInt tempPos = charPos;
	        	   		
	        	   		TInt startCount = -1 , endCount = -1;
	        	   		
    	   				//TInt tempIndex(0);
    	   				//Get the position of the next syllable to be checked
    	   				IndicSyllableBoundary(startCount, endCount, indicSyllableCount, aItemString.Mid(index));
    	   				tempPos = aItemString.Mid(index+startCount).MatchC( lastChar, &collationMethod ); 
    	   				
    	   				if (
    	   				//if found position is not within the next syllable to be searched, 
    	   				//return EFalse.
    	   				    ( tempPos != 0 )  
    	   				//Also check if character to be searched is a single unicode while
    	   				//the match is at the start of a special ligature
    	   				   	|| ( !IsSpecialIndicLigature( lastChar ) && 
    	   				            IsSpecialIndicLigature( aItemString.Mid(index+startCount) ) )
    	   				    )
    	   				    {
    	   				    delete searchText;
    	   				    return EFalse;
    	   				    }
	        	   		
	        	   		//else, continue - find the next characters to be displayed on the grid	
	        	   		tempPos = index + endCount + 1;
	        	   		
	        	   		do	{
	        	   		    if(charPos!=KErrNotFound && (tempPos) < itemStringLength )
        	   					{
        	   						TRAP_IGNORE( UpdateNextCharsL( aNextChars, aItemString.Mid(tempPos) ) );
        	   					}
        	   				
        	   				//Is the found next character a consonent/independent-vowel/non-Indic character?
        	   				if ( IsValidNextChars( *aNextChars ) )
        	   					{
        	   					//found a valid character for displaying on the grid - return from here
        	   					delete searchText;
            					return ETrue;
        	   					}
        	   				else //we found an invalid valid character - keep searching
        	   					{
        	   					TPtr ptr = aNextChars->Des();
        	   					ptr.Delete(aNextChars->Length()-1,1);
        	   					//Is this a fallback rendered character?
        	   					if ( IsFallbackRenderedCharacter(aItemString, tempPos) )
        	   					    {
        	   					    //Keep the entry but don't show any more characters from this word
        	   					    delete searchText;
        	   					    return ETrue;
        	   					    }
        	   					}
        	   				}
        	   			//keep looping till we find a valid nextChar or we reach the end of the string
        	   			while(tempPos < itemStringLength ); 
        	   			
        	   			}
        	   			
        	   		} // if( result != KErrNotFound )                                                                  	   	
                } // if (index==0 ..)        
      	    } // for loop	 
	    
  	    if( result != KErrNotFound )
            {
            delete searchText;
            return ETrue;
           	}    
        else 
            {
            delete searchText;
            return EFalse;
            }
        	            		
         } // if (error == KErrNone)   
    delete searchText;                 
    return EFalse;
	}
	
// -----------------------------------------------------------------------------
// CFindUtilWestern::MatchAdaptiveRefineL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//  
TBool CFindUtilWestern::MatchAdaptiveRefineL( const TDesC& aItemString, 
	const TDesC& aSearchText, HBufC*& aNextChars )
	{
    if ( aItemString.Length() == 0 )
        {
        return EFalse;
        }
    if ( aSearchText.Length() == 0 )
        {        
        UpdateNextCharsFromString( aNextChars, aItemString );
        return ETrue;
        }
        
    if( iDigraphChars == NULL )
        {
        iDigraphChars = StringLoader::LoadL( R_QTN_ADS_DIGRAPH );
        TPtr digraph = iDigraphChars->Des();
        digraph.UpperCase();
        }
        
    TBuf<KAknStringBufferSize> itemString(aItemString);
    itemString.UpperCase();

    //AS does not show tone marks and diacritics when language is Thai.
    TLanguage lang = User::Language();  
    if ( lang == ELangThai )
        {
        for(TInt i=0; i < itemString.Length(); i++)
            {
            if(IsThaiSpecialCharacter( itemString[i] ))
                {
                itemString.Delete(i,1);
                }
            }
        }

    if ( IsIndicWord(aItemString) )
    	{
    	// itemString contains Devanagari letters
    	return IsIndicAdaptiveFindMatch( itemString, aSearchText, aNextChars, iInputLanguage );		
    	}
    else 
    	{
    	return IsAdaptiveFindMatch( itemString, aSearchText, aNextChars, iInputLanguage, iDigraphChars->Des() );				
    	}    
	}
	
// ---------------------------------------------------------
// Match arithmetic for accurate search, special conversion 
// for aItemString is implemented with MFindStringConverter
// before the final match
// ---------------------------------------------------------
//
TBool CFindUtilWestern::MatchRefineL( const TDesC& /*aItemString*/, const TDesC& /*aSearchText*/, 
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
// Factory function at first ordinal
EXPORT_C MFindUtil* FindUtilFactoryFunctionL()
    {
    return new( ELeave ) CFindUtilWestern();
    }

// end of file
