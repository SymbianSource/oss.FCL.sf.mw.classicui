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
* Description:  Plugin implementation of global list message query.
*
*/

#include "AknSystemListMsgPopup.h"
#include <AknNotifyStd.h>
#include <AknsUtils.h>

#include <avkon.rsg>
#include <eikbtgpc.h>
#include <eikenv.h>
#include <avkon.hrh>
#include <bautils.h>
#include "AknListQueryNotificationDialog.h"
#include "AknListMsgQueryNotificationDialog.h"
#include <aknnotpi.rsg>
#include <AknGlobalListMsgQuery.h>
#include <s32mem.h>
#include <uikon/eiksrvui.h>
#include <AknNotifySignature.h>
#include <aknmessagequerycontrol.h>

#include <AknMediatorFacade.h>
#include <aknSDData.h>
#include <SecondaryDisplay/AknSecondaryDisplayDefs.h>
 
#include "AknAppsKeyCleanup.inl"

const TInt KListQueryItemLength = 64;
const TInt KCharsInTInt = 4; // TInt32 takes 4 chars.
const TInt KItemArrayGranularity = 3;
_LIT(KEmptyHeading, " ");

CAknGlobalListMsgQuerySubject* CAknGlobalListMsgQuerySubject::NewL()
    {
    CAknGlobalListMsgQuerySubject* self = new (ELeave) CAknGlobalListMsgQuerySubject(); 
    CleanupStack::PushL(self);
    self->ConstructL(); 
    CleanupStack::Pop(self);
    return self;
    }

CAknGlobalListMsgQuerySubject::CAknGlobalListMsgQuerySubject()
: iPending(EFalse)
    {
    iStoredEikonEnv = CEikonEnv::Static();
    }

void CAknGlobalListMsgQuerySubject::ConstructL()
    {
    }

CAknGlobalListMsgQuerySubject::~CAknGlobalListMsgQuerySubject()
    {
    //delete iDlg;
    Cancel();
    
    // Complete the RMessage if we need to.
    if (iPending)
        {
        iMessage.Complete(KErrDied);
        }

    delete iArray;
    delete iHeading;
    delete iMsgText;
    }

void CAknGlobalListMsgQuerySubject::Release()
    {
    delete this;
    }

CAknGlobalListMsgQuerySubject::TNotifierInfo CAknGlobalListMsgQuerySubject::RegisterL()
    {
    iInfo.iUid = KAknGlobalListMsgQueryUid;
    iInfo.iChannel = EAknNotifierChannelListMsgQuery;
    iInfo.iPriority = ENotifierPriorityHigh;
    return iInfo;
    }
    
CAknGlobalListMsgQuerySubject::TNotifierInfo CAknGlobalListMsgQuerySubject::Info() const
    {
    return iInfo;
    }

TPtrC8 CAknGlobalListMsgQuerySubject::StartL(const TDesC8& /*aBuffer*/)
    {
    return KNullDesC8();
    }

