/*
* Copyright (c) 2003-2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:     Implementation for ECom monitoring class for AIW framework.
*
*/




#include "AiwEcomMonitor.h"
#include "AiwCommon.h"
#include "AiwUids.hrh"
#include "AiwServiceIfBase.h"

// CONSTANTS
_LIT8(KContentTag, "<CONTENT>");
_LIT8(KOpaqueTag, "<OPAQUE>");
_LIT8(KAiwMimeTypeAll, "*");

const TInt KMaxDataParamSize = 255;

CAiwEcomMonitor* CAiwEcomMonitor::NewL(TCallBack& aSynchronizeCallBack)
    {
    CAiwEcomMonitor* self = new (ELeave) CAiwEcomMonitor(aSynchronizeCallBack); 
    CleanupStack::PushL(self);  
    self->ConstructL();
    CleanupStack::Pop(); // self
    return self;
    }


CAiwEcomMonitor::CAiwEcomMonitor(TCallBack& aSynchronizeCallBack) 
:CActive(CActive::EPriorityStandard), iSynchronizeCallBack(aSynchronizeCallBack)
    {
    }


CAiwEcomMonitor::~CAiwEcomMonitor()
    {
    Cancel();
    iEcomSession.Close();
    REComSession::FinalClose();
    }


void CAiwEcomMonitor::ConstructL()
    {
    iEcomSession = REComSession::OpenL();
    CActiveScheduler::Add(this);
    StartMonitoring();
    }

      
void CAiwEcomMonitor::RunL()
    {
    iSynchronizeCallBack.CallBack();
    StartMonitoring();
    }


    
void CAiwEcomMonitor::DoCancel()
    {
    iEcomSession.CancelNotifyOnChange(iStatus);
    }


void CAiwEcomMonitor::StartMonitoring()
    {
    iEcomSession.NotifyOnChange(iStatus);
    SetActive();
    }



void CAiwEcomMonitor::ListImplemetationsL(RImplInfoPtrArray& aResult, 
    CAiwCriteriaItem* aItem) const
    {
    TEComResolverParams params;
    
    TUid resolvUid = { KAiwResolverImplUidValue };  
    
    TBuf8<KMaxDataParamSize> dataType;     
    dataType.Copy(KContentTag);
    dataType.Append(aItem->ContentType());
    dataType.Append(KOpaqueTag);
    dataType.AppendNumUC(aItem->ServiceCmd(), EHex);

    params.SetDataType(dataType);
    params.SetWildcardMatch(dataType.Find(KAiwMimeTypeAll) != KErrNotFound);
    
    iEcomSession.ListImplementationsL(aItem->ServiceClass(), params, resolvUid, aResult);
    }



CAiwServiceIfBase* CAiwEcomMonitor::CreateImplementationL(TUid aImplUid)
    {
    TUid dtorKeyId;

    CAiwServiceIfBase* iface = (CAiwServiceIfBase*)iEcomSession.CreateImplementationL(aImplUid, 
        dtorKeyId);

    if (iface)
        {
        iface->SetDtorKeyId( dtorKeyId );               
        iface->SetImplementationUid( aImplUid );
        }           
    
    return iface;
    }

// End of file
