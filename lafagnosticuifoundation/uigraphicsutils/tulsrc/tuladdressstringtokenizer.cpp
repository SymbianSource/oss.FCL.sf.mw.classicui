// Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//


 
// INCLUDE FILES
#include <e32svr.h>
#include <tuladdressstringtokenizer.h>
#include <tulpanics.h>
#include "languagespecificnumberconverter.h"

// DEFINE

const TInt KFindItemMaxNumbers  = 48; // Maximum phone number supported in Contacts
const TInt KFindItemMinNumbers  = 3;
const TInt KDotsInIpAddress     = 3;
const TInt KNumbersInIpAddress  = 3;

const TInt KCharLinefeed = 0x000A;
const TInt KCharFormfeed = 0x000C;
const TInt KCharCarriageReturn = 0x000D;
const TInt KCharLineSeparator = 0x2028;
const TInt KCharParagraphSeparator = 0x2029;

// Valid characters for different search cases
_LIT( KPhoneNumberChars, "1234567890*#-./");
_LIT( KEmailChars, "!#$?%&*+-/");
_LIT( KEmailHostChars, "abcdefghijklmnopqrstuvwxyz1234567890._-");
_LIT( KUrlChars, "%/-~?=:&,#+|");

// generic URI scheme checking 
_LIT( KURISchemeStartCharacters, "abcdefghijklmnopqrstuvwxyz" );
_LIT( KURISchemeBodyCharacters, "abcdefghijklmnopqrstuvwxyz1234567890+-.");
_LIT( KURISchemeTerminator, ":");
_LIT( KURICharacters, "abcdefghijklmnopqrstuvwxyz1234567890?/;:@&=+$,%-_.!~*'()#|");

// Url Address beginnings (to support deprecated search cases)
_LIT( KHttpUrlAddress, "http://");
_LIT( KRtspUrlAddress, "rtsp://");
_LIT( KHttpsUrlAddress, "https://");

// Non-schematic URL address beginnings
_LIT( KWwwUrlAddress, "www.");
_LIT( KWapUrlAddress, "wap.");

// IP address pattern to match
_LIT( KIPAddress, "*.*.*.*");

// Panic
_LIT( KFindItemPanic, "ETUL-Panic");

GLDEF_C void Panic(TTulPanic aPanic)
	{
    User::Panic(KFindItemPanic, aPanic);
	}


// ================= MEMBER FUNCTIONS =======================

/**
C++ default constructor.
*/
CTulAddressStringTokenizer::CTulAddressStringTokenizer()
    {
	// C++ default constructor must NOT contain any code, that might leave.
    }

/**
Symbian OS constructor
@param aText  Text that will be parsed
@param aSearchCases   Identifies what items are we looking for:
                          EFindItemSearchPhoneNumberBin
                          EFindItemSearchMailAddressBin
                          EFindItemSearchURLBin
                          EFindItemSearchScheme
                      Any combination of these flags can be given
                      as a bit mask.
@param aMinNumbers    Minimum count of numbers in a string when 
                      the string is considered as a phone number.
*/
void CTulAddressStringTokenizer::ConstructL(const TDesC& aText, TInt aSearchCases, TInt aMinNumbers)
    {
    iMinNumbers = aMinNumbers;
    HBufC* buf = NULL;
	TLanguage language = User::Language();

    if (language == ELangArabic || language == ELangHebrew || language == ELangUrdu || 
    	language == ELangFarsi || language == ELangHindi)
		{
		buf = aText.AllocLC();
        TPtr ptr = buf->Des();
        LanguageSpecificNumberConverter::ConvertToWesternNumbers( ptr );
		PerformSearchL( *buf, aSearchCases );
		}
	else
		PerformSearchL( aText, aSearchCases );

	if(buf)
		CleanupStack::PopAndDestroy(buf);
	}

/**
Performs the search. Uses search algorithms SearchGenericUriL(), SearchMailAddressL(), 
SearchUrlL() and SearchPhoneNumberL().
*/
void CTulAddressStringTokenizer::PerformSearchL(const TDesC& aText , TInt aSearchCases)
	{
	ASSERT(!iFoundItems);
	iFoundItems = new (ELeave) CArrayFixFlat<SFoundItem>(2);

    TBool somethingSearched = EFalse;

    // first detect binary mask cases
    if ( (aSearchCases & EFindItemSearchScheme) == EFindItemSearchScheme)
        {
        SearchGenericUriL( aText );
        somethingSearched = ETrue;
        }

    // Prioritize mail address found before URL search. Address name@123.123.123.123 
    // would otherwise be detected as IP number.
    if ( (aSearchCases & EFindItemSearchMailAddressBin) == EFindItemSearchMailAddressBin)
        {
        SearchMailAddressL( aText );
        somethingSearched = ETrue;
        }

    if ( (aSearchCases & EFindItemSearchURLBin) == EFindItemSearchURLBin)
        {
        SearchUrlL( aText, ETrue );
        somethingSearched = ETrue;
        }

    // Search phone numbers last as all others can contain number sequences
    if ( (aSearchCases & EFindItemSearchPhoneNumberBin) == EFindItemSearchPhoneNumberBin)
        {
        SearchPhoneNumberL( aText );
        somethingSearched = ETrue;
        }
    
    // if no binary cases found
	if ( !somethingSearched )
        {
		__ASSERT_DEBUG( 1, Panic(ETulPanicInvalidTokenizerSearchCase) );
		}
	}

