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
* Description: 
*
*/

#include "AknGlobalListQuery.h"
#include <bamdesca.h> // MDesCArray
#include <AknNotifyStd.h>
#include <AknPanic.h>
#include <s32mem.h>
#include <AknNotifySignature.h>
#include <aknSDData.h>

const TInt KBufferGranularity = 128;

EXPORT_C CAknGlobalListQuery* CAknGlobalListQuery::NewL()
    {
    CAknGlobalListQuery* self = NewLC();
    CleanupStack::Pop();    // self
    return self;
    }

EXPORT_C CAknGlobalListQuery* CAknGlobalListQuery::NewLC()
    {
    CAknGlobalListQuery* self = new(ELeave) CAknGlobalListQuery;
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

EXPORT_C CAknGlobalListQuery::~CAknGlobalListQuery()
    {
    iNotify.Close();
    delete iBuffer;
    delete iHeading;
    delete iAknSDData;
    }

EXPORT_C void CAknGlobalListQuery::ShowListQueryL( 
    const MDesCArray* aItems,
    TRequestStatus& aStatus,
    const TInt aIndex)
    {
    iIndex = aIndex;
    const TInt count = aItems->MdcaCount();

    delete iBuffer;
    iBuffer = NULL;
    iBuffer = CBufFlat::NewL(KBufferGranularity);

    RBufWriteStream bufStream;
    bufStream.Open(*iBuffer);

    CleanupClosePushL(bufStream);

    bufStream.WriteInt32L(KAKNNOTIFIERSIGNATURE);

    bufStream.WriteInt16L(aIndex);

    bufStream.WriteInt16L(count);
    for (TInt ii=0; ii<count; ii++)
        {
        bufStream << (aItems->MdcaPoint(ii));
        }

    if ( iHeading )
        {
        bufStream.WriteInt16L(iHeading->Length());
        bufStream << (*iHeading);
        }
    else // heading is optional
        {
        bufStream.WriteInt16L(KErrNotFound);
        }

    if (iAknSDData)
        {
        bufStream.WriteInt8L(ETrue);
        bufStream << *iAknSDData;        
        }
    else 
        {
        bufStream.WriteInt8L(EFalse);            
        }

    iBufferPtr.Set(iBuffer->Ptr(0));
    iNotify.StartNotifierAndGetResponse(aStatus, KAknGlobalListQueryUid,
        iBufferPtr, iResultBuf );

    CleanupStack::PopAndDestroy();  // bufStream
    }


/**
* Move selection up
*/
EXPORT_C void CAknGlobalListQuery::MoveSelectionUp()
    {
    iCmd = EAknMoveUpGlobalListQuery;
    UpdateListQuery();
    }

/**
* Move selection down
*/
EXPORT_C void CAknGlobalListQuery::MoveSelectionDown()
    {
    iCmd = EAknMoveDownGlobalListQuery;
    UpdateListQuery();
    }

/**
* Select currently selected item in the list
*/
EXPORT_C void CAknGlobalListQuery::SelectItem()
    {
    iCmd = EAknSelectGlobalListQuery;
    UpdateListQuery();
    }

/**
* Cancel the list query
*/
EXPORT_C void CAknGlobalListQuery::CancelListQuery()
    {
    if (iBuffer)
        {
        iNotify.CancelNotifier(KAknGlobalListQueryUid);
        delete iBuffer;
        iBuffer = 0;
        }
    }

void CAknGlobalListQuery::UpdateListQuery()
    {
    TPckgBuf<SAknNotifierPackage<SAknGlobalListQueryParams> > pckg;
    pckg().iParamData.iCmd = iCmd;
    TPckgBuf<TInt> ret;
    iNotify.UpdateNotifier( KAknGlobalListQueryUid, pckg, ret);
    }


EXPORT_C void CAknGlobalListQuery::SetHeadingL(const TDesC& aHeading)
    {
    delete iHeading;
    iHeading = 0;
    iHeading = aHeading.AllocL();
    }


CAknGlobalListQuery::CAknGlobalListQuery()
    {
    }

void CAknGlobalListQuery::ConstructL()
    {
    User::LeaveIfError(iNotify.Connect());
    }
    
EXPORT_C void CAknGlobalListQuery::SetSecondaryDisplayData(CAknSDData* aData)
   {
   delete iAknSDData;
   iAknSDData = aData;
   }

// End of File
