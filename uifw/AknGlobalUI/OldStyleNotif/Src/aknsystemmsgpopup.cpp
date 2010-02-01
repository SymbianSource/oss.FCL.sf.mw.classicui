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
* Description:  Plugin implementation of global message query.
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
#include <aknmessagequerydialog.h>
#include <aknmessagequerycontrol.h>
#include "aknsystemmsgpopup.h"
#include <s32mem.h>
#include <uikon/eiksrvui.h>
#include <AknNotifySignature.h>
#include <AknsUtils.h>
#include <aknconsts.h>
#include <aknSDData.h>
#include <AknMediatorFacade.h>
#include <aknnoteattributes.h>
#include <SecondaryDisplay/AknSecondaryDisplayDefs.h>
#include "AknAppsKeyCleanup.inl"

const TInt KCharsInTInt = 4; // TInt32 takes 4 chars.

// =============================================================================
// Message query dialog.
// =============================================================================

CAknMsgQueryNotificationDialog::CAknMsgQueryNotificationDialog(                    
    MAknQueryNotificationCallback* aCallBack,
    CAknMsgQueryNotificationDialog** aSelfPtr,
    HBufC* aMessage,
    TInt aSoftkeys,
    HBufC* aHeader,
    CEikImage* aHeaderImage,
    const TTone aTone) 
: CAknMessageQueryDialog(aTone),
    iSoftkeys(aSoftkeys),
    iCallBack(aCallBack),
    iSelfPtr(aSelfPtr),
    // Maintain these even the base class should do that.
    iMessage(aMessage),
    iHeader(aHeader),
    iHeaderImage(aHeaderImage)
    {
    }

void CAknMsgQueryNotificationDialog::PreLayoutDynInitL()
    {
    // Base call first.      
    CAknMessageQueryDialog::PreLayoutDynInitL();

    if (iMessage)
        {
        STATIC_CAST(CAknMessageQueryControl*, 
            Control(EAknMessageQueryContentId))->SetMessageTextL(iMessage);
            
        STATIC_CAST(CAknMessageQueryControl*, 
            Control(EAknMessageQueryContentId))->SetMopParent(this);
            
        delete iMessage;
        iMessage = NULL;
        }

    CAknPopupHeadingPane* headingPane = STATIC_CAST(CAknPopupHeadingPane*, 
        Control(EAknMessageQueryHeaderId));
        
    if (!headingPane)
        {
        return;
        }
 
    if (iHeader)
        {
        headingPane->SetTextL(*iHeader);
        delete iHeader;
        iHeader = NULL;
        }

    if (iHeaderImage)
        {
        headingPane->SetHeaderImageOwnedL(iHeaderImage);
        iHeaderImage = NULL;
        }
    }

void CAknMsgQueryNotificationDialog::PostLayoutDynInitL()
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
    
    CAknMessageQueryDialog::PostLayoutDynInitL();
    }


CAknMsgQueryNotificationDialog::~CAknMsgQueryNotificationDialog()
    {
    if (iSelfPtr) 
        {
        *iSelfPtr = NULL;
        }

    if (iTimer)
        {
        iTimer->Cancel();
        delete iTimer;
        }

    delete iMessage;
    delete iHeader;
    delete iHeaderImage;
    }

TKeyResponse CAknMsgQueryNotificationDialog::OfferKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode aType)
    {

    if (aKeyEvent.iScanCode == EStdKeyYes)
        {
        return EKeyWasConsumed;
        }
    
    if (aType != EEventKey)
        {
        return EKeyWasNotConsumed;
        }

    return CAknMessageQueryDialog::OfferKeyEventL(aKeyEvent, aType);
    }


TBool CAknMsgQueryNotificationDialog::OkToExitL(TInt aButtonId)
    {
    TInt ret = -1;
    if (aButtonId != EAknSoftkeyCancel)
        {
        ret = aButtonId;
        }
    iCallBack->QueryDismissedL(ret);

    if (ret == -1 || !iDelay)
        {
        return ETrue;
        }
    
    else if (!iTimer) 
        {
        iTimer = CPeriodic::NewL(CActive::EPriorityUserInput);
        iTimer->Start(iDelay,iDelay,TCallBack(DeleteMe, this));
        }
    return EFalse;
    }

TInt CAknMsgQueryNotificationDialog::DeleteMe(TAny* aThis)
    {
    CAknMsgQueryNotificationDialog* me = (CAknMsgQueryNotificationDialog*)aThis;
    delete me;
    return 0;  
    }

void CAknMsgQueryNotificationDialog::CEikDialog_Reserved_1()
    {
    }