/**
Two-phase constructor method that is used to create a new instance 
of the CTulAddressStringTokenizer class. This instance can then be queried for
the items defined by the second parameter. The actual search is 
executed during construction.

@param aText will be parsed.
@param aSearchCases identifies what items we are looking for: 
						EFindItemSearchPhoneNumberBin
						EFindItemSearchMailAddressBin
						EFindItemSearchURLBin
						EFindItemSearchScheme
Any combination of these flags can be given as a bit mask.
@return a pointer to a new instance of CTulAddressStringTokenizer class.

@panic ETulPanicInvalidTokenizerSearchCase in debug build if there is no valid search case.
@panic ETulPanicDescriptorLength in debug build if item's position 
and/or length is out of the document's range.
@leave KErrNone, if successful; otherwise one of the other system-wide error codes.
*/
EXPORT_C CTulAddressStringTokenizer* CTulAddressStringTokenizer::NewL(const TDesC& aText, TInt aSearchCases)
    {
    CTulAddressStringTokenizer* self = new (ELeave) CTulAddressStringTokenizer; 
    CleanupStack::PushL(self);
    self->ConstructL(aText, aSearchCases, KFindItemMinNumbers);
    CleanupStack::Pop();
    return self;
    }

/**
Two-phase constructor method that is used to create a new instance
of the CTulAddressStringTokenizer class. This instance can then be queried for
the items defined by the second parameter. The actual search is 
executed during construction.

@param aText will be parsed.
@param aSearchCases identifies what items we are looking for: 
						EFindItemSearchPhoneNumberBin
						EFindItemSearchMailAddressBin
						EFindItemSearchURLBin
						EFindItemSearchScheme
Any combination of these flags can be given as a bit mask.
@param aMinNumbers defines a minimum count of numbers in a phone 
number string, during a phone number  
search.
@return a pointer to an new instance of CTulAddressStringTokenizer class.

@panic ETulPanicInvalidTokenizerSearchCase in debug build if there is no valid search case.
@panic ETulPanicDescriptorLength in debug build if item's position 
and/or length is out of the document's range.
@leave KErrNone, if successful; otherwise one of the other system-wide error codes.
*/
EXPORT_C CTulAddressStringTokenizer* CTulAddressStringTokenizer::NewL(const TDesC& aText, TInt aSearchCases,
    TInt aMinNumbers )
    {
    CTulAddressStringTokenizer* self = new (ELeave) CTulAddressStringTokenizer;   
    CleanupStack::PushL( self );
    self->ConstructL( aText, aSearchCases, aMinNumbers );
    CleanupStack::Pop( );
    return self;
    }

    
/**
Destructor.
*/
EXPORT_C CTulAddressStringTokenizer::~CTulAddressStringTokenizer()
    {
    delete iFoundItems;
	}

// API methods for using engine separately from FindItemUI

/**
Executes a new search with the already created CTulAddressStringTokenizer 
instance. The position in the found items array is reset to the 
beginning of the array.

@param aText will be parsed.
@param aSearchCases identifies what items are we looking for: 
						EFindItemSearchPhoneNumberBin
						EFindItemSearchMailAddressBin
						EFindItemSearchURLBin
						EFindItemSearchScheme
Any combination of these flags can be given as a bit mask.
@return number of found items.

@panic ETulPanicInvalidTokenizerSearchCase in debug build if there is no valid search case.
@panic ETulPanicDescriptorLength in debug build if item's position 
and/or length is out of the document's range.
@leave one of the Symbian error codes.
*/
EXPORT_C TInt CTulAddressStringTokenizer::DoNewSearchL(const TDesC& aText, TInt aSearchCases)
    {
    return DoNewSearchL( aText, aSearchCases, KFindItemMinNumbers );
    }

// API methods for using engine separately from FindItemUI

/**
Executes a new search with the already created CTulAddressStringTokenizer 
instance. The position in the found items array is reset to the 
beginning of the array.

@param aText will be parsed.
@param aSearchCases identifies what items are we looking for: 
						EFindItemSearchPhoneNumberBin
						EFindItemSearchMailAddressBin
						EFindItemSearchURLBin
						EFindItemSearchScheme
Any combination of these flags can be given as a bit mask.
@param aMinNumbers defines a minimum count of numbers in a phone 
number string, during a phone number  
search.
@return number of found items.

@panic ETulPanicInvalidTokenizerSearchCase in debug build if there is no valid search case.
@panic ETulPanicDescriptorLength in debug build if item's position 
and/or length is out of the document's range.
@leave KErrNone, if successful; otherwise one of the other system-wide error codes.
*/
EXPORT_C TInt CTulAddressStringTokenizer::DoNewSearchL(const TDesC& aText, TInt aSearchCases, TInt aMinNumbers)
    {
    delete iFoundItems;
    iFoundItems = NULL;
	iPosition = 0;
    ConstructL(aText, aSearchCases, aMinNumbers);
    return ItemCount();
    }

