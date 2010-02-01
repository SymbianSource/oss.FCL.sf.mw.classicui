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


#include <eikenv.h>

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h> 
#include <uikon/eiknotifyalert.h> 
#endif

#include "AknNotifierControllerPlugin.h"
#include <s32mem.h>
#include <eikappui.h>
#include <aknkeys.h>
#include <coedef.h>
#include <uikon/eiksrvui.h>
#include <eikon.hrh>
#include <apgwgnam.h>
#include <AknDlgShut.h>
#include <bautils.h>
#include <AknNotifySignature.h>
#include <AknCapServerDefs.h>

const TInt KAknObserverListGranularity = 4;

_LIT(KRESOURCEFILE,"z:\\resource\\aknnotpi.rsc");
    
EXPORT_C void CAknNotifierController::RegisterNotifierControllerPlugin(CAknNotifierWrapper* aMe, 
    TBool aUnregister)
    {
    if (!aMe)
        {
        return;
        }
    
    if (!aUnregister)
        {
        if (FindNotifierWrapperIndex(aMe) == KErrNotFound)
            {
            TRAP_IGNORE( iRegisteredList->AppendL(aMe) );
            }   
        }
    else
        {
        TInt index = FindNotifierWrapperIndex(aMe);
        if (index != KErrNotFound)
            {
            iRegisteredList->Delete(index);
            }
        }
    }

void CAknNotifierController::NotifyAppServers(TInt aCmd)
    {
    TUid commonServerUid = {0};
    
    // Do this only once for common notifier server.
    // Re-use existing session from pre-loaded wrapper, otherwise handle as any other wrapper.
    if (iPreloadList.Count())
        {
        CAknCommonNotifierWrapper* ccl = iPreloadList[0]; 
        commonServerUid = ccl->AppServerUid();
        ccl->DoNotifierControllerCommand(aCmd);
        }
    
    // and for akncapserver
    RAknUiServer* akncapserverClient = CAknSgcClient::AknSrv();
    if ( akncapserverClient && akncapserverClient->Handle() )
        {
        akncapserverClient->DoNotifierControllerCommand(aCmd);
        }
    
    TInt count = iRegisteredList->Count();
    for (TInt ii = 0; ii < count; ii++)
        {
        CAknNotifierWrapper* nw = (*iRegisteredList)[ii]; 
        TUid appserverUid = nw->AppServerUid(); 
        if ( appserverUid != commonServerUid && appserverUid != KAknCapServerUid)
            {
            nw->DoNotifierControllerCommand(aCmd);            
            }
        }
    }
    
TInt CAknNotifierController::FindNotifierWrapperIndex(CAknNotifierWrapper* aPtr)
    {
    TInt index = KErrNotFound;
    TInt count = iRegisteredList->Count();
    for (TInt ii = 0; ii < count; ii++)
        {
        if ( ((*iRegisteredList)[ii]) == aPtr)
            {
            index = ii;
            }
        }
    return index;
    }

CAknNotifierController* CAknNotifierController::NewL()
    {
    CAknNotifierController* self = new(ELeave)CAknNotifierController();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();    //self
    return self;
    }

void CAknNotifierController::ConstructL()
    {
    TFileName resourceFile;
    resourceFile.Append(KRESOURCEFILE);
    BaflUtils::NearestLanguageFile(CEikonEnv::Static()->FsSession(),resourceFile);
    iResourceFileOffset = CEikonEnv::Static()->AddResourceFileL(resourceFile);

    iObserverList = new(ELeave)CArrayPtrFlat<MAknKeyLockObserver>(KAknObserverListGranularity);
    iRegisteredList = new(ELeave)CArrayPtrFlat<CAknNotifierWrapper>(KAknObserverListGranularity);
    iController = new (ELeave) CAknNotifierControllerUtility(0);
    
    // Make sure AppUi has a pointer to this (Obsolete, Fix Me !!)
    STATIC_CAST(CEikServAppUi*,CEikonEnv::Static()->AppUi())->iKeyLockController = this;
    }

CAknNotifierController::CAknNotifierController()
:iAllowNotifications(ETrue)
    {
    }

