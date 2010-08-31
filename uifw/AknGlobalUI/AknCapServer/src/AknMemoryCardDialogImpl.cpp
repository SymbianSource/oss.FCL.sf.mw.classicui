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

#include <AknQueryDialog.h>
#include <aknmemorycardui.rsg>
#include <StringLoader.h>
#include <aknsoundsystem.h>
#include <AknNotifyStd.h>
#include <SecondaryDisplay/AknSecondaryDisplayDefs.h>
#include "AknCapServerEntry.h"
#include "AknCapServerDefs.h"
#include "AknMemoryCardDialogImpl.h"

class CAknCodeQuery: public CAknTextQueryDialog
    {
public:
    CAknCodeQuery(
        TDes& aDataText, 
        const CAknTextQueryDialog::TTone& aTone = CAknTextQueryDialog::ENoTone);
        
    TBool OkToExitL(TInt aButtonId);
    void TryExit(TInt aButtonId); 
    void SetObserver(CAknCodeQuery** aSelf, CAknMMCPasswordRequester* aObserver );
    ~CAknCodeQuery(){};
    
private:
    CAknMMCPasswordRequester* iObserver;
    CAknCodeQuery** iSelf;
    };

CAknMMCPasswordRequester::CAknMMCPasswordRequester()
    {
    }

CAknMMCPasswordRequester* CAknMMCPasswordRequester::NewL()
    {
    CAknMMCPasswordRequester* self = new (ELeave) CAknMMCPasswordRequester();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(); //self
    return self;
    }

void CAknMMCPasswordRequester::ConstructL()
    {
    iResFileLdr.AddResourceFileL();
    }

CAknMMCPasswordRequester::~CAknMMCPasswordRequester()
    {
    if (iQuery)
        {
        delete iQuery;
        CompleteAllMessages(KErrDied);
        }

    iResFileLdr.DeleteResourceFile();

    delete iPrompt;
    iPrompt = NULL;
    
    iMessages.Close();
    }

void CAknMMCPasswordRequester::ClientExit( TInt aClientID, TBool aCompleteWithCancel )
    {
    for(TInt i = iMessages.Count()-1; i >= 0; i--)
        {
        if (iMessages[i].iClientId == aClientID)
            {
            if (aCompleteWithCancel)
                {
                iMessages[i].iMessage.Complete(KErrCancel);
                }
            iMessages.Remove(i);
            break;
            }
        }
    }
    
void CAknMMCPasswordRequester::CompleteAllMessages(TInt aReason)
   {
   for(TInt i = iMessages.Count()-1; i >= 0; i--)
        {
        iMessages[i].iMessage.Complete(aReason);
        iMessages.Remove(i);
        }
    }

void CAknMMCPasswordRequester::AppendQueueItemL(const RMessagePtr2& aMessage, TInt aClientID)
    {
    if (!aClientID)
        {
        // recursive call for start (there must be active message before this can occur)
        __ASSERT_ALWAYS(iMessages.Count(), User::Invariant());
        return; 
        }
    for(TInt i = iMessages.Count()-1; i >= 0; i--)
        {
        if (iMessages[i].iClientId == aClientID)
            {
            User::Leave(KErrAlreadyExists);
            }
        }
    User::LeaveIfError(iMessages.Append(TMessageWithClientId(aMessage, aClientID)));
    }   

void CAknMMCPasswordRequester::StartL(TInt aDrive, TBool aStore, const RMessagePtr2& aMessage, 
    TInt aClientID)
    {
    // Will leave if same client tries to activate new request while old pending, basically should
    // panic the client.
    AppendQueueItemL(aMessage, aClientID); 
    
    if (iQuery)
        {
        return;
        }

    iStore = aStore;
    iDriveNumber = aDrive;
    
    SetPromptL();

    iPassWd.FillZ(); // this is safe as we are derived from 
                     // CBase and this is done for every unlock operation
    iPassWd.Zero();
    
    iQuery = new (ELeave) CAknCodeQuery(iPassWd);
    iQuery->PrepareLC(R_MMC_PASSWORD_QUERY);
    iQuery->SetObserver(&iQuery,this);

    if (iPrompt)
        {
        iQuery->SetPromptL(*iPrompt);
        }
    
    CAknKeySoundSystem* sounds = iAvkonAppUi->KeySounds();
    // we are assuming that there is no need to bring sounds forwards more than once per operation
    if (iNumberOfAttempts == 0 && sounds ) 
        {
        sounds->BringToForeground();
        }

    iQuery->PublishDialogL(EAknMemoryCardQuery);
    iQuery->RunLD();
    // block apps key after it is sure that OkToExitL will be called for query
    ((CAknCapAppServerAppUi*)iAvkonAppUi)->SuppressAppSwitchingL(EAknAppsKeyBlockAddCount, 0);
    }