void CAknMsgQueryNotificationDialog::CEikDialog_Reserved_2()
    {
    }

void CAknMsgQueryNotificationDialog::CAknDialog_Reserved()
    {
    }

void CAknMsgQueryNotificationDialog::CAknQueryDialog_Reserved()
    {
    }

// =============================================================================
// Message query subject.
// =============================================================================

CAknGlobalMsgQuerySubject* CAknGlobalMsgQuerySubject::NewL()
    {
    CAknGlobalMsgQuerySubject* self = new (ELeave) CAknGlobalMsgQuerySubject(); 
    CleanupStack::PushL(self);
    self->ConstructL(); 
    CleanupStack::Pop(self);
    return self;
    }

CAknGlobalMsgQuerySubject::CAknGlobalMsgQuerySubject()
: iPending(EFalse)
    {
    iStoredEikonEnv = CEikonEnv::Static();
    }

void CAknGlobalMsgQuerySubject::ConstructL()
    {
    }

CAknGlobalMsgQuerySubject::~CAknGlobalMsgQuerySubject()
    {
    //delete iDlg;
    delete iBitmap;
    Cancel();
    
    // Complete the RMessage if we need to.
    if (iPending)
        {
        iMessage.Complete(KErrDied);
        }
    }

void CAknGlobalMsgQuerySubject::Release()
    {
    delete this;
    }

CAknGlobalMsgQuerySubject::TNotifierInfo CAknGlobalMsgQuerySubject::RegisterL()
    {
    iInfo.iUid = KAknGlobalMsgQueryUid;
    iInfo.iChannel = EAknNotifierChannelMsgQuery;
    iInfo.iPriority = ENotifierPriorityHigh;
    return iInfo;
    }

CAknGlobalMsgQuerySubject::TNotifierInfo CAknGlobalMsgQuerySubject::Info() const
    {
    return iInfo;
    }

TPtrC8 CAknGlobalMsgQuerySubject::StartL(const TDesC8& /*aBuffer*/)
    {
    return KNullDesC8();
    }

void CAknGlobalMsgQuerySubject::StartL(const TDesC8& aBuffer, TInt /*aReplySlot*/, 
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
    TInt softkeys = readStream.ReadInt32L();
    TInt imageId = readStream.ReadInt16L();
    TInt imageMaskId = readStream.ReadInt16L();
    TInt tone = readStream.ReadInt16L();

    TInt textLength = readStream.ReadInt16L();
    HBufC* text = HBufC::NewLC(textLength);
    TPtr textPtr = text->Des();
    readStream >> textPtr;

    TInt headerLength = readStream.ReadInt16L();
    HBufC* header = HBufC::NewLC(headerLength);
    TPtr headerPtr = header->Des();
    readStream >> headerPtr;

    TInt imageFileLength = readStream.ReadInt16L();
    TFileName imageFile;
    if (imageFileLength)
        {
        readStream >> imageFile;
        }

    TInt delay = readStream.ReadInt32L();

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
   
    TRAPD(err, AknsUtils::CreateIconL(skin, id, bitmap, mask, imageFile, imageId, imageMaskId));
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
    iDlg = new (ELeave) CAknMsgQueryNotificationDialog(this, &iDlg, text, softkeys, header, 
        image, (CAknQueryDialog::TTone)tone);

    iDlg->SetExitDelay(delay);

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
        // message query identifier is published to the secondary display.
        iDlg->PublishDialogL(EAknUnidentifiedMsgQuery, KAknSecondaryDisplayCategory);
        }        
        
    CleanupStack::Pop(2, text);
    if (!iAppsKeySuppressed) 
        {
        ((CAknNotifierAppServerAppUi*)(iStoredEikonEnv->EikAppUi()))->SuppressAppSwitching(ETrue);
        }

    CleanupStack::PushL(TCleanupItem(ReleaseAppsKey, 0));

#ifdef RD_SCALABLE_UI_V2
    iDlg->SetGloballyCapturing(ETrue); 
#endif

    iDlg->ExecuteLD(R_GLOBAL_MESSAGE_QUERY);
    CleanupStack::Pop(); // Apps key cleanup.

    iAppsKeySuppressed = ETrue;
    iPending = ETrue;
    }

void CAknGlobalMsgQuerySubject::Cancel()
    {
    delete iDlg;
    iDlg = NULL;
    TRAP_IGNORE(QueryDismissedL(EAknSoftkeyCancel));
    }

TPtrC8 CAknGlobalMsgQuerySubject::UpdateL(const TDesC8& aBuffer)
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

void CAknGlobalMsgQuerySubject::QueryDismissedL(TInt aResult)
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
