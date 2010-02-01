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

#ifndef __AKNNOTIFIERCONTROLLERPLUGIN_H__
#define __AKNNOTIFIERCONTROLLERPLUGIN_H__

#include <AknNotifierControllerUtilities.h>
#include <AknNotifierWrapper.h>
#include <aknkeylock.h>

enum TKeyLockStatus
    {
    EKeyLockStopNotifications   = 1,
    EKeyLockAllowNotifications  = 2,
    EKeyLockEnabled             = 3,
    EKeyLockDisabled            = 4,
    EKeyLockCancelNotification  = 5,
    EKeyLockOffered             = 6,
    EHideSoftNotifications      = 7,
    EShowSoftNotifications      = 8
    };

// MAknKeyLockObserver
// Notifier must derive from this in order to reveive notfication as to when
// the keylock status has changed
class MAknKeyLockObserver
    {
public:
    virtual void KeyLockStatusChange(TKeyLockStatus aStatus) = 0;
    };


// MAknKeyLockController
// The MAknKeyLockController is used by notifier in order to control the keylock mechanism
class MAknKeyLockController
    {
public:
    virtual TBool IsKeyLockEnabled() = 0;
    virtual TBool AllowNotifications() = 0;
    virtual void UnlockKeys() = 0;
    virtual void LockKeys(TBool aAutoLockOn = EFalse) = 0;
    virtual void AddObserverL(MAknKeyLockObserver* aObserver) = 0;
    virtual void RemoveObserver(MAknKeyLockObserver* aObserver) = 0;
    };

class CAknNotifierController: public CBase, public MAknKeyLockController
    {
public:
    IMPORT_C void RegisterNotifierControllerPlugin(CAknNotifierWrapper* aMe, TBool aUnregister = EFalse);
    IMPORT_C void RegisterPreloadPluginL(CAknCommonNotifierWrapper* aNotifier);
    void NotifyAppServers(TInt aCmd);

public:
    static CAknNotifierController* NewL();
    ~CAknNotifierController();
    // From MAknKeyLockObserver
    TBool IsKeyLockEnabled();
    TBool AllowNotifications();
    void UnlockKeys();
    void LockKeys(TBool aAutoLockOn = EFalse);
    void AddObserverL(MAknKeyLockObserver* aObserver);
    void RemoveObserver(MAknKeyLockObserver* aObserver);
    void DoAllowNotifications();
    void DoStopNotifications();
    void DoCancelAllNotificatons();

private:
    CAknNotifierController();
    void ConstructL();

    void NotifyStatusChange(TKeyLockStatus aStatus);
    
    TInt FindNotifierWrapperIndex(CAknNotifierWrapper* aPtr);
    
    TBool KeylockReady();

private:
    CArrayPtrFlat<MAknKeyLockObserver>* iObserverList;
    TBool iAllowNotifications;
    CAknNotifierControllerUtility* iController;
    TInt iResourceFileOffset;
    CArrayPtrFlat<CAknNotifierWrapper>* iRegisteredList;
    RAknKeylock2 iKeylock;
    
public:
    RPointerArray<CAknCommonNotifierWrapper> iPreloadList; 
    };

#endif // AKNNOTIFIERCONTROLLERPLUGIN
