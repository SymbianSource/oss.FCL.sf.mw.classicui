/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#include "EIKDBCOB.H"
#include <eikdialg.h>

CEikDialogButtonCommandObserver::CEikDialogButtonCommandObserver(CEikDialog& aDialog)
	: iDialog(aDialog)
	{
	}

CEikDialogButtonCommandObserver::~CEikDialogButtonCommandObserver()
	{
	}

CEikDialogButtonCommandObserver* CEikDialogButtonCommandObserver::NewLC(CEikDialog& aDialog)
	{
	CEikDialogButtonCommandObserver* self=new(ELeave) CEikDialogButtonCommandObserver(aDialog);
	CleanupStack::PushL(self);
	return self;
	}

/**
 * Creates a new CEikDialogButtonCommandObserver with observer aObserver.
 * Returns a pointer to the object and transfers ownership.
 */
CEikDialogButtonCommandObserver* CEikDialogButtonCommandObserver::NewL(CEikDialog& aDialog)
	{
	CEikDialogButtonCommandObserver* self=NewLC(aDialog);
	CleanupStack::Pop();	// self
	return self;
	}

/**
 * Processes the command identified by aCommandId by passing it on to its observer.
 */
void CEikDialogButtonCommandObserver::ProcessCommandL(TInt aCommandId)
	{
	iDialog.TryExitL(aCommandId);
	}

