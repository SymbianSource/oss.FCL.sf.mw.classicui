/*
* Copyright (c) 2003 Nokia Corporation and/or its subsidiary(-ies).
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
*   The file contains constants and methods for the maintenance of date format. 
*   A visually-defined avkon enumeration for the date format is defined.
*   Mapping routines are exported for the mapping either way of Symbian OS's 
*   TDateFormat to the here-defined visual date format
*
*
*/


#ifndef AKNDATEFORMATUTILS_H
#define AKNDATEFORMATUTILS_H

#include <e32std.h>

// CONSTANTS

// DATA TYPES
//
// This enumeration explicitly refers to the visual presentation of the date format
// 
enum TAknVisualDateFormat
    {
    EVisualDayMonthYear=0,
    EVisualMonthDayYear,
    EVisualYearMonthDay
    };

class AknDateFormatUtils
    {  
public:

    /**
    * Maps Symbian's Date format enumeration to the Avkon, visually defined format
    * 
    * @param    aFormat         Date format enumeration as used by TLocale.SetDateFormat();
    * @param    aForceLanguage  If not NULL, this is used as if it were the current language
    * @return                   Avkon-defined visual format enumeration
    */
    IMPORT_C static TAknVisualDateFormat MapSymbianDateFormatToVisualDateFormat(
        TDateFormat aFormat, TLanguage* aForceLanguage  );

    /**
    * Maps Avkon's visually-defined date format to Symbian's Date format enumeration
    * 
    * @param    aFormat         Date format enumeration as used by TLocale.SetDateFormat();
    * @param    aForceLanguage  If not NULL, this is used as if it were the current language
    * @return                   Avkon-defined visual format enumeration
    */
    IMPORT_C static TDateFormat MapVisualDateFormatToSymbianDateFormat(
        TAknVisualDateFormat aFormat , TLanguage* aForceLanguage );

private:

    /**
    * This routine does all the work of looking at ui language, digit type, date separator
    * to determine if the bidi algorithm is going to switch things around visually.
    */
    static TBool DateFieldReOrderingNeeded( TLanguage* aForceLanguage ); 

    /**
    * This routine encodes the standard "western" mapping from visual to TLocale's setting
    */
    static TDateFormat MapWesternVisualDateFormatToSymbianDateFormat(
        TAknVisualDateFormat aFormat );

    /**
    * This routine encodes the standard "western" mapping from TLocale's setting to visual
    */
    static TAknVisualDateFormat MapSymbianDateFormatToWesternVisualDateFormat(
        TDateFormat aFormat );

    };


#endif // AKNDATEFORMATUTILS_H

