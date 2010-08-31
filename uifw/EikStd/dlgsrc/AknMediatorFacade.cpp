/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies).
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

#include <eikenv.h>
#include <eikappui.h>
#include <eikapp.h>
#include <coedef.h>
#include <MediatorDomainUIDs.h>
#include <AknNotifyStd.h>
#include <SecondaryDisplay/AknSecondaryDisplayDefs.h>

#include "AknMediatorFacade.h" 
#include "AknMediatorObserver.h"

const TInt KBufferGranularity = 128; // quite big, perhaps

EXPORT_C CAknMediatorFacade* CAknMediatorFacade::NewL(CEikDialog* aDialog)
    {
    CAknMediatorFacade* me = new (ELeave) CAknMediatorFacade(aDialog);
    CleanupStack::PushL(me);
    me->ConstructL();
    CleanupStack::Pop();
    return me;
    }

EXPORT_C CAknMediatorFacade* AknMediatorFacade(const MObjectProvider* aMop)
    {
    CAknMediatorFacade* caps = NULL;
    if( aMop ) 
        {
        const_cast<MObjectProvider*>(aMop)->MopGetObject( caps );
        }    

    return caps;
    }

void CAknMediatorFacade::ConstructL()
    {
    iCommander = CMediatorCommandInitiator::NewL(this);
    iUpdater = CMediatorEventConsumer::NewL(this);
    iBuf = CBufFlat::NewL(KBufferGranularity);    
    iStream.Open(*iBuf);
    }

EXPORT_C void CAknMediatorFacade::IssueCommand()
    {
    if (iDialogIndex == 0)
        return;
    
    __ASSERT_DEBUG(iDialogIndex != KErrNotFound, User::Invariant());
    if (iAppUid == KNullUid)
        {
        iAppUid = ((CEikAppUi*)CEikonEnv::Static()->AppUi())->Application()->AppDllUid();
        }

    // ingnore return value, if this fails we have no feed back channel from cover.
    iUpdater->SubscribeEvent( KMediatorSecondaryDisplayDomain, 
                              iAppUid,
                              iDialogIndex,
                              TVersion(0,0,0));

    // we don't care this return value either.
    iCommander->IssueCommand( KMediatorSecondaryDisplayDomain, 
                              iAppUid,
                              iDialogIndex,
                              TVersion(0,0,0),
                              iBuf->Ptr(0));



    }
    
EXPORT_C void CAknMediatorFacade::CancelCommand()
    {
    if (iDialogIndex == 0)
        {
        return;        
        }
    
    if (iUpdater)
        {
        iUpdater->UnsubscribeEvent( KMediatorSecondaryDisplayDomain, 
                                    iAppUid,
                                    iDialogIndex);        
        }
        
    if (iCommander)
        {
        iCommander->CancelCommand( KMediatorSecondaryDisplayDomain, 
                              iAppUid,
                              iDialogIndex);
        }
    }
    
EXPORT_C void CAknMediatorFacade::ResetBuffer()
    {
    iStream.Release();
    iBuf->Reset();
    iStream.Open(*iBuf);
    }

EXPORT_C void CAknMediatorFacade::SetObserver(MAknDialogMediatorObserver* aObserver)
    {
    iExternalObserver = aObserver;
    }

CAknMediatorFacade::~CAknMediatorFacade()
    {
    if(iExternalObserver)
        {
        iExternalObserver->NotifyMediatorExit();
        }
    // as mediator does not cancel all functionality related to session to be terminated
    // cancel commands manually  
    CancelCommand();
    
    // These will cancel remaining active requests in destructor.    
    delete iCommander;
    delete iUpdater;
    delete iUpdateToCover;
    
    iStream.Close();
    delete iBuf;
    }

void CAknMediatorFacade::MediatorEventL( TUid aDomain,
                         TUid aCategory, 
                         TInt aEventId, 
                         const TDesC8& aData )
    {
    TAknDialogMediatorObserverCommand cmd = EHandleAsNormal;

    if (iExternalObserver)
        {
        cmd = iExternalObserver->MediatorCommandL( aDomain, aCategory, 
                                           aEventId, aData );    
        }

    HandleCommandL(cmd, aData); 
    }

void CAknMediatorFacade::CommandResponseL( TUid aDomain,
                           TUid aCategory, 
                           TInt aCommandId,
                           TInt aStatus, 
                           const TDesC8& aData )
    {
    if (aStatus == KErrNone)
        {
        TAknDialogMediatorObserverCommand cmd = EHandleAsNormal;

        if (iExternalObserver)
            {
            cmd = iExternalObserver->MediatorCommandL( aDomain, aCategory, 
                                               aCommandId, aData );    
            }
        HandleCommandL(cmd, aData);
        }
    }

CAknMediatorFacade::CAknMediatorFacade(CEikDialog* aDialog)
    :iDialogIndex(KErrNotFound),iDialog(aDialog) 
    {
    __ASSERT_ALWAYS(iDialog, User::Invariant());
    }

void CAknMediatorFacade::HandleCommandL(TAknDialogMediatorObserverCommand aCmd, const TDesC8& aData)
    {
    switch (aCmd)
        {   
    case EAcceptDialog:
        {
        iDialog->TryExitL(EEikBidOk); // simulates selection key
        break;
        }
    case ECancelDialog:
        {
        iDialog->TryExitL(EEikBidCancel);
        break;
        }
    case EHandleAsNormal:
        {
        ProcessDataL( aData );
        } // fall through
    case EDoNothingWithThisCommand:
    default:
        break;

        }

    }

void CAknMediatorFacade::ProcessDataL( const TDesC8& aData )
    {
    if (aData.Length() >= 4)
        {
        SAknDialogFeedback* key = (SAknDialogFeedback*)aData.Ptr();

        TInt dialogCommand =  key->iCommandId; // four bytes of data

        if (dialogCommand == KAknMediatorFacade  // for bc though nobody should use this
            || dialogCommand == EAknDialogFeedback)
            {
            TKeyResponse kresp = EKeyWasNotConsumed;
            if (iDialog->ButtonGroupContainer().ButtonGroup() )
                {
                kresp = iDialog->ButtonGroupContainer().ButtonGroup()->AsControl()->OfferKeyEventL(key->iKey, EEventKey);
                }
            if (kresp != EKeyWasConsumed)
                {
                iDialog->OfferKeyEventL(key->iKey, EEventKey); // all we can do
                }
            }
        }
    }
    
EXPORT_C void CAknMediatorFacade::PostUpdatedDataL(TInt aEventId)
    {
    if (iAppUid == KNullUid)
        return; // no commands have been sent before, ignore update event
    
    if (!iUpdateToCover)
        {
        iUpdateToCover = CMediatorEventProvider::NewL();
        }
        
    iUpdateToCover->RaiseEvent( KMediatorSecondaryDisplayDomain,
                           iAppUid, 
                           aEventId!=0?aEventId:iDialogIndex+KAknMediatorUpdateChannelOffset,
                           TVersion(0,0,0), 
                           iBuf->Ptr(0));
    }

// end of file

