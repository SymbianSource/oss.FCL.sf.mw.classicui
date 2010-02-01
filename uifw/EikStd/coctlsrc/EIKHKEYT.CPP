/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#include <eikhkeyt.h>
#include <eikpanic.h>
#include <coemain.h>
#include <barsread.h>

EXPORT_C CEikHotKeyTable::CEikHotKeyTable()
    : CArrayFixFlat<SEikHotKey> (4) // granularity of 4
    {
    }

EXPORT_C CEikHotKeyTable::~CEikHotKeyTable()
    {
    }

EXPORT_C TBool CEikHotKeyTable::HotKeyFromCommandId(TInt aCommandId,TInt& aKeycode,TInt& aModifiers) const
    {
    if (Count())
        {
        TInt i=0;
        const SEikHotKey* hotKey=&(*this)[0];
        while (i++<Count())
            {
            if (hotKey->iCommandId==aCommandId)
                {
                if (i<=iNumberPlain)
                    {
                    aKeycode=hotKey->iKeycode;
                    aModifiers=0;
                    }
                else
                    {
                    aKeycode=hotKey->iKeycode-('a'-1);
                    if (i>iNumberPlain+iNumberCtrl)
                        aModifiers=EModifierShift|EModifierCtrl;
                    else
                        aModifiers=EModifierCtrl;
                    }
                return(ETrue);
                }
            hotKey++;
            }
        }
    return(EFalse);
    }

EXPORT_C TInt CEikHotKeyTable::CommandIdFromHotKey(TInt aKeycode,TInt aModifiers) const
    {
	if (aModifiers&EModifierPureKeycode && aModifiers&EModifierCtrl)
		return 0;
    TInt start=0;
    TInt count=0;
    if (!aModifiers || aModifiers==EModifierShift)
        count=iNumberPlain;
    else
        {
        aKeycode+='a'-1;
        if (aModifiers==EModifierCtrl)
            {
            start=iNumberPlain;
            count=iNumberCtrl;
            }
        else if (aModifiers==(EModifierShift|EModifierCtrl))
            {
            start=iNumberPlain+iNumberCtrl;
            count=iNumberShiftCtrl;
            }
        }
    if (count && Count())
        {
        const SEikHotKey* hotKey=&(*this)[start];
        while (count--)
            {
            if (hotKey->iKeycode==aKeycode)
                return(hotKey->iCommandId);
            hotKey++;
            }
        }
    return(0);
    }

EXPORT_C void CEikHotKeyTable::AddItemL(TInt aCommandId,TInt aKeycode,TInt aModifiers)
    {
    TInt pos=0;
    TInt* pNumber=&iNumberPlain;
    switch (aModifiers)
        {
    case 0:
        break;
    case EModifierCtrl:
        pos=iNumberPlain;
        pNumber=&iNumberCtrl;
        break;
    case (EModifierShift|EModifierCtrl):
        pos=iNumberPlain+iNumberCtrl;
        pNumber=&iNumberShiftCtrl;
        break;
    default:
        User::Leave(KErrNotSupported);
        }
    SEikHotKey hotKey;
    hotKey.iCommandId=aCommandId;
    hotKey.iKeycode=aKeycode;
    InsertL(pos+*pNumber,hotKey);
    (*pNumber)++; // after the InsertL succeeds
    }

EXPORT_C void CEikHotKeyTable::RemoveItem(TInt aCommandId)
    {
    TInt i=0;
    FOREVER
        {
        if (i==Count())
            Panic(EEikPanicNoHotKeyToRemove);
        SEikHotKey& hotKey=(*this)[i];
        if (hotKey.iCommandId==aCommandId)
            {
            if (i<iNumberPlain)
                iNumberPlain--;
            else if (i<iNumberPlain+iNumberCtrl)
                iNumberCtrl--;
            else
                iNumberShiftCtrl--;
            break;
            }
        i++;
        }
    Delete(i);
    }

EXPORT_C void CEikHotKeyTable::ConstructFromResourceL(TInt aResourceId)
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader,aResourceId);
    iNumberPlain=reader.ReadInt16();
    if (iNumberPlain)
        {
	    const SEikHotKey* ptr=(const SEikHotKey*)reader.Ptr();
	    reader.Advance(iNumberPlain*sizeof(SEikHotKey));
	    AppendL(ptr,iNumberPlain);
        }
    iNumberCtrl=reader.ReadInt16();
    if (iNumberCtrl)
        {
	    const SEikHotKey* ptr=(const SEikHotKey*)reader.Ptr();
	    reader.Advance(iNumberCtrl*sizeof(SEikHotKey));
	    AppendL(ptr,iNumberCtrl);
        }
    iNumberShiftCtrl=reader.ReadInt16();
    if (iNumberShiftCtrl)
        {
	    const SEikHotKey* ptr=(const SEikHotKey*)reader.Ptr();
	    reader.Advance(iNumberShiftCtrl*sizeof(SEikHotKey));
	    AppendL(ptr,iNumberShiftCtrl);
        }
    CleanupStack::PopAndDestroy();
    }

EXPORT_C void CEikHotKeyTable::Reset()
    {
	iNumberPlain=iNumberCtrl=iNumberShiftCtrl=0;
    CArrayFixFlat<SEikHotKey>::Reset();
    }
