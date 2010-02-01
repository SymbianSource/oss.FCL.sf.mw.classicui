/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Server applications framework: Null service
 *
 *
*/


#include <apgcli.h>
#include <eikenv.h>
#include <eikappui.h>
#include "AknNullServiceImpl.h"

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
TUid RAknNullService::ServiceUid() const
    {
    return KAknNullServiceUid;
    }


// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
EXPORT_C CAknNullService* CAknNullService::NewL(const TUid& aAppUid, MAknServerAppExitObserver* aObserver)
    {
    CAknNullService* self = NewLC(aAppUid, aObserver);
    CleanupStack::Pop(self);
    return self;
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
CAknNullService* CAknNullService::NewLC(const TUid& aAppUid, MAknServerAppExitObserver* aObserver)
    {
    CAknNullServiceImpl* self = new(ELeave) CAknNullServiceImpl();
    CleanupStack::PushL(self);
    self->ConstructL(aAppUid, aObserver);
    return self;
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
CAknNullServiceImpl::CAknNullServiceImpl()
    {
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
CAknNullServiceImpl::~CAknNullServiceImpl()
    {
    delete iMonitor;
    iService.Close();
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void CAknNullServiceImpl::ConstructL(const TUid& aAppUid, MAknServerAppExitObserver* aObserver)
    {
    iService.ConnectChainedAppL(aAppUid);

    if (aObserver)
        {
        iMonitor = CApaServerAppExitMonitor::NewL(iService, *aObserver, CActive::EPriorityStandard);
        }
    }

// End of file.
