// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#include <uikon/eikalsrv.h>
#include "TRemoteFactory.h"

static void StartServerL()
	{
	CActiveScheduler* sched = new CActiveScheduler();
	CleanupStack::PushL(sched);
	
	CActiveScheduler::Install(sched);

	CTRemoteFactory* remoteFactory = CTRemoteFactory::NewL();
	CleanupStack::PushL(remoteFactory);
	
	CEikServAlarmAlertServer* server = NULL;

	
	TRAPD(err, server = CEikServAlarmAlertServer::NewL(remoteFactory, remoteFactory->MaxAlarms()));	


	if(err != KErrNone)
		{
		remoteFactory->SendInt(err);
		User::Leave(err);
		}
	
	// A nice litte workaround to get EASAltAlertServerResponseClearAll to be tested.
	remoteFactory->SetServer(server);	

	CleanupStack::PushL(server);
	
	CActiveScheduler::Start();
	
	CleanupStack::PopAndDestroy(3, sched);
	}

GLDEF_C TInt E32Main()
	{
	__UHEAP_MARK;
	
	CTrapCleanup* cleanup = CTrapCleanup::New();

	if (!cleanup)
		{
		return KErrGeneral;
		}

	TRAPD(err, StartServerL());
	delete cleanup;

	__UHEAP_MARKEND;
	return err;
	}
	
