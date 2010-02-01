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

#include "AknGlobalConfirmationQuery.h"
#include <AknNotifyStd.h>
#include <AknPanic.h>
#include <AknNotifySignature.h>
#include <aknSDData.h>
#include <s32mem.h>

const TInt KBufferGranularity = 128;

EXPORT_C CAknGlobalConfirmationQuery* CAknGlobalConfirmationQuery::NewL()
    {
    CAknGlobalConfirmationQuery* self = NewLC();
    CleanupStack::Pop();    // self
    return self;
    }

EXPORT_C CAknGlobalConfirmationQuery* CAknGlobalConfirmationQuery::NewLC()
    {
    CAknGlobalConfirmationQuery* self = new(ELeave) CAknGlobalConfirmationQuery;
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

EXPORT_C CAknGlobalConfirmationQuery::~CAknGlobalConfirmationQuery()
    {
    iNotify.Close();
    delete iBuffer;
    delete iAknSDData;
    }

EXPORT_C void CAknGlobalConfirmationQuery::ShowConfirmationQueryL( 
    TRequestStatus& aStatus,
    const TDesC& aPrompt,
    TInt aSoftkeys,
    TInt aAnimation,
    const TDesC& aImageFile,
    TInt aImageId,
    TInt aImageMaskId,
    CAknQueryDialog::TTone aTone,
    TBool aDismissWithAllKeys )
    {
    delete iBuffer;
    iBuffer = NULL;
    iBuffer = CBufFlat::NewL(KBufferGranularity);

    RBufWriteStream bufStream;
    bufStream.Open(*iBuffer);

    CleanupClosePushL(bufStream);

    bufStream.WriteInt32L(KAKNNOTIFIERSIGNATURE);

    if ( aDismissWithAllKeys )
        {
        bufStream.WriteInt8L( ETrue );
        }
    else
        {
        bufStream.WriteInt8L( EFalse );
        }

    bufStream.WriteInt32L(aSoftkeys);
    bufStream.WriteInt32L(aAnimation);
    bufStream.WriteInt16L(aImageId);
    bufStream.WriteInt16L(aImageMaskId);
    bufStream.WriteInt16L(aTone);
    bufStream.WriteInt16L(aPrompt.Length());
    bufStream << aPrompt;
    bufStream.WriteInt16L(aImageFile.Length());
    if (aImageFile.Length())
        {
        bufStream << aImageFile;
        }

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
    iNotify.StartNotifierAndGetResponse(aStatus, KAknGlobalConfirmationQueryUid,
        iBufferPtr, iResultBuf);

    CleanupStack::PopAndDestroy();  // bufStream
    }


EXPORT_C void CAknGlobalConfirmationQuery::UpdateConfirmationQuery( TInt aSoftkeys )
    {
    iSoftkeys = aSoftkeys;
    iCmd = EAknUpdateGlobalQuery;
    TPckgBuf<SAknNotifierPackage<SAknGlobalMsgQueryParams> > pckg;
    pckg().iParamData.iCmd = iCmd;
    pckg().iParamData.iSoftkeys = iSoftkeys;

    TPckgBuf<TInt> ret;
    iNotify.UpdateNotifier( KAknGlobalConfirmationQueryUid, pckg, ret);
    }


EXPORT_C void CAknGlobalConfirmationQuery::CancelConfirmationQuery()
    {
    if (iBuffer)
        {
        iNotify.CancelNotifier(KAknGlobalConfirmationQueryUid);
        delete iBuffer;
        iBuffer = 0;
        }
    }


CAknGlobalConfirmationQuery::CAknGlobalConfirmationQuery()
    {
    }

void CAknGlobalConfirmationQuery::ConstructL()
    {
    User::LeaveIfError(iNotify.Connect());
    }

EXPORT_C void CAknGlobalConfirmationQuery::SetImageSkinId( TAknsItemID& aId )
    {
    iSkinsMajorId = aId.iMajor;
    iSkinsMinorId = aId.iMinor;
    }

EXPORT_C void CAknGlobalConfirmationQuery::SetSecondaryDisplayData(CAknSDData* aData)
   {
   delete iAknSDData;
   iAknSDData = aData;
   }

// End of File
