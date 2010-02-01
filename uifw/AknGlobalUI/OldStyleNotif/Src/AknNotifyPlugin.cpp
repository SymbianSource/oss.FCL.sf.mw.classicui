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


#include "AknNotifyPlugin.h"
#include <AknNotifyStd.h>

#include <eikenv.h>
#include <eikspane.h>
#include <avkon.hrh>
#include <eikspane.h>
#include <aknappui.h>

#include <bautils.h> // For NearestLanguageFile
#include <aknnotpi.rsg>

#include <AknNotifySignature.h>
#include <s32mem.h>
#include <e32capability.h>
#include <eiksrvsp.h>
#include "aknstatuspanedatapublisher.h"

const TInt KIndicatorTap = 0xFFFF;

void CAknMediatorEvent::RaiseEvent(TInt aId, const TDesC8& aBuf )
    {
    TInt err(0);
    if (iImpl)
        {
        if (iArray.Find(aId) == KErrNotFound)
            {
            err = iImpl->RegisterEvent( 
                KMediatorSecondaryDisplayDomain,
                KAknSecondaryDisplayCategory, 
                aId,
                TVersion(0,0,0),
                TCapabilitySet(ECapabilityReadDeviceData));
                
            if (!err)                
                {
                iArray.Append(aId);
                }
            }
            
        if (!err)
            { // ignore possible errors from now on...
            iImpl->RaiseEvent( 
                KMediatorSecondaryDisplayDomain,
                KAknSecondaryDisplayCategory, 
                aId,
                TVersion(0,0,0), 
                aBuf);
            }
        }
    }

NONSHARABLE_CLASS(CAknIndicatorData): public CBase
    {
public:
    void HandleIndicatorChanged(TInt aIndicator, TInt aState)
        {
        TInt index = KErrNotFound;    
        for (TInt i = 0; i < iArray.Count(); i++)
            {
            if (iArray[i].iIndicator == aIndicator)
                {
                index = i;
                break;
                }
            }
        if (index == KErrNotFound)
            {
            const SAknSmallIndicatorData data=
                {
                aIndicator, aState
                };
            if (aState != EAknIndicatorStateOff)
                {
                iArray.Append(data); // ignore return value
                }
            }
        else
            {
            if (aState == EAknIndicatorStateOff)
                {
                iArray.Remove(index);
                }
            else
                {
                iArray[index].iIndicatorState = aState;
                }    
            }    
        }
        
    void ExternalizeL(RWriteStream& aStream) const
        {
        TInt count = iArray.Count();
        aStream.WriteInt16L(count);
        for (TInt i = 0; i < count; i++)
            {
            aStream.WriteInt32L(iArray[i].iIndicator);
            aStream.WriteInt32L(iArray[i].iIndicatorState);
            }
        }
        
    ~CAknIndicatorData()
        {
        iArray.Close();
        }

    RArray<SAknSmallIndicatorData> iArray;
    };


void CAknPopupNotifierSubject::Release()
    {
    delete this;
    }

CAknPopupNotifierSubject::TNotifierInfo CAknPopupNotifierSubject::RegisterL()
    {
    iInfo.iUid=KAknPopupNotifierUid;
    iInfo.iChannel=KAknPopupNotifierUid;            // made up uid
    iInfo.iPriority=ENotifierPriorityVHigh;
    return iInfo;
    }

CAknPopupNotifierSubject::TNotifierInfo CAknPopupNotifierSubject::Info() const
    {
    return iInfo;
    }

TPtrC8 CAknPopupNotifierSubject::StartL(const TDesC8& aBuffer)
    {
    PopupL(aBuffer);
    return KNullDesC8();
    }

void CAknPopupNotifierSubject::StartL(const TDesC8& aBuffer, TInt /*aReplySlot*/, 
    const RMessagePtr2& aMessage)
    {
    PopupL(aBuffer);
    aMessage.Complete(EEikNotExtRequestCompleted);
    }

