/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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

#include <AknNotifyStd.h>
#include <SecondaryDisplay/AknSecondaryDisplayDefs.h>
#include <s32mem.h>
#include "aknSDData.h"

EXPORT_C void CAknSDData::ExternalizeL(RWriteStream& aStream) const
    {
    aStream.WriteInt32L(iCategory.iUid);
    aStream.WriteInt32L(iDialogIdx);
    if (iAdditionalData)
        {
        aStream.WriteInt32L(iAdditionalData->Length());
        aStream << *iAdditionalData;            
        }
    else 
        {
        aStream.WriteInt32L(KErrNotFound);              
        }    
    }
        
EXPORT_C void CAknSDData::InternalizeL(RReadStream& aStream)
    {
    delete iAdditionalData;
    iAdditionalData = 0;

    iCategory.iUid = aStream.ReadInt32L();
    iDialogIdx = aStream.ReadInt32L();
    TInt size = aStream.ReadInt32L();
    if (size != KErrNotFound )
        {
        iAdditionalData = HBufC8::NewL(size);
        TPtr8 ptr (iAdditionalData->Des());
        aStream >> ptr;
        }
    }

EXPORT_C void CAknSDData::InsertGlobalListQueryItemIdsL(RArray<TInt>& aIdArray)
    {
    TInt count = aIdArray.Count();
    if (count == 0)
        {
        return; // no use to waste mem and time to post nothing
        }
    
    TInt previousLength = iAdditionalData?iAdditionalData->Length():0;
        
    HBufC8* newBuf = HBufC8::NewLC((count+2)*4+previousLength);
    TPtr8 ptr = newBuf->Des();
    RDesWriteStream strm(ptr);
    CleanupClosePushL(strm);
    strm.WriteInt32L(EAknListQueryItemsInfo);
    strm.WriteInt32L(count);
    for(TInt i = 0;i < count; i++)
        {
        strm.WriteInt32L(aIdArray[i]);
        }

    if (previousLength)
        {
        strm << *iAdditionalData;        
        }
        
    strm.CommitL();
    CleanupStack::PopAndDestroy(); // close stream
    
    CleanupStack::Pop(); // new buf
    delete iAdditionalData;
    iAdditionalData = newBuf;    
    }
    
// End of file 