// ---------------------------------------------------------
// Search Algorithms and helpers
// ---------------------------------------------------------
/**
Character information methods

@param charac a Character to be investigated
@return ETrue if the parameter for phone number was valid, else returns EFalse
*/
TBool CTulAddressStringTokenizer::IsValidPhoneNumberChar(const TChar& aCharac)
    { 
    // Returns ETrue if the parameter is a valid character in a phonenumber
    const TDesC& array = KPhoneNumberChars;
    return (array.Locate(aCharac) != KErrNotFound);
    }

/**
Character information methods

@param charac a Character to be investigated
@return ETrue if the parameter for login part of the e-mail address is valid, else returns EFalse
*/
TBool CTulAddressStringTokenizer::IsValidEmailChar(const TChar& aCharac)
    { 
    // Returns ETrue if the parameter is a valid character for username part of e-mail address
    // ASCII 33 - 47 (without '"', ',', ''', '(' and ')' because they can be used to separate address
    // from rest of the text )
    const TDesC& array = KEmailChars;
    return (array.Locate(aCharac) != KErrNotFound || IsValidEmailHostChar(aCharac));
    }

/**
Character information methods

@param charac a Character to be investigated
@return ETrue if the parameter for host part of the e-mail address is valid, else returns EFalse
*/
TBool CTulAddressStringTokenizer::IsValidEmailHostChar(const TChar& aCharac)
    { 
    // Returns ETrue if the parameter is a valid character for a host part of e-mail address
    const TDesC& array = KEmailHostChars;
    return (array.Locate( aCharac.GetLowerCase() ) != KErrNotFound);
    }

/**
Character information methods

@param charac a Character to be investigated
@return ETrue if the parameter for URL is valid, else returns EFalse
*/
TBool CTulAddressStringTokenizer::IsValidUrlChar(const TChar& aCharac)
    { 
    // Returns ETrue if the parameter is a valid character for url
    if (IsValidEmailHostChar(aCharac))
		return ETrue;

    const TDesC& array = KUrlChars;
    return (array.Locate(aCharac) != KErrNotFound);
    }

/**
Search algorithm for searching e-mail addresses

@param aText Text that will be parsed
@return ETrue if any EMail items were found else returns EFalse
@leave KErrNone, if successful; otherwise one of the other system-wide error codes.
@panic ETulPanicDescriptorLength in debug build if item's position 
and/or length is out of the document's range.
*/
TBool CTulAddressStringTokenizer::SearchMailAddressL( const TDesC& aText )
    {
    TInt searchStart = 0;
    TInt searchResult = 0;
    const TInt end = aText.Length(); // end of document

    do
        {
        TPtrC segment = aText.Right( end - searchStart );
        searchResult = segment.LocateF('@');

        if (searchResult != KErrNotFound)
            { // @ found
            // There should be valid characters (not a period) before and after the @ character
            if ( searchResult == 0 // first char
                || (searchResult >= segment.Length() - 1) // last char 
                || !(IsValidEmailChar(segment[searchResult - 1])) 
                || !(IsValidEmailHostChar(segment[searchResult + 1]))
                || segment[searchResult - 1] == '.' 
                || segment[searchResult + 1] == '.'
               )
                {
                searchStart += searchResult + 1;
                continue;
                }

            TBool wasPeriod = EFalse; // To prevent sequential periods
            // Get TLex from the pointer to get a better API for parsing
            TLexMark startPos;
            TLexMark endPos;
            TLex token = segment;
            
            // Go to searchResult and un-get until the beginning of e-mail address is reached
            token.Inc( searchResult );
            token.Mark();
            do
                {
                token.UnGet();
                if ( token.Peek() == '.' )
                    { // If it was a period
                    if (wasPeriod)	// and if the former was also -> break
                        break;
                    else	// else mark that this one was a period
                        wasPeriod = ETrue;
                    }
                else
                    wasPeriod = EFalse;
                }
            while (token.Offset() > 0 && IsValidEmailChar(token.Peek()));
            
            if (token.Offset() != 0 || !IsValidEmailChar(token.Peek()))
                token.Inc();

            // Get rid of periods from the start of address
            // Does it have to start with a number or char(abc...).
            // If it does, the loop should check that it gets rid of all special chars also.
            while (token.Peek() == '.')
                token.Inc();

            token.Mark( startPos ); // Mark the beginning of address
            token.UnGetToMark();
            wasPeriod = EFalse;
            
            do	// Go forward until a nonvalid character
                {
                token.Inc();
                if ( token.Peek() == '.' )
                    { // If it was a period
                    if ( wasPeriod )	// and if the former was also -> break
                        break;
                    else	// else mark that this one was a period
                        wasPeriod = ETrue;
                    }
                else
                    wasPeriod = EFalse;
                }
            while ( !token.Eos() && IsValidEmailHostChar( token.Peek() ) );
            
            // If address ends with a period take it away
            token.UnGet();
            if (token.Peek() != '.')
                token.Inc();

            token.Mark( endPos ); // Mark the beginning of address

            // Append the found string to the array
            __ASSERT_DEBUG( searchStart + token.MarkedOffset( startPos ) 
                            + token.MarkedOffset( endPos ) 
                            - token.MarkedOffset( startPos ) <= aText.Length(), 
                            Panic(ETulPanicDescriptorLength) );
            AddItemL( searchStart + token.MarkedOffset( startPos ), 
                      token.MarkedOffset( endPos ) - token.MarkedOffset( startPos ), 
                      EFindItemSearchMailAddressBin);
            searchStart += token.MarkedOffset( endPos ) + 1;
            }
        }
    while ( searchResult != KErrNotFound && searchStart < end );

    return (iFoundItems->Count() > 0);
    }