void CAknGlobalListMsgQuerySubject::StartL(const TDesC8& aBuffer, TInt /*aReplySlot*/, 
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
    iSelectFirst = readStream.ReadInt16L();
    TInt count = readStream.ReadInt16L();

    // Create array
    delete iArray;
    iArray = 0;
    iArray = new (ELeave) CDesCArrayFlat(KItemArrayGranularity);
    
    TBuf<KListQueryItemLength> arrayItem;

    for (TInt ii = 0; ii < count; ii++)
        {
        readStream >> arrayItem;
        iArray->AppendL(arrayItem);
        }
        
    TInt headingLength = readStream.ReadInt16L();
    delete iHeading;
    iHeading = 0;
    
    if (headingLength >= 0)
        {
        iHeading = HBufC::NewL(headingLength);
        TPtr ptr = iHeading->Des();
        readStream >> ptr;
        }
    else if (headingLength != KErrNotFound)
        {
        User::Leave(KErrArgument);    
        }
    
    // Enable listbox to have message under title.
    TInt msgTextLength = readStream.ReadInt16L();
    delete iMsgText;
    iMsgText = 0;
    
    if (msgTextLength >= 0)
        {
        iMsgText = HBufC::NewL(msgTextLength);
        TPtr ptrMsg = iMsgText->Des();
        readStream >> ptrMsg;
        }
    else if (msgTextLength != KErrNotFound)        
        {
        User::Leave(KErrArgument);    
        }        
        
    TInt imageId = readStream.ReadInt16L();
    TInt imageMaskId = readStream.ReadInt16L();
    TInt tone = readStream.ReadInt16L();
    TInt imageFileLength = readStream.ReadInt16L();
    TFileName imageFile;
    if (imageFileLength)
        {
        readStream >> imageFile;
        }
     
    TInt skinsMajor = readStream.ReadInt32L();
    TInt skinsMinor = readStream.ReadInt32L();  
    TInt softkeys = readStream.ReadInt32L();
    TInt acceptKeyId = readStream.ReadInt32L();
    TInt cancelKeyId = readStream.ReadInt32L();
    
    if (!softkeys)
        {
        softkeys = R_AVKON_SOFTKEYS_OK_CANCEL__OK;
        }
        
    // Accept key cannot be EAknSoftkeyCancel and cancel key cannot be EAknSoftkeyOk.
    if (acceptKeyId == EAknSoftkeyCancel || cancelKeyId == EAknSoftkeyOk)
        {
        User::Leave(KErrArgument);
        }
        
    CAknSDData* sddata = 0;
    if (readStream.ReadInt8L())
        {
        sddata = new (ELeave) CAknSDData();
        CleanupStack::PushL(sddata);
        readStream >> *sddata;
        }
   
    delete iDlg;
    iDlg = NULL;
        
    iDlg = new (ELeave) CAknListMsgQueryNotificationDialog(
        &iListIndex, 
        this, 
        &iDlg, 
        acceptKeyId, 
        cancelKeyId);
        
    iDlg->SetTone(tone);
    
    if (sddata)
        {
        CArrayFixFlat<TInt>* array = 0;
        CleanupStack::PushL(array); // even as null
        if (sddata->iAdditionalData && 
            sddata->iAdditionalData->Length() > 2*sizeof(TInt32)) // command id and count
            {
            RDesReadStream strm(*sddata->iAdditionalData);
            CleanupClosePushL(strm);
            TInt count = strm.ReadInt32L(); // recycling...
            if (count == EAknListQueryItemsInfo)
                {
                count = strm.ReadInt32L();
                array = new (ELeave) CArrayFixFlat<TInt>(1);
                for (TInt i = 0; i < count; i++)
                    {
                    array->AppendL(strm.ReadInt32L());
                    }
                }   
            CleanupStack::PopAndDestroy(&strm);
        
            // Tidy additional data so that there will not be two item arrays.
            TInt bytesToRemove = (count + 2) * 4;
            HBufC8* newDes = 0;
            if (bytesToRemove != sddata->iAdditionalData->Length())
                {
                newDes = sddata->iAdditionalData->Mid(bytesToRemove).AllocL();                
                }           
            delete sddata->iAdditionalData;
            sddata->iAdditionalData = newDes;
            }
            
        iDlg->PublishDialogL(sddata->iDialogIdx, sddata->iCategory, array);
        CleanupStack::Pop(array); // Ownership transferred to dialog successfully.
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
        // list query identifier is published to the secondary display.
        iDlg->PublishDialogL(EAknUnidentifiedListQuery, KAknSecondaryDisplayCategory);
        }        
        
    CEikImage* image = new (ELeave) CEikImage;
    CleanupStack::PushL(image);
    TAknsItemID id;
    id.Set(skinsMajor, skinsMinor);
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TRAPD(err, AknsUtils::CreateIconL(skin, id, bitmap, mask, imageFile, imageId, imageMaskId));

    // Enable listbox to have message under title.
    if (!err)
        {
        image->SetPicture(bitmap,mask);        
        }
    else
        {
        CleanupStack::PopAndDestroy(image);
        image = 0;    
        }

    if (!iMsgText)
        {
        iMsgText = KNullDesC().AllocL();
        }
        
    if (!iHeading || !iHeading->Length())
        {
        delete iHeading;
        iHeading = NULL;
        iHeading = KEmptyHeading().AllocL();
        }        

    if (!iAppsKeySuppressed)
        {
        ((CAknNotifierAppServerAppUi*)(iStoredEikonEnv->EikAppUi()))->SuppressAppSwitching(ETrue);
        }
        
    CleanupStack::PushL(TCleanupItem(ReleaseAppsKey, 0));
    
    iDlg->PrepareLC(R_GLOBAL_LIST_MSG_QUERY);
    iDlg->MessageBox()->SetMessageTextL(iMsgText);

    CAknListQueryControl* listControl = iDlg->ListControl();
    CAknPopupHeadingPane* head = listControl->Heading();
    head->SetHeaderImageOwnedL(image);
    head->SetTextL(iHeading->Des());

    iDlg->SetOwnershipType(ELbmOwnsItemArray);
    iDlg->SetItemTextArray(iArray);
    TInt itemCount = iArray->Count();
    iArray = 0;
    
    // The selection index must point to an existing item. Otherwise a panic will occur.
    if (iSelectFirst < 0 || iSelectFirst > itemCount - 1)
        {
        User::Leave(KErrArgument);
        }

    CEikListBox* listBox = iDlg->ListBox();
    listBox->SetCurrentItemIndex(iSelectFirst);
    listBox->UpdateScrollBarsL();
    
    // If softkeys are given, the resource id must point to a valid resource.
    // Trying to use invalid softkeys can cause panic.
    if (!(iStoredEikonEnv->IsResourceAvailableL(softkeys)))
        {
        User::Leave(KErrArgument);
        }    
    iDlg->ButtonGroupContainer().SetCommandSetL(softkeys);
    
    iDlg->RunLD();
    CleanupStack::Pop(); // Apps key cleanup.
    
    if (image)
        {
        CleanupStack::Pop(image);
        }
            
    iAppsKeySuppressed = ETrue;
    iPending = ETrue;
    }

