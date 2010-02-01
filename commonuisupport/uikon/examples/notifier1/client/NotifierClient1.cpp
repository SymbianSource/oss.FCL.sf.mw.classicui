// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <e32base.h>

const TUid KNotifier1Uid = { 0x102826DC };

void DisplayNotifierL()
	{
	RNotifier notifierSession;
	User::LeaveIfError(notifierSession.Connect());
	CleanupClosePushL(notifierSession);

	TInt err = notifierSession.StartNotifier(KNotifier1Uid, KNullDesC8);
	User::LeaveIfError(err);
	User::After(5000000);
	TBuf8<1> dummy;
	notifierSession.UpdateNotifier(KNotifier1Uid, KNullDesC8, dummy);
	User::After(5000000);
	notifierSession.CancelNotifier(KNotifier1Uid);

	CleanupStack::PopAndDestroy(&notifierSession);
	}

GLDEF_C TInt E32Main()
	{
	CTrapCleanup* cleanup = CTrapCleanup::New();
	if (cleanup == NULL)
		{
		return KErrNoMemory;
		}
	TRAPD(err, DisplayNotifierL());
	delete cleanup;
	return err;
    }