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

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <vwsdefpartner.h>
#endif
#include "AknSoftNotifier.h"
#include <s32mem.h>
#include <AknSoftNotificationParameters.h>
#include <AknNotifySignature.h>
#include <aknSDData.h>
#include "aknsoftnoteconsts.h"

const TInt KBufferGranularity = 128;
const TInt KGlobalNoteTextLength = 256;


#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
#include <akntranseffect.h>
#include <akntransitionutils.h>
#include <gfxtranseffect/gfxtranseffect.h>


class CWait;
const TInt KNoteDelayToIdleState = 450000; // 0,45s.

/*
* AknSoftNotifier's extension class
*/
NONSHARABLE_CLASS(CAknSoftNotifierExt): public CBase
    {
    public:
        static CAknSoftNotifierExt* NewL();
        ~CAknSoftNotifierExt();
        void ShowNotifsDelayed( TBool aShow );
        void SetNotifier( CAknSoftNotifier* aNotifier );
        void CancelNotifDelay();
            
    private: // Methods
        CAknSoftNotifierExt();
        void ConstructL();
        TInt DoShowNotifs();
        
    private: // Data
        CAknSoftNotifier* iNotifier;
        CWait* iWait;
        TBool iNotifsShowState;
        
    public:
    friend class CWait;
    
    
    };

/*
* Class used from CAknSoftNotifierExt to create 
* small delay when entering idle state
* Delay is needed for soft notification transition to be shown
*/
NONSHARABLE_CLASS(CWait) : public CTimer
	{
	public:
	    static CWait* NewL();
		void Wait( CAknSoftNotifierExt* aExt, TInt aTimeToWait );
	private:
		CWait();
		void ConstructL();
		void RunL();
	private:
		CAknSoftNotifierExt* iExt;
	};	


CWait* CWait::NewL()
    {
    CWait * self = new(ELeave) CWait;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }
    
void CWait::Wait( CAknSoftNotifierExt* aExt, TInt aTimeToWait )
	{
	iExt = aExt;
	After(aTimeToWait);
	}

CWait::CWait() : CTimer(CActive::EPriorityIdle) 
	{
	CActiveScheduler::Add(this);
	}

void CWait::ConstructL()
    {
    CTimer::ConstructL();
    }
    
void CWait::RunL()
	{
	TInt error = iExt->DoShowNotifs();
	User::LeaveIfError( error );
	}

    
CAknSoftNotifierExt* CAknSoftNotifierExt::NewL()
    {
    CAknSoftNotifierExt * self = new(ELeave) CAknSoftNotifierExt;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    } 
    
CAknSoftNotifierExt::~CAknSoftNotifierExt()
    {
    delete iWait;
    iWait = NULL;
    }
    
void CAknSoftNotifierExt::ShowNotifsDelayed( TBool aShow )
    {
    iNotifsShowState = aShow;
    iWait->Cancel();
    
    if( aShow && iWait )
        {
        iWait->Wait( this, KNoteDelayToIdleState );
        }
    else
        {
        // no delay when exiting idle state
        iWait->Wait( this, 0 );
        }
    }
    
void CAknSoftNotifierExt::SetNotifier( CAknSoftNotifier* aNotifier )
    {
    iNotifier = aNotifier;
    }
    
void CAknSoftNotifierExt::CancelNotifDelay()
    {
    iWait->Cancel();
    }
    
CAknSoftNotifierExt::CAknSoftNotifierExt()
    {
    }

void CAknSoftNotifierExt::ConstructL()
    {
    iWait = CWait::NewL();
    }
    
    
TInt CAknSoftNotifierExt::DoShowNotifs()
    {
    TRAPD( error,iNotifier->PrepareBufferL(ESetIdleState, iNotifsShowState, NULL, EFalse, ETrue));
    return error;
    }
         
    
#endif // RD_UI_TRANSITION_EFFECTS_POPUPS
    
   
    
    

EXPORT_C CAknSoftNotifier* CAknSoftNotifier::NewL()
    {
    CAknSoftNotifier* self = NewLC();
    CleanupStack::Pop();
    return self;
    }

