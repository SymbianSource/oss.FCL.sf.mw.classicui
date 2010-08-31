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

/**
 @file
 @internalComponent - Internal Symbian test code 
*/

#include <e32std.h>
#include <e32uid.h>
#include <e32base.h>
#include <e32test.h>
#include <apadef.h>
#include "CoeDataStorage.h"
#include <eikenv.h>
void PopulateColorListL()
	{
	CCoeDataStorage* dataStorage = CCoeDataStorage::NewL();
	CleanupStack::PushL(dataStorage);
	dataStorage->PopulateColorArrayL();
	CleanupStack::PopAndDestroy(dataStorage);
	}

GLDEF_C TInt E32Main()
	{
    CTrapCleanup *cleanup=CTrapCleanup::New();
   	if(cleanup == NULL)
		{
		return KErrNoMemory;
		}
   TRAP_IGNORE(PopulateColorListL());
    delete(cleanup);
	return KErrNone;
	}


