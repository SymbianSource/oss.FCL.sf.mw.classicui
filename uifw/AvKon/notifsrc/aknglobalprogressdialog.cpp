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
* Description:  Implementation of a global progress dialog. See header file
*                for usage example.
*
*/

#include "AknGlobalProgressDialog.h"
#include <AknNotifyStd.h>
#include <AknPanic.h>
#include <s32mem.h>
#include <AknNotifySignature.h>
#include <aknSDData.h>

const TInt KBufferGranularity = 128;

EXPORT_C CAknGlobalProgressDialog* CAknGlobalProgressDialog::NewL()
    {
    CAknGlobalProgressDialog* self = NewLC();
    CleanupStack::Pop();    // self
    return self;
    }

EXPORT_C CAknGlobalProgressDialog* CAknGlobalProgressDialog::NewLC()
    {
    CAknGlobalProgressDialog* self = new(ELeave) CAknGlobalProgressDialog;
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

EXPORT_C CAknGlobalProgressDialog::~CAknGlobalProgressDialog()
    {
    iNotify.Close();
    delete iBuffer;
    delete iIconText;
    delete iIconFile;
    delete iImageFile;
    delete iAknSDData;
    }

EXPORT_C void CAknGlobalProgressDialog::SetIconL( 
    const TDesC& aIconText,
    const TDesC& aIconFile,
    TInt aIconId,
    TInt aIconMaskId )
    {
    delete iIconText;
    iIconText = NULL;
    delete iIconFile;
    iIconFile = NULL;
    iIconText = aIconText.AllocL();
    iIconFile = aIconFile.AllocL();
    iIconId = aIconId;
    iIconMaskId = aIconMaskId;
    }

EXPORT_C void CAknGlobalProgressDialog::SetImageL( 
    const TDesC& aImageFile,
    TInt aImageId,
    TInt aImageMaskId )
    {
    delete iImageFile;
    iImageFile = NULL;
    iImageFile = aImageFile.AllocL();
    iImageId = aImageId;
    iImageMaskId = aImageMaskId;
    }

EXPORT_C void CAknGlobalProgressDialog::ShowProgressDialogL( 
    TRequestStatus& aStatus,
    const TDesC& aPrompt,
    TInt aSoftkeys,
    TInt aFinalValue,
    CAknNoteDialog::TTone aTone)
    {
    delete iBuffer;
    iBuffer = NULL;
    iBuffer = CBufFlat::NewL(KBufferGranularity);

    RBufWriteStream bufStream;
    bufStream.Open(*iBuffer);

    CleanupClosePushL(bufStream);

    bufStream.WriteInt32L(KAKNNOTIFIERSIGNATURE);

    bufStream.WriteInt32L(aSoftkeys);
    bufStream.WriteInt16L(iImageId);
    bufStream.WriteInt16L(iImageMaskId);
    bufStream.WriteInt16L(iIconId);
    bufStream.WriteInt16L(iIconMaskId);
    bufStream.WriteInt32L(aFinalValue);
    bufStream.WriteInt16L(aTone);
    bufStream.WriteInt16L(aPrompt.Length());
    if ( aPrompt.Length() )
        {
        bufStream << aPrompt;
        }
    bufStream.WriteInt16L( iImageFile ? iImageFile->Length() : 0 );
    if (iImageFile && iImageFile->Length())
        {
        bufStream << *iImageFile;
        }
    bufStream.WriteInt16L( iIconFile ? iIconFile->Length() : 0 );
    if (iIconFile && iIconFile->Length())
        {
        bufStream << *iIconFile;
        }
    bufStream.WriteInt16L( iIconText ? iIconText->Length() : 0 );
    if (iIconText && iIconText->Length())
        {
        bufStream << *iIconText;
        }

    bufStream.WriteInt32L(iImageSkinsMajorId);
    bufStream.WriteInt32L(iImageSkinsMinorId);

    bufStream.WriteInt32L(iIconSkinsMajorId);
    bufStream.WriteInt32L(iIconSkinsMinorId);
    
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
    iNotify.StartNotifierAndGetResponse(aStatus, KAknGlobalProgressDialogUid,
        iBufferPtr, iResultBuf);

    CleanupStack::PopAndDestroy();  // bufStream
    }

EXPORT_C void CAknGlobalProgressDialog::UpdateProgressDialog( 
    TInt aValue, 
    TInt aFinalValue )
    {
    iCmd = EAknUpdateGlobalQuery;
    iValue = aValue;
    iFinalValue = aFinalValue;
    UpdateNotifier();
    }

EXPORT_C void CAknGlobalProgressDialog::ProcessFinished()
    {
    iCmd = EAknFinishGlobalProgressDialog;
    UpdateNotifier();
    }

EXPORT_C void CAknGlobalProgressDialog::CancelProgressDialog()
    {
    if (iBuffer)
        {
        iNotify.CancelNotifier(KAknGlobalProgressDialogUid );
        delete iBuffer;
        iBuffer = 0;
        }
    }

void CAknGlobalProgressDialog::UpdateNotifier()
    {
    TPckgBuf<SAknNotifierPackage<SAknGlobalProgressDialogParams> > pckg;
    pckg().iParamData.iCmd = iCmd;
    pckg().iParamData.iValue = iValue;
    pckg().iParamData.iFinalValue = iFinalValue;
    TPckgBuf<TInt> ret;
    iNotify.UpdateNotifier( KAknGlobalProgressDialogUid, pckg, ret);
    }

CAknGlobalProgressDialog::CAknGlobalProgressDialog()
    {
    }

void CAknGlobalProgressDialog::ConstructL()
    {
    User::LeaveIfError(iNotify.Connect());
    }

EXPORT_C void CAknGlobalProgressDialog::SetImageSkinIds( TAknsItemID& aImageId, 
    TAknsItemID& aIconId )
    {
    iImageSkinsMajorId = aImageId.iMajor;
    iImageSkinsMinorId= aImageId.iMinor;

    iIconSkinsMajorId = aIconId.iMajor;
    iIconSkinsMinorId = aIconId.iMinor;
    }
    
EXPORT_C void CAknGlobalProgressDialog::SetSecondaryDisplayData(CAknSDData* aData)
   {
   delete iAknSDData;
   iAknSDData = aData;
   }
    
// End of File
