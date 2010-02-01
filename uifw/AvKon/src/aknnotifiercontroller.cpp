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

// AKNNOTIFIERCONTROLLER.CPP
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// Avkon Notifier Controller
#include <AknNotifierControllerUtilities.h>
#include "akneiksrvc.h"
#include "AknNotifierController.h"

void DoSendToEikonServer(TInt aCmd)
	{
	RAknEikAppUiSession client;
	if ( client.Connect() == KErrNone )
        client.DoNotifierControllerCommand(aCmd);
	client.Close();
	}


EXPORT_C void AknNotifierController::HideAllNotifications(TBool aHide)
	{
    DoSendToEikonServer(aHide?
        CAknNotifierControllerUtility::EDoStop:
        CAknNotifierControllerUtility::EDoAllow
		);
	}

EXPORT_C void AknNotifierController::CancelAllNotifications()
	{
	DoSendToEikonServer(CAknNotifierControllerUtility::DoCancelAll);	
	}
	

// End of File
