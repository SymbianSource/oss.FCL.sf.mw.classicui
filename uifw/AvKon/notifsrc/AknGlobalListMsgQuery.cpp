/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation for a global list message query client API.
*
*/

#include "AknGlobalListMsgQuery.h"
#include <bamdesca.h> // MDesCArray
#include <AknNotifyStd.h>
#include <AknPanic.h>
#include <s32mem.h>
#include <AknNotifySignature.h>
#include <aknSDData.h>

const TInt KBufferGranularity = 128;

EXPORT_C CAknGlobalListMsgQuery* CAknGlobalListMsgQuery::NewL()
    {
    CAknGlobalListMsgQuery* self = NewLC();
    CleanupStack::Pop(self);
    return self;
    }

EXPORT_C CAknGlobalListMsgQuery* CAknGlobalListMsgQuery::NewLC()
    {
    CAknGlobalListMsgQuery* self = new(ELeave) CAknGlobalListMsgQuery;
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

EXPORT_C CAknGlobalListMsgQuery::~CAknGlobalListMsgQuery()
    {
    iNotify.Close();
    delete iBuffer;
    delete iHeading;
    delete iAknSDData;
    }

EXPORT_C void CAknGlobalListMsgQuery::ShowListMsgQueryL( 
    const MDesCArray* aItems,
    TRequestStatus& aStatus,
    const TDesC& aHeaderText,
    const TDesC& aMsgText,
    const TInt aIndex,    
    TInt aSoftKeys,
    TInt aAcceptKeyId,
    TInt aCancelKeyId,
    const TDesC& aHeaderImageFile,    
    TInt aImageId,
    TInt aImageMaskId,
    CAknQueryDialog::TTone aTone)
    {
    iIndex = aIndex;
    const TInt count = aItems->MdcaCount();
    
    SetHeadingL(aHeaderText);

    delete iBuffer;
    iBuffer = NULL;
    iBuffer = CBufFlat::NewL(KBufferGranularity);

    RBufWriteStream bufStream;
    bufStream.Open(*iBuffer);

    CleanupClosePushL(bufStream);

    bufStream.WriteInt32L(KAKNNOTIFIERSIGNATURE);
    bufStream.WriteInt16L(aIndex);

    bufStream.WriteInt16L(count);
    for (TInt ii = 0; ii < count; ii++)
        {
        bufStream << (aItems->MdcaPoint(ii));
        }

    if (iHeading)
        {
        bufStream.WriteInt16L(iHeading->Length());
        bufStream << (*iHeading);
        }
    else // heading is optional
        {
        bufStream.WriteInt16L(KErrNotFound);
        }
        
    // Enable listbox to have message under title.
    bufStream.WriteInt16L(aMsgText.Length());
    bufStream << aMsgText;
    
    bufStream.WriteInt16L(aImageId);
    bufStream.WriteInt16L(aImageMaskId);
    bufStream.WriteInt16L(aTone);
    bufStream.WriteInt16L(aHeaderImageFile.Length());
    if (aHeaderImageFile.Length())
        {
        bufStream << aHeaderImageFile;
        }
    bufStream.WriteInt32L(iSkinsMajorId);
    bufStream.WriteInt32L(iSkinsMinorId); 
    bufStream.WriteInt32L(aSoftKeys);
    bufStream.WriteInt32L(aAcceptKeyId);
    bufStream.WriteInt32L(aCancelKeyId);
     
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
    
    iNotify.StartNotifierAndGetResponse(
        aStatus, 
        KAknGlobalListMsgQueryUid,
        iBufferPtr, 
        iResultBuf);

    CleanupStack::PopAndDestroy(&bufStream);
    }

/**
* Move selection up
*/
EXPORT_C void CAknGlobalListMsgQuery::MoveSelectionUp()
    {
    iCmd = EAknMoveUpGlobalListQuery;
    UpdateListMsgQuery();
    }

/**
* Move selection down
*/
EXPORT_C void CAknGlobalListMsgQuery::MoveSelectionDown()
    {
    iCmd = EAknMoveDownGlobalListQuery;
    UpdateListMsgQuery();
    }

/**
* Select currently selected item in the list
*/
EXPORT_C void CAknGlobalListMsgQuery::SelectItem()
    {
    iCmd = EAknSelectGlobalListQuery;
    UpdateListMsgQuery();
    }

/**
* Cancel the query
*/
EXPORT_C void CAknGlobalListMsgQuery::CancelListMsgQuery()
    {
    if (iBuffer)
        {
        iNotify.CancelNotifier(KAknGlobalListMsgQueryUid);
        delete iBuffer;
        iBuffer = 0;
        }
    }

void CAknGlobalListMsgQuery::UpdateListMsgQuery()
    {
    TPckgBuf<SAknNotifierPackage<SAknGlobalListQueryParams> > pckg;
    pckg().iParamData.iCmd = iCmd;
    TPckgBuf<TInt> ret;
    iNotify.UpdateNotifier(KAknGlobalListMsgQueryUid, pckg, ret);
    }

void CAknGlobalListMsgQuery::SetHeadingL(const TDesC& aHeading)
    {
    delete iHeading;
    iHeading = 0;
    iHeading = aHeading.AllocL();
    }

CAknGlobalListMsgQuery::CAknGlobalListMsgQuery()
    {
    }

void CAknGlobalListMsgQuery::ConstructL()
    {
    User::LeaveIfError(iNotify.Connect());
    }
    
EXPORT_C void CAknGlobalListMsgQuery::SetSecondaryDisplayData(CAknSDData* aData)
   {
   delete iAknSDData;
   iAknSDData = aData;
   }
   
EXPORT_C void CAknGlobalListMsgQuery::SetImageSkinId(const TAknsItemID& aId)
    {
    iSkinsMajorId = aId.iMajor;
    iSkinsMinorId = aId.iMinor;
    }

// End of File