void CAknGlobalListMsgQuerySubject::Cancel()
    {
    delete iDlg;
    iDlg = NULL;
    TRAP_IGNORE(QueryDismissedL(EAknSoftkeyCancel));
    }

TPtrC8 CAknGlobalListMsgQuerySubject::UpdateL(const TDesC8& aBuffer)
    {
    if (!iDlg)
        {
        return KNullDesC8();
        }

    // Get parameters.
    SAknNotifierPackage<SAknGlobalListQueryParams>* params 
        = (SAknNotifierPackage<SAknGlobalListQueryParams>*)aBuffer.Ptr();

    if (aBuffer.Length() < 0 
        || (TUint)aBuffer.Length() < sizeof(SAknNotifierPackage<SAknGlobalListQueryParams>)
        || params->iSignature != KAKNNOTIFIERSIGNATURE)
        {
        User::Leave(KErrArgument);
        }

    TInt cmd = params->iParamData.iCmd;
    TKeyEvent keyEvent;
    keyEvent.iRepeats = 0;
    TEventCode eventType = EEventKey;
    switch (cmd)
        {
        case EAknCancelGlobalQuery:
            delete iDlg;
            iDlg = NULL;
            QueryDismissedL(EAknSoftkeyCancel);
            return KNullDesC8();
        case EAknMoveDownGlobalListQuery:
            keyEvent.iCode = EKeyDownArrow;
            break;
        case EAknMoveUpGlobalListQuery:
            keyEvent.iCode = EKeyUpArrow;
            break;
        case EAknSelectGlobalListQuery:
            keyEvent.iCode = EKeyOK;
            break;
        default:
            return KNullDesC8();
        }
        
    iDlg->OfferKeyEventL(keyEvent, eventType);

    return KNullDesC8();
    }

void CAknGlobalListMsgQuerySubject::QueryDismissedL(TInt aResult)
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
