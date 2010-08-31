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
* Description:  AVKON global confirmation query.
*
*/

#include <AknNotifyStd.h>
#include <avkon.rsg>
#include <eikbtgpc.h>
#include <eikenv.h>
#include <avkon.hrh>
#include <bautils.h>
#include <aknnotpi.rsg>
#include <AknQueryDialog.h>
#include <aknQueryControl.h>
#include "aknsystemconfirmationpopup.h"
#include <s32mem.h>
#include <uikon/eiksrvui.h>
#include <AknNotifySignature.h>
#include <AknsUtils.h>
#include <aknconsts.h>

#include "AknAppsKeyCleanup.inl"

#include <AknMediatorFacade.h>
#include <aknSDData.h>
#include <SecondaryDisplay/AknSecondaryDisplayDefs.h>

const TInt KCharsInTInt = 4; // TInt32 takes 4 chars.

// =============================================================================
// Confirmation query dialog.
// =============================================================================

CAknQueryNotificationDialog::CAknQueryNotificationDialog(                    
    MAknQueryNotificationCallback* aCallBack,
    CAknQueryNotificationDialog** aSelfPtr,
    TInt aSoftkeys,
    TInt aAnimation,
    CEikImage* aImage,
    const TTone aTone,
    TBool aEveryKeyDismisses,
    TInt aImageId,
    TInt aMaskId) 
: CAknQueryDialog(aTone),
    iSoftkeys(aSoftkeys),
    iAnimation(aAnimation),
    iImage(aImage),
    iCallBack(aCallBack),
    iSelfPtr(aSelfPtr),
    iEveryKeyDismisses(aEveryKeyDismisses), 
    iImageId(aImageId),
    iMaskId(aMaskId)
    {
    }

void CAknQueryNotificationDialog::PostLayoutDynInitL()
    {
    if (iSoftkeys)
        {
        // If softkeys are given, the resource id must point to a valid resource.
        // Trying to use invalid softkeys can cause panic.
        if (!(iCoeEnv->IsResourceAvailableL(iSoftkeys)))
            {
            User::Leave(KErrArgument);
            }
        
        ButtonGroupContainer().SetCommandSetL(iSoftkeys);
        }
    
    if (iImage || iAnimation)
        {
        CAknQueryControl* control = STATIC_CAST(CAknQueryControl*, ControlOrNull(EGeneralQuery));
        if (control && iImage)
            {
            control->SetImageL(iImage);
            iImage = 0; // Ownership to query.
            }
        else if (control && iAnimation)
            {
            control->SetAnimationL(iAnimation);
            }
        else if (control && iImageId)
            {
            // Bitmaps from avkon skinned in query.
            control->SetImageL(KAvkonBitmapFile, iImageId, iMaskId); 
            }
        }
    CAknQueryDialog::PostLayoutDynInitL();
    }

CAknQueryNotificationDialog::~CAknQueryNotificationDialog()
    {
    if (iImage && iImage->IsPictureOwnedExternally())
        {
        delete ((CApaMaskedBitmap*) iImage->Bitmap());
        }
    
    delete iImage;

    if (iSelfPtr)
        { 
        *iSelfPtr = NULL;
        }
    }

TKeyResponse CAknQueryNotificationDialog::OfferKeyEventL(const TKeyEvent& aKeyEvent, 
    TEventCode aType)
    {
    
    if (aType != EEventKey)
        {
        if (aKeyEvent.iScanCode == EStdKeyYes)
            {
            return EKeyWasConsumed;
            }
        else
            {
            return EKeyWasNotConsumed;    
            }
        }
    
    if (iEveryKeyDismisses)
        {
        TryExitL(EEikBidCancel);
        return EKeyWasConsumed;
        }

    if (aKeyEvent.iScanCode == EStdKeyYes)
        {
        return EKeyWasConsumed;
        }
    
    TInt code = aKeyEvent.iCode;

    switch (code)
        {
        case EKeyOK:
            {
            // If left softkey is empty, disable ok key.
            TInt cmd = ButtonGroupContainer().ButtonGroup()->CommandId(0);
            if (cmd)
                {
                TryExitL(cmd);
                return EKeyWasConsumed;
                }
            }
        }
    
    return CAknQueryDialog::OfferKeyEventL(aKeyEvent, aType);
    }

