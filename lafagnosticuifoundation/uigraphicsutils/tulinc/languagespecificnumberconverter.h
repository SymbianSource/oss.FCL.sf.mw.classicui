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



#ifndef LANGUAGESPECIFICNUMBERCONVERTER_H
#define LANGUAGESPECIFICNUMBERCONVERTER_H

//  INCLUDES
#include <e32cmn.h>

/*
LanguageSpecificNumberConverter API offers methods for converting

- European digits to Arabic-Indic, Eastern Arabic-Indic, Devanagari or Thai 
  digits based on existing digit type setting.
- Arabic-Indic, Eastern Arabic-Indic and Devanagari digits to European digits.

API also offers method for checking if conversion of digits needed.
All methods are static.

@internalComponent
@released 
*/
class LanguageSpecificNumberConverter
    {
public:
    static void Convert(TDes &aDes);
    static void ConvertToWesternNumbers(TDes &aDes);
    static TBool IsConversionNeeded();
    };

#endif      // LANGUAGESPECIFICNUMBERCONVERTER_H
            
// End of File
