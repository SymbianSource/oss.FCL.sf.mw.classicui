/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:         Implement of pen input plugin utils:resource,repository,LafEnv
*
*/








#include <centralrepository.h>

#include "ChineseFindUtils.h"

// ======== MEMBER FUNCTIONS ========

CFindRepositoryWatcher* CFindRepositoryWatcher::NewL(
    const TUid aUid,
    const TUint32 aKey,
    CCenRepNotifyHandler::TCenRepKeyType aKeyType,
    TCallBack aCallBack,
    CRepository* aRepository)
    {
    CFindRepositoryWatcher* self = new(ELeave) CFindRepositoryWatcher(aUid, aKey, aCallBack, aRepository);

    CleanupStack::PushL(self);
    self->ConstructL(aKeyType);
    CleanupStack::Pop(self);

    return self;
    }

CFindRepositoryWatcher* CFindRepositoryWatcher::NewL(
    const TUid aUid,
    TCallBack aCallBack,
    CRepository* aRepository)
    {
    CFindRepositoryWatcher* self = new(ELeave) CFindRepositoryWatcher(aUid, NCentralRepositoryConstants::KInvalidNotificationId, aCallBack, aRepository);

    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);

    return self;
    }

CFindRepositoryWatcher::~CFindRepositoryWatcher()
    {
    if (iNotifyHandler)
        {
        iNotifyHandler->StopListening();
        delete iNotifyHandler;
        }
    }

CFindRepositoryWatcher::CFindRepositoryWatcher(
    const TUid aUid,
    const TUint32 aKey,
    TCallBack aCallBack,
    CRepository* aRepository)
    :
    iUid(aUid), iKey(aKey), iCallBack(aCallBack), iRepository(aRepository)
    {
    }

void CFindRepositoryWatcher::ConstructL(CCenRepNotifyHandler::TCenRepKeyType aKeyType)
    {
    iNotifyHandler = CCenRepNotifyHandler::NewL(*this, *iRepository, aKeyType, iKey);
    iNotifyHandler->StartListeningL();
    }

void CFindRepositoryWatcher::ConstructL()
    {
    iNotifyHandler = CCenRepNotifyHandler::NewL(*this, *iRepository);
    iNotifyHandler->StartListeningL();
    }

TUint32 CFindRepositoryWatcher::ChangedKey()
    {
    return iChangedKey;
    }
       
void CFindRepositoryWatcher::HandleNotifyInt(TUint32 aKey, TInt /*aNewValue*/)
    {
    iChangedKey = aKey;
    iCallBack.CallBack();
    iChangedKey = NCentralRepositoryConstants::KInvalidNotificationId;
    }

void CFindRepositoryWatcher::HandleNotifyError(TUint32 /*aKey*/, TInt /*aError*/, CCenRepNotifyHandler* /*aHandler*/)
    {
    }

void CFindRepositoryWatcher::HandleNotifyGeneric(TUint32 aId)
    {
    iChangedKey = aId;
    iCallBack.CallBack();
    iChangedKey = NCentralRepositoryConstants::KInvalidNotificationId;  
    }

// End Of File