TBool CAknQueryNotificationDialog::OkToExitL(TInt aButtonId)
    {
    if (!iEveryKeyDismisses && aButtonId == EAknSoftkeyEmpty)
        {
        return EFalse; // R_AKN_SOFTKEYS_EMPTY uses ids :( 
        }

    TInt ret = -1;
    if (aButtonId != EAknSoftkeyCancel)
        {
        ret = aButtonId;
        }
    iCallBack->QueryDismissedL(ret);
    return ETrue;
    }

void CAknQueryNotificationDialog::CEikDialog_Reserved_1()
    {
    }

void CAknQueryNotificationDialog::CEikDialog_Reserved_2()
    {
    }

void CAknQueryNotificationDialog::CAknDialog_Reserved()
    {
    }

void CAknQueryNotificationDialog::CAknQueryDialog_Reserved()
    {
    }

// =============================================================================
// Confirmation query subject.
// =============================================================================

CAknGlobalConfirmationQuerySubject* CAknGlobalConfirmationQuerySubject::NewL()
    {
    CAknGlobalConfirmationQuerySubject* self = new (ELeave) CAknGlobalConfirmationQuerySubject(); 
    CleanupStack::PushL(self);
    self->ConstructL(); 
    CleanupStack::Pop(self);
    return self;
    }

CAknGlobalConfirmationQuerySubject::CAknGlobalConfirmationQuerySubject()
: iPending(EFalse)
    {
    iStoredEikonEnv = CEikonEnv::Static();
    }

void CAknGlobalConfirmationQuerySubject::ConstructL()
    {
    }

CAknGlobalConfirmationQuerySubject::~CAknGlobalConfirmationQuerySubject()
    {
    //delete iDlg;
    Cancel();
    
    // Complete the RMessage if we need to.
    if (iPending)
        {
        iMessage.Complete(KErrDied);
        }
    }

void CAknGlobalConfirmationQuerySubject::Release()
    {
    delete this;
    }

CAknGlobalConfirmationQuerySubject::TNotifierInfo CAknGlobalConfirmationQuerySubject::RegisterL()
    {
    iInfo.iUid = KAknGlobalConfirmationQueryUid;
    iInfo.iChannel = EAknNotifierChannelConfirmationQuery;
    iInfo.iPriority = ENotifierPriorityHigh;
    return iInfo;
    }

CAknGlobalConfirmationQuerySubject::TNotifierInfo CAknGlobalConfirmationQuerySubject::Info() const
    {
    return iInfo;
    }

TPtrC8 CAknGlobalConfirmationQuerySubject::StartL(const TDesC8& /*aBuffer*/)
    {
    return KNullDesC8();
    }

void CAknGlobalConfirmationQuerySubject::StartL(const TDesC8& aBuffer, TInt /*aReplySlot*/, 
    const RMessagePtr2& aMessage)
    {
    if (iPending)
        {
        aMessage.Complete(KErrInUse);
        return;
        }

    RDesReadStream readStream(aBuffer);

    if (aBuffer.Length() < KCharsInTInt || readStream.ReadInt32L() != KAKNNOTIFIERSIGNATURE)
        {
        User::Leave(KErrArgument);
        }

    iMessage = aMessage;
    
    TBool everyKeyDismisses = readStream.ReadInt8L();
    TInt softkeys = readStream.ReadInt32L();
    TInt animation = readStream.ReadInt32L();
    TInt imageId = readStream.ReadInt16L();
    TInt imageMaskId = readStream.ReadInt16L();
    TInt tone = readStream.ReadInt16L();

    TInt textLength = readStream.ReadInt16L();
    HBufC* text = HBufC::NewLC(textLength);
    TPtr textPtr = text->Des();
    readStream >> textPtr;

    TInt imageFileLength = readStream.ReadInt16L();
    TFileName imageFile;
    if (imageFileLength)
        {
        readStream >> imageFile;
        }

    TInt skinsMajor = readStream.ReadInt32L();
    TInt skinsMinor = readStream.ReadInt32L();

    CAknSDData* sddata = 0;
    if (readStream.ReadInt8L())
        {
        sddata = new (ELeave) CAknSDData();
        CleanupStack::PushL(sddata);
        readStream >> *sddata;
        }

    CEikImage* image = new (ELeave) CEikImage;
    CleanupStack::PushL(image);

    TAknsItemID id;
    id.Set(skinsMajor, skinsMinor);
 
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    TRAPD(err, AknsUtils::CreateIconL(
        skin,id,
        bitmap, mask,
        imageFile,
        imageId, imageMaskId));
        
    if (!err)
        {
        image->SetPicture(bitmap, mask);        
        }
    else
        {
        CleanupStack::PopAndDestroy(image);
        image = 0;    
        }
    
    delete iDlg;
    iDlg = NULL;

    // iDlg takes ownership of text buffers.
    iDlg = new (ELeave) CAknQueryNotificationDialog( 
        this, 
        &iDlg, 
        softkeys,
        animation, 
        image, 
        (CAknQueryDialog::TTone)tone,
        everyKeyDismisses, 
        imageId, 
        imageMaskId);

    if (image)
        {
        CleanupStack::Pop(image); 
        }

    if (sddata)
        {
        iDlg->PublishDialogL(sddata->iDialogIdx, sddata->iCategory);
        if (sddata->iAdditionalData)
            {
            CAknMediatorFacade* cover_info = AknMediatorFacade(iDlg);
            if (cover_info)
                {
                cover_info->BufStream() << *(sddata->iAdditionalData);
                cover_info->BufStream().CommitL();
                }
            }
        CleanupStack::PopAndDestroy(sddata);
        }
    else
        {
        // If secondary display data hasn't been defined, then the unidentified
        // confirmation note identifier is published to the secondary display.
        iDlg->PublishDialogL(EAknUnidentifiedConfirmationNote, KAknSecondaryDisplayCategory);
        }
  
    if (!iAppsKeySuppressed)
        {
        ((CAknNotifierAppServerAppUi*)(iStoredEikonEnv->EikAppUi()))->SuppressAppSwitching(ETrue);
        }

    CleanupStack::PushL(TCleanupItem(ReleaseAppsKey, 0));

    iDlg->ExecuteLD(R_GLOBAL_CONFIRMATION_QUERY, *text);

    CleanupStack::Pop(); // Apps key cleanup.
    CleanupStack::PopAndDestroy(text);
    
    iAppsKeySuppressed = ETrue;
    iPending = ETrue;
    }

