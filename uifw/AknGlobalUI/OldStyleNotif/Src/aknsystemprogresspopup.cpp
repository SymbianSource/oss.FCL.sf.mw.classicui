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
* Description:  Plugin implementation of global progress dialog.
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
#include <AknProgressDialog.h>
#include <eikprogi.h>
#include <notelaf.h>
#include <AknUtils.h>
#include <AknBidiTextUtils.h>
#include "aknsystemprogresspopup.h"
#include "AknNotifyPlugin.hrh"
#include <s32mem.h>
#include <AknNotifySignature.h>
#include "aknnoteattributes.h"
#include <AknsUtils.h>
#include <aknconsts.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknMediatorFacade.h>
#include <aknSDData.h>
#include <SecondaryDisplay/AknSecondaryDisplayDefs.h>
#include "AknAppsKeyCleanup.inl"

const TInt KCharsInTInt = 4; // TInt32 takes 4 chars.

// =============================================================================
// Progress dialog subject.
// =============================================================================

CAknGlobalProgressDialogSubject* CAknGlobalProgressDialogSubject::NewL()
    {
    CAknGlobalProgressDialogSubject* self = new (ELeave) CAknGlobalProgressDialogSubject();   
    CleanupStack::PushL(self);
    self->ConstructL(); 
    CleanupStack::Pop(self);
    return self;
    }

CAknGlobalProgressDialogSubject::CAknGlobalProgressDialogSubject()
:iPending(EFalse)
    {
    iStoredEikonEnv = CEikonEnv::Static();
    }

void CAknGlobalProgressDialogSubject::ConstructL()
    {
    }

CAknGlobalProgressDialogSubject::~CAknGlobalProgressDialogSubject()
    {
    //delete iDlg;
    delete iPrompt;

    Cancel();
    
    // Complete the RMessage if we need to.
    if (iPending)
        {
        iMessage.Complete(KErrDied);
        }
    }

void CAknGlobalProgressDialogSubject::Release()
    {
    delete this;
    }

CAknGlobalProgressDialogSubject::TNotifierInfo CAknGlobalProgressDialogSubject::RegisterL()
    {
    iInfo.iUid = KAknGlobalProgressDialogUid;
    iInfo.iChannel = EAknNotifierChannelProgressDialog;
    iInfo.iPriority = ENotifierPriorityHigh;
    return iInfo;
    }
CAknGlobalProgressDialogSubject::TNotifierInfo CAknGlobalProgressDialogSubject::Info() const
    {
    return iInfo;
    }

TPtrC8 CAknGlobalProgressDialogSubject::StartL(const TDesC8& /*aBuffer*/)
    {
    return KNullDesC8();
    }

