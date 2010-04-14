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
* Description:  Plugin implementation of global list query.
*
*/

#include "AknSystemListPopup.h"
#include <AknNotifyStd.h>

#include <avkon.rsg>
#include <eikbtgpc.h>
#include <eikenv.h>
#include <avkon.hrh>
#include <bautils.h>
#include "AknListQueryNotificationDialog.h"
#include <aknnotpi.rsg>
#include <AknGlobalListQuery.h>
#include <s32mem.h>
#include <uikon/eiksrvui.h>
#include <AknNotifySignature.h>

#include <AknMediatorFacade.h>
#include <aknSDData.h>
#include <SecondaryDisplay/AknSecondaryDisplayDefs.h>
 
#include "AknAppsKeyCleanup.inl"

const TInt KListQueryItemLength = 64;
const TInt KCharsInTInt = 4; // TInt32 takes 4 chars.
const TInt KArrayGranularity = 3;

CAknGlobalListQuerySubject* CAknGlobalListQuerySubject::NewL()
    {
    CAknGlobalListQuerySubject* self = new (ELeave) CAknGlobalListQuerySubject(); 
    CleanupStack::PushL(self);
    self->ConstructL(); 
    CleanupStack::Pop(self);
    return self;
    }

CAknGlobalListQuerySubject::CAknGlobalListQuerySubject()
: iPending(EFalse)
    {
    iStoredEikonEnv = CEikonEnv::Static();
    }

void CAknGlobalListQuerySubject::ConstructL()
    {
    }

CAknGlobalListQuerySubject::~CAknGlobalListQuerySubject()
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
    }

void CAknGlobalListQuerySubject::Release()
    {
    delete this;
    }

CAknGlobalListQuerySubject::TNotifierInfo CAknGlobalListQuerySubject::RegisterL()
    {
    iInfo.iUid = KAknGlobalListQueryUid;
    iInfo.iChannel = EAknNotifierChannelList;
    iInfo.iPriority = ENotifierPriorityHigh;
    return iInfo;
    }
    
CAknGlobalListQuerySubject::TNotifierInfo CAknGlobalListQuerySubject::Info() const
    {
    return iInfo;
    }

TPtrC8 CAknGlobalListQuerySubject::StartL(const TDesC8& /*aBuffer*/)
    {
    return KNullDesC8();
    }

void CAknGlobalListQuerySubject::StartL(const TDesC8& aBuffer, TInt /*aReplySlot*/, 
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
    iArray = new (ELeave) CDesCArrayFlat(KArrayGranularity);
    
    TBuf<KListQueryItemLength> arrayItem;

    for (TInt ii = 0; ii < count; ii++)
        {
        readStream >> arrayItem;
        iArray->AppendL(arrayItem);
        }
        
    TInt headingLength = readStream.ReadInt16L();
    delete iHeading;
    iHeading = 0;
    
    if (headingLength != KErrNotFound)
        {
        iHeading = HBufC::NewL(headingLength);
        TPtr ptr = iHeading->Des();
        readStream >> ptr;
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
        
    iDlg = new (ELeave) CAknListQueryNotificationDialog(&iListIndex, this, &iDlg);
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
            CleanupStack::PopAndDestroy();
        
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
        CleanupStack::Pop(); // Ownership transferred to dialog successfully. 
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

    if (!iAppsKeySuppressed)
        {
        ((CAknNotifierAppServerAppUi*)(iStoredEikonEnv->EikAppUi()))->SuppressAppSwitching(ETrue);
        }
    CleanupStack::PushL(TCleanupItem(ReleaseAppsKey, 0));    
    
    if (!iHeading) 
        {
        iDlg->PrepareLC(R_GLOBAL_LIST_QUERY);
        }
    else
        {
        iDlg->PrepareLC(R_GLOBAL_LIST_QUERY_WITH_HEADING);
        iDlg->QueryHeading()->SetTextL(iHeading->Des());
        }
        
    iDlg->SetOwnershipType(ELbmOwnsItemArray);
    iDlg->SetItemTextArray(iArray);
    TInt itemCount = iArray->Count();
    iArray = 0;

    // If the list is not empty, the selection index must point to an existing item. 
    // Otherwise a panic will occur.
    if (itemCount && (iSelectFirst < 0 || iSelectFirst > itemCount - 1))
        {
        User::Leave(KErrArgument);
        }    
    
    CEikListBox* listBox = iDlg->ListBox();
    if (itemCount)
        {
        listBox->SetCurrentItemIndex(iSelectFirst);
        }
    listBox->UpdateScrollBarsL();
   
    iDlg->RunLD();
    
    CleanupStack::Pop(); // Apps key cleanup.
    iAppsKeySuppressed = ETrue;
    iPending = ETrue;
    }

void CAknGlobalListQuerySubject::Cancel()
    {
    delete iDlg;
    iDlg = NULL;
    TRAP_IGNORE(QueryDismissedL(EAknSoftkeyCancel));
    }

TPtrC8 CAknGlobalListQuerySubject::UpdateL(const TDesC8& aBuffer)
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

void CAknGlobalListQuerySubject::QueryDismissedL(TInt aResult)
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
