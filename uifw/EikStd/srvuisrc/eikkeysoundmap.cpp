/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  EikSrv keysound map.
*
*/

#include "eikkeysoundmap.h"
#include <avkon.hrh>

const TInt KEikKeySoundMapGranularity = 4;
const TInt KEikSKeyGranularity = 16;

// class TSkey - SKey definition
// Keycode and Repeat are stored as a single code, to enable fast searching
void TSKey::Set(TInt aKeyCode, TInt aRepeatType, TInt aSid)
    {
    iSid = aSid;
    iKeyCode = aKeyCode + (aRepeatType << 16);
    }
    
// ===============================   
// CEikKeySoundMap implementation.
// ===============================

CEikKeySoundMap* CEikKeySoundMap::NewL()
    {
    CEikKeySoundMap* self = new(ELeave)CEikKeySoundMap();
    return self;
    }

CEikKeySoundMap::~CEikKeySoundMap()
    {
    }

CEikKeySoundMap::CEikKeySoundMap()
:CArrayFixFlat<TSKey>(KEikSKeyGranularity)
    {
    }

void CEikKeySoundMap::InternalizeL(RReadStream& aStream, TInt aItems, TInt aUid)
    {
    for (TInt ii=0; ii<aItems; ii++)
        {
        TInt sid = aStream.ReadInt16L();
        if (sid < 1000)
            {
            sid = (aUid << 16) + sid;
            }
        TInt key = aStream.ReadUint16L();
        TInt type = aStream.ReadInt8L();
        TSKey sKey;
        sKey.Set(key, type, sid);
        TKeyArrayFix sidKey(_FOFF(TSKey, iKeyCode), ECmpTInt);
        InsertIsqL(sKey, sidKey);
        }
    }

TBool CEikKeySoundMap::Find(TSKey& aKey)
    {
    TKeyArrayFix sidKey(_FOFF(TSKey, iKeyCode), ECmpTInt);
    TInt index;
    if (FindIsq(aKey, sidKey, index) == 0)
        {
        aKey.iSid = At(index).iSid;
        return ETrue;
        }
    return EFalse;
    }

TInt CEikKeySoundMap::ContextResourceId()
    {
    return iContextResourceId;  
    }

void CEikKeySoundMap::SetContextResourceId(TInt aContextResId)
    {
    iContextResourceId = aContextResId; 
    }

// =================================   
// CEikKeySoundStack implementation.
// =================================

CEikKeySoundStack* CEikKeySoundStack::NewL()
    {
    CEikKeySoundStack* self = new(ELeave)CEikKeySoundStack();
    return self;
    }

CEikKeySoundStack::~CEikKeySoundStack()
    {
    ResetAndDestroy();
    }

CEikKeySoundStack::CEikKeySoundStack()
:CArrayPtrFlat<CEikKeySoundMap>(KEikKeySoundMapGranularity)
    {
    }

TBool CEikKeySoundStack::Find(TInt aScanCode, TInt aRepeat, TInt& aSid)
    {
    TSKey key;
    // Decide on key-repeat type to check for
    if (aRepeat == 0)
        {
        key.Set(aScanCode, ESKeyTypeShort, 0);
        }
    else
        {
        if (iPreviousRepeat == 0)
            {
            key.Set(aScanCode, ESKeyTypeLong, 0);
            }
        else
            {
            key.Set(aScanCode, ESKeyTypeRepeat, 0);
            }
        }

    iPreviousRepeat = aRepeat;

    // Check in top layer
    TInt index = Count();
    while (index)
        {
        index--;
        CEikKeySoundMap* map = At(index);
        if (map->Find(key))
            {
            if (key.iSid == EAvkonSIDNoSound)
                return EFalse;
            else if (key.iSid == EAvkonSIDDefaultSound)
                {
                // Go direct to play default sound
                index = 1;
                continue;
                }
            else
                {
                aSid = key.iSid;
                return ETrue;
                }
            }
        }
    return EFalse;
    }

