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
* Description:  Implementation of CAknJapaneseReading class.
*
*/


// INCLUDE FILES
#include "AknJapaneseReading.h"
#include "AknJapaneseReadingDLL.h"
#include <PtiEngine.h>

// EXTERNAL DATA STRUCTURES

// EXTERNAL FUNCTION PROTOTYPES  

// CONSTANTS

// MACROS

// LOCAL CONSTANTS AND MACROS

// MODULE DATA STRUCTURES

// LOCAL FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

// ============================= LOCAL FUNCTIONS ===============================

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknJapaneseReading::CAknJapaneseReading
// Constructor.
// -----------------------------------------------------------------------------
//
CAknJapaneseReading::CAknJapaneseReading()
    : CCoeStatic(KAknJapaneseReadingStaticId)
    {
    }

// -----------------------------------------------------------------------------
// CAknJapaneseReading::~CAknJapaneseReading
// Destructor.
// -----------------------------------------------------------------------------
//
CAknJapaneseReading::~CAknJapaneseReading()
    {
    }

// -----------------------------------------------------------------------------
// CAknJapaneseReading::CreateL
// 
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknJapaneseReading::CreateL(CPtiEngine* aPtiEngine)
    {
    CAknJapaneseReading* self
        = static_cast<CAknJapaneseReading*>
                        (CCoeEnv::Static(KAknJapaneseReadingStaticId));
    if (!self)
        {
        // create singleton
        self = new(ELeave) CAknJapaneseReading;
        }
    self->iPtiEngine = aPtiEngine;
    }

// -----------------------------------------------------------------------------
// CAknJapaneseReading::ReadingTextL
// Return Reading Text when completed string.
// -----------------------------------------------------------------------------
//
EXPORT_C TPtrC CAknJapaneseReading::ReadingTextL()
    {
    CAknJapaneseReading* self = Static();
    if (!self)
        {
        return TPtrC();
        }
    return self->iPtiEngine->ReadingTextL();
    }

// End of File
