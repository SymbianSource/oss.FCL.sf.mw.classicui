/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  RNotifier handler for dynamic soft notifications.
*
*/

#include "AknDynamicNotifier.h"
#include <AknNotifierWrapperDefs.h>
#include <AknCapServerDefs.h>
#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon.hrh>
#else
#include <uikon.hrh>
#include <uiklaf/private/pluginuid.hrh>
#endif

//-----------------------------------------------------------------------------
// RDynNotifier::Connect
//-----------------------------------------------------------------------------
//   
TInt RDynNotifier::Connect()
    {
    TInt ret = KErrNone;
    if ( Handle() == NULL)
        {
        _LIT(KServerNameFormat, "%08x_%08x_AppServer");
        TFullName serverName;
        TUid serviceUid = KAknNotifierServiceUid;
        serverName.Format(KServerNameFormat, KUikonUidPluginInterfaceNotifiers, KAknCapServerUid);
        ret = CreateSession(serverName,*reinterpret_cast<TVersion*>(&serviceUid));           
        }
  return ret;
  }   

//-----------------------------------------------------------------------------
// CAknDynamicNotifier::~CAknDynamicNotifier
//-----------------------------------------------------------------------------
//   
CAknDynamicNotifier::~CAknDynamicNotifier()
    {
    if( iStarted )
        {
        iNotify.CancelNotifier( iUid );
        }
    iNotify.Close();
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotifier::CAknDynamicNotifier
//-----------------------------------------------------------------------------
//   
CAknDynamicNotifier::CAknDynamicNotifier( TUid aUid ) : 
    iUid( aUid )
    {
    }
    
//-----------------------------------------------------------------------------
// CAknDynamicNotifier::StartOrUpdate
//-----------------------------------------------------------------------------
//   
TInt CAknDynamicNotifier::StartOrUpdate(
    const TDesC8& aBuffer,
    TDes8& aResponse )
    {
    TInt err = iNotify.Connect();
    if( !err )
        {
        if( !iStarted )
            {
            err = iNotify.StartNotifier( iUid, aBuffer, aResponse );
            if( !err )
                {
                iStarted = ETrue;
                }
            }
        else
            {
            err = iNotify.UpdateNotifier( iUid, aBuffer, aResponse );
            }
        }

    return err;
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotifier::StartOrUpdate
//-----------------------------------------------------------------------------
//   
TInt CAknDynamicNotifier::StartOrUpdate(
    TRequestStatus& aStatus,
    const TDesC8& aBuffer,
    TDes8& aResponse)
    {
    TInt err = iNotify.Connect();
    if( !err )
        {
        iStarted = ETrue;
        iNotify.StartNotifierAndGetResponse( aStatus, iUid, aBuffer, aResponse );
        }
    return err;
    }


// End of File
