/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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

#include <e32property.h>
#include <e32std.h> // needed because activeidle2domainpskeys.h doesn't include this
#include "AknCapServerEntry.h"

#define KPhoneAppUid TUid::Uid(0x100058B3)

TBool AknPhoneKeyForwarder::ForwardKeyToPhoneApp(TAny* aKeyEvent)
    {
    RWsSession& ws = CCoeEnv::Static()->WsSession();
    TApaTaskList list(ws);
    TApaTask phone = list.FindApp(KPhoneAppUid);
    if (phone.Exists())
        { 
        TKeyEvent& key  = *(TKeyEvent*)aKeyEvent;
        
        // make sure that phone will receive focus before sending key to it
        ws.SetWindowGroupOrdinalPosition(phone.WgId(), 0);
        
        // send key event
        phone.SendKey(key);

        // and check if the up event has been delivered to us meanwhile
        if (STATIC_CAST(CAknCapAppServerAppUi*,CEikonEnv::Static()->AppUi())->iUpReceived)
            {
            TWsEvent event;
            event.SetType(EEventKeyUp);
            *event.Key()=key;
            event.SetTimeNow();
            ws.SendEventToWindowGroup(phone.WgId(), event);
            }
        }

    return EFalse; // don't retry
    }

TBool AknPhoneKeyForwarder::ForwardUpEventToPhoneApp(TAny* aKeyEvent)
    {
    RWsSession& ws = CCoeEnv::Static()->WsSession();
    TApaTaskList list(ws);
    TApaTask phone = list.FindApp(KPhoneAppUid);
    if (phone.Exists())
        { 
        TWsEvent event;
        event.SetType(EEventKeyUp);
        *event.Key()=*(TKeyEvent*)aKeyEvent;
        event.SetTimeNow();
        ws.SendEventToWindowGroup(phone.WgId(), event);
        }
    
    return EFalse; // no need to re-run
    }

// End of file