void CAknGlobalConfirmationQuerySubject::Cancel()
    {
    delete iDlg;
    iDlg = NULL;
    TRAP_IGNORE(QueryDismissedL(EAknSoftkeyCancel));
    }

TPtrC8 CAknGlobalConfirmationQuerySubject::UpdateL(const TDesC8& aBuffer)
    {
    if (!iDlg)
        {
        return KNullDesC8();
        }

    // Get parameters.
    SAknNotifierPackage<SAknGlobalMsgQueryParams>* params 
        = (SAknNotifierPackage<SAknGlobalMsgQueryParams>*)aBuffer.Ptr();

    if (aBuffer.Length() < 0 
        || (TUint)aBuffer.Length() < sizeof(SAknNotifierPackage<SAknGlobalMsgQueryParams>)
        || params->iSignature != KAKNNOTIFIERSIGNATURE)
        {
        User::Leave(KErrArgument);
        }

    if (params->iParamData.iCmd == EAknCancelGlobalQuery)
        {
        delete iDlg;
        iDlg = NULL;
        QueryDismissedL(EAknSoftkeyCancel);
        }
    else
        {
        // Update softkeys, but only if the resource id points to a valid resource.
        // Trying to use invalid softkeys can cause panic.
        if (iStoredEikonEnv->IsResourceAvailableL(params->iParamData.iSoftkeys))
            {
            iDlg->ButtonGroupContainer().SetCommandSetL(params->iParamData.iSoftkeys);
            iDlg->ButtonGroupContainer().DrawNow();

            CAknMediatorFacade* coverData = AknMediatorFacade(iDlg);
            if (coverData)
                {
                SAknIntegerUpdate s = 
                    {
                    EAknGlobalNotifierUpdateSoftkeys,
                    params->iParamData.iSoftkeys
                    };
            
                TPckg<SAknIntegerUpdate> pck(s);
                coverData->ResetBuffer();
                coverData->BufStream() << pck;
                coverData->BufStream().CommitL();
                coverData->PostUpdatedDataL();
                }
            }
        else
            {
            // Invalid softkeys, dismiss query with error code.
            QueryDismissedL(KErrArgument);
            }
        }

    return KNullDesC8();
    }

void CAknGlobalConfirmationQuerySubject::QueryDismissedL(TInt aResult)
    {
    if (iPending)
        {
        iMessage.Complete(aResult);
        }
        
    iPending = EFalse;
    iReturnVal = NULL;
    
    if (iAppsKeySuppressed)
        {
        ((CAknNotifierAppServerAppUi*)(iStoredEikonEnv->EikAppUi()))->SuppressAppSwitching(EFalse);
        }
    iAppsKeySuppressed = EFalse;
    }

// End of file
