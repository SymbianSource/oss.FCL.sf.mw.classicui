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
* Description:  Implementation of visual - Symbian OS date formats for 
*
*/


#include <AknDateFormatUtils.h>

#include <biditext.h>
#include <e32std.h>
#include <AknUtils.h>

/**
* Current implementation of this should work for any RTL language if it sets the 
* digit type to digit types checked for below
*
* It is meant as a patch for S60 2.0, not as a complete solution to the problem of date
* presentation.
*/
TBool AknDateFormatUtils::DateFieldReOrderingNeeded(TLanguage* aForceLanguage )
    {
    TBool reorderingNeeded(EFalse);
    TLocale locale;
    TLanguage language = (aForceLanguage != NULL) ? *aForceLanguage : AknLangUtils::UserLanguage();

    // Reordering needed in case of RTL language, we have arabic digits and if the separator is not 
    // numeric separator.
     if ( TBidiText::ScriptDirectionality( language ) == TBidiText::ERightToLeft )
        {
        TInt digitType = locale.DigitType();
        if ( digitType == EDigitTypeArabicIndic ||
             digitType == EDigitTypeEasternArabicIndic )
            {
            TChar sep( locale.DateSeparator(1) );
            if ( sep.GetBdCategory() != TChar::ECommonNumberSeparator )
                {
                reorderingNeeded = ETrue;
                }
            }
        }
        
    return reorderingNeeded;
    }

TAknVisualDateFormat AknDateFormatUtils::MapSymbianDateFormatToWesternVisualDateFormat(
    TDateFormat aFormat )
    {
    TAknVisualDateFormat visualFormat(EVisualDayMonthYear);
    switch ( aFormat )
        {
        case EDateEuropean:
            visualFormat = EVisualDayMonthYear;
            break;

        case EDateAmerican:
            visualFormat = EVisualMonthDayYear;
            break;

        case EDateJapanese:
            visualFormat = EVisualYearMonthDay;
            break;
        }
    return visualFormat;
    }

TDateFormat AknDateFormatUtils::MapWesternVisualDateFormatToSymbianDateFormat(
    TAknVisualDateFormat aFormat )
    {
    TDateFormat osFormat(EDateEuropean);
    switch( aFormat )
        {
        case EVisualDayMonthYear:
        osFormat = EDateEuropean;
            break;
        case EVisualMonthDayYear:
            osFormat = EDateAmerican;
            break;
        case EVisualYearMonthDay:
            osFormat = EDateJapanese;
            break;
        }
    return osFormat;
    }

EXPORT_C TAknVisualDateFormat AknDateFormatUtils::MapSymbianDateFormatToVisualDateFormat(
    TDateFormat aFormat, TLanguage* aForceLanguage )
    {
    // Get the western mapping first
    TAknVisualDateFormat visualFormat = 
        MapSymbianDateFormatToWesternVisualDateFormat( aFormat );

    if ( DateFieldReOrderingNeeded( aForceLanguage ) )
        {
        if ( visualFormat == EVisualDayMonthYear ) 
            visualFormat = EVisualYearMonthDay;
        else if ( visualFormat == EVisualYearMonthDay )
            visualFormat =  EVisualDayMonthYear;
        }

    return visualFormat;
    }

EXPORT_C TDateFormat AknDateFormatUtils::MapVisualDateFormatToSymbianDateFormat(
    TAknVisualDateFormat aFormat, TLanguage* aForceLanguage ) 
    {
    // Get the western mapping first
    TDateFormat osFormat = 
        MapWesternVisualDateFormatToSymbianDateFormat( aFormat );

    if ( DateFieldReOrderingNeeded( aForceLanguage ) )
        {
        if ( osFormat == EDateEuropean ) 
            osFormat = EDateJapanese;
        else if ( osFormat == EDateJapanese )
            osFormat =  EDateEuropean;
        }
    return osFormat;
    }