CAknNotifierController::~CAknNotifierController()
    {
    delete iObserverList;
    iPreloadList.Close();
    if (iResourceFileOffset)
        {
        CCoeEnv::Static()->DeleteResourceFile(iResourceFileOffset);
        }
    }

TBool CAknNotifierController::IsKeyLockEnabled()
    {
    TBool ret = EFalse;
    if (KeylockReady())
        {
        ret = iKeylock.IsKeyLockEnabled();
        }

    return ret;
    }

TBool CAknNotifierController::AllowNotifications()
    {
    return iAllowNotifications;
    }

void CAknNotifierController::UnlockKeys()
    {
    if (KeylockReady())
        {
        iKeylock.DisableKeyLock();
        }
    }

void CAknNotifierController::LockKeys(TBool aAutoLockOn)
    {
    if (KeylockReady())
        {
        if (!aAutoLockOn)
            iKeylock.EnableKeyLock();
        else 
            iKeylock.EnableAutoLockEmulation();
        }   
    }

void CAknNotifierController::AddObserverL(MAknKeyLockObserver* aObserver)
    {
#if defined(_DEBUG)
    TInt count = iObserverList->Count();
    for (TInt ii = 0; ii < count; ii++)
        {
        if ( ((*iObserverList)[ii]) == aObserver)
            {
            User::Invariant();
            }
        }
#endif
    iObserverList->AppendL(aObserver);
    }

void CAknNotifierController::RemoveObserver(MAknKeyLockObserver* aObserver)
    {
    TInt count = iObserverList->Count();
    for (TInt ii = 0; ii < count; ii++)
        {
        if ( ((*iObserverList)[ii]) == aObserver)
            {
            iObserverList->Delete(ii);
            return;
            }
        }
#if defined(_DEBUG)
    User::Invariant();
#endif
    }

void CAknNotifierController::NotifyStatusChange(TKeyLockStatus aStatus)
    {
    TInt count = iObserverList->Count();
    for (TInt ii = count-1; ii >= 0; ii--)
        {
        ((*iObserverList)[ii])->KeyLockStatusChange(aStatus);
        }
    }

void CAknNotifierController::DoAllowNotifications()
    {
    TBool lastvalue = iAllowNotifications;
    iAllowNotifications = ETrue;
    NotifyStatusChange(EKeyLockAllowNotifications);
    iController->DoAllowNotifications();
    if (!lastvalue)
        {
        // Enable FSW (could use direct connect to AknCapServer to do this as well).
        STATIC_CAST(CEikServAppUi*,CEikonEnv::Static()->AppUi())->SuppressAppSwitching(EFalse);
        }
    }

void CAknNotifierController::DoStopNotifications()
    {
    TBool lastvalue = iAllowNotifications;
    iAllowNotifications = EFalse;
    NotifyStatusChange(EKeyLockStopNotifications);
    iController->DoStopNotifications();
    if (lastvalue)
        {
        // Disable FSW (could use direct connect to AknCapServer to do this as well).
        STATIC_CAST(CEikServAppUi*,CEikonEnv::Static()->AppUi())->SuppressAppSwitching(ETrue);
        }
    }

void CAknNotifierController::DoCancelAllNotificatons()
    {
    // Used when end key is pressed, to allow phone app to cancel all
    // notifications. Global notes / soft notifications that would
    // not normally be shown (out of priority) are not cancelled.
    if ( IsKeyLockEnabled() )
        {
        return;
        }

    NotifyStatusChange(EKeyLockCancelNotification);

    // Send cancel key event to all other notifications, and hope they cancel.
    // Ignore error message - there's nothing more we can do.
    TRAP_IGNORE(iController->DoCancelAllNotificatonsL());
    }

TBool CAknNotifierController::KeylockReady()
    {
    if (iKeylock.Handle() == 0)
        {
        if (iKeylock.Connect() != KErrNone)
            {
            return EFalse;
            }
        }
    return ETrue;   
    }

EXPORT_C void CAknNotifierController::RegisterPreloadPluginL(CAknCommonNotifierWrapper* aNotifier)
    {
    User::LeaveIfError(iPreloadList.Append(aNotifier));
    }
    
// end of file