/**
Search algorithm for searching phone numbers

@param aText Text that will be parsed
@return ETrue if any Phone Number items were found else returns EFalse
@leave KErrNone, if successful; otherwise one of the other system-wide error codes.
@panic ETulPanicDescriptorLength in debug build if item's position 
and/or length is out of the document's range.
*/
TBool CTulAddressStringTokenizer::SearchPhoneNumberL( const TDesC& aText )
    {
    TLexMark startMark; // Points to the start of the found phone number
    TLexMark endMark; // Points to the end of the found phone number
    TLexMark mark;
    const TInt end = aText.Length();

    TLex number = aText;

    while ( !(number.Eos()) )
        {
        TInt numberCount = 0; // How many real numbers (1234567890)
        TInt bracketsOpen = 0; // How many brackets are currently open
        TInt brackets = 0; // How many brackets overall

        TChar charac = number.Peek();

        while( (!(IsValidPhoneNumberChar( charac ) || charac == '+'
               || charac == '(' ) || charac == '-' || charac == '.' || charac == '/') 
			   && !(number.Eos()) && number.Offset() < end )
            {
            number.Inc();
            charac = number.Peek();
            }

        if ( number.Offset() >= end )
            break;
        
        if ( number.Peek() == '#' )
			{
			number.Inc();
			if (number.Peek() == '.' )
				continue;

			number.UnGet();
			}

        if ( number.Peek() == '+' )
            { // '+' has to be followed by a number (not # or * ...)
            number.Inc();
            if ( !(number.Peek().IsDigit()) )
                continue;

            number.UnGet();
            }

        if ( number.Peek() == '(' )
            { // '(' has to be followed by valid phone number 
              // character (whitespaces are allowed before) or '+' is a next character
            number.Inc();
            if ( !(number.Peek() == '+') )
                {
                number.Mark(mark);
                number.SkipSpace();
                charac = number.Peek();
                if ( !( IsValidPhoneNumberChar(charac) || charac == '+' 
                    || charac == '(' ) || charac == '-' || charac == '.' || charac == '/')
                    {
                    number.Inc();
                    continue;
                    }
                else
                    {
                    number.UnGetToMark(mark);
                    number.UnGet();
                    number.Mark(startMark);
                    }
                } 
            else
                {
                number.UnGet();
                number.Mark(startMark);
                number.Inc();
                }

            bracketsOpen++;
            brackets++;
            }
        else
            number.Mark(startMark);

        if ( number.Peek().IsDigit() )	// If the character was a number
            numberCount++;
        else if ( bracketsOpen > 0 ) 
            { 
            number.Inc();
            TChar next  = number.Peek();
            TInt bracketsOpen2 = bracketsOpen;
            while( (IsValidPhoneNumberChar( next ) || next.IsSpace()
                || next == '(' || next == ')' || next == 'p' || next == '+'
                || next == 'w' ) && !(number.Eos()) && number.Offset() < end)
                {
                if ( next == '(' )
                    bracketsOpen2++;
                else if ( next == ')' )
                    bracketsOpen2--;
                
                if ( bracketsOpen2 == 0 )
                    break;

                number.Inc();
                next = number.Peek();
                }

            number.UnGetToMark(startMark);
            if ( bracketsOpen2 != 0 )
                {
                number.Inc();
                continue;
                }
            }

        number.Inc();
        while ( number.Peek() == '(' && !(number.Eos()) && bracketsOpen > 0 )
            {
            number.Inc();
            bracketsOpen++;
            }

        if ( number.Peek() == '+' && bracketsOpen > 0 )
            number.Inc();

        // a Valid first character has been found. Let's go forward as long as valid characters are found.
        charac = number.Peek();

        while( (IsValidPhoneNumberChar( charac ) || charac.IsSpace()
            || charac == '(' || charac == ')' || charac == 'p'
            || charac == 'w' ) && !(number.Eos()) && number.Offset() < end
            && charac != KCharLinefeed && charac != KCharFormfeed 
            && charac != KCharCarriageReturn
            && charac != KCharLineSeparator
            && charac != KCharParagraphSeparator )
            {
            if ( number.Peek() == '(' )
                { // '(' can't be the last character in phone number
                number.Mark(mark);
                number.Inc();
                
                TChar spaceJump = number.Peek();
                while ( !number.Eos() && spaceJump.IsSpace() && spaceJump != KCharLinefeed 
                        && spaceJump != KCharFormfeed && spaceJump != KCharCarriageReturn 
                        && charac != KCharLineSeparator && spaceJump != KCharParagraphSeparator)
                    {
                    number.Inc();
                    spaceJump = number.Peek();
                    }
                
                if ( !(IsValidPhoneNumberChar(number.Peek())) && number.Peek() != ')'
                     && number.Peek() != '(' )
                    {
                    number.UnGetToMark(mark);
                    break;
                    }

                TChar next  = number.Peek();
                TInt bracketsOpen2 = bracketsOpen + 1;
                while( (IsValidPhoneNumberChar( next ) || next.IsSpace()
                    || next == '(' || next == ')' || next == 'p'
                    || next == 'w' ) && !(number.Eos()) && number.Offset() < end)
                    {
                    if ( next == '(' )
                        bracketsOpen2++;
                    else if ( next == ')' )
                        bracketsOpen2--;

                    if ( bracketsOpen2 == 0 )
                        break;

                    number.Inc();
                    next = number.Peek();
                    }

                number.UnGetToMark(mark);

                if ( bracketsOpen2 != 0 )
                    break;

                bracketsOpen++;
                brackets++;
                }
            else if ( number.Peek() == ')' )
                {
                if ( bracketsOpen <= 0 )	// there has to be equal number of brackets
                    break;

                bracketsOpen--;
				number.Mark(mark);
                number.Inc();
				if ( number.Peek() == '.' )	// '.' is not allowed after ')'
                    break;

                number.UnGetToMark(mark);
                }
            else if ( number.Peek() == '-' || number.Peek() == 'w' 
                        || number.Peek() == 'p' || number.Peek() == '.' || number.Peek() == '/')
                { // Hyphen mark and 'p' & 'w' chars must be followed by a number
				TChar last = number.Peek();
                number.Mark(mark);
                number.Inc();
                
                TChar spaceJump = number.Peek();
                while ( !number.Eos() && spaceJump.IsSpace() && spaceJump != KCharLinefeed 
                        && spaceJump != KCharFormfeed && spaceJump != KCharCarriageReturn 
                        && charac != KCharLineSeparator && spaceJump != KCharParagraphSeparator )
                    {
                    number.Inc();
                    spaceJump = number.Peek();
                    }
                    
                if ( !(number.Peek().IsDigit()) )
                    {
					if (last == '.' && number.Peek() == ')' && bracketsOpen > 0 )
						continue;
					else
						{
						number.UnGetToMark(mark);
						break;
						}
                    }

                number.UnGetToMark(mark);
                }
            else if ( number.Peek().IsDigit() )
                numberCount++;

            number.Inc();
            charac = number.Peek();
            }

        // Get rid of whitespaces from the end
        number.UnGet();
        while( number.Peek().IsSpace() && !(number.Eos()))
            number.UnGet();

        number.Inc();
        // ------------------------------------
        number.Mark(endMark);

        // If they exist, remove brackets from the beginning and the end
        number.Mark(mark); // Let's mark where to continue the search
        TBool endBrackets = ETrue;
        do
            {
            number.UnGet();

            if ( number.Peek() == ')' )
                {
                number.UnGetToMark(startMark);
                if ( number.Peek() == '(' )
                    {
                    // If there's more than one pair of brackets -> don't strip them.
                    if ( brackets > 1 )
                        break;

                    number.Inc();
                    number.Mark(startMark);
                    number.UnGetToMark(endMark);
                    number.UnGet();
                    number.Mark(endMark);
                    // Get rid of whitespaces and periods from the end and from the beginning
					number.UnGet();
                    while ( (number.Peek().IsSpace() || number.Peek() == '.') 
                            && number.Offset() > number.MarkedOffset(startMark) )     
                        { // from the end
                        number.UnGet();
                        }
					number.Inc();
                    number.Mark(endMark);
                    number.UnGetToMark(startMark);
                    while ( (number.Peek().IsSpace() || number.Peek() == '.') 
                            && number.Offset() < number.MarkedOffset(endMark) )     
                        { // from the beginning
                        number.Inc();
                        }
                    number.Mark(startMark);
                    number.UnGetToMark(endMark);
                    // ----
                    }
                else
                    endBrackets = EFalse;
                }
            else
                endBrackets = EFalse;
            }
        while ( endBrackets );

        number.UnGetToMark(mark);
        // ----------------        

        if ( numberCount <= KFindItemMaxNumbers && numberCount >= iMinNumbers )
            {
			TPtrC tokenPtr = number.MarkedToken(startMark);
			TInt tokensEnd = tokenPtr.Length();
			TInt numbers = 0;
			TInt partialNumber = 0;
			TBool wasValidPhoneNumber = ETrue;
			TInt i = 0;

			for ( ; i < tokensEnd; i++ )
				{
				if ( tokenPtr[i] == '.' )
					partialNumber = 0;
				else if ( ((TChar)tokenPtr[i]).IsDigit() )
					{
					numbers++;
					partialNumber++;
					}

				if ( ( partialNumber == 1 || partialNumber == 2 ) && i + 1 < tokensEnd )
					{
					if ( tokenPtr[i + 1] == '.' )
						wasValidPhoneNumber = EFalse;
					}
				}
				
			if (!wasValidPhoneNumber && numbers > 6)
				wasValidPhoneNumber = ETrue;
			
			if (wasValidPhoneNumber)
				{
	            __ASSERT_DEBUG( number.MarkedOffset(startMark) + number.MarkedOffset(endMark) 
	                            - number.MarkedOffset(startMark) <= aText.Length(), 
	                            Panic(ETulPanicDescriptorLength) );

	            AddItemL( number.MarkedOffset(startMark), 
	                      number.MarkedOffset(endMark) - number.MarkedOffset(startMark), 
	                      EFindItemSearchPhoneNumberBin );
				}
			}

        }

    return (iFoundItems->Count() > 0);
    }


