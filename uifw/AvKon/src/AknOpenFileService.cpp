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
* Description:  Server applications framework: Open file service
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
#include "AknOpenFileServiceImpl.h"

const TUid KUidEmbedInputStream  = { 0x1000 };
// const TUid KUidEmbedOutputStream = { 0x2000 };

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void RAknOpenFileService::OpenFileNameL(const TDesC& aFileName)
    {
    TInt err = SendReceive(EAknOpenFileServiceCmdOpenFilename, TIpcArgs(&aFileName));
    User::LeaveIfError(err);
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void RAknOpenFileService::OpenFileNameL(const TDesC& aFileName, CAiwGenericParamList* aParam)
    {
    TIpcArgs args;
    HBufC8* buf = aParam->PackForServerL(args); // packs params 0 and 1.

    // pack more params.
    args.Set(2, &aFileName);

    TInt err = SendReceive(EAknOpenFileServiceCmdOpenFilenameWithParams, args);

    delete buf;

    User::LeaveIfError(err);
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void RAknOpenFileService::OpenHandleL(const RFile& aFile, CAiwGenericParamList* aParam)
    {
    TAiwVariant filehandle(aFile);
    TAiwGenericParam param(EGenericParamInternalFile, filehandle);
    aParam->AppendL(param);
    
    TIpcArgs args;
    HBufC8* buf = aParam->PackForServerL(args); // packs params 0 and 1.
       
    TInt err = SendReceive(EAknOpenFileServiceCmdOpenHandleWithParams, args);
    
    delete buf;
    
    User::LeaveIfError(err);
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
TUid RAknOpenFileService::ServiceUid() const
    {
    return KAknOpenFileServiceUid;
    }



// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
CAknOpenFileServiceSession::CAknOpenFileServiceSession()
: iDoc(CEikonEnv::Static()->EikAppUi()->Document())
    {
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
CAknOpenFileServiceSession::~CAknOpenFileServiceSession()
    {
    delete iStore;
    delete iDictionary;
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void CAknOpenFileServiceSession::CreateL()
    {
    CAknAppServiceBase::CreateL();
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void CAknOpenFileServiceSession::ServiceL(const RMessage2& aMessage)
    {
    switch (aMessage.Function())
        {
        case EAknOpenFileServiceCmdOpenFilename:
            OpenFileNameL(aMessage);
            break;

        case EAknOpenFileServiceCmdOpenFilenameWithParams:
            OpenFileNameWithParamsL(aMessage);
            break;

        case EAknOpenFileServiceCmdOpenHandleWithParams:
            OpenHandleWithParamsL(aMessage);
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
void CAknOpenFileServiceSession::ServiceError(const RMessage2& aMessage,TInt aError)
    {
    CAknAppServiceBase::ServiceError(aMessage, aError);
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void CAknOpenFileServiceSession::OpenFileNameL(const RMessage2& aMessage)
    {
    CAiwGenericParamList* paramList = CAiwGenericParamList::NewLC();

    TSecureId clientSid = aMessage.SecureId();
    TAiwVariant clientAppUid((TUid)clientSid);
    TAiwGenericParam uid(EGenericParamApplication, clientAppUid);
    paramList->AppendL(uid);

    ExternalizeParamsL(paramList);

    CleanupStack::PopAndDestroy(); // paramList

    TFileName fileName;
    aMessage.Read(0, fileName);

    iDoc->OpenFileL(ETrue, fileName, CEikonEnv::Static()->FsSession());

    aMessage.Complete(KErrNone);
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void CAknOpenFileServiceSession::OpenFileNameWithParamsL(const RMessage2& aMessage)
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
    aMessage.Read(2, fileName);

    iDoc->OpenFileL(ETrue, fileName, CEikonEnv::Static()->FsSession());

    aMessage.Complete(KErrNone);
    }


// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void CAknOpenFileServiceSession::OpenHandleWithParamsL(const RMessage2& aMessage)
    {
    CAiwGenericParamList* paramList = CAiwGenericParamList::NewLC();
    paramList->UnpackFromClientL(aMessage);

    TSecureId clientSid = aMessage.SecureId();
    TAiwVariant clientAppUid((TUid)clientSid);
    TAiwGenericParam uid(EGenericParamApplication, clientAppUid);
    paramList->AppendL(uid);

    RFile fileHandle;
    TInt index = 0;
    const TAiwGenericParam* param = NULL;

    param = paramList->FindFirst(index, EGenericParamInternalFile, EVariantTypeFileHandle);

    if (index >= 0 && param)
        {
        param->Value().Get(fileHandle);
        paramList->Remove(EGenericParamInternalFile);
        }

    ExternalizeParamsL(paramList);

    CleanupStack::PopAndDestroy(); // paramList

    CFileStore* filestore=NULL;
    iDoc->OpenFileL(filestore,fileHandle);

    aMessage.Complete(KErrNone);
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void CAknOpenFileServiceSession::ExternalizeParamsL(CAiwGenericParamList* aParamList)
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
EXPORT_C CAknOpenFileService* CAknOpenFileService::NewL(
    const TDesC& aFileName, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam)
    {
    CAknOpenFileService* self = NewLC(aFileName, aObserver, aParam);
    CleanupStack::Pop(self);
    return self;
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
CAknOpenFileService* CAknOpenFileService::NewLC(
    const TDesC& aFileName, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam)
    {
    CAknOpenFileServiceImpl* self = new (ELeave) CAknOpenFileServiceImpl();
    CleanupStack::PushL(self);
    self->ConstructL(aFileName, aObserver, aParam);
    return self;
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
EXPORT_C CAknOpenFileService* CAknOpenFileService::NewL(
    const TUid& aAppUid, const RFile& aFileHandle, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam)
    {
    CAknOpenFileService* self = NewLC(aAppUid, aFileHandle, aObserver, aParam);
    CleanupStack::Pop(self);
    return self;
    }


// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
CAknOpenFileService* CAknOpenFileService::NewLC(
    const TUid& aAppUid, const RFile& aFileHandle, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam)
    {
    CAknOpenFileServiceImpl* self = new (ELeave) CAknOpenFileServiceImpl();
    CleanupStack::PushL(self);
    self->ConstructL(aAppUid, aFileHandle, aObserver, aParam);
    return self;
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
CAknOpenFileServiceImpl::CAknOpenFileServiceImpl()
    {
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
CAknOpenFileServiceImpl::~CAknOpenFileServiceImpl()
    {
    delete iMonitor;
    iService.Close();
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void CAknOpenFileServiceImpl::ConstructL(
    const TDesC& aFileName, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam)
    {
    TUid app = FindAppForFileL(aFileName);
    iService.ConnectChainedAppL(app);

    if (aObserver)
        {
        iMonitor = CApaServerAppExitMonitor::NewL(iService, *aObserver, EActivePriorityRedrawEvents+1);	// priority used to get exit messages before the client app redraws
        }

    if (aParam && aParam->Count())
        {
        iService.OpenFileNameL(aFileName, aParam);
        }
    else
        {
        iService.OpenFileNameL(aFileName);
        }
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void CAknOpenFileServiceImpl::ConstructL(
    const TUid& aAppUid, const RFile& aFileHandle, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam)
    {
    iService.ConnectChainedAppL(aAppUid);

    if (aObserver)
        {
        iMonitor = CApaServerAppExitMonitor::NewL(iService, *aObserver, EActivePriorityRedrawEvents+1);	// priority used to get exit messages before the client app redraws
        }

    iService.OpenHandleL(aFileHandle, aParam);
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
TUid CAknOpenFileServiceImpl::FindAppForFileL(const TDesC& aFileName)
    {
    TUid uid;
    TDataType type;

    RApaLsSession ls;
    User::LeaveIfError(ls.Connect());
    CleanupClosePushL(ls);
    User::LeaveIfError(ls.AppForDocument(aFileName, uid, type));
    CleanupStack::PopAndDestroy(&ls);

    return uid;
    }

// End of file.
