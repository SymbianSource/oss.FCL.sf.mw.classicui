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

#include "AknAsyncDemoNotify.h"
#include <aknNotifyStd.h>

EXPORT_C CAknAsyncDemoNotify* CAknAsyncDemoNotify::NewL(const TCallBack& aCallBack)
    {
    CAknAsyncDemoNotify* self = new(ELeave) CAknAsyncDemoNotify(aCallBack);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(); // self
    return self;
    }

EXPORT_C CAknAsyncDemoNotify::~CAknAsyncDemoNotify()
    {
    Cancel();
    iNotify.Close();
    }

EXPORT_C const TDesC8& CAknAsyncDemoNotify::Message()
    {
    return iBuf;
    }

CAknAsyncDemoNotify::CAknAsyncDemoNotify(const TCallBack& aCallBack)
: CActive(EPriorityNormal), iCallBack(aCallBack)
    {
    CActiveScheduler::Add(this);
    }

void CAknAsyncDemoNotify::ConstructL()
    {
    QueueL();
    }

void CAknAsyncDemoNotify::QueueL()
    {
    User::LeaveIfError(iNotify.Connect());
    iBuf.Zero();
    iNotify.StartNotifierAndGetResponse(iStatus, KAknAsyncDemoNotifierUid, KNullDesC8, iBuf);
    SetActive();
    }

void CAknAsyncDemoNotify::DoCancel()
    {
    iNotify.CancelNotifier(KAknAsyncDemoNotifierUid);
    }

void CAknAsyncDemoNotify::RunL()
    {
    User::LeaveIfError(iStatus.Int());
    iCallBack.CallBack();
    // This is some wierdness in notifiers - you have to entirely cancel, shut down
    // and reconnect between async requests.
    iNotify.CancelNotifier(KAknAsyncDemoNotifierUid);
    iNotify.Close();
    QueueL();
    }

// End of File
