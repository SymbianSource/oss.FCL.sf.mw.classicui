/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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

// AKNKEYLOCK.CPP
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// Avkon KeyLock Client

#include <AknNotifySignature.h>
#include <AknCapServerDefs.h>
#include <AknNotifierWrapperDefs.h>
#include <apgtask.h>
#include <coemain.h>
#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon.hrh>
#else
#include <uikon.hrh>
#include <uiklaf/private/pluginuid.hrh>
#endif
#include <avkondomainpskeys.h>      // KPSUidAvkonDomain, KAknKeyguardStatus, TAknKeyguardStatus
#include <e32property.h>
#include "aknkeylock.h"
#include "AknNotifierController.h"

// RAknKeyLock

EXPORT_C void RAknKeyLock::EnableKeyLock()
	{
	SendMessage(ELockEnabled);
	}

EXPORT_C void RAknKeyLock::DisableKeyLock()
	{
	SendMessage(ELockDisabled);
	}

EXPORT_C void RAknKeyLock::OfferKeyLock()
	{
	SendMessage(EOfferKeylock);
	}



EXPORT_C TBool RAknKeyLock::IsKeyLockEnabled()
	{
	TInt value;
	TInt err = RProperty::Get(KPSUidAvkonDomain, KAknKeyguardStatus, value);
	if ( err != KErrNone ) 
	    return EFalse;
	switch( value ) 
	    {
	    case EKeyguardLocked:
	    case EKeyguardAutolockEmulation:
	        return ETrue;
	    case EKeyguardNotActive:
	    default:
	        return EFalse;
	    }
	}

EXPORT_C void RAknKeyLock::EnableSoftNotifications(TBool aEnable)
	{
    AknNotifierController::HideAllNotifications(!aEnable);
    }

EXPORT_C void RAknKeyLock::CancelAllNotifications()
	{
    AknNotifierController::CancelAllNotifications();
	}


EXPORT_C void RAknKeyLock::EnableAutoLockEmulation()
	{
	SendMessage(EEnableAutoLockEmulation);
	}


EXPORT_C void RAknKeyLock::DisableWithoutNote()
	{
	SendMessage(EDisableWithoutNote);
	}

EXPORT_C void RAknKeyLock::EnableWithoutNote()
	{
	SendMessage(EEnableWithoutNote);
	}

void RAknKeyLock::SendMessage(TKeyLockNotifierReason aMessage)
	{
	TPckgBuf<SAknNotifierPackage<SAknKeyLockNotifierParams> > data;
	TRequestStatus status;
	data().iParamData.iReason = aMessage;
	StartNotifierAndGetResponse(status,KAknKeyLockNotifierUid, data, data);
	User::WaitForRequest(status);
	CancelNotifier(KAknKeyLockNotifierUid);
	}

// RAknKeyLock2

EXPORT_C TInt RAknKeylock2::Connect()
	{
	TInt ret = KErrNotReady;
	CCoeEnv* coe = CCoeEnv::Static();
	if (!coe)
		{
		return KErrNotSupported; // we need that window group list
		}
    TApaTaskList list(CCoeEnv::Static()->WsSession());
    TApaTask task = list.FindApp(KAknCapServerUid);
    if (task.Exists() )
        {
        if ( Handle() == NULL)
            {
            _LIT(KServerNameFormat, "%08x_%08x_AppServer");
	        TFullName serverName;
	        TUid serviceUid = KAknNotifierServiceUid;
	        serverName.Format(KServerNameFormat, KUikonUidPluginInterfaceNotifiers, KAknCapServerUid);
			ret = CreateSession(serverName,*reinterpret_cast<TVersion*>(&serviceUid));           
            }
        else 
        	{
        	ret = KErrNone; // or should this be KErrAlreadyExist		
        	}
        }
	return ret;
	}


// End of File