/**
Parses URL from a token. Is used by SearchUrlL method and if a URL
was found it's appended to item array. Note that parsing for generic URIs 
is done with SearchGenericUriL -method.

@param aType  a Type of URL to seach, i.e.
                  www.
                  wap.
                  IP e.g.127.0.0.1
@param        aTokenPtr Pointer to token that will be parsed
@param        aTextOffset Offset of the token (start position in the whole text)
@leave KErrNone, if successful; otherwise one of the other system-wide error codes.
@return ETrue if the parameter for phone number is valid, else returns EFalse
*/
TBool CTulAddressStringTokenizer::ParseUrlL(const TDesC& aType, const TPtrC& aTokenPtr, TInt aTextOffset)
    {
    TBool wasValidUrl = EFalse;
    TLex url;
    
    TInt position = aTokenPtr.FindF( aType ); 
    if ( position != KErrNotFound )
        { // address start found
        url = aTokenPtr.Right( aTokenPtr.Length() - position );
        url.Inc( aType.Length() );

        while( IsValidUrlChar( url.Peek() ) && !(url.Eos()) )
            {
            if( url.Peek() == ':' )
                {
                url.Inc();
                if ( !url.Peek().IsDigit() )
                    {
                    url.UnGet();
                    break;
                    }
                }
            else
                url.Inc();
            }

        // If a period or question mark was followed by a whitespace remove it
        if ( url.Eos() ) // Can't be followed by white space if it's
            { // the last character at token
            url.UnGet();
            if ( url.Peek() != '.' && url.Peek() != '?' && url.Peek() != ',' )	// If it wasn't a period or question mark
                url.Inc();
            }
        
        url.Mark();
        wasValidUrl = ETrue;
        }

    if ( wasValidUrl && ( url.MarkedOffset() > aType.Length() ) )
        {
        AddItemL( aTextOffset - aTokenPtr.Length() + position, url.MarkedOffset(), EFindItemSearchURLBin );
        return ETrue;
        }

    return EFalse;
    }