EXPORT_C CAknSoftNotifier* CAknSoftNotifier::NewLC()
    {
    CAknSoftNotifier * self = new(ELeave) CAknSoftNotifier;
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

EXPORT_C CAknSoftNotifier::~CAknSoftNotifier()
    {
    delete iBuffer;
    
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    delete iExt;
#endif
    }

void CAknSoftNotifier::ConstructL()
    {
    CAknNotifyBase::ConstructL();
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    iExt = CAknSoftNotifierExt::NewL();
    iExt->SetNotifier( this );
#endif
    }

EXPORT_C void CAknSoftNotifier::AddNotificationL(TAknSoftNotificationType aType, TPtrC* aText)
    {
    PrepareBufferL(aType, 1, aText, EFalse, ETrue);
    }

EXPORT_C void CAknSoftNotifier::AddNotificationL(TAknSoftNotificationType aType,TInt aCount)
    {
    PrepareBufferL(aType, aCount, NULL, EFalse, ETrue);
    }

EXPORT_C void CAknSoftNotifier::SetNotificationCountL(TAknSoftNotificationType aType, TInt aCount, 
    TPtrC* aText)
    {
    PrepareBufferL(aType, aCount, aText, EFalse, EFalse);
    }

EXPORT_C void CAknSoftNotifier::CancelSoftNotificationL(TAknSoftNotificationType aType)
    {
    PrepareBufferL(aType, 0, NULL, ETrue, EFalse);
    }

CAknSoftNotifier::CAknSoftNotifier() : CAknNotifyBase(KAknSoftNotificationUid)
    {
    }

EXPORT_C void CAknSoftNotifier::SetIdleStateL(TBool aIdleState)
    {
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    iExt->CancelNotifDelay();

    if( CAknTransitionUtils::TransitionsEnabled( AknTransEffect::EComponentTransitionsOff ) &&
        aIdleState )
        {
        // Shows notes in idle with small delay when going to idle, if popup transitions
        // are enabled. This is to secure that note appear transition can be seen.
        iExt->ShowNotifsDelayed( aIdleState );    
        }
    else
        {
        PrepareBufferL(ESetIdleState, aIdleState, NULL, EFalse, ETrue);    
        }
#else
    PrepareBufferL(ESetIdleState, aIdleState, NULL, EFalse, ETrue);
#endif
    }

void CAknSoftNotifier::PrepareBufferL(TAknSoftNotificationType aType, TInt aCount, TPtrC* aText, 
    TBool aCancel, TBool aAddCount, CAknSoftNotificationParameters* aParams)
    {
    delete iBuffer;
    iBuffer = NULL;

    if ( aText && aText->Length() > KGlobalNoteTextLength )
        {
        User::Leave( KErrTooBig );
        }

    iBuffer = CBufFlat::NewL(KBufferGranularity);

    RBufWriteStream bufStream;
    bufStream.Open(*iBuffer);

    CleanupClosePushL(bufStream);

    bufStream.WriteInt32L(KAKNNOTIFIERSIGNATURE);

    bufStream.WriteUint8L(aType);
    bufStream.WriteInt16L(aCount);  // count
    bufStream.WriteUint8L(aCancel); // iscancel
    bufStream.WriteUint8L(aAddCount);   // add

    if (aText)
        {
        bufStream << (*aText);
        }
    else
        {
        bufStream << KNullDesC();
        }

    if (aParams)
        {
        bufStream.WriteInt32L( aParams->iNoteResourceId); // Works as unique ID
        bufStream.WriteInt16L( KAknSoftNotificationCustom ); // parameter type
        
        // If this sequence is changed, remeber also change the reading in notify plugin's side  
        bufStream.WriteInt32L(aParams->iResourceFile->Length());
        bufStream << (*aParams->iResourceFile);
        bufStream.WriteInt32L(aParams->iNoteResourceId);
        bufStream.WriteInt32L(aParams->iPriority);
        bufStream.WriteInt32L(aParams->iSoftkeys);
        bufStream.WriteInt32L(aParams->iTone);
        bufStream.WriteUint32L(aParams->iViewId.iAppUid.iUid);
        bufStream.WriteUint32L(aParams->iViewId.iViewUid.iUid);
        bufStream.WriteUint32L(aParams->iCustomMessageId.iUid);
        bufStream.WriteInt32L(aParams->iAcceptSoftKey);

        bufStream.WriteUint32L(aParams->iPluralViewId.iAppUid.iUid);
        bufStream.WriteUint32L(aParams->iPluralViewId.iViewUid.iUid);
        bufStream.WriteUint32L(aParams->iGroupedTextResourceId);

        if ( aParams->iViewId != KNullViewId )
            {
            bufStream.WriteInt32L(aParams->iViewActivationMsg->Length());
            bufStream << (*aParams->iViewActivationMsg);
            }
        else
            {
            bufStream.WriteInt32L(KErrNotFound);
            }

        // only custrom notes may need to send data to cover ui
        if (SecondaryDisplayData())
            {
            bufStream.WriteInt8L(ETrue);
            bufStream << *(SecondaryDisplayData());
            }
        else
            {
            bufStream.WriteInt8L(EFalse);            
            }
        }

    CleanupStack::PopAndDestroy();  // bufStream

    iBufferPtr.Set(iBuffer->Ptr(0));

    TBuf8<1> resp;
    StartOrUpdateL(iBufferPtr,resp);
    }

EXPORT_C void CAknSoftNotifier::CAknNotifyBase_Reserved()
    {
    }

EXPORT_C void CAknSoftNotifier::AddCustomNotificationL( 
    CAknSoftNotificationParameters& aParams, 
    TInt aCount )
    {
    PrepareBufferL(ECustomSoftNotification, aCount, NULL, EFalse, ETrue, &aParams );
    }

EXPORT_C void CAknSoftNotifier::SetCustomNotificationCountL( 
    CAknSoftNotificationParameters& aParams, 
    TInt aCount )
    {
    PrepareBufferL(ECustomSoftNotification, aCount, NULL, EFalse, EFalse, &aParams );
    }

EXPORT_C void CAknSoftNotifier::CancelCustomSoftNotificationL( 
    CAknSoftNotificationParameters& aParams )
    {
    PrepareBufferL(ECustomSoftNotification, 0, NULL, ETrue, EFalse, &aParams );
    }

// End of File
