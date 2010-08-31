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
* Description:  Avkon keylock client class definition.
*
*/


#ifndef __AKNKEYLOCK_H__
#define __AKNKEYLOCK_H__

#include <e32base.h>
#include <AknNotifyStd.h>

/**
 * A handle class API disabling/enabling keylock state. 
 *
 * @lib avkon.lib
 * @since S60 0.9
 */
class RAknKeyLock : public RNotifier
    {
public:
    /**
     * Locks the keys of the device and shows a keys locked note.
     */
    IMPORT_C void EnableKeyLock();

    /**
     * Unlocks the keys of the device and shows a keys unlocked note.
     */  
    IMPORT_C void DisableKeyLock();

    /**
     * Returns whether the phone keys have been locked or not.
     *
     * @return ETrue if the keys have been locked normally or the phone is in 
     *         autolock state.
     */
    IMPORT_C TBool IsKeyLockEnabled();

    /**
     * Controls whether soft notifications will be shown at all.
     *
     * @param ETrue if soft notifications should be shown.
     */  
    IMPORT_C void EnableSoftNotifications(TBool aEnable);

    /**
     * Shows a note on the screen asking the user permission to lock the keypad.
     */
    IMPORT_C void OfferKeyLock();
    
    /**
     * All notifications queued to be shown are cancelled.
     */
    IMPORT_C void CancelAllNotifications();
    
    /**
     * Locks the device keys similar to autolock/device lock state.
     *
     * @internal
     * @since S60 2.0  
     */
    IMPORT_C void EnableAutoLockEmulation();
    
    /**
     * Unlocks the keys of the device without showing the keys unlocked note.
     *
     * @since S60 2.0     
     */
    IMPORT_C void DisableWithoutNote();
    
    /**
     * Locks the keys of the device without showing the keys locked note.
     *
     * @since S60 2.1     
     */
    IMPORT_C void EnableWithoutNote();
    
private:
    void SendMessage(TKeyLockNotifierReason aMessage);
    };

/**
 * Direct client to AknCapServer. 
 *
 * @lib avkon.lib
 * @since S60 3.0
 */
class RAknKeylock2 : public RAknKeyLock
    {
public:
    /**
     * Connects to the AknCapServer.
     *
     * @return KErrNone if connection was successful, KErrNotSupported if 
     *         CCoeEnv is not accessible. Other system wide error codes are 
     *         also possible in error situations.
     */
    IMPORT_C TInt Connect();
    };

#endif // __AKNKEYLOCK_H__
