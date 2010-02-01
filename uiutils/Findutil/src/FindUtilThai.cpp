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
* Description:         Thai Find Utilities implementation file.
*
*/









#include "FindUtilThai.h"
const TInt KLitTab('\t');
const TInt KLitSpace(' ');
const TInt KLitHyphen('-');
const TInt KLitLineFeed(8233);
const TInt KLitStar('*');
const TInt KMatchingBufferLength(256);

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

inline TBool IsFindMatch(const TDesC& aItemString, const TDesC& aSearchText)
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

}

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CFindUtilThai::CFindUtilThai
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CFindUtilThai::CFindUtilThai()
    {
    }

// Destructor
CFindUtilThai::~CFindUtilThai()
    {
    }

// -----------------------------------------------------------------------------
// CFindUtilThai::Match
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TBool CFindUtilThai::Match(const TDesC& aContactsField, const TDesC& aWord)
    {
    if (!aContactsField.Length())
        {
        return EFalse;
        }
    
    if (aContactsField.MatchC(aWord) != KErrNotFound)
        {
        return ETrue;
        }
    else if (aContactsField.MatchF(aWord) != KErrNotFound)
        {
        return ETrue;
        }
    return EFalse;
    }

// -----------------------------------------------------------------------------
// CFindUtilThai::MatchRefineL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TBool CFindUtilThai::MatchRefineL( const TDesC& aItemString, const TDesC& aSearchText)
    {
    if ( aItemString.Length() == 0 )
        {
        return EFalse;
        }

    if ( aSearchText.Length() == 0 )
        {
        return ETrue;
        }

    return IsFindMatch(aItemString, aSearchText);
    }

// -----------------------------------------------------------------------------
// CFindUtilThai::IsWordValidForMatching
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TBool CFindUtilThai::IsWordValidForMatching(const TDesC& /*aWord*/)
    {
    return ETrue;
    }


// ========================= FOR ADAPTIVE FIND ================================

/**
 * Update next characters if find pane state was changed.
 *
 * @since 5.0
 * @param aNextChars reference to the next characters for the adaptive search grid
 * @param aCh Criteria from the search field.    
 */
inline void UpdateNextCharsL( HBufC*& aNextChars, TChar aCh )
	{
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
            TRAP_IGNORE( UpdateNextCharsL( aNextChars, aItemString[i] ) );   	   		
            }
		}
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
 * 
 * @return @c ETrue if list box item text @c aItemText matches @c 
 *         aSearchText otherwise @c EFalse.
 */
inline TBool IsAdaptiveFindMatch( const TDesC& aItemString, 
	const TDesC& aSearchText, HBufC*& aNextChars )
	{	    	
	HBufC16* searchText = NULL;
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
    	
        searchText->Des().Append( KLitStar );
       
        TInt all_result = KErrNotFound;
        for( TInt i = 0; i < itemStringLength; i++ )
            {
            if ( i==0 || IsFindWordSeparator( aItemString[i-1] ) )
                {
                TInt result = aItemString.Mid(i).MatchF( searchText->Des() );
                
                if( result != KErrNotFound ) 
                    {
                    all_result = result;
                    if( i < (itemStringLength-searchTextLength) )                	   	       	   		
                        {
                        if( !(IsThaiSpecialCharacter( aItemString[i+searchTextLength])) )
                            {
                            TRAP_IGNORE( UpdateNextCharsL( aNextChars, aItemString[i+searchTextLength]) );
                            }            	   
                        }
                    }                                                                  	   	
                } // if (i==0 ..)        
      	    } // for	 
	    
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
// CFindUtilWestern::MatchAdaptiveRefineL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//  
TBool CFindUtilThai::MatchAdaptiveRefineL( const TDesC& aItemString, 
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
    return IsAdaptiveFindMatch( aItemString, aSearchText, aNextChars );		
	}
	
// ---------------------------------------------------------
// Match arithmetic for accurate search, special conversion 
// for aItemString is implemented with MFindStringConverter
// before the final match
// ---------------------------------------------------------
//
TBool CFindUtilThai::MatchRefineL( const TDesC& /*aItemString*/, const TDesC& /*aSearchText*/, 
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
    return new( ELeave ) CFindUtilThai();
    }

// end of file
