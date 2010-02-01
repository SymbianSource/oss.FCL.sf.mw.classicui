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



#ifndef __TULPHONENUMBERUTILS_H__
#define __TULPHONENUMBERUTILS_H__

#include    <coemain.h>


/**
Class offers static methods for parsing and validating phone numbers. 
Phone Parser API provides methods which are used to parse and validate
phone numbers. The API consists of the TulPhoneNumberUtils class.

Examples of valid phone numbers:
1.	+358501234567
2.	+358 (50) 123 4567

Even though both of the above examples are valid phone numbers, only 1) is 
accepted as a phone number by many systems. To convert 2) to 1), use the 
parsing method of the API.

Usage:
  
@code
 #include <tulphonenumberutils.h> 

 // Example shows how to use the parsing method of the API.

 // A number to be parsed. 
 TBuf<50> number1 = _L("+358 (40) 123 132");

 // Type of the phone number to be parsed is a regular phone number.
 TBool validNumber1 = 
 TulPhoneNumberUtils::NormalizePhoneNumber( number1,
                                      TulPhoneNumberUtils::EPlainPhoneNumber );

 // The phone number number1 is a valid regular phone number.
 // After parsing validNumber1 is ETrue and 
 // number1 is "+35840123132".
 // Do something like SendSMS( number1 ) etc.

 // A number to be parsed. 
 TBuf<50> number2 = _L("+358 (40) 123p132"); // note 'p'

 // Type of the phone number to be parsed is a regular phone number.
 TBool validNumber2 = 
 TulPhoneNumberUtils::NormalizePhoneNumber( number2,
                                      TulPhoneNumberUtils::EPlainPhoneNumber );

 // The phone number number2 is not a valid regular phone number.
 // After parsing validNumber2 is EFalse and 
 // number2 is "+358 (40) 123p132" (unchanged).
@endcode

@publishedAll
@released
*/
NONSHARABLE_CLASS(TulPhoneNumberUtils)
    {
public:
    /** 
    * Enumeration for phone number types. 
    * Used to specify the type of phone numbers in methods of 
    * TulPhoneNumberUtils class.
    */
    enum TPhoneNumberType
        {
        /** The supplied phone number is a regular phone number. */
        EPlainPhoneNumber,
        /** The supplied phone number is a contact card number. */
        EContactCardNumber,
        /** The supplied phone number is is a phone client number. */
        EPhoneClientNumber,
        /** The supplied phone number is an SMS number. */
        ESMSNumber
        };

    IMPORT_C static TBool Normalize( TDes& aNumber, TPhoneNumberType aType = EPlainPhoneNumber);
    IMPORT_C static TBool IsValid( const TDesC& aNumber, TPhoneNumberType aType = EPlainPhoneNumber );
public: // deprecated
    inline static TBool ParsePhoneNumber( TDes& aNumber, TInt aType );
    inline static TBool IsValidPhoneNumber( const TDesC& aNumber, TInt aType );
private:    
    static TBool IsValidPhoneNumber( const TDesC& aNumber, const TDesC& aValidChars);
    static void ParseInvalidChars( TDes& aNumber, const TDesC& aInvalidChars);
    };

// For source compatibility with S60

/** @deprecated */
inline TBool TulPhoneNumberUtils::ParsePhoneNumber( TDes& aNumber, TInt aType )
	{ return TulPhoneNumberUtils::Normalize(aNumber, static_cast<TPhoneNumberType>(aType)); }
/** @deprecated */
inline TBool TulPhoneNumberUtils::IsValidPhoneNumber( const TDesC& aNumber, TInt aType )
	{ return TulPhoneNumberUtils::IsValid(aNumber, static_cast<TPhoneNumberType>(aType)); }
	
#endif      // __TULPHONENUMBERUTILS_H__
            