void CAknPopupNotifierSubject::Cancel()
    {
    }

TPtrC8 CAknPopupNotifierSubject::UpdateL(const TDesC8& aBuffer)
    {
    PopupL(aBuffer);
    return KNullDesC8();
    }

CAknPopupNotifierSubject* CAknPopupNotifierSubject::NewL()
    {
    CAknPopupNotifierSubject* self=new (ELeave) CAknPopupNotifierSubject();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

CAknPopupNotifierSubject::CAknPopupNotifierSubject()
    {
    }

void CAknPopupNotifierSubject::ConstructL()
    {
    }

void CAknPopupNotifierSubject::PopupL(const TDesC8& aBuffer)
    {
    TPtrC msg(reinterpret_cast<const TUint16*>(aBuffer.Ptr()), aBuffer.Length()/2);
    CEikonEnv::Static()->InfoWinL(_L("popup"), msg);
    }

void CAknSignalNotifierSubject::Release()
    {
    delete this;
    }

CAknSignalNotifierSubject::TNotifierInfo CAknSignalNotifierSubject::RegisterL()
    {
    iInfo.iUid=KAknSignalNotifierUid;
    iInfo.iChannel=KAknSignalNotifierUid;
    iInfo.iPriority=ENotifierPriorityVHigh;
    return iInfo;
    }

CAknSignalNotifierSubject::TNotifierInfo CAknSignalNotifierSubject::Info() const
    {
    return iInfo;
    }

TPtrC8 CAknSignalNotifierSubject::StartL(const TDesC8& aBuffer)
    {
    HandleSignalMessageL(aBuffer);
    return KNullDesC8();
    }

void CAknSignalNotifierSubject::StartL(const TDesC8& aBuffer, TInt /*aReplySlot*/, 
    const RMessagePtr2& aMessage)
    {
    HandleSignalMessageL(aBuffer);
    aMessage.Complete(EEikNotExtRequestCompleted);
    }

void CAknSignalNotifierSubject::Cancel()
    {
    }

TPtrC8 CAknSignalNotifierSubject::UpdateL(const TDesC8& aBuffer)
    {
    HandleSignalMessageL(aBuffer);
    return KNullDesC8();
    }

CAknSignalNotifierSubject* CAknSignalNotifierSubject::NewL(CAknMediatorEvent* aEvent)
    {
    CAknSignalNotifierSubject* self=new (ELeave) CAknSignalNotifierSubject();
    CleanupStack::PushL(self);
    self->iEvent = aEvent;
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

CAknSignalNotifierSubject::CAknSignalNotifierSubject()
    {
    }

CAknSignalNotifierSubject::~CAknSignalNotifierSubject()
    {
    }

void CAknSignalNotifierSubject::ConstructL()
    {
    }

void CAknSignalNotifierSubject::HandleSignalMessageL(const TDesC8& aBuffer)
    {
    SAknNotifierPackage<SAknSignalNotifyParams>* params = 
        (SAknNotifierPackage<SAknSignalNotifyParams>*)aBuffer.Ptr();
        
    if ( aBuffer.Length() < 0 
        || (TUint)aBuffer.Length() < sizeof(SAknNotifierPackage<SAknSignalNotifyParams>) 
        || params->iSignature != KAKNNOTIFIERSIGNATURE )
        {
        User::Leave( KErrArgument );
        }
    SAknSignalNotifyParams sParams = params->iParamData; //  safe

    CEikServStatusPane* ssp = static_cast<CEikServStatusPane*>(CEikStatusPaneBase::Current());
    CAknStatusPaneDataPublisher* publisher = ssp->iDataPublisher;
    
    if ( sParams.iValue != EAknSignalStateNotChanged )
        {
        publisher->SetSignalLevel(params->iParamData.iValue);
        }
        
    if ( sParams.iGprsState != EAknSignalGprsIndicatorBgTypeWipe && 
         sParams.iGprsState != EAknNaviPaneBackgroundTypeSolid &&
         sParams.iGprsState >= 0 )    
        {               
        publisher->SetSignalIcon( sParams.iGprsState );       
        }   
        
    publisher->PublishDataL();  

    TPckgBuf<SAknSignalNotifyParams> buf(sParams);
    iEvent->RaiseEvent(EAknSignalIndicatorSDInfo, buf );
    }

void CAknBatteryNotifierSubject::Release()
    {
    delete this;
    }

CAknBatteryNotifierSubject::TNotifierInfo CAknBatteryNotifierSubject::RegisterL()
    {
    iInfo.iUid=KAknBatteryNotifierUid;
    iInfo.iChannel=KAknBatteryNotifierUid;
    iInfo.iPriority=ENotifierPriorityVHigh;
    return iInfo;
    }

CAknBatteryNotifierSubject::TNotifierInfo CAknBatteryNotifierSubject::Info() const
    {
    return iInfo;
    }

TPtrC8 CAknBatteryNotifierSubject::StartL(const TDesC8& aBuffer)
    {
    HandleBatteryMessageL(aBuffer);
    return KNullDesC8();
    }

void CAknBatteryNotifierSubject::StartL(const TDesC8& aBuffer, TInt /*aReplySlot*/, 
    const RMessagePtr2& aMessage)
    {
    HandleBatteryMessageL(aBuffer);
    aMessage.Complete(EEikNotExtRequestCompleted);
    }

void CAknBatteryNotifierSubject::Cancel()
    {
    }

TPtrC8 CAknBatteryNotifierSubject::UpdateL(const TDesC8& aBuffer)
    {
    HandleBatteryMessageL(aBuffer);
    return KNullDesC8();
    }

CAknBatteryNotifierSubject* CAknBatteryNotifierSubject::NewL(CAknMediatorEvent* aEvent)
    {
    CAknBatteryNotifierSubject* self=new (ELeave) CAknBatteryNotifierSubject();
    CleanupStack::PushL(self);
    self->iEvent = aEvent;
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

CAknBatteryNotifierSubject::CAknBatteryNotifierSubject()
    {
    }

CAknBatteryNotifierSubject::~CAknBatteryNotifierSubject()
    {
    }

void CAknBatteryNotifierSubject::ConstructL()
    {
    }

void CAknBatteryNotifierSubject::HandleBatteryMessageL(const TDesC8& aBuffer)
    {
    SAknNotifierPackage<SAknBatteryNotifyParams>* params = 
        (SAknNotifierPackage<SAknBatteryNotifyParams>*)aBuffer.Ptr();

    if ( aBuffer.Length() < 0 
        || (TUint)aBuffer.Length() < sizeof(SAknNotifierPackage<SAknBatteryNotifyParams>) 
        || params->iSignature != KAKNNOTIFIERSIGNATURE )
        {
        User::Leave( KErrArgument );
        }

    CEikServStatusPane* ssp = static_cast<CEikServStatusPane*>(CEikStatusPaneBase::Current());
    CAknStatusPaneDataPublisher* publisher = ssp->iDataPublisher;
    switch ( params->iParamData.iType )
        {
        case SAknBatteryNotifyParams::ESetValue:
            {
            publisher->SetBatteryLevel(params->iParamData.iValue);
            break;
            }
        case SAknBatteryNotifyParams::ERecharge:
            {
            publisher->SetRecharge(ETrue);
            break;
            }
        case SAknBatteryNotifyParams::EStopRecharge:
            {
            publisher->SetRecharge(EFalse);
            break;
            }
        case SAknBatteryNotifyParams::ENoRecharge:
            {
            publisher->SetRecharge(EFalse);
            break;
            }
        case SAknBatteryNotifyParams::ESetState:
            {
            publisher->SetBatteryIcon( params->iParamData.iBatteryState );
            break;
            }
        default:
            break;
        }
    publisher->PublishDataL();  

    TPckgBuf<SAknBatteryNotifyParams> buf(params->iParamData );
    iEvent->RaiseEvent(EAknBatteryIndicatorSDInfo, buf);
    }

TInt CAknBatteryNotifierSubject::TickerCallback(TAny* aThis)
    {
    return static_cast<CAknBatteryNotifierSubject*>(aThis)->DoTick();
    }

TInt CAknBatteryNotifierSubject::DoTick()
    {
    return ETrue;
    }

void CAknSmallIndicatorSubject::Release()
    {
    delete this;
    }

CAknSmallIndicatorSubject::TNotifierInfo CAknSmallIndicatorSubject::RegisterL()
    {
    iInfo.iUid=KAknSmallIndicatorUid;
    iInfo.iChannel=KAknSmallIndicatorUid;
    iInfo.iPriority=ENotifierPriorityVHigh;
    return iInfo;
    }

CAknSmallIndicatorSubject::TNotifierInfo CAknSmallIndicatorSubject::Info() const
    {
    return iInfo;
    }

TPtrC8 CAknSmallIndicatorSubject::StartL(const TDesC8& aBuffer)
    {
    HandleIndicatorMessageL(aBuffer);
    return KNullDesC8();
    }

void CAknSmallIndicatorSubject::StartL(const TDesC8& aBuffer, TInt /*aReplySlot*/, 
    const RMessagePtr2& aMessage)
    {
    HandleIndicatorMessageL(aBuffer);
    aMessage.Complete(EEikNotExtRequestCompleted);
    }

void CAknSmallIndicatorSubject::Cancel()
    {
    }

TPtrC8 CAknSmallIndicatorSubject::UpdateL(const TDesC8& aBuffer)
    {
    HandleIndicatorMessageL(aBuffer);
    return KNullDesC8();
    }

CAknSmallIndicatorSubject* CAknSmallIndicatorSubject::NewL(CAknMediatorEvent* aEvent)
    {
    CAknSmallIndicatorSubject* self=new (ELeave) CAknSmallIndicatorSubject();
    CleanupStack::PushL(self);
    self->ConstructL();
    self->iEvent = aEvent; // do not store until leaving methods are clear
    CleanupStack::Pop();
    return self;
    }

CAknSmallIndicatorSubject::CAknSmallIndicatorSubject()
    {
    }

CAknSmallIndicatorSubject::~CAknSmallIndicatorSubject()
    {
    delete iIndicatorSDData;
    delete iEvent; // bit nasty, but does not have really effect even if not deleted at all
    }


void CAknSmallIndicatorSubject::ConstructL()
    {
    iIndicatorSDData = new (ELeave) CAknIndicatorData();
    }

void CAknSmallIndicatorSubject::HandleIndicatorMessageL(const TDesC8& aBuffer)
    {
    SAknNotifierPackage<SAknSmallIndicatorParams>* params = 
        (SAknNotifierPackage<SAknSmallIndicatorParams>*)aBuffer.Ptr();

    if ( aBuffer.Length() < 0 
        || (TUint)aBuffer.Length() < sizeof(SAknNotifierPackage<SAknSmallIndicatorParams>) 
        || params->iSignature != KAKNNOTIFIERSIGNATURE )
        {
        User::Leave( KErrArgument );
        }

    CEikServStatusPane* ssp = static_cast<CEikServStatusPane*>(CEikStatusPaneBase::Current());
    CAknStatusPaneDataPublisher* publisher = ssp->iDataPublisher;

    if (params->iParamData.iValue == KIndicatorTap)
        {
        publisher->HandleIndicatorTapL(params->iParamData.iSmallIndicatorUid);  
        }
    else
        {           
        publisher->SetIndicatorState(params->iParamData.iSmallIndicatorUid, params->iParamData.iValue);         
        publisher->PublishDataL();  

        // publish current indicator status to coverui    
        iIndicatorSDData->HandleIndicatorChanged(
            params->iParamData.iSmallIndicatorUid.iUid, 
            params->iParamData.iValue);
            
        CBufFlat* buf = CBufFlat::NewL(5);
        CleanupStack::PushL(buf);
        RBufWriteStream stream;
        stream.Open(*buf);
        CleanupClosePushL(stream);
        stream << *iIndicatorSDData;
        stream.CommitL();
        CleanupStack::PopAndDestroy();  // close stream           
        
        iEvent->RaiseEvent(EAknSmallIndicatorSDInfo, buf->Ptr(0) );
        CleanupStack::PopAndDestroy(buf);                    
        }
    }

void CAknIncallBubbleSubject::Release()
    {
    delete this;
    }


CAknIncallBubbleSubject::TNotifierInfo CAknIncallBubbleSubject::RegisterL()
    {
    iInfo.iUid=KAknIncallBubbleUid;
    iInfo.iChannel=KAknIncallBubbleUid;
    iInfo.iPriority=ENotifierPriorityVHigh;
    return iInfo;
    }

CAknIncallBubbleSubject::TNotifierInfo CAknIncallBubbleSubject::Info() const
    {
    return iInfo;
    }

TPtrC8 CAknIncallBubbleSubject::StartL(const TDesC8& aBuffer)
    {
    HandleIndicatorMessageL( aBuffer, 0 );
    return KNullDesC8();
    }

void CAknIncallBubbleSubject::StartL(const TDesC8& aBuffer, TInt /*aReplySlot*/, 
    const RMessagePtr2& aMessage)
    {
    RThread clientThread;
    TUint64 clientId = 0;
    if ( KErrNone == aMessage.Client( clientThread ) )
        {
        clientId = clientThread.Id().Id();
        }
    clientThread.Close();
    HandleIndicatorMessageL( aBuffer, clientId );
    aMessage.Complete(EEikNotExtRequestCompleted);
    }

void CAknIncallBubbleSubject::Cancel()
    {
    }

TPtrC8 CAknIncallBubbleSubject::UpdateL(const TDesC8& aBuffer)
    {
    HandleIndicatorMessageL(aBuffer,0);
    return KNullDesC8();
    }

CAknIncallBubbleSubject* CAknIncallBubbleSubject::NewL()
    {
    CAknIncallBubbleSubject* self=new (ELeave) CAknIncallBubbleSubject();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

CAknIncallBubbleSubject::CAknIncallBubbleSubject()
    {
    }

void CAknIncallBubbleSubject::ConstructL()
    {
    }

void CAknIncallBubbleSubject::HandleIndicatorMessageL( const TDesC8& aBuffer , const TUint64& aClientId  )
    {
    SAknNotifierPackage<SAknIncallBubbleParams>* params = 
        (SAknNotifierPackage<SAknIncallBubbleParams>*)aBuffer.Ptr();

    if ( aBuffer.Length() < 0 
        || (TUint)aBuffer.Length() < sizeof(SAknNotifierPackage<SAknIncallBubbleParams>) 
        || params->iSignature != KAKNNOTIFIERSIGNATURE )
        {
        User::Leave( KErrArgument );
        }
    
    CEikServStatusPane* ssp = static_cast<CEikServStatusPane*>(CEikStatusPaneBase::Current());
    CAknStatusPaneDataPublisher* publisher = ssp->iDataPublisher;
    TInt flags = params->iParamData.iIncallBubbleFlags;
    if ( flags & EAknStatusBubbleReservedInternal ) 
        {
        if (flags & 4)
            {
            publisher->SetIncallBubbleAllowedInUsual( ETrue , aClientId );
            }
        else if (flags & 2)
            {
            publisher->SetIncallBubbleAllowedInUsual( EFalse , aClientId );
            }
        else if (flags & 1)
            {
            publisher->SetIncallBubbleAllowedInIdle( ETrue );
            }
        else
            { 
            publisher->SetIncallBubbleAllowedInIdle( EFalse );
            }
        }
    else
        {
        publisher->SetIncallBubbleFlags( flags );
        }    

    publisher->PublishDataL();  
    }


