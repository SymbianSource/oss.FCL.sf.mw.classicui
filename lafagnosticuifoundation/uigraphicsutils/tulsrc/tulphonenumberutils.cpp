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
#include    <tulphonenumberutils.h>


// CONSTANTS
// Number matching constants
// Note: Space represents all whitespaces in these constants
_LIT(KPlainValidChars, "+1234567890()- ./");
_LIT(KPlainCharsToParse, "()- ./");
_LIT(KContactCardValidChars, "+1234567890()-pw#* ./");
_LIT(KContactCardCharsToParse, " ./");
_LIT(KPhoneClientValidChars, "+1234567890()-pw#* ./");
_LIT(KPhoneClientCharsToParse, "()- ./");
_LIT(KSMSNumberValidChars, "+1234567890()- ./*");

// DEFINES
const TInt KPhoneNoUtilsMinNumbers  = 1;
const TInt KPhoneNoUtilsMaxNumbers  = 48; // Maximum phone number supported in Contacts
                                          // see dependent test case t_phonenumberutils.cpp when changing this 

// ---------------------------------------------------------
// Phone number parsing methods
// ---------------------------------------------------------

/**
This method is meant for internal use of Phone Parser. 
Check if string is a valid phone number
@param aNumber Number which will be checked
@param aValidChars Characters that are valid for the number.
          Note: Some chars have special rules. See Address Tokenizer UI specification for more info.
@return ETrue if the number was valid, otherwise EFalse.
*/
TBool TulPhoneNumberUtils::IsValidPhoneNumber(const TDesC& aNumber, const TDesC& aValidChars)
    {
    TInt TotalNumbers = 0;
    TInt State = 1;
    TInt openBrackets = 0;
    TBool isWhiteSpaceValid = EFalse;
    // EndStates is a bitfield where each bit value 1 represents
    // a valid end state.
    TInt32 EndStates = (1L << 4) | (1L << 7) | (1L << 10) | (1L << 15) | (1L << 17) | 
        (1L << 18) | (1L << 20) | (1L << 21) | (1L << 22);

    // Check that if space was valid -> all whitespaces are valid
    if (aValidChars.Locate(' ') != KErrNotFound)
        {
        isWhiteSpaceValid = ETrue;
        }


    for(TInt i=0; i < aNumber.Length(); i++)
        {
            TChar C = aNumber[i];
            if (aValidChars.Locate(C) == KErrNotFound)
                {
                // Space represents all whitespaces in valid chars
                if (!(C.IsSpace() && isWhiteSpaceValid))
                    {
                    return EFalse;
                    }
                }
            // White spaces are skipped
            if (C.IsSpace() || C == '.')
                {
                continue;
                }

            // Brackets are skipped
            if (C == '(')
                {
                if (i == aNumber.Length() - 1)
                    { // cannot be the last char
                    return EFalse;
                    }
                openBrackets++;
                continue;
                }
            else if (C == ')')
                {
                if (i == 0)
                    { // cannot be the first char
                    return EFalse;
                    }
                openBrackets--;
                continue;
                }

            // The numbers are counted
            if (C.IsDigit())
                {
                TotalNumbers++;
                }

            // State transitions
            switch(State)
                {
                case 1:
                    if (C == '+')
                        State = 6;
                    else if (C.IsDigit())
                        State = 10;
                    else if (C == '*' || C == '#')
                        State = 9;
                    else
                        return EFalse;
                    break;
                case 4:
                    if (C == '-' || C == 'p' || C == 'w' || C=='/')
                        State = 5;
                    else if (C == '*' || C == '#')
                        State = 9;
                    else if (C.IsDigit())
                        State = 4;
                    else
                        return EFalse;
                    break;
                case 5:
                    if (C.IsDigit())
                        State = 4;
                    else
                        return EFalse;
                    break;
                case 6:
                    if (C.IsDigit())
                        State = 10;
                    else if (C == '*' || C == '#')
                        State = 18;
                    else
                        return EFalse;
                    break;
                case 9:
                    if (C.IsDigit())
                        State = 4;
                    else if (C != '*' && C != '#')
                       return EFalse;
                    break;
                case 10:
                    if (C == '-' || C == 'p' || C == 'w' || C == '/')
                        State = 11;
                    else if (C == '*' || C == '#')
                        State = 18;
                    else if (!C.IsDigit())
                        return EFalse;
                    break;
                case 11:
                    if (C.IsDigit())
                        State = 10;
                    else
                        return EFalse;
                    break;
                case 18:
                    if (C == '*' || C == '#')
                        State = 18;
                    else if (C.IsDigit())
                        State = 10;
                    else
                        return EFalse;
                    break;
                default:
                	break;
                }
        }

    if (TotalNumbers < KPhoneNoUtilsMinNumbers || TotalNumbers > KPhoneNoUtilsMaxNumbers)
        {
        return EFalse;
        }

    // Check that we left the state machine
    // in a correct end state.
    if ((EndStates & (1L << State)) && openBrackets == 0)
        {
        return ETrue;
        }
    return EFalse;

    }

