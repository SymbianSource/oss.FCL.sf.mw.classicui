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
* Description:  Server applications framework: LaunchApp service
 *
 *
*/


#include <apgcli.h>
#include <eikenv.h>
#include <eikappui.h>
#include <eikdoc.h>
#include <s32mem.h> // for CBufStore
#include <s32std.h> // for CStreamDictionary
#include <AiwGenericParam.h>
#include "AknLaunchAppServiceImpl.h"

const TUid KUidEmbedInputStream  = { 0x1000 };
// const TUid KUidEmbedOutputStream = { 0x2000 };

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void RAknLaunchAppService::LaunchAppL(CAiwGenericParamList* aParam)
    {
    TIpcArgs args;
    HBufC8* buf = aParam->PackForServerL(args); // packs params 0 and 1.

    TInt err = SendReceive(EAknLaunchAppServiceCmdLaunchAppWithParams, args);

    delete buf;

    User::LeaveIfError(err);
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
TUid RAknLaunchAppService::ServiceUid() const
    {
    return KAknLaunchAppServiceUid;
    }


// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
CAknLaunchAppServiceSession::CAknLaunchAppServiceSession()
: iDoc(CEikonEnv::Static()->EikAppUi()->Document())
    {
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
CAknLaunchAppServiceSession::~CAknLaunchAppServiceSession()
    {
    delete iStore;
    delete iDictionary;
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void CAknLaunchAppServiceSession::CreateL()
    {
    CAknAppServiceBase::CreateL();
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void CAknLaunchAppServiceSession::ServiceL(const RMessage2& aMessage)
    {
    switch (aMessage.Function())
        {
        case EAknLaunchAppServiceCmdLaunchAppWithParams:
            LaunchAppWithParamsL(aMessage);
            break;

        default:
            CAknAppServiceBase::ServiceL(aMessage);
            break;
        }
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void CAknLaunchAppServiceSession::ServiceError(const RMessage2& aMessage,TInt aError)
    {
    CAknAppServiceBase::ServiceError(aMessage, aError);
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void CAknLaunchAppServiceSession::LaunchAppWithParamsL(const RMessage2& aMessage)
    {
    CAiwGenericParamList* paramList = CAiwGenericParamList::NewLC();
    paramList->UnpackFromClientL(aMessage);

    TSecureId clientSid = aMessage.SecureId();
    TAiwVariant clientAppUid((TUid)clientSid);
    TAiwGenericParam uid(EGenericParamApplication, clientAppUid);
    paramList->AppendL(uid);

    ExternalizeParamsL(paramList);

    CleanupStack::PopAndDestroy(); // paramList

    TFileName fileName;

    iDoc->OpenFileL(ETrue, fileName, CEikonEnv::Static()->FsSession());

    aMessage.Complete(KErrNone);
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void CAknLaunchAppServiceSession::ExternalizeParamsL(CAiwGenericParamList* aParamList)
    {
    // Create an in-memory store of parameters.
    delete iStore;
    iStore = NULL;
    iStore = CBufStore::NewL(127);

    RStoreWriteStream outStream;
    iStreamId = outStream.CreateLC(*iStore);
    aParamList->ExternalizeL(outStream);
    iStore->CommitL();
    CleanupStack::PopAndDestroy(); // outStream

    delete iDictionary;
    iDictionary = NULL;
    iDictionary = CStreamDictionary::NewL();

    iDictionary->AssignL(KUidEmbedInputStream, iStreamId);
    outStream.CreateLC(*iStore);
    iDictionary->ExternalizeL(outStream);
    iStore->CommitL();
    CleanupStack::PopAndDestroy(); // outstream

    RStoreReadStream readStream;
    readStream.OpenLC(*iStore, iStreamId);
    iDoc->RestoreL(*iStore, *iDictionary);
    CleanupStack::PopAndDestroy(); // readStream
    }


// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
EXPORT_C CAknLaunchAppService* CAknLaunchAppService::NewL(
    const TUid& aAppUid, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam)
    {
    CAknLaunchAppService* self = NewLC(aAppUid, aObserver, aParam);
    CleanupStack::Pop(self);
    return self;
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
CAknLaunchAppService* CAknLaunchAppService::NewLC(
    const TUid& aAppUid, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam)
    {
    CAknLaunchAppServiceImpl* self = new(ELeave) CAknLaunchAppServiceImpl();
    CleanupStack::PushL(self);
    self->ConstructL(aAppUid, aObserver, aParam);
    return self;
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
CAknLaunchAppServiceImpl::CAknLaunchAppServiceImpl()
    {
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
CAknLaunchAppServiceImpl::~CAknLaunchAppServiceImpl()
    {
    delete iMonitor;
    iService.Close();
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void CAknLaunchAppServiceImpl::ConstructL(
    const TUid& aAppUid, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam)
    {
    iService.ConnectChainedAppL(aAppUid);

    if (aObserver)
        {
        iMonitor = CApaServerAppExitMonitor::NewL(iService, *aObserver, CActive::EPriorityStandard);
        }

    if (aParam && aParam->Count())
        {
        iService.LaunchAppL(aParam);
        }
    }

// End of file.
