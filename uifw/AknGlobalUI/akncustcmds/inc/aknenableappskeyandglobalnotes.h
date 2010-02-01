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
* Description : Declaration of CAknEnableAppsKeyAndGlobalNotes class.
*
*/

#ifndef AKNENABLEAPPSKEYANDGLOBALNOTES_H
#define AKNENABLEAPPSKEYANDGLOBALNOTES_H

#include <e32base.h>
#include <ssm/ssmcustomcommand.h>

/**
* Custom command for initializing some P&S keys used in the system.
*/
NONSHARABLE_CLASS( CAknEnableAppsKeyAndGlobalNotes )
  : public CBase,
    public MSsmCustomCommand
    {
public:

	static CAknEnableAppsKeyAndGlobalNotes* NewL();
    virtual ~CAknEnableAppsKeyAndGlobalNotes();

private: // From MSsmCustomCommand

    TInt Initialize( CSsmCustomCommandEnv* aCmdEnv );
	void Execute( const TDesC8& aParams, TRequestStatus& aRequest );
	void ExecuteCancel();
	void Release();
	void Close();

private:

    CAknEnableAppsKeyAndGlobalNotes();

    };

#endif // AKNENABLEAPPSKEYANDGLOBALNOTES_H