/**
Checks if string is a valid phone number.
This method checks if the supplied phone number is a valid phone
number of the supplied type.

@param aNumber whose validity will be checked.
@param aType  is the type of the supplied phone number.
@return ETrue if the supplied phone number is a valid number of the 
supplied type. Otherwise EFalse.
*/
EXPORT_C TBool TulPhoneNumberUtils::IsValid(const TDesC& aNumber, TPhoneNumberType aType)
    {
    TPtrC validChars;

    switch (aType)
        {
        case EPlainPhoneNumber:
            {
            validChars.Set(KPlainValidChars);
            break;
            }
        case EContactCardNumber:
            {
            validChars.Set(KContactCardValidChars);
            break;
            }
        case EPhoneClientNumber:
            {
            validChars.Set(KPhoneClientValidChars);
            break;
            }
		case ESMSNumber:
			{
			validChars.Set(KSMSNumberValidChars);
			break;
			}
        default:
            validChars.Set(KNullDesC);
        }
    return IsValidPhoneNumber(aNumber, validChars);
    }

/**
This method is meant for internal use of Phone Parser.
Parses invalid characters from a string
@param aNumber Number which will be parsed.
@param aInvalidChars Characters that are invalid.
*/
void TulPhoneNumberUtils::ParseInvalidChars(TDes& aNumber, const TDesC& aInvalidChars)
    {
    TBool parseWhiteSpaces = EFalse;
    // If a space needs to be parsed, all whitespaces should be parsed
    if (aInvalidChars.Locate(' ') != KErrNotFound)
        {
        parseWhiteSpaces = ETrue;
        }
    for (TInt i = 0; i < aNumber.Length(); i++)
        {
        if ((aInvalidChars.Locate(aNumber[i]) != KErrNotFound) ||
             ((STATIC_CAST(TChar,aNumber[i])).IsSpace() && parseWhiteSpaces))
            {
            aNumber.Delete(i,1);
            i--;
            }
        }
    }

/**
Parses the supplied phone number. This method removes irrelevant 
characters and white spaces from the supplied phone number. Allowed
characters are determined by phone number type.

@param aNumber will be checked and parsed. After returning contains
		the parsed number if the supplied phone number was a valid phone 
		number. If the number was not valid no parsing will be done.
@param aType is the type of the supplied phone number.
@return ETrue if the supplied phone number is a valid number of the
supplied type and the parsing succeeds. Otherwise EFalse.
*/
EXPORT_C TBool TulPhoneNumberUtils::Normalize(TDes& aNumber,  TPhoneNumberType aType)
    {
    if (!IsValid(aNumber, aType))
        {
        return EFalse;
        }
    TPtrC charsToParse;

    switch (aType)
        {
        case EPlainPhoneNumber:
		case ESMSNumber:
            {
            charsToParse.Set(KPlainCharsToParse);
            break;
            }
        case EContactCardNumber:
            {
            charsToParse.Set(KContactCardCharsToParse);
            break;
            }
        case EPhoneClientNumber:
            {
            charsToParse.Set(KPhoneClientCharsToParse);
            break;
            }
        }
    ParseInvalidChars(aNumber, charsToParse);
    
    return ETrue;
    }

//  End of File  