/**
Search fixed start URLs, i.e. URLs without schema (www., wap.).
Also finds IPv4 addresses (*.*.*.*).
As a special case, supports deprecated hardcoded schematic addresses finding 
(http://, https://, rtsp://) to make sure deprecated search cases work 
as they did previously.

@param aText Text that will be parsed
@param aFindFixedSchemas If true, will find old fixed schematic URLs also
@return ETrue if any URL are found else returns EFalse
@leave KErrNone, if successful; otherwise one of the other system-wide error codes.
@panic ETulPanicDescriptorLength in debug build if item's position and/or length is out of the document's range.
*/
TBool CTulAddressStringTokenizer::SearchUrlL( const TDesC& aText, const TBool aFindFixedSchemas )
    {
    TLex text = aText;
    while ( !text.Eos() )
        {
        while( !(text.Eos()) && !IsValidUrlChar( text.Peek() ) )
            text.Inc();

        text.Mark();
        while( !(text.Eos()) && IsValidUrlChar( text.Peek() ) )
            text.Inc();

        TPtrC tokenPtr = text.MarkedToken();
        TBool wasValidUrl = EFalse;

        if ( aFindFixedSchemas )	// Search for http://
            wasValidUrl = ParseUrlL( KHttpUrlAddress, tokenPtr, text.Offset() );
        
        if (aFindFixedSchemas && !wasValidUrl)	// Search for https://
            wasValidUrl = ParseUrlL( KHttpsUrlAddress, tokenPtr, text.Offset() );

        if (aFindFixedSchemas && !wasValidUrl) // Search for rtsp://
            wasValidUrl = ParseUrlL( KRtspUrlAddress, tokenPtr, text.Offset() );

        if ( !wasValidUrl )	// Search for www.
            wasValidUrl = ParseUrlL( KWwwUrlAddress, tokenPtr, text.Offset() );

        if ( !wasValidUrl )	// Search for wap.
            wasValidUrl = ParseUrlL( KWapUrlAddress, tokenPtr, text.Offset() );

        if ( !wasValidUrl )	// Search for IP-address (xxx.xxx.xxx.xxx)
            { 
            if ( tokenPtr.Match( KIPAddress ) != KErrNotFound )
                {
                TInt periods = 0;
                wasValidUrl = ETrue;
                TBool endWithPunctuation = EFalse;
                TBool betweenBrackets = EFalse;

                // First see if token ends with ",",".","!","?",";" or ":"
                TChar charac = tokenPtr[tokenPtr.Length() - 1];
                TChar charac0 = tokenPtr[0];
                if ( charac == ',' || charac == '.' ||
                     charac == '!' || charac == '?' ||
                     charac == ';' || charac == ':' )
                    {
                    endWithPunctuation = ETrue;
                    }
                // Or if it starts and ends with brackets or quotation marks
                else if ( ( charac0 == '(' && charac == ')' )
                       || ( charac0 == '"' && charac == '"' )
                       || ( charac0 == '[' && charac == ']' )
                       || ( charac0 == '<' && charac == '>' ) )
                    {
                    betweenBrackets = ETrue;
                    }

                TInt i = 0;
                TInt tokensEnd = tokenPtr.Length();
                if ( endWithPunctuation )
                    tokensEnd--;
                else if ( betweenBrackets )
                    {
                    i = 1;
                    tokensEnd--;
                    }

                // Take a closer look to see if a valid IP-address
                TBuf<3> ipPart;
                TInt numbers = 0;
                for ( ; i < tokensEnd; i++ )
                    {
                    if ( !( ((TChar)tokenPtr[i]).IsDigit() || tokenPtr[i] == '.' ) )
                        {
                        wasValidUrl = EFalse;
                        break;
                        }

                    if ( tokenPtr[i] == '.' )
                        periods++;
                    else
                        numbers++;

                    if ( numbers > KNumbersInIpAddress || periods > KDotsInIpAddress )
                        {
                        wasValidUrl = EFalse;
                        break;
                        }

                    if ( ((TChar)tokenPtr[i]).IsDigit() )
                        {
                        ipPart.Append( tokenPtr[i] );
                        TBool checkInt = EFalse;
                        if ( i + 1 < tokensEnd )
                            {
                            if ( tokenPtr[i+1] == '.' )
                                checkInt = ETrue;
                            }

                        if ( i == tokensEnd - 1 || checkInt )
                            {
                            TLex val = ipPart;
                            TInt numberInt;
                            TInt error = val.Val( numberInt );
                            if ( error != KErrNone || numberInt > 255 )
                                {
                                wasValidUrl = EFalse;
                                break;
                                }

                            numbers = 0;
                            ipPart.Delete( 0, ipPart.Length() );
                            }
                        }
                    }

                if ( wasValidUrl && periods == KDotsInIpAddress )
                    {
                    TInt startPos = text.Offset() - tokenPtr.Length();
                    TInt length = tokenPtr.Length();
                    // If there was a punctuation at the end or brackets, let's take it/them away
                    if ( endWithPunctuation || betweenBrackets)
                        {
                        length--;
                        if ( betweenBrackets )
                            {
                            startPos++;
                            length--;
                            }
                        }

                    __ASSERT_DEBUG( startPos + length <= aText.Length(), Panic(ETulPanicDescriptorLength) );
                    AddItemL( startPos, length, EFindItemSearchURLBin );
                    }
                }
            }
        }

    return (iFoundItems->Count() > 0);
    }