void CAknMMCPasswordRequester::Cancel(TInt aClientID)
    {
    if ( iQuery )
        {
        if (iMessages.Count() == 1)
            {
            iQuery->TryExit( EEikBidCancel ); // completes the message        
            }
        else
            {
            ClientExit(aClientID, ETrue );
            }
        }
    }

void CAknMMCPasswordRequester::SetPromptL()
    {
    delete iPrompt;
    iPrompt = NULL;

    if ( iNumberOfAttempts > 0 ) 
        {
        iPrompt = StringLoader::LoadL(R_QTN_MEM_CARD_UNLOCK_ERROR); 
        }
    else 
        {
        iPrompt = StringLoader::LoadL(R_QTN_MEM_CARD_UNLOCK_PROMPT);
        }
    }

void CAknMMCPasswordRequester::UnlockCard(TBool aAccept)
    {
    if ( aAccept ) 
        {
        TMediaPassword p;
        p.FillZ(KMaxMediaPassword); // not sure if fileserver uses buffer length correctly
        p.Zero();

        const TUint8 *pt8Src = reinterpret_cast<const TUint8 *>(iPassWd.Ptr());
        // We use this to check whether there is something else than zeros in ttext8 array left
        const TUint16 *pt16Src = iPassWd.Ptr();

        for (TInt j = 0; j < KMaxMediaPassword / 2 && pt16Src[j]; ++j)
            {
            p.Append(pt8Src[j << 1]);
            p.Append(pt8Src[(j << 1) + 1]);
            }

        iNumberOfAttempts++;
        TInt err = CCoeEnv::Static()->FsSession().UnlockDrive(iDriveNumber,p,ETrue);
#ifdef _DEBUG
        RDebug::Print(_L("CAknMMCPasswordRequester::Ulock ret: %D"),err);
#endif
        if (err == KErrNone || err == KErrAlreadyExists)
            {
            CompleteAllMessages(KErrNone);
            iNumberOfAttempts = 0;
            }
        else 
            {
            // borrow top most message, it is not used anyway                
            TRAPD (err, StartL(iDriveNumber,iStore,iMessages[0].iMessage)); 
            if (err)
                {
                CompleteAllMessages(err); // To ensure that old instance of query will be deleted. 
                }
            iNumberOfAttempts = 0;
            return;
            }
        }
    else // user or system cancel 
        {
        CompleteAllMessages(KErrCancel);
        iNumberOfAttempts = 0;
        }
    }

CAknCodeQuery::CAknCodeQuery(TDes& aDataText, const CAknTextQueryDialog::TTone& aTone)
    :CAknTextQueryDialog(aDataText, aTone)
    {
    }

TBool CAknCodeQuery::OkToExitL(TInt aButtonId)
    {
    TBool result = (aButtonId == EAknSoftkeyOk||aButtonId == EEikBidOk);

    if ( result )
        {
        CAknQueryControl* control = QueryControl();
        if (control)
            {
            control->GetText(iDataText);
            }
        }
    (*iSelf) = 0;

    iObserver->UnlockCard( result ); // synch, ie. query will be deleted after this returns !
    ((CAknCapAppServerAppUi*)iAvkonAppUi)->SuppressAppSwitchingL(EAknAppsKeyBlockDecreaseCount, 0);
    return ETrue;
    }
        
void CAknCodeQuery::SetObserver(CAknCodeQuery** aSelf, CAknMMCPasswordRequester* aObserver )
    {
    iObserver = aObserver;
    iSelf = aSelf;
    }

void CAknCodeQuery::TryExit(TInt aButtonId)
    { 
    TRAP_IGNORE( TryExitL(aButtonId));
    }

// End of file
