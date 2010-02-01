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

#include "AknGlobalMsgQuery.h"
#include <AknNotifyStd.h>
#include <AknPanic.h>
#include <AknNotifySignature.h>
#include <aknSDData.h>
#include <s32mem.h>

const TInt KBufferGranularity = 128;

EXPORT_C CAknGlobalMsgQuery* CAknGlobalMsgQuery::NewL()
    {
    CAknGlobalMsgQuery* self = NewLC();
    CleanupStack::Pop();    // self
    return self;
    }

EXPORT_C CAknGlobalMsgQuery* CAknGlobalMsgQuery::NewLC()
    {
    CAknGlobalMsgQuery* self = new(ELeave) CAknGlobalMsgQuery;
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

EXPORT_C CAknGlobalMsgQuery::~CAknGlobalMsgQuery()
    {
    CancelMsgQuery();
    iNotify.Close();
    delete iBuffer;
    delete iAknSDData;
    }

EXPORT_C void CAknGlobalMsgQuery::ShowMsgQueryL( 
    TRequestStatus& aStatus,
    const TDesC& aMsgText,
    TInt aSoftkeys,
    const TDesC& aHeaderText,
    const TDesC& aHeaderImageFile,
    TInt aImageId,
    TInt aImageMaskId,
    CAknQueryDialog::TTone aTone )
    {
    delete iBuffer;
    iBuffer = NULL;
    iBuffer = CBufFlat::NewL(KBufferGranularity);

    RBufWriteStream bufStream;
    bufStream.Open(*iBuffer);

    CleanupClosePushL(bufStream);

    bufStream.WriteInt32L(KAKNNOTIFIERSIGNATURE);

    bufStream.WriteInt32L(aSoftkeys);
    bufStream.WriteInt16L(aImageId);
    bufStream.WriteInt16L(aImageMaskId);
    bufStream.WriteInt16L(aTone);
    bufStream.WriteInt16L(aMsgText.Length());
    bufStream << aMsgText;
    bufStream.WriteInt16L(aHeaderText.Length());
    bufStream << aHeaderText;
    bufStream.WriteInt16L(aHeaderImageFile.Length());
    if (aHeaderImageFile.Length())
        {
        bufStream << aHeaderImageFile;
        }
    bufStream.WriteInt32L(iDelay);

    bufStream.WriteInt32L(iSkinsMajorId);
    bufStream.WriteInt32L(iSkinsMinorId); 
    
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
    iNotify.StartNotifierAndGetResponse(aStatus, KAknGlobalMsgQueryUid,
        iBufferPtr, iResultBuf);

    CleanupStack::PopAndDestroy();  // bufStream
    }

EXPORT_C void CAknGlobalMsgQuery::UpdateMsgQuery( TInt aSoftkeys )
    {
    iSoftkeys = aSoftkeys;
    iCmd = EAknUpdateGlobalQuery;
    TPckgBuf<SAknNotifierPackage<SAknGlobalMsgQueryParams> > pckg;
    pckg().iParamData.iCmd = iCmd;
    pckg().iParamData.iSoftkeys = iSoftkeys;

    TPckgBuf<TInt> ret;
    iNotify.UpdateNotifier( KAknGlobalMsgQueryUid, pckg, ret);
    }


EXPORT_C void CAknGlobalMsgQuery::CancelMsgQuery()
    {
    if (iBuffer)
        {
        iNotify.CancelNotifier(KAknGlobalMsgQueryUid);
        delete iBuffer;
        iBuffer = 0;
        }
    }


EXPORT_C void CAknGlobalMsgQuery::SetExitDelay(TInt aDelay)
    {
    iDelay = aDelay; // basicallyt this method could be inline
    }


CAknGlobalMsgQuery::CAknGlobalMsgQuery()
    {
    }

void CAknGlobalMsgQuery::ConstructL()
    {
    User::LeaveIfError(iNotify.Connect());
    }

EXPORT_C void CAknGlobalMsgQuery::SetImageSkinId( TAknsItemID& aId )
    {
    iSkinsMajorId = aId.iMajor;
    iSkinsMinorId = aId.iMinor;
    }
    
EXPORT_C void CAknGlobalMsgQuery::SetSecondaryDisplayData(CAknSDData* aData)
   {
   delete iAknSDData;
   iAknSDData = aData;
   }
    
// End of File