/**
Search algorithm for searching generic URIs

@param aText Text that will be parsed
@return ETrue if any generic URI is found else returns EFalse
@leave KErrNone, if successful; otherwise one of the other system-wide error codes.
*/
TBool CTulAddressStringTokenizer::SearchGenericUriL( const TDesC& aText )
    {
    // Detect generic URI within the token
    const TDesC& schemeStartArray = KURISchemeStartCharacters;
    const TDesC& schemeBodyArray = KURISchemeBodyCharacters;
    const TDesC& schemeTerminatorArray = KURISchemeTerminator;
    const TDesC& URIArray = KURICharacters;

    TBool wasValidUri = EFalse;
    TLex text = aText;

    while ( !text.Eos() )
        {
        // Discard characters until URI scheme terminator is found
        while( !(text.Eos()) && schemeTerminatorArray.Locate(text.Peek()) == KErrNotFound )
            text.Inc();

        // if at end of the text, no legit URI found
        if ( !text.Eos() )
            {
            // Store the schema end offset (+1 to skip ':')
            TInt schemeEndOffset = text.Offset() + 1;

            // Scheme must be at least 1 character long at the beginning of the text to be valid
            if ( text.Offset() > 0 ) 
                {
                // Un-get last scheme character to begin examination
                text.UnGet();

                // Rewind until beginning of the URI
                while ( text.Offset() > 0 && schemeBodyArray.Locate(text.Peek().GetLowerCase()) != KErrNotFound )
                    text.UnGet();
        
                // Now text pointer is at first character of the URI
                // Do go back through the scheme until a legal beginning character for URI 
                // is found or back to the (schemeEndOffset - 1) i.e. URI scheme terminator
                while ( schemeStartArray.Locate(text.Peek().GetLowerCase()) == KErrNotFound && (text.Offset() + 1) < schemeEndOffset )
                    text.Inc();

                // check if terminated because a valid start character was found when
                // scheme terminator was reached.
                if ( schemeStartArray.Locate(text.Peek().GetLowerCase()) != KErrNotFound )
                    {
                    // First character is a valid URI char, so the scheme is valid -> 
                    // marks the beginning of the array
                    text.Mark();
            
                    // fast forward to the end of the scheme
                    while( text.Offset() < schemeEndOffset )    
                        text.Inc();
            
                    // Get characters until end of schema
                    while( !(text.Eos()) && URIArray.Locate( text.Peek().GetLowerCase() ) != KErrNotFound )
                        text.Inc();

                    // remove certain punctuation from end of the URI, as it is likely 
                    // to be part of the surrounding text.
                    text.UnGet();

                    //special processing for bracket
                    //only remove the end bracket if there is no open bracket in the uri
                    //not counting bracket pairs for efficiency
                    if (text.Peek()!=')' || text.MarkedToken().Locate(TChar('('))!=-1)
                        text.Inc();

                    text.UnGet();
                    if ( text.Peek() != '.' && text.Peek() != '?' && text.Peek() != ',')
                        text.Inc();
                
                    // URI cannot contain only scheme, so check that pointer was increased 
                    // by at least one character
                    if ( schemeEndOffset != text.Offset() )
                        {
                        // Append found text to item array (it is now known to be 
                        // syntactically valid URI as it contains characters after the scheme)
                        AddItemL( text.MarkedOffset(), text.Offset() - text.MarkedOffset(), EFindItemSearchScheme );
                        wasValidUri = ETrue;
                        }
                    }
                else // First character of scheme is not legit, fast forward to end of the 
                     // scheme anyway to continue search
                    {
                    while( text.Offset() < schemeEndOffset )        
                        text.Inc();
                    }
                }
            else
 				text.Inc();
            }
        }

    return wasValidUri;
    }

