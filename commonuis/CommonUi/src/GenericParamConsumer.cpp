/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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


#include "GenericParamConsumer.h"

#include <AiwGenericParam.h>
#include <s32mem.h>

#include "DocConstants.h"


EXPORT_C CAiwGenericParamConsumer::CAiwGenericParamConsumer(CEikApplication& aApp) : CAknDocument(aApp)
{
}

EXPORT_C CAiwGenericParamConsumer::~CAiwGenericParamConsumer()
{
    delete iParams;
}

EXPORT_C void CAiwGenericParamConsumer::RestoreL(const CStreamStore& aStore, const CStreamDictionary& aStreamDic)
{
    RStoreReadStream stream;
    TStreamId id = aStreamDic.At(KUidEmbedInputStream);

    delete iParams;
    iParams = NULL;
    iParams = CAiwGenericParamList::NewL();

    stream.OpenLC(aStore, id);
    iParams->InternalizeL(stream);
    CleanupStack::PopAndDestroy();  // stream

    iStore = const_cast<CStreamStore*>(&aStore);
    iStreamDic = const_cast<CStreamDictionary*>(&aStreamDic);
}

EXPORT_C void CAiwGenericParamConsumer::SetOutputParamsL(const CAiwGenericParamList* aParamList)
{
    if (iStore && iStreamDic && aParamList)
    {
        RStoreWriteStream outStream;
        TStreamId id = outStream.CreateLC(*iStore);
        aParamList->ExternalizeL( outStream );
        iStore->CommitL();
        CleanupStack::PopAndDestroy(); // outStream

        iStreamDic->AssignL(KUidEmbedOutputStream, id);
        outStream.CreateLC(*iStore);
        iStreamDic->ExternalizeL(outStream);
        iStore->CommitL();
        CleanupStack::PopAndDestroy();
    }
}

//  End of File  