void CAknGlobalProgressDialogSubject::StartL(const TDesC8& aBuffer, TInt /*aReplySlot*/, 
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
    TInt iconId = readStream.ReadInt16L();
    TInt iconMaskId = readStream.ReadInt16L();
    TInt finalValue = readStream.ReadInt32L();
    TInt tone = readStream.ReadInt16L();

    // Get prompt text
    TInt promptLength = readStream.ReadInt16L();

    delete iPrompt;
    iPrompt = NULL;

    iPrompt = HBufC::NewL(promptLength + KAknBidiExtraSpacePerLine);
    TPtr promptPtr = iPrompt->Des();
    readStream >> promptPtr;

    // Get image file name.
    TInt imageFileLength = readStream.ReadInt16L();
    TFileName imageFile;
    if (imageFileLength)
        {
        readStream >> imageFile;
        }

    // Get icon file name.
    TInt iconFileLength = readStream.ReadInt16L();
    TFileName iconFile;
    if (iconFileLength)
        {
        readStream >> iconFile;
        }

    // Get icon text.
    TInt iconTextLength = readStream.ReadInt16L();

    HBufC* iconText = NULL;
    if (iconTextLength)
        {
        iconText = HBufC::NewLC(iconTextLength + KAknBidiExtraSpacePerLine);
        TPtr iconTextPtr = iconText->Des();
        readStream >> iconTextPtr;

        // Clip strings to fit in one line each.
        // We also convert them to visual order.
        const CFont* font = iStoredEikonEnv->NormalFont();
        
        TAknLayoutRect layRect;
        TAknLayoutText textLay;
        AknLayoutUtils::TAknCbaLocation cbaLocation(AknLayoutUtils::CbaLocation());
        TInt variety(0);
        if (cbaLocation == AknLayoutUtils::EAknCbaLocationRight)
            {
            variety = 4;
            }
        else if (cbaLocation == AknLayoutUtils::EAknCbaLocationLeft)
            {
            variety = 7;
            }
        else
            {
            variety = 1;
            }
        
        layRect.LayoutRect(iAvkonAppUi->ApplicationRect(), 
            AknLayoutScalable_Avkon::popup_note_window(variety));

        TAknTextLineLayout layLine = AKN_LAYOUT_TEXT_Note_pop_up_window_texts_Line_1(1);
        textLay.LayoutText(layRect.Rect(), layLine);
        TInt clipWidth = textLay.TextRect().Width();

        AknBidiTextUtils::ConvertToVisualAndClipL(iconTextPtr, *font, clipWidth, clipWidth);

        layLine = AKN_LAYOUT_TEXT_Note_pop_up_window_texts_Line_1(4);
        textLay.LayoutText(layRect.Rect(), layLine);

        clipWidth = textLay.TextRect().Width();

        AknBidiTextUtils::ConvertToVisualAndClipL(promptPtr, *font, clipWidth, clipWidth);

        // +1 for '\n'
        iPrompt = iPrompt->ReAllocL(iPrompt->Length() + iconText->Length() + 1);

        promptPtr.Set(iPrompt->Des());
        promptPtr.Append('\n');
        promptPtr.Append(*iconText);
        CleanupStack::PopAndDestroy(iconText);
        }

    TInt skinsMajorImage = readStream.ReadInt32L();
    TInt skinsMinorImage = readStream.ReadInt32L();
    TInt skinsMajorIcon = readStream.ReadInt32L();
    TInt skinsMinorIcon = readStream.ReadInt32L();

    CAknSDData* sddata = 0;
    if (readStream.ReadInt8L())
        {
        sddata = new (ELeave) CAknSDData();
        CleanupStack::PushL(sddata);
        readStream >> *sddata;
        }    

    // Initialize dialog, done before image loading as eases up cleanupstack handling.
    delete iDlg;
    iDlg = NULL;
    iDlg = new (ELeave) CAknProgressDialog(REINTERPRET_CAST(CEikDialog**, &iDlg), ETrue);
    iDlg->SetCallback(this);
    
    if (sddata)
        {
        iDlg->PublishDialogL(sddata->iDialogIdx, sddata->iCategory);
        if (sddata->iAdditionalData)
            {
            CAknMediatorFacade* cover_info = AknMediatorFacade(iDlg);
            if(cover_info)
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
        // progress note identifier is published to the secondary display.
        iDlg->PublishDialogL(EAknUnidentifiedProgressNote, KAknSecondaryDisplayCategory);
        }
        
    if (!iAppsKeySuppressed)
        {
        ((CAknNotifierAppServerAppUi*)(iStoredEikonEnv->EikAppUi()))->SuppressAppSwitching(ETrue);
        }
    CleanupStack::PushL(TCleanupItem(ReleaseAppsKey, 0));    
    
    iDlg->PrepareLC(R_GLOBAL_PROGRESS_DIALOG);

    // Load image.
    CEikImage* image = new (ELeave) CEikImage;
    CleanupStack::PushL(image);

    TAknsItemID id = {0,0};
    
    if (skinsMajorImage||skinsMinorImage||imageFile.CompareF(KAvkonBitmapFile) == 0)
        {
        if (skinsMajorImage||skinsMinorImage)
            {
            id.Set(skinsMajorImage,skinsMinorImage);
            }
        else 
            {
            id = CAknNoteAttributes::GetSkinnedBitmapID(imageId);
            }
        }
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
   
    TRAPD(err, AknsUtils::CreateIconL(
        skin,id,
        bitmap, mask,
        imageFile,
        imageId, imageMaskId ));

    if (!err)
        {
        image->SetPicture(bitmap,mask);        
        }
    else
        {
        CleanupStack::PopAndDestroy(image);
        image = 0;    
        }

    // Load icon.
    CEikImage* icon = new (ELeave) CEikImage;
    CleanupStack::PushL(icon);
    id.Set(0,0);
    
    bitmap = NULL;
    mask = NULL;
    
    if (skinsMajorIcon || skinsMinorIcon || iconFile.CompareF(KAvkonBitmapFile) == 0)
        {
        if (skinsMajorIcon || skinsMinorIcon)
            {
            id.Set(skinsMajorIcon,skinsMinorIcon);
            }
        else 
            {
            id = CAknNoteAttributes::GetSkinnedBitmapID(iconId);
            }
        }

    TRAP(err, AknsUtils::CreateIconL(
        skin,id,
        bitmap, mask,
        iconFile,
        iconId, iconMaskId ));

    if (!err)
        {
        icon->SetPicture(bitmap,mask);        
        }
    else
        {
        CleanupStack::PopAndDestroy(icon);
        icon = 0;    
        }

    // Set icon.
    if (icon)
        {
        iDlg->SetIconL(icon);
        CleanupStack::Pop(icon);
        }

    // Set image.
    if (image)
        {
        iDlg->SetImageL(image);
        CleanupStack::Pop(image);
        }
    
    // Set progress info.
    iProgressInfo = iDlg->GetProgressInfoL();
    iProgressInfo->SetFinalValue(finalValue);
    
    // Set softkeys.
    if (softkeys)
        {
        // If softkeys are given, the resource id must point to a valid resource.
        // Trying to use invalid softkeys can cause panic.
        if (!(iStoredEikonEnv->IsResourceAvailableL(softkeys)))
            {
            User::Leave(KErrArgument);
            }         
        
        iDlg->ButtonGroupContainer().SetCommandSetL(softkeys);
        }

    // If icon text was present, we processed the text ourselves.
    // (Wrapped, truncated, converted from logical to visual.)
    if (iconTextLength)
        {
        iDlg->SetTextProcessing(EFalse);
        }

    // Set label and tone.
    iDlg->SetTextL(*iPrompt);
    iDlg->SetTone((CAknNoteDialog::TTone)tone);
    
    // Execute dialog.
    iDlg->RunLD();
    
    CleanupStack::Pop(); // Apps key cleanup.
    iAppsKeySuppressed = ETrue;     
    
    delete iPrompt;
    iPrompt = NULL;
    
    iPending = ETrue;
    }

void CAknGlobalProgressDialogSubject::Cancel()
    {
    delete iDlg;
    iDlg = NULL;
    TRAP_IGNORE(DialogDismissedL(EAknSoftkeyCancel));
    }

TPtrC8 CAknGlobalProgressDialogSubject::UpdateL(const TDesC8& aBuffer)
    {
    if (!iDlg)
        {
        return KNullDesC8();
        }
        
    // Get parameters.
    SAknNotifierPackage<SAknGlobalProgressDialogParams>* params 
        = (SAknNotifierPackage<SAknGlobalProgressDialogParams>*)aBuffer.Ptr();

    if (aBuffer.Length() < 0 
        || (TUint)aBuffer.Length() < sizeof(SAknNotifierPackage<SAknGlobalProgressDialogParams>)
        || params->iSignature != KAKNNOTIFIERSIGNATURE)
        {
        User::Leave(KErrArgument);
        }

    if (params->iParamData.iCmd == EAknCancelGlobalQuery)
        {
        delete iDlg;
        iDlg = NULL;
        DialogDismissedL(EAknSoftkeyCancel);
        }
    else if (params->iParamData.iCmd == EAknUpdateGlobalQuery)
        {
        // Update current and final value.
        if (params->iParamData.iValue >= 0)
            {
            iProgressInfo->SetFinalValue(params->iParamData.iFinalValue);
            }
            
        iProgressInfo->SetAndDraw(params->iParamData.iValue);

        CAknMediatorFacade* coverData = AknMediatorFacade(iDlg);
        if (coverData)
            {
            coverData->ResetBuffer();
            coverData->BufStream().WriteInt32L(EAknGlobalPDialogValuesUpdate);
            coverData->BufStream().WriteInt32L(params->iParamData.iValue);
            coverData->BufStream().WriteInt32L(params->iParamData.iFinalValue);
            coverData->BufStream().CommitL();
            coverData->PostUpdatedDataL();
            }
        }
    else if (params->iParamData.iCmd == EAknFinishGlobalProgressDialog)
        {
        iDlg->ProcessFinishedL();
        }

    return KNullDesC8();
    }

void CAknGlobalProgressDialogSubject::DialogDismissedL(TInt aButtonId)
    {
    if (iPending)
        {
        iMessage.Complete(aButtonId);
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
