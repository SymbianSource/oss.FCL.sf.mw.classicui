/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
*/



#ifndef __TULADDRESSSTRINGTOKENIZER_H__
#define __TULADDRESSSTRINGTOKENIZER_H__

#include <e32base.h>

/**
Address String Tokenizer API offers methods for parsing phone numbers and e-mail, 
URL and URI addresses from the given text. The API consists of the 
CTulAddressStringTokenizer class.

Usage:

@code
 #include <tuladdressstringtokenizer.h>

 // SFoundItem instance
 CTulAddressStringTokenizer::SFoundItem item;

 // Some text
 TBufC<256> strSomeText(_L("Mail to me@someplace.com or call 040 1234567. 
 You can also tune in to audio feed at rtsp://someplace.com/somefeed.ra."));
	
 // First the user has to create an instance of CTulAddressStringTokenizer by using the
 // factory method NewL(). The method takes two parameters. The first 
 // parameter defines the text to be searched from and the second parameter 
 // tells what exactly is being looked for.
 CTulAddressStringTokenizer singleSearch = CTulAddressStringTokenizer::NewL(strSomeText, 
                  CTulAddressStringTokenizer::EFindItemSearchMailAddressBin);

 // The passed text is parsed in construction, and found items can be fetched 
 // by using the ItemArray() method. It returns a constant array containing 
 // all the found items. The interface also offers helper functions for 
 // handling the item array by itself. 

 // Get count of found items.
 TInt count(singleSearch->ItemCount());

 // Get currently selected item (me@someplace.com) to the result1 variable.
 singleSearch->Item(item);
 TPtrC16 result1(strSomeText.Mid(item.iStartPos, item.iLength));

 // Deallocate memory
 delete singleSearch;

 // Create an instance of CTulAddressStringTokenizer and look for all possible 
 // things (cases work as binary mask).
 CTulAddressStringTokenizer* multiSearch = CTulAddressStringTokenizer::NewL(strSomeText,
                  (CTulAddressStringTokenizer::EFindItemSearchPhoneNumberBin |           
                  CTulAddressStringTokenizer::EFindItemSearchURLBin | 
                  CTulAddressStringTokenizer::EFindItemSearchMailAddressBin | 
                  CTulAddressStringTokenizer::EFindItemSearchScheme));

 // Get count of found items.
 TInt count2(multiSearch->ItemCount());

 // Get currently selected item to the result2 variable.
 multiSearch->Item(item);

 // Debug print all items and their type.
 for( TInt i=0; i<count2; i++)
     {
     TPtrC16 result2(strSomeText.Mid(item.iStartPos, item.iLength));
     RDebug::Print(_L("Found type %d item:"), item.iItemType);
     RDebug::Print(_L("%S"), &result2);
     multiSearch->NextItem(item);
     }

 // Deallocate memory
 delete multiSearch;
@endcode

@publishedAll
@released
*/

class CTulAddressStringTokenizer : public CBase
    {
public:
    /**
    Enumeration to define the search case. 
    Multiple enumerations can be used as binary mask.
    */
    enum TTokenizerSearchCase
        {
        // Searches phone numbers.
		EFindItemSearchPhoneNumberBin = 4, 
        // Searches mail addresses.
        EFindItemSearchMailAddressBin = 8,
        // Searches fixed start URLs ("http://", "https://", "rtsp://"), "www.", "wap." and IPv4 addresses.
        EFindItemSearchURLBin  = 16,
        // Searches for all URIs containing a scheme.
        EFindItemSearchScheme  = 32
        };

    // Struct to contain a found item.
    struct SFoundItem
        {
        TInt iStartPos;	// Start position of the found item.
        TInt iLength;	// Length of the found item (characters).
        TTokenizerSearchCase iItemType;		// Search case of the found item
		};

public:  // Constructors and destructor
    IMPORT_C static CTulAddressStringTokenizer* NewL( const TDesC& aText, TInt aSearchCases );
    IMPORT_C static CTulAddressStringTokenizer* NewL( const TDesC& aText,  TInt aSearchCases, TInt aMinNumbers );
    IMPORT_C ~CTulAddressStringTokenizer();
public:
	IMPORT_C TInt ItemCount() const;
    IMPORT_C TBool Item( SFoundItem& aItem ) const;
    IMPORT_C TBool NextItem( SFoundItem& aItem );
    IMPORT_C TBool PrevItem( SFoundItem& aItem );
    IMPORT_C const CArrayFixFlat<SFoundItem>* ItemArray() const;
	IMPORT_C TInt Position() const;	
    IMPORT_C void ResetPosition();
    IMPORT_C TInt DoNewSearchL( const TDesC& aText, TInt aSearchCases);
    IMPORT_C TInt DoNewSearchL( const TDesC& aText, TInt aSearchCases,  TInt aMinNumbers );
private:
    CTulAddressStringTokenizer();
    void AddItemL( TInt aStartPos, TInt aLength, TTokenizerSearchCase aType );

    TBool SearchPhoneNumberL( const TDesC& aText );
    TBool SearchMailAddressL( const TDesC& aText );  
    TBool SearchGenericUriL( const TDesC& aText );
    TBool SearchUrlL( const TDesC& aText, TBool aFindFixedSchemas );
    TBool ParseUrlL( const TDesC& aType, const TPtrC& aTokenPtr, TInt aTextOffset );

    static TBool IsValidEmailChar(const TChar& charac); // Login part of the e-mail address
    static TBool IsValidEmailHostChar(const TChar& charac); // Host part of the e-mail address
    static TBool IsValidPhoneNumberChar(const TChar& charac); // Phone number
    static TBool IsValidUrlChar( const TChar& charac); // URL

    void ConstructL( const TDesC& aText, TInt aSearchCases, TInt aMinNumbers );
	void PerformSearchL( const TDesC& aText, TInt aSearchCases );
    
    CTulAddressStringTokenizer( const CTulAddressStringTokenizer& );	// Prohibit copy constructor
    CTulAddressStringTokenizer& operator= ( const CTulAddressStringTokenizer& );  // Prohibit assigment operator
private:
    CArrayFixFlat<SFoundItem>* iFoundItems;		// Array of all found items.
    TInt iPosition;		// Engine's position in the iFoundItems.
    TInt iMinNumbers;	// Minimum count of numbers in a phone number
    };


#endif      // __TULADDRESSSTRINGTOKENIZER_H__
            
