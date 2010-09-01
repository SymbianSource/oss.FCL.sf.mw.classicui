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
* Description:  Declaration of core part of CAknJapaneseReading class.
*
*/


#ifndef __AKNJAPANESEREADING__H__
#define __AKNJAPANESEREADING__H__

// INCLUDES
#include <e32base.h>
#include <coemain.h>
#include <badesca.h>

// CONSTANTS
const TUid KAknJapaneseReadingStaticId = { 0x101F861C };

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class CPtiEngine;

// CLASS DECLARATION

/**
* CAknJapaneseReading is a part of Japanese FEP.
* If the application needs to get Reading Text, use to this class.
*  
* @lib AknJapaneseReading.lib
* @see CAknJapaneseReading, other application
*/
NONSHARABLE_CLASS(CAknJapaneseReading) : public CCoeStatic
    {
    public: // Constructors and destructor

        /**
        * Destructor.
        */
        virtual ~CAknJapaneseReading();

    public: // New functions

        /**
        * Create this class.
        */
        IMPORT_C static void    CreateL(CPtiEngine* aPtiEngine);

        /**
        * Return Reading Text when completed string.
        *
        * @return reading string, (NULL if it cannot get Reading text from Engine)
        */
        IMPORT_C static TPtrC ReadingTextL();

    public: // Functions from CCoeStatic

    private: // Constructors and destructor

        /**
        * private c++ constructor.
        */
        CAknJapaneseReading();

    private: // New functions

        /**
        * Return this object.
        *
        * @return constructed CAknJapaneseReading object.
        */
        inline static CAknJapaneseReading* Static();

    private:
        CPtiEngine* iPtiEngine;     // not own
    };

#include "AknJapaneseReading.inl"

#endif // __AKNJAPANESEREADING__H__
// End of file
