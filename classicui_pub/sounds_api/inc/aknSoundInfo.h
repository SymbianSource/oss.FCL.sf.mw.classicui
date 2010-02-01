/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Provides API for sound info delivery.
*
*/

#ifndef AKNSOUNDINFO_H
#define AKNSOUNDINFO_H

// INCLUDES
#include <e32base.h>

// DATA TYPES
enum TSoundType
    {
    ESoundTone = 1,
    ESoundFile = 2,
    ESoundSequence = 3
    };

// FORWARD DECLARATIONS
class RWriteStream;

// CLASS DECLARATION
/**
*  Provides structure needed for passing the sound information for applications that create own
*  instances to Media Server.
*
*  @lib Avkon.lib
*  @since S60 2.0
*/
NONSHARABLE_CLASS(CAknSoundInfo) : public CBase
    {
public:
    /**
    * Constructor.
    *
    * @return Pointer to the new instance.
    */
    IMPORT_C static CAknSoundInfo* NewL();

    /**
    * Destructor.
    */
    IMPORT_C ~CAknSoundInfo();

public: // New functions
    /**
    * Not currently implemented.
    */
    IMPORT_C void InternalizeL(RReadStream& aStream);

    /**
    * Not currently implemented.
    */
    IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

public: // Data
    /** Priority of the sound. */
    TInt16 iPriority;

    /** Frequency of the sound. */
    TInt16 iFrequency;

    /** Preference of the sound. */
    TInt iPreference;

    /** Sound file, used with ESoundFile type only. */
    HBufC* iFile;

    /** Duration of the sound. */
    TInt iDuration;

    /** Sequence of the sound, used with ESoundSequence type only. */
    HBufC8* iSequence;

    /** Default volume of the sound. */
    TUint8 iVolume;

    /** Sound type. */
    TSoundType iType;

private:
    /**
    * Default Constructor
    */
    CAknSoundInfo();
    };

#endif // AKNSOUNDINFO_H

// End of file