// ---------------------------------------------------------
// Position and count methods
// ---------------------------------------------------------

/**
Gets the number of items in the found items array.

@return the number of items in the found items array. 
*/
EXPORT_C TInt CTulAddressStringTokenizer::ItemCount() const
    {
    return (iFoundItems ? iFoundItems->Count() : 0);
    }

/**
Gets the current position (or the position of the currently selected item) 
in the found items array.

@return the current position in the found items array of the 
CTulAddressStringTokenizer instance. If no items are in the array, zero is returned.
*/
EXPORT_C TInt CTulAddressStringTokenizer::Position() const
    {
    return iPosition;
    }

/**
Resets the position in item array to zero (beginning of the array).
*/
EXPORT_C void CTulAddressStringTokenizer::ResetPosition()
    {
    iPosition = 0;
    }

// ---------------------------------------------------------
// GetItem methods
// ---------------------------------------------------------

/**
Gets the array of found items. Returns a constant pointer to the 
found items array of the CTulAddressStringTokenizer instance. The items cannot
be modified through this pointer, only accessed. The ownership of 
the array stays with CTulAddressStringTokenizer.

@return a constant pointer to the array of found items. Ownership 
stays with CTulAddressStringTokenizer.
*/
EXPORT_C const CArrayFixFlat<CTulAddressStringTokenizer::SFoundItem>* CTulAddressStringTokenizer::ItemArray() const
    {
    return iFoundItems;
    }

/**
Gets the currently 'selected' item in the array of found items. 

@param aItem contains the currently selected item after returning.
@return ETrue if the item was found. EFalse if the item wasn't found.
*/
EXPORT_C TBool CTulAddressStringTokenizer::Item( SFoundItem& aItem ) const
    { // Return EFalse if no items were found
    if ( iFoundItems->Count() <= 0 )
        {
        aItem.iStartPos = 0;
        aItem.iLength = 0;
		aItem.iItemType = EFindItemSearchPhoneNumberBin;
		return EFalse;
        }

    aItem = iFoundItems->At( iPosition );
    return ETrue;
    }

/**
Gets the next found item relative to the currently selected item.
Moves the selection to point to the next item in the array of 
found items. 

@param aItem contains the next item after returning.
@return ETrue if the item was found. EFalse if there's no next item.
*/
EXPORT_C TBool CTulAddressStringTokenizer::NextItem( SFoundItem& aItem )
    {
    if (iFoundItems->Count() <= (iPosition + 1))
        return EFalse;

    iPosition++;
    aItem = iFoundItems->At( iPosition );
    return ETrue;
    }

/**
Gets the previous found item relative to the currently selected 
item. Moves the selection to point to the previous item in the 
array of found items.. 

@param aItem contains the previous item after returning.
@return ETrue if the item was found. EFalse if there's no previous item.
*/
EXPORT_C TBool CTulAddressStringTokenizer::PrevItem( SFoundItem& aItem )
    {
    if ( iPosition <= 0 )
        return EFalse;

    iPosition--;
    aItem = iFoundItems->At( iPosition );
    return ETrue;
    }

/**
Adds item to search arrays. Adding is done so that arrays are always sorted.
If added element would overlap a previously found element, it is not added.

@param aStartPos  Start position of the found item
@param aLength    Length of found item
@param aType      Type of the found item
@leave KErrNone, if successful; otherwise one of the other system-wide error codes.
*/
void CTulAddressStringTokenizer::AddItemL(TInt aStartPos, TInt aLength, TTokenizerSearchCase aType )
    {
    // Create item element
    SFoundItem foundItem;
    foundItem.iStartPos = aStartPos;
    foundItem.iLength = aLength;
	foundItem.iItemType = aType;

    // Add item data to arrays
    TKeyArrayFix insertKey(0, ECmpTInt); 
	iFoundItems->InsertIsqAllowDuplicatesL(foundItem, insertKey);	    
	}

//  End of File
