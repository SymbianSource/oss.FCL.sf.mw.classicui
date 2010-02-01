/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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

#include <eikstart.h>
#include <AknDef.h>
#include <barsread.h>
#include <bautils.h>
#include <e32property.h>
#include <UikonInternalPSKeys.h>    // KUikLayoutState
#include <eikpriv.rsg>
#include <coedef.h>
#include <eiksvdef.h>
#include <aknconsts.h>
#include <AknsConstants.h>
#include <apgwgnam.h>
#include <akneiksrvs.h>
#include <akneiksrvc.h>
#include "AknNfySrvUi.h"
#include "AknNfySrv.h"
#include <AknWsEventObserver.h>


class RAknEikSrvExtension: public RAknEikAppUiSession
    {
public:
    void DoSignal()
        {
        SendReceive(EEikAppUiExtension, TIpcArgs(EAknCommonNotifierServerRunning, &KNullDesC8));
        }
    };


CAknNfySrvApplication::CAknNfySrvApplication()
    {
    }

void CAknNfySrvApplication::NewAppServerL(CApaAppServer*& aAppServer)
    {
    CAknNfySrv* server = new (ELeave) CAknNfySrv();
    server->SetPriority(EActivePriorityIpcEventsHigh);
    server->SetImplementationFinderL(server);
    aAppServer = &*server;
    }
    
CApaDocument* CAknNfySrvApplication::CreateDocumentL()
    {
    return new (ELeave) CAknNfySrvDocument(*this);
    }

CEikAppUi* CAknNfySrvDocument::CreateAppUiL()
    {
    return new (ELeave) CAknNfySrvAppUi();
    }

CAknNfySrvAppUi::CAknNfySrvAppUi()
    {
    }
    
CAknNfySrvAppUi::~CAknNfySrvAppUi()
    {
    }

void CAknNfySrvAppUi::ConstructL()
    {
    // base call
    CAknNotifierAppServerAppUi::ConstructL();
    }

TBool  CAknNfySrvAppUi::FrameworkCallsRendezvous() const
    {
    RWsSession& wsSession = iEikonEnv->WsSession();

    // To make sure that wserv does not change our priority even we lose foreground.
    wsSession.ComputeMode(RWsSession::EPriorityControlDisabled);

    // Boost our priority similar to eikon server 
    // as eikon server is synchronously dependent of us.
    
    RThread thread; 
#if defined(__EPOC32__)
    thread.SetProcessPriority(EPriorityHigh);
#else
    thread.SetPriority(EPriorityAbsoluteForeground);
#endif

    RAknEikSrvExtension eiksrv;
    TInt err = eiksrv.Connect();
    if (err == KErrNone)
        {
        eiksrv.DoSignal();
        eiksrv.Close();     
        }

    return ETrue;
    }

// actual entry point   
LOCAL_C CApaApplication* NewApplication()
    {
    return new CAknNfySrvApplication();
    }   
    
GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of file
