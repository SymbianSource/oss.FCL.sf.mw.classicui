/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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

#include <e32base.h>
#include <AknNotifyStd.h>
#include "AknNotify.h"
#include "AknNotifyDebug.h"
#include <aknSDData.h>
#include <AknCapServerDefs.h>
#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon.hrh>
#else
#include <uikon.hrh>
#include <uiklaf/private/pluginuid.hrh>
#endif
#include <apaserverapp.h>
#include <eikserverapp.h>
#include <AknNotifierWrapper.h>

TInt RNotifier2::Connect()
    {
    TInt ret = KErrNone;
    if (Handle() == NULL)
        {
        _LIT(KServerNameFormat, "%08x_%08x_AppServer");
        TFullName serverName;
        TUid serviceUid = KAknNotifierServiceUid;
        serverName.Format(KServerNameFormat, KUikonUidPluginInterfaceNotifiers, KAknCapServerUid);
        ret = CreateSession(serverName,*reinterpret_cast<TVersion*>(&serviceUid));           
        }
    return ret;
    }     

EXPORT_C CAknNotifyBase::~CAknNotifyBase()
    {
    if (iStarted)
        {
        iNotify.CancelNotifier(iUid);
        }
    
    delete iSecondaryDisplayData;
    iNotify.Close();
    }

CAknNotifyBase::CAknNotifyBase(TUid aUid) : iUid(aUid)
    {
    }

void CAknNotifyBase::ConstructL()
    {
    }

void CAknNotifyBase::StartOrUpdateL(const TDesC8& aBuffer,TDes8& aResponse)
    {
    TInt err = iNotify.Connect();
    User::LeaveIfError(err);

    if (!iStarted)
        {
        err = iNotify.StartNotifier(iUid, aBuffer, aResponse);
        if (err == KErrNone)
            {
            iStarted = ETrue;
            }
        }
    else
        {
        err = iNotify.UpdateNotifier(iUid, aBuffer, aResponse);
        }

#ifdef AKNNOTIFY_RDEBUG_INFO    
    RDebug::Print(_L("CAknNotifyBase::StartOrUpdateL: err %d"),err); 
#endif  
    
    User::LeaveIfError(err);
    }

void CAknNotifyBase::StartOrUpdateAndGetResponseL(
    TRequestStatus& aStatus,
    const TDesC8& aBuffer,
    TDes8& aResponse)
    {
    TInt err = iNotify.Connect();
    User::LeaveIfError(err);

    iStarted = ETrue;
    iNotify.StartNotifierAndGetResponse(aStatus, iUid, aBuffer, aResponse);
    }

EXPORT_C void CAknNotifyBase::CAknNotifyBase_Reserved()
    {
    }

EXPORT_C void CAknNotifyBase::SetSecondaryDisplayData(CAknSDData* aData)
   {
   delete iSecondaryDisplayData;
   iSecondaryDisplayData = aData;
   }
   
CAknSDData* CAknNotifyBase::SecondaryDisplayData()
    {
    return iSecondaryDisplayData;
    }

// End of File
